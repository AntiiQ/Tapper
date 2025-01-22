#ifndef UTILS 
#define UTILS

#include "raylib.h"

// Colors
#define BASE (Color) {25, 23, 36, 255} 
#define SURFACE (Color) {31, 29, 46, 255}
#define BRIGHT (Color) {224, 222, 244, 255}
#define OVERLAY (Color) {38, 35, 58, 255}
#define MUTED (Color) {110, 106, 134, 255}
#define MYGOLD (Color) {246, 193, 119, 255}
#define SUBTLE (Color) {49, 116, 143, 255}
#define ROSE (Color) {235, 188, 186, 255}

#define HLOW (Color) {33, 32, 46, 255}
#define HMED (Color) {64, 61, 82, 255}

#define OVERLAYT(x) (Color) {38, 35, 58, x}

// structs
typedef struct{
    char* text;
    int capacity;
    int length;
    Rectangle textBox;
    bool mouseOnText;
    int framesCounter;

    int fontSize;
    int lineHeight;     // Height of each line of text
    int maxWidth;
    int maxVisibleLines;
}TextFieldState;


// Funnction Prototypes

void Clear();
void CheckDisplayGrid(void);
void CheckDisplayFPS(void);
int CheckToggleFullScreen(void);
void DrawLinedRectangle(int posX, int posY, int width, int height, Color fillColor, Color borderColor);
int GetUnitSize(void);

void TextField(TextFieldState* state);
TextFieldState* createTextFieldState(int capacity, Rectangle Dimensions) ;
void destroyTextFieldState(TextFieldState* state);


void strcat_c(char *str, char c);

#endif