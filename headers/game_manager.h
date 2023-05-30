#include "raylib.h"

//general defines ------------------------
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#define TitleFont 90
#define subTitleFont 60
#define buttonFont 40
#define textFont 30
#define lobbyOpt 7
#define settingsOpt 4
//----------------------------------------

//general structs ------------------------
typedef struct {
	int choice;
	int volume[3];
	int pause;
	int setting;
} System;
//----------------------------------------

//global variables -----------------------
/*N.B.: tutte i file con "temp" sono provvisori in attesa della grafica finale*/
int screenWidth, screenHeight;//screen
double p_x, p_y, p_width, p_height;// temp var for player
Vector2 mousePos;//mouse
Rectangle resumeBtn, settingsBtn, exitBtn;//pause buttons
System sys;
Texture2D lobbyBg, trainingFloor, no_texture, donut, kiriko, mouseTexture;//textures & img
Sound slash, currentSound;//sound
Music lobbyMusic, survivalMusic, duelMusic, currentMusic;//music
//----------------------------------------

/*-------------------------------------------- general functions -------------------------------------------*/
void DrawTextSF(char *text, int x, int y, int font, Color col1, Color col2, Color col3) {
	DrawText(text,x-2,y-2,font,col1);
	DrawText(text,x,y,font,col2);
	DrawText(text,x+2,y+2,font,col3);
}

void DrawRangeBar(int progress, int height) {
	int progressLenght=(!progress)?0:progress*2.5;

	DrawRectangle((screenWidth/2) - 127,height,10,19,GetColor(0x232323ff));//first end of bar
	DrawRectangle((screenWidth/2) + 117,height+5,10,19,GetColor(0x232323ff));//end of bar
	DrawRectangle((screenWidth/2) - 127,height+5,254,14,GetColor(0x232323ff));//outerBar
	DrawRectangle((screenWidth/2) - 125,height+7,250,10,WHITE);//innerBar
	DrawRectangle((screenWidth/2) - 125,height+7,progressLenght,10,RED);//Master Volume Level
	DrawText(TextFormat("%d",progress),(screenWidth/2)+136,height+2,18,BLACK);//Master Volume Number
	DrawText(TextFormat("%d",progress),(screenWidth/2)+137,height+3,18,BLACK);//Master Volume Number
	DrawText(TextFormat("%d",progress),(screenWidth/2)+138,height+4,18,RED);//Master Volume Number
	DrawRectangle((screenWidth/2) - 127+progressLenght,height-1,10,26,BLACK);//outerRangeCursor
	DrawRectangle((screenWidth/2) - 125+progressLenght,height+1,6,22,RED);//innerRangeCursor
}
/* ---------------------------------------------------------------------------------------------------------*/

/* ----------------------------------------- Lobby & Settings section --------------------------------------*/
void DrawLobby () {
	DrawTextureEx(lobbyBg, (Vector2){0,0},0,(float) screenWidth/1920,WHITE);//bg
	//title
	DrawTextSF((char*)"Kiriko",(screenWidth/2) - (MeasureText("Kiriko",TitleFont)/2),50,TitleFont,RED,BLACK,BLACK);
	DrawTextSF((char*)"and the donuts",(screenWidth/2) - (MeasureText("and the donuts",subTitleFont)/2)+2,142,subTitleFont,RED,BLACK,BLACK);
	//training
	DrawTextSF((char*)"Training",12,252,buttonFont,BLACK,BLACK,(sys.choice==1)?RED:WHITE);
	//duel
	DrawTextSF((char*)"Duel",12,302,buttonFont,BLACK,BLACK,(sys.choice==2)?RED:WHITE);
	//survival
	DrawTextSF((char*)"Survival",12,352,buttonFont,BLACK,BLACK,(sys.choice==3)?RED:WHITE);
	//settings
	DrawTextSF((char*)"Settings",12,402,buttonFont,BLACK,BLACK,(sys.choice==4)?RED:WHITE);
	//how to play
	DrawTextSF((char*)"How to play",12,452,buttonFont,BLACK,BLACK,(sys.choice==5)?RED:WHITE);
	//credits
	DrawTextSF((char*)"Credits",12,502,buttonFont,BLACK,BLACK,(sys.choice==6)?RED:WHITE);
	//exit game
	DrawTextSF((char*)"Exit game",12,552,buttonFont,BLACK,BLACK,(sys.choice==7)?RED:WHITE);
}

void DrawSettings (int choice, Texture2D bg) {
	DrawTextureEx(bg,(Vector2){0,0},0,(float) screenWidth/1920,WHITE);//bg
	//title
	DrawTextSF((char*)"Settings",(screenWidth/2) - (MeasureText("Settings",TitleFont)/2),50,TitleFont,RED,BLACK,BLACK);
	//Master Volume
	DrawTextSF((char*)"Master Volume",(screenWidth/2) - (MeasureText("Master Volume",buttonFont)/2),250,buttonFont,BLACK,BLACK,(choice==40)?RED:WHITE);

	int shiftDown=0, volumeLevel;//shift down all below if smth is focussed & lvl in px of certain volume

	if (choice==40) {//Master Volume range bar if MasterVolume is focussed
		shiftDown=60;
  		DrawRangeBar(sys.volume[0],303);
	}

	//Music Volume
	DrawTextSF((char*)"Music Volume",(screenWidth/2) - (MeasureText("Music Volume",buttonFont)/2),310+shiftDown,buttonFont,BLACK,BLACK,(choice==41)?RED:WHITE);

	if (choice==41) {//Music Volume range bar if MusicVolume is focussed
		shiftDown=60;
		DrawRangeBar(sys.volume[1],363);
	}

	//Effects Volume
	DrawTextSF((char*)"Effects Volume",(screenWidth/2) - (MeasureText("Effects Volume",buttonFont)/2),370+shiftDown,buttonFont,BLACK,BLACK,(choice==42)?RED:WHITE);

	if (choice==42) {//Effects Volume range bar if EffectsVolume is focussed
		shiftDown=60;
		DrawRangeBar(sys.volume[2],423);
	}

	//reset the settings
	DrawTextSF((char*)"Reset the Settings",(screenWidth/2) - (MeasureText("Reset the Settings",buttonFont)/2),430+shiftDown,buttonFont,BLACK,BLACK,(choice==43)?RED:WHITE);
	//Exit
	DrawTextSF((char*)"Exit",(screenWidth/2) - (MeasureText("Exit",buttonFont)/2),490+shiftDown,buttonFont,BLACK,BLACK,(choice==40+settingsOpt)?RED:WHITE);
}

void HandleSettingsEvents(int *choice, int pause) {
	//events
	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
		*choice-=1;
		if (*choice<40) *choice=40+settingsOpt;
		PlaySoundMulti(currentSound);
	}
	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
		*choice+=1;
		if (*choice>40+settingsOpt) *choice=40;
		PlaySoundMulti(currentSound);
	}
	if  ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && *choice<40+settingsOpt) {//right
		sys.volume[*choice-40]=(sys.volume[*choice-40]+5>100)?100:sys.volume[*choice-40]+5;//prevent overpass 100
		if (*choice==40 || *choice==41) {
			SetMusicVolume(currentMusic,((float)sys.volume[1]/100)*((float)sys.volume[0]/100));//adapt new volume
		}
		if (*choice==40 || *choice==42) {
			SetSoundVolume(currentSound,((float)sys.volume[2]/100)*((float)sys.volume[0]/100));//adapt new volume
		}

	}
	if  ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && *choice<40+settingsOpt) {//left
		sys.volume[*choice-40]=(sys.volume[*choice-40]-5<0)?0:sys.volume[*choice-40]-5;//prevent overpass 0
		if (*choice==40 || *choice==41) {
			SetMusicVolume(currentMusic, ((float)sys.volume[1]/100)*((float)sys.volume[0]/100));//adapt new volume
		}
		if (*choice==40 || *choice==42) {
			SetSoundVolume(currentSound, ((float)sys.volume[2]/100)*((float)sys.volume[0]/100));//adapt new volume
		}
	}
	if (IsKeyPressed(KEY_ENTER))  {//enter
		if (*choice==43) {//reset settings
			sys.volume[0]=75;
			sys.volume[1]=50;
			sys.volume[2]=70;
			SetMusicVolume(currentMusic,((float)sys.volume[1]/100)*((float)sys.volume[0]/100));
			SetSoundVolume(currentSound,((float)sys.volume[2]/100)*((float)sys.volume[0]/100));
		}
		else if (*choice==40+settingsOpt) {//exit
			*choice=pause;//back to prew/paused choice
		}
	}
}
/* ---------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------- Pause Functions ---------------------------------------------*/
void DrawPause() {
	DrawRectangle(0,0,screenWidth,screenHeight,GetColor(0x000005f));//darken screen
	
	//pause body
	//DrawRectangle((screenWidth*0.4)-7,(screenHeight*0.35)-7,(screenWidth*0.15)+9,179,BLACK);//outerborder up1
	DrawRectangle((screenWidth*0.4)-12,(screenHeight*0.35)-12,(screenWidth*0.1)+14,141.5,BLACK);//outerborder up2
	//DrawRectangle((screenWidth*0.4)-5,(screenHeight*0.35)-5,(screenWidth*0.15)+5,175,RED);//border up1
	DrawRectangle((screenWidth*0.4)-10,(screenHeight*0.35)-10,(screenWidth*0.1)+10,137.5,RED);//border up2

	//DrawRectangle((screenWidth*0.45)-2,(screenHeight*0.35)+83,(screenWidth*0.15)+9,179,BLACK);//outerborder down1
	DrawRectangle((screenWidth*0.5)-2,(screenHeight*0.35)+125.5,(screenWidth*0.1)+14,141.5,BLACK);//outerborder down2
	//DrawRectangle((screenWidth*0.45),(screenHeight*0.35)+85,(screenWidth*0.15)+5,175,RED);//border down1
	DrawRectangle(screenWidth*0.5,(screenHeight*0.35)+127.5,(screenWidth*0.1)+10,137.5,RED);//border down2

	DrawRectangle(screenWidth*0.4,screenHeight*0.35,screenWidth*0.2,255,BLACK);//outerbody
	DrawRectangle((screenWidth*0.4)+5,(screenHeight*0.35)+5,(screenWidth*0.2)-10,245,GRAY);//innerbody
	//title
	DrawTextSF((char*)"Pause",(screenWidth/2)-(MeasureText("Pause",subTitleFont)/2)+2,(screenHeight/20)*7+12,subTitleFont,RED,BLACK,BLACK);
	//pause line separator
	DrawLineEx((Vector2) {(float)(screenWidth/10)*4+10,(float)(screenHeight/20)*7+68},(Vector2) {(float)(screenWidth/10)*6-19,(float)(screenHeight/20)*7+68},2,BLACK);
	DrawLineEx((Vector2) {(float)(screenWidth/10)*4+12,(float)(screenHeight/20)*7+70},(Vector2) {(float)(screenWidth/10)*6-17,(float)(screenHeight/20)*7+70},2,RED);
	DrawLineEx((Vector2) {(float)(screenWidth/10)*4+14,(float)(screenHeight/20)*7+72},(Vector2) {(float)(screenWidth/10)*6-15,(float)(screenHeight/20)*7+72},2,BLACK);
	//option resume
	DrawTextSF((char*)"resume",(screenWidth/2) - (MeasureText("resume",buttonFont)/2),(screenHeight/20)*7+85,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,resumeBtn)?RED:WHITE);
	//option settings
	DrawTextSF((char*)"settings",(screenWidth/2) - (MeasureText("settings",buttonFont)/2),(screenHeight/20)*7+145,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,settingsBtn)?RED:WHITE);
	//option exit
	DrawTextSF((char*)"exit",(screenWidth/2) - (MeasureText("exit",buttonFont)/2),(screenHeight/20)*7+205,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,exitBtn)?RED:WHITE);
	//mouse
	DrawTextureV(mouseTexture,mousePos,WHITE);//mouse
}

void DrawSettingsPaused() {
	DrawRectangle(0,0,screenWidth,screenHeight,GetColor(0x000005f));
	//settings body
	DrawRectangle((screenWidth*0.5)-(MeasureText("Settings",TitleFont)/2)-60,0,10,screenHeight/2,BLACK);//outerborder up2
	DrawRectangle((screenWidth*0.5)-(MeasureText("Settings",TitleFont)/2)-58,0,8,(screenHeight/2)-2,RED);//border up2

	DrawRectangle((screenWidth*0.5)+(MeasureText("Settings",TitleFont)/2)+50,screenHeight/2,10,screenHeight/2,BLACK);//outerborder down2
	DrawRectangle((screenWidth*0.5)+(MeasureText("Settings",TitleFont)/2)+50,screenHeight/2+2,8,screenHeight/2-2,RED);//border down2
	DrawRectangle((screenWidth*0.5)-(MeasureText("Settings",TitleFont)/2)-50,0,MeasureText("Settings",TitleFont)+100,screenHeight,BLACK);//outerbody
	DrawRectangle((screenWidth*0.5)-(MeasureText("Settings",TitleFont)/2)-45,0,MeasureText("Settings",TitleFont)+90,screenHeight,GRAY);//innerbody
	//button
	DrawSettings(sys.setting,no_texture);
	//separator line
	DrawLineEx((Vector2){(screenWidth*0.5)-(MeasureText("Settings",TitleFont)/2)-37,198},(Vector2){(screenWidth*0.5)+(MeasureText("Settings",TitleFont)/2)+33,198},3,BLACK);
	DrawLineEx((Vector2){(screenWidth*0.5)-(MeasureText("Settings",TitleFont)/2)-35,200},(Vector2){(screenWidth*0.5)+(MeasureText("Settings",TitleFont)/2)+35,200},3,RED);
	DrawLineEx((Vector2){(screenWidth*0.5)-(MeasureText("Settings",TitleFont)/2)-33,202},(Vector2){(screenWidth*0.5)+(MeasureText("Settings",TitleFont)/2)+37,202},3,BLACK);
}
/*----------------------------------------------------------------------------------------------------------*/

/* ----------------------------------------------- Training -------------------------------------------------*/
void DrawTraining(Camera2D camera) {
	BeginMode2D(camera);
		//map
		DrawTextureEx(trainingFloor,(Vector2){(float)-screenWidth,(float)-screenHeight},0,(float)screenWidth/1920,WHITE);
		//player
		DrawTextureEx(kiriko,(Vector2){(float)p_x,(float)p_y},0,1,WHITE);
		//mouse
		if(!sys.pause) DrawTextureV(mouseTexture,mousePos,WHITE);//mouse
	EndMode2D();
}
/* ---------------------------------------------------------------------------------------------------------*/

/* ------------------------------------------------- Duel --------------------------------------------------*/
void DrawDuel() {
	DrawText("You are now in duel mode",(screenWidth/2) - (MeasureText("You are now in duel mode",TitleFont)/2)-2,48,TitleFont,RED);
	DrawText("You are now in duel mode",(screenWidth/2) - (MeasureText("You are now in duel mode",TitleFont)/2),50,TitleFont,BLACK);
	DrawText("You are now in duel mode",(screenWidth/2) - (MeasureText("You are now in duel mode",TitleFont)/2)+2,52,TitleFont,BLACK);
}
/* ---------------------------------------------------------------------------------------------------------*/

/* ----------------------------------------------- Survival ------------------------------------------------*/
void DrawSurvival() {
	DrawText("You are now in survival mode",(screenWidth/2) - (MeasureText("You are now in survival mode",TitleFont)/2)-2,48,TitleFont,RED);
	DrawText("You are now in survival mode",(screenWidth/2) - (MeasureText("You are now in survival mode",TitleFont)/2),50,TitleFont,BLACK);
	DrawText("You are now in survival mode",(screenWidth/2) - (MeasureText("You are now in survival mode",TitleFont)/2)+2,52,TitleFont,BLACK);
}
/* ---------------------------------------------------------------------------------------------------------*/

/* ---------------------------------------------- How to Play ----------------------------------------------*/
void DrawHowToPlay(Camera2D camera) {
	DrawTextureEx(lobbyBg,(Vector2){0,0},0.0f,(float)screenWidth/1920,WHITE);//bg
	DrawRectangle(0,0,screenWidth,screenHeight,GetColor(0x5e5e5e5f));//darken bg
	
	BeginMode2D(camera);
		DrawTextSF((char*)"How to Play",(screenWidth/2) - (MeasureText("How to Play",TitleFont)/2),50,TitleFont,RED,BLACK,BLACK);
		DrawTextSF((char*)"Hi and welcome to 'Kiriko and the donuts!'",(screenWidth/2) - (MeasureText("Hi and welcome to 'Kiriko and the donuts!'",subTitleFont)/2),250,subTitleFont,BLACK,BLACK,RED);

		DrawTextSF((char*)"Basic Commands:",12,350,subTitleFont,BLACK,BLACK,RED);
		DrawText("Use arrows or WASD to move in the menus and ENTER to confirm.",15,420,textFont,BLACK);
		DrawText("In order to exit the game whenever you want, you can always use alt+f4 ",15,450,textFont,BLACK);
		
		DrawTextSF((char*)"In-game Commands:",12,530,subTitleFont,BLACK,BLACK,RED);
		DrawTextSF((char*)"Pause:",15,600,textFont,BLACK,BLACK,RED);
		DrawText(" whenever you are in Training or Survival or Duel, you can always pause",15+MeasureText("Pause:",textFont),600,textFont,BLACK);
		DrawText("the game using ESCAPE, you will then use the mouse to move around the menu,",35,630,textFont,BLACK);
		DrawText("enter again ESCAPE to quick resume.",35,660,textFont,BLACK);

		DrawTextSF((char*)"Training:",15,690,textFont,BLACK,BLACK,RED);
		DrawText(" here you can practice your aim with your mouse against",15+MeasureText("Training:",textFont),690,textFont,BLACK);
		DrawText("the enemies (CLICK button enabled)",35,720,textFont,BLACK);

		DrawTextSF((char*)"Survival and Duel:",15,750,textFont,BLACK,BLACK,RED);
		DrawText(" these two games are endless PvE (Player vs Enemies),",15+MeasureText("Survival and Duel:",textFont),750,textFont,BLACK);
		DrawText("hold on as long as you can for greater records!",35,780,textFont,BLACK);
		DrawText("As the endless says, there is no ending in it except in duel",35,810,textFont,BLACK);
		DrawText("when a player dies, the other wins.",35,840,textFont,BLACK);

		DrawTextSF((char*)"Have a great experience playing all of them!",(screenWidth/2) - (MeasureText("Have a great experience playing all of them!",buttonFont)/2),910,buttonFont,BLACK,BLACK,RED);
 EndMode2D();
}
/* ---------------------------------------------------------------------------------------------------------*/

/* ------------------------------------------------ Credits -------------------------------------------------*/
void DrawCredits(Camera2D camera) {
	DrawTextureEx(lobbyBg,(Vector2){0,0},0.0f,(float)screenWidth/1920,WHITE);//bg
	DrawRectangle(0,0,screenWidth,screenHeight,GetColor(0x5e5e5e5f));//darken bg
	
	BeginMode2D(camera);
		DrawTextSF((char*)"Credits",(screenWidth*0.5) - (MeasureText("Credits",TitleFont)/2),50,TitleFont,RED,BLACK,BLACK);
		DrawTextSF((char*)"Programmers",(screenWidth/2) - (MeasureText("Programmers",buttonFont)/2),200,buttonFont,RED,BLACK,BLACK);
		DrawTextSF((char*)"Bardin Gabriele",(screenWidth/2) - (MeasureText("Bardin Gabriele",buttonFont)/2),260,buttonFont,BLACK,BLACK,RED);
		DrawTextSF((char*)"Tomas Maceira",(screenWidth/2) - (MeasureText("Tomas Maceira",buttonFont)/2),310,buttonFont,BLACK,BLACK,RED);

		DrawTextSF((char*)"Graphic Designer",(screenWidth/2) - (MeasureText("Graphic Designer",buttonFont)/2),410,buttonFont,RED,BLACK,BLACK);
		DrawTextSF((char*)"Textures",(screenWidth/2) - (MeasureText("Textures",buttonFont)/2),460,buttonFont,RED,BLACK,BLACK);
		DrawTextSF((char*)"Aron Capraro",(screenWidth/2) - (MeasureText("Aron Capraro",buttonFont)/2),510,buttonFont,BLACK,BLACK,RED);

		DrawTextSF((char*)"Maps & Backgrounds",(screenWidth/2) - (MeasureText("Maps & Backgrounds",buttonFont)/2),610,buttonFont,RED,BLACK,BLACK);
		DrawTextSF((char*)"Giacomo Pasqualini",(screenWidth/2) - (MeasureText("Giacomo Pasqualini",buttonFont)/2),660,buttonFont,BLACK,BLACK,RED);

		DrawTextSF((char*)"Musics produced by",(screenWidth/2) - (MeasureText("Musics produced by",buttonFont)/2),760,buttonFont,RED,BLACK,BLACK);
		DrawTextSF((char*)"Marllon Silva / xDeviruchi",(screenWidth/2) - (MeasureText("Marllon Silva / xDeviruchi",buttonFont)/2),820,buttonFont,BLACK,BLACK,RED);

		DrawTextSF((char*)"Sounds",(screenWidth/2) - (MeasureText("Sounds",buttonFont)/2),920,buttonFont,RED,BLACK,BLACK);
		DrawTextSF((char*)"Giacomo Pasqualini",(screenWidth/2) - (MeasureText("Giacomo Pasqualini",buttonFont)/2),970,buttonFont,BLACK,BLACK,RED);

		DrawTextSF((char*)"Thanks for Playing!",(screenWidth/2) - (MeasureText("Thanks for Playing!",TitleFont)/2),1100,TitleFont,RED,BLACK,BLACK);
	EndMode2D();
}
/* ---------------------------------------------------------------------------------------------------------*/
