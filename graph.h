#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include "array.h"

typedef struct graph graph;
typedef struct edge edge;

// Allocates a new graph with N vertices and no edges, with edge data of size DATA_SIZE.
// Returns a pointer to the graph on success, or NULL on failure.
graph * graph_new(size_t n, size_t data_size);

// Allocates a new graph with the same vertices, edges, and data size as G, and copies the data from G.
// Returns a pointer to the graph on success, or NULL on failure.
graph * graph_copy(graph * g);

// Frees the graph G.
void graph_free(graph * g);

// Returns the number of vertices in the graph G.
size_t graph_vertices(graph * g);

// Returns the number of edges in the graph G.
size_t graph_edges(graph * g);

// Adds an edge from FROM to TO in the graph G, with data DATA.
// Copies the memory pointed to by DATA into the graph.
// Returns a pointer to the added edge on success, NULL on failure.
edge * graph_add_edge(graph * g, size_t from, size_t to, void * data);

// Removes the edge from FROM to TO in the graph G.
// Returns 0 on success, -1 on failure.
int graph_remove_edge(graph * g, size_t from, size_t to);

// Returns a pointer to the edge from FROM to TO in the graph G, or NULL on failure.
edge * graph_edge(graph * g, size_t from, size_t to);

// Returns a pointer to the adjacency list of vertex V in the graph G, or NULL on failure.
// Modifying the data in the array will modify the data in the graph.
array * graph_outgoing_edges(graph * g, size_t v);

// Returns the index of the vertex FROM in the edge E, or SIZE_MAX on failure.
size_t edge_from(edge * e);

// Returns the index of the vertex TO in the edge E, or SIZE_MAX on failure.
size_t edge_to(edge * e);

// Returns a pointer to the data of the edge E, or NULL on failure.
void * edge_data(edge * e);

#endif
