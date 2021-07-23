#include "pch.h"
#include "Circle.h"

CCircle::CCircle()
{
} 

CCircle::~CCircle()
{
}

void CCircle::Draw(CDC* pDC)
{
	CBrush brush(RGB(255, 255, 0));
	pDC->SelectObject(&brush);

	CPen Pen(PS_SOLID, 5, RGB(100, 100, 100));
	
	pDC->SelectObject(&Pen);
	pDC->Ellipse(m_start.x, m_start.y, m_end.x, m_end.y);
}