#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
        set<string> words;
    string buf;
    stringstream ss(rawWords);
    while(ss>>buf) {
        vector<int> subLocs;

        if(buf.length()<=1) {continue;}

        for(unsigned int i=0; i<buf.length(); i++) {
            if(ispunct(buf[i])!=0) {
                subLocs.push_back(i);
            }
        }

        unsigned int subCts = subLocs.size();

        if(subCts==0) {
            words.insert(convToLower(buf));
        } 

        if(subCts>0) {
            for(unsigned int i=0; i<subCts; i++) {
                //beginning
                if(i==0) {
                    string temp = buf.substr(0,subLocs[i]);
                    if(temp.length()>1) {
                        words.insert(convToLower(buf));
                    }
                }
                //end
                if(i==subCts-1) {
                    string temp = buf.substr(subLocs[i]);
                    if(temp.length()>1) {
                        words.insert(convToLower(buf));
                    }
                }
                //middle cases
                if(i>0 && i<subCts-1){
                    string temp = buf.substr(subLocs[i], subLocs[i+1]);
                    if(temp.length()>1) {
                        words.insert(convToLower(buf));
                    }
                }

            }
        }

        
    }

    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
