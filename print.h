/*title : print.h         */
/*autor : mathieu Levy    */
/*      brandon Horbeck   */

#ifndef PRINT_H
#define PRINT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

#define ROOM_WIDTH 135
#define ROOM_HEIGHT 90
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720


#define GRAVITY -0.7
#define FROTTEMENT 1.1
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*Struct.h*/

/*Physic_t : acceleration and position*/
 
struct Physic_t{
  double x;      /* Position     */ 
  double y;      /*              */
  double sx;     /* Speed        */
  double sy;     /*              */
  double a;      /* Acceleration */
  double smax;   /* SpeedMax     */
  int jumpPower; /* JumpPower    */
};

typedef struct Physic_t physic_t;

/*Sprite_t: All characteristic for each sprite*/

enum Sprite_type {hero1};
typedef enum Sprite_type sprite_type; 

struct Sprite_t{
  sprite_type type;
  physic_t physic; 
  int currentPicture;   
  int currentAnimation; 
  int nb_sprite;
  int size;
  int count;         /*decompte               */
  int sprite_number; /*if you use an array    */
  int max_number;    /*max number of the array*/
  int life;
  SDL_Rect position; /*In the game            */
  SDL_Rect picture;  /*int he spritePicture   */
  SDL_Surface *spritePicture;


};

typedef struct Sprite_t sprite_t;

void spriteInit(sprite_t *sprite, sprite_type type,
		double accel, double smax, int jumpPower,
		int nb_sprite,
		int sprite_size,
		int sprite_number, int max_number,
		int life,
		SDL_Surface * sprite_picture);

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

/*print.h*/

void set_colorkey_(SDL_Surface *sprite_picture,
		   int R, int G, int B,
		   SDL_Surface *screen);
SDL_Surface* download_sprite_(char *nameSprite);
void displayMap (char** map, sprite_t *hero1, bool *readed,
		 SDL_Surface *screen, SDL_Surface *background,
		 SDL_Surface *beam);

char** crea_Map (int size_x, int size_y);
void free_Map (char** map, int size_y);
void readMap (char* nameMap, char** map);

void drawSprite(sprite_t *sprite, SDL_Surface *screen);

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*animation.h*/

void animSprite ( SDL_Rect * picture, int nbSprite,
		  int spriteSize);


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*physics.h*/
void brake(sprite_t *sprite, bool isJumping);
void move (sprite_t *sprite);
void run (sprite_t *character, double direction);
void jumping (sprite_t *character, double *timer);

void jump(sprite_t *character, bool *isJumping, bool *allowedToJump);
void fall(sprite_t *sprite, double *timer, bool *isJumping);
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////



#endif
