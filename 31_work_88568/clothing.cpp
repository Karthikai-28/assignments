#include "clothing.h"
#include "util.h"

#include <iomanip>
#include <string>
#include <set>
#include <sstream>


using namespace std;

Clothing::Clothing(const string name, const double price, const int quantity, const string category,
		std::string size, std::string brand): Product(category, name, price, quantity)
{
	size_ = size;
	brand_ = brand;
}


set<string> Clothing::keywords() const
{
	set<string> name = parseStringToWords(name_);
	set<string> brand = parseStringToWords(brand_);
	set<string> size = parseStringToWords(size_);
	
	set<string> uni1 = setUnion(name, brand);
	set<string> uni2 = setUnion(uni1, size);

	return uni2;
}


string Clothing::displayString() const
{
	//get price
	stringstream ss;
	ss << price_;
	string price;
	ss >> price;
	//quantity
	stringstream ss2;
	ss2 << qty_;
	string qty;
	ss2 >> qty; 

	//return string
	return name_ + "\n" + "brand: " + brand_ + " " + "size: " +
	size_ + "\n" + price + " " + qty + " left.";

}
void Clothing::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
		<< "\n" << size_ << "\n" << brand_ << "\n"; 
}