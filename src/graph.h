#pragma once

#include <stddef.h>
#include <stdbool.h>

// Represents a graph vertex.
typedef size_t vertex_t;

// Represents a directed graph.
typedef struct graph      * graph_t;
typedef struct graph const* const_graph_t;
// The types `graph_t` and `const_graph_t` are abstract, in that
// clients will handle graphs only via a pointer to a struct
// whose definition isn't visible to them.

// Allocates and initializes a new graph of `size` vertices.
//
// Ownership:
//   - Ownership of the resulting object transferred to the caller,
//     who must release it by calling graph_destroy().
//
// Errors:
//   - Returns NULL if memory cannot be allocated.
graph_t graph_create(size_t size);

// Releases the memory owned by `g`.
//
// It's okay if `g` is NULL.
void graph_destroy(graph_t g);

// Returns the number of vertices in the graph.
size_t graph_size(const_graph_t g);

// Adds an edge from node `from` to node `to`.
void graph_add_edge(graph_t g, vertex_t src, vertex_t dst);

// Removes the edge from node `from` to node `to`.
void graph_remove_edge(graph_t g, vertex_t src, vertex_t dst);

// Determines whether there is an edge from node `from` to node `to`.
bool graph_has_edge(const_graph_t g, vertex_t src, vertex_t dst);

// Stores up to `out_cap` successors of node `from` in the array
// pointed to by `out`, and returns the capacity needed for all of
// `from`'s successors. That is, if the result is `<= out_cap` then
// you got all of them, but if the result `> out_cap` then `out_cap`
// wasn't large enough.
size_t
graph_get_successors(const_graph_t g,
                     vertex_t src,
                     size_t out_cap,
                     vertex_t out[out_cap]);

