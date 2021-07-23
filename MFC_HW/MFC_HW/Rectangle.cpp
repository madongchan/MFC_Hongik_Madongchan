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
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);

	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&bitmap);

	int a = m_end.x - m_start.x;
	int b = m_end.y - m_start.x;
	
	CPen pen(PS_SOLID, 5, RGB(100, 100, 100));
	pDC->SelectObject(&pen);
	pDC->Rectangle(m_start.x, m_start.y, m_end.x, m_end.y);//(*memDC).Rectangle(m_start.x, m_start.y, m_end.x, m_end.y);
	pDC->StretchBlt(m_start.x, m_start.y, a, b, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

}