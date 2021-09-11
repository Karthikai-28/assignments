#include <iostream> 
#include <ctime> 
#include <cstdlib> 
#include "orderedpair.h" 
using namespace std; 
using namespace cs_pairs;
int main() 
{
    int num1, num2;
    OrderedPair<int> myList[10];
    
    srand(static_cast<unsigned>(time(0)));
    cout << "default value: ";
    myList[0].print();
    cout << endl;
    
    for (int i = 0; i < 10; i++) 
    {
        myList[i].setFirst(rand() % 50);
        myList[i].setSecond(rand() % 50 + 50);
    }
    
    myList[2] = myList[0] + myList[1];
    
    if (myList[0] < myList[1]) 
    {
        myList[0].print();
        cout << " is less than ";
        myList[1].print(); 
        cout << endl;
    }
    
    for (int i = 0; i < 10; i++) 
    {
        myList[i].print();
        cout << endl;
    }
    
    cout << "Enter two numbers to use in an OrderedPair.  Make sure they are different numbers: ";
    cin >> num1 >> num2;
    OrderedPair<int> x;
    
    try 
    {
        x.setFirst(num1);
        x.setSecond(num2);
    } catch (OrderedPair<int>::DuplicateMemberError e) 
    {
        x.setFirst(OrderedPair<int>::DEFAULT_VALUE);
        x.setSecond(OrderedPair<int>::DEFAULT_VALUE);        
    }
    
    cout << "The resulting OrderedPair: ";
    x.print();
    cout << endl;

    // String Version

    cout << endl << "-------------Strings---------------" << endl;
    string s1, s2;
    OrderedPair<string> myList2[10];
    
    srand(static_cast<unsigned>(time(0)));
    cout << "default value: ";
    myList2[0].print();
    cout << endl;
    
    for (int i = 0; i < 10; i++) 
    {
        string empty = "";
        myList2[i].setFirst(empty + char('a' + rand() % 26));
        myList2[i].setSecond(empty + char('A' + rand() % 26));
    }
    
    myList2[2] = myList2[0] + myList2[1];
    
    if (myList2[0] < myList2[1]) 
    {
        myList2[0].print();
        cout << " is less than ";
        myList2[1].print(); 
        cout << endl;
    }
    
    for (int i = 0; i < 10; i++) 
    {
        myList2[i].print();
        cout << endl;
    }
    
    cout << "Enter two strings to use in an OrderedPair.  Make sure they are different: ";
    cin >> s1 >> s2;
    OrderedPair<string> s;
    
    try 
    {
        s.setFirst(s1);
        s.setSecond(s2);
    } 
    catch (OrderedPair<string>::DuplicateMemberError e) 
    {
        s.setFirst(OrderedPair<string>::DEFAULT_VALUE);
        s.setSecond(OrderedPair<string>::DEFAULT_VALUE);        
    }

    cout << "The resulting OrderedPair: ";
    s.print();
    cout << endl;
}