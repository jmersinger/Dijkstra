#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <string>
#include <map>


class Vertex
{
    private:
        std::string label; // Label of the vertex
        std::map<std::string, Vertex*> connecting_edges; // Map to store connecting vertices
        std::string getLabel() const; // Getter function for the label

    public:
        friend class Graph; // Granting access to the Graph class
        void addVertex(std::string label, Vertex* v); // Add a vertex to the connecting edges
        void removeVertex(std::string label); // Remove a vertex from the connecting edges
        std::map<std::string, Vertex*> adjacents() const; // Get adjacent vertices

        Vertex(std::string input)
        {
            this->label = input; // Initializing the label of the vertex
        }
};

#endif 