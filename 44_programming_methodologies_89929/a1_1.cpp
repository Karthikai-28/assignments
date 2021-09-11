#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct highscore {
    int score;
    char name[24];
};

void readData(vector<highscore>& scores);
void sortData(vector<highscore>& scores);
void displayData(const vector<highscore>& scores);


int main() {

    int vectorSize;
    cout << "How many scores will you enter?: ";
    cin >> vectorSize;

    vector<highscore> scores(vectorSize);

    readData(scores);
    sortData(scores);
    displayData(scores);
}



void readData(vector<highscore>& scores) 
{
    for (vector<highscore>::iterator i = scores.begin(); 
    i != scores.end(); i++) 
    {
        cout << "Enter the name this entry: ";
        cin >> i->name;
        cout << "Enter the score this entry: ";
        cin >> i->score;
    }
    cout << endl;

}
void sortData(vector<highscore>& scores) {
    
    highscore tempscore;

    for(vector<highscore>::iterator j = scores.begin(); 
    j != scores.end()-1; j++) 
    {
        for(vector<highscore>::iterator i = scores.begin(); i != scores.end(); 
        i++) 
        {
            
            if (i->score < (i+1)->score) 
            {
                
                tempscore = *i;
                *i = *(i+1);
                *(i+1) = tempscore;

            }
        }
    }
}

void displayData(const vector<highscore>& scores) 
{
    cout << "Top Scorers:" << endl;
    for(vector<highscore>::const_iterator i = scores.begin(); 
    i != scores.end(); i++) 
    {
        cout << i->name << ": " << i->score << endl;
    }
}