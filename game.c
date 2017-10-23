
/*this is the file which reunites all the functions*/
/*Brandon Hornbeck*/
/*Mathieu Levy*/


#include "print.h"
#define NB_KEY 3

void handleEvent (SDL_Event event, int *quit, int tableEvent[NB_KEY]);
void game ();


  


void handleEvent (SDL_Event event, int *quit,  int tableEvent[NB_KEY])
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
      tableEvent[2] = 1;
      break;
    default:
      break;
    }
  case SDL_KEYUP:
    switch (event.key.keysym.sym){
    case SDLK_LEFT:
      tableEvent[0] = 0;
      break;
    case SDLK_RIGHT:
      tableEvent[1] = 0;
      break;
    case SDLK_SPACE:
      tableEvent[2] = 0;
      break;
    default:
      break;
	
    }
  
  }
}


void game ()
{
  SDL_Surface *screen, *background, *beam;



  /************************/

  char** map = NULL;
  map = creaMap(ROOM_WIDTH, ROOM_HEIGHT);
  int quit = 0;
  int tableEvent[NB_KEY];

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


  readMap("test.txt", map);


  /*Main loop : check event and re-draw the window until the end*/
  while (!quit){

    /*Look for an event; possibly update position *
     * and shape of sprites                       */
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      handleEvent(event, &quit, tableEvent);
    }

    /*Draw the background*/
    displayMap(map, screen, background, beam);


    /*update the screen*/
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  /*End of main loop*/

  
  /*Freedom !*/
  freeMap (map, ROOM_HEIGHT);
  SDL_FreeSurface(beam);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);


  
}
  
  
int main (int argc, char *argv[])
{
  game();
  printf("\nEXIT SUCCESS \n");
  return EXIT_SUCCESS;
}
  
