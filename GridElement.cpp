#include "GridElement.h"

CGridElement::CGridElement()
:CGridElement(0, 0)
{
}

CGridElement::CGridElement(const int iX, const int iY)
: m_iX(iX % GRIDSIZE)
, m_iY(iY % GRIDSIZE)
, m_bActive(false)
{
}

bool CGridElement::operator==(const CGridElement& GECompare) const noexcept
{
    const bool bEqualX = m_iX == GECompare.m_iX;
    const bool bEqualY = m_iY == GECompare.m_iY;
    return bEqualX && bEqualY;
}

void CGridElement::AddX(const int iAddX) noexcept
{
    m_iX = (m_iX + iAddX + GRIDSIZE) % GRIDSIZE; // Add GRIDSIZE for negative clipping
}

void CGridElement::AddY(const int iAddY) noexcept
{
    m_iY = (m_iY + iAddY + GRIDSIZE) % GRIDSIZE; // Add GRIDSIZE for negative clipping
}
