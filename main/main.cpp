#include <stdio.h>
#include "Calculator.h"
#include <iostream>
#include <queue>

void PrintQueue(queue<pair<string, ElemType> > q);

int main()
{
	Calculator calc("11*34+(123+2 /3)+111");
	queue<pair<string, ElemType> > parsed = calc.Parse("-11 *  -34*sin(-123+6 /-3*(-2))+   111");
	//
	queue<pair<string, ElemType> > parsed2 = parsed;
	while (!parsed2.empty())
	{
		cout << parsed2.front().first << endl;
		parsed2.pop();
	}
	queue<pair<string, ElemType> > postfix = calc.ToPostfix(parsed);
	
	PrintQueue(postfix);
	
	//cout << s << endl;
	//parsed = calc.Parse(s);
	cout << calc.CalculateFromPostfix(postfix) << endl;
		
  return 0;
}

void PrintQueue(queue<pair<string, ElemType> > q)
{
	while (!q.empty())
	{
		cout << q.front().first << " ";// << endl;
		q.pop();
	}
	cout << endl;
}