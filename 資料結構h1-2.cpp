#include <iostream>
#include <string>

using namespace std;


void Powerset(const string& a, int index, string current)
{
	if (index == a.length())
	{
		cout << "(";
		for (size_t i = 0; i < current.length(); i++)
		{
			cout << current[i];
			if (i + 1 < current.length())
			{
				cout << ", ";
			}
		}
		cout << ")" << endl;
		return;
	}

	Powerset(a, index + 1, current);

	Powerset(a, index + 1, current + a[index]);
}

int main()
{
	string a;
	while (cin >> a)
	{
		Powerset(a, 0, "");
	}
	return 0;
}