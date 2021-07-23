#pragma once

class CShape
{
public:
	CPoint m_start;
	CPoint m_end;

	CShape();
	~CShape();

	virtual void Clicked(CPoint pt);
	virtual void Draw(CDC *pDC);
};
