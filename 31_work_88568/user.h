#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <cmath>
#include <set>
#include <vector>
/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class Product;
class User {
public:
    User();
    User(std::string name, double balance, int type);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    bool pwCheck(long long);
    long long getPw() const;

private:
    std::string name_;
    double balance_;
    int type_;
    long long password_; //hashed
};
#endif
