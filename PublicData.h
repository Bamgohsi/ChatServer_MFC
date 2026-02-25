#pragma once

//#include <afxstr.h>   // CString
//#include <windows.h>  // DWORD

enum type
{
	Error,
	Send,
	Receive,
	Setting,
	Heartbit
};

struct IniConfig
{
	//CString ip = L"127.0.0.1"; // 현재 사용 X
	CString logDir;
	CString iniDir;
	int delDay;
};