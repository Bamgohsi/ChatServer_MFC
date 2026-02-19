// SettingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 대화 상자

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DLG, pParent)
{
	m_Ip = m_ini.GetIp();						// 생성자 이니셜라이져로 멤버변수 초기화할 경우
	m_SaveLogPath = m_ini.GetSaveLogPath();		// 헤더파일에서 m_ini가 멤버변수들보다 아래에 있으면 미생성 객체 접근으로 크래시 가능성
	m_DelDay = m_ini.GetDelDay();
}

CSettingDlg::~CSettingDlg()
{
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSettingDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSettingDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CSettingDlg 메시지 처리기

BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IPADDR, m_Ip);
	DDX_Text(pDX, IDC_MEDBR_LOGPATH, m_SaveLogPath);
	DDX_Text(pDX, IDC_CBXEX_DELDAY, m_DelDay);
	DDX_Control(pDX, IDC_CBXEX_DELDAY, m_delDay_combo);
}

void CSettingDlg::OnBnClickedBtnSave()
{
	if(!UpdateData(TRUE))	return; // DDX 변환/검증 실패 시

	if (m_Ip == L"0.0.0.0" || m_SaveLogPath.IsEmpty() || m_DelDay <= 0)
	{
		AfxMessageBox(L"올바른 값을 입력하세요");
		return;
	}
	m_ini.SaveIni(m_Ip, m_SaveLogPath, m_DelDay);
	AfxMessageBox(L"저장되었습니다.");
}


void CSettingDlg::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDCANCEL);
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_delDay_combo.AddString(_T("1"));
	m_delDay_combo.AddString(_T("3"));
	m_delDay_combo.AddString(_T("7"));
	m_delDay_combo.AddString(_T("30"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
