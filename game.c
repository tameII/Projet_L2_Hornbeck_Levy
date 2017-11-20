/*this is the file which reunites all the functions*/
/*Brandon Hornbeck*/
/*Mathieu Levy*/

#include "print.h"

#define NB_KEY 3


//////////////////////////////////
void wipe_tab(int *tab, int N);

 
/*Event gestion*/
void handleEvent (SDL_Event event, int *quit,
		  int *tableEvent);
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



/*Event gestion*/
void handleEvent (SDL_Event event, int *quit,
		  int *tableEvent)
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
  
  char** map = NULL;
  map = crea_Map(ROOM_WIDTH, ROOM_HEIGHT);
  int quit = 0;

  int tableEvent[NB_KEY];
  wipe_tab(tableEvent, NB_KEY);
  int i;
  
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
  ennemy_picture = download_sprite_("ennemy.bmp");
  set_colorkey_(h1_picture, 255, 0, 255, screen);
  set_colorkey_(ennemy_picture, 255, 0, 255, screen);
  
  printf("\nPictures loaded \n");
  
  /*InitSprite*/
  init_hero1(&h1, h1_picture);
  readMap("test.txt", map);
  
  beam_nb = countInTheMap(map, '1');
  // creaTabSprite(beam, beam_nb);
  beam = (sprite_t*)malloc(beam_nb * sizeof(sprite_t));
  init_beam(beam, beam_nb, beam_picture);


  /*Testing procedure....*/
  printf("Testing procedure... \n");
  testAllProcedure();
  
    printf("\nLaunch the game : \n");
  /*Main loop : check event and re-draw the window until the end*/
  while (!quit){

    /*Look for an event; possibly update position *
     * and shape of sprites                       */
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      handleEvent (event, &quit, tableEvent);
	}
    applyEvent(&h1, tableEvent);
    /*Draw the background*/
    displayMap(map, &h1, &readed, screen, background, beam, ennemies, &nbEnnemies, ennemy_picture);

    move(&h1);
    brake(&h1);
    fall(&h1);
    hyperespace(&h1); //c'est juste pour pas me prendre la tete que j'ajoute ça
    
    animChar(&h1);
    updateBody(&h1);
    drawSprite(&h1, screen);
    // printf("x = %d, y= %d \n",h1.position.x, h1.position.y);
    for (i=0; i<beam_nb; i++){
      collision(&beam[i], &h1);
    }
      
    
    ennemyPhysics(ennemies, screen, nbEnnemies, h1);
    
    //SDL_BlitSurface(h1_picture, NULL, screen, &h1.position);
    /*update the screen*/
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  /*End of main loop*/

  
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
  
