/* 
   BMAX common.c file
   author: Bunkai
*/

#include <psp2/kernel/clib.h> 
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "kbDisplay.h" // definitions required for the ps vita ime

//Vita Screen dimension defined in the debugScreen files


// dump the info, on screen, in a text file for debuging purposes
int debugLog (char * filepath, char* data) {
 
 psvDebugScreenInit(); // required to show the printf text on screen
 
 printf("\n\t");   // add a blank line to make it easier to read in the vita screen
 printf(data);     // print the error in the screen
 sceKernelDelayThread(3*1000000);  // delay 3 secs to make sure the user has seen/read it
 
 FILE *fOut = fopen(filepath, "a"); // O_WRONLY|O_CREAT|O_APPEND
 if (fOut != NULL) {
  fprintf(fOut,data); // dump the error in the log file
  if ( fwrite("\n",1,sizeof(char),fOut) < 0) return 1;    // next log in a new line looks better
 }

 fclose(fOut);
 return 0;
}


// function to ask the user the language to use in the app
char * chooseLang() {
 char * lang;

 uint16_t input[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1] = {0};
 SceImeDialogParam param; // dialog display struct 
 int shown_dial = 0;  // boolean: 0 = false, 1 = true
 bool said_yes = false; // indicates if lang is correct or not

 sceAppUtilInit(&(SceAppUtilInitParam){}, &(SceAppUtilBootParam){});
 sceCommonDialogSetConfigParam(&(SceCommonDialogConfigParam){});

 gxm_init();


 // input loop 
 while (!said_yes) {
  //clear current screen buffer
	memset(dbuf[backBufferIndex].data,0xff000000,DISPLAY_HEIGHT*DISPLAY_STRIDE_IN_PIXELS*4);

	// shown dialog parameters
	if (!shown_dial) {
		sceImeDialogParamInit(&param);

		param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH;
		param.languagesForced = SCE_TRUE;
		param.type = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
		param.option = 0;
		param.textBoxMode = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
		param.title = u"Choose language using ISO 639 (e.g. ENG for english)";
		param.maxTextLength = SCE_IME_DIALOG_MAX_TEXT_LENGTH;
		param.initialText = u"language";
		param.inputTextBuffer = input;

		shown_dial = sceImeDialogInit(&param) > 0;
	}


	// is exit condition met?
	if (sceImeDialogGetStatus() == SCE_COMMON_DIALOG_STATUS_FINISHED) {
	 // filling buffer with the inputs
		SceImeDialogResult result={};
		sceImeDialogGetResult(&result); // get the language of choice	
		// check if the user has finished typing (last input is enter key)
		uint16_t*last_input = (result.button == SCE_IME_DIALOG_BUTTON_ENTER) ? input:u"";
					
		// check if the language is correct and save it
			
			if (said_yes = !memcmp(last_input,u"eng",4*sizeof(u' '))){
			 sceImeDialogTerm(); // lang is correct,
			 shown_dial = 1;     // finish looping 
	
			 lang = "eng"; // save the selected lang in the global var
			 break;	
			}
				
				
			if (said_yes = !memcmp(last_input,u"spa",4*sizeof(u' '))){
			 sceImeDialogTerm(); // lang is correct,
			 shown_dial = 1;     // finish looping 
				
			 lang = "spa"; // save the selected lang in the global var
			 break;	
			}
				
				
			if (said_yes = !memcmp(last_input,u"jpn",4*sizeof(u' '))){
			 sceImeDialogTerm(); // lang is correct,
			 shown_dial = 1;     // finish looping 
				
			 lang = "jpn"; // save the selected lang in the global var	
			 break;
			}	
				
			sceImeDialogTerm(); // lang is not correct,
			shown_dial = 0; // respawn sceImeDialogInit on next loop 
							
	}

	// still inside the loop
		
		sceCommonDialogUpdate(&(SceCommonDialogUpdateParam){{
		NULL,dbuf[backBufferIndex].data,0,0,
		DISPLAY_WIDTH,DISPLAY_HEIGHT,DISPLAY_STRIDE_IN_PIXELS},
		dbuf[backBufferIndex].sync});

	gxm_swap();
	sceDisplayWaitVblankStart();

 } // exiting the loop
	
 gxm_term();
 return lang; 
}


// function to print a txt file in screen
void echoFile( char * file) {

 psvDebugScreenInit(); // required to show the printf text on screen
 
 FILE *fop = fopen(file, "r"); // O_RDONLY
 
 if (fop != NULL) { // if the fop worked
 
  printf("\n\t");   // add a blank line to make it easier to read in the vita screen
  
   // print all characters (text) from the file on screen
  char printedChar = fgetc(fop); 
  while ( !feof(fop) ) {
   printf("%c", printedChar);
   printedChar = fgetc(fop);
  }
  
  // to make the separation with next stuff prettier
  printf("\n\n------\n\n"); 
 } 

 else debugLog ("ux0:data/debugLog.txt","error opening file []");  // if fop didn't work
 
 fclose(fop);
 
 // wait for user input to exit
  printf("> press L+R to exit\n\t"); 
 
 // enable analog button sampling
 if ( sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG) < 0) {
  debugLog("ux0:data/debugLog.txt","error enabling button sampling mode");
  exit(1);
 }

 // definine variables
 SceCtrlData ctrl;

 // start button sampling 

 do {
      if ( sceCtrlPeekBufferPositive(0,&ctrl,1) < 1 ) {
        debugLog("ux0:data/debugLog.txt","error getting button sample");
        exit(1);  
      }
 }

 while (ctrl.buttons != ( SCE_CTRL_LTRIGGER | SCE_CTRL_RTRIGGER ) ); 
}

// function that prints the help file in the user specified language using echoFile
void help(char * lang) {

 psvDebugScreenInit(); // required to show the printf text on screen
 
 printf("\n\t"); 
 printf("> printing help file.\n\t");

 char langFile [29] = "app0:/bmax_files/help_"; // source file name (text common to all help files)
 strcat(langFile,lang);                        // add text specific for the language
 strcat(langFile,".txt");		        // add the extension (common to all files)
 
 echoFile(langFile);
}

