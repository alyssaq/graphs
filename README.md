# Graphs

One of the key data structures in computer science, the **graph**   
So timeless, so beautiful...

## To install and use [Boost Graph Library](http://www.boost.org/doc/libs/1_38_0/libs/graph/doc/quick_tour.html) on Mac
1) Install [Macports](http://www.macports.org/)     
2) Install boost with macports    

    > sudo ports install boost

Note that on Mac, the boost header files are located at: /opt/local/include/boost   
3) To compile a cpp file and include boost library .hpp files, use the -I flag:   

    > g++ main.cpp -I /opt/local/include/

4) To run:

    > ./a.out

## Viewing graphs with [GraphViz](http://www.graphviz.org/)
1) Install [GraphViz](http://www.graphviz.org/) with brew or macports    
2) Create a [dot file](http://www.graphviz.org/doc/info/lang.html)  
Note that on Mac, graphviz is located at: /usr/local/Cellar/graphviz/    
You may symlink to the dot executable at: /usr/local/Cellar/graphviz/2.32.0/bin/dot   
3) To create a png image from the dot file with the same filename:   

    > dot -O sample.dot -T png   

## References:
http://www-h.eng.cam.ac.uk/help/tpl/talks/C++graphs.html#Graphs   
http://facultypages.morris.umn.edu/~mcphee/Courses/1996_97/Spring/CSci_3190/Assignments/Graph/   
http://www.boost.org/doc/libs/1_54_0/libs/graph/doc/   
