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


#define GRAVITY -0.3
#define FROTTEMENT 1.1

#define SPRITE_STAND_RIGHT 0
#define SPRITE_STAND_LEFT 1
#define SPRITE_RUN_RIGHT 2
#define SPRITE_RUN_LEFT 3
#define SPRITE_JUMP_RIGHT 4
#define SPRITE_JUMP_LEFT 5
#define SPRITE_ATTACK_RIGHT 6
#define SPRITE_ATTACK_LEFT 7 

#define STICKMAN_HEIGHT 60          /*height of the body of the sticman */
#define STICKMAN_WIDTH 30           /*width of the body of the sticman  */
#define STICKMAN_X_GAP 16           /*gap on x between position and body*/
#define STICKMAN_Y_GAP 3            /*gap on x between position and body*/

#define RUN_STEP 0.2
#define JUMP_STEP 0.2

#define ACCEL_H1  0.05
#define S_MAX_H1  1.5
#define JPOWER_H1 2
#define NB_SPRITE_H1 1
#define SPRITE_SIZE_H1 64
#define LIFE_H1 3

#define MAX_ENNEMIES 100
#define ACCEL_ENNEMY 0.2
#define S_MAX_ENNEMY 1.5
#define JPOWER_ENNEMY 3
#define NB_SPRITE_ENNEMY 1
#define LIFE_ENNEMY 3


#define BASE_LIFE 1
#define BASE_ACCEL 0.1
#define BASE_S_MAX 5
#define BASE_JPOWER 1


#define BASE_LIFE 1
#define BASE_ACCEL 0.1
#define BASE_S_MAX 5
#define BASE_JPOWER 1
#define HIT_RANGE 100



#define TO_THE_LEFT -1
#define TO_THE_RIGHT 1

#define COLL_LEFT 1
#define COLL_RIGHT 2
#define COLL_UP 3
#define COLL_DOWN 4

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
  bool inTheAir; /*true if the sprite is in the air*/
  bool allowedToJump;
  double timerOfJump;
};

typedef struct Physic_t physic_t;

/*Sprite_t: All characteristic for each sprite*/

enum Sprite_type {hero1, ennemy_t, beam_t};
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
  SDL_Rect body;     /*postion of the body*/
  SDL_Surface *spritePicture;

 
};

typedef struct Sprite_t sprite_t;

void hyperespace(sprite_t *sprite);


void spriteInit(sprite_t *sprite, sprite_type type,
		double accel, double smax, int jumpPower,
		int nb_sprite,
		int sprite_size,
		int sprite_number, int max_number,
		int life, int bodyHeight, int bodyWidth,
		SDL_Surface * sprite_picture);

void init_hero1(sprite_t *hero1, SDL_Surface *sprite_picture);
void initEnnemy(sprite_t *charac, int numberEnnemy, SDL_Surface *ennemy_picture);
void init_beam(sprite_t *beam, int beam_nb, SDL_Surface *sprite_picture);

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

/*print.h*/

void set_colorkey_(SDL_Surface *sprite_picture,
		   int R, int G, int B,
		   SDL_Surface *screen);
SDL_Surface* download_sprite_(char *nameSprite);
void displayMap (char** map, sprite_t *hero1, bool *readed,
		 SDL_Surface *screen, SDL_Surface *background,
		 sprite_t *beam, sprite_t *ennemies,
		 int *nbEnnemy, SDL_Surface *ennemy_picture);
int countInTheMap(char **map, char c);
void creaTabSprite(sprite_t *tab, int size_x);
char** crea_Map (int size_x, int size_y);
void free_Map (char** map, int size_y);
void readMap (char* nameMap, char** map);

void drawSprite(sprite_t *sprite, SDL_Surface *screen);

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*animation.h*/

void animSprite ( SDL_Rect * picture, int nbSprite,
		  int spriteSize);
void directionChar (sprite_t *character);
void animChar (sprite_t *character);

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*physics.h*/
void brake(sprite_t *sprite);
void move (sprite_t *sprite);
void run (sprite_t *character, double direction);
void jumping (sprite_t *character);


void jump(sprite_t *character);
void fall(sprite_t *sprite);
//////////////////////////////////////////////////////////
void ennemyPhysics(sprite_t *ennemies, SDL_Surface *screen, int nbEnnemies, sprite_t h1);
//////////////////////////////////////////////////////////


void updateBody(sprite_t *stickman);
int dist(int x1, int y1, int x2, int y2);
void collision(sprite_t *sprite1, sprite_t *sprite2);
int minimum (int a, int b);
int maximum (int a, int b);
bool pointInTheBox(int x, int y, SDL_Rect box);
bool collBetweenBox(SDL_Rect box1, SDL_Rect box2);
int posCompared (SDL_Rect box1, SDL_Rect box2);


////////////////////////////////:
/*Procedures test*/
void testAllProcedure();
void testPointInTheBox();
void  testCollBetweenBox();
void  testPosCompared();
/////////////////////////////////////////////////////


#endif
