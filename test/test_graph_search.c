#include "graph_search.h"
#include <libipd.h>
#include <assert.h>
#include <stdlib.h>

static void test_ghp_4(void)
{
    graph_t g4 = graph_create(4);
    assert( g4 );

    CHECK( graph_has_path(g4, 0, 0) );
    CHECK( ! graph_has_path(g4, 0, 1) );

    graph_add_edge(g4, 0, 1);
    CHECK( graph_has_path(g4, 0, 1) );

    graph_add_edge(g4, 1, 0);
    CHECK( ! graph_has_path(g4, 0, 2) );

    graph_add_edge(g4, 1, 2);
    CHECK( graph_has_path(g4, 0, 2) );
    CHECK( ! graph_has_path(g4, 0, 3) );

    graph_add_edge(g4, 2, 3);
    CHECK( graph_has_path(g4, 0, 3) );

    graph_destroy(g4);
}


// Computes vertex numbers for the graphs constructed by
// `build_lattice` (below).
static vertex_t lattice_vertex(size_t W, int col, int row)
{
    return row * W + col;
}

// Constructs this graph (wherein all lines stand for downward
// edges):
//
//    0     1    ...   (W-2)  (W-1)
//    | \/  | \  ...  /  |  \/  |
//    | /\  | /  ...  \  |  /\  |
//    W   (W+1)  ...  (2W-2) (2W-1)
//    | \/  | \  ...  /  | \ /  |
//    . . . . .  ...  .  . . .  .
//    .  .  . .  ...  .  .  .   .
//    . . . . .  ...  .  . . .  .
//    | / \ | \  ...  \  | / \  |
// (HW-W)(HW-W+1)...  (HW-2) (HW-1)
//
static graph_t
build_lattice(size_t const W, size_t const H)
{
    graph_t g = graph_create(W * H);
    assert( g );

    for (size_t row = 0; row + 1 < H; ++row) {
        for (size_t col = 0; col < W; ++col) {
            vertex_t u = lattice_vertex(W, col, row);

            graph_add_edge(g, u, lattice_vertex(W, col, row + 1));

            if (col > 0)
                graph_add_edge(g, u, lattice_vertex(W, col - 1, row + 1));

            if (col + 1 < W)
                graph_add_edge(g, u, lattice_vertex(W, col + 1, row + 1));
        }
    }

    return g;
}

// Predicts when the graph constructed by `build_lattice` has a path.
static bool lattice_has_path(int col_src, int row_src,
                             int col_dst, int row_dst)
{
    return row_dst >= row_src &&
            row_dst - row_src >= abs(col_dst - col_src);
}

static void test_ghp_lattice(size_t const W, size_t const H)
{
    assert( W > 1 );
    assert( H > 1 );

    graph_t g = build_lattice(W, H);

    for (int row_src = 0; row_src < H; ++row_src) {
        for (int col_src = 0; col_src < W; ++col_src) {
            vertex_t src = lattice_vertex(W, col_src, row_src);
            for (int row_dst = 0; row_dst < H; ++row_dst) {
                for (int col_dst = 0; col_dst < W; ++col_dst) {
                    vertex_t dst = lattice_vertex(W, col_dst, row_dst);
                    CHECK_INT( graph_has_path(g, src, dst),
                               lattice_has_path(col_src, row_src,
                                                col_dst, row_dst) );
                }
            }
        }
    }

    graph_destroy(g);
}

// Like `build_lattice`, but connects the bottom row back to the top
// to make some cycles.
static graph_t
build_cyclic(size_t const W, size_t const H)
{
    graph_t g = build_lattice(W, H);

    for (size_t col = 0; col < W; ++col) {
        vertex_t u = lattice_vertex(W, col, H - 1);
        graph_add_edge(g, u, lattice_vertex(W, col, 0));
        if (col > 0)
            graph_add_edge(g, u, lattice_vertex(W, col - 1, 0));
        if (col + 1 < W)
            graph_add_edge(g, u, lattice_vertex(W, col + 1, 0));
    }

    return g;
}

static void test_ghp_cyclic(size_t const W, size_t const H)
{
    graph_t g = build_cyclic(W, H);

    vertex_t u = lattice_vertex(W, 0,     0);
    vertex_t v = lattice_vertex(W, W - 1, 0);
    CHECK( graph_has_path(g, u, v) );

    graph_destroy(g);
}

int main(void)
{
    test_ghp_4();

    test_ghp_lattice(4, 4);
    test_ghp_lattice(12, 13);

    test_ghp_cyclic(4, 4);
    test_ghp_cyclic(13, 17);
}
