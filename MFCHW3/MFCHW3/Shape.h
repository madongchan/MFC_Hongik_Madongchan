#pragma once
#include "pch.h"
class CShape
{
public:
	CPoint m_pt;
	bool m_LButtonDown;
	bool m_RButtonDown;
	int rect;
	int num;

	CShape();
	~CShape();
};