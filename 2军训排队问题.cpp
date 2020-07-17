#include<cstdio>
#include<iostream>
#pragma warning(disable:4996)
using namespace std;
int numnext[500000];
int numprev[500000];
int main()
{
	int N, M;
	int head = 0, tail = 0;
	scanf("%d %d", &N, &M);
	int type;
	for (int i = 0; i < N + M; i++)
	{
		scanf("%d", &type);
		if (type)
		{
			int sou, des, pos;
			scanf("%d %d %d", &sou, &des, &pos);
			if (head == 0)
			{
				head = sou;
			    tail = sou;
			}
			else if (des == head && pos == 0)
			{
				numprev[head] = sou;
				numnext[sou] = head;
				head = sou;
			}
			else if (des == tail && pos == 1)
			{
				numnext[tail] = sou;
				numprev[sou] = tail;
				tail = sou;
			}
			else
			{
				if (pos)
				{
					int a = numnext[des];
					numnext[des] = sou;
					numprev[sou] = des;
					numnext[sou] = a;
					numprev[a] = sou;
				}
				else
				{
					int a = numprev[des];
					numnext[sou] = des;
					numprev[des] = sou;
					numnext[a] = sou;
					numprev[sou] = a;
				}
			}
		}
		else
		{
			int tar;
			scanf("%d", &tar);
			if (head == tar)
			{
				head = numnext[tar];
				numprev[numnext[tar]] = 0;
				numnext[tar] = numprev[tar] = 0;
			}
			else if (tail == tar)
			{
				tail = numprev[tar];
				numnext[numprev[tar]] = 0;
				numnext[tar] = numprev[tar] = 0;
			}
			else
			{
				numnext[numprev[tar]] = numnext[tar];
				numprev[numnext[tar]] = numprev[tar];
				numnext[tar] = numprev[tar] = 0;
			}
		}
	}
	if (head)
	{
		printf("%d ", head);
		int next = numnext[head];
		for (int j = 1; j < N - M; j++)
		{
			printf("%d ", next);
			next = numnext[next];
		}
	}
	cout << -1;
	return 0;
}