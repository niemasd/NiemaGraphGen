#include <iostream>
#include "writer.h"
using namespace std;

// FAVITES output format
void WriterFAVITES::write_node(unsigned long long const & u) {
    cout << "NODE\t" << u << "\t." << endl;
}
void WriterFAVITES::write_edge(unsigned long long const & u, unsigned long long const & v) {
    cout << "EDGE\t" << u << '\t' << v << "\t.\tu" << endl;
}
