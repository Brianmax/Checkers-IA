#include <assert.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "game.h"
#include <iostream>
#include <limits>
#include <list>
#include "board.h"
#include <time.h>
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::list;



game::game(): currentB(sptr<board>(new board())), bestM(NULL), tempBestM(NULL), maxdepth(0),
		cdepth(0), timeUp(false), gameOver(false), reachedEnd(false), startTime(0), endTime(0),
		startTimeD(0), endTimeD(0) {}

void game::playTheGame()
{
	gameOver = false;
	currentB->startup();
	while (!gameOver)
		printGame();
}

void game::endMessage()
{
	gameOver = true;
	cout << "Fin del juego" << endl;
	cout << endl;
	if (currentB->getTurn() == 'r')
		cout << "Victoria jugador 1" << endl;
	else cout << "Victoria jugador 2." << endl;
	cout << "Deseas jugar de nuevo?" << endl;
	char answer;
	cin >> answer;
	bool loop = true;
	while (loop)
	{
		if (tolower(answer) == 'y')
		{
			loop = false;
			playTheGame();
		}
		else if (tolower(answer) == 'n')
			loop = false;
		else
		{
			cout << "Deseas jugar de nuevo?" << endl;
			cin >> answer;
		}
	}
}

void game::computerTurn()
{
	currentB->printMoves();

	if (currentB->mlist.size() == 1)
	{
		bestM = currentB->mlist.front();
		time(&startTime);
		time(&endTime);
		cdepth = 0;
	}
	else
	{
		time(&startTime);
		for (int i = 1; i != maxIterDepth; ++i)
		{
			time(&startTimeD);

			maxdepth = i;

			alphabeta(currentB, i, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
			time(&endTimeD);

			if (difftime(endTimeD, startTimeD) >= ((board::timeLimit)/2))
			{
				time(&endTime);
				timeUp = true;
				break;
			}

			if (timeUp)
				break;
			else
				bestM = tempBestM;

			if (reachedEnd)
				break;
		}
	}
	assert(bestM != NULL);

	outputMessage();
}

void game::outputMessage()
{
	currentB->makeMove(bestM);
	cout << "Busqueda en profundidad completa " << cdepth << "." << endl;
	if (timeUp && cdepth != maxIterDepth && !reachedEnd)
		cout << "Tiempo de busqueda excedido " << cdepth + 1 << "." << endl;
	cout << "Busqueda para un total de: " << difftime(endTime, startTime) << " seconds" << endl;
	cout << "Movimiento escogido es: ";
	board::convertCommand(bestM->command);
	cout << endl;

	bestM = NULL;
	tempBestM = NULL;
	timeUp = false;
	reachedEnd = false;
}

void game::printGame()
{
	currentB->printBoard();
	if (currentB->terminalTest())
		endMessage();
	else if (currentB->isComputerTurn())
		computerTurn();
	else
		currentB->inputCommand();
}
const int game::maxIterDepth = 20;
int game::alphabeta(sptr<board>& b, int depth, int alpha, int beta)
{
	if (depth != maxdepth && b->terminalTest())
	{
		//b->printBoard();
		reachedEnd = true;
		cdepth = maxdepth;
		if (b->getTurn() == 'r')
			return std::numeric_limits<int>::max();
		else return std::numeric_limits<int>::min();
	}
	reachedEnd = false;
	if (depth == 0)
		return b->evaluate();
	list<move*>::iterator iter = b->mlist.begin();

	int localalpha = std::numeric_limits<int>::min();
	int localbeta = std::numeric_limits<int>::max();
	if (b->getTurn() == 'b')
	{
		for (; iter != b->mlist.end(); ++iter)
		{
			time(&endTime);
			if (difftime(endTime, startTime) >= (board::timeLimit - 1))
			{
				timeUp = true;
				break;
			}

			b->makeMove(*iter);
			sptr<board> newB(new board(*b));
			int value = alphabeta(newB, depth-1, alpha, min(localbeta, beta));
			b->undoMove(*iter);
			b->changeTurn();
			if (value > alpha)
			{
				alpha = value;
				if (depth == maxdepth)
					tempBestM = (*iter);
			}

			if (alpha >= beta && depth < maxdepth)
				return alpha;
		}

		if (!timeUp && depth == maxdepth)
			cdepth = depth;
		return alpha;
	}
	else
	{
		for (; iter != b->mlist.end(); ++iter)
		{
			time(&endTime);
			if (difftime(endTime, startTime) >= (board::timeLimit - 1))
			{
				timeUp = true;
				break;
			}
			b->makeMove(*iter);
			sptr<board> newB(new board(*b));
			int value = alphabeta(newB, depth-1, max(localalpha, alpha), beta);
			b->undoMove(*iter);
			b->changeTurn();
			if (value < beta)
			{
				beta = value;
				if (depth == maxdepth)
					tempBestM = (*iter);
			}
			if (alpha >= beta)
				return beta;
		}
		if (!timeUp && depth == maxdepth)
			cdepth = depth;
		return beta;
	}
}
