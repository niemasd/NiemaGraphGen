#ifndef COMMON_H
#define COMMON_H
#include <chrono>
#include <random>
#include <unordered_set>
using namespace std;

// random number generation
extern int RNG_SEED;
extern default_random_engine RNG;

// useful constants
extern unsigned long long const ONE_ULL;
extern long double ONE_LD;

/**
 * Sample multiple integers in a given range [min_val, max_val]
 * @param min_val Minimum value in the range
 * @param max_val Maximum value in the range
 * @param num_samples Number of integers to sample
 */
unordered_set<unsigned long long> sample_range_no_replacement(unsigned long long const & min_val, unsigned long long const & max_val, unsigned long long const & num_samples);
#endif
