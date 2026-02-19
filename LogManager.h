#pragma once
class CLogManager
{
public:
	CLogManager();
	~CLogManager();

private:
	CString m_serIp;
	CString m_cliIp;
	CString m_saveLogPath;
	int m_delDay;
};

