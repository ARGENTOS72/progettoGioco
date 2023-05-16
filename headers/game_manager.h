#include "raylib.h"

//general structs -----------
typedef struct {
	int choice;
	int volume[3];
} System;
//---------------------------

//global variables ---------
int screenWidth, screenHeight;
//--------------------------

/* ----------------------------------------- Lobby & Settings section --------------------------------------*/
//general defines ------
#define TitleFont 90
#define subTitleFont 60
#define buttonFont 40
#define lobbyOpt 4
#define settingsOpt 4
//---------------------

void DrawLobby (int choice) {//: training , duel , survival , settings
	//title
    DrawText("Kiriko",(screenWidth/2) - (MeasureText("Kiriko",TitleFont)/2)-2,48,TitleFont,RED);
	DrawText("Kiriko",(screenWidth/2) - (MeasureText("Kiriko",TitleFont)/2),50,TitleFont,BLACK);
	DrawText("Kiriko",(screenWidth/2) - (MeasureText("Kiriko",TitleFont)/2)+2,52,TitleFont,BLACK);

	//subtitle
	DrawText("and the donuts",(screenWidth/2) - (MeasureText("and the donuts",subTitleFont)/2)-2,138,subTitleFont,RED);
	DrawText("and the donuts",(screenWidth/2) - (MeasureText("and the donuts",subTitleFont)/2)+2,142,subTitleFont,BLACK);
	DrawText("and the donuts",(screenWidth/2) - (MeasureText("and the donuts",subTitleFont)/2),140,subTitleFont,BLACK);

	//<a href="training">training</a>
	DrawText("training",8,248,buttonFont,BLACK);
	DrawText("training",12,252,buttonFont,BLACK);
	DrawText("training",10,250,buttonFont,(choice==1)?RED:WHITE);

	//<a href="duel">duel</a>
	DrawText("duel",8,298,buttonFont,BLACK);
	DrawText("duel",12,302,buttonFont,BLACK);
	DrawText("duel",10,300,buttonFont,(choice==2)?RED:WHITE);

	//<a href="survival">survival</a>
	DrawText("survival",8,348,buttonFont,BLACK);
	DrawText("survival",12,352,buttonFont,BLACK);
	DrawText("survival",10,350,buttonFont,(choice==3)?RED:WHITE);

	//<a href="settings">settings</a>
	DrawText("settings",8,398,buttonFont,BLACK);
	DrawText("settings",12,402,buttonFont,BLACK);
	DrawText("settings",10,400,buttonFont,(choice==4)?RED:WHITE);
}

void DrawSettings (System sys) {//: master volume , music volume , effects volume
	//title
    DrawText("Settings",(screenWidth/2) - (MeasureText("Settings",TitleFont)/2)-2,48,TitleFont,RED);
	DrawText("Settings",(screenWidth/2) - (MeasureText("Settings",TitleFont)/2),50,TitleFont,BLACK);
	DrawText("Settings",(screenWidth/2) - (MeasureText("Settings",TitleFont)/2)+2,52,TitleFont,BLACK);

	//Master Volume
	DrawText("Master Volume",(screenWidth/2) - (MeasureText("Master Volume",buttonFont)/2)-2,248,buttonFont,BLACK);
	DrawText("Master Volume",(screenWidth/2) - (MeasureText("Master Volume",buttonFont)/2),250,buttonFont,BLACK);
	DrawText("Master Volume",(screenWidth/2) - (MeasureText("Master Volume",buttonFont)/2)+2,252,buttonFont,(sys.choice==40)?RED:WHITE);

	int shiftDown=0;//shift down all below if smth is focussed
	int volumeLevel;//lvl in px of certain volume

	if (sys.choice==40) {//Master Volume range bar if MasterVolume is focussed
		shiftDown=60;
		volumeLevel=(sys.volume[0]==0)?0:(sys.volume[0]*250)/100;
		DrawRectangle((screenWidth/2) - 127,303,10,19,GetColor(0x232323ff));//first end of bar
		DrawRectangle((screenWidth/2) + 117,308,10,19,GetColor(0x232323ff));//end of bar
		DrawRectangle((screenWidth/2) - 127,308,254,14,GetColor(0x232323ff));//outerBar
		DrawRectangle((screenWidth/2) - 125,310,250,10,WHITE);//innerBar
		DrawRectangle((screenWidth/2) - 125,310,volumeLevel,10,RED);//Master Volume Level
		DrawText(TextFormat("%d",sys.volume[0]),(screenWidth/2) + 136,305,18,BLACK);//Master Volume Number
		DrawText(TextFormat("%d",sys.volume[0]),(screenWidth/2) + 137,306,18,BLACK);//Master Volume Number
		DrawText(TextFormat("%d",sys.volume[0]),(screenWidth/2) + 138,307,18,RED);//Master Volume Number
		DrawRectangle((screenWidth/2) - 127+volumeLevel,302,10,26,BLACK);//outerRangeCursor
		DrawRectangle((screenWidth/2) - 125+volumeLevel,304,6,22,RED);//innerRangeCursor

	}

	//Music Volume
	DrawText("Music Volume",(screenWidth/2) - (MeasureText("Music Volume",buttonFont)/2)-2,308+shiftDown,buttonFont,BLACK);
	DrawText("Music Volume",(screenWidth/2) - (MeasureText("Music Volume",buttonFont)/2),310+shiftDown,buttonFont,BLACK);
	DrawText("Music Volume",(screenWidth/2) - (MeasureText("Music Volume",buttonFont)/2)+2,312+shiftDown,buttonFont,(sys.choice==41)?RED:WHITE);

	if (sys.choice==41) {//Music Volume range bar if MusicVolume is focussed
		shiftDown=60;
		volumeLevel=(sys.volume[1]==0)?0:(sys.volume[1]*250)/100;
		DrawRectangle((screenWidth/2) - 127,363,10,19,GetColor(0x232323ff));//first end of bar
		DrawRectangle((screenWidth/2) + 117,368,10,19,GetColor(0x232323ff));//end of bar
		DrawRectangle((screenWidth/2) - 127,368,254,14,GetColor(0x232323ff));//outerBar
		DrawRectangle((screenWidth/2) - 125,370,250,10,WHITE);//innerBar
		DrawRectangle((screenWidth/2) - 125,370,volumeLevel,10,RED);//Master Volume Level
		DrawText(TextFormat("%d",sys.volume[1]),(screenWidth/2) + 136,365,18,BLACK);//Master Volume Number
		DrawText(TextFormat("%d",sys.volume[1]),(screenWidth/2) + 137,366,18,BLACK);//Master Volume Number
		DrawText(TextFormat("%d",sys.volume[1]),(screenWidth/2) + 138,367,18,RED);//Master Volume Number
		DrawRectangle((screenWidth/2) - 127+volumeLevel,362,10,26,BLACK);//outerRangeCursor
		DrawRectangle((screenWidth/2) - 125+volumeLevel,364,6,22,RED);//innerRangeCursor

	}

	//Effects Volume
	DrawText("Effects Volume",(screenWidth/2) - (MeasureText("Effects Volume",buttonFont)/2)-2,368+shiftDown,buttonFont,BLACK);
	DrawText("Effects Volume",(screenWidth/2) - (MeasureText("Effects Volume",buttonFont)/2),370+shiftDown,buttonFont,BLACK);
	DrawText("Effects Volume",(screenWidth/2) - (MeasureText("Effects Volume",buttonFont)/2)+2,372+shiftDown,buttonFont,(sys.choice==42)?RED:WHITE);

	if (sys.choice==42) {//Effects Volume range bar if EffectsVolume is focussed
		shiftDown=60;
		volumeLevel=(sys.volume[2]==0)?0:(sys.volume[2]*250)/100;
		DrawRectangle((screenWidth/2) - 127,423,10,19,GetColor(0x232323ff));//first end of bar
		DrawRectangle((screenWidth/2) + 117,428,10,19,GetColor(0x232323ff));//end of bar
		DrawRectangle((screenWidth/2) - 127,428,254,14,GetColor(0x232323ff));//outerBar
		DrawRectangle((screenWidth/2) - 125,430,250,10,WHITE);//innerBar
		DrawRectangle((screenWidth/2) - 125,430,volumeLevel,10,RED);//Master Volume Level
		DrawText(TextFormat("%d",sys.volume[2]),(screenWidth/2) + 136,425,18,BLACK);//Master Volume Number
		DrawText(TextFormat("%d",sys.volume[2]),(screenWidth/2) + 137,426,18,BLACK);//Master Volume Number
		DrawText(TextFormat("%d",sys.volume[2]),(screenWidth/2) + 138,427,18,RED);//Master Volume Number
		DrawRectangle((screenWidth/2) - 127+volumeLevel,422,10,26,BLACK);//outerRangeCursor
		DrawRectangle((screenWidth/2) - 125+volumeLevel,424,6,22,RED);//innerRangeCursor

	}

	//reset the settings
	DrawText("Reset the Settings",(screenWidth/2) - (MeasureText("Reset the Settings",buttonFont)/2)-2,428+shiftDown,buttonFont,BLACK);
	DrawText("Reset the Settings",(screenWidth/2) - (MeasureText("Reset the Settings",buttonFont)/2),430+shiftDown,buttonFont,BLACK);
	DrawText("Reset the Settings",(screenWidth/2) - (MeasureText("Reset the Settings",buttonFont)/2)+2,432+shiftDown,buttonFont,(sys.choice==43)?RED:WHITE);

	//Exit
	DrawText("Exit",(screenWidth/2) - (MeasureText("Exit",buttonFont)/2)-2,488+shiftDown,buttonFont,BLACK);
	DrawText("Exit",(screenWidth/2) - (MeasureText("Exit",buttonFont)/2),490+shiftDown,buttonFont,BLACK);
	DrawText("Exit",(screenWidth/2) - (MeasureText("Exit",buttonFont)/2)+2,492+shiftDown,buttonFont,(sys.choice==40+settingsOpt)?RED:WHITE);
}
/* ---------------------------------------------------------------------------------------------------------*/
