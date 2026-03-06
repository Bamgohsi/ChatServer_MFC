#include "pch.h"
#include "IniConfig.h"

IniConfig g_iniConfig = {
	_T("192.168.0.191"),									// connectIpAddr
	_T("Server"),											// roleType
	_T("D:\\BGH\\ChattingProgram\\ChatServer\\Log"),		// logDir
	30,														// delDay
	_T("D:\\BGH\\ChattingProgram\\ChatServer\\config.ini")	// iniDir
};