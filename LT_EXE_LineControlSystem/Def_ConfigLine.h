//*****************************************************************************
// Filename	: 	Def_ConfigLine.h
// Created	:	2021/11/1 - 15:23
// Modified	:	2021/11/1 - 15:23
//
// Author	:	piring
//	
// Purpose	:	
//*****************************************************************************
#ifndef Def_LineConfig_h__
#define Def_LineConfig_h__


#pragma once

#include <afxwin.h>
#include <stdint.h>
#include <vector>

#include "Def_ConfigEquipment.h"

//-----------------------------------------------------------------------------
// ?�인??검?�기 구성 ?�정??구조�?//-----------------------------------------------------------------------------
class CConfig_Line
{
public:
	std::vector<CConfig_Eqp> EqpList;

	CConfig_Line()
	{

	};

	CConfig_Line& operator= (const CConfig_Line& ref)
	{
		EqpList.clear();
		EqpList = ref.EqpList;
		return *this;
	};

	// ?�텝 �?��
	size_t GetCount() const
	{
		return EqpList.size();
	};
	// 모든 ?�텝 ??��
	virtual void RemoveAll()
	{
		EqpList.clear();
	};
	// ?�텝 추�?
	virtual void Eqp_Add(__in CConfig_Eqp IN_stTestStep)
	{
		EqpList.push_back(IN_stTestStep);
	};
	// ?�텝 ?�입
	virtual void Eqp_Insert(__in uint16_t IN_nIdx, __in CConfig_Eqp IN_stTestStep)
	{
		if (0 < EqpList.size())
		{
			EqpList.insert(EqpList.begin() + IN_nIdx, IN_stTestStep);
		}
	};
	// ?�텝 ??��
	virtual void Eqp_Remove(__in uint16_t IN_nIdx)
	{
		if (0 < EqpList.size())
		{
			EqpList.erase(EqpList.begin() + IN_nIdx);
		}
	};
	// ?�텝 ?�정
	virtual void Eqp_Modify(__in uint16_t IN_nIdx, __in CConfig_Eqp IN_stTestStep)
	{
		if (0 < EqpList.size())
		{
			EqpList.at(IN_nIdx) = IN_stTestStep;
		}
	};
	// ?�텝 ?�로 ?�동
	virtual void Eqp_Up(__in uint16_t IN_nIdx)
	{
		if (0 < EqpList.size())
		{
			// 0�??�덱?�는 ?�로 ?�동 불�?
			if ((0 < IN_nIdx) && (1 < EqpList.size()))
			{
				CConfig_Eqp stStep = EqpList.at(IN_nIdx);

				EqpList.erase(EqpList.begin() + IN_nIdx);
				EqpList.insert(EqpList.begin() + IN_nIdx, stStep);
			}
		}
	};
	// ?�텝 ?�래�??�동
	virtual void Eqp_Down(__in uint16_t IN_nIdx)
	{
		if (0 < EqpList.size())
		{
			// 마�?�??�덱?�는 ?�래�??�동 불�?
			if ((IN_nIdx < (EqpList.size() - 1)) && (1 < EqpList.size()))
			{
				CConfig_Eqp stStep = EqpList.at(IN_nIdx);

				EqpList.erase(EqpList.begin() + IN_nIdx);

				// 변경되???�치가 최하?�이�? Insert ?�??Add ?�용
				if ((IN_nIdx + 1) < (EqpList.size()))
				{
					EqpList.insert(EqpList.begin() + IN_nIdx, stStep);
				}
				else
				{
					EqpList.push_back(stStep);
				}
			}
		}
	};
	virtual CConfig_Eqp& GetAt(__in uint16_t IN_nIdx)
	{
		return EqpList.at(IN_nIdx);
	}
	virtual const CConfig_Eqp& GetAt(__in uint16_t IN_nIdx) const
	{
		return EqpList.at(IN_nIdx);
	}
	// Eqp id�?Eqp type 구하�?/
	bool Get_EquipmentType(__in LPCTSTR IN_szEqpID, __out uint8_t& OUT_nEqpType)
	{
		for (auto nIdx = 0; nIdx < EqpList.size(); ++nIdx)
		{
			if (0 == EqpList.at(nIdx).Get_EquipmentId().Compare(IN_szEqpID))
			{
				OUT_nEqpType = EqpList.at(nIdx).Get_EquipmentType();
				return true;
			}
		}

		return false;
	};
	// ?�비 ?�서�?Eqp id 구하�?/
	bool Get_EquipmentID(__in uint8_t IN_LineOrder, __out CString& OUT_szEqpID)
	{
		if (IN_LineOrder < EqpList.size())
		{
			OUT_szEqpID = EqpList.at(IN_LineOrder).Get_EquipmentId();
			return true;
		}

		return false;
	};
	// ?�비 ?�?�으�??�인???�일 ?�비 개수 구하�?/
	uint8_t Get_EquipmentCount(__in uint8_t nEquipmentType)
	{
		uint8_t nCount = 0;

		for (auto nIdx = 0; nIdx < EqpList.size(); ++nIdx)
		{
			if (nEquipmentType == EqpList.at(nIdx).Get_EquipmentType())
			{
				++nCount;
			}
		}

		return nCount;
	};
	// Eqp ID�??�인???�일 ?�비 개수 구하�?/
	uint8_t Get_EquipmentCount(__in LPCTSTR IN_szEqpID)
	{
		uint8_t nEquipmentType = 0;

		if (Get_EquipmentType(IN_szEqpID, nEquipmentType))
		{
			return Get_EquipmentCount(nEquipmentType);
		}
		else
		{
			return 0;
		}
	};

// 	WORD Get_ItemID(__in UINT IN_nIdx)
// 	{
// 		return EqpList.at(IN_nIdx).nItem_ID;
// 	}
	
}; // CConfig_Line
#endif // Def_LineConfig_h__
