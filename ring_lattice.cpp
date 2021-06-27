#include "common.h"
#include "ring_lattice.h"

void generate_ring_lattice_graph(unsigned long long const & N, unsigned long long const & K) {
    unsigned long long const K_OVER_2 = K / 2;
    writer.write_nodes(N);
    for(unsigned long long i = 0; i < N; ++i) {
        for(unsigned long long d = 1; d <= K_OVER_2; ++d) {
            writer.write_edge(i, (i+d)%N);
        }
    }
}
/*
void generate_complete_graph(unsigned long long const & N) {
    unsigned long long const N_MINUS_1 = N-1;
    writer.write_nodes(N);
    for(unsigned long long i = 0; i < N_MINUS_1; ++i) {
        for(unsigned long long j = i+1; j < N; ++j) {
            writer.write_edge(i, j);
        }
    }
}
*/
