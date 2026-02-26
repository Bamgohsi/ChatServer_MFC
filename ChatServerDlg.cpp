
// ChatServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatServerDlg 대화 상자



CChatServerDlg::CChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
	, m_strSend(_T(""))
	, m_connected(false)
	, m_connecting(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strSend);
	DDX_Control(pDX, IDC_LIST_CHAT, m_list);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatServerDlg::OnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_SET, &CChatServerDlg::OnBnClickedBtnSet)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChatServerDlg 메시지 처리기

BOOL CChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	SetTimer(1, 1000, NULL); // 타이머 세팅

	SetHBPiCtrl();	// 하트비트 체크용 픽처컨트롤 초기세팅

	//m_socCom = NULL;
	// 서버 소켓을 생성(포트번호 5000)
	m_socServer.Create(5000);
	// 클라이언트의 접속을 기다림
	m_socServer.Listen();
	// 소켓 클래스와 메인 윈도우(여기에서는 CChatServerDlg)를 연결
	m_socServer.Init(this->m_hWnd);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 클라이언트 연결 요청이 왔기 때문에 Accept 함수로 접속
// 실제 접속을 담당하는 것은 CSocServer
// 이렇게 접속한 소켓은 GetAcceptSocCom을 이용해 얻어옴
// OnAccept 실행 이후 서버용 소켓인 m_socServer의 역할은 끝나고, 실제 모든 통신은 통신용 소켓인 m_socCom을 이용

LPARAM CChatServerDlg::OnAccept(UINT wParam, LPARAM lParam)
{	// 클라이언트에서 접속 요청이 왔을 때
	// m_strStatus = "접속성공";

	// 통신용 소켓을 생성한 뒤
	m_socCom = m_socServer.GetAcceptSocCom();
	// 서버소켓과 통신소켓을 연결한다.
	m_socCom->Init(this->m_hWnd);

	const char* ok = "접속성공";
	m_socCom->Send(ok, (int)strlen(ok) + 1);	//소켓이 연결되었다는 것을 클라이언트에게 알리기 위해 Send 함수로 "접속성공"이라는 문자열을 보냄

	UpdateData(FALSE);
	//SetTimer(1, 1000, NULL);
	m_lastRecvTick = GetTickCount();
	m_connected = true;
	m_connecting = false;

	return TRUE;
}

// 데이터를 보내는 것은 소켓 클래스의 멤버 함수인 Send를 이용
// 데이터를 받을 때는 통신 소켓 클래스에 오버라이딩한 OnReceive 메시지 함수를 사용

LPARAM CChatServerDlg::OnReceive(UINT wParam, LPARAM lParam)
{
	char pTmp[256];
	memset(pTmp, 0, 256);
	if (m_socCom->Receive(pTmp, sizeof(pTmp)) <= 0)	//
	{
		// TODO : Error 코드 로그 기록
		return 0;
	}

	// 수신된 ANSI 데이터를 유니코드(T)로 변환 (CP_ACP 명시)
	CString strTmp = (CString)CA2T(pTmp, CP_ACP);


	m_lastRecvTick = GetTickCount();
	if (strTmp == _T("Pong\n"))				// 추후 message type으로 수정필요
	{
		m_lastRecvTick = GetTickCount();
		return 0;
	}

	int i = m_list.GetCount();
	m_list.InsertString(i, _T("[상대] : ") + strTmp);


	return 0;
}

// [전송] 버튼을 클릭했을 때
void CChatServerDlg::OnClickedBtnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_socCom == nullptr)
	{
		AfxMessageBox(L"클라이언트가 아직 연결되지 않았습니다.");
		return;
	}
	UpdateData(TRUE);
	if (m_strSend.IsEmpty()) return;

	//char pTmp[256];
	//memset(pTmp, 0, 256);

	// CP_ACP를 명시하여 한글 인코딩을 확실히 잡아줍니다.
	//strcpy_s(pTmp, 256, (LPCSTR)CT2A(_T("[Send]") + m_strSend + _T("[/Send]"), CP_ACP));
	CStringA pTmp = CT2A(_T("[Send]") + m_strSend + _T("[/Send]"), CP_ACP);

	m_socCom->Send((LPCSTR)pTmp, pTmp.GetLength());

	// 내 리스트박스에 표시
	m_list.InsertString(m_list.GetCount(), _T("[나] : ") + m_strSend);

	m_strSend = _T("");
	UpdateData(FALSE);
}


BOOL CChatServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN &&											// 키입력이 들어왔을 때
		pMsg->wParam == VK_RETURN &&											// 마우스 커서가 텍스트 입력창에 있고
		GetFocus()->GetSafeHwnd() == GetDlgItem(IDC_EDIT_INPUT)->GetSafeHwnd())	// 엔터키를 입력한다면
	{
		OnClickedBtnSend(); // 전송버튼이벤트 발생
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CChatServerDlg::OnBnClickedBtnSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CSettingDlg dlg;
	dlg.DoModal();
	
}
//int i = 0;
void CChatServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_connected && nIDEvent == 1)
	{
		m_lastRecvTick % 2000 < 1000 ? SetHbColor(m_brushGreen) : SetHbColor(m_brushBG);

		m_socCom->Send("Ping\n", strlen("Ping\n"));		// 1초마다 클라이언트에게 "Ping\n" 전송 // 수정필요.

		DWORD now = GetTickCount();

		if (now - m_lastRecvTick >= 5000)	//현재시간과 마지막으로 수신한 
		{
			SetHbColor(m_brushRed);
			m_lastRecvTick = GetTickCount();
			m_list.InsertString(m_list.GetCount(), _T("error : 연결 끊김 재접속 시도"));

			m_socCom->Close();	// 타임아웃시 기존 통신용 소켓 정리
			m_connected = false;
			m_socCom = NULL;

			return;
		}

		return;
	}

	if (!m_connecting && !m_connected && nIDEvent == 1)			// 통신연결 상태가 아닐경우
	{
		SetHbColor(m_brushYello);
		m_connecting = true;
		return;
	}
	//if (i++ % 5 == 0) AfxMessageBox(L"타임아웃"); // 테스트용
	
	CDialogEx::OnTimer(nIDEvent);
}
void CChatServerDlg::SetHbColor(CBrush &brush)
{
	CWnd* pWnd = GetDlgItem(IDC_STATIC_HB);
	CDC* pDC = pWnd->GetDC(); // DC 얻기
	CRect rect;
	pWnd->GetClientRect(&rect); // 영역 크기 가져오기

	// 2. 브러시 및 펜 설정 (필요시)
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	CGdiObject* oldPen = pDC->SelectStockObject(NULL_PEN);

	// 3. 원 그리기 (직사각형에 내접하는 타원/원)
	// rect.left, top, right, bottom을 사용하여 중심 지정
	pDC->Ellipse(rect);
	pDC->SelectObject(oldPen);

	// 4. 자원 해제
	pDC->SelectObject(pOldBrush);
	pWnd->ReleaseDC(pDC);
}

void CChatServerDlg::SetHBPiCtrl()
{
	if (CWnd* p = GetDlgItem(IDC_STATIC_HB))
	{
		p->ModifyStyle(WS_BORDER, 0);           // 1) 일반 테두리 제거
		p->ModifyStyle(SS_BLACKFRAME, 0);      // 2) Static 프레임 제거(있을 경우)
		p->ModifyStyle(SS_GRAYFRAME, 0);
		p->ModifyStyle(SS_ETCHEDFRAME, 0);

		p->ModifyStyleEx(WS_EX_CLIENTEDGE, 0); // 3) 3D 테두리 제거(있을 경우)

		// 스타일 변경 반영
		p->SetWindowPos(nullptr, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}

	m_brushYello.CreateSolidBrush(RGB(255, 255, 0));				// 노란색 원
	m_brushRed.CreateSolidBrush(RGB(255, 0, 0));					// 초록색 원
	m_brushGreen.CreateSolidBrush(RGB(0, 255, 0));					// 빨간색 원
	m_brushBG.CreateSolidBrush(GetSysColor(COLOR_3DFACE));			// 백그라운드색 원
}