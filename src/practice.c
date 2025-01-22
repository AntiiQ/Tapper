/*Practice Screen for Tapper*/

#include "raylib.h"
#include "raygui.h"

#include "include/practice.h"

#include "include/settings.h"
#include "include/utils.h"

/*The Practice Selection Screen*/
void Practice(Config config)
{
    int unit = GetUnitSize();
    int titleFontSize = (int) ((0.144444444) * GetScreenHeight()) - 10;
    int fontSize = 50 + (GetScreenHeight() - 900) / 18;
    
    int guiFontLarge = 50 + ((GetScreenHeight() - 900) / 20), guiFontSmall = 30 + (GetScreenHeight() - 900) / 90;
    
    bool buttonReturn = false, buttonStdDecode = false , buttonStdEncode = false , buttonExtDecode = false , buttonExtEncode = false;

    bool checkLetters = false , checkSymbols = false , checkNumbers = false, checkCustom = false;

    bool dropdownLengthEditMode = false;
    int dropdownLength = 0;

    TextFieldState* textField = createTextFieldState(128, (Rectangle) {5*unit, 20* unit, 34* unit, 7* unit});

    while (!(WindowShouldClose() || buttonReturn))
    {    
        // Update Logic
        GuiSetStyle(0, 16, guiFontLarge);

        // Draw
        BeginDrawing();
        Clear();

        CheckDisplayGrid();
        DrawLinedRectangle(unit, unit, 62* unit, 34* unit, OVERLAYT(230), MUTED);

        DrawText("Practice", 5* unit, unit, titleFontSize, MUTED);
        DrawText("Standard", 14* unit, 9* unit, (int) titleFontSize * 0.6, MUTED);
        DrawText("Extended", 45* unit, 9* unit, (int) titleFontSize * 0.6, MUTED);
        DrawLine(40* unit, 8* unit, 40* unit, 35* unit, MUTED);
        
        if (dropdownLengthEditMode) GuiLock(); // To diable interation with other controls if the drop down menu is selected

        GuiCheckBox((Rectangle) {5* unit, 13* unit, 2* unit, 2* unit}, "Letters", &checkLetters);
        GuiCheckBox((Rectangle) {17* unit, 13* unit, 2* unit, 2* unit}, "Numbers", &checkNumbers);
        GuiCheckBox((Rectangle) {29* unit, 13* unit, 2* unit, 2* unit}, "Symbols", &checkSymbols);
        GuiCheckBox((Rectangle) {5* unit, 17* unit, 2* unit, 2* unit}, "Custom", &checkCustom);

        buttonStdDecode  = GuiButton((Rectangle){8 * unit, 28.5 * unit, 12 * unit, 3 * unit}, "Decode");
        buttonStdEncode  = GuiButton((Rectangle){24 * unit, 28.5 * unit, 12 * unit, 3 * unit}, "Encode");
        buttonExtDecode  = GuiButton((Rectangle){46 * unit, 24.5 * unit, 12 * unit, 3 * unit}, "Decode");
        buttonExtEncode  = GuiButton((Rectangle){46 * unit, 28.5 * unit, 12 * unit, 3 * unit}, "Encode");

        buttonReturn = GuiButton((Rectangle){60 * unit, 2 * unit,  2 * unit, 2 *unit}, "x");

        TextField(textField);


        DrawText("Length:", 44 * unit, 13 * unit, fontSize, MUTED);

        GuiSetStyle(0, 16, guiFontSmall);
        if (GuiDropdownBox((Rectangle) {52 * unit, 13 * unit, 8 * unit, 2* unit}, "Short;Medium;Long", &dropdownLength, dropdownLengthEditMode))
            dropdownLengthEditMode = !dropdownLengthEditMode;
        GuiUnlock();

        CheckDisplayFPS();
        EndDrawing();
    }
    destroyTextFieldState(textField);
}