#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int minheap[150000];
int maxheap[150000];
int midnum[300000];
int readNum() 
{
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	int v = 0;
	while (ch >= '0' && ch <= '9')
	{
		v = v * 10 + ch - '0';
		ch = getchar();
	}
	return v;
};
bool compare(int a, int b)
{
	return a > b;
}
int main()
{
	int n, m;
	n = readNum();
	m = readNum();
	int tem1, tem2;
	tem1 = readNum();
	tem2 = readNum();
	int count = 0;
	if (tem1 >= tem2)
	{
		minheap[count] = tem1;
		maxheap[count] = tem2;
		count++;
	}
	else
	{
		minheap[count] = tem2;
		maxheap[count] = tem1;
		count++;
	}
	midnum[0] = tem1 * 2;
	midnum[1] = tem1 + tem2;
	make_heap(maxheap, maxheap);
	make_heap(minheap, minheap, compare);
	int i;
	for ( i = 2; i < n; i++)
	{
		tem1 = readNum();
		if (tem1 <= minheap[0])
		{
			maxheap[count] = tem1;
			push_heap(maxheap, maxheap + count + 1);
		}
		else
		{
			maxheap[count] = minheap[0];
			push_heap(maxheap, maxheap + count + 1);
			pop_heap(minheap, minheap + count, compare);
			minheap[count - 1] = tem1;
			push_heap(minheap, minheap + count, compare);
		}
		midnum[i] = maxheap[0] * 2;
		i++;
		if (i == n)
			break;
		tem1 = readNum();
		if (tem1 >= maxheap[0])
		{
			minheap[count] = tem1;
			push_heap(minheap, minheap + count + 1, compare);
		}
		else
		{
			minheap[count] = maxheap[0];
			push_heap(minheap, minheap + count + 1, compare);
			pop_heap(maxheap, maxheap + count + 1);
			maxheap[count] = tem1;
			push_heap(maxheap, maxheap + count + 1);
		}
		midnum[i] = maxheap[0] + minheap[0];
		count++;
	}
	for (int i = 0; i < m; i++)
	{
		tem1 = readNum();
		if (midnum[tem1] % 2)
			cout << midnum[tem1] / 2 << ".5" << endl;
		else
			cout << midnum[tem1] / 2 << endl;
	}
	return 0;
}