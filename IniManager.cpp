// IniManager.cpp: 구현 파일
// 
#include "pch.h"
#include "IniManager.h"

CIniManager::CIniManager()
{
	m_iniCfg.logDir = _T("D:\\BGH\\ChattingProgram\\ChatServer\\logfiles");
	m_iniCfg.delDay = 30;
	m_iniCfg.iniDir = _T("D:\\BGH\\ChattingProgram\\ChatServer\\config.ini");


	if (::GetFileAttributes(m_iniCfg.iniDir) != INVALID_FILE_ATTRIBUTES)
	{
		LoadIni();
	}
	SaveIni();
}

CIniManager::~CIniManager()
{
}

void CIniManager::SaveIni()
{
	CString delDay;
	delDay.Format(_T("%d"), m_iniCfg.delDay);

	::WritePrivateProfileString(_T("SERVER"), _T("삭제날짜"), delDay, m_iniCfg.iniDir);
	::WritePrivateProfileString(_T("SERVER"), _T("Log저장위치"), m_iniCfg.logDir, m_iniCfg.iniDir);
}
void CIniManager::SaveIni(CString lpath, int dday)
{
	if (!lpath.IsEmpty())   m_iniCfg.logDir = lpath;
	if (dday > 0)           m_iniCfg.delDay = dday;

	SaveIni();
}

void CIniManager::LoadIni()
{
	TCHAR szBuf[256];

	// 경로 읽기
	::GetPrivateProfileString(_T("SERVER"), _T("Log저장위치"), _T("D:\\BGH\\ChattingProgram\\ChatServer"), szBuf, 256, m_iniCfg.iniDir);
	m_iniCfg.logDir = szBuf;

	// 삭제 날짜 읽기
	m_iniCfg.delDay = ::GetPrivateProfileInt(_T("SERVER"), _T("삭제날짜"), 30, m_iniCfg.iniDir);
}

IniConfig CIniManager::GetConfig()
{
	IniConfig cfg;
	cfg.logDir = m_iniCfg.logDir;
	cfg.iniDir = m_iniCfg.iniDir;
	cfg.delDay = m_iniCfg.delDay;

	return cfg;
}