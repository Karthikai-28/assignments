#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

const int COLS = 2;

double calcArea(int xycoords[][COLS], int num_side, double area);
double calcPerimeter(int xycoords[][COLS], int num_side, double perimeter);
void displayGraph(int copyarray[][COLS], int num_side);

int main(){
    int num_side;

    cout << "This program will return the area and perimeter of any non-self-intersecting polygon\n";

    do{
        cout << "Enter the number of sides your polygon will have: "; cin >> num_side;

        if(num_side <= 2) cout << "Error, size of polygon is less than 2!" << endl;
    } while(num_side <= 2);

    int xycoords[(num_side + 1)][COLS];
    int copyarray[num_side][COLS];

    for (int i = 0; i < num_side; i++){
        system("clear");
        cout << "Please enter " << num_side << " pairs of space-seperated coordinates: " << "\n("; cin >> xycoords[i][0]; system("clear");

        cout << "Please enter " << num_side << " pairs of space-seperated coordinates: " << "\n(" << xycoords[i][0] << ","; cin >> xycoords[i][1]; system("clear");

        cout << "Please enter " << num_side << " pairs of space-seperated coordinates: " << "\n(" << xycoords[i][0] << "," << xycoords[i][1] << ")\n";
        system("sleep 0.5"); system("clear");

        copyarray[i][0] = xycoords[i][0];
        copyarray[i][1] = xycoords[i][1];
    }

    cout << "Calculating perimeter and area..\n"; system("sleep 1.5");
    cout << "Gathering results...\n"; system("sleep 2; clear");

    xycoords[num_side][0] = xycoords[0][0];
    xycoords[num_side][1] = xycoords[0][1];

    double area = calcArea(xycoords, num_side, 0);
    double perimeter = calcPerimeter(xycoords, num_side, 0);

    cout << "Your coordinates are: ";
    for(int x = 0; x < num_side; x++) cout << " (" << copyarray[x][0] << "," << copyarray[x][1] << ")";

    cout << endl << "Your area is: " << area << endl << "Your perimeter is: " << perimeter << endl;

    return 0;
}

double calcArea(int xycoords[][COLS], int num_side, double area){
    for(int i = 0; i < num_side; i++){
		area += (((xycoords[i][0] * xycoords[i + 1][1]) - (xycoords[i][1] * xycoords[i + 1][0])));
	}

    return abs(area / 2);
}

double calcPerimeter(int xycoords[][COLS], int num_side, double perimeter){
    for(int i = 0; i < num_side; i++) perimeter += sqrt(pow((xycoords[i + 1][0] - xycoords[i][0]), 2) + pow((xycoords[i + 1][1] - xycoords[i][1]), 2));

    return perimeter;
}