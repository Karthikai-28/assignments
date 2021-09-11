#ifndef DBPARSER_H
#define DBPARSER_H
#include <iostream>
#include <string>
#include <map>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "product_parser.h"

/**
 * Interface for all section parsers_
 *  A section parser parses everything between
 *  <section> ... </section> in the database file
 */
class SectionParser {
public:
    virtual ~SectionParser() { }
    /**
     * Parses the section stored in the given istream
     * Increments lineno after successfully parsing each lineno
     * Sets errorMsg with a descriptive message upon an error
     * Returns true if an error occurred.
     */
    virtual bool parse(std::istream& is, DataStore& ds,
                       int& lineno, std::string& errorMsg) = 0;
    /**
     * Reports how many items were parsed
     */
    virtual void reportItemsRead(std::ostream& os) = 0;
};

/**
 * Main parser utilizing section parsers to do most
 *  of the actual parsing.  Breaks the database into
 *  sections and handle error output
 */
class DBParser {
public:
    DBParser();
    ~DBParser();
    /**
     *  Registers a section parser that will be invoked
     *  when a section with sectionName is found in the
     *  database
     */
    void addSectionParser(const std::string& sectionName,
                          SectionParser*         parser);
    /**
     *  Registers a section parser that will be invoked
     *  when a section with sectionName is found in the
     *  database. Returns true if an error occurs.
     */
    bool parse(std::string db_filename, DataStore& ds);

private:
    enum PState { FIND_SECTION, IN_SECTION };
    int lineno_;
    std::string errorMsg_;
    bool error_;
    std::map<std::string, SectionParser*> parsers_;

};


/**
 * Product section parser.  Uses separate ProductParsers
 *  to parse each type of product
 */
class ProductSectionParser : public SectionParser
{
public:
    ProductSectionParser();
    ~ProductSectionParser();
    virtual bool parse(std::istream& is, DataStore& ds,
                       int& lineno, std::string& errorMsg);
    virtual void reportItemsRead(std::ostream& os);
    void addProductParser(ProductParser* p);
protected:
    Product* parseProduct(const std::string& category,
                          std::istream& is,
                          int& lineno,
                          std::string& errorMsg);
private:
    std::map<std::string, ProductParser*> prodParsers_;
    unsigned int numRead_ ;
};

/**
 * User section parser that parses and creates Users
 */
class UserSectionParser : public SectionParser
{
public:
    UserSectionParser();
    ~UserSectionParser() {}
    virtual bool parse(std::istream& is, DataStore& ds,
                       int& lineno, std::string& errorMsg);
    virtual void reportItemsRead(std::ostream& os);
protected:
    User* parseUser(
        std::istream& is,
        DataStore& ds,
        std::string& errorMsg);
private:

    unsigned int numRead_ ;

};

class ReviewSectionParser : public SectionParser
{
public:
    ReviewSectionParser();
    ~ReviewSectionParser() {}
    virtual bool parse(std::istream& is, DataStore& ds,
                       int& lineno, std::string& errorMsg);
    virtual void reportItemsRead(std::ostream& os);
protected:
    Review* parseReview(
        std::istream& is,
        const std::string& prodname,
        std::string& errorMsg);
private:

    unsigned int numRead_ ;

};
#endif
