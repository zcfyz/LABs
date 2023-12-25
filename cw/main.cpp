#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <queue>
#include "Stack.h"

class DisjointSet {
public:
    DisjointSet(const std::vector<std::string>& vertices) {
        for (const auto& vertex : vertices) {
            parent[vertex] = vertex;
            rank[vertex] = 0;
        }
    }

    std::string find(const std::string& vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent[vertex]);
        }
        return parent[vertex];
    }

    void unionSets(const std::string& v1, const std::string& v2) {
        std::string root1 = find(v1);
        std::string root2 = find(v2);

        if (root1 != root2) {
            if (rank[root1] < rank[root2]) {
                parent[root1] = root2;
            }
            else if (rank[root1] > rank[root2]) {
                parent[root2] = root1;
            }
            else {
                parent[root2] = root1;
                rank[root1]++;
            }
        }
    }

private:
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, int> rank;
};

class Graph {
public:
    Graph(const std::vector<std::string>& vertices) : vertices(vertices) {

        adjacencyMatrix.resize(vertices.size(), std::vector<int>(vertices.size(), 0));

        for (const auto& vertex : vertices) {
            adjacencyList[vertex] = std::vector<std::string>();
        }
    }

    void addEdge(const std::string& u, const std::string& v, int weight) {
        edges.push_back(std::make_tuple(weight, u, v));

        int indexU = std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), u));
        int indexV = std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), v));
        adjacencyMatrix[indexV][indexU] = weight;

        if (std::find(adjacencyList[v].begin(), adjacencyList[v].end(), u) == adjacencyList[v].end()) {
            adjacencyList[v].push_back(u);
        }
    }


    void printAdjacencyMatrix() const {
        std::cout << "AdjacencyMatrix:" << std::endl;
        for (const auto& row : adjacencyMatrix) {
            for (int weight : row) {
                std::cout << weight << " ";
            }
            std::cout << std::endl;
        }
    }

    void printAdjacencyList() const {
        std::cout << "AdjacencyList:" << std::endl;
        for (const auto& entry : adjacencyList) {
            std::cout << entry.first << ": ";
            for (const std::string& neighbor : entry.second) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    const std::vector<std::string>& getVertices() const {
        return vertices;
    }

    const std::vector<std::tuple<int, std::string, std::string>>& getEdges() const {
        return edges;
    }

    void breadthFirstTraversal(const std::string& startVertex) const {
        std::unordered_map<std::string, bool> visited;
        std::queue<std::string> queue;

        visited[startVertex] = true;
        queue.push(startVertex);

        while (!queue.empty()) {
            std::string currentVertex = queue.front();
            std::cout << currentVertex << " ";
            queue.pop();

            for (const auto& neighbor : adjacencyList.at(currentVertex)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }

        std::cout << std::endl;
    }

    void depthFirstTraversal(const std::string& startVertex) const {
        std::unordered_map<std::string, bool> visited;
        depthFirstTraversalRecursive(startVertex, visited);
        std::cout << std::endl;
    }
    

private:
    void depthFirstTraversalRecursive(const std::string& vertex, std::unordered_map<std::string, bool>& visited) const {
        visited[vertex] = true;
        std::cout << vertex << " ";

        for (const auto& neighbor : adjacencyList.at(vertex)) {
            if (!visited[neighbor]) {
                depthFirstTraversalRecursive(neighbor, visited);
            }
        }
    }

    std::vector<std::string> vertices;
    std::vector<std::tuple<int, std::string, std::string>> edges;
    std::vector<std::vector<int>> adjacencyMatrix;
    std::unordered_map<std::string, std::vector<std::string>> adjacencyList;
};

void merge(std::vector<std::tuple<int, std::string, std::string>>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<std::tuple<int, std::string, std::string>> L(n1);
    std::vector<std::tuple<int, std::string, std::string>> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (std::get<0>(L[i]) < std::get<0>(R[j])) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<std::tuple<int, std::string, std::string>>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

Graph readGraphFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::vector<std::string> vertices;
    std::string line;

    if (file.is_open()) {
        std::getline(file, line);
        std::istringstream iss(line);
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(vertices));

        Graph graph(vertices);

        int i = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> weights;
            std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(weights));

            for (int j = 0; j < weights.size(); j++) {
                if (i != j && std::stoi(weights[j]) > 0) {
                    graph.addEdge(vertices[i], vertices[j], std::stoi(weights[j]));
                }
            }

            i++;
        }

        file.close();
        return graph;
    }
    else {
        throw std::runtime_error("Unable to open file");
    }
}

std::tuple<std::vector<std::tuple<std::string, std::string, int>>, int> kruskal(const std::vector<std::string>& vertices, const std::vector<std::tuple<int, std::string, std::string>>& edges) {
    std::vector<std::tuple<std::string, std::string, int>> mst;
    DisjointSet disjointSet(vertices);
    int totalWeight = 0;

    std::vector<std::tuple<int, std::string, std::string>> sortedEdges = edges;
    mergeSort(sortedEdges, 0, sortedEdges.size() - 1);

    for (const auto& edge : sortedEdges) {
        int weight = std::get<0>(edge);
        std::string v1 = std::get<1>(edge);
        std::string v2 = std::get<2>(edge);

        if (disjointSet.find(v1) != disjointSet.find(v2)) {
            disjointSet.unionSets(v1, v2);
            mst.push_back(std::make_tuple(v1, v2, weight));
            totalWeight += weight;
        }
    }

    return std::make_tuple(mst, totalWeight);
}

int main() {
    std::string filePath = "input.txt";
    Graph graph = readGraphFromFile(filePath);

    auto result = kruskal(graph.getVertices(), graph.getEdges());
    std::vector<std::tuple<std::string, std::string, int>> mst = std::get<0>(result);
    int totalWeight = std::get<1>(result);

    graph.printAdjacencyMatrix();
    graph.printAdjacencyList();

    std::cout << "Minimum spanning tree:" << std::endl;
    for (const auto& edge : mst) {
        std::cout << std::get<0>(edge) << " - " << std::get<1>(edge) << " : " << std::get<2>(edge) << std::endl;
    }
    std::cout << "Summary weight: " << totalWeight << std::endl;

    std::cout << "Breadth-First Traversal: ";
    graph.breadthFirstTraversal(graph.getVertices()[0]);

    std::cout << "Depth-First Traversal: ";
    graph.depthFirstTraversal(graph.getVertices()[0]);


    return 0;
}