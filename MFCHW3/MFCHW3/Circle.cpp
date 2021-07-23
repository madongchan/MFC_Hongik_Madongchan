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
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&pen);
	pDC->Ellipse(m_pt.x - 50, m_pt.y - 50, m_pt.x + 50, m_pt.y + 50);
}