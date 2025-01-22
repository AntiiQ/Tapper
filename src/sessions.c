/*Code for morse sessions such as the standard lesson challanges*/

#include "raylib.h"
#include "raygui.h"

#include "include/morseutils.h"
#include "include/utils.h"
#include "include/settings.h"

#include <string.h>


void GroupsOf5Characters(char* output, int amountOfChars, const char* selectedChars)
{
    int i, j = 0;
    int groupSize = 5;
    int totalOutputSize = amountOfChars + (amountOfChars - 1) / groupSize;
    
    for (i = 0; i < amountOfChars; i++) {
        // Add a space after every group of 5 characters, except the last group
        if (i > 0 && i % groupSize == 0) {
            output[j++] = ' ';
        }
        // Add a random character from selectedChars
        output[j++] = selectedChars[rand() % strlen(selectedChars)];
    }
    output[j] = '\0'; // Null-terminate the output string
}


// ~1 minute decoding session for practice and lessons
void StandardDecodingSession(char* selectCharacters, Config config)
{
    int unit = GetScreenHeight() / 36;
    int titleFontSize = (int) ((0.144444444) * GetScreenHeight()) + 6;

    bool buttonReturn;

    char plainText[300] = "";
    char morse[2048] = " / ";

    GroupsOf5Characters(plainText, config.wpm * 5, selectCharacters);
    EncodeTextStr(plainText + 3, morse, 2048);

    AudioStream stream;
    InitAudio(&stream, config.volume, config.pitch);


    while (!(WindowShouldClose() || buttonReturn))
    {    
        CheckDisplayGrid();

        BeginDrawing();
        Clear();
        DrawLinedRectangle(unit, unit, 62 * unit, 34 * unit, OVERLAYT(230), MUTED);

        DrawText("Decoding", 4* unit, unit, titleFontSize, MUTED);

        buttonReturn = GuiButton((Rectangle){60 * unit, 2 * unit,  2 * unit, 2 *unit}, "X");

        EndDrawing();
    }

    FreeAudio(&stream);

}