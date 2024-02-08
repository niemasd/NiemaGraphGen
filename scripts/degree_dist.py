#! /usr/bin/env python3
'''
Script to calculate degree distribution from one or more NGG graphs
'''

# imports
from gzip import open as gopen
from seaborn import relplot
from struct import unpack
import argparse
import matplotlib.pyplot as plt

# constants
INPUT_FORMATS = ['txt', 'txt.gz', 'ngg', 'ngg.gz']
NGG_INT_SIZE = {0b00: 1, 0b01: 2, 0b10: 4, 0b11: 8}
NGG_INT_SIZE_LETTER = {1: 'B', 2: 'H', 4: 'I', 8: 'L'}
PLOT_KINDS = ['line', 'scatter']

# parse user args
def parse_args():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('-m', '--merge_inputs', action='store_true', help="Merge Inputs into Single Degree Distribution")
    parser.add_argument('-f', '--force_format', required=False, type=str, default=None, help="Force Input Format (options: %s)" % ' | '.join(INPUT_FORMATS))
    parser.add_argument('-ot', '--output_tsv', required=False, type=str, default=None, help="Output File (TSV)")
    parser.add_argument('-op', '--output_pdf', required=False, type=str, default=None, help="Output File (PDF)")
    parser.add_argument('-k', '--kind', required=False, type=str, default='line', help="PDF Plot Kind (options: %s)" % ', '.join(PLOT_KINDS))
    parser.add_argument('-t', '--title', required=False, type=str, default=None, help="PDF Title")
    parser.add_argument('-xl', '--xlabel', required=False, type=str, default="Degree", help="PDF X-Axis Label")
    parser.add_argument('-yl', '--ylabel', required=False, type=str, default="Count", help="PDF Y-Axis Label")
    parser.add_argument('-xm', '--xmin', required=False, type=int, default=None, help="PDF X-Axis Minimum")
    parser.add_argument('-xM', '--xmax', required=False, type=int, default=None, help="PDF X-Axis Maximum")
    parser.add_argument('-ym', '--ymin', required=False, type=int, default=None, help="PDF Y-Axis Minimum")
    parser.add_argument('-yM', '--ymax', required=False, type=int, default=None, help="PDF Y-Axis Maximum")
    parser.add_argument('--xlog', action='store_true', help="PDF Log-Scaled X-Axis")
    parser.add_argument('--ylog', action='store_true', help="PDF Log-Scaled Y-Axis")
    parser.add_argument('input_files', metavar='filename', type=str, nargs='+', help="Input NiemaGraphGen file(s)")
    args = parser.parse_args()
    if args.output_tsv is None and args.output_pdf is None:
        raise ValueError("Must specify either output TSV or output PDF (or both)")
    if args.force_format is not None and args.force_format not in INPUT_FORMATS:
        raise ValueError("Invalid input format: %s" % args.force_format)
    if args.kind not in PLOT_KINDS:
        raise ValueError("Invalid plot kind: %s (options: %s)" % (args.kind, ', '.join(PLOT_KINDS)))
    return args

# count degrees from contact network
def count_degrees(fn, file_format=None):
    # check file format
    if file_format is None:
        for ext in INPUT_FORMATS:
            if fn.lower().strip().endswith(ext):
                file_format = ext; break

    # invalid file format
    if file_format is None:
        raise ValueError("Invalid file format: %s" % fn)

    # FAVITES format
    elif file_format.startswith('txt'):
        if file_format.endswith('.gz'):
            f = gopen(fn, 'rt')
        else:
            f = open(fn, 'r')
        degree = dict() # degree[node] = degree of `node`
        for l in f:
            if l.startswith('NODE\t'):
                node = l.split('\t')[1].strip()
                if node in degree:
                    raise ValueError("Duplicate node: %s (%s)" % (node, fn))
                degree[node] = 0
            elif l.startswith('EDGE\t'):
                u, v = l.split('\t')[1:3]
                degree[u.strip()] += 1; degree[v.strip()] += 1

    # compact format
    elif file_format.startswith('ngg'):
        if file_format.endswith('.gz'):
            f = gopen(fn, 'rb')
        else:
            f = open(fn, 'rb')
        header = unpack('B', f.read(1))[0]
        int_size = NGG_INT_SIZE[header & 0b00000011]
        int_size_letter = NGG_INT_SIZE_LETTER[int_size]
        n = unpack(int_size_letter, f.read(int_size))[0]
        degree = [0 for _ in range(n)] # degree[node] = degree of `node`
        while True:
            chunk = f.read(int_size)
            if len(chunk) == 0:
                break # reached end of file
            u = unpack(int_size_letter, chunk)[0]
            v = unpack(int_size_letter, f.read(int_size))[0]
            degree[u] += 1; degree[v] += 1

    # count degrees and return
    count = dict() # count[degree] = number of people with degree `degree`
    if isinstance(degree, dict):
        degree_iter = degree.values()
    else:
        degree_iter = degree
    for d in degree_iter:
        if d not in count:
            count[d] = 0
        count[d] += 1
    return count

# main program
if __name__ == "__main__":
    # parse args and input files
    args = parse_args()
    counts = dict() # counts[fn][degree] = number of people in `fn` with degree `degree`
    for fn in args.input_files:
        counts[fn] = count_degrees(fn, file_format=args.force_format)
    max_degree = max(d for fn, degree_counts in counts.items() for d in degree_counts.values())

    # write TSV and/or prep for plotting
    if args.output_tsv is not None:
        tsv_f = open(args.output_tsv, 'w')
        tsv_f.write('Degree\t')
        if args.merge_inputs:
            tsv_f.write("Count")
        else:
            tsv_f.write('\t'.join(args.input_files))
        tsv_f.write('\n')
        for d in range(max_degree+1):
            tsv_f.write('%d' % d)
            if args.merge_inputs:
                tot = 0
                for fn in args.input_files:
                    if d in counts[fn]:
                        tot += counts[fn][d]
                tsv_f.write('\t%d' % tot)
            else:
                for fn in args.input_files:
                    if d in counts[fn]:
                        tsv_f.write('\t%d' % counts[fn][d])
                    else:
                        tsv_f.write('\t0')
            tsv_f.write('\n')

    # prep for plotting
    if args.output_pdf:
        x = list(); y = list(); h = list()
        if args.merge_inputs:
            h = None
        for d in range(max_degree+1):
            if args.merge_inputs:
                x.append(d); tot = 0
                for fn in args.input_files:
                    if d in counts[fn]:
                        tot += counts[fn][d]
                y.append(tot)
            else:
                for fn in args.input_files:
                    x.append(d); h.append(fn)
                    if d in counts[fn]:
                        c = counts[fn][d]; y.append(c)
                    else:
                        y.append(0)

        # create plot
        fig = relplot(x=x, y=y, hue=h, kind=args.kind)
        if args.title is not None:
            plt.title(args.title)
        plt.xlabel(args.xlabel)
        plt.ylabel(args.ylabel)
        if args.xmin is None:
            args.xmin = 0
        if args.ymin is None:
            args.ymin = 0
        if args.xlog:
            plt.xscale('log')
            if args.xmin == 0:
                args.xmin = 1
        if args.ylog:
            plt.yscale('log')
            if args.ymin == 0:
                args.ymin = 1
        plt.xlim(xmin=args.xmin, xmax=args.xmax)
        plt.ylim(ymin=args.ymin, ymax=args.ymax)
        plt.tight_layout()
        fig.savefig(args.output_pdf, format='pdf', bbox_inches='tight')
