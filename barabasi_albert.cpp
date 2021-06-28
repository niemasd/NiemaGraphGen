#include "barabasi_albert.h"

void generate_ba_graph(NGG_UINT const & N, NGG_UINT const & M) {
    // useful constants
    NGG_UINT const TWO_TIMES_TOTAL_NUM_EDGES = 2*(N-M)*M; // N-M new nodes will be created, each with M edges

    // write nodes up-front
    writer.write_nodes(N);

    // set up repeated nodes list from which to select targets randomly
    vector<NGG_UINT> repeated_nodes;
    repeated_nodes.reserve(TWO_TIMES_TOTAL_NUM_EDGES);
    for(NGG_UINT i = 0; i < M; ++i) {
        repeated_nodes.push_back(i);
    }

    // create new nodes + edges
    unordered_set<NGG_UINT> targets;
    targets.reserve(2*M); // reserve 2M slots (will store M elements)
    for(NGG_UINT new_node = M; new_node < N; ++new_node) {
        targets.clear();
        while(targets.size() < M) {
            targets.insert(repeated_nodes[uniform_int_distribution<NGG_UINT>(0,repeated_nodes.size()-1)(RNG)]);
        }
        for(NGG_UINT const & target : targets) {
            writer.write_edge(new_node, target);
            repeated_nodes.push_back(new_node);
            repeated_nodes.push_back(target);
        }
    }
}
