#pragma once

#include "../Module/Control/ColorStatic.h"
#include "../Module/Control/ClrButton.h"
#include "../Module/Control/NumEdit.h"

#include "../Module/ListCtrl/CommonListCtrl.h"

#define MAX_MOTOR_PARA_LIST_QUAN	12

// CVisionAgentMachineMotorDlg 대화 상자

class CVisionAgentMachineMotorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentMachineMotorDlg)

public:
	CVisionAgentMachineMotorDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentMachineMotorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MACHINE_MOTOR_DIALOG  };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();

	bool m_bDialog_Entry;

	void InitCtrl();
	void InitDefaultPara();
	void InitListControlPara();
	void InitSpread();
	void ChangeSpreadData();
	void ChangeSelSpreadData(INT nSelNum);
	void InitUI();
	void UpdateUI();
	BOOL CheckChangeData();

	//TSpread	 *m_spread;
	CCommonListCtrl *m_pListCtrl;
	CStringArray	m_procsTexts;

	CStatic		m_stcName;
	CNumEdit	m_EditAutoVel;
	CNumEdit	m_EditAutoAccel;
	CNumEdit	m_EditAutoDecel;
	CNumEdit	m_EditManualHighVel;
	CNumEdit	m_EditManualMediumVel;
	CNumEdit	m_EditManualLowVel;
	CNumEdit	m_EditSafetyPosMin;
	CNumEdit	m_EditSafetyPosMax;
	CNumEdit	m_EditOrginPos;
	CNumEdit	m_EditMaxVel;

	CString		m_AxisName[AXIS_MAX];
	LRESULT OnListCtrlClick(WPARAM wParam, LPARAM lParam);

	int m_ListClickIndex;
	void SetItemValue(int StickIndex);
	afx_msg void OnBnClickedMachineMotorUpdateBtn();
	//afx_msg void OnNMClickVisonAgentModelStickList(NMHDR *pNMHDR, LRESULT *pResult);
	
};
