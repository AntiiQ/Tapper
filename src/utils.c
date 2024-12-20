/*Utility Funnctions for TAPPER*/

#include "raylib.h"
#include "raygui.h"

#include "include/utils.h"

/*Clears Screen, sets it BASE color*/
void Clear()
{
    //ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 
    ClearBackground(BASE);
}

/*Displays Grid if M is pressed*/
void CheckDisplayGrid(void)
{
    if (IsKeyDown(KEY_M))
    {
        int screenWidth = GetScreenWidth(), screenHeight = GetScreenHeight();

        // Vertical Lines
        for (int x = screenWidth / 16; x < screenWidth; x += screenWidth / 16)    
            DrawLine(x, 0, x, screenHeight, BRIGHT);
        // Horizontal Lines
        for (int y = screenHeight / 9; y < screenHeight; y += screenHeight / 9)    
            DrawLine(0, y, screenWidth, y,  BRIGHT);
    }
}

/*Displays FPS if F10 is pressed*/
void CheckDisplayFPS(void)
{
    if (IsKeyDown(KEY_F10))
    {
        DrawText(TextFormat("%d", GetFPS()), 10, 0, 100, BRIGHT);
    }
}

int CheckToggleFullScreen(void)
{
    if (IsKeyPressed(KEY_F11))
    {
        ToggleBorderlessWindowed();
        return 1;
    }
    return 0;
}

/*Draw an Rectangle with outlines*/
void DrawLinedRectangle(int posX, int posY, int width, int height, Color fillColor, Color borderColor)
{
        DrawRectangle(posX, posY, width, height, fillColor);
        DrawRectangleLines(posX, posY, width, height, borderColor);
}

/*Get a standardized pixel unit based on*/
int GetUnitSize(void)
{
    return GetScreenHeight() / 36;
}


void strcat_c(char *str, char c)
{
    for (;*str;str++); // note the semicolon here.
    *str++ = c;
    *str++ = 0;
}

