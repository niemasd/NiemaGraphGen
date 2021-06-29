#include "newman_watts_strogatz.h"
#include "ring_lattice.h"

/**
 * There are N nodes, and in the original lattice graph, each node has K edges.
 * Thus, each node has N-K-1 possible new edges that can be added in the NWS rewiring.
 * We can think of this as a matrix with N rows and N-K-1 columns:
 *
 *    -------------------------------------------------------
 * 0: | K/2 + 1     | K/2 + 2 | ... | (N - K/2 - 1)     % N |
 *    -------------------------------------------------------
 * 1: | K/2 + 2     | K/2 + 3 | ... | (N - K/2 - 0)     % N |
 *    -------------------------------------------------------
 * 2: | K/2 + 3     | K/2 + 4 | ... | (N - K/2 + 1)     % N |
 *    -------------------------------------------------------
 * .: | ........... | ....... | ... | ..................... |
 *    -------------------------------------------------------
 * i: | K/2 + 1 + i | ....... | ... | (N - K/2 + i - 1) % N |
 *    -------------------------------------------------------
 *
 * If (u,v) is selected, then (v,u) can't be selected.
 * Thus, we don't care about half of it.
 * For example, for N = 5 and K = 2 ("X" denotes "don't care"):
 *
 *       ALL               X
 *    ---------        ---------
 * 0: | 2 | 3 |     0: | 2 | 3 |
 *    ---------        ---------
 * 1: | 3 | 4 |     1: | 3 | 4 |
 *    ---------        ---------
 * 2: | 4 | 0 |     2: | 4 | X |
 *    ---------        ---------
 * 3: | 0 | 1 |     3: | X | X |
 *    ---------        ---------
 * 4: | 1 | 2 |     4: | X | X |
 *    ---------        ---------
 *
 * For example, for N = 7 and K = 2:
 *
 *           ALL                       X
 *    -----------------        -----------------
 * 0: | 2 | 3 | 4 | 5 |     0: | 2 | 3 | 4 | 5 |
 *    -----------------        -----------------
 * 1: | 3 | 4 | 5 | 6 |     1: | 3 | 4 | 5 | 6 |
 *    -----------------        -----------------
 * 2: | 4 | 5 | 6 | 0 |     2: | 4 | 5 | 6 | X |
 *    -----------------        -----------------
 * 3: | 5 | 6 | 0 | 1 |     3: | 5 | 6 | X | X |
 *    -----------------        -----------------
 * 4: | 6 | 0 | 1 | 2 |     4: | 6 | X | X | X |
 *    -----------------        -----------------
 * 5: | 0 | 1 | 2 | 3 |     5: | X | X | X | X |
 *    -----------------        -----------------
 * 6: | 1 | 2 | 3 | 4 |     6: | X | X | X | X |
 *    -----------------        -----------------
 *
 * For example, for N = 7 and K = 4:
 *
 *       ALL               X
 *    ---------        ---------
 * 0: | 3 | 4 |     0: | 3 | 4 |
 *    ---------        ---------
 * 1: | 4 | 5 |     1: | 4 | 5 |
 *    ---------        ---------
 * 2: | 5 | 6 |     2: | 5 | 6 |
 *    ---------        ---------
 * 3: | 6 | 0 |     3: | 6 | X |
 *    ---------        ---------
 * 4: | 0 | 1 |     4: | X | X |
 *    ---------        ---------
 * 5: | 1 | 2 |     5: | X | X |
 *    ---------        ---------
 * 6: | 2 | 3 |     6: | X | X |
 *    ---------        ---------
 *
 * The last column in the first row has node N - K/2 - 1,
 * and the last column in the last full row has node N - 1,
 * so there are (N-1) - (N-K/2-1) + 1 = K/2 + 1 non-empty rows:
 * row 0 through row K/2.
 *
 * Thus, for rows 0 through K/2, we can imagine the following matrix,
 * where cells are filled with the array representation index:
 *
 *      --------------------------------------------------------------
 * 0:   |            0 |                1 | ... |              N-K-2 |
 *      --------------------------------------------------------------
 * 1:   |        N-K-1 |              N-K | ... |       2(N-K-1) - 1 |
 *      --------------------------------------------------------------
 * 2:   |     2(N-K-1) |     2(N-K-1) + 1 | ... |       3(N-K-1) - 1 |
 *      --------------------------------------------------------------
 * ...: | ............ | ................ | ... | .................. |
 *      --------------------------------------------------------------
 * i:   |     i(N-K-1) |     i(N-K-1) + 1 | ... |   (i+1)(N-K-1) - 1 |
 *      --------------------------------------------------------------
 * ...: | ............ | ................ | ... | .................. |
 *      --------------------------------------------------------------
 * K/2: | (K/2)(N-K-1) | (K/2)(N-K-1) + 1 | ... | (K/2+1)(N-K-1) - 1 |
 *      --------------------------------------------------------------
 *
 * Row K/2+1 has exactly 1 empty slot,
 * row K/2+2 has exactly 2 empty slots,
 * so the first row that is totally empty (N-K-1 empty slots) is row K/2+(N-K-1) = N - K/2 - 1.
 * You seem to always have exactly K rows that are full and K rows that are empty,
 * with row K having one empty, row K+1 having 2 empty, row K+x having x+1 empty.
 * Thus, we get the following (where Y means non-empty):
 *
 *          ---------------------------
 * K/2+1:   | Y | Y | Y | ... | Y | X |
 *          ---------------------------
 * K/2+2:   | Y | Y | Y | ... | X | X |
 *          --------------------------
 * .....:   | . | . | . | ... | X | X |
 *          ---------------------------
 * N-K/2-2: | Y | X | X | ... | X | X |
 *          ---------------------------
 *
 * This is a square matrix with a triangle in the upper-left, with N-K-2 rows and N-K-2 columns.
 * Used this to get the row + col from an index:
 * https://stackoverflow.com/a/27088560
 */
void generate_nws_graph(NGG_UINT const & N, NGG_UINT const & K, long double const & P) {
    // useful constants
    NGG_UINT const K_OVER_2 = K/2;
    NGG_UINT const K_OVER_2_PLUS_1 = K_OVER_2 + 1;
    NGG_UINT const NUM_LATTICE_EDGES = N * K_OVER_2;
    NGG_UINT const N_MINUS_K_MINUS_1 = N - K - 1; // this is the number of columns in the hypothetical matrix
    NGG_UINT const N_MINUS_K_MINUS_2 = N_MINUS_K_MINUS_1 - 1;
    NGG_UINT const N_MINUS_K_MINUS_3 = N_MINUS_K_MINUS_2 - 1;
    NGG_UINT const NUM_NONLATTICE_EDGES_DIRECTED = N_MINUS_K_MINUS_1 * N; // this is the number of cells in the hypothetical matrix
    NGG_UINT const NUM_NONLATTICE_EDGES = NUM_NONLATTICE_EDGES_DIRECTED / 2; // can't have both (u,v) and (v,u)
    NGG_UINT const FIRST_INDEX_TRIANGLE = (K_OVER_2 + 1) * N_MINUS_K_MINUS_1;
    NGG_UINT const LAST_INDEX_FULL_RECTANGLE = FIRST_INDEX_TRIANGLE - 1;
    NGG_UINT const INNER_SQRT_TERM = 4*N_MINUS_K_MINUS_1*N_MINUS_K_MINUS_2 - 7;
    NGG_UINT const NMKM1_C_2 = N_MINUS_K_MINUS_1*(N_MINUS_K_MINUS_2)/2;

    // first create ring lattice graph (no edges are removed in Newman-Watts-Strogatz)
    generate_ring_lattice_graph(N, K);

    // determine the new edges to add from binomial(nk/2, p)
    binomial_distribution<NGG_UINT> num_new_edges_dist(NUM_LATTICE_EDGES, P);
    NGG_UINT const NUM_NEW_EDGES = min(num_new_edges_dist(RNG), NUM_NONLATTICE_EDGES);
    NGG_UINT tmp_row; NGG_UINT tmp_col; NGG_UINT tmp_ind; NGG_UINT u; NGG_UINT v; // temp variables
    for(NGG_UINT const & new_edge_int : sample_range_no_replacement(0, NUM_NONLATTICE_EDGES-1, NUM_NEW_EDGES)) {
        // if this edge is in the top rectangle part of matrix
        if(new_edge_int <= LAST_INDEX_FULL_RECTANGLE) {
            u = new_edge_int / N_MINUS_K_MINUS_1; // row in rectangle part of matrix
            tmp_col = new_edge_int % N_MINUS_K_MINUS_1; // column in rectangle part of matrix
            v = K_OVER_2_PLUS_1 + u + tmp_col;
        }
        
        // otherwise, edge is in the bottom triangle part of matrix
        else {
            tmp_ind = new_edge_int - FIRST_INDEX_TRIANGLE;
            tmp_row = N_MINUS_K_MINUS_3 - (NGG_UINT)(sqrt(-EIGHT_ULL*tmp_ind + INNER_SQRT_TERM)/TWO_LD - HALF_LD);
            u = tmp_row + K_OVER_2_PLUS_1;
            tmp_col = (N_MINUS_K_MINUS_1-tmp_row)*((N_MINUS_K_MINUS_1-tmp_row)-ONE_ULL)/TWO_ULL - NMKM1_C_2 + tmp_ind;
        }

        // figured out both u and v, so write this edge
        v = K_OVER_2_PLUS_1 + u + tmp_col;
        writer.write_edge(u, v);
    }
}
