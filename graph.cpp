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

int Graph::numNodes() const {
  return adj_.size();
}

int Graph::numEdges() const {
  std::vector<std::vector<EdgeNode> >::const_iterator citer;
  int numEdges = 0;
  for (citer = adj_.begin(); citer != adj_.end(); citer++) {
    numEdges += citer->size();
  }
  return numEdges;
}
 
void Graph::addEdge(int x, int y, int weight = 1) {
  EdgeNode edgeNode(y, weight);
  adj_[x].push_back(edgeNode); // Add edgeNode y to x’s list.
}

//An EdgeNode is equal so long as the nodeIdx is the same.
//  The weight of the edge is irrelevant.
struct nodeEqual : std::unary_function<EdgeNode,bool> {
  const int &idx_;
  nodeEqual(const int &idx) : idx_(idx) {}

  bool operator()(const EdgeNode &edgeNode) const { 
    return edgeNode.nodeIdx_ == idx_; 
  }  
};

void Graph::removeEdge(int x, int y) {
  std::vector<EdgeNode> &adjNodes = adj_[x];  //erase-remove idiom
  adjNodes.erase(std::remove_if(adjNodes.begin(), adjNodes.end(), 
                                nodeEqual(y)), adjNodes.end());
}

void Graph::removeNode(int node) {
  adj_.erase(adj_.begin() + node); //erase this node and all its edges
  //Remove all the other edges from other nodes to this node of interest
  for (int i = 0; i < adj_.size(); i++) {
    this->removeEdge(i, node);
  }
}

std::string Graph::BFS(int src) const {
  std::vector<bool> visited(this->numNodes(), false); // All nodes not visited
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

void Graph::Dijkstra(int src, shortestPathObj &dij) const {
  int numNodes = this->numNodes();
  std::set<int> nodeSet; //set of all nodes to be processed
  std::vector<bool> visited(numNodes, false); // All nodes not visited
  dij.distance_.resize(numNodes, MAXINT);
  dij.predecessor_.resize(numNodes, -1);

  dij.distance_[src] = 0; //dist from src to src
  nodeSet.insert(nodeSet.end(), src); //O(1) with iterator hint
  
  while (!nodeSet.empty()) {
    int node = getClosestUnvisitedNode(dij.distance_, visited); //1st round, node = src
    visited[node] = true;
    nodeSet.erase(nodeSet.find(node), nodeSet.end());

    // Loop through adjacent nodes breadth-first.
    for (edgeNodeCiter vciter = adj_[node].begin(); vciter != adj_[node].end(); ++vciter) {
      int totalDist = dij.distance_[node] + vciter->weight_; //accumulate shortest dist from src
      int adjNode   = vciter->nodeIdx_;
      if (!visited[adjNode] && totalDist <= dij.distance_[adjNode]) {
        dij.distance_[adjNode]    = totalDist; //always keep the shortest dist from src to curNode
        dij.predecessor_[adjNode] = node;
        nodeSet.insert(nodeSet.end(), adjNode); // O(log n)
      }
    }
  }
}

//Print the shortest path from source to a destination node
void shortestPathObj::printPath(int src, int dest) const {
  if (predecessor_[dest] == -1) return;
  if (dest == src) std::cout << src << " ";

  printPath(src, predecessor_[dest]);
  std::cout << dest << " ";
}

//Print the shortest path from src to any other node
void shortestPathObj::print(int src) const {
  for (int i = 0; i < distance_.size(); i++) {
    std::cout << "(" << src << "," << i << ") dist:" << distance_[i] << ". Path:";
    printPath(src, i);
    std::cout << std::endl;
  }
}