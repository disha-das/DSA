#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifndef KRUSHKAL
#define KRUSHKAL

#define N_VERTICES 5
#define N_EDGES 120

/*** GraphEdge class holds the weight and edge vertex attributes for an edge ***/
class GraphEdge {
        public:
                GraphEdge() {
                        weight = 0;
			vertex_u = 0;
			vertex_v = 0;
                }
                GraphEdge(int wt_value, int vertex_u_idx, int vertex_v_idx) {
                        weight = wt_value;
			vertex_u = vertex_u_idx;
			vertex_v = vertex_v_idx;
                }
                int weight;
		int vertex_u;
		int vertex_v;
                GraphEdge *next;
};

#endif
