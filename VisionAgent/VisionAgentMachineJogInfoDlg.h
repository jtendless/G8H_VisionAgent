#pragma once

#include "../Module/Control/ColorStatic.h"
#include "../Module/Control/ClrButton.h"
#include "../Module/Control/NumEdit.h"
#include "../Module/Motion/JogMotion.h"
//#include "../Module/Motion/MaskLoaderMotion.h"
// CVisionAgentMachineJogInfoDlg 대화 상자입니다.
class CVisionAgentDlg;
class CVisionAgentMachineJogInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentMachineJogInfoDlg)

public:
	CVisionAgentMachineJogInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentMachineJogInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VISION_AGENT_MACHINE_JOG_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitCtrl();
	void InitDefaultPara();
	//int m_bMotionControlFlag;

	enum_Axis m_eAxis;
	CString m_strAxis;

	//21.02.09 sjc add
	CString			m_StrTitleBar;
	CNumEdit		m_EditPosition;
	CNumEdit		m_EditVel;
	CNumEdit		m_EditAcc;
	CNumEdit		m_EditDec;
	CNumEdit		m_EditJogVelHight;
	CNumEdit		m_EditJogVelMid;
	CNumEdit		m_EditJogVelLow;

	CColorStatic	m_stcServoOnLed;
	CColorStatic	m_stcAlarmLed;
	CColorStatic	m_stcInMotionLed;
	CColorStatic	m_stcHomeLed;
	CColorStatic	m_stcLimitMinusLed;
	CColorStatic	m_stcLimitPlusLed;
	CColorStatic	m_stcHomingLed;
	CColorStatic	m_stcOriginLed;

	CComboBox		m_ComboVelLevel;	

	CNumEdit		m_EditPosMove;
	CNumEdit		m_EditRelativeMove;

	//CMaskLoaderMotion *pMaskLoader;
	CJogMotion	*m_JogMotion;
	

	void ControlsEnable(BOOL bEnable);

	afx_msg void OnBnClickedMachineJogInfoClosseBtn();
	afx_msg void OnBnClickedMachineJogInfoServoOnBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMachineJogInfoAlarmBtn();
	afx_msg void OnBnClickedMachineJogInfoOriginBtn();
	afx_msg void OnBnClickedMachineJogInfoStopBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedMachineJogInfoPosMoveBtn();
	afx_msg void OnBnClickedMachineJogInfoRelativeMinusBtn();
	afx_msg void OnBnClickedMachineJogInfoRelativePlusBtn();

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	bool m_bInit;

};
