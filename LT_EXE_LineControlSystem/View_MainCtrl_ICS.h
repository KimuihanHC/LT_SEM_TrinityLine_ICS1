//*****************************************************************************
// Filename	: 	View_MainCtrl_ICS.h
// Created	:	2021/1/27 - 13:55
// Modified	:	2021/1/27 - 13:55
//
// Author	:	piring
//	
// Purpose	:	 
//*****************************************************************************
#ifndef View_MainCtrl_ICS_h__
#define View_MainCtrl_ICS_h__


#pragma once

#include "View_MainCtrl.h"
#include "TestManager_EQP_ICS.h"


//=============================================================================
// CView_MainCtrl_ICS
//=============================================================================
class CView_MainCtrl_ICS : public CView_MainCtrl, public CTestManager_EQP_ICS
{
public:
	CView_MainCtrl_ICS();
	virtual ~CView_MainCtrl_ICS();

protected:
	afx_msg int		OnCreate		(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize			(UINT nType, int cx, int cy);

	// 로그 메세지
	afx_msg	LRESULT	OnWM_LogMsg					(WPARAM wParam, LPARAM lParam);

	afx_msg	LRESULT	OnWM_SwitchPermissionMode	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_ChangeRecipe			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_ChangedSetting			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_EqpCtrlCmd				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_TestSelect				(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT	OnWM_Eqp_Connection			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_AutoMode			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_Alarm				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_PortStatus			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_ConveyorStatus		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_EndOfProduction	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_CheckEmptyEqp		(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT	OnWM_Loader_RegisterSocket	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Loader_Check_TrackOut	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Tester_TrackIn			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Tester_EndInspection	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Unload_ReqTestResult	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Unload_NG_Info			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Unload_UnregisterSocket(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT	OnWM_Update_SocketData		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Update_SocketData_All	(WPARAM wParam, LPARAM lParam);

#if (USE_XML)
	afx_msg LRESULT	OnWM_Svr_Connection						(WPARAM wParam, LPARAM lParam);	
	afx_msg LRESULT OnWM_Svr_REQUEST_LINK_TEST				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPLY_LINK_TEST				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPORT_ONLINE_STATE			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPORT_USER_CHANGE				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REQUEST_USER_CHANGE			(WPARAM wParam, LPARAM lParam);	
	afx_msg LRESULT	OnWM_Svr_REPLY_USER_COMMAND				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPORT_EQUIPMENT_STATE			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REQUEST_EQUIPMENT_STATE_DISPLAY(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPLY_EQUIPMENT_STATE_DISPLAY	(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPORT_LOSS_STATE				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REQUEST_LOSS_WINDOW			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPLY_LOSS_WINDOW				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REPORT_ALARM_STATE				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REQUEST_ALARM_LIST				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REPLY_ALARM_LIST				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REPORT_RMS_MODE				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REQUEST_SET_DATETIME			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REPLY_SET_DATETIME				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REQUEST_TERMINAL_MESSAGE		(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REPLY_TERMINAL_MESSAGE			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REQUEST_OPCALL_MESSAGE			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REPLY_OPCALL					(WPARAM wParam, LPARAM lParam);
	//=============================================================================
	// WM_EVENT_EQUIPMENT 2023.04.11a uhkim
	//=============================================================================
	afx_msg LRESULT	OnWM_Eqp_REPORT_ONLINE_STATE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPORT_USER_CHANGE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPLY_USER_COMMAND(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPORT_EQUIPMENT_STATE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPLY_EQUIPMENT_STATE_DISPLAY(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPORT_LOSS_STATE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPLY_LOSS_WINDOW(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Eqp_REPORT_ALARM_STATE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Eqp_REPORT_RMS_MODE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Eqp_REPLY_OPCALL(WPARAM wParam, LPARAM lParam);
#endif	//TEST
#if TEST
	afx_msg LRESULT OnWM_Svr_UNITID_READ					(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REQUEST_UNITID_READ			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPLY_UNITID_READ				(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnWM_Svr_REPORT_START_PROCESS			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPORT_START_LOT				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Svr_REPORT_END_EVENT				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Svr_REPORT_END_PROCESS				(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnWM_Eqp_UNITID_READ					(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPLY_UNITID_READ				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Eqp_REPORT_START_PROCESS			(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPORT_START_LOT				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWM_Eqp_REPORT_END_EVENT				(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnWM_Eqp_REPORT_END_PROCESS				(WPARAM wParam, LPARAM lParam);
#endif	//TEST
	DECLARE_MESSAGE_MAP()

	//=========================================================================
	// CView_MainCtrl ?�정??	//=========================================================================
	//-----------------------------------------------------
	// 초기 ?�정 관??	//-----------------------------------------------------
	// ?�성?�에??초기?????�팅
	virtual void	OnInit_ConstructionSetting		();
	// Window ?�성 ???�팅
	virtual void	OnInit_UISetting				();
	// 주�??�치??기본 ?�정
	virtual void	OnInit_DeviceSetting			();

	//-------------------------------------------------------------------------
	// ?�일 불러?�기 �??�팅
	bool			OnLoad_LineInfo					(__in bool IN_bNotifySettingWnd = true);
	bool			OnLoad_SocketInfo				(__in bool IN_bNotifySettingWnd = true);
	bool			OnLoad_UserInfo					(__in bool IN_bNotifySettingWnd = true);
	//bool			OnLoad_AlarmInfo				(__in bool IN_bNotifySettingWnd = true);
	bool			OnLoad_NGCodeInfo				(__in bool IN_bNotifySettingWnd = true);
	bool			OnLoad_DebugInfo				(__in bool IN_bNotifySettingWnd = true);

	bool			OnLoad_ModelInfo				();
	bool			OnLoad_FailInfo					();

	bool			OnLoad_Prev_LineInfo			();
	bool			OnLoad_Prev_LineInfo_OnlyYield	();

	// ?�비 ?�이?? ?�신, GUI 매칭
	virtual void	OnMatchingEquipment				();
	bool			Compare_LineConfig_ServRestart	(__in CConfig_Line* IN_Old, __in CConfig_Line* IN_New);
	//=========================================================================
	// CTestManager_EQP_ICS ?�정??	
	//=========================================================================
	//-----------------------------------------------------
	// 로그/?�일 처리
	//-----------------------------------------------------
	virtual void	OnInit_LogFolder				();

	//-----------------------------------------------------
	// UI ?�데?�트
	//-----------------------------------------------------
	virtual void	OnSetStatus_Production			(__in bool IN_bEnd);

	//-----------------------------------------------------
	// 결과 ?�이??처리
	//-----------------------------------------------------
	virtual void	OnLog_EquipmentAlarm			(__in uint8_t IN_nEqpOder, __in const ST_AlarmStatus* IN_pAlarm);
	virtual void	OnLog_RegisterSocket			(__in LPCTSTR IN_szRFID);

	// ?�품 결과 ?�면???�시
	virtual void	OnReport_Socket					(__in LPCTSTR IN_szRFID);
	virtual void	OnReport_Socket_NG				(__in LPCTSTR IN_szRFID);

	// 검??진행 ?�간 체크 (?�비, ?�라 L/R)
	virtual void	OnUpdate_ElapsedTime_Unit		(__in UINT nEquipmentIdx, __in uint8_t IN_nPara);
	virtual void	OnUpdate_ElapsedTime_All		();

public: 
	//=========================================================================
	// CView_MainCtrl ?�정??	//=========================================================================
	// 차일???�도???�환 ???�용
	virtual UINT	SwitchWindow				(__in UINT nIndex);
	// ?�치 ?�신 ?�태 ?�시 ?�도???�인???�정
	virtual void	SetCommPanePtr				(__in CWnd* pwndCommPane);

	// ?�션??변�??�었??경우 ?�시 UI???�이?��? ?�팅?�기 ?�한 ?�수
	virtual void	ReloadOption				();

	// ?�로그램 로딩 ?�난 ???�동 처리�??�한 ?�수
	virtual void	InitStartProgress			();	
	virtual BOOL	InitStartDeviceProgress		();	

	// ?�로그램 종료??처리?�야 ??기능?�을 처리?�는 ?�수
	virtual void	FinalExitProgress			();

	//=========================================================================
	// CTestManager_EQP_ICS ?�정??	//=========================================================================
	// 검?�기 종류 ?�정
	virtual void	OnSet_SystemType			(__in enInsptrSysType nSysType);

	// 로그 메세지 처리???�수
	virtual void	OnAdd_Log					(__in LPCTSTR lpszLog, __in BOOL bError = FALSE, __in UINT nLogType = LOGTYPE_NONE, __in BOOL bOnlyLogType = FALSE);
	virtual void	OnAdd_Log					(__in LPCTSTR lpszLog, __in UINT nLogType = LOGTYPE_NONE);

	// ?�어 권한 ?�정
	virtual void	OnInit_PermissionMode		(__in enPermissionMode nAcessMode);	
	virtual void	OnSet_PermissionMode		(__in enPermissionMode nAcessMode);	

	void			Proc_LineCtrlCmd			(__in uint8_t IN_nCmdIndex);
	void			Proc_EquipmentCtrlCmd		(__in uint8_t IN_nCmdIndex, __in uint8_t IN_nEqpOrder);

	//=========================================================================
	// TEST 코드
	//=========================================================================
	virtual void	Test_Process				(__in UINT nTestNo);	

#if (USE_XML)
protected:
	bool			OnLoad_ServerInfo(__in bool IN_bNotifySettingWnd = true);
	bool			OnLoad_EESInfo(__in bool IN_bNotifySettingWnd = true);
	bool			OnLoad_ALInfo(__in bool IN_bNotifySettingWnd = true);
	bool			OnLoad_LossInfo(__in bool IN_bNotifySettingWnd = true);
protected:
	virtual void	OnMatchingServer();
	bool            Compare_ServerConfig_ServRestart(__in CConfig_Server* IN_Old, __in CConfig_Server* IN_New);
public:
	void			OnSet_Connection						(LPARAM IN_LPARAM);
	void			Proc_ServerRequestLinkTest				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplyLinkTest				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReportOnlineState			(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerReportUserChange				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerRequestUserChange			(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplyUserCommand				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerReportEquipmentState			(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerRequestEquipmentStateDisplay	(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplyEquipmentStateDisplay	(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerReplyLossState				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerRequestLossState				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplyLossWindow				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerReportAlarmState				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerRequestAlarmList				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplyAlarmList				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerEESMode						(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerRequestSetDateTime			(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplySetDateTime				(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerRequestTerminalMessage		(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplyTerminalMessage			(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerRequestOpCallMessage			(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplyOpCall					(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
public:
	virtual void	OnSet_EESMode(__in enEES_Mode nAcessMode);
#endif
#if TEST
protected:
	virtual void	OnReport_TerminalMessage(__in lt::Request_Terminal_Message_Args::Args& IN_Data);
	virtual	void	OnReport_OpCall(__in lt::Request_Opcall_Args::Args&  IN_Data);
	virtual BOOL	GetNtPrivilege();
public:
	void			Proc_ServerUnitIdRead(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerRequestUnitIdRead(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReplytUnitIdRead(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);

	void			Proc_ServerReportStartProcess(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReportStartLot(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReportEndEvent(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
	void			Proc_ServerReportEndProcess(__in WPARAM IN_WPARAM, __in LPARAM IN_LPARAM);
#endif
};
#if (USE_XML)
extern CView_MainCtrl_ICS* mView_MainCtrl_ICS;
#endif
#endif // View_MainCtrl_ICS_h__
