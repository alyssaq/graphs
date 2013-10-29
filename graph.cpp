#include <iostream>
#include <sstream>
#include <queue>
#include <iterator>
#include "graph.h"

Graph::Graph(int numNodes) {
  numNodes_ = numNodes;
  adj_.resize(numNodes, std::vector<EdgeNode>());
}
 
void Graph::addEdge(int x, int y, int weight = 1) {
  EdgeNode edgeNode(y, weight);
  adj_[x].push_back(edgeNode); // Add edgeNode y to x’s list.
}

std::string Graph::BFS(int src) {
  // Mark all the nodes as not visited
  std::vector<bool> visited(numNodes_, false);
  std::queue<int> queue; // Create a queue for BFS
  std::vector<EdgeNode>::const_iterator vciter; //iter to get all adjacent nodes
  std::ostringstream sstream;

  // Mark the current node as visited and enqueue it
  visited[src] = true;
  queue.push(src);

  while (!queue.empty()) {
    int curNode = queue.front();
    sstream << curNode << " ";
    queue.pop();

    // Get all adjacent nodes of the dequeued node
    // If an adjacent has not been visited, then mark it visited and enqueue it
    for (vciter = adj_[curNode].begin(); vciter != adj_[curNode].end(); ++vciter) {
      if (!visited[vciter->nodeIdx_]) {
        visited[vciter->nodeIdx_] = true;
        queue.push(vciter->nodeIdx_);
      }
    }
  }

  return sstream.str();
}