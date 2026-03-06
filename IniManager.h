#pragma once
#include "PublicData.h"

class CIniManager {
public:
	CIniManager();
	~CIniManager();

public:
	void SaveIni();										// 현재 멤버변수들을 ini파일에 저장하는 함수
	void LoadIni();										// 현재 ini파일의 값을 불러와 멤버변수에 저장하는 변수
private:
	int m_delDay;			// 로그삭제날짜 변수
};