#ifndef BLOCKS_H 
#define BLOCKS_H

#define MAX_SIZE 10
#define NUM_OF_ROWS 9

typedef struct Block
{
    bool active;
    Vector2 position;
    int width;          // Varaible width, 1 or 3
}Block;

void UpdateDrawBlocks(int numOfRows, Block blocks[numOfRows][MAX_SIZE]);
void InitAllBlocks(int numOfRows, Block blocks[numOfRows][MAX_SIZE]);

#endif