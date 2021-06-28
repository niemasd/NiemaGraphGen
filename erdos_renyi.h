#ifndef ERDOS_RENYI_H
#define ERDOS_RENYI_H
#include "common.h"

/**
 * Generate a graph under the Erdos-Renyi model
 * @param N total number of nodes in the graph
 * @param P probability for edge creation
 */
void generate_er_graph(NGG_UINT const & N, long double const & P);
#endif
