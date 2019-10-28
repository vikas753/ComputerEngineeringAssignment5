//////////////////////////////////////
//
//  Name  : VIKAS VEERABATHINI
//  NU ID : 001302155
//  Program to display mechanism of 
//  dijikstra's algorithm on an 
//  undirected map of NU campus
//
///////////////////////////////////// 

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cstdlib>
#include<sstream>
using namespace std;

// Node definition of NU campus map
typedef struct GraphNodeType
{
  string NodeKey;
  vector<double> lengthList;        // Array for Length from source to index of element
  vector<int> AdjacentNodeKeyList;  // Index in graph of elements
} GraphNode_t;

// Head node of an undirected graph of NU campus map
vector<GraphNode_t> GraphHeadNode;

// It reflects pattern of input which is
// <vertex1> <vertex2> <length>
#define NUM_ELEMS_CONTAINER 3

// Search for an element in graph nodes with string Key , return
// it's index if found else -1
int SearchElementIndexInGraph(string NodeKeySearch)
{
  for(int iterGraphNodes=0;iterGraphNodes < GraphHeadNode.size();iterGraphNodes++)
  {
    if(NodeKeySearch == GraphHeadNode[iterGraphNodes].NodeKey)
    {
      return iterGraphNodes;
    }
  }
  return -1;
}


// Creates an adjacency list with an input as a file
// handler

void CreateGraphInputElements(ifstream& InputFileHandler)
{
  string tempContainerStorage[NUM_ELEMS_CONTAINER];
  while((InputFileHandler >> tempContainerStorage[0]) && (InputFileHandler >> tempContainerStorage[1]) && (InputFileHandler >> tempContainerStorage[2]))
  {

    string source = tempContainerStorage[0];
    string destination = tempContainerStorage[1];
    float length = stof(tempContainerStorage[2]);
    cout << source << destination << length << endl;
    int sourceElemIndex = SearchElementIndexInGraph(source);
    int destElemIndex   = SearchElementIndexInGraph(destination);
   
    if(sourceElemIndex == -1)
    {
      GraphNode_t TempNode;
      TempNode.NodeKey = source;
      GraphHeadNode.push_back(TempNode);
      sourceElemIndex = GraphHeadNode.size()-1;
    }
   
    if(destElemIndex == -1)
    {
      GraphNode_t TempNode;
      TempNode.NodeKey = destination;
      TempNode.lengthList.push_back(length);
      TempNode.AdjacentNodeKeyList.push_back(sourceElemIndex);
      GraphHeadNode.push_back(TempNode);
      destElemIndex = GraphHeadNode.size()-1;
    }
   
    GraphHeadNode[sourceElemIndex].lengthList.push_back(length);
    GraphHeadNode[sourceElemIndex].AdjacentNodeKeyList.push_back(destElemIndex);
  }
}

// Display Graph elements with source node and connected 
// elements alongwith their weights
void DisplayGraph()
{
  for(int iterGraphNodes=0;iterGraphNodes < GraphHeadNode.size();iterGraphNodes++)
  {
    cout << " Source Node :" << GraphHeadNode[iterGraphNodes].NodeKey << endl; 
    for(int iterAdjacentNodes=0;iterAdjacentNodes < GraphHeadNode[iterGraphNodes].AdjacentNodeKeyList.size();iterAdjacentNodes++)
    {
      cout << "  ->  Length : " <<  GraphHeadNode[iterGraphNodes].lengthList[iterAdjacentNodes] << " ->  Node : " << GraphHeadNode[GraphHeadNode[iterGraphNodes].AdjacentNodeKeyList[iterAdjacentNodes]].NodeKey << endl;         
    } 
  }
}

int main()
{
  ifstream fileReader("InputElementsDB.txt");
  
  if (!fileReader)
  {
    cout << "Error InputElementsDB.txt failed to open program terminated";
    cin.ignore();
    exit(1);
  }  

  CreateGraphInputElements(fileReader);
  DisplayGraph();
  return 0;
}
