#include "main_window.h"
#include "hash.h"
#include "heap.h"


MainWindow::MainWindow(MyDataStore* ds)
{
	setWindowTitle("AMAZON :^)");
	ds_ = ds;

	this->setMinimumSize(QSize(1200, 600));
	currUser = -1;
	currProduct = -1;
	loggedUser = new User();

//RECOMMEND
	recommendationsLayout = new QVBoxLayout;
	recommendationsWindow = new QWidget;
	recommendationsWindow->setMinimumSize(QSize(400,300));
	recommendationsList = new QListWidget;
	recommendationsLabel = new QLabel("product -- recommendation score");
	recDoneButton = new QPushButton("DONE");
	connect(recDoneButton, SIGNAL(clicked()), this, SLOT(closeRecommendations()));

	recommendationsWindow->setWindowTitle("YOU SHOULD BUY...");
	recommendationsLayout->addWidget(recommendationsLabel);
	recommendationsLayout->addWidget(recommendationsList);
	recommendationsLayout->addWidget(recDoneButton);
	recommendationsWindow->setLayout(recommendationsLayout);


//LOGIN
	loginLayout = new QVBoxLayout;
	loginULabel = new QLabel("username:");
	loginPLabel = new QLabel("password:");
	loginWindow = new QWidget;
	loginWindow->setMinimumSize(QSize(300,200));
	loginWindow->setWindowTitle("Amazon login");
	loginUsername = new QLineEdit;
	loginPassword = new QLineEdit;
	loginButton = new QPushButton("Sign in");
	loginQuitButton = new QPushButton("Quit");
	loginNewUserButton = new QPushButton("Create new user");
	// loginErrorUser = new QMessageBox();
	// loginErrorUser->setText("Invalid username. Please try again.");
	// loginErrorPassword = new QMessageBox();
	// loginErrorPassword->setText("Invalid password. Please try again.");
	loginError = new QMessageBox();


	loginLayout->addWidget(loginULabel);
	loginLayout->addWidget(loginUsername);
	loginLayout->addWidget(loginPLabel);
	loginLayout->addWidget(loginPassword);
	loginLayout->addWidget(loginButton);
	loginLayout->addWidget(loginNewUserButton);
	loginLayout->addWidget(loginQuitButton);

	connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
	connect(loginNewUserButton, SIGNAL(clicked()), this, SLOT(addNewUser()));
	connect(loginQuitButton, SIGNAL(clicked()), this, SLOT(quit()));

	loginWindow->setLayout(loginLayout);
	loginWindow->show();

//SEARCHING (includes and/or)
	overallLayout = new QVBoxLayout;
	searchLayout = new QHBoxLayout;
	//searchTypeLayout = new QHBoxLayout;
	searchBar = new QLineEdit();
	searchButton = new QPushButton("SEARCH");
	andRadio = new QRadioButton("AND");
	orRadio = new QRadioButton("OR");
	searchLabel = new QLabel("search:");

	searchLayout->addWidget(searchLabel);
	searchLayout->addWidget(searchBar);
	searchLayout->addWidget(andRadio);
	searchLayout->addWidget(orRadio);
	searchLayout->addWidget(searchButton);

	productList = new QListWidget;

	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchClicked()));

//DISPLAY+SORTING RESULTS

	searchResultsLayout = new QVBoxLayout();
	prodLabel = new QLabel("PRODUCTS");


	sortLayout = new QHBoxLayout();
	sortLabel = new QLabel("\t\t\t\t\t\t\tsort results:");
	alphaSortButton = new QPushButton("alphabetical (A-Z)");
	ratingSortButton = new QPushButton("average rating (high - low)");
	connect(alphaSortButton, SIGNAL(clicked()), this, SLOT(alphaSort()));
	connect(ratingSortButton, SIGNAL(clicked()), this, SLOT(ratingSort()));
	sortLayout->addWidget(sortLabel);
	sortLayout->addWidget(alphaSortButton);
	sortLayout->addWidget(ratingSortButton);

	listsLayout = new QHBoxLayout();
	reviewList = new QListWidget;
	searchResultsLayout -> addWidget(prodLabel);
	searchResultsLayout -> addWidget(productList);
	listsLayout->addLayout(searchResultsLayout);
	rvwLayout = new QVBoxLayout();
	rvwLabel = new QLabel("REVIEWS (from most recent)");
	rvwLayout->addWidget(rvwLabel);
	rvwLayout->addWidget(reviewList);
	listsLayout->addLayout(rvwLayout);
	
	userLabel = new QLabel("");

	userLayout = new QVBoxLayout();

	addToCart = new QPushButton("add product to cart");
	removeFromCart = new QPushButton("remove from cart");
	viewCart = new QPushButton("view cart");
	recommendationsButton = new QPushButton("product recommendations");
	buyCart = new QPushButton("check out");
	closeCart = new QPushButton("close cart");

	userLayout->addWidget(recommendationsButton);
	userLayout->addWidget(viewCart);
	userLayout->addWidget(userLabel);
	searchResultsLayout->addWidget(addToCart);

	connect(viewCart, SIGNAL(clicked()), this, SLOT(openCartWindow()));
	cartWindow = new QWidget();
	cartLayout = new QHBoxLayout();
	cartContentsList = new QListWidget();
	cartLayout->addWidget(cartContentsList);
	cartLayout->addWidget(removeFromCart);
	cartLayout->addWidget(buyCart);
	cartLayout->addWidget(closeCart);

	connect(addToCart, SIGNAL(clicked()), this, SLOT(addToCartClicked()));
	connect(removeFromCart, SIGNAL(clicked()), this, SLOT(removeFromCartClicked()));
	connect(productList, SIGNAL(currentRowChanged(int)), this, SLOT(changeCurrentRow(int)));
	connect(closeCart, SIGNAL(clicked()), this, SLOT(closeCartWindow()));
	connect(buyCart, SIGNAL(clicked()), this, SLOT(checkout()));
	connect(recommendationsButton, SIGNAL(clicked()), this, SLOT(openRecommendations()));

	saveButton = new QPushButton("SAVE SHOPPING");
	quitButton = new QPushButton("EXIT AMAZON");
	switchUserButton = new QPushButton("LOG OUT/SWITCH USER");
	connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
	connect(switchUserButton, SIGNAL(clicked()), this, SLOT(logOut()));
	sqLayout = new QVBoxLayout;
	sqLayout->addWidget(saveButton);
	sqLayout->addWidget(switchUserButton);
	sqLayout->addWidget(quitButton);

	addReviewButton = new QPushButton("add review");

	//sortReviewButton = new QPushButton("sort reviews (most recent)");
	//rvwLayout->addWidget(sortReviewButton);

	rvwLayout->addWidget(addReviewButton);
	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addReview()));
	connect(productList, SIGNAL(currentRowChanged(int)), this, SLOT(updateReviews(int))); 
	reviewWindow = new QWidget();
	reviewWindow->setWindowTitle("add a review");
	addReviewLayout = new QVBoxLayout();
	ratingLabel = new QLabel("Rating: ");
	dateLabel = new QLabel("Date(YYYY-MM-DD): ");
	
	reviewTextLabel = new QLabel("Review: ");

	finalAddReviewButton = new QPushButton("submit review");

	addRating = new QComboBox();
	for(unsigned int i = 1; i <= 5; i++) {
		addRating -> addItem(QString::number(i)); 
	}

	dateDay = new QComboBox();
	for(unsigned int i = 1; i <= 31; i++) {
		dateDay -> addItem(QString::number(i)); 
	}

	dateMonth = new QComboBox();
	for(unsigned int i = 1; i<=12; i++) {
		dateMonth->addItem(QString::number(i));
	}

	dateYear = new QComboBox();
	for(unsigned int i = 2016; i <= 2030; i++) {
		dateYear -> addItem(QString::number(i)); 
	}

	reviewText = new QLineEdit();
	reviewTextLayout = new QHBoxLayout;
	reviewTextLayout->addWidget(reviewTextLabel);
	reviewTextLayout->addWidget(reviewText);

	addDateLayout = new QHBoxLayout;
	addDateLayout->addWidget(dateLabel);
	addDateLayout->addWidget(dateYear);
	addDateLayout->addWidget(dateMonth);
	addDateLayout->addWidget(dateDay);

	ratingLayout = new QHBoxLayout;
	ratingLayout->addWidget(ratingLabel);
	ratingLayout->addWidget(addRating);

	exitAddReview = new QPushButton("exit");

	addReviewLayout->addLayout(ratingLayout);
	addReviewLayout->addLayout(addDateLayout);
	addReviewLayout->addLayout(reviewTextLayout);
	addReviewLayout->addWidget(finalAddReviewButton);
	addReviewLayout->addWidget(exitAddReview);

	reviewWindow->setLayout(addReviewLayout);

	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addReview()));
	connect(finalAddReviewButton, SIGNAL(clicked()), this, SLOT(finalAddReview()));
	connect(exitAddReview, SIGNAL(clicked()), this, SLOT(closeReview()));


	cartWindow->setLayout(cartLayout);

	overallLayout-> addLayout(searchLayout);
	overallLayout-> addLayout(sortLayout);
	overallLayout-> addLayout(listsLayout);
	overallLayout-> addLayout(userLayout);
	overallLayout-> addLayout(sqLayout);


	setLayout(overallLayout);
}


void MainWindow::openRecommendations() {
	computeRecommendations(loggedUser);
	//recommendationsWindow->show();
}

void MainWindow::closeRecommendations() {
	recommendationsWindow->close();
}

void MainWindow::computeRecommendations(User* u) {
	vector<std::pair<string, double>> v = ds_->makeSuggestion(u->getName());

	if(v.size() == 0) {
		loginError->setText("no recommendations");
		loginError->exec(); 
		return;
	}

	for(unsigned int i = 0; i < v.size(); i++){	
		QString rec = QString::fromStdString(v[i].first) + " - " 
			+ QString::number(v[i].second) + "\n";

		recommendationsList -> addItem(rec);
	}

	recommendationsWindow->show();
}

//login functions
void MainWindow::login() {
	string username = loginUsername->text().toStdString();
	string password = loginPassword->text().toStdString();

	//if either input empty
	if(username.length() == 0 || password.length() == 0) {
		loginError->setText("Please complete required fields.");
		loginError->exec();
		return;
	}

	User* u = ds_->getUser(username);
	long long temp = pwHash(password);

	//if username exists, check for password
	if(ds_->existingUser(username)) {
		if(u->pwCheck(temp)) {
			loggedUser = u;
			this->setWindowTitle(QString::fromStdString(username)+"'s shopping spree!");
			this->show();
			loginWindow->hide();
			return;
		}
		else {
			loginError->setText("Invalid password.");
			loginError->exec();
			return;
		}
	}
	else {
		loginError->setText("Invalid username.");
		loginError->exec();
		return;
	}

}


void MainWindow::addNewUser() {
	string username = loginUsername->text().toStdString();
	string password = loginPassword->text().toStdString();

	//if either input empty
	if(username.length() == 0 || password.length() == 0) {
		loginError->setText("Please complete required fields.");
		loginError->exec();
		return;
	}

	if(ds_->existingUser(username)) {
		loginError->setText("Username already taken. Try again.");
		loginError->exec();
		return;
	}

	//password cannot be >8 characters
	if(password.length()>8) {
			loginError->setText("Maximum password length: 8 characters. Try again.");
			loginError->exec();
			return;
	}
	

	User* u = new User(username, 100.00, 0, pwHash(password));
	ds_->addUser(u);

	loggedUser = u;

	this->setWindowTitle(QString::fromStdString(username)+"'s shopping spree!");
	this->show();
	loginWindow->hide();

}

void MainWindow::logOut() {
	loginPassword->clear();
	this->hide();
	loginWindow->show();
}



//slot functions
void MainWindow::searchClicked() {

	vector<string> terms;
	string term;
	stringstream ss((searchBar->text()).toStdString()); 

	while(ss>>term) {
		terms.push_back(convToLower(term));
	}

	if(andRadio->isChecked()) {
		prodHits = ds_->search(terms, 0);
	}
	else if(orRadio->isChecked()) {
		prodHits = ds_->search(terms, 1);
	}

	productList-> clear();

	//updates hits into product list widget
	for(unsigned int i = 0; i < prodHits.size(); i++){	
		QString product = QString::fromStdString(prodHits[i]->getName()) + "\tPrice: $" 
			+ QString::number(prodHits[i]->getPrice()) + "\n";

		productList -> addItem(product);
	}

}


void MainWindow::alphaSort() 
{
	alphaComparator comp;
	mergeSort(prodHits,comp);
	addToProductList();
}

void MainWindow::ratingSort() 
{
	ratingComparator comp(ds_);
	mergeSort(prodHits, comp);
	addToProductList();
}


void MainWindow::addToProductList() 
{

	productList->clear();

	for(unsigned int i = 0; i < prodHits.size(); i++){	
		QString product = QString::fromStdString(prodHits[i]->getName()) + "\tPrice: $" 
			+ QString::number(prodHits[i]->getPrice()) + "\n";

		productList -> addItem(product);
	}
}

void MainWindow::addToCartClicked()
{	

	Product* prod = NULL;
	if(currUser != -1) {
		prod = prodHits[currUser];
	}
	if(prod != NULL) {
		std::string username_ = loggedUser->getName();
		ds_->addCart(username_, prod);
	}

	cartContentsList->clear();

	//gets name of selected dropdown 
	string username_ = loggedUser->getName();
	vector<Product*> cart = ds_->getCart(username_);


	for(unsigned int i=0; i < cart.size(); i++) {
		QString cartItem = QString::fromStdString(cart[i]->getName());
		cartContentsList->addItem(cartItem);
	}

}

void MainWindow::removeFromCartClicked()
{
	if(cartContentsList->currentRow() != -1) {
		ds_->deleteItem(loggedUser->getName(), cartContentsList->currentRow());
		cartContentsList->takeItem(cartContentsList->currentRow());
	}
}

void MainWindow::changeCurrentRow(int r)
{
	currUser = r;
	currProduct = r;
}

void MainWindow::openCartWindow() 
{	
	cartContentsList->clear();

	//gets name of selected dropdown 
	string username_ = loggedUser->getName();
	vector<Product*> cart = ds_->getCart(username_);


	for(unsigned int i=0; i < cart.size(); i++) {
		QString cartItem = QString::fromStdString(cart[i]->getName());
		cartContentsList->addItem(cartItem);
	}
	
	cartWindow->setWindowTitle(QString::fromStdString(username_)+"'s shopping cart");
	//cartWindow->update();
	cartWindow->show();
}

void MainWindow::closeCartWindow()
{
	cartWindow->hide();
}

void MainWindow::updateReviews(int r)
{
	vector<Review*> reviews = ds_->getProductReviews(prodHits[r]);

	for (int i =0; i < reviewList->count(); i++) {
		reviewList-> takeItem(0);
		i--;
	}

	dateComparator comp;
	mergeSort(reviews, comp);

	for(unsigned int i = 0; i < reviews.size(); i++){
		QString review = ("Rating: " + QString::number(reviews[i] -> rating) 
			+ "\tDate: " + QString::fromStdString(reviews[i] -> date) + "\n" + "\"" + QString::fromStdString(reviews[i] -> reviewText) 
			+ "\" - " + QString::fromStdString(reviews[i]->username) + "\n");

		reviewList->addItem(review);
	}

}

void MainWindow::addReview()
{
	if(currProduct!=-1)
	reviewWindow->show();

}

void MainWindow::closeReview() 
{
	reviewWindow->hide();
}

void MainWindow::finalAddReview() 
{

	Review* rvw = new Review;

	rvw->prodName = prodHits[currProduct]->getName();
	rvw->username = loggedUser->getName();
	rvw->rating = addRating->currentText().toInt();
	rvw->date = dateYear->currentText().toStdString()+"-"+
		dateMonth->currentText().toStdString()+"-"+dateDay->currentText().toStdString();
	rvw->reviewText = reviewText->text().toStdString();

	ds_->addReview(rvw);

	updateReviews(currProduct);

	reviewWindow->hide();
}

void MainWindow::checkout()
{
	string username_ = loggedUser->getName();
	ds_->buyCart(username_);

	//cartContentsList->clear();
	
	this->openCartWindow();

}


void MainWindow::save()
{
	string filename = QFileDialog::getSaveFileName().toStdString();
	ofstream ofile(filename.c_str());
	ds_->dump(ofile);
	ofile.close();
}

void MainWindow::quit()
{
	this->close();
	loginWindow->close();
}