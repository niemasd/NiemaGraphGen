#ifndef BARBELL_H
#define BARBELL_H
#include "common.h"

/**
 * Generate a barbell graph
 * @param M1 number of nodes in each of the two complete subgraphs
 * @param M2 number of nodes in the path connecting the two complete subgraphs
 */
void generate_barbell_graph(NGG_UINT const & M1, NGG_UINT const & M2);
#endif
