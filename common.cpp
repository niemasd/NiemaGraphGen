#include <iostream>
#include "common.h"

// initialize extern variables from common.h
int RNG_SEED = chrono::system_clock::now().time_since_epoch().count();
default_random_engine RNG(RNG_SEED);
unsigned long long const ONE_ULL = (unsigned long long)1;
long double ONE_LD = (long double)1.;

/**
 * implement Robert Floyd's sampling algorithm
 * https://www.gormanalysis.com/blog/random-numbers-in-cpp/#sampling-without-replacement
 * https://www.nowherenearithaca.com/2013/05/robert-floyds-tiny-and-beautiful.html
 * https://stackoverflow.com/a/28287865/2146894
 */
unordered_set<unsigned long long> sample_range_no_replacement(unsigned long long const & min_val, unsigned long long const & max_val, unsigned long long const & num_samples) {
    unordered_set<unsigned long long> samples;
    for(unsigned long long r = max_val-num_samples+1; r <= max_val; ++r) {
        unsigned long long v = uniform_int_distribution<unsigned long long>(min_val, r)(RNG);
        if(!samples.insert(v).second) { samples.insert(r); }
    }
    if(samples.size() != num_samples) {
        cerr << "sample_range_no_replacement(" << min_val << ',' << max_val << ',' << num_samples << ") failed" << endl; exit(1);
    }
    return samples;
}
