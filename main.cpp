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
  std::cout << "size:" << g.size() << " - " << str << std::endl;

  Graph g2(6);
  g2.addEdge(1, 2, 2);
  g2.addEdge(1, 4, 6);
  g2.addEdge(1, 3, 2);
  g2.addEdge(2, 4, 3);
  g2.addEdge(3, 5, 6);
  g2.addEdge(4, 5, 1);
  g2.addEdge(4, 6, 5);
  g2.addEdge(5, 6, 2);
  std::cout << "size:" << g2.size() << std::endl;
  g2.Dijkstra(1);
  
  return 0;
}