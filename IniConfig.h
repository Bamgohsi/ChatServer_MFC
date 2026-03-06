#pragma once
#include <afxstr.h>

struct IniConfig
{
	CString connectIpAddr; // 클라타입일때 연결할 ip주소
	CString roleType;
	CString logDir;
	int delDay;
	const CString iniDir;
};

extern IniConfig g_iniConfig;