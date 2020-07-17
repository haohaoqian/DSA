#include<cstdio>
#pragma warning(disable:4996)
using namespace std;
int input[9][9];
int order[81];
int sum(int data[9][9])
{
	int S = 0;
	S = S + (data[0][0] + data[8][0] + data[0][8] + data[8][8]);
	S = S + 2 * (data[0][1] + data[0][7] + data[1][0] + data[1][1] + data[1][7] + data[1][8] + data[8][1] + data[8][7] + data[7][0] + data[7][1] + data[7][7] + data[7][8]);
	S = S + 3 * (data[0][2] + data[0][6] + data[1][2] + data[1][6] + data[7][2] + data[7][6] + data[8][2] + data[8][6] + data[2][0] + data[2][1] + data[2][2] + data[2][6] + data[2][7] + data[2][8] + data[6][0] + data[6][1] + data[6][2] + data[6][6] + data[6][7] + data[6][8]);
	S = S + 4 * (data[0][3] + data[0][5] + data[1][3] + data[1][5] + data[2][3] + data[2][5] + data[6][3] + data[6][5] + data[7][3] + data[7][5] + data[8][3] + data[8][5] + data[3][0] + data[3][1] + data[3][2] + data[3][3] + data[3][5] + data[3][6] + data[3][7] + data[3][8] + data[5][0] + data[5][1] + data[5][2] + data[5][3] + data[5][5] + data[5][6] + data[5][7] + data[5][8]);
	S = S + 5 * (data[0][4] + data[1][4] + data[2][4] + data[3][4] + data[5][4] + data[6][4] + data[7][4] + data[8][4] + data[4][0] + data[4][1] + data[4][2] + data[4][3] + data[4][4] + data[4][5] + data[4][6] + data[4][7] + data[4][8]);
	return S;
}
bool judge(int x, int y, int data[9][9],int value)
{
	bool flag = true;
	if (value > 9)
		flag = false;
	else
	{
		for (int i = 0; i < 9; i++)
		{
			if (i == y)
				continue;
			if (data[x][i] == value)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			for (int i = 0; i < 9; i++)
			{
				if (i == x)
					continue;
				if (data[i][y] == value)
				{
					flag = false;
					break;
				}
			}
		}
		if (flag)
		{
			int left = 3 * (x / 3);
			int up = 3 * (y / 3);
			for (int x0 = left; x0 < left + 3; x0++)
			{
				for (int y0 = up; y0 < up + 3; y0++)
				{
					if (x0 == x && y0 == y)
						continue;
					else
						if (data[x0][y0] == value)
						{
							flag = false;
							break;
						}
				}
				if (!flag)
					break;
			}
		}
	}
	return flag;
}
int main()
{
	int score = 0;
	int tem;
	bool flag = true;
	for (int row = 0; row < 9; row++)
		for (int line = 0; line < 9; line++)
			scanf("%d", &input[row][line]);
	for (int t = 0; t < 81; t++)
		order[t] = -1;
	int count = 0;
	bool ctrl = true;
	int known, known0 = 0;
	int row0 = -1, line0 = -1;
	while (flag)
	{
		if (order[count] == -1)
		{
			known = 0;
			known0 = 9;
			row0 = line0 = -1;
			for (int row = 0; row < 9; row++)
				for (int line = 0; line < 9; line++)
				{
					known = 0;
					if (input[row][line] == 0)
					{
						for (int t = 1; t <= 9; t++)
							if (judge(row, line, input, t))
								known++;
						if (known <= known0)
						{
							known0 = known;
							row0 = row;
							line0 = line;
						}
					}
					else
						continue;
				}
		}
		else
		{
			row0 = order[count] / 10;
			line0 = order[count] - 10 * row0;
		}
		if (row0 == -1)
		{
			tem = sum(input);
			score = (tem > score) ? tem : score;
			flag = true;
			if (count == 0)
				flag = false;
			else
				count--;
		}
		else
		{
			if (order[count] == -1)
			{
				order[count] = row0 * 10 + line0;
				count++;
			}
			while (true)
			{
				input[row0][line0]++;
				if (judge(row0, line0, input, input[row0][line0]))
				{
					if (order[count] != -1)
						count++;
					break;
				}
				if (input[row0][line0] >= 9)
				{
					if (count == 0)
						flag = false;
					else
					{
						input[row0][line0] = 0;
						if (order[count] == -1)
							count = count - 2;
						else
							count--;
					}
					break;
				}
			}
		}
	}
	printf("%d", score);
	return 0;
}
