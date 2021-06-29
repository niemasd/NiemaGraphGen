#ifndef COMMON_H
#define COMMON_H
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <unordered_set>
#include <utility>
using namespace std;

// data type for unsigned integers
#ifndef NGG_UINT
#if   defined NGG_UINT_8
#define NGG_UINT uint_fast8_t
#elif defined NGG_UINT_16
#define NGG_UINT uint_fast16_t
#elif defined NGG_UINT_32
#define NGG_UINT uint_fast32_t
#elif defined NGG_UINT_64
#define NGG_UINT uint_fast64_t
#else // default
#define NGG_UINT uint_fast64_t 
#endif
#endif

// random number generation
extern int RNG_SEED;
extern default_random_engine RNG;

// useful constants
extern long double HALF_LD;
extern NGG_UINT const ONE_ULL;
extern long double ONE_LD;
extern NGG_UINT const TWO_ULL;
extern long double TWO_LD;
extern NGG_UINT const EIGHT_ULL;

/**
 * Write graphs to standard output
 */
class Writer {
    public:
        /**
         * Write the nodes 0 to N-1
         * @param N The total number of nodes
         */
        virtual void write_nodes(NGG_UINT const & N) = 0;

        /**
         * Write an edge to standard output
         * @param u The first node in the edge to output
         * @param v The second node in the edge to output
         */
        virtual void write_edge(NGG_UINT const & u, NGG_UINT const & v) = 0;
};

/**
 * Write graphs in the FAVITES contact network format
 */
class WriterFAVITES : public Writer {
    public:
        void write_nodes(NGG_UINT const & N);
        void write_edge(NGG_UINT const & u, NGG_UINT const & v);
};

/**
 * Write graphs in the compact format
 */
class WriterCompact : public Writer {
    public:
        void write_nodes(NGG_UINT const & N);
        void write_edge(NGG_UINT const & u, NGG_UINT const & v);
};

// declare output writer
extern
#if   defined OUTFAVITES // FAVITES output format
WriterFAVITES
#elif defined OUTCOMPACT // compact output format
WriterCompact
#endif
writer;

/**
 * Write error message to standard error and crash program
 * @param message Error message to print
 */
void error(string const & message);

/**
 * Sample multiple integers in a given range [min_val, max_val]
 * @param min_val Minimum value in the range
 * @param max_val Maximum value in the range
 * @param num_samples Number of integers to sample
 */
unordered_set<NGG_UINT> sample_range_no_replacement(NGG_UINT const & min_val, NGG_UINT const & max_val, NGG_UINT const & num_samples);
#endif
