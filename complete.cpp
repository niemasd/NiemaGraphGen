#include <iostream>
#include "common.h"
#include "complete.h"
using namespace std;

void generate_complete_graph(unsigned long long const & N) {
    unsigned long long const N_MINUS_1 = N-1;
    for(unsigned long long i = 0; i < N_MINUS_1; ++i) {
        for(unsigned long long j = i+1; j < N; ++j) {
            writer.write_edge(i, j);
        }
    }
}
