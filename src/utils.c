/*Utility Funnctions for TAPPER*/

#include "raylib.h"
#include "raygui.h"

#include "include/utils.h"

#include <ctype.h>

#include <stdlib.h>

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

/*Updates and Draws a Text field */
void TextField(TextFieldState* state)
{
    // Update Logic
    if (CheckCollisionPointRec(GetMousePosition(), state->textBox)) state->mouseOnText = true;
    else state->mouseOnText = false;

    if (state->mouseOnText)
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = toupper(GetCharPressed());

        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (state->length < state->capacity))
            {
                // Temporarily add character to check lines
                state->text[state->length] = (char)(key);
                state->text[state->length + 1] = '\0';
                
                // Count lines with temp character
                int lines = 0;
                int lineStart = 0;
                int lastSpace = -1;
                for (int i = 0; i <= state->length + 1; i++) {
                    if (state->text[i] == ' ' || state->text[i] == '\0') {
                        char temp = state->text[i];
                        state->text[i] = '\0';
                        int width = MeasureText(&state->text[lineStart], state->fontSize);
                        state->text[i] = temp;
                        
                        if (width > state->maxWidth) {
                            lines++;
                            if (lastSpace != -1) {
                                lineStart = lastSpace + 1;
                                i = lastSpace;
                            } else {
                                lineStart = i;
                            }
                        }
                        lastSpace = i;
                    }
                }
                
                // Remove temporary character
                state->text[state->length] = '\0';
                
                // Only add if within visible lines
                if (lines < state->maxVisibleLines) {
                    state->text[state->length] = (char)key;
                    state->text[state->length+1] = '\0';
                    state->length++;
                }
            }
            key = toupper(GetCharPressed());
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            state->length--;
            if (state->length < 0) state->length = 0;
            state->text[state->length] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (state->mouseOnText) state->framesCounter++;
    else state->framesCounter = 0;

    // Draw Logic
    DrawRectangleRec(state->textBox, OVERLAY);
    if (state->mouseOnText) DrawRectangleLines((int)state->textBox.x, (int)state->textBox.y, (int)state->textBox.width, (int)state->textBox.height, BRIGHT);
    else DrawRectangleLines((int)state->textBox.x, (int)state->textBox.y, (int)state->textBox.width, (int)state->textBox.height, MUTED);

    int currentX = (int)state->textBox.x + 5;
    int currentY = (int)state->textBox.y + 8;
    int lineStart = 0;
    int lastSpace = -1;
    int currentLine = 0;

    // Draw wrapped text
    for (int i = 0; i <= state->length; i++) {
        if (currentLine >= state->maxVisibleLines) break;

        if (state->text[i] == ' ' || state->text[i] == '\0') {
            char temp = state->text[i];
            state->text[i] = '\0';
            int width = MeasureText(&state->text[lineStart], state->fontSize);
            state->text[i] = temp;
            
            if (width > state->maxWidth) {
                if (lastSpace != -1) {
                    temp = state->text[lastSpace];
                    state->text[lastSpace] = '\0';
                    DrawText(&state->text[lineStart], currentX, currentY, state->fontSize, MUTED);
                    state->text[lastSpace] = temp;
                    
                    currentY += state->lineHeight;
                    currentLine++;
                    lineStart = lastSpace + 1;
                    i = lastSpace;
                } else {
                    temp = state->text[i];
                    state->text[i] = '\0';
                    DrawText(&state->text[lineStart], currentX, currentY, state->fontSize, MUTED);
                    state->text[i] = temp;
                    
                    currentY += state->lineHeight;
                    currentLine++;
                    lineStart = i;
                }
                if (currentLine >= state->maxVisibleLines) break;
            }
            lastSpace = i;
        }
    }

    if (lineStart < state->length && currentLine < state->maxVisibleLines) {
        DrawText(&state->text[lineStart], currentX, currentY, state->fontSize, MUTED);
    }

    if (state->mouseOnText && state->length < state->capacity) {
        if (((state->framesCounter/(GetFPS() / 2))%2) == 0) {
            char temp = state->text[state->length];
            state->text[state->length] = '\0';
            int textWidth = MeasureText(&state->text[lineStart], state->fontSize);
            state->text[state->length] = temp;
            DrawText("_", currentX + textWidth, currentY, state->fontSize, MUTED);
        }
    }
}

/*Creates and populates a TextFiledState struct*/
TextFieldState* createTextFieldState(int capacity, Rectangle Dimensions) 
{
    TextFieldState* state = malloc(sizeof(TextFieldState));
    state->capacity = capacity;
    state->length = 0;
    state->text = malloc(state->capacity);
    state->textBox = Dimensions;
    state->text[0] = '\0';
    state->mouseOnText = false;
    state->framesCounter = 0;

    state->fontSize = 40;
    state->lineHeight = state->fontSize + 5;
    state->maxVisibleLines = ((int)state->textBox.height - 16) / state->lineHeight;
    state->maxWidth = (int)state->textBox.width - 10;

    return state;
}

/*Frees up the TextFieldState struct*/
void destroyTextFieldState(TextFieldState* state) 
{
    free(state->text);
    free(state);
}


void strcat_c(char *str, char c)
{
    for (;*str;str++); // note the semicolon here.
    *str++ = c;
    *str++ = 0;
}

