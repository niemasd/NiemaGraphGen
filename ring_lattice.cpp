#include "ring_lattice.h"

void generate_ring_lattice_graph(NGG_UINT const & N, NGG_UINT const & K) {
    NGG_UINT const K_OVER_2 = K / 2;
    writer.write_nodes(N);
    for(NGG_UINT i = 0; i < N; ++i) {
        for(NGG_UINT d = 1; d <= K_OVER_2; ++d) {
            writer.write_edge(i, (i+d)%N);
        }
    }
}
