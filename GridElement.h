#pragma once
#include "Snake.h"
#include <utility>

class GridElement
{
public:
	// TODO comments
	GridElement();													// Default constructor
	GridElement(const int iX, const int iY);						// Constructor	
	~GridElement();													// Destructor

	bool operator == (const GridElement) const;

	IntPair GetXY() const { return std::make_pair(m_iX, m_iY); }
	
	void AddX(const int iAddX);
	void AddY(const int iAddY);

	void SetActive(const bool bActive)	{ m_bActive = bActive; }
	bool GetActive() const { return m_bActive; }
private:
	int		m_iX;			// X coordinate of the element
	int		m_iY;			// Y coordinate of the element
	bool 	m_bActive;		// Active flag, true is active, only used for food
};