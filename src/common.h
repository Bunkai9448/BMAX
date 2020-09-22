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

// function for the screenLoop or main screen of the program
void mainScreen();

// function to choose the lang of the app (for specific texts)
char * chooseLang();

// function to print a txt file in screen
// arg0: dir of txt file (char *)
void echoFile() ;

// function that prints the help file on screen for the user to read it
// arg0: language
void help();

//TODO
// function to select the app to launch
//
char * appSelect();

//TODO
// function to launch the selected app in appSelect()
// arg0: app to launch
void selectedApp();

