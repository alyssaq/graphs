#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include "graph.h"

using namespace std;

Graph::Graph(int V) {
  numVertices_ = V;
  for (int i = 0; i < V; i++) {
    adj_.push_back(vector<int>());
  }
}
 
void Graph::addEdge(int v, int w) {
  adj_[v].push_back(w); // Add w to v’s list.
}
 
void Graph::BFS(int s) {
  // Mark all the vertices as not visited
  vector<bool> visited(numVertices_, false);
  queue<int> queue; // Create a queue for BFS
  std::vector<int>::const_iterator vciter; //iter to get all adjacent vertices

  // Mark the current node as visited and enqueue it
  visited[s] = true;
  queue.push(s);

  while (!queue.empty()) {
    // Dequeue a vertex from queue and print it
    cout << queue.front() << " ";
    queue.pop();

    // Get all adjacent vertices of the dequeued vertex s
    // If a adjacent has not been visited, then mark it visited and enqueue it
    for (vciter = adj_[s].begin(); vciter != adj_[s].end(); ++vciter) {
      if (!visited[*vciter]) {
        visited[*vciter] = true;
        queue.push(*vciter);
      }
    }
  }
}
