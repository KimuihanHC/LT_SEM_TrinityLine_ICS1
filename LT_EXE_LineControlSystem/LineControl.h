//*****************************************************************************
// Filename	: 	LineControl.h
// Created	:	2021/11/18 - 17:32
// Modified	:	2021/11/18 - 17:32
//
// Author	:	piring
//	
// Purpose	:	?€λΉ? ?΅μ  λ°??Έλ€???μ΄
//*****************************************************************************
#ifndef LineControl_h__
#define LineControl_h__

#pragma once

#include "LineInfo.h"

//-----------------------------------------------------------------------------
// ?€λΉ? ?΅μ  λ°??Έλ€???μ΄
//-----------------------------------------------------------------------------
class CLineControl : public CLineInfo
{
public:
	CLineControl();
	virtual ~CLineControl();

protected:

	// ?μΌ ?λ³΄(?)

	

	// Loader
	// Tester, Tester, ....
	// Return
	// Unloader


	// κ²???λ£
	// Recv_CompleteTest( ok / ng );
	// Send_Reply_CompleteTest();



	// ?μ‘: ?λ² ?κ° ?κΈ°??	// Send_TimeSync ( server_time );

	// ?μ‘: ?¬μ©??κΆν, ?Έμ΄, ?κ°

	// ?μ‘: ?€λΉ ?μ΄ (?€λΉ???€λΉ μ§ν ?ν λ³κ²?
	// Send_Request_Change_EqpProcessStatus( EqpProcessStatus );

	// ?μ : ?λ

	// ?μ‘: ?΄μ© λͺ¨λ (?€λΉ???΄μ© λͺ¨λ λ³κ²?
	// Send_Request_Change_EqpOperMode( EqpOperMode );

	// ?μ : ?€λΉ ?ν

	// ?μ : RFID ?±λ‘
	// ?μ : RFID ?¬μ ?ΉμΈ ?μ²­
	// ?μ : RFID κ²??κ²°κ³Ό ?μ²­
	// ?μ : RFID κ²??κ²°κ³Ό ?±λ‘
	// ?μ : RFID ?±λ‘ ?΄μ 

	// ?μ‘: All Socket Clear

	// ?μ : λ²νΌ ?ν	
	// Recv_RequestArriveSocket( fromEqp, BufferType, RFID);
	// Send_ReplyArriveSocket( test/bypass/wait );

	// ?μ : μ»¨λ² ?΄μ΄ ?ν


	// ?μ : κ²??ZONE  ?ν (L/R)

	// ?μ : ?€λΉ μ΄κΈ° ?ν (Loader)
	// ?μ : ?€λΉ μ΄κΈ° ?ν (Unloader)
	// ?μ : ?€λΉ μ΄κΈ° ?ν (κ²?¬κΈ°)
	// Recv_EqpStatus ( buffer, Zone, return, eqpOpermode, EqpProcessStatus);

public:



};

#endif // LineControl_h__
