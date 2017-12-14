/*this is the file which reunites all the functions*/
/*Brandon Hornbeck*/
/*Mathieu Levy*/  

#include "print.h"


#define NB_KEY 5
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

/*print*/

void switchPicture(sprite_t *sprite,
		   SDL_Surface *picture1, SDL_Surface *picture2);
/*Update the SDl_Rect position of the sprite*/
void placeMenuButton(sprite_t *spriteButton, int x, int y);


/*Check event :*/
void applyEvent (sprite_t *h1, int *tableEvent);
void handleEvent (SDL_Event event, int *gameOver, int *endMenu, int *ending,
		  int *play, int *menu, int *level, int *credit,
		  int *tableEvent);

/*Sprite E and F and their picture can be set at NULL*/
void initMenu(sprite_t *spriteA, SDL_Surface *A_picture,
	      sprite_t *spriteB, SDL_Surface *B_picture,
	      sprite_t *spriteC, SDL_Surface *C_picture,
	      sprite_t *spriteD, SDL_Surface *D_picture,
	      sprite_t *spriteE, SDL_Surface *E_picture,
	      sprite_t *spriteF, SDL_Surface *F_picture);




//////////////////////////////////
void wipe_tab(int *tab, int N);

 
/*Event gestion*/

 
void game ();




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




/*Event gestion*/
void handleEvent (SDL_Event event, int *gameOver, int *endMenu, int *ending,
		  int *play, int *menu, int *level, int *credit,
		  int *tableEvent)
{
  switch (event.type) {
    /*Close button pressed*/
  case SDL_QUIT:
    quitGame(endMenu, gameOver, ending);
    break;
    
      
    /*handle keyboards*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym){
    case SDLK_ESCAPE:
      launchMenu(gameOver, ending,
		 menu, play, level, credit);
      break;
    case SDLK_q:
      launchEnding(gameOver, ending,
		   menu, play, level, credit);
      break;
    case SDLK_LEFT:
      tableEvent[0] = 1; 
      break;
    case SDLK_RIGHT:
      tableEvent[1] = 1;
      break;
    case SDLK_UP:
      tableEvent[2] = 1;
      break;
    case SDLK_DOWN:
      tableEvent[4] = 1;
      break;
    case SDLK_SPACE:
      tableEvent[3] = 1;
      break;
    default:
      break;
    }
    break;
  case SDL_KEYUP:
    switch (event.key.keysym.sym){
    case SDLK_LEFT:
      tableEvent[0] = 0;
      break;
    case SDLK_RIGHT:
      tableEvent[1] = 0;
      break;
    case SDLK_UP:
      tableEvent[2] = 0;
      break;
    case SDLK_DOWN:
      tableEvent[4] = 0;
      break;
    case SDLK_SPACE:
      tableEvent[3] = 0;
    default:
      break;
    }
    break;
  }
}

/*this fonction call every event*/
void applyEvent (sprite_t *h1, int *tableEvent)
{
  if(tableEvent[0] == 1){
    run(h1, TO_THE_LEFT);
  }
  
  if(tableEvent[1] == 1){
    run(h1, TO_THE_RIGHT);
  }
  if(tableEvent[2] == 1){
      jump(h1);
      h1->physic.allowedToJump = false;
  }
  if(tableEvent[2] == 0){
  }
  if(tableEvent[3] == 1){
    hit(h1);
    h1->physic.allowedToHit = false;
  }
  if(tableEvent[3] == 0){
    h1->physic.allowedToHit = true;
  }
  if(tableEvent[4] == 0){
  }
  if(tableEvent[4] == 1){
    h1->physic.sy += 2;
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


/*Draw on screen 4 buttons */
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
	if(spriteE->spritePicture == ESelect_picture){ //correspond à un changement de page
	  *actualPage = 2;
	}
      }
      if(spriteF != NULL){
	if(spriteF->spritePicture == FSelect_picture){ //correspond à un retour arrière
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
	if(spriteF->spritePicture == FSelect_picture){ //correspond à un retour arrière
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
	      sprite_t *spriteA, SDL_Surface *A_picture, SDL_Surface *ASelect_picture,
	      sprite_t *spriteB, SDL_Surface *B_picture, SDL_Surface *BSelect_picture,
	      sprite_t *spriteC, SDL_Surface *C_picture, SDL_Surface *CSelect_picture,
	      sprite_t *spriteD, SDL_Surface *D_picture, SDL_Surface *DSelect_picture,
	      sprite_t *spriteE, SDL_Surface *E_picture, SDL_Surface *ESelect_picture,
	      sprite_t *spriteF, SDL_Surface *F_picture, SDL_Surface *FSelect_picture)
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
	    sprite_t *spriteA, SDL_Surface *A_picture, SDL_Surface *ASelect_picture,
	    sprite_t *spriteB, SDL_Surface *B_picture, SDL_Surface *BSelect_picture,
	    sprite_t *spriteC, SDL_Surface *C_picture, SDL_Surface *CSelect_picture,
	    sprite_t *spriteD, SDL_Surface *D_picture, SDL_Surface *DSelect_picture,
	    sprite_t *spriteE, SDL_Surface *E_picture, SDL_Surface *ESelect_picture,
	    sprite_t *spriteF, SDL_Surface *F_picture, SDL_Surface *FSelect_picture)
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
  if(spriteA != NULL){
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
  if(spriteB != NULL){
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

  if(spriteC != NULL){
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

  if(spriteD != NULL){
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

  if(spriteE != NULL){
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

  if(spriteF != NULL){
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

void handleEventMenu(SDL_Event event, int *endMenu, int *gameOver, int *ending,
		     int *menu, int *level, int *credit, int *play, int *placement,
		     int *actualPage, int *lvlChoosen,
		     sprite_t *spriteA, SDL_Surface *A_picture, SDL_Surface *ASelect_picture,
		     sprite_t *spriteB, SDL_Surface *B_picture, SDL_Surface *BSelect_picture,
		     sprite_t *spriteC, SDL_Surface *C_picture, SDL_Surface *CSelect_picture,
		     sprite_t *spriteD, SDL_Surface *D_picture, SDL_Surface *DSelect_picture,
		     sprite_t *spriteE, SDL_Surface *E_picture, SDL_Surface *ESelect_picture,
		     sprite_t *spriteF, SDL_Surface *F_picture, SDL_Surface *FSelect_picture)
{

  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    quitGame(endMenu, gameOver, ending);
    break;
  case SDL_KEYUP:
    switch (event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
	quitGame(endMenu, gameOver, ending);
	break;
      case SDLK_UP:
	upMenu(placement,
	       spriteA, A_picture, ASelect_picture,
	       spriteB, B_picture, BSelect_picture,
	       spriteC, C_picture, CSelect_picture,
	       spriteD, D_picture, DSelect_picture,
	       spriteE, E_picture, ESelect_picture,
	       spriteF, F_picture, FSelect_picture);
	break;
      case SDLK_DOWN:
	downMenu(placement,
		 spriteA, A_picture, ASelect_picture,
		 spriteB, B_picture, BSelect_picture,
		 spriteC, C_picture, CSelect_picture,
		 spriteD, D_picture, DSelect_picture,
		 spriteE, E_picture, ESelect_picture,
		 spriteF, F_picture, FSelect_picture);
	break;
      case SDLK_RETURN:
	if(*menu){
	  handleMenuReturn(endMenu, gameOver, ending,
			   menu, play, level, credit,
			   actualPage, lvlChoosen,
			   spriteA, ASelect_picture,
			   spriteB, BSelect_picture,
			   spriteC, CSelect_picture,
			   spriteD, DSelect_picture,
			   NULL, NULL,
			   NULL, NULL);
	}
	else if(*level){
	  handleMenuReturn(endMenu, gameOver, ending,
			   menu, play, level, credit,
			   actualPage, lvlChoosen,
			   spriteA, ASelect_picture,
			   spriteB, BSelect_picture,
			   spriteC, CSelect_picture,
			   spriteD, DSelect_picture,
			   spriteE, ESelect_picture,
			   spriteF, FSelect_picture);
	}
	break;
      default:
	break;
      }
  case SDL_MOUSEMOTION:
    collisionMenuMouseLeft(event.motion.x, event.motion.y, placement,
			   spriteA, A_picture, ASelect_picture,
			   spriteB, B_picture, BSelect_picture,
			   spriteC, C_picture, CSelect_picture,
			   spriteD, D_picture, DSelect_picture,
			   spriteE, E_picture, ESelect_picture,
			   spriteF, F_picture, FSelect_picture);
    break;
  case SDL_MOUSEBUTTONUP:
    switch(event.button.button) {
    case SDL_BUTTON_LEFT:
      if(*menu){
	handleMenuReturn(endMenu, gameOver, ending,
			 menu, play, level, credit,
			 actualPage, lvlChoosen,
			 spriteA, ASelect_picture,
			 spriteB, BSelect_picture,
			 spriteC, CSelect_picture,
			 spriteD, DSelect_picture,
			 NULL, NULL,
			 NULL, NULL);
      }
      else if(*level){
	handleMenuReturn(endMenu, gameOver, ending,
			 menu, play, level, credit,
			 actualPage, lvlChoosen,
			 spriteA, ASelect_picture,
			 spriteB, BSelect_picture,
			 spriteC, CSelect_picture,
			 spriteD, DSelect_picture,
			 spriteE, ESelect_picture,
			 spriteF, FSelect_picture);
      }
      break;
    case SDL_BUTTON_RIGHT:
      if(*menu){
	handleMenuReturn(endMenu, gameOver, ending,
			 menu, play, level, credit,
			 actualPage, lvlChoosen,
			 spriteA, ASelect_picture,
			 spriteB, BSelect_picture,
			 spriteC, CSelect_picture,
			 spriteD, DSelect_picture,
			 NULL, NULL,
			 NULL, NULL);
      }
      else if(*level){
	handleMenuReturn(endMenu, gameOver, ending,
			 menu, play, level, credit,
			 actualPage, lvlChoosen,
			 spriteA, ASelect_picture,
			 spriteB, BSelect_picture,
			 spriteC, CSelect_picture,
			 spriteD, DSelect_picture,
			 spriteE, ESelect_picture,
			 spriteF, FSelect_picture);
      }
      break;
    case SDL_BUTTON_MIDDLE:
      if(*menu){
	handleMenuReturn(endMenu, gameOver, ending,
			 menu, play, level, credit,
			 actualPage, lvlChoosen,
			 spriteA, ASelect_picture,
			 spriteB, BSelect_picture,
			 spriteC, CSelect_picture,
			 spriteD, DSelect_picture,
			 NULL, NULL,
			 NULL, NULL);
      }
      else if(*level){
	handleMenuReturn(endMenu, gameOver, ending,
			 menu, play, level, credit,
			 actualPage, lvlChoosen,
			 spriteA, ASelect_picture,
			 spriteB, BSelect_picture,
			 spriteC, CSelect_picture,
			 spriteD, DSelect_picture,
			 spriteE, ESelect_picture,
			 spriteF, FSelect_picture);
      }
      break;
    case SDL_BUTTON_WHEELUP:
      upMenu(placement,
	     spriteA, A_picture, ASelect_picture,
	     spriteB, B_picture, BSelect_picture,
	     spriteC, C_picture, CSelect_picture,
	     spriteD, D_picture, DSelect_picture,
	     spriteE, E_picture, ESelect_picture,
	     spriteF, F_picture, FSelect_picture);
      break;
    case SDL_BUTTON_WHEELDOWN:
      downMenu(placement,
	       spriteA, A_picture, ASelect_picture,
	       spriteB, B_picture, BSelect_picture,
	       spriteC, C_picture, CSelect_picture,
	       spriteD, D_picture, DSelect_picture,
	       spriteE, E_picture, ESelect_picture,
	       spriteF, F_picture, FSelect_picture);
      break;
    default:
      break;
    }
  default:
    break;
    
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
    if(h1->currentAnimation != SPRITE_WIN1 && h1->currentAnimation != SPRITE_WIN2){ //stand right
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

/*Main function*/
void game ()
{
  SDL_Surface *screen, *background, *beam_picture, *h1_picture, *ennemy_picture, *hp_picture, *hpR_picture;
  
  SDL_Surface *play_picture, *playSelect_picture, *quit_picture, *quitSelect_picture;
  SDL_Surface *level_picture, *levelSelect_picture, *credit_picture, *creditSelect_picture;
  
  SDL_Surface *lvl1_picture, *lvl1Select_picture, *lvl2_picture, *lvl2Select_picture;
  SDL_Surface *lvl3_picture, *lvl3Select_picture, *lvl4_picture, *lvl4Select_picture;
  SDL_Surface *lvl5_picture, *lvl5Select_picture, *lvl6_picture, *lvl6Select_picture;
  SDL_Surface *lvl7_picture, *lvl7Select_picture, *lvl8_picture, *lvl8Select_picture;
  SDL_Surface *changePage_picture, *changePageSelect_picture;
  SDL_Surface *pageBef_picture, *pageBefSelect_picture;

  SDL_Rect hp_position, hp_image, hpR_position;
    
  sprite_t spritePlay, spriteLevel, spriteCredit, spriteQuit;
  sprite_t spriteLvl1, spriteLvl2, spriteLvl3, spriteLvl4;
  sprite_t spriteLvl5, spriteLvl6, spriteLvl7, spriteLvl8;
  sprite_t spriteChangePage, spritePageBef;
  sprite_t *beam = NULL;
  sprite_t h1; //main character
  sprite_t *ennemies = NULL;  //tab of ennemies
  int nbEnnemies = 0; //number of ennemies currently on the screen
  int beam_nb = 0;
  /************************/

  /************************/

  char** map = NULL;
  map = crea_Map(ROOM_WIDTH, ROOM_HEIGHT);
  bool readed = false;
  int  endMenu = 0, gameOver = 1, ending = 1, win = 0;
  int menu = 1, level = 0, credit = 0, play = 0;
  int actualPage = 1;
  int placement = 0;
  int lvlChoosen = 1;
  int countEnding;
  int tableEvent[NB_KEY];
  wipe_tab(tableEvent, NB_KEY);

  
  /*initialise SDL*/
  SDL_Init (SDL_INIT_VIDEO);

  /*set title bar*/
  SDL_WM_SetCaption("Stick Rescue", "Stick Rescue");

  /*Create the window*/
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /*Set keyboard repeat*/
  SDL_EnableKeyRepeat(10, 10);

  /*Picture Load:*/
  background = download_sprite_("nouveaufond.bmp");
  /*Menu*/
  play_picture = download_sprite_("play.bmp");
  playSelect_picture = download_sprite_("play_lumineux.bmp");
  quit_picture = download_sprite_("quit.bmp");
  quitSelect_picture = download_sprite_("quit_lumineux.bmp");
  level_picture = download_sprite_("level.bmp");
  levelSelect_picture = download_sprite_("level_lumineux.bmp");
  credit_picture = download_sprite_("credit.bmp");
  creditSelect_picture = download_sprite_("credit_lumineux.bmp");
  /*Level:*/
  lvl1_picture = download_sprite_("lvl1.bmp");
  lvl1Select_picture = download_sprite_("lvl1_lumineux.bmp");
  lvl2_picture = download_sprite_("lvl2.bmp");
  lvl2Select_picture = download_sprite_("lvl2_lumineux.bmp");
  lvl3_picture = download_sprite_("lvl3.bmp");
  lvl3Select_picture = download_sprite_("lvl3_lumineux.bmp");
  lvl4_picture = download_sprite_("lvl4.bmp");
  lvl4Select_picture = download_sprite_("lvl4_lumineux.bmp");
  lvl5_picture = download_sprite_("lvl5.bmp");
  lvl5Select_picture = download_sprite_("lvl5_lumineux.bmp");
  lvl6_picture = download_sprite_("lvl6.bmp");
  lvl6Select_picture = download_sprite_("lvl6_lumineux.bmp");
  lvl7_picture = download_sprite_("lvl7.bmp");
  lvl7Select_picture = download_sprite_("lvl7_lumineux.bmp");
  lvl8_picture = download_sprite_("lvlMassacre.bmp");
  lvl8Select_picture = download_sprite_("lvlMassacre_lumineux.bmp");
  /*ChangePage*/
  changePage_picture= download_sprite_("changePage.bmp");
  changePageSelect_picture = download_sprite_("changePage_lumineux.bmp");
  pageBef_picture = download_sprite_("retourPage.bmp");
  pageBefSelect_picture = download_sprite_("retourPage_lumineux.bmp");
  /*Map*/
  beam_picture = download_sprite_("beam.bmp");

  /*HP*/
  h1_picture = download_sprite_("h1.bmp");
  hp_picture = download_sprite_("hp_bar.bmp");
  hpR_picture = download_sprite_("hp_round.bmp");
  ennemy_picture = download_sprite_("ennemy2.bmp");

  /*Character*/
  h1_picture = download_sprite_("h1.bmp");
  ennemy_picture = download_sprite_("ennemy2.bmp");
  /*Hp*/
  set_colorkey_(hpR_picture, 255, 0, 255, screen);
  /*character*/
  set_colorkey_(h1_picture, 255, 0, 255, screen);
  set_colorkey_(ennemy_picture, 255, 0, 255, screen);
  /*Menu*/
  set_colorkey_(play_picture, 255, 0, 255, screen);
  set_colorkey_(playSelect_picture, 255, 0, 255, screen);
  set_colorkey_(quit_picture, 255, 0, 255, screen);
  set_colorkey_(quitSelect_picture, 255, 0, 255, screen);
  set_colorkey_(level_picture, 255, 0, 255, screen);
  set_colorkey_(levelSelect_picture, 255, 0, 255, screen);
  set_colorkey_(credit_picture, 255, 0, 255, screen);
  set_colorkey_(creditSelect_picture, 255, 0, 255, screen);
  /*ChangePage*/
  set_colorkey_(changePage_picture, 255, 0, 255, screen);
  set_colorkey_(changePageSelect_picture, 255, 0, 255, screen);
  set_colorkey_(pageBef_picture, 255, 0, 255, screen);
  set_colorkey_(pageBefSelect_picture, 255, 0, 255, screen);
  /*Level*/
  set_colorkey_(lvl1_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl1Select_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl2_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl2Select_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl3_picture   ,255, 0, 255, screen); 
  set_colorkey_(lvl3Select_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl4_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl4Select_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl5_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl5Select_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl6_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl6Select_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl7_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl7Select_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl8_picture   ,255, 0, 255, screen);
  set_colorkey_(lvl8Select_picture   ,255, 0, 255, screen);
  
  printf("\nPictures loaded \n");
  


  /*Init all sprite and SDL_Rect*/
  /*Menu*/
  initMenu(&spritePlay, play_picture, &spriteLevel, level_picture,
	   &spriteCredit, credit_picture, &spriteQuit, quit_picture,
	   NULL, NULL, NULL, NULL);
  initMenu(&spriteLvl1, lvl1_picture, &spriteLvl2, lvl2_picture,
	   &spriteLvl3, lvl3_picture, &spriteLvl4, lvl4_picture,
	   NULL, NULL, NULL, NULL);
  initMenu(&spriteLvl5, lvl5_picture, &spriteLvl6, lvl6_picture,
	   &spriteLvl7, lvl7_picture, &spriteLvl8, lvl8_picture,
	   &spriteChangePage, changePage_picture,
	   &spritePageBef, pageBef_picture);
  /*Other*/
  setHp(&hp_position, &hp_image, &hpR_position);

  printf("\nLaunch the menu : \n");
  while(!endMenu){

    /*Menu*/
    if(!play){
      if(menu){
	SDL_Event event1;
	if (SDL_PollEvent(&event1)){
	  handleEventMenu(event1, &endMenu, &gameOver, &ending,
			  &menu, &level, &credit, &play, &placement,
			  &actualPage, &lvlChoosen,
			  &spritePlay, play_picture, playSelect_picture,
			  &spriteLevel, level_picture, levelSelect_picture,
			  &spriteCredit, credit_picture, creditSelect_picture,
			  &spriteQuit, quit_picture, quitSelect_picture,
			  NULL, NULL, NULL,
			  NULL, NULL, NULL); //because only  4 buttons
	}
	
	drawPage(background, screen,
		 &spritePlay, &spriteLevel,
		 &spriteCredit, &spriteQuit,
		 NULL, NULL);
      }
      else if(level){
	if(actualPage == 1){
	  SDL_Event event2;
	  if (SDL_PollEvent(&event2)){
	
	    handleEventMenu(event2, &endMenu, &gameOver, &ending,
			    &menu, &level, &credit, &play, &placement,
			    &actualPage, &lvlChoosen,
			    &spriteLvl1, lvl1_picture, lvl1Select_picture,
			    &spriteLvl2, lvl2_picture, lvl2Select_picture,
			    &spriteLvl3, lvl3_picture, lvl3Select_picture,
			    &spriteLvl4, lvl4_picture, lvl4Select_picture,
			    &spriteChangePage, changePage_picture, changePageSelect_picture,
			    &spritePageBef, pageBef_picture, pageBefSelect_picture);

	  }
	  drawPage(background, screen,
		   &spriteLvl1, &spriteLvl2,
		   &spriteLvl3, &spriteLvl4,
		   &spriteChangePage, &spritePageBef);

	}
	else if(actualPage == 2){
	  SDL_Event event3;
	  if (SDL_PollEvent(&event3)){
	    handleEventMenu(event3, &endMenu, &gameOver, &ending,
			    &menu, &level, &credit, &play, &placement,
			    &actualPage, &lvlChoosen,
			    &spriteLvl5, lvl5_picture, lvl5Select_picture,
			    &spriteLvl6, lvl6_picture, lvl6Select_picture,
			    &spriteLvl7, lvl7_picture, lvl7Select_picture,
			    &spriteLvl8, lvl8_picture, lvl8Select_picture,
			    &spriteChangePage, changePage_picture, changePageSelect_picture,
			    &spritePageBef, pageBef_picture, pageBefSelect_picture);
	  

	  }
	  drawPage(background, screen,
		   &spriteLvl5, &spriteLvl6,
		   &spriteLvl7, &spriteLvl8,
		   &spriteChangePage, &spritePageBef);
	}

      }
      else if(credit){ 
	printf("Credit work perfectly\n");
	/*Need to implement that*/
	/*Why not use SDL_TTF?*/
	launchMenu(&gameOver, &ending,
		   &menu, &level, &credit, &play);
      }
    }/*End of if(!play)*/
    else if(play){
      /*Init all*/
      wipe_tab(tableEvent, NB_KEY);
      readed = false;

      countEnding = COUNT_ENDING;
      win = 0;
      init_hero1(&h1, h1_picture);

      selectionLevel(map, lvlChoosen);
      beam_nb = countInTheMap(map, '1');
      printf("beam_nb :%d \n", beam_nb);
      nbEnnemies = countInTheMap(map, '7');
      printf("nbEnnemies : %d \n", nbEnnemies);

      beam = (sprite_t*)malloc(beam_nb * sizeof(sprite_t));
      init_beam(beam, beam_nb, beam_picture);

      ennemies = (sprite_t*)malloc(beam_nb * sizeof(sprite_t));

      printf("Launch the game : \n");
      /*Main loop : check event and re-draw the window until the end*/
      while (!gameOver){
	/*Look for an event; possibly update position *
	 * and shape of sprites                       */
	SDL_Event event;
	if (SDL_PollEvent(&event)){
	  handleEvent (event, &gameOver, &endMenu, &ending,
		       &play, &menu, &level, &credit,
		       tableEvent);
	}
	applyEvent(&h1, tableEvent);
      
	readMap(map, &h1, &readed, screen, background,
		beam, ennemies, &nbEnnemies, ennemy_picture);
      
	h1Physics(&h1, beam, beam_nb);
	ControlHP(&h1, &hp_image);
	ennemyPhysics(ennemies, nbEnnemies, beam, beam_nb, &h1);
	
	displayAll(background, screen,
		   beam, beam_nb,
		   h1,
		   ennemies, nbEnnemies);
	blitHp(h1, hp_picture,
	       hp_image, screen, hp_position,
	       hpR_picture, hpR_position);

        spriteDead(&h1, ennemies, nbEnnemies, &win,
	        &gameOver, &ending,
		   &menu, &play, &level, &credit);
	
	/*update the screen*/ 
	SDL_UpdateRect(screen, 0, 0, 0, 0);
      }      /*End of main loop*/
      while(!ending){
	animEnding(&h1, win);
	displayAll(background, screen,
		   beam, beam_nb,
		   h1,
		   ennemies, nbEnnemies);
	blitHp(h1, hp_picture,
	       hp_image, screen, 
	       hp_position, hpR_picture, hpR_position);
	countEnding -= 1;
	if(countEnding <= 0){
	  launchMenu(&gameOver, &ending,
		     &menu, &level, &credit, &play);
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
      }/*End of ending*/
      free(ennemies);
      free(beam);
    } 
   

    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  /*End of menu*/


  
  /*Freedom !*/ 
  /// free(ennemies);
  //free(beam);
  free_Map (map, ROOM_HEIGHT);
  
  printf("\nFreeSurface .... \n");
  /*Menu*/
  SDL_FreeSurface(play_picture);
  SDL_FreeSurface(playSelect_picture);
  SDL_FreeSurface(quit_picture);
  SDL_FreeSurface(quitSelect_picture);
  SDL_FreeSurface(level_picture);
  SDL_FreeSurface(levelSelect_picture);
  SDL_FreeSurface(credit_picture);
  SDL_FreeSurface(creditSelect_picture);
  /*ChangeLevel*/
  SDL_FreeSurface(changePage_picture);
  SDL_FreeSurface(changePageSelect_picture);
  SDL_FreeSurface(pageBef_picture);
  SDL_FreeSurface(pageBefSelect_picture);
  /*Level*/
  SDL_FreeSurface(lvl1_picture);
  SDL_FreeSurface(lvl1Select_picture);
  SDL_FreeSurface(lvl2_picture);
  SDL_FreeSurface(lvl2Select_picture);
  SDL_FreeSurface(lvl3_picture);
  SDL_FreeSurface(lvl3Select_picture);
  SDL_FreeSurface(lvl4_picture);
  SDL_FreeSurface(lvl4Select_picture);
  SDL_FreeSurface(lvl5_picture);
  SDL_FreeSurface(lvl5Select_picture);
  SDL_FreeSurface(lvl6_picture);
  SDL_FreeSurface(lvl6Select_picture);
  SDL_FreeSurface(lvl7_picture);
  SDL_FreeSurface(lvl7Select_picture);
  SDL_FreeSurface(lvl8_picture);
  SDL_FreeSurface(lvl8Select_picture);
  /*Character*/
  SDL_FreeSurface(h1_picture);
  SDL_FreeSurface(hp_picture);
  SDL_FreeSurface(ennemy_picture);
  /*map*/
  SDL_FreeSurface(beam_picture);
  /*End*/
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);
  printf("FreeSurface successful \n");

  
}
  
  
int main (int argc, char *argv[])
{
  game();
  printf("\nEXIT SUCCESS \n");
  return EXIT_SUCCESS;
}
  
