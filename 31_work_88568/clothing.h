
#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include "user.h"


class Clothing : public Product {
public:
	Clothing(const std::string name, const double price, const int quantity, const std::string category,
		std::string size, std::string brand);

	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;


private:
	std::string size_;
	std::string brand_;
};

#endif