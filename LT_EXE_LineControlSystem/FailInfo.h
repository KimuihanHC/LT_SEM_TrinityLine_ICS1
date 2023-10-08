#ifndef FailInfo_h__
#define FailInfo_h__

#pragma once

#include "FailInfo_Eqp.h"
//#include <vector>
#include <map>

//-----------------------------------------------------------------------------
// CFailInfo
//-----------------------------------------------------------------------------
class CFailInfo
{
public:

	CFailInfo();
	~CFailInfo();


	//std::vector<CFailInfo_Eqp> m_EqpList;
	std::map<uint8_t, CFailInfo_Eqp> m_EqpList;

protected:
	CString		m_szPath;
	CString		m_szPath_Report;

public:

	// ini ���� ���� ���
	void	Set_Path				(__in LPCTSTR IN_szPath);
	void	Set_Path_Report			(__in LPCTSTR IN_szPath);

	// ���� ��� ����
	void	Clear_EqpList			();
	void	Add_Equipment			(__in uint8_t IN_nEqpOrder, __in LPCTSTR IN_szEquipmentID);
	void	Add_Equipment			(__in uint8_t IN_nEqpOrder, __in LPCTSTR IN_szEquipmentID, __in uint8_t IN_nTestPortCount);
	size_t	Get_EquipmentCount		();

	// ���� �ҷ� ���� Ŭ���� ���
	bool	IsExist					(__in uint8_t IN_nEqpOrder);
	CFailInfo_Eqp&			Get_Equipment	(__in uint8_t IN_nEqpOrder);
	const CFailInfo_Eqp&	Get_Equipment	(__in uint8_t IN_nEqpOrder) const;

	// NG Code ī���� �ʱ�ȭ
	void	Reset_Count_All			();
	void	Reset_Count				(__in uint8_t IN_nEqpOrder);
	void	Reset_Count_NGCode		(__in uint8_t IN_nEqpOrder, __in int16_t IN_nNGCode);

	// NG Code ī��Ʈ ����
	void	IncreaseCount			(__in uint8_t IN_nEqpOrder, __in int16_t IN_nNGCode, __in uint8_t IN_nNG_Para);

	//        -> Eqp
	//        -> A,L,R
	// Ng Code

	bool	Save_IniFile			();
	bool	Load_IniFile			();
	
	bool	Write_CSV_File			(__in uint8_t IN_nEqpOrder, __in LPCTSTR IN_szPathFile);
	bool	Write_CSV_File			(__in LPCTSTR IN_szPath);
	bool	Write_CSV_File_Default	();

};


#endif // FailInfo_h__