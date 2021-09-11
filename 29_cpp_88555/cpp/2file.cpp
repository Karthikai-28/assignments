#include <iostream>
#include <fstream>
using namespace std;

struct student
{
    char name[50];
    int roll;
    float marks;
};

int main() 
{
    fstream my_file;
	my_file.open("details.txt", ios::out);
	if (!my_file) {
		cout << "File not created!";
	}
	else {
		cout << "File created successfully!";
	}
    student s;
    cout << "Enter information," << endl;
    cout << "Enter name: ";
    cin >> s.name;
    cout << "Enter roll number: ";
    cin >> s.roll;
    cout << "Enter marks: ";
    cin >> s.marks;

    cout << "\nDisplaying Information," << endl;
    cout << "Name: " << s.name << endl;
    my_file << "Name: " << s.name << '\n';
    cout << "Roll: " << s.roll << endl;
    my_file << "Roll: " << s.roll << '\n';
    cout << "Marks: " << s.marks << endl;
    my_file << "Marks: " << s.marks << '\n';
    return 0;
}
