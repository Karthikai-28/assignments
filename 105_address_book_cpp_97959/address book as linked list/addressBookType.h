#ifndef H_addressBookType
#define H_addressBookType

#include <string>
#include <fstream>
#include "extPersonType.h"
#include "arrayListType.h"

using namespace std;

class addressBookType: public arrayListType<extPersonType>
{
public:
	void print() const;

	void printNameInTheMonth(int month);
	void printInfoOf(string lName);
	void printNamesWithStatus(string status);
	void printAt(int i);

	void printNamesBetweenLastNames(string last1, string last2);

	int search(string lName);

	void saveData(ofstream&);

	addressBookType();
};

#endif
