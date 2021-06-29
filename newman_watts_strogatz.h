#ifndef NEWMAN_WATTS_STROGATZ_H
#define NEWMAN_WATTS_STROGATZ_H
#include "common.h"

/**
 * Generate a Newman-Watts-Strogatz graph
 * https://networkx.org/documentation/stable/reference/generated/networkx.generators.random_graphs.newman_watts_strogatz_graph.html
 * @param N total number of nodes in the graph
 * @param K degree of each node (must be even)
 * @param P rewiring probability
 */
void generate_nws_graph(NGG_UINT const & N, NGG_UINT const & K, long double const & P);
#endif
