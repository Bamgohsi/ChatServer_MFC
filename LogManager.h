#pragma once
#include "PublicData.h"

class CLogManager
{
public:
	CLogManager();
	~CLogManager();
	void WriteLog(MsgType type, CString data);
	void DelLog();
	//로그를 타입과 데이터를 매개인자로 받아서 로그를 만드는 함수
	//로그를 ini삭제날짜로 자동삭제하는 함수

private:
	CString typeDirStr;
	void FormatMsgType(MsgType type);
};

extern CLogManager g_log;

