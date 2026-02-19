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
	, m_Ip(m_ini.GetIp())
	, m_SaveLogPath(m_ini.GetSaveLogPath())
	, m_DelDay(m_ini.GetDelDay())
{
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
}

void CSettingDlg::OnBnClickedBtnSave()
{
	UpdateData(TRUE);
	m_ini.SaveIni(m_Ip, m_SaveLogPath, m_DelDay);
	AfxMessageBox(L"저장되었습니다.");
}


void CSettingDlg::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDD_SETTING_DLG);
}
