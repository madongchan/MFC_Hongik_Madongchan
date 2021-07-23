
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCHW3.h"
#include "ChildView.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm");

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	x = 0;
	y = 0;
	numShape = 0;
	play = false;
	rectNum = 0;
	selectNum = 0;
	scrollplayNum = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(101, OnButtonClickedClear)
	ON_BN_CLICKED(102, OnButtonClickedSave)
	ON_BN_CLICKED(103, OnButtonClickedLoad)
	ON_BN_CLICKED(104, OnButtonClickedReplay)
	ON_BN_CLICKED(105, OnButtonClickedStop)
	ON_BN_CLICKED(106, OnButtonClickedDelete)
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
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

	CPen black_pen(PS_SOLID, 1, blackcolor);
	CPen red_pen(PS_SOLID, 1, redcolor);

	CPen dash_pen(PS_DASH, 1, blackcolor);
	CPen solid_pen(PS_SOLID, 1, blackcolor);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	POSITION ptListShape = m_shape.GetHeadPosition();//도형
	POSITION ptListLine = m_shape.GetHeadPosition();//선
	POSITION ptListAnmation = m_shape.GetHeadPosition();//애니메이션

	while (ptListLine != NULL)
	{
		CPoint sPoint = m_point.GetAt(ptListLine);
		m_point.GetNext(ptListLine);
		if (ptListLine == NULL) break;
		CPoint ePoint = m_point.GetAt(ptListLine);


		if (play == true)
		{
			memDC.SelectObject(&dash_pen);
		}
		else
		{
			memDC.SelectObject(&solid_pen);
		}

		memDC.MoveTo(sPoint);
		memDC.LineTo(ePoint);
	}
	while (ptListShape != NULL)
	{

		CShape mShape = m_shape.GetAt(ptListShape);
		m_shape.GetNext(ptListShape);


		if (mShape.num == selectNum)
			memDC.SelectObject(&red_pen);
		else
			memDC.SelectObject(&black_pen);

		if (play == false)
		{
			if (mShape.m_LButtonDown)
			{
				memDC.Rectangle(mShape.m_pt.x - 40, mShape.m_pt.y - 40, mShape.m_pt.x + 40, mShape.m_pt.y + 40);
			}
			else if (mShape.m_RButtonDown)
			{
				memDC.Ellipse(mShape.m_pt.x - 40, mShape.m_pt.y - 40, mShape.m_pt.x + 40, mShape.m_pt.y + 40);
			}
		}
	}
	//애니메이션
	if (play == true)
	{
		if (x < numShape)
		{
			for (int i = 0; i < x; i++)
			{
				s_Point = m_shape.GetAt(ptListAnmation);
				m_point.GetNext(ptListAnmation);
				e_Point = m_shape.GetAt(ptListAnmation);
			}

			h_move = (e_Point.m_pt.x - s_Point.m_pt.x) / 20.0f;
			v_move = (e_Point.m_pt.y - s_Point.m_pt.y) / 20.0f;
			memDC.SelectObject(&solid_pen);
			//사각형에서 원으로 갈 때
			if (s_Point.rect == 0 && e_Point.rect == 100)
			{
				startRoundRect = 0;
				endRoundRect = 100;
				Alpha = (float)y / 20.0f;//0~1
				memDC.RoundRect(s_Point.m_pt.x - 40 + h_move * y, s_Point.m_pt.y - 40 + v_move * y, s_Point.m_pt.x + 40 + h_move * y, s_Point.m_pt.y + 40 + v_move * y, //선 따라 이동
					startRoundRect * (1 - Alpha) + endRoundRect * Alpha, startRoundRect * (1 - Alpha) + endRoundRect * Alpha);//선형보간법
			}
			//원에서 사각형으로 갈 때
			if (s_Point.rect == 100 && e_Point.rect == 0)
			{
				startRoundRect = 100;
				endRoundRect = 0;
				Alpha = (float)y / 20.0f;
				memDC.RoundRect(s_Point.m_pt.x - 40 + h_move * y, s_Point.m_pt.y - 40 + v_move * y, s_Point.m_pt.x + 40 + h_move * y, s_Point.m_pt.y + 40 + v_move * y,
					startRoundRect * (1 - Alpha) + endRoundRect * Alpha, startRoundRect * (1 - Alpha) + endRoundRect * Alpha);
			}
			//사각형에서 사각형으로 갈 때
			if (s_Point.rect == 0 && e_Point.rect == 0)
			{
				memDC.RoundRect(s_Point.m_pt.x - 40 + h_move * y, s_Point.m_pt.y - 40 + v_move * y, s_Point.m_pt.x + 40 + h_move * y, s_Point.m_pt.y + 40 + v_move * y,
					0, 0);
			}
			//원에서 원으로 갈 때
			if (s_Point.rect == 100 && e_Point.rect == 100)
			{
				startRoundRect = 100;
				endRoundRect = 0;
				Alpha = (float)y / 20.0f;
				memDC.RoundRect(s_Point.m_pt.x - 40 + h_move * y, s_Point.m_pt.y - 40 + v_move * y, s_Point.m_pt.x + 40 + h_move * y, s_Point.m_pt.y + 40 + v_move * y,
					100, 100);
			}
			if (y > 20)
			{
				x++;
				y = 1;
				scrollplayNum++;
			}
			m_HBar.SetScrollPos(scrollplayNum);
		}
		if (x >= numShape)
		{
			x = 1;
			scrollplayNum = 0;
		}

	}

	m_HBar.SetScrollRange(0, rectNum - 1);

	m_HBar.ShowWindow(true);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	
	SetTimer(0, 33, NULL);

	m_button_clear.Create(_T("CLEAR"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 100, 30), this, 101);//four-integers are left, top, right, and bottom
	m_button_save.Create(_T("SAVE"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 0, 200, 30), this, 102);
	m_button_load.Create(_T("LOAD"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(200, 0, 300, 30), this, 103);
	m_button_replay.Create(_T("REPLAY"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(300, 0, 400, 30), this, 104);
	m_button_stop.Create(_T("STOP"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(400, 0, 500, 30), this, 105);
	m_button_delete.Create(_T("Delete"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(500, 0, 600, 30), this, 106);

	m_HBar.Create(SBS_HORZ, CRect(600, 0, 900, 30), this, 107);
	m_HBar.SetScrollRange(0, 0);
	m_HBar.ShowWindow(true);
	return 0;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	shape.m_LButtonDown = true;
	shape.m_pt = point;
	shape.rect = 0;
	shape.num = rectNum;
	m_shape.AddTail(shape);
	m_point.AddHead(shape.m_pt);
	numShape++;
	rectNum++;
	shape.m_LButtonDown = false;
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	shape.m_RButtonDown = true;
	shape.m_pt = point;
	shape.rect = 100;
	shape.num = rectNum;
	m_shape.AddTail(shape);
	m_point.AddHead(shape.m_pt);
	numShape++;
	rectNum++;
	shape.m_RButtonDown = false;
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnButtonClickedClear()
{
	m_shape.RemoveAll();
	m_point.RemoveAll();
	selectNum = 0;
	numShape = 0;
	rectNum = 0;
	shape.num = rectNum;
	m_HBar.SetScrollPos(rectNum);
	m_HBar.SetScrollRange(rectNum, rectNum);
	Invalidate();
}
void CChildView::OnButtonClickedSave()
{
	CFile file(_T("Save.dat"), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);

	file.Write(&rectNum, sizeof(rectNum));
	m_shape.Serialize(ar);
	m_point.Serialize(ar);
}
void CChildView::OnButtonClickedLoad()
{
	CFile file(_T("Save.dat"), CFile::modeRead);
	CArchive ar(&file, CArchive::load);

	m_shape.RemoveAll();
	m_point.RemoveAll();
	file.Read(&rectNum, sizeof(rectNum));
	m_shape.Serialize(ar);
	m_point.Serialize(ar);
	selectNum = 0;
	Invalidate();
}
void CChildView::OnButtonClickedReplay()
{
	play = true;
}
void CChildView::OnButtonClickedStop()
{
	scrollplayNum = 0;
	m_HBar.SetScrollPos(scrollplayNum);
	play = false;
	x = 0;
	y = 0;
	Invalidate();
}

void CChildView::OnButtonClickedDelete()
{
	POSITION ptListShape = m_shape.GetHeadPosition();
	while (ptListShape != NULL)
	{
		POSITION cur = ptListShape;
		CShape mShape = m_shape.GetAt(ptListShape);
		
		
		if (mShape.num == selectNum)
		{
			for (POSITION i = ptListShape; i != NULL; m_shape.GetNext(i))
			{
				CShape Shape = m_shape.GetAt(i);
				Shape.num--;
				m_shape.SetAt(i, Shape);
			}
			numShape--;
			rectNum--;
			m_shape.RemoveAt(cur);
		}
		m_shape.GetNext(ptListShape);
	}
	m_HBar.SetScrollRange(0, rectNum - 1);
	m_HBar.ShowWindow(true);
	Invalidate();
}

void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (pScrollBar != NULL) {
		if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)
		{
			pScrollBar->SetScrollPos(nPos);
			selectNum = nPos;
			this->Invalidate();
		}
		if (nSBCode == SB_LINERIGHT)
		{
			selectNum++;
			if (selectNum > rectNum - 1)
				selectNum--;
			m_HBar.SetScrollPos(selectNum);
			this->Invalidate();

		}
		if (nSBCode == SB_LINELEFT)
		{
			selectNum--;
			if (selectNum < 0)
				selectNum++;
			m_HBar.SetScrollPos(selectNum);
			this->Invalidate();
		}

	}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0)
	{
		y++;
		Invalidate();
	}
	
	CWnd::OnTimer(nIDEvent);
}
