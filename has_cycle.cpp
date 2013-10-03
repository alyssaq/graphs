
/*
  has_cycle.cpp

  Implementation of the member function Has_cycle in the graph class.
  This function determines whether there is a cycle in a directed graph.

  The basic algorithm is to start at each node, and move forward along
  every path from that node (using depth first search).  I mark every
  vertex as _visited_ as we pass through it, and mark every vertex as 
  _processed_ once we have gone down every path from that vertex.  As an
  efficiency trick, we can stop the depth first search whenever we encounter
  a _processed_ vertex.  If we ever re-encounter a _visited_ vertex during
  a depth first search, we've found a cycle and can terminate the process.

  This is in _no way_ optimal.  There are a number of choices that could
  have been made differently, and which would have led to significant
  differences in the resulting implementation.  As one example, I chose
  to make Has_cycle a member function of the graph class, when it could
  well have been made a free function that takes a graph and returns a
  bool, or a member of some graph utility class.  
  
  I've also chosen to not "pollute" the graph class with member
  variables (like the processed and visited sets) and typedefs (such as
  set< Vertex, less<Vertex> >) that are only used for this function.  This
  keeps the definition of the Graph class cleaner, but makes these functions
  messier, so there's obviously a trade-off.

  As you work through the Lakos text, you may want to occassionally return
  to this code and apply his ideas and measures to see how well this code 
  measures up, and in what ways his ideas might be used to modify this code.

  Nic McPhee
  March, 1997
*/

#include <assert.h>

#include "graph.h"

// Determines whether the graph has a cycle.
template<class Vertex, class Edge_value>
bool Graph<Vertex, Edge_value>::Has_cycle(void)
{
  set< Vertex, less<Vertex> > processed;
  set< Vertex, less<Vertex> > visited;

  Graph<Vertex, Edge_value>::vertex_iterator i;
  bool has_cycle;

  // Go through each vertex and do a depth first search
  // starting there.
  i = vertex_begin();
  has_cycle = false;
  while (!has_cycle && i != vertex_end()) {
    has_cycle = has_cycle || Check_node_for_cycle(*i, processed, visited);
    // After each pass through check_node_for_cycle, there should
    // be no nodes left in visited.
    assert(visited.size() == 0);
    ++i;
  }

  // We have either processed every vertex, or we found a cycle and bailed early.
  assert(has_cycle || (processed.size() == Num_vertices()));

  return(has_cycle);
}

// This is the function that actually does all the real work.  We do a depth
// first search from start_vertex looking for cycles.  Note that it's crucial
// that the processed and visited arguments must be passed by reference so 
// that we can add and delete items from these sets in the various recursive
// calls.
template<class Vertex, class Edge_value>
bool Graph<Vertex, Edge_value>::Check_node_for_cycle(const Vertex& start_vertex, 
              set< Vertex, less<Vertex> >& processed,
              set< Vertex, less<Vertex> >& visited)
{
  if (processed.find(start_vertex) == processed.end()) {
    // We've not already processed this node in an earlier pass.
    // We now insert the vertex into the visited set.  The insert
    // method on sets returns a pair, the first of which is an
    // iterator pointing to the inserted item, and the second
    // of which is a boolean telling us whether the item was indeed
    // inserted, or whether it was already in the set.  We'll use
    // this boolean value to determine whether we'd already visited
    // this node, implying that we have a cycle.
    pair<set< Vertex, less<Vertex> >::iterator, bool> 
            insert_result(visited.insert(start_vertex));
    if (!insert_result.second) {
      // We've already visited this vertex on this pass, i.e.,
      // we have a cycle.
      return(true);
    } else {
      // We've not seen this node already.
      // Loop through the vertices that start_vertex has
      // edges going to, and make recursive calls for each of them.
      bool has_cycle = false;
      
      // A multimap can contain multiple pairs for the same key
      // (in our case, multiple edges leaving the same vertex).  The
      // multimap class has a member function equal_range that
      // returns a pair of iterators.  The first points to the
      // first item in the multiset with the given key (in our
      // case start_vertex), and the second points to the first
      // item _after_ the _last_ item with our given key.  Thus
      // one can loop starting at the first iterator and ending
      // at the second iterator, and get all the pairs that match
      // our key.
      pair<edge_set::iterator, edge_set::iterator> vertex_edge_bounds;
      vertex_edge_bounds = edges.equal_range(start_vertex);

      // Go through each edge from start_vertex, and recursively call
      // Check_node_for_cycle.
      edge_set::const_iterator i = vertex_edge_bounds.first;
      while (!has_cycle && i != vertex_edge_bounds.second) {
        has_cycle = has_cycle || Check_node_for_cycle((*i).second, processed, visited);
        ++i;
      }
      // We've now chased down every edge from start_vertex, so 
      // we'll add start_vertex to the set of processed vertices.
            processed.insert(start_vertex);
            // Remove start_vertex from the list of visited vertices.
            visited.erase(insert_result.first);
            return(has_cycle);
        }
    } else {
        // We've already been here, and there were no cycles from this
        // point.
        return(false);
    }
}