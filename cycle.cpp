#include "cycle.h"
#include "path.h"

void generate_cycle_graph(NGG_UINT const & N) {
    if(N == 1) {
        writer.write_nodes(N);
    } else {
        generate_path_graph(N);
        if(N > 2) {
            writer.write_edge(N-1, 0);
        }
    }
}
