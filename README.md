# NiemaGraphGen
NiemaGraphGen (NGG) is a collection of efficient C++ implementations of graph generators for use in sampling contact networks in global-scale pandemic simulations. Importantly, NGG avoids actually storing the graph in memory and instead is intended to be used in a data streaming pipeline. Currently, NGG implements generators for the following types of graphs:

* [Barabási–Albert model](https://en.wikipedia.org/wiki/Barab%C3%A1si%E2%80%93Albert_model) ([Barabási & Albert, 1999](https://doi.org/10.1126/science.286.5439.509))
* [Barbell graph](https://en.wikipedia.org/wiki/Barbell_graph)
* [Complete graph](https://en.wikipedia.org/wiki/Complete_graph)
* [Cycle graph](https://en.wikipedia.org/wiki/Cycle_graph)
* [Empty graph](https://en.wikipedia.org/wiki/Null_graph#Edgeless_graph) (not particularly useful)
* [Erdős–Rényi model](https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model) (Erdős & Rényi, 1959)
* [Newman–Watts–Strogatz model](https://doi.org/10.1016/S0375-9601(99)00757-4) ([Newman & Watts, 1999](https://doi.org/10.1016/S0375-9601(99)00757-4))
* [Path graph](https://en.wikipedia.org/wiki/Path_graph)
* [Ring lattce](https://runestone.academy/runestone/books/published/complex/SmallWorldGraphs/RingLattice.html)

# Installation
NGG is written in C++ and has no dependencies beyond a modern C++ compiler (and `make` for convenience). You can simply download the latest release tarball (or clone the repo) and compile with `make`:

```bash
git clone https://github.com/niemasd/NiemaGraphGen.git
cd NiemaGraphGen
make
sudo mv ngg_* /usr/local/bin/ # optional; install NGG executables globally
```

# Usage
Each graph generator is implemented as its own `ngg_???` executable. To view each generator's usage message, simply run the executable with the `-h` or `--help` argument:

```bash
ngg_barabasi_albert -h # show the usage message for the Barabási–Albert generator
```

# Advanced Compilation Options
The default compilation options (i.e., by downloading the NGG source code and running `make`) should be sufficient for most use-cases. However, NGG supports some advanced compilation options that may be of interest.

### Changing the Size of Unsigned Integers
NGG represents each node using an unsigned integer. By default, NGG uses 32-bit unsigned integers, which supports up to 2^32 - 1 = 4,294,967,295 nodes in a single graph. This is more than half the population of the Earth, so it should be sufficient for most simulation studies, but by changing the compilation flags, you can change this size as desired. In general, the larger the unsigned integer size, the larger networks you can simulate, but the more memory NGG will consume. To change the size of unsigned integers, you can change the following line in the [`Makefile`](Makefile):

```make
UINTFLAG=-DNGG_UINT_8  #  8-bit (up to 2^8  - 1 = 255 nodes)
UINTFLAG=-DNGG_UINT_16 # 16-bit (up to 2^16 - 1 = 65,535 nodes)
UINTFLAG=-DNGG_UINT_32 # 32-bit (up to 2^32 - 1 = 4,294,967,295 nodes) (default)
UINTFLAG=-DNGG_UINT_64 # 64-bit (up to 2^64 - 1 = 18,446,744,073,709,551,615 nodes)
```

### Changing the Output Format
By default, NGG outputs contact networks in the [FAVITES format](https://github.com/niemasd/FAVITES/wiki/File-Formats#contact-network-file-format). However, for ultra-large simulation studies, the resulting files may be massive. To address this, NGG also supports a "compact" binary output format, which is defined as follows:

* **First Byte:** Header (`000000AA`)
  * The 6 leftmost bits are currently unused (hence the `0` values)
  * `AA` represents the number of bytes *b* per integer (`00` = 1, `01` = 2, `10` = 4, and `11` = 8)
* **Next *b* Bytes:** The total number of nodes in the graph
* **Remaining Bytes:** The edges (*u*,*v*) in the graph represented as blocks of 2*b* bytes
  * The first *b* bytes in a block reprent *u*
  * The second *b* bytes in a block represent *v*

Both output formats should be fairly nicely compressible, which can further reduce output filesize (e.g. by piping to `gzip` to compress the stream).

To change the output format, you can change the following line in the [`Makefile`](Makefile):

```make
OUTFLAG=-DOUTFAVITES # FAVITES format
OUTFLAG=-DOUTCOMPACT # compact format
```

# Citing NiemaGraphGen
A manuscript is in the works, but until it's released, please cite this GitHub repository.
