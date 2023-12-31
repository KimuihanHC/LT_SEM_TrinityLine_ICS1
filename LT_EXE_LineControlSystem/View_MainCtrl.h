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
// CView_MainCtrl μ°?//=============================================================================
class CView_MainCtrl : public CWnd
{
// ?μ±?λ??
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

	// λ°°κ²½??μ²λ¦¬??/
	CBrush				m_brBkgr;

	//-----------------------------------------------------
	// μ°¨μΌ???λ??κ΅¬λΆ??	//-----------------------------------------------------	
	UINT					m_nWndIndex;
	CWnd*					m_pWndPtr[SUBVIEW_MAX];

	CWnd_MainView			m_wndMainView;
	CWnd_SocketView			m_wndSocketView;
	CWnd_SettingView		m_wndSettingView;
	CWnd_LogView			m_wndLogView;

	// ?΅μ  ?ν ?μ Pane???¬μΈ??/
	CWnd*					m_pwndCommPane				= nullptr;

	CView_MonitoringData	m_ViewSub;			// Sub ?λ??

	ST_MONITORINFO			m_infoMonitor;		// λͺ¨λ???λ³΄ κ΅¬μ‘°μ²?	
	uint8_t					m_nLanguage					= 1;

	//-----------------------------------------------------
	// μ΄κΈ° ?€μ  κ΄??	//-----------------------------------------------------
	// ?μ±?μ??μ΄κΈ°?????Έν
	virtual void	OnInit_ConstructionSetting			(){};
	// Window ?μ± ???Έν
	virtual void	OnInit_UISetting					(){};
	// μ£Όλ??₯μΉ??κΈ°λ³Έ ?€μ 
	virtual void	OnInit_DeviceSetting				(){};
	
	//-----------------------------------------------------
	// Sub ?λ???€μ  κ΄??	//-----------------------------------------------------
	void			Create_SubWindows			();
	virtual void	ShowWindow_SubMonitoring	(__in BOOL bShow);

	void			Update_Language				(__in uint8_t IN_nLanguage);

//=============================================================================
public: 
//=============================================================================
	
	// ?λ??λ°°κ²½???€μ ???¨μ
	void			SetBackgroundColor			(__in COLORREF color, __in BOOL bRepaint = TRUE);

	// μ°¨μΌ???λ???ν ???¬μ©
	virtual UINT	SwitchWindow				(__in UINT nIndex);
	// ?₯μΉ ?΅μ  ?ν ?μ ?λ???¬μΈ???€μ 
	virtual void	SetCommPanePtr				(__in CWnd* pwndCommPane);
	
	// ?΅μ??λ³κ²??μ??κ²½μ° ?€μ UI???°μ΄?°λ? ?Έν?κΈ° ?ν ?¨μ
	virtual void	ReloadOption				(){};

	// ?λ‘κ·Έλ¨ λ‘λ© ?λ ???λ μ²λ¦¬λ₯??ν ?¨μ
	virtual void	InitStartProgress			(){};	
	// ?λ‘κ·Έλ¨ μ’λ£??μ²λ¦¬?΄μΌ ??κΈ°λ₯?€μ μ²λ¦¬?λ ?¨μ
	virtual void	FinalExitProgress			(){};
	
	//--------------------- TEST --------------------------
	virtual void	Test_Process				(__in UINT nTestNo) = 0;
	//--------------------- TEST --------------------------
	
};

#endif // View_MainCtrl_h__


