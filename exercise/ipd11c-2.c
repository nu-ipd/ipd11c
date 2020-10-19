#include "graph.h"
#include <libipd.h>
#include <assert.h>

// Determines whether there is a path from node `src` to node `dst`
// whose length is `n` or fewer.
//
// Examples: See tests.
bool graph_has_path_n(const_graph_t g,
                      vertex_t src,
                      vertex_t dst,
                      size_t n)
{
    // TODO: Make this return the correct answer for all possible
    // arguments instead of just a few.
    return src == dst
           || (n >= 1 && graph_has_edge(g, src, dst));
}

// Builds the graph 0 -> 1 -> ... -> (N-2) -> (N-1).
static graph_t build_linear_graph(size_t N)
{
    graph_t g = graph_create(N);
    assert( g );

    for (vertex_t i = 0; i + 1 < N; ++i) {
        graph_add_edge(g, i, i + 1);
    }

    return g;
}

static void test_ghpn_3(void)
{
    graph_t g3  = build_linear_graph(3);

    CHECK( graph_has_path_n(g3, 0, 0, 0) );
    CHECK( graph_has_path_n(g3, 0, 0, 1) );
    CHECK( graph_has_path_n(g3, 0, 0, 2) );

    CHECK( ! graph_has_path_n(g3, 0, 1, 0) );
    CHECK( graph_has_path_n(g3, 0, 1, 1) );
    CHECK( graph_has_path_n(g3, 0, 1, 2) );

    CHECK( ! graph_has_path_n(g3, 0, 2, 0) );
    CHECK( ! graph_has_path_n(g3, 0, 2, 1) );
    CHECK( graph_has_path_n(g3, 0, 2, 2) );
    CHECK( graph_has_path_n(g3, 0, 2, 3) );

    CHECK( ! graph_has_path_n(g3, 2, 0, 10) );

    graph_destroy(g3);
}

static void test_ghpn_16(void)
{
    graph_t g16 = graph_create(16);

    // TODO: More checks here.

    graph_destroy(g16);
}

int main(void)
{
    test_ghpn_3();
    test_ghpn_16();

    // TODO: At least one more test here -- something with a cycle!
}