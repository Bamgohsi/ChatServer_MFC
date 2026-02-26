
// ChatServerDlg.h: 헤더 파일
//

#pragma once

#include "stdAfx.h"
#include "IniManager.h"
#include "SettingDlg.h"

// CChatServerDlg 대화 상자
class CChatServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM IParam);	// 클라이언트 접속 요청이 왔을 때 실행되는 메세지 함수
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM IParam);	// 클라이언트에서 오는 데이터 수신할때 실행되는 메세지 함수
	DECLARE_MESSAGE_MAP()
private:
	CSocServer m_socServer;	// 서버용 소켓
	CSocCom* m_socCom;		// 통신용 소켓
	CString m_strSend;		// 입력창에 연결된 문자열 변수
	CListBox m_list;		// 채팅창 컨트롤 관리 객체
	DWORD m_lastRecvTick;	// 마지막 하트비트 체크 변수
	bool m_connected;		// 통신연결 상태확인 변수
	bool m_connecting;		// 통신연결중 상태확인 변수
	CBrush m_brushYello;	// 노란색 원 (통신 연결 대기 상태)
	CBrush m_brushRed;		// 빨간색 원 (통신 끊김. 하트비트 타임아웃)
	CBrush m_brushGreen;	// 초록색 원 (통신중, 백그라운드색 과 번갈아 출력)
	CBrush m_brushBG;		// 백그라운드색 원 (통신중, 초록색과 번갈아 출력)

public:
	afx_msg void OnClickedBtnSend();				// 채팅 전송 버튼 이벤트 메세지 함수
	virtual BOOL PreTranslateMessage(MSG* pMsg);	// 채팅을 엔터로 입력하는 가상함수(오버라이딩)
	afx_msg void OnBnClickedBtnSet();				// 세팅창 다이얼로그를 여는 메세지 함수
	afx_msg void OnTimer(UINT_PTR nIDEvent);		// 통신연결 및 하트비트 전용 타이머 메세지 함수
	void SetHbColor(CBrush &brush);					// 하트비트 체크용도인 픽처 컨트롤 색깔 세팅 함수
	void SetHBPiCtrl();
};
