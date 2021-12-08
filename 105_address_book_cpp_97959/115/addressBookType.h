
#ifndef ADDRESS_BOOK_TYPE
#define ADDRESS_BOOK_TYPE


#include <iostream>
#include <string>
#include <fstream>
#include "extPersonType.h"
#include "dateType.h"

using namespace std;

//Class addressBookType definition
class addressBookType {
	private:
//Declares an array of objects of extPersonType class of 500
		extPersonType ept[500];
//To store number of records
		int numberOfRecord;
	public:

//Function to return number of records
int getNumberOfRecord(){
	
return numberOfRecord;

}

//---------Prototype of the functions-----

void readFile(string);
void displayFile();
void sortLastName();
void searchLastName(string, int);
void getAddressByMonth(int);
void betweenTwo(string name1,string name2);
void duplicateType(string);
void saveData();



};


//-------------Function to display duplicate person status------
void addressBookType::duplicateType(string type){

//Loops till number of records
for(int x{0}; x < getNumberOfRecord(); x++)
{
//Checks if current person status is equal to the person status given as parameter then display the person information
if(ept[x].getPersonStatus().compare(type) == 0){
	
	cout<<"\n\n\t\t\t ******************* Person Information ****************";
	ept[x].personType::print();
	ept[x].address.print();
	ept[x].dateOfBirth.print();
	ept[x].print();
		}
	}
}

//------------ Contacts with the same month of birth -------------|

void addressBookType::getAddressByMonth(int monthNumber)
{

//Loops till number of records
for(int x {0}; x < getNumberOfRecord(); x++){
//Checks if the current month is equal to previous month then display the person information
	if(ept[x].dateOfBirth.getMonth() == monthNumber)
		
{
	
	cout<<"\n\n\t\t\t ******************* Person Information ****************";
	ept[x].personType::print();
	cout << "\n";
	ept[x].address.print();
	ept[x].dateOfBirth.print();
	ept[x].print();
		}
	}
}

//------------------Function to search a person last name and display person information--------
void addressBookType::searchLastName(string name, int no){

	int flag = 0;
	//Loops till number of records
for(int x{0}; x < getNumberOfRecord(); x++){
//Checks if the current person last name is equal to person name in the parameter
	if(ept[x].personType::getLastName() == name)
		
{
//Check if no is 2 then display complete person information

if(no == 2){
	
	cout<<"\n\n\t\t\t ******************* Person Information ****************\n";
	ept[x].personType::print();
	ept[x].address.print();
	ept[x].dateOfBirth.print();
	ept[x].print();
	cout<<"\n\n\t\t\t *******************THE END OF THE RECORD****************\n";
}
//If no is 3 display only address phone number and date of birth
else{
	cout<<"\n\n\t\t\t ******************* Person address phone number and date of birth ****************\n";
	ept[x].address.print();
	ept[x].dateOfBirth.print();
	ept[x].print();
	cout<<"\n\n\t\t\t *******************THE END OF THE RECORD****************\n";
}

flag = 1;
}
}

if(flag != 1)
cout<<"\n Record for "<< name<<" not found.";
}//End of function


//-------- To find people between two last names----------

void addressBookType::betweenTwo(string name1, string name2){
	
	
	int first_index;
	int second_index;
	
	bool first_found = false;
	bool second_found = false;
	
	
	for(int x {0}; x < getNumberOfRecord(); x++){
		

	if(ept[x].personType::getLastName() == name1){
		first_index = x;
		first_found = true;
	}
} 



for(int x {0}; x < getNumberOfRecord(); x++){
		
	if(ept[x].personType::getLastName() == name2){
		second_index = x;
		second_found = true;
	}
}

//cout << "Firest person index: " << first_index << endl;
//cout << "Second person index: " << second_index << endl;
	
	
if(first_found && second_found){
	
	cout<<"\n\n\t\t\t *** The contacts between "; 
    cout << ept[first_index].personType::getLastName() << " and " << ept[second_index].personType::getLastName() << " are ***\n\n";
	
for(int x {first_index + 1}; x < second_index; x++){
	ept[x].personType::print();
	ept[x].address.print();
	ept[x].dateOfBirth.print();
	ept[x].print();
	cout << "\n\n*********************" << endl;

}
}else{
	
	cout << "Could not find anyone" << endl;
}
};




//-------- read data from the file and store it to the corresponding data member ----------
void addressBookType::readFile(string fileName){
	
int co = 0;
string f, l;
int d;

//Creates an object of ifstream
ifstream rFile;

//Opens the file Address.txt for reading
rFile.open(fileName.c_str());


//in case if the program is unable to the file it shows this message 

if(!rFile){
	cout<<"\n ERROR: Unable to open the file "<< fileName <<" for reading.";
	exit(0);
}

//Loops till end of file
while(!rFile.eof()){
// Checks if current record counter co is equals to maximum record then display
// error message and come out of the loop

if(co == 500){
	cout<<"\n Reached maximum limit. Cannot add more records.";
	break;
}

// Read first and last name
	rFile>>f;
	rFile>>l;
	ept[co].setName(f, l);
// Reads date of birth
//so since in exercise 11-2 we had the following data format: Date #: month-day-year
// I assume that the first number represents month, second - day ...
	rFile>>d;
	ept[co].dateOfBirth.setMonth(d);
	rFile>> d;
	ept[co].dateOfBirth.setDay(d);
	rFile>>d;
	ept[co].dateOfBirth.setYear(d);
	rFile.ignore();
// Reads address
	getline(rFile, l);
	ept[co].address.setStreetAddress(l);
// Reads city
	getline(rFile, l);
	ept[co].address.setCity(l);
// Reads state
	getline(rFile, l);
	ept[co].address.setState(l);
// Reads zip code
	rFile>>l;
	ept[co].address.setZipcode(l);
// Reads phone number
	rFile>>l;
	ept[co].setPhoneNumber(l);
// Reads person status
	rFile>>l;
	ept[co].setPersonStatus(l);
//Increase the counter by one
	co++;
}//End of while
//Close file
	rFile.close();
//Assigns the counter value to the number of records
	numberOfRecord = co;
}//End of function


//------Function to write data to file--------
void addressBookType::saveData(){


	ofstream wFile;
	
//Opens the file AddressNew.txt for writing

	wFile.open("AddressNew.txt");

//Loops till end of the record
for(int co = 0; co < numberOfRecord; co++){
// Writes data to file
	wFile<<ept[co].getFirstName()<<" "<<ept[co].getLastName()<<endl;
	wFile<<ept[co].dateOfBirth.getDate()<<" "<<ept[co].dateOfBirth.getMonth()<<" "
	<<ept[co].dateOfBirth.getYear()<<endl;
	wFile<<ept[co].address.getStreetAddress()<<endl;
	wFile<<ept[co].address.getCity()<<endl;
	wFile<<ept[co].address.getState()<<endl;
	wFile<<ept[co].address.getZipcode()<<endl;
	wFile<<ept[co].getPhoneNumber()<<endl;
	
	
	
// Checks if it is last record then do not write new line character after it
if(co == numberOfRecord - 1)
wFile<<ept[co].getPersonStatus();
// Otherwise it is not last record write new line character after it
else
wFile<<ept[co].getPersonStatus()<<endl;
}//End of while
cout<<"\n\n File Saved Successfully.";
//Close file
wFile.close();
}//End of function


//--------Function to display person information------
	void addressBookType::displayFile(){
//Loops till end of the record
for(int x = 0; x < numberOfRecord; x++){
	
	cout<<"\n\n\t\t\t ******************* Person "<<(x + 1)<<" Information ****************";
	ept[x].personType::print();
	ept[x].address.print();
	ept[x].dateOfBirth.print();
	ept[x].print();

}//End of for
}//End of function

//Function to sort the person information based on last name
void addressBookType::sortLastName(){
int x, y;
//Creates an temporary object
extPersonType temp;
//Loops till end of the record
for(x = 0; x < getNumberOfRecord(); x++){
	
//Loops till end of the record minus one and x value
for(y = 0; y < getNumberOfRecord() - x - 1; y++){
//Checks if the current person last name is greater than next person last name
if(ept[y].personType::getLastName() > ept[y + 1].personType::getLastName()){
//Swapping process
	temp = ept[y];
	ept[y] = ept[y + 1];
	ept[y + 1] = temp;
}//End of if
}//End of inner for
}//End of outer for
}//End of function


#endif