#ifndef FailInfo_Eqp_h__
#define FailInfo_Eqp_h__

#pragma once

#include <map>
#include "Def_FailInfo.h"

class CFailInfo_Eqp
{
public:
	// NG Code ī��Ʈ
	std::map<int16_t, ST_NGCode_Count>	m_NG_Count;

protected:
	uint8_t		m_nEqpOrder			= 0;
	CString		m_szEquipmentID;	// ���� ���� ID
	uint8_t		m_nTestPortCount	= 2;	// �˻� para ����
	CString		m_szPath;			// ini ������ ����Ǵ� Path

	HWND		m_hWndGUI			= nullptr;
	UINT		m_nWM_Notify		= WM_NGCODE_NOTIFY;
	inline void	WM_Notify_NGCode	(__in int16_t IN_nNGCode);
	inline void	WM_Notify_NGCode_All();

	bool		Save_IniFile_NGCode	(__in LPCTSTR IN_szPathFile, __in int16_t IN_nNGCode, __in bool IN_bNewData = false);

	bool		Write_File			(__in LPCTSTR IN_szPathFile, __in LPCTSTR IN_szData, __in LPCTSTR IN_szHeader);

public:
	// Data�� GUI�� ǥ���ϱ� ���� ���
	void		Set_GUI_HWND		(__in HWND IN_hWnd);
	// Notify Windows Message ����
	void		Set_WinMsg_Notify	(__in UINT IN_nWM_Notify);

	// ���� ID
	void		Set_EquipmentID		(__in uint8_t IN_nEqpOrder, __in LPCTSTR IN_szEquipmentID);
	CString&	Get_EquipmentID		();
	const CString&	Get_EquipmentID	() const;

	// �˻� para ����
	void		Set_TestPortCount	(__in uint8_t IN_nTestPortCount);
	uint8_t		Get_TestPortCount	() const;

	// ���� ����
	uint8_t		Get_EqpOrder		() const;

	ST_NGCode_Count&		Get_NGCount	(__in int16_t IN_nNGCode);
	const ST_NGCode_Count&	Get_NGCount	(__in int16_t IN_nNGCode) const;

	// std:map�� NG Code�� �����ϳ�?
	bool		IsExist				(__in int16_t IN_nNGCode) const;

	// ini ���� ���� ��� ����
	void		Set_Path			(__in LPCTSTR IN_szPath);

	void		Clear_NGCode		();
	void		Reset_Count_All		();
	void		Reset_Count			(__in int16_t IN_nNGCode);

	// NG Code std:map�� �߰�
	bool		Insert				(__in int16_t IN_nNGCode);

	// ī��Ʈ ����
	void		IncreaseCount		(__in int16_t IN_nNGCode, __in uint8_t IN_nNG_Para);

	// ���� ó��
	bool		Save_IniFile		(__in LPCTSTR IN_szPathFile);
	bool		Save_IniFile		();
	bool		Load_IniFile		(__in LPCTSTR IN_szPathFile);
	bool		Load_IniFile		();

	bool		Write_CSV_File		(__in LPCTSTR IN_szPathFile);

	// NG Count�� 0�� �׸� ����
	void		Remove_ZeroCount_Item();
};


#endif // FailInfo_Eqp_h__
