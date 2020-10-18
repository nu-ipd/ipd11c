#include "graph.h"

#include <assert.h>
#include <stdlib.h>

struct graph
{
    size_t  size;
    bool*   adj;
};

static size_t index(const_graph_t g, vertex_t src, vertex_t dst)
{
    assert( src < g->size );
    assert( dst < g->size );

    return src * g->size + dst;
}

graph_t graph_create(size_t n)
{
    bool* matrix = malloc(n * n * sizeof matrix[0]);
    if (!matrix) {
        return NULL;
    }

    graph_t g = malloc(sizeof *g);
    if (!g) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < n * n; ++i) {
        matrix[i] = false;
    }

    g->size = n;
    g->adj  = matrix;

    return g;
}

void graph_destroy(graph_t g)
{
    if (!g) return;
    free(g->adj);
    free(g);
}

size_t graph_size(const_graph_t g)
{
    return g->size;
}

void graph_add_edge(graph_t g, vertex_t src, vertex_t dst)
{
    g->adj[index(g, src, dst)] = true;
}

void graph_remove_edge(graph_t g, vertex_t src, vertex_t dst)
{
    g->adj[index(g, src, dst)] = false;
}

bool graph_has_edge(const_graph_t g, vertex_t src, vertex_t dst)
{
    return g->adj[index(g, src, dst)];
}

size_t
graph_get_successors(const_graph_t g,
                     vertex_t src,
                     size_t out_cap,
                     vertex_t out[out_cap])
{
    assert( src < g->size );

    size_t fill = 0;

    for (size_t dst = 0; dst < g->size; ++dst) {
        if (graph_has_edge(g, src, dst)) {
            if (fill < out_cap) {
                out[fill] = dst;
            }

            ++fill;
        }
    }

    return fill;
}
