#include "graph.hpp"
#include <iostream>
#include <stack>

/**
 * @brief Constructs a graph with a specified number of nodes.
 * @param numNodes The number of nodes in the graph.
 */
Graph::Graph(int numNodes) : adjacencyList(numNodes) {}

void Graph::addEdge(int node1, int node2) {
    adjacencyList[node1].push_back(node2);  // Add node2 to the adjacency list of node1
    adjacencyList[node2].push_back(node1);  // Add node1 to the adjacency list of node2 (undirected graph)
}

void Graph::findEulerianCircuit() {
    if (!isEulerian()) {  // Check if the graph is Eulerian
        std::cout << "The graph does not have an Eulerian circuit." << std::endl;
        return;
    }

    std::vector<std::list<int>> tempAdjList = adjacencyList;  // Temporary copy for modification
    std::stack<int> currentPath;  // Stack to hold the current path
    std::vector<int> circuit;  // Vector to store the final Eulerian circuit

    // Find a starting node with at least one edge
    int startNode = -1;
    for (int i = 0; i < tempAdjList.size(); ++i) {
        if (!tempAdjList[i].empty()) {
            startNode = i;
            break;
        }
    }

    if (startNode == -1) {
        std::cout << "The graph has no edges." << std::endl;
        return;
    }

    currentPath.push(startNode);  // Start from a vertex with at least one edge

    while (!currentPath.empty()) {
        int currentNode = currentPath.top();  // Get the current node

        if (!tempAdjList[currentNode].empty()) {  // If the current node has neighbors
            int nextNode = tempAdjList[currentNode].front();  // Get the next node
            currentPath.push(nextNode);  // Push the next node to the stack

            tempAdjList[currentNode].remove(nextNode);  // Remove the edge from currentNode to nextNode
            tempAdjList[nextNode].remove(currentNode);  // Remove the edge from nextNode to currentNode
        } else {
            circuit.push_back(currentNode);  // Add the current node to the circuit
            currentPath.pop();  // Pop the current node from the stack
        }
    }

    std::cout << "Eulerian circuit: ";
    for (int node : circuit) {  // Print the Eulerian circuit
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

bool Graph::isConnected() {
    std::vector<bool> visited(adjacencyList.size(), false);  // Vector to track visited nodes
    int startNode = -1;

    // Find a starting node with neighbors
    for (int i = 0; i < adjacencyList.size(); ++i) {
        if (!adjacencyList[i].empty()) {
            startNode = i;
            break;
        }
    }

    if (startNode == -1) {
        return true;  // No edges in the graph, considered connected
    }

    dfs(startNode, visited);  // Perform DFS from the starting node

    for (int i = 0; i < adjacencyList.size(); ++i) {  // Check if all non-empty nodes are visited
        if (!adjacencyList[i].empty() && !visited[i]) {
            return false;
        }
    }

    return true;
}

void Graph::dfs(int node, std::vector<bool>& visited) {
    visited[node] = true;  // Mark the current node as visited
    for (int neighbor : adjacencyList[node]) {  // Visit all neighbors of the current node
        if (!visited[neighbor]) {
            dfs(neighbor, visited);
        }
    }
}

bool Graph::isEulerian() {
    if (!isConnected()) return false;  // The graph must be connected

    for (const auto& neighbors : adjacencyList) {  // Check if all vertices have an even degree
        if (neighbors.size() % 2 != 0) {
            return false;
        }
    }

    return true;
}

void Graph::display() const {
    for (std::vector<std::list<int>>::size_type i = 0; i < adjacencyList.size(); ++i) {
        std::cout << i << ": ";
        for (const auto& neighbor : adjacencyList[i]) {  // Print all neighbors of the current node
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}