﻿//*****************************************************************************
// Filename	: 	Wnd_Cfg_Line.h
// Created	:	2021/10/21 - 15:15
// Modified	:	2021/10/21 - 15:15
//
// Author	:	piring
//	
// Purpose	:	
//*****************************************************************************
#ifndef Wnd_Cfg_Server_h__
#define Wnd_Cfg_Server_h__

#pragma once
#include "Wnd_BaseView.h"
#include "VGStatic.h"
#include "Def_ConfigLineServer.h"
#include "List_ServerConfig.h"

//-----------------------------------------------------------------------------
// CWnd_Cfg_Line
//-----------------------------------------------------------------------------
class CWnd_Cfg_Server : public CWnd_BaseView
{
	DECLARE_DYNAMIC(CWnd_Cfg_Server)

public:
	CWnd_Cfg_Server();
	virtual ~CWnd_Cfg_Server();
	enum enEqpCtrl
	{
		EC_Add,
		EC_Insert,
		EC_Remove,
		EC_Modify,
		EC_Order_Up,
		EC_Order_Down,
		EC_MaxEnum,
	};
	enum enEqpItemData
	{
		EID_Eqp_Alias = 0,
		EID_Eqp_Type,
		EID_Eqp_Id,
		EID_IP_Address,
		//EID_Svr_Type,
		EID_MaxEnum,
	};
	enum enXmlCtrl
	{
		XML_Load,
		XML_Save,
		XML_Clear,
		XML_MaxCount,
	};

protected:
	DECLARE_MESSAGE_MAP()


	afx_msg int		OnCreate					(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize						(UINT nType, int cx, int cy);
	void			MoveWindow_EqpCtrl			(int x, int y, int nWidth, int nHeight);
	void			MoveWindow_EqpItem			(int x, int y, int nWidth, int nHeight);

	afx_msg void	OnBnClickedBnEqpCtrl		(UINT nID);
	afx_msg void	OnCbnSelendokEqpType		();
	afx_msg void	OnBnClickedBnListCtrl		(UINT nID);
	afx_msg void	OnBnClickedBnClearList		();
	afx_msg void	OnBnClickedBnVerifyLine		();
	afx_msg void	OnBnClickedBnApply			();
	afx_msg void	OnCbnSelendokSvrType		();

	CFont			m_font_Default;
	CFont			m_Font;

	CMFCButton			m_bn_Apply;

	CList_ServerConfig	m_lc_ServerInfo;
	CMFCButton			m_bn_VerifyLineConfig;

	// 설비 항목 추가/삭제/이동
	CMFCButton		m_bn_ItemCtrl[EC_MaxEnum];

	// 검사기 항목 ---------------------------------------------------
	CVGStatic		m_st_EqpItemData[EID_MaxEnum];	
	
	CComboBox		m_cb_ServerType;	//추가 옵션.
	CEdit			m_ed_EqpAlias;
	CEdit			m_ed_EquipmentId;
	CMFCMaskedEdit	m_ed_IPAddress;

	CMFCButton		m_bn_XmlCtrl[XML_MaxCount];

	
	CString			m_szPath_XML;		// XML 파일 패스
	CString			m_szPath_Default;	// 기본 저장 파일 전체 경로

	//std::vector<CString>	m_EquipmentTypeList;

	// 기타 데이터 사용여부
	bool			m_bUseExtraData		= false;

	// UI에 설정된 설비 구성 데이터 구하기
	BOOL	Get_EquipmentData			(__out CConfig_Svr& OUT_stEquipment);
	void	Verify_Equipment			(__inout CConfig_Svr& OUT_stEquipment);

	// 버튼 제어 함수
	void	Item_Add					();
	void	Item_Insert					();
	void	Item_Remove					();
	void	Item_Modify					();
	void	Item_Up						();
	void	Item_Down					();

	// XML 불러오기 / 저장하기
	BOOL	LoadXML_ServerInfo	(__out CConfig_Server& OUT_stLineInfo, __out CString& OUT_FilePath, __out CString& OUT_FileTitle);
	BOOL	LoadXML_ServerInfo	(__in LPCTSTR IN_szFilePath, __out CConfig_Server& OUT_stLineInfo);
	BOOL	LoadXML_ServerInfo	();
	BOOL	SaveXML_ServerInfo	();
	void	Apply_ServerInfo	();

	// 설비 항목 선택에 따른 파라미터 데이터 사용 및 명칭 업데이트
	void	UpdateUI_EquipmentData		(__in int IN_nIndex);
	// ComboBox의 설비 항목 리스트 업데이트
	//void	UpdateUI_EquipmentType		();

	// 루프 begin -> end 구조가 정상인지 판단
	bool	Verify_EquipmentSequence	(__in const CConfig_Server* IN_pLineInfo);

public:

	virtual void	OnLanguage				(__in uint8_t IN_nLanguage);

	// 권한 설정
	void		Set_PermissionMode			(__in enPermissionMode IN_PermissionMode);

	// 기본 저장 파일 전체 경로
	void		Set_FileFullPath			(__in LPCTSTR IN_szFullPath);

	// 설비 List 저장 파일 경로
	void		Set_XMLFilePath				(__in LPCTSTR szPath_XML);

	// 기타 데이터 사용 여부
	void		Set_UseExtraData			(__in bool bUse);

	// 저장된 라인 구성 정보 데이터 불러오기
	void		Set_Configuration			(__in const CConfig_Server* IN_pLineInfo);
	void		Set_Configuration			();
	void		Get_Configuration			(__out CConfig_Server& OUT_stLineInfo);

	// 초기 상태로 설정 (New)
	void		Init_DefaultSet				();

	// 사용하는 설비 항목 목록 추가
//	void		Reset_EquipmentTypeList		();
// 	void		Set_EquipmentTypeList		(__in CString* IN_pEqpTypeList, __in UINT IN_nCount);
// 	void		Set_EquipmentTypeList		(__in std::vector<CString>* IN_pEqpTypeVector);
// 	void		Add_EquipmentTypeList		(__in CString* IN_pEqpTypeList, __in UINT IN_nCount);
// 	void		Add_EquipmentTypeList		(__in std::vector<CString>* IN_pEqpTypeVector);


	

};

#endif // Wnd_Cfg_Line_h__


