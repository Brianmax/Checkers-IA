#ifndef BOARD_H_
#define BOARD_H_

#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

class jump
{
	jump* prev;

	char jumpingPiece;

	bool noNext;

	int numTimes;

	char c;

	int xs;
	int ys;

	int x;
	int y;

	int xend;
	int yend;

    int key;
    
	jump(char jpingp, char piece, int xs, int ys, int xc, int yc, int xe, int ye, jump* p, int k):
		prev(p), jumpingPiece(jpingp), noNext(true), numTimes(0), c(piece), xs(xs), ys(ys),
		 x(xc), y(yc), xend(xe), yend(ye), key(k){}

	friend class move;
	friend class board;
};

class move
{
	char mP;

	int xi;
	int yi;

	int xf;
	int yf;

	std::string command;

	std::list<jump*> jpoints;

	move(char c, int xs, int ys, int xe, int ye): mP(c), xi(xs), yi(ys), xf(xe), yf(ye) {}

	~move();
	
	friend class board;
	friend class game;
};

class board
{
	char arr[8][4];


	char color;
	static bool isComputer[2];

	board();
	~board();
	board(const board&);
    
	void changeTurn()
    {
        if (color == 'r')
            color = 'b';
        else
            color = 'r';
    }
    
	static void convertCommand(const std::string&);
    
	bool terminalTest()
    {
        if (!movesAvailable())
            return true;
        return false;
    }
    
	bool movesAvailable()
    {
        if (jumpsAvailable())
            return true;
        if (listMoves())
            return true;
        return false;
    }
    
	void handleKinging(const int& x, const int& y)
    {
        if (x == 0 && arr[x][y] == 'r')
            arr[x][y] = 'R';
        if (x == 7 && arr[x][y] == 'b')
            arr[x][y] = 'B';
    }
    
	bool isValidPos(int i, int j)
    {
        if (i >= 0 && i < 8 && j >= 0 && j < 4)
            return true;
        else return false;
    }

	void reset();

	void modifyBoard(std::ifstream&);

    void remove_carriage_return(std::string&);

    int createkey(int, int, int, int, int, int);
    int reverse(int);
	void createJump(std::list<jump*>&, char, int, int, int, int, int, int, jump*);
	void createJumpMove(std::list<jump*>&);
	void jumpAvailable(std::list<jump*>&, char c, int, int, jump*);
	bool jumpsAvailable();
	bool jumpConditions(int, int, int, int);

	void checkNeighbors(int&, int&);
	void createMove(const int&, const int&, int, int);
	bool listMoves();


	void convert(const int&, const int&, std::string&);

	int convertY(const int& x, const int& y);

	void printline(const int&, const std::string&, const std::string&);

	void printcolor(const char&);
	static void whoComputer();
    
	static int timeLimit;

	std::list<move*> mlist;
	bool isComputerTurn()
    {
        if (color == 'b' && isComputer[0])
            return true;
        if (color == 'r' && isComputer[1])
            return true;
        return false;
    }
	void inputCommand();
	void printBoard();
	void printMoves();
	void makeMove(move*);
	void undoMove(move*);
	int cornerDiagonal(char, char);
	int evaluate();
	void startup();
	char getTurn()
    {
        return color;
    }
	friend class game;
	template <class T> friend class sptr;
};

#endif /* BOARD_H_ */
