#ifndef REVIEW_H
#define REVIEW_H
#include <string>

struct Review
{
    Review() :  prodName(), rating(), username(), date(), reviewText()
    { }
    Review(const std::string& prod,
           int rate,
           const std::string& u,
           const std::string& d,
           const std::string& review_text) :
        prodName(prod),
        rating(rate),
        username(u),
        date(d),
        reviewText(review_text)
    { }

  void dump(std::ostream& os) {
    os<<prodName<<std::endl<<rating<<" "<<username<<" "<<date<<" "<<reviewText<<std::endl;
  }

    std::string prodName;
    int rating;
    std::string username;
    std::string date;
    std::string reviewText;
};

#endif