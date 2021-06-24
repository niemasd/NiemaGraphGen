#include <iostream>
#include "common.h"
#include "complete.h"
using namespace std;

void generate_ba_graph(unsigned long long const & N, unsigned long long const & M) {
    if(N < M) {
        cerr << "Number of nodes must be larger than number of edges from new" << endl; exit(1);
    }
    for(unsigned long long new_node = M; new_node < N; ++new_node) {
        for(unsigned long long target : sample_range_no_replacement(0, new_node-1, M)) {
            cout << "EDGE\t" << new_node << '\t' << target << "\t.\tu" << endl;
        }
    }
}
