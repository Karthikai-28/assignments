#pragma once
#include "addressType.h"
#include "dateType.h"
#include "PersonType.h"

enum relationShip {FAMILY, FRIEND, BUSINESS};

class extPersonType :
    public PersonType
{
public:
    relationShip getRelationShip() const;
private:

    addressType address;
    dateType birth_date;
    relationShip relationship;
    string telephone_number;

};