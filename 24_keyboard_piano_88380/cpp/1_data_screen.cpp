#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string Source;
string Year;
string Mean;
int num;

int main()
{

ifstream ip("temp.csv");
    if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

    while (ip.good())
    {
        getline(ip,Source,',');
        getline(ip,Year,',');
        getline(ip,Mean,'\n');

        // std::cout << Source << " " << Year << " " << Mean << '\n';
        std::cout << Year << '\n';
    }
    ip.close ();
}