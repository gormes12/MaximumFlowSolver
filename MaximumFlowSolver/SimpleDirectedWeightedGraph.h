#pragma once
#define NOT_NEIGHBORS 0 //The capacity of an edge is a possitive number
#define NO_PATH -1 // There can not be a negative distance
#define NO_PARENT -1 // There can not be a negative vertex
#define M_INFINITY -1
#include "LinkedList.h"
#include "MaxHeap.h"
#include "Pair.h"

class SimpleDirectedWeightedGraph
{
protected:
	int** m_AdjacencyMatrix;
	int m_NumOfVertex;

	void deleteAdjacencyMatrix();
	int min(int i_Num1, int i_Num2);

public:
	SimpleDirectedWeightedGraph();  //c'tor
	~SimpleDirectedWeightedGraph();   //d'tor
	virtual void MakeEmptyGraph(int i_NumOfVertex);
	bool IsAdjacent(int i_Vertex1, int i_Vertex2);
	LinkedList<int>* GetAdjList(int i_Vertex);
	virtual void AddEdge(int i_Vertex1, int i_Vertex2, int i_Weight);
	virtual void RemoveEdge(int i_Vertex1, int i_Vertex2);
	int* BFS(int i_S, int* i_Path);
	void SetWeight(int i_Vertex1, int i_Vertex2, int i_Weight);
	int GetWeight(int i_Vertex1, int i_Vertex2);
	int GetNumOfVertex();
};

