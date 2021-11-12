/*
 * lex.cpp
 *
 * CS280 - Fall 2021
 */

#include <cctype>
#include <map>

using std::map;
using namespace std;

#include "lex.h"
static map<Token,string> tokenPrint = {
		{PROGRAM, "PROGRAM"},
		{WRITE, "WRITE"},
		{INT, "INT"},
		{ END, "END" },
		{ IF, "IF" },
		{FLOAT, "FLOAT"},
		{STRING, "STRING"},
		{ REPEAT, "REPEAT" },
		
		
		{BEGIN, "BEGIN"},

		{ IDENT, "IDENT" },

		{ ICONST, "ICONST" },
		{ RCONST, "RCONST" },
		{ SCONST, "SCONST" },
		
		{ PLUS, "PLUS" },
		{ MINUS, "MINUS" },
		{ MULT, "MULT" },
		{ DIV, "DIV" },
		{REM, "REM"},
		{ ASSOP, "ASSOP" },
		{ LPAREN, "LPAREN" },
		{ RPAREN, "RPAREN" },
            
		{ COMMA, "COMMA" },
		{ EQUAL, "EQUAL" },
		{ GTHAN, "GTHAN" },
		
		{ SEMICOL, "SEMICOL" },
		
		{ ERR, "ERR" },

		{ DONE, "DONE" },
};

//Keywords mapping
static map<string,Token> kwmap = {
		{"PROGRAM", PROGRAM},
		{"WRITE", WRITE},
		{ "INT", INT},
		{ "FLOAT", FLOAT},
		{ "STRING", STRING},
		{ "REPEAT", REPEAT },
		{ "BEGIN", BEGIN },
		{"IF", IF},
		{ "END", END },
};
    
ostream& operator<<(ostream& out, const LexItem& tok) {
	Token tt = tok.GetToken();
	out << tokenPrint[ tt ];
	if( tt == IDENT || tt == ICONST || tt == SCONST || tt == RCONST || tt == ERR ) {
		out << "(" << tok.GetLexeme() << ")";
	}
	return out;
}

LexItem id_or_kw(const string& lexeme, int linenum)
{
	Token tt = IDENT;

	auto kIt = kwmap.find(lexeme);
	if( kIt != kwmap.end() )
		tt = kIt->second;

	return LexItem(tt, lexeme, linenum);
}



LexItem
getNextToken(istream& in, int& linenum)
{
	enum TokState { START, INID, INSTRING, ININT, INFLOAT, INCOMMENT } lexstate = START;
	string lexeme;
	char ch, nextch, nextchar;
	       
	//cout << "in getNestToken" << endl;
    while(in.get(ch)) {
    	//cout << "in while " << ch << endl;
		switch( lexstate ) {
		case START:
			if( ch == '\n' )
				linenum++;
                
			if( isspace(ch) )
				continue;

			lexeme = ch;

			if( isalpha(ch) ) {
				lexeme = toupper(ch);
				lexstate = INID;
			}
			else if( ch == '"' ) {
				lexstate = INSTRING;
				
			}
			
			else if( isdigit(ch) ) {
				lexstate = ININT;
			}
			else if( ch == '#' ) {
				lexstate = INCOMMENT;
			}	
						
			else {
				Token tt = ERR;
				switch( ch ) {
				case '+':
					tt = PLUS;
                    break;  
					
				case '-':
					tt = MINUS;
                    break; 
					
				case '*':
					tt = MULT;
					break;

				case '/':
					tt = DIV;
					break;
					
				case '%':
					tt = REM;
					break;
				case '=':
					nextchar = in.peek();
					if(nextchar == '='){
						in.get(ch);
						tt = EQUAL;
						break;
					}
					tt = ASSOP;
					break;
				case '(':
					tt = LPAREN;
					break;
				case ')':
					tt = RPAREN;
					break;
				
				case ';':
					tt = SEMICOL;
					break;
				case ',':
					tt = COMMA;
					break;
				case '>':
					tt = GTHAN;
					break;
				
				case '.':
					nextch = in.peek();
					if(isdigit(nextch)){
						lexstate = INFLOAT;
						continue;
					}
					else {
						lexeme += nextch;
						return LexItem(ERR, lexeme, linenum);
						cout << "Here what?" << endl;
					}
					
				}
				
				return LexItem(tt, lexeme, linenum);
			}
			break;

		case INID:
			if( isalpha(ch) || isdigit(ch) || ch == '_') {
				ch = toupper(ch);
				//cout << "inid " << ch << endl;
				lexeme += ch;
			}
			else {
				in.putback(ch);
				return id_or_kw(lexeme, linenum);
			}
			break;

		case INSTRING:
                          
			if( ch == '\n' ) {
				return LexItem(ERR, lexeme, linenum);
			}
			lexeme += ch;
			if( ch == '"' ) {
				lexeme = lexeme.substr(1, lexeme.length()-2);
				return LexItem(SCONST, lexeme, linenum);
			}
			break;

		case ININT:
			if( isdigit(ch) ) {
				lexeme += ch;
			}
			else if(ch == '.') {
				lexstate = INFLOAT;
				in.putback(ch);
				
			}
			else {
				in.putback(ch);
				return LexItem(ICONST, lexeme, linenum);
			}
			break;
		
		case INFLOAT:
			if( ch == '.' && isdigit(in.peek()) ) {
				lexeme += ch;
				
			}
			else if(isdigit(ch)){
				lexeme += ch;
			}
			else if(ch == '.' && !isdigit(in.peek())){
				lexeme += ch;
				return LexItem(ERR, lexeme, linenum);
			}
			else {
				in.putback(ch);
				return LexItem(RCONST, lexeme, linenum);
			}
			break;
		
					
		case INCOMMENT:
			if( ch == '\n' ) {
               ++linenum;
				lexstate = START;
			}
			break;
		}

	}//end of while loop

	if( in.eof() )
		return LexItem(DONE, "", linenum);
	return LexItem(ERR, "some strange I/O error", linenum);
}





