#include<iostream>
#include<string>
#include<sstream>
using namespace std;
char chem[4000];
unsigned long long record[4001];
unsigned long long read(int& i)
{
	unsigned long long j = 0;
	while (true)
	{
		j = 10 * j + chem[i] - 48;
		i++;
		if (chem[i] > '9' || chem[i] < '0')
			break;
	}
	return j;
}
int value(int &count)
{
	switch (chem[count])
	{
	case'H':
	{
		switch (chem[count + 1])
		{
		case'e':count++; return 4 * 2;
		case'g':count++; return 201 * 2;
		default:return 1 * 2;
		}
	}
	case'N':
	{
		switch (chem[count + 1])
		{
		case'a':count++; return 23 * 2;
		case'e':count++; return 20 * 2;
		default:return 14 * 2;
		}
	}
	case'C':
	{
		switch (chem[count + 1])
		{
		case'a':count++; return 40 * 2;
		case'l':count++; return 35.5 * 2;
		case'u':count++; return 63.5 * 2;
		default:return 12 * 2;
		}
	}
	case'O':return 16 * 2;
	case'F':
	{
		switch (chem[count + 1])
		{
		case'e':count++; return 56 * 2;
		default:return 19 * 2;
		}
	}
	case'M':
	{
		switch (chem[count + 1])
		{
		case'g':count++; return 24 * 2;
		case'n':count++; return 55 * 2;
		}
	}
	case'A':
	{
		switch (chem[count + 1])
		{
		case'l':count++; return 27 * 2;
		case'r':count++; return 40 * 2;
		case'g':count++; return 108 * 2;
		case'u':count++; return 197 * 2;
		}
	}
	case'S':
	{
		switch (chem[count + 1])
		{
		case'i':count++; return 28 * 2;
		default:return 32 * 2;
		}
	}
	case'P':
	{
		switch (chem[count + 1])
		{
		case't':count++; return 195 * 2;
		case'o':count++; return 209 * 2;
		default:return 31 * 2;
		}
	}
	case'K':return 39 * 2;
	case'T':count++; return 48 * 2;
	case'Z':count++; return 65 * 2;
	case'Y':return 89 * 2;
	case'I':return 127 * 2;
	case'B':count++; return 137 * 2;
	}
}
string add(string a,string b)
{
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
		return c;
	}
	else
	{
		string d = c.substr(1, l1);
		return d;
	}
}
string divide(string a)
{
	string helper;
	char rem = '0';
	for (int i = 0; i < a.length(); i++)
	{
		helper.push_back((a[i] - 48 + (rem - 48) * 10) / 2 + 48);
		rem = (a[i] - 48) % 2 + 48;
	}
	if (rem != '0')
	{
		helper.push_back('.');
		helper.push_back('5');
	}
	if (helper[0] == '0')
	{
		string helper2(helper, 1);
		helper = helper2;
	}
	return helper;
}
int main()
{
	string mass;
	cin.get(chem, 4000);
	int j = 0;
	for (int i = 0; true; i++)
	{
		if (chem[i] == '\0')
			break;
		switch (chem[i])
		{
		case'(':record[j] = 5; j++; break;
		case')':record[j] = 6; j++; break;
		case'_':record[j] = 7; i = i + 2; j++; record[j] = read(i); j++; break;
		case'~':
			i++; 
			if (chem[i] == 'H')
				record[j] = 36;
			else
				record[j] = (read(i)*36); 
			i = i + 5; j++; break;
		default:record[j] = value(i); j++; break;
		}
	}
	for (int i = 0; i < j; i++ )
	{
		if (record[i] == 6)
		{
			record[i] = 0;
			int t = 1;
			while (true)
			{
				if (record[i - t] == 5)
				{
					record[i - t] = 0;
					break;
				}
				record[i] = record[i] + record[i - t];
				record[i - t] = 0;
				t++;
			}
		}
		if (record[i] == 7)
		{
			record[i] = record[i - 1] * record[i + 1];
			record[i - 1] = 0;
			record[i + 1] = 0;
			i++;
		}
	}
	for (int i = 0; i < j; i++)
	{
		stringstream aid;
		string helper;
		aid << record[i];
		aid >> helper;
		mass = add(helper, mass);
	}
	mass = divide(mass);
	cout << mass;
	return 0；
}