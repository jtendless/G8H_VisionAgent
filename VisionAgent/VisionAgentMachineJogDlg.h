#pragma once

#include "../Module/Control/ColorStatic.h"

#include "../Module/Control/NumEdit.h"
#include "../Module/Motion/JogMotion.h"

// CVisionAgentMachineJogDlg 대화 상자

enum en_MACHINE_JOG_DEF
{
	MACHINE_JOG_WORKSTAGE = 0,
	MACHINE_JOG_GANTRY_Y,
	MACHINE_JOG_GANTRY_Z,
	//
	MACHINE_JOG_FRAME_UPDOWN,				// 합착이재기
	MACHINE_JOG_STAGE_UVW,
	//
	MACHINE_JOG_GLASS_POPUP_Z,
	MACHINE_JOG_FRAME_GRIPPER_SSIDE,		// FRAME GRIPPER 단변
	MACHINE_JOG_FRAME_GRIPPER_LSIDE,		// FRAME GRIPPER 장변
	//
	MACHINE_JOG_GLASS_RELEASE_SSIDE,
	MACHINE_JOG_GLASS_RELEASE_SMOVE,
	MACHINE_JOG_GLASS_RELEASE_LSIDE,
	MACHINE_JOG_GLASS_RELEASE_LMOVE,
	//
	MACHINE_JOG_FRAME_TRANSFER_MOVE,
	MACHINE_JOG_ROLLER_RELEASE_MOVE,
	MACHINE_JOG_GLASS_RELEASE_LSIDE_R,		// 장변R
	MACHINE_JOG_ROLLER_RELEASE,
	//
	MACHINE_JOG_CLEANNING,
	MACHINE_JOG_FRAME_TRANSFER_L,
	//
	MACHINE_JOG_MAX,
};

class CVisionAgentMachineJogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentMachineJogDlg)

public:
	CVisionAgentMachineJogDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentMachineJogDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MACHINE_JOG_DIALOG  };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	bool m_bDialog_Entry;

	void InitCtrl();
	void InitPara();

	CComboBox		m_ComboAxis[MACHINE_JOG_MAX];
	CClrButton		m_btnJogInfo[MACHINE_JOG_MAX];
	CClrButton		m_btnJogMinus[MACHINE_JOG_MAX];
	CClrButton		m_btnJogPlus[MACHINE_JOG_MAX];
	CColorStatic	m_stcCurPos[MACHINE_JOG_MAX];
	CColorStatic	m_stcServoOnLed[MACHINE_JOG_MAX];
	CNumEdit		m_EditAbsMovePos[MACHINE_JOG_MAX];
	CClrButton		m_btnAbsMove[MACHINE_JOG_MAX];
	CNumEdit		m_EditRelativeDist[MACHINE_JOG_MAX];
	CClrButton		m_btnRelMinus[MACHINE_JOG_MAX];
	CClrButton		m_btnRelPlus[MACHINE_JOG_MAX];
	CComboBox		m_ComboManualSpeed[MACHINE_JOG_MAX];

	CButton			m_checkWithMoveBackLightX;
	CButton			m_checkWithMoveAOICamera;

	CJogMotion*		m_JogMotion;

	//Ssming Jog버튼 클릭 후 버튼 벗어나서 버튼 뗄시에 계속 동작하는 오류 해결하기 위함
	//enum_Axis m_eAxisJog;

public:
	BOOL GetAxisJogParamByUI(en_MACHINE_JOG_DEF eJogUIDefine, enum_Axis* peAxis, double* pPosAbs, double* pPosRel, double* pJogSpeed, double* pAccel, double* pDecel, CString* strDiscription);

	static void JogMoveComplete(void * argument);
	void funcJogInfo(en_MACHINE_JOG_DEF eJogUIDefine);
	void funcAbsMove(en_MACHINE_JOG_DEF eJogUIDefine);
	void funcRelMoveMinus(en_MACHINE_JOG_DEF eJogUIDefine);
	void funcRelMovePlus(en_MACHINE_JOG_DEF eJogUIDefine);
	
	
	afx_msg void OnBnClickedMachineJogAllStopBtn();

	//afx_msg void OnBnClickedButtonMachineJogInfoGantryY();
	//afx_msg void OnBnClickedButtonMachineJogInfoGantryX();
	//afx_msg void OnBnClickedButtonMachineJogInfoCameraZ();
	//afx_msg void OnBnClickedButtonMachineJogInfoBoxAlignCameraY();
	//afx_msg void OnBnClickedButtonMachineJogInfoLoadingStage();
	//afx_msg void OnBnClickedButtonMachineJogInfoLoader();
	//afx_msg void OnBnClickedButtonMachineJogInfoGripperClamp();
	//afx_msg void OnBnClickedButtonMachineJogInfoGripperStretch();
	//afx_msg void OnBnClickedButtonMachineJogInfoGripperPitch();
	//afx_msg void OnBnClickedButtonMachineJogInfoGripperWedgeZ();
	//afx_msg void OnBnClickedButtonMachineJogInfoInspectionStage();
	//afx_msg void OnBnClickedButtonMachineJogInfoBacklight();
	//afx_msg void OnBnClickedButtonMachineJogInfoUnloader();
	//afx_msg void OnBnClickedButtonMachineJogInfoMagazineLift();
	//afx_msg void OnBnClickedButtonMachineJogInfoInkjet();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveGantryY();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveGantryX();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveCameraZ();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveBoxAlignCameraY();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveLoadingStage();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveLoader();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveGripperStretch();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveGripperPitch();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveGripperWedgeZ();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveInspectionStage();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveBacklight();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveUnloader();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveMagazineLift();
	//afx_msg void OnBnClickedButtonMachineJogAbsMoveInkjet();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusGantryY();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusGantryX();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusCameraZ();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusBoxAlignCameraY();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusLoadingStage();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusLoader();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusGripperStretch();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusGripperPitch();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusGripperWedgeZ();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusInspectionStage();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusBacklight();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusUnloader();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusMagazineLift();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusInkjet();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusGantryY();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusGantryX();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusCameraZ();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusBoxAlignCameraY();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusLoadingStage();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusLoader();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusGripperStretch();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusGripperPitch();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusGripperWedgeZ();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusInspectionStage();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusBacklight();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusUnloader();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusMagazineLift();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusInkjet();
	//afx_msg void OnBnClickedButtonMachineJogInfoPaper();
	//afx_msg void OnBnClickedButtonMachineJogAbsMovePaper();
	//afx_msg void OnBnClickedButtonMachineJogRelMinusPaper();
	//afx_msg void OnBnClickedButtonMachineJogRelPlusPaper();

	afx_msg void OnBnClickedCheckMachineJogWithMoveBacklightX();
	afx_msg void OnBnClickedCheckMachineJogWithMoveAoiCamera();

};
