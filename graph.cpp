#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <iterator>
#include "graph.h"

Graph::Graph(int numNodes) {
  adj_.resize(numNodes, std::vector<EdgeNode>());
}

void Graph::clear() {
  std::vector<std::vector<EdgeNode> >::iterator iter;
  for (iter = adj_.begin(); iter != adj_.end(); iter++) {
    iter->clear();
  }
  adj_.clear();
}

int Graph::size() const {
  return adj_.size();
}
 
void Graph::addEdge(int x, int y, int weight = 1) {
  EdgeNode edgeNode(y, weight);
  adj_[x].push_back(edgeNode); // Add edgeNode y to x’s list.
}

std::string Graph::BFS(int src) const {
  std::vector<bool> visited(size(), false); // All nodes not visited
  std::queue<int> queue; // Create a queue for BFS
  std::vector<EdgeNode>::const_iterator vciter; //iter to get all adjacent nodes
  std::ostringstream sstream; //BFS string path

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

//concatenate vector into a string
std::string vector2string(const std::vector<int>& v) {
  std::ostringstream sstream;
  copy(v.begin(), v.end() - 1, std::ostream_iterator<int>(sstream, ", "));
  sstream << *(v.end() - 1);
  
  return sstream.str();
}

void Graph::Dijkstra(int src) const {
  int numNodes = size();
  std::vector<int> dists(numNodes, MAXINT);
  std::vector<int> previous(numNodes, -1);
  std::vector<int> nodeSet; //set of all nodes in Graph
  for (int i = 0; i < numNodes; i++) nodeSet.push_back(i);

  std::vector<int>::iterator iter;
  std::vector<EdgeNode>::const_iterator vciter;
  dists[src] = 0; //dist from src to src

  while (!nodeSet.empty()) {
    iter = std::min_element(dists.begin(), dists.end());
    int node = iter - dists.begin() + 1; //node with smallest dist
    std::cout << node << " " << vector2string(nodeSet) << std::endl;
    nodeSet.erase(std::remove(nodeSet.begin(), nodeSet.end(), node), nodeSet.end());
    std::cout << node << " " << vector2string(nodeSet) << std::endl;

    if (dists[node] == MAXINT) break; //inaccessible node

    for (vciter = adj_[node].begin(); vciter != adj_[node].end(); vciter++) {
      int totalDist = dists[node] + vciter->weight_; 
      int adjNode   = vciter->nodeIdx_;
      if (totalDist < dists[adjNode]) {
        dists[adjNode]    = totalDist;
        previous[adjNode] = node;
      }
    }
  }

  std::cout << "dists: " << vector2string(dists) << std::endl;
  std::cout << "prevs: " << vector2string(previous) << std::endl;
}

void Graph::Dijkstra(int src) const {
  int numNodes = size();
  std::vector<int> dists(numNodes, MAXINT);
  std::vector<int> previous(numNodes, -1);
  std::vector<int> nodeSet; //set of all nodes in Graph
  for (int i = 0; i < numNodes; i++) nodeSet.push_back(i);

  std::vector<int>::iterator iter;
  std::vector<EdgeNode>::const_iterator vciter;
  dists[src] = 0; //dist from src to src

  while (!nodeSet.empty()) {
    iter = std::min_element(dists.begin(), dists.end());
    int node = iter - dists.begin() + 1; //node with smallest dist
    std::cout << node << " " << vector2string(nodeSet) << std::endl;
    nodeSet.erase(std::remove(nodeSet.begin(), nodeSet.end(), node), nodeSet.end());
    std::cout << node << " " << vector2string(nodeSet) << std::endl;

    if (dists[node] == MAXINT) break; //inaccessible node

    for (vciter = adj_[node].begin(); vciter != adj_[node].end(); vciter++) {
      int totalDist = dists[node] + vciter->weight_; 
      int adjNode   = vciter->nodeIdx_;
      if (totalDist < dists[adjNode]) {
        dists[adjNode]    = totalDist;
        previous[adjNode] = node;
      }
    }
  }

  std::cout << "dists: " << vector2string(dists) << std::endl;
  std::cout << "prevs: " << vector2string(previous) << std::endl;
}


