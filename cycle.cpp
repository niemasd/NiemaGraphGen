#include "cycle.h"
#include "common.h"
#include "path.h"

void generate_cycle_graph(unsigned long long const & N) {
    generate_path_graph(N);
    writer.write_edge(N-1, 0);
}
