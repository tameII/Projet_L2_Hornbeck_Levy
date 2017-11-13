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
SDL_Surface* download_sprite_(char *nameSprite)
{
 
  SDL_Surface *temp, *name;
  temp = SDL_LoadBMP(nameSprite);
  name = SDL_DisplayFormat(temp);;
  SDL_FreeSurface(temp);
  
  return name;
}
////////////////////////////////////////////////////////////
/*struct.c*/
void spriteInit(sprite_t *sprite, sprite_type type,
	        double accel, double smax, int jumpPower,
		int nb_sprite,
		int sprite_size,
		int sprite_number, int max_number,
		int life,
		SDL_Surface * sprite_picture)
{

  sprite->type = type;
  sprite->physic.x =  0;
  sprite->physic.y =  0;
  sprite->physic.sx = 0;
  sprite->physic.sy = 0;
  sprite->physic.a = accel ;
  sprite->physic.smax = smax;
  sprite->physic.jumpPower = jumpPower;
  sprite->currentPicture = 0;
  sprite->currentAnimation = 0;
  sprite->size = sprite_size;
  sprite->nb_sprite = nb_sprite;
  sprite->size = sprite_size;
  sprite->count = 0;
  sprite->sprite_number = sprite_number;  /* Number in the array               */
  sprite->max_number = max_number;        /* Number max of sprite in the array */
  sprite->life = life;
  sprite->picture.x = 0;
  sprite->picture.y = 0;
  sprite->picture.w = sprite_size;
  sprite->picture.h = sprite_size;
  sprite->spritePicture = sprite_picture;

}


void init_hero1(sprite_t *h1, SDL_Surface *sprite_picture)
{
  
  spriteInit( h1, hero1,
	      ACCEL_H1 , S_MAX_H1, JPOWER_H1,
	      NB_SPRITE_H1, SPRITE_SIZE_H1,
	      1, 1,          /*if we talk about a tab of sprite*/
	      LIFE_H1,
	      sprite_picture);

}

void initEnnemy(sprite_t *charac, int numberEnnemy, SDL_Surface *ennemy_picture)
{
  spriteInit(charac, ennemy_t, ACCEL_ENNEMY, S_MAX_ENNEMY, JPOWER_ENNEMY,
	     NB_SPRITE_ENNEMY, SPRITE_SIZE_H1, numberEnnemy, MAX_ENNEMIES, 
	     LIFE_ENNEMY, ennemy_picture);
}

void init_beam(sprite_t *beam, int beam_nb, SDL_Surface *sprite_picture)
{
  printf("rentré dans init beam\n");
  int i;
  for(i=0; i<beam_nb; i++){
    //  printf("i = %d \n", i);
    spriteInit(&beam[i], beam_t, BASE_ACCEL, BASE_S_MAX, BASE_JPOWER, 1, 
	     8, beam_nb, 1, BASE_LIFE, sprite_picture);
  }
  printf("init beam work\n");
}

///////////////////////////////////////////////////////////

/* display the map                              */
/* She is readed one full time to know the base *
 * position of all character                    */
void displayMap (char** map, sprite_t *hero1, bool *readed,
		 SDL_Surface *screen, SDL_Surface *background,
		 sprite_t *beam, sprite_t *ennemies, int *nbEnnemy,
		 SDL_Surface *ennemy_picture)
{
  int currBeam = 0;
  int currEnnemy = 0;
  int i,j;
  SDL_BlitSurface(background, NULL, screen, NULL);
  for (i = 0; i < ROOM_HEIGHT; i++){
    for (j = 0; j < ROOM_WIDTH; j++){
      
      // printf("%c", map[i][j]);
      //printf("i : %d, j : %d \n",i,j);
      
      switch (map[i][j]) {
      case '1':
	if(!*readed){
	  beam[currBeam].position.x = j*8;
	  beam[currBeam].position.y = i*8;
	}
  	SDL_BlitSurface(beam->spritePicture, NULL, screen, &beam[currBeam].position);
	currBeam += 1;
	break;
      case '3':
	if(!*readed){
	  hero1->physic.x = j*8;
	  hero1->physic.y = i*8;
	}
	break;
      case '7':
	if (!*readed){
	  initEnnemy(&ennemies[currEnnemy], currEnnemy, ennemy_picture);
	  ennemies[currEnnemy].physic.x = j*8;
	  ennemies[currEnnemy].physic.y = i*8;
	  printf("7 readed\n");
	  printf("x = %f  ||  y = %f\n",ennemies[currEnnemy].physic.x,ennemies[currEnnemy].physic.y);
	  currEnnemy += 1;
	  printf("currEnnemy = %d\n",currEnnemy);
	  *nbEnnemy += 1;
	  printf("nbEnnemy = %d\n",*nbEnnemy);
	}
	break;
      default:
	break;
      }
    }
  }
  for (i=0; i<=*nbEnnemy; i++){
    if (!*readed){
      printf("ennemy %d || x = %f || y = %f\n",i,ennemies[i].physic.x,ennemies[i].physic.y);
      printf("nbEnnemy = %d\n",*nbEnnemy);
    }
  }
  *readed = true;
}


int countInTheMap(char **map, char c)
{
  int i,j;
  int count = 0;

  for (i = 0; i < ROOM_HEIGHT; i++){
    for (j = 0; j < ROOM_WIDTH; j++){
      if(map[i][j] == c) {
	count +=1;
      }
    }
  }
  return count;
}

void creaTabSprite(sprite_t *tab, int size_x)
{
  
  tab = (sprite_t*)malloc(size_x * sizeof(sprite_t*));

  
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
void drawSprite(sprite_t *sprite, SDL_Surface *screen)
{
  SDL_BlitSurface(sprite->spritePicture,
		  &sprite->picture, screen,
		  &sprite->position);

}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*animation.c*/

/*  picture is the current sprite used,                *
 *  nbSprite is the number of sprites in the animation */

void animSprite ( SDL_Rect * picture, int nbSprite, int spriteSize)
{
  picture->x += spriteSize;
  if (picture->x >= nbSprite * spriteSize){
    picture->x = 0;
  }
}
void directionChar (sprite_t *character)
{
  if (character->physic.sx > 0 && character->physic.sx < RUN_STEP){
    // printf("standRight\n");
    character->currentPicture = SPRITE_STAND_RIGHT;
    character->nb_sprite = 1;
  }
  if (character->physic.sx < 0 && character->physic.sx > -RUN_STEP){
    //  printf("standLeft\n");
    character->currentPicture = SPRITE_STAND_LEFT;
    character->nb_sprite = 1;
  }
  if (character->physic.sx > 0 && character->physic.sx > RUN_STEP){
    // printf("runRight\n");
    character->currentPicture = SPRITE_RUN_RIGHT;
    character->nb_sprite = 4;
  }
  if (character->physic.sx < 0 && character->physic.sx < -RUN_STEP){
    //printf("runLeft \n");
    character->currentPicture = SPRITE_RUN_LEFT;
    character->nb_sprite = 4;
  }
}

void animChar (sprite_t *character)
{

  directionChar(character);
  character->picture.y = character->size * character->currentPicture;

  animSprite(&character->picture, character->nb_sprite, character->size);
  /*
  printf("character->nb_sprite : %d \n", character->nb_sprite);
  printf("character->size : %d \n", character->size);
  printf("\n");
  printf("character->picture.x : %d \n", character->picture.x);
  printf("character->picture.y : %d \n", character->picture.y);
  printf("character->picture.h : %d \n", character->picture.h);
  printf("character->picture.w : %d \n", character->picture.w);
  printf("\n");
  */
  
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*physics.c*/

/*This file will rule all the movements, jumps, and landings*/

/*#define GRAVITY -9.8*/

/*Brake if not in the air*/
void brake(sprite_t *sprite)
{

  if(!sprite->physic.inTheAir){
    /*if the sprite go the left*/
    if(sprite->physic.sx < 0.0){
      sprite->physic.sx /= FROTTEMENT;
    }  
    /*else if the sprite go to the right*/
    if(sprite->physic.sx > 0.0){
      sprite->physic.sx /= FROTTEMENT;
    }
  }
  
}

/*move a sprite by his speed vector*/
void move (sprite_t *sprite)
{
  
  sprite -> physic.x += sprite -> physic.sx;
  sprite -> physic.y += sprite -> physic.sy;
  sprite -> position.x = (int) sprite -> physic.x;
  sprite -> position.y = (int) sprite -> physic.y;
  // printf("sx: %f, sy: %f",sprite -> physic.sx, sprite -> physic.sy );
  // printf("x: %d, y: %d \n", sprite->position.x, sprite->position.y);
}


/*make a character running, direction = -1 if left, 1 if right*/
void run (sprite_t *character, double direction)
{

  /*the speed rise by adding the acceleration*/
  character->physic.sx += (character->physic.a) * direction;

  /*don't pass over the max speed */
  if (character->physic.sx >= character->physic.smax){
    character->physic.sx = character->physic.smax;
  }
  else if(character->physic.sx <= -character->physic.smax){
    character->physic.sx = -character->physic.smax;
  }
  
}



void jump(sprite_t *character, bool *allowedToJump)
{
  if(!character->physic.inTheAir && *allowedToJump){
    character->physic.sy = -character->physic.jumpPower;
    character->physic.inTheAir = true;
  }
}

void fall(sprite_t *sprite, double *timer)
{
  if(sprite->physic.inTheAir){
     sprite->physic.sy -= GRAVITY * *timer;
    *timer += 0.001;
  }
  if(!sprite->physic.inTheAir){
    sprite->physic.sy = 0;
  }
  
}
//////////////////////////////////////////////////////////
/*Take two sprite : return true if the two sprite are in contact*/
bool collideSpriteTest(sprite_t sprite1, sprite_t sprite2)
{
  int cu = 0;
  int cv = 0;
  return collideSpriteTestParam(sprite1, sprite2, sprite1.spritePicture->format
		      ,&cu, &cv);
}

bool collideSpriteTestParam(sprite_t sprite1, sprite_t sprite2, SDL_PixelFormat* format,
		  int * cu, int * cv) 
{
  /* rough test using the bounding boxes (bb) only */
  bool test = !(sprite2.physic.x > sprite1.physic.x + sprite1.size ||
		sprite2.physic.x + sprite2.size < sprite1.physic.x ||
		sprite2.physic.y > sprite1.physic.y + sprite1.spritePicture->h ||
		sprite2.physic.y + sprite2.spritePicture->h < sprite1.physic.y);

  /* if the rough test succeeded, a fine test is performed using             *
   *  the colorkeys (transparency colors) of the sprites (may be optimized!) */
  if (test) {
    Uint32 *bmp1 = (Uint32*)malloc(sizeof(Uint32) * sprite1.size *
				   sprite1.spritePicture->h),
      *sprite_it, *bmp_it;
    Uint32 *bmp2 = (Uint32*)malloc(sizeof(Uint32) * sprite2.size *
				   sprite2.spritePicture->h);
    int u, v, v1 = 0; 

    /* lock the video memory and copy the sprite bitmaps into cpu memory */
    SDL_LockSurface(sprite1.spritePicture);
    SDL_LockSurface(sprite2.spritePicture);
    bmp_it = bmp1;
    sprite_it = (Uint32*)(sprite1.spritePicture->pixels) +  sprite1.currentPicture/2
      * sprite1.size;
    for (v = 0; v < sprite1.spritePicture->h; v++) {
      for (u = 0; u < sprite1.size; u++) {
	*bmp_it++ = *sprite_it++;
      }
      sprite_it += (sprite1.spritePicture->w - sprite1.size);
    }
    bmp_it = bmp2;
    sprite_it = (Uint32*)(sprite2.spritePicture->pixels) +  sprite2.currentPicture/2
      * sprite2.size;
    for (v = 0; v < sprite2.spritePicture->h; v++) {
      for (u = 0; u < sprite2.size; u++) {
	*bmp_it++ = *sprite_it++;
      }
      sprite_it += (sprite2.spritePicture->w - sprite2.size);
    }
    SDL_UnlockSurface(sprite1.spritePicture);
    SDL_UnlockSurface(sprite2.spritePicture);

    bmp_it = bmp1;
    test = false;

    /* for each pixel p1 in bmp1, until test = true... */
    while (!test && v1 < sprite1.spritePicture->h) {
      int u1 = 0;
      while (!test && u1 < sprite1.size) {
	/* get the screen coordinates of pixel p1 */
	int screen_u = u1 + sprite1.physic.x;
	int screen_v = v1 + sprite1.physic.y;

	/* if the screen coordinates of p1 are inside the bb of sprite2... */
	if (screen_u >= sprite2.physic.x &&
	    screen_u < sprite2.physic.x + sprite2.size &&
	    screen_v >= sprite2.physic.y &&
	    screen_v < sprite2.physic.y + sprite2.spritePicture->h) {
	  Uint32 pixel1 = *bmp_it;
	  unsigned int col1;
	  Uint8 r, g, b;
	  
	  /* get the color col1 of p1*/
	  SDL_GetRGB(pixel1, format, &r, &g, &b);
	  col1 = SDL_MapRGB(format, r, g, b);

	  /* if col1 is a NON transparent color... */
	  if (col1 != sprite1.spritePicture->format->colorkey) {
	    Uint32 pixel2;
	    unsigned int col2;
	    Uint8 r, g, b;
	    int u2, v2;

	    /* get the local coordinates of pixel p2 in sprite2 corresponding *
	     *  to the screen coordinates of p1                               */
	    u2 = screen_u - sprite2.physic.x;
	    v2 = screen_v - sprite2.physic.y;
	    
	    /* get the color col2 of p2 */
	    pixel2 = *(bmp2 + u2 + v2 * sprite2.size);
	    SDL_GetRGB(pixel2, format, &r, &g, &b);
	    col2 = SDL_MapRGB(format, r, g, b);
	    
	    /* if col2 is also a non transparent color, a collision occurs  */
	    if (col2 != sprite2.spritePicture->format->colorkey) {
	      test = true;
	      *cu = screen_u; 
	      *cv = screen_v;
	    }
	  }
	}
	u1++;
	bmp_it++;
      }
      v1++;
    }
    free(bmp1);
    free(bmp2);
  }
  
  return test;
}

//////////////////////////////////////////////////////////
