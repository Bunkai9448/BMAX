/* 
   BMAX screen.c file
   author: Bunkai
*/
 
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <stdio.h>
#include <stdbool.h>

#include "common.h"

//Vita Screen dimension defined in the debugScreen files

//Vita Screen SDL variables
SDL_Window    * gWindow    = NULL;  // window rendered to
SDL_Surface   * gSurface   = NULL;  // surface contained by the window
SDL_Surface   * gImage     = NULL;  // The image we will load


// function to init SDL
int initSDL(){

 int result = 1; // 1 = False, something went wrong
 
 // init SDL
 if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
     debugLog ("ux0:data/debugLog.txt","error sdl [initializing]");
 }
 else { //if SDL was initialized, create window

  if ((gWindow = SDL_CreateWindow( "GoodBye", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
   
         debugLog ("ux0:data/debugLog.txt","error sdl [creating window]");
  }
  else { // if window was created, create render
      
       if (((gSurface = SDL_GetWindowSurface( gWindow ))) == NULL)
           debugLog ("ux0:data/debugLog.txt","error sdl [creating render]");
           
           // if we have reached this line, the init was successful
           result = 0;
         }
  }
           
 return result;
}

// function to load bmp on screen with sdl
int loadBMP(char * bmpPath){

 if (( gImage = SDL_LoadBMP( bmpPath )) == NULL ) {
     debugLog ("ux0:data/debugLog.txt","error sdl [creating surface]");
     return 1;
 } 
          
 //Apply the image
 SDL_BlitSurface( gImage, NULL, gSurface, NULL );
			
 //Update the surface
 SDL_UpdateWindowSurface( gWindow );
  
 SDL_Delay(3000); // screen delay to give time to see it
   
 return 0; // everything went well
}

// function to clean memory and close SDL
void closeSDL(){ 
 
  //Deallocate surface
  SDL_FreeSurface( gImage );
  gImage = NULL;

  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;

  //Quit SDL subsystems
  SDL_Quit();

}

// dummy function to check SDL and load a goodbye image for the BMAX app
void goodBye() {

 if ( !initSDL() ) { // if render was created, load image
     if ( !loadBMP("app0:/bmax_files/goodbye.bmp") ) // if load img was successful
        closeSDL(); 
     }

}
