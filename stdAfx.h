#pragma once
#include <afxsock.h>		// 소켓 클래스 사용 위한 include
#include "SocServer.h"		// 서버용 소켓
#include "SocCom.h"			// 통신용 소켓

#define UM_ACCPET WM_USER+1	// 메인 윈도우에 메시지 보내기위한 구별자
							// 메인 윈도우(m_hWnd)에 SendMessage를 이용해 UM_ACCEPT라는 사용자 정의 메시지를 줌
#define UM_RECEIVE WM_USER+2 // UM_ACCEPT와 비슷한 역할