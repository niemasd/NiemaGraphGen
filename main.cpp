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
#define NUM_USER_ARGS 3
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
}
