#ifndef SETTINGS_H 
#define SETTINGS_H

#include "blocks.h"

// Hold application config information
typedef struct
{
    int screenWidth;
    int screenHeight;

    float volume;
    float pitch;
    int wpm;
    float morseUnit;
}Config;

Config GetConfig(void);
void Settings(Config config, Block blocks[NUM_OF_ROWS][MAX_SIZE]);

#endif