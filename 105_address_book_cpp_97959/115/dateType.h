
#ifndef DATE_TYPE
#define DATE_TYPE

//Class dateType definition

using namespace std;

class dateType {

private:
	int _month, _day, _year;
	
public:

void print(){
	cout<<"\n Date of Birth: "<< _month <<"-"<< _day <<"-"<< _year;
	
	}

//Default constructor
	dateType(){
_day = _month = _year = 0;
}

//Default deconstructor
~dateType(){};

//Parameterized constructor
dateType(int month, int day, int year){
	
	//I assume that the data is always valid since there is no specification in the exercise for it
	  if (month <= 12 && month > 0 && day <= 31 && day > 0 && year > 0){
	  //first test where we check if the month, day, and year are valid 

    if(month == 4 && day > 30){
		// April always has maximum of 30 days 
		//so i set the day to be 30 - the max
		_month = month;
        _day = 30;
        _year = year;
	}
	else if(month == 2 && day > 29){
		//the program checks if February has less than 29 days 
		//if it is more than 29, it means that the data is NOT valid
		//so i set the day to be 29 - the max
		_month = month;
        _day = 29;
        _year = year;
	}else{
		
		//If the data passes all the validations, it means it is valid and we can store it
		//	if the date is valid we store the date into the member variables and set data to be valid
      _month = month;
      _day = day;
      _year = year;
		}

	}else{
		
		//since there is no specification of what to do, I just set the date to the following
		_month = 2;
        _day = 12;
        _year = 2012;
	}
	
		
}

void setDate(int month, int day, int year)
{
	

  if (month <= 12 && month > 0 && day <= 31 && day > 0 && year > 0){
	  //first test where we check if the month, day, and year are valid 

    if(month == 4 && day > 30){
		// April always has maximum of 30 days 
		//so i set the day to be 30 - the max
		_month = month;
        _day = 30;
        _year = year;
	}
	else if(month == 2 && day > 29){
		//the program checks if February has less than 29 days 
		//if it is more than 29, it means that the data is NOT valid
		//so i set the day to be 29 - the max
		_month = month;
        _day = 29;
        _year = year;
	}else{
		
		//If the data passes all the validations, it means it is valid and we can store it
		//	if the date is valid we store the date into the member variables and set data to be valid
      _month = month;
      _day = day;
      _year = year;
	
		}

	}else{
		
		//since there is no specification of what to do if data is not valid, I just set the date to the following
		_month = 2;
        _day = 12;
        _year = 2012;
	}
	
		
	
}



//accessors and mutators
void setDay(int d){
	
	if(d > 31 || d <= 0){
		_day = 31;
	}else{
		_day = d;
	};
	
}

int getDate(){
	return _day;
}

void setMonth(int m){
	
	if(m > 12 || m <= 0){
		_month = 12;
	}else{
		_month = m;
	};
}

int getMonth(){
	return _month;
}

void setYear(int y){
	if(y < 0){
		_year = 2012;
	}else{
		_year = y;
	}
}

int getYear(){
	return _year;
}

};//End of class

#endif