#include "book.h"
#include "util.h"

#include <iomanip>
#include <string>
#include <set>
#include <sstream>


using namespace std;

Book::Book(const string name, const double price, const int quantity, const std::string category,
	string isbn, string author): Product(category, name, price, quantity)
{
	isbn_ = isbn;
	author_ = author;
}


set<string> Book::keywords() const
{
	set<string> name = parseStringToWords(name_);
	set<string> author = parseStringToWords(author_);
	set<string> isbn = parseStringToWords(isbn_);

	set<string> uni1 = setUnion(name, author);
	set<string> uni2 = setUnion(uni1, isbn);

	return uni2;
}


string Book::displayString() const
{
	//get price
	stringstream ss;
	ss << price_;
	string price;
	ss >> price;

	stringstream ss2;
	ss2 << qty_;
	string qty;
	ss2 >> qty; 

	//return string
	return name_ + "\n" + "Author: " + author_ + " " + "ISBN: " +
	isbn_ + "\n" + price + " " + qty + " left.";

}
void Book::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
		<< "\n" << isbn_ << "\n" << author_ << "\n"; 
}