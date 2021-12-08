#include "AddressBookType.h"
void AddressBookType::sortByName()
{

}
bool AddressBookType::loadFromDisk(const string& filename)
{
	return true;
}
vector<extPersonType> AddressBookType::searchByLastName(const string& last_name)
{
	vector<extPersonType> last_name_matches;
	for(linkedListIterator<extPersonType> it = addressbook.begin(); it != addressbook.end(); ++it)
	{
		extPersonType extperson = *it;
		if (extperson.lastName() == last_name)
			last_name_matches.push_back(extperson);
	}
	return last_name_matches;
}
void AddressBookType::printAddressPhoneDOB()
{
	for (linkedListIterator<extPersonType> it = addressbook.begin(); it != addressbook.end(); ++it)
	{
		extPersonType extperson = *it;
		cout << extperson.lastName() << ", " << extperson.firstName() << endl;
	}
}
bool AddressBookType::printBirthDays(size_t month)
{
	for (linkedListIterator<extPersonType> it = addressbook.begin(); it != addressbook.end(); ++it)
	{
		extPersonType extperson = *it;
		cout << extperson.lastName() << ", " << extperson.firstName() << endl;
	}
	return true;
}
bool AddressBookType::printBetweenLastNames(const string& low_last_name, 
											const string& high_last_name)
{
	if (high_last_name < low_last_name)
		return false;

	size_t counter = 0;
	for (linkedListIterator<extPersonType> it = addressbook.begin(); it != addressbook.end(); ++it)
	{
		extPersonType extperson = *it;
		string last_name = extperson.lastName();
		if (low_last_name <= last_name && last_name <= high_last_name)
		{
			counter++;
			cout << extperson.lastName() << ", " << extperson.firstName() << endl;
		}
	}
	return counter > 0;
}
bool AddressBookType::printFamilyMembers()
{
	size_t counter = 0;
	for (linkedListIterator<extPersonType> it = addressbook.begin(); it != addressbook.end(); ++it)
	{
		extPersonType extperson = *it;
		if (extperson.getRelationShip() == relationShip::FAMILY)
		{
			counter++;
			cout << extperson.lastName() << ", " << extperson.firstName() << endl;
		}
	}
	return counter > 0;
}
bool AddressBookType::printFriendsMembers()
{
	return true;
}