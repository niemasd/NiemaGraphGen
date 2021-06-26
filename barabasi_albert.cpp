#include "barabasi_albert.h"
#include "common.h"
using namespace std;

void generate_ba_graph(unsigned long long const & N, unsigned long long const & M) {
    if(N < M) {
        error("Number of nodes must be larger than number of edges from new");
    }
    for(unsigned long long new_node = M; new_node < N; ++new_node) {
        for(unsigned long long target : sample_range_no_replacement(0, new_node-1, M)) {
            writer.write_edge(new_node, target);
        }
    }
}
