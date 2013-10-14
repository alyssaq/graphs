/*
    graph.h
  
    Interface file for _directed_ graphs.
    
    This is a very functional graph class, although it doesn't have every bell and whistle
    one might hope for.  One interesting design question is whether Has_cycle(void) should
    in fact be a member function of this class, or whether we should have some separate
    Graph_utility class (or even Has_cycle class) where we put such definitions.  You
    might keep this question in mind as we read Lakos and see if you can figure out what
    he would recommend in this case.
    
    This requires that the template type Vertex be totally ordered (i.e., < needs to be
    defined for objects of type Vertex).
    
    Interface by: Nic McPhee
    @Author: Alyssa Quek
*/

#ifndef _GRAPH_OLD_H_
#define _GRAPH_OLD_H_

#include <set.h>
#include <map.h>
#include <multimap.h>

/*
    We'll templatize Graph on two types.  One will be the type we'll use to
    represent a Vertex, and one will the type of the values that we associate
    with every edge.  Note that we don't always need values associated with edges
    (not all graphs are weighted).  This suggests that this interface has too much
    functionality for certain uses.  Given this, how might we change the design?
*/
template<class Vertex, class Edge_value>
class Graph
{
public:
         Graph(void);                        // Empty graph
    int  Num_vertices(void) const;
    int  Num_edges(void) const;
    // Is there an edge from p to q?
    bool Adjacent(const Vertex& p, const Vertex& q) const;
    // Assume it has this vertex.
    void DeleteVertex(const Vertex& p);
    // Assume it has this edge.
    void DeleteEdge(const Vertex& p, const Vertex& q);
    // Assume p not in graph already.
    void InsertVertex(const Vertex& p);            
    // Assume (p,q) not in graph already.
    void InsertEdge(const Vertex& p, const Vertex& q, const Edge_value& val = Edge_value());
    // Change the value associated with the edge from p to q.
    void Update(const Edge_value& e, const Vertex& p, const Vertex& q);
    // Return the value associated with the edge from p to q.
    Edge_value Retrieve(const Vertex& p, const Vertex& q) const;

private:
    // These typedef's are just here to create shorter, more "readable"
    // names for these commonly used types.
    // The set of vertices in the graph.
    typedef set<Vertex, less<Vertex> > vertex_set;
    // The set of (directed) edges from a vertex.
    typedef multimap<Vertex, Vertex, less<Vertex> > edge_set;
    // An edge is just an ordered pair of vertices.
    typedef pair<const Vertex, Vertex> edge_pair;
    // A map that gives us the Edge_value associated with every edge (i.e., edge_pair).
    typedef map<edge_pair, Edge_value, less<edge_pair> > edge_value_map;
    // The actual set of vertices.
    vertex_set vertices;
    // The set of edges.
    edge_set edges;
    // The mapping of edges to edge_vals.
    edge_value_map edge_vals;

public:
    // Here we define two iterators that allow us to easily
    // loop through both the set of vertices and the set of
    // edges.  In each case we're actually just using the iterators
    // that come with the set and map data structures, but we're
    // hiding that fact from users to increase insulation.
    // We're not providing a ton of different iterators and
    // operations on them, but it's enough to get by.
    typedef vertex_set::const_iterator vertex_iterator;
    typedef edge_value_map::const_iterator edge_iterator;
    vertex_iterator vertex_begin(void) const { return(vertices.begin()); };
    vertex_iterator vertex_end(void) const { return(vertices.end()); };
    edge_iterator edge_begin(void) const { return(edge_vals.begin()); };
    edge_iterator edge_end(void) const { return(edge_vals.end()); };

    // Code for checking to see if a graph has a cycle.
private:
    // A (private) auxillary function used in the calculation
    // of Has_cycle.
    bool Check_node_for_cycle(const Vertex& start_vertex, 
        set< Vertex, less<Vertex> >& processed,
        set< Vertex, less<Vertex> >& visited);
public:
    // Does our directed graph have a cycle?
    bool Has_cycle(void);
};

#endif