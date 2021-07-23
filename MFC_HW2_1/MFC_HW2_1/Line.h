#pragma once


class CLine
{
public:
	CLine(void);
	~CLine(void);

	CPoint m_start;
	CPoint m_end;

	void Draw(CDC* pDC);
};
