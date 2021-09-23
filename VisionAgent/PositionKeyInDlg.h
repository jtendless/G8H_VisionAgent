#pragma once
enum eFindType{
	eGLASS = 0,
	eFilm		 = 1,

};

// CPositionKeyInDlg 대화 상자
#ifndef MIL_NOT_USE
class CWkLibVision;
#endif
class CPositionKeyInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPositionKeyInDlg)
private : 
	void				PeekAndPump();
	BOOL			m_bResult = FALSE;
public:
	CPositionKeyInDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPositionKeyInDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_POSITION_KEY_IN };
#endif
#ifndef MIL_NOT_USE
	CWkLibVision *m_pCamera;

	void SetCameraInfo(CWkLibVision * ImageProc, eFindType FindType);
#endif	
	BOOL				Delay();
	BOOL				GetResult(DOUBLE &dX, DOUBLE &dY);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGetManualPos();
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
