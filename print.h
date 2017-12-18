/*title : print.h         */
/*autor : mathieu Levy    */
/*      brandon Horbeck   */

#ifndef PRINT_H 
#define PRINT_H

#include <stdbool.h>   
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <SDL.h>

#define ROOM_WIDTH 135
#define ROOM_HEIGHT 90
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define NB_LVL 8
#define WIDTH_MENU_BUTTON 200
#define HEIGHT_MENU_BUTTON 50

#define COUNT_ENDING 1700
 
#define GRAVITY -0.05 //-0.1
#define FROTTEMENT 1.1

#define STUNT_TIMER 500
#define TIMER_OF_REST_FROM_JUMP 90

#define SPRITE_STAND_RIGHT 0
#define SPRITE_STAND_LEFT 1
#define SPRITE_RUN_RIGHT 2
#define SPRITE_RUN_LEFT 3
#define SPRITE_JUMP_RIGHT 4
#define SPRITE_JUMP_LEFT 5
#define SPRITE_ATTACK_RIGHT 6
#define SPRITE_ATTACK_LEFT 7 
#define SPRITE_STUNT_RIGHT 8
#define SPRITE_STUNT_LEFT 9
#define SPRITE_LOSE_LEFT 10
#define SPRITE_LOSE_RIGHT 11
#define SPRITE_WIN1 12
#define SPRITE_WIN2 13

#define COUNT_ANIM_WIN 80
#define COUNT_ANIM_LOSE 80
 
#define STICKMAN_HEIGHT 60          /*height of the body of the stickman */
#define STICKMAN_WIDTH 22           /*width of the body of the stickman  */
#define STICKMAN_X_GAP 20           /*gap on x between position and body*/
#define STICKMAN_Y_GAP 3            /*gap on x between position and body*/

#define RUN_STEP 0.002
#define JUMP_STEP 0.5

#define ACCEL_H1  0.04
#define S_MAX_H1  1.8
#define JPOWER_H1 1
#define NB_SPRITE_H1 1
#define SPRITE_SIZE_H1 64
#define LIFE_H1 7

#define MAX_ENNEMIES 1000
#define ACCEL_ENNEMY 0.05
#define S_MAX_ENNEMY 1.5
#define JPOWER_ENNEMY 1
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
#define HIT_RANGE 40
#define HIT_RETREAT 0.1
#define TIMER_ATTACK 700

#define SEE_X 400
#define SEE_Y 150
#define JUMP_RANGE 25

#define TO_THE_LEFT -1
#define TO_THE_RIGHT 1

#define COLL_LEFT 1
#define COLL_RIGHT 2
#define COLL_UP 3
#define COLL_DOWN 4


#define HP_X 100
#define HP_Y 100
#define HP_H 20
#define HP_W 400
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
  int timerOfRestFromJump;
  bool isJumping;
  bool isAttacking; /*true if is attacking*/
  int attackX;  /*attack point*/
  int attackY;
  bool allowedToHit;
  bool stunt; /*true if the stickman has been hitten*/
  int stunt_timer; /*when comes to zero stunt =false */
  int timerAttack;

};

typedef struct Physic_t physic_t;

/*Sprite_t: All characteristic for each sprite*/

enum Sprite_type {hero1, ennemy_t, beam_t, menu_t};
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
  int killed;
  SDL_Rect position_aft;
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
		int life,
		SDL_Surface * sprite_picture);

void init_hero1(sprite_t *hero1, SDL_Surface *sprite_picture);
void initEnnemy(sprite_t *charac, int numberEnnemy, SDL_Surface *ennemy_picture);
void init_beam(sprite_t *beam, int beam_nb, SDL_Surface *sprite_picture);
void updateBeam(sprite_t *beam);
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

/*print.h*/

void set_colorkey_(SDL_Surface *sprite_picture,
		   int R, int G, int B,
		   SDL_Surface *screen);
SDL_Surface* download_sprite_(char *nameSprite);


void readMap (char** map, sprite_t *hero1, bool *readed,
	      SDL_Surface *screen, SDL_Surface *background,
	      sprite_t *beam, int nbBeam, SDL_Surface *beam_picture,
	      sprite_t *ennemies, SDL_Surface *ennemy_picture);

int countInTheMap(char **map, char c);
void creaTabSprite(sprite_t *tab, int size_x);
char** crea_Map (int size_x, int size_y);
void free_Map (char** map, int size_y);
void readTxt (char* nameMap, char** map);

void drawSprite(sprite_t sprite, SDL_Surface *screen);

void displayAll(SDL_Surface *background, SDL_Surface *screen,
		sprite_t *beam, int beam_nb,
		sprite_t h1,
		sprite_t *ennemies, int nbEnnemies);

void ControlHP(sprite_t *h1, SDL_Rect *image);
void blitHp(sprite_t h1, SDL_Surface *hp_picture,
	    SDL_Rect image, SDL_Surface *screen, SDL_Rect position, SDL_Surface *hpR_picture, SDL_Rect hpR_position);
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*animation.h*/

void animSprite (sprite_t *character);
void directionChar (sprite_t *character);
void animChar (sprite_t *character);
void endAttack(sprite_t *character);
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////

/*physics.h*/
void brake(sprite_t *sprite);
void move (sprite_t *sprite);
void run (sprite_t *character, double direction);
void jumping (sprite_t *character);

void copySDL_Rect(SDL_Rect *copy, SDL_Rect *past);
void copySDL_RectToDouble(SDL_Rect *copy, double *x, double *y);

void jump(sprite_t *character);
void fall(sprite_t *sprite);
void hit(sprite_t *character);
void placeHitPoint (sprite_t *character);
//////////////////////////////////////////////////////////
void h1Physics(sprite_t *h1, sprite_t *beam, int beam_nb);
//////////////////////////////////////////////////////////
void stuntAction(sprite_t *sprite);
void timerAttackAction (sprite_t *sprite);
bool seen(int distx, int disty);
void followIA(sprite_t *sprite, sprite_t *h1);
void hitAction(sprite_t *bully, sprite_t *victim);
void attackIA(sprite_t *ennemy, sprite_t h1);
///////////////////////////////////:
void ennemyPhysics(sprite_t *ennemies, int nbEnnemies,
		   sprite_t *beam, int beam_nb, sprite_t *h1);

//////////////////////////////////////////////////////////


void updateBody(sprite_t *stickman);
int dist(int x1, int y1, int x2, int y2);

void collision(sprite_t *beam, int beam_nb, sprite_t *sprite);
void collisionBeam(sprite_t *beam, sprite_t *sprite,
		   bool *floor, bool *ceiling,
		   bool *leftWall, bool *rightWall);
  
int minimum (int a, int b);
int maximum (int a, int b);
bool pointInTheBox(int x, int y, SDL_Rect box);
bool collBetweenBox(SDL_Rect box1, SDL_Rect box2);
void posCompared (SDL_Rect box1, SDL_Rect box2, int *px, int *py);


//////////////////////////////////
void quitGame(int *endMenu, int *gameOver, int *ending);
void launchMenu(int *gameOver, int *ending,
		int *menu, int *play, int *level, int *credit);
void launchGame(int *gameOver, int *ending,
		int *menu, int *play, int *level, int *credit);
void launchSelectLevel(int *gameOver, int *ending,
		       int *menu, int *play, int *level, int *credit);
void launchCredit(int *gameOver, int *ending,
		  int *menu, int *play, int *level, int *credit);
void launchEnding(int *gameOver, int *ending,
		  int *menu, int *play, int *level, int *credit);

void wipe_tab(int *tab, int N);
void placeMenuButton(sprite_t *spriteButton, int x, int y);
void initMenu(sprite_t *spriteA, SDL_Surface *A_picture,
	      sprite_t *spriteB, SDL_Surface *B_picture,
	      sprite_t *spriteC, SDL_Surface *C_picture,
	      sprite_t *spriteD, SDL_Surface *D_picture,
	      sprite_t *spriteE, SDL_Surface *E_picture,
	      sprite_t *spriteF, SDL_Surface *F_picture);
void drawPage(SDL_Surface *background, SDL_Surface *screen,
	      sprite_t *spriteA, sprite_t *spriteB,
	      sprite_t *spriteC, sprite_t *spriteD,
	      sprite_t *spriteE, sprite_t *spriteF);
void putPicture(sprite_t *sprite, SDL_Surface *surface);
void selectButton(sprite_t *spriteA, SDL_Surface *A_picture,
	      sprite_t *spriteB, SDL_Surface *B_picture, 
	      sprite_t *spriteC, SDL_Surface *C_picture,
	      sprite_t *spriteD, SDL_Surface *D_picture,
	      sprite_t *spriteE, SDL_Surface *E_picture,
		  sprite_t *spriteF, SDL_Surface *F_picture);
void handleMenuReturn(int *endMenu, int *gameOver, int *ending,
		      int *menu, int *play, int *level, int *credit,
		      int *actualPage, int *lvlChoosen,
		      sprite_t *spriteA, SDL_Surface *ASelect_picture,
		      sprite_t *spriteB, SDL_Surface *BSelect_picture,
		      sprite_t *spriteC, SDL_Surface *CSelect_picture,
		      sprite_t *spriteD, SDL_Surface *DSelect_picture,
		      sprite_t *spriteE, SDL_Surface *ESelect_picture,
		      sprite_t *spriteF, SDL_Surface *FSelect_picture);
void downMenu(int *placement,
	      sprite_t *spriteA, SDL_Surface *A_picture, SDL_Surface *ASelect_picture,
	      sprite_t *spriteB, SDL_Surface *B_picture, SDL_Surface *BSelect_picture,
	      sprite_t *spriteC, SDL_Surface *C_picture, SDL_Surface *CSelect_picture,
	      sprite_t *spriteD, SDL_Surface *D_picture, SDL_Surface *DSelect_picture,
	      sprite_t *spriteE, SDL_Surface *E_picture, SDL_Surface *ESelect_picture,
	      sprite_t *spriteF, SDL_Surface *F_picture, SDL_Surface *FSelect_picture);
void upMenu(int *placement,
	    sprite_t *spriteA, SDL_Surface *A_picture, SDL_Surface *ASelect_picture,
	    sprite_t *spriteB, SDL_Surface *B_picture, SDL_Surface *BSelect_picture,
	    sprite_t *spriteC, SDL_Surface *C_picture, SDL_Surface *CSelect_picture,
	    sprite_t *spriteD, SDL_Surface *D_picture, SDL_Surface *DSelect_picture,
	    sprite_t *spriteE, SDL_Surface *E_picture, SDL_Surface *ESelect_picture,
	    sprite_t *spriteF, SDL_Surface *F_picture, SDL_Surface *FSelect_picture);
void collisionMenuMouseLeft(int x, int y, int *placement,
			    sprite_t *spriteA,
			    SDL_Surface *A_picture, SDL_Surface *ASelect_picture,
			    sprite_t *spriteB,
			    SDL_Surface *B_picture, SDL_Surface *BSelect_picture,
			    sprite_t *spriteC,
			    SDL_Surface *C_picture, SDL_Surface *CSelect_picture,
			    sprite_t *spriteD,
			    SDL_Surface *D_picture, SDL_Surface *DSelect_picture,
			    sprite_t *spriteE,
			    SDL_Surface *E_picture, SDL_Surface *ESelect_picture,
			    sprite_t *spriteF,
			    SDL_Surface *F_picture, SDL_Surface *FSelect_picture);
void selectionLevel(char **map, int lvlChoosen);
void setHp(SDL_Rect *hp_position,SDL_Rect *hp_image,
	   SDL_Rect *hpR_position);
void animEnding(sprite_t *h1, int win);
void spriteDead(sprite_t *h1, sprite_t *ennemies, int nbEnnemies, int *win,
		int *gameOver, int *ending,
		int *menu, int *play, int *level, int *credit);
#endif
