#pragma once
#include "Shape.h"

class CPolygon : public CShape
{
public:
	int point_num;
	CPoint PtVertex[20];
	CPolygon();
	~CPolygon();

	void Clicked(CPoint pt);
	void Draw(CDC* pDC);
};

