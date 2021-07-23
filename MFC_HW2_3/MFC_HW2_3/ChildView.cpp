
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFC_HW2_3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	pt.x = 0;
	pt.y = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
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
	memDC.CreateCompatibleDC(&dc);//device context로 부터 호환되는 dc를 얻어온다(그릴장소를 얻는다)

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());//클라이언트 공간 크기의 도화지를 만든다
	memDC.SelectObject(&bitmap);//도화지를 선택한다

	memDC.Rectangle(-10, -10, rect.Width() + 10, rect.Width() + 10);

	// 서서히 색이 변하는 원 그리기
	//for (int x = pt.x; x < pt.x+255; x++) {
	//	for (int y = pt.y; y < pt.y+255; y++) {
	//		//(x,y)가 원의 내부 좌표일 때만 색을 칠한다
	//		if ((x - (pt.x + 127)) * (x - (pt.x + 127)) + (y - (pt.y + 127)) * (y - (pt.y + 127)) < (127) * (127)) {
	//			memDC.SetPixelV(x, y, RGB(x, 0, y));
	//		}
	//	}
	//}
	for (int x = pt.x; x < pt.x + 255; x++) {
		for (int y = pt.y; y < pt.y + 255; y++) {
			//(x,y)가 원의 내부 좌표일 때만 색을 칠한다
			if ((x - (pt.x+127)) * (x - (pt.x+127)) + (y - (pt.y+127)) * (y - (pt.y+127)) < (127) * (127)) {

				memDC.SetPixelV(x-127, y-127, RGB(x-pt.x, 0, y-pt.y));

			}
		}
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	pt.x = point.x;
	pt.y = point.y;
	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}
