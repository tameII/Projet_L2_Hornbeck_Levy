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
  sprite->sprite_number = sprite_number;  /* Number in the array              */
  sprite->max_number = max_number;        /* Number max of sprite in the array*/
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
  sprite->physic.allowedToHit = true;

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

  int i;
  for(i=0; i<beam_nb; i++){
    //  printf("i = %d \n", i);
    spriteInit(&beam[i], beam_t, BASE_ACCEL, BASE_S_MAX, BASE_JPOWER, 1, 
	       8, i, beam_nb, BASE_LIFE, sprite_picture);
  }

}

void updateBeam(sprite_t *beam)
{
  int i = 0;
  int beam_nb = beam[i].max_number;


  for(i=0; i<beam_nb; i++){
    // printf("i = %d\n", i);
    beam[i].body.x = beam[i].position.x;
    beam[i].body.y = beam[i].position.y;
    beam[i].body.w = 8;
    beam[i].body.h = 8;
    //   beam[i].physic.x = beam[i].position.x;
    // beam[i].physic.y = beam[i].position.y;

  }

}
///////////////////////////////////////////////////////////


/* read the map                              */
/* She is readed one full time to know the base *
 * position of all character                    */
void readMap (char** map, sprite_t *hero1, bool *readed,
		 SDL_Surface *screen, SDL_Surface *background,
		 sprite_t *beam, sprite_t *ennemies, int *nbEnnemy,
	      SDL_Surface *ennemy_picture)
{

  if(!*readed){
    int currBeam = 0;
    int currEnnemy = 0;
    int x = 0;
    int y = 0;
    int i,j;
    for (i = 0; i < ROOM_HEIGHT; i++){ 
      for (j = 0; j < ROOM_WIDTH; j++){
      
	switch (map[i][j]) {
	case '1':
	  x = j*8;
	  y = i*8;
	  beam[currBeam].physic.x = x;
	  beam[currBeam].physic.y = y;
	  beam[currBeam].position.x = x;
	  beam[currBeam].position.y = y;
	  updateBeam(beam);
	  currBeam += 1;
	  break;
	case '3':
	  hero1->physic.x = j*8;
	  hero1->physic.y = i*8;
	  hero1->position.x = j*8;
	  hero1->position.y = i*8;
	  copySDL_Rect(&hero1->position, &hero1->position_aft);
	  break;
	case '7':
	  initEnnemy(&ennemies[currEnnemy], currEnnemy, ennemy_picture);
	  ennemies[currEnnemy].physic.x = j*8;
	  ennemies[currEnnemy].physic.y = i*8;
	  currEnnemy += 1;
	  *nbEnnemy += 1;
	  break;
	default:
	  break;
	}
      }
    }
    *readed = true;
  }


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
/*****************************************************************/

/*Read the entry file and put all char in a tab[][](map) */
void readTxt (char* nameMap, char** map)
{
  char C; /*the actual char red*/
  int countColomn = 0, countLane = -1;  //countlane = -1 because it will increase to zero at the beginnig of the reading file process
  FILE* txt = fopen(nameMap, "r");

  
  
  do 
  {
    C = fgetc(txt);  /* storing the actual data*/
    if (C == '/'){
      countColomn = 0;
      countLane++;
      C = fgetc(txt);
    }
  
    
      
    map[countLane][countColomn] = C;
    countColomn++;
    if (countColomn >= ROOM_WIDTH){
      while (C != '/' && C != EOF){
	C = fgetc(txt);
	//printf("ça boucle");
      }
      countColomn = 0;
      countLane++;
    }
    //printf("ça boucle");
  } while (C != EOF && countLane < ROOM_HEIGHT);
  fclose(txt); 
 
} 




/*Warning: this function is not really effective*/
/*We need a new one*/
void drawSprite(sprite_t sprite, SDL_Surface *screen)
{
  SDL_BlitSurface(sprite.spritePicture,
		  &sprite.picture, screen,
		  &sprite.position);

}

void displayAll(SDL_Surface *background, SDL_Surface *screen,
		sprite_t *beam, int beam_nb,
		sprite_t h1,
		sprite_t *ennemies, int nbEnnemies)
{
  int i = 0;
  SDL_BlitSurface(background, NULL, screen, NULL);


  for(i = 0; i < beam_nb; i++){
    SDL_BlitSurface(beam[i].spritePicture, NULL, screen,
		    &beam[i].position);
  }
  
  drawSprite(h1, screen);

  
  for(i=0 ; i < nbEnnemies ; i++){
    drawSprite(ennemies[i], screen);
  }
  
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*animation.c*/

/*  picture is the current sprite used,                *
 *  nbSprite is the number of sprites in the animation */

void animSprite (sprite_t *character)
{
  character->picture.x += character->size; 
  //printf("animation\n");
  if (character->picture.x >= character->nb_sprite * character->size){
    character->picture.x = 0;
    if(character->physic.isAttacking){
      endAttack(character);
    }
  }
}
/*JAI CHANGE CA*/
void directionChar (sprite_t *character)
{
  if(!character->physic.isAttacking){
    if (character->physic.sx > 0 && character->physic.sx < RUN_STEP){
      // printf("standRight\n");
      character->currentAnimation = SPRITE_STAND_RIGHT;
      character->picture.x = 0;
      character->nb_sprite = 4;
      if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP){
	character->currentAnimation = SPRITE_JUMP_RIGHT;
	character->nb_sprite = 4;
      } 
    }
    if(character->currentAnimation != SPRITE_STAND_LEFT){
      if (character->physic.sx < 0 && character->physic.sx > -RUN_STEP){
	//  printf("standLeft\n");
	character->currentAnimation = SPRITE_STAND_LEFT;
	character->picture.x = 0;
	character->nb_sprite = 4;
	if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP){
	  character->currentAnimation = SPRITE_JUMP_LEFT;
	  character->nb_sprite = 4;
	} 
      }
    }
    if(character->currentAnimation != SPRITE_RUN_RIGHT){
      if (character->physic.sx > 0 && character->physic.sx > RUN_STEP){
	// printf("runRight\n");
	character->currentAnimation = SPRITE_RUN_RIGHT;
	character->picture.x = 0;
	character->nb_sprite = 8;
	if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP){
	  character->currentAnimation = SPRITE_JUMP_RIGHT;
	  character->nb_sprite = 4;
	}
      }
    }
    if(character->currentAnimation != SPRITE_RUN_LEFT){
      if (character->physic.sx < 0 && character->physic.sx < -RUN_STEP){
	//printf("runLeft \n");
	character->currentAnimation = SPRITE_RUN_LEFT;
	character->picture.x = 0;
	character->nb_sprite = 8;
	if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP){
	  character->currentAnimation = SPRITE_JUMP_LEFT;
	  character->nb_sprite = 4;
	} 
      }
    }
  }
}

void animChar (sprite_t *character)
{
  
  directionChar(character);
  character->picture.y = character->size * character->currentAnimation;
  character->count += 1;
  if (character->count >= 100){
    character->count = 0;
    animSprite(character);
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

void endAttack(sprite_t *character)
{     
  if(character->currentAnimation == SPRITE_ATTACK_LEFT){
    character->currentAnimation = SPRITE_STAND_LEFT;
  }
  else {
    character->currentAnimation = SPRITE_ATTACK_RIGHT;
  }
  character->physic.isAttacking = false;
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*physics.c*/

/*This file will rule all the movements, jumps, and landings*/


/*Brake if not in the air*/
void brake(sprite_t *sprite)
{
    /*if the sprite go the left*/
    if(sprite->physic.sx < 0.0){
      sprite->physic.sx /= FROTTEMENT;
    }  
    /*else if the sprite go to the right*/
    if(sprite->physic.sx > 0.0){
      sprite->physic.sx /= FROTTEMENT;
    
  }
  
}

/*move a sprite by his speed vector*/
void move (sprite_t *sprite)
{
  
  sprite -> physic.x += sprite -> physic.sx;
  sprite -> physic.y += sprite -> physic.sy;
  sprite -> position_aft.x = (int) sprite -> physic.x;
  sprite -> position_aft.y = (int) sprite -> physic.y;

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



/*Changement ici*/
/**/
void copySDL_Rect(SDL_Rect *copy, SDL_Rect *past)

{
  past->x = copy->x;
  past->y = copy->y;
  past->w = copy->w;
  past->h = copy->h;

} 


void copySDL_RectToDouble(SDL_Rect *copy, double *x, double *y)
{

 *x = (double)copy->x;
 *y = (double)copy->y;


}

/**/
/*Fin du changement*/


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
    if(sprite->physic.sy < sprite->physic.smax){
      sprite->physic.sy -= GRAVITY * sprite->physic.timerOfJump;
      sprite->physic.timerOfJump += 0.001;
    }
  }
  if(!sprite->physic.inTheAir){
    sprite->physic.sy = 0;
  }
  
}




void hit(sprite_t *character)
{
  //printf("allowed to hit = %d\n", character->physic.allowedToHit);
  if (character->physic.allowedToHit){
    character->physic.isAttacking = true;
    character->nb_sprite = 6;
    switch (character->currentAnimation){
      case 4:
      case 2:
      case 0:
	character->currentAnimation = SPRITE_ATTACK_RIGHT;
	break;
      case 5:
      case 3:
      case 1:
	character->currentAnimation = SPRITE_ATTACK_LEFT;
	break;
      default:
	break;
    }
  }
}


void placeHitPoint (sprite_t *character)
{
  int xGap, yGap;
  int position = character->picture.x;
  if (!character->physic.isAttacking){
    character->physic.attackX = -1;  /*place the point outta the screen*/
    character->physic.attackY = -1;
  }
  else {
    if (character->currentAnimation == SPRITE_ATTACK_LEFT){
      switch (position){ /*look where is the sprite on the image*/
	case 0:   /*first one*/
	  xGap = 20;
	  yGap = 17;
	  break;
	case 64:  /*2nd*/
	  xGap = 15;
	  yGap = 16;
	  break;
	case 128: /*3rd*/
	  xGap = 4;
	  yGap = 21;
	  break;
	case 192: /*4th*/
	  xGap = 5;
	  yGap = 21;
	  break;
	case 256:  /*5th*/
	  xGap = 4; 
	  yGap = 20;
	  break;
	case 320:  /*6th*/
	  xGap = 13;
	  yGap = 29;
	  break;
	default:
	  break;
      }
    }
    if (character->currentAnimation == SPRITE_ATTACK_RIGHT){
      switch (position){ /*look where is the sprite on the image*/
	case 0:   /*first one*/
	  xGap = 44;
	  yGap = 17;
	  break;
	case 64:  /*2nd*/
	  xGap = 49;
	  yGap = 16;
	  break;
	case 128: /*3rd*/
	  xGap = 59;
	  yGap = 21;
	  break;
	case 192: /*4th*/
	  xGap = 59;
	  yGap = 21;
	  break;
	case 256:  /*5th*/
	  xGap = 60; 
	  yGap = 20;
	  break;
	case 320:  /*6th*/
	  xGap = 51;
	  yGap = 30;
	  break;
	default:
	  break;
      }
    }
    character->physic.attackX = character->position.x + xGap;
    character->physic.attackY = character->position.y + yGap;
  }
}
	
//////////////////////////////////////////////////////////
/*ALL HERO1 function*/
void h1Physics(sprite_t *h1, sprite_t *beam, int beam_nb)
{


  move(h1);
  updateBody(h1);

  brake(h1);
  fall(h1);

  animChar(h1);
  
  placeHitPoint(h1);
  collision(beam, beam_nb, h1);
}


//////////////////////////////////////////////////////////
/*ALL ENNEMIES FUNCTIONS*/

void stuntAction(sprite_t *sprite)
{
  sprite->physic.stunt_timer -= 1;
  if(sprite->physic.stunt_timer <= 0){
    sprite->physic.stunt = false;
  }

}

void followIA(sprite_t *sprite, sprite_t *h1)
{
  int distx;
  
  //find the distance separating the ennemy and the hero
  distx = (h1->physic.x - sprite->physic.x);


  if (!sprite->physic.stunt){
    if (distx >= HIT_RANGE){
      run(sprite, TO_THE_RIGHT); //he goes to the right
    }
    if (distx <= -HIT_RANGE){
      run(sprite, TO_THE_LEFT);
    }
  }
}

/*Ici le bully c'est l'attaquant et victim l"attaqué*/
void hitAction(sprite_t *bully, sprite_t *victim)
{

  if(pointInTheBox(bully->physic.attackX, bully->physic.attackY, victim->body)
     && !victim->physic.stunt){

    if(bully->currentAnimation == SPRITE_ATTACK_LEFT){
      victim->physic.sx -= HIT_RETREAT;
    }
    else{ //SPRITE_ATTACK_RIGHT
      victim->physic.sx += HIT_RETREAT;
    }
    victim->physic.stunt = true;
    victim->physic.stunt_timer = STUNT_TIMER;
  }

}

void ennemyPhysics(sprite_t *ennemies, int nbEnnemies, sprite_t *beam, int beam_nb, sprite_t *h1)
{

  int i;
  for (i = 0; i <= nbEnnemies; i++){
    stuntAction(&ennemies[i]);
    followIA(&ennemies[i], h1);
    
    move(&ennemies[i]);
    updateBody(&ennemies[i]);
    
    brake(&ennemies[i]);
    fall(&ennemies[i]);
    
    animChar(&ennemies[i]);
    hitAction(h1, &ennemies[i]);

    collision(beam, beam_nb, &ennemies[i]);

    
  }
}







//////////////////////////////////////////////////////////
/*ALL COLLISION FUNCTIONS*/

/*here because body is used for collisions*/
void updateBody(sprite_t *stickman)
{
  stickman->body.x = stickman->position_aft.x + STICKMAN_X_GAP;
  stickman->body.y = stickman->position_aft.y + STICKMAN_Y_GAP;
}

/*calculate the square of the distance between 2 points*/
int dist(int x1, int y1, int x2, int y2)
{
  int dist;
  dist = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));
  return dist;
}



/********************************************************************************/


/*General function, if we need to test more thing than beam we put it here *
 * (like a coll sprite/sprite instead of beam/sprite)                      */
void collision(sprite_t *beam, int beam_nb, sprite_t *sprite)
{
  bool floor = false;
  bool ceiling = false;
  bool leftWall = false;;
  bool rightWall = false;
  int i;

     for (i=0; i<beam_nb; i++){
       collisionBeam(&beam[i], sprite,
		     &floor, &ceiling,
		     &leftWall, &rightWall);
      }
 
      
}




/*check collide & place the sprite in the right place*/
void collisionBeam(sprite_t *beam, sprite_t *sprite,
		   bool *floor, bool *ceiling,
		   bool *leftWall, bool *rightWall)
{

  int px, py;

  
  if(collBetweenBox(beam->body, sprite->body)){
    posCompared(beam->body, sprite->body, &px, &py);

    
    if(py == COLL_UP && px == 0){
      *floor = true;
      sprite->physic.inTheAir = false;
      sprite->physic.allowedToJump = true;
      sprite->physic.timerOfJump = 0;
      
    }
    else if(py == COLL_DOWN && !*floor && !*ceiling){
      *ceiling = true;
      sprite->physic.inTheAir = true;
      sprite->position.y = beam->position.y+1;
      fall(sprite);
    }
    else if(px == COLL_LEFT && !*leftWall){
      *leftWall = true;
      //   sprite->position.x = beam->position.x+1;
      //  brake(sprite);   
    }
    else if(px == COLL_RIGHT && !*rightWall){
      *rightWall = true;
      // sprite->position.x = beam->position.x-1;
      // brake(sprite);
    }
    copySDL_Rect(&sprite->position, &sprite->position_aft);
  }
  else if(!*floor){
    sprite->physic.inTheAir = true;
  }




  // hyperespace(sprite);
  copySDL_Rect(&sprite->position_aft, &sprite->position);
  updateBody(sprite);
}
 









/*********************************************************************************/

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


/* retourne un int correspondant la position   *
 * de la box2 par rapport a celle de la box1   *
 * Donc on renvoie la pos de box1              *
 * Px : Position in x, Py : Position in y      */
void posCompared (SDL_Rect box1, SDL_Rect box2, int *px, int *py)
{
  int x1 = box1.x;
  int y1 = box1.y;
  int xw1 = box1.x + box1.w;
  int yh1 = box1.y + box1.h;
  //  int midx1 = x1 + (box1.w)/2;
   int midy1 = y1 + (box1.h)/2;
  
  int x2 = box2.x;
  int y2 = box2.y;
  // int xw2 = box2.x + box2.w;
  // int yh2 = box2.y + box2.h;
  int midx2 = x2 + (box2.w)/2;
  int midy2 = y2 + (box2.h)/2;

  //si x1<midx2<xw1 
  if(x1 < midx2 && midx2 < xw1){
    *px = 0; //mean the mid is in the intervall
  }
  else if(x1 > midx2){
    *px = COLL_LEFT;
  }
  else {    //xw1 < midx2
    *px = COLL_RIGHT;
  }
  
  if(y1 < midy2 && midy2 < yh1){
    if(midy1 < midy2){
      *py = COLL_DOWN;
    }
    else{
      *py = COLL_UP;
    }
  }
  else if(y1 > midy2){
    *py = COLL_UP;
  }
  else{
    *py = COLL_DOWN;
  }

}


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////



/*test.c*/
void testAllProcedure(SDL_Surface *screen)
{
  // testPointInTheBox();
  // testCollBetweenBox();
  testPosCompared(screen);
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


/*Event gestion : THIS IS FOR THE SCREEN TESTING*/
void handleEventTest (SDL_Event event, int *quit,
		      int *endTest, SDL_Rect *box2)
{

  switch (event.type) {
    /*Close button pressed*/
  case SDL_QUIT:
    *quit=1;
    break;
    
    
    /*handle keyboards*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym){
    case SDLK_ESCAPE:
      *quit = 1;
      break;
    case SDLK_q:
      *endTest = 1;
      break;
    case SDLK_RETURN:
      *endTest = 1;
      break;
      break;
    case SDLK_RIGHT:
      box2->x +=40;
      break;
    case SDLK_LEFT:
      box2->x -= 40;
      break;
    case SDLK_UP:
      box2->y -= 40;
      break;
    case SDLK_DOWN:
      box2->y += 40;
      break;
    default:
      break;
    }
    break;
       
  }
  
}
/*specifical function*/
/*max tab is 20*/
void createTabBox(SDL_Rect *box)
{
  int i;

    for(i=0; i<18; i++){
      box[i].x = 500+8*i;
      box[i].y = 250;
      box[i].h = 8;
      box[i].w = 8;
    }


}

/*test : int PosCompared (SDL_Rect box1, SDL_Rect box2)*/
void  testPosCompared(SDL_Surface *screen)
{

  /*New var test*/
  
  int i;
  /*Create box to see in game*/
  SDL_Surface  *background_test;
  SDL_Surface *box1_picture, *box2_picture;
  SDL_Rect box[20];
  SDL_Rect box2;
  SDL_Rect box2_bef;
  // int px, py;
  int quit = 0;
  int endTest = 0;
  bool init = false;

  background_test = download_sprite_("background.bmp");
  box1_picture = download_sprite_("littlebox.bmp"); 
  box2_picture = download_sprite_("box2.bmp");

  /*begin test*/
  printf("testposCompared : \n");
  while (!endTest && !quit){
    if(!init){
      printf("left = %d \n", COLL_LEFT);
      printf("right = %d \n",COLL_RIGHT);
      printf("up = %d \n", COLL_UP);
      printf("down = %d \n", COLL_DOWN);
      printf("Start the test : \n");

      createTabBox(box); 

      box2.x = 250;
      box2.y = 250;
      box2.h = 64;
      box2.w = 64;

      init = true;
    }

    /*nouveau test*/
    for(i=0;i<18;i++){
      if(collBetweenBox(box[i], box2)){
	copySDL_Rect(&box2_bef, &box2);
      }
    }
    if(box2.y == SCREEN_HEIGHT + box2.h){
      box2.y = SCREEN_HEIGHT + box2.h;
      }
  copySDL_Rect(&box2, &box2_bef);

    
  SDL_Event event;
    if (SDL_PollEvent(&event)) {
      handleEventTest (event, &quit, &endTest, &box2);
    }

    SDL_BlitSurface(background_test, NULL, screen, NULL);
    
    for(i=0;i<18;i++){
    SDL_BlitSurface(box1_picture, NULL, screen, &box[i]);
    }
    SDL_BlitSurface(box2_picture, NULL, screen, &box2);


    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  /*Free the SDL_Surface*/
  SDL_FreeSurface(background_test);
  SDL_FreeSurface(box1_picture);
  SDL_FreeSurface(box2_picture);

}

