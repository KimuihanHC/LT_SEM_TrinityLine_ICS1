//*****************************************************************************
// Filename	: 	Def_Socket_Config.h
// Created	:	2021/12/20 - 15:10
// Modified	:	2021/12/20 - 15:10
//
// Author	:	piring
//	
// Purpose	:	
//*****************************************************************************
#ifndef Def_Socket_Config_h__
#define Def_Socket_Config_h__


#pragma once

#include <afxwin.h>
#include <map>

// ?�켓 ?�보
#define			MAX_SOCKET_COUNT		999

//-----------------------------------------------
// ?�품 모델 종류
//-----------------------------------------------
typedef enum
{
	Model_46,	// SFR ?�각 H
	Model_83,	// SFR 광각 H, V
	Model_180,	// SFR 광각 H

	Max_ModelCount,
}enModelType;

static LPCTSTR g_szModelType[] =
{
	_T("46"),
	_T("83"),
	_T("180"),
	NULL
};

//-----------------------------------------------
// ?�켓 종류
//-----------------------------------------------
typedef enum 
{
	Socket_H,	// SFR 광각 H, SFR ?�각(Narrow)
	Socket_V,	// SFR 광각 V
	Socket_Highland,
	Max_SocketTypeCount,
}enSocketType;

static LPCTSTR g_szSocketTypeName[] =
{
	_T("H Type"),
	_T("V Type"),
	_T("Highland"),
	nullptr
};

// ?�켓 ?�입 ?�인 ?�태
// 0: Error
// 1: Accept
// 2: Accpet (All Test End)
// 3: Bypass

//-----------------------------------------------
// ?�켓 검??진행 ?�태
//-----------------------------------------------
typedef enum
{
	STS_Fail,		// 
	STS_Pass,		// 
	STS_NotTest,	// 
	Max_SocketTestStatusCount,
}enSocketTestStatus;

static LPCTSTR g_szSocketTestStatus[] =
{
	_T("Fail"),
	_T("Pass"),
	_T("Not Test"),
	nullptr
};

//-----------------------------------------------------------------------------
// CConfig_Socket
//-----------------------------------------------------------------------------
class CConfig_Socket
{
public:

	CString		szRFID;			// RFID 
	uint8_t		nSocketType;	// Socket Type
	CString		szComment;		// Comment

	//uint8_t		m_AngleOfView;		// 광각 / ?�각
	//uint8_t		m_nDirectionType;	// 46??/ 90??/ 180??
	CConfig_Socket()
	{
		nSocketType			= 0;
		//m_AngleOfView		= 0;
		//m_nDirectionType	= 0;
	};

	CConfig_Socket& operator= (const CConfig_Socket& ref)
	{
		szRFID			= ref.szRFID;
		nSocketType		= ref.nSocketType;
		szComment		= ref.szComment;

		//m_AngleOfView		= ref.m_AngleOfView;
		//m_nDirectionType	= ref.m_nDirectionType;

		return *this;
	};

	void Reset()
	{
		szRFID.Empty();
		nSocketType			= 0;
		szComment.Empty();
	};
};

//-----------------------------------------------------------------------------
// CSocketList
//-----------------------------------------------------------------------------
class CSocketList
{
public:

	// key : RFID
#ifdef _UNICODE
	std::map<std::wstring, CConfig_Socket> SocketList;
#else
	std::map<std::string, CConfig_Socket> SocketList;
#endif

	CSocketList()
	{

	};

	CSocketList& operator= (const CSocketList& ref)
	{
		SocketList.clear();
		SocketList = ref.SocketList;

		return *this;
	};

	// ?�켓 �?��
	size_t GetCount() const
	{
		return SocketList.size();
	};

	// 모든 ?�켓 ??��
	virtual void RemoveAll()
	{
		SocketList.clear();
	};

	// ?�켓 ?�입
	virtual bool Socket_Insert(__in CConfig_Socket IN_stSocket)
	{
		auto Ret = SocketList.insert({IN_stSocket.szRFID.GetBuffer(), IN_stSocket});

		return Ret.second;
	};

	// ?�켓 ??��
	virtual void Socket_Remove(__in LPCTSTR szRFID)
	{
		if (0 < SocketList.size())
		{
			SocketList.erase(szRFID);
		}
	};

	// ?�켓 ?�정
	virtual void Socket_Modify(__in CConfig_Socket IN_stSocket)
	{
		if (0 < SocketList.size())
		{
			SocketList.at(IN_stSocket.szRFID.GetBuffer()) = IN_stSocket;
		}
	};

	virtual CConfig_Socket GetAt(__in LPCTSTR szRFID)
	{
		return SocketList.at(szRFID);
	}

	virtual const CConfig_Socket GetAt(__in LPCTSTR szRFID) const
	{
		return SocketList.at(szRFID);
	}

	uint16_t Get_SocketCount(__in uint8_t nSocketType)
	{
		uint16_t nCount = 0;

		auto eIter = SocketList.end();
		auto Iter = SocketList.begin();
		while (Iter != eIter)
		{
			if (nSocketType == Iter->second.nSocketType)
			{
				++nCount;
			}

			Iter++;
		}
		return nCount;
	};


	// RFID�?Socket Type 구하�?/
	bool Get_SocketType(__in LPCTSTR IN_szRFID, __out uint8_t& OUT_nSocketType)
	{
		auto result = SocketList.find(IN_szRFID);
		if (result != SocketList.end()) 
		{
			OUT_nSocketType = SocketList.at(IN_szRFID).nSocketType;
			return true;
		}
		else 
		{
			return false;
		}
	};

};

#endif // Def_Socket_Config_h__