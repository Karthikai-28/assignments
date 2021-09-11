#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	set<T> intersect; 

	//add all elements of set2 that equal something in set1
	for (typename set<T>::iterator it = s1.begin(); it != s1.end(); ++it)
    {
        if (s2.find(*it) != s2.end())
            intersect.insert(*it);
    }

    return intersect;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	set<T> uni;
	//insert all elements of set1
	for (typename set<T>::iterator it1 = s1.begin(); it1 != s1.end(); ++it1) {
		uni.insert(*it1);
	}

	//add all unique elements of set2
	for (typename set<T>::iterator it2 = s2.begin(); it2 != s2.end(); ++it2) {
		//if(uni.find(*it2)==uni.end())
		uni.insert(*it2);
	}

	return uni;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
