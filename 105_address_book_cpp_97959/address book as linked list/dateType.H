#ifndef date_H
#define date_H
 
class dateType
{
public:
    void setDate(int month, int day, int year);
		//Function to set the date.
		//Data members dMonth, dDay, and dYear are set 
		//according to the parameters
		//Post: dMonth = month; dDay = day;
		// 			 dYear = year;

	void getDate(int& month, int& day, int& year);
		//Function to return the date
		//Post: month = dMonth; day = dDay;
		//				  year = dYear;

	void printDate() const;
		//Function to output the date in the form mm-dd-yyyy.

    dateType(int month = 1, int day = 1, int year = 1900);
		//Constructor to set the date
		//Data members dMonth, dDay, and dYear are set 
		//according to the parameters. If no values are
		//specified when an object is declares, the default 
		//values are used.
		//Post: dMonth = month; dDay = day; 
		//    	          dYear = year;

private:
	bool isLeapYear(int y); 
		//Function to check if a year is a leap year

    int dMonth;		//variable to store month
    int dDay;		//variable to store day
    int dYear;		//variable to store year
};

#endif