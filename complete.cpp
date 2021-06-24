#include <iostream>
#include "complete.h"
using namespace std;

void generate_complete_graph(unsigned long long const & N) {
    // output nodes
    for(unsigned long long i = 0; i < N; ++i) {
        cout << "NODE\t" << i << "\t." << endl;
    }

    // output edges
    unsigned long long const N_MINUS_1 = N-1;
    for(unsigned long long i = 0; i < N_MINUS_1; ++i) {
        for(unsigned long long j = i+1; j < N; ++j) {
            cout << "EDGE\t" << i << '\t' << j << "\t.\tu" << endl;
        }
    }
}
