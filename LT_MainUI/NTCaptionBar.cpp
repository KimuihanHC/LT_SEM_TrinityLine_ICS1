﻿//*****************************************************************************
// Filename	: 	NTCaptionBar.cpp
//
// Created	:	
// Modified	:	2010/03/10 - 11:01
//
// Author	:	PiRing
//	
// Purpose	:	
//*****************************************************************************
// NTCaptionBar.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NTCaptionBar.h"
#include "NTVisualManager.h"
#include "NTStyle.h"

// CNTCaptionBar

IMPLEMENT_DYNAMIC(CNTCaptionBar, CPane)

//=============================================================================
// 생성자
//=============================================================================
CNTCaptionBar::CNTCaptionBar() : CPane   ()
	, m_hIcon           (NULL)
	, m_szIcon          (0, 0)
	, m_bParentActive   (false)
	, m_bParentMaximize (false)
{
	m_wmOption = NULL;
}

//=============================================================================
// 소멸자
//=============================================================================
CNTCaptionBar::~CNTCaptionBar()
{
}


BEGIN_MESSAGE_MAP(CNTCaptionBar, CPane)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CNTCaptionBar 메시지 처리기입니다.

//=============================================================================
// Method		: CNTCaptionBar::PreCreateWindow
// Access		: virtual protected 
// Returns		: BOOL
// Parameter	: CREATESTRUCT & cs
// Qualifier	:
// Last Update	: 2010/03/18 - 17:19
// Desc.		: 
//=============================================================================
BOOL CNTCaptionBar::PreCreateWindow (CREATESTRUCT& cs)
{
	// in Win4, status bars do not have a border at all, since it is
	//  provided by the client area.
	if ((m_dwStyle & (CBRS_ALIGN_ANY | CBRS_BORDER_ANY)) == CBRS_TOP)
	{
		m_dwStyle &= ~(CBRS_BORDER_ANY | CBRS_BORDER_3D);
	}

	return CPane::PreCreateWindow(cs);
}

//=============================================================================
// Method		: CNTCaptionBar::Create
// Access		: public 
// Returns		: BOOL
// Parameter	: CWnd * pParentWnd
// Parameter	: UINT nID
// Qualifier	:
// Last Update	: 2010/03/18 - 17:19
// Desc.		: 
//=============================================================================
BOOL CNTCaptionBar::Create (CWnd* pParentWnd, UINT nID)
{
	return CreateEx(pParentWnd, nID);
}

//=============================================================================
// Method		: CNTCaptionBar::CreateEx
// Access		: public 
// Returns		: BOOL
// Parameter	: CWnd * pParentWnd
// Parameter	: UINT nID
// Qualifier	:
// Last Update	: 2010/03/18 - 17:19
// Desc.		: 
//=============================================================================
BOOL CNTCaptionBar::CreateEx (CWnd* pParentWnd, UINT nID)
{
	ASSERT_VALID(pParentWnd);   // must have a parent

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | CBRS_TOP;

	// save the style
	SetPaneAlignment (dwStyle & CBRS_ALL);

	// create the HWND
	CRect rect(0, 0, 0, 0);

	LPCTSTR lpszClass = AfxRegisterWndClass(CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_BTNFACE+1), NULL);

	m_dwControlBarStyle = 0; // can't float, resize, close, slide

	BOOL bSystemSmall = (pParentWnd->GetExStyle() & WS_EX_TOOLWINDOW) != 0;

	if (!CWnd::Create(lpszClass, NULL, dwStyle | WS_CLIPSIBLINGS, rect, pParentWnd, nID))
	{
		return FALSE;
	}

	if (pParentWnd->IsKindOf (RUNTIME_CLASS (CFrameWndEx)))
	{
		((CFrameWndEx*) pParentWnd)->AddPane (this);
	}
	else
	{
		ASSERT (FALSE);
		return FALSE;
	}

	HINSTANCE hInstance = AfxFindResourceHandle (MAKEINTRESOURCE (nID), RT_GROUP_ICON);

	if (hInstance != NULL)
	{
		CSize szIcon (::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON));

		HICON hIcon = (HICON)::LoadImage (hInstance, MAKEINTRESOURCE (nID), IMAGE_ICON, szIcon.cx, szIcon.cy, LR_DEFAULTCOLOR);

		if (hIcon != NULL)
		{
			SetIcon (hIcon);
		}
	}

	CString strCaption;

	pParentWnd->GetWindowText (strCaption);

	if (strCaption.IsEmpty ())
	{
		BOOL bValidString;
		bValidString = strCaption.LoadString (nID);
	}

	if (!strCaption.IsEmpty ())
	{
		SetWindowText (strCaption);
	}

	NONCLIENTMETRICS ncm;
	ZeroMemory (&ncm, sizeof (NONCLIENTMETRICS));
	ncm.cbSize = sizeof (NONCLIENTMETRICS);

	SystemParametersInfo (SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);

	m_SystemHeight  = ::GetSystemMetrics (bSystemSmall ? SM_CYSMCAPTION : SM_CYCAPTION);
	m_CaptionHeight = m_SystemHeight;

	SetCaptionFont (bSystemSmall ? ncm.lfSmCaptionFont : ncm.lfCaptionFont);

	CRect rt (0, 0, bSystemSmall ? ncm.iSmCaptionWidth : ncm.iCaptionWidth, bSystemSmall ? ncm.iSmCaptionHeight : ncm.iCaptionHeight);


	CNTVisualManager* pManager = DYNAMIC_DOWNCAST (CNTVisualManager, CMFCVisualManager::GetInstance ());

	if (pManager != NULL)
	{
		if (pManager->LoadNTCaptionButtonsIcons (_T("IDB_NT_CAPTION_BTNS")))
		{
			rt.right  = pManager->GetNTCaptionButtonsSize ().cx;
			rt.bottom = pManager->GetNTCaptionButtonsSize ().cx;
		};

		m_CaptionHeight = rt.bottom + 2;
	}


	m_BtnClose.Create (_T(""), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, rt, this, SC_CLOSE);
	m_BtnClose.SetTooltip (_T("프로그램을 종료합니다."));	

	m_BtnMaximize.Create (_T(""), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, rt, this, SC_MAXIMIZE);
	m_BtnMaximize.SetTooltip (_T("창을 전체 화면 크기로 확대합니다."));

	m_BtnMinimize.Create (_T(""), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, rt, this, SC_MINIMIZE);
	m_BtnMinimize.SetTooltip (_T("창을 아이콘으로 축소합니다."));

	m_BtnOption.Create (_T(""), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, rt, this, SC_OPTION);
	m_BtnOption.SetTooltip (_T("환경설정"));
	m_BtnOption.SetSysCommand (SC_OPTION);

	return TRUE;
}

//=============================================================================
// Method		: CNTCaptionBar::SetCaptionHeight
// Access		: public 
// Returns		: void
// Parameter	: int nHeight
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::SetCaptionHeight (int nHeight)
{
	if (m_CaptionHeight != nHeight)
	{
		m_CaptionHeight = nHeight;

		RecalcLayout ();
	}
}

//=============================================================================
// Method		: CNTCaptionBar::CalcFixedLayout
// Access		: public 
// Returns		: CSize
// Parameter	: BOOL
// Parameter	: BOOL
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
CSize CNTCaptionBar::CalcFixedLayout (BOOL, BOOL)
{
	ASSERT_VALID(this);

	// recalculate based on font height + icon height + borders
	TEXTMETRIC tm;
	{
		CClientDC dcScreen(NULL);
		HFONT hFont = GetCaptionFont ();

		HGDIOBJ hOldFont = dcScreen.SelectObject(hFont);
		VERIFY(dcScreen.GetTextMetrics(&tm));
		dcScreen.SelectObject(hOldFont);
	}

	int nHeight = max ( max (tm.tmHeight, m_szIcon.cy), GetCaptionHeight ());

	return CSize (32767, nHeight);// + CY_BORDER * 4 - rectSize.Height());
}

//=============================================================================
// Method		: CNTCaptionBar::SetCaptionFont
// Access		: public 
// Returns		: void
// Parameter	: const LOGFONT & lf
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::SetCaptionFont (const LOGFONT& lf)
{
	if (m_CaptionFont.GetSafeHandle () != NULL)
	{
		m_CaptionFont.DeleteObject ();
	}

	m_CaptionFont.CreateFontIndirect (&lf);
}

//=============================================================================
// Method		: CNTCaptionBar::SetIcon
// Access		: public 
// Returns		: void
// Parameter	: HICON hIcon
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::SetIcon (HICON hIcon)
{
	m_szIcon = CSize (0, 0);

	if (m_hIcon != NULL)
	{
		::DestroyIcon(m_hIcon);
	}

	m_hIcon = hIcon;

	if (m_hIcon != NULL)
	{
		ICONINFO ii;
		ZeroMemory (&ii, sizeof (ICONINFO));

		::GetIconInfo (m_hIcon, &ii);

		if (ii.hbmColor != NULL)
		{
			BITMAP bm;
			ZeroMemory (&bm, sizeof (BITMAP));

			if (::GetObject (ii.hbmColor, sizeof (BITMAP), &bm) != 0)
			{
				m_szIcon.cx = bm.bmWidth;
				m_szIcon.cy = bm.bmHeight;
			}
		}
	}
}

//=============================================================================
// Method		: CNTCaptionBar::SetParentActive
// Access		: public 
// Returns		: void
// Parameter	: BOOL bParentActive
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::SetParentActive (BOOL bParentActive)
{
	if (m_bParentActive != bParentActive)
	{
		m_bParentActive = bParentActive;
		Invalidate ();
	}
}

//=============================================================================
// Method		: CNTCaptionBar::SetParentMaximize
// Access		: public 
// Returns		: void
// Parameter	: BOOL bParentMaximize
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::SetParentMaximize (BOOL bParentMaximize)
{
	if (m_BtnMaximize.GetSafeHwnd () != NULL)
	{
		m_BtnMaximize.SetSysCommand (bParentMaximize ? SC_RESTORE : SC_MAXIMIZE);
		m_BtnMaximize.SetTooltip (bParentMaximize ? _T("창을 보통 크기로 복원합니다.") : _T("창을 전체 화면 크기로 확대합니다."));
	}

	if (m_bParentMaximize != bParentMaximize)
	{
		m_bParentMaximize = bParentMaximize;

		Invalidate ();
	}
}

//=============================================================================
// Method		: Enable_OptionButton
// Access		: public  
// Returns		: void
// Parameter	: __in bool bEnable
// Qualifier	:
// Last Update	: 2022/2/19 - 14:37
// Desc.		:
//=============================================================================
void CNTCaptionBar::Enable_OptionButton(__in bool bEnable)
{
	m_BtnOption.ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
}

//=============================================================================
// Method		: CNTCaptionBar::GetCaptionTextColor
// Access		: public 
// Returns		: COLORREF
// Qualifier	: const
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
COLORREF CNTCaptionBar::GetCaptionTextColor () const
{
	//return IsParentActive () ? afxGlobalData.clrCaptionText : afxGlobalData.clrInactiveCaptionText;
	return RGB(255, 255, 255);

}

//=============================================================================
// Method		: CNTCaptionBar::DoPaint
// Access		: virtual protected 
// Returns		: void
// Parameter	: CDC * pDCPaint
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::DoPaint (CDC* pDCPaint)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDCPaint);

	CRect rectClip;
	pDCPaint->GetClipBox (rectClip);

	CRect rect;
	GetClientRect(rect);

	CMemDC memDC (*pDCPaint, this);
	CDC* pDC = &memDC.GetDC ();

	CMFCVisualManager::GetInstance ()->OnFillBarBackground (pDC, this, rect, rectClip);

	HGDIOBJ  hOldFont    = pDC->SelectObject (GetCaptionFont());

	int      nOldMode    = pDC->SetBkMode    (TRANSPARENT);
	COLORREF crTextColor = pDC->SetTextColor (GetCaptionTextColor());
	//COLORREF crBkColor   = pDC->SetBkColor   (afxGlobalData.clrBtnFace);
	COLORREF crBkColor   = pDC->SetBkColor   (RGB(0,255,255));

	if (m_hIcon != NULL && m_szIcon != CSize (0, 0))
	{
		CRect rectIcon (0, 0, m_SystemHeight, rect.Height ());

		int x = max (0, (rectIcon.Width ()  - m_szIcon.cx) / 2);
		int y = max (0, (rectIcon.Height () - m_szIcon.cy) / 2);

		::DrawIconEx (pDC->GetSafeHdc (), x, y, m_hIcon, m_szIcon.cx, m_szIcon.cy, 0, NULL, DI_NORMAL);

		rect.left  += m_SystemHeight;

		CRect rt;
		m_BtnMinimize.GetWindowRect (rt);
		ScreenToClient (rt);

		rect.right = rt.left - 1;
	}

	if (!m_strCaption.IsEmpty ())
	{
		pDC->DrawText (m_strCaption, rect, DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER);
	}

	pDC->SetTextColor (crTextColor);
	pDC->SetBkColor   (crBkColor);
	pDC->SetBkMode    (nOldMode);

	pDC->SelectObject (hOldFont);
}


/////////////////////////////////////////////////////////////////////////////
// CNTCaptionBar message handlers

//=============================================================================
// Method		: CNTCaptionBar::OnSetText
// Access		: protected 
// Returns		: LRESULT
// Parameter	: WPARAM
// Parameter	: LPARAM lParam
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
LRESULT CNTCaptionBar::OnSetText (WPARAM, LPARAM lParam)
{
	TRY
	{
		m_strCaption.Empty();
		if (lParam != NULL)
		{
			m_strCaption = (LPCTSTR)lParam;
		}

		Invalidate ();
	}
	CATCH_ALL(e)
	{
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL

		return TRUE;
}

//=============================================================================
// Method		: CNTCaptionBar::OnSize
// Access		: protected 
// Returns		: void
// Parameter	: UINT nType
// Parameter	: int cx
// Parameter	: int cy
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::OnSize (UINT nType, int cx, int cy) 
{
	CPane::OnSize(nType, cx, cy);

	if (m_BtnClose.GetSafeHwnd () != NULL && m_BtnMaximize.GetSafeHwnd () != NULL && m_BtnMinimize.GetSafeHwnd () != NULL && m_BtnMinimize.GetSafeHwnd () != NULL)
	{
		int nHeight = cy;

		DWORD dwFlag = SWP_NOOWNERZORDER | SWP_NOZORDER;

		CRect rt;
		m_BtnClose.GetWindowRect (rt);
		rt.OffsetRect (-rt.TopLeft ());

		CSize szBtnSize (0, 0);

		CNTVisualManager* pManager = DYNAMIC_DOWNCAST (CNTVisualManager, CMFCVisualManager::GetInstance ());

		if (pManager != NULL)
		{
			szBtnSize = pManager->GetNTCaptionButtonsSize ();
		}

		if (szBtnSize == CSize (0, 0))
		{
			szBtnSize = rt.Size ();
		}

		if (szBtnSize.cy > nHeight)
		{
			rt.right   = szBtnSize.cy;
			rt.bottom  = szBtnSize.cy;
			rt.DeflateRect (1, 1);
		}
		else
		{
			rt.right   = szBtnSize.cx;
			rt.top     = (nHeight - szBtnSize.cy) / 2;
			rt.bottom  = rt.top + szBtnSize.cy;
		}

		rt.OffsetRect (cx - rt.Width (), 0);
		m_BtnClose.SetWindowPos(&wndTop, rt.left, rt.top, rt.Width(), rt.Height(), dwFlag);

		rt.OffsetRect(-rt.Width()-1, 0);
		m_BtnMaximize.SetWindowPos(&wndTop, rt.left, rt.top, rt.Width(), rt.Height(), dwFlag);

		rt.OffsetRect(-rt.Width()-1, 0);
		m_BtnMinimize.SetWindowPos(&wndTop, rt.left, rt.top, rt.Width(), rt.Height(), dwFlag);

		rt.OffsetRect(-rt.Width()-1, 0);
		rt.OffsetRect(-rt.Width()-1, 0);
		m_BtnOption.SetWindowPos(&wndTop, rt.left, rt.top, rt.Width(), rt.Height(), dwFlag);
	}
}

//=============================================================================
// Method		: CNTCaptionBar::PreTranslateMessage
// Access		: virtual protected 
// Returns		: BOOL
// Parameter	: MSG * pMsg
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
BOOL CNTCaptionBar::PreTranslateMessage (MSG* pMsg) 
{
	if (!CPane::PreTranslateMessage (pMsg))
	{
		return FALSE;
	}

	CWnd* pParentWnd = GetParent ();

	if (pParentWnd != NULL)
	{
		CPoint pt;
		::GetCursorPos (&pt);

		UINT uiHit = HitTest (pt);

		if (uiHit == HTCAPTION || uiHit == HTSYSMENU)
		{
			UINT   message = 0;
			WPARAM wParam  = uiHit;
			LPARAM lParam  = MAKELPARAM (pt.x, pt.y);

			switch (pMsg->message)
			{
			case WM_LBUTTONDOWN:
				message = WM_NCLBUTTONDOWN;
				break;
			case WM_LBUTTONUP:
				message = WM_NCLBUTTONUP;
				break;
			case WM_LBUTTONDBLCLK:
				message = WM_NCLBUTTONDBLCLK;
				break;
			}

			if (message != 0)
			{
				if (message == WM_NCLBUTTONDOWN && uiHit == HTSYSMENU)
				{
					CRect rt;
					GetWindowRect (rt);

					ShowSysMenu (CPoint (rt.left, rt.bottom));
				}
				else
				{
					pParentWnd->SendMessage (message, wParam, lParam);
				}
			}
		}
	}

	return TRUE;
}

//=============================================================================
// Method		: CNTCaptionBar::HitTest
// Access		: virtual protected 
// Returns		: UINT
// Parameter	: const CPoint & pt
// Qualifier	: const
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
UINT CNTCaptionBar::HitTest (const CPoint& pt) const
{
	UINT uiHit = HTNOWHERE;

	CPoint ptHit  (pt);
	ScreenToClient (&ptHit);

	CRect rtClient;
	GetClientRect (rtClient);

	if (rtClient.PtInRect (ptHit))
	{
		uiHit = HTCAPTION;

		CRect rt (0, 0, m_SystemHeight, GetCaptionHeight ());

		if (m_hIcon != NULL && m_szIcon != CSize (0, 0))
		{
			if (rt.PtInRect (ptHit))
			{
				uiHit = HTSYSMENU;
			}
		}

		if (uiHit == HTCAPTION)
		{
			const CWnd* pCapture = GetCapture ();

			// 추가 버튼


			// System Button
			const CNTCaptionBarButton* pBtns[4] = 
			{
				&m_BtnClose, &m_BtnMaximize, &m_BtnMinimize, &m_BtnOption
			};

			for (long i = 0; i < 4; i++)
			{
				const CNTCaptionBarButton* pBtn = pBtns[i];

				if (pBtn != NULL && pBtn->GetSafeHwnd () != NULL && pBtn->IsWindowVisible ())
				{
					pBtn->GetWindowRect (rt);
					if (rt.PtInRect (pt) || pCapture == pBtn)
					{
						switch (pBtn->GetSysCommand ())
						{
						case SC_CLOSE:
							uiHit = HTCLOSE;
							break;

						case SC_MINIMIZE:
							uiHit = HTMINBUTTON; // or HTREDUCE
							break;

						case SC_RESTORE:
						case SC_MAXIMIZE:
							uiHit = HTMAXBUTTON; // or HTZOOM
							break;

						case SC_CONTEXTHELP:
							uiHit = HTHELP;
							break;

						case SC_OPTION:
							uiHit = HTMENU;
							break;

						default:
							ASSERT (FALSE);
						}
						break;
					}
				}
			}
		}
	}

	return uiHit;
}

//=============================================================================
// Method		: CNTCaptionBar::ShowSysMenu
// Access		: virtual protected 
// Returns		: void
// Parameter	: const CPoint & point
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::ShowSysMenu (const CPoint& point)
{
	CWnd* pParentWnd = GetParent ();

	if (pParentWnd != NULL)
	{
		CMenu* pMenu = pParentWnd->GetSystemMenu (FALSE);

		if (pMenu == NULL || pMenu->GetSafeHmenu () == NULL)
		{
			return;
		}

		pMenu->SetDefaultItem (SC_CLOSE);

		if (m_bParentMaximize)
		{
			pMenu->EnableMenuItem (SC_SIZE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem (SC_MOVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem (SC_MAXIMIZE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

			pMenu->EnableMenuItem (SC_RESTORE, MF_BYCOMMAND | MF_ENABLED);
		}
		else
		{
			pMenu->EnableMenuItem (SC_RESTORE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

			pMenu->EnableMenuItem (SC_SIZE, MF_BYCOMMAND | MF_ENABLED);
			pMenu->EnableMenuItem (SC_MOVE, MF_BYCOMMAND | MF_ENABLED);
			pMenu->EnableMenuItem (SC_MAXIMIZE, MF_BYCOMMAND | MF_ENABLED);
		}

		((CWinAppEx*)AfxGetApp ())->GetContextMenuManager ()->ShowPopupMenu (pMenu->GetSafeHmenu(), point.x, point.y, this, TRUE, TRUE, FALSE);
	}
}

//=============================================================================
// Method		: CNTCaptionBar::OnContextMenu
// Access		: protected 
// Returns		: void
// Parameter	: CWnd *
// Parameter	: CPoint point
// Qualifier	:
// Last Update	: 2010/03/18 - 17:18
// Desc.		: 
//=============================================================================
void CNTCaptionBar::OnContextMenu (CWnd* /*pWnd*/, CPoint point) 
{
	UINT uiHit = HitTest (point);

	if (uiHit == HTCAPTION || uiHit == HTSYSMENU)
	{
		ShowSysMenu (point);
	}
}

//=============================================================================
// Method		: CNTCaptionBar::OnCommand
// Access		: virtual protected 
// Returns		: BOOL
// Parameter	: WPARAM wParam
// Parameter	: LPARAM lParam
// Qualifier	:
// Last Update	: 2010/03/18 - 17:17
// Desc.		: 
//=============================================================================
BOOL CNTCaptionBar::OnCommand (WPARAM wParam, LPARAM lParam)
{
	UINT nID = LOWORD (wParam);

	if (SC_SIZE <= nID && nID <= SC_CONTEXTHELP)
	{
		OnSysCommand (nID, 0);
		return TRUE;
	}
	else if (SC_OPTION == nID)
	{
		CWnd* pParentWnd = GetParent ();

		if (pParentWnd != NULL)
		{
			pParentWnd->PostMessage (m_wmOption, NULL);
		}
	}

	return CPane::OnCommand(wParam, lParam);
}

//=============================================================================
// Method		: CNTCaptionBar::OnSysCommand
// Access		: protected 
// Returns		: void
// Parameter	: UINT nID
// Parameter	: LPARAM lParam
// Qualifier	:
// Last Update	: 2010/03/18 - 17:17
// Desc.		: 
//=============================================================================
void CNTCaptionBar::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CWnd* pParentWnd = GetParent ();

	if (pParentWnd != NULL)
	{
		pParentWnd->PostMessage (WM_SYSCOMMAND, nID, lParam);
	}
}

