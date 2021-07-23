#include "pch.h"
#include "Rectangle.h"

CRectangle::CRectangle()
{
}
CRectangle::~CRectangle()
{
}

void CRectangle::Draw(CDC* pDC)
{
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&pen);
	pDC->Rectangle(m_pt.x - 50, m_pt.y - 50, m_pt.x + 50, m_pt.y + 50);
}