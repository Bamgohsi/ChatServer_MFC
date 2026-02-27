#include "pch.h"
#include "FrameManager.h"

CFrameManager::CFrameManager()
{
	mod = "Server";
}

CFrameManager::~CFrameManager()
{

}
//CString FormatSendFrame(MsgType type, ProgramMod programMod, CString msg); // [메시지 종류][서버/클라여부][메시지][/메시지 종류] 이렇게 구성
//CString FormatLogFrame(MsgType type, ProgramMod programMod, CString msg); // [시간, 서버/클라 구분, 타입, 데이터] 이렇게 구성

CString CFrameManager::ParseType(CString msg)
{
	int type_pos = msg.Find(L"]");
	if (type_pos == -1)
		return msg;
	CString parsetype = msg.Mid(0, type_pos + 1);
	return parsetype;
}
CStringA CFrameManager::FormatMsgSendFrame(MsgType type, CString msg) // [메시지 종류][서버/클라여부][메시지][/메시지 종류] 이렇게 구성
{
	CString formatmsg;

	switch (type)
	{
	case MsgType::Error:		// 에러 
		break;
	case MsgType::Send:			// send
		formatmsg.Format(L"[Send][%s][%s][/Send]", mod, msg);
		break;
	case MsgType::Receive:		// receive
		break;
	case MsgType::Setting:		// setting
		break;
	case MsgType::Heartbeat:	// hearbeat
		formatmsg.Format(L"[Heartbeat][%s][%s][/Send]", mod, msg);
		break;
	default:
		break;
	}
	return CT2A(formatmsg, CP_ACP);
}
CStringA CFrameManager::FormatHbSendFrame()
{
	CString formathb = (L"[HB][0][/HB]");

	return  CT2A(formathb, CP_ACP);;
}
CString CFrameManager::FormatLogFrame(MsgType type, CString msg) // [시간, 서버/클라 구분, 타입, 데이터] 이렇게 구성
{
	switch (type)
	{
	case MsgType::Error :		// 에러 
		break;
	case MsgType::Send :		// send
		break;
	case MsgType::Receive :		// receive
		break;
	case MsgType::Setting :		// setting
		break;
	case MsgType::Heartbeat :	// hearbeat
		break;
	default:
		break;
	}
	return L"ToDo";
}
CString CFrameManager::ParseMsg(CString msg)
{
	//	프로토콜 통일후 삭제 필요
	if (msg.Mid(0) == "Pong\n")
		return msg;
	int left_pos = msg.Find(L"[Client][");
	int right_pos = msg.Find(L"][/Send]");
	if (left_pos == -1 || right_pos == -1)
		return msg;
	left_pos += (int)strlen("[Client][");
	CString parsemsg = msg.Mid(left_pos, right_pos - left_pos);
	return parsemsg;
}
//enum class MsgType : int
//{
//	Error = 0,
//	Send = 1,
//	Receive = 2,
//	Setting = 3,
//	Heartbeat = 4,
//};