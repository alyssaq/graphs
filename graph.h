/*
Adjacency list representation for sparse directed graphs with weights.
Representation consists of a vector of vectors of EdgeNodes.
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

// Struct to store the vectors needed to print the shortest path
struct shortestPathObj {
  // A node's predecessor in the shortest path. -1 if non-existent
  std::vector<int>  predecessor_; 
  // Total shortest dist from src to a node
  std::vector<int>  distance_; 

  //Print the shortest path from src to any other node
  void print(int src) const;   
  //Print the shortest path from source to a destination node
  void printPath(int src, int dest) const; 
};

class Graph {   
  std::vector<std::vector<EdgeNode> > adj_;

 public:
  Graph(int numNodes);  
  void clear(); //empty the Graph
  int size() const;
  void addEdge(int x, int y, int weight);
  std::string BFS(int src) const;  // BFS traversal from a given source 

  /* Dijkstra's algorithm: find shortest path from a given source node
     O(E + n log n): E = numEdges, n = numNodes
  */
  void Dijkstra(int src, shortestPathObj &dij) const;    
};

#endif
