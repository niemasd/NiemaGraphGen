#include "common.h"

// initialize extern variables from common.h
int RNG_SEED = chrono::system_clock::now().time_since_epoch().count();
default_random_engine RNG(RNG_SEED);
NGG_UINT const ONE_ULL = (NGG_UINT)1;
long double ONE_LD = (long double)1.;
NGG_UINT const TWO_ULL = (NGG_UINT)2;
long double TWO_LD = (long double)2.;
NGG_UINT const EIGHT_ULL = (NGG_UINT)8;

// FAVITES output format
void WriterFAVITES::write_nodes(NGG_UINT const & N) {
    for(NGG_UINT i = 0; i < N; ++i) {
        cout << "NODE\t" << i << "\t." << endl;
    }
}
void WriterFAVITES::write_edge(NGG_UINT const & u, NGG_UINT const & v) {
    cout << "EDGE\t" << u << '\t' << v << "\t.\tu" << endl;
}

// compact output format
void WriterCompact::write_nodes(NGG_UINT const & N) {
    uint_fast8_t flags = 0; // 000000AA
    switch(sizeof(NGG_UINT)) {
        case 1:             break; // AA = 00
        case 2: flags |= 1; break; // AA = 01
        case 4: flags |= 2; break; // AA = 10
        case 8: flags |= 3; break; // AA = 11
        default: cerr << "Invalid NGG_UINT" << endl; exit(1);
    }
    cout.put(flags);
    cout.write((char*)&N, sizeof(N));
}
void WriterCompact::write_edge(NGG_UINT const & u, NGG_UINT const & v) {
    cout.write((char*)&u, sizeof(u));
    cout.write((char*)&v, sizeof(v));
}

// set up writer
#if defined OUTFAVITES   // FAVITES output format
WriterFAVITES
#elif defined OUTCOMPACT // compact output format
WriterCompact
#endif
writer;

// error function
void error(string const & message) {
    cerr << message << endl; exit(1);
}

/**
 * implement Robert Floyd's sampling algorithm
 * https://www.gormanalysis.com/blog/random-numbers-in-cpp/#sampling-without-replacement
 * https://www.nowherenearithaca.com/2013/05/robert-floyds-tiny-and-beautiful.html
 * https://stackoverflow.com/a/28287865/2146894
 */
unordered_set<NGG_UINT> sample_range_no_replacement(NGG_UINT const & min_val, NGG_UINT const & max_val, NGG_UINT const & num_samples) {
    unordered_set<NGG_UINT> samples;
    for(NGG_UINT r = max_val-num_samples+1; r <= max_val; ++r) {
        NGG_UINT v = uniform_int_distribution<NGG_UINT>(min_val, r)(RNG);
        if(!samples.insert(v).second) { samples.insert(r); }
    }
    if(samples.size() != num_samples) {
        cerr << "sample_range_no_replacement(" << min_val << ',' << max_val << ',' << num_samples << ") failed" << endl; exit(1);
    }
    return samples;
}
