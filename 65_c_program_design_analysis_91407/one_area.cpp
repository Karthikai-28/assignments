#include <bits/stdc++.h>
using namespace std;
//calculating the coordinates of smallest rectangle
void print_rectangle(int X[], int Y[], int n){
   //finding minimum and maximum points
   int Xmax = *max_element(X, X + n);
   int Xmin = *min_element(X, X + n);
   int Ymax = *max_element(Y, Y + n);
   int Ymin = *min_element(Y, Y + n);
   cout << "{" << Xmin << ", " << Ymin << "}" << endl;
   cout << "{" << Xmin << ", " << Ymax << "}" << endl;
   cout << "{" << Xmax << ", " << Ymax << "}" << endl;
   cout << "{" << Xmax << ", " << Ymin << "}" << endl;
}
int main(){
    int x_values;
    int y_values;
   cin >> x_values;
   cout << "The x";
   cin >> y_values;
   int X[] = {x_values};
   int Y[] = {y_values};
   int n = sizeof(X) / sizeof(X[0]);
   print_rectangle(X, Y, n);
   return 0;
} 