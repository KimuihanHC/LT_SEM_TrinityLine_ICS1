//*****************************************************************************
// Filename	: 	Def_Socket_Info.h
// Created	:	2021/10/21 - 15:59
// Modified	:	2021/10/21 - 15:59
//
// Author	:	poiring
//	
// Purpose	:	 
//*****************************************************************************
#ifndef Def_Socket_Info_h__
#define Def_Socket_Info_h__


#pragma once

#include <map>
#include "Def_Socket_Config.h"
#include "Def_Yield.h"
#include "Def_Equipment_Type.h"
#include "Def_Constant.h"
#include "CommonFunction.h"

typedef struct _tag_TestResult
{
	int16_t		m_nNG_Code		= 0;	// NGCode (0 ?�면 ?�품)
	int8_t		m_nNG_Para		= 0;	// Fail Para (-1 ?�면 ?�품 or �?검??
	uint8_t		m_nNG_EqpOrder	= 0;	// Fail Equipment ?�서 (0 ?�면 ?�품 or �?검??
	CString		m_szNG_EqpID;			// Fail Equipment id (null ?�면 ?�품 or �?검??
	uint8_t		m_nNG_EqpType	= 0;	// Fail 발생???�비 종류 (Test 종류)//

	_tag_TestResult& operator= (const _tag_TestResult& ref)
	{
		m_nNG_Code		= ref.m_nNG_Code;
		m_nNG_Para		= ref.m_nNG_Para;
		m_nNG_EqpOrder	= ref.m_nNG_EqpOrder;
		m_szNG_EqpID	= ref.m_szNG_EqpID;
		m_nNG_EqpType	= ref.m_nNG_EqpType;
		return *this;
	};

	void Reset()
	{
		m_nNG_Code		= 0;
		m_nNG_Para		= 0;
		m_nNG_EqpOrder	= 0;
		m_szNG_EqpID.Empty();
		m_nNG_EqpType	= 0;
	}

}ST_TestResult;

//-----------------------------------------------------------------------------
// CSocketInfo Unit
//-----------------------------------------------------------------------------
class CSocketInfo_Unit : public CConfig_Socket
{
public:
	// ?�켓 ?�정
	//CString		szRFID;			// RFID 
	//uint8_t		nSocketType;	// Socket Type
	//CString		szComment;		// Comment

	// ?�품 ?�보
	CString			m_szBarcode;		// ?�품 바코??/
	uint8_t			m_nStatus;			// ?�켓 ?�태, ?�품 검???�정 (Pass, Fail, Bypass, ...)
	uint8_t			m_nJudgement[Max_TesterCount];		// ?�품 검?�별 ?�정 (Not Test, Pass, Fail)

	// ?�켓 ?�치 ?�보
	uint8_t			m_nEqpOrder;		// ?�비 ?�서
	CString			m_szEquipmentID;	// ?�비 id
	uint8_t			m_nPort_inEqp;		// ?�비 ?�의 ?�치 (Port, Conveyor) -> Port ?�선
	uint8_t			m_nTargetEqpOrder;	// 목적지 ?�비 ?�서
	CString			m_szTargetEqpID;	// 목적지 ?�비 id

	bool			m_bTargetFar;		// 목적 ?�비가 출발 ?�비?�서 멀�??�다.

	ST_TestResult	m_stTestResult;		// 검??결과
	CYield_Socket	m_Yield;			// ?�켓 ?�율
	SYSTEMTIME		m_tmLoad;			// ?�켓 ?�입 ?�간 (Loader)
	SYSTEMTIME		m_tmUnload;			// ?�켓 배출 ?�간 (Unloader)
	SYSTEMTIME		m_tmTrackIn;		// ?�비???�입???�간 (Tester)
	double			m_dCycleTime;		// Load -> Unload ?�간
	double			m_dTacttime;		// ?�전 ?�켓 배출?�간 -> ?�재 ?�켓 배출?�간

	bool			m_bRework;			// ?��??�하???�품?��??//
#if (USE_XML)
	CString			m_LotID;
#endif

	CSocketInfo_Unit()
	{
		m_nEqpOrder			= 0;
		m_nPort_inEqp		= 0;
		m_nTargetEqpOrder	= 0;
		m_bTargetFar		= false;

		m_nStatus			= 0;
		memset(m_nJudgement, 0, sizeof(uint8_t) * Max_TesterCount);

		memset(&m_tmLoad, 0, sizeof(SYSTEMTIME));
		memset(&m_tmUnload, 0, sizeof(SYSTEMTIME));
		memset(&m_tmTrackIn, 0, sizeof(SYSTEMTIME));
		m_dCycleTime		= 0.0f;
		m_dTacttime			= 0.0f;

		m_bRework			= false;
	};

	virtual ~CSocketInfo_Unit()
	{

	};

	CSocketInfo_Unit& operator= (const CConfig_Socket& ref)
	{
		CConfig_Socket::operator=(ref);

		return *this;
	};

	CSocketInfo_Unit& operator= (const CSocketInfo_Unit& ref)
	{
		CConfig_Socket::operator=(ref);

		m_szBarcode			= ref.m_szBarcode;
		m_nStatus			= ref.m_nStatus;
		memcpy(m_nJudgement,  ref.m_nJudgement, sizeof(uint8_t) * Max_TesterCount);
		m_nEqpOrder			= ref.m_nEqpOrder;
		m_szEquipmentID		= ref.m_szEquipmentID;
		m_nPort_inEqp		= ref.m_nPort_inEqp;
		m_nTargetEqpOrder	= ref.m_nTargetEqpOrder;
		m_szTargetEqpID		= ref.m_szTargetEqpID;

		m_stTestResult		= ref.m_stTestResult;

		m_Yield				= ref.m_Yield;
		memcpy(&m_tmLoad,    &ref.m_tmLoad, sizeof(SYSTEMTIME));
		memcpy(&m_tmUnload,  &ref.m_tmUnload, sizeof(SYSTEMTIME));
		memcpy(&m_tmTrackIn, &ref.m_tmTrackIn, sizeof(SYSTEMTIME));
		m_dCycleTime		= ref.m_dCycleTime;
		m_dTacttime			= ref.m_dTacttime;

		m_bRework			= ref.m_bRework;
#if (USE_XML)
		m_LotID				= ref.m_LotID;
#endif 
		return *this;
	};

	void Reset()
	{
		CConfig_Socket::Reset();

		m_szBarcode.Empty();
		m_nStatus			= 0;
		memset(m_nJudgement, 0, sizeof(uint8_t) * Max_TesterCount);
		m_nEqpOrder			= 0;
		m_szEquipmentID.Empty();
		m_nPort_inEqp		= 0;
		m_nTargetEqpOrder	= 0;
		m_szTargetEqpID.Empty();

		m_stTestResult.Reset();

		m_Yield.Reset();
		memset(&m_tmLoad, 0, sizeof(SYSTEMTIME));
		memset(&m_tmUnload, 0, sizeof(SYSTEMTIME));
		memset(&m_tmTrackIn, 0, sizeof(SYSTEMTIME));
		m_dCycleTime		= 0.0f;
		m_dTacttime			= 0.0f;

		m_bRework			= false;
#if (USE_XML)
		m_LotID.Empty();
#endif
	};

	void Reset_Yield()
	{
		m_Yield.Reset();
	};

	void Reset_TestResult()
	{
		m_stTestResult.Reset();
	}

	void Set_Barcode(__in LPCTSTR IN_szBarcode, __in bool IN_bRework = false)
	{
		m_szBarcode = IN_szBarcode;
		m_bRework	= IN_bRework;

		if (m_szBarcode.IsEmpty())
		{
			// ?�켓???�품???�으�?NG 처리?�다.
			m_stTestResult.m_nNG_Code = -2;
		}
	};

	void Reset_Barcode()
	{
		m_szBarcode.Empty();
	}

	bool IsEmpty_Barcode()
	{
		return m_szBarcode.IsEmpty();
	}



	void Set_Status(__in uint8_t IN_nStatus)
	{
		m_nStatus = IN_nStatus;
	};

	void Set_Judgment_Tester(__in uint8_t IN_nTester, uint8_t IN_nStatus)
	{
		if (IN_nTester < Max_TesterCount)
		{
			m_nJudgement[IN_nTester] = IN_nStatus;
		}
	};

	void Set_EquipmentOrder(__in uint8_t IN_nEqpOrder)
	{
		m_nEqpOrder = IN_nEqpOrder;
	};

	void Set_Equipment(__in LPCTSTR IN_szEqpID)
	{
		m_szEquipmentID = IN_szEqpID;
	};

	void Set_Location_inEqp(__in LPCTSTR IN_szEqpID, __in uint8_t IN_nLocation)
	{
		if (0 != m_szEquipmentID.Compare(IN_szEqpID))
		{
			m_szEquipmentID = IN_szEqpID;
		}

		m_nPort_inEqp = IN_nLocation;
	};

	void Set_TargetEquipment(__in LPCTSTR IN_szEqpID)
	{
		m_szTargetEqpID = IN_szEqpID;
	};

	void Set_TargetEqpOrder(__in uint8_t IN_nTargerEqpOrder)
	{
		m_nTargetEqpOrder = IN_nTargerEqpOrder;
	};

	void Set_TestResult(__in int16_t IN_nNGCode, __in uint8_t IN_nPara, __in uint8_t IN_nNG_EqpOrder, __in LPCTSTR IN_szNG_EqpID)
	{
		m_stTestResult.m_nNG_Code		= IN_nNGCode;
		m_stTestResult.m_nNG_Para		= IN_nPara;
		m_stTestResult.m_nNG_EqpOrder	= IN_nNG_EqpOrder;
		m_stTestResult.m_szNG_EqpID		= IN_szNG_EqpID;
	};

	void Set_TestResult(__in int16_t IN_nNGCode, __in uint8_t IN_nPara, __in uint8_t IN_nNG_EqpOrder, __in LPCTSTR IN_szNG_EqpID, __in uint8_t IN_nNG_EqpType)
	{
		m_stTestResult.m_nNG_Code		= IN_nNGCode;
		m_stTestResult.m_nNG_Para		= IN_nPara;
		m_stTestResult.m_nNG_EqpOrder	= IN_nNG_EqpOrder;
		m_stTestResult.m_szNG_EqpID		= IN_szNG_EqpID;
		m_stTestResult.m_nNG_EqpType	= IN_nNG_EqpType;
	};

	// Increase (equipment id, socket rfid, pass/fail)
	virtual void IncreasePass_byEqp(__in LPCTSTR szEqpID, __in uint8_t IN_nPara)
	{
		m_Yield.IncreasePass_byEqp(szEqpID, IN_nPara);
	};

	virtual void IncreaseFail_byEqp(__in LPCTSTR szEqpID, __in uint8_t IN_nPara)
	{
		m_Yield.IncreaseFail_byEqp(szEqpID, IN_nPara);
	};

	virtual void IncreasePass()
	{
		m_Yield.IncreasePass();
	};

	virtual void IncreaseFail()
	{
		m_Yield.IncreaseFail();
	};

	void Set_InputTime()
	{
		GetLocalTime(&m_tmLoad);
	};

	void Set_OutputTime()
	{
		GetLocalTime(&m_tmUnload);

		m_dCycleTime = CompareSystemTime(&m_tmUnload, &m_tmLoad);
	};
	void Set_TrackInTime()
	{
		GetLocalTime(&m_tmTrackIn);

	}

	uint32_t Get_ElapsedTime_Load()
	{
		if (m_nStatus == enSocketStatus::SoS_Ready)
			return 0;

		SYSTEMTIME tmLocal;
		GetLocalTime(&tmLocal);

		auto difftime = CompareSystemTime(&tmLocal, &m_tmLoad);

		return static_cast<uint32_t>(difftime);
	}

	uint32_t Get_ElapsedTime_TrackIn()
	{
		if (m_nStatus == enSocketStatus::SoS_Ready)
			return 0;

		SYSTEMTIME tmLocal;
		GetLocalTime(&tmLocal);

		auto difftime = CompareSystemTime(&tmLocal, &m_tmTrackIn);

		return static_cast<uint32_t>(difftime);
	}

	double Get_CycleTime()
	{
		return m_dCycleTime;
	}

	void Set_Tacttime(__in double IN_dTacttime)
	{
		m_dTacttime = IN_dTacttime;
	}

	double Get_Tacttime()
	{
		return m_dTacttime;
	}

	void Reset_TestTime()
	{
		m_dCycleTime = 0.0f;
		m_dTacttime = 0.0f;
	}

	bool Is_Fail()
	{
		return (enSocketStatus::SoS_Fail == m_nStatus);
	}

	bool Is_Error()
	{
		return (enSocketStatus::SoS_Error == m_nStatus);
	}

	bool Is_Bypass()
	{
		return (enSocketStatus::SoS_Bypass == m_nStatus);
	}

	bool Is_Rework()
	{
		return m_bRework;
	}

	void Set_FarAway_TargetEqp(__in bool bFar)
	{
		m_bTargetFar = bFar;
	}

	bool Get_FarAway_TargetEqp() const
	{
		return m_bTargetFar;
	}
#if (USE_XML)
	bool IsEmpty_Lot()
	{
		return m_LotID.IsEmpty();
	}
	bool Set_Lot(__in LPCTSTR IN_szData)
	{
		return m_LotID = IN_szData;
	}
	CString Get_Lot()
	{
		return m_LotID;
	}
#endif
};
#endif // Def_Socket_Info_h__
