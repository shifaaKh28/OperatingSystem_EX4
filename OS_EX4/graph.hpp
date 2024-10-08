#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <list>

/**
 * @class Graph
 * @brief Represents an undirected graph using an adjacency list.
 *
 * The Graph class provides methods for adding edges, displaying the graph,
 * and finding an Eulerian circuit if it exists.
 */
class Graph {
public:
    /**
     * @brief Constructs a graph with a specified number of nodes.
     * @param numNodes The number of nodes in the graph.
     */
    Graph(int numNodes);

    /**
     * @brief Adds an undirected edge between two nodes.
     * @param node1 The first node.
     * @param node2 The second node.
     */
    void addEdge(int node1, int node2);

    /**
     * @brief Finds and prints the Eulerian circuit if it exists.
     */
    void findEulerianCircuit();

    /**
     * @brief Displays the adjacency list of the graph.
     */
    void display() const;
    
/*get the degree of a vertex*/
    int getDegree(int node) const;

private:
    std::vector<std::list<int>> adjacencyList; ///< Adjacency list representation of the graph.

    /**
     * @brief Checks if the graph is connected.
     * @return True if the graph is connected, false otherwise.
     */
    bool isConnected();

    /**
     * @brief Depth-first search helper function to check connectivity.
     * @param node The current node.
     * @param visited Vector to track visited nodes.
     */
    void dfs(int node, std::vector<bool>& visited);

    /**
     * @brief Checks if the graph has an Eulerian circuit.
     * @return True if the graph has an Eulerian circuit, false otherwise.
     */
    bool isEulerian();

    
};

#endif
