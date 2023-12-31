//*****************************************************************************
// Filename	: 	Def_ModelConfig.h
// Created	:	2021/11/4 - 18:10
// Modified	:	2021/11/4 - 18:10
//
// Author	:	piring
//	
// Purpose	:	 
//*****************************************************************************
#ifndef Def_ModelConfig_h__
#define Def_ModelConfig_h__


#pragma once

#include "Def_Equipment_Type.h"


//---------------------------------------------------------
// ?ํ ๋ชจ๋ธ ?ค์  ๊ตฌ์กฐ์ฒ?//---------------------------------------------------------
class CConfig_Model
{
public:

	CString			m_szAlias;		// ๋ช์นญ
	uint8_t			m_nSocketType;	// ?ฌ์ฉ ?์ผ
	uint8_t			m_nModelType;	// ?ฌ์ฉ ?์ผ

	bool			m_bEnable_TestType[Max_TesterCount];		// ๊ฒ??์งํ ?์ฑ???ฌ๋?
#ifdef 	NEW_INSPECTION_TYPE_APPLY
	bool			m_bEnable_InspType[Max_InspTypeCount];		// ๊ฒ??์งํ ?์ฑ???ฌ๋?
#endif	// NEW_INSPECTION_TYPE_APPLY
	//bool			bChecked_TestType[Max_TesterCount];		// ?์ฑ?๋ ๊ฒ??์ค?๊ฒ??์งํ ?ฌ๋?

	CConfig_Model()
	{
		m_nSocketType	= 0;
		m_nModelType	= 0;

		memset(m_bEnable_TestType, 0, sizeof(bool) * Max_TesterCount);
#ifdef 	NEW_INSPECTION_TYPE_APPLY
		memset(m_bEnable_InspType, 0, sizeof(bool) * Max_InspTypeCount);
#endif	// NEW_INSPECTION_TYPE_APPLY
		//memset(bChecked_TestType, 0, sizeof(bool) * Max_TesterCount);
	};

	void Reset()
	{
		m_szAlias.Empty();
	};

	CConfig_Model& operator= (const CConfig_Model& ref)
	{
		m_szAlias			= ref.m_szAlias;
		m_nSocketType		= ref.m_nSocketType;
		m_nModelType		= ref.m_nModelType;

		for (auto nIdx = 0; nIdx < Max_TesterCount; ++nIdx)
		{
			m_bEnable_TestType[nIdx]	= ref.m_bEnable_TestType[nIdx];
			//bChecked_TestType[nIdx] = ref.bChecked_TestType[nIdx];
		}

#ifdef 	NEW_INSPECTION_TYPE_APPLY
		for (auto nIdx = 0; nIdx < Max_InspTypeCount; ++nIdx)
		{
			m_bEnable_InspType[nIdx] = ref.m_bEnable_InspType[nIdx];
		}
#endif	// NEW_INSPECTION_TYPE_APPLY

		return *this;
	};



};


#endif // Def_ModelConfig_h__
