#pragma once
#include <string>
#include <list>
#include <utility>
using namespace std;
class Syntax
{
private:
	list<string> Syn_out = {""};
	list<pair<string, string>>::iterator it_lex;
	bool CompUnit();
	bool Decl();
	bool ConstDecl();
	bool BType();
	bool ConstDef();
	bool ConstInitVal();
	bool VarDecl();
	bool VarDef();
	bool InitVal();
	bool FuncDef();
	bool MainFuncDef();
	bool FuncType();
	bool FuncFParams();
	bool FuncFParam();
	bool Block();
	bool BlockItem();
	bool Stmt();
	bool Exp();
	bool Cond();
	bool LVal();
	bool PrimaryExp();
	bool Number();
	bool UnaryExp();
	bool UnaryOp();
	bool FuncRParams();
	bool MulExp();
	bool _MulExp();
	bool AddExp();
	bool _AddExp();
	bool RelExp();
	bool _RelExp();
	bool EqExp();
	bool _EqExp();
	bool LAndExp();
	bool _LAndExp();
	bool LOrExp();
	bool _LOrExp();
	bool ConstExp();
public:
	void analysis(list<pair<string, string>> lex_out);
	list<string> getSyn_out();
};

