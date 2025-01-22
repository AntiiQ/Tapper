/*The Morse Utilites For Tapper*/

#include "include/morseutils.h"
#include "include/utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define TICK 0.5f

/* MORSE TO CHAR */
/*-------------------------------------------------------------------------*/

// Needed for the Build Tree Function
typedef struct {
    char *morseCode;
    char letter;
} MorseEntry;

// Function to create a new node
MorseNode* CreateMorseNode(char character) 
{
    // malloc -ed as it is dynamically allocated     
    MorseNode* node = malloc(sizeof(MorseNode));
    if (node == NULL) {
        // Handle allocation failure
        fprintf(stderr, "ERROR: Memory allocation failed!\n");
        return NULL;
    }

    node->character = character;
    node->dot = NULL;
    node->dash = NULL;

    return node;
}

// Insert a character into the Morse tree
void InsertMorseNode(MorseNode* root, const char* morse, char character) 
{
    MorseNode* current = root;
    for (int i = 0; morse[i] != '\0'; i++) {
        if (morse[i] == '.') {
            if (!current->dot) current->dot = CreateMorseNode('\0');
            current = current->dot;
        } else if (morse[i] == '-') {
            if (!current->dash) current->dash = CreateMorseNode('\0');
            current = current->dash;
        }
    }
    current->character = character;
}

// Initialise the Morse tree
MorseNode* BuildMorseTree() 
{
    MorseNode *root = CreateMorseNode('\0');

    MorseEntry morseTable[] = {
        // Alpha
        {".-", 'A'},    {"-...", 'B'},  {"-.-.", 'C'},  {"-..", 'D'},
        {".", 'E'},     {"..-.", 'F'},  {"--.", 'G'},   {"....", 'H'},
        {"..", 'I'},    {".---", 'J'},  {"-.-", 'K'},   {".-..", 'L'},
        {"--", 'M'},    {"-.", 'N'},    {"---", 'O'},   {".--.", 'P'},
        {"--.-", 'Q'},  {".-.", 'R'},   {"...", 'S'},   {"-", 'T'},
        {"..-", 'U'},   {"...-", 'V'},  {".--", 'W'},   {"-..-", 'X'},
        {"-.--", 'Y'},  {"--..", 'Z'},

        // Digits
        {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
        {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'},
        {"---..", '8'}, {"----.", '9'}, 

        // Symbols 
        {".-...", '&'},     {".----.", '\''},   {".--.-.", '@'},
        {"-.--.-", ')'},    {"-.--.", '('},     {"---...", ':'},
        {"--..--", ','},    {"-...-", '='},     {"-.-.--", '!'},
        {".-.-.-", '.'},    {"-....-", '-'},    {".-.-.", '+'},     
        {".-..-.", '"'},    {"..--..", '?'},    {"-..-.", '/'}
    };

    int numEntries = sizeof(morseTable) / sizeof(morseTable[0]);

    for (int i = 0; i < numEntries; i++) {
        InsertMorseNode(root, morseTable[i].morseCode, morseTable[i].letter);
    }

    return root;
}

// Decode Morse code using the tree
char DecodeMorseToChar(MorseNode* root, const char* morse) 
{
    if (!morse || morse[0] == '\0') {
        // Explicit handling of empty or null input
        return '\0';
    };

    if (morse[0] == '/'){
        return ' ';
    };

    MorseNode* current = root;
    for (int i = 0; morse[i] != '\0'; i++) {
        if (morse[i] == '.') {
            current = current->dot;
        } else if (morse[i] == '-') {
            current = current->dash;
        }
        if (!current) {
            //puts("Invalid Morse Code");
            return '?'; 
        }// Invalid Morse
    }

    // the check should be necessary as not all nodes could be filled
    return current->character ? current->character : '?'; 
}

// Converts String into Morse
void DecodeMorseToStr(const char* morse, char* result, MorseNode* root, size_t resultSize)
{
    if (morse == NULL || result == NULL || root == NULL) {
        fprintf(stderr, "ERROR: Invalid input to DecodeMorseToStr.\n");
        return;
    }

    char* copy = strdup(morse); // dup the input string
    if (copy == NULL){
        fprintf(stderr, "ERROR: strdup failed!\n");
        return;
    } 

    const char delims[] = " ";
    char* token = strtok(copy, delims);
    int i = 0;
    
    while (token != NULL) {
        char decodedChar = DecodeMorseToChar(root, token); // Decode the token

        if (decodedChar == '\0') {
            // Handle invalid Morse code token
            fprintf(stderr, "WARNING: Invalid Morse code token '%s'.\n", token);
            token = strtok(NULL, delims); // Continue to the next token
            continue;
        }
        
        // Check buffer space
        if (i + 1 >= resultSize) { // +1 for null terminator
            fprintf(stderr, "ERROR: Result buffer overflow.\n");
            break;
        }


        result[i++] = decodedChar; // Append decoded char to result
        token = strtok(NULL, delims); // Get next token
    }

    result[i] = '\0'; // Null-terminate the result string
    free(copy);
}

// Free the entire Morse tree recursivley (post order traversal)
void FreeMorseTree(MorseNode* root) 
{
    if (root == NULL) return;

    // Free left and right subtrees
    FreeMorseTree(root->dot);
    FreeMorseTree(root->dash);

    // Free the current node
    free(root);
}

void DecodeMorse(const char* morse, char* result, size_t resultSize)
{
    MorseNode* root = BuildMorseTree();
    DecodeMorseToStr(morse, result, root, resultSize);
    FreeMorseTree(root);
}
/*-------------------------------------------------------------------------*/

/* CHAR TO MORSE */
/*-------------------------------------------------------------------------*/

// Make sure result can store the encoded text, as it could be quite large
void EncodeTextStr(const char *text, char* result, size_t resultSize) 
{
    if (text == NULL || result == NULL || resultSize == 0) {
        fprintf(stderr, "ERROR: Encoding; Invalid input or insufficient buffer size");
        return;
    }
    
    // Table only contains 7-bit ascii characters, no need to make it large as extended ascii doesnt provide usefullness here
    const char *morseTable[128] = {
        // Control characters (0-31) -skipped
        [' '] = "/",             // Space
        ['A'] = ".-", ['B'] = "-...", ['C'] = "-.-.", ['D'] = "-..", ['E'] = ".", ['F'] = "..-.",
        ['G'] = "--.", ['H'] = "....", ['I'] = "..", ['J'] = ".---", ['K'] = "-.-", ['L'] = ".-..",
        ['M'] = "--", ['N'] = "-.", ['O'] = "---", ['P'] = ".--.", ['Q'] = "--.-", ['R'] = ".-.",
        ['S'] = "...", ['T'] = "-", ['U'] = "..-", ['V'] = "...-", ['W'] = ".--", ['X'] = "-..-",
        ['Y'] = "-.--", ['Z'] = "--..",

        ['0'] = "-----", ['1'] = ".----", ['2'] = "..---", ['3'] = "...--", ['4'] = "....-",
        ['5'] = ".....", ['6'] = "-....", ['7'] = "--...", ['8'] = "---..", ['9'] = "----.",

        ['.'] = ".-.-.-", [','] = "--..--", ['?'] = "..--..", ['\''] = ".----.", ['!'] = "-.-.--",
        ['/'] = "-..-.", ['('] = "-.--.", [')'] = "-.--.-", ['&'] = ".-...", [':'] = "---...",
        ['='] = "-...-", ['+'] = ".-.-.", ['-'] = "-....-",
        ['"'] = ".-..-.", ['@'] = ".--.-."
    };

    size_t pos = 0;  // Position in the result buffer
    result[0] = '\0';  // Start with an empty string in the result buffer


    for (size_t i = 0; text[i] != '\0'; i++){
        unsigned char c = (unsigned char)toupper(text[i]);
        // if the character values is in the original ascii, this will attempt to encode it
        const char *morse = (c < 128) ? morseTable[c] : NULL;

        if (morse){
            size_t morseLen = strlen(morse);
            // Adds a space between morse letters
            if (pos > 0 && pos + 1 < resultSize) 
                result[pos++] = ' ';

            // Appends Morse Code if it fits
            if (pos + morseLen < resultSize) {
                strcpy(result + pos, morse);
                pos += morseLen;
            }else{
                // Prevents overflow
                fprintf(stderr, "ERROR: EncodeTextStr() doesn't have enough space fro result");
                result[pos] = '\0'; // Null-terminate in case of truncation
                break;
            }
        }

        result[pos] = '\0'; // Null-Terminates the string
    }

}
/*-------------------------------------------------------------------------*/

/* SOUND */
/*-------------------------------------------------------------------------*/
#define MAX_SAMPLES_PER_UPDATE      4096
#define MAX_SAMPLES                 512

// Stable frequency (e.g., 440 Hz for A4 note)
float _frequency = 900.0f;

// Audio index for sine wave generation
float _sineIdx = 0.0f;

// Audio input processing callback
void AudioInputCallback(void *buffer, unsigned int frames)
{
    float incr = _frequency / 44100.0f;  // Increment per sample for sine wave
    short *d = (short *)buffer;        // Cast the audio buffer to short (16-bit)

    for (unsigned int i = 0; i < frames; i++)
    {
        d[i] = (short)(32000.0f * sinf(2 * PI * _sineIdx));  // Generate sine wave sample
        _sineIdx += incr;  // Increment the sine wave index
        if (_sineIdx > 1.0f) _sineIdx -= 1.0f;  // Loop the sine wave index
        if (_sineIdx < 0.0f) _sineIdx += 1.0f;  // Prevent underflow (safety)
    }
}

void InitAudio(AudioStream* stream, float volume, float pitch)
{
    //InitAudioDevice();
    SetMasterVolume(volume);
    _frequency = pitch;

    *stream = LoadAudioStream(44100, 16, 1); // Load audio stream (44.1 kHz, 16-bit mono)

    SetAudioStreamCallback(*stream, AudioInputCallback);  // Set the audio callback
    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);
}

// De-initialize Audio Device
void FreeAudio(AudioStream* stream)
{
    StopAudioStream(*stream);
    UnloadAudioStream(*stream);  // Unload audio stream if it's loaded
    //CloseAudioDevice();  // Close the audio device
}
/*-------------------------------------------------------------------------*/

/* HELD INPUT TO MORSE */
/*-------------------------------------------------------------------------*/

void updateMorseInput(MorseState* state, float morseUnit) 
{
    float deltaTime = GetFrameTime();
    bool isKeyPressed = IsKeyDown(KEY_SPACE) + IsKeyDown(KEY_KP_DECIMAL);
    
    // Initialize key press tracking
    if (isKeyPressed && !state->wasKeyPressed) {
        // If we've waited long enough since last release, add word separator
        if (state->releaseTime >= 7 * morseUnit && state->length > 0) {
            if (state->length + 4 >= state->capacity) {  // Need space for " / "
                state->capacity *= 2;
                state->morseString = realloc(state->morseString, state->capacity);
            }
            // Add " / " word separator
            state->morseString[state->length++] = ' ';
            state->morseString[state->length++] = '/';
            state->morseString[state->length++] = ' ';
            state->morseString[state->length] = '\0';
        }
        
        state->keyPressTime = 0.0f;
        PlayAudioStream(*(state->stream));
        state->isPlayingSound = true;
        state->wasKeyPressed = true;
        state->releaseTime = 0.0f;
        state->letterSpaceAdded = false;
    }
    
    // Track key hold duration
    if (isKeyPressed) {
        state->keyPressTime += deltaTime;
    }
    
    // Track key release duration and handle audio
    if (!isKeyPressed) {
        state->releaseTime += deltaTime;
        
        // Check for letter gap and add space if needed
        if (!state->letterSpaceAdded && state->releaseTime >= 3 * morseUnit && state->length > 0) {
            if (state->length + 1 >= state->capacity) {
                state->capacity *= 2;
                state->morseString = realloc(state->morseString, state->capacity);
            }
            state->morseString[state->length++] = ' ';
            state->morseString[state->length] = '\0';
            state->letterSpaceAdded = true;
        }
        
        if (state->isPlayingSound) {
            StopAudioStream(*(state->stream));
            state->isPlayingSound = false;
        }
    }
    
    // Key released - determine if it was a dot or dash
    if (!isKeyPressed && state->wasKeyPressed) {
        // Ensure we have space in the string
        if (state->length + 1 >= state->capacity) {
            state->capacity *= 2;
            state->morseString = realloc(state->morseString, state->capacity);
        }
        
        // Add dot or dash based on duration (3 units for dash)
        if (state->keyPressTime < 3 * morseUnit) {
            state->morseString[state->length++] = '.';
        } else {
            state->morseString[state->length++] = '-';
        }
        state->morseString[state->length] = '\0';
        
        state->wasKeyPressed = false;
        state->keyPressTime = 0.0f;
    }
}

MorseState* createMorseState(AudioStream* stream) 
{
    MorseState* state = malloc(sizeof(MorseState));
    state->capacity = 256;
    state->length = 0;
    state->morseString = malloc(state->capacity);
    state->morseString[0] = '\0';
    state->keyPressTime = 0.0f;
    state->releaseTime = 0.0f;
    state->wasKeyPressed = false;
    state->isPlayingSound = false;
    state->letterSpaceAdded = false;
    state->stream = stream;
    return state;
}

void destroyMorseState(MorseState* state) 
{
    if (state->isPlayingSound) {
        StopAudioStream(*(state->stream));
    }
    free(state->morseString);
    free(state);
}
/*-------------------------------------------------------------------------*/

/* MORSE TO SOUND */
/*-------------------------------------------------------------------------*/

void PlayMorse(AudioStream* stream, char* morse, int len, float morseUnit, MorsePlayState* state)
{
    if (state->location <= len && state->timeWaited >= state->waitForTime){
        
        state->timeWaited = 0;
        if (state->charJustPlayed){
            
            state->waitForTime = morseUnit;
            StopAudioStream(*stream);
            state->charJustPlayed = false;

        }else if (morse[state->location] == '-'){
            
            state->waitForTime = 3 * morseUnit;
            PlayAudioStream(*stream);
            state->charJustPlayed = true;
            state->location += 1;

        }else if (morse[state->location] == '.'){

            state->waitForTime = morseUnit;
            PlayAudioStream(*stream);
            state->charJustPlayed = true;
            state->location += 1;

        }else if (morse[state->location] == ' '){
            
            state->waitForTime = 3 * morseUnit;
            StopAudioStream(*stream);
            state->location += 1;
        }else{
            
            // This accounts for the " / ", as there are 2 spaces surounding it 3(from space)+3+1(from / here) = 7
            state->waitForTime = 3 * morseUnit;
            StopAudioStream(*stream);
            state->location += 1;
        }
    }

    // Stop the audio once the entire Morse code has been played
    if (state->location > len) {
        StopAudioStream(*stream);  // Ensure audio is stopped when Morse code is finished
    }

    state->timeWaited += GetFrameTime();
}
/*-------------------------------------------------------------------------*/
