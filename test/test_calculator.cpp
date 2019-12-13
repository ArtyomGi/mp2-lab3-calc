#include <gtest.h>
#include "Calculator.h"

TEST(Calc, can_create_calculator_with_positive_length)
{
	ASSERT_NO_THROW(Calculator c("17-3"));
}

TEST(Calc, throws_when_create_calculator_with_negative_length)
{
	ASSERT_ANY_THROW(Calculator c(""));
}

TEST(Calc, can_get_right_answer)
{
	Calculator c("-11 *  cos(-34)*sin(-123+6 /-3*(-2))+   111*sqrt(100)");

	EXPECT_NEAR(1113.47, c.Calculate(false), 0.1);
}

TEST(Calc, can_parse)
{
	Calculator c("2+2");

	queue<pair<string, ElemType>> q = c.Parse("12 -34 *(6+4)");

	EXPECT_NE(0, q.size());
}

TEST(Calc, throws_when_postfix_with_unclosed_brackets)
{
	Calculator c("2+2");

	queue<pair<string, ElemType>> q = c.Parse("12 (-34 *(6+4)");
	

	ASSERT_ANY_THROW(c.ToPostfix(q));
}

TEST(Calc, throws_when_postfix_with_unneseccary_brackets)
{
	Calculator c("2+2");

	queue<pair<string, ElemType>> q = c.Parse("12 -34 *(6+4) )");


	ASSERT_ANY_THROW(c.ToPostfix(q));
}