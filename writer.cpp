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

// compact output format
WriterCompact::WriterCompact() : max_node_label(0), wrote_max_node_label(false) {}
WriterCompact::~WriterCompact() {
    if(!wrote_max_node_label) {
        cout.write((char*)&max_node_label, sizeof(max_node_label));
        wrote_max_node_label = true;
    }
}
void WriterCompact::write_node(unsigned long long const & u) {
    if(u > max_node_label) {
        max_node_label = u;
    }
}
void WriterCompact::write_edge(unsigned long long const & u, unsigned long long const & v) {
    if(!wrote_max_node_label) {
        cout.write((char*)&max_node_label, sizeof(max_node_label));
        wrote_max_node_label = true;
    }
    cout.write((char*)&u, sizeof(u));
    cout.write((char*)&v, sizeof(v));
}
