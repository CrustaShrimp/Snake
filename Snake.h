#pragma once

#include "resource.h"
class WindowProperties
{
public:
	WindowProperties();
	~WindowProperties();

	void SetWidth (const int iWidth ) { m_iWidth  = iWidth ; }
	void SetHeight(const int iHeight) { m_iHeight = iHeight; }

	int GetWidth () const { return m_iWidth; }
	int GetHeight() const { return m_iHeight; }
protected:
private:
	int m_iWidth;
	int m_iHeight;
};