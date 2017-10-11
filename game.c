/*this is the file which reunites all the functions*/
/*Brandon Hornbeck*/
/*Mathieu Levy*/

#include "print.h"

void handleEvent (SDL_Event event, int *quit);
void game ();

void handleEvent (SDL_Event event, int *quit)
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
  map = crea_Map(ROOM_WIDTH, ROOM_HEIGHT);
  int quit = 0;


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
  printf("\nPictures loaded \n");

  readMap("test.txt", map);

  
  printf("\nLaunch the game : \n");
  /*Main loop : check event and re-draw the window until the end*/
  while (!quit){

    /*Look for an event; possibly update position *
     * and shape of sprites                       */
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      handleEvent(event, &quit);
    }

    /*Draw the background*/
    displayMap(map, screen, background, beam);


    /*update the screen*/
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  /*End of main loop*/

  
  /*Freedom !*/
  free_Map (map, ROOM_HEIGHT);
  printf("\nFreeSurface .... \n");
  SDL_FreeSurface(beam);
  printf("Free beam \n");
  SDL_FreeSurface(background);
  printf("Free background \n");
  SDL_FreeSurface(screen);
  printf("Free screen \n");
  printf("FreeSurface successful \n");

  
}
  
  
int main (int argc, char *argv[])
{
  game();
  printf("\nEXIT SUCCESS \n");
  return EXIT_SUCCESS;
}
  