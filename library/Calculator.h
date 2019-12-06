#pragma once

#include <string>
#include <queue>
#include <utility>

using namespace std;

enum ElemType { Operation, Operand };

class Calculator
{
	string expr;

	const string operations = { '+', '-', '*', '/', '(', ')' };
	queue<pair<string, ElemType>> parsed;
public:
	Calculator(const string _expr)
	{
		if (!_expr.length()) throw "String length must be positive";
		expr = _expr;
	}

	void Parse();
	void ToPostfix();
	void Calculate();
	queue<pair<string, ElemType>>& getQ()
	{
		return parsed;
	}
};