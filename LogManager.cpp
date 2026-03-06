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
	filePath.Format(_T("%s\\%s_%s.txt"), LogFilePath, ymd, typeDirStr);

	FILE* fp = NULL;
	_wfopen_s(&fp, filePath.GetString(), L"a, ccs=UTF-8");
	if (!fp)
	{
		return;
	}
	fputws(data + _T("\n"), fp);

	fclose(fp);
}

void CLogManager::DelLog(CString logPath) // 현재 재귀적으로 모두 삭제함
{
	CFileFind finder;

	BOOL bWorking = TRUE;
	bWorking = finder.FindFile(logPath + _T("\\*.*"));

	COleDateTime now = COleDateTime::GetCurrentTime();		// 햔재 날짜
	COleDateTimeSpan delDay(g_iniConfig.delDay, 0, 0, 0);	// 삭제 기준날짜


	while (bWorking)
	{
		bWorking = finder.FindNextFile();	// 다음 파일 검색
		if (finder.IsDots()) continue;		// 찾은 파일이 디렉토리면 continue
		if (finder.IsDirectory())			// 현재 디렉토리면 DelLog 재귀 호출해서 디렉토리내 모든 파일 순회
		{
			DelLog(finder.GetFilePath());
			//RemoveDirectory(finder.GetFilePath()); // 빈 디렉토리 삭제
		}
		else
		{
			int y = _ttoi(finder.GetFileName().Mid(0, 4));
			int m = _ttoi(finder.GetFileName().Mid(4, 2));
			int d = _ttoi(finder.GetFileName().Mid(6, 2));

			COleDateTime fileDate(y, m, d, 0, 0, 0);	// 로그파일의 yyyymmdd형식을 캡슐화

			if (fileDate.GetStatus() != COleDateTime::valid) continue;	// 유효하지 않은 파일이름이면 continue

			if ((fileDate + delDay) < now)
				DeleteFile(finder.GetFilePath());
		}
	}
	finder.Close();

	//CTime now = CTime::GetCurrentTime();

	// if(g_iniConfig.delDay)
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