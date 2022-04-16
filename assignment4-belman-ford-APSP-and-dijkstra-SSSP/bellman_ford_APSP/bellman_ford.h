#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifndef BELLMAN_FORD
#define BELLMAN_FORD

/***
GraphEdge class holds the edge attributes of an edge in the graph.
start vertex's index : vertex_u
end vertex's index : vertex_v
weight of edge : weight
***/
class GraphEdge {
        public:
                GraphEdge() {
			vertex_u = 0;
			vertex_v = 0;
                        weight = 0;
                }
                GraphEdge(int vertex_u_idx, int vertex_v_idx, int wt_value) {
			vertex_u = vertex_u_idx;
			vertex_v = vertex_v_idx;
                        weight = wt_value;
                }
		int vertex_u;
		int vertex_v;
                int weight;
};

/***
GraphVertex class holds a vertex's attributes.
current minimum distance from source vertex : min_dist
curren predecessor to attain current minimum : predecessor_index
***/
class GraphVertex {
        public:
                GraphVertex() {
			min_dist = -1;
			predecessor_index = -1;
                }
                GraphVertex(int min_dist_val, int pred_v_idx) {
			min_dist = min_dist_val;
			predecessor_index = pred_v_idx;
                }
		int min_dist;
		int predecessor_index;
};

#endif
