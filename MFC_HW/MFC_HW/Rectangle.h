#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle();
	~CRectangle();

	void Draw(CDC* pDC);

};