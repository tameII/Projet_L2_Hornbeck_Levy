/*this is the file which reunites all the functions*/
/*Brandon Hornbeck*/
/*Mathieu Levy*/  

#include "print.h"


#define NB_KEY 5

/*Check event :*/
void applyEvent (sprite_t *h1, int *tableEvent);
void handleEvent (SDL_Event event, int *gameOver, int *endMenu, int *ending,
		  int *play, int *menu, int *level, int *credit,
		  int *tableEvent);


//////////////////////////////////
/*Event gestion*/
void game ();





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
  }
  if(tableEvent[3] == 1){
    hit(h1);
    h1->physic.allowedToHit = false;
  }
  if(tableEvent[3] == 0){
    h1->physic.allowedToHit = true;
  }
}



void handleEventMenu(SDL_Event event,
		     int *endMenu, int *gameOver, int *ending,
		     int *menu, int *level, int *credit, int *play,
		     int *placement, int *actualPage, int *lvlChoosen,
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


/*Main function*/
void game ()
{
  SDL_Surface *screen, *background, *beam_picture;
  SDL_Surface *h1_picture, *ennemy_picture;
  SDL_Surface *hp_picture, *hpR_picture;

  SDL_Surface *play_picture, *playSelect_picture;
  SDL_Surface *quit_picture, *quitSelect_picture;
  SDL_Surface *level_picture, *levelSelect_picture;
  SDL_Surface  *credit_picture, *creditSelect_picture;
  
  SDL_Surface *lvl1_picture, *lvl1Select_picture;
  SDL_Surface *lvl2_picture, *lvl2Select_picture;
  SDL_Surface *lvl3_picture, *lvl3Select_picture;
  SDL_Surface *lvl4_picture, *lvl4Select_picture;
  SDL_Surface *lvl5_picture, *lvl5Select_picture;
  SDL_Surface *lvl6_picture, *lvl6Select_picture;
  SDL_Surface *lvl7_picture, *lvl7Select_picture;
  SDL_Surface *lvl8_picture, *lvl8Select_picture;

  SDL_Surface *changePage_picture, *changePageSelect_picture;
  SDL_Surface *pageBef_picture, *pageBefSelect_picture;


  SDL_Rect hp_position, hp_image, hpR_position;


  sprite_t spritePlay, spriteLevel, spriteCredit, spriteQuit;

  sprite_t spriteLvl1, spriteLvl2, spriteLvl3, spriteLvl4;
  sprite_t spriteLvl5, spriteLvl6, spriteLvl7, spriteLvl8;

  sprite_t spriteChangePage, spritePageBef;


  sprite_t h1; //main character
 

  int nbEnnemies = 0;
  int nbBeam = 0; 
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
  int actualLevel = lvlChoosen;
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
  lvl8_picture = download_sprite_("lvl8.bmp");
  lvl8Select_picture = download_sprite_("lvl8_lumineux.bmp");
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
	lvlChoosen = actualLevel;
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
			    &spriteChangePage, changePage_picture,
			    changePageSelect_picture,
			    &spritePageBef, pageBef_picture,
			    pageBefSelect_picture);

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
			    &spriteChangePage, changePage_picture,
			    changePageSelect_picture,
			    &spritePageBef, pageBef_picture,
			    pageBefSelect_picture);
	  

	  }
	  drawPage(background, screen,
		   &spriteLvl5, &spriteLvl6,
		   &spriteLvl7, &spriteLvl8,
		   &spriteChangePage, &spritePageBef);
	}
	actualLevel = lvlChoosen;
	if(win){
	  actualLevel -= 1;
	}
      }
      else if(credit){ 
	system("xdg-open https://github.com/tameII/Projet_L2_Hornbeck_Levy");
	launchMenu(&gameOver, &ending,
		   &menu, &level, &credit, &play);
      }
    }/*End of if(!play)*/
    else if(play){
      /*Init all*/
      wipe_tab(tableEvent, NB_KEY);
      readed = false;
      countEnding = COUNT_ENDING;
      if(win){
	actualLevel += 1;
	win = 0;
      }
      init_hero1(&h1, h1_picture);
      selectionLevel(map, actualLevel);

      nbBeam = 0;
      nbBeam = countInTheMap(map, '1');
      printf("nbBeam :%d \n", nbBeam);
      nbEnnemies = 0;
      nbEnnemies = countInTheMap(map, '7');
      printf("nbEnnemies : %d \n", nbEnnemies);
      
      sprite_t *beam = NULL;
      beam = (sprite_t*)malloc(nbBeam * sizeof(sprite_t));
      sprite_t *ennemies = NULL; 
      ennemies = (sprite_t*)malloc(nbEnnemies * sizeof(sprite_t));
      
      readMap(map, &h1, &readed, screen, background,
	      beam, nbBeam, beam_picture,
	      ennemies, ennemy_picture);
      
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

	h1Physics(&h1, beam, nbBeam);
	ControlHP(&h1, &hp_image);
	ennemyPhysics(ennemies, nbEnnemies, beam, nbBeam, &h1);
	
	displayAll(background, screen,
		   beam, nbBeam,
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
		   beam, nbBeam,
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
  SDL_FreeSurface(hpR_picture);
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
  
