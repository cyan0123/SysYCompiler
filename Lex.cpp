#include "Lex.h"

void Lex::analysis(string str)
{
	if (str == "") return;
	int state = 0;
	string tmp = "";
	for (int f = 0; f <= str.length();)
	{
		switch (state)
		{
		case 0:
			tmp = "";
			tmp += str[f];
			if (str[f] == '"')
			{
				state = 1;
			}
			else if ((str[f] >= 'A' && str[f] <= 'Z') || 
				(str[f] >= 'a' && str[f] <= 'z'))
			{
				state = 3;
			}
			else if (str[f] >= '0' && str[f] <= '9')
			{
				state = 8;
			}
			else if (str[f] == ' ' || str[f] == '\t')
			{
				state = 0;
			}
			else
			{
				state = 7;
			}
			f++;
			break;
		case 1:
			tmp += str[f];
			if (str[f] == '"')
			{
				state = 2;
			}
			f++;
			break;
		case 2:
			lex_out.push_back(make_pair(category_code["FormatString"], tmp));
			state = 0;
			break;
		case 3:
			if ((str[f] >= 'A' && str[f] <= 'Z') ||
				(str[f] >= 'a' && str[f] <= 'z'))
			{
				state = 3;
				tmp += str[f];
				f++;
			}
			else
			{
				state = 4;
			}
			break;
		case 4:
			if (category_code.find(tmp) != category_code.end())
			{
				state = 5;
			}
			else
			{
				state = 6;
			}
			break;
		case 5:
			lex_out.push_back(make_pair(category_code[tmp], tmp));
			state = 0;
			break;
		case 6:
			lex_out.push_back(make_pair(category_code["Ident"], tmp));
			state = 0;
			break;
		case 7:
			if (category_code.find(tmp) != category_code.end())
			{
				lex_out.push_back(make_pair(category_code[tmp], tmp));
				state = 0;
			}
			break;
		case 8:
			if (str[f] >= '0' && str[f] <= '9')
			{
				state = 8;
				tmp += str[f];
				f++;
			}
			else
			{
				state = 9;
			}
			break;
		case 9:
			lex_out.push_back(make_pair(category_code["IntConst"], tmp));
			state = 0;
			break;
		default:
			break;
		}
	}
}

list<pair<string, string>> Lex::getLex_out()
{
	return lex_out;
}
