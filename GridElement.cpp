#include "GridElement.h"

GridElement::GridElement()
	:m_iX(0)
	,m_iY(0)
	,m_bActive(false)
{

}

GridElement::GridElement(const int iX, const int iY)
	:m_iX(iX % g_iGridSizePlusOne)
	,m_iY(iY % g_iGridSizePlusOne)
	,m_bActive(false)
{

}

GridElement::~GridElement()
{

}

bool GridElement::operator==(const GridElement GECompare) const
{
	const bool bEqualX = m_iX == GECompare.m_iX;
	const bool bEqualY = m_iY == GECompare.m_iY;
	return bEqualX && bEqualY;
}

void GridElement::AddX(const int iAddX)
{
	m_iX = (m_iX + iAddX) % g_iGridSizePlusOne;
}

void GridElement::AddY(const int iAddY)
{
	m_iY = (m_iY + iAddY) % g_iGridSizePlusOne;
}
