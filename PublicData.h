#pragma once

//#include <afxstr.h>   // CString
//#include <windows.h>  // DWORD

enum class MsgType : int
{
	Error = 0,
	Send = 1,
	Receive = 2,
	Setting = 3,
	init = 4
};

enum class RoleType
{
	Server,
	Client
};

//struct IniConfig
//{
//	//CString ip = L"127.0.0.1"; // 현재 사용 X
//	CString logDir;
//	CString iniDir;
//	int delDay;
//};