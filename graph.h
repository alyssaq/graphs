/*
Adjacency list representation for sparse directed graphs with weights.
Representation consists of a vector of vectors of EdgeNodes, 
Lists may also be used.
Each index in the vector represents a node/vertex
A node points to a vector of EdgeNode to indicate an edge to another node.

@author: Alyssa Quek 
*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <string>
#include <limits>

static const int MAXINT = std::numeric_limits<int>::max();

struct EdgeNode {
  int nodeIdx_;  //adjacency info
  int weight_;   //edge weight

  EdgeNode(int node, int weight) : nodeIdx_(node), weight_(weight) {};
};

class Graph {   
  std::vector<std::vector<EdgeNode> > adj_;

 public:
  Graph(int numNodes);  
  void clear(); //empty the Graph
  int size() const;
  void addEdge(int x, int y, int weight);
  std::string BFS(int src) const;  // BFS traversal from a given source 
  void Dijkstra(int src) const;    // Find shortest path with Dijkstra's algo
};

#endif
