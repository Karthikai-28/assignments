#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip> 
#include <cctype>
using namespace std;

int main()
{
string file1,file2;
string str = "<>"; 
ifstream ipfile;
ofstream opfile;
char c;



int amountline = 0;
int amountcha = 0;
int amounttag = 0;
int amountcomment = 0;
cout <<  "Please enter the name of the file you wish to check" << endl;
cin >> file1;


ipfile.open(file1.c_str());


if (!ipfile.is_open())

{
	cout << "Oops! Couldn't open " << file1 << "!\n"<<endl;

	return 1;



}
 
{

cout << " Please enter the file you wish the edited contents to be copied to" << endl;
cout << " This will be created if it does not already exist"<< endl; 
cin >> file2;
}

opfile.open(file2.c_str());


while (!ipfile.eof())

{	

ipfile.get(c);
opfile << c;


		

		if(c!='\n' && !ipfile.eof() && c!=' ')
		{
			amountcha++;
		}
		if(c=='\n')
		{
			amountline++;
		}

	 if( str.find("<") != string::npos && str.find(">") != string::npos)
{
    amounttag++;
}

   
      if ( c == '!')
      {
      amountcomment++;
      }

if (c=='<' )

	 {
		 
		istag = true;

	 }

	 if (c== '>' && istag == true)

	 {

amounttag++;
istag = false; 
	 }




if (c== '!')

{

	iscomment = true; 

}

if ( c== '-' && iscomment == true)
{
amountcomment++;
amounttag --;
iscomment = false; 

}

cout << " This file contains :" << amountline << " lines" << endl;
cout << " This file contains :" << amountcha << " charecters" << endl;
cout << " this file has : " << amountcomment<<  " comments " << endl;
cout << " This file contains  : " << amounttag << "tags"   << endl; 

cout << " Copy complete, edited code located in " << file2 << endl;



return 0;
}
}