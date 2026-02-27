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
	CString ParseType(CString msg);
	CStringA FormatMsgSendFrame(MsgType type, CString msg); // [메시지 종류][서버/클라여부][메시지][/메시지 종류] 이렇게 구성
	CStringA FormatHbSendFrame();
	CString FormatLogFrame(MsgType type, CString msg); // [시간, 서버/클라 구분, 타입, 데이터] 이렇게 구성
	CString ParseMsg(CString msg);
private:
	CString mod;
};
// 타입 종류는 [error, send, receive, setting]
// 메세지 규칙은 [메시지 종류][서버/클라여부][메시지][/메시지 종류]
// 로그가 기록될때는 [시간, 서버/클라 구분, 타입, 데이터] 이렇게 구성
// 
//enum class MsgType : int
//{
//	Error = 0,
//	Send = 1,
//	Receive = 2,
//	Setting = 3,
//	Heartbeat = 4,
//};

/* 필요한 함수
1. send할때 전송한 문자열을 대화창에 띄우고 난 후에 [문자열을 프로토콜 규칙에 맞게 더하는 함수]
2. send할때 [로그 규칙에 맞게 변환하는 함수](로그 저장함수는 로그매니저가 담당)
3. receive할때 우선 대화창에 띄우고 receive시 [문자열을 로그 규칙에맞게 반환하는 함수]
4. error발생시 [로그 규칙에 맞게 문자열을 반환하는 함수]
5. 

*/