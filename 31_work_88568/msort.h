#ifndef MSORT_H
#define MSORT_H

#include <vector>

using namespace std;

//prototypes

//to sort array into lhs and rhs
template<class T, class Comparator>
void mergeSort(vector<T>& myArray, Comparator comp);

//merge arrays
template<class T, class Comparator>
void merge(vector<T>& lhs, vector<T>& rhs, vector<T>& mergedArray, Comparator comp);

//---------

template<class T, class Comparator>
void mergeSort(vector<T>& myArray, Comparator comp) 
{
	vector<T> lhs, rhs; 
	unsigned int mid = (int)(myArray.size()/2);


	if(myArray.size() > 1) 
	{
		//first half (lhs)
		for(unsigned int i = 0; i < mid; i++) {
			lhs.push_back(myArray[i]);
		}

		//rhs
		for(unsigned int i = mid; i < myArray.size(); i++) {
			rhs.push_back(myArray[i]);
		}

		mergeSort(lhs, comp);
		mergeSort(rhs, comp);

		merge(lhs, rhs, myArray, comp);
	}

	else return;
}


template<class T, class Comparator>
void merge(vector<T>& lhs, vector<T>& rhs, vector<T>& mergedArray, Comparator comp)
{
	unsigned int lhs_pos = 0, rhs_pos = 0;

	vector<T> tempArray;

	while(lhs_pos < lhs.size() && rhs_pos < rhs.size()) {
		//left < right
		if(comp(lhs[lhs_pos] , rhs[rhs_pos])) {
			tempArray.push_back(lhs[lhs_pos++]);
		}
		else {
			tempArray.push_back(rhs[rhs_pos++]);
		}
	}

	//fill in any remaining
	for(unsigned int i = lhs_pos; i < lhs.size(); i++) {
		tempArray.push_back(lhs[lhs_pos++]);
	}

	for(unsigned int i = rhs_pos; i < rhs.size(); i++) {
		tempArray.push_back(rhs[rhs_pos++]);
	}

	mergedArray.swap(tempArray);

};

#endif