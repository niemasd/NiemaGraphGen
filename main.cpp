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
#if defined COMPLETE // complete graph
#include "complete.h"
#endif

// description
#ifndef DESCRIPTION
#define DESCRIPTION string("NiemaGraphGen v") + string(NGG_VERSION)
#endif

// opening message
#ifndef OPEN_MESSAGE
const string OPEN_MESSAGE = DESCRIPTION + string(
#if defined COMPLETE // complete graph
" (Complete Graph)"
#endif
);
#endif

// number of user args
#ifndef NUM_USER_ARGS
#if defined COMPLETE // complete graph
#define NUM_USER_ARGS 2
#endif
#endif

// main driver
int main(int argc, char** argv) {
    // check usage
    if(argc != NUM_USER_ARGS || strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0) {
        cerr << OPEN_MESSAGE << endl << "USAGE: " << argv[0] << " <num_nodes>"
        #if defined COMPLETE // complete graph
            // no parameters needed
        #endif
        << endl; exit(1);
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
    unsigned long long const N = stoull(argv[1]);
    #if defined COMPLETE // complete graph
        // no parameters needed
    #endif

    // generate graph
    #if defined COMPLETE // complete graph
        generate_complete_graph(N);
    #endif
    return 0;
}
