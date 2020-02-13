#pragma once

#include "resource.h"
#include <utility>
#define GRIDSIZE 50

typedef std::pair<int, int> IntPair;

enum DIFFICULTY
{
	UNINIT = 1000,
	EASY   = 200,
	MEDIUM = 100,
	HARD   = 50
};

//************************************
// Method:    PlaySnakeJazz
// FullName:  PlaySnakeJazz
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const bool bPlay
//************************************
void PlaySnakeJazz(const bool bPlay);
static int TranslateGameToDisplay(const int iGameSize) { return 8 * iGameSize; }
static IntPair TranslateGameToDisplay(const IntPair Coordinates);