/*this is the file which reunites all the functions*/
/*Brandon Hornbeck*/
/*Mathieu Levy*/ 

#include "print.h"

#define NB_KEY 4


//////////////////////////////////
void wipe_tab(int *tab, int N);

 
/*Event gestion*/

void applyEvent (sprite_t *h1, int *tableEvent);
void game ();



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

void handleEventMenu(SDL_Event event, int *endMenu, int *gameOver)
{
  switch (event.type) {
    /*Close button pressed*/
  case SDL_QUIT:
    *endMenu=1;
    break;
    /*handle keyboards*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym){
    case SDLK_ESCAPE:
      *endMenu = 1;
      break;
    case SDLK_RETURN:
    case SDLK_SPACE:
      *gameOver = 0;
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

/*Event gestion*/
void handleEvent (SDL_Event event, int *gameOver, int *endMenu,
		  int *tableEvent)
{
  switch (event.type) {
    /*Close button pressed*/
  case SDL_QUIT:
    *gameOver=1;
    *endMenu = 1;
    break;
    
      
    /*handle keyboards*/
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym){
    case SDLK_ESCAPE:
    case SDLK_q:
      *gameOver = 1;
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
    h1->physic.allowedToJump = true;
  }
  if(tableEvent[3] == 1){
    hit(h1);
    h1->physic.allowedToHit = false;
  }
  if(tableEvent[3] == 0){
    h1->physic.allowedToHit = true;
  }
}

/*Main function*/
void game ()
{
  SDL_Surface *screen, *background, *beam_picture, *h1_picture, *ennemy_picture;
  sprite_t *beam = NULL;
  sprite_t h1; //main character
  sprite_t ennemies [MAX_ENNEMIES];  //tab of ennemies
  int nbEnnemies = 0; //number of ennemies currently on the screen
  bool readed = false;
  int beam_nb;
  /************************/

  /************************/

  char** map = NULL;
  map = crea_Map(ROOM_WIDTH, ROOM_HEIGHT);
  int  endMenu = 0, gameOver = 1;

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
  background = download_sprite_("background.bmp");
  beam_picture = download_sprite_("beam.bmp");
  
  
  h1_picture = download_sprite_("h1.bmp");
  ennemy_picture = download_sprite_("ennemy2.bmp");
  set_colorkey_(h1_picture, 255, 0, 255, screen);
  set_colorkey_(ennemy_picture, 255, 0, 255, screen);
  
  printf("\nPictures loaded \n");
  
  /*InitSprite*/
  init_hero1(&h1, h1_picture);
  readTxt("level2.txt", map);
  
  beam_nb = countInTheMap(map, '1');
  printf("beam_nb :%d \n", beam_nb);
  nbEnnemies = countInTheMap(map, '7');
  printf("nbEnnemies : %d \n", nbEnnemies);

  beam = (sprite_t*)malloc(beam_nb * sizeof(sprite_t));
  init_beam(beam, beam_nb, beam_picture);

  /*Testing procedure....*/
  // printf("Testing procedure... \n");
  // testAllProcedure(screen);


  printf("\nLaunch the game : \n");
  

  while(!endMenu){
    
    SDL_Event event;
    if (SDL_PollEvent(&event)){
      handleEventMenu(event, &endMenu, &gameOver);
    }
 
    
    /*Main loop : check event and re-draw the window until the end*/
    while (!gameOver){

      /*Look for an event; possibly update position *
       * and shape of sprites                       */

    
      SDL_Event event;
      if (SDL_PollEvent(&event)){
	handleEvent (event, &gameOver, &endMenu, tableEvent);
      }
      applyEvent(&h1, tableEvent);
    

      readMap(map, &h1, &readed, screen, background,
		 beam, ennemies, &nbEnnemies, ennemy_picture);

      h1Physics(&h1, beam, beam_nb);
      
      ennemyPhysics(ennemies, nbEnnemies, beam, beam_nb, &h1);

  
      
      //  displayAll(background, screen, beam, beam_nb,  ennemies, nbEnnemies);
     displayAll(background, screen,
		beam, beam_nb,
		h1,
		ennemies, nbEnnemies);


      /*update the screen*/
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    /*End of main loop*/
    /*Display menu : */
    SDL_BlitSurface(background, NULL, screen, NULL);

    
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  /*End of menu*/


  
  /*Freedom !*/
  free_Map (map, ROOM_HEIGHT);
  
  printf("\nFreeSurface .... \n");
  SDL_FreeSurface(beam_picture);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);
  SDL_FreeSurface(ennemy_picture);
  printf("FreeSurface successful \n");

  
}
  
  
int main (int argc, char *argv[])
{
  game();
  printf("\nEXIT SUCCESS \n");
  return EXIT_SUCCESS;
}
  
