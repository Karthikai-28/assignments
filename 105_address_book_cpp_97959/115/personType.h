
#ifndef PERSON_TYPE
#define PERSON_TYPE

#include <iostream>
#include <string>


using namespace std;

//Class personType definition
class personType{
	
	public:
//Parameterized constructor
		personType(string first = " ", string last = " "){
		_firstName = first;
		_lastName = last;
		};//End of constructor

//deconstructor

	~personType(){};

//Function to print person name
	void print() const{
		cout<<"\n First Name: "<<_firstName<<"\n Last Name: "<< _lastName << endl;
	}//End of function

//Getter and setter methods
	void setName(string first, string last){
		_firstName = first;
		_lastName = last;
	}//End of function
	
string getFirstName( ) const {
	return _firstName;
}

string getLastName( ) const {
	
	return _lastName;
}

private:
//Data member to store first name and last name
	string _firstName;
	string _lastName;
	
};//End of class

#endif