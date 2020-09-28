/* 
   BMAX common.h file
   author: Bunkai
*/

#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "debugScreen.h"
#define printf psvDebugScreenPrintf

// function that creates a txt for debugging purposes
// arg0: txt file where the text is dumped
// arg1: text to print
int debugLog();

// function to say goodBye as initiation to SDL
void goodBye();

// function to choose the lang of the app (for specific texts)
char * chooseLang();

// function to print a txt file in screen
// arg0: dir of txt file (char *)
void echoFile() ;

// function that prints the help file on screen for the user to read it
// arg0: language
void help();

// function to select the app to launch, this is the main menu of the homebrew
char * appSelect();

// function to launch the selected app in appSelect()
// arg0: app to launch
// arg1: lang selected. for those function that need it
char * selectedApp();

// function to ask the user if he/she really wants to close BMAX
int exitBmax();
