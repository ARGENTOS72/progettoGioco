/*
    Test principale di un possibile gioco

    //------------ATTENZIONE------------

    Dimensioni delle hitbox, personaggi ecc...
    sono tutte provvisorie utilizzate per
    fare i test, mancono ancora i controlli
    per la vittoria e i menu logicamente

*/

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//struttura kiriko (tu) senza typedef non l'avevano spiegato
struct pg{
    int x;                  //coordinate
	int y;
	int vX;                 //velocita
	int vY;
	int width;              //dimensioni
	int height;
	Texture2D immagine;     //immagine
};
//struttura ciambella/nemico attualmente 1 bot
struct en{
    int x;
	int y;
	int vX;
	int vY;
	int width;
	int height;
	Texture2D immagine;
};
//dimensioni schermo
const int screenWidth = 1000;
const int screenHeight = 600;
//inizializzazione strutture
struct pg player;
struct en enemy;

int main(void){
    //Initialization
    int punteggio=0;        //variabile vecchia usata per test
    int hpPlayer=100;       //vita giocatore
    int hpEnemy=490;        //vita nemico
    int xVel, yVel;         //variabili per velocità
    InitWindow(screenWidth, screenHeight,"test_1");
    Rectangle hitArea;
    //inizializzo la ciambella e la posizione, con la posizione del rettangolo per le hitbox mettendole uguali
    Rectangle nemico;
    enemy.x=400;
    enemy.y=300;
    enemy.width=30;
    enemy.height=30;
    enemy.immagine = LoadTexture("immagini/ciambella.png");

    nemico.x=enemy.x;
    nemico.y=enemy.y;
    nemico.width=enemy.width;
    nemico.height=enemy.height;
    //inizializzo il player e la posizione, con la posizione del rettangolo per le hitbox mettendole uguali
    Rectangle giocatore;
    player.x=400;
    player.y=500;
    player.width=40;
    player.height=40;
    player.immagine = LoadTexture("immagini/kiriko.png");

    giocatore.x=player.x;
    giocatore.y=player.y;
    giocatore.width=player.width;
    giocatore.height=player.height;

    //inizializzo tutte le hitbox degli attacchi del nemico, forse se ne può far solo 1, non ottimizzato, 1 quadrato per lato
    Rectangle hitNemicoDestra;
    hitNemicoDestra.x=enemy.x+30;
    hitNemicoDestra.y=enemy.y-10;
    hitNemicoDestra.width=50;
    hitNemicoDestra.height=50;

    Rectangle hitNemicoSinistra;
    hitNemicoSinistra.x=enemy.x-60;
    hitNemicoSinistra.y=enemy.y-10;
    hitNemicoSinistra.width=50;
    hitNemicoSinistra.height=50;


    Rectangle hitNemicoSopra;
    hitNemicoSopra.x=enemy.x-8;
    hitNemicoSopra.y=enemy.y-55;
    hitNemicoSopra.width=50;
    hitNemicoSopra.height=50;

    Rectangle hitNemicoSotto;
    hitNemicoSotto.x=enemy.x-8;
    hitNemicoSotto.y=enemy.y+35;
    hitNemicoSotto.width=50;
    hitNemicoSotto.height=50;

    //NOOOO I BOOLEANIIIII, variabili che servono per le hit
    bool colpito=false;
    int frame_count=0,frame_count1=0,frame_count2=0,frame_count3=0;

    SetTargetFPS(60); //Framerate
    //--------------------------------------------------------------------------------------

    //Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
         // Update
        //----------------------------------------------------------------------------------
        //Player movement
        if (IsKeyDown(KEY_D)){
            player.x += 4.0f;
            if(IsKeyPressed(KEY_M)){
                player.x+=40;
            }
        }
        if (IsKeyDown(KEY_A)){
            player.x -= 4.0f;
            if(IsKeyPressed(KEY_M)){
                player.x-=40;
            }
        }
        if (IsKeyDown(KEY_W)){
            player.y -= 4.0f;
            if(IsKeyPressed(KEY_M)){
                player.y-=40;
            }
        }
        if (IsKeyDown(KEY_S)){
            player.y += 4.0f;
            if(IsKeyPressed(KEY_M)){
                player.y+=40;
            }
        }
        //per mantenere la posizione delle hitbox
        giocatore.x=player.x;
        giocatore.y=player.y;

        //genera la hitbox in base a che freccetta viene premuta, (hit tra colpi del giocatore e nemico)
        //il rettangolo colorato serve solo per visualizzare l'area della hitbox
        if (IsKeyPressed(KEY_UP)){
            DrawRectangle(player.x,(player.y-50),50,50,RED);
            hitArea.x=player.x;
            hitArea.y=(player.y-50);
            hitArea.width=50;
            hitArea.height=50;

            if(CheckCollisionRecs(nemico, hitArea)){
                hpEnemy-=10; //diminuisce la vita del nemico
            }
        }
        if (IsKeyPressed(KEY_DOWN)){
            DrawRectangle(player.x,(player.y+80),50,50,RED);
            hitArea.x=player.x;
            hitArea.y=(player.y+80);
            hitArea.width=50;
            hitArea.height=50;

            if(CheckCollisionRecs(nemico, hitArea)){
                hpEnemy-=10;
            }
        }
        if (IsKeyPressed(KEY_LEFT)){
            DrawRectangle((player.x-40),player.y,50,80,RED);
            hitArea.x=(player.x-40);
            hitArea.y=player.y;
            hitArea.width=50;
            hitArea.height=80;

            if(CheckCollisionRecs(nemico, hitArea)){
                hpEnemy-=10;
            }
        }
        if (IsKeyPressed(KEY_RIGHT)){
            DrawRectangle((player.x+40),player.y,50,80,RED);
            hitArea.x=(player.x+40);
            hitArea.y=player.y;
            hitArea.width=50;
            hitArea.height=80;

            if(CheckCollisionRecs(nemico, hitArea)){
                hpEnemy-=10;
            }
        }

        //Enemy Movement
        if(enemy.x>=player.x){  //meno fluido
            enemy.x -= 1.0f;
        }
        if(enemy.x<=player.x){
            enemy.x += 1.0f;
        }
        if(enemy.y>=(player.y+40)){
            enemy.y -= 1.0f;
        }
        if(enemy.y<=(player.y+40)){
            enemy.y += 1.0f;
        }
        //per mantenere le varie hitbox degli attacchi del nemico in posizioni corrette
        hitNemicoDestra.x=enemy.x+30;
        hitNemicoDestra.y=enemy.y-10;
        hitNemicoSinistra.x=enemy.x-60;
        hitNemicoSinistra.y=enemy.y-10;
        hitNemicoSopra.x=enemy.x-8;
        hitNemicoSopra.y=enemy.y-55;
        hitNemicoSotto.x=enemy.x-8;
        hitNemicoSotto.y=enemy.y+35;
        /*xVel = player.x - enemy.x;  //prova movimento ma è troppo veloce
        yVel = player.y - enemy.y;
        enemy.x += xVel * GetFrameTime();
        enemy.y += yVel * GetFrameTime();*/
        nemico.x=enemy.x;
        nemico.y=enemy.y;

        //Hitbox tra i colpi del nemico e il giocatore col framecounter permette di temporizzare i colpi del nemico
        if(CheckCollisionRecs(hitNemicoDestra, giocatore)){     //funz no bool, per fortuna ragazzi niente booleani
            if(frame_count<=61){
                frame_count++;                                  //frame counter diversi per ogni parte, forse ottimizzabile
            }
            if(frame_count==60){                                //quando passa 1 secondo il nemico colpisce
                DrawRectangle(enemy.x+30,enemy.y-10,50,50,RED);
                hpPlayer-=5; //diminuisce la vita del player
                frame_count=0;
            }
        }

        if(CheckCollisionRecs(hitNemicoSinistra, giocatore)){
            if(frame_count1<=61){
                frame_count1++;
            }
            if(frame_count1==60){
                DrawRectangle(enemy.x-60,enemy.y-10,50,50,GREEN);
                hpPlayer-=5;
                frame_count1=0;
            }
        }

        if(CheckCollisionRecs(hitNemicoSopra, giocatore)){
                if(frame_count2<=61){
                    frame_count2++;
                }
                if(frame_count2==60){
                    DrawRectangle(enemy.x-8,enemy.y-55,50,50,VIOLET);
                    hpPlayer-=5;
                    frame_count2=0;
                }

        }

        if(CheckCollisionRecs(hitNemicoSotto, giocatore)){
                if(frame_count3<=61){
                    frame_count3++;
                }
                if(frame_count3==60){
                    DrawRectangle(enemy.x-8,enemy.y+35,50,50,ORANGE);
                    hpPlayer-=5;
                    frame_count3=0;
                }

        }

        //questi erano dei test per visualizzare le aree delle hitbox si possono togliere
        /*if(player.x+10>enemy.x-50 && player.x+10<enemy.x-10 && player.y+40>enemy.y-30 && player.y+40<enemy.y+30){
            DrawRectangle(enemy.x-50,enemy.y-10,40,40,GREEN);

        }
        /*if(player.x+10>enemy.x-8 && player.x+10<enemy.x+30 && player.y+40>enemy.y-55 && player.y+40<enemy.y-10){
            DrawRectangle(enemy.x-8,enemy.y-55,40,40,VIOLET);

        }/
        if(player.x+10>enemy.x-8 && player.x+10<enemy.x+30 && player.y+40<enemy.y+35 && player.y+40>enemy.y-10){
            DrawRectangle(enemy.x-8,enemy.y+35,40,40,RED);

        }*/

        //Stampa su schermo
        BeginDrawing();

            ClearBackground(WHITE);                                                 //sfondo
            DrawTexture(player.immagine, player.x, player.y, WHITE);                //giocatore
            DrawTexture(enemy.immagine, enemy.x, enemy.y, WHITE);                   //nemico
            DrawText(TextFormat("hp enemy: %03i", hpEnemy), 300, 50, 30, BLACK);    //vita nemico
            DrawText(TextFormat("hp player: %03i", hpPlayer), 300, 90, 30, BLACK);  //vita giocatore
            DrawRectangle(230,500,500,10,BLACK);                                    //barra della vita del nemico
            DrawRectangle(235,502,hpEnemy,6,RED);

        EndDrawing();
    }

    UnloadTexture(player.immagine);
    UnloadTexture(enemy.immagine);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
