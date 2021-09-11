#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include "user.h"


class Book : public Product {
public:
	Book(const std::string name, const double price, const int quantity, const std::string category,
		std::string isbn, std::string author);

	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;


private:
	std::string author_;
	std::string isbn_;
};

#endif