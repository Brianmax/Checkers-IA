#include <assert.h>
#include "board.h"
#include <fstream>
#include <cctype>
#include <list>
#include <string>
#include <sstream>

using std::getline;
using std::ifstream;
using std::list;
using std::string;
using std::stringstream;

bool board::isComputer[2];

int board::timeLimit = 0;
move::~move()
{
	for (list<jump*>::iterator it = jpoints.begin(); it != jpoints.end(); ++it)
	{
		--(*it)->numTimes;
		if ((*it)->numTimes == 0)
			delete (*it);
	}
}
board::board()
{
	reset();
}
board::~board()
{
	while (!mlist.empty())
	{
		delete mlist.front();
		mlist.pop_front();
	}
}
//constructor copia: copia todos los valores de datos excepto la lista de movimientos

//muy util para la creacion de nuevos tableros para cada movimiento en el algoritmo
board::board(const board& b): color(b.color)
{
	for (int i = 0; i != 8; ++i)
		for (int j = 0; j != 4; ++j)
			arr[i][j] = b.arr[i][j];
}


void board::reset()
{
	color = 'b';
	for (int i = 0; i != 3; ++i)
		for (int j = 0; j != 4; ++j)
			arr[i][j] = 'b';
	for (int i = 3; i != 5; ++i)
		for (int j = 0; j != 4; ++j)
			arr[i][j] = 'e';
	for (int i = 5; i != 8; ++i)
		for (int j = 0; j != 4; ++j)
			arr[i][j] = 'r';
}
void board::modifyBoard(ifstream& fin)
{
	string line;
	int count = 0;
	while (getline(fin, line) && count != 8)
	{
		remove_carriage_return(line);
		stringstream ss(line);
		for (int jIndex = 0; jIndex != 4; ++jIndex)
			ss >> arr[count][jIndex];
		++count;
	}

	getline(fin, line);
	remove_carriage_return(line);
	stringstream ss(line);
	ss >> color;
	color = tolower(color);
	assert(color == 'b' || color == 'r');
}
//elimina el el caracter \r en una cadena o el caracter \n
inline void board::remove_carriage_return(std::string& line)
{
    if (*line.rbegin() == '\r' || *line.rbegin() == '\n')
    	line.erase(line.length() - 1);
}
