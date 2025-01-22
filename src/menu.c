/*The Main Menu of TAPPER*/

#include "raylib.h"
#include "raygui.h"

#include "include/menu.h"

#include "include/blocks.h"
#include "include/utils.h"


/*Displays the Main Menu, Returns the screen to go to next*/
int Menu(Block blocks[NUM_OF_ROWS][MAX_SIZE])
{
    int unit = GetUnitSize(); //standardized unit
    int titleFontSize = (int) ((0.144444444) * GetScreenHeight()) + 6;
    
    bool buttonLesson = 0;
    bool buttonPractice = 0;
    bool buttonOnline = 0;
    bool buttonStatistics = 0;
    bool buttonSettings = 0;
    bool buttonTesting = 0;
    
    GuiSetStyle(0, 16, 50 + ((GetScreenHeight() - 900) / 20)); // Change the Font Size of some gui elements, nameley buttons
    GuiSetStyle(0, 17, 2); // Changes Font Spacing to 2; originally one

    while (!WindowShouldClose())
    {
        //CheckToggleFullScreen();

        if (buttonLesson) return 1;
        if (buttonPractice) return 2;
        if (buttonOnline) return 3;
        if (buttonStatistics) return 4;
        if (buttonSettings) return 5;

        if (buttonTesting) return 6;

        BeginDrawing();
        Clear();

        UpdateDrawBlocks(NUM_OF_ROWS, blocks);

        CheckDisplayGrid();

        DrawLinedRectangle(2 * unit, 2 * unit, unit * 24, unit * 32, OVERLAYT(230), MUTED);

        DrawText("Tapper", unit * 4, unit * 5, titleFontSize, MUTED);

        //There's probably a better way but it eludes me
        buttonLesson    = GuiButton((Rectangle){8 * unit, 12.5 * unit, 12 * unit, 3 * unit}, "Lessons");
        buttonPractice  = GuiButton((Rectangle){8 * unit, 16.5 * unit, 12 * unit, 3 * unit}, "Practice");
        buttonOnline    = GuiButton((Rectangle){8 * unit, 20.5 * unit, 12 * unit, 3 * unit}, "Online");
        buttonStatistics= GuiButton((Rectangle){8 * unit, 24.5 * unit, 12 * unit, 3 * unit}, "Statistics");
        buttonSettings  = GuiButton((Rectangle){8 * unit, 28.5 * unit, 12 * unit, 3 * unit}, "Settings");

        buttonTesting   = GuiButton((Rectangle){2 * unit, 2 * unit, 2 * unit, 2 * unit}, "T");

        CheckDisplayFPS();
        EndDrawing();
    
    }

    return -1;
}
