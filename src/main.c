// Libraries?
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// Header Files
// Iteration 1
#include "include/utils.h"
#include "include/menu.h"

// Iteration 2
#include "include/settings.h"
#include "include/blocks.h"

// Iteration 3
// Morse Utils

// Iteration 4
// Morse Utils

// Iteration 5
#include "include/practice.h"

// Temp
#include "include/temp.h"
#include "include/lesson.h"

#include "../resources/custom.h"

// Definitons

typedef enum 
{   LESSON_SCREEN = 1, PRACTICE_SCREEN, ONLINE_SCREEN, STATISTICS_SCREEN, SETTINGS_SCREEN, TESTING_SCREEN} ScreenType;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Config config = GetConfig();

    InitWindow(config.screenWidth, config.screenHeight, "Tapper");
    SetExitKey(KEY_NULL); // Disables escape as a close button
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    InitAudioDevice();

    GuiLoadStyleCustom();

    ScreenType currentScreen = 0;

    Block blocks[NUM_OF_ROWS][MAX_SIZE];
    InitAllBlocks(NUM_OF_ROWS, blocks);

    // Main loop
    while (!WindowShouldClose())    // Detect window close button
    {
        currentScreen = Menu(blocks);

        switch (currentScreen)
        {
            case LESSON_SCREEN:     Lesson();               break;
            case PRACTICE_SCREEN:   Practice(config);       break;
            case ONLINE_SCREEN:     Online();               break;
            case STATISTICS_SCREEN: Statistics();           break;
            case SETTINGS_SCREEN:   Settings(config, blocks);       config = GetConfig();       break;
            case TESTING_SCREEN:    Testing();              break;
            default:                break;
        }
    }
        
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
