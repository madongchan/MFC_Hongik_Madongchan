#include "pch.h"
#include "Line.h"

CLine::CLine(void)
{
}

CLine::~CLine(void)
{
}

void CLine::Draw(CDC* pDC)
{
	pDC->MoveTo(m_start);
	pDC->LineTo(m_end);
}