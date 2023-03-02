#include "graphl.h"
#include "nodedata.h"
#include <climits> 
#include <iostream>
#include <vector>

using namespace std;

//constructor
GraphL:: GraphL(){
  size = 0;
  for(int i = 0; i < 101; i++){
    graph[i].visited = false;
    graph[i].edgeHead = nullptr;
    graph[i].data = nullptr;
  }
}

//destructor
GraphL:: ~GraphL(){
  EdgeNode *copy, *temp;
  for(int i = 0; i < 101; i++){
    copy = graph[i].edgeHead;
    while(copy != nullptr){
      temp = copy -> nextEdge;
      delete copy;
      copy = temp;
    }
    if(graph[i].data != nullptr) delete graph[i].data;
    graph[i].data = NULL;
    graph[i].edgeHead = NULL;
  }
  delete copy;
  delete temp;
  copy = NULL;
  temp = NULL;
}

//functions//

//build the graph from the given file
void GraphL:: buildGraph(ifstream &file){
  string line;
  getline(file, line);
  size = stoi(line);
  if(size > 100){
    cout << "Too many nodes entered." << endl;
    return;
  }
  for(int i = 1; i <= size; i++){
    getline(file, line);
    graph[i].data = new NodeData(line); //enter name into the node
    graph[i].edgeHead = nullptr;
  }
  int from, to, space;
  while(getline(file, line)){
    space = line.find(" ");
    from = stoi(line.substr(0, space));
    to = stoi(line.substr(space + 1));
    if(from == 0 || to == 0) return; //end of graph
    EdgeNode* copy = graph[from].edgeHead;
    graph[from].edgeHead = new EdgeNode;
    graph[from].edgeHead -> nextEdge = copy;
    graph[from].edgeHead -> adjGraphNode = to;
  }
}

//Makes a depth-first search and displays each node in depth-first order
void GraphL:: depthFirstSearch(){
  cout << "Depth-first ordering: ";
  for(int i = 1; i <= size; i++){
    if(!graph[i].visited) helpDFS(i);
  }
  cout << endl;
}
//helper function for dfs, uses recursion
void GraphL:: helpDFS(int node){
  cout << node << " ";
  graph[node].visited = true;
  EdgeNode* copy = graph[node].edgeHead;
  while (copy != nullptr) {
    if (!graph[copy -> adjGraphNode].visited) {
      helpDFS(copy -> adjGraphNode);
    }
    copy = copy -> nextEdge;
  }
}

// Displays each node information and edge in the graph using couts
 void GraphL:: displayGraph(){
   for(int i = 1; i <= size; i++){
     cout << "Node " << i << "   " << graph[i].data -> data << endl;
     displayHelp(graph[i].edgeHead, i);
     cout << endl;
   }
}

//helper display all
void GraphL:: displayHelp(EdgeNode *head, int node){
  if(head != nullptr){
    cout << "Edge " << node << " " << head -> adjGraphNode << endl;
    displayHelp(head -> nextEdge, node);
  }
}

//helper fuction to make sure that buildGraph was good
void GraphL:: showNodes(){
  for(int i = 1; i <= size; i++){
     EdgeNode* copy = graph[i].edgeHead;
     cout << graph[i].data -> data << endl;
     while(copy != nullptr){
       cout << copy -> adjGraphNode << " ";
       copy = copy -> nextEdge;
     }
     cout << endl;
   }
}


