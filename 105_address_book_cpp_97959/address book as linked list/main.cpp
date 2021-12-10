// Main Program
// defined loadAddressBook, saveData, and showMenu function
// 

#include <iostream> //for cin, cout, etc
#include <fstream> // for files
#include <string> // for string type
#include "addressBookType.h" // headers, declarations for addressBookType class

using namespace std;

void loadAddressBook(addressBookType& addressBook); // loads the address book
void saveData(addressBookType& addressBook); // saves the data into a file specified

void showMenu(); // displays the menu in the console.

int main()
{
	addressBookType addressBook;
	string str; // for prompt that takes 1 input
	string str1; // for prompts that takes 2 inputs
	string str2; // for prompt that takes 2 inputs
	int choice; // for menu selection shown using showMenu
	int locate; // index location found via addressBook.search(str)
	int month; // prompt for month 

	loadAddressBook(addressBook);

	showMenu();

	cin >> choice;
	while (choice != 8)//if 8 then exit
	{
		switch (choice)
		{
		case 1: 
            cout << "Enter the last name of the person: ";
            cin >> str;
            cout << endl;

            locate = addressBook.search(str);

            if (locate != -1)
                cout << str << " is in the address book" << endl;
            else
                cout << str << " is not in the address book" << endl;
            break;
		case 2: 
            cout << "Enter the last name of the person: ";
            cin >> str;
            cout << endl;

            locate = addressBook.search(str);

            if (locate != -1)
                addressBook.printAt(locate);
            else
                cout << str << " is not in the address book" << endl;
            break;
		case 3: 
            cout << "Enter the month number: ";
            cin >> month;
            cout << endl;

            addressBook.printNameInTheMonth(month);
            break;
		case 4: 
			cout << "Enter person type Family, Friend, Business: ";
            cin >> str;
            cout << endl;

            addressBook.printNamesWithStatus(str);
            break;
           

            

		case 5: 
			cout << "Enter starting last name: ";
	        cin >> str1;
            cout << endl;
            cout << "Enter ending last name: ";
            cin >> str2;
            cout << endl;
            
			addressBook.printNamesBetweenLastNames(str1, str2);
            break;
		case 6: 
            addressBook.print();
            break;
		case 7: 
            saveData(addressBook);
            break;
		default: 
            cout << "Invalid choice" << endl;
		}

		showMenu();
		cin >> choice;
	}

	char response;

	cout << "Save data Yes (Y/y) No(N/n)?: ";
	cin >> response;
	cout << endl;
	if (response == 'y' || response == 'Y')
		saveData(addressBook);
		
	return 0;
}

void loadAddressBook(addressBookType& addressBook)
{
	ifstream infile;

	char filename[50];
	
	string first;
	string last;

	int month;
	int day;
	int year;

	string street;
	string city;
	string state;
	string zip;

	string phone;
	string pStatus;

	extPersonType temp;

	cout << "Enter file name: ";
	cin >> filename;
	cout << endl;

	infile.open(filename);
	if (!infile)
	{
		cout << "Input file does not exist. "
			 << "Program terminated!" << endl;
		return;
	}

	int i = 0;

	infile >> first >> last >> month >> day >> year;
	infile.ignore(100,'\n');
	getline(infile,street);
	getline(infile,city);
	getline(infile, state);
	infile >> zip >> phone >> pStatus;

	while (infile)
	{
		temp.setInfo(first,last,month,day,year,street,city,state,
					zip,phone,pStatus);

		addressBook.insertAt(i, temp);
		i++;

		infile >> first >> last >> month >> day >> year;	
		infile.ignore(100,'\n');
		getline(infile,street);
		getline(infile,city);
		getline(infile, state);
		infile >> zip >> phone >> pStatus;
	}
}

void saveData(addressBookType& addressBook)
{
	ofstream outfile;

	string filename;

	filename = "HW3Data.txt";
	outfile.open(filename);
	if (!outfile)
	{
		cout << "Input file does not exists. "
			 << "Program terminates!!!" << endl;
		return;
	}

	addressBook.saveData(outfile);
}

void showMenu()
{
	
	cout << "Choose from the following option:" << endl;
	cout << "1: Check if a person is in the address book" << endl;
	cout << "2: Search for a person by last name" << endl;
	cout << "3: Print the names of all the people whose birthdays are in a given month" << endl;
	cout << "4: Print the names of all the people having the same status" << endl;
	cout << "5: Print the names of all the people between two last names" << endl;
	cout << "6: Print the address book" << endl;
	cout << "7: Save data" << endl;
	cout << "8: Terminate the program" << endl;
}