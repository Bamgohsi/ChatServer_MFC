#include "pch.h"
#include "LogManager.h"
#include "IniConfig.h"

CLogManager g_log;

CLogManager::CLogManager()
{

}

CLogManager::~CLogManager()
{

}

static CCriticalSection csLogWrite;

void CLogManager::WriteLog(MsgType type, CString data)
{
	CSingleLock lock(&csLogWrite, TRUE);
	FormatMsgType(type);

	CString LogFilePath;

	LogFilePath.Format(_T("%s\\%s"), g_iniConfig.logDir, typeDirStr); // g_iniConfig.logDir = _T("D:\\BGH\\ChattingProgram\\ChatServer\\Log")

	if (GetFileAttributes(LogFilePath) == INVALID_FILE_ATTRIBUTES) // 저장경로에 디렉토리 파일이 없으면 생성
	{
		SHCreateDirectoryEx(NULL, LogFilePath, NULL);
	}

	CTime now = CTime::GetCurrentTime();
	CString ymd = now.Format(_T("%Y%m%d"));

	CString filePath;
	filePath.Format(_T("%s\\%s\_%s.txt"), LogFilePath, ymd, typeDirStr);

	FILE* fp = NULL;
	_wfopen_s(&fp, filePath.GetString(), L"a, ccs=UTF-8");
	if (!fp)
	{
		return;
	}
	fputws(data + _T("\n"), fp);

	fclose(fp);
}

void CLogManager::DelLog()
{

}

void CLogManager::FormatMsgType(MsgType type)
{
	switch (type)
	{
	case MsgType::Error:		// 에러 
		typeDirStr = "Error";
		break;
	case MsgType::Send:			// send
		typeDirStr = "Send";
		break;
	case MsgType::Receive:		// receive
		typeDirStr = "Receive";
		break;
	case MsgType::Setting:		// setting
		typeDirStr = "Setting";
		break;
	default:
		typeDirStr = "Init";	// default
		break;
	}
}

