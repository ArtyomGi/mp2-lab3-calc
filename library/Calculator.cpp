#include "Calculator.h"
#include "Stack.h"

void Calculator::ToPostfix()
{
	Stack<> s()
}

void Calculator::Parse()
{
	int state = 0;
	string tmp;


	for (string::const_iterator i = expr.cbegin(); i != expr.cend(); i++)
	{
		switch (state)
		{
		case 0:
			if (operations.find(*i) != string::npos)
			{
				parsed.push({ string(1, *i), Operation });
			}
			//else if (*i == ' ')
			else
			{
				tmp = *i;
				state = 1;
			}
			break;
		case 1:
			if (operations.find(*i) != string::npos)
			{
				//cout << "case 1: " << *i << endl;
				if (tmp.length())
				{
					//throw "No operand before operation";
					parsed.push({ tmp, Operand });
					tmp.clear();
				}
				parsed.push({ string(1, *i), Operation });
				state = 0;
			}
			else if (*i == ' ')
			{
				//cout << "case 1 : " << *i << endl;
				if (tmp.length())
				{
					//throw "No operand before operation";
					parsed.push({ tmp, Operand });
					tmp.clear();
				}
				//tmp.clear();
				state = 1;
				//break;
			}
			else
			{
				tmp += *i;
			}
			break;
		}
		/*if (operations.find(*i) != std::string::npos)
		{

		}*/
	}
}