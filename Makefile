
stickrescue: game.c print.c print.h

	gcc -Wall -g -std=c99 game.c print.c print.h `sdl-config --cflags --libs` -lm -o stickrescue



