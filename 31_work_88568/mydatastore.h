#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

#include "datastore.h"
#include "util.h"
#include "user.h"
#include "product.h"

using namespace std;

struct distComp {
	bool operator()(pair<std::string, double> lhs, pair<string, double> rhs)
	{
		if (lhs.second != rhs.second) {
			return lhs.second > rhs.second;
		}
		else {
			return lhs.first < rhs.first;
		}
	}
};

class MyDataStore : public DataStore
{
public:
	MyDataStore();
	~MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	void addReview(Review* r);

	vector<Product*> search(vector<string>& terms, int type);
	void dump(ostream& ofile);

	void addCart(string username, Product* p);
    void buyCart(string username);
    void viewCart(string username);
    void deleteItem(string username, int item);

 
    const vector<User*> getUsers();
   	User* getUser(string username);
    vector<Product*> getCart(string username);

    vector<Review*> getProductReviews(Product* p);
	vector<Review*> getAllReviews();
    double getAvgRating(Product* p);
    set<User*> getReviewers(Product* p);
    double getUserRating(User* u, Product* p);

    bool existingUser(string username);

    double getBasicSimilarity(User* u1, User* u2);
    void refinedSimilarity(User* currUser); //dijkstras
    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);



private:
	vector<Product*> products; //duplicates OK
	vector<User*> users;
	vector<Review*> reviews;

	map<string, set<Product*> > productkeys;
	map<string, vector<Product*> >  carts; //FIFO
	map<Product*, vector<Review*> > prodReviews; 

	map<string,double> userSimilarities;
	//bool existingUser(string username);


};
#endif