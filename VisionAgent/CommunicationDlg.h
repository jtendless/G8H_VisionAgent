#pragma once


// CCommunicationDlg 대화 상자입니다.
#include "CommunicationAIODlg.h"
#include "CommunicationDIODlg.h"

class CCommunicationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommunicationDlg)

public:
	CCommunicationDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCommunicationDlg();

// 대화 상자 데이터입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
