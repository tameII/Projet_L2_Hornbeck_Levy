/*this is the file which reunites all the functions*/
/*Brandon Hornbeck*/
/*Mathieu Levy*/

#include "print.h"

#define NB_KEY 3


#define BASE_LIFE 1
#define BASE_ACCEL 0.1
#define BASE_S_MAX 5
#define BASE_JPOWER 1

#define ACCEL_H1  0.1
#define S_MAX_H1  5
#define JPOWER_H1 3
#define NB_SPRITE_H1 1
#define SPRITE_SIZE_H1 64
#define LIFE_H1 3


#define TO_THE_LEFT -1
#define TO_THE_RIGHT 1

//////////////////////////////////
void wipe_tab(int *tab, int N);
void init_hero1(sprite_t *hero1, SDL_Surface *sprite_picture);
 
void handleEvent (SDL_Event event, int *quit,
		  int tableEvent [NB_KEY], sprite_t *h1, bool *isJumping);

void game ();

/*fonction pour faire réapparaitre un sprite de l'autre coté coté de l'écran */
/*Elle sert just pour les test pour le moment                                */
/*J'ai retiré la possibilité de réapparaitre en bas depuis le haut           */
/*(pour pas faire de FLOUSHFLOUSHFLOSHFLSHFSHFH a la portal)                 */
void hyperespace(sprite_t *sprite, double *timerOfJump, bool *isJumping)
{
  if(sprite->physic.x < 0){
    sprite->physic.x = sprite->physic.x + SCREEN_WIDTH - sprite->size;
  }
  else if(sprite->physic.x > SCREEN_WIDTH - sprite->size){
    sprite->physic.x = sprite->physic.x - SCREEN_WIDTH + sprite->size;
  }
  if(sprite->physic.y > SCREEN_HEIGHT - sprite->size){
    sprite->physic.y = SCREEN_HEIGHT - sprite->size;
    *timerOfJump = 0;
    *isJumping = false;
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

/*Initialisation of the main character*/
/*h1 = heroe1*/
void init_hero1(sprite_t *h1, SDL_Surface *sprite_picture)
{
  
  spriteInit( h1, hero1,
	      ACCEL_H1 , S_MAX_H1, JPOWER_H1,
	      NB_SPRITE_H1, SPRITE_SIZE_H1,
	      1, 1,          /*if we talk about a tab of sprite*/
	      LIFE_H1,
	      sprite_picture);

}


/*Event gestion*/
void handleEvent (SDL_Event event, int *quit,
		  int tableEvent [NB_KEY],
		  sprite_t *h1, bool *isJumping)
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
    case SDLK_q:
      *quit = 1;
      break;
    case SDLK_LEFT:
      tableEvent[0] = 1; 
      break;
    case SDLK_RIGHT:
      tableEvent[1] = 1;
      break;
    case SDLK_SPACE:
    case SDLK_UP:
      tableEvent[2] = 1;
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
    case SDLK_SPACE:
    case SDLK_UP:
      tableEvent[2] = 0;
      break;
    default:
      break;
    }
    break;
  }

  if(tableEvent[0] == 1){
    run(h1, TO_THE_LEFT);
  }
  
  if(tableEvent[1] == 1){
    run(h1, TO_THE_RIGHT);
  }
  /*If LEFT and RIGHT not pressed
  if(tableEvent[0] == 0 && tableEvent[1] == 0){
    brake(h1);
  } */
  
  if(tableEvent[2] == 1){
    jump(h1, isJumping);
  }
}

/*Main function*/
void game ()
{
  SDL_Surface *screen, *background, *beam, *h1_picture;

  sprite_t h1; //main character

  bool readed = false;
  /************************/

  char** map = NULL;
  map = crea_Map(ROOM_WIDTH, ROOM_HEIGHT);
  int quit = 0;

  int tableEvent[NB_KEY];
  wipe_tab(tableEvent, NB_KEY);

  double timerOfJump = 0;
  bool isJumping = false;
  
  /*initialise SDL*/
  SDL_Init (SDL_INIT_VIDEO);

  /*set title bar*/
  SDL_WM_SetCaption("Stick Rescue", "Stick Rescue");

  /*Create the window*/
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /*Set keyboard repeat*/
  SDL_EnableKeyRepeat(10, 10);

  /*Picture Load:*/
  background = download_sprite_("background.bmp");
  beam = download_sprite_("beam.bmp");
  
  h1_picture = download_sprite_("forwards.bmp");
  set_colorkey_(h1_picture, 255, 0, 255, screen);
  
  printf("\nPictures loaded \n");

  /*InitSprite*/
  init_hero1(&h1, h1_picture);
  readMap("test.txt", map);



    printf("\nLaunch the game : \n");
  /*Main loop : check event and re-draw the window until the end*/
  while (!quit){

    /*Look for an event; possibly update position *
     * and shape of sprites                       */
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      handleEvent (event, &quit, tableEvent, &h1, &isJumping);
	}
    /*Draw the background*/
    displayMap(map, &h1, &readed, screen, background, beam);

    move(&h1);
    brake(&h1, isJumping);
    fall(&h1, &timerOfJump,  &isJumping);
    hyperespace(&h1, &timerOfJump, &isJumping); //c'est juste pour pas me prendre la tete que j'ajoute ça
    
    drawSprite(&h1, screen);
    //SDL_BlitSurface(h1_picture, NULL, screen, &h1.position);
    /*update the screen*/
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  /*End of main loop*/

  
  /*Freedom !*/
  free_Map (map, ROOM_HEIGHT);
  
  printf("\nFreeSurface .... \n");
  SDL_FreeSurface(beam);
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
  
