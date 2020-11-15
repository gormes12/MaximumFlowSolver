#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "MaxHeap.h"
#include "FlowNetworkGraph.h"
using namespace std;

class Program
{
private:
	int getPositiveNumberFromFile(ifstream& i_InFile);
	void getEdgeFromFile(ifstream& i_InFile, int &i_VertexI, int &i_VertexJ, int &i_Capacity, int i_NumOfVertex);
	bool checkIfVertexIsInRange(int i_Vertex, int i_NumOfVertex);
	void printMessage(int i_ExpectedNumbersInLine);
	void skipEmptyLine(ifstream& i_File, int & i_Len, int & i_Place, string & i_Line);
	void wrapCheckLine(ifstream& i_File, int i_ExpectedNumbersInLine);
	bool checkLine(string i_Line, int i_Len, int & io_CountNumbersInLine, bool & o_AtLeastOneDigit);
	void getSandT(ifstream& i_File, int & i_VertexS, int & i_VertexT, int i_NumOfVertex);
public:
	void start(char* i_FileName);
};