#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "time.h"

template <class T>
class sptr
{
private:
	T* pData;
public:
	sptr(T* pVal): pData(pVal) {}
	~sptr()	{delete pData;}
	T& operator*() {return *pData;}
	T* operator->() {return pData;}
};

class game
{

	sptr<board> currentB;

	static const int maxIterDepth;

	move* bestM;

	move* tempBestM;

	int maxdepth;

	int cdepth;
	bool timeUp;

	bool gameOver;

	bool reachedEnd;

	time_t startTime;
	time_t endTime;

	time_t startTimeD;
	time_t endTimeD;

	void printGame();

	void outputMessage();

	void computerTurn();

	int alphabeta(sptr<board>&, int, int, int);

	void endMessage();

public:

	game();

	void playTheGame();

};


#endif /* GAME_H_ */
