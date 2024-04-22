#include "Graph.cpp" 

int main(void) {

    Graph g; 

    // Vertices and edges for the graph
    std::vector<std::string> vertices1 = { "1", "2", "3", "4", "5", "6" };
    std::vector<std::tuple<std::string, std::string, unsigned long>> edges1 = { 
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, 
        {"2", "3", 10}, {"2", "4", 15}, 
        {"3", "4", 11}, {"3", "6", 2}, 
        {"4", "5", 6}, 
        {"5", "6", 9} 
    };

    // Add vertices to the graph
    for (int i = 0; i < vertices1.size(); i++) {
        g.addVertex(vertices1[i]);
    }

    // Add edges to the graph
    for (int i = 0; i < edges1.size(); i++) {
        g.addEdge(std::get<0>(edges1[i]), std::get<1>(edges1[i]), std::get<2>(edges1[i]));
    }

    // Remove an edge from the graph
    g.removeEdge("1", "2");

    std::vector<std::string> path1; // Vector to store the shortest path
    std::vector<std::string> path2; // Vector to store the shortest path

    // Find the shortest path between vertices "1" and "6"
    unsigned long x = g.shortestPath("1", "3", path1); 

    // Find the shortest path between vertices "1" and "5"
    unsigned long y = g.shortestPath("1", "5", path2); 

    // Output results
    std::cout << "Minumum Distance:" << x << std::endl; 
    std::cout << "Path: " << std::endl; 
    for (const auto& vertex : path1) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    std::cout << "Minumum Distance:" << y << std::endl; 
    std::cout << "Path: " << std::endl; 
    for (const auto& vertex : path2) {
        std::cout << vertex << " "; 
    }
    std::cout << std::endl;
    return 0;
}
