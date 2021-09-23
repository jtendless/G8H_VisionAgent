#pragma once


// CSystemSaftySubDlg 대화 상자
class CSystemSaftySubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemSaftySubDlg)

public:
	CSystemSaftySubDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSystemSaftySubDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SYSTEM_SUB_MACHINE_AXIS };
#endif
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	BOOL InitCtrl();
	BOOL InitPara();
	BOOL SavePara();
	BOOL CheckChangeData();

	CNumEdit m_editSafetyMin_Review10X_X;
	CNumEdit m_editSafetyMax_Review10X_X;
	CNumEdit m_editSafetyMin_Review10X_Y_In_BoxStage;
	CNumEdit m_editSafetyMin_Review10X_Y_In_PaperStage;
	CNumEdit m_editSafetyMin_Review10X_Y_In_InspectionStage;
	CNumEdit m_editSafetyMax_Review10X_Y;
	CNumEdit m_editSafetyMin_Review10X_Z;

	CNumEdit m_editSafetyMin_AOI_X;
	CNumEdit m_editSafetyMax_AOI_X;
	CNumEdit m_editSafetyMin_AOI_Y;
	CNumEdit m_editSafetyMax_AOI_Y;
	CNumEdit m_editSafetyMin_AOI_Z;

	CNumEdit m_editSafetyMin_3D_X;
	CNumEdit m_editSafetyMax_3D_X;
	CNumEdit m_editSafetyMin_3D_Y;
	CNumEdit m_editSafetyMax_3D_Y;
	CNumEdit m_editSafetyMin_3D_Z;

	CNumEdit m_editSafetyMin_Loader_Z_In_BoxStage;
	CNumEdit m_editSafetyMin_Loader_Z_In_PaperStage;
	CNumEdit m_editSafetyMin_Loader_Z_In_InspectionStage;

	CNumEdit m_editDist_GantryYToUnloaderY;
	CNumEdit m_editDist_GantryYToLoaderY;

	CNumEdit m_editMinDist_GantryYToUnloaderY;
	CNumEdit m_editMinDist_GantryYToLoaderY;

	CNumEdit m_editMinDist_PaperUnloaderToLoaderY;
	CNumEdit m_editMinDist_PaperUnloaderToLoaderX;

	CButton m_chkSafetyUsage;
};
