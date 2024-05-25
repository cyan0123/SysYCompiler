#include "Syntax.h"
#define lexlist_it list<pair<string, string>>::iterator 
#define synlist_it list<string>::iterator

void Syntax::analysis(list<pair<string, string>> lex_out)
{
	it_lex = lex_out.begin();
	CompUnit();
	Syn_out.pop_front();
}

list<string> Syntax::getSyn_out()
{
	return Syn_out;
}

bool Syntax::CompUnit()
{
	while (Decl());
	while (FuncDef());
	if (MainFuncDef())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::Decl()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (ConstDecl() || VarDecl())
	{
		//Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::ConstDecl()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->second == "const")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (BType() && ConstDef())
		{
			while (it_lex->second == ",")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				if (!ConstDef())
				{
					it_lex = tmp;
					Syn_out.erase(++tmp_syn, Syn_out.end());
					return false;
				}
			}
			if (it_lex->second == ";")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				Syn_out.push_back("<" + string(__func__) + ">");
				return true;
			}
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::BType()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->second == "int")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		//Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::ConstDef()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->first == "IDENFR")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		while (it_lex->second == "[")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (ConstExp())
			{
				if (it_lex->second == "]")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
				}
				else
				{
					it_lex = tmp;
					Syn_out.erase(++tmp_syn, Syn_out.end());
					return false;
				}
			}
			else
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
		}
		if (it_lex->second == "=")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (ConstInitVal())
			{
				Syn_out.push_back("<" + string(__func__) + ">");
				return true;
			}
		}
		
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::ConstInitVal()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (ConstExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (it_lex->second == "{")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (ConstInitVal())
		{
			while (it_lex->second == ",")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				if (!ConstInitVal())
				{
					it_lex = tmp;
					Syn_out.erase(++tmp_syn, Syn_out.end());
					return false;
				}
			}
		}
		if (it_lex->second == "}")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::VarDecl()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (BType() && VarDef())
	{
		while (it_lex->second == ",")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!VarDef())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
		}
		if (it_lex->second == ";")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::VarDef()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->first == "IDENFR")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		while (it_lex->second == "[")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (ConstExp())
			{
				if (it_lex->second == "]")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
				}
				else
				{
					it_lex = tmp;
					Syn_out.erase(++tmp_syn, Syn_out.end());
					return false;
				}
			}
			else
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
		}
		if (it_lex->second == "=")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!InitVal())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
		}
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::InitVal()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (Exp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (it_lex->second == "{")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (InitVal())
		{
			while (it_lex->second == ",")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				if (!InitVal())
				{
					it_lex = tmp;
					Syn_out.erase(++tmp_syn, Syn_out.end());
					return false;
				}
			}
		}
		if (it_lex->second == "}")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::FuncDef()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (FuncType())
	{
		if (it_lex->first == "IDENFR")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (it_lex->second == "(")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				if (FuncFParams());
				if (it_lex->second == ")")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
					if (Block())
					{
						Syn_out.push_back("<" + string(__func__) + ">");
						return true;
					}
				}
			}
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::MainFuncDef()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->second == "int")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (it_lex->second == "main")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (it_lex->second == "(")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				if (it_lex->second == ")")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
					if (Block())
					{
						Syn_out.push_back("<" + string(__func__) + ">");
						return true;
					}
				}
			}
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::FuncType()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->second == "int")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (it_lex->second == "void")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::FuncFParams()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (FuncFParam())
	{
		while (it_lex->second == ",")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!FuncFParam())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
		}
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::FuncFParam()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (BType())
	{
		if (it_lex->first == "IDENFR")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (it_lex->second == "[")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				if (it_lex->second == "]")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
					while (it_lex->second == "[")
					{
						Syn_out.push_back(it_lex->first + " " + it_lex->second);
						it_lex++;
						if (ConstExp())
						{
							if (it_lex->second == "]")
							{
								Syn_out.push_back(it_lex->first + " " + it_lex->second);
								it_lex++;
							}
							else
							{
								it_lex = tmp;
								Syn_out.erase(++tmp_syn, Syn_out.end());
								return false;
							}
						}
						else
						{
							it_lex = tmp;
							Syn_out.erase(++tmp_syn, Syn_out.end());
							return false;
						}
					}
				}
				else
				{
					it_lex = tmp;
					Syn_out.erase(++tmp_syn, Syn_out.end());
					return false;
				}
			}
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::Block()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->second == "{")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		while (BlockItem());
		if (it_lex->second == "}")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::BlockItem()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (Decl() || Stmt())
	{
		//Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::Stmt()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->first == "IDENFR")
	{
		if (LVal())
		{
			if (it_lex->second == "=")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				if (Exp())
				{
					if (it_lex->second == ";")
					{
						Syn_out.push_back(it_lex->first + " " + it_lex->second);
						it_lex++;
						Syn_out.push_back("<" + string(__func__) + ">");
						return true;
					}
					else
					{
						it_lex = tmp;
						synlist_it tmp_tmp_syn = tmp_syn;
						Syn_out.erase(++tmp_syn, Syn_out.end());
						tmp_syn = tmp_tmp_syn;
					}
				}
				else if (it_lex->second == "getint")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
					if (it_lex->second == "(")
					{
						Syn_out.push_back(it_lex->first + " " + it_lex->second);
						it_lex++;
						if (it_lex->second == ")")
						{
							Syn_out.push_back(it_lex->first + " " + it_lex->second);
							it_lex++;
							if (it_lex->second == ";")
							{
								Syn_out.push_back(it_lex->first + " " + it_lex->second);
								it_lex++;
								Syn_out.push_back("<" + string(__func__) + ">");
								return true;
							}
							else
							{
								it_lex = tmp;
								synlist_it tmp_tmp_syn = tmp_syn;
								Syn_out.erase(++tmp_syn, Syn_out.end());
								tmp_syn = tmp_tmp_syn;
							}
						}
						else
						{
							it_lex = tmp;
							synlist_it tmp_tmp_syn = tmp_syn;
							Syn_out.erase(++tmp_syn, Syn_out.end());
							tmp_syn = tmp_tmp_syn;
						}
					}
					else
					{
						it_lex = tmp;
						synlist_it tmp_tmp_syn = tmp_syn;
						Syn_out.erase(++tmp_syn, Syn_out.end());
						tmp_syn = tmp_tmp_syn;
					}
				}
				else
				{
					it_lex = tmp;
					synlist_it tmp_tmp_syn = tmp_syn;
					Syn_out.erase(++tmp_syn, Syn_out.end());
					tmp_syn = tmp_tmp_syn;
				}
			}
			else
			{
				it_lex = tmp;
				synlist_it tmp_tmp_syn = tmp_syn;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				tmp_syn = tmp_tmp_syn;
			}
		}
		else
		{
			it_lex = tmp;
			synlist_it tmp_tmp_syn = tmp_syn;
			Syn_out.erase(++tmp_syn, Syn_out.end());
			tmp_syn = tmp_tmp_syn;
		}
		if (Exp());
		if (it_lex->second == ";")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	else if (Block())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (it_lex->second == "if")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (it_lex->second == "(")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (Cond())
			{
				if (it_lex->second == ")")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
					if (Stmt())
					{
						if (it_lex->second == "else")
						{
							Syn_out.push_back(it_lex->first + " " + it_lex->second);
							it_lex++;
							if (!Stmt())
							{
								it_lex = tmp;
								Syn_out.erase(++tmp_syn, Syn_out.end());
								return false;
							}
						}
						Syn_out.push_back("<" + string(__func__) + ">");
						return true;
					}
				}
			}
		}
	}
	else if (it_lex->second == "while")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (it_lex->second == "(")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (Cond())
			{
				if (it_lex->second == ")")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
					if (Stmt())
					{
						Syn_out.push_back("<" + string(__func__) + ">");
						return true;
					}
				}
			}
		}
	}
	else if (it_lex->second == "break")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (it_lex->second == ";")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	else if (it_lex->second == "continue")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (it_lex->second == ";")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	else if (it_lex->second == "return")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (Exp());
		if (it_lex->second == ";")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	else if (it_lex->second == "printf")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (it_lex->second == "(")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (it_lex->first == "STRCON")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				while (it_lex->second == ",")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
					if (!Exp())
					{
						it_lex = tmp;
						Syn_out.erase(++tmp_syn, Syn_out.end());
						return false;
					}
				}
				if (it_lex->second == ")")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
					if (it_lex->second == ";")
					{
						Syn_out.push_back(it_lex->first + " " + it_lex->second);
						it_lex++;
						Syn_out.push_back("<" + string(__func__) + ">");
						return true;
					}
				}
			}
		}
	}
	else
	{
		if (Exp());
		if (it_lex->second == ";")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::Exp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (AddExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::Cond()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (LOrExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::LVal()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->first == "IDENFR")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		while (it_lex->second == "[")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (Exp())
			{
				if (it_lex->second == "]")
				{
					Syn_out.push_back(it_lex->first + " " + it_lex->second);
					it_lex++;
				}
				else
				{
					it_lex = tmp;
					Syn_out.erase(++tmp_syn, Syn_out.end());
					return false;
				}
			}
			else
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
		}
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::PrimaryExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->second == "(")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (Exp())
		{
			if (it_lex->second == ")")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				Syn_out.push_back("<" + string(__func__) + ">");
				return true;
			}
		}
	}
	else if (LVal())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (Number())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::Number()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->first == "INTCON")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::UnaryExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->first == "IDENFR")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (it_lex->second == "(")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (FuncRParams());
			if (it_lex->second == ")")
			{
				Syn_out.push_back(it_lex->first + " " + it_lex->second);
				it_lex++;
				Syn_out.push_back("<" + string(__func__) + ">");
				return true;
			}
			else
			{
				it_lex = tmp;
				synlist_it tmp_tmp_syn = tmp_syn;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				tmp_syn = tmp_tmp_syn;
			}
		}
		else
		{
			it_lex = tmp;
			synlist_it tmp_tmp_syn = tmp_syn;
			Syn_out.erase(++tmp_syn, Syn_out.end());
			tmp_syn = tmp_tmp_syn;
		}
		if (PrimaryExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	else if (PrimaryExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (UnaryOp())
	{
		if (UnaryExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::UnaryOp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (it_lex->second == "+")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (it_lex->second == "-")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (it_lex->second == "!")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::FuncRParams()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (Exp())
	{
		while (it_lex->second == ",")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!Exp())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
		}
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::MulExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (UnaryExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		while (it_lex->second == "*" || it_lex->second == "/" || it_lex->second == "%")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!UnaryExp())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
			Syn_out.push_back("<" + string(__func__) + ">");
		}
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::AddExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (MulExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		while (it_lex->second == "+" || it_lex->second == "-")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!MulExp())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
			Syn_out.push_back("<" + string(__func__) + ">");
		}
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::RelExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (AddExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		while (it_lex->second == ">" || it_lex->second == "<" ||
			it_lex->second == "<=" || it_lex->second == ">=")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!AddExp())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
			Syn_out.push_back("<" + string(__func__) + ">");
		}
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::EqExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (RelExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		while (it_lex->second == "==" || it_lex->second == "!=")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!RelExp())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
			Syn_out.push_back("<" + string(__func__) + ">");
		}
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::LAndExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (EqExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		while (it_lex->second == "&&")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!EqExp())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
			Syn_out.push_back("<" + string(__func__) + ">");
		}
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::LOrExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (LAndExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		while (it_lex->second == "||")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!LAndExp())
			{
				it_lex = tmp;
				Syn_out.erase(++tmp_syn, Syn_out.end());
				return false;
			}
			Syn_out.push_back("<" + string(__func__) + ">");
		}
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}

bool Syntax::ConstExp()
{
	lexlist_it tmp = it_lex;
	synlist_it tmp_syn = Syn_out.end();
	tmp_syn--;
	if (AddExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	it_lex = tmp;
	Syn_out.erase(++tmp_syn, Syn_out.end());
	return false;
}
