#pragma once

#include "resource.h"
#include <utility>
#define GRIDSIZE 50

typedef std::pair<int, int> IntPair;

enum class DIFFICULTY
{
    UNINIT = 200,
    EASY   = 150,
    MEDIUM = 100,
    HARD   = 50
};

//************************************
// Plays SNAKE.wav (snakejazz)
// only when the parameter bPlay is true
// If the parameter is false, stops the music
// The sound mode must be enabled, otherwise
// the music stops too
//
// Method:    PlaySnakeJazz
// FullName:  PlaySnakeJazz
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const bool bPlay
//************************************
void PlaySnakeJazz(const bool bPlay);


//************************************
// Translates a gamesize (int) into
// screensize by multiplying by factor (8)
//
// Method:    TranslateGameToDisplay
// FullName:  TranslateGameToDisplay
// Access:    public static 
// Returns:   int
// Qualifier:
// Parameter: const int iGameSize
//************************************
static int TranslateGameToDisplay(const int iGameSize) { return 8 * iGameSize; }

//************************************
// Translate game coordinates into 
// Display coordinates by translating 
// the individual coordinates
// using the static function
// TranslateGameToDisplay(const int iGameSize)
//
// Method:    TranslateGameToDisplay
// FullName:  TranslateGameToDisplay
// Access:    public static 
// Returns:   IntPair
// Qualifier:
// Parameter: const IntPair Coordinates
//************************************
static IntPair TranslateGameToDisplay(const IntPair Coordinates);