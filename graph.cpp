#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <set>
#include <iterator>
#include "graph.h"

typedef std::vector<EdgeNode>::const_iterator edgeNodeCiter; 

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
    for (edgeNodeCiter vciter = adj_[curNode].begin(); vciter != adj_[curNode].end(); ++vciter) {
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

int getClosestUnvisitedNode(std::vector<int> &dists, std::vector<bool> &visited) {
  std::vector<int>::const_iterator citer = dists.begin();
  int minNode = -1, minDist = MAXINT;

  for (; citer != dists.end(); citer++) {
    int nodeIdx = citer - dists.begin();
    if (!visited[nodeIdx] && *citer < minDist) {
      minDist = *citer;
      minNode = nodeIdx;
    }
  }
  return minNode;
}

void printPath(int node, int src, std::vector<int> &predecessor) {
  if (predecessor[node] == -1) return;
  if (node == src) std::cout << src << " ";

  printPath(predecessor[node], src, predecessor);
  std::cout << node << " ";
}

void Graph::Dijkstra(int src) const {
  int numNodes = size();
  std::set<int> nodeSet; //set of all nodes to be processed
  std::vector<bool> visited(numNodes, false); // All nodes not visited
  std::vector<int>  distance(numNodes, MAXINT);
  std::vector<int>  predecessor(numNodes, -1);

  distance[src] = 0; //dist from src to src
  nodeSet.insert(nodeSet.end(), src); //O(1) with iterator hint
  
  while (!nodeSet.empty()) {
    int node = getClosestUnvisitedNode(distance, visited); //1st round, node = src
    visited[node] = true;
    nodeSet.erase(nodeSet.find(node), nodeSet.end());

    // Loop through adjacent nodes breadth-first.
    for (edgeNodeCiter vciter = adj_[node].begin(); vciter != adj_[node].end(); ++vciter) {
      int totalDist = distance[node] + vciter->weight_; //accumulate shortest dist from src
      int adjNode   = vciter->nodeIdx_;
      if (!visited[adjNode] && totalDist <= distance[adjNode]) {
        distance[adjNode]    = totalDist; //always keep the shortest dist from src to curNode
        predecessor[adjNode] = node;
        nodeSet.insert(nodeSet.end(), adjNode); // O(log n)
      }
    }
  }

  //Print the shortest path from src to any other node
  for (int i = 0; i < numNodes; i++) {
    std::cout << "(" << src << "," << i << ") dist:" << distance[i] << ". Path:";
    printPath(i, src, predecessor);
    std::cout << std::endl;
  }
}