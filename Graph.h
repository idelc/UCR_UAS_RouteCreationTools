#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>

#include "graphVertex.h"

using namespace std;

class Graph {
private:
  // A vector containing all of the vertices
  // in the graph. The start vertex is in 
  // the first position in the vector.
  vector<Vertex> vertices;
public:
  // Default const
  Graph();
  // Reads the graph input file and instantiates a graph object
  Graph(list<point> points);
  ~Graph();
  // Outputs graph object to a .dot file, 
  // then makes a system call that calls dotty on 
  // this file. In the dotty file, each node should
  // include vertex label and its distance value.
  void output_graph(const string &);
  // Breadth First Search. Via a BFS traversal,
  // this function should assign each individual
  // vertex's distance to the number of hops that
  // the vertex is from the start vertex. You can 
  // find the pseudo code for BFS on graphs.pdf
  void bfs();

  list<point> customShortestPath();
};

#endif /* GRAPH_H_ */
