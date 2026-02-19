#include "pch.h"
#include "LogManager.h"
#include "IniManager.h"

CLogManager::CLogManager()
{
	CIniManager m_ini;
	m_delDay = m_ini.GetDelDay();
	m_serIp = m_ini.GetIp();
	m_saveLogPath = m_ini.GetSaveLogPath();
}

CLogManager::~CLogManager()
{

}