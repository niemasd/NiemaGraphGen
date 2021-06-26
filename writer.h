#ifndef WRITER_H
#define WRITER_H
/**
 * Write graphs to standard output
 */
class Writer {
    public:
        /**
         * Write the nodes 0 to N-1
         * @param N The total number of nodes
         */
        virtual void write_nodes(unsigned long long const & N) = 0;

        /**
         * Write an edge to standard output
         * @param u The first node in the edge to output
         * @param v The second node in the edge to output
         */
        virtual void write_edge(unsigned long long const & u, unsigned long long const & v) = 0;
};

/**
 * Write graphs in the FAVITES contact network format
 */
class WriterFAVITES : public Writer {
    public:
        void write_nodes(unsigned long long const & N);
        void write_edge(unsigned long long const & u, unsigned long long const & v);
};

/**
 * Write graphs in the compact format
 */
class WriterCompact : public Writer {
    public:
        void write_nodes(unsigned long long const & N);
        void write_edge(unsigned long long const & u, unsigned long long const & v);
};
#endif
