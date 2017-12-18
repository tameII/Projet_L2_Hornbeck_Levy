#include "print.h" 
 
/*fonction pour faire réapparaitre un sprite de l'autre coté coté de l'écran */
/*Elle sert just pour les test pour le moment                                */
/*J'ai retiré la possibilité de réapparaitre en bas depuis le haut           */
/*(pour pas faire de FLOUSHFLOUSHFLOSHFLSHFSHFH a la portal)                 */
void hyperespace(sprite_t *sprite)
{
  if(sprite->physic.y > SCREEN_HEIGHT+1){
    sprite->killed = 1;
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
  if(sprite != NULL){
    sprite->type = type;
    sprite->physic.x = SCREEN_WIDTH/ 2;
    sprite->physic.y = SCREEN_HEIGHT/ 2;
    sprite->physic.sx = 1;
    sprite->physic.sy = 1;
    sprite->physic.a = accel ;
    sprite->physic.smax = smax;
    sprite->physic.inTheAir = true;
    sprite->physic.jumpPower = jumpPower;
    sprite->physic.allowedToJump = true;
    sprite->physic.isJumping = false;
    sprite->physic.isAttacking = false;
    sprite->physic.timerOfJump = 0;
    sprite->physic.timerOfRestFromJump = 0;
    sprite->physic.timerAttack = 0;
    sprite->physic.allowedToHit = false;
    sprite->physic.stunt = false;
    sprite->physic.stunt_timer = 0;
    sprite->physic.attackX = -1;
    sprite->physic.attackY = -1;

    sprite->currentPicture = 0; 
    sprite->currentAnimation = 0;
    sprite->nb_sprite = nb_sprite;
    sprite->size = sprite_size;
    sprite->count = 0;
    sprite->sprite_number = sprite_number;/*Number in  array*/
    sprite->max_number = max_number;/*Number max in  array*/
    sprite->life = life;
    sprite->killed = 0;

    sprite->position_aft.x = 0;
    sprite->position_aft.y = 0;
    sprite->position_aft.w = 1;
    sprite->position_aft.h = 1;

    sprite->position.x = 0;
    sprite->position.y = 0;
    sprite->position.w = 1;
    sprite->position.h = 1;

    sprite->picture.x = 0;
    sprite->picture.y = 0;
    sprite->picture.w = sprite_size;
    sprite->picture.h = sprite_size;

    sprite->body.x = 0;
    sprite->body.y = 0;
    sprite->body.h = STICKMAN_HEIGHT;
    sprite->body.w = STICKMAN_WIDTH;

    sprite->spritePicture = sprite_picture;


  }
}

/*Initialise all variable for heroe*/
void init_hero1(sprite_t *h1, SDL_Surface *sprite_picture)
{
  
  spriteInit( h1, hero1,
	      ACCEL_H1 , S_MAX_H1, JPOWER_H1,
	      NB_SPRITE_H1, SPRITE_SIZE_H1,
	      1, 1, /*if we talk about a tab of sprite*/
	      LIFE_H1,
	      sprite_picture);

}

/*init all variable for ennmy*/
void initEnnemy(sprite_t *charac, int numberEnnemy, SDL_Surface *ennemy_picture)
{
  spriteInit(charac, ennemy_t, ACCEL_ENNEMY, S_MAX_ENNEMY, JPOWER_ENNEMY,
	     NB_SPRITE_ENNEMY, SPRITE_SIZE_H1, numberEnnemy, MAX_ENNEMIES, 
	     LIFE_ENNEMY, ennemy_picture);
}
/*init all variable for beam*/
void init_beam(sprite_t *beam, int nbBeam, SDL_Surface *sprite_picture)
{

  int i;
  for(i=0; i<nbBeam; i++){
    spriteInit(&beam[i], beam_t, BASE_ACCEL, BASE_S_MAX, BASE_JPOWER, 1, 
	       8, i, nbBeam, BASE_LIFE, sprite_picture);
  }

}

/*we need a second init for the beam:*/
void updateBeam(sprite_t *beam)
{
  int i = 0;
  int beam_nb = beam[i].max_number;


  for(i=0; i<beam_nb; i++){
    beam[i].body.x = beam[i].position.x;
    beam[i].body.y = beam[i].position.y;
    beam[i].body.w = 8;
    beam[i].body.h = 8;
  }

}
///////////////////////////////////////////////////////////



/* read the map                              */
/* She is readed one full time to know the base *
 * position of all character and beam           */
void readMap (char** map, sprite_t *hero1, bool *readed,
	      SDL_Surface *screen, SDL_Surface *background,
	      sprite_t *beam, int nbBeam, SDL_Surface *beam_picture,
	      sprite_t *ennemies, SDL_Surface *ennemy_picture)
{

  if(!*readed){
    init_beam(beam, nbBeam, beam_picture);
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
	  break;
	default:
	  break;
	}
      }
    }
    *readed = true;
  }
  
}

/*Count the number of char specified in the map*/
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

/*Dynamic allocation for a sprite*/
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

/*check if the entry file is readable*/
bool checkMap (char* nameMap)
{
  char C;
  FILE* txt = fopen(nameMap, "r");
  C = fgetc(txt);
  if (C!='/'){
    return false;
  } 
  else {
    return true;
  }
}



/*Read the entry file and put all char in a tab[][](map) */
/*countLane is set at -1 because we will increase it at begin*/
void readTxt (char* nameMap, char** map)
{
    
  if (!checkMap(nameMap)){
    printf("file not readable, please start your file with a '/'\n");
    exit(1);
  }
  char C; /*the actual char red*/
  int countColomn = 0, countLane = -1;
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
	}
	countColomn = 0;
	countLane++;
      }
    } while (C != EOF && countLane < ROOM_HEIGHT);
  fclose(txt); 
 
} 




/*Call SDL_Blitsurface to draw eas*/
void drawSprite(sprite_t sprite, SDL_Surface *screen)
{
  SDL_BlitSurface(sprite.spritePicture,
		  &sprite.picture, screen,
		  &sprite.position);

}

/*Call SDL_BlitSurface for all sprite in game,           *
 *change order to choose  what appear on first on screen */
void displayAll(SDL_Surface *background, SDL_Surface *screen,
		sprite_t *beam, int nbBeam,
		sprite_t h1,
		sprite_t *ennemies, int nbEnnemies)
{
  int i = 0;
  SDL_BlitSurface(background, NULL, screen, NULL);

  
  for(i = 0; i < nbBeam; i++){
    SDL_BlitSurface(beam[i].spritePicture, NULL, screen,
		    &beam[i].position);
  }

  drawSprite(h1, screen);

  for(i=0 ; i < nbEnnemies ; i++){
    if(ennemies[i].killed == 0){
      drawSprite(ennemies[i], screen);
    }
  }
}

 
/*The hp is directed by the life of h1.*/
void ControlHP(sprite_t *h1, SDL_Rect *image)
{
  double percent, newWidth;
  percent = (double)h1->life / LIFE_H1;
  newWidth = percent * HP_W;
  image->w = (int)newWidth;

    
}

void blitHp(sprite_t h1, SDL_Surface *hp_picture,
	    SDL_Rect image, SDL_Surface *screen, SDL_Rect position,
	    SDL_Surface *hpR_picture, SDL_Rect hpR_position)
{
  if(h1.life > 0){
    SDL_BlitSurface(hp_picture, &image, screen, &position);
    SDL_BlitSurface(hpR_picture, NULL, screen, &hpR_position);
  }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*animation.c*/

/*  picture is the current sprite used,                *
 *  nbSprite is the number of sprites in the animation */
void animSprite (sprite_t *character)
{
  character->picture.x += character->size; 
  if (character->picture.x >= character->nb_sprite * character->size){
    character->picture.x = 0;
    if(character->physic.isAttacking){
      endAttack(character);
    }
  }
}

/*Test to know where the sprite goes. */
void directionChar (sprite_t *character)
{
  if (character->physic.stunt){
    character->nb_sprite = 2;
    if (character->currentAnimation != SPRITE_STUNT_LEFT 
	&& character->currentAnimation != SPRITE_STUNT_RIGHT){
      if (character->physic.sx < 0){
	character->currentAnimation = SPRITE_STUNT_RIGHT;
	character->picture.x = 0;
      }
      else {
	character->currentAnimation = SPRITE_STUNT_LEFT;
	character->picture.x = 0;
      }
    }
  }
  else {
    if(!character->physic.isAttacking){
      
      if (character->physic.sx > 0 && character->physic.sx < RUN_STEP){
	// printf("standRight\n");
	  
	if(character->currentAnimation != SPRITE_STAND_RIGHT){
	  character->picture.x = 0;
	}
	character->currentAnimation = SPRITE_STAND_RIGHT;
	character->nb_sprite = 4;
	if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP
	   || character->physic.isJumping){
	  character->currentAnimation = SPRITE_JUMP_RIGHT;
	  character->nb_sprite = 4;
	}
	
	
      }
      
      if (character->physic.sx < 0 && character->physic.sx > -RUN_STEP){
	//  printf("standLeft\n");
	  
	if(character->currentAnimation != SPRITE_STAND_LEFT){
	  character->picture.x = 0;
	}
	character->currentAnimation = SPRITE_STAND_LEFT;
	character->nb_sprite = 4;
	if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP
	   || character->physic.isJumping){
	  character->currentAnimation = SPRITE_JUMP_LEFT;
	  character->nb_sprite = 4;
	} 
	
      }
      
      if (character->physic.sx > 0 && character->physic.sx > RUN_STEP){
	// printf("runRight\n");
	  
	if(character->currentAnimation != SPRITE_RUN_RIGHT){
	  character->picture.x = 0;
	}
	character->currentAnimation = SPRITE_RUN_RIGHT;
	character->nb_sprite = 8;
	if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP
	   || character->physic.isJumping){
	  character->currentAnimation = SPRITE_JUMP_RIGHT;
	  character->nb_sprite = 4;
	}
	
      }
     
      if (character->physic.sx < 0 && character->physic.sx < -RUN_STEP){
	//printf("runLeft \n");
	  
	if(character->currentAnimation != SPRITE_RUN_LEFT){
	  character->picture.x = 0;
	}
	character->currentAnimation = SPRITE_RUN_LEFT;
	character->nb_sprite = 8;
	if(character->physic.sy > JUMP_STEP || character->physic.sy < -JUMP_STEP
	   || character->physic.isJumping){
	  character->currentAnimation = SPRITE_JUMP_LEFT;
	  character->nb_sprite = 4;
	} 
	
      }
    }
  }
}
/*Ask direction and know when to use animSprite*/
void animChar (sprite_t *character)
{
  
  directionChar(character);
  character->picture.y = character->size * character->currentAnimation;
  character->count += 1;
  if (character->count >= 80){
    character->count = 0;
    animSprite(character);
  }
}
/*Stop attack and refresh to stand*/
void endAttack(sprite_t *character)
{     
  if(character->currentAnimation == SPRITE_ATTACK_LEFT){
    character->currentAnimation = SPRITE_STAND_LEFT;
  }
  else {
    character->currentAnimation = SPRITE_ATTACK_RIGHT;
  }
  character->physic.isAttacking = false;
  character->nb_sprite = 4;
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
  if (!character->physic.stunt){
    /*the speed rise by adding the acceleration*/
    if(character->physic.timerAttack <= 0){
      character->physic.sx += (character->physic.a)*direction;
    }
    /*don't pass over the max speed */
    if (character->physic.sx >= character->physic.smax){
      character->physic.sx = character->physic.smax;
    }
    else if(character->physic.sx <= -character->physic.smax){
      character->physic.sx = -character->physic.smax;
    }
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
  if(character->physic.allowedToJump 
     && character->physic.timerOfRestFromJump == 0){
    character->physic.isJumping = true;
    character->physic.sy = -character->physic.jumpPower;
    character->physic.timerOfRestFromJump = TIMER_OF_REST_FROM_JUMP;
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
  else if(!sprite->physic.inTheAir){
    sprite->physic.sy = 0;
  }
  if(sprite->physic.timerOfRestFromJump > 0){
    sprite->physic.timerOfRestFromJump -= 1;
  }
}




void hit(sprite_t *character)
{
  if (character->physic.allowedToHit){
    character->physic.isAttacking = true;
    character->nb_sprite = 6;
    character->picture.x = 0;
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

/*Place the hit point at the right pos*/
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
	xGap = -1;
	yGap = -1;
	break;
      case 64:  /*2nd*/
	xGap = -1;
	yGap = -1;
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
	xGap = -1;
	yGap = -1;
	break;
      case 64:  /*2nd*/
	xGap = -1;
	yGap = -1;
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

  stuntAction(h1);
  move(h1);
  updateBody(h1);

  brake(h1);
  fall(h1);

  animChar(h1);
  
  placeHitPoint(h1);
  collision(beam, beam_nb, h1);
  hyperespace(h1);
  
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

void timerAttackAction (sprite_t *sprite)
{
  sprite->physic.timerAttack -= 1;
  if(sprite->physic.timerAttack <= 0){
    sprite->physic.allowedToHit = true;
  }
}

bool seen(int distx, int disty)
{
  if (abs(distx) <= abs(SEE_X) && abs(disty) <= abs(SEE_Y)){
    return true;
  }
  else {
    return false;
  }
}

void followIA(sprite_t *sprite, sprite_t *h1)
{
  int distx, disty;
  
  //find the distance separating the ennemy and the hero
  distx = (h1->physic.x - sprite->physic.x);
  disty = (sprite->physic.y - h1->physic.y);
  if (seen(distx, disty)){
    if (!sprite->physic.stunt){
      if (distx >= HIT_RANGE){
        run(sprite, TO_THE_RIGHT); //he goes to the right
      }
      if (distx <= -HIT_RANGE){
        run(sprite, TO_THE_LEFT);
      }
    }
  }
}


/*Bully is attacking victim*/
void hitAction(sprite_t *bully, sprite_t *victim)
{

  if(pointInTheBox(bully->physic.attackX, bully->physic.attackY, victim->body)
     && !victim->physic.stunt){
    if(bully->currentAnimation == SPRITE_ATTACK_LEFT){
      victim->physic.sx = -HIT_RETREAT;
    }
    else{ //SPRITE_ATTACK_RIGHT
      victim->physic.sx = +HIT_RETREAT;
    }
    victim->physic.stunt = true;
    victim->physic.stunt_timer = STUNT_TIMER;
    victim->life -= 1;
    if (victim->life <= 0){
      victim->killed = 1;
    }
  }
  if(victim->currentAnimation == SPRITE_STUNT_RIGHT){
    victim->physic.sx = -HIT_RETREAT;
    
  }
  else if( victim->currentAnimation == SPRITE_STUNT_LEFT){
    victim->physic.sx = HIT_RETREAT;
  }

}

/*AI Who know when h1 is near and attack him if*
 * h1 is in HIT_RANGE                          */
void attackIA(sprite_t *ennemy, sprite_t h1)
{
  int distx, disty;
  distx = (h1.physic.x - ennemy->physic.x);
  disty = (h1.physic.y - ennemy->physic.y);
  if(seen(distx, disty)){
    if (abs(distx) <= abs(HIT_RANGE) && ennemy->physic.allowedToHit
	&& !ennemy->physic.stunt){
      hit(ennemy);
      ennemy->physic.allowedToHit = false;
      ennemy->physic.timerAttack = TIMER_ATTACK;
    }
  }
}

bool ennemyJump (sprite_t ennemy, sprite_t h1)
{
  int distx, disty;
  distx = (h1.physic.x - ennemy.physic.x);
  disty = (ennemy.physic.y - h1.physic.y);
  if (abs(distx)<=abs(HIT_RANGE)){
    if (disty>=JUMP_RANGE){
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

/*Général physics for all ennemies*/
void ennemyPhysics(sprite_t *ennemies, int nbEnnemies,
		   sprite_t *beam, int nbBeam, sprite_t *h1)
{

  int i;
  for (i = 0; i < nbEnnemies; i++){
    if(ennemies[i].killed == 0){
      stuntAction(&ennemies[i]);
      followIA(&ennemies[i], h1);

      move(&ennemies[i]);
      updateBody(&ennemies[i]);
    
      brake(&ennemies[i]);
      fall(&ennemies[i]);

      attackIA(&ennemies[i], *h1);
      placeHitPoint(&ennemies[i]);
      timerAttackAction(&ennemies[i]);
      hitAction(&ennemies[i], h1);

      hitAction(h1, &ennemies[i]);
      animChar(&ennemies[i]);
		      
      collision(beam, nbBeam, &ennemies[i]);
      if (ennemyJump(ennemies[i], *h1)){
	jump(&ennemies[i]);
      }
      hyperespace(&ennemies[i]);

    }
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



/*****************************************************************************/

/*General function, if we need to test more thing than beam we put it here *
 * (like a coll sprite/sprite instead of beam/sprite)                      */
void collision(sprite_t *beam, int beam_nb, sprite_t *sprite)
{
  bool floor = false;
  bool ceiling = false;
  bool leftWall = false;;
  bool rightWall = false;
  int i = beam_nb-1;

  while (i>=0){
    collisionBeam(&beam[i], sprite,
		  &floor, &ceiling,
		  &leftWall, &rightWall);
    i -= 1;
  }

     
}


/*check collide & place the sprite in the right place*/
//COLL_LEFT = sprite a GAUCHE de la beam
//COll_RIGHT = sprite a ddroite de la beam
//COLL_UP = sprite au dessus de la beam etc
void collisionBeam(sprite_t *beam, sprite_t *sprite,
		   bool *floor, bool *ceiling,
		   bool *leftWall, bool *rightWall)
{

  int px, py;

  
  if(collBetweenBox(beam->body, sprite->body)){
  
    posCompared(beam->body, sprite->body, &px, &py);

    if(py == COLL_UP){
      *floor = true;
      sprite->physic.inTheAir = false;
      sprite->physic.allowedToJump = true;
      sprite->physic.timerOfJump = 0;
      sprite->physic.isJumping = false;
   
      if(sprite->physic.sy == 0 && px == 0){
	sprite->physic.y -= 1;
      }
    }
    else if(py == COLL_DOWN && !*ceiling){// && px == 0){
      *ceiling = true;
      if(sprite->physic.sy < 0 ){
	sprite->physic.y +=1;
      }
    }
    else if(px == COLL_LEFT && !*leftWall){
      *leftWall = true;
      if(sprite->physic.sx > 0 && sprite->physic.sy>=0){
	sprite->physic.x -= 1;
      }
    }
    else if(px == COLL_RIGHT && !*rightWall){
      *rightWall = true;
      if(sprite->physic.sx < 0 && sprite->physic.sy>=0){
	sprite->physic.x += 1;
      }
    }

     
  }
  else if(!*floor){
    sprite->physic.inTheAir = true;
  }

  copySDL_Rect(&sprite->position_aft, &sprite->position);
  updateBody(sprite);
}
 
/******************************************************************************/

/*the point (x,y) it is in the box ?? true if yes*/
bool pointInTheBox(int x, int y, SDL_Rect box)
{
  
  bool res = false;
  if ( x >= box.x && x < box.x + box.w &&
       y >= box.y && y < box.y + box.h    ) {
    res = true;
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
  int midy1 = y1 + (box1.h)/2;
  
  int x2 = box2.x;
  int y2 = box2.y;
  int midx2 = x2 + (box2.w)/2;
  int midy2 = y2 + (box2.h)/2;

  if(x1 < midx2 && midx2 < xw1){ //le milieu du sprite(compris entre x1 et xw1)
    *px = 0; 
  }
  else if(x1 > midx2){ //la beam est a droite du milieu du sprite
    *px = COLL_LEFT;
  }
  else {    //la beam est a gauche du milieu du sprite
    *px = COLL_RIGHT;
  }
  if(midy1 < midy2){
    *py = COLL_DOWN;//coll_down
  }
  else{
    *py = COLL_UP; //COLL_UP
  }
}


void selectionLevel(char **map, int lvlChoosen)
{
  switch(lvlChoosen){
  case 1:
    readTxt("level1.txt", map);
    break;
  case 2:
    readTxt("level2.txt", map);
    break;
  case 3:
    readTxt("level3.txt", map);
    break;
  case 4:
    readTxt("level4.txt", map);
    break;
  case 5:
    readTxt("level5.txt", map);
    break;
  case 6:
    readTxt("level6.txt", map);
    break;
  case 7:
    readTxt("level7.txt", map);
    break;
  case 8:
    readTxt("level8.txt", map);
    break;
  default:
    break;
  }
}

void setHp(SDL_Rect *hp_position,SDL_Rect *hp_image,
	   SDL_Rect *hpR_position)
{
  hp_position->x = HP_X;
  hp_position->y = HP_Y;
  hp_position->h = HP_H;
  hp_position->w = HP_W;
  hp_image->x = 0;
  hp_image->y = 0;
  hp_image->h = HP_H;
  hp_image->w = HP_W;
  hpR_position->x = HP_X;
  hpR_position->y = HP_Y;
  hpR_position->h = HP_H;
  hpR_position->w = HP_W;
}


/*Gére toute l'animation du sprite de fin. les autres sprites sont gelés*/
void animEnding(sprite_t *h1, int win)
{
  h1->count += 1;
 
  if(win){
    //Le sprite de win s'anime
    if(h1->currentAnimation != SPRITE_WIN1
       && h1->currentAnimation != SPRITE_WIN2){ //stand right
      h1->currentAnimation = SPRITE_WIN1;
      h1->picture.x = 0;
      h1->nb_sprite = 9;
      h1->count = 0;
    }
    if (h1->count >= COUNT_ANIM_WIN){
      h1->count = 0;
      h1->picture.x += h1->size; 
    }
    if (h1->picture.x >= h1->nb_sprite * h1->size){
      if(h1->currentAnimation != SPRITE_WIN2){
	h1->currentAnimation = SPRITE_WIN2;
	h1->picture.x = 0;
	h1->nb_sprite = 4;
	h1->count = 0;	
      }
      else if(h1->currentAnimation != SPRITE_WIN1){
	h1->picture.x = h1->size*3; 
      }
    }
  }
  else{ //Perdu
    if(h1->currentAnimation != SPRITE_LOSE_RIGHT){
      if (h1->physic.sx > 0){
	h1->currentAnimation = SPRITE_LOSE_RIGHT;
	h1->picture.x = 0;
	h1->nb_sprite = 8;
	h1->count = 0;
      }
    }
    if(h1->currentAnimation != SPRITE_LOSE_LEFT){
      if (h1->physic.sx < 0){
	h1->currentAnimation = SPRITE_LOSE_LEFT;
	h1->picture.x = 0;
	h1->nb_sprite = 8;
	h1->count = 0;
      }
    }
    if (h1->count >= COUNT_ANIM_LOSE){
      h1->count = 0;
      h1->picture.x += h1->size; 
    }
    if(h1->picture.x >= h1->nb_sprite * h1->size){
      h1->picture.x = h1->size*7; 
    }
  }
  h1->picture.y = h1->size * h1->currentAnimation;
}

void spriteDead(sprite_t *h1, sprite_t *ennemies, int nbEnnemies, int *win,
		int *gameOver, int *ending,
		int *menu, int *play, int *level, int *credit)
{
  int i;
  int allKilled = 1;
  
  if(h1->killed == 1){
    launchEnding(gameOver, ending,
		 menu, play, level, credit);
  }
  for(i=0;i<nbEnnemies;i++){
    if(ennemies[i].killed == 0){
      allKilled = 0;
    }
  }
  if(nbEnnemies <= 0 || allKilled){
    *win = 1;
    launchEnding(gameOver, ending,
		 menu, play, level, credit);
  }  
}


//////////////////////////////////////////////////
/*Put a 0 in all member of the tab*/
void wipe_tab(int *tab, int N)
{
  int i;
  for(i=0;i<N;i++){
    tab[i] = 0;
  }

}

void placeMenuButton(sprite_t *spriteButton, int x, int y)
{
  if(spriteButton != NULL){
    spriteButton->position.x = x;
    spriteButton->position.y = y;
    spriteButton->position.w = WIDTH_MENU_BUTTON;
    spriteButton->position.h = HEIGHT_MENU_BUTTON;
  }
}


/*size of a button : 200 width and 50 height*/
void initMenu(sprite_t *spriteA, SDL_Surface *A_picture,
	      sprite_t *spriteB, SDL_Surface *B_picture,
	      sprite_t *spriteC, SDL_Surface *C_picture,
	      sprite_t *spriteD, SDL_Surface *D_picture,
	      sprite_t *spriteE, SDL_Surface *E_picture,
	      sprite_t *spriteF, SDL_Surface *F_picture)
{
  spriteInit(spriteA, menu_t,
	     0,0,0,1,0,0,1,0,
	     A_picture);
  placeMenuButton(spriteA, 440, 181);
  
  spriteInit(spriteB, menu_t,
	     0,0,0,1,0,0,1,0,
	     B_picture);
  placeMenuButton(spriteB, 440, 281);
  
  spriteInit(spriteC, menu_t,
	     0,0,0,1,0,0,1,0,
	     C_picture);
  placeMenuButton(spriteC, 440, 386);
  
  spriteInit(spriteD, menu_t,
	     0,0,0,1,0,0,1,0,
	     D_picture);
  placeMenuButton(spriteD, 440, 486);

  spriteInit(spriteE, menu_t,
	     0,0,0,1,0,0,1,0,
	     E_picture);
  placeMenuButton(spriteE, 440, 586);

  spriteInit(spriteF, menu_t,
	     0,0,0,1,0,0,1,0,
	     F_picture);
  placeMenuButton(spriteF, 430, 81);

}

/*Draw on screen the buttons */
void drawPage(SDL_Surface *background, SDL_Surface *screen,
	      sprite_t *spriteA, sprite_t *spriteB,
	      sprite_t *spriteC, sprite_t *spriteD,
	      sprite_t *spriteE, sprite_t *spriteF)
{
  SDL_BlitSurface(background, NULL, screen, NULL);
  if(spriteA != NULL){
    SDL_BlitSurface(spriteA->spritePicture, NULL, screen, &spriteA->position);
  }
  if(spriteB != NULL){
    SDL_BlitSurface(spriteB->spritePicture, NULL, screen, &spriteB->position);
  }
  if(spriteC != NULL){
    SDL_BlitSurface(spriteC->spritePicture, NULL, screen, &spriteC->position);
  }
  if(spriteD != NULL){
    SDL_BlitSurface(spriteD->spritePicture, NULL, screen, &spriteD->position);
  }
  if(spriteE != NULL){
    SDL_BlitSurface(spriteE->spritePicture, NULL, screen, &spriteE->position);
  }
  if(spriteF != NULL){
    SDL_BlitSurface(spriteF->spritePicture, NULL, screen, &spriteF->position);
  }
}


/*If you press return, this will happen :              */
/*Be aware to set up A and B and C and D good at begin.*/
/*E and F can be set at NULL                           */
void handleMenuReturn(int *endMenu, int *gameOver, int *ending,
		      int *menu, int *play, int *level, int *credit,
		      int *actualPage, int *lvlChoosen,
		      sprite_t *spriteA, SDL_Surface *ASelect_picture,
		      sprite_t *spriteB, SDL_Surface *BSelect_picture,
		      sprite_t *spriteC, SDL_Surface *CSelect_picture,
		      sprite_t *spriteD, SDL_Surface *DSelect_picture,
		      sprite_t *spriteE, SDL_Surface *ESelect_picture,
		      sprite_t *spriteF, SDL_Surface *FSelect_picture)
{
  /*Gestion du menu:*/
  if(*menu){
    if(spriteD->spritePicture == DSelect_picture){  //si quit alors
      quitGame(endMenu, gameOver, ending);
    }
    else if(spriteA->spritePicture == ASelect_picture){ //si play alors
      launchGame(gameOver, ending,
		 menu, play, level, credit);
    }
    else if(spriteB->spritePicture == BSelect_picture){ //si level alors
      launchSelectLevel(gameOver, ending,
			menu, play, level, credit);
    }
    else if(spriteC->spritePicture == CSelect_picture){ //si credit alors
      launchCredit(gameOver, ending,
		   menu, play, level, credit);
    }
  }
  /*gestion des levels*/
  else if(*level){
    if(*actualPage == 1){
      if(spriteA->spritePicture == ASelect_picture){ //lvl1
	*lvlChoosen = 1;
	launchGame(gameOver, ending,
		   menu, play, level, credit);
      }
      else if(spriteB->spritePicture == BSelect_picture){ //lvl2
	*lvlChoosen = 2;
	launchGame(gameOver, ending,
		   menu, play, level, credit);
      }
      else if(spriteC->spritePicture == CSelect_picture){ //lvl3
	*lvlChoosen = 3;
	launchGame(gameOver, ending,
		   menu, play, level, credit);
      }
      else if(spriteD->spritePicture == DSelect_picture){ //lvl4
	*lvlChoosen = 4;
	launchGame(gameOver, ending,
		   menu, play, level, credit);
      }
      else if(spriteE != NULL){
	if(spriteE->spritePicture == ESelect_picture){ //changement de page
	  *actualPage = 2;
	}
      }
      if(spriteF != NULL){
	if(spriteF->spritePicture == FSelect_picture){ //retour arrière
	  launchMenu(gameOver, ending,
		     menu, play, level, credit);
	}
      }
    }
    else if(*actualPage == 2){
      if(spriteA->spritePicture == ASelect_picture){ //lvl5
	*lvlChoosen = 5;
	launchGame(gameOver, ending,
		   menu, play, level, credit);
      }
      else if(spriteB->spritePicture == BSelect_picture){ //lvl6
	*lvlChoosen = 6;
	launchGame(gameOver, ending,
		   menu, play, level, credit);
      }
      else if(spriteC->spritePicture == CSelect_picture){ //lvl7
	*lvlChoosen = 7;
	launchGame(gameOver, ending,
		   menu, play, level, credit);
      }
      else if(spriteD->spritePicture == DSelect_picture){ //lvl8
	*lvlChoosen = 8;
	launchGame(gameOver, ending,
		   menu, play, level, credit);
      }
      else if(spriteE != NULL){
	if(spriteE->spritePicture == ESelect_picture){ //retour arrière
	  *actualPage = 1;
	}
      }
      if(spriteF != NULL){
	if(spriteF->spritePicture == FSelect_picture){ //retour arrière
	  *actualPage = 1;
	}
      }
    }
  }
}

/*Just put the surface in sprite->spriteSurface*
 * but with condition of sprite != NULL        */
void putPicture(sprite_t *sprite, SDL_Surface *surface)
{
  if(sprite != NULL){
    sprite->spritePicture = surface;
  }
}

/*The first button put here is selected and other are unchoosen*/
/*In fact, put a picture on 6 or less sprite*/
void selectButton(sprite_t *spriteA, SDL_Surface *A_picture,
		  sprite_t *spriteB, SDL_Surface *B_picture, 
		  sprite_t *spriteC, SDL_Surface *C_picture,
		  sprite_t *spriteD, SDL_Surface *D_picture,
		  sprite_t *spriteE, SDL_Surface *E_picture,
		  sprite_t *spriteF, SDL_Surface *F_picture)
{
  putPicture(spriteA, A_picture);
  putPicture(spriteB, B_picture);
  putPicture(spriteC, C_picture);
  putPicture(spriteD, D_picture);
  putPicture(spriteE, E_picture);
  putPicture(spriteF, F_picture);
}

void downMenu(int *placement,
	      sprite_t *spriteA, SDL_Surface *A_picture,
	      SDL_Surface *ASelect_picture,
	      sprite_t *spriteB, SDL_Surface *B_picture,
	      SDL_Surface *BSelect_picture,
	      sprite_t *spriteC, SDL_Surface *C_picture,
	      SDL_Surface *CSelect_picture,
	      sprite_t *spriteD, SDL_Surface *D_picture,
	      SDL_Surface *DSelect_picture,
	      sprite_t *spriteE, SDL_Surface *E_picture,
	      SDL_Surface *ESelect_picture,
	      sprite_t *spriteF, SDL_Surface *F_picture,
	      SDL_Surface *FSelect_picture)
{
  *placement +=1;
  if (*placement > 5){
    *placement = 0;
  }
  switch (*placement) {
  case 0:
    selectButton(spriteA, A_picture,
		 spriteB, B_picture, 
		 spriteC, C_picture,
		 spriteD, D_picture,
		 spriteE, E_picture,
		 spriteF, FSelect_picture);
   
    break;
  case 1:
    selectButton(spriteA, ASelect_picture,
		 spriteB, B_picture, 
		 spriteC, C_picture,
		 spriteD, D_picture,
		 spriteE, E_picture,
		 spriteF, F_picture);
    break;
  case 2:
    selectButton(spriteA, A_picture,
		 spriteB, BSelect_picture, 
		 spriteC, C_picture,
		 spriteD, D_picture,
		 spriteE, E_picture,
		 spriteF, F_picture);
    break;
  case 3:
    selectButton(spriteA, A_picture,
		 spriteB, B_picture, 
		 spriteC, CSelect_picture,
		 spriteD, D_picture,
		 spriteE, E_picture,
		 spriteF, F_picture);
    break;
  case 4:
    selectButton(spriteA, A_picture,
		 spriteB, B_picture, 
		 spriteC, C_picture,
		 spriteD, DSelect_picture,
		 spriteE, E_picture,
		 spriteF, F_picture);
    break;
  case 5:
    selectButton(spriteA, A_picture,
		 spriteB, B_picture, 
		 spriteC, C_picture,
		 spriteD, D_picture,
		 spriteE, ESelect_picture,
		 spriteF, F_picture);
    break;
  default:
    break;
  }
}

void upMenu(int *placement,
	    sprite_t *spriteA, SDL_Surface *A_picture, 
	    SDL_Surface *ASelect_picture,
	    sprite_t *spriteB, SDL_Surface *B_picture, 
	    SDL_Surface *BSelect_picture,
	    sprite_t *spriteC, SDL_Surface *C_picture, 
	    SDL_Surface *CSelect_picture,
	    sprite_t *spriteD, SDL_Surface *D_picture, 
	    SDL_Surface *DSelect_picture,
	    sprite_t *spriteE, SDL_Surface *E_picture, 
	    SDL_Surface *ESelect_picture,
	    sprite_t *spriteF, SDL_Surface *F_picture, 
	    SDL_Surface *FSelect_picture)
{
  *placement -=1;
  if (*placement < 0){
    *placement = 5;
  }
  switch(*placement){
  case 0:
    selectButton(spriteA, A_picture,
		 spriteB, B_picture, 
		 spriteC, C_picture,
		 spriteD, D_picture,
		 spriteE, E_picture,
		 spriteF, FSelect_picture);
    break;
  case 1:
    selectButton(spriteA, ASelect_picture,
		 spriteB, B_picture, 
		 spriteC, C_picture,
		 spriteD, D_picture,
		 spriteE, E_picture,
		 spriteF, F_picture);
    break;
  case 2:
    selectButton(spriteA, A_picture,
		 spriteB, BSelect_picture, 
		 spriteC, C_picture,
		 spriteD, D_picture,
		 spriteE, E_picture,
		 spriteF, F_picture);
    break;
  case 3:
    selectButton(spriteA, A_picture,
		 spriteB, B_picture, 
		 spriteC, CSelect_picture,
		 spriteD, D_picture,
		 spriteE, E_picture,
		 spriteF, F_picture);
    break;
  case 4:
    selectButton(spriteA, A_picture,
		 spriteB, B_picture, 
		 spriteC, C_picture,
		 spriteD, DSelect_picture,
		 spriteE, E_picture,
		 spriteF, F_picture);
    break;
  case 5:
    selectButton(spriteA, A_picture,
		 spriteB, B_picture, 
		 spriteC, C_picture,
		 spriteD, D_picture,
		 spriteE, ESelect_picture,
		 spriteF, F_picture);
    break;
  default:
    break;
  }
}



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
			    SDL_Surface *F_picture, SDL_Surface *FSelect_picture)
{
  if(spriteA != NULL && A_picture != NULL && ASelect_picture != NULL){
    if(pointInTheBox(x, y, spriteA->position)){
      *placement = 1;
      selectButton(spriteA, ASelect_picture,
		   spriteB, B_picture, 
		   spriteC, C_picture,
		   spriteD, D_picture,
		   spriteE, E_picture,
		   spriteF, F_picture);
    }
  }
  if(spriteB != NULL && B_picture != NULL && BSelect_picture != NULL){
    if(pointInTheBox(x, y, spriteB->position)){
      *placement = 2;
      selectButton(spriteA, A_picture,
		   spriteB, BSelect_picture, 
		   spriteC, C_picture,
		   spriteD, D_picture,
		   spriteE, E_picture,
		   spriteF, F_picture);
    }
  }

  if(spriteC != NULL && C_picture != NULL && CSelect_picture != NULL){
    if(pointInTheBox(x, y, spriteC->position)){
      *placement = 3;
      selectButton(spriteA, A_picture,
		   spriteB, B_picture, 
		   spriteC, CSelect_picture,
		   spriteD, D_picture,
		   spriteE, E_picture,
		   spriteF, F_picture);
    }
  }

  if(spriteD != NULL && D_picture != NULL && DSelect_picture != NULL){
    if(pointInTheBox(x, y, spriteD->position)){
      *placement = 4;
      selectButton(spriteA, A_picture,
		   spriteB, B_picture, 
		   spriteC, C_picture,
		   spriteD, DSelect_picture,
		   spriteE, E_picture,
		   spriteF, F_picture);
    }
  }

  if(spriteE != NULL && E_picture != NULL && ESelect_picture != NULL){
    if(pointInTheBox(x, y, spriteE->position)){
      *placement = 5;
      selectButton(spriteA, A_picture,
		   spriteB, B_picture, 
		   spriteC, C_picture,
		   spriteD, D_picture,
		   spriteE, ESelect_picture,
		   spriteF, F_picture);
    }
  }

  if(spriteF != NULL && F_picture != NULL && FSelect_picture != NULL){
    if(pointInTheBox(x, y, spriteF->position)){
      *placement = 0;
      selectButton(spriteA, A_picture,
		   spriteB, B_picture, 
		   spriteC, C_picture,
		   spriteD, D_picture,
		   spriteE, E_picture,
		   spriteF, FSelect_picture);
    }
  }
}




void launchCredit(int *gameOver, int *ending,
		  int *menu, int *play, int *level, int *credit)
{
  *gameOver = 1;
  *ending = 1;
  *play = 0;
  *menu = 0;
  *level = 0;  
  *credit = 1; 
}



void quitGame(int *endMenu, int *gameOver, int *ending)
{
  *endMenu = 1;
  *gameOver = 1; 
  *ending = 1;
}

void launchMenu(int *gameOver, int *ending,
		int *menu, int *play, int *level, int *credit)
{
  *gameOver = 1;
  *ending = 1;
  *play = 0;
  *menu = 1;
  *level = 0;
  *credit = 0;
}

void launchGame(int *gameOver, int *ending,
		int *menu, int *play, int *level, int *credit)
{
  *gameOver = 0;
  *ending = 1;
  *play = 1;
  *menu = 0;
  *level =0;
  *credit = 0;

}

void launchSelectLevel(int *gameOver, int *ending,
		       int *menu, int *play, int *level, int *credit)
{
  *gameOver = 1;
  *ending = 1;
  *play = 0;
  *menu = 0;
  *level = 1;
  *credit = 0;

}

void launchEnding(int *gameOver, int *ending,
		  int *menu, int *play, int *level, int *credit)
{
  *gameOver = 1;
  *ending = 0;
  *play = 0;
  *menu = 0;
  *level = 0;
  *credit = 0;
}


