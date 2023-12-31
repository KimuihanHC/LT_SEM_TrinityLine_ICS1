//*****************************************************************************
// Filename	: 	Def_Equipment_Type.h
// Created	:	2021/10/21 - 15:52
// Modified	:	2021/10/21 - 15:52
//
// Author	:	piring
//	
// Purpose	:	 
//*****************************************************************************
#ifndef Def_Equipment_Type_h__
#define Def_Equipment_Type_h__

#include <stdint.h>
#include <afxwin.h>
#include "Def_CompileOption.h"

#pragma once

// ?€λΉ ???: version 1.0 (?Έν??? μ? ?ν΄ ?¬μ©)
typedef enum
{
	Eqp_V1_Loader,			// 0
	Eqp_V1_Returner,		// 1
	Eqp_V1_ColorCal,		// 2 
	Eqp_V1_SFR_CL_46,		// 3 : SFR ?κ°
	Eqp_V1_SFR_MultiCL_83,	// 4 : 83
	Eqp_V1_SFR_MultiCL_180,	// 5 : 180
	Eqp_V1_HotPixel,		// 6
	Eqp_V1_StrayLight,		// 7 Ghost & Flare
	Eqp_V1_Distortion,		// 8
	Eqp_V1_SFR_MultiCL,		// 9 : SFR κ΄κ°
	Eqp_V1_HotPixel3port,	// 10 : Hot Pixel 3 Para
	Eqp_V1_ServerEes,		// 11 : Hot Pixel 3 Para

	Max_EqpV1TypeCount,
}enEquipmentType_ver_1;



//-------------------------------------------------------------------
// ?€λΉ ???: version 2.0
//-------------------------------------------------------------------
typedef enum
{	
	Eqp_Handler,		// 0
	Eqp_Loader,			// 1
	Eqp_Returner,		// 2

	Eqp_ColorCal,		// 3 
	Eqp_SFR_CL_46,		// 4 : SFR ?κ°
	Eqp_SFR_MultiCL_83,	// 5 : 83
	Eqp_SFR_MultiCL_180,// 6 : 180
	Eqp_SFR_MultiCL,	// 7 : SFR κ΄κ°
	Eqp_HotPixel,		// 8
	//Eqp_HotPixel3port,	// 10 : Hot Pixel 3 Para
	Eqp_StrayLight,		// 9 Ghost & Flare
	Eqp_Distortion,		// 10
	Eqp_EEPROM,			// 11 : ?μ½
	Max_EqpTypeCount,
	Eqp_Tester_First	= Eqp_ColorCal,
	Eqp_Tester_Last		= Eqp_EEPROM,		
}enEquipmentType;

static LPCTSTR g_szEqpTypeName[] =
{
	_T("Handler"),
	_T("Loader Machine"),
	_T("Returner"),

	_T("Color Calibration"),
	_T("SFR CL 46"),		// ?κ°
	_T("SFR Multi CL 83"),	// κ΄κ° 83
	_T("SFR Multi CL 180"),	// κ΄κ° 180
	_T("SFR Multi CL"),		// κ΄κ° 83 & 180
	_T("Hot Pixel"),
	//_T("Hop Pixel 3 Para"),
	_T("Stray Light"),
	_T("Distortion"),
	_T("EEPROM"),
	nullptr
};

static LPCTSTR g_szEqpTypeInitial[] =
{
	_T("Hlr"),
	_T("Loa"),
	_T("Ret"),
	_T("CCa"),
	_T("S46"),
	_T("S83"),
	_T("S180"),
	_T("SMC"),
	_T("Hot"),
	//_T("HP3"),
	_T("GnF"),
	_T("Dis"),
	_T("E2P"),
	nullptr
};

//-------------------------------------------------------------------
// UI ?€μ  λ°??μΈ ?€μ 
//-------------------------------------------------------------------
typedef enum
{	
	EqpUI_Handler,			//  0
	EqpUI_Loader,			//  1
	EqpUI_Returner,			//  2
							    
	EqpUI_ColorCal,			//  3 
	EqpUI_SFR_CL_46,		//  4 : SFR ?κ°
	EqpUI_SFR_MultiCL_83,	//  5 : 83
	EqpUI_SFR_MultiCL_180,	//  6 : 180
	EqpUI_SFR_MultiCL,		//  7 : SFR κ΄κ°
	EqpUI_HotPixel,			//  8
	EqpUI_HotPixel3port,	//  9 : Hot Pixel 3 Para
	EqpUI_StrayLight,		// 10 : Ghost & Flare
	EqpUI_Distortion,		// 11
	EqpUI_EEPROM,			// 12 : ?μ½
	EqpUI_Ees,			//2023.01.05a Test//2023.01.26a uhkim ?¬μ© ?ν¨

	Max_EqpTypeUICount,
}enEquipmentType_UI;

static LPCTSTR g_szEqpTypeName_UI[] =
{
	_T("Handler"),
	_T("Loader Machine"),
	_T("Returner"),

	_T("Color Calibration"),
	_T("SFR CL 46"),		// ?κ°
	_T("SFR Multi CL 83"),	// κ΄κ° 83
	_T("SFR Multi CL 180"),	// κ΄κ° 180
	_T("SFR Multi CL"),		// κ΄κ° 83 & 180
	_T("Hot Pixel"),
	_T("Hop Pixel 3 Para"),
	_T("Stray Light"),
	_T("Distortion"),
	_T("EEPROM"),
	nullptr
};

static LPCTSTR g_szEqpTypeUI_Initial[] =
{
	_T("Hlr"),
	_T("Loa"),
	_T("Ret"),
	_T("CCa"),
	_T("S46"),
	_T("S83"),
	_T("S180"),
	_T("SMC"),
	_T("Hot"),
	_T("HP3"),
	_T("GnF"),
	_T("Dis"),
	_T("E2P"),
	nullptr
};

//-------------------------------------------------------------------
// κ²???€λΉ ???//-------------------------------------------------------------------
typedef enum
{
	Tester_ColorCal,		// 0
	Tester_SFR_CL_46,		// 1 : ?κ°
	Tester_SFR_MultiCL_83,	// 2 : κ΄κ°
	Tester_SFR_MultiCL_180,	// 3 : κ΄κ°
	Tester_SFR_MultiCL,		// 4 : κ΄κ°
	Tester_HotPixel,		// 5
	//Tester_HotPixel3port,	// 6 : Hot Pixel 3 Para
	Tester_StrayLight,		// 7 Ghost & Flare
	Tester_Distortion,		// 8
	Tester_EEPROM,
	Max_TesterCount,
}enTesterType;

static LPCTSTR g_szTesterTypeName[] =
{
	_T("Color Calibration"),
	_T("SFR CL 46"),		// ?κ°
	_T("SFR Multi CL 83"),// κ΄κ° 83
	_T("SFR Multi CL 180"),	// κ΄κ° 180
	_T("SFR Multi CL"),// κ΄κ° 83 & 180
	_T("Hot Pixel"),
	//_T("Hop Pixel 3 Para"),
	_T("Stray Light"),
	_T("Distortion"),
	_T("EEPROM"),
	nullptr
};

static LPCTSTR g_szTesterTypeInitial[] =
{
	_T("CCa"),
	_T("S46"),
	_T("S83"),
	_T("S180"),
	_T("SMC"),
	_T("Hot"),
	//_T("HP3"),
	_T("GnF"),
	_T("Dis"),
	_T("E2P"),
	nullptr
};
#ifdef 	NEW_INSPECTION_TYPE_APPLY
//-------------------------------------------------------------------
// κ²??μ’λ₯
//-------------------------------------------------------------------
typedef enum
{
	InspType_NotInspection = 0,// 0
	InspType_ColorCal,			// 1
	InspType_SFR,				// 2
	InspType_HotPixel,			// 3
	InspType_StrayLight,		// 4
	InspType_Distortion,		// 5
	InspType_EEPROM,			// 6
	Max_InspTypeCount,
}enInspectionType;

static LPCTSTR g_szInspectionTypeName[] =
{
	_T("Not Inspection"),
	_T("Color Calibration"),
	_T("SFR"),
	_T("Hot Pixel"),
	_T("Stray Light"),
	_T("Distortion"),
	_T("EEPROM"),
	nullptr
};
#endif	// NEW_INSPECTION_TYPE_APPLY

// Equipment id  κ΅¬μ‘°
// 1. Line Name
// 2. Line λ²νΈ
// 3. Equipment Name
// 4. Equipment λ²νΈ
// ex) TLine_01_Loader_01



static int8_t ConvTo_TesterType(__in enEquipmentType IN_nEqpType)
{
	return  static_cast<int8_t>(IN_nEqpType - Eqp_Tester_First);
};

#ifdef 	NEW_INSPECTION_TYPE_APPLY
static int8_t ConvTo_InspectionType(__in enEquipmentType IN_nEqpType)
{

	switch (IN_nEqpType)
	{
	case Eqp_ColorCal:
		return static_cast<int8_t>(InspType_ColorCal);
		break;

	case Eqp_SFR_CL_46:
	case Eqp_SFR_MultiCL_83:
	case Eqp_SFR_MultiCL_180:
	case Eqp_SFR_MultiCL:
		return static_cast<int8_t>(InspType_SFR);
		break;

	case Eqp_HotPixel:
	//case Eqp_HotPixel3port:
		return static_cast<int8_t>(InspType_HotPixel);
		break;

	case Eqp_StrayLight:
		return static_cast<int8_t>(InspType_StrayLight);
		break;

	case Eqp_Distortion:
		return static_cast<int8_t>(InspType_Distortion);
		break;

	case Eqp_EEPROM:
		return static_cast<int8_t>(InspType_EEPROM);
		break;

	case Eqp_Handler:
	case Eqp_Loader:
	case Eqp_Returner:
	default:
		break;
	}


	return  static_cast<int8_t>(IN_nEqpType - Eqp_Tester_First);
};
#endif	// NEW_INSPECTION_TYPE_APPLY

static int8_t ConvTo_EquipmentType(__in enTesterType IN_nTesterType)
{
	return  static_cast<int8_t>(IN_nTesterType + Eqp_Tester_First);
};

static bool IsTester_byEqpType(__in uint8_t IN_nEqpType)
{
	return ((Eqp_Tester_First <= IN_nEqpType) && (IN_nEqpType <= Eqp_Tester_Last));
};


#define		LOADER_EQP_ORDER		0
#define		FIRST_TESTER_EQP_ORDER	1




#endif // Def_Equipment_Type_h__
