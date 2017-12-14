/*HandleEvent.c*/
/*Mathieu levy and Brandon Hornbeck*/

#include "handleEvent.h" 



void launchCredit(int *gameOver, int *ending,
		  int *menu, int *play, int *level, int *credit)
{
	*gameOver = 1;
	*ending = 1;
	*play = 0;
	*menu = 0;
	*level = 0;
	*credit = 1;
}

