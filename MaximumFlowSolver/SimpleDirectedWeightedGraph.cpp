#include "SimpleDirectedWeightedGraph.h"
#include "Queue.h"

SimpleDirectedWeightedGraph::SimpleDirectedWeightedGraph()
{
	m_NumOfVertex = 0;
	m_AdjacencyMatrix = nullptr;
}

SimpleDirectedWeightedGraph::~SimpleDirectedWeightedGraph()
{
	deleteAdjacencyMatrix();
}

void SimpleDirectedWeightedGraph::deleteAdjacencyMatrix()
{
	for (int i = 0; i < m_NumOfVertex; i++)
	{
		delete[] m_AdjacencyMatrix[i];
	}

	delete[] m_AdjacencyMatrix;
	m_NumOfVertex = 0;
}

void SimpleDirectedWeightedGraph::MakeEmptyGraph(int i_NumOfVertex)
{
	if (m_AdjacencyMatrix != nullptr)
	{
		deleteAdjacencyMatrix();
	}

	m_NumOfVertex = i_NumOfVertex;
	m_AdjacencyMatrix = new int*[i_NumOfVertex];
	for (int i = 0; i < i_NumOfVertex; i++)
	{
		m_AdjacencyMatrix[i] = new int[i_NumOfVertex];
		for (int j = 0; j < i_NumOfVertex; j++)
		{
			m_AdjacencyMatrix[i][j] = NOT_NEIGHBORS;
		}
	}
}

bool SimpleDirectedWeightedGraph::IsAdjacent(int i_Vertex1, int i_Vertex2)
{
	bool isAdjacent = false;

	if (m_AdjacencyMatrix[i_Vertex1][i_Vertex2] != NOT_NEIGHBORS)
	{
		isAdjacent = true;
	}

	return isAdjacent;
}

LinkedList<int>* SimpleDirectedWeightedGraph::GetAdjList(int i_Vertex)
{
	LinkedList<int> *adjList = new LinkedList<int>;

	for (int i = 0; i < m_NumOfVertex; i++)
	{
		if (m_AdjacencyMatrix[i_Vertex][i] != NOT_NEIGHBORS)
		{
			adjList->Insert(i);
		}
	}

	return adjList;
}

void SimpleDirectedWeightedGraph::AddEdge(int i_Vertex1, int i_Vertex2, int i_Weight)
{
	if (m_AdjacencyMatrix[i_Vertex1][i_Vertex2] == NOT_NEIGHBORS)
	{
		m_AdjacencyMatrix[i_Vertex1][i_Vertex2] = i_Weight;
	}
	else
	{
		cout << "Error! This is a simple graph! This edge is already exist!\n";
		exit(1);
	}
}

void SimpleDirectedWeightedGraph::RemoveEdge(int i_Vertex1, int i_Vertex2)
{
	m_AdjacencyMatrix[i_Vertex1][i_Vertex2] = NOT_NEIGHBORS;
}

int * SimpleDirectedWeightedGraph::BFS(int i_S, int* i_Path)
{
	int u, v;
	int* distanceArr = new int[m_NumOfVertex];
	Queue<int> Q;
	Node<int>* vNode;
	LinkedList<int>* uNeighboorsList;

	for (int i = 0; i < m_NumOfVertex; i++) // init - θ(n)
	{
		distanceArr[i] = NO_PATH;
		i_Path[i] = NO_PARENT;
	}

	Q.EnQueue(i_S);
	distanceArr[i_S] = 0;
	while (!Q.IsEmpty())
	{
		u = Q.DeQueue();
		uNeighboorsList = this->GetAdjList(u); //θ(n)
		vNode = uNeighboorsList->GetHead();
		while (vNode != nullptr)
		{
			v = vNode->GetData();
			if (distanceArr[v] == NO_PATH)
			{
				distanceArr[v] = distanceArr[u] + 1;
				i_Path[v] = u;
				Q.EnQueue(v);
			}
			vNode = vNode->m_Next;
		}

		delete uNeighboorsList;
	}

	return distanceArr;
}

void SimpleDirectedWeightedGraph::SetWeight(int i_Vertex1, int i_Vertex2, int i_Weight)
{
	m_AdjacencyMatrix[i_Vertex1][i_Vertex2] = i_Weight;
}

int SimpleDirectedWeightedGraph::GetWeight(int i_Vertex1, int i_Vertex2)
{
	return m_AdjacencyMatrix[i_Vertex1][i_Vertex2];
}

int SimpleDirectedWeightedGraph::GetNumOfVertex()
{
	return m_NumOfVertex;
}



int SimpleDirectedWeightedGraph::min(int i_Num1, int i_Num2)
{
	int min;

	if (i_Num1 < i_Num2)
	{
		min = i_Num1;
	}
	else
	{
		min = i_Num2;
	}

	return min;
}

