The executable provides an All Pairs Shortest Path solution using the Bellman Ford Algorithm.

V is the number of graph vertices.
E is the number of graph edges.

The executable prompts for a "data file input". Eg: "data_dimacs_NY_graph" or "data_small_graph" in the format mentioned in the 9th DIMACS Challenge.

From this data file, a graph specification file "input.gr" is written and operated on.

After the bellman ford algorithm run is complete, the APSP solution in printed on screen.

The algorithm implemented is O(V*V*E) and if the graph is complete, it is O(V^4).

This algorithm can be improved further:
Yen's improvements -
1) If a vertex v has a distance value that has not changed since the last time the edges out of v were relaxed, then there is no need to relax the edges out of v a second time.
2) Linearly ordered vertices are partitioned into 2 subsets. Main loop runs from |V| -1 to |V|/2

Bannister and Eppstein improvement-
An improvement over Yen's second method. Replace linear order with a random permutaion of vertices. Main loop runs |v|/3 times generally.

An alternate to this is to use Floyd Warshall which is O(V^3). This specifically tackels the APSP problem.
 
