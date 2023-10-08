//*****************************************************************************
// Filename	: 	RegEquipment.cpp
// Created	:	2021/12/21 - 13:46
// Modified	:	2021/12/21 - 13:46
//
// Author	:	piring
//	
// Purpose	:	 
//*****************************************************************************
#include "stdafx.h"
#include "RegServer.h"
#include "Def_Socket_Info.h"
#include "SocketMonitoring.h"
#include "Server.h"
#include "Registry.h"

CRegServer::CRegServer()
{
	m_szRegPath.Format(_T("%s\\ServerInfo"), REG_PATH_APP_BASE);
	m_szRegModulePath = m_szRegPath;
}
CRegServer::CRegServer(__in LPCTSTR lpszRegPath)
{
	m_szRegPath.Format(_T("%s\\ServerInfo"), lpszRegPath);
	m_szRegModulePath = m_szRegPath;
}
CRegServer::~CRegServer()
{

}

//=============================================================================
// Method		: Set_RegistryPath
// Access		: public  
// Returns		: void
// Parameter	: __in LPCTSTR lpszRegPath
// Qualifier	:
// Last Update	: 2022/1/10 - 18:10
// Desc.		:
//=============================================================================
void CRegServer::Set_RegistryPath(__in LPCTSTR lpszRegPath)
{
	m_szRegPath.Format(_T("%s\\ServerInfo"), lpszRegPath);
}
CString CRegServer::Get_RegistryPath() const
{
	return m_szRegPath;
}
//=============================================================================
// Method		: Check_RegistryPath
// Access		: public  
// Returns		: bool
// Parameter	: __in LPCTSTR IN_szEqpID
// Qualifier	:
// Last Update	: 2022/8/12 - 10:47
// Desc.		:
//=============================================================================
bool CRegServer::Check_RegistryPath(__in LPCTSTR IN_szEqpID)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;

	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_szEqpID);

	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();

	delete m_pReg;
	return true;
}
#ifdef SOCKET
//=============================================================================
// Method		: Save_Equipment
// Access		: public  
// Returns		: bool
// Parameter	: __in const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2021/12/21 - 16:15
// Desc.		:
//=============================================================================
bool CRegServer::Save_Equipment(__in const CServer* IN_pEquipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	DWORD		dwValue = 0;
	
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// Base
		//-------------------------------------------------------
		// 	bool		m_bSkip				= false;	// ?�비 Skip ?��?
		m_pReg->WriteDWORD(_T("Skip"), IN_pEquipment->Get_Skip() ? 1 : 0);

		// uint8_t		m_nReservedPortCnt	= 0;
		m_pReg->WriteDWORD(_T("ReservedPortCnt"), IN_pEquipment->Get_ReservedPortCnt());
	
		//-------------------------------------------------------
		// 	std::vector<ST_PortStatus>		m_nPortStatus;
		//-------------------------------------------------------

		for (auto nIdx = 0; nIdx < IN_pEquipment->Get_PortCount(); ++nIdx)
		{
			szKey.Format(_T("Port_%02d_Status"), nIdx);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_PortStatus(nIdx).nStatus);

			szKey.Format(_T("Port_%02d_RFID"), nIdx);
			szValue = IN_pEquipment->Get_PortStatus(nIdx).szRfid;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());

			szKey.Format(_T("Port_%02d_Barcode"), nIdx);
			szValue = IN_pEquipment->Get_PortStatus(nIdx).szBarcode;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());
		}

		//-------------------------------------------------------
		// 	std::vector<ST_ConveyorStatus>	m_nConveyorStatus;
		//-------------------------------------------------------
		for (auto nIdx = 0; nIdx < IN_pEquipment->Get_ConveyorCount(); ++nIdx)
		{
			szKey.Format(_T("Conveyor_%02d_Status"), nIdx);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_ConveyorStatus(nIdx).nStatus);

			szKey.Format(_T("Conveyor_%02d_ExistSocket"), nIdx);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_ConveyorStatus(nIdx).nExistSocket);

			szKey.Format(_T("Conveyor_%02d_RFID"), nIdx);			
			szValue = IN_pEquipment->Get_ConveyorStatus(nIdx).szRfid;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());

			szKey.Format(_T("Conveyor_%02d_Barcode"), nIdx);			
			szValue = IN_pEquipment->Get_ConveyorStatus(nIdx).szBarcode;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());
		}

		//-------------------------------------------------------
		// Alarm
		//-------------------------------------------------------
		// 	uint32_t	m_nAlarmCode		= 0;
		//m_pReg->WriteDWORD(_T("AlarmCode"), IN_pEquipment->m_nAlarmCode);

		// 	CString		m_szAlarmInfo;
		//szValue = IN_pEquipment->m_szAlarmInfo;
		//m_pReg->WriteString(_T("AlarmInfo"), szValue.GetBuffer());

		// 	std::vector<ST_AlarmStatus>		m_nAlarmStatus;
		m_pReg->WriteDWORD(_T("Alarm_Count"), static_cast<DWORD>(IN_pEquipment->Get_AlarmCount()));
		for (auto nIdx = 0; nIdx < IN_pEquipment->Get_AlarmCount(); ++nIdx)
		{
			// uint32_t	m_nAlarmCode = 0;
			szKey.Format(_T("Alarm_%02d_Code"), nIdx);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_AlarmStatus(nIdx).m_nAlarmCode);

			// CString	m_szAlarmInfo;
			szKey.Format(_T("Alarm_%02d_Info"), nIdx);
			szValue = IN_pEquipment->Get_AlarmStatus(nIdx).m_szAlarmInfo;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());
		}

		//-------------------------------------------------------
		// Yield
		//-------------------------------------------------------

		// CYield_Equipment		m_Yield_Day;		// ?�루�??�율 (Sifht 변�????�동 초기??
		//IN_pEquipment->Get_Yield_Day().dwTotal;
		m_pReg->WriteDWORD(_T("Yield_Day_Total"), IN_pEquipment->Get_Yield_Day().dwTotal);

		//IN_pEquipment->Get_Yield_Day().dwPass;
		m_pReg->WriteDWORD(_T("Yield_Day_Pass"), IN_pEquipment->Get_Yield_Day().dwPass);

		//IN_pEquipment->Get_Yield_Day().dwFail;
		m_pReg->WriteDWORD(_T("Yield_Day_Fail"), IN_pEquipment->Get_Yield_Day().dwFail);

		for (auto nPara = 0; nPara < enEqpPara::Para_MaxCount; ++nPara)
		{
			//IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwTotal;
			szKey.Format(_T("Yield_Day_Para_%02d_Total"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwTotal);

			//IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwPass;
			szKey.Format(_T("Yield_Day_Para_%02d_Pass"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwPass);

			//IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwFail;
			szKey.Format(_T("Yield_Day_Para_%02d_Fail"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwFail);
		}

		// CYield_Equipment		m_Yield_Cumulative;	// ?�적 ?�율 (?�동 초기??
		//IN_pEquipment->Get_Yield_Cumulative().dwTotal;
		m_pReg->WriteDWORD(_T("Yield_Cumulative_Total"), IN_pEquipment->Get_Yield_Cumulative().dwTotal);

		//IN_pEquipment->Get_Yield_Cumulative().dwPass;
		m_pReg->WriteDWORD(_T("Yield_Cumulative_Pass"), IN_pEquipment->Get_Yield_Cumulative().dwPass);

		//IN_pEquipment->Get_Yield_Cumulative().dwFail;
		m_pReg->WriteDWORD(_T("Yield_Cumulative_Fail"), IN_pEquipment->Get_Yield_Cumulative().dwFail);

		for (auto nPara = 0; nPara < enEqpPara::Para_MaxCount; ++nPara)
		{
			//IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwTotal;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Total"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwTotal);

			//IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwPass;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Pass"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwPass);

			//IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwFail;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Fail"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwFail);
		}
		// SYSTEMTIME		m_tm_CheckShift;	// ?�전 8??체크
		szValue = SystemTimeToFormatString(IN_pEquipment->Get_CheckShiftTime());
		m_pReg->WriteString(_T("Shift_CheckTime"), szValue.GetBuffer());
		//FormatStringToSystemTime();
		

	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Set_Equipment_Skip
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2022/8/12 - 12:02
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Skip(const CServer * IN_pEquipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// Base
		//-------------------------------------------------------
		// 	bool		m_bSkip				= false;	// ?�비 Skip ?��?
		m_pReg->WriteDWORD(_T("Skip"), IN_pEquipment->Get_Skip() ? 1 : 0);
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}
#endif //SOCKET
//=============================================================================
// Method		: Set_Equipment_Reserve
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2022/8/12 - 12:02
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Reserve(const CServer * IN_pEquipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// Base
		//-------------------------------------------------------
		// uint8_t		m_nReservedPortCnt	= 0;
		m_pReg->WriteDWORD(_T("ReservedPortCnt"), IN_pEquipment->Get_ReservedPortCnt());

		// uint8_t		m_nReservedOvered	= 0;
		m_pReg->WriteDWORD(_T("ReservedOvered"), IN_pEquipment->Get_ReservedOverCnt());
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}
#if SOCKET
//=============================================================================
// Method		: Set_Equipment_EndProduction
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2022/8/12 - 12:03
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_EndProduction(const CServer * IN_pEquipment)
{

	return true;
}

//=============================================================================
// Method		: Set_Equipment_Shift
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2022/8/12 - 12:03
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Shift(const CServer * IN_pEquipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		// SYSTEMTIME		m_tm_CheckShift;	// ?�전 8??체크
		szValue = SystemTimeToFormatString(IN_pEquipment->Get_CheckShiftTime());
		m_pReg->WriteString(_T("Shift_CheckTime"), szValue.GetBuffer());
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Set_Equipment_Port
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2022/8/12 - 12:03
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Port(const CServer * IN_pEquipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// 	std::vector<ST_PortStatus>		m_nPortStatus;
		//-------------------------------------------------------

		for (auto nIdx = 0; nIdx < IN_pEquipment->Get_PortCount(); ++nIdx)
		{
			szKey.Format(_T("Port_%02d_Status"), nIdx);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_PortStatus(nIdx).nStatus);

			szKey.Format(_T("Port_%02d_RFID"), nIdx);
			szValue = IN_pEquipment->Get_PortStatus(nIdx).szRfid;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());

			szKey.Format(_T("Port_%02d_Barcode"), nIdx);
			szValue = IN_pEquipment->Get_PortStatus(nIdx).szBarcode;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());
		}
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Set_Equipment_Port
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Parameter	: uint8_t IN_nPortIndex
// Qualifier	:
// Last Update	: 2022/8/12 - 12:03
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Port(const CServer * IN_pEquipment, uint8_t IN_nPortIndex)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// 	std::vector<ST_PortStatus>		m_nPortStatus;
		//-------------------------------------------------------

		szKey.Format(_T("Port_%02d_Status"), IN_nPortIndex);
		m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_PortStatus(IN_nPortIndex).nStatus);

		szKey.Format(_T("Port_%02d_RFID"), IN_nPortIndex);
		szValue = IN_pEquipment->Get_PortStatus(IN_nPortIndex).szRfid;
		m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());

		szKey.Format(_T("Port_%02d_Barcode"), IN_nPortIndex);
		szValue = IN_pEquipment->Get_PortStatus(IN_nPortIndex).szBarcode;
		m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());

	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Set_Equipment_Conveyor
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2022/8/12 - 12:03
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Conveyor(const CServer * IN_pEquipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// 	std::vector<ST_ConveyorStatus>	m_nConveyorStatus;
		//-------------------------------------------------------

		for (auto nIdx = 0; nIdx < IN_pEquipment->Get_ConveyorCount(); ++nIdx)
		{
			szKey.Format(_T("Conveyor_%02d_Status"), nIdx);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_ConveyorStatus(nIdx).nStatus);

			szKey.Format(_T("Conveyor_%02d_ExistSocket"), nIdx);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_ConveyorStatus(nIdx).nExistSocket);

			szKey.Format(_T("Conveyor_%02d_RFID"), nIdx);
			szValue = IN_pEquipment->Get_ConveyorStatus(nIdx).szRfid;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());

			szKey.Format(_T("Conveyor_%02d_Barcode"), nIdx);
			szValue = IN_pEquipment->Get_ConveyorStatus(nIdx).szBarcode;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());
		}
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Set_Equipment_Conveyor
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Parameter	: uint8_t IN_ConveyorIndex
// Qualifier	:
// Last Update	: 2022/8/12 - 12:03
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Conveyor(const CServer * IN_pEquipment, uint8_t IN_ConveyorIndex)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// 	std::vector<ST_ConveyorStatus>	m_nConveyorStatus;
		//-------------------------------------------------------

		szKey.Format(_T("Conveyor_%02d_Status"), IN_ConveyorIndex);
		m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_ConveyorStatus(IN_ConveyorIndex).nStatus);

		szKey.Format(_T("Conveyor_%02d_ExistSocket"), IN_ConveyorIndex);
		m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_ConveyorStatus(IN_ConveyorIndex).nExistSocket);

		szKey.Format(_T("Conveyor_%02d_RFID"), IN_ConveyorIndex);
		szValue = IN_pEquipment->Get_ConveyorStatus(IN_ConveyorIndex).szRfid;
		m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());

		szKey.Format(_T("Conveyor_%02d_Barcode"), IN_ConveyorIndex);
		szValue = IN_pEquipment->Get_ConveyorStatus(IN_ConveyorIndex).szBarcode;
		m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Set_Equipment_Alarm
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2022/8/12 - 12:03
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Alarm(const CServer * IN_pEquipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// Alarm
		//-------------------------------------------------------
		// 	uint32_t	m_nAlarmCode		= 0;
		//m_pReg->WriteDWORD(_T("AlarmCode"), IN_pEquipment->m_nAlarmCode);

		// 	CString		m_szAlarmInfo;
		//szValue = IN_pEquipment->m_szAlarmInfo;
		//m_pReg->WriteString(_T("AlarmInfo"), szValue.GetBuffer());

		// 	std::vector<ST_AlarmStatus>		m_nAlarmStatus;
		m_pReg->WriteDWORD(_T("Alarm_Count"), static_cast<DWORD>(IN_pEquipment->Get_AlarmCount()));
		for (auto nIdx = 0; nIdx < IN_pEquipment->Get_AlarmCount(); ++nIdx)
		{
			// uint32_t	m_nAlarmCode = 0;
			szKey.Format(_T("Alarm_%02d_Code"), nIdx);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_AlarmStatus(nIdx).m_nAlarmCode);

			// CString	m_szAlarmInfo;
			szKey.Format(_T("Alarm_%02d_Info"), nIdx);
			szValue = IN_pEquipment->Get_AlarmStatus(nIdx).m_szAlarmInfo;
			m_pReg->WriteString(szKey.GetBuffer(), szValue.GetBuffer());
		}
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Set_Equipment_Yield
// Access		: public  
// Returns		: bool
// Parameter	: const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 2022/8/12 - 12:03
// Desc.		:
//=============================================================================
bool CRegServer::Set_Equipment_Yield(const CServer * IN_pEquipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pEquipment->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// Yield
		//-------------------------------------------------------
		// CYield_Equipment		m_Yield_Day;		// ?�루�??�율 (Sifht 변�????�동 초기??
		//IN_pEquipment->Get_Yield_Day().dwTotal;
		m_pReg->WriteDWORD(_T("Yield_Day_Total"), IN_pEquipment->Get_Yield_Day().dwTotal);

		//IN_pEquipment->Get_Yield_Day().dwPass;
		m_pReg->WriteDWORD(_T("Yield_Day_Pass"), IN_pEquipment->Get_Yield_Day().dwPass);

		//IN_pEquipment->Get_Yield_Day().dwFail;
		m_pReg->WriteDWORD(_T("Yield_Day_Fail"), IN_pEquipment->Get_Yield_Day().dwFail);

		for (auto nPara = 0; nPara < enEqpPara::Para_MaxCount; ++nPara)
		{
			//IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwTotal;
			szKey.Format(_T("Yield_Day_Para_%02d_Total"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwTotal);

			//IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwPass;
			szKey.Format(_T("Yield_Day_Para_%02d_Pass"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwPass);

			//IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwFail;
			szKey.Format(_T("Yield_Day_Para_%02d_Fail"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Day().m_Para[nPara].dwFail);
		}

		// CYield_Equipment		m_Yield_Cumulative;	// ?�적 ?�율 (?�동 초기??
		//IN_pEquipment->Get_Yield_Cumulative().dwTotal;
		m_pReg->WriteDWORD(_T("Yield_Cumulative_Total"), IN_pEquipment->Get_Yield_Cumulative().dwTotal);

		//IN_pEquipment->Get_Yield_Cumulative().dwPass;
		m_pReg->WriteDWORD(_T("Yield_Cumulative_Pass"), IN_pEquipment->Get_Yield_Cumulative().dwPass);

		//IN_pEquipment->Get_Yield_Cumulative().dwFail;
		m_pReg->WriteDWORD(_T("Yield_Cumulative_Fail"), IN_pEquipment->Get_Yield_Cumulative().dwFail);

		for (auto nPara = 0; nPara < enEqpPara::Para_MaxCount; ++nPara)
		{
			//IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwTotal;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Total"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwTotal);

			//IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwPass;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Pass"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwPass);

			//IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwFail;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Fail"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), IN_pEquipment->Get_Yield_Cumulative().m_Para[nPara].dwFail);
		}
		// SYSTEMTIME		m_tm_CheckShift;	// ?�전 8??체크
		szValue = SystemTimeToFormatString(IN_pEquipment->Get_CheckShiftTime());
		m_pReg->WriteString(_T("Shift_CheckTime"), szValue.GetBuffer());
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Load_Equipment
// Access		: public  
// Returns		: bool
// Parameter	: __in LPCTSTR IN_szEqpID
// Parameter	: __out CEquipment & OUT_Equipment
// Qualifier	:
// Last Update	: 2021/12/21 - 16:15
// Desc.		:
//=============================================================================
bool CRegServer::Load_Equipment(__in LPCTSTR IN_szEqpID, __out CServer& OUT_Equipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;	
	DWORD		dwValue = 0;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_szEqpID);

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// Base
		//-------------------------------------------------------
		// 	bool		m_bSkip				= false;	// ?�비 Skip ?��?
		if (m_pReg->ReadDWORD(_T("Skip"), dwValue))
 			OUT_Equipment.Set_Skip(dwValue ? true : false, false);
 		else
 			OUT_Equipment.Set_Skip(false, false);

		// uint8_t		m_nReservedPortCnt	= 0;
		if (m_pReg->ReadDWORD(_T("ReservedPortCnt"), dwValue))
			OUT_Equipment.Set_ReservedPortCnt(static_cast<uint8_t>(dwValue), false);
		else
			OUT_Equipment.Set_ReservedPortCnt(0, false);

		// uint8_t		m_nReservedOvered	= 0;
		if (m_pReg->ReadDWORD(_T("ReservedOvered"), dwValue))
			OUT_Equipment.Set_ReservedOverCnt(static_cast<uint8_t>(dwValue));
		else
			OUT_Equipment.Set_ReservedOverCnt(0);

		//-------------------------------------------------------
		// 	std::vector<ST_PortStatus>		m_nPortStatus;
		//-------------------------------------------------------
		for (auto nIdx = 0; nIdx < OUT_Equipment.Get_PortCount(); ++nIdx)
		{
			ST_PortStatus newPort;

			szKey.Format(_T("Port_%02d_Status"), nIdx);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				newPort.nStatus = static_cast<uint8_t>(dwValue);
			else
				newPort.nStatus = 0;

			szKey.Format(_T("Port_%02d_RFID"), nIdx);
			if (m_pReg->ReadString(szKey.GetBuffer(), szValue))
				newPort.szRfid = szValue.GetBuffer();
			else
				newPort.szRfid.Empty();

			szKey.Format(_T("Port_%02d_Barcode"), nIdx);
			if (m_pReg->ReadString(szKey.GetBuffer(), szValue))
				newPort.szBarcode = szValue.GetBuffer();
			else
				newPort.szBarcode.Empty();

			OUT_Equipment.Set_PortStatus(nIdx, newPort.nStatus, newPort.szRfid.GetBuffer(), newPort.szBarcode.GetBuffer(), false);
		}

		//-------------------------------------------------------
		// 	std::vector<ST_ConveyorStatus>	m_nConveyorStatus;
		//-------------------------------------------------------
		for (auto nIdx = 0; nIdx < OUT_Equipment.Get_ConveyorCount(); ++nIdx)
		{
			ST_ConveyorStatus newConveyor;

			szKey.Format(_T("Conveyor_%02d_Status"), nIdx);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				newConveyor.nStatus = static_cast<uint8_t>(dwValue);
			else
				newConveyor.nStatus = 0;

			szKey.Format(_T("Conveyor_%02d_ExistSocket"), nIdx);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				newConveyor.nExistSocket = static_cast<uint8_t>(dwValue);
			else
				newConveyor.nExistSocket = 0;

			szKey.Format(_T("Conveyor_%02d_RFID"), nIdx);
			if (m_pReg->ReadString(szKey.GetBuffer(), szValue))
				newConveyor.szRfid = szValue.GetBuffer();
			else
				newConveyor.szRfid.Empty();

			szKey.Format(_T("Conveyor_%02d_Barcode"), nIdx);
			if (m_pReg->ReadString(szKey.GetBuffer(), szValue))
				newConveyor.szBarcode = szValue.GetBuffer();
			else
				newConveyor.szBarcode.Empty();

			OUT_Equipment.Set_ConveyorStatus(nIdx, newConveyor.nStatus, newConveyor.nExistSocket, newConveyor.szRfid, newConveyor.szBarcode, false);
		}
		//-------------------------------------------------------
		// Alarm
		//-------------------------------------------------------
		DWORD dwCount = 0;
		if (m_pReg->ReadDWORD(_T("Alarm_Count"), dwValue))
			dwCount = dwValue;
		
		for (DWORD nIdx = 0; nIdx < dwCount; ++nIdx)
		{
			ST_AlarmStatus newAlarm;

			// uint32_t	m_nAlarmCode = 0;
			szKey.Format(_T("Alarm_%02d_Code"), nIdx);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				newAlarm.m_nAlarmCode = static_cast<uint8_t>(dwValue);
			else
				newAlarm.m_nAlarmCode = 0;

			// CString	m_szAlarmInfo;
			szKey.Format(_T("Alarm_%02d_Info"), nIdx);
			if (m_pReg->ReadString(szKey.GetBuffer(), szValue))
				newAlarm.m_szAlarmInfo = szValue.GetBuffer();
			else
				newAlarm.m_szAlarmInfo.Empty();

			OUT_Equipment.Get_AlarmStatus().push_back(newAlarm);
		}

		/*if (0 < dwCount)
		{
			OUT_Equipment.Set_AlarmStatus_Last(OUT_Equipment.Get_AlarmStatus().back().m_nAlarmCode, OUT_Equipment.Get_AlarmStatus().back().m_szAlarmInfo.GetBuffer());
		}*/

		//-------------------------------------------------------
		// Yield
		//-------------------------------------------------------
		// CYield_Equipment		m_Yield_Day;		// ?�루�??�율 (Sifht 변�????�동 초기??
		CYield_Equipment		Yield_Day;
		//OUT_Equipment.Get_Yield_Day().dwTotal;
		if (m_pReg->ReadDWORD(_T("Yield_Day_Total"), dwValue))
			Yield_Day.dwTotal = dwValue;
		else
			Yield_Day.dwTotal = 0;

		//OUT_Equipment.Get_Yield_Day().dwPass;
		if (m_pReg->ReadDWORD(_T("Yield_Day_Pass"), dwValue))
			Yield_Day.dwPass = dwValue;
		else
			Yield_Day.dwPass = 0;

		//OUT_Equipment.Get_Yield_Day().dwFail;
		if (m_pReg->ReadDWORD(_T("Yield_Day_Fail"), dwValue))
			Yield_Day.dwFail = dwValue;
		else
			Yield_Day.dwFail = 0;

		for (auto nPara = 0; nPara < enEqpPara::Para_MaxCount; ++nPara)
		{
			//OUT_Equipment.Get_Yield_Day().m_Para[nPara].dwTotal;
			szKey.Format(_T("Yield_Day_Para_%02d_Total"), nPara);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Day.m_Para[nPara].dwTotal = dwValue;
			else
				Yield_Day.m_Para[nPara].dwTotal = 0;

			//OUT_Equipment.Get_Yield_Day().m_Para[nPara].dwPass;
			szKey.Format(_T("Yield_Day_Para_%02d_Pass"), nPara);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Day.m_Para[nPara].dwPass = dwValue;
			else
				Yield_Day.m_Para[nPara].dwPass = 0;

			//OUT_Equipment.Get_Yield_Day().m_Para[nPara].dwFail;
			szKey.Format(_T("Yield_Day_Para_%02d_Fail"), nPara);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Day.m_Para[nPara].dwFail = dwValue;
			else
				Yield_Day.m_Para[nPara].dwFail = 0;
		}

		OUT_Equipment.Set_Yield_Day(&Yield_Day);


		// CYield_Equipment		m_Yield_Cumulative;	// ?�적 ?�율 (?�동 초기??
		CYield_Equipment		Yield_Cumulative;
		//OUT_Equipment.Get_Yield_Cumulative().dwTotal;
		if (m_pReg->ReadDWORD(_T("Yield_Cumulative_Total"), dwValue))
			Yield_Cumulative.dwTotal = dwValue;
		else
			Yield_Cumulative.dwTotal = 0;

		//OUT_Equipment.Get_Yield_Cumulative().dwPass;
		if (m_pReg->ReadDWORD(_T("Yield_Cumulative_Pass"), dwValue))
			Yield_Cumulative.dwPass = dwValue;
		else
			Yield_Cumulative.dwPass = 0;

		//OUT_Equipment.Get_Yield_Cumulative().dwFail;
		if (m_pReg->ReadDWORD(_T("Yield_Cumulative_Fail"), dwValue))
			Yield_Cumulative.dwFail = dwValue;
		else
			Yield_Cumulative.dwFail = 0;

		for (auto nPara = 0; nPara < enEqpPara::Para_MaxCount; ++nPara)
		{
			//OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwTotal;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Total"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwTotal);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Cumulative.m_Para[nPara].dwTotal = dwValue;
			else
				Yield_Cumulative.m_Para[nPara].dwTotal = 0;

			//OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwPass;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Pass"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwPass);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Cumulative.m_Para[nPara].dwPass = dwValue;
			else
				Yield_Cumulative.m_Para[nPara].dwPass = 0;

			//OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwFail;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Fail"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwFail);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Cumulative.m_Para[nPara].dwFail = dwValue;
			else
				Yield_Cumulative.m_Para[nPara].dwFail = 0;
		}
		
		OUT_Equipment.Set_Yield_Cumulative(&Yield_Cumulative);

		// SYSTEMTIME		m_tm_CheckShift;	// ?�전 8??체크
		if (m_pReg->ReadString(_T("Shift_CheckTime"), szValue))
		{
			SYSTEMTIME tmCheck;
			FormatStringToSystemTime(szValue.GetBuffer(), tmCheck);
			OUT_Equipment.Set_CheckShiftTime(&tmCheck, false);
		}
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Load_Yield
// Access		: public  
// Returns		: bool
// Parameter	: LPCTSTR IN_szEqpID
// Parameter	: CEquipment & OUT_Equipment
// Qualifier	:
// Last Update	: 2022/8/11 - 19:52
// Desc.		:
//=============================================================================
bool CRegServer::Load_Yield(LPCTSTR IN_szEqpID, CServer & OUT_Equipment)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	DWORD		dwValue = 0;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_szEqpID);

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// Yield
		//-------------------------------------------------------
		// CYield_Equipment		m_Yield_Day;		// ?�루�??�율 (Sifht 변�????�동 초기??
		CYield_Equipment		Yield_Day;
		//OUT_Equipment.Get_Yield_Day().dwTotal;
		if (m_pReg->ReadDWORD(_T("Yield_Day_Total"), dwValue))
			Yield_Day.dwTotal = dwValue;
		else
			Yield_Day.dwTotal = 0;

		//OUT_Equipment.Get_Yield_Day().dwPass;
		if (m_pReg->ReadDWORD(_T("Yield_Day_Pass"), dwValue))
			Yield_Day.dwPass = dwValue;
		else
			Yield_Day.dwPass = 0;

		//OUT_Equipment.Get_Yield_Day().dwFail;
		if (m_pReg->ReadDWORD(_T("Yield_Day_Fail"), dwValue))
			Yield_Day.dwFail = dwValue;
		else
			Yield_Day.dwFail = 0;

		for (auto nPara = 0; nPara < enEqpPara::Para_MaxCount; ++nPara)
		{
			//OUT_Equipment.Get_Yield_Day().m_Para[nPara].dwTotal;
			szKey.Format(_T("Yield_Day_Para_%02d_Total"), nPara);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Day.m_Para[nPara].dwTotal = dwValue;
			else
				Yield_Day.m_Para[nPara].dwTotal = 0;

			//OUT_Equipment.Get_Yield_Day().m_Para[nPara].dwPass;
			szKey.Format(_T("Yield_Day_Para_%02d_Pass"), nPara);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Day.m_Para[nPara].dwPass = dwValue;
			else
				Yield_Day.m_Para[nPara].dwPass = 0;

			//OUT_Equipment.Get_Yield_Day().m_Para[nPara].dwFail;
			szKey.Format(_T("Yield_Day_Para_%02d_Fail"), nPara);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Day.m_Para[nPara].dwFail = dwValue;
			else
				Yield_Day.m_Para[nPara].dwFail = 0;
		}

		OUT_Equipment.Set_Yield_Day(&Yield_Day);


		// CYield_Equipment		m_Yield_Cumulative;	// ?�적 ?�율 (?�동 초기??
		CYield_Equipment		Yield_Cumulative;
		//OUT_Equipment.Get_Yield_Cumulative().dwTotal;
		if (m_pReg->ReadDWORD(_T("Yield_Cumulative_Total"), dwValue))
			Yield_Cumulative.dwTotal = dwValue;
		else
			Yield_Cumulative.dwTotal = 0;

		//OUT_Equipment.Get_Yield_Cumulative().dwPass;
		if (m_pReg->ReadDWORD(_T("Yield_Cumulative_Pass"), dwValue))
			Yield_Cumulative.dwPass = dwValue;
		else
			Yield_Cumulative.dwPass = 0;

		//OUT_Equipment.Get_Yield_Cumulative().dwFail;
		if (m_pReg->ReadDWORD(_T("Yield_Cumulative_Fail"), dwValue))
			Yield_Cumulative.dwFail = dwValue;
		else
			Yield_Cumulative.dwFail = 0;

		for (auto nPara = 0; nPara < enEqpPara::Para_MaxCount; ++nPara)
		{
			//OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwTotal;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Total"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwTotal);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Cumulative.m_Para[nPara].dwTotal = dwValue;
			else
				Yield_Cumulative.m_Para[nPara].dwTotal = 0;

			//OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwPass;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Pass"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwPass);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Cumulative.m_Para[nPara].dwPass = dwValue;
			else
				Yield_Cumulative.m_Para[nPara].dwPass = 0;

			//OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwFail;
			szKey.Format(_T("Yield_Cumulative_Para_%02d_Fail"), nPara);
			m_pReg->WriteDWORD(szKey.GetBuffer(), OUT_Equipment.Get_Yield_Cumulative().m_Para[nPara].dwFail);
			if (m_pReg->ReadDWORD(szKey.GetBuffer(), dwValue))
				Yield_Cumulative.m_Para[nPara].dwFail = dwValue;
			else
				Yield_Cumulative.m_Para[nPara].dwFail = 0;
		}

		OUT_Equipment.Set_Yield_Cumulative(&Yield_Cumulative);

		// SYSTEMTIME		m_tm_CheckShift;	// ?�전 8??체크
		if (m_pReg->ReadString(_T("Shift_CheckTime"), szValue))
		{
			SYSTEMTIME tmCheck;
			FormatStringToSystemTime(szValue.GetBuffer(), tmCheck);
			OUT_Equipment.Set_CheckShiftTime(&tmCheck, false);
		}
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}

//=============================================================================
// Method		: Save_Equipment_ID
// Access		: public  
// Returns		: bool
// Parameter	: __in const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 203.05.25
// Desc.		:
//=============================================================================
bool CRegServer::Save_Equipment_ID(__in const CServer* IN_pServer)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	DWORD		dwValue = 0;

	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_pServer->Get_ServerId());

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		m_pReg->WriteString(_T("SUBEQPID"), IN_pServer->Get_SubEqpID());

		for (auto nIdx = 0; nIdx < IN_pServer->Get_EquipmentIDCount(); ++nIdx)
		{
			szKey.Format(_T("Port_%02d_EquipID"), nIdx);
			m_pReg->WriteString(szKey.GetBuffer(), IN_pServer->Get_EquipmentIDStatus(nIdx).Get_EQUIPMENTID());

			szKey.Format(_T("Port_%02d_PortID"), nIdx);
			m_pReg->WriteString(szKey.GetBuffer(), IN_pServer->Get_EquipmentIDStatus(nIdx).Get_PORTID());
		}
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}
//=============================================================================
// Method		: Load_EquipmentID
// Access		: public  
// Returns		: bool
// Parameter	: __in LPCTSTR IN_szEqpID
// Parameter	: __out CEquipment & OUT_Equipment
// Qualifier	:
// Last Update	: 2023.05.25
// Desc.		:
//=============================================================================
bool CRegServer::Load_Equipment_ID(__in LPCTSTR IN_szEqpID, __out CServer& OUT_Server)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	DWORD		dwValue = 0;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_szEqpID);

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// 	std::vector<ST_PortStatus>		m_nPortStatus;
		//-------------------------------------------------------
		szKey.Format(_T("SUBEQPID"));
		if (m_pReg->ReadString(szKey.GetBuffer(), szValue)) {
			szValue.GetBuffer();
		}
		OUT_Server.Set_SubEqpID(szValue);

		for (auto nIdx = 0; nIdx < OUT_Server.Get_EquipmentIDCount(); ++nIdx)
		{
			ST_EquipmentID newEquipmentID;

			szKey.Format(_T("Port_%02d_EquipID"), nIdx);
			if (m_pReg->ReadString(szKey.GetBuffer(), szValue))
				newEquipmentID.Set_EQUIPMENTID(szValue.GetBuffer());
			else
				newEquipmentID.Set_EQUIPMENTID(_T(""));

			szKey.Format(_T("Port_%02d_PortID"), nIdx);
			if (m_pReg->ReadString(szKey.GetBuffer(), szValue))
				newEquipmentID.Set_PORTID(szValue.GetBuffer());
			else
				newEquipmentID.Set_PORTID(_T(""));

			OUT_Server.Set_PortStatusEquipmentIDEvent(nIdx, &newEquipmentID);
		}
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}
//=============================================================================
// Method		: Save_Equipment_ID
// Access		: public  
// Returns		: bool
// Parameter	: __in const CEquipment * IN_pEquipment
// Qualifier	:
// Last Update	: 203.05.25
// Desc.		:
//=============================================================================
bool CRegServer::Save_Equipment_ID(__in LPCTSTR IN_szEqpID, __in uint8_t IN_nPortIndex, __in uint8_t Type, LPCTSTR IN_Data)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	DWORD		dwValue = 0;

	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_szEqpID);

#ifdef USE_VERIFY_KEY_ALWAYS
	if (!m_pReg->VerifyKey(szRegPath))
	{
		m_pReg->CreateKey(HKEY_CURRENT_USER, szRegPath);
	}
	m_pReg->Close();
#endif

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		switch (Type) {
		case 0:
			m_pReg->WriteString(_T("SUBEQPID"), IN_Data);
			break;
		case 1:
			szKey.Format(_T("Port_%02d_EquipID"), IN_nPortIndex);
			m_pReg->WriteString(szKey.GetBuffer(), IN_Data);
			break;
		case 2:
			szKey.Format(_T("Port_%02d_PortID"), IN_nPortIndex);
			m_pReg->WriteString(szKey.GetBuffer(), IN_Data);
			break;
		}
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return true;
}
//=============================================================================
// Method		: Load_EquipmentID
// Access		: public  
// Returns		: bool
// Parameter	: __in LPCTSTR IN_szEqpID
// Parameter	: __out CEquipment & OUT_Equipment
// Qualifier	:
// Last Update	: 2023.05.25
// Desc.		:
//=============================================================================
CString CRegServer::Load_Equipment_ID(__in LPCTSTR IN_szEqpID, __in uint8_t IN_nPortIndex, __in uint8_t Type)
{
	CRegistry*	m_pReg = new CRegistry(HKEY_CURRENT_USER);
	CString		szRegPath;
	CString		szKey;
	CString		szValue;
	DWORD		dwValue = 0;
	szRegPath.Format(_T("%s\\%s"), m_szRegPath.GetBuffer(), IN_szEqpID);

	if (m_pReg->Open(HKEY_CURRENT_USER, szRegPath))
	{
		//-------------------------------------------------------
		// 	std::vector<ST_PortStatus>		m_nPortStatus;
		//-------------------------------------------------------
		switch (Type) {
		case  0:
			szKey.Format(_T("SUBEQPID"));
			break;
		case 1:
			szKey.Format(_T("Port_%02d_EquipID"), IN_nPortIndex);
			break;
		case 2:
			szKey.Format(_T("Port_%02d_PortID"), IN_nPortIndex);
			break;
		}
		m_pReg->ReadString(szKey.GetBuffer(), szValue);
	}
	else
	{
		delete m_pReg;
		return false;
	}

	m_pReg->Close();

	delete m_pReg;
	return szValue.GetBuffer();
}
#endif//SOCKET