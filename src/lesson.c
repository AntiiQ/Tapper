/*The Lesson Functions*/

#include "raylib.h"
#include "raygui.h"

#include "include/utils.h"

void Lesson(void)
{
    int unit = GetUnitSize();
    int titleFontSize = (int) ((0.144444444) * GetScreenHeight()) + 6;

    bool buttonReturn;


    while (!(WindowShouldClose() || buttonReturn))
    {    


        BeginDrawing();
        CheckDisplayGrid();
        Clear();
        DrawLinedRectangle(unit, unit, 62 * unit, 34 * unit, OVERLAYT(230), MUTED);

        DrawText("Lesson", 4* unit, unit, titleFontSize, MUTED);

        buttonReturn = GuiButton((Rectangle){60 * unit, 2 * unit,  2 * unit, 2 *unit}, "x");

        EndDrawing();
    }
}