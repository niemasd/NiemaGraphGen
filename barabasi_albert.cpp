#include "barabasi_albert.h"

void generate_ba_graph(NGG_UINT const & N, NGG_UINT const & M) {
    error("The generate_ba_graph() function has a bug and is incorrect");
    writer.write_nodes(N);
    for(NGG_UINT new_node = M; new_node < N; ++new_node) {
        for(NGG_UINT target : sample_range_no_replacement(0, new_node-1, M)) {
            writer.write_edge(new_node, target);
        }
    }
}
