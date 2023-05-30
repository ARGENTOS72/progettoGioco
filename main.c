#include "headers/game_manager.h"

int main() {
	//enable vsync (before InitWindow) -> better graphic performance
	SetConfigFlags(FLAG_VSYNC_HINT);
	//init general
    InitWindow(0,0, "Kiriko and the donuts");//FullScreen
	ToggleFullscreen();
    screenWidth=GetScreenWidth();//get FullScreen width
    screenHeight=GetScreenHeight();//get FullScreen height
    InitAudioDevice();
    HideCursor();

	//init var -----------------------------------------------------------------------
	//sys
	System sys=(System){1,{75,50,70},0,0};
	//pause
	resumeBtn=(Rectangle){(screenWidth/2)-(MeasureText("resume",subTitleFont)/2)-2,(screenHeight/20)*7+83,MeasureText("resume",subTitleFont),buttonFont};
	settingsBtn=(Rectangle){(screenWidth/2)-(MeasureText("settings",subTitleFont)/2)-2,(screenHeight/20)*7+143,MeasureText("settings",subTitleFont),buttonFont};
	exitBtn=(Rectangle){(screenWidth/2)-(MeasureText("exit",subTitleFont)/2)-2,(screenHeight/20)*7+203,MeasureText("exit",subTitleFont),buttonFont};
	//camera
	Camera2D camera={0};
    camera.target=(Vector2){0,0};
    camera.offset=(Vector2){0,0};
    camera.rotation=0.0f;
    camera.zoom=1.0f;
    double p_x=0, p_y=0, p_width=49, p_height=80;// temp var for player
    
	/*N.B.: tutte i file con "temp" sono provvisori in attesa della grafica finale*/
	//img
	Texture2D lobbyBg = LoadTexture("img/kiriko-bg.png");
	Texture2D trainingFloor = LoadTexture("img/dojo.png");
	Texture2D no_texture;
	
	//textures
	Texture2D donut = LoadTexture("textures/temp donut.png");
	Texture2D kiriko = LoadTexture("textures/temp kiriko.png");
	Texture2D mouseTexture = LoadTexture("textures/temp mouse.png");
	
	//sound
	Sound slash = LoadSound("audio/slash.mp3");
	//setup sound
	Sound currentSound=slash;//use currentSound to play all the sound with adjusted volume
	SetSoundVolume(currentSound, ((float)sys.volume[2]/100)*((float)sys.volume[0]/100));
	
	//music
	Music lobbyMusic = LoadMusicStream("audio/temp lobby8bit.mp3");
	Music survivalMusic = LoadMusicStream("audio/temp survival8bit.mp3");
	Music duelMusic = LoadMusicStream("audio/temp duel8bit.mp3");
	//setup music
	Music currentMusic = lobbyMusic;//use currentMusic to play all the music with adjusted volume
	currentMusic.looping=true;
	SetMusicVolume(currentMusic, ((float)sys.volume[1]/100)*((float)sys.volume[0]/100));
	PlayMusicStream(currentMusic);

	SetTargetFPS(60);
    while (sys.choice!=lobbyOpt*10) {
    	//general update music
    	UpdateMusicStream(currentMusic);
    	
        if (sys.choice<10) {//Lobby --------------------------------------------------
			//events
			if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
				sys.choice--;
				if (sys.choice<1) sys.choice=lobbyOpt;
				currentSound=slash;
				PlaySoundMulti(currentSound);
			}
			if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
				sys.choice++;
				if (sys.choice>lobbyOpt) sys.choice=1;
				currentSound=slash;
				PlaySoundMulti(currentSound);
			}
			if (IsKeyPressed(KEY_ENTER)) {//confirm
				sys.pause=sys.choice;
				sys.choice*=10;
			}
			
		} else if (sys.choice==10 || sys.choice==20 || sys.choice==30 || sys.choice==50 || sys.choice==60) {//setup modalities -------
			//disable pause
			sys.pause=0;
			//change music
			StopMusicStream(currentMusic);
			if (sys.choice==10 || sys.choice==50) currentMusic=lobbyMusic;
			else if (sys.choice==20) currentMusic=duelMusic;
			else currentMusic=survivalMusic;
			PlayMusicStream(currentMusic);
			//reset camera2D
			camera.target=(Vector2) {0,0};
			//other setup (player xy).......
			p_x=0;
			p_y=0;
			//
			sys.choice++;
			
		} else if (sys.choice==11) {//Training ---------------------------------------
			if (!sys.pause) {//se non e' in pausa
				//update:
				//camera
				if (p_x < -(screenWidth/2) || p_x > (screenWidth/2)) {
					camera.target.x=(p_x < -(screenWidth/2))?-screenWidth:0;
				}
				else camera.target.x=p_x-(screenWidth/2);
				if (p_y < -(screenHeight/2) || p_y > (screenHeight/2)) {
					camera.target.y=(p_y < -(screenHeight/2))?-screenHeight:0;
				}
				else camera.target.y=p_y-(screenHeight/2);
				//mouse position camera
				mousePos=(Vector2) {GetMouseX()+camera.target.x,GetMouseY()+camera.target.y};

				//events
				if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
					p_y=MAX(-screenHeight,p_y-5);
				}
				if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
					p_y=MIN(screenHeight-p_height,p_y+5);
				}
				if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
					p_x=MIN(screenWidth-p_width,p_x+5);
				}
				if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
					p_x=MAX(-screenWidth,p_x-5);
				}
				if (IsKeyReleased(KEY_ESCAPE)) {
					sys.pause=sys.choice;
				}
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//click

				}
			} else {//gioco in pausa
				if (!sys.setting) {//se non su settings
					mousePos=GetMousePosition();
					if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
						sys.pause=0;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,settingsBtn)) {//temporary goto settings
						sys.setting=40;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,exitBtn)) {//goto lobby
						sys.pause=0;
						sys.choice=1;
						currentMusic=lobbyMusic;
						StopMusicStream(currentMusic);
						PlayMusicStream(currentMusic);
					}
				} else {//settings paused
					currentSound=slash;
					HandleSettingsEvents(&sys.setting,sys.volume,0,currentMusic,currentSound);
				}
			}
			
		} else if (sys.choice==21) {//Duel -------------------------------------------
			if (!sys.pause) {//se non e' in pausa
				//events
				if (IsKeyReleased(KEY_ESCAPE)) {
					sys.pause=sys.choice;
				}
			} else {//gioco in pausa
				if (!sys.setting) {//se non su settings
					mousePos=GetMousePosition();
					if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
						sys.pause=0;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,settingsBtn)) {//temporary goto settings
						sys.setting=40;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,exitBtn)) {//goto lobby
						sys.pause=0;
						sys.choice=1;
						currentMusic=lobbyMusic;
						StopMusicStream(currentMusic);
						PlayMusicStream(currentMusic);
					}
				} else {//settings paused
					currentSound=slash;
					HandleSettingsEvents(&sys.setting,sys.volume,0,currentMusic,currentSound);
				}
			}
		} else if (sys.choice==31) {//Survival ---------------------------------------
			if (!sys.pause) {//se non e' in pausa
				//events
				if (IsKeyReleased(KEY_ESCAPE)) {
					sys.pause=sys.choice;
				}
			} else {//gioco in pausa
				if (!sys.setting) {//se non su settings
					mousePos=GetMousePosition();
					if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
						sys.pause=0;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,settingsBtn)) {//temporary goto settings
						sys.setting=40;
					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,exitBtn)) {//goto lobby
						sys.pause=0;
						sys.choice=1;
						currentMusic=lobbyMusic;
						StopMusicStream(currentMusic);
						PlayMusicStream(currentMusic);
					}
				} else {//settings paused
					currentSound=slash;
					HandleSettingsEvents(&sys.setting,sys.volume,0,currentMusic,currentSound);
				}
			}
		} else if (sys.choice>=40 && sys.choice<=40+settingsOpt) {//Settings ----------
			//events
			currentSound=slash;
			HandleSettingsEvents(&sys.choice,sys.volume,sys.pause,currentMusic,currentSound);

		} else if (sys.choice==51) {//how to play-------------------------------------
			//events
			if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {//up
				if (camera.target.y>0) camera.target.y-=5;
			}
			if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {//down
				if (camera.target.y<1000-screenHeight) camera.target.y+=5;
			}
			if (IsKeyPressed(KEY_ESCAPE)) {//confirm
				sys.choice=5;
			}
		}else if (sys.choice==61) {//credits------------------------------------------
			//update
			if (camera.target.y<1020)camera.target.y+=30*GetFrameTime();
			//events
			if (IsKeyPressed(KEY_ESCAPE)) {//goto lobby
				sys.choice=6;
				//set lobby music
				StopMusicStream(currentMusic);
				currentMusic=lobbyMusic;
				PlayMusicStream(currentMusic);
			}
		}
		//general events -  -  -  -  -
		if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_F4)) {//alt+f4 -> exit
			sys.choice=lobbyOpt*10;
		}
		
		BeginDrawing();//Draw --------------------------------------------------------
			ClearBackground(WHITE);
			if (sys.choice<10) DrawLobby(sys.choice,lobbyBg);//lobby --- --- ---
			else if (sys.choice==11) {//Training --- --- --
				DrawTraining(camera,trainingFloor,kiriko,mouseTexture,p_x,p_y,sys.pause);
				if (sys.setting) DrawSettingsPaused(sys,no_texture);//settings
				else if (sys.pause) DrawPause(mouseTexture);//pausa
			}
			else if (sys.choice==21) {//Duel --- --- ---
				DrawDuel();
				if (sys.setting) DrawSettingsPaused(sys,no_texture);//settings
				else if (sys.pause) DrawPause(mouseTexture);//pausa
			}
			else if (sys.choice==31) {//Survival --- --- ---
				DrawSurvival();
				if (sys.setting) DrawSettingsPaused(sys,no_texture);//settings
				else if (sys.pause) DrawPause(mouseTexture);//pausa
			}
			else if (sys.choice>=40 && sys.choice<=40+settingsOpt) DrawSettings(sys.choice,sys.volume,lobbyBg);//Settings
			else if (sys.choice==51) DrawHowToPlay(camera,lobbyBg);
			else if (sys.choice==61) DrawCredits(camera,lobbyBg);
		EndDrawing();
		
    }
    
    //unload resources
    UnloadTexture(lobbyBg);
    UnloadTexture(donut);
    
    UnloadMusicStream(lobbyMusic);
    UnloadMusicStream(duelMusic);
    UnloadMusicStream(survivalMusic);
    
    UnloadSound(slash);
    
    CloseWindow();
    
    return 0;
}
