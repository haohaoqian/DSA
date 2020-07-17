#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a, b;
	cin >> a;
	cin >> b;
	char l1 = a.length();
	char l2 = b.length();
	if (l1 > l2)
		b = string(l1 - l2, '0') + b;
	else if (l1 < l2)
	{
		a = string(l2 - l1, '0') + a;
		l1 = l2;
	}
	string c(l1 + 1, '0');
	char remain = 0;
	for (char x = l1 - 1; x >= 0; x--)
	{
		c[x + 1] = (((a[x] - 48) + (b[x] - 48) + remain) % 10) + 48;
		remain = ((a[x] - 48) + (b[x] - 48) + remain) / 10;
	}
	if (remain != 0)
	{
		c[0] = remain + 48;
		cout << c;
	}
	else
	{
		string d = c.substr(1, l1);
		cout << d;
	}
	return 0;
}