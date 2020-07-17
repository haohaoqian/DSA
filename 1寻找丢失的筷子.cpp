#include<cstdio>
#include<algorithm>
#pragma warning(disable:4996)
using namespace std;
int a[8000000];
int main()
{
	int count = 0;
	int N;
	scanf("%d", &N);
	for (count; count < 2 * N - 1; count++)
		scanf("%d", &a[count]);
	if (N <= 100000)
	{
		sort(a, a + 2 * N - 1);
		count = 1;
		int rem = a[0], cou = 1;
		for (count; count < 2 * N; count++)
		{
			if (a[count] == rem)
				cou++;
			else
			{
				if (cou % 2 == 0)
				{
					cou = 1;
					rem = a[count];
				}
				else
				{
					printf("%d", rem);
					break;
				}
			}
		}
	}
	else
	{
		int count1 = 0, count2 = 0;
		count1 = 0;
		int rem = -1, cou = 1;
		for (count1; count1 < 2 * N - 1; count1++)
		{
			if (rem != a[count1] && a[count1] != 0)
			{
				rem = a[count1];
				for (count2 = count1 + 1; count2 < 2 * N - 1; count2++)
				{
					if (rem == a[count2])
					{
						cou++;
						a[count2] = 0;
					}
				}
				if (cou % 2 != 0)
				{
					printf("%d", rem);
					break;
				}
				else
					cou = 1;
			}
		}
	}
	return 0;
}