#include "cycle.h"
#include "path.h"

void generate_cycle_graph(NGG_UINT const & N) {
    generate_path_graph(N);
    writer.write_edge(N-1, 0);
}
