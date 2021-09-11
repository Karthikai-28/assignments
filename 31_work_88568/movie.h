#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "user.h"


class Movie : public Product {
public:
	Movie(const std::string name, const double price, const int quantity, const std::string category,
		std::string genre, std::string rating);

	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;


private:
	std::string genre_;
	std::string rating_;
};

#endif