#pragma once

#include "PublicData.h"

struct Frame
{
	MsgType msType;
	bool msid;
	CString msPayload;
};
class CFrameManager
{
public:
	CFrameManager();
	~CFrameManager();

public:
	
	/*
	send 보내기전에 문자열 넣어서 반환하는 함수
	receive 받을때 문자열 빼서 수신하는 함수
	하트비트에 문자열 추가해서 송수신.

	*/
};

