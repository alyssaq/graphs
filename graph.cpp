#include <iostream>
#include <sstream>
#include <queue>
#include <iterator>
#include "graph.h"

Graph::Graph(int numVertices) {
  numVertices_ = numVertices;
  for (int i = 0; i < numVertices; i++) {
    adj_.push_back(std::vector<EdgeNode>());
  }
}
 
void Graph::addEdge(int x, int y, int weight = 1) {
  EdgeNode edgeNode(y, weight);
  adj_[x].push_back(edgeNode); // Add edgeNode y to x’s list.
}

std::string Graph::BFS(int src) {
  // Mark all the vertices as not visited
  std::vector<bool> visited(numVertices_, false);
  std::queue<int> queue; // Create a queue for BFS
  std::vector<EdgeNode>::const_iterator vciter; //iter to get all adjacent vertices
  std::ostringstream sstream;

  // Mark the current node as visited and enqueue it
  visited[src] = true;
  queue.push(src);

  while (!queue.empty()) {
    // Dequeue a vertex from queue and print it
    sstream << queue.front() << " ";
    queue.pop();

    // Get all adjacent vertices of the dequeued vertex s
    // If a adjacent has not been visited, then mark it visited and enqueue it
    for (vciter = adj_[src].begin(); vciter != adj_[src].end(); ++vciter) {
      if (!visited[vciter->nodeIdx_]) {
        visited[vciter->nodeIdx_] = true;
        queue.push(vciter->nodeIdx_);
      }
    }
  }

  return sstream.str();
}