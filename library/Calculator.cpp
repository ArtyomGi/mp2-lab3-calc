#include "Calculator.h"

void Calculator::ToPostfix()
{

}

void Calculator::Parse()
{
	for (string::const_iterator i = expr.cbegin(); i != expr.cend(); i++)
	{
		if (operations.find(*i) != std::string::npos)
		{

		}
	}
}