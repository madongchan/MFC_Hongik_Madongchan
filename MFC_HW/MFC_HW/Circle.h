#pragma once
#include "Shape.h"


class CCircle : public CShape
{
public:
	CCircle();
	~CCircle();

	void Draw(CDC *pDC);
};
