#pragma once

// CProcessPpaDlg ��ȭ �����Դϴ�.

class CProcessPpaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessPpaDlg)
public:

	int m_nTopBottomFlag;

	int m_nCx;
	int m_nCy;

	CProcessPpaDlg( CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CProcessPpaDlg();

	void RecalcLayout();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROCESS_PPA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual 
BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual BOOL DestroyWindow();
};