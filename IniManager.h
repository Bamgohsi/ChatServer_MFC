#pragma once

class CIniManager {
public:
	CIniManager();
	~CIniManager();

public:
	void SaveIni();
	void SaveIni(CString ip, CString lpath, int dday);
	void LoadIni();
	CString GetIp();
	CString GetSaveLogPath();
	int GetDelDay();

private:
	CString m_serIp;
	CString m_cliIp;
	CString m_saveLogPath;
	CString m_saveIniPath;
	int m_delDay;
};