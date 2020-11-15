# MaximumFlowSolver

# Introduction
Solves the Max-Flow problem on a given network, based on Ford-Fulkerson algorithm, and compares between BFS and Dijkstra implementations of that algorithm. 

## Deploying
1. Build Solution
2. Download the input files inside of repository `MaximumFlowSolver` or create one by the following format that occurs down.
3. Run the exe file (that created as a result of step 1#) from the cmd with one argument input which is the path of the input file that represents the graph.


The file must contains the following format:<br>
Row number 1: integer positive number n, that represents the amount of vertexes in the graph<br>
Row number 2: integer positive number m, that represents the edges in the graph <br>
Row number 3: integer number, that represents the vertex S in the Flow Network Graph. This number must be between 1 to n. <br>
Row number 4: integer number, that represents the vertex T in the Flow Network Graph. This number must be between 1 to n and different from S. <br>
next rows: <br>
m rows that each contains three numbers that represents edge in the Graph.<br>
for example: to represnt the edge (i,j) with capacity x the row will be like: i j x. (i and j must be between 1 to n and x must be a positive integer.)

After the program reads the m rows of triples it stops reading from the file (even if there is more data)
