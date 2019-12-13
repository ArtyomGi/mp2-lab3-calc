#include "Calculator.h"
#include "Stack.h"
#include "cmath"

vector<double> Calculator::Calculate(int PrintQ = 0)
{
	vector<double> res;
	try
	{
		queue<pair<string, ElemType> > parsed = Parse(expr);

		if (PrintQ)
		{
			queue<pair<string, ElemType> > parsed2 = parsed;
			while (!parsed2.empty())
			{
				cout << parsed2.front().first << endl;
				parsed2.pop();
			}
		}

		queue<pair<string, ElemType> > postfix = ToPostfix(parsed);

		if (PrintQ)
		{
			queue<pair<string, ElemType> > parsed2 = postfix;
			while (!parsed2.empty())
			{
				cout << parsed2.front().first << ' ';
				parsed2.pop();
			}
			cout << endl;
		}
		res = CalculateFromPostfix(postfix);
	}
	catch (const char* error)
	{
		cout << "Error has occured!" << endl;
		cout << "Error: " << error << endl;
	}
	catch (...)
	{
		cout << "Unexpectable error has occured!" << endl;
	}
	
	return res;
}

queue<pair<string, ElemType>> Calculator::ToPostfix(queue<pair<string, ElemType>> parsed)
{
	Stack<pair<string, ElemType>> st(parsed.size());
	queue<pair<string, ElemType>> symbols = parsed;
	queue<pair<string, ElemType>> result;
	ElemType last = symbols.front().second;
	//int minusNumber = 0;
	

	//checking for minus
	
	//queue<pair<string, ElemType>> copyparsed = parsed;
	//
	//while (!copyparsed.empty())
	//{
	//	if(copyparsed.front().first.back() == '-' && )
	//	last = copyparsed.front().second;
	//	copyparsed.pop();
	//}
	/////////////////

	while (!symbols.empty())
	{
		pair<string, ElemType> current = symbols.front();
		if (current.second == Operand || current.second == Variable)
			result.push(current);
		else if (current.second == Delimiter)
		{
			if (!st.isEmpty())
			{
				while (!st.isEmpty())
				{
					if (st.front().first.back() == ')' || st.front().first.back() == '(') throw "Unnecessary brackets";
					result.push({ st.pop().first, Operation });
					//result += st.pop().first;
				}
			}
			result.push({ current.first, Delimiter });
		}
		else
		{
			if (current.first.back() == ')')
			{
				if (st.isEmpty()) throw "Current symbol is ), but stack is empty";
				while (st.front().first.back() != '(')
				{
					result.push({ st.pop().first , Operation });
					//result += st.pop().first;
					if (st.isEmpty()) throw "( isn't found";
				}
				st.pop();
			}
			else if (st.isEmpty()) st.push(current);
			else if (current.first.back() == '(')
				st.push(current);
			else
			{
				while (!st.isEmpty() && getPriority(st.front().first) >= getPriority(current.first))
					result.push({ st.pop().first, Operation });
					//result += st.pop().first;
				st.push(current);
			}
		}
		last = current.second;
		symbols.pop();
		
	}
	if (!st.isEmpty())
	{
		while (!st.isEmpty())
		{
			if (st.front().first.back() == ')' || st.front().first.back() == '(') throw "Unnecessary brackets";
			result.push({ st.pop().first , Operation });
			//result += st.pop().first;
		}
	}
	return result;
}

queue<pair<string, ElemType>> Calculator::Parse(string expr)
{
	int state = 0;
	string tmp;

	queue<pair<string, ElemType>> parsed;

	for (string::const_iterator i = expr.cbegin(); i != expr.cend(); i++)
	{
		switch (state)
		{
		case 0:
			if (*i == '-' && (parsed.empty() || parsed.back().second == Operation || parsed.back().second == Delimiter))
			{
				tmp = *i;
				state = 1;
			}
			else if (*i == ';')
			{
				parsed.push({ string(1, *i), Delimiter });
			}
			else if (operations.find(*i) != string::npos) // + else
			{
				parsed.push({ string(1, *i), Operation });
			}
			else if (*i == ' ')
			{
				break;
			}
			else
			{
				tmp = *i;
				state = 1;
			}
			break;
		case 1:
			if (operations.find(*i) != string::npos)
			{
				if (tmp.length())
				{
					//throw "No operand before operation";
					if(tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "sqrt")
						parsed.push({ tmp, Operation });
					else if(!isNumber(tmp))
						parsed.push({ tmp, Variable });
					else
						parsed.push({ tmp, Operand });
					tmp.clear();
				}
				parsed.push({ string(1, *i), Operation });
				state = 0;
			}
			else if (*i == ';')
			{
				if (tmp.length())
				{
					//throw "No operand before operation";
					if (tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "sqrt")
						parsed.push({ tmp, Operation });
					else if (!isNumber(tmp))
						parsed.push({ tmp, Variable });
					else
						parsed.push({ tmp, Operand });
					tmp.clear();
				}
				parsed.push({ string(1, *i), Delimiter });
				state = 0;
			}
			else if (*i == ' ')
			{
				//cout << "case 1 : " << *i << endl;
				if (tmp.length())
				{
					//throw "No operand before operation";

					if (tmp == "sin" || tmp == "cos" || tmp == "tan" || tmp == "sqrt")
						parsed.push({ tmp, Operation });
					else if (!isNumber(tmp))
						parsed.push({ tmp, Variable });
					else
						parsed.push({ tmp, Operand });
					tmp.clear();
				}
				//tmp.clear();
				state = 0;
				//break;
			}
			else
			{
				tmp += *i;
			}
			break;
		}
	}

	if (tmp.size())
	{
		if (!isNumber(tmp))
			parsed.push({ tmp, Variable });
		else
			parsed.push({ tmp, Operand });
	}

	// parsed.push({ tmp, Operand });

	return parsed;
}

vector<double> Calculator::CalculateFromPostfix(queue<pair<string, ElemType>> parsedPostf)
{
	vector<double> results;
	vector<pair<string, double>> vars;
	//result = result;
	bool ok = false;
	Stack<pair<string, ElemType>> st(parsedPostf.size());
	double op1, op2;
	while (!parsedPostf.empty())
	{
		if (parsedPostf.front().second == Operand || parsedPostf.front().second == Variable)
			st.push(parsedPostf.front());
		else if (parsedPostf.front().second == Delimiter)
		{
			if (st.isEmpty()) throw "Mismatch of operators and operands (no more operands are left)";
			if (st.size() > 1) throw "Mismatch of operators and operands (2 or more operands are left)";
			
			if (st.front().second == Variable)
			{
				ok = false;

				for (auto i = vars.begin(); i < vars.end(); i++)
				{
					if (i->first == st.front().first)
					{
						results.push_back(i->second);
						ok = true;
						break;
					}
				}

				if (!ok) throw "Can't find variable (Empty)";
				st.pop();
			}
			else results.push_back(stod(st.pop().first.c_str()));

			//results.push_back(stod(st.pop().first.c_str()));
		}
		else
		{
			switch (parsedPostf.front().first.back())
			{
			case '=':
				if (st.size() < 2) throw "No operands for operator =";
				op2 = stod(st.pop().first.c_str());
				if (st.front().second != Variable) throw "Left value must be variable";

				ok = false;

				for (auto i = vars.begin(); i < vars.end(); i++)
				{
					if (i->first == st.front().first)
					{
						i->second = op2;
						ok = true;
						break;
					}
				}

				if (!ok) vars.push_back({ st.front().first, op2 });

				break;
			case '+':
			case '-':
			case '*':
			case '/':
				if (st.size() < 2) throw "No operands for operator +";

				if (st.front().second == Variable)
				{
					ok = false;

					for (auto i = vars.begin(); i < vars.end(); i++)
					{
						if (i->first == st.front().first)
						{
							op2 = i->second;
							ok = true;
							break;
						}
					}

					if (!ok) throw "Can't find variable (2)";
					st.pop();
				}
				else op2 = stod(st.pop().first.c_str());

				if (st.front().second == Variable)
				{
					ok = false;

					for (auto i = vars.begin(); i < vars.end(); i++)
					{
						if (i->first == st.front().first)
						{
							op1 = i->second;
							ok = true;
							break;
						}
					}

					if (!ok) throw "Can't find variable (1)";
					st.pop();
				}
				else op1 = stod(st.pop().first.c_str());

				switch (parsedPostf.front().first.back())
				{
				case '+':
					st.push({ to_string(op1 + op2), Operand });
					break;
				case '-':
					st.push({ to_string(op1 - op2), Operand });
					break;
				case '*':
					st.push({ to_string(op1 * op2), Operand });
					break;
				case '/':
					st.push({ to_string(op1 / op2), Operand });
					break;
				}

				
				break;
			/*case '-':
				if (st.size() < 2) throw "No operands for operator -";
				op2 = stod(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(op1 - op2), Operand });
				break;
			case '*':
				if (st.size() < 2) throw "No operands for operator *";
				op2 = stod(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(op1 * op2), Operand });
				break;
			case '/':
				if (st.size() < 2) throw "No operands for operator /";
				op2 = stod(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(op1 / op2), Operand });
				break;*/
			}
			if (parsedPostf.front().first == "sin")
			{
				if (st.size() < 1) throw "No operands for operator sin";
				//op2 = atoi(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(sin(op1)), Operand });
			}
			else if (parsedPostf.front().first == "cos")
			{
				if (st.size() < 1) throw "No operands for operator cos";
				//op2 = atoi(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(cos(op1)), Operand });
			}
			else if (parsedPostf.front().first == "tan")
			{
				if (st.size() < 1) throw "No operands for operator tan";
				//op2 = atoi(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(tan(op1)), Operand });
			}
			else if (parsedPostf.front().first == "sqrt")
			{
				if (st.size() < 1) throw "No operands for operator sqrt";
				//op2 = atoi(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(sqrt(op1)), Operand });
			}
		}

		parsedPostf.pop();
	}

	if (st.size() > 1) throw "Mismatch of operators and operands (2 or more operands are left)";
	if (!st.isEmpty())
	{
		if (st.front().second == Variable)
		{
			ok = false;

			for (auto i = vars.begin(); i < vars.end(); i++)
			{
				if (i->first == st.front().first)
				{
					results.push_back(i->second);
					ok = true;
					break;
				}
			}

			if (!ok) throw "Can't find variable (Empty)";
			st.pop();
		}
		else results.push_back(stod(st.pop().first.c_str()));
	}

	return results;//stod(st.pop().first.c_str());
}

int Calculator::isOperator(string str)
{
	if (str == "sin" || str == "cos" || str == "tan" || str == "sqrt")
		return true;
	if (operations.find(str) != string::npos)
		return true;
	return false;
}

int Calculator::isNumber(string str)
{
	//if(str[0] == '-') str.erase(str.begin(), str.begin() + 1);
	for (auto i = str.begin(); i < str.end(); i++)
	{
		if (*i == '-') continue;
		if (*i < '0' || *i > '9') return false;
	}
	return true;
}

int Calculator::getPriority(string operation)
{
	if (operation == "sin" || operation == "cos" || operation == "tan" || operation == "sqrt")
		return 3;
	else if (priority2.find(operation) != string::npos)
		return 2;
	else if (priority1.find(operation) != string::npos)
		return 1;
	else if (priority0.find(operation) != string::npos)
		return 0;
	else if (priority_1.find(operation) != string::npos)
		return -1;
	else throw "Not an operation";
}