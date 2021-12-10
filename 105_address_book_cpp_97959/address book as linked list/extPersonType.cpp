#include <iostream>
#include <string>
#include "extPersonType.h"

void extPersonType::printAddress() const
{
	personType::print();
	cout << endl;

	address.print();
}

void extPersonType::printInfo() const
{
	personType::print();
	cout << endl;

	cout << "Date of Birth: ";
	dob.printDate();
	cout << endl;

	cout << "Phone Number: " << phoneNumber << endl;
	cout << "Person Type: " << personStatus << endl;
	address.print();
	cout << endl;
}

void extPersonType::setInfo(string fName, string lName,
							int month, int day, int year,
							string street, string c, string s, 
							string z, string phone, string pStatus)
{
	personType::setName(fName,lName);
	dob.setDate(month, day, year);
	address.setAddress(street,c,s,z);
	phoneNumber = phone;
	personStatus = pStatus;
}

void extPersonType::setInfo(string fName, string lName,
						dateType d, addressType ad, 
						string phone, string pStatus)
{
	personType::setName(fName,lName);
	dob = d;
	address = ad;
	phoneNumber = phone;
	personStatus = pStatus;
}

bool extPersonType::isLastName(string lName)
{
	string first;
	string last;

	personType::getName(first,last);

	return (last == lName);
}

void extPersonType::getLastName(string& lName)
{
	string first;
	string last;

	personType::getName(first,last);

	lName = last;
}

void extPersonType::getAddress(string& sAddress, string& c, 
					string& s, string& z)
{
	address.getAddress(sAddress,c,s,z);
}

void extPersonType::getPhoneNumber(string& phone)
{
	phone = phoneNumber;
}
	
void extPersonType::getStatus(string& status)
{
	status = personStatus;
}

bool extPersonType::isStatus(string status)
{
	return (status == personStatus);
}

bool extPersonType::isDOB(int month, int day, int year)
{
	int m;
	int d;
	int y;

	dob.getDate(m, d, y);

	return (m == month && d == day && y == year);
}

void extPersonType::getDOB(int& month, int& day, int& year)
{
	dob.getDate(month, day, year);
}

bool extPersonType::isMonth(int month)
{
	int m;
	int d;
	int y;

	dob.getDate(m, d, y);

	return (m == month);
}

extPersonType::extPersonType(string fName, string lName,
							int month, int day, int year,
							string street, string c, string s, 
							string z, string phone, string pStatus)
{
	personType::setName(fName,lName);
	dob.setDate(month, day, year);
	address.setAddress(street, c, s, z);
	phoneNumber = phone;
	personStatus = pStatus;
}

