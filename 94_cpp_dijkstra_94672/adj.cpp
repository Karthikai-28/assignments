#include<climits>
#include <stdio.h>
#include<iostream>
using namespace std;
#define V 5  //Defines total number of vertices in the graph
#define INFINITY 999
int N, M;

int miniDist(int distance[], bool Tset[]) // finding minimum distance
{
    int minimum=INT_MAX,ind;
              
    for(int k=0;k<6;k++) 
    {
        if(Tset[k]==false && distance[k]<=minimum)      
        {
            minimum=distance[k];
            ind=k;
        }
    }
    return ind;
}

void DijkstraAlgo(int graph[6][6],int src) // adjacency matrix 
{
    int distance[6]; // // array to calculate the minimum distance for each node                             
    bool Tset[6];// boolean array to mark visited and unvisited for each node
    
     
    for(int k = 0; k<6; k++)
    {
        distance[k] = INT_MAX;
        Tset[k] = false;    
    }
    
    distance[src] = 0;   // Source vertex distance is set 0               
    
    for(int k = 0; k<6; k++)                           
    {
        int m=miniDist(distance,Tset); 
        Tset[m]=true;
        for(int k = 0; k<6; k++)                  
        {
            // updating the distance of neighbouring vertex
            if(!Tset[k] && graph[m][k] && distance[m]!=INT_MAX && distance[m]+graph[m][k]<distance[k])
                distance[k]=distance[m]+graph[m][k];
        }
    }
    cout<<"Vertex\t\tDistance from source vertex"<<endl;
    for(int k = 0; k<6; k++)                      
    { 
        char str=65+k; 
        cout<<str<<"\t\t\t"<<distance[k]<<endl;
    }
}

void createAdjMatrix(int Adj[][N + 1],
                     int arr[][2])
{
  
    // Initialise all value to this
    // Adjacency list to zero
    for (int i = 0; i < N + 1; i++) {
  
        for (int j = 0; j < N + 1; j++) {
            Adj[i][j] = 0;
        }
    }
  
    // Traverse the array of Edges
    for (int i = 0; i < M; i++) {
  
        // Find X and Y of Edges
        int x = arr[i][0];
        int y = arr[i][1];
  
        // Update value to 1
        Adj[x][y] = 1;
        Adj[y][x] = 1;
    }
}

void printAdjMatrix(int Adj[][N + 1])
{
  
    // Traverse the Adj[][]
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
  
            // Print the value at Adj[i][j]
            printf("%d ", Adj[i][j]);
        }
        printf("\n");
    }
}

int main()
{
	int i,j, s;
	// cout<<"\n Enter the cost matrix weights";
    int cost[6][6]={
        {0, 1, 2, 0, 0, 0},
        {1, 0, 0, 5, 1, 0},
        {2, 0, 0, 2, 3, 0},
        {0, 5, 2, 0, 2, 2},
        {0, 1, 3, 2, 0, 1},
        {0, 0, 0, 2, 1, 0}};

     N = 5;
  
    // Given Edges
    int arr[][2]
        = { { 1, 2 }, { 2, 3 }, 
            { 4, 5 }, { 1, 5 } };
  
    // Number of Edges
    M = sizeof(arr) / sizeof(arr[0]);
  
    // For Adjacency Matrix
    int Adj[N + 1][N + 1];
  
    // Function call to create
    // Adjacency Matrix
    createAdjMatrix(Adj, arr);
  
    // Print Adjacency Matrix
    printAdjMatrix(Adj);

     cout<<cost[6][6];
	    for(i=1;i<=V;i++)      //Indexing ranges from 1 to n
          for(j=1;j<=V;j++)
          {
			//Absence of edge between vertices i and j is represented by INFINITY
             if(cost[i][j]==0)     
               cost[i][j]=INFINITY;    
           }
// cout<<"\n Enter the Source Vertex"; 
// cin>>s;

	DijkstraAlgo(cost,0);
	return 0;                       	
}

	