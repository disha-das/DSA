/*------------------ 
System Headers 
----------------- */
#include<iostream>
//#include<conio.h>
#include<stdlib.h>
#include<stdio.h>


using namespace std;

/*------------------------------------------------------- 
Macros:: kindly specify the number of edges and vertices 
-------------------------------------------------------- */

#define NUM_EDGES 6
#define NUM_VERTICES 6

/*------------------------------------------------------- 
Custom Variables and Structures Used 
-------------------------------------------------------- */

struct edge
{
       int start_vertex;
       int end_vertex;
       int weight;
};

struct vertices
{
	int number;
	int min_dist;
	int pred;
	int processed;
};

vertices* brr[NUM_VERTICES];
edge* arr[NUM_EDGES];

/*------------------------------------------------------- 
Custom Functions Used 
-------------------------------------------------------- */
void Dijkstra();
void Init_Shortest_Path();


/*------------------------------------------------------- 
main(): The Graph values are read from the specified file
Format of the file should be 
<char, source vertex, end vertex , weight>
Then Vertex 1 is taken as source vertex and the shortest 
path to all other vertices as well as there predecessors 
are displayed
-------------------------------------------------------- */

int main()
{
	FILE * fptr;
	fptr= fopen("graph_ip.txt", "r+");
	if(fptr == NULL)
	{
		cout<<"Cannot access inputfile\n"<<endl;
		return -1;
	}
	int i=0 , x,y,z, size;
	char a, str[60];
	arr[i]=(edge*)calloc(sizeof(struct edge),sizeof(int));

	while(fscanf(fptr, " %c %d %d %d\n", &a, &x, &y , &z)!= EOF)
	{
	arr[i]->start_vertex = x;
	arr[i]->end_vertex=y;
	arr[i]->weight=z;
	i++;
	arr[i]=(edge*)calloc(sizeof(struct edge),sizeof(int));
	}
	size = i;
	cout<< "Your graph is :: "<<endl;
    for(i =0 ; i<size ; i++)
    { 
		cout<< "Edge" << i+1 <<endl;
      	cout<<"Start vertex: " << arr[i]->start_vertex <<endl;
      	cout<<"End vertex: " <<arr[i]->end_vertex <<endl ;
      	cout<<"Weight: " << arr[i]->weight<< endl;
    }
    
   
    Dijkstra();
    
    cout<< "\n\nYour shortest distances are :: "<<endl;
    for(i =1 ; i<= NUM_VERTICES ; i++)
    {   if(brr[i]->pred == -1 )
		{
			cout<< "Vertex :: " << i << " is not connected to source vertex 1"<<endl;
		}
		else
		{    
			cout<<"Vertex :: "<<brr[i]->number<<endl;
	    	cout<<"Shotest Path from Vertex 1 is of length :: "<<brr[i]->min_dist<<endl;
	    	cout<<"Predecessor Vertex :: " << brr[i]->pred<<endl;
		}
    }
    
    for(i =1 ; i<= NUM_VERTICES ; i++)
    {
		free(brr[i]);
	}
	
	for(i =0 ; i<size ; i++)
    { 
    	free(arr[i]);
	}
	fclose(fptr);
	
	return 0;
	

}

/*------------------------------------------------------- 
Init_Shortest_Path(): The vertices array is initialized. 
Min distance for every vertex = greatest integer, min dist
of the source vertex 1 is 0. Predecessor for source vertex 1 
is 0 and predecessor for all other vertices =-1
-------------------------------------------------------- */

void Init_Shortest_Path()
{	
	brr[1]=(vertices*)calloc(sizeof(struct vertices),sizeof(int));
	brr[1]->number = 1;
	brr[1]->min_dist = 0;
	brr[1]->pred = 1;
	brr[1]->processed =1;
	
	for (int i=2; i<=NUM_VERTICES ; i++)
	{
		brr[i]=(vertices*)calloc(sizeof(struct vertices),sizeof(int));
		brr[i]->number = i;
		brr[i]->min_dist = 65536;
		brr[i]->pred = -1;
		brr[i]->processed =0;
	}
}

/*------------------------------------------------------- 
Dijkstra(): The Vertex 1 is taken as source vertex and the 
shortest path to all other vertices as well as there
predecessors are calculated
-------------------------------------------------------- */

void Dijkstra()
{
	 Init_Shortest_Path(); 
	 int min = 65536, temp_dist =0, adj_v, count =1, position = 0;
	for ( int j = 0 ; j< NUM_EDGES; j++)
	{
		if(arr[j]->start_vertex == 1)
		{
		int temp = arr[j]->end_vertex;
		brr[temp]->min_dist = arr[j]->weight;
		brr[temp]->pred = 1;
		}
	}
	 
	while(count<NUM_VERTICES ) 
	{
		min = 65537;
		count++;
		position =0;
		for ( int i = 1; i<= NUM_VERTICES ; i++)
		{	
			if(( brr[i]->min_dist< min) && (brr[i]->processed == 0))
			{
				min = brr[i]->min_dist;	
				position =i; 
			}
		}
		brr[position]->processed = 1; 
		for ( int j = 0 ; j< NUM_EDGES; j++)
		{
			if(arr[j]->start_vertex == brr[position]->number)
			{	
				adj_v= arr[j]->end_vertex;
				temp_dist = brr[position]->min_dist + arr[j]->weight;
				if(temp_dist <= brr[adj_v]->min_dist)
				{	
					brr[adj_v]->min_dist = temp_dist;
					brr[adj_v]->pred = brr[position]->number;	
				} 
			
			}
		}
	}
		
}
