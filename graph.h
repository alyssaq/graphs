/*
Adjacency list representation for sparse directed graphs.
Representation consists of a vector of pointers one, 
one for each vertex in the graph

@author: Alyssa Quek 
*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
 
class Graph {
  int numVertices_;    // No. of vertices
  std::vector<std::vector<int> > adj_;

 public:
  Graph(int V);  // Constructor
  void addEdge(int v, int w); // function to add an edge to graph
  void BFS(int s);  // prints BFS traversal from a given source s
};
 

#endif
