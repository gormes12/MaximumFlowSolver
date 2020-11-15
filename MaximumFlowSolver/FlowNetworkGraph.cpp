#include "FlowNetworkGraph.h"

FlowNetworkGraph::FlowNetworkGraph()
{
	m_FlowMatrix = nullptr;
}

FlowNetworkGraph::~FlowNetworkGraph()
{
	if (m_FlowMatrix != nullptr)
	{
		deleteFlowMatrix();
	}
}

void FlowNetworkGraph::MakeEmptyGraph (int i_NumOfVertex)
{
	SimpleDirectedWeightedGraph::MakeEmptyGraph(i_NumOfVertex);

	if (m_FlowMatrix != nullptr)
	{
		deleteFlowMatrix();
	}

	m_FlowMatrix = new int*[i_NumOfVertex];
	for (int i = 0; i < i_NumOfVertex; i++)
	{
		m_FlowMatrix[i] = new int[i_NumOfVertex];
		for (int j = 0; j < i_NumOfVertex; j++)
		{
			m_FlowMatrix[i][j] = 0;
		}
	}
}

void FlowNetworkGraph::AddEdge(int i_Vertex1, int i_Vertex2, int i_Flow, int i_Capacity)
{
	if (i_Capacity > 0)
	{
		SimpleDirectedWeightedGraph::AddEdge(i_Vertex1, i_Vertex2, i_Capacity);
		m_FlowMatrix[i_Vertex1][i_Vertex2] = i_Flow;
		m_FlowMatrix[i_Vertex2][i_Vertex1] = i_Flow * -1;
	}
	else
	{
		throw "Capacity must be a positive number";
	}
}

void FlowNetworkGraph::RemoveEdge(int i_Vertex1, int i_Vertex2)
{
	SimpleDirectedWeightedGraph::RemoveEdge(i_Vertex1, i_Vertex2);
	m_FlowMatrix[i_Vertex1, i_Vertex2] = 0;
}

void FlowNetworkGraph::FordFulkersonByBFS(int i_S, int i_T)
{
	int* distanceArr;
	int* path = new int[m_NumOfVertex];
	int residualCapacityInPathToT, numOfIterations = 0;
	FlowNetworkGraph* residualGraph = makeResidualGraph(); //θ(n^2)

	zeroFlowInAllEdges(); //θ(n^2)
	distanceArr = residualGraph->BFS(i_S,path); //θ(n^2)
	while (distanceArr[i_T] != NO_PATH)
	{
		numOfIterations++;
		residualCapacityInPathToT = residualGraph->GetWeight(path[i_T], i_T); //init residualCapacity with the first edge (p[t]->t)
		getResidualCapacityInPathFromSToT(residualGraph, path, path[i_T], residualCapacityInPathToT); //θ(m)
		addFlowInGraph(residualCapacityInPathToT, path, i_T); //θ(m)
		updateResidualGraph(residualGraph, path,i_T); //θ(m)
		delete distanceArr;
		distanceArr = residualGraph->BFS(i_S, path); // θ(n^2)
	}

	printMaxFlowAndMinCut(residualGraph, i_S, numOfIterations, "BFS"); // θ(n^2)
	delete distanceArr;
	delete path;
	delete residualGraph;
}

void FlowNetworkGraph::FordFulkersonByDijkstra(int i_S, int i_T)
{
	int numOfIterations = 0, maxResidualCapacity;
	int* path = new int[m_NumOfVertex];
	FlowNetworkGraph* residualGraph = makeResidualGraph();
	
	zeroFlowInAllEdges();
	maxResidualCapacity = residualGraph->findMaxResidualCapacityWithDijkstra(i_S, i_T, path);
	while (maxResidualCapacity != NO_PATH)
	{
		numOfIterations++;
		addFlowInGraph(maxResidualCapacity, path, i_T);
		updateResidualGraph(residualGraph, path, i_T);
		maxResidualCapacity = residualGraph->findMaxResidualCapacityWithDijkstra(i_S, i_T, path);
	}

	printMaxFlowAndMinCut(residualGraph, i_S, numOfIterations, "Greedy");
	delete path;
	delete residualGraph;
}


void FlowNetworkGraph::addFlowInGraph(int i_ResidualCapacityToAdd, int* i_Path, int i_T)
{
	int u, v;

	while (i_Path[i_T] != NO_PARENT)
	{
		u = i_Path[i_T];
		v = i_T;
		m_FlowMatrix[u][v] += i_ResidualCapacityToAdd;
		m_FlowMatrix[v][u] = m_FlowMatrix[u][v] * -1;
		i_T = i_Path[i_T];
	}
}

void FlowNetworkGraph::updateResidualGraph(SimpleDirectedWeightedGraph * i_ResidualGraph, int * i_Path, int i_T)
{
	int u, v, newWeight;

	while (i_Path[i_T] != NO_PARENT)
	{
		u = i_Path[i_T];
		v = i_T;
		newWeight = m_AdjacencyMatrix[u][v] - m_FlowMatrix[u][v];
		i_ResidualGraph->SetWeight(u, v, newWeight);
		newWeight = m_AdjacencyMatrix[v][u] - m_FlowMatrix[v][u];
		i_ResidualGraph->SetWeight(v, u, newWeight);
		i_T = i_Path[i_T];
	}
}

int FlowNetworkGraph::getMaxFlow(int i_S) //sum up all the out edges from vertex S. 
{
	int maxFlow = 0;
	Node<int>* currNode;
	LinkedList<int>* sNeighboors =  this->GetAdjList(i_S);

	currNode = sNeighboors->GetHead();
	while (currNode != nullptr)
	{
		maxFlow += m_FlowMatrix[i_S][currNode->GetData()];
		currNode = currNode->m_Next;
	}

	delete sNeighboors;
	
	return maxFlow;
}

void FlowNetworkGraph::printMinCut(SimpleDirectedWeightedGraph * i_ResidualGraph, int i_S)
{
	Queue<int> vertexSCanNotReach, vertexSCanReach;
	int* path = new int[m_NumOfVertex];
	int* d = i_ResidualGraph->BFS(i_S, path);

	for (int i = 0; i < m_NumOfVertex; i++)
	{
		if (d[i] != NO_PATH)
		{
			vertexSCanReach.EnQueue(i + 1);
		}
		else
		{
			vertexSCanNotReach.EnQueue(i + 1);
		}
	}

	cout << "Min cut: S = ";
	if (!vertexSCanReach.IsEmpty())
	{
		vertexSCanReach.Print();
	}
	else
	{
		cout << "{ }\n";
	}

	cout << ". T = ";
	if (!vertexSCanNotReach.IsEmpty())
	{
		vertexSCanNotReach.Print();
	}
	else
	{
		cout << "{ }\n";
	}

	cout << "." << endl;
	delete path;
	delete d;
}

void FlowNetworkGraph::printMaxFlowAndMinCut(SimpleDirectedWeightedGraph * i_ResidualGraph, int i_S, int i_NumOfIteration, const char* i_NameOfAlgorithm)
{
	cout << i_NameOfAlgorithm << " Method:\n";
	cout << "Max flow = " << getMaxFlow(i_S) << endl;
	printMinCut(i_ResidualGraph, i_S);
	cout << "Number of iterations = " << i_NumOfIteration << endl;
}

FlowNetworkGraph* FlowNetworkGraph::makeResidualGraph()
{
	FlowNetworkGraph* residualGraph = new FlowNetworkGraph();

	residualGraph->makeEmptyResidualGraph(m_NumOfVertex);
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		for (int j = 0; j < m_NumOfVertex; j++)
		{
			if (m_AdjacencyMatrix[i][j] != NOT_NEIGHBORS) // if there is (i,j) edge
			{
				residualGraph->SetWeight(i, j, m_AdjacencyMatrix[i][j]);
			}
		}
	}

	return residualGraph;
}

void FlowNetworkGraph::makeEmptyResidualGraph(int i_NumOfVertex)
{
	SimpleDirectedWeightedGraph::MakeEmptyGraph(i_NumOfVertex);
}

void FlowNetworkGraph::getResidualCapacityInPathFromSToT(SimpleDirectedWeightedGraph* i_ResidualGraph, int * i_Path, int i_T, int& io_Min)
{
	if (i_Path[i_T] == NO_PARENT)
	{
		return;
	}
	else
	{
		io_Min = min(io_Min, i_ResidualGraph->GetWeight(i_Path[i_T], i_T));
		getResidualCapacityInPathFromSToT(i_ResidualGraph, i_Path, i_Path[i_T], io_Min);
	}
}

void FlowNetworkGraph::zeroFlowInAllEdges()
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		for (int j = 0; j < m_NumOfVertex; j++)
		{
			m_FlowMatrix[i][j] = 0;
		}
	}
}

void FlowNetworkGraph::deleteFlowMatrix()
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		delete[] m_FlowMatrix[i];
	}

	delete[] m_FlowMatrix;
}

int FlowNetworkGraph::findMaxResidualCapacityWithDijkstra(int i_S, int i_T, int * i_Path)
{
	int* residualCapacity = initResidualCapacityArr(i_S);  //for each vertex we saved its residual capacity
	int v, minCapacity, res;
	Pair u;
	Pair* pairArr = initPairArr(i_S);
	MaxHeap heap(pairArr, m_NumOfVertex);
	LinkedList<int>* uNeighboorsList;
	Node<int>* vNode;

	initPath(i_Path); //θ(n)
	while (!heap.IsEmpty())     // n iteration 
	{
		u = heap.DeleteMax(); //θ(logn)
		uNeighboorsList = GetAdjList(u.GetData()); //θ(n)
		vNode = uNeighboorsList->GetHead();
		while (vNode != nullptr)
		{
			v = vNode->GetData();
			if (u.GetData() == i_S)
			{
				minCapacity = m_AdjacencyMatrix[u.GetData()][v];
			}
			else
			{
				minCapacity = min(residualCapacity[u.GetData()], m_AdjacencyMatrix[u.GetData()][v]);
			}

			if (minCapacity > residualCapacity[v] && i_Path[v] != u.GetData() && v != i_S)
			{
				heap.IncreaseKey(heap.GetIndexPlaceInHeap(v), minCapacity); //θ(logn)
				residualCapacity[v] = minCapacity;
				i_Path[v] = u.GetData();
			}

			vNode = vNode->m_Next;
		}

		delete uNeighboorsList;
	}

	res = residualCapacity[i_T];
	delete[] pairArr;
	delete[] residualCapacity;

	return res;
}

void FlowNetworkGraph::initPath(int * i_Path)
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		i_Path[i] = NO_PARENT;
	}
}

int * FlowNetworkGraph::initResidualCapacityArr(int i_S)
{
	int* residualCapacityArr = new int[m_NumOfVertex];

	for (int i = 0; i < m_NumOfVertex; i++)
	{
		residualCapacityArr[i] = M_INFINITY;
	}

	residualCapacityArr[i_S] = 0;   // init S

	return residualCapacityArr;
}

Pair * FlowNetworkGraph::initPairArr(int i_S)
{
	Pair* pairArr = new Pair[m_NumOfVertex];

	for (int i = 0; i < m_NumOfVertex; i++)
	{
		pairArr[i].SetData(i);
		pairArr[i].SetKey(M_INFINITY);
	}

	pairArr[i_S].SetKey(0);   // In order for s to be first in max heap

	return pairArr;
}
