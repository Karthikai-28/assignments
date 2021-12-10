#include <iostream>
#include <fstream>
#include <string>
#include "addressBookType.h"

using namespace std;

void addressBookType::print() const
{
	for (int i = 0; i < length; i++)
		list[i].printInfo();
}

void addressBookType::printNameInTheMonth(int month)
{
	for (int i = 0; i < length; i++)
	{
		if (list[i].isMonth(month))
		{
			list[i].print();
			cout << endl;
		}
	}
}

void addressBookType::printInfoOf(string lName) 
{
	int i = search(lName);

	if (i != -1)
		list[i].printInfo();
	else
		cout << lName << " is not in address book." << endl;
}

void addressBookType::printNamesWithStatus(string status)
{
	for (int i = 0; i < length; i++)
		if (list[i].isStatus(status))
		{
			list[i].print();
			cout << endl;
		}
}

void addressBookType::printAt(int i)
{
	if (i < length)
		list[i].printInfo();
	else
		cout << "No such person" << endl;

}

void addressBookType::printNamesBetweenLastNames(string last1, string last2)
{
	string lName;

	for (int i = 0; i < length; i++)
	{
		list[i].getLastName(lName);
		if (last1 <= lName && lName <= last2)
		{
			list[i].print();
			cout << endl;
		}
	}
}

int addressBookType::search(string lName)
{
	bool found = false;
	int i = 0;

	for (i = 0; i < length; i++)
		if (list[i].isLastName(lName))
		{
			found = true;
			break;
		}

	if (found)
		return i;
	else 
		return -1;
}


addressBookType::addressBookType()
{
	length = 0;
}

void addressBookType::saveData(ofstream& outFile)
{
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


	for (int i = 0; i < length; i++)
	{
		list[i].getName(first,last);
		list[i].getDOB(month, day, year);
		list[i].getAddress(street,city,state,zip);
		list[i].getPhoneNumber(phone);
		list[i].getStatus(pStatus);

		outFile << first << " " << last << endl;
		outFile << month << " " << day << " " << year << endl;
		outFile << street << endl << city << endl << state << endl << zip << endl;
		outFile << phone << endl << pStatus << endl;
	}
}