
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include "Shape.h"

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

	CList <CShape> m_shape;
	CPoint m_st;
	CPoint m_ed;
	CShape shape;

	int numObject;
	int m_dx;
	int m_dy;
	bool m_RButton; //오른쪽 마우스 클릭했는지
	bool m_bMoveRectangle; //지우개 움직이는지 아닌지
// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnColorBlack();
	afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorBlack(CCmdUI* pCmdUI);
	afx_msg void OnSelectRectangle();
	afx_msg void OnSelectCircle();
	afx_msg void OnSelectMove();
	afx_msg void OnUpdateSelectRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectMove(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

