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
SDL_Window    * gWindow    = NULL;  // window rendered to
SDL_Surface   * gSurface   = NULL;  // surface contained by the window
SDL_Surface   * gImage     = NULL;  // The image we will load


void goodBye(){ // this should be divided in more functions for modularity.

  // initializing
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
     debugLog ("ux0:data/debugLog.txt","error sdl [initializing]");

  else { //if SDL was initialized, create window

    if ((gWindow = SDL_CreateWindow( "GoodBye", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    debugLog ("ux0:data/debugLog.txt","error sdl [creating window]");

    else { // if window was created, create render
      
       if (((gSurface = SDL_GetWindowSurface( gWindow ))) == NULL)
           debugLog ("ux0:data/debugLog.txt","error sdl [creating render]");
    
       else { // if render was created, load image

          if (( gImage = SDL_LoadBMP( "app0:/bmax_files/goodbye.bmp" )) == NULL ) 
           debugLog ("ux0:data/debugLog.txt","error sdl [creating surface]"); 
          
	   //Apply the image
	   SDL_BlitSurface( gImage, NULL, gSurface, NULL );
			
	   //Update the surface
	   SDL_UpdateWindowSurface( gWindow );
         
      }
    }
  }
  
  SDL_Delay(3000); // screen delay to give time to see it
  
  //Deallocate surface
  SDL_FreeSurface( gImage );
  gImage = NULL;

  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;

  //Quit SDL subsystems
  SDL_Quit();

}

