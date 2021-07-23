#pragma once
#include "pch.h"
class CShape
{
public:
	CPoint m_pt;
	COLORREF m_color;
	bool m_bDrawCir;
	bool m_bDrawRect;

	CShape();
	~CShape();

};
