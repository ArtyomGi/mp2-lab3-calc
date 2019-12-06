#pragma once

template <class T>
class Stack
{
	int len;
	int index;
	T *pMem;
public:
	Stack(int N)
	{
		if (N <= 0) throw "Error";
		len = N;
		index = -1;
		pMem = new T[len];
	}

	Stack(const Stack& s);
	void push(T el);
	T pop();
	bool isEmpty();
	bool isFull();
};

template <class T>
Stack<T>::Stack(const Stack<T>& s)
{
	len = s.len;
	index = s.index;
	for (int i = 0; i < s.index; i++)
		pMem[i] = s.pMem[i];
}

template <class T>
void Stack<T>::push(T el)
{
	if (isFull) throw "Stack is full";
	index++;
	pMem[index] = el;
}

template <class T>
T Stack<T>::pop()
{
	if (isEmpty) throw "Stack is empty";
	T tmp = pMem[index];
	index--;
	return tmp;
}

template <class T>
bool Stack<T>::isEmpty()
{
	return (index == -1);
}

template <class T>
bool Stack<T>::isFull()
{
	return (index >= len-1);
}
