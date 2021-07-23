#include "pch.h"
#include "Shape.h"

CShape::CShape()
{
	m_LButtonDown = false;
	m_RButtonDown = false;
	num = 0;
	rect = 0;
}
CShape::~CShape()
{
}