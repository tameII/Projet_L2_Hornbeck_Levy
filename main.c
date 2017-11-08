/*this is the main file*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>


#include "print.c"
#include "mapreader.c"
#include "game.c"


int main (int argc, char *argv[])
{
  game();
  return EXIT_SUCCESS;
}
