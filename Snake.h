#pragma once
#include <afxwin.h>         // CButton, CString
#include "resource.h"
#include <utility>

constexpr int GRIDSIZE = 50;
typedef std::pair<int, int> IntPair;

enum class EDIFFICULTY
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
// Access:    public constexpr 
// Returns:   int
// Qualifier:
// Parameter: const int iGameSize
//************************************
constexpr int TranslateGameToDisplay(const int iGameSize) { return 8 * iGameSize; }

//************************************
// Translate game coordinates into 
// Display coordinates by translating 
// the individual coordinates
// using the static function
// TranslateGameToDisplay(const int iGameSize)
//
// Method:    TranslateGameToDisplay
// FullName:  TranslateGameToDisplay
// Access:    public constexpr 
// Returns:   IntPair
// Qualifier:
// Parameter: const IntPair Coordinates
//************************************
constexpr IntPair TranslateGameToDisplay(const IntPair Coordinates);