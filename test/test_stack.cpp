#include <gtest.h>
#include "Stack.h"

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> st(5));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> st(-10));
}

TEST(Stack, can_get_size)
{
	Stack<int> st(5);
	
	st.push(7);
	st.push(-20);

	EXPECT_EQ(2, st.size());
}

TEST(Stack, can_get_front_element)
{
	Stack<int> st(5);

	st.push(7);
	st.push(-20);

	EXPECT_EQ(-20, st.front());
}

TEST(Stack, can_push_and_pop_element)
{
	Stack<int> st(5);

	st.push(-19);
	st.push(32);
	st.pop();

	EXPECT_EQ(-19, st.pop());
}

TEST(Stack, throws_when_pop_from_empty_stack)
{
	Stack<int> st(5);

	ASSERT_ANY_THROW(st.pop());
}

TEST(Stack, throws_when_push_to_full_stack)
{
	Stack<int> st(2);

	st.push(3);
	st.push(-5);

	ASSERT_ANY_THROW(st.push(12));
}

TEST(Stack, can_check_if_it_empty)
{
	Stack<int> st(2);

	EXPECT_TRUE(st.isEmpty());
}

TEST(Stack, can_check_if_it_full)
{
	Stack<int> st(2);

	st.push(3);
	st.push(-5);

	EXPECT_TRUE(st.isFull());
}