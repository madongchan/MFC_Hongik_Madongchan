
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCFinalExamPracticeQuestions2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);

	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);//화면 하얗게
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CBrush whitebrush = whitecolor;
	CBrush pinkbrush = pinkcolor;

	POSITION ptListShape = m_shape.GetHeadPosition();//도형
	POSITION ptListShape2 = m_shape.GetTailPosition();//도형
	while (ptListShape != NULL)
	{
		CShape mShape = m_shape.GetAt(ptListShape);
		

		if (is_RButtonCliked == true && checkshape == ptListShape)
		{
			memDC.SelectObject(&pinkbrush);
		}
		else
		{
			memDC.SelectObject(&whitebrush);
		}
		
		memDC.Rectangle(mShape.s_Point.x, mShape.s_Point.y, mShape.e_Point.x, mShape.e_Point.y);
		m_shape.GetNext(ptListShape);
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	shape.s_Point = point;
	shape.e_Point = point;
	
	m_shape.AddTail(shape);
	//CShape mShape = m_shape.GetAt(checkshape);
	

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	shape.e_Point = point;
	
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	POSITION ptListShape = m_shape.GetTailPosition();//도형
	s_pos = point;
	is_RButtonCliked = true;
	checkshape = NULL;
	while (ptListShape != NULL)
	{
		CShape mShape = m_shape.GetAt(ptListShape);
		

		if (mShape.s_Point.x < point.x && point.x < mShape.e_Point.x && mShape.s_Point.y < point.y && point.y < mShape.e_Point.y)
		{
			checkshape = ptListShape;
			break;
		}
		m_shape.GetPrev(ptListShape);
	}

	
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	POSITION ptListShape = m_shape.GetHeadPosition();//도형
	while (ptListShape != NULL)
	{
		CShape mShape = m_shape.GetAt(ptListShape);
		m_shape.GetNext(ptListShape);
	}
	is_RButtonCliked = false;
	Invalidate();
	
	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON)
	{
		POSITION cur = m_shape.GetTailPosition();
		CShape mooyaho = m_shape.GetAt(cur);
		mooyaho.e_Point = point;
		m_shape.SetAt(cur, mooyaho);
		Invalidate();
	}
	if (nFlags & MK_RBUTTON)
	{
		if (checkshape != NULL)
		{
			CShape mShape = m_shape.GetAt(checkshape);

			CPoint ss = point - s_pos;
			mShape.s_Point = mShape.s_Point + ss;
			mShape.e_Point = mShape.e_Point + ss;
			m_shape.SetAt(checkshape, mShape);
			s_pos = point;
		}
			

		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
