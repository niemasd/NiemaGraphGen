#include "path.h"

void generate_path_graph(NGG_UINT const & N) {
    NGG_UINT const N_MINUS_1 = N-1;
    writer.write_nodes(N);
    for(NGG_UINT i = 0; i < N_MINUS_1; ++i) {
        writer.write_edge(i, i+1);
    }
}
