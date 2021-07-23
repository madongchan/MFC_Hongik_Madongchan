
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
	CList<CShape>m_shape;
	CShape shape;

	CList<CPoint>m_point;

	CShape s_Point;
	CShape e_Point;

	COLORREF blackcolor = RGB(0, 0, 0);
	COLORREF redcolor = RGB(255, 0, 0);

	
	//선형보간법
	int startRoundRect;
	int endRoundRect;
	float Alpha;
	//애니메이션
	float h_move;
	float v_move;
	int x;
	int y;
	bool play;
	int scrollplayNum;
	//스크롤바
	int numShape;
	int rectNum;
	int selectNum;
	

	CButton m_button_clear;
	CButton m_button_save;
	CButton m_button_load;
	CButton m_button_replay;
	CButton m_button_stop;
	CButton m_button_delete;

	CScrollBar m_HBar;
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonClickedClear();//필수
	afx_msg void OnButtonClickedSave();//필수
	afx_msg void OnButtonClickedLoad();//필수
	afx_msg void OnButtonClickedReplay();//필수
	afx_msg void OnButtonClickedStop();//필수
	afx_msg void OnButtonClickedDelete();//필수
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

