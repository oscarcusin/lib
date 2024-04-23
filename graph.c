#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "graph.h"

struct graph {
    size_t vertices, edges, data_size;
    array * adj[];
};

struct edge {
    size_t from, to;
    char data[];
};

graph * graph_new(size_t n, size_t data_size) {
    graph * g = malloc(sizeof(graph) + n * sizeof(array *));
    if (!g) return NULL;
    g->vertices = n;
    g->edges = 0;
    g->data_size = data_size;
    memset(g->adj, 0, n * sizeof(array *));
    return g;
}

graph * graph_copy(graph * g) {
    if (!g) return NULL;
    graph * copy = malloc(sizeof(graph) + g->vertices * sizeof(array *));
    if (!copy) return NULL;
    for (size_t i = 0; i < g->vertices; i++) {
        if (!g->adj[i]) {
            copy->adj[i] = NULL;
            continue;
        }
        copy->adj[i] = array_copy(g->adj[i]);
        if (!copy->adj[i]) {
            for (size_t j = 0; j < i; j++) {
                array_free(copy->adj[j]);
            }
            free(copy);
            return NULL;
        }
    }
    copy->vertices = g->vertices;
    copy->edges = g->edges;
    copy->data_size = g->data_size;
    return copy;
}

void graph_free(graph * g) {
    if (!g) return;
    for (size_t i = 0; i < g->vertices; i++) {
        array_free(g->adj[i]);
    }
    free(g);
}

size_t graph_vertices(graph * g) {
    if (!g) return 0;
    return g->vertices;
}

size_t graph_edges(graph * g) {
    if (!g) return 0;
    return g->edges;
}

edge * graph_add_edge(graph * g, size_t from, size_t to, void * data) {
    if (!g || from >= g->vertices || to >= g->vertices) return NULL;
    if (!g->adj[from]) {
        g->adj[from] = array_new(sizeof(edge) + g->data_size);
        if (!g->adj[from]) return NULL;
    }
    edge * e = malloc(sizeof(edge) + g->data_size);
    if (!e) return NULL;
    e->from = from;
    e->to = to;
    memcpy(e->data, data, g->data_size);
    edge * item = array_add(g->adj[from], e);
    free(e);
    if (!item) return NULL;
    g->edges++;
    return item;
}

int graph_remove_edge(graph * g, size_t from, size_t to) {
    if (!g || from >= g->vertices || to >= g->vertices) return -1;
    edge temp = {from, to};
    for (edge * e = array_begin(g->adj[from]); e != array_end(g->adj[from]); e = array_next(g->adj[from], e)) {
        if (!memcmp(e, &temp, sizeof(edge))) {
            array_remove(g->adj[from], e);
            g->edges--;
            return 0;
        }
    }
    return -1;
}

int _graph_edge_cmp(const void * a, const void * b) {
    if (((edge *) a)->to < ((edge *) b)->to) return -1;
    if (((edge *) a)->to > ((edge *) b)->to) return 1;
    return 0;
}

edge * graph_edge(graph * g, size_t from, size_t to) {
    if (!g || from >= g->vertices || to >= g->vertices) return NULL;
    return array_search(g->adj[from], _graph_edge_cmp, &(edge) {from, to});
}

array * graph_outgoing_edges(graph * g, size_t v) {
    if (!g || v >= g->vertices) return NULL;
    return g->adj[v];
}

size_t edge_from(edge * e) {
    if (!e) return SIZE_MAX;
    return e->from;
}

size_t edge_to(edge * e) {
    if (!e) return SIZE_MAX;
    return e->to;
}

void * edge_data(edge * e) {
    if (!e) return NULL;
    return e->data;
}
