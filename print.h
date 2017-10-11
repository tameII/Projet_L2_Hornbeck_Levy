/*title : print.h         */
/*autor : mathieu Levy    */
/*      brandon Horbeck   */

#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

#define ROOM_WIDTH 135
#define ROOM_HEIGHT 90
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720


void set_colorkey_(SDL_Surface *sprite_picture,
		   int R, int G, int B,
		   SDL_Surface *screen);
SDL_Surface* download_sprite_(char *nomSprite);
void displayMap (char** map, SDL_Surface *screen,
		 SDL_Surface *background, SDL_Surface *beam);


char** crea_Map (int size_x, int size_y);
void free_Map (char** map, int size_x);
void readMap (char* nameMap, char** map);


#endif
