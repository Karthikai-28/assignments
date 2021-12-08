#pragma once
#include <vector>
#include "extPersonType.h"
#include "unorderedLinkedList.h"
class AddressBookType
{
public:
	bool loadFromDisk(const string& filename);
	void printAddressPhoneDOB();
	bool printBirthDays(size_t month);
	bool printBetweenLastNames(const string& low_last_name, const string& high_last_name);
	bool printFamilyMembers();
	bool printFriendsMembers();
	vector<extPersonType> searchByLastName(const string& last_name);

	void sortByName();
private:
	unorderedLinkedList<extPersonType> addressbook;
};

