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
	,m_bActive(true)
{

}

GridElement::~GridElement()
{

}