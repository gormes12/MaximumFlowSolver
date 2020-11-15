#pragma once
#include "SimpleDirectedWeightedGraph.h"
#include "Queue.h"
#include <iostream>
#define NO_FLOW 0
using namespace std;

// This class inheritances from the class SimpleDirectedWeightedGraph, using the 
// value of AdjacencyMatrix as a capacity.

class FlowNetworkGraph : public SimpleDirectedWeightedGraph
{
private:
	int** m_FlowMatrix;
	
	int getMaxFlow(int i_S);
	void deleteFlowMatrix();
	void zeroFlowInAllEdges();
	void getResidualCapacityInPathFromSToT(SimpleDirectedWeightedGraph* i_ResidualGraph, int* i_Path, int i_T, int& io_Min);
	void addFlowInGraph(int i_ResidualCapacityToAdd, int* i_Path, int i_T);
	void updateResidualGraph(SimpleDirectedWeightedGraph* i_ResidualGraph, int* i_Path, int i_T);
	void printMinCut(SimpleDirectedWeightedGraph* i_ResidualGraph, int i_S);
	void printMaxFlowAndMinCut(SimpleDirectedWeightedGraph* i_ResidualGraph, int i_S, int i_NumOfIteration, const char* i_NameOfAlgorithm);
	void makeEmptyResidualGraph(int i_NumOfVertex);
	FlowNetworkGraph* makeResidualGraph();
	int* initResidualCapacityArr(int i_S);
	Pair* initPairArr(int i_S);
	void initPath(int* i_Path);
	int findMaxResidualCapacityWithDijkstra(int i_S, int i_T, int* i_Path);


public:
	FlowNetworkGraph(); //c'tor
	~FlowNetworkGraph(); //d'tor
	virtual void MakeEmptyGraph(int i_NumOfVertex) override;
	virtual void AddEdge(int i_Vertex1, int i_Vertex2, int i_Flow, int i_Capacity) throw (const char*);
	virtual void RemoveEdge(int i_Vertex1, int i_Vertex2) override;
	void FordFulkersonByBFS(int i_S, int i_T);
	void FordFulkersonByDijkstra(int i_S, int i_T);
};

