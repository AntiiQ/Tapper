/*Temporary functions that will be moved lated for the sake of redability*/

#include "raylib.h"
#include "raygui.h"

#include "include/temp.h"
#include "include/utils.h"

#include "include/morseutils.h"
#include "include/settings.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



void Testing(void)
{
    int unit = GetScreenHeight() / 36;
    int titleFontSize = (int) ((0.144444444) * GetScreenHeight()) + 6;

    InitAudioDevice();

    Config config = GetConfig();

    bool buttonReturn;

    AudioStream stream1, stream2;
    InitAudio(&stream1, config.volume, config.pitch);
    InitAudio(&stream2, config.volume, config.pitch);



    float heldTime = 0.0f;
    float unheldTime = 0.0f;

    MorsePlayState state = {0, 0, 0, 0};

    char toDraw[256] = "";
    char morse[256] = "--A..";

    while (!(WindowShouldClose() || buttonReturn))
    {    
        /*Uncomment depending on what to test*/

        PlayMorse(&stream2, morse, strlen(morse), config.morseUnit, &state);
            
        UpdateTimeVarsAndPlaySound(&stream1,&heldTime, &unheldTime, 0);
        strcat_c(toDraw, TimeToMorse(&heldTime, &unheldTime, config.morseUnit));

        BeginDrawing();
        Clear();
        CheckDisplayGrid();
        DrawLinedRectangle(unit, unit, 62 * unit, 34 * unit, OVERLAYT(230), MUTED);

        DrawText("Testing", 4* unit, unit, titleFontSize, MUTED);

        buttonReturn = GuiButton((Rectangle){60 * unit, 2 * unit,  2 * unit, 2 *unit}, "X");

    
        DrawText("Press SPACE to start/stop the audio", 10, 10, 20, DARKGRAY);

        DrawText(TextFormat("HeldTime: %f", heldTime), 7*4*unit, 2*unit, 20, DARKGRAY);
        DrawText(TextFormat("unHeldTime: %f", unheldTime), 7*4*unit, 4*unit, 20, DARKGRAY);

        DrawText(toDraw, 4*unit, 12*unit, 20, DARKGRAY);

    
        CheckDisplayFPS();

        EndDrawing();

    }

    // De-initialize
    FreeAudio(&stream1);
    CloseAudioDevice();
}

void Practice(void)
{
    int unit = GetScreenHeight() / 36;
    int titleFontSize = (int) ((0.144444444) * GetScreenHeight()) + 6;

    bool buttonReturn;


    while (!(WindowShouldClose() || buttonReturn))
    {    
        CheckDisplayGrid();


        BeginDrawing();
        Clear();
        DrawLinedRectangle(unit, unit, 62 * unit, 34 * unit, OVERLAYT(230), MUTED);

        DrawText("Practice", 4* unit, unit, titleFontSize, MUTED);

        buttonReturn = GuiButton((Rectangle){60 * unit, 2 * unit,  2 * unit, 2 *unit}, "X");

        EndDrawing();
    }
}

void Online(void)
{
    int unit = GetScreenHeight() / 36;
    int titleFontSize = (int) ((0.144444444) * GetScreenHeight()) + 6;

    bool buttonReturn;


    while (!(WindowShouldClose() || buttonReturn))
    {    
        CheckDisplayGrid();


        BeginDrawing();
        Clear();
        DrawLinedRectangle(unit, unit, 62 * unit, 34 * unit, OVERLAYT(230), MUTED);

        DrawText("Online", 4* unit, unit, titleFontSize, MUTED);

        buttonReturn = GuiButton((Rectangle){60 * unit, 2 * unit,  2 * unit, 2 *unit}, "X");

        EndDrawing();
    }
}

void Statistics(void)
{
    int unit = GetScreenHeight() / 36;
    int titleFontSize = (int) ((0.144444444) * GetScreenHeight()) + 6;

    bool buttonReturn;


    while (!(WindowShouldClose() || buttonReturn))
    {    
        CheckDisplayGrid();


        BeginDrawing();
        Clear();
        DrawLinedRectangle(unit, unit, 62 * unit, 34 * unit, OVERLAYT(230), MUTED);

        DrawText("Statistics", 4* unit, unit, titleFontSize, MUTED);

        buttonReturn = GuiButton((Rectangle){60 * unit, 2 * unit,  2 * unit, 2 *unit}, "X");

        EndDrawing();
    }
}