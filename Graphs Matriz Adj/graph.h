#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int vertices;
    int edges;
    int **adj_matrix;
} Graph;

Graph* initGraph(int vertices);
void destroyGraph(Graph* graph);
void insertArc(Graph* graph, int v, int w);
void removeArc(Graph* graph, int v, int w);
void printGraph(Graph* graph);

#endif /* GRAPH_H */
