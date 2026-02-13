// IniManager.cpp: 구현 파일
// 
#include "pch.h"
#include "IniManager.h"

CIniManager::CIniManager()
	: m_serIp(_T("127.0.0.1"))
	, m_saveLogPath(_T("D:\\BGH\\ChattingProgram\\ChatServer\\logfiles"))
	, m_delDay(30)
	, m_saveIniPath(_T("D:\\BGH\\ChattingProgram\\ChatServer\\config.ini")) //config.ini저장위치
{
	if (::GetFileAttributes(m_saveIniPath) != INVALID_FILE_ATTRIBUTES)
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
	delDay.Format(_T("%d"), m_delDay);

	::WritePrivateProfileString(_T("SERVER"), _T("IP"), m_serIp, m_saveIniPath);
	::WritePrivateProfileString(_T("SERVER"), _T("삭제날짜"), delDay, m_saveIniPath);
	::WritePrivateProfileString(_T("SERVER"), _T("Log저장위치"), m_saveLogPath, m_saveIniPath);
}
void CIniManager::SaveIni(CString ip, CString lpath, int dday)
{
	if (!ip.IsEmpty())      m_serIp = ip;
	if (!lpath.IsEmpty())   m_saveLogPath = lpath;
	if (dday > 0)           m_delDay = dday;

	SaveIni();
}

void CIniManager::LoadIni()
{
	TCHAR szBuf[256];

	// IP 읽기
	::GetPrivateProfileString(_T("SERVER"), _T("IP"), _T("127.0.0.1"), szBuf, 256, m_saveIniPath);
	m_serIp = szBuf;

	// 경로 읽기
	::GetPrivateProfileString(_T("SERVER"), _T("Log저장위치"), _T("D:\\BGH\\ChattingProgram\\ChatServer"), szBuf, 256, m_saveIniPath);
	m_saveLogPath = szBuf;

	// 삭제 날짜 읽기
	m_delDay = ::GetPrivateProfileInt(_T("SERVER"), _T("삭제날짜"), 30, m_saveIniPath);
}

CString CIniManager::GetIp() { return m_serIp; }
CString CIniManager::GetSaveLogPath() { return m_saveLogPath; }
int     CIniManager::GetDelDay() { return m_delDay; }
