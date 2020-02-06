#include "GridElement.h"

GridElement::GridElement()
	:m_iX(0)
	,m_iY(0)
	,m_iNumber(0)
	,m_bActive(false)
{

}

GridElement::GridElement(const int iX, const int iY)
	:m_iX(iX % g_iGridSizePlusOne)
	,m_iY(iY % g_iGridSizePlusOne)
	,m_iNumber(0)
	,m_bActive(true)
{

}

GridElement::GridElement(const int iX, const int iY, const int iNumber)
	:m_iX(iX% g_iGridSizePlusOne)
	,m_iY(iY% g_iGridSizePlusOne)
	,m_iNumber(iNumber)
	,m_bActive(true)
{

}

GridElement::~GridElement()
{

}