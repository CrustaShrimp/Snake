#pragma once
#include "Snake.h"
#include <utility>

class CGridElement
{
public:
    // TODO comments
    CGridElement();                          //!< Default constructor
    CGridElement(const int iX, const int iY);//!< Constructor
 
    bool operator == (const CGridElement& GECompare) const noexcept;
 
    IntPair GetXY() const { return std::make_pair(m_iX, m_iY); }
 
    void AddX(const int iAddX) noexcept;
    void AddY(const int iAddY) noexcept;
 
    void SetActive(const bool bActive) noexcept { m_bActive = bActive; }
    bool GetActive() const noexcept { return m_bActive; }
private:
    int     m_iX;       //!< X coordinate of the element
    int     m_iY;       //!< Y coordinate of the element
    bool    m_bActive;  //!< Active flag, true is active, only used for food
};