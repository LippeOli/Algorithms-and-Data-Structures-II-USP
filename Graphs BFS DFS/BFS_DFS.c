//BFS e DFS em grafos considerando a representação em Matriz de Adjacências
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Implementação da fila para BFS
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->rear == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_VERTICES - 1)
        return;
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    int item;
    if (isEmpty(q))
        return -1;
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
        q->front = q->rear = -1;
    return item;
}

// Implementação do BFS
void bfs(int graph[MAX_VERTICES][MAX_VERTICES], int start, int numVertices) {
    Queue q;
    bool visited[MAX_VERTICES] = {false};
    initQueue(&q);
    
    visited[start] = true;
    enqueue(&q, start);
    
    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("\nvisited %d", current);
        
        for (int i = 0; i < numVertices; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
}

// Implementação do DFS
void dfs(int graph[MAX_VERTICES][MAX_VERTICES], int start, bool visited[MAX_VERTICES], int numVertices) {
    printf("\nvisited %d", start);
    visited[start] = true;
    
    for (int i = 0; i < numVertices; i++) {
        if (graph[start][i] && !visited[i]) {
            dfs(graph, i, visited, numVertices);
        }
    }
}

int main() {
    int vertices, v, w;
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};

    scanf("%d", &vertices);

    for (int i = 0; i < vertices; i++) {
        scanf("%d %d", &v, &w);
        if (v >= 0 && v < MAX_VERTICES && w >= 0 && w < MAX_VERTICES) {
            graph[v][w] = 1;
            graph[w][v] = 1; 
        }
    }

    // Demonstrando BFS e DFS
    int numVertices = MAX_VERTICES;
    
    printf("DFS");
    bool visited[MAX_VERTICES] = {false};
    dfs(graph, 0, visited, numVertices);

    printf("\nBFS");
    bfs(graph, 0, numVertices);

    return 0;
}
