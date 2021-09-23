
// VisionAgentDlg.h : 헤더 파일
//

#define RESOURCE_SPACE		1
#define QUICK_DATA_SPREAD_MAX_COL 5
#define QUICK_DATA_SPREAD_SCROLL_SIZE 20
#pragma once

//Log Define
#define _MSG_LOG_		WM_USER + 1000
#define MAX_LOG_RAW			10

//21.07.29 sjc hsms
#define PORT_COUNT		8		//구미:  1=load port,  2~8=unload cassette port
#define LSD_COUNT		100		//LSD 최대갯수
#define GSD_COUNT		100		//GSD 최대갯수
#define GLASS_COUNT		10		//글래스=스틱 갯수
#define SLOT_COUNT		10		//박스에서 슬랏최대갯수
#define SUBGLS_COUNT	100		//SUBGLS 최대갯수
#define	IONIZER_COUNT	0		//미사용
#define STAGE_COUNT		5		//LoadPort,Loader,검사Stage,Unloader,UnloadPort
#define CASSETTE_COUNT	0		//미사용
#define CHAMBER_COUNT	0		//미사용
#define MYDEVICEID		1		//미사용
#define MYUNITID		101		//설비 UNITID
#define MYCONTROLID		100		//설비 CONTROLID
#define MYIONIZERID		1		//미사용
#define MATERIAL_COUNT	10		//스틱 최대 갯수
//

#include "resource.h"
//Button Head 추가.
#include "Control/ColorStatic.h"
#include "Control/ClrButton.h"
#include "Vision/VisionAgentDefine.h"
#include "DrawMask.h"
#include "VisionAgentLogDlg.h"

#include "ServerClient/SocketManager.h"
#include "ServerClient/TCPIP.h" //KJT 20200823

#include "Common/ClientInterface.h"

#include "VisionAgentSafetyMap.h"
//SimulationView
#include "VisionAgentSimulationViewDlg.h"

#include "../WkLibLaserDispOm/WkLibLaserDispOm.h"
#pragma comment(lib, "../x64/Debug/WkLibLaserDispOm")

//21.07.29 sjc hsms
#include "xcomproctrl1.h"
#include "../Module/Cim/Secs.h"
#include "afxdisp.h"
//
class CVisionAgentDlgAutoProxy;

struct stPOSITION {
	stPOSITION() {
		ID[0] = 1;
		sprintf(STICKID, "");
		sprintf(STICKNO, "");
	}
	BYTE ID[2];
	char STICKID[30];
	char STICKNO[3];
};

// CVisionAgentDlg 대화 상자
class CModelDlg;
class CSystemDlg;
class CManualDlg;
class CMeasurementDlg;
class CCommunicationDlg;
class CMachineDlg;
class CVisionAgentProcessDlg;
class CLogger;
class CVisionAgentAlarmDlg;
class CVisionAgentECSDlg;

class CVisionAgentDlg : public CDialogEx
{
// 생성입니다.
public:
	CVisionAgentDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CVisionAgentDlg();	
// 대화 상자 데이터입니다.
	enum { IDD = IDD_VISION_AGENT_DIALOG };
		
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	CVisionAgentDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;
	
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	virtual void OnCancel();

	//Main Dialog
	BOOL m_bEntry = FALSE;
	//Network-------------------------------------------------------------------------------------
	int m_nStatusSocketConnect;

	char m_chReceiveData[10000];
	int m_nFuncAddr;
	int m_nReturn;
	byte m_byArg[10000];
	
	BOOL  m_bFlowAlignRun;
	BOOL  m_bFlowRun;
	
	//Pop Up Dlg
	CModelDlg				*m_pModelDlg;
	CManualDlg				*m_pManualDlg;
	CSystemDlg				*m_pSystemDlg;
	CMeasurementDlg			*m_pMeasurementDlg;
	CCommunicationDlg		*m_pCommunicationDlg;
	CMachineDlg				*m_pMahcineDlg;
	CVisionAgentProcessDlg	*m_pProcessDlg;
	CVisionAgentAlarmDlg	*m_pAlarmDlg;
	CVisionAgentECSDlg		*m_pECSDlg;

	CVisionAgentSafetyMap			*m_pSafetyMapDlg;
	//////////////////////////////////////////////////////////////
	BOOL m_bShowSafetyMapModeless;

	CWinThread* m_pMonitoringThread;
	int m_nIsRunningMonitoringThread;
	int m_nStopMonitoringThread;

	CWinThread* m_pStatusThread;
	int m_nIsRunningStatusThread;
	int m_nStopStatusThread;

	CWinThread* m_pSaftyThread;
	int m_nIsRunningSaftyThread;
	int m_nStopSaftyThread;

	//창 Open 확인.
	BOOL m_bShowModelModeless;
	BOOL m_bShowManualModeless;
	BOOL m_bShowMachineModeless;
	BOOL m_bShowCommunicationModeless;
	BOOL m_bShowMeasurementModeless;
	BOOL m_bShowAlarmModeless;
	BOOL m_bShowVisionModeless;
	BOOL m_bShowSystemModeless;
	BOOL m_bShowMachineStateModeless;
	BOOL m_bShowProcessDlg;
	BOOL m_bShowECSModeless;

	CFont m_fontStcMainLogo;
	CFont m_fontStcHansongLogo;
	CFont m_fontAutoRunDisp;
	CFont m_fontStateBar;
	CFont m_fontMainMenu;
	CFont m_fontFlow;
	CFont m_fontFlowPrcess;
	CFont m_fontQuickData;
	CFont m_fontNaming;

	TCHAR m_nRun[3];
	INT m_nAutoCnt;
	//Display Mode
	BOOL m_bDisplay;
	//Main State
	CClrButton m_btnSubMenu;
	CColorStatic m_stcMainTitle;
	CColorStatic m_stcHansongTitle;

	CColorStatic m_stc_btnMainMenu[MAX_MAIN_MENU_BTN];
	CColorStatic m_stcStateBar_Name[MAX_STATE_MENU_STC];
	CColorStatic m_stcStateBar_Value[MAX_STATE_MENU_STC];

	//Naming
	CColorStatic m_stcLogNaming;
	CColorStatic m_stcCameraViewMode_Naming;
	//CColorStatic m_stcReview20X_Cam_Naming;
	//CColorStatic m_stcPreAlign_Cam_Naming;
	CColorStatic m_stcBoxAlignLeft_Cam_Naming;
	CColorStatic m_stcBoxAlignRight_Cam_Naming;

	//Process----------------------------------
	double			m_dStart_Tick;
	bool			m_bFlow_Flash;
	//-----------------------------------------
	//Auto Run Display ------------------------------------------------------------------
	CColorStatic m_stcAutoRunDisp;

	//Network
	CClientInterface m_ClientInterface;

	CSocketManager m_SocketWrite;
	CSocketManager m_SocketReceive;
	//CSocketManager m_SocketVisionWrite;
	//CSocketManager m_SocketVisionReceive;

	int m_nLoaderBarCodeConnect;

	SockAddrIn m_SockPeer;

	BOOL m_bConnectWorkNetwork;
	BOOL m_bStateConnectWorkNetwork;
	BOOL m_bVisionConnectWorkNetwork;

	BOOL ConnectWorkNetwork();
	void GetNetworkStatus();

	//Tempurature
	int SaveTempur();

	BOOL SetDefaultOutput();

	BOOL MakeDefaultDir();

	int m_nPrevConnect;
	int m_nConnect;
	int m_nRetryCnt;
	int m_nStateConnect;
	int m_nVisionConnect;
	char m_pch[1000];//21.04.09 sjc
	double m_AOILaserValue[2];//21.04.09 sjc 0 = head 1, 1= head 2

	CClrButton m_btnAoiReadyStatus;

	CColorStatic				m_btnLogSelect[6];
	CColorStatic				m_btnLogViewer;
	
	CRect						m_LogSize;
	int							m_nCurLogDlg;
	CVisionAgentLogDlg			*m_VisionAgentLogAllDlg;
	CVisionAgentLogDlg			*m_VisionAgentLogProcessDlg;
	CVisionAgentLogDlg			*m_VisionAgentLogVisionDlg;
	CVisionAgentLogDlg			*m_VisionAgentLogSystemDlg;
	CVisionAgentLogDlg			*m_VisionAgentLogEtcDlg;
	CVisionAgentLogDlg			*m_VisionAgentLogAlarmDlg;
	CVisionAgentLogDlg			*m_pCurLogDlg;

	CButton m_CheckProcessDlg;
	int m_nCurrSubDlg;
	CWnd* m_pCurrSubDlg;

	//Simulation View
	CVisionAgentSimulationViewDlg m_VisionAgentSimulationViewDlg;

	stPOSITION	m_POSITION[POSITION_COUNT + 1];

	void DialogInit();
	void NetworkInit();

	void	InitSubDlg();
	void	Init_Log_Dlg();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void StateDisplay();
	void AlarmDisplay();
	void LogInUserID();

	void	ShowLogDlg(int nDlgNo);
	void	HideLogDlg();
	CString  m_strOldTemp;

	//파일 입출력
	//File Path-------------------------------------------------------------------------------------
	//CString m_StrVisionAgentPath;
	CString m_StrModelFrameParaFilePath;

	void ResetModel();

	BOOL m_bHomeChk;
	double	m_dAxisCmdFinishPos[DIRECT_AXIS_MAX];
	BOOL	m_bAxisFinalHomeStatus[DIRECT_AXIS_MAX];
	void AjinHomeRecovery();
	int SaveAjinHomeParameterTempFile(); //KJT 20210520 AWK
	int CopyTempFile(); //KJT 20210520 AWK
	int SaveAjinHomeParameter();
	int LoadAjinHomeParameter();

	int m_nAXLOpen;
	int m_nVisionMaxAxisSize;

	int GetBoardInfo();
	int GetMotionPara();
	CString m_StrMotFilePath;
	CString m_StrHomeFilePath;
	
	//Log Function
	CListBox m_listLog;
	//int m_nInsertItemNum;

	BOOL bDoorOpenFlag;

	double m_dPrevLaserFocusValue;
	int m_nPrevPickupUnitState;
	int m_nPrevClampState;
	int m_nPrevStretchState;

	//Thread------------------------------
	//1. Safety Check
	CWinThread* m_pSafety_Thread;
	int m_nIsRunningSafetyThread;
	int m_nStopSafetyThread;
	
	//3. Ajin Check
	CWinThread* m_pStatus_Ajin_Thread;
	int m_nIs_Running_Status_Ajin_Thread;
	int m_nStopStatusAjinThread;
	//4. Laser Dist & Load Cell Check
	CWinThread* m_pData_Thread;
	int m_nIs_Running_Data_Thread;
	int m_nStop_Data_Thread;
	//5. DIO & AI Check
	CWinThread* m_pSensing_Thread;
	int m_nIs_Running_Sensing_Thread;
	int m_nStop_Sensing_Thread;

	enum_Camera_ViewMode m_ePrevCamViewMode;

	//21.07.29 sjc hsms
	CXcomproctrl1 m_XComPro;
	bool m_XcomInitialized;
	bool m_XcomStarted;
	void Xcom_Init();

	void SecsEventXcomproctrl1(short nEventId, long lParam);
	void SecsMsgXcomproctrl1();
	CSecs* m_pSecs;
	//
public :
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnReceiveCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnStnClickedStaticModelBtn();
	afx_msg void OnStnClickedStaticCommunicationBtn();
	afx_msg void OnStnClickedStaticManualBtn();
	afx_msg void OnStnClickedStaticSystemBtn();
	afx_msg void OnStnClickedStaticHansongTitle();
	afx_msg void OnStnClickedStaticStopBtn();
//	afx_msg void OnStnClickedStaticMainTitle();
	afx_msg void OnStnClickedStaticMeasurementBtn();
	afx_msg void OnStnClickedStaticAutoRunBtn();
	afx_msg void OnStnClickedStaticAutoRunDisplay();
	afx_msg void OnStnDblclickStaticAutoRunDisplay();

	virtual BOOL DestroyWindow();

	afx_msg void OnStnClickedStaticReadyBtn();
	afx_msg void OnStnClickedLogAll();
	afx_msg void OnStnClickedLogProcess();
	afx_msg void OnStnClickedLogSystem();
	afx_msg void OnStnClickedLogVision();
	afx_msg void OnStnClickedLogEtc();
	afx_msg void OnStnClickedLogAlarm();
	afx_msg void OnStnClickedLogViewer();
	afx_msg void OnBnClickedCheckShowProcessSub();
	afx_msg void OnStnClickedStaticMachineBtn();
	CButton m_radioCamView6G;
	CButton m_radioCamView8G;
	afx_msg void OnBnClickedRdoCamView6g();
	afx_msg void OnBnClickedRdoCamView8g();
	void ChangeCamera(int nCamNo);
	afx_msg void OnStnDblclickStaticMainTitle();
	afx_msg void OnStnClickedStaticMainAlarm();

#pragma region //Label
	AxisLabel m_AxisLabel[AXIS_MAX];
	DInputLabel m_DInputLabel[MAX_DINPUT_SIZE];
	DOutputLabel m_DOutputLabel[MAX_DOUTPUT_SIZE];
	AInputLabel m_AInputLabel[MAX_AINPUT_SIZE];
	AOutputLabel m_AOutputLabel[MAX_AOUTPUT_SIZE];
	int SaveAxisLabelParameter();
	int SaveDInputLabelParameter();
	int SaveDOutputLabelParameter();
	int SaveAInputLabelParameter();
	int SaveAOutputLabelParameter();
	int LoadAxisLabelParameter();
	int LoadDInputLabelParameter();
	int LoadDOutputLabelParameter();
	int LoadAInputLabelParameter();
	int LoadAOutputLabelParameter();
	CString LoadFileData(CStdioFile* csfInFile, CString strSrcData, CString strCompData);
#pragma endregion

#ifndef SIM_MODE
	CWkLibLaserDispOm				*m_pLaserDisp;
#endif
	afx_msg void OnStnClickedStaticEcsBtn();
	//21.07.29 sjc hsms
	DECLARE_EVENTSINK_MAP()
	//
};

UINT Status_Ajin_Thread_Proc(LPVOID lpParam);
UINT Safety_Thread_Proc(LPVOID lpParam);
UINT Data_Thread_Proc(LPVOID lpParam);

//#ifndef USE_MIL_CAMERA
//UINT CameraDispThread(LPVOID pParent);
//#endif