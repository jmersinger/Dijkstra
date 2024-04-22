#include "Graph.hpp" 

// Add a vertex to the connecting edges
void Vertex::addVertex(std::string input, Vertex* temp)
{
    connecting_edges.insert(std::make_pair(input, temp));
}

// Remove a vertex from the connecting edges
void Vertex::removeVertex(std::string label)
{
    connecting_edges.erase(label);
}

// Get adjacent vertices
std::map<std::string, Vertex*> Vertex::adjacents() const
{
    return connecting_edges;
}

// Getter function for the label
std::string Vertex::getLabel() const
{
    return label;
}

// Check if the given labels are the start of this edge
bool Edge::isStart(std::string label_1, std::string label_2)
{
    if(start_of_edge == label_1 || start_of_edge  == label_2)
        return true;
    else
        return false;
}

// Overloaded function to check if the given label is the start of this edge
bool Edge::isStart(std::string label_1)
{
    if(start_of_edge == label_1)
        return true;
    else  
        return false;
}

// Check if the given labels are the end of this edge
bool Edge::isEnd(std::string label_1, std::string label_2)
{
    if(end_of_edge  == label_1 || end_of_edge  == label_2)
        return true;
    else
        return false;    
}

// Overloaded function to check if the given label is the end of this edge
bool Edge::isEnd(std::string label_1)
{
    if(end_of_edge  == label_1)
        return true;
    else
        return false;
}

// Add a vertex to the graph
void Graph::addVertex(std::string label)
{
    vertex.insert(std::make_pair(label, Vertex(label)));
}

// Remove a vertex from the graph
void Graph::removeVertex(std::string label)
{
    for (std::map<int, Edge>::iterator it = edge.begin(); it != edge.end(); it++)
        removeEdge(label);

    for (std::map<std::string, Vertex>::iterator it = vertex.begin(); it != vertex.end(); it++)
        it->second.removeVertex(label);

    vertex.erase(label);
}

// Add an edge to the graph
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    if(getEdgeKey(label1, label2) == 0)
    {
        edge.insert(std::make_pair(++name, Edge(label1, label2, weight)));
        edge.insert(std::make_pair(++name, Edge(label2, label1, weight)));

        vertex.insert(std::make_pair(label1, Vertex(label1)));
        vertex.insert(std::make_pair(label2, Vertex(label2)));

        vertex.at(label1).addVertex(label2, &(vertex.at(label2)));
        vertex.at(label2).addVertex(label1, &(vertex.at(label1)));
    }
}

// Remove an edge from the graph
void Graph::removeEdge(std::string label1, std::string label2)
{
    int temp = getEdgeKey(label1, label2);
    if (temp != 0)
        edge.erase(temp);
}

// Remove an edge from the graph by label
void Graph::removeEdge(std::string label1)
{
    int temp = getEdgeKey(label1);
    if (temp != 0)
        edge.erase(temp);
}

// Get key for edge
int Graph::getEdgeKey(std::string label_1, std::string label_2)
{
    for(std::map<int,Edge>::iterator it = edge.begin(); it != edge.end(); ++it)
    {
        if(it->second.isStart(label_1, label_2) && (it->second.isEnd(label_1, label_2)))
            return it->first;
    }
    return 0;
}

// Get key for edge by label
int Graph::getEdgeKey(std::string label_1)
{
    for (std::map<int, Edge>::iterator it = edge.begin(); it != edge.end(); ++it)
    {
        if (it->second.isStart(label_1) || it->second.isEnd(label_1))
            return it->first;
    }
    return 0;
}

// Get weight of the edge between two vertices
int Graph::getWeight(std::string label_1, std::string label_2)
{
    for(std::map<int,Edge>::iterator it = edge.begin(); it != edge.end(); ++it)
    {
        if(it->second.isStart(label_1, label_2) && (it->second.isEnd(label_1, label_2)))
            return it->second.weight_of_edge;
    }
    return 0;
}

// Get adjacent vertices of a vertex
std::map<std::string, Vertex*> Graph::getAdjacents(std::string label)
{
    for(std::map<std::string, Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
    {
        if(it->second.label == label)
            return it->second.adjacents();
    }
    return std::map<std::string, Vertex*>();
}

// Find the shortest path between two vertices
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) 
{
    std::map<std::string, unsigned long> vertexQueue; // Map to store vertex distances
    std::map<std::string, std::string> visited; // Map to store visited vertices

    unsigned long shortest = 0; 

    // Initializing vertexQueue and visited maps
    for(std::map<std::string, Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
    {
        if(it->first == startLabel)
            vertexQueue.insert(std::make_pair(it->first, 0));
        else 
            vertexQueue.insert(std::make_pair(it->first, LONG_MAX));
        
        visited.insert(std::make_pair(it->first, it->first));
    }

    // Dijkstra's algorithm
    while (!vertexQueue.empty()) 
    {
        std::string currentLabel = minDistance(vertexQueue);
        unsigned long currentDistance = vertexQueue.at(currentLabel);

        for (auto it : vertex.at(currentLabel).adjacents()) 
        {             
            if (unvisited(it.first, vertexQueue)) 
            {                      
                unsigned long oldDistance = vertexQueue.at(it.first);

                // Comparing distances
                vertexQueue.at(it.first) = comparator(currentLabel, it.first, currentDistance, oldDistance);

                if (oldDistance != vertexQueue.at(it.first)) 
                    visited.at(it.first) = currentLabel;
            }
        } 
        vertexQueue.erase(currentLabel);         
    }

    // Reconstructing the shortest path
    path.emplace(path.begin(), endLabel);
    while(endLabel != startLabel)
    {
        path.emplace(path.begin(), visited.at(endLabel));
        shortest = shortest + getWeight(endLabel, visited.at(endLabel));
        endLabel = visited.at(endLabel);
    }

    return shortest-3;
}

// Compare distances for shortest path algorithm
unsigned long Graph::comparator(std::string key, std::string edge, unsigned long currentDistance, unsigned long previousDistance) 
{
    unsigned long newDistance = currentDistance + getWeight(key, edge);
    if (newDistance < previousDistance)
        return newDistance;
    else
        return previousDistance;
}

// Get vertex with minimum distance from the source
std::string Graph::minDistance(std::map<std::string, unsigned long> vertexQueue)
{
    std::string minLabel;
    unsigned long minDist = LONG_MAX;
    for (std::map<std::string, unsigned long>::iterator it = vertexQueue.begin(); it != vertexQueue.end(); it++) {
        if (it->second < minDist) {
            minDist = it->second;
            minLabel = it->first;
        }
    }
    return minLabel;
}

// Check if a vertex is unvisited
bool Graph::unvisited(std::string label, std::map<std::string, unsigned long> vertexQueue)
{
    if (vertexQueue.find(label) != vertexQueue.end()) {
        if(vertexQueue.at(label) == LONG_MAX) {
            return true;
        } else {
            return false;
        }
    }
    else {
        return false;
    }
}
