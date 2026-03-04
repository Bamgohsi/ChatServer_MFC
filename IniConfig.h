#pragma once
#include <afxstr.h>

struct IniConfig
{
	//CString ip = L"127.0.0.1"; // 현재 사용 X
	CString logDir;
	int delDay;
	const CString iniDir;
};

extern IniConfig g_iniConfig;