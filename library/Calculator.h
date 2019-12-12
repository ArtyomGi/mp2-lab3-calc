#pragma once

#include <string>
#include <queue>
#include <utility>

using namespace std;

enum ElemType { Operation, Operand };

class Calculator
{
	//string expr;

	const string operations = { '+', '-', '*', '/', '(', ')' };
	const string priority2 = { '*', '/' };
	const string priority1 = { '+', '-' };
	const string priority_1 = { '(', ')' };

	
public:
	Calculator(const string _expr)
	{
		if (!_expr.length()) throw "String length must be positive";
		//expr = _expr;
	}

	queue<pair<string, ElemType>> Calculator::Parse(string expr);
	queue<pair<string, ElemType>> ToPostfix(queue<pair<string, ElemType>> parsed);
	//void Calculate();
	double Calculator::CalculateFromPostfix(queue<pair<string, ElemType>> parsedPostf);
	int getPriority(string operation);
	/*queue<pair<string, ElemType>>& getQ()
	{
		return parsed;
	}*/
};