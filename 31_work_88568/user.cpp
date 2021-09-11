#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type, long long password) :
    name_(name), balance_(balance), type_(type), password_(password)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}

bool User::pwCheck(long long pw) {
	return pw == password_;
}

long long User::getPw() const {
	return password_;
}