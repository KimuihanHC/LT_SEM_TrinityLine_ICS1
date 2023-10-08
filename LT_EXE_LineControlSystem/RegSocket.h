//*****************************************************************************
// Filename	: 	RegSocket.h
// Created	:	2021/12/21 - 13:45
// Modified	:	2021/12/21 - 13:45
//
// Author	:	piring
//	
// Purpose	:	 
//*****************************************************************************
#ifndef RegSocket_h__
#define RegSocket_h__


#pragma once

#include "Def_Socket_Info.h"

class CSocketMonitoring;

//-----------------------------------------------------------------------------
// CRegSocket
//-----------------------------------------------------------------------------
class CRegSocket
{
public:
	CRegSocket();
	CRegSocket(__in LPCTSTR lpszRegPath);
	~CRegSocket();

protected:
	CString		m_szRegPath;

public:
	void	Set_RegitryPath				(__in LPCTSTR lpszRegPath);

	// ?��??�트�??�스 체크?�여 ?�으�??�성
	bool	Check_RegistryPath			(__in LPCTSTR IN_szRFID);
	bool	Check_RegistryPath			(__in const CSocketMonitoring* IN_SocketInto);

	// ?��??�트리에 ?�켓?�보 ?�??/
	bool	Set_SocketInfo				(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_Barcode		(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_Status		(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_Equipment	(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_Location		(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_Target		(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_Yield		(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_TestResult	(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_InputTime	(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
	bool	Set_SocketInfo_OutputTime	(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);


	// ?��??�트리에 ?�?�된 ?�켓 ?�보 가?�오�?/
	bool	Get_SocketInfo				(__in LPCTSTR IN_szRFID, __out CSocketInfo_Unit& OUT_SocketInto);
	bool	Get_SocketInfo				(__out CSocketMonitoring& OUT_SocketInto);

#if (USE_XML)
	bool	Set_SocketInfo_LOTID		(__in LPCTSTR IN_szRFID, __in const CSocketInfo_Unit* IN_pSocketInfo);
#endif
};


#endif // RegSocket_h__
