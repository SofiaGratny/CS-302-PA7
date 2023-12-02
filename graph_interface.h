#ifndef GRAPH_INTERFACE_
#define GRAPH_INTERFACE_
template<class LabelType>
class GraphInterface
{
public:
    /** 
    @return  */
    virtual int getNumVertices() const = 0;
    /** 
    @return */
    virtual int getNumEdges() const = 0;
    /** 
    @param start
    @param end 
    @param edgeWeight 
    @return */
    virtual bool add(LabelType start, LabelType end, int edgeWeight) = 0;
    /** 
    @param start 
    @param end 
    @return  */
    virtual bool remove(LabelType start, LabelType end) = 0;
    /** 
    @param start 
    @param end 
    @return */
    virtual int getEdgeWeight(LabelType start, LabelType end) const = 0;
    /** 
    @param start
    @param visit  */
    virtual void depthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;
    /** 
    @param start 
    @param visit*/
    virtual void breadthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;
    /** */
    virtual ~GraphInterface() { }
}; // end GraphInterface
#endif
