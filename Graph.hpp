#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp" // Including the base class
#include "edge.hpp" // Including the edge class
#include "vertex.hpp" // Including the vertex class

#include <iterator>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>


class Graph : public GraphBase // Inheriting from GraphBase
{
    private:
        std::map<std::string, Vertex> vertex; // Map to store vertices
        std::map<int, Edge> edge; // Map to store edges
        int name = 0; // Variable to assign unique names to edges

        int getEdgeKey(std::string label1, std::string label2); // Get key for edge
        int getEdgeKey(std::string label1); // Overloaded function to get key for edge
        void removeEdge(std::string label); // Remove an edge
        int getWeight(std::string label_1, std::string label_2); // Get weight of the edge between two vertices
        std::map<std::string, Vertex*> getAdjacents(std::string label); // Get adjacent vertices of a vertex
        unsigned long comparator(std:: string key, std::string edge, unsigned long currentDistance, unsigned long previousDistance); // Compare distances for shortest path algorithm
        std::string minDistance(std::map<std::string, unsigned long> vertexQueue); // Get vertex with minimum distance from the source
        bool unvisited(std::string label, std::map<std::string, unsigned long> vertexQueue); // Check if a vertex is unvisited

    public:
        void addVertex(std::string label); // Add a vertex to the graph
        void removeVertex(std::string label); // Remove a vertex from the graph
        void addEdge(std::string label1, std::string label2, unsigned long weight); // Add an edge to the graph
        void removeEdge(std::string label1, std::string label2); // Remove an edge from the graph
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path); // Find the shortest path between two vertices

};

#endif // GRAPH_HPP
