#pragma once
#include <string>
using namespace std;
class PersonType
{
public:
	bool operator==(const PersonType& other);
	bool operator!=(const PersonType& other);

	string firstName() const;
	string lastName() const;
		
private:
	string first_name;
	string last_name;
};