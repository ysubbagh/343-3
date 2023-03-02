#include "graphm.h"
#include "nodedata.h"
#include <climits> 
#include <iostream>
#include <vector>

using namespace std;

// constructor
GraphM::GraphM() {
  size = 0;
  // setup of tabletype T
  for (int i = 0; i < MAXNODES; i++) {
    for (int j = 0; j < MAXNODES; j++) {
      T[i][j].visited = false;
      T[i][j].dist = INT_MAX; // infinite
      T[i][j].path = 0;
    }
  }
}

// functions//
// read in the file and build the graph
void GraphM::buildGraph(ifstream &file) {
  string line;
  getline(file, line);
  size = stoi(line);               // set size to the fist line in the file
  for (int i = 1; i <= size; i++) { // get the node names
    getline(file, line);
    data[i] = NodeData(line);
  }
  vector<int> nums;
  while (file.peek() != EOF && getline(file, line)) { // get and set the paths
    nums = parseString(line);
    if(nums[0] == 0) return; //end of data for the graph, 0 is first val in the line
    insertEdge(nums[0], nums[1], nums[2]);
  }
}
// helper function for buildGraph, parses apart the values in each line into a vector
vector<int> GraphM::parseString(string line) { 
  vector<int> nums; 
  int end;
  string temp;
  for(int i = 0; i < 3; i++){
    end = line.find(" ");
    if(end != -1){ //first 2 vals
      temp = line.substr(0, end);
      line = line.substr(end + 1);
    }else{ //last val, aka the dist
      temp = line;
    }
    nums.push_back(stoi(temp));
  }
  //cout << "nums: " << nums[0] << ", " << nums[1] << ", " << nums[2] << endl;
  return nums; 
}

//insert an edge between nodes
bool GraphM::insertEdge(int src, int dst, int dist){
  if(C[src][dst] != 0) return false; //already a distance set for that edge
  C[src][dst] = dist;
  return true; //basecase
}

//remove an edge between nodes
bool GraphM::removeEdge(int src, int dst){
  if(C[src][dst] == 0) return false; //there is no edge between those nodes
  C[src][dst] = 0;
  return true; //basecase
}

//find shortest path in the graph 
void GraphM::findShortestPath(){
  for(int src = 1; src <= size; src++){
    T[src][src].dist = 0;
    int v = 0;
    for (int i = 1; i<= size; i++) {
      if ( !T[src][i].visited && T[src][i].dist < T[src][v].dist){
        v = i; //find shortest path
      }
      T[src][v].visited = true;
      for (int w = 1; w <= size; w++) {
        if (!T[v][w].visited && C[v][w] != INT_MAX) {
          if (T[src][v].dist + C[v][w] < T[src][w].dist) {
            T[src][w].dist = T[src][v].dist + C[v][w];
            T[src][w].path = v;
          }
        }
      }
    }
  }
}

//uses "cout"s to demonstrate that the algorithm works properly.
void GraphM:: displayAll(){ 
  cout << "Description      From_Node  To_Node  Distance  Path" << endl;
  for(int i = 1; i <= size; i++){
    cout << data[i].data << endl; //node name
    for(int j = 1; j <= size; j++){
      if(i == j) continue;
      cout << "                      " << i << "        " << j << "      ";
      if(C[i][j] == 0){
        cout << "---       ---";
      }else{
        cout << T[i][j].dist << "        ";
        pathNums(i, j);
      }
      cout << endl;
    }
    cout << endl;
  }
}

//display the shortest distance with path info between the fromNode to toNode
void GraphM:: display(int src, int dst){
  if(src < 1 || src > size || dst < 1 || dst > size) cout << "Invalid nodes." << endl;
  if(src == dst) cout << "Same node entered." << endl;
  if(T[src][dst].dist == INT_MAX) cout << "No path exists." << endl;
  cout << src << " " << dst << " " << T[src][dst].dist << "    "; //given nodes and their dist
  pathNums(src, dst);
  cout << endl;
  pathName(src, dst);
  cout << endl;
}
//help display print out the node numbers in the path
void GraphM:: pathNums(int src, int dst){
  if (T[src][dst].path == 0) { //base case
    cout << src << " ";
    return;
  }
  pathNums(src, T[src][dst].path);
  cout << dst << " ";
}
//help display print out the node names
void GraphM:: pathName(int src, int dst){
  if (T[src][dst].path == 0) { //base case
    cout << data[src].data << endl;
    return;
  }
  pathName(src, T[src][dst].path);
  cout << data[dst].data << endl;
}

//help print check that build graph was done correctly
void GraphM::printNodes(){
  for(int src = 1; src <= size; src++){
    cout << "Node " << src << ": " << data[src] << endl;
    for(int dst = 1; dst <= size; dst++){
      if(src == dst || C[src][dst] == 0) continue;
      cout << src << " -> " << dst << " = " << C[src][dst] << endl;
    }
    cout << endl << endl;
  }
}
//helper print function to check the table after findingshortestpath
void GraphM:: printTable(){
  cout << "    ";
  for(int i = 1; i <= size; i++) {
    cout << i << "   ";
  }
  cout << endl;
  for(int i = 1; i <= size; i++){
    cout << i << " | ";
    for(int j = 1; j <= size; j++){
      if(T[i][j].dist == INT_MAX) continue;
      cout << T[i][j].dist << "  ";
    }
    cout << endl;
  }
}