#include "PersonType.h"
bool PersonType::operator==(const PersonType& other)
{
	return last_name == other.last_name && first_name == other.first_name;
}
bool PersonType::operator!=(const PersonType& other)
{
	return last_name != other.last_name || first_name != other.first_name;
}
string PersonType::firstName() const
{
	return first_name;
}
string PersonType::lastName() const
{
	return last_name;
}