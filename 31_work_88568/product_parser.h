#ifndef PRODUCT_PARSER_H
#define PRODUCT_PARSER_H
#include <string>
#include <iostream>
#include "product.h"

class ProductParser
{
public:
    ProductParser();

    virtual ~ProductParser();

    /**
     * Parses product info from the given input stream
     */
    Product* parse(std::string category,
                   std::istream& is,
                   bool& error,
                   std::string& errorMsg,
                   int& lineno);

    /**
     * Returns the product category for this parser
     */
    virtual std::string categoryID() = 0;

protected:
    /**
     * Parses the common data members of a product
     */
    void parseCommonProduct(std::istream& is,
                            bool& error,
                            std::string& errorMsg,
                            int& lineno);

    /**
     * Parses the unique data members of a specific product type
     *   and allocates a specific Product object
     */
    virtual Product* parseSpecificProduct(std::string category,
                                          std::istream& is,
                                          bool& error,
                                          std::string& errorMsg,
                                          int& lineno) = 0;


    /**
     * Dynamically allocates a specific product type from the data
     *  parsed and stored in the specific product parser
     */
    virtual Product* makeProduct() = 0;

    std::string prodName_;
    double price_;
    int qty_;

};


class ProductBookParser : public ProductParser
{
public:
    ProductBookParser();
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);

    std::string categoryID();

protected:
    Product* makeProduct();

private:
    std::string isbn_;
    std::string author_;
};


class ProductClothingParser : public ProductParser
{
public:
    ProductClothingParser();
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);

    std::string categoryID();

protected:
    Product* makeProduct();

private:
    std::string size_;
    std::string brand_;
};


class ProductMovieParser : public ProductParser
{
public:
    ProductMovieParser();
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);

    std::string categoryID();

protected:
    Product* makeProduct();

private:
    std::string genre_;
    std::string rating_;
};

#endif
