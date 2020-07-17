#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<queue>
#pragma warning(disable:4996)
using namespace std;
vector<int> connection[500001];
int history[500001];
int readNum()
{
	char ch = getchar();
	while (ch < '0' or ch > '9') ch = getchar();
	int v = 0;
	while (ch >= '0' and ch <= '9')
	{
		v = v * 10 + ch - '0';
		ch = getchar();
	}
	return v;
}
int search(int start, int dest)
{
	if (start == dest)
		return 0;
	queue<int> visit1;
	queue<int> visit2;
	memset(history, 0, 500001 * 4);
	int distance = 0;
	visit1.push(start);
	history[start] = 1;
	visit1.push(-1);
	for (size_t t = 0; t < connection[visit1.front()].size(); t++)
	{
		if (history[connection[visit1.front()][t]] == -1)
			return ++distance;
		else
		{
			if (history[connection[visit1.front()][t]] != 1)
			{
				visit1.push(connection[visit1.front()][t]);
				history[connection[visit1.front()][t]] = 1;
			}
		}
	}
	visit1.pop();
	if (history[dest] == 1)
		return 1;
	visit2.push(dest);
	history[dest] = -1;
	visit2.push(-1);
	while (true)
	{
		visit1.pop();
		visit1.push(-1);
		distance++;
		while (visit2.front() != -1)
		{
			for (size_t t = 0; t < connection[visit2.front()].size(); t++)
			{
				if (history[connection[visit2.front()][t]] == 1)
					return ++distance;
				else
				{
					if (history[connection[visit2.front()][t]] != -1)
					{
						visit2.push(connection[visit2.front()][t]);
						history[connection[visit2.front()][t]] = -1;
					}
				}
			}
			visit2.pop();
		}
		visit2.pop();
		visit2.push(-1);
		distance++;
		while (visit1.front() != -1)
		{
			for (size_t t = 0; t < connection[visit1.front()].size(); t++)
			{
				if (history[connection[visit1.front()][t]] == -1)
					return ++distance;
				else
				{
					if (history[connection[visit1.front()][t]] != 1)
					{
						visit1.push(connection[visit1.front()][t]);
						history[connection[visit1.front()][t]] = 1;
					}
				}
			}
			visit1.pop();
		}
	}
}
int main()
{
	int n1, n, m;
	cin >> n1;
	cin >> n;
	cin >> m;
	int count = 100001;
	for (int i = 0; i < n; i++)
	{
		int tem1, tem2, tem3;
		tem1 = readNum();
		tem2 = readNum();
		tem3 = readNum();
		if (tem1 == tem2)
			continue;
		if (tem3 == 1)
		{
			connection[tem1].push_back(tem2);
			connection[tem2].push_back(tem1);
		}
		if (tem3 == 2)
		{
			connection[tem1].push_back(count);
			connection[count].push_back(tem1);
			connection[count].push_back(tem2);
			connection[tem2].push_back(count);
			count++;
		}
		if (tem3 == 3)
		{
			connection[tem1].push_back(count);
			connection[count].push_back(tem1);
			connection[count].push_back(count + 1);
			connection[count + 1].push_back(count);
			connection[count + 1].push_back(tem2);
			connection[tem2].push_back(count + 1);
			count = count + 2;
		}
	}
	for (int j = 0; j < m; j++)
	{
		int tem1, tem2, distance;
		tem1 = readNum();
		tem2 = readNum();
		distance = search(tem1, tem2);
		printf("%d\n", distance);
	}
	return 0;
}