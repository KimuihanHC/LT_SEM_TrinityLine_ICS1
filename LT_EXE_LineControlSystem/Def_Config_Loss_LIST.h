//*****************************************************************************
// Filename	: 	Def_Config_Loss_LIST.h
// Created	:	
// Modified	:	2023.04.21 16:00
//
// Author	:	piring
//	
// Purpose	:	
//*****************************************************************************
#ifndef Def_Config_Loss_LIST_h__
#define Def_Config_Loss_LIST_h__


#pragma once

#include <afxwin.h>
#include <stdint.h>
#include <vector>

#include "Def_Config_Loss.h"

//-----------------------------------------------------------------------------
// EES 구성 ?�정??구조�?//-----------------------------------------------------------------------------
class CConfig_Loss_LIST
{
public:
	std::vector<CConfig_Loss> Loss_LIST;
	CConfig_Loss_LIST()	{

	};

	CConfig_Loss_LIST& operator= (const CConfig_Loss_LIST& ref)
	{
		Loss_LIST.clear();
		Loss_LIST = ref.Loss_LIST;
		return *this;
	};

	// ?�텝 �?��
	size_t Get_Loss_Count() const
	{
		return Loss_LIST.size();
	};
	// 모든 ?�텝 ??��
	virtual void RemoveAll()
	{
		Loss_LIST.clear();
	};
	// ?�텝 추�?
	virtual void Loss_Add(
		__in CConfig_Loss IN_stTestStep)
	{
		Loss_LIST.push_back(IN_stTestStep);
	};
	// ?�텝 ?�입
	virtual void Loss_Insert(
		__in uint16_t IN_nIdx, 
		__in CConfig_Loss IN_stTestStep)
	{
		if (0 < Loss_LIST.size())
		{
			Loss_LIST.insert(Loss_LIST.begin() + IN_nIdx, IN_stTestStep);
		}
	};
	// ?�텝 ??��
	virtual void Loss_Remove(
		__in uint16_t IN_nIdx)
	{
		if (0 < Loss_LIST.size())
		{
			Loss_LIST.erase(Loss_LIST.begin() + IN_nIdx);
		}
	};
	// ?�텝 ?�정
	virtual void Loss_Modify(
		__in uint16_t IN_nIdx, 
		__in CConfig_Loss IN_stTestStep)
	{
		if (0 < Loss_LIST.size())
		{
			Loss_LIST.at(IN_nIdx) = IN_stTestStep;
		}
	};
	// ?�텝 ?�로 ?�동
	virtual void Loss_Up(
		__in uint16_t IN_nIdx)
	{
		if (0 < Loss_LIST.size())
		{
			// 0�??�덱?�는 ?�로 ?�동 불�?
			if ((0 < IN_nIdx) && (1 < Loss_LIST.size()))
			{
				CConfig_Loss stStep = Loss_LIST.at(IN_nIdx);

				Loss_LIST.erase(Loss_LIST.begin() + IN_nIdx);
				Loss_LIST.insert(Loss_LIST.begin() + IN_nIdx, stStep);
			}
		}
	};
	// ?�텝 ?�래�??�동
	virtual void Loss_Down(
		__in uint16_t IN_nIdx)
	{
		if (0 < Loss_LIST.size())
		{
			// 마�?�??�덱?�는 ?�래�??�동 불�?
			if ((IN_nIdx < (Loss_LIST.size() - 1)) && (1 < Loss_LIST.size()))
			{
				CConfig_Loss stStep = Loss_LIST.at(IN_nIdx);

				Loss_LIST.erase(Loss_LIST.begin() + IN_nIdx);

				// 변경되???�치가 최하?�이�? Insert ?�??Add ?�용
				if ((IN_nIdx + 1) < (Loss_LIST.size()))
				{
					Loss_LIST.insert(Loss_LIST.begin() + IN_nIdx, stStep);
				}
				else
				{
					Loss_LIST.push_back(stStep);
				}
			}
		}
	};
	virtual CConfig_Loss& GetAt(
		__in uint16_t IN_nIdx)
	{
		return Loss_LIST.at(IN_nIdx);
	}
	virtual const CConfig_Loss& GetAt(
		__in uint16_t IN_nIdx) const
	{
		return Loss_LIST.at(IN_nIdx);
	}
}; 
#endif // Def_Config_Loss_LIST_h__
