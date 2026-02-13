// SocServer.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "SocServer.h"


// CSocServer

CSocServer::CSocServer()
{
}

CSocServer::~CSocServer()
{
}


// CSocServer 멤버 함수

// 소켓 클래스에서는 소켓의 메시지(On으로 시작하는 함수)만을 처리하고, 실제 동작은 메인 프로그램에서 수행
// 소켓 클래스와 메인 윈도우를 연결시키는 것이 필요 -> Init 함수

void CSocServer::Init(HWND hWnd)
{	// 메인 윈도우 포인터 받기
	m_hWnd = hWnd;
}

// 클라이언트에서 접속 요청이 올 경우 OnAccept 함수가 호출됨
// OnAccept 함수가 호출되면 접속 요청할 한 소켓과 다른 소켓을 연결하기 위해 
// Accept 함수를 호출한 뒤 메인 윈도우에 OnAccept 함수가 호출되었다는 것을 알려줌
void CSocServer::OnAccept(int nErrorCode)
{
    // 중요: Accept 하기 전에 통신용 소켓(m_socCom)이 생성되어 있어야 합니다.
    // 만약 이미 소켓 핸들이 있다면 닫고 새로 생성합니다.
    if (m_socCom.m_hSocket != INVALID_SOCKET) {
        m_socCom.Close();
    }

    // Accept의 인자로 m_socCom을 넘겨줍니다.
    if (Accept(m_socCom))
    {
        // 접속 성공 시 메인 윈도우에 알림
        SendMessage(m_hWnd, UM_ACCEPT, 0, 0);
    }

    CSocket::OnAccept(nErrorCode);
}

// 메인 윈도우에서는 m_socCom을 얻어서 통신을 처리
CSocCom* CSocServer::GetAcceptSocCom()
{	// 통신 소켓을 return
	// 반환되는 통신 소켓은 클라이언트와 연결됨
	return &m_socCom;
}