#include <iostream>
#include <string>
#include "addressBookType.h"
#include "addressType.h"
#include "dateType.h"
#include "extPersonType.h"
#include "personType.h"

using namespace std;

int menu(){
	
int input;
						 //Displays menu
	cout<<"\n\n\n ********************* My Address Book ********************* \n\n\n";
	cout<<" 1. Sort the address book by last name. \n";
	cout<<" 2. Search for a person by last name. \n";
	cout<<" 3. Print the address phone number and date of birth of a given person (if exist). \n";
	cout<<" 4. Print names of people whose birthdays are in a given month. \n";
	cout<<" 5. Print the names of all the people between two last names. \n";
	cout<<" 6. Depending on request, print all family members, friends or business associates. \n";
	cout<<" 7. Save data.\n";
	cout<<" 9. Exit.";
			//Accept user choice
	cout<<"\n\t\t What is your choice? ";
	cin>> input;
	cout<<"---------------------------------------------------------------\n\n\n ";


//Return user choice
return input;
}//End of function

//Main function definition
int main() {
	
	int input;
	int month;
	string data;
	string fileName;
	string lName1 {""};
			string lName2 {""};
//Creates an object of addressBookType class

addressBookType test;

cout<<"\n Enter the filename: ";

cin >> fileName;
//Read the file contents
test.readFile(fileName);

//Loops till user choice is not 9
do{
//Displays menu and stores the user choice
input = menu();
	switch(input){
		case 1:
			test.sortLastName();
			test.displayFile();
			break;
		case 2:
			cout<<"\n Enter the last name to search record: ";
			cin>>data;
			test.searchLastName(data, 2);
			break;
		case 3:
			cout<<"\n Enter the last name to print address phone number and date of birth: ";
			cin>>data;
			test.searchLastName(data, 3);
			break;
		case 4:
			cout<<"\n Enter the month number print address phone number and date of birth: ";
			cin>> month;
			test.getAddressByMonth(month);
			break;
		case 5:
			cout <<"\n Enter two last names to display contacts between them: ";
					
		    cin >> lName1 >> lName2;
			test.betweenTwo(lName1, lName2);
			break;
		case 6:
			cout<<"\n Enter the person type (Family / Friends / Business): ";
			cin>>data;
			test.duplicateType(data);
			break;
		case 7:
			test.saveData();
			break;
		case 9:
			cout<<"\n\t\t Program Finished.";
			exit(0);
		default:
			cout<<"\n Invalid choice!";
		}
		
	}
		
		while(9);//End of do - while
		
		
}
