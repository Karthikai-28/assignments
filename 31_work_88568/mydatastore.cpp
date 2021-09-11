#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <fstream>

#include "mydatastore.h"
#include "datastore.h"
#include "util.h"
#include "review.h"
#include "heap.h"
#include "msort.h"

using namespace std;

	MyDataStore::MyDataStore() { }

	MyDataStore::~MyDataStore() {

		//clear keys to products
		for (vector<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
			delete *it; 
		}

		//clear ppl
		for (vector<User*>::iterator it2 = users.begin(); it2 != users.end(); ++it2) {
			delete *it2; 
		}

		//clear reviews
		for (vector<Review*>::iterator it3 = reviews.begin(); it3 != reviews.end(); ++it3) {
			delete *it3; 
		}
		
	}

	void MyDataStore::addProduct(Product* p) {

		products.push_back(p);

		//keywords that this product should be associated with
		set<string> keys = p->keywords();

		for(set<string>::iterator it=keys.begin(); it!=keys.end(); ++it) {

			//keyword not inputted yet -- make new product set
			if(productkeys.find(*it) == productkeys.end()) {

				set<Product*> temp; temp.insert(p);

				productkeys.insert(make_pair(*it, temp));
				//cout << *it << " " << p->getName() << endl;

			}

			//else, insert product into existing key's set
			else {
				productkeys.find(*it)->second.insert(p);
			}

		}
	}


	void MyDataStore::addUser(User* u) {

		bool exists = false;

		//if empty, just add user (not possibly existent)
		if(users.size() == 0) { users.push_back(u); }

		//else, check to see if username exists and only add if unique
		else if (users.size() > 0) {
			for(unsigned int i = 0; i < users.size(); i++) {
				if(u->getName() == users[i]->getName()) {
					exists = true;
				}
			}

			if(!exists) {
				users.push_back(u);
			}
		}
	}



	void MyDataStore::addReview(Review* r) {

		// for(unsigned int i = 0; i < products.size(); i++) {
		// 	//if the review's product matches a product
		// 	if(products[i]->getName() == r->prodName) {
		// 		reviews.push_back(r);
		// 	}
		// }

		//impossible to enter a review for a product that doesn't exist from UI;
		//don't need to check if matching rip
		reviews.push_back(r);

		//map review to corresponding product..
		for(unsigned int i = 0; i < products.size(); i++) {
			if(convToLower(products[i] -> getName()) == convToLower(r -> prodName)){
				prodReviews[products[i]].push_back(r);
				//products[i]->addToReviewedUsers(getUser(r->username));
				return;
			}
		}

	}



	vector<Product*> MyDataStore::search(vector<string>& terms, int type) {

		vector<Product*> hits;

		//if nothing to search lol
		if(terms.size()==0) { return hits; }

		//initialize to first set of items
		if(productkeys.find(terms[0])!=productkeys.end()) {

			set<Product*> keysproducts = productkeys.find(terms[0])->second;

			set<Product*> otherkeysproducts;

			//AND search: intersect
			if(type == 0) {
				vector<string>::iterator it;
				for(it = terms.begin(); it!=terms.end(); ++it) {
					map<string, set<Product*> >::iterator key = productkeys.find((*it));
					if (key == productkeys.end()){
						continue;
					}
					otherkeysproducts = key->second;

					//update w correseponding set search each time
					keysproducts = setIntersection(keysproducts, otherkeysproducts);
				}
			}

			//OR search: union
			if(type == 1) {
				vector<string>::iterator it;
				for(it = terms.begin(); it!=terms.end(); ++it) {
					map<string, set<Product*> >::iterator key = productkeys.find((*it));
					if (key == productkeys.end()){
						continue;
					}

					otherkeysproducts = key->second;
					keysproducts = setUnion(keysproducts, otherkeysproducts);
				}
			}

			for(set<Product*>::iterator it = keysproducts.begin(); it!=keysproducts.end(); ++it) {
				hits.push_back(*it);
			}

		}

		return hits;


	}


	void MyDataStore::dump(ostream& ofile) {

		ofile << "<products>" << endl;

		for(unsigned int i=0; i<products.size(); i++) {
			products[i]->dump(ofile);
		}
		ofile << "</products>" << endl;


		ofile << "<users>" << endl;
		for(unsigned int i=0; i<users.size(); i++) {
			users[i]->dump(ofile);
		}
		ofile << "</users>" << endl;


		ofile << "<reviews>" << endl;
		for(unsigned int i=0; i<reviews.size(); i++) {
			reviews[i]->dump(ofile);
		}
		ofile << "</reviews>" << endl;

	}


	void MyDataStore::addCart(string username, Product* p) {

		if(!existingUser(username)) { cout<< "Invalid username" << endl; return; }
		

		//if the user has no cart/products: make a cart, add product.
		if(carts.find(username)==carts.end()) {
			vector<Product*> temp;
			temp.push_back(p);
			carts.insert(make_pair(username, temp));
		}

		//if user's cart exists -- add p
		else {
			carts.find(username)->second.push_back(p);
		}
	}


    void MyDataStore::buyCart(string username) {

    	if(!existingUser(username)) { cout<< "Invalid username" << endl ; return; }

    	//gets specific user
    	vector<User*>::iterator it;
    	for(it=users.begin(); it!=users.end(); ++it) {
    		if((*it)->getName() == username) {
    			break;
    		}
    	}


    	//loop through cart items; track qty and how broke u r @user
    		if(carts.find(username) != carts.end()) {

    			vector <Product*>* userCart = &carts.find(username)->second;

    			for(unsigned int i=0; i<userCart->size(); i++) {
    				//makes sure product available + affordable
    				if(userCart->at(i)->getQty() > 0 && ((*it)->getBalance() - userCart->at(i)->getPrice()) >= 0) {
    					//pay for item
    					(*it)->deductAmount(userCart->at(i)->getPrice());
    					//take ur item from cart 
    					userCart->at(i)->subtractQty(1); //from stock
    					userCart->erase(userCart->begin()+i); //from cart
 						i--;
    				}
    				else 
    				{
    					//too poor or no items
    					cout << "Too poor/no products" << endl;
    				}
    			}
    		}
    		else 
    		{
    			//no cart
    			cout << "Cart empty" << endl;
    			return;
    		}
    	
    }

    void MyDataStore::viewCart(string username){ 

    	if(!existingUser(username)) { cout<< "Invalid username" << endl; return; }

    	
    	if(carts.find(username) != carts.end()) {

    		vector<Product*> userCart = carts.find(username)->second;

    		for(unsigned int i=0; i<userCart.size(); i++) {
    			cout << "Item " << i+1 << endl;
    			cout << userCart[i]->displayString()<< endl;
    			//cout << userCart[i]->getPrice() << " " << userCart[i]->getQty() << " left.\n" << endl;

    		}
    	}
    	else {
			cout << "Empty cart" << endl;
			return;
		}

    }

    bool MyDataStore::existingUser(string username) {

    	for(vector<User*>::iterator it = users.begin(); it!=users.end(); ++it) {
    		if((*it)->getName() == username) { return true; }
    	}

    	return false;
    }


    const vector<User*> MyDataStore::getUsers() {
		return users;
	}
	
	vector<Product*> MyDataStore::getCart(string username) {
		return carts[username];
	}

	void MyDataStore::deleteItem(string username, int item) {
		carts[username].erase((carts[username].begin()+item));

	}


	double MyDataStore::getAvgRating(Product* p) {
		double sum = 0;

		if(prodReviews[p].size() == 0) return sum;

		for(unsigned int i=0; i < prodReviews[p].size(); i++){
			sum+= (prodReviews[p])[i]->rating;
		}

		return sum/(prodReviews[p].size());
	}

	
	vector<Review*> MyDataStore::getProductReviews(Product* p) {
		return prodReviews[p];
	}

	vector<Review*> MyDataStore::getAllReviews() {
		return reviews;
	}

	User* MyDataStore::getUser(string username) {
		User* u = NULL;

		for(unsigned int i = 0; i < users.size(); i++) {
			if((users[i]->getName() == username))
			{
				u = users[i];
			}
		}

		return u;
	}

	set<User*> MyDataStore::getReviewers(Product* p) {
		set<User*> reviewers;

		vector<Review*> r = getProductReviews(p);

		for (unsigned int i = 0; i < r.size(); i++) {
			reviewers.insert(getUser(r[i]->username));
		}

		return reviewers;
	}

	double MyDataStore::getUserRating(User* u, Product* p) {
		vector<Review*> reviews = getProductReviews(p);

		for (unsigned int i = 0; i < reviews.size(); i++) {
			if (reviews[i]->username == u->getName()) {
				return reviews[i]->rating;
			}
		}
		return 0;
	}


    double MyDataStore::getBasicSimilarity(User* u1, User* u2) {

    	set<Product*> a;
    	set<Product*> b;
    	set<Product*> c;

    	//getting user reviews
    	map<Product*, vector<Review*>>::iterator it;
    	for (it = prodReviews.begin(); it != prodReviews.end(); ++it) {
			for (unsigned int i = 0; i < (it->second).size(); ++i) {
				if (u1->getName() == (it->second)[i]->username) {
					a.insert(it->first);
				}
				else if (u2->getName() == (it->second)[i]->username) {
					b.insert(it->first);
				}
			}
		}

		//reviewed products
		c = setIntersection(a,b);

		if(c.empty()) {
			return 1.0; //minimum similarity
		}

		double avgSimilarity = 0;
		set<Product*>::iterator it2;
		int ct = 0;

		for(it2 = c.begin(); it2 != c.end(); ++it2) {
			Review* aReview = NULL; 
			Review* bReview = NULL;

			for(unsigned int i = 0; i < prodReviews[*it2].size(); ++i) {
				if(u1->getName() == prodReviews[*it2][i]->username) {
					aReview = prodReviews[*it2][i];
				}
				else if(u2->getName() == prodReviews[*it2][i]->username) {
					bReview = prodReviews[*it2][i];
				}
			}

			//calculate the similarity of A's rating, a, and B's rating, b, as |a-b|/4
			avgSimilarity += (abs(aReview->rating - bReview->rating))/4.0;
			++ct;
		}

		return avgSimilarity/ct;
    }


    void MyDataStore::refinedSimilarity(User* currUser) {
    	Heap<string> pq;
    	pq.push(0,currUser->getName());
    	userSimilarities.insert(make_pair(currUser->getName(),0));

    	//populate map
    	for(unsigned int i = 0; i < users.size(); i++) {
			User* neighbor = users[i];
			if(currUser != neighbor) {
				double sim = getBasicSimilarity(currUser, neighbor);
				userSimilarities.insert(make_pair(neighbor->getName(),sim));
				pq.push(sim, neighbor->getName());
			}
		
    	}

		//set<string> checked; //prevent revisiting users

		while(!pq.empty()) {
			string current = pq.top();
			User* currentObj = getUser(current);
			//checked.insert(current);
			pq.pop();

			for(unsigned int i = 0; i < users.size(); i++) {
				map<string, double>::iterator topIt = userSimilarities.find(current);
				map<string, double>::iterator userIt = userSimilarities.find(users[i]->getName());

				double temp = topIt->second + getBasicSimilarity(currentObj, users[i]);

				if(temp < userIt->second) {
					userSimilarities[users[i]->getName()] = temp;
					pq.decreaseKey(temp, users[i]->getName());
				}
			}
		}
    }


    vector<std::pair<string, double> > MyDataStore::makeSuggestion(std::string currentUser) {

    	vector<pair<string,double>> suggestions;
    	User* u = getUser(currentUser);

    	unsigned int ct = 0;
    	for(unsigned int i = 0; i < products.size(); i++) {
    		Product* p = products[i];
    		vector<Review*> pRvws = getProductReviews(p);
    		for(unsigned j = 0; j < pRvws.size(); j++) {
    			if(pRvws[j]->username == currentUser) ct++;
    		}
    	}


    	//user has reviewed everything
    	if(ct >= products.size()) { 
    		cout << "no suggestions." << endl;
    		return suggestions;
    	}

    	refinedSimilarity(u);

    	for(unsigned int i = 0; i < products.size(); i++) {
    		set<User*> ps = getReviewers(products[i]);
    		if(ps.find(u) != ps.end()) {
    			double rp = 0;
    			double w = 0;

    			set<User*>::iterator it;
    			for(it = ps.begin(); it != ps.end(); ++it) {
    				double rate = getUserRating(*it, products[i]);
    				double sim = userSimilarities[(*it)->getName()];

    				w += (1-sim);
    				rp += (1-sim)*rate;
    			}

    			if(w!=0) {
    				suggestions.push_back(make_pair(products[i]->getName(), rp/w));
    			}
    			else {
    				suggestions.push_back(make_pair(products[i]->getName(), 0));
    			}
    		}
    	}

    	distComp comp;
    	mergeSort(suggestions, comp);

    	//output to rec file
    	ofstream out;
    	out.open("rec.txt");
		out << currentUser << endl;
		for (unsigned int i = 0; i < suggestions.size(); i++) {
			out << suggestions[i].second << " " << suggestions[i].first << endl;
		}

		return suggestions;
    }

