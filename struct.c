/**************************/
/*title: struct.h         */
/*Author: Mathieu Levy    */
/*              &         */
/*        Brandon Hornbeck*/
/**************************/
/*You can find here initialising function*/

#include "struct.h"



void spriteInit(sprite_t *sprite, sprite_type type,
		int accel, int smax,
		int nb_sprite,
		int sprite_size,
		int sprite_number, int max_number,
		int life,
		SDL_Surface * sprite_picture)
{

  sprite->type = type;
  sprite->physic.a = accel ;
  sprite->physic.smax = smax;
  sprite->currentPicture = 0;
  sprite->currentAnimation = 0;
  sprite->size = sprite_size;
  sprite->nb_sprite = nb_sprite;
  sprite->size = sprite_size;
  sprite->count = 0;
  sprite->sprite_number = sprite_number;
  sprite->max_number = max_number;
  sprite->life = life;
  sprite->spritePicture = sprite_picture;
  

}


