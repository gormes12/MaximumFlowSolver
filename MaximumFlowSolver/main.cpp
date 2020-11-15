#define _CRT_SECURE_NO_WARNINGS
#include "Program.h"


/*

This program solves the Max-Flow Problem in Flow Network Graph, using Ford-Fulkerson.
Open the exe file from the cmd with one argument which is the path of the file that represents the graph.
The file must contains the following format:
Row nummber 1: integer positive number n, that represents the amount of vertexes in the graph
Row nummber 2: integer positive number m, that represents the edges in the graph
Row nummber 3: integer number, that represents the vertex S in the Flow Network Graph. This number must be between 1 to n.
Row nummber 4: integer number, that represents the vertex T in the Flow Network Graph. This number must be between 1 to n and different from S.
next rows:
m rows that each contains three numbers that represents edge in the Graph. for example: to represnt the edge (i,j) with capacity x
the row will be like: i j x. (i and j must be between 1 to n and x must be a positive integer.)

After the program reads the m rows of triples it stops reading from the file (even if there is more data)
*/

void main(int argc, char* argv[])
{
	Program program;
	program.start(argv[1]);
}


