#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <list>
#include <map>
#include <climits>

using namespace std;

class Vertex {
public:
  // An STL list of STL pairs. For each int,int pair, 
  // the integer values are the neighboring vertex's
  // position in the graph object's vector vertices 
  // and the cost of the edge to that neighbor.
  list<pair<int, int> > neighbors;
  // Individual vertex's label.
  int label;
  // Distance the vertex is from the start vertex.
  int distance;
  string color;
  // A pointer to the previous vertext in 
  // BFS traversal. Initially prev is null for all vertices.
  Vertex* prev;
  
  Vertex():label(-1),distance(INT_MAX),color("WHITE"),prev(0){}
  ~Vertex(){}
};

#endif /* VERTEX_H */
