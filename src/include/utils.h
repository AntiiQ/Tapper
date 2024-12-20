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

#define HLOW (Color) {33, 32, 46, 255}

#define OVERLAYT(x) (Color) {38, 35, 58, x}


// Funnction Prototypes

void Clear();
void CheckDisplayGrid(void);
void CheckDisplayFPS(void);
int CheckToggleFullScreen(void);
void DrawLinedRectangle(int posX, int posY, int width, int height, Color fillColor, Color borderColor);
int GetUnitSize(void);

void strcat_c(char *str, char c);

#endif