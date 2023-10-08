//*****************************************************************************
// Filename	: 	SocketMonitoring.h
// Created	:	2021/11/18 - 14:20
// Modified	:	2021/11/18 - 14:20
//
// Author	:	piring
//	
// Purpose	:	 
//*****************************************************************************
#ifndef SocketMonitoring_h__
#define SocketMonitoring_h__


#pragma once

#include <map>
#include "Def_Socket_Info.h"
#include "Def_Yield.h"
#include "RegSocket.h"
#include "Def_DebugInfo.h"


class CLineInfo;
class CRework_Info;

//-----------------------------------------------------------------------------
// CSocketMonitoring
//-----------------------------------------------------------------------------
class CSocketMonitoring
{
public:
	CSocketMonitoring();
	~CSocketMonitoring();

	CSocketMonitoring& operator= (const CSocketList& ref);
	CSocketMonitoring& operator= (const CSocketMonitoring& ref);

//protected:

	// ?�켓 ?�보 (key: RFID)//
#ifdef _UNICODE
	std::map<std::wstring, CSocketInfo_Unit> m_Sockets;
#else
	std::map<std::string, CSocketInfo_Unit> m_Sockets;
#endif

protected:
	// ?��??�트리에 ?�이???�?�용??/
	CRegSocket		m_regSocket;

	uint8_t			m_nLineSocketJIG_Type	= 0;	// H, V

	HWND			m_hWndOwner				= nullptr;
	UINT			m_nWM_Notify			= NULL;
	inline void		WM_Update_GUI_Data		(__in LPCTSTR IN_szRFID, __in uint16_t IN_nFlag);
	inline void		WM_Update_GUI_Data_All	(__in uint16_t IN_nFlag);

	// ?�인 ?�보//
	const CLineInfo*	m_pLineInfo			= nullptr;

	// ?�버�??�보//
	const ST_DebugInfo*	m_pDebugInfo		= nullptr;

	// MES Rework NG Code
	int16_t				m_nMES_ReworkCode	= 0;	// REWORK ?�품 MES 결과 코드: ?�비?�서 ?�당코드�?리턴 ??경우 REWORK ?�품?�로 ?�품 처리

	// ?�일 or ?��??�트�?처리//
	bool	Save_SocketInfo				(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_Barcode		(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_Status		(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_Equipment	(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_Location	(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_Target		(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_Yield		(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_TestResult	(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_InputTime	(__in LPCTSTR IN_szRFID);
	bool	Save_SocketInfo_OutputTime	(__in LPCTSTR IN_szRFID);

	bool	Load_SocketInfo				(__in LPCTSTR IN_szRFID);

	//bool	Save_ReworkInfo				(__in LPCTSTR IN_szRFID);
	//bool	Load_ReworkInfo				(__in LPCTSTR IN_szBarcode, __in LPCTSTR IN_szRFID);
	//bool	Remove_ReworkInfo			(__in LPCTSTR IN_szBarcode);

	bool	Write_File					(__in LPCTSTR IN_szPathFile, __in LPCTSTR IN_szData, __in LPCTSTR IN_szHeader);

public:

	// ?�체 ?�이?? 초기??/
	void	Reset						();	

	// ?�정 ?�켓 ?�이??초기??/
	void	Reset_Socket				(__in LPCTSTR szRFID);	

	// ?�켓 목록 ?�데?�트 (?�켓 ?�이??추�?)//
#ifdef _UNICODE
	void	Init_Sockets				(__in const std::vector<std::wstring>* IN_RFIDs);
#else
	void	Init_Sockets				(__in const std::vector<std::string>* IN_RFIDs);
#endif

	// ?�산?�량 증�? (equipment id, socket rfid, pass/fail)//
	void	IncreasePass_byEqp			(__in LPCTSTR szEqpID, __in LPCTSTR szRFID, __in uint8_t IN_nPara);
	void	IncreaseFail_byEqp			(__in LPCTSTR szEqpID, __in LPCTSTR szRFID, __in uint8_t IN_nPara);
	// Unload??Unregister ????처리//
	void	IncreaseYield_Final			(__in LPCTSTR szRFID);

	// ?�켓 �?��//
	size_t	GetCount					() const;

	// 모든 ?�켓 ??��//
	void	RemoveAll					();

	// ?�켓 ?�입//
	bool	Socket_Insert				(__in CSocketInfo_Unit& IN_stSocket);

	// ?�켓 ??��//
	void	Socket_Remove				(__in LPCTSTR szRFID);

	// ?�켓 ?�정//
	void	Socket_Modify				(__in CSocketInfo_Unit* IN_pstSocket);

	// RFID ?�보�??�켓 ?�보 ?�기//
	CSocketInfo_Unit&		GetAt		(__in LPCTSTR szRFID);
	const CSocketInfo_Unit& GetAt		(__in LPCTSTR szRFID) const;


public:

	// Data�?GUI???�시?�기 ?�해 ?�용//
	void	Set_OwnerHWND				(__in HWND IN_hWnd);
	// Notify Windows Message ?�정//
	void	Set_WinMsg_UpdateUI			(__in UINT IN_nWM_UpdateUI);


	// ?�재 ?�용 ?�정???�켓 JIG Type//
	void	Set_LineSocketJIG_Type		(__in uint8_t IN_nSocketType);
	uint8_t	Get_LineSocketJIG_Type		() const;

	// ?�켓 RFID 기�??�로 Socket Type�?Comment가 변경된 경우//
	void	Set_SocketConfig			(__in const CSocketList* IN_pSocketList);
	// ?�켓 ?�보 ?�정//
	void	Set_SocketInfo				(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	// ?�로그램 ?�작 ???�?�된 ?�켓 ?�보 ?�정//
	void    Set_Stored_SocketInfo		(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);

	void	SetPtr_LineInfo				(__in const CLineInfo* IN_pConfigLine);

	void	SetPtr_DebugMode			(__in const ST_DebugInfo* IN_pDebugInfo);

	// MES Rework NG Code
	void	Set_MES_ReworkCode			(__in int16_t IN_nReworkCode);
	int16_t	Get_MES_ReworkCode			() const;

protected:

	// 로더 ?�입?�간//
	void	Set_InputTime				(__in LPCTSTR IN_szRFID);
	// ?�로??배출 ?�간//
	void	Set_OutputTime				(__in LPCTSTR IN_szRFID);

	// ?�켓???�품 바코???�정//
	void	Set_Barcode					(__in LPCTSTR IN_szRFID, __in LPCTSTR IN_szBarcode, __in bool IN_bRework = false);	
	
	// ?�켓???�태 ?�정//
	void	Set_Status					(__in LPCTSTR IN_szRFID, __in uint8_t IN_nStatus);
	
	// ?�품??최종 ??�??�정//
	void	Set_Judgment_Final			(__in LPCTSTR IN_szRFID, __in uint8_t IN_nJudge);

	// ?�켓???�는 ?�비 ?�정//
	void	Set_Equipment				(__in LPCTSTR IN_szRFID, __in LPCTSTR IN_szEqpID);
	
	// ?�비?�의 ?�켓 ?�치 (Port, Conveyor) ?�정 가?�하�?.
	void	Set_Location				(__in LPCTSTR IN_szRFID, __in LPCTSTR IN_szEqpID, __in uint8_t IN_nLocation);
	
	// ?�켓??목적 ?�비 ?�정//
	void	Set_TargetEquipment			(__in LPCTSTR IN_szRFID, __in uint8_t IN_nEqpOrder, __in LPCTSTR IN_szEqpID);
	
	// ?�품??검?�별 결과 ?�정//
	void	Set_Judgment_Tester			(__in LPCTSTR IN_szRFID, __in uint8_t IN_nTester, __in uint8_t IN_nJudge);

	void	Reset_Socket_Yield			(__in LPCTSTR szRFID);
	void	Reset_Socket_Yield_All		();

	

public:
	// ?�신 ?�벤??처리 --------------------------------------------------------
	// ?�켓 ?�입 가???//
	bool	Is_ExistSocket				(__in LPCTSTR IN_szRFID);
	bool	Verify_Socket				(__in LPCTSTR IN_szRFID);
	bool	Register_Socket				(__in LPCTSTR IN_FromEqpID, __in LPCTSTR IN_szRFID, __in LPCTSTR IN_szBarcode);
	bool	Unregister_Socket			(__in LPCTSTR IN_FromEqpID, __in LPCTSTR IN_szRFID);
	bool	Get_TestResult				(__in LPCTSTR IN_szRFID, __out ST_TestResult& OUT_stTestResult);
	void	Check_UnloadTime			(__in LPCTSTR IN_szRFID);
	//bool	Get_TestResult				(__in LPCTSTR IN_FromEqpID, __in LPCTSTR IN_szRFID, __out ST_TestResult& OUT_stTestResult);	
	bool	Set_TestResult				(__in LPCTSTR IN_FromEqpID, __in LPCTSTR IN_szRFID, __in int16_t IN_nNGCode, __in uint8_t IN_nPara, __in uint8_t IN_nNG_EqpOrder, __in uint8_t IN_nNG_EqpType, __in bool IN_bRework = false);
	bool	Set_TestResult				(__in LPCTSTR IN_FromEqpID, __in LPCTSTR IN_szRFID, __in const ST_TestResult* IN_pstTestResult, __in bool IN_bRework = false);
	
	void	Set_SocketLocation			(__in LPCTSTR IN_szRFID, __in LPCTSTR IN_szEqpID, __in uint8_t IN_nLocation);
	void	Set_SocketTarget			(__in LPCTSTR IN_szRFID, __in uint8_t IN_nEqpOrder, __in LPCTSTR IN_szEqpID);

	// ?�켓 ?�이??초기??/
	void	Reset_RegisterData			(__in LPCTSTR IN_szRFID);
	void	Reset_RegisterData_All		();
	void	Reset_TestResult			(__in LPCTSTR IN_szRFID);
	void	Reset_Yield					(__in LPCTSTR IN_szRFID);
	void	Reset_Yield_All				();
	
	// ?�켓 결과 Log//
	bool	Write_CSV_File				(__in LPCTSTR IN_szPath);
	
#if (USE_XML)
protected:
	void	Set_LOTID					(__in LPCTSTR IN_szRFID, __in LPCTSTR IN_szData);
	bool	Save_SocketInfo_LOTID		(__in LPCTSTR IN_szRFID);
public:
	bool	Is_ExistBarcode				(__in LPCTSTR IN_szBarcode);
	bool	Register_SocketLotID		(__in LPCTSTR IN_szRFID, __in uint32_t IN_TYPE, __in LPCTSTR IN_szData);
#endif
};

#endif // SocketMonitoring_h__
