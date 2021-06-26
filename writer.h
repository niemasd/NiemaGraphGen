#ifndef WRITER_H
#define WRITER_H
/**
 * Write graphs to standard output
 */
class Writer {
    public:
        /**
         * Write a node to standard output
         * @param u The node to output
         */
        virtual void write_node(unsigned long long const & u) = 0;

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
        void write_node(unsigned long long const & u);
        void write_edge(unsigned long long const & u, unsigned long long const & v);
};

/**
 * Write graphs in the compact format
 */
class WriterCompact : public Writer {
    private:
        unsigned long long max_node_label;
        bool wrote_max_node_label;
    public:
        WriterCompact();
        ~WriterCompact();
        void write_node(unsigned long long const & u);
        void write_edge(unsigned long long const & u, unsigned long long const & v);
};
#endif
