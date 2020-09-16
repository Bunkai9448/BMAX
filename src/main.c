/* 
   BMAX main.c file
   author: Bunkai
*/

#include "common.h"


// main program

int main(int argc, char *argv[]) {

  // check debugLog and serves as introductory sentence for the app
  debugLog ("ux0:data/debugLog.txt","\"Knowledge begins in wonder\"\n\tSocrates."); 
  
  char * lang = chooseLang(); // IME dialog to get the language to use in the app

  help(lang); // shows the help to the user to read in his/her language of choose 

  // SDL loading and loop
  mainScreen();

  // exiting
  SDL_Quit();
  sceKernelExitProcess(0); // close and exit the app thread
  return 0;
}
