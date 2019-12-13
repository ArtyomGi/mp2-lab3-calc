#pragma once

#include <string>
#include <queue>
#include <utility>

using namespace std;

enum ElemType { Operation, Operand, Delimiter, Variable };

class Calculator
{
	string expr;

	const string operations = { '+', '-', '*', '/', '(', ')', '=' };
	const string priority2 = { '*', '/' };
	const string priority1 = { '+', '-' };
	const string priority0 = { '=' };
	const string priority_1 = { '(', ')' };
	//const char func[] = { "sin", "cos" };

	
public:
	Calculator(const string _expr)
	{
		if (!_expr.length()) throw "String length must be positive";
		expr = _expr;
	}

	queue<pair<string, ElemType>> Calculator::Parse(string expr);
	queue<pair<string, ElemType>> ToPostfix(queue<pair<string, ElemType>> parsed);
	vector<double> CalculateFromPostfix(queue<pair<string, ElemType>> parsedPostf);
	vector<double> Calculate(int);
	int getPriority(string operation);
	int isOperator(string operation);
	int isNumber(string str);
	/*queue<pair<string, ElemType>>& getQ()
	{
		return parsed;
	}*/
};