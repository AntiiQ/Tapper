// Libraries?
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


//Header Files

//------------------------------------------------------------------------------------
//  definitions
//------------------------------------------------------------------------------------
#define TICK 0.5f

//------------------------------------------------------------------------------------
//  Types and Structures Definition
//------------------------------------------------------------------------------------
typedef enum ScreenType 
    { MENU = 0, LESSON, PRACTICE, ONLINE, STATISTICS, SETTINGS, TESTING }ScreenType; // assigns a numerical value to the Screen type thingies

typedef struct MenuButtons {
    bool buttonMenu;
    bool buttonLesson;
    bool buttonPractice;
    bool buttonOnline;
    bool buttonStatistics;
    bool buttonSettings;
    bool buttonTesting;
};

//------------------------------------------------------------------------------------
// Function Declarations
//------------------------------------------------------------------------------------
void Update_Menu(ScreenType *currentScreen, struct MenuButtons MenuButtons)
{
    if (MenuButtons.buttonLesson)       *currentScreen = LESSON;
    if (MenuButtons.buttonPractice)     *currentScreen = PRACTICE;
    if (MenuButtons.buttonOnline)       *currentScreen = ONLINE;
    if (MenuButtons.buttonStatistics)   *currentScreen = STATISTICS;
    if (MenuButtons.buttonSettings)     *currentScreen = SETTINGS;
                
    if (MenuButtons.buttonTesting)      *currentScreen = TESTING;

}


void Draw_Menu(struct MenuButtons* MenuButtons)
{
    DrawText("Tapper", 20, 20, 100, LIGHTGRAY);
    (*MenuButtons).buttonLesson        = GuiButton((Rectangle){ 49, 240, 455, 70 }, "Lessons"); 
    (*MenuButtons).buttonPractice      = GuiButton((Rectangle){ 49, 340, 455, 70 }, "Practice"); 
    (*MenuButtons).buttonOnline        = GuiButton((Rectangle){ 49, 440, 455, 70 }, "Online"); 
    (*MenuButtons).buttonStatistics    = GuiButton((Rectangle){ 49, 540, 455, 70 }, "Statistics"); 
    (*MenuButtons).buttonSettings      = GuiButton((Rectangle){ 49, 640, 455, 70 }, "Settings"); 

    (*MenuButtons).buttonTesting       = GuiButton((Rectangle){ 1000, 640, 100, 70 }, "testing");
}

char TimeToMorse(float *heldTime, float *unheldTime)
{ 
    if (*unheldTime > 3 * TICK){
        *unheldTime = 0.0;
        return ' ';
    }else if (*heldTime > 3 * TICK && *unheldTime > 0){
        *heldTime = 0.0;
        return '-';
    }else if (*heldTime > 0 && *unheldTime > 0){
        *heldTime = 0.0;
        return '.';
    }

    return 0;
}

//Concatenate one char to a string
void strcat_c (char *str, char c)
  {
    for (;*str;str++); // note the terminating semicolon here. 
    *str++ = c; 
    *str++ = 0;
  }
//------------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 1600;
    int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Tapper");
    SetExitKey(KEY_NULL); // Disables escape as a close button

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    ScreenType currentScreen = MENU;
    struct MenuButtons MenuButtons = {false};


    float heldTime = 0.0f;
    float unheldTime = 0.0f;

    char str[1024] = {0};

    // Main loop
    while (!WindowShouldClose())    // Detect window close button
    {
        // Update Logic
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case MENU: 
            {
                Update_Menu(&currentScreen, MenuButtons);
            }break;

            //change when needed
            //------------------
            case LESSON:
            {
                if (MenuButtons.buttonMenu)       currentScreen = MENU;
            } break;
            case PRACTICE:
            {
                if (MenuButtons.buttonMenu)       currentScreen = MENU;

            } break;
            case ONLINE:
            {
                if (MenuButtons.buttonMenu)       currentScreen = MENU;
            } break;
            case STATISTICS:
            {
                if (MenuButtons.buttonMenu)       currentScreen = MENU;
            } break;
            case SETTINGS:
            {
                if (MenuButtons.buttonMenu)       currentScreen = MENU;
            } break;
            //------------------
            case TESTING:
            {
                if (MenuButtons.buttonMenu)       currentScreen = MENU;

                if (IsKeyDown(KEY_SPACE)) {
                    heldTime += GetFrameTime();
                    unheldTime = 0.0;
                }else {
                    unheldTime += GetFrameTime();
                } 

                strcat_c(str, TimeToMorse(&heldTime, &unheldTime));

            } break;
            default:    currentScreen = MENU; break;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 
            switch(currentScreen)
                {
                case MENU:
                    {
                        Draw_Menu(&MenuButtons);
                    } break;
                    case LESSON:
                    {
                        DrawText("Lessons", 20, 20, 100, LIGHTGRAY);
                        MenuButtons.buttonMenu = GuiButton((Rectangle){ 49, 240, 455, 70 }, "Back"); 
                    } break;
                    case PRACTICE:
                    {
                        DrawText("Practice", 20, 20, 100, LIGHTGRAY);
                        MenuButtons.buttonMenu = GuiButton((Rectangle){ 49, 240, 455, 70 }, "Back"); 
                    } break;
                    case ONLINE:
                    {
                        DrawText("Online", 20, 20, 100, LIGHTGRAY);
                        MenuButtons.buttonMenu = GuiButton((Rectangle){ 49, 240, 455, 70 }, "Back"); 
                    } break;
                    case STATISTICS:
                    {
                        DrawText("Statistics", 20, 20, 100, LIGHTGRAY);
                        MenuButtons.buttonMenu = GuiButton((Rectangle){ 49, 240, 455, 70 }, "Back"); 
                    }break;
                    case SETTINGS:
                    {
                        DrawText("Settings", 20, 20, 100, LIGHTGRAY);
                        MenuButtons.buttonMenu = GuiButton((Rectangle){ 49, 240, 455, 70 }, "Back"); 
                    }break;
                    case TESTING:
                    {
                        DrawText("TESTING", 20, 20, 100, LIGHTGRAY);
                        MenuButtons.buttonMenu = GuiButton((Rectangle){ 49, 240, 455, 70 }, "Back"); 

                        DrawText(TextFormat("Time held: %f", heldTime), 1000, 20, 25, LIGHTGRAY);
                        DrawText(TextFormat("Time unheld: %f", unheldTime), 1000, 40, 25, LIGHTGRAY);
                        DrawText(str, 49, 400, 25, BLACK);
                    }break;
                    default: break;
                }

        EndDrawing();
        //--------------------------------------------------------------------------------------
    }
        

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();

    return 0;
}

//------------------------------------------------------------------------------------
// Function Definitions
//------------------------------------------------------------------------------------
