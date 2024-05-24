#include "Syntax.h"

void Syntax::analysis(list<pair<string, string>> lex_out)
{
	it_lex = lex_out.begin();
	CompUnit();
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
	if (ConstDecl() || VarDecl())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::ConstDecl()
{
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
					return false;
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
	return false;
}

bool Syntax::BType()
{
	if (it_lex->second == "int")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::ConstDef()
{
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
					return false;
				}
			}
			else
			{
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
	return false;
}

bool Syntax::ConstInitVal()
{
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
	return false;
}

bool Syntax::VarDecl()
{
	if (BType() && VarDef())
	{
		while (it_lex->second == ",")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!VarDef())
				return false;
		}
		if (it_lex->second == ";")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::VarDef()
{
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
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		if (it_lex->second == "=")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!InitVal())
			{
				return false;
			}
		}
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::InitVal()
{
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
	return false;
}

bool Syntax::FuncDef()
{
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
	return false;
}

bool Syntax::MainFuncDef()
{
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
	return false;
}

bool Syntax::FuncType()
{
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
	return false;
}

bool Syntax::FuncFParams()
{
	if (FuncFParam())
	{
		while (it_lex->second == ",")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!FuncFParam())
			{
				return false;
			}
		}
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::FuncFParam()
{
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
						if (!ConstExp())
						{
							return false;
						}
					}
				}
				else
				{
					return false;
				}
			}
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::Block()
{
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
	return false;
}

bool Syntax::BlockItem()
{
	if (Decl() || Stmt())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::Stmt()
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
					}
				}
			}
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
	return false;
}

bool Syntax::Exp()
{
	if (AddExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::Cond()
{
	if (LOrExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::LVal()
{
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
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::PrimaryExp()
{
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
	return false;
}

bool Syntax::Number()
{
	if (it_lex->first == "INTCON")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::UnaryExp()
{
	if (PrimaryExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	else if (it_lex->first == "IDENFR")
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
		}
	}
	else if (UnaryOp())
	{
		if (UnaryExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::UnaryOp()
{
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
	return false;
}

bool Syntax::FuncRParams()
{
	if (Exp())
	{
		while (it_lex->second == ",")
		{
			Syn_out.push_back(it_lex->first + " " + it_lex->second);
			it_lex++;
			if (!Exp())
			{
				return false;
			}
		}
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

bool Syntax::MulExp()
{
	if (UnaryExp())
	{
		if (_MulExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::_MulExp()
{
	while (it_lex->second == "*" || it_lex->first == "/" || it_lex->first == "%")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (!UnaryExp())
		{
			return false;
		}
	}
	return true;
}

bool Syntax::AddExp()
{
	if (MulExp())
	{
		if (_AddExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::_AddExp()
{
	while (it_lex->second == "+" || it_lex->first == "-")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (!MulExp())
		{
			return false;
		}
	}
	return true;
}

bool Syntax::RelExp()
{
	if (AddExp())
	{
		if (_RelExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::_RelExp()
{
	while (it_lex->second == ">" || it_lex->first == "<" || 
		it_lex->first == "<=" || it_lex->first == ">=")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (!AddExp())
		{
			return false;
		}
	}
	return true;
}

bool Syntax::EqExp()
{
	if (RelExp())
	{
		if (_EqExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::_EqExp()
{
	while (it_lex->second == "==" || it_lex->first == "!=")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (!RelExp())
		{
			return false;
		}
	}
	return true;
}

bool Syntax::LAndExp()
{
	if (EqExp())
	{
		if (_LAndExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::_LAndExp()
{
	while (it_lex->second == "&&")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (!EqExp())
		{
			return false;
		}
	}
	return true;
}

bool Syntax::LOrExp()
{
	if (LAndExp())
	{
		if (_LOrExp())
		{
			Syn_out.push_back("<" + string(__func__) + ">");
			return true;
		}
	}
	return false;
}

bool Syntax::_LOrExp()
{
	while (it_lex->second == "||")
	{
		Syn_out.push_back(it_lex->first + " " + it_lex->second);
		it_lex++;
		if (!LAndExp())
		{
			return false;
		}
	}
	return true;
}

bool Syntax::ConstExp()
{
	if (AddExp())
	{
		Syn_out.push_back("<" + string(__func__) + ">");
		return true;
	}
	return false;
}

