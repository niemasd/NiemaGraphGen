#ifndef COMMON_H
#define COMMON_H
#include <chrono>
#include <random>
#include <unordered_set>
using namespace std;

// random number generation
extern int RNG_SEED;
extern default_random_engine RNG;

/*
class RangeSamples {
    public:
        unsigned long long const MIN_VAL;
        unsigned long long const MAX_VAL;
        unsigned long long const NUM_SAMPLES;
        RangeSamples(unsigned long long const & min_val, unsigned long long const & max_val, unsigned long long const & num_samples);
        class iterator {
            public:
                bool const VALID;
                unsigned long long VALUE;
                iterator(bool const & valid, unsigned long long const & value);
                unsigned long long operator*();
                void operator++();
                bool operator!=(iterator);
        };
        iterator begin();
        iterator end();
};
RangeSamples sample_range_no_replacement(unsigned long long const & min_val, unsigned long long const & max_val, unsigned long long const & num_samples);
*/
/**
 * Sample multiple integers in a given range [min_val, max_val]
 * @param min_val Minimum value in the range
 * @param max_val Maximum value in the range
 * @param num_samples Number of integers to sample
 */
unordered_set<unsigned long long> sample_range_no_replacement(unsigned long long const & min_val, unsigned long long const & max_val, unsigned long long const & num_samples);
#endif
