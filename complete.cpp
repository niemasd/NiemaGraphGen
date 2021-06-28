#include "complete.h"

void generate_complete_graph(NGG_UINT const & N) {
    NGG_UINT const N_MINUS_1 = N-1;
    writer.write_nodes(N);
    for(NGG_UINT i = 0; i < N_MINUS_1; ++i) {
        for(NGG_UINT j = i+1; j < N; ++j) {
            writer.write_edge(i, j);
        }
    }
}
