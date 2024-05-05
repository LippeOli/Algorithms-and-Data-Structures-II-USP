#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

class Arc {
public:
    int source;
    int destination;
    int weight;
    Arc(int src, int dest, int w) : source(src), destination(dest), weight(w) {}
};

class Graph {
private:
    std::vector<std::vector<int>> matrix;
    int size;

public:
    Graph(int size) : size(size) {
        matrix.resize(size, std::vector<int>(size, std::numeric_limits<int>::max()));
        for (int i = 0; i < size; ++i) {
            matrix[i][i] = 0;
        }
    }

    void insertArc(const Arc& arc) {
        matrix[arc.source][arc.destination] = arc.weight;
    }

    void removeArc(const Arc& arc) {
        matrix[arc.source][arc.destination] = 0;
        matrix[arc.destination][arc.source] = 0;
    }

    void printArcs(int vertex) const {
        bool isFirstPrinted = true;
        for (int i = 0; i < size; i++) {
            if (matrix[vertex][i] != std::numeric_limits<int>::max()) {
                if (!isFirstPrinted) {
                    std::cout << ", ";
                } else {
                    isFirstPrinted = false;
                }
                std::cout << i;
            }
        }
    }

    void printGraph() const {
        for (int i = 0; i < size; i++) {
            std::cout << "Vertex " << i << ", arcs: ";
            printArcs(i);
            std::cout << "\n";
        }
    }

    int getNumberOfArcs(bool isBidirectional) const {
        int count = 0;
        for (const auto& row : matrix) {
            count += std::count(row.begin(), row.end(), 1);
        }
        return isBidirectional ? count : count / 2;
    }

    void deepSearch(int currentVertex, std::vector<bool>& visited) const {
        visited[currentVertex] = true;
        std::cout << "visited " << currentVertex << "\n";

        for (int i = 0; i < size; i++) {
            if (matrix[currentVertex][i] != std::numeric_limits<int>::max() && !visited[i]) {
                deepSearch(i, visited);
            }
        }
    }

    void breadSearch(std::vector<bool>& visited) const {
        std::queue<int> queue;
        queue.push(0);
        visited[0] = true;

        while (!queue.empty()) {
            int currentVertex = queue.front();
            queue.pop();
            std::cout << "visited " << currentVertex << "\n";

            for (int i = 0; i < size; i++) {
                if (matrix[currentVertex][i] != std::numeric_limits<int>::max() && !visited[i]) {
                    visited[i] = true;
                    queue.push(i);
                }
            }
        }
    }

    std::vector<int> dijkstra(int source, std::vector<int>& predecessor) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        std::vector<int> dist(size, std::numeric_limits<int>::max());
        predecessor.assign(size, -1);

        pq.push(std::make_pair(0, source));
        dist[source] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < size; ++v) {
                if (matrix[u][v] != std::numeric_limits<int>::max()) {
                    int alt = dist[u] + matrix[u][v];
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        predecessor[v] = u;
                        pq.push(std::make_pair(dist[v], v));
                    }
                }
            }
        }

        return dist;
    }
};

void printPath(int v, const std::vector<int>& predecessor) {
    if (predecessor[v] == -1) {
        std::cout << v;
        return;
    }

    printPath(predecessor[v], predecessor);
    std::cout << " -> " << v;
}

int main() {
    int numbVertices;
    std::cin >> numbVertices;
    Graph graph(numbVertices);

    int source, destination, weight;
    while (std::cin >> source >> destination >> weight) {
        Arc arc(source, destination, weight);
        graph.insertArc(arc);
    }

    for (int i = 0; i < numbVertices; ++i) {
        std::vector<int> predecessor;
        std::vector<int> distances = graph.dijkstra(i, predecessor);

        std::cout << "Node " << i << ":\n";
        for (int dest = 0; dest < numbVertices; ++dest) {
            std::cout << "Distance from " << i << " to " << dest << " = ";
            if (distances[dest] == std::numeric_limits<int>::max()) {
                std::cout << "infinity\n";
            } else {
                std::cout << distances[dest] << "\n";

                if (distances[dest] > 0) {
                    std::cout << "Path: ";
                    printPath(dest, predecessor);
                    std::cout << "\n";
                }
            }
        }

        if (i < numbVertices - 1) {
            std::cout << "\n";
        }
    }

    return 0;
}
