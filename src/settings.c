/*Settings screen and Funtions for TAPPER*/

#include "raylib.h"
#include "raygui.h"

#include "include/settings.h"

#include "include/utils.h"
#include "include/blocks.h"


#include <stdio.h>
#include <math.h>

// To ensure directory exists
#ifdef _WIN32
    #include <direct.h>
    #define MAKE_DIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MAKE_DIR(path) mkdir(path, 0777) 
    // 0777 means anyone can access the directory
    // scince it will not coantain sensitive info this is acceptable
#endif

int WriteConfig(const Config* config);
Config GetConfig(void);

void Settings(Config config, Block blocks[NUM_OF_ROWS][MAX_SIZE])
{
    int unit, titleFontSize, fontSize, guiFontSize;

    int dropdownResolutionActive;

    switch (config.screenHeight)
    {
        case 720:   dropdownResolutionActive = 0; break;
        case 900:   dropdownResolutionActive = 1; break;
        case 1080:  dropdownResolutionActive = 2; break;
                
        default:    dropdownResolutionActive = 0; break;
    }

    bool dropdownResolutionEditMode = false;
    float sliderPitch = config.pitch;
    float sliderWPM = (float) config.wpm;

    bool buttonReturn = false;


    while (!(WindowShouldClose() || buttonReturn))
    {    
        UpdateDrawBlocks(NUM_OF_ROWS, blocks);

        config.pitch = sliderPitch;
        config.wpm = roundf(sliderWPM);
        
        switch (dropdownResolutionActive)
        {
            case 0:     config.screenWidth = 1280; config.screenHeight = 720; break;
            case 1:     config.screenWidth = 1600; config.screenHeight = 900; break; 
            case 2:     config.screenWidth = 1920; config.screenHeight = 1080; break;
                    
            default:    break;
        }
        SetWindowSize(config.screenWidth, config.screenHeight);
        
        unit = GetUnitSize();
        titleFontSize = (int) ((0.144444444) * GetScreenHeight()) - 10;
        fontSize = 50 + (config.screenHeight - 900) / 18;
        guiFontSize = 20 + (config.screenHeight - 900) / 90;

        GuiSetStyle(0, 16, guiFontSize); // switches gui font size
        BeginDrawing();
        Clear();

        //UpdateDrawBlocks(numOfRows, blocks);

        CheckDisplayGrid();

        DrawLinedRectangle(2 * unit, 2 * unit, unit * 24, unit * 32, OVERLAYT(230), MUTED);

        DrawText("Settings", unit * 4, unit * 4, titleFontSize, MUTED);
        buttonReturn = GuiButton((Rectangle){24 * unit, 2 * unit,  2 * unit, 2 *unit}, "x");

        if (dropdownResolutionEditMode) GuiLock(); // To diable interation with other controls if the drop down menu is selected

        DrawText("Volume:", 4 * unit, 17 * unit, fontSize, MUTED);
        GuiSliderBar((Rectangle) {13 * unit, 17.5 * unit,  11 * unit, 1.25 * unit}, NULL, NULL, &(config.volume), 0, 1);

        DrawText("Pitch:", 4 * unit, 21 * unit, fontSize, MUTED);
        GuiSlider((Rectangle) {13 * unit, 21.5 * unit,  11 * unit, 1.25 * unit}, TextFormat("%.0fHz", sliderPitch), NULL, &sliderPitch, 300, 1500);

        DrawText("WPM:", 4 * unit, 25 * unit, fontSize, MUTED);
        GuiSlider((Rectangle) {13 * unit, 25.5 * unit,  11 * unit, 1.25 * unit}, TextFormat("%.0fWPM", sliderWPM), NULL, &sliderWPM, 1, 50);

        DrawText("Resolution:", 4 * unit, 13 * unit, fontSize, MUTED);
        if (GuiDropdownBox((Rectangle) {17 * unit, 13 * unit, 6 * unit, 2* unit}, "1280x720;1600x900;1920x1080", &dropdownResolutionActive, dropdownResolutionEditMode))
            dropdownResolutionEditMode = !dropdownResolutionEditMode;
        GuiUnlock();

        if (CheckToggleFullScreen()) GetUnitSize();
        CheckDisplayFPS();
        EndDrawing();
    }
    config.morseUnit = 1 / ((double)config.wpm * 5 / 6);
    WriteConfig(&config);
}

Config GetConfig(void) {
    Config dflt = (Config) {1600, 900, 0.50f, 440, 10, 0.12}; // Default config
    Config config;

    FILE* file = fopen("userdata/config.bin", "rb");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Failed to load config file. Using default config\n");
        return dflt; // Use default if file cannot be opened
    }

    // Attempt to read the config from the file
    if (fread(&config, sizeof(Config), 1, file) != 1) {
        fprintf(stderr, "ERROR: Failed to read config data. Using default config\n");
        fclose(file); 
        return dflt;  
    }

    fclose(file); 
    return config; 
}

int WriteConfig(const Config* config)
{
    if (config == NULL) {
        fprintf(stderr, "ERROR: Invalid config pointer\n");
        return -1;
    }

    // Ensures directory exists
    MAKE_DIR("userdata");

    FILE* file = fopen("userdata/config.bin", "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        return -1;
    }

    if(fwrite(config, sizeof(*config), 1, file) != 1){
        fprintf(stderr, "ERROR: Failed To write config to file\n");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}