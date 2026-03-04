// IniManager.cpp: 구현 파일
// 
#include "pch.h"
#include "IniManager.h"
#include "IniConfig.h"

CIniManager::CIniManager()
{
	if (::GetFileAttributes(g_iniConfig.iniDir) != INVALID_FILE_ATTRIBUTES)
	{
		LoadIni();
	}
	else
	{
		SaveIni();
	}
}

CIniManager::~CIniManager()
{
}

void CIniManager::SaveIni()
{
	CString delDay;
	delDay.Format(_T("%d"), g_iniConfig.delDay);

	::WritePrivateProfileString(_T("SERVER"), _T("삭제날짜"), delDay, g_iniConfig.iniDir);
	::WritePrivateProfileString(_T("SERVER"), _T("Log저장위치"), g_iniConfig.logDir, g_iniConfig.iniDir);
}
void CIniManager::SaveIni(CString lpath, int dday)
{
	if (!lpath.IsEmpty())   g_iniConfig.logDir = lpath;
	if (dday > 0)           g_iniConfig.delDay = dday;

	SaveIni();
}

void CIniManager::LoadIni()
{
	TCHAR szBuf[256];

	// 경로 읽기
	::GetPrivateProfileString(_T("SERVER"), _T("Log저장위치"), _T("D:\\BGH\\ChattingProgram\\ChatServer"), szBuf, 256, g_iniConfig.iniDir);
	g_iniConfig.logDir = szBuf;

	// 삭제 날짜 읽기
	g_iniConfig.delDay = ::GetPrivateProfileInt(_T("SERVER"), _T("삭제날짜"), 30, g_iniConfig.iniDir);
}