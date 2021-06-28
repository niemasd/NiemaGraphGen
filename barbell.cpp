#include "barbell.h"

void generate_barbell_graph(NGG_UINT const & M1, NGG_UINT const & M2) {
    // create useful constants and write nodes
    NGG_UINT const M1_MINUS_1 = M1-1;
    NGG_UINT const TWO_M1 = 2*M1;
    NGG_UINT const TWO_M1_MINUS_1 = TWO_M1-1;
    NGG_UINT const NUM_NODES = TWO_M1 + M2;
    NGG_UINT const NUM_NODES_MINUS_1 = NUM_NODES-1;
    writer.write_nodes(NUM_NODES);

    // 0 to M1-1 are the first complete graph
    for(NGG_UINT i = 0; i < M1_MINUS_1; ++i) {
        for(NGG_UINT j = i+1; j < M1; ++j) {
            writer.write_edge(i, j);
        }
    }

    // M1 to 2M1-1 are the second complete graph
    for(NGG_UINT i = M1; i < TWO_M1_MINUS_1; ++i) {
        for(NGG_UINT j = i+1; j < TWO_M1; ++j) {
            writer.write_edge(i, j);
        }
    }

    // 2M1 to 2M1+M2-1 are the path
    for(NGG_UINT i = TWO_M1; i < NUM_NODES_MINUS_1; ++i) {
        writer.write_edge(i, i+1);
    }

    // connect each complete graph to the path
    writer.write_edge(0, TWO_M1);             // node 0  (first complete graph)  <---> node 2M1 (left side of path)
    writer.write_edge(M1, NUM_NODES_MINUS_1); // node M1 (second complete graph) <---> node N-1 (right side of path)
}
