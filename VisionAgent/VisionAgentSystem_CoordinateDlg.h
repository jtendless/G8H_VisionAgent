#pragma once


// CVisionAgentSystem_CoordinateDlg 대화 상자

class CVisionAgentSystem_CoordinateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSystem_CoordinateDlg)

public:
	CVisionAgentSystem_CoordinateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentSystem_CoordinateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM_COORDINATE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	BOOL InitCtrl();
	BOOL InitPara();
	BOOL SavePara();
	BOOL CheckChangeData();

	CNumEdit		m_editOffsetReview10xTo20x_X;
	CNumEdit		m_editOffsetReview10xTo20x_Y;
	CNumEdit		m_editOffsetReview10xTo20x_Z;
	CNumEdit		m_editOffsetReview10xToPreAlign_X;
	CNumEdit		m_editOffsetReview10xToPreAlign_Y;
	CNumEdit		m_editOffsetReview10xToPreAlign_Z;
	CNumEdit		m_editOffsetReview10xToAoi_X;
	CNumEdit		m_editOffsetReview10xToAoi_Y;
	CNumEdit		m_editOffsetReview10xToAoi_Z;
	CNumEdit		m_editOffsetReview10xTo3dCam_X;
	CNumEdit		m_editOffsetReview10xTo3dCam_Y;
	CNumEdit		m_editOffsetReview10xTo3dCam_Z;
	//20210729 JINI
	CNumEdit		m_editOffsetReview10xTo50x_X;
	CNumEdit		m_editOffsetReview10xTo50x_Y;

	CNumEdit		m_editOffsetCameraZ1; //AOI
	CNumEdit		m_editOffsetCameraZ2; //3D, Zoom(PreAlign)
	CNumEdit		m_editOffsetCameraZ3; //Review

	CNumEdit		m_edit3DCam_Resolution_X;
	CNumEdit		m_edit3DCam_Resolution_Y;

	//20210729 JINI
	CNumEdit		m_edit10XCam_Resolution_X;
	CNumEdit		m_edit10XCam_Resolution_Y;

	CNumEdit		m_edit20XCam_Resolution_X;
	CNumEdit		m_edit20XCam_Resolution_Y;

	CNumEdit		m_edit50XCam_Resolution_X;
	CNumEdit		m_edit50XCam_Resolution_Y;

	CNumEdit		m_editMaxTensionOffset_LoaderX;
	CNumEdit		m_editMaxTensionOffset_UnloaderX;
	CNumEdit		m_editMaxTensionOffset_PaperUnloaderX;

	CNumEdit		m_editReview10XtoLaserOffsetX;
	CNumEdit		m_editReview10XtoLaserOffsetY;
	CNumEdit		m_editLaserFocusOffsetGlass;
	CNumEdit		m_editLaserFocusOffsetStick;

	CNumEdit	m_editBackLightXFwdStartDelay[4];
	CNumEdit	m_editBackLightXFwdAccDecScale[4];
	CNumEdit	m_editBackLightXBwdStartDelay[4];
	CNumEdit	m_editBackLightXBwdAccDecScale[4];

	afx_msg void OnBnClickedButtonSystemCoordinateCameraZ1OffsetSetPosition();
	afx_msg void OnBnClickedButtonSystemCoordinateCameraZ2OffsetSetPosition();
	afx_msg void OnBnClickedButtonSystemCoordinateCamera3dMainZOffsetSetPosition();
	afx_msg void OnBnClickedButtonSystemCoordinateCameraZ1OffsetSetZero();
	afx_msg void OnBnClickedButtonSystemCoordinateCameraZ2OffsetSetZero();
	afx_msg void OnBnClickedButtonSystemCoordinateCamera3dMainZOffsetSetZero();
	afx_msg void OnBnClickedButtonSystemCoordinateLaserFocusOffsetGlassGet();
	afx_msg void OnBnClickedButtonSystemCoordinateLaserFocusOffsetStickGet();
};
