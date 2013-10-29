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

  g.clear();
  std::cout << "size:" << g.size() << std::endl;

  return 0;
}