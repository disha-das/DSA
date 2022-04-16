#include "bellman_ford.h"

using namespace std;

GraphEdge g_edg[60000000];
GraphVertex g_vert[25000000];

/*********
Initialize node min weights and predecessors
source_vertex_index: source vertex from which min paths to all other vertices is calculated
n_nodes: number of nodes in graph
99999999 is used as "infinity" to denote a very high weight or "no path"
*********/
void init_single_source(int source_vertex_index, int n_nodes)
{
	int i = 1;
	for(i = 1; i <= n_nodes; i++)
	{
		GraphVertex newnode(999999, -1);
		memcpy(&g_vert[i], &newnode, sizeof(struct GraphVertex));
	}
	g_vert[source_vertex_index].min_dist = 0;
}

/*********
Relaxes and edge between vertex_index_u and vertex_index_v
We improve shortest path to v if v.d (vertex_index_v.min_dist) via u (vertex_index_u) decreases.
vertex_index_u: from index for the directed edge
vertex_index_v: to index for the directed edge
weight: weight of edge from vertex_index_u to vertex_index_v
*********/
void relax(int vertex_index_u, int vertex_index_v, int weight)
{
	if(g_vert[vertex_index_v].min_dist > (g_vert[vertex_index_u].min_dist + weight))
	{
		g_vert[vertex_index_v].min_dist = g_vert[vertex_index_u].min_dist + weight;
		g_vert[vertex_index_v].predecessor_index = vertex_index_u;
	}
}

/*********
Compute shortest paths from source vertex to all other vertices in graph
source_vertex_index: source vertex
n_nodes: number of nodes in graph
n_arcs: number of edges in graph
*********/
int bellman_ford(int source_vertex_index, int n_nodes, int n_arcs)
{
	int i = 1, j = 1;
	init_single_source(source_vertex_index, n_nodes);
	for (i = 1; i < n_nodes ; i++)
		for (j = 1; j <= n_arcs; j++)
			relax(g_edg[j].vertex_u, g_edg[j].vertex_v, g_edg[j].weight);
	for (j = 1; j <= n_arcs; j++)
		if (g_vert[g_edg[j].vertex_v].min_dist > (g_vert[g_edg[j].vertex_u].min_dist + g_edg[j].weight))
			return -1;
	return 1;
}

int main()
{
	FILE *fptr1, *fptr2;
	char c, d, str[60];
	int nodes = 0, arcs = 0, i = 0, j = 1;
	char temp1[10], temp2[10], n_nodes[10], n_arcs[10];
	int no_neg_cycle;
	char data_file[100];

/*** Create graph specification file from data file ***/
	cout <<  "Enter data file name" << endl;
	scanf("%s",data_file);
	fptr1 = fopen(data_file,"r");
	fptr2 = fopen("input.gr","w");
	c = fgetc(fptr1);
	d = fgetc(fptr2);
	fputc(c, fptr2);
	for (i = 0; i < 6; i++)
	{
		fgets(str, 60, fptr1);
		if (strncmp(str, "p sp ", 5) == 0)
		{
			fseek(fptr1, -strlen(str), SEEK_CUR);
			/***read and store number of nodes and arcs***/
			fscanf(fptr1, "%s %s %s %s\n", temp1, temp2, n_nodes, n_arcs); 
			cout << "number of nodes are " << n_nodes << endl;
			cout << "number of arcs are " << n_arcs << endl ;
		}
		if (i != 2)
			fputs(str,fptr2);
		else
			fputs("c input file having graph specifications: input.gr\n", fptr2);
	}
	fprintf(fptr2, "c node ids are numbers in 1..%s\n", n_nodes);
	fputs("c\na 1 2 17\nc arc from node 1 to node 2 of weight 17\n", fptr2);
	c = fgetc(fptr1);
	d = fgetc(fptr2);
	while (c != EOF)
	{
		fputc(c, fptr2);
		c = fgetc(fptr1);
	}
	fclose(fptr1);
	fclose(fptr2);

	/*** read graph spec file and store edge details
	as an array of GraphEdge class elements***/
	fptr2 = fopen("input.gr","r");
        for (i = 1; i <= atoi(n_arcs) + 11; i++) {
		fgets(str, 60, fptr2);
		if ((strncmp(str, "a ", 2) == 0) && i > 10)
		{
			int vertex_u, vertex_v, weight;	
			fseek(fptr2, -strlen(str), SEEK_CUR);
			fscanf(fptr1, "%s %d %d %d\n", temp1, &vertex_u, &vertex_v, &weight);
			GraphEdge newnode(vertex_u, vertex_v, weight);
			memcpy(&g_edg[j], &newnode, sizeof(struct GraphEdge));
			j++;
		}
	}

	fclose(fptr2);

	/*** run bellman_Ford n_nodes times
	to obtain shortest paths from all vertices
	as source vertices
	Print results for each vertex as source vertext***/
	for (i = 1; i <= atoi(n_nodes); i++) {
		cout << "The shortest path details for source "<< i<<" are:" << endl;

		no_neg_cycle = bellman_ford(i, atoi(n_nodes), atoi(n_arcs));
		if(no_neg_cycle)
		{
			cout << "Graph contains no negative cycles" << endl;
		}
		else
		{
			cout << "Graph contains neative cycle" << endl;
			return 0;
		}

		cout << "<min weight> <pred idx>" << endl;
		for (j = 1; j <= atoi(n_nodes); j++) {
                	cout << g_vert[j].min_dist << " " << g_vert[j].predecessor_index << endl;
        	}
	}
	return 0;
}

