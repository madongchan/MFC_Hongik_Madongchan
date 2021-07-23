
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCHW2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_RButton = false;
	numObject = 0;
	m_dx = 0;
	m_dy = 0;
	m_bMoveRectangle = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_COMMAND(ID_COLOR_BLACK, &CChildView::OnColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CChildView::OnUpdateColorBlack)
	ON_COMMAND(ID_SELECT_RECTANGLE, &CChildView::OnSelectRectangle)
	ON_COMMAND(ID_SELECT_CIRCLE, &CChildView::OnSelectCircle)
	ON_COMMAND(ID_SELECT_MOVE, &CChildView::OnSelectMove)
	ON_UPDATE_COMMAND_UI(ID_SELECT_RECTANGLE, &CChildView::OnUpdateSelectRectangle)
	ON_UPDATE_COMMAND_UI(ID_SELECT_CIRCLE, &CChildView::OnUpdateSelectCircle)
	ON_UPDATE_COMMAND_UI(ID_SELECT_MOVE, &CChildView::OnUpdateSelectMove)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
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
	
	memDC.PatBlt(0, 0, rect.Width(), rect.Height() , WHITENESS);

	

	POSITION ptList = m_shape.GetHeadPosition();
	//그림 그리기 네모나 원을 연속으로 선처럼 보이게?
	while (ptList != NULL)
	{
		POSITION cur = ptList;
		CShape mShape = m_shape.GetAt(ptList);
		m_shape.GetNext(ptList);
		//오른쪽 아래 방향일때 지우기
		if (m_st.x < mShape.m_pt.x && mShape.m_pt.x < m_ed.x && m_st.y < mShape.m_pt.y && mShape.m_pt.y < m_ed.y)
		{
			m_shape.RemoveAt(cur);
			numObject--;
		}
		//오른쪽 위 방향일때 지우기
		else if (m_st.x < mShape.m_pt.x && mShape.m_pt.x < m_ed.x && m_st.y > mShape.m_pt.y && mShape.m_pt.y > m_ed.y)
		{
			m_shape.RemoveAt(cur);
			numObject--;
		}
		//왼쪽 아래 방향일때 지우기
		else if (m_st.x > mShape.m_pt.x && mShape.m_pt.x > m_ed.x && m_st.y < mShape.m_pt.y && mShape.m_pt.y < m_ed.y)
		{
			m_shape.RemoveAt(cur);
			numObject--;
		}
		//왼쪽 위 방향일때 지우기
		else if (m_st.x > mShape.m_pt.x && mShape.m_pt.x > m_ed.x && m_st.y > mShape.m_pt.y && mShape.m_pt.y > m_ed.y)
		{
			m_shape.RemoveAt(cur);
			numObject--;
		}
		CBrush brush(mShape.m_color);
		memDC.SelectObject(&brush);
		memDC.SelectStockObject(NULL_PEN);
		if (mShape.m_bDrawRect)
		{
			memDC.Rectangle(mShape.m_pt.x, mShape.m_pt.y, mShape.m_pt.x + 10, mShape.m_pt.y + 10);
		}
		if (mShape.m_bDrawCir)
		{
			memDC.Ellipse(mShape.m_pt.x, mShape.m_pt.y, mShape.m_pt.x + 10, mShape.m_pt.y + 10);
		}
		

	}
	//지우개
	CPen pen(PS_SOLID, 2, RGB(139, 0, 255));
	memDC.SelectObject(&pen);
	memDC.SelectStockObject(DC_BRUSH);
	if (m_RButton)
	{
		memDC.Rectangle(m_st.x, m_st.y, m_ed.x, m_ed.y);
	}

	//객체들 숫자
	CString str;
	str.Format(_T("%d"), numObject);
	memDC.TextOutW(10, 10, _T("Number of Objects: ") + str);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	shape.m_pt = point;
	m_shape.AddTail(shape);
	numObject++;
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON)
	{
		shape.m_pt = point;
		m_shape.AddTail(shape);
		numObject++;
		Invalidate();
	}
	else if (nFlags & MK_RBUTTON)
	{
		m_ed = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_st = point;
	m_ed = point;
	m_RButton = true;
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ed = point;
	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 33, NULL);
	return 0;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_RIGHT:
		m_dx = 10;
		m_dy = 0;
		break;
	case VK_LEFT:
		m_dx = -10;
		m_dy = 0;
		break;
	case VK_UP:
		m_dx = 0;
		m_dy = -10;
		break;
	case VK_DOWN:
		m_dx = 0;
		m_dy = 10;
		break;
	default:
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	// 아래쪽으로 지우개를 그렸을때만 튕기는 것 , 해결
	if (nIDEvent == 0)
	{
		CRect rect;
		GetClientRect(&rect);
		if (m_ed.y > rect.bottom || m_st.y > rect.bottom)
		{
			m_dy = -10;
		}
		else if (m_st.y < rect.top || m_ed.y < rect.top)
		{
			m_dy = 10;
		}
		else if (m_ed.x > rect.right || m_st.x > rect.right)
		{
			m_dx = -10;
		}
		else if (m_st.x < rect.left || m_ed.x < rect.left)
		{
			m_dx = 10;
		}

		if (m_bMoveRectangle == true)
		{
			m_st.x += m_dx;
			m_ed.x += m_dx;

			m_st.y += m_dy;
			m_ed.y += m_dy;
		}
		else //움직이기는 버튼이 안눌러졌다면 멈추게하고 속도를 0으로 초기화
		{
			m_dx = 0;
			m_dy = 0;
		}
		Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}

void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	shape.m_color = RGB(255, 0, 0);
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	shape.m_color = RGB(0, 255, 0);
	Invalidate();
}


void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	shape.m_color = RGB(0, 0, 255);
	Invalidate();
}


void CChildView::OnColorBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	shape.m_color = RGB(0, 0, 0);
	Invalidate();
}


void CChildView::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (shape.m_color == RGB(255, 0, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (shape.m_color == RGB(0, 255, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (shape.m_color == RGB(0, 0, 255))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateColorBlack(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (shape.m_color == RGB(0, 0, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnSelectRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	shape.m_bDrawCir = false;
	shape.m_bDrawRect = true;
	Invalidate();
}


void CChildView::OnSelectCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	shape.m_bDrawCir = true;
	shape.m_bDrawRect = false;
	Invalidate();
}


void CChildView::OnSelectMove()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_bMoveRectangle == false)
	{
		m_bMoveRectangle = true;
	}
	else
	{
		m_bMoveRectangle = false;
	}

	Invalidate();
}


void CChildView::OnUpdateSelectRectangle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (shape.m_bDrawRect)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateSelectCircle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (shape.m_bDrawCir)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateSelectMove(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_bMoveRectangle)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}
