/*
Adjacency list representation for sparse directed graphs.
Representation consists of a vector of pointers one, 
one for each vertex in the graph

@author: Alyssa Quek 
*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>

struct EdgeNode {
  int nodeIdx_;     //adjacency info
  int weight_;   //edge weight

  EdgeNode(int node, int weight) : nodeIdx_(node), weight_(weight) {};
};

class Graph {
  int numVertices_;    // No. of vertices
  std::vector<std::vector<EdgeNode> > adj_;

 public:
  Graph(int numVertices);  // Constructor
  void addEdge(int x, int y, int weight); // function to add an edge to graph
  void BFS(int src);  // prints BFS traversal from a given source src
};

#endif
