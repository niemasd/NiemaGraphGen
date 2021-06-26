#include <iostream>
#include "writer.h"
using namespace std;

// FAVITES output format
void WriterFAVITES::write_nodes(unsigned long long const & N) {
    for(unsigned long long i = 0; i < N; ++i) {
        cout << "NODE\t" << i << "\t." << endl;
    }
}
void WriterFAVITES::write_edge(unsigned long long const & u, unsigned long long const & v) {
    cout << "EDGE\t" << u << '\t' << v << "\t.\tu" << endl;
}

// compact output format
void WriterCompact::write_nodes(unsigned long long const & N) {
    cout.write((char*)&N, sizeof(N));
}
void WriterCompact::write_edge(unsigned long long const & u, unsigned long long const & v) {
    cout.write((char*)&u, sizeof(u));
    cout.write((char*)&v, sizeof(v));
}
