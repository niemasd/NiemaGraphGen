#ifndef BARABASI_ALBERT_H
#define BARABASI_ALBERT_H
#include "common.h"

/**
 * Generate a graph under the Barabasi-Albert model
 * @param N total number of nodes in the graph
 * @param M number of edges from a new node
 */
void generate_ba_graph(NGG_UINT const & N, NGG_UINT const & M);
#endif
