#include "headers/game_manager.h"

int main() {
    //init general
    InitWindow(0,0, "Kiriko and the donuts");//FullScreen
    ToggleFullscreen();
    screenWidth=GetScreenWidth();//get FullScreen width
    screenHeight=GetScreenHeight();//get FullScreen height
    InitAudioDevice();
    HideCursor();

    //init var
    System sys;
    sys.choice=1;
    sys.volume[0]=75;
    sys.volume[1]=50;
    sys.volume[2]=70;
	
    //img
    Texture2D lobbyBg = LoadTexture("img/bg1.png");
	
    //textures
    Texture2D donut = LoadTexture("prew project/immagini/ciambella.png");
	
    //sound
    Sound slash = LoadSound("audio/slash.mp3");
    SetSoundVolume(slash, ((float)sys.volume[2]/100)*((float)sys.volume[0]/100));
	
    //music
    Music Kikrok = LoadMusicStream("audio/samurai.mp3");
    Kikrok.looping=true;
    SetMusicVolume(Kikrok, ((float)sys.volume[1]/100)*((float)sys.volume[0]/100));
    PlayMusicStream(Kikrok);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
    	
        if (sys.choice<10) {//Lobby ------------------------------------
            //update
            UpdateMusicStream(Kikrok);
			
            //events
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
                sys.choice--;
                if (sys.choice<1) sys.choice=lobbyOpt;
                PlaySoundMulti(slash);
            }
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
                sys.choice++;
                if (sys.choice>lobbyOpt) sys.choice=1;
                PlaySoundMulti(slash);
            }
            if (IsKeyPressed(KEY_ENTER)) sys.choice*=10;//confirm
			
            } else if (sys.choice==10) {//Training ------------------------
			
            } else if (sys.choice==20) {//Duel ----------------------------
		
            } else if (sys.choice==30) {//Survival ------------------------
			
            } else if (sys.choice>=40 && sys.choice<=40+settingsOpt) {//Setings -------------------------
                //update
		UpdateMusicStream(Kikrok);
			
		//events
		if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
		    sys.choice--;
		    if (sys.choice<40) sys.choice=40+settingsOpt;
		    PlaySoundMulti(slash);
		}
		if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
		    sys.choice++;
		    if (sys.choice>40+settingsOpt) sys.choice=40;
		    PlaySoundMulti(slash);
		}
		if  ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && sys.choice<40+settingsOpt) {//right
		    sys.volume[sys.choice-40]=(sys.volume[sys.choice-40]+5>100)?100:sys.volume[sys.choice-40]+5;//prevent overpass 100
		    if (sys.choice==40 || sys.choice==41) {
		        SetMusicVolume(Kikrok, ((float)sys.volume[1]/100)*((float)sys.volume[0]/100));//adapt new volume
		    }
		    if (sys.choice==40 || sys.choice==42) {
		        SetSoundVolume(slash, ((float)sys.volume[2]/100)*((float)sys.volume[0]/100));//adapt new volume
		    }

		}
		if  ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && sys.choice<40+settingsOpt) {//left
		    sys.volume[sys.choice-40]=(sys.volume[sys.choice-40]-5<0)?0:sys.volume[sys.choice-40]-5;//prevent overpass 0
		    if (sys.choice==40 || sys.choice==41) {
		        SetMusicVolume(Kikrok, ((float)sys.volume[1]/100)*((float)sys.volume[0]/100));//adapt new volume
		    }
		    if (sys.choice==40 || sys.choice==42) {
		        SetSoundVolume(slash, ((float)sys.volume[2]/100)*((float)sys.volume[0]/100));//adapt new volume
		    }
		}
		if (IsKeyPressed(KEY_ENTER))  {//enter
		    if (sys.choice==43) {//reset settings
		        sys.volume[0]=75;
			sys.volume[1]=50;
			sys.volume[2]=70;
			SetMusicVolume(Kikrok, ((float)sys.volume[1]/100)*((float)sys.volume[0]/100));
			SetSoundVolume(slash, ((float)sys.volume[2]/100)*((float)sys.volume[0]/100));
		    }
		    else if (sys.choice==40+settingsOpt) sys.choice=1;//exit
		}

            }
		
            BeginDrawing();//Draw ---------------------------------------
                ClearBackground(WHITE);
                if (sys.choice<10) {//Lobby
		        DrawTextureEx(lobbyBg, (Vector2){0,0},0,0.724,WHITE);//bg
		    DrawLobby(sys.choice);//buttons
				
	        } else if (sys.choice==10) {//Training
		    DrawText("You are now in training mode",(screenWidth/2) - (MeasureText("You are now in training mode",TitleFont)/2)-2,48,TitleFont,RED);
		    DrawText("You are now in training mode",(screenWidth/2) - (MeasureText("You are now in training mode",TitleFont)/2),50,TitleFont,BLACK);
		    DrawText("You are now in training mode",(screenWidth/2) - (MeasureText("You are now in training mode",TitleFont)/2)+2,52,TitleFont,BLACK);
				
	        } else if (sys.choice==20) {//Duel
		    DrawText("You are now in duel mode",(screenWidth/2) - (MeasureText("You are now in duel mode",TitleFont)/2)-2,48,TitleFont,RED);
		    DrawText("You are now in duel mode",(screenWidth/2) - (MeasureText("You are now in duel mode",TitleFont)/2),50,TitleFont,BLACK);
		    DrawText("You are now in duel mode",(screenWidth/2) - (MeasureText("You are now in duel mode",TitleFont)/2)+2,52,TitleFont,BLACK);
				
	        } else if (sys.choice==30) {//Survival
		    DrawText("You are now in survival mode",(screenWidth/2) - (MeasureText("You are now in survival mode",TitleFont)/2)-2,48,TitleFont,RED);
		    DrawText("You are now in survival mode",(screenWidth/2) - (MeasureText("You are now in survival mode",TitleFont)/2),50,TitleFont,BLACK);
		    DrawText("You are now in survival mode",(screenWidth/2) - (MeasureText("You are now in survival mode",TitleFont)/2)+2,52,TitleFont,BLACK);

	        } else if (sys.choice>=40 && sys.choice<=40+settingsOpt) {//Settings
		    DrawTextureEx(lobbyBg, (Vector2){0,0},0,0.724,WHITE);//bg
		    DrawSettings(sys);
				
		}
            EndDrawing();
		
    }
    
    //unload resources
    UnloadTexture(lobbyBg);
    UnloadTexture(donut);
    
    UnloadMusicStream(Kikrok);
    
    UnloadSound(slash);
    
    CloseWindow();
    
    return 0;
}
