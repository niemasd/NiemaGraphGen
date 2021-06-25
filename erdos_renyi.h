#ifndef ERDOS_RENYI_H
#define ERDOS_RENYI_H
/**
 * Generate a graph under the Erdos-Renyi model
 * @param N total number of nodes in the graph
 * @param P probability for edge creation
 */
void generate_er_graph(unsigned long long const & N, long double const & P);
#endif
