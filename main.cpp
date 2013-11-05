#include "graph.cpp"
// Driver program to test methods of graph class
int main()
{

  Graph g(4);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 2);
  g.addEdge(2, 0);
  g.addEdge(2, 3);
  g.addEdge(3, 3);

  std::cout << "Following is Breadth First Traversal (starting from vertex 2) \n";
  std::string str = g.BFS(2);
  std::cout << "(" << g.numNodes() << " nodes, " << g.numEdges() << " edges) - " << str << std::endl;
  g.removeEdge(3, 3);
  g.removeEdge(3, 1);
  g.removeEdge(0, 1);
  str = g.BFS(2);
  std::cout << "(" << g.numNodes() << " nodes, " << g.numEdges() << " edges) - " << str << std::endl;
  g.removeNode(0);
  std::cout << "(" << g.numNodes() << " nodes, " << g.numEdges() << " edges)" << std::endl;
  

  std::cout << "Following is the shortest path (starting from vertex 1) \n";
  Graph g2(7);
  g2.addEdge(0, 1, 1);
  g2.addEdge(1, 2, 2);
  g2.addEdge(1, 4, 6);
  g2.addEdge(1, 3, 2);
  g2.addEdge(2, 4, 3);
  g2.addEdge(3, 5, 6);
  g2.addEdge(4, 5, 1);
  g2.addEdge(4, 6, 5);
  g2.addEdge(5, 6, 2);
  shortestPathObj dij;
  g2.Dijkstra(1, dij);
  dij.print(1);

  return 0;
}