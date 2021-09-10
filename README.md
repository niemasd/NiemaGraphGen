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
