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
	afx_msg void OnBnClickedBtnSave();					// 저장 버튼 이벤트. 현재 멤버변수들의 값으로 ini파일에 저장하는 메세지 함수
	afx_msg void OnBnClickedBtnCancel();				// 취소 버튼 이벤트. 모달 방식 다이얼로그 종료시 ChatServerDlg.cpp의 함수 스코프내 CSettingDlg 객체가 소멸되므로 내부 멤버변수도 소멸

private:
	IniConfig m_iniCfg;			// IniConfig 구조체
	CIniManager m_iniMgr;		// IniManager 객체
	CComboBox m_delDay_combo;	// 콤보박스 클래스 객체 (삭제날짜 목록 추가용도)
public:
	virtual BOOL OnInitDialog();
};