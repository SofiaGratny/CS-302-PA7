#ifndef GRAPH
#define GRAPH

template<class LabelType>
class Graph
{
public:
    Graph();

    virtual int getEdgeWeight(LabelType start, LabelType end) const = 0;
    virtual ~Graph() { }

};
#include "graph.cpp"
#endif
