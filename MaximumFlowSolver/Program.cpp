#include "Program.h"


int Program::getPositiveNumberFromFile(ifstream & i_InFile)
{
	int res;

	i_InFile >> res;
	if (res < 0)
	{
		cout << "Invalid input\n";
		i_InFile.close();
		exit(1);
	}

	return res;
}

void Program::getEdgeFromFile(ifstream & i_InFile, int & i_VertexI, int & i_VertexJ, int & i_Capacity, int i_NumOfVertex)
{
	i_InFile >> i_VertexI;
	if (!checkIfVertexIsInRange(i_VertexI, i_NumOfVertex))
	{
		cout << "Invalid input. There can not be vertex whose number is " << i_VertexI << ". Max number is " << i_NumOfVertex << endl;
		i_InFile.close();
		exit(1);
	}

	i_InFile >> i_VertexJ;
	if (!checkIfVertexIsInRange(i_VertexJ, i_NumOfVertex))
	{
		cout << "Invalid input. There can not be vertex whose number is " << i_VertexJ << ". Max number is " << i_NumOfVertex << endl;
		i_InFile.close();
		exit(1);
	}

	if (i_VertexI == i_VertexJ)
	{
		cout << "It's simple graph, can't be self edge!"<< endl;
		i_InFile.close();
		exit(1);
	}
	i_InFile >> i_Capacity;
	if (i_Capacity <= 0)
	{
		cout << "Invalid input. Capacity must be positive\n";
		i_InFile.close();
		exit(1);
	}
}

bool Program::checkIfVertexIsInRange(int i_Vertex, int i_NumOfVertex)
{
	bool isOk = true;

	if ((i_Vertex > i_NumOfVertex) || (i_Vertex < 1))
	{
		isOk = false;
	}

	return isOk;
}

void Program::printMessage(int i_ExpectedNumbersInLine)
{
	if (i_ExpectedNumbersInLine == 3)
	{
		cout << "In order to insert an edge you must enter exactly 3 numbers!\nTwo vertexes and capacity" << endl;
	}
	else
	{
		cout << "You must enter exactly 1 number in order to insert: number of vertexes, number of edges, vertex 's' or vertex 't'" << endl;
	}
}

void Program::skipEmptyLine(ifstream & i_File, int & i_Len, int & i_Place, string & i_Line)
{
	do 
	{
		if (i_File.eof())
		{
			cout << "Invalid File! Missing data!\n";
			i_File.close();
			exit(1);
		}

		i_Place = (int)i_File.tellg();
		getline(i_File, i_Line);
		i_Len = (int)i_Line.length();

	} while (i_Len == 0);  // skip empty lines
}

void Program::wrapCheckLine(ifstream & i_File, int i_ExpectedNumbersInLine)
{
	string line;
	int len, place, countNumInLine = 0;
	bool atLeastOneDigit;

	do
	{
		skipEmptyLine(i_File, len, place, line);
		if (!checkLine(line, len, countNumInLine, atLeastOneDigit))
		{
			i_File.close();
			exit(1);
		}

	} while (!atLeastOneDigit); // skip lines that contain only spaces.

	if (countNumInLine == i_ExpectedNumbersInLine)
	{
		i_File.seekg(place);
	}
	else
	{
		printMessage(i_ExpectedNumbersInLine);
		i_File.close();
		exit(1);
	}
}

bool Program::checkLine(string i_Line, int i_Len, int & o_CountNumbersInLine, bool & o_AtLeastOneDigit)
{
	bool isValidLine = true;
	o_AtLeastOneDigit = false;

	for (int i = 0; i < i_Len; i++)
	{
		if (isdigit((int)i_Line[i]))
		{
			o_AtLeastOneDigit = true;
			if ((i == (i_Len - 1)) || (i_Line[i + 1] == ' '))
			{
				o_CountNumbersInLine++;
			}
		}
		else
		{
			if (i_Line[i] != ' ')
			{
				cout << "Invalid File! The file must contain only numbers!\n";
				isValidLine = false;
				break;
			}
		}
	}

	return isValidLine;
}

void Program::getSandT(ifstream & i_File, int & i_VertexS, int & i_VertexT, int i_NumOfVertex)
{
	wrapCheckLine(i_File, 1);
	i_VertexS = getPositiveNumberFromFile(i_File);
	wrapCheckLine(i_File, 1);
	i_VertexT = getPositiveNumberFromFile(i_File);
	if (i_VertexS == i_VertexT)
	{
		cout << "Invalid File! Vertex S and Vertex T must be different!\n";
		i_File.close();
		exit(1);
	}

	if (!(checkIfVertexIsInRange(i_VertexS, i_NumOfVertex) && checkIfVertexIsInRange(i_VertexT, i_NumOfVertex)))
	{
		cout << "Invalid File! Vertex S and Vertex T must be in range!\n";
		i_File.close();
		exit(1);
	}
}

void Program::start(char * i_FileName)
{
	int numOfVertex, numOfEdges, vertexS, vertexT;
	int vertexI, vertexJ, capacityEdge;
	bool fEof = false;
	FlowNetworkGraph G;
	ifstream graphInFile(i_FileName);
	if (!graphInFile.fail())
	{
		wrapCheckLine(graphInFile, 1);
		numOfVertex = getPositiveNumberFromFile(graphInFile);
		if (numOfVertex != 0)
		{
			wrapCheckLine(graphInFile, 1);
			numOfEdges = getPositiveNumberFromFile(graphInFile);
			getSandT(graphInFile, vertexS, vertexT, numOfVertex);

			G.MakeEmptyGraph(numOfVertex);
			for (int i = 0; i < numOfEdges; i++)
			{
				wrapCheckLine(graphInFile, 3);
				getEdgeFromFile(graphInFile, vertexI, vertexJ, capacityEdge, numOfVertex);
				G.AddEdge(vertexI - 1, vertexJ - 1, 0, capacityEdge);
			}

			G.FordFulkersonByBFS(vertexS - 1, vertexT - 1);
			cout << endl;
			G.FordFulkersonByDijkstra(vertexS - 1, vertexT - 1);
		}
		else
		{
			cout << "There are no vertex in graph.\n";
		}

		graphInFile.close();
	}
	else
	{
		cout << "File can't open. Check if the file exists.\n";
	}
}
