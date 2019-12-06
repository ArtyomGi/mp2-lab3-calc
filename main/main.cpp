#include <stdio.h>
#include "Calculator.h"
#include <iostream>
#include <queue>


int main()
{
	Calculator calc("11  (123+2 +3)  ++");
	calc.Parse();
	queue<pair<string, ElemType> > q = calc.getQ();

	while (!q.empty())
	{
		cout << q.front().first << endl;
		q.pop();
	}
		
  return 0;
}