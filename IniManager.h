#pragma once
#include "PublicData.h"

class CIniManager {
public:
	CIniManager();
	~CIniManager();

public:
	void SaveIni();										// 현재 멤버변수들을 ini파일에 저장하는 함수
	void SaveIni(CString lpath, int dday);				// 매개인자로 넘겨준 값들을 ini파일에 저장하는 함수(오버로딩)
	void LoadIni();										// 현재 ini파일의 값을 불러와 멤버변수에 저장하는 변수
	IniConfig GetConfig();
private:
	int m_delDay;			// 로그삭제날짜 변수
	IniConfig m_iniCfg;
};