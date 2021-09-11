#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

long long pwHash(std::string pwInput){

	long long int pw = 0;
	int exp = 0;

	for(int i = pwInput.length()-1; i >= 0; --i) {
		pw += (long long int)((pwInput[i])*(pow((long long)128,exp)));
		++exp;
	}

	unsigned int digits[4] = {0};

	for(int i = 3; i >= 0; --i) {
		digits[i] = pw % 65521;
		pw /= 65521;
	}

	return ((digits[0]*45912)+ (digits[1]*35511) + (digits[2]*65169) +(digits[3]*4625))%65521;
}

#endif