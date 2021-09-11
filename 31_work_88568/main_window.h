#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QListWidget>
#include <QComboBox>
#include <QItemSelectionModel> //for row change
#include <QFileDialog>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QMessageBox>

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <deque>

#include "mydatastore.h"
#include "msort.h"

struct alphaComparator {
	bool operator()(Product* lhs, Product* rhs) {
		return lhs->getName() < rhs->getName();
	}
};

struct dateComparator {
	bool operator()(Review* lhs, Review* rhs) {
		return lhs->date > rhs->date;
	}
};

struct ratingComparator {

	MyDataStore * ds_;

	ratingComparator(MyDataStore* ds) {
			ds_ = ds;
		}

	bool operator()(Product* lhs, Product* rhs) {
		return ds_->getAvgRating(lhs) > ds_->getAvgRating(rhs);
	}
};

class MainWindow : public QWidget
{
	Q_OBJECT

//NOTE TO SELF: 
	//top horizontal column for search functions
	//2 vertical columns for results and reviews
	//use pop up box to add review; utilize Qt calendar/date
	//quit button bottom horizontal 

public:
	MainWindow(MyDataStore* ds);
	//~MainWindow();

private slots:
	void searchClicked();
	void alphaSort();
	void ratingSort();
	void addToProductList(); //for updating product list
	void addToCartClicked();
	void removeFromCartClicked();
	void openCartWindow();
	void closeCartWindow();
	void changeCurrentRow(int r);
	void updateReviews(int r);
	void addReview();
	void closeReview();
	void finalAddReview();
	void checkout();
	void save();
	void quit();
//login
	void addNewUser();
	//void saveNewUser();
	void login();
	void logOut();
//reccs
	void openRecommendations();
	void computeRecommendations(User* u);
	void closeRecommendations();

private:
	MyDataStore* ds_;

	QVBoxLayout* overallLayout;
	int currUser, currProduct; //to track selection
	vector<Product*> prodHits;
	User* loggedUser;

	//RECS
	QPushButton* recommendationsButton;
	QPushButton* recDoneButton;
	QWidget* recommendationsWindow;
	QVBoxLayout* recommendationsLayout;
	QLabel* recommendationsLabel;
	QListWidget* recommendationsList;


	//LOGIN
	QVBoxLayout* loginLayout;
	QWidget* loginWindow;
	QLineEdit* loginUsername;
	QLineEdit* loginPassword;
	QPushButton* loginButton;
	QPushButton* loginNewUserButton;
	QPushButton* loginQuitButton;
	QLabel* loginULabel;
	QLabel* loginPLabel;
	// QMessageBox* loginErrorUser;
	// QMessageBox* loginErrorPassword;
	QMessageBox* loginError;
	QPushButton* switchUserButton;


	//SEARCH
	//searching + type
	QHBoxLayout* searchLayout;
	//QHBoxLayout* searchTypeLayout;
	QLineEdit* searchBar;
	QPushButton* searchButton;
	QRadioButton* andRadio;
	QRadioButton* orRadio;



	//sorting search results
	QHBoxLayout* sortLayout;
	QVBoxLayout* searchResultsLayout;
	QListWidget* productList;
	QLabel* prodLabel;

	QPushButton* alphaSortButton;
	QPushButton* ratingSortButton;
	QHBoxLayout* listsLayout;
	QVBoxLayout* userLayout;
	QLabel* userLabel;
	QComboBox* userList;
	QPushButton* addToCart;
	QPushButton* viewCart;
	QLabel* sortLabel;


	QPushButton* removeFromCart;
	QPushButton* buyCart;
	QPushButton* closeCart;
	QWidget* cartWindow;
	QListWidget* cartContentsList;
	QHBoxLayout* cartLayout;

	QPushButton* quitButton;
	QPushButton* saveButton;

	QVBoxLayout* sqLayout;

	QListWidget* reviewList;
	QVBoxLayout* rvwLayout;
	QLabel* rvwLabel;
	QPushButton* addReviewButton;

	QLabel* searchLabel;
	//QPushButton* sortReviewButton;
	QWidget* reviewWindow;
	QLabel* ratingLabel; 
	QComboBox* addRating;
	QLabel* dateLabel;
	QLabel* dashLabel;
	QHBoxLayout* addDateLayout;
	QComboBox* dateDay;
	QComboBox* dateMonth;
	QComboBox* dateYear;
	QHBoxLayout* ratingLayout;
	QLabel* reviewTextLabel;
	QLineEdit* reviewText;
	QHBoxLayout* reviewTextLayout;
	QVBoxLayout* addReviewLayout;

	QPushButton* finalAddReviewButton;
	QPushButton* exitAddReview;





};

#endif