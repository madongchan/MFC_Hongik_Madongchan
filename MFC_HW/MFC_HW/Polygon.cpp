#include "pch.h"
#include "Polygon.h"

CPolygon::CPolygon()
{
	point_num = 0;
}

CPolygon::~CPolygon()
{
}

void CPolygon::Clicked(CPoint pt) {
	PtVertex[point_num] = pt;
	point_num++;
}

void CPolygon::Draw(CDC* pDC) {
	for (int i = 0; i < point_num; i++)
	{
		CPoint vtx = PtVertex[i];
		pDC->Ellipse(vtx.x, vtx.y, vtx.x + 2, vtx.y + 2);
	}
	CRgn rgn;
	rgn.CreatePolygonRgn(PtVertex, point_num, ALTERNATE);
	CBrush brush(RGB(0, 0, 255));
	pDC->FillRgn(&rgn, &brush);
}