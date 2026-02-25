#pragma once
#include "PublicData.h"

class CIniManager {
public:
	CIniManager();
	~CIniManager();

public:
	void SaveIni();										// 현재 멤버변수들을 ini파일에 저장하는 함수
	void SaveIni(CString ip, CString lpath, int dday);	// 매개인자로 넘겨준 값들을 ini파일에 저장하는 함수(오버로딩)
	void LoadIni();										// 현재 ini파일의 값을 불러와 멤버변수에 저장하는 변수
	CString GetIp();									// 멤버변수 m_serIp를 반환하는 Get함수
	CString GetSaveLogPath();							// 멤버변수 m_saveLogPath를 반환하는 Get함수
	int GetDelDay();									// 멤버변수 m_delDay를 반환하는 Get함수

private:
	CString m_serIp;		// 서버 ip 변수
	CString m_cliIp;		// 클라 ip 변수
	CString m_saveLogPath;	// 로그 저장경로 변수
	CString m_saveIniPath;	// ini파일 저장경로 변수
	int m_delDay;			// 로그삭제날짜 변수
	IniConfig m_ini;
};