#include <assert.h>
#include "board.h"
#include <iostream>
#include <list>
#include <string>

using std::endl;
using std::cin;
using std::cout;
using std::getline;
using std::endl;
using std::list;
using std::string;

void board::convert(const int& x, const int& y, string& s)
{
	 char c1 = '0' + x;
	 char c2;
	 if (x % 2 == 0)
	 {
		 c2 = '0' + (2*y + 1);
	 }
	 else
	 {
		 c2 = '0' + (2*y);
	 }
	 s += c1;
	 s += ' ';
	 s += c2;
	 s += ' ';
}

inline int board::convertY(const int& x, const int& y)
{
    if (x % 2 == 0)
        return (2*y + 1);
    else return (2*y);
}

void board::printline(const int& i, const string& lineEven, const string& lineOdd)
{
	if (i % 2 == 0)
	{
		cout << lineEven << endl;
		cout << "  " << i << " |XXXXX|";
		for (int j = 0; j != 3; ++j)
		{
			cout << "  ";
			printcolor(arr[i][j]);
			cout << "  |XXXXX|";
		}
		cout << "  ";
		printcolor(arr[i][3]);
		cout << "  |" << endl;;
		cout << lineEven << endl;
	}
	else
	{
		cout << lineOdd << endl;
		cout << "  " << i << " |";
		for (int j = 0; j != 3; ++j)
		{
			cout << "  ";
			printcolor(arr[i][j]);
			cout << "  |XXXXX|";
		}
		cout << "  ";
		printcolor(arr[i][3]);
		cout << "  |XXXXX|" << endl;;
		cout << lineOdd << endl;
	}
}
void board::printcolor(const char& c)
{
	if (c == 'e')
		cout << ' ';
	else if (c == 'r' || c == 'R')
	{
		string default_console = "\033[0m";
		string color = "\033[1;35m";
		cout << color << c;
		cout << default_console;
	}
	else
	{
		string default_console = "\033[0m";
		string color = "\033[1;36m";
		cout << color << c;
		cout << default_console;
	}
}

void board::whoComputer()
{
	bool b = true;
	char c = ' ';
	while (b)
	{
		cout << "Deseas que el jugador 1 sea una computadora? (S/N): " << endl;
		cin >> c;
		if (tolower(c) == 's')
		{
			board::isComputer[0] = true;
			b = false;
		}
		else if (tolower(c) == 'n')
		{
			board::isComputer[0] = false;
			b = false;
		}
	}
	b = true;
	c = ' ';
	while (b)
	{
		cout << "Deseas que el jugador 2 sea una computadora? (S/N): " << endl;
		cin >> c;
		if (tolower(c) == 's')
		{
			board::isComputer[1] = true;
			b = false;
		}
		else if (tolower(c) == 'n')
		{
			board::isComputer[1] = false;
			b = false;
		}
	}
	if (board::isComputer[0] == true || board::isComputer[1] == true)
	{
		timeLimit = 3;
	}
}

