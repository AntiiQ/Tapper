#ifndef MORSEUTILS_H 
#define MORSEUTILS_H

#include "raylib.h"

#include <stddef.h>
#include <stdbool.h>

// Morse to char binary tree struct
typedef struct MorseNode {
    char character;
    struct MorseNode *dot; // analogue to left pointer
    struct MorseNode *dash; // analogue to right pointer
} MorseNode;

// Status for PlayMorse function so that it's non-blocking
typedef struct {
    int   location;
    float waitForTime;
    float timeWaited;
    bool  charJustPlayed;
}MorsePlayState;

typedef struct {
    char* morseString;
    int capacity;
    int length;
    float keyPressTime;
    float releaseTime;
    bool wasKeyPressed;
    AudioStream* stream;
    bool isPlayingSound;
    bool letterSpaceAdded;
} MorseState;

/* MORSE TO CHAR */
MorseNode* BuildMorseTree();
void FreeMorseTree(MorseNode* root);

char DecodeMorseToChar(MorseNode* root, const char* morse);
void DecodeMorseToStr(const char* morse, char* result, MorseNode* root, size_t resultSize);
void DecodeMorse(const char* morse, char* result, size_t resultSize);

/* CHAR TO MORSE */
void EncodeTextStr(const char *text, char* result, size_t resultSize);

/* SOUND */
void InitAudio(AudioStream* stream, float volume, float pitch);
void FreeAudio(AudioStream* stream);

/* HELD INPUT TO MORSE */
void updateMorseInput(MorseState* state, float morseUnit);
MorseState* createMorseState(AudioStream* stream);
void destroyMorseState(MorseState* state);

/* MORSE TO SOUND */
void PlayMorse(AudioStream *stream, char* morse, int len, float morseUnit, MorsePlayState* state);

#endif