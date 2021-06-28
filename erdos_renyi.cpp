#include <cmath>
#include "erdos_renyi.h"

// https://networkx.org/documentation/stable/_modules/networkx/generators/random_graphs.html#fast_gnp_random_graph
void generate_er_graph(NGG_UINT const & N, long double const & P) {
    long double const LP = log(ONE_LD - P);
    NGG_UINT v = 1;
    NGG_UINT w = (NGG_UINT)-1;
    writer.write_nodes(N);
    while(v < N) {
        w += (ONE_ULL + (NGG_UINT)(log(ONE_LD - uniform_real_distribution<long double>(0,1)(RNG)) / LP));
        while(w >= v && v < N) {
            w -= v++;
        }
        if(v < N) {
            writer.write_edge(v, w);
        }
    }
}
