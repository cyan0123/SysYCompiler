#pragma once
#include <string>
#include <map>
#include <list>
#include <set>
#include <utility>
using namespace std;

class Lex
{
private:
	map<string, string> category_code = {
		make_pair("Ident", "IDENFR"),
		make_pair("IntConst", "INTCON"),
		make_pair("FormatString", "STRCON"),
		make_pair("main", "MAINTK"),
		make_pair("const", "CONSTTK"),
		make_pair("int", "INTTK"),
		make_pair("break", "BREAKTK"),
		make_pair("continue", "CONTINUETK"),
		make_pair("if", "IFTK"),
		make_pair("else", "ELSETK"),
		make_pair("!", "NOT"),
		make_pair("&&", "AND"),
		make_pair("||", "OR"),
		make_pair("while", "WHILETK"),
		make_pair("getint", "GETINTTK"),
		make_pair("printf", "PRINTFTK"),
		make_pair("return", "RETURNTK"),
		make_pair("+", "PLUS"),
		make_pair("-", "MINU"),
		make_pair("void", "VOIDTK"),
		make_pair("*", "MULT"),
		make_pair("/", "DIV"),
		make_pair("%", "MOD"),
		make_pair("<", "LSS"),
		make_pair("<=", "LEQ"),
		make_pair(">", "GRE"),
		make_pair(">=", "GEQ"),
		make_pair("==", "EQL"),
		make_pair("!=", "NEQ"),
		make_pair("=", "ASSIGN"),
		make_pair(";", "SEMICN"),
		make_pair(",", "COMMA"),
		make_pair("(", "LPARENT"),
		make_pair(")", "RPARENT"),
		make_pair("[", "LBRACK"),
		make_pair("]", "RBRACK"),
		make_pair("{", "LBRACE"),
		make_pair("}", "RBRACE")
	};
	list<pair<string, string>> lex_out;
	int state = 0;
public:
	void analysis(string str);
	list<pair<string, string>> getLex_out();
};

