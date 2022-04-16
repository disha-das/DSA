The executable provides an Single Source Shortest Path solution using  Dijkstra's Algorithm.

The number of vertices has to be specified under the macro NUM_VERTICES.
The number of edges has to be specified under the macro NUM_EDGES.

The array of pointers vertices* contains the details of all the vertices such as the minimum distance from source, predecessor and vertex number.
The array of pointers edges* contains the details of all the edges such as start vertex, end vertex and weight.

The executable prompts for a "graph_ip.txt" input file. This is a custome input file used to test the implementation of the algorithm. 
For running it on any of the DIMACS Input file, the name of the file has to be changed to that one in the .cpp file.
Also the macros NUM_VERTICES and NU_EDGES are to be defined accordingly.

Eg: for running this on the New York Graph.gr file, we have to change the filename to New York Graph.gr, the NUM_VERTICES to 264346 
and NUM_EDGES to 733846

After Dijkstra's algorithm run is complete, the Shortest Path and the predecessor of each vertex is displayed.

The algorithm implemented is O(V*E) and if the graph is complete, it is O(V^3).

This algorithm can be improved further:
One of the improvements can be made is that we first detect the unreachable nodes through BFS algorithm and then eliminate them from the input.
This will reduce the size of the input.  

 
