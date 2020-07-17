#include<cstdio>
#include<cmath>
#pragma warning(disable:4996)
using namespace std;
char group[100000];
double data[2000000];
int main()
{
	int m, n;
	scanf("%d %d",&m,&n);
	double* w = new double[m];
	w[0] = 1;
	for (int j = 1; j < m; j++)
		w[j] = 0;
	for (int j = 0; j < n; j++)
	{
		double first;
		scanf("%lf", &first);
		if (first == 0)
			group[j] = -1;
		else
			group[j] = 1;
		for (int i = 0; i < m; i++)
			scanf("%lf", &data[j * m + i]);
	}
	double result;
	for (int turns = 0; turns < 500; turns++)
		for (int j = 0; j < n; j++)
		{
			result = 0;
			for (int i = 0; i < m; i++)
				result = result + w[i] * data[j * m + i];
			if (group[j] * result <= 0)
				for (int i = 0; i < m; i++)
					w[i] = w[i] + 0.2 * group[j] * data[j * m + i];
		}
	double length = 0;
	for (int i = 0; i < m; i++)
		length = length + w[i] * w[i];
	for (int i = 0; i < m; i++)
		printf("%.17lf ", w[i]/sqrt(length));
	return 0;
}