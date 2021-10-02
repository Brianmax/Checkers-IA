#include <assert.h>
#include "board.h"
#include <cctype>
#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;
using std::toupper;

void board::checkNeighbors(int& x, int& y)
{
	if (tolower(arr[x][y]) == 'b' || arr[x][y] == 'R')
	{
		if (x % 2 == 0)
		{
			createMove(x, y, x+1, y);
			createMove(x, y, x+1, y+1);
		}
		else
		{
			createMove(x, y, x+1, y);
			createMove(x, y, x+1, y-1);
		}
	}
	if (tolower(arr[x][y]) == 'r' || arr[x][y] == 'B')
	{
		if (x % 2 == 0)
		{
			createMove(x, y, x-1, y);
			createMove(x, y, x-1, y+1);
		}
		else
		{
			createMove(x, y, x-1, y);
			createMove(x, y, x-1, y-1);
		}
	}
}

void board::createMove(const int& xi,const int& yi, int xf, int yf)
{
	if (isValidPos(xf, yf) && arr[xf][yf] == 'e')
	{
		move* m = new move(arr[xi][yi], xi, yi, xf, yf);
		mlist.push_back(m);
		convert(xi, yi, m->command);
		convert(xf, yf, m->command);
		m->command += "-1";
	}
}

bool board::listMoves()
{
	while (!mlist.empty())
	{
		delete mlist.front();
		mlist.pop_front();
	}

	if (color == 'b')
	{
		for (int i = 0; i!= 8; ++i)
			for (int j = 0; j != 4; ++j)
				if (arr[i][j] == color || arr[i][j] == toupper(color))
					checkNeighbors(i, j);
	}
	else
	{
		for (int i = 7; i!= -1; --i)
			for (int j = 0; j != 4; ++j)
				if (arr[i][j] == color || arr[i][j] == toupper(color))
					checkNeighbors(i, j);
	}

	if (mlist.empty())
		return false;
	return true;
}

