
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCFinalExamPracticeQuestions4.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	RectangleCliked = true;
	m_pt.x = 100;
	m_pt.y = 100;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_BN_CLICKED(101, OnButtonClickedRectangle)
	ON_BN_CLICKED(102, OnButtonClickedEllipse)
	ON_WM_CREATE()
	ON_WM_SIZE()
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
	CRect rect;
	GetClientRect(&rect);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);

	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);//화면 하얗게
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CBrush pinkbrush = RGB(255, 192, 203);
	memDC.SelectObject(&pinkbrush);

	m_pt = (rect.bottom, rect.right);
	if (RectangleCliked == true)
	{
		memDC.Rectangle(70, 50, rect.right - m_pt.x / 20, rect.bottom - m_pt.y / 20 - 30);
		//memDC.Rectangle(rect.left - m_pt.x, rect.top - m_pt.y, rect.right - m_pt.x, rect.bottom - m_pt.y);
		//memDC.Rectangle(rect.left, rect.top, rect.right, rect.bottom);
	}
	else
	{
		memDC.Ellipse(50, 50, rect.right - m_pt.x / 20, rect.bottom - rect.bottom / 20);
	}
	CString str;
	str.Format(_T("%d"), m_pt.y + rect.bottom);
	memDC.TextOutW(300, 0, _T("m_pt.y: ") + str);
	CString str1;
	str1.Format(_T("%d"), rect.bottom);
	memDC.TextOutW(400, 0, _T("rect.right: ") + str1);


	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

void CChildView::OnButtonClickedRectangle()
{
	RectangleCliked = true;
	Invalidate();
}
void CChildView::OnButtonClickedEllipse()
{
	RectangleCliked = false;
	Invalidate();
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_rectanglebutton.Create(_T("Rectangle"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(0, 0, 100, 30), this, 101);//four-integers are left, top, right, and bottom
	m_ellipsebutton.Create(_T("Ellipse"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(100, 0, 200, 30), this, 102);
	m_rectanglebutton.SetCheck(1);
	return 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	/*CRect rect;
	GetClientRect(&rect);
	rect.left = cx / 2 - 25;
	rect.right = cx / 2 + 25;
	rect.top = cy / 2 - 25;
	rect.bottom = cy / 2 + 25;*/
	m_pt = (cx, cy);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
