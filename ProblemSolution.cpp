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
  int inQueue;                      // Is the node in a Queue for algorithm
  float distance;                   
  int predecessorKeyIndex;           // Index of predecessor of node 
  vector<float> lengthList;        // Array for Length from source to index of element
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

#define INFINITY_SENTINEL 0x5A5A5A5A
#define INQUEUE_STATE     1
#define OUTQUEUE_STATE    0


// Checks whether it's distance from predecessor is lesser compared
// to that calculated previously , if so then it resets the distance
// and predecessor
void relaxAPi(int sourceIdx , int DestIdx , float weight)
{
  if(GraphHeadNode[DestIdx].distance > GraphHeadNode[sourceIdx].distance + weight)
  {
    GraphHeadNode[DestIdx].distance = GraphHeadNode[sourceIdx].distance + weight;
    GraphHeadNode[DestIdx].predecessorKeyIndex = sourceIdx;
  }
}

// Returns the node index with minimum distance
// returns -1 if no minimum index exists
int GetMinKeyIndex()
{
  int Minimum = INFINITY_SENTINEL;
  int MinKeyIndex = -1;

  for(int i=0;i<GraphHeadNode.size();i++)
  {
    if(GraphHeadNode[i].inQueue == INQUEUE_STATE)
    {
      if(GraphHeadNode[i].distance < Minimum)
      {
        MinKeyIndex = i;
      }
    }   
  }
  return MinKeyIndex;
}
void initialize_source_node(int SourceNodeIdx);

// APplies a dijkstra algorithm from sourceIdx and
// stops abruptly once DestIdx is encountered . 

float getShortestPath(int sourceIdx , int DestIdx)
{
  initialize_source_node(sourceIdx);
  int MinKeyIdx = -1;
  while((MinKeyIdx = GetMinKeyIndex()) != -1)
  {
    GraphHeadNode[MinKeyIdx].inQueue = OUTQUEUE_STATE;
    if(MinKeyIdx == DestIdx)
    {
      return GraphHeadNode[MinKeyIdx].distance;   
    }

    for(int i=0;i<GraphHeadNode[MinKeyIdx].AdjacentNodeKeyList.size();i++)
    {
      relaxAPi(MinKeyIdx , GraphHeadNode[MinKeyIdx].AdjacentNodeKeyList[i] , GraphHeadNode[MinKeyIdx].lengthList[i]); 
    }
  }
  return -1;
}

// Initialize a source node with a distance of 0 and
// other nodes at a distance of infinity
void initialize_source_node(int SourceNodeIdx)
{
  GraphHeadNode[SourceNodeIdx].distance = 0;
  GraphHeadNode[SourceNodeIdx].predecessorKeyIndex = -1;
  GraphHeadNode[SourceNodeIdx].inQueue = INQUEUE_STATE;

  for(int i=0;i<GraphHeadNode.size();i++)
  {
    if(i!= SourceNodeIdx)
    {
      GraphHeadNode[i].distance = INFINITY_SENTINEL; 
      GraphHeadNode[i].inQueue  = INQUEUE_STATE;
    }
  }
}

float getShortestPathString(string Source , string Destination)
{
  int sourceElemIndex = SearchElementIndexInGraph(Source);
  int destElemIndex   = SearchElementIndexInGraph(Destination);
  if((sourceElemIndex == -1) || (destElemIndex == -1))
  {
    return -1;
  }
  return getShortestPath(sourceElemIndex,destElemIndex);
}

void PrintShortestPath(string Source , string Dest)
{
  int SourceIdx =  SearchElementIndexInGraph(Source);
  int DestIdx   =  SearchElementIndexInGraph(Dest);

  cout << Dest << "<-";
 
  int tempPredecessorKeyIdx = GraphHeadNode[DestIdx].predecessorKeyIndex; 
  while(tempPredecessorKeyIdx != SourceIdx)
  {
    cout << GraphHeadNode[tempPredecessorKeyIdx].NodeKey << "<-" ; 
    tempPredecessorKeyIdx = GraphHeadNode[tempPredecessorKeyIdx].predecessorKeyIndex; 
  }

  cout << Source << endl;

  return;
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
  string source , destination;
  
  cout << " Enter Source element for shortest path calulations " << endl;
  cin >> source;
  cout << " Enter Destination element for shortest path calulations " << endl;
  cin >> destination;
  float ShortestPathDistance = -1.0;
  if((ShortestPathDistance = getShortestPathString(source,destination)) != -1)
  {
    cout << " Shortest Path : " << endl;
    PrintShortestPath(source,destination);
    cout << " Shortest Path Distance between source : " << source << " and destination : " << destination << " is : " << ShortestPathDistance << endl;
  }
  else
  {
    cout << " Error ! No shortest path found " << endl;
    exit(1);
  }

  return 0;
}
