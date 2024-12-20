/* Block Related Functions for TAPPER*/

#include "raylib.h"

#include "include/blocks.h"

#include "include/utils.h"

#include <stdio.h>
#include <time.h> // For Random Number Generator


bool InitBlock(Block blocks[MAX_SIZE], int row);
void InitAllBlocks(int numOfRows, Block blocks[numOfRows][MAX_SIZE]);

// Updates and Draws Blocks
void UpdateDrawBlocks(int numOfRows, Block blocks[numOfRows][MAX_SIZE])
{
    int unit = GetUnitSize();
    bool shouldInit;

    // Update active blocks
    int killDistance = GetScreenWidth();

    for (int i = 0; i < numOfRows; i++) {
        shouldInit = true;
        for (int j = 0; j < MAX_SIZE; j++){

            // Increment and Draws active block position
            if (blocks[i][j].active){
                blocks[i][j].position.x += 100 * GetFrameTime() +.1 * i;

                // If any blocks are before 0, no need to initialise another
                if (blocks[i][j].position.x <= 0)
                    shouldInit = false;

            // Kill Blocks if needed
            if ( blocks[i][j].position.x > killDistance)
                blocks[i][j].active = false;


            // Draw Remaining Boxes
            //DrawRectangle(blocks[i][j].position.x, blocks[i][j].position.y, blocks[i][j].width, 3 * unit, MYGOLD);
            DrawRectangleV(blocks[i][j].position, (Vector2) {blocks[i][j].width, 3 * unit}, MYGOLD);
            }
        }
        // Initilise Blocks if needed
        if (shouldInit)
            if (InitBlock(blocks[i], i)) 
                printf("\n!!!Init Block Failure!\n");
    }

}

/*Initilises a Block, 0 - indexed/Max of 9*/
bool InitBlock(Block blocks[MAX_SIZE], int row)
{
    int unit = GetUnitSize();
    bool found = false;
    int i;

    for (i = 0; i < MAX_SIZE; i++)
        if (blocks[i].active == false){
            found = true;
            break;
        }

    if (!found) return -1;

    // Assings a width to the block
    blocks[i].width = GetRandomValue(0,1) * 8 * unit + 4 * unit; // Either 1 or 3  * 4 units

    // Assigns gap between it and next block
    blocks[i].position.x = 0 - blocks[i].width - (GetRandomValue(0,1) * 8 * unit + 4 * unit);

    blocks[i].active = true;

    return 0;
}

/*Initialises the blocks array so that each row has an active block*/
void InitAllBlocks(int numOfRows, Block blocks[numOfRows][MAX_SIZE])
{
    // Initialise the varibles, to reduce risk
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            blocks[i][j] = (Block){0};
        }
    }

    SetRandomSeed(time(NULL));
    int unit = GetUnitSize();

    // init first blocks
    for (int i = 0; i < numOfRows; i++){
        InitBlock(blocks[i], i);
    }   
    for (int i = 0; i < numOfRows; i++) 
        for (int j = 0; j < MAX_SIZE; j++)
            blocks[i][j].position.y = i * 4 * unit + 0.5 * unit;

}