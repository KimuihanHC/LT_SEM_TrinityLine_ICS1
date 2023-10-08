//*****************************************************************************
// Filename	: View_MainCtrl.h
// Created	: 2010/11/26
// Modified	: 2016/06/07
//
// Author	: PiRing
//	
// Purpose	: 
//*****************************************************************************
#ifndef View_MainCtrl_h__
#define View_MainCtrl_h__

#pragma once

#include "TestManager_EQP.h"
// UI
#include "Wnd_MainView.h"
#include "Wnd_SettingView.h"
#include "Wnd_SocketView.h"
#include "Wnd_LogView.h"
#include "View_MonitoringData.h"
#include "Define_MonitorInfoFunc.h"

typedef enum _enumSubView
{
	SUBVIEW_MAIN = 0,
	SUBVIEW_SOCKET,
	SUBVIEW_RECIPE,
	SUBVIEW_LOG,
	SUBVIEW_MAX,
}enumSubView;

//=============================================================================
// CView_MainCtrl �?//=============================================================================
class CView_MainCtrl : public CWnd
{
// ?�성?�니??
public:
	CView_MainCtrl();
	virtual ~CView_MainCtrl();

protected:

	afx_msg int		OnCreate				(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize					(UINT nType, int cx, int cy);
	afx_msg void	OnPaint					();
	afx_msg BOOL	OnEraseBkgnd			(CDC* pDC);
	afx_msg HBRUSH	OnCtlColor				(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void	OnTimer					(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
	
	virtual BOOL	PreCreateWindow			(CREATESTRUCT& cs);

	// 배경??처리??/
	CBrush				m_brBkgr;

	//-----------------------------------------------------
	// 차일???�도??구분??	//-----------------------------------------------------	
	UINT					m_nWndIndex;
	CWnd*					m_pWndPtr[SUBVIEW_MAX];

	CWnd_MainView			m_wndMainView;
	CWnd_SocketView			m_wndSocketView;
	CWnd_SettingView		m_wndSettingView;
	CWnd_LogView			m_wndLogView;

	// ?�신 ?�태 ?�시 Pane???�인??/
	CWnd*					m_pwndCommPane				= nullptr;

	CView_MonitoringData	m_ViewSub;			// Sub ?�도??

	ST_MONITORINFO			m_infoMonitor;		// 모니???�보 구조�?	
	uint8_t					m_nLanguage					= 1;

	//-----------------------------------------------------
	// 초기 ?�정 관??	//-----------------------------------------------------
	// ?�성?�에??초기?????�팅
	virtual void	OnInit_ConstructionSetting			(){};
	// Window ?�성 ???�팅
	virtual void	OnInit_UISetting					(){};
	// 주�??�치??기본 ?�정
	virtual void	OnInit_DeviceSetting				(){};
	
	//-----------------------------------------------------
	// Sub ?�도???�정 관??	//-----------------------------------------------------
	void			Create_SubWindows			();
	virtual void	ShowWindow_SubMonitoring	(__in BOOL bShow);

	void			Update_Language				(__in uint8_t IN_nLanguage);

//=============================================================================
public: 
//=============================================================================
	
	// ?�도??배경???�정???�수
	void			SetBackgroundColor			(__in COLORREF color, __in BOOL bRepaint = TRUE);

	// 차일???�도???�환 ???�용
	virtual UINT	SwitchWindow				(__in UINT nIndex);
	// ?�치 ?�신 ?�태 ?�시 ?�도???�인???�정
	virtual void	SetCommPanePtr				(__in CWnd* pwndCommPane);
	
	// ?�션??변�??�었??경우 ?�시 UI???�이?��? ?�팅?�기 ?�한 ?�수
	virtual void	ReloadOption				(){};

	// ?�로그램 로딩 ?�난 ???�동 처리�??�한 ?�수
	virtual void	InitStartProgress			(){};	
	// ?�로그램 종료??처리?�야 ??기능?�을 처리?�는 ?�수
	virtual void	FinalExitProgress			(){};
	
	//--------------------- TEST --------------------------
	virtual void	Test_Process				(__in UINT nTestNo) = 0;
	//--------------------- TEST --------------------------
	
};

#endif // View_MainCtrl_h__


