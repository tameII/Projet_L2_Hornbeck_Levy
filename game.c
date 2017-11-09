/*this is the file which reunites all the functions*/
/*Brandon Hornbeck*/
/*Mathieu Levy*/

#include "print.h"

#define NB_KEY 3


#define BASE_LIFE 1
#define BASE_ACCEL 0.1
#define BASE_S_MAX 5
#define BASE_JPOWER 1
#define HIT_RANGE 100



#define TO_THE_LEFT -1
#define TO_THE_RIGHT 1

//////////////////////////////////
void wipe_tab(int *tab, int N);

 
/*Event gestion*/
void handleEvent (SDL_Event event, int *quit,
		  int *tableEvent, bool *allowedToJump);
void applyEvent (sprite_t *h1, int *tableEvent,
		 bool *allowedToJump);
void game ();

/*fonction pour faire réapparaitre un sprite de l'autre coté coté de l'écran */
/*Elle sert just pour les test pour le moment                                */
/*J'ai retiré la possibilité de réapparaitre en bas depuis le haut           */
/*(pour pas faire de FLOUSHFLOUSHFLOSHFLSHFSHFH a la portal)                 */
void hyperespace(sprite_t *sprite, double *timerOfJump)
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
    sprite->physic.inTheAir = false;
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



/*Event gestion*/
void handleEvent (SDL_Event event, int *quit,
		  int *tableEvent, bool *allowedToJump)
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
      *allowedToJump = true;
      break;
    default:
      break;
    }
    break;
  }
}

/*this fonction call every event*/
void applyEvent (sprite_t *h1, int *tableEvent, bool *allowedToJump)
{
  if(tableEvent[0] == 1){
    run(h1, TO_THE_LEFT);
  }
  
  if(tableEvent[1] == 1){
    run(h1, TO_THE_RIGHT);
  }
  if(tableEvent[2] == 1){
    jump(h1, allowedToJump);
    *allowedToJump = false;
  }
}

/*Main function*/
void game ()
{
  SDL_Surface *screen, *background, *beam, *h1_picture, *ennemy_picture;

  sprite_t h1; //main character
  sprite_t ennemies [MAX_ENNEMIES];  //tab of ennemies
  int nbEnnemies = 0; //number of ennemies currently on the screen
  bool readed = false;
  /************************/
  int i;
  char** map = NULL;
  map = crea_Map(ROOM_WIDTH, ROOM_HEIGHT);
  int quit = 0;

  int tableEvent[NB_KEY];
  wipe_tab(tableEvent, NB_KEY);

  double timerOfJump = 0;
  bool allowedToJump = true;
  double distx, disty;

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
  
  
  h1_picture = download_sprite_("h1.bmp");
  ennemy_picture = download_sprite_("ennemy.bmp");
  set_colorkey_(h1_picture, 255, 0, 255, screen);
  set_colorkey_(ennemy_picture, 255, 0, 255, screen);
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
      handleEvent (event, &quit, tableEvent, &allowedToJump);
	}
applyEvent(&h1, tableEvent, &allowedToJump);
    /*Draw the background*/
    displayMap(map, &h1, &readed, screen, background, beam, ennemies, &nbEnnemies, ennemy_picture);

    move(&h1);
    brake(&h1);
    fall(&h1, &timerOfJump);
    hyperespace(&h1, &timerOfJump); //c'est juste pour pas me prendre la tete que j'ajoute ça
    
    animChar(&h1);
    drawSprite(&h1, screen);
    /*lead all the ennemies*/
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
      hyperespace(&ennemies[i], &timerOfJump); //c'est juste pour pas me prendre la tete que j'ajoute ça
      move(&ennemies[i]);
      brake(&ennemies[i]);
      drawSprite(&ennemies[i], screen);
      /*printf("position.x = %d  ||  position.y = %d\n",ennemies[i].position.x,ennemies[i].position.y);
      printf("x = %f  ||  y = %f\n",ennemies[i].physic.x,ennemies[i].physic.y);*/
    }
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
  
