#ifndef EDGE_HPP
#define EDGE_HPP


#include <iostream>
#include <string>


class Edge
{
    private:
        std::string start_of_edge; // Starting point of the edge
        std::string end_of_edge; // Ending point of the edge

    public:
        friend class Graph; // Granting access to the Graph class
        unsigned long weight_of_edge; // Weight of the edge
        bool isStart(std::string label_1, std::string label_2); // Check if the given labels are the start of this edge
        bool isStart(std::string label_1); // Overloaded function to check if the given label is the start of this edge
        bool isEnd(std::string label_1, std::string label_2); // Check if the given labels are the end of this edge
        bool isEnd(std::string label_1); // Overloaded function to check if the given label is the end of this edge

        Edge(std::string s, std::string e, unsigned long w)
        {
            start_of_edge = s; // Initializing the start of the edge
            end_of_edge = e; // Initializing the end of the edge
            weight_of_edge = w; // Initializing the weight of the edge
        }
};
#endif 