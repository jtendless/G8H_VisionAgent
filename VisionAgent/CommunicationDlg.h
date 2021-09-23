#pragma once


// CCommunicationDlg ��ȭ �����Դϴ�.
#include "CommunicationAIODlg.h"
#include "CommunicationDIODlg.h"

class CCommunicationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommunicationDlg)

public:
	CCommunicationDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCommunicationDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_COMMUNICATION };
#endif

	//BOOL RecalcLayout();
	//BOOL ShowData();
public:
	CCommunicationAIODlg	*m_pCommunicationAIODlg;
	CCommunicationDIODlg	*m_pCommunicationDIODlg;
	CColorStatic			m_Comm_Lamp[2];
	void	ShowDlg(int nDlgNo);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnDio();
	afx_msg void OnBnClickedBtnAio();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnCommunicationClose();
};
