#pragma once

//#include <afxstr.h>   // CString
//#include <windows.h>  // DWORD

enum class MsgType : int
{
	Error		= 0,
	Send		= 1,
	Receive		= 2,
	Setting		= 3,
	Heartbeat	= 4
};

struct IniConfig
{
	//CString ip = L"127.0.0.1"; // 현재 사용 X
	CString logDir;
	CString iniDir;
	int delDay;
};

enum class ProgramMod : bool
{ // enum class는 enum 처럼 int 자동 형변환이 되지 않으므로 static_cast<int> 로 명시적 형변환이 필요함.
	Server = 0,
	Client = 1
};