#pragma once

// CProcessPpaDlg 대화 상자입니다.

class CProcessPpaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessPpaDlg)
public:

	int m_nTopBottomFlag;

	int m_nCx;
	int m_nCy;

	CProcessPpaDlg( CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CProcessPpaDlg();

	void RecalcLayout();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROCESS_PPA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual 
BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual BOOL DestroyWindow();
};