#include<bits/stdc++.h>
using namespace std;

class Graph {
   private:
  bool** adjMatrix;
  int numVertices;

   public:
  // Initialize the matrix to zero
  Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new bool*[numVertices];
    for (int i = 0; i < numVertices; i++) {
      adjMatrix[i] = new bool[numVertices];
      for (int j = 0; j < numVertices; j++)
        adjMatrix[i][j] = false;
    }
  }

  // Add edges
  void addEdge(int i, int j) {
    adjMatrix[i][j] = true;
    adjMatrix[j][i] = true;
  }

  // Remove edges
  void removeEdge(int i, int j) {
    adjMatrix[i][j] = false;
    adjMatrix[j][i] = false;
  }

  // Print the martix
  void toString() {
    for (int i = 0; i < numVertices; i++) {
      cout << i << " : ";
      for (int j = 0; j < numVertices; j++)
        cout << adjMatrix[i][j] << " ";
      cout << "\n";
    }
  }

  ~Graph() {
    for (int i = 0; i < numVertices; i++)
      delete[] adjMatrix[i];
    delete[] adjMatrix;
  }
};

int main()
{
    Graph g(4);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);

    g.toString();
	int n = 9;
	
	int mat[9][9] = { { 100,4,100,100,100,100,100,8,100}, 
                      { 4,100,8,100,100,100,100,11,100}, 
                      {100,8,100,7,100,4,100,100,2}, 
                      {100,100,7,100,9,14,100,100,100}, 
                      {100,100,100,9,100,100,100,100,100}, 
                      {100,100,4,14,10,100,2,100,100}, 
                      {100,100,100,100,100,2,100,1,6}, 
                      {8,11,100,100,100,100,1,100,7}, 
                      {100,100,2,100,100,100,6,7,100}};
	
	int src = 0;
	int count = 1;
	
	int path[n];
	for(int i=0;i<n;i++)
		path[i] = mat[src][i];
	
	int visited[n] = {0};
	visited[src] = 1;
	
	while(count<n)
	{
		int minNode;
		int minVal = 100;
		
		for(int i=0;i<n;i++)
			if(visited[i] == 0 && path[i]<minVal)
			{
				minVal = path[i];
				minNode = i;
			}
		
		visited[minNode] = 1;
		
		for(int i=0;i<n;i++)
			if(visited[i] == 0)
				path[i] = min(path[i],minVal+mat[minNode][i]);
					
		count++;
	}
	
	path[src] = 0;
	for(int i=0;i<n;i++)
		cout<<src<<" -> "<<path[i]<<endl;
	
	return(0);
}