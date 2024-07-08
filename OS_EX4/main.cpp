#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "graph.hpp"

/**
 * @brief Generates a random graph by adding a specified number of edges.
 * @param g The graph object.
 * @param numEdges The number of edges to add.
 * @param numVertices The number of vertices in the graph.
 */
void generateRandomGraph(Graph& g, int numEdges, int numVertices) {
    for (int i = 0; i < numEdges; ++i) {
        int node1 = rand() % numVertices;  // Generate a random node1
        int node2 = rand() % numVertices;  // Generate a random node2
        g.addEdge(node1, node2);  // Add an edge between node1 and node2
    }
}


int main(int argc, char* argv[]) {
    int numEdges = 0;
    int numVertices = 0;
    int seed = time(0);  // Default seed is current time
    int option;

    // Use getopt to parse command-line arguments
    while ((option = getopt(argc, argv, "e:v:s:")) != -1) {
        switch (option) {
            case 'e':
                numEdges = atoi(optarg);  // Get number of edges from argument
                break;
            case 'v':
                numVertices = atoi(optarg);  // Get number of vertices from argument
                break;
            case 's':
                seed = atoi(optarg);  // Get random seed from argument
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -e numEdges -v numVertices [-s seed]" << std::endl;
                return 1;
        }
    }

    // Validate the number of edges and vertices
    if (numEdges <= 0 || numVertices <= 0) {
        std::cerr << "Number of edges and vertices must be positive." << std::endl;
        return 1;
    }

    srand(seed);  // Set random seed

    Graph g(numVertices);  // Create a graph with the specified number of vertices
    generateRandomGraph(g, numEdges, numVertices);  // Generate the random graph

    std::cout << "Generated random graph with seed " << seed << ":" << std::endl;
    g.display();  // Display the generated graph

    std::cout << std::endl;
    g.findEulerianCircuit();  // Attempt to find and display the Eulerian circuit

    return 0;
}
