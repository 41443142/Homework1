#include<iostream>
#include<cmath>

using namespace std;

void push_stack(int*& s, int& top, int& capacity, int val)
{
	top++;
	if (top >= capacity)
	{
		int new_capacity = capacity * 2;
		int* new_s = new int[new_capacity];
		for (int i = 0; i < capacity; i++)
		{
			new_s[i] = s[i];
		}
		delete[] s;
		s = new_s;
		capacity = new_capacity;
	}
	s[top] = val;
}

int pop_stack(int*& s, int& top)
{
	int val = s[top];
	top--;
	return val;
}

// 遞迴版本
int A(int m, int n)
{
	if (m == 0)
	{
		return n + 1;
	}
	else if (n == 0)
	{
		return A(m - 1, 1);
	}
	else
	{
		return A(m - 1, A(m, n - 1));
	}
}

// 非遞迴版本 (自訂 Stack)
int B(int m, int n)
{
	int capacity = 16;
	int top = -1;
	int* s = new int[capacity];
	push_stack(s, top, capacity, m);
	while (top >= 0)
	{
		m = pop_stack(s, top);
		if (m == 0)
		{
			n++;
		}
		else if (n == 0)
		{
			push_stack(s, top, capacity, m - 1);
			n = 1;
		}
		else
		{
			push_stack(s, top, capacity, m - 1);
			push_stack(s, top, capacity, m);
			n--;
		}
	}
	delete[] s;
	return n;
}

int main()
{
	int m, n, a, b;
	while (cin >> m >> n)
	{
		a = A(m, n);
		cout << a << endl;

		b = B(m, n);
		cout << b << endl;
	}
	return 0;
}