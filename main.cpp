#include <cstdlib>
#include <iostream>
#include <string.h>
#include "common.h"
using namespace std;

// NiemaGraphGen version
#ifndef NGG_VERSION
#define NGG_VERSION "0.0.1"
#endif

// RNG seed environment variable
#ifndef RNG_SEED_ENV_VAR
#define RNG_SEED_ENV_VAR "NGG_RNG_SEED"
#endif

// import generator
#if   defined BA       // Barabasi-Albert graph
#include "barabasi_albert.h"
#elif defined BARBELL  // barbell graph
#include "barbell.h"
#elif defined COMPLETE // complete graph
#include "complete.h"
#elif defined EMPTY    // empty graph
// no imports needed
#elif defined ER       // Erdos-Renyi graph
#include "erdos_renyi.h"
#endif

// description
#ifndef DESCRIPTION
#define DESCRIPTION string("NiemaGraphGen v") + string(NGG_VERSION)
#endif

// opening message
#ifndef OPEN_MESSAGE
const string OPEN_MESSAGE = DESCRIPTION + string(
#if   defined OUTFAVITES // FAVITES output format
" (FAVITES Output Format)"
#elif defined OUTCOMPACT // compact output format
" (Compact Output Format)"
#endif
#if   defined BA       // Barabasi-Albert graph
" (Barabasi-Albert)"
#elif defined BARBELL  // barbell graph
" (Barbell Graph)"
#elif defined COMPLETE // complete graph
" (Complete Graph)"
#elif defined EMPTY    // empty graph
" (Empty Graph)"
#elif defined ER       // Erdos-Renyi graph
" (Erdos-Renyi)"
#endif
);
#endif

// number of user args
#ifndef NUM_USER_ARGS
#if   defined BA       // Barabasi-Albert graph
#define NUM_USER_ARGS 3
#elif defined BARBELL  // barbell graph
#define NUM_USER_ARGS 3
#elif defined COMPLETE // complete graph
#define NUM_USER_ARGS 2
#elif defined EMPTY    // empty graph
#define NUM_USER_ARGS 2
#elif defined ER       // Erdos-Renyi graph
#define NUM_USER_ARGS 3
#endif
#endif

// main driver
int main(int argc, char** argv) {
    // check usage
    if(argc != NUM_USER_ARGS || strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0) {
        error(OPEN_MESSAGE + "\nUSAGE: " + argv[0]
        #if   defined BA       // Barabasi-Albert graph
            + " <num_nodes> <num_edges_from_new>"
        #elif defined BARBELL  // barbell graph
            + "<num_nodes_complete> <num_nodes_path>"
        #elif defined COMPLETE // complete graph
            + " <num_nodes>"
        #elif defined EMPTY    // empty graph
            + " <num_nodes>"
        #elif defined ER       // Erdos-Renyi graph
            + " <num_nodes> <prob_edge_creation>"
        #endif
        );
    }

    // check if user provided a seed
    const char* const rng_seed_env = getenv(RNG_SEED_ENV_VAR);
    if(rng_seed_env != nullptr) {
        int tmp = atoi(rng_seed_env);
        if(tmp != 0) {
            RNG_SEED = tmp; RNG = default_random_engine(RNG_SEED);
        }
    }

    // parse parameter(s)
    #if   defined BA       // Barabasi-Albert graph
        unsigned long long const N = stoull(argv[1]);
        unsigned long long const M = stoull(argv[2]);
        if(N < M) {
            error("Number of nodes must be larger than number of edges from new");
        }
    #elif defined BARBELL  // barbell graph
        unsigned long long const M1 = stoull(argv[1]);
        unsigned long long const M2 = stoull(argv[2]);
    #elif defined COMPLETE // complete graph
        unsigned long long const N = stoull(argv[1]);
    #elif defined EMPTY    // empty graph
        unsigned long long const N = stoull(argv[1]);
    #elif defined ER       // Erdos-Renyi graph
        unsigned long long const N = stoull(argv[1]);
        long double const P = stold(argv[2]);
        if(P < 0 || P > 1) {
            error("Probability must be in range [0,1]");
        }
    #endif

    // generate graph
    #if   defined BA       // Barabasi-Albert graph
        generate_ba_graph(N, M);
    #elif defined BARBELL  // barbell graph
        generate_barbell_graph(M1, M2);
    #elif defined COMPLETE // complete graph
        generate_complete_graph(N);
    #elif defined EMPTY    // empty graph
        writer.write_nodes(N);
    #elif defined ER       // Erdos-Renyi graph
        generate_er_graph(N, P);
    #endif
    return 0;
}
