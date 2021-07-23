#include "pch.h"
#include "Shape.h"

CShape::CShape()
{
	m_pt.SetPoint(0, 0);
	m_color = RGB(0, 0, 0);
	m_bDrawCir = false;
	m_bDrawRect = true;
}

CShape::~CShape()
{

}