
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

	//m_ini.SaveIni();	//ini default 값으로 생성 및 저장

	m_socCom = NULL;
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
	m_socCom->Send(ok, (int)strlen(ok) + 1);	//소켓이 연결되었다는 것을 클라이어늩에게 알리기 위해 Send 함수로 "접속성공"이라는 문자열을 보냄

	UpdateData(FALSE);
	return TRUE;
}

// 데이터를 보내는 것은 소켓 클래스의 멤버 함수인 Send를 이용
// 데이터를 받을 때는 통신 소켓 클래스에 오버라이딩한 OnReceive 메시지 함수를 사용

LPARAM CChatServerDlg::OnReceive(UINT wParam, LPARAM lParam)
{
	char pTmp[256];
	memset(pTmp, 0, 256);
	m_socCom->Receive(pTmp, 256);

	// 수신된 ANSI 데이터를 유니코드(T)로 변환 (CP_ACP 명시)
	CString strTmp = (CString)CA2T(pTmp, CP_ACP);

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

	char pTmp[256];
	memset(pTmp, 0, 256);

	// CP_ACP를 명시하여 한글 인코딩을 확실히 잡아줍니다.
	strcpy_s(pTmp, 256, (LPCSTR)CT2A(m_strSend, CP_ACP));

	m_socCom->Send(pTmp, 256);

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
	if (m_setDlg.GetSafeHwnd() != NULL)
	{
		return;
	}
	m_setDlg.m_Ip = m_ini.GetIp();
	m_setDlg.m_SaveLogPath = m_ini.GetSaveLogPath();
	m_setDlg.m_DelDay = m_ini.GetDelDay();

	m_setDlg.Create(IDD_SETTING_DLG, this);
	m_setDlg.ShowWindow(SW_SHOW);
}