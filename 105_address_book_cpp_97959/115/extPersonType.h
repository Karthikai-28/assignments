#ifndef EXT_PERSON_TYPE
#define EXT_PERSON_TYPE


#include "personType.h"
#include "addressType.h"
#include "dateType.h"

using namespace std;

//Class extPersonType derived from personType
class extPersonType : public personType {
	
private:
//Data member to store phone number and person status
	string phoneNumber;
	string personStatus;
	
public:


//Variables of addressType class and dateType class

	addressType address;
	dateType dateOfBirth;

//Function to print data
void print() const{
	cout<<"\n Phone Number: "<<phoneNumber;
	cout<<"\n Person Type: "<<personStatus;
}

//defoult constructor
extPersonType(){ }


//Parameterized constructor
extPersonType(addressType a, dateType d, string ph, string ps, string fi, string la):personType(fi, la){
	address = a;
	dateOfBirth = d;
	phoneNumber = ph;
	personStatus = ps;
}



//Accessors and Mutetors
void setPhoneNumber(string p){
	phoneNumber = p;
}

string getPhoneNumber(){
	return phoneNumber;
}

void setPersonStatus(string p){
	personStatus = p;
}

string getPersonStatus() {
	return personStatus;
	}


};//End of function


#endif