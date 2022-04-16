#include <iostream>
#include <string>
#include "kruskal.h"

using namespace std;

GraphEdge g_edg[100000];
GraphEdge mst_edg[100000];
int vertex_name_arr[100];
int vertex_parent_arr[100];

/*********
Initialize the membership sets for Name Array Implementation.
Each vertex forms a separate singleton set having name as
it's own index.
*********/
void init_name_array(int num_vertices)
{
	int i = 0;
	for (i = 0; i < num_vertices; i++)
	{
		vertex_name_arr[i] = i;
	}
}

/*********
Initialize the membership sets for Parent Array Implementation.
Each vertex forms a separate singleton set having parent (set's root) as
it's own index.
*********/
void init_parent_array(int num_vertices)
{
	int i = 0;
        for (i = 0; i < num_vertices; i++)
        {
                vertex_parent_arr[i] = i;
        }
}

/*********
Returns name of membership set for input vertex index
as per Name Array Implementation.
*********/
int find_vertex_name(int vertex)
{
	return vertex_name_arr[vertex];	
}


/*********
Returns name of membership set for input vertex index
as per Parent Array Implementation.
*********/
int find_vertex_parent(int vertex)
{
	int y = vertex_parent_arr[vertex];
	while (y != vertex_parent_arr[y])
		y = vertex_parent_arr[y];
	return y;
}

/*********
Returns name of membership set for input vertex index
as per Parent Array Implementation with Path Compression.
This reduces the time taken in subsequent find operations.
*********/
int find_vertex_parent_path_compress(int vertex)
{
	int i = 0;
	int j = 0;
	int compression_array[100] = {-1};
	int y = vertex;
	int z;
	int root;
	/*** while root is not found, keep building compression array ***/
	while (y != vertex_parent_arr[y])
	{
		compression_array[i] = y;
		i++;
		y = vertex_parent_arr[y];
	}
	j = i;
	i = 0;
	z = compression_array[0];
	root = y;
	/*** hook all in compression set directly to the rooti of the set ***/
	while (j > 0)
	{
		vertex_parent_arr[z] = root;
		j--;
		i++;
		z = compression_array[i];
	}
	return root;
}

/*********
Merge two vertex sets based on Parent Array Implementation.
Membership sets of vertex vertex_u and vertex_v are merged using union operation.
*********/
void union_vertices_parent(int vertex_u, int vertex_v, int num_vertices)
{
	int smaller = vertex_u;
        int greater = vertex_v;
	int i = 0;

        if (vertex_u > vertex_v)
        {
                smaller = vertex_v;
                greater = vertex_u;
        }
	vertex_parent_arr[greater] = smaller;
}

/*********
Merge two vertex sets based on Name Array Implementation.
Membership sets of vertex vertex_u and vertex_v are merged using union operation.
*********/
void union_vertices_name(int vertex_u, int vertex_v, int num_vertices)
{
	int i = 0;
	int smaller = vertex_u;
	int greater = vertex_v;

	if (vertex_u > vertex_v)
	{
		smaller = vertex_v;
		greater = vertex_u;
	}

	for (i = 0; i < num_vertices; i++) 
	{
		if(vertex_name_arr[i] == greater)
			vertex_name_arr[i] = smaller;
	}
}

/*** Lomuto Partition API for Quicksort **/
int partition(int low, int high)
{
	GraphEdge pivot = g_edg[high];
	int i = (low - 1);

	for (int j = low; j <= high- 1; j++)
	{
		if (g_edg[j].weight <= pivot.weight)
		{
			i++;
			GraphEdge temp;
			memcpy(&temp, &g_edg[i], sizeof(struct GraphEdge));
			memcpy(&g_edg[i], &g_edg[j], sizeof(struct GraphEdge));
			memcpy(&g_edg[j], &temp, sizeof(struct GraphEdge));
		}
	}
	{
		GraphEdge temp;
		memcpy(&temp, &g_edg[i+1], sizeof(struct GraphEdge));
		memcpy(&g_edg[i+1], &g_edg[high], sizeof(struct GraphEdge));
		memcpy(&g_edg[high], &temp, sizeof(struct GraphEdge));
	}
	return (i + 1);
}

/*** Recursive quicksort API ***/
void quickSort(int low, int high) 
{
	if (low < high)
	{
		int pi = partition(low, high);

		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}
  
/*** Call quicksort algo to sort graph edges based on weight values ***/
void sort_graph_edges(int arr_size) {
	quickSort(0, arr_size - 1);	
}

static void usage() {
	cout << "This executable implements the krushkal algo to find MST in 3 ways/modes:" <<endl;
	cout << "mode1: name array" <<endl;
	cout << "mode2: parent array" <<endl;
	cout << "mode3: parent array with weighted merge" <<endl;
	cout << "First provide as input the graph:" <<endl;
}

int main()
{
	int mode;
	int n_edges, n_vert;
	int n_mst_edges;
	int i = 0, j = 0, z = 0;
	void (*init_vertex_set)(int num_vertices);
	int (*find_vertex)(int vertex);
	void (*union_vertices)(int vertex_u, int vertex_v, int num_vertices);

	usage();

	/*** Take as input all graph details in specified format***/
	cout << "\n\nEnter number of edges in graph" <<endl;
	cin >> n_edges;
	cout << "\n\nEnter number of vertices in graph" <<endl;
        cin >> n_vert;
	cout << " Input all edges:" <<endl;
	cout << "[<weight> <index of vertex u> <index of vertex v>]:" <<endl;
	cout << "Example, an edge of weight 5 between vertex 1 and 2: [5 1 2]" <<endl;
	for (i = 0; i < n_edges; i++) {
		int weight, vertex_u, vertex_v;
		cout << "\nEnter edge " << i << ":"<<endl;
		cin  >> weight >> vertex_u >> vertex_v;
		GraphEdge newnode(weight, vertex_u, vertex_v);
		memcpy(&g_edg[i], &newnode, sizeof(struct GraphEdge));
	}

	cout << "\n\nEnter mode number" <<endl;
	cin >> mode;
	/*** Based on mode input, appropriate functions are plugged in ***/
	switch (mode)
	{
	case 1:
		init_vertex_set = init_name_array;
		find_vertex = find_vertex_name;
		union_vertices = union_vertices_name;
		break;
	case 2:
		init_vertex_set = init_parent_array;
		find_vertex = find_vertex_parent;
		union_vertices = union_vertices_parent;
		break;
	case 3:
		init_vertex_set = init_parent_array;
		find_vertex = find_vertex_parent_path_compress;
		union_vertices = union_vertices_parent;
		break;
	default:
		break;
	}

	/*** The krushkal procedure***/
	/*** init vertex partition sets ***/
	init_vertex_set(n_vert);
	/*** sort graaph edges based on increasing weight ***/
	sort_graph_edges(n_edges);
	cout << "\nThe sorted edges are:" << endl;
        cout << "<weight> <index of vertex u> <index of vertex v>" << endl;
        for (i = 0; i < n_edges; i++) {
                cout << g_edg[i].weight <<" " << g_edg[i].vertex_u <<" "<< g_edg[i].vertex_v <<endl;
        }

	/*** keep building the MST set ***/
	for (i = 0; i < n_edges; i++)
	{
		int x = find_vertex(g_edg[i].vertex_u);
		int y = find_vertex(g_edg[i].vertex_v);
		if (x != y)
		{
			mst_edg[j] = g_edg[i];
			union_vertices(x, y, n_vert);
			j++;
		}
	}
	n_mst_edges = j;

	/*** Print the MST edges ***/
	cout<<"\nMST is: " <<endl;
	for (i = 0; i < n_mst_edges; i++) {
                cout << mst_edg[i].weight <<" " << mst_edg[i].vertex_u <<" "<< mst_edg[i].vertex_v <<endl;
        }

	return 0;
}

