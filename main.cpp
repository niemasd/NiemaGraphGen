#include <string>
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
}
