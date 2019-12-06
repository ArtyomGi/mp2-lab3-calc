#pragma once

#include <string>
#include "Stack.h"
#include <utility>

using namespace std;

class Calculator
{
	string expr;
	enum ElemType { Operation, Operand };
	const string operations = { '+', '-', '*', '/', '(', ')' };
	Stack<pair<string, ElemType>> parsed;
public:
	Calculator(const string _expr):
		parsed(_expr.length())
	{
		if (!_expr.length()) throw "String length must be positive";
		expr = _expr;
	}

	void Parse();
	void ToPostfix();
	void Calculate();
};