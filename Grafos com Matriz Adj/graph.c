#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* initGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->edges = 0;

    graph->adj_matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adj_matrix[i] = (int*)calloc(vertices, sizeof(int));
    }

    return graph;
}

void destroyGraph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);
}

void insertArc(Graph* graph, int v, int w) {
    if (v >= 0 && v < graph->vertices && w >= 0 && w < graph->vertices) {
        if (graph->adj_matrix[v][w] == 0) {
            graph->adj_matrix[v][w] = 1;
            graph->edges++;
        }
    }
}

void removeArc(Graph* graph, int v, int w) {
    if (v >= 0 && v < graph->vertices && w >= 0 && w < graph->vertices) {
        if (graph->adj_matrix[v][w] == 1) {
            graph->adj_matrix[v][w] = 0;
            graph->edges--;
        }
    }
}

void printGraph(Graph* graph) {
    printf("Total of vertices: %d, total of arcs: %d\n", graph->vertices, (graph->edges/2));
    for (int i = 0; i < graph->vertices; i++) {
        printf("Vertex %d, arcs:", i);
        int first_arc_printed = 0;
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adj_matrix[i][j] == 1) {
                if (first_arc_printed) {
                    printf(",");
                }
                printf(" %d", j);
                first_arc_printed = 1;
            }
        }
        printf("\n");
    }
}
