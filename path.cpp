#include "common.h"
#include "path.h"
using namespace std;

void generate_path_graph(unsigned long long const & N) {
    unsigned long long const N_MINUS_1 = N-1;
    writer.write_nodes(N);
    for(unsigned long long i = 0; i < N_MINUS_1; ++i) {
        writer.write_edge(i, i+1);
    }
}
