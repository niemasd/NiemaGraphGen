#ifndef RING_LATTICE_H
#define RING_LATTICE_H
#include "common.h"

/**
 * Generate a ring lattice graph
 * @param N total number of nodes in the graph
 * @param K degree of each node (must be even)
 */
void generate_ring_lattice_graph(NGG_UINT const & N, NGG_UINT const & K);
#endif
