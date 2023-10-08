//*****************************************************************************
// Filename	: 	Def_Config_ALID_LIST.h
// Created	:	
// Modified	:	2023.04.20 17:00
//
// Author	:	piring
//	
// Purpose	:	
//*****************************************************************************
#ifndef Def_Config_ALID_LIST_h__
#define Def_Config_ALID_LIST_h__


#pragma once

#include <afxwin.h>
#include <stdint.h>
#include <vector>

#include "Def_Config_ALID.h"

class CConfig_AL_LIST
{
public:
	std::vector<CConfig_AL> AL_LIST;
	CConfig_AL_LIST()
	{

	};

	CConfig_AL_LIST& operator= (const CConfig_AL_LIST& ref)
	{
		AL_LIST.clear();
		AL_LIST = ref.AL_LIST;
		return *this;
	};

	// ?�텝 �?��
	size_t Get_AL_Count() const
	{
		return AL_LIST.size();
	};
	// 모든 ?�텝 ??��
	virtual void RemoveAll()
	{
		AL_LIST.clear();
	};
	// ?�텝 추�?
	virtual void AL_Add(
		__in CConfig_AL IN_stTestStep)
	{
		AL_LIST.push_back(IN_stTestStep);
	};
	// ?�텝 ?�입
	virtual void AL_Insert(
		__in uint16_t IN_nIdx,
		__in CConfig_AL IN_stTestStep)
	{
		if (0 < AL_LIST.size())
		{
			AL_LIST.insert(AL_LIST.begin() + IN_nIdx, IN_stTestStep);
		}
	};
	// ?�텝 ??��
	virtual void AL_Remove(
		__in uint16_t IN_nIdx)
	{
		if (0 < AL_LIST.size())
		{
			AL_LIST.erase(AL_LIST.begin() + IN_nIdx);
		}
	};
	// ?�텝 ?�정
	virtual void AL_Modify(
		__in uint16_t IN_nIdx,
		__in CConfig_AL IN_stTestStep)
	{
		if (0 < AL_LIST.size())
		{
			AL_LIST.at(IN_nIdx) = IN_stTestStep;
		}
	};
	// ?�텝 ?�로 ?�동
	virtual void AL_Up(
		__in uint16_t IN_nIdx)
	{
		if (0 < AL_LIST.size())
		{
			// 0�??�덱?�는 ?�로 ?�동 불�?
			if ((0 < IN_nIdx) && (1 < AL_LIST.size()))
			{
				CConfig_AL stStep = AL_LIST.at(IN_nIdx);

				AL_LIST.erase(AL_LIST.begin() + IN_nIdx);
				AL_LIST.insert(AL_LIST.begin() + IN_nIdx, stStep);
			}
		}
	};
	// ?�텝 ?�래�??�동
	virtual void AL_Down(
		__in uint16_t IN_nIdx)
	{
		if (0 < AL_LIST.size())
		{
			// 마�?�??�덱?�는 ?�래�??�동 불�?
			if ((IN_nIdx < (AL_LIST.size() - 1)) && (1 < AL_LIST.size()))
			{
				CConfig_AL stStep = AL_LIST.at(IN_nIdx);

				AL_LIST.erase(AL_LIST.begin() + IN_nIdx);

				// 변경되???�치가 최하?�이�? Insert ?�??Add ?�용
				if ((IN_nIdx + 1) < (AL_LIST.size()))
				{
					AL_LIST.insert(AL_LIST.begin() + IN_nIdx, stStep);
				}
				else
				{
					AL_LIST.push_back(stStep);
				}
			}
		}
	};
	virtual CConfig_AL& GetAt(
		__in uint16_t IN_nIdx)
	{
		return AL_LIST.at(IN_nIdx);
	}
	virtual const CConfig_AL& GetAt(
		__in uint16_t IN_nIdx) const
	{
		return AL_LIST.at(IN_nIdx);
	}

}; // CConfig_AL


#endif // Def_Config_ALID_LIST_h__
