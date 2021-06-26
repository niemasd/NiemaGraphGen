#include <cmath>
#include "common.h"
#include "erdos_renyi.h"
using namespace std;

// https://networkx.org/documentation/stable/_modules/networkx/generators/random_graphs.html#fast_gnp_random_graph
void generate_er_graph(unsigned long long const & N, long double const & P) {
    if(P < 0 || P > 1) {
        error("Probability must be in range [0,1]");
    }
    long double const LP = log(ONE_LD - P);
    unsigned long long v = 1;
    unsigned long long w = (unsigned long long)-1;
    while(v < N) {
        w += (ONE_ULL + (unsigned long long)(log(ONE_LD - uniform_real_distribution<long double>(0,1)(RNG)) / LP));
        while(w >= v && v < N) {
            w -= v++;
        }
        if(v < N) {
            writer.write_edge(v, w);
        }
    }
}
