#include<cstdio>
#pragma warning(disable:4996)
using namespace std;
int main()
{
	int m, n;
	scanf("%d %d", &n, &m);
	double* a = new double[n + 1];
	double* b = new double[n];
	double* c = new double[n];
	double* r = new double[n * m];
	for (int i = 0; i < n; i++)
		scanf("%lf", &b[i]);
	for (int i = 0; i < n - 1; i++)
		scanf("%lf", &c[i]);
	c[n - 1] = 0;
	a[0] = 0;
	for (int i = 0; i < n - 1; i++)
		scanf("%lf", &a[i + 1]);
	for (int j = 0; j < m; j++)
		for (int i = 0; i < n; i++)
			scanf("%lf", &r[j + i * m]);
	for (int i = 1; i < n; i++)
	{
		double helper;
		helper = a[i] / b[i - 1];
		a[i] = 0;
		b[i] = b[i] - helper * c[i - 1];
		for (int j = 0; j < m; j++)
			r[j + i * m] = r[j + i * m] - r[j + (i - 1) * m] * helper;
	}
	a[n] = 0;
	for (int j = 0; j < m; j++)
	{
		for (int i = n - 1; i >= 0; i--)
			a[i] = (r[j + i * m] - c[i] * a[i + 1]) / b[i];
		for (int i = 0; i < n; i++)
			printf("%lf ", a[i]);
		printf("\n");
	}
	return 0;
}