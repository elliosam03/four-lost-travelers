#ifndef GRAPH_H
#define GRAPH_H

#include "graphLL.h"
#include <fstream>
#include <vector>

class Graph
{
public:
    Graph(int size = 0);
    bool isEmpty() const;
    void createGraph();
    void clearGraph();

    GraphLL<int> &getAdjacentVertices(int vertex);
    
    friend std::ostream &operator<<(std::ostream &out, Graph &g);

private:
    int maxSize = 0;
    std::vector<GraphLL<int>> graph;
};

// graph constructor
Graph::Graph(int size)
{
    if (size >= 0)
    {
        maxSize = size;
    }
    else
    {
        maxSize = 0;
    }
    graph.resize(maxSize);
}

// check if graph is empty
bool Graph::isEmpty() const
{
    return graph.empty();
}

// create graph using adjacency list
void Graph::createGraph()
{
    std::ifstream fin("graph.txt");
    
    if (!fin.is_open())
    {
        throw std::runtime_error("Cannot open input file.");
    }

    if (!isEmpty())
    {
        clearGraph();
    }

    int vertex;
    int adjacentVertex;
    int lastVertex = 0;


    while (fin >> vertex)   // find last vertex
    {
        if (vertex > lastVertex)
        {
            lastVertex = vertex;
        }
    }

    fin.clear();
    fin.seekg(0);   // return to beginning of file

    maxSize = lastVertex + 1;
    graph.resize(maxSize);

    while (fin >> vertex)
    {
        while (fin >> adjacentVertex && adjacentVertex != -1)
        {
            graph[vertex].insert(adjacentVertex);
        }
    }

    fin.close();
}

// clear graph
void Graph::clearGraph()
{
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i].deleteNodes();
    }
    graph.clear();
    maxSize = 0;
}

// return the vertex's adjacent vertexes
GraphLL<int> &Graph::getAdjacentVertices(int vertex)
{
    return graph[vertex];
}

// graph output operator override
std::ostream &operator<<(std::ostream &out, Graph &g)
{
    // graphviz
    out << "di-graph {" << std::endl;
    for (int i = 0; i < g.graph.size(); i++)
    {
        for (LinkedListIterator<int> graphIt = g.graph[i].begin(); graphIt != g.graph[i].end(); ++graphIt)
        {
            out << i << "->" << *graphIt << ";" << std::endl;
        }
    }
    out << std::endl;
    out << "}";
    return out;
}

#endif