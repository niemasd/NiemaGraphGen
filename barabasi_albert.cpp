#include "barabasi_albert.h"
#include "common.h"

void generate_ba_graph(unsigned long long const & N, unsigned long long const & M) {
    error("The generate_ba_graph() function has a bug and is incorrect");
    writer.write_nodes(N);
    for(unsigned long long new_node = M; new_node < N; ++new_node) {
        for(unsigned long long target : sample_range_no_replacement(0, new_node-1, M)) {
            writer.write_edge(new_node, target);
        }
    }
}
