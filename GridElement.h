#pragma once

#include "MainGame.h"

extern const int g_iGridSizePlusOne;

class GridElement
{
public:

	// TODO comments
	GridElement();													// Default constructor
	GridElement(const int iX, const int iY);						// Constructor	
	GridElement(const int iX, const int iY, const int iNumber)		// Constructor
	~GridElement();													// Destructor
private:
	int		m_iX;			// X coordinate of the element
	int		m_iY;			// Y coordinate of the element
	int		m_iNumber;		// Element number in the snake, only used for snake
	bool 	m_bActive;		// Active flag, true is active, only used for food
};
