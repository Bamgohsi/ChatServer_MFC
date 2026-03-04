#include "pch.h"
#include "FrameManager.h"

CFrameManager::CFrameManager()
{
	pframe.roleStr = "Server";
	ProtocolFrameInit();
}

CFrameManager::~CFrameManager()
{

}
//CString FormatSendFrame(MsgType type, ProgramMod programMod, CString msg); // [메시지 종류][서버/클라여부][메시지][/메시지 종류] 이렇게 구성
//CString FormatLogFrame(MsgType type, ProgramMod programMod, CString msg); // [시간, 서버/클라 구분, 타입, 데이터] 이렇게 구성

CString CFrameManager::ParseType(CString msg)
{
	if (msg.Find(L"[") != 0)
		return msg;
	int type_pos = msg.Find(L"]");
	if (type_pos == -1)
		return msg;
	CString parsetype = msg.Mid(0, type_pos + 1);
	return parsetype;
}
CStringA CFrameManager::FormatMsgSendFrame(MsgType type, CString msg) // [메시지 종류][서버/클라여부][메시지][/메시지 종류] 이렇게 구성
{
	CString formatmsg;

	if (type == MsgType::Send)
	{
		pframe.typeOpenStr = "Send";
		pframe.typeCloseStr = "/Send";
	}
	formatmsg.Format(L"[%s][%s][%s][%s]", pframe.typeOpenStr, pframe.roleStr, msg, pframe.typeCloseStr);

	return CT2A(formatmsg, CP_ACP);
}
CStringA CFrameManager::FormatHbSendFrame()
{
	//CString formathb = (L"[HB][0][/HB]");

	return  CT2A(L"[HB][0][/HB]", CP_ACP);
}
CString CFrameManager::FormatLogFrame(MsgType type, CString data) // [시간, 서버/클라 구분, 타입, 데이터] 이렇게 구성
{
	CString logBuffer;
	now = CTime::GetCurrentTime();
	lframe.nowTimeStr.Format(L"%04d년-%02월-%02d일-%02d시-%02d분-%02d분-%02d초", now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond());
	FormatMsgType(type);
	lframe.dataStr = data;

	logBuffer.Format(L"[%s, %s, %s, %s]", lframe.nowTimeStr, lframe.roleStr, lframe.typeStr, lframe.dataStr);

	return logBuffer;
}

CString CFrameManager::ParseMsg(CString msg)
{
	CString msgBuffer = msg;

	int type_pos = ParseType(msg).GetLength();
	if (type_pos <= 0)
		return msg;

	msgBuffer = msg.Mid(type_pos, msg.GetLength() - type_pos - (type_pos + 1));

	int role_pos = msgBuffer.Find(L"]");
	if (role_pos == -1)
		return msg;

	int openMsgStr = role_pos + 2; // [Client][메시지내용] 에서 ][ 다음 위치 

	msgBuffer = msgBuffer.Mid(openMsgStr, msgBuffer.GetLength() - (openMsgStr + 1));

	return msgBuffer;
}

void CFrameManager::ProtocolFrameInit()
{
	pframe.typeOpenStr = "";
	pframe.msgText = "";
	pframe.typeCloseStr = "";
}

void CFrameManager::FormatMsgType(MsgType type)
{
	switch (type)
	{
	case MsgType::Error:		// 에러 
		lframe.typeStr = "Error";
		break;
	case MsgType::Send:		// send
		lframe.typeStr = "Send";
		break;
	case MsgType::Receive:		// receive
		lframe.typeStr = "Receive";
		break;
	case MsgType::Setting:		// setting
		lframe.typeStr = "Setting";
		break;
	default:
		lframe.typeStr = "Init";
		break;
	}
}
//enum class MsgType : int
//{
//	Error = 0,
//	Send = 1,
//	Receive = 2,
//	Setting = 3,
//	Heartbeat = 4,
//};