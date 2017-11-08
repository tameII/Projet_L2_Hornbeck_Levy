/*Title: animation.c*/
/*Authors: Brandon Hornbeck */
/*                &         */
/*         Mathieu Levy     */ 

/*This is the file which is running the animation process*/

#include "animation.h"

/*  position is the pointer of the SDL_Rect which determines the current sprite used, and nbSprite is the number of 
 *sprites in the animation and spriteSize is the size of one sprite*/

void animSprite ( SDL_Rect * position, int nbSprite, int spriteSize)
{
  position->x += spriteSize;
  if (position->x == nb_sprite * spriteSize){
    position->x = 0;
  }
}
