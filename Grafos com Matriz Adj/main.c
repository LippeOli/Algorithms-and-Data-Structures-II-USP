#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    int vertices;
    scanf("%d", &vertices);

    Graph* graph = initGraph(vertices);

    int v, w;
    for (int i = 0; i <= vertices; i++) {
        scanf("%d %d", &v, &w);
        if (v >= 0 && v < vertices && w >= 0 && w < vertices) {
            insertArc(graph, v, w);
            insertArc(graph, w, v); // Adicionando também o arco no sentido inverso
        } else {
            printf("Vértices fora do intervalo esperado. Ignorando entrada.\n");
        }
    }
    
    printGraph(graph);

    destroyGraph(graph);

    return 0;
}
