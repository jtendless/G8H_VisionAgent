#pragma once


// CVisionAgentModelModelChangeRenameDlg 대화 상자입니다.

class CVisionAgentModelModelChangeDlg;
class CVisionAgentModelModelChangeRenameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentModelModelChangeRenameDlg)

public:
	CVisionAgentModelModelChangeRenameDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentModelModelChangeRenameDlg();

	CVisionAgentModelModelChangeDlg *m_pParent;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MODEL_MODEL_CHANGE_RENAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedVisonAgentModelModelChangeNewBtnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedModelChangeNewCloseBtn();
};
