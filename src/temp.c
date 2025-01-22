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

    

    Config config = GetConfig();

    bool buttonReturn;

    AudioStream stream1, stream2;
    InitAudio(&stream1, config.volume, config.pitch);

    MorseState* inputState = createMorseState(&stream1);


    printf("%f", config.morseUnit);
    while (!(WindowShouldClose() || buttonReturn))
    {    

        updateMorseInput(inputState, config.morseUnit);

        BeginDrawing();
        Clear();
        CheckDisplayGrid();
        DrawLinedRectangle(unit, unit, 62 * unit, 34 * unit, OVERLAYT(230), MUTED);

        DrawText("Testing", 4* unit, unit, titleFontSize, MUTED);

        buttonReturn = GuiButton((Rectangle){60 * unit, 2 * unit,  2 * unit, 2 *unit}, "X");

    
        DrawText("Press SPACE to start/stop the audio", 10, 10, 20, DARKGRAY);

        DrawText(TextFormat("HeldTime: %f", inputState->keyPressTime), 7*4*unit, 2*unit, 20, DARKGRAY);
        DrawText(TextFormat("unHeldTime: %f", inputState->releaseTime), 7*4*unit, 4*unit, 20, DARKGRAY);

        DrawText((inputState->morseString), 4*unit, 12*unit, 20, DARKGRAY);

    
        CheckDisplayFPS();

        EndDrawing();

    }

    // De-initialize
    destroyMorseState(inputState);
    FreeAudio(&stream1);
    CloseAudioDevice();
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