#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#pragma warning(disable:4996)
using namespace std;
struct point
{
	int x, y;
	int num;
};
point B[50001];
struct point_
{
	int x, y;
};
struct kd_tree_point
{
	point parent;
	point_ leftup, rightdown;
	int childnum[2];
};
kd_tree_point tree[50001];
int tree_node_num = 1;
bool axis;
long long dis(point p1, point p2)
{
	return (long long)(p1.x - p2.x)*(p1.x - p2.x) + (long long)(p1.y - p2.y)*(p1.y - p2.y);
}
long long dis(point p1, point_ p2)
{
	return (long long)(p1.x - p2.x)*(p1.x - p2.x) + (long long)(p1.y - p2.y)*(p1.y - p2.y);
}
long long dis(point p1, kd_tree_point p2)
{
	return max(max(dis(p1, p2.leftup), dis(p1, p2.rightdown)), max((long long)(p1.x - p2.leftup.x)*(p1.x - p2.leftup.x) + (long long)(p1.y - p2.rightdown.y)*(p1.y - p2.rightdown.y), (long long)(p1.x - p2.rightdown.x)*(p1.x - p2.rightdown.x) + (long long)(p1.y - p2.leftup.y)*(p1.y - p2.leftup.y)));
}
bool point_cmp(point a,point b)
{
	if (axis)
		return((a.y < b.y) || ((a.y == b.y) && (a.x < b.x)));
	else
		return((a.x < b.x) || ((a.x == b.x) && (a.y < b.y)));
}
struct queue_node
{
	long long dis;
	int num;
	queue_node(long long dis = -1, int num = -1):dis(dis),num(num) {}
	bool operator <(queue_node m) const
	{
		return (dis > m.dis || (dis == m.dis && num < m.num));
	}
};
priority_queue<queue_node> record;
int build_kd_tree(int start, int end, bool d)
{
	if (start > end)
		return 0;
	else
	{
		axis = d;
		int mid = (start + end) / 2;
		int count = tree_node_num++;
		nth_element(B + start, B + mid, B + end + 1, point_cmp);
		tree[count].parent = B[mid];
		tree[count].leftup.x = tree[count].parent.x;
		tree[count].leftup.y = tree[count].parent.y;
		tree[count].rightdown.x = tree[count].parent.x;
		tree[count].rightdown.y = tree[count].parent.y;
		tree[count].childnum[0] = build_kd_tree(start, mid - 1, !d);
		tree[count].childnum[1] = build_kd_tree(mid + 1, end, !d);
		tree[count].leftup.x = min(min(tree[tree[count].childnum[0]].leftup.x, tree[tree[count].childnum[1]].leftup.x), tree[count].leftup.x);
		tree[count].leftup.y = max(max(tree[tree[count].childnum[0]].leftup.y, tree[tree[count].childnum[1]].leftup.y), tree[count].leftup.y);
		tree[count].rightdown.x = max(max(tree[tree[count].childnum[0]].rightdown.x, tree[tree[count].childnum[1]].rightdown.x), tree[count].rightdown.x);
		tree[count].rightdown.y = min(min(tree[tree[count].childnum[0]].rightdown.y, tree[tree[count].childnum[1]].rightdown.y), tree[count].rightdown.y);;
		return count;
	}
}
void search(int cur, point p)
{
	if (cur == 0)
		return;
	else
	{
		queue_node tem = { dis(tree[cur].parent,p),tree[cur].parent.num };
		if (tem < record.top())
		{
			record.pop();
			record.push(tem);
		}
		long long dis_[2] = { dis(p,tree[tree[cur].childnum[0]]),dis(p,tree[tree[cur].childnum[1]]) };
		if (dis_[0] > dis_[1])
		{
			search(tree[cur].childnum[0], p);
			if (queue_node(dis_[1], tree[tree[cur].childnum[1]].parent.num) < record.top())
				search(tree[cur].childnum[1], p);
		}
		else
		{
			search(tree[cur].childnum[1], p);
			if (queue_node(dis_[0], tree[tree[cur].childnum[0]].parent.num) < record.top())
				search(tree[cur].childnum[0], p);
		}
	}
}
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
int main()
{
	int m, n;
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= m; i++)
	{
		B[i].num = i;
		B[i].x = readNum();
		B[i].y = readNum();
	}
	tree[0].parent.x = -1;
	tree[0].parent.y = -1;
	tree[0].parent.num = -1;
	tree[0].leftup.x = 1000000000 + 1;
	tree[0].leftup.y = -1;
	tree[0].rightdown.x = -1;
	tree[0].rightdown.y = 1000000000 + 1;
	build_kd_tree(1, m, 0);
	int xj, yj, k;
	for (int j = 0; j < n; j++)
	{
		xj = readNum();
		yj = readNum();
		k = readNum();
		while (!record.empty())
			record.pop();
		for (int t = 0; t < k; t++)
			record.push(queue_node());
		point p = { xj,yj,-1 };
		search(1, p);
		printf("%d\n", record.top().num);
	}
	return 0;
}