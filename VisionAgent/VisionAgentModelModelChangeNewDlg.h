#pragma once

#include "../Module/Control/NumEdit.h"

// CVisionAgentModelModelChangeNewDlg 대화 상자입니다.
class CVisionAgentModelModelChangeDlg;
class CVisionAgentModelModelChangeNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentModelModelChangeNewDlg)

public:
	CVisionAgentModelModelChangeNewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentModelModelChangeNewDlg();

	CVisionAgentModelModelChangeDlg *m_pParent;

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MODEL_CHANGE_NEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void InitCtrl();
	void InitDefaultPara();
	BOOL m_bOKFlag;
	CString m_strNewDirName;
	CEdit m_EditName;
	CNumEdit m_EditNo;
	WORD m_wRecipID;
	BOOL m_bIsAlignStick;
	CComboBox m_ComboStickRGB;
	CButton m_checkIsAlignStick;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedModelChangeNewCloseBtn();
	int ModeSelect;
	int ModelIndex;
	BOOL OkFlag;
	afx_msg void OnBnClickedVisonAgentModelModelChangeNewBtnOk();
	afx_msg void OnDestroy();
};
