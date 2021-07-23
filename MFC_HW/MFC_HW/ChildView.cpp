
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFC_HW.h"
#include "ChildView.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Polygon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	*m_Shape = nullptr;
	m_numShape = 0;
	m_LButtonDown = false;
	m_RButtonDown = false;
	m_MButtonDown = false;
	m_PolyMode = false;
}

CChildView::~CChildView()
{
	for (int i = 0; i < 1000; i++)
	{
		
	}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//	ON_WM_NCLBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);//device context로 부터 호환되는 dc를 얻어온다(그릴장소를 얻는다)

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());//클라이언트 공간 크기의 도화지를 만든다
	memDC.SelectObject(&bitmap);//도화지를 선택한다

	

	

	memDC.Rectangle(-10, -10, rect.Width() + 10, rect.Width() + 10);
	//memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for (int i = 0; i < m_numShape + 1; i++) {
		if (m_Shape != nullptr)
		{
			m_Shape[i]->Draw(&memDC);
		}
	}
			
	if ((m_LButtonDown | m_RButtonDown) &!m_PolyMode)
	{
		m_Shape[m_numShape]->Draw(&memDC);
	}
	
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCapture();

	if (m_PolyMode)
		return;
	
	m_LButtonDown = true;
	
	m_Shape[m_numShape] = new CCircle();
	m_Shape[m_numShape]->m_start = point;

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCapture();
	if (m_PolyMode)
		return;
	
	m_RButtonDown = true;
	
	m_Shape[m_numShape] = new CRectangle();
	m_Shape[m_numShape]->m_start = point;

	CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ReleaseCapture();
	if (m_PolyMode || !m_LButtonDown)
		return;
	
	m_LButtonDown = false;
	
	m_Shape[m_numShape]->m_end = point;
	m_numShape++;
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ReleaseCapture();
	if (m_PolyMode)
		return;
	
	m_RButtonDown = false;
	
	m_Shape[m_numShape]->m_end = point;
	m_numShape++;
	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_LButtonDown || m_RButtonDown)
	{
		m_Shape[m_numShape]->m_end = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}




void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	dc.SelectStockObject(DKGRAY_BRUSH);
	dc.Ellipse(point.x, point.y, point.x + 5, point.y + 5);

	if (!m_PolyMode)
	{
		m_Shape[m_numShape] = new CPolygon();
	}
	m_PolyMode = true;
	m_Shape[m_numShape]->Clicked(point);

	CWnd::OnMButtonDown(nFlags, point);
}


void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_PolyMode = false;
	m_numShape++; //다음폴리곤으로

	Invalidate();
	CWnd::OnLButtonDblClk(nFlags, point);
}
