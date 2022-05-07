#include "pch.h"
#include <iostream>
using namespace std;
struct node { int x, y; };
int main()
{
	linkQueue<node> aa;
	node newfind, last;
	int **maze;
	int row, col, i, j, wall;

	cout << "please type in row and col:";
	cin >> row >> col;
	wall = row * col;
	maze = new int*[row];
	for (i = 0; i < row; ++i)
	{
		maze[i] = new int[col];
		cout << i<<"line.please input where the wall is(0 is empty and " << wall << " is wall):";
		for (j = 0; j < col; ++j)
			cin >> maze[i][j];
    }
		newfind.x = 0;
		newfind.y = 0;
		aa.enQueue(newfind);
	while (!aa.isEmpty())
		{
			last = aa.deQueue();
			//上
			if (last.x != 0 && maze[last.x - 1][last.y] == 0)
			{
				newfind.x = last.x - 1;
				newfind.y = last.y;
				if (newfind.x != 0 || newfind.y != 0)
				{
					maze[newfind.x][newfind.y] = maze[last.x][last.y] + 1;
					aa.enQueue(newfind);
				}
			}
			//右
		if ((last.x == row - 1) && (last.y == col - 2)) break;
		if (maze[last.x][last.y + 1] == 0 && last.y + 1 < col)
			{
				newfind.x = last.x;
				newfind.y = last.y + 1;
				maze[newfind.x][newfind.y] = maze[last.x][last.y] + 1;
				aa.enQueue(newfind);
			}
			//下
		if ((last.x == row -2) && (last.y == col - 1)) break;
		if (maze[last.x + 1][last.y] == 0 && last.x + 1 < row)
			{
				newfind.x = last.x + 1;
				newfind.y = last.y;
				maze[newfind.x][newfind.y] = maze[last.x][last.y] + 1;
				aa.enQueue(newfind);
			}
			//左
			if (last.y != 0 && maze[last.x][last.y - 1] == 0)
			{
				newfind.x = last.x;
				newfind.y = last.y - 1;
				if (newfind.x != 0 || newfind.y != 0)
				{
					maze[newfind.x][newfind.y] = maze[last.x][last.y] + 1;
					aa.enQueue(newfind);
				}
			}
		}
	maze[row - 1][col - 1] = maze[last.x][last.y] + 1;

	int length = maze[row - 1][col - 1] + 1;
	node *path = new node[length];
	newfind.x = row - 1;
	newfind.y = col - 1;
	while (newfind.x != 0 || newfind.y != 0)
	{
		path[maze[newfind.x][newfind.y]] = newfind;
		if (newfind.x != 0 && (maze[newfind.x - 1][newfind.y] < maze[newfind.x][newfind.y]))
		{newfind.x = newfind.x - 1;continue;}
		if (newfind.x != row - 1 && maze[newfind.x + 1][newfind.y] < maze[newfind.x][newfind.y])
		{newfind.x = newfind.x + 1;continue;}
		if (newfind.y != 0 && maze[newfind.x][newfind.y - 1] < maze[newfind.x][newfind.y])
		{newfind.y = newfind.y - 1;continue;}
		if (newfind.y != col - 1 && maze[newfind.x][newfind.y + 1] < maze[newfind.x][newfind.y])
		{newfind.y = newfind.y + 1;continue;}
	}
	path[0] = newfind;
	cout << "path is:";
	for (i = 0; i < length - 1; ++i)
		cout << "(" << path[i].x << "," << path[i].y << ")->";
	cout << "(" << path[length - 1].x << "," << path[length - 1].y << ")";

	return 0;
}
