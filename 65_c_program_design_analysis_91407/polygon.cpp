#include <iostream>
#include <cstdlib>
#include <unistd.h>
double findArea(double points[][2], long rows); 
using namespace std;

int main(){	
	double arrayOfVertices[][2] = { {3,4}, {5,11}, {12,8}, {9,5},{5,6}}; 

	cout<<"The Area of the given Polygon = "<<findArea(arrayOfVertices, sizeof(arrayOfVertices)/sizeof(*arrayOfVertices))<<endl;      
	return 0;
}

double findArea(double points[][2], long rows){
	cout<<"Calculating area... \n";
	usleep(3000000);
	double sum = 0, area = 0;
	for(long r=0; r<rows; r++){
		if(r == rows-1){
			sum += points[r][0]*points[0][1] - points[0][0]*points[r][1];
		}else {
			sum += points[r][0]*points[r+1][1] - points[r+1][0]*points[r][1];
		}
	}
	area = abs((long)sum)/2;
	return area;
}