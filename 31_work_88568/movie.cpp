#include "movie.h"
#include "util.h"

#include <iomanip>
#include <string>
#include <set>
#include <sstream>


using namespace std;

Movie::Movie(const std::string name, const double price, const int quantity, const std::string category,
		std::string genre, std::string rating): Product(category, name, price, quantity)
{
	genre_ = genre;
	rating_ = rating;
}


set<string> Movie::keywords() const
{
	set<string> name = parseStringToWords(name_);
	set<string> rating = parseStringToWords(rating_);
	set<string> genre = parseStringToWords(genre_);
	
	set<string> uni1 = setUnion(name, rating);
	set<string> uni2 = setUnion(uni1, genre);

	return uni2;
}


string Movie::displayString() const
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
	return name_ + "\n" + "rating: " + rating_ + " " + "genre: " +
	genre_ + "\n" + price + " " + qty + " left.";

}
void Movie::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
		<< "\n" << genre_ << "\n" << rating_ << "\n"; 
}
