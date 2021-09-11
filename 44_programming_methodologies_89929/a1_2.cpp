#include <iostream>
#include <string>

using namespace std;

void initializeArrays(string names[], int scores[], int size);
void sortData(string names[], int scores[], int size);
void displayData(const string names[], const int scores[], int size);

int main() 
{
    
    int numOfPlayers;
    cout << "How many scores will you enter?: ";
    cin >> numOfPlayers;
    
    string* names = new string[numOfPlayers];
    int* scores = new int[numOfPlayers];
    
    initializeArrays(names, scores, numOfPlayers);
    sortData(names, scores, numOfPlayers);
    displayData(names, scores, numOfPlayers);
    
}
    
// Allows you to initialize an array of names and array of scores of a given size
void initializeArrays(string names[], int scores[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        cout << "Enter the name for score #" << i + 1 << ": ";
        cin >> names[i];
        cout << "Enter the score for score #" << i + 1 << ": ";
        cin >> scores[i];
    }
}
// Sorts data in two parallel arrays based on the integer array using bubblesort
void sortData(string names[], int scores[], int size) 
{
    int tempscore;string tempname;
    for (int j = 0; j < size - 1; j++) 
    {
        for (int i = 0; i < size; i++) 
        {
            if (scores[i] < scores[i + 1]) 
            {
                tempscore = scores[i];
                scores[i] = scores[i + 1];
                scores[i + 1] = tempscore;
                tempname = names[i];names[i] = names[i + 1];
                names[i + 1] = tempname;
            }
        }
    }
}

// Prints the contents of the name and scores arrays to the console
void displayData(const string names[], const int scores[], int size) 
{
    cout << endl << "Top Scorers:" << endl;
    for (int i = 0; i < size; i++) 
    {
        cout << names[i] << ": " << scores[i] << endl;
    }
}