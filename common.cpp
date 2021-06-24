#include "common.h"

// initialize extern variables from common.h
int RNG_SEED = chrono::system_clock::now().time_since_epoch().count();
default_random_engine RNG(RNG_SEED);
