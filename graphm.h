#include "nodedata.h" // node data
#include <climits> // to use int_max
#include <iostream> //input and output
#include <vector> 

using namespace std;

class GraphM {

public:
  // constructor//
  GraphM();

  // functions//
  //  builds up graph node information and adjacency matrix of edges between
  //  each node   reading from a data file.
  void buildGraph(ifstream &file);
  // insert an edge into graph between two given nodes
  bool insertEdge(int src, int dst, int dist);
  // remove an edge between two given nodes
  bool removeEdge(int src, int dst);
  // find the shortest path between every node to every other node in the graph,
  // i.e.,   TableType T is updated with shortest path information
  void findShortestPath();
  // uses "cout"s to demonstrate that the algorithm works properly.
  void displayAll() ;
  // display certain nodes shortest paths/
  void display(int src, int dst) ;
  //helper print functions to make sure other functions are working properly
  void printNodes();
  void printTable();

private:
  const static int MAXNODES = 101;
  NodeData data[MAXNODES]; // data for graph nodes

  int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix

  int size; // number of nodes in the graph
  struct TableType {
    bool visited; // whether node has been visited
    int dist;     // shortest distance from source known so far
    int path;     // previous node in path of min dist
  };
  TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path

  //helper functions//
  //parse apart the value for setting the cost array
  vector<int> parseString(string line);
  //display help functions
  void pathNums(int src, int dst);
  void pathName(int src, int dst);
  
};