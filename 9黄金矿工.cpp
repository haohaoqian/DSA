#include<cstdio>
#include<cmath>
#pragma warning(disable:4996)
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
using namespace std;
int map[600][600];
int max[2][601][601];
int main()
{
	int miner;
	scanf("%d", &miner);
	int length;
	scanf("%d", &length);
	int row, line;
	for (row = 0; row < length; row++)
		for (line = 0; line < length; line++)
			scanf("%d", &map[row][line]);
	if (miner == 1)
	{
		for (int row = length - 1; row >= 0; row--)
			for (int line = length - 1; line >= 0; line--)
				max[1][row][line] = map[row][line] + ((max[1][row + 1][line] > max[1][row][line + 1]) ? max[1][row + 1][line] : max[1][row][line + 1]);
		printf("%d", max[1][0][0]);
	}
	else
	{
		int ctrl = 1;
		for (int steps = 2 * length - 2; steps >= 0; steps--)
		{
			for (int row1 = MAX(0, steps - length + 1); row1 <= MIN(length - 1, steps); row1++)
				for (int row2 = MAX(0, steps - length + 1); row2 <= MIN(length - 1, steps); row2++)
				{
					max[ctrl - 1][row1][row2] = map[row1][steps - row1] + map[row2][steps - row2] + MAX(max[2 - ctrl][row1 + 1][row2 + 1], MAX(max[2 - ctrl][row1][row2], MAX(max[2 - ctrl][row1 + 1][row2], max[2 - ctrl][row1][row2 + 1])));
					if (row1 == row2)
						max[ctrl - 1][row1][row2] -= map[row1][steps - row1];
				}
			ctrl = 3 - ctrl;
		}
		printf("%d", max[2 - ctrl][0][0]);
	}
	return 0;
}