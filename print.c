/*this is the file where every display function is encoded*/

#include "print.h"

/*fonction pour faire réapparaitre un sprite de l'autre coté coté de l'écran */
/*Elle sert just pour les test pour le moment                                */
/*J'ai retiré la possibilité de réapparaitre en bas depuis le haut           */
/*(pour pas faire de FLOUSHFLOUSHFLOSHFLSHFSHFH a la portal)                 */
void hyperespace(sprite_t *sprite)
{
  if(sprite->physic.x < 0){
    sprite->physic.x = sprite->physic.x + SCREEN_WIDTH - sprite->size;
  }
  else if(sprite->physic.x > SCREEN_WIDTH - sprite->size){
    sprite->physic.x = sprite->physic.x - SCREEN_WIDTH + sprite->size;
  }
  if(sprite->physic.y > SCREEN_HEIGHT - sprite->size){
    sprite->physic.y = SCREEN_HEIGHT - sprite->size;
    sprite->physic.timerOfJump = 0;
    sprite->physic.inTheAir = false;
    sprite->physic.allowedToJump = true;
  }
}



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
		int life, int bodyHeight, int bodyWidth,
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
  sprite->body.h = STICKMAN_HEIGHT;
  sprite->body.w = STICKMAN_WIDTH;
  sprite->physic.allowedToJump = true;
  sprite->physic.timerOfJump = 0;

}


void init_hero1(sprite_t *h1, SDL_Surface *sprite_picture)
{
  
  spriteInit( h1, hero1,
	      ACCEL_H1 , S_MAX_H1, JPOWER_H1,
	      NB_SPRITE_H1, SPRITE_SIZE_H1,
	      1, 1,          /*if we talk about a tab of sprite*/
	      LIFE_H1, STICKMAN_HEIGHT, STICKMAN_WIDTH,
	      sprite_picture);

}

void initEnnemy(sprite_t *charac, int numberEnnemy, SDL_Surface *ennemy_picture)
{
  spriteInit(charac, ennemy_t, ACCEL_ENNEMY, S_MAX_ENNEMY, JPOWER_ENNEMY,
	     NB_SPRITE_ENNEMY, SPRITE_SIZE_H1, numberEnnemy, MAX_ENNEMIES, 
	     LIFE_ENNEMY, STICKMAN_HEIGHT, STICKMAN_WIDTH, ennemy_picture);
}

void init_beam(sprite_t *beam, int beam_nb, SDL_Surface *sprite_picture)
{

  int i;
  for(i=0; i<beam_nb; i++){
    //  printf("i = %d \n", i);
    spriteInit(&beam[i], beam_t, BASE_ACCEL, BASE_S_MAX, BASE_JPOWER, 1, 
	     8, beam_nb, 1, BASE_LIFE, 8, 8, sprite_picture);
    updateBody(&beam[i]);
  }

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
	  //  printf("x = %f  ||  y = %f\n",ennemies[currEnnemy].physic.x,ennemies[currEnnemy].physic.y);
	  currEnnemy += 1;
	  // printf("currEnnemy = %d\n",currEnnemy);
	  *nbEnnemy += 1;
	  // printf("nbEnnemy = %d\n",*nbEnnemy);
	}
	break;
      default:
	break;
      }
    }
  }
  /*  for (i=0; i<=*nbEnnemy; i++){
    if (!*readed){
      printf("ennemy %d || x = %f || y = %f\n",i,ennemies[i].physic.x,ennemies[i].physic.y);
      printf("nbEnnemy = %d\n",*nbEnnemy);
    }
    }*/
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
    character->nb_sprite = 4;
    if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP){
      character->currentPicture = SPRITE_JUMP_RIGHT;
      character->nb_sprite = 4;
    } 
  }
  if (character->physic.sx < 0 && character->physic.sx > -RUN_STEP){
    //  printf("standLeft\n");
    character->currentPicture = SPRITE_STAND_LEFT;
    character->nb_sprite = 4;
    if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP){
      character->currentPicture = SPRITE_JUMP_LEFT;
      character->nb_sprite = 4;
    } 
  }
  if (character->physic.sx > 0 && character->physic.sx > RUN_STEP){
    // printf("runRight\n");
    character->currentPicture = SPRITE_RUN_RIGHT;
    character->nb_sprite = 8;
    if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP){
      character->currentPicture = SPRITE_JUMP_RIGHT;
      character->nb_sprite = 4;
    }
  }
  if (character->physic.sx < 0 && character->physic.sx < -RUN_STEP){
    //printf("runLeft \n");
    character->currentPicture = SPRITE_RUN_LEFT;
    character->nb_sprite = 8;
    if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP){
      character->currentPicture = SPRITE_JUMP_LEFT;
      character->nb_sprite = 4;
    } 
  }


}

void animChar (sprite_t *character)
{
  
  directionChar(character);
  character->picture.y = character->size * character->currentPicture;
  character->count += 1;
  if (character->count >= 100){
  animSprite(&character->picture, character->nb_sprite, character->size);
  character->count = 0;
  }
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



void jump(sprite_t *character)
{
  if(!character->physic.inTheAir && character->physic.allowedToJump){
    character->physic.sy = -character->physic.jumpPower;
    character->physic.inTheAir = true;
  }
}

void fall(sprite_t *sprite)
{
  if(sprite->physic.inTheAir){
     sprite->physic.sy -= GRAVITY * sprite->physic.timerOfJump;
     sprite->physic.timerOfJump += 0.001;
  }
  if(!sprite->physic.inTheAir){
    sprite->physic.sy = 0;
  }
  
}
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
/*ALL ENNEMIES FUNCTIONS*/

void ennemyPhysics(sprite_t *ennemies, SDL_Surface *screen, int nbEnnemies, sprite_t h1)
{
  double distx; // disty;
  int i;
  for (i = 0; i <= nbEnnemies; i++){
    //find the distance sepearating the ennemy and the hero
    distx = (h1.physic.x - ennemies[i].physic.x);
    //disty = (h1.physic.y - ennemies[i].physic.y);
    //Hero on the right 
    if (distx >= HIT_RANGE){
      run(&ennemies[i], TO_THE_RIGHT); //he goes to the right
    }
    if (distx <= -HIT_RANGE){
      run(&ennemies[i], TO_THE_LEFT);
    }
    hyperespace(&ennemies[i]); //c'est juste pour pas me prendre la tete que j'ajoute ça
    move(&ennemies[i]);
    brake(&ennemies[i]);
    drawSprite(&ennemies[i], screen);
    /*printf("position.x = %d  ||  position.y = %d\n",ennemies[i].position.x,ennemies[i].position.y);
    printf("x = %f  ||  y = %f\n",ennemies[i].physic.x,ennemies[i].physic.y);*/
  }
}

//////////////////////////////////////////////////////////
/*ALL COLLISION FUNCTIONS*/

/*here because body is used for collisions*/
void updateBody(sprite_t *stickman)
{
  stickman->body.x = stickman->position.x + STICKMAN_X_GAP;
  stickman->body.y = stickman->position.y + STICKMAN_Y_GAP;
}

/*calculate the square of the distance between 2 points*/
int dist(int x1, int y1, int x2, int y2)
{
  int dist;
  dist = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));
  return dist;
}
/*check collide & place the sprite2 in the right place*/
void collision(sprite_t *sprite1, sprite_t *sprite2)
{

  int dir;

  if(collBetweenBox(sprite1->body, sprite2->body)){
   dir = posCompared(sprite1->body, sprite2->body);
   switch (dir) {
   case COLL_LEFT:
     //printf("Switch collision Left \n");
     sprite2->physic.x = sprite1->physic.x + (double)(sprite2->body.w + 1);  //place the sprite2 on the right of sprite1 
     break;
   case COLL_RIGHT:
     //printf("Switch collision right \n");
     sprite2->physic.x = sprite1->physic.x - (double)(sprite1->body.w - 1); //place on the left
     break;
   case COLL_UP:
     printf("Switch collision up \n");
     sprite2->physic.y = sprite1->physic.y - (double)(sprite2->body.h - 1); //above
     sprite2->physic.inTheAir = false;
     sprite2->physic.allowedToJump = true;
     
     break;
   case COLL_DOWN:
     //printf("Swtich collision down \n");
     sprite2->physic.y = sprite1->physic.y + (double)(sprite1->body.h + 1); //under
   default:
     break;
   }

  }

}



/*the point (x,y) it is in the box ?? true if yes*/
bool pointInTheBox(int x, int y, SDL_Rect box)
{

  bool res;
  if ( x >= box.x && x < box.x + box.w &&
       y >= box.y && y < box.y + box.h    ) {
    res = true;
  }
  else{
    res = false;
      }
  
  return res;

}

/*retourne vrai si la box1 rentre en col avec box2*/
/*bool collBetweenBox(SDL_Rect box1, SDL_Rect box2)
{
  bool res;
   if( (box2.x >= box1.x + box1.w)      // trop à droite
	&& (box2.x + box2.w >= box1.x) // trop à gauche
	&& (box2.y >= box1.y + box1.h) // trop en bas
      && (box2.y + box2.h <= box1.y) ) {  // trop en haut
          res = false; 
   }
   else {
          res = true; 
   }
   return res;
}*/

/*Fonction qui retourne le minimum de deux entiers*/
int minimum (int a, int b)
{
  if (a < b ) {
    return a;
  }
  else {
    return b;
  }
}


//Fonction qui retourne le maximum de deux entiers 
int maximum (int a, int b)
{
  if (a > b) {
    return a;
  }
  else {
    return b;
  }
}



//Fonction qui permet la collision entre 2 objets
bool collBetweenBox(SDL_Rect box1, SDL_Rect box2)
{
  if ( maximum ( box1.x , box2.x ) <= minimum ( ( box1.x + box2.w ) ,
       ( box2.x + box2.w ) ) )
  {
  if ( maximum (box1.y , box2.y ) <= minimum ( ( box1.y + box1.h ) ,
	 (box2.y + box2.h ) ) ){
      
      return true;
    }
  }
  return false;
}

/* retourne un int correspondant la position  *
 * de la box2 par rapport a celle de la box1 *
 * Donc on renvoie la pos de box1             */
int posCompared (SDL_Rect box1, SDL_Rect box2)
{
  int res = 0;
  int distUp, distDown, distLeft, distRight;  //squares of the lenghts of the rectangle made by the collision
  if(pointInTheBox(box1.x, box1.y, box2)){ //haut gauche
    if(pointInTheBox(box1.x, box1.y + box1.h, box2)){ //bas gauche
      //printf("Collision pts : HG et BG (a G ) \n");
      res = COLL_LEFT;
    }
    else if(pointInTheBox(box1.x + box1.w, box1.y, box2)){ //haut droite
      //printf("Collision pts : HG et HD (en H ) \n");
      res = COLL_UP;
    }
    else{
      //printf("Collision pts : HG seul \n");
      distUp = dist(box1.x, box1.y, box2.x + box2.w, box1.x);
      distLeft = dist(box1.x, box1.y, box1.x, box2.y + box2.h);
      if (distLeft >= distUp){
	res = COLL_LEFT; /*box2 on the left of box1*/
      }
      else {
	res = COLL_UP;  /*box2 above box1*/
      }
    }
  }
  if(pointInTheBox(box1.x + box1.w, box1.y, box2)){ //bas gauche
    if(pointInTheBox(box1.x + box1.w, box1.y + box1.h, box2)){ //bas droite
      //printf("Collision pts : BG + BD ( en B ) \n");
      res = COLL_DOWN;
    }
    else{
      //printf("Collision pts :  BG seul \n");
      distLeft = dist(box1.x, box1.y + box1.h, box1.x, box2.y);
      distDown = dist(box1.x, box1.y + box1.h, box2.x + box2.w, box1.y + box1.h);
      if(distLeft >= distDown){
	res = COLL_LEFT;  /*box2 on the left of box1*/
      }
      else {
	res = COLL_DOWN; /*box2 under box1*/
      }
    }
  }
  if(pointInTheBox(box1.x, box1.y + box1.h, box2)){ //haut droite
    if(pointInTheBox(box1.x + box1.w, box1.y + box1.h, box2)){ //bas droite
      //printf("Collision pts : HD + BD ( a D ) \n");
      res = COLL_RIGHT;
    }
    else{
      //printf("Collision pts : HD \n");
      distUp = dist(box1.x + box1.w, box1.y, box2.x, box1.y);
      distRight = dist(box1.x + box1.h, box1.y, box1.x + box1.w, box2.y + box2.h);
      if (distRight >= distUp){
	res = COLL_RIGHT;
      }
      else {
	res = COLL_UP;
      }
    }
  }
  if(pointInTheBox(box1.x + box1.w, box1.y + box1.h, box2)){ //bas droite
    //printf("Collision pts : BD \n");
    distDown = dist(box1.x, box1.y, box2.x + box2.w, box1.y);
    distRight = dist(box1.x, box1.y, box1.x, box2.y + box2.h);
    if (distRight >= distDown){
      res = COLL_RIGHT;
    }
    else {
      res = COLL_DOWN;
    }
  }
  //printf("res = %d\n", res);
  return res;
}

//////////////////////////////////////////////////////////::
/*test.c*/
void testAllProcedure()
{
  testPointInTheBox();
  testCollBetweenBox();
  testPosCompared();
}
/*Test : pointInTheBox(int x, int y, SDL_Rect Box)*/
void testPointInTheBox()
{
  SDL_Rect box;
  int x;
  int y;
  box.x = 10;
  box.y = 10;
  box.w = 5;
  box.h = 5;
  printf("Testing pointInTheBox with a box like : \n");
  printf("box.x = %d, box.y = %d, box.w = %d, box.h = %d  \n", box.x, box.y, box.w, box.h);

  x = 0;
  y = 0;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }

  /*Test de la diagonale*/
  x = 9;
  y = 9;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 10;
  y = 10;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 11;
  y = 11;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 12;
  y = 12;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 13;
  y = 13;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 14;
  y = 14;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 15;
  y = 15;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 16;
  y = 16;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }

  /*Test des droites horizontale  et verticales*/
  x = 10;
  y = 11;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 10;
  y = 14;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 11;
  y = 10;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  x = 13;
  y = 10;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  /*Test de cas particuliers*/
  x = 12;
  y = 13;
  if(pointInTheBox(x, y, box)){
    printf("x = %d, y = %d is in the box \n",x , y);
  }
  
  printf("\n");

}


/*test : CollBetweenBox(SDL_Rect box1, SDL_Rect box2)*/
void testCollBetweenBox()
{
  printf("testCollBetweenBox : \n");
  SDL_Rect box1, box2;

  box1.x = 0;
  box1.y = 0;
  box1.h = 5;
  box1.w = 5;

  box2.x = 0;
  box2.y = 0;
  box2.h = 5;
  box2.w = 5;
  if(collBetweenBox(box1, box2)){
    printf("Test think there is collision beetwen these : \n");
    printf("Box1 : x: %d; y: %d; w: %d; h: %d \n",box1.x, box1.y, box1.h, box1.w);
    printf("Box2 : x: %d; y: %d; w: %d; h: %d \n",box2.x, box2.y, box2.h, box2.w);
    printf("\n");
  }

  box1.x = 0;
  box1.y = 0;
  box1.h = 5;
  box1.w = 5;

  box2.x = 2;
  box2.y = 2;
  box2.h = 5;
  box2.w = 5;
  if(collBetweenBox(box1, box2)){
    printf("Test think there is collision beetwen these : \n");
    printf("Box1 : x: %d; y: %d; w: %d; h: %d \n",box1.x, box1.y, box1.h, box1.w);
    printf("Box2 : x: %d; y: %d; w: %d; h: %d \n",box2.x, box2.y, box2.h, box2.w);
    printf("\n");
  }
  
  box1.x = 0;
  box1.y = 0;
  box1.h = 5;
  box1.w = 5;

  box2.x = 1;
  box2.y = 1;
  box2.h = 2;
  box2.w = 5;
  if(collBetweenBox(box1, box2)){
    printf("Test think there is collision beetwen these : \n");
    printf("Box1 : x: %d; y: %d; w: %d; h: %d \n",box1.x, box1.y, box1.h, box1.w);
    printf("Box2 : x: %d; y: %d; w: %d; h: %d \n",box2.x, box2.y, box2.h, box2.w);
    printf("\n");
  }

  
  box1.x = 0;
  box1.y = 0;
  box1.h = 5;
  box1.w = 5;

  box2.x = 10;
  box2.y = 10;
  box2.h = 5;
  box2.w = 5;
  if(collBetweenBox(box1, box2)){
    printf("Test think there is collision beetwen these : \n");
    printf("Box1 : x: %d; y: %d; w: %d; h: %d \n",box1.x, box1.y, box1.h, box1.w);
    printf("Box2 : x: %d; y: %d; w: %d; h: %d \n",box2.x, box2.y, box2.h, box2.w);
    printf("\n");
  }
  
}


/*test : int PosCompared (SDL_Rect box1, SDL_Rect box2)*/
void  testPosCompared()
{
  
  printf("testposCompared : \n");
  
  printf("left = %d \n", COLL_LEFT);
  printf("right = %d \n",COLL_RIGHT);
  printf("up = %d \n", COLL_UP);
  printf("down = %d \n", COLL_DOWN);
  printf("Start the test : \n");
  SDL_Rect box1, box2;
  int dir;
  box1.x = 0;
  box1.y = 0;
  box1.h = 5;
  box1.w = 5;

  box2.x = 0;
  box2.y = 0;
  box2.h = 5;
  box2.w = 5;

  dir = posCompared(box1, box2);
  printf("dir = %d \n", dir);
  printf("Box1 : x: %d; y: %d; w: %d; h: %d \n",box1.x, box1.y, box1.h, box1.w);
  printf("Box2 : x: %d; y: %d; w: %d; h: %d \n",box2.x, box2.y, box2.h, box2.w);
  printf("\n");
}
