#ifndef ADDRESS_TYPE
#define ADDRESS_TYPE

using namespace std;

class addressType

{
private:
//Data member to store street
	string streetAddress;
//Data member to store city
	string city;
//Data member to store state
	string state;
//Data member to store pin
	string zipcode;
public:

//a custome method 
void print(){
	cout<<"\n ----- ADDRESS ----- \n";
	cout<<" Street: "<<streetAddress;
	cout<<"\t City: "<<city;
	cout<<"\t State: "<<state;
	cout<<"\t Zipcode: "<<zipcode;
}

//Default constructor
	addressType(){
		streetAddress = city = state = zipcode = "";
	}

//Default deconstructor
	~addressType(){};
	
//Parameterized constructor
addressType(string sa, string c, string st, string z){
	streetAddress = sa;
	city = c;
	state = st;
	zipcode = z;
}


//accessors and mutators

void setStreetAddress(string sa){
		streetAddress = sa;
	}
	
string getStreetAddress(){
	return streetAddress;
}

void setCity(string c){
	city = c;
}


string getCity(){
	return city;
}

void setState(string sa){
	state = sa;
}

string getState(){
	return state;
}

void setZipcode(string z){
	zipcode = z;
}

string getZipcode(){
	return zipcode;
}

};//End of the class


#endif