/* 
   BMAX screen.c file
   author: Bunkai
*/
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <stdio.h>

#include "common.h"

//Vita Screen dimension defined in the debugScreen files

//Vita Screen SDL variables
SDL_Window    * gWindow   = NULL; // window rendered to
SDL_Renderer  * gRenderer = NULL; // surface contained by the window
 

// redrectangle, future game loop
SDL_Rect fillRect = { SCREEN_WIDTH  /4, 
		      SCREEN_HEIGHT /4, 
		      SCREEN_WIDTH  /2, 
		      SCREEN_HEIGHT /2
};


void mainScreen(){

  // initializing
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
     debugLog ("ux0:data/debugLog.txt","error sdl initializing");;


  // program_loop
    if ((gWindow = SDL_CreateWindow( "RedRectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    debugLog ("ux0:data/debugLog.txt","error sdl creating window");

  if ((gRenderer = SDL_CreateRenderer( gWindow, -1, 0)) == NULL)
    debugLog ("ux0:data/debugLog.txt","error sdl creating render");;
  

  SDL_SetRenderDrawColor( gRenderer, 255,0,0,255);
  SDL_RenderFillRect( gRenderer, &fillRect );
  SDL_RenderPresent( gRenderer );
  SDL_Delay(4000);
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;
}

