#include "Calculator.h"
#include "Stack.h"
#include "cmath"

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
		if (current.second == Operand)
			result.push({ current.first, Operand });
		else
		{
			/*if (last == Operation && current.first.back() == '-')
			{
				//symbols.pop();
				//symbols.push({ string(1, '0'), Operand });
				//symbols.push({ string(1, '-'), Operation });
				//symbols.
			}*/
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
	int lastState = 0;

	for (string::const_iterator i = expr.cbegin(); i != expr.cend(); i++)
	{
		//lastState = state;
		switch (state)
		{
		case 0:
			if (*i == '-' && (parsed.empty() || parsed.back().second == Operation))
			{
				tmp = *i;
				state = 1;
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
				//cout << "case 1: " << *i << endl;
				if (tmp.length())
				{
					//throw "No operand before operation";
					if(tmp == "sin") parsed.push({ tmp, Operation });
					else parsed.push({ tmp, Operand });
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

					if (tmp == "sin") parsed.push({ tmp, Operation });
					else parsed.push({ tmp, Operand });
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
		lastState = state;
		/*if (operations.find(*i) != std::string::npos)
		{

		}*/
	}

	if (tmp.size()) parsed.push({ tmp, Operand });

	return parsed;
}

double Calculator::CalculateFromPostfix(queue<pair<string, ElemType>> parsedPostf)
{
	//result = result;
	Stack<pair<string, ElemType>> st(parsedPostf.size());
	double op1, op2;
	while (!parsedPostf.empty())
	{
		if (parsedPostf.front().second == Operand)
			st.push(parsedPostf.front());
		else
		{
			switch (parsedPostf.front().first.back())
			{
			case '+':
				if (st.size() < 2) throw "No operands for operator +";
				op2 = stod(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(op1 + op2), Operand });
				break;
			case '-':
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
				break;
			}
			if (parsedPostf.front().first == "sin")
			{
				if (st.size() < 1) throw "No operands for operator sin";
				//op2 = atoi(st.pop().first.c_str());
				op1 = stod(st.pop().first.c_str());

				st.push({ to_string(sin(op1)), Operand });
				//break;
			}
		}

		parsedPostf.pop();
	}
	if (st.isEmpty()) throw "Error";
	return stod(st.pop().first.c_str());
}

int Calculator::getPriority(string operation)
{
	if (operation == "sin")
		return 3;
	else if (priority2.find(operation) != string::npos)
		return 2;
	else if (priority1.find(operation) != string::npos)
		return 1;
	else if (priority_1.find(operation) != string::npos)
		return -1;
	else throw "Not an operation";
}