#pragma once

#include "resource.h"
#include <utility>
#define GRIDSIZE 50

typedef std::pair<int, int> IntPair;

static int TranslateGameToDisplay(const int iGameSize) { return 8 * iGameSize; }
static IntPair TranslateGameToDisplay(const IntPair Coordinates);