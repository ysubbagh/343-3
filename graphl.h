#include "nodedata.h" // node data
#include <iostream>   //input and output
#include <vector>

using namespace std;

class GraphL {

public:
  // constructor
  GraphL();
  // destructor
  ~GraphL();

  // functions//
  // builds up graph node information and adjacency list of edges between each
  // node reading from a data file
  void buildGraph(ifstream &file);
  // Displays each node information and edge in the graph using couts
  void displayGraph();
  // Makes a depth-first search and displays each node in depth-first order
  void depthFirstSearch();

private:
  struct EdgeNode; // forward reference for the compiler

  struct GraphNode {    // structs used for simplicity, use classes if desired
    EdgeNode *edgeHead; // head of the list of edges
    NodeData *data;     // data information about each node
    bool visited;
  };

  struct EdgeNode { //insert in the front of the list, first to access will be at the back of the list
    int adjGraphNode; // subscript of the adjacent graph node
    EdgeNode *nextEdge;
  };

  // array of GraphNodes
  GraphNode graph[101];
  int size;

  //helper functions//
  //check build is correct
  void showNodes();
  //helper for displayAll
  void displayHelp(EdgeNode *head, int node);
  //recurisve help function for DFS
  void helpDFS(int node);
};