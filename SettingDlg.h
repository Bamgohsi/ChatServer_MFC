#pragma once
#include "IniManager.h"

// CSettingDlg 대화 상자

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSettingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_DLG };
#endif

protected:

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancel();

private:
	CIniManager m_ini;
	CString m_Ip;
	CString m_SaveLogPath;
	int m_DelDay;
};