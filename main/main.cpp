#include <stdio.h>
#include "Calculator.h"
#include <iostream>
#include <queue>

void PrintQueue(queue<pair<string, ElemType> > q);

int main()
{
	//-11 *  cos(-34)*sin(-123+6 /-3*(-2))+   111*sqrt(100)
	//-11 *  cos(-34)*sin(-123+6 /-3*(-2))+   111;sqrt(100);50+34*(19+11)
	//a = -11 *  cos(-34)*sin(-123+6 /-3*(-2))+   111;kor = sqrt(100);50+34*(19+11);c=5*kor;
	cout << "What do you want to calculate?" << endl;
	string calculation;
	getline(cin, calculation);

	Calculator calc(calculation);
	vector<double> results = calc.Calculate(true);
	for (auto i = results.begin(); i < results.end(); i++)
		cout << *i << endl;

	//a = -11 *  cos(-34)*sin(-123+6 /-3*(-2))+   111;sqrt(100);50+34*(19+11);c=5;
	/*queue<pair<string, ElemType> > parsed = calc.Parse("a = -11 *  cos(-34)*sin(-123+6 /-3*(-2))+   111;kor = sqrt(100);50+34*(19+11);c=5*kor;");
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
	results = calc.CalculateFromPostfix(postfix);
	for (auto i = results.begin(); i < results.end(); i++)
		cout << *i << endl;*/
		
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