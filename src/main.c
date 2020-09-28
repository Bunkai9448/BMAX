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
 int end = 0; // boolean var to control the main loop


 // homebrew's main loop 
 do {
   char * selApp = appSelect(); // main menu 

   // launch selected app and returns language (for those cases when the language changes)
   lang = selectedApp(selApp,lang); 
   
   // if he/she wants to exit, launch a confirmation screen to close BMAX

   if ( !strcmp(selApp,"exit") ) end = exitBmax() ; // exit = 1 means he/she confirms
   			                  // exit = 0 means he/she declines
   
 } while (!end); // check condition for the homebrew's main loop 



  // load an image with SDL to say goodbye. 
  goodBye();

  // exiting
  sceKernelExitProcess(0); // close and exit the app thread
  return 0;
}
