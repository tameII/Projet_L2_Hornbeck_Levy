/*this is the file where every display function is encoded*/

#include "print.h"



///////////////////////////////////////////////////////////
/*auxiliary function : set colorkey*/
void set_colorkey_(SDL_Surface *sprite_picture,
		   int R, int G, int B,
		   SDL_Surface *screen)
{
  int colorkey;
  colorkey = SDL_MapRGB(screen->format, R, G, B);
  SDL_SetColorKey(sprite_picture, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

/*auxiliary fonction to downloadsprite*/
SDL_Surface* download_sprite_(char *nomSprite)
{
 
  SDL_Surface *temp, *nom;
  temp = SDL_LoadBMP(nomSprite);
  nom = SDL_DisplayFormat(temp);;
  SDL_FreeSurface(temp);
  
  return nom;
}
////////////////////////////////////////////////////////////


/* display the map                              */
/* She is readed one full time to know the base *
 * position of all character                    */
void displayMap (char** map, sprite_t *hero1, bool *readed,
		 SDL_Surface *screen, SDL_Surface *background,
		 SDL_Surface *beam)
{

  
  SDL_Rect pos;
  int i,j;
  SDL_BlitSurface(background, NULL, screen, NULL);
  for (i = 0; i < ROOM_HEIGHT; i++){
    for (j = 0; j < ROOM_WIDTH; j++){
      
      // printf("%c", map[i][j]);
      //printf("i : %d, j : %d \n",i,j);
      
      switch (map[i][j]) {
      case '1':
	pos.x = j*8;   
	pos.y = i*8;
	SDL_BlitSurface(beam, NULL, screen, &pos);
	break;
      case '3':
	if(!readed){
	  //hero1.physic.x = j*8;
	  printf("readed\n");
	}
	break;
      default:
	break;
      }
    }
  }
  *readed = true;
}


/*Memory allocation for the map                                  *
 *Declaration of "pointer of pointer(**)" who point on pointer(*)*
 *association of (**) with (*) who point on the char             */
char** crea_Map (int size_x, int size_y)
{
  int i;
  char** tab;  
  tab = (char**)malloc(size_y * sizeof(char*)); /*Declaration*/ 
  for(i=0; i<size_y; i++){
    tab[i] = (char*)malloc(size_x * sizeof(char)); /*Association*/
  }
  return tab;
}

/* Free the tab: take the y of the tab  *
 * and free all the y pointer           *
 * Next you just need to free the tab ! */
void free_Map (char** map, int size_y)
{
  int y;
  for (y=0; y<size_y; y++){
	free(map[y]);           //free the pointer first
    }
    free(map);                //free the tab
    map = NULL;               //security
  }

/*Read the entry file and put all char in a tab[][](map) */
void readMap (char* nameMap, char** map)
{
  char C; /*the actual char red*/
  int countColomn = 0, countLane = 0;
  FILE* txt = fopen(nameMap, "r");

  
  
  do 
  {
    C = fgetc(txt);  /* storing the actual data*/
    map[countLane][countColomn] = C;
    countColomn++;
    if (countColomn >= ROOM_WIDTH){
      countColomn = 0;
      countLane++;
    }
  } while (C != EOF && countLane < ROOM_HEIGHT);
  fclose(txt); 
 
}	

/*Warning: this function is not really effective*/
/*We need a new one*/
void drawSprite(sprite_t sprite, SDL_Surface *screen)
{
  SDL_BlitSurface(sprite.spritePicture,
		  &sprite.position, screen,
		  &sprite.picture);

}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*struct.c*/


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

  if (sprite->type == hero1){
    printf("OMG, spriteInit WORK\n");
  }

}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*animation.c*/

/*  position is the pointer of the SDL_Rect which determines the current sprite used, and nbSprite is the number of 
 *sprites in the animation and spriteSize is the size of one sprite*/

void animSprite ( SDL_Rect * position, int nbSprite, int spriteSize)
{
  position->x += spriteSize;
  if (position->x == nbSprite * spriteSize){
    position->x = 0;
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*physics.c*/

/*This file will rule all the movements, jumps, and landings*/

/*#define GRAVITY -9.8*/

/*move a sprite by his speed vector*/
void move (sprite_t *sprite)
{
  sprite -> physic.x += sprite -> physic.sx;
  sprite -> physic.y += sprite -> physic.sy;
  sprite -> position.x = (int) sprite -> physic.x;
  sprite -> position.y = (int) sprite -> physic.y;
  printf("sx: %f, sy: %f",sprite -> physic.sx, sprite -> physic.sy );
  printf("x: %d, y: %d \n", sprite->position.x, sprite->position.y);
}


/*make a character running, direction = -1 if left, 1 if right*/
void run (sprite_t *character, int direction)
{
  character->physic.sx += (character->physic.a)*direction;  /*the speed rise by adding the acceleration*/
  if (abs(character->physic.sx) > character->physic.smax){
    character->physic.sx = character->physic.smax;  /*if the speed of the sprite is higher than its speed limit, its speed becomes its speed limit*/ 
  }
}

/*jump finds the appropriate jump speed of a character, if there is a colision with the ground, timer must be 0 now*/
void jumping (sprite_t *character, double *timer)
{
   *timer += 1;
   character->physic.sy = (GRAVITY * *timer)
     + character-> physic.jumpPower;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
