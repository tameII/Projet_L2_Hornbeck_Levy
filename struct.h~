/**************************/
/*title: struct.h         */
/*Author: Mathieu Levy    */
/*              &         */
/*        Brandon Hornbeck*/
/**************************/
/*https://www.rocq.inria.fr/secret/Anne.Canteaut/COURS_C/cours.pdf*/
/*You can find here the structures of all objects*/
#ifndef STRUC_H
#define STRUC_H

#include "print.h"

/*Physic_t : acceleration and position*/
 
struct Physic_t{
  double x;    /* Position    */ 
  double y;    /*             */
  double sx;   /*  Speed      */
  double sy;   /*             */
  double smax; /*   SpeedMax  */
  int a;       /*Acceleration */
 
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


#endif
