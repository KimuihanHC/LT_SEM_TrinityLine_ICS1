//*****************************************************************************
// Filename	: 	LineControl.h
// Created	:	2021/11/18 - 17:32
// Modified	:	2021/11/18 - 17:32
//
// Author	:	piring
//	
// Purpose	:	?�비?� ?�신 �??�들???�어
//*****************************************************************************
#ifndef LineControl_h__
#define LineControl_h__

#pragma once

#include "LineInfo.h"

//-----------------------------------------------------------------------------
// ?�비?� ?�신 �??�들???�어
//-----------------------------------------------------------------------------
class CLineControl : public CLineInfo
{
public:
	CLineControl();
	virtual ~CLineControl();

protected:

	// ?�켓 ?�보(?)

	

	// Loader
	// Tester, Tester, ....
	// Return
	// Unloader


	// 검???�료
	// Recv_CompleteTest( ok / ng );
	// Send_Reply_CompleteTest();



	// ?�송: ?�버 ?�간 ?�기??	// Send_TimeSync ( server_time );

	// ?�송: ?�용??권한, ?�어, ?�간

	// ?�송: ?�비 ?�어 (?�비???�비 진행 ?�태 변�?
	// Send_Request_Change_EqpProcessStatus( EqpProcessStatus );

	// ?�신: ?�람

	// ?�송: ?�용 모드 (?�비???�용 모드 변�?
	// Send_Request_Change_EqpOperMode( EqpOperMode );

	// ?�신: ?�비 ?�태

	// ?�신: RFID ?�록
	// ?�신: RFID ?�입 ?�인 ?�청
	// ?�신: RFID 검??결과 ?�청
	// ?�신: RFID 검??결과 ?�록
	// ?�신: RFID ?�록 ?�제

	// ?�송: All Socket Clear

	// ?�신: 버퍼 ?�태	
	// Recv_RequestArriveSocket( fromEqp, BufferType, RFID);
	// Send_ReplyArriveSocket( test/bypass/wait );

	// ?�신: 컨베?�어 ?�태


	// ?�신: 검??ZONE  ?�태 (L/R)

	// ?�신: ?�비 초기 ?�태 (Loader)
	// ?�신: ?�비 초기 ?�태 (Unloader)
	// ?�신: ?�비 초기 ?�태 (검?�기)
	// Recv_EqpStatus ( buffer, Zone, return, eqpOpermode, EqpProcessStatus);

public:



};

#endif // LineControl_h__
