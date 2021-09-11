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

## Installation
NGG is written in C++ and has no dependencies beyond a modern C++ compiler (and `make` for convenience). You can simply download the latest release tarball (or clone the repo) and compile with `make`:

```bash
git clone https://github.com/niemasd/NiemaGraphGen.git
cd NiemaGraphGen
make
sudo mv ngg_* /usr/local/bin/ # optional; install NGG executables globally
```

### Changing Size of Unsigned Integers
NGG represents each node using an unsigned integer. By default, NGG uses 32-bit unsigned integers, which supports up to 2^32 - 1 = 4,294,967,295 nodes in a single graph. This is more than half the population of the Earth, so it should be sufficient for most simulation studies, but by changing the compilation flags, you can change this size as desired. In general, the larger the unsigned integer size, the larger networks you can simulate, but the more memory NGG will consume. You can change the following line in the [`Makefile`](Makefile):

```make
UINTFLAG=-DNGG_UINT_8  #  8-bit (up to 2^8  - 1 = 255 nodes)
UINTFLAG=-DNGG_UINT_16 # 16-bit (up to 2^16 - 1 = 65,535 nodes)
UINTFLAG=-DNGG_UINT_32 # 32-bit (up to 2^32 - 1 = 4,294,967,295 nodes) (default)
UINTFLAG=-DNGG_UINT_64 # 64-bit (up to 2^64 - 1 = 18,446,744,073,709,551,615 nodes)
```

## Usage
Each graph generator is implemented as its own `ngg_???` executable. To view each generator's usage message, simply run the executable with the `-h` or `--help` argument:

```bash
ngg_barabasi_albert -h # show the usage message for the Barabási–Albert generator
```

# Citing NiemaGraphGen
A manuscript is in the works, but until it's released, please cite this GitHub repository.
