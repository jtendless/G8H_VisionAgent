// VisionAgentSystem_CoordinateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentSystem_CoordinateDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystem_CoordinateDlg 대화 상자

IMPLEMENT_DYNAMIC(CVisionAgentSystem_CoordinateDlg, CDialogEx)

CVisionAgentSystem_CoordinateDlg::CVisionAgentSystem_CoordinateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYSTEM_COORDINATE_DIALOG, pParent)
{
	Create(IDD_SYSTEM_COORDINATE_DIALOG, pParent);
}

CVisionAgentSystem_CoordinateDlg::~CVisionAgentSystem_CoordinateDlg()
{
}

void CVisionAgentSystem_CoordinateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentSystem_CoordinateDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE_CAMERA_Z1_OFFSET_SET_POSITION, &CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCameraZ1OffsetSetPosition)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE_CAMERA_Z2_OFFSET_SET_POSITION, &CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCameraZ2OffsetSetPosition)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE_CAMERA_3D_MAIN_Z_OFFSET_SET_POSITION, &CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCamera3dMainZOffsetSetPosition)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE_CAMERA_Z1_OFFSET_SET_ZERO, &CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCameraZ1OffsetSetZero)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE_CAMERA_Z2_OFFSET_SET_ZERO, &CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCameraZ2OffsetSetZero)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE_CAMERA_3D_MAIN_Z_OFFSET_SET_ZERO, &CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCamera3dMainZOffsetSetZero)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE_LASER_FOCUS_OFFSET_GLASS_GET, &CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateLaserFocusOffsetGlassGet)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE_LASER_FOCUS_OFFSET_STICK_GET, &CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateLaserFocusOffsetStickGet)
END_MESSAGE_MAP()


// CVisionAgentSystem_CoordinateDlg 메시지 처리기

BOOL CVisionAgentSystem_CoordinateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CVisionAgentSystem_CoordinateDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CVisionAgentSystem_CoordinateDlg::InitCtrl()
{
	CSystemData::m_Coordinate.Info.d3DCam_Resolution_X = _3D_CAM_RESOLUTION_X; //Fixed
	CSystemData::m_Coordinate.Info.d3DCam_Resolution_Y = _3D_CAM_RESOLUTION_Y; //Fixed

	m_editOffsetReview10xTo20x_X.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_20X_X, this);
	m_editOffsetReview10xTo20x_Y.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_20X_Y, this);
	m_editOffsetReview10xTo20x_Z.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_20X_Z, this);
	m_editOffsetReview10xToPreAlign_X.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_PRE_ALIGN_X, this);
	m_editOffsetReview10xToPreAlign_Y.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_PRE_ALIGN_Y, this);
	m_editOffsetReview10xToPreAlign_Z.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_PRE_ALIGN_Z, this);
	m_editOffsetReview10xToAoi_X.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_AOI_X, this);
	m_editOffsetReview10xToAoi_Y.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_AOI_Y, this);
	m_editOffsetReview10xToAoi_Z.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_AOI_Z, this);
	m_editOffsetReview10xTo3dCam_X.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_3D_CAM_X, this);
	m_editOffsetReview10xTo3dCam_Y.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_3D_CAM_Y, this);
	m_editOffsetReview10xTo3dCam_Z.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_3D_CAM_Z, this);	
	m_editOffsetReview10xTo50x_X.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_50X_X, this);
	m_editOffsetReview10xTo50x_Y.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_50X_Y, this);

	m_editOffsetCameraZ1.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_CAMERA_Z_OFFSET_Z1, this);
	m_editOffsetCameraZ2.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_CAMERA_Z_OFFSET_Z2, this);
	m_editOffsetCameraZ3.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_CAMERA_Z_OFFSET_3D_MAIN, this);

	m_edit3DCam_Resolution_X.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_3D_CAMERA_RESOLUTION_X, this);
	m_edit3DCam_Resolution_Y.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_3D_CAMERA_RESOLUTION_Y, this);

	m_edit10XCam_Resolution_X.SubclassDlgItem(IDC_EDIT_CAMERA_10X_RESOLUTION_X, this);
	m_edit10XCam_Resolution_Y.SubclassDlgItem(IDC_EDIT_CAMERA_10X_RESOLUTION_Y, this);

	m_edit20XCam_Resolution_X.SubclassDlgItem(IDC_EDIT_CAMERA_20X_RESOLUTION_X, this);
	m_edit20XCam_Resolution_Y.SubclassDlgItem(IDC_EDIT_CAMERA_20X_RESOLUTION_Y, this);

	m_edit50XCam_Resolution_X.SubclassDlgItem(IDC_EDIT_CAMERA_50X_RESOLUTION_X, this);
	m_edit50XCam_Resolution_Y.SubclassDlgItem(IDC_EDIT_CAMERA_50X_RESOLUTION_Y, this);

	m_editMaxTensionOffset_LoaderX.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_MAX_TENSION_OFFSET_LOADER_X, this); //KJT 20210806 Add
	m_editMaxTensionOffset_UnloaderX.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_MAX_TENSION_OFFSET_UNLOADER_X, this);
	m_editMaxTensionOffset_PaperUnloaderX.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_MAX_TENSION_OFFSET_PAPER_UNLOADER_X, this);

	m_editReview10XtoLaserOffsetX.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_LASER_X, this);
	m_editReview10XtoLaserOffsetY.SubclassDlgItem(IDC_EDIT_CAMERA_OFFSET_REVIEW_10X_TO_LASER_Y, this);

	m_editLaserFocusOffsetGlass.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_LASER_FOCUS_OFFSET_GLASS, this);
	m_editLaserFocusOffsetStick.SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_LASER_FOCUS_OFFSET_STICK, this);

//#pragma region //GantryX, BackLightX Sync
	m_editBackLightXFwdStartDelay[0].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_FWD_START_DELAY_VEL50, this);
	m_editBackLightXFwdAccDecScale[0].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_FWD_ACC_DEC_SCALE_VEL50, this);
	m_editBackLightXBwdStartDelay[0].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_BWD_START_DELAY_VEL50, this);
	m_editBackLightXBwdAccDecScale[0].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_BWD_ACC_DEC_SCALE_VEL50, this);

	m_editBackLightXFwdStartDelay[1].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_FWD_START_DELAY_VEL100, this);
	m_editBackLightXFwdAccDecScale[1].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_FWD_ACC_DEC_SCALE_VEL100, this);
	m_editBackLightXBwdStartDelay[1].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_BWD_START_DELAY_VEL100, this);
	m_editBackLightXBwdAccDecScale[1].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_BWD_ACC_DEC_SCALE_VEL100, this);

	m_editBackLightXFwdStartDelay[2].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_FWD_START_DELAY_VEL150, this);
	m_editBackLightXFwdAccDecScale[2].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_FWD_ACC_DEC_SCALE_VEL150, this);
	m_editBackLightXBwdStartDelay[2].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_BWD_START_DELAY_VEL150, this);
	m_editBackLightXBwdAccDecScale[2].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_BWD_ACC_DEC_SCALE_VEL150, this);

	m_editBackLightXFwdStartDelay[3].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_FWD_START_DELAY_VEL200, this);
	m_editBackLightXFwdAccDecScale[3].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_FWD_ACC_DEC_SCALE_VEL200, this);
	m_editBackLightXBwdStartDelay[3].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_BWD_START_DELAY_VEL200, this);
	m_editBackLightXBwdAccDecScale[3].SubclassDlgItem(IDC_EDIT_SYSTEM_COORDINATE_BACKLIGHT_X_BWD_ACC_DEC_SCALE_VEL200, this);
//#pragma endregin

	return TRUE;
}

BOOL CVisionAgentSystem_CoordinateDlg::InitPara()
{
	CString Str = _T("");
	int i = 0;

	m_editOffsetReview10xTo20x_X.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X));
	m_editOffsetReview10xTo20x_Y.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y));
	m_editOffsetReview10xTo20x_Z.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Z));
	m_editOffsetReview10xToPreAlign_X.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X));
	m_editOffsetReview10xToPreAlign_Y.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y));
	m_editOffsetReview10xToPreAlign_Z.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Z));
	m_editOffsetReview10xToAoi_X.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X));
	m_editOffsetReview10xToAoi_Y.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Y));
	m_editOffsetReview10xToAoi_Z.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Z));
	m_editOffsetReview10xTo3dCam_X.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_X));
	m_editOffsetReview10xTo3dCam_Y.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_Y));
	m_editOffsetReview10xTo3dCam_Z.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_Z));
	m_editOffsetReview10xTo50x_X.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_X));
	m_editOffsetReview10xTo50x_Y.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_Y));

	m_editOffsetCameraZ1.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_CAMERA_Z1]));
	//m_editOffsetCameraZ2.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z2]));
	//m_editOffsetCameraZ3.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z3]));

	m_edit3DCam_Resolution_X.SetWindowText(_ToStr(_T("%.20f"), CSystemData::m_Coordinate.Info.d3DCam_Resolution_X));
	m_edit3DCam_Resolution_Y.SetWindowText(_ToStr(_T("%.20f"), CSystemData::m_Coordinate.Info.d3DCam_Resolution_Y));

	//20210729 JINI
	m_edit10XCam_Resolution_X.SetWindowText(_ToStr(_T("%.20f"), CSystemData::m_Coordinate.Info.d10XCam_Resolution_X));
	m_edit10XCam_Resolution_Y.SetWindowText(_ToStr(_T("%.20f"), CSystemData::m_Coordinate.Info.d10XCam_Resolution_Y));

	m_edit20XCam_Resolution_X.SetWindowText(_ToStr(_T("%.20f"), CSystemData::m_Coordinate.Info.d20XCam_Resolution_X));
	m_edit20XCam_Resolution_Y.SetWindowText(_ToStr(_T("%.20f"), CSystemData::m_Coordinate.Info.d20XCam_Resolution_Y));

	m_edit50XCam_Resolution_X.SetWindowText(_ToStr(_T("%.20f"), CSystemData::m_Coordinate.Info.d50XCam_Resolution_X));
	m_edit50XCam_Resolution_Y.SetWindowText(_ToStr(_T("%.20f"), CSystemData::m_Coordinate.Info.d50XCam_Resolution_Y));

	m_editMaxTensionOffset_LoaderX.SetWindowText(_ToStr(_T("%.3f"), CSystemData::m_Coordinate.Info.dMax_Tension_Offset_LoaderX)); //KJT 20210806 Add
	m_editMaxTensionOffset_UnloaderX.SetWindowText(_ToStr(_T("%.3f"), CSystemData::m_Coordinate.Info.dMax_Tension_Offset_UnloaderX));
	m_editMaxTensionOffset_PaperUnloaderX.SetWindowText(_ToStr(_T("%.3f"), CSystemData::m_Coordinate.Info.dMax_Tension_Offset_PaperUnloaderX));	

	m_editReview10XtoLaserOffsetX.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xToLaser_X)); //KJT 20210824
	m_editReview10XtoLaserOffsetY.SetWindowText(_ToStr(_T("%.5f"), CSystemData::m_Coordinate.Info.dOffsetReview10xToLaser_Y)); //KJT 20210824

	m_editLaserFocusOffsetGlass.SetWindowText(_ToStr(_T("%.4f"), CSystemData::m_Coordinate.Info.dLaserFocusOffsetGlass));
	m_editLaserFocusOffsetStick.SetWindowText(_ToStr(_T("%.4f"), CSystemData::m_Coordinate.Info.dLaserFocusOffsetStick));

	//for (i = 0; i < 4; i++)
	for (i = 0; i < 2; i++)
	{
		Str.Format(_T("%d"), CSystemData::m_Coordinate.Info.nBackLightXFwdStartDelay[i]);
		m_editBackLightXFwdStartDelay[i].SetWindowText(Str);
		Str.Format(_T("%.5f"), CSystemData::m_Coordinate.Info.dBackLightXFwdAccDecScale[i]);
		m_editBackLightXFwdAccDecScale[i].SetWindowText(Str);
		Str.Format(_T("%d"), CSystemData::m_Coordinate.Info.nBackLightXBwdStartDelay[i]);
		m_editBackLightXBwdStartDelay[i].SetWindowText(Str);
		Str.Format(_T("%.5f"), CSystemData::m_Coordinate.Info.dBackLightXBwdAccDecScale[i]);
		m_editBackLightXBwdAccDecScale[i].SetWindowText(Str);
	}

	return TRUE;
}

BOOL CVisionAgentSystem_CoordinateDlg::CheckChangeData()
{
	CString Str = _T("");
	int i = 0;

	m_editOffsetReview10xTo20x_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X = _ttof(Str);
	m_editOffsetReview10xTo20x_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y = _ttof(Str);
	m_editOffsetReview10xTo20x_Z.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Z = _ttof(Str);
	m_editOffsetReview10xToPreAlign_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X = _ttof(Str);
	m_editOffsetReview10xToPreAlign_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y = _ttof(Str);
	m_editOffsetReview10xToPreAlign_Z.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Z = _ttof(Str);
	m_editOffsetReview10xToAoi_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X = _ttof(Str);
	m_editOffsetReview10xToAoi_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Y = _ttof(Str);
	m_editOffsetReview10xToAoi_Z.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Z = _ttof(Str);
	m_editOffsetReview10xTo3dCam_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_X = _ttof(Str);
	m_editOffsetReview10xTo3dCam_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_Y = _ttof(Str);
	m_editOffsetReview10xTo3dCam_Z.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_Z = _ttof(Str);
	m_editOffsetReview10xTo50x_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_X = _ttof(Str);
	m_editOffsetReview10xTo50x_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_Y = _ttof(Str);

	m_editOffsetCameraZ1.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_CAMERA_Z1] = _ttof(Str);
	//m_editOffsetCameraZ2.GetWindowText(Str);
	//CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z2] = _ttof(Str);
	//m_editOffsetCameraZ3.GetWindowText(Str);
	//CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z3] = _ttof(Str);

	m_edit3DCam_Resolution_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.d3DCam_Resolution_X = _ttof(Str);
	m_edit3DCam_Resolution_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.d3DCam_Resolution_Y = _ttof(Str);

	//20210729 JINI
	m_edit10XCam_Resolution_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.d10XCam_Resolution_X = _ttof(Str);
	m_edit10XCam_Resolution_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.d10XCam_Resolution_Y = _ttof(Str);

	m_edit20XCam_Resolution_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.d20XCam_Resolution_X = _ttof(Str);
	m_edit20XCam_Resolution_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.d20XCam_Resolution_Y = _ttof(Str);

	m_edit50XCam_Resolution_X.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.d50XCam_Resolution_X = _ttof(Str);
	m_edit50XCam_Resolution_Y.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.d50XCam_Resolution_Y = _ttof(Str);

	m_editMaxTensionOffset_LoaderX.GetWindowText(Str); //KJT 20210806 Add
	CSystemData::m_Coordinate.Info.dMax_Tension_Offset_LoaderX = _ttof(Str);
	m_editMaxTensionOffset_UnloaderX.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dMax_Tension_Offset_UnloaderX = _ttof(Str);
	m_editMaxTensionOffset_PaperUnloaderX.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dMax_Tension_Offset_PaperUnloaderX = _ttof(Str);

	m_editReview10XtoLaserOffsetX.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xToLaser_X = _ttof(Str); //KJT 20210824
	m_editReview10XtoLaserOffsetY.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dOffsetReview10xToLaser_Y = _ttof(Str); //KJT 20210824

	m_editLaserFocusOffsetGlass.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dLaserFocusOffsetGlass = _ttof(Str);
	m_editLaserFocusOffsetStick.GetWindowText(Str);
	CSystemData::m_Coordinate.Info.dLaserFocusOffsetStick = _ttof(Str);

	for (i = 0; i < 4; i++)
	{
		m_editBackLightXFwdStartDelay[i].GetWindowText(Str);
		CSystemData::m_Coordinate.Info.nBackLightXFwdStartDelay[i] = _ttoi(Str);
		m_editBackLightXFwdAccDecScale[i].GetWindowText(Str);
		CSystemData::m_Coordinate.Info.dBackLightXFwdAccDecScale[i] = _ttof(Str);
		m_editBackLightXBwdStartDelay[i].GetWindowText(Str);
		CSystemData::m_Coordinate.Info.nBackLightXBwdStartDelay[i] = _ttoi(Str);
		m_editBackLightXBwdAccDecScale[i].GetWindowText(Str);
		CSystemData::m_Coordinate.Info.dBackLightXBwdAccDecScale[i] = _ttof(Str);
	}

	return TRUE;
}

BOOL CVisionAgentSystem_CoordinateDlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CSystemData::m_Coordinate.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}

void CVisionAgentSystem_CoordinateDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		InitPara();
	}
	else if (bShow == FALSE)
	{
	}
}


void CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCameraZ1OffsetSetPosition()
{
	CString szMsg;
	double dCmdPos;
	if (IDYES == AfxMessageBox(_T("Set Camera Z1 Offset?"), MB_YESNO))
	{
		m_editOffsetCameraZ1.GetWindowText(szMsg);
		AxmStatusGetCmdPos(DIRECT_AXIS_CAMERA_Z1, &dCmdPos);
		CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_CAMERA_Z1] = _ttof(szMsg) - dCmdPos;
		szMsg.Format(_T("%10.5f"), CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_CAMERA_Z1]);
		m_editOffsetCameraZ1.SetWindowText(szMsg);
	}
}


void CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCameraZ2OffsetSetPosition()
{
	//CString szMsg;
	//double dCmdPos;
	//if (IDYES == AfxMessageBox(_T("Set Camera Z2 Offset?"), MB_YESNO))
	//{
	//	m_editOffsetCameraZ2.GetWindowText(szMsg);
	//	AxmStatusGetCmdPos(DIRECT_AXIS_AJIN_CAMERA_Z2, &dCmdPos);
	//	CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z2] = _ttof(szMsg) - dCmdPos;
	//	szMsg.Format(_T("%10.5f"), CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z2]);
	//	m_editOffsetCameraZ2.SetWindowText(szMsg);
	//}
}

void CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCamera3dMainZOffsetSetPosition()
{
	//CString szMsg;
	//double dCmdPos;
	//if (IDYES == AfxMessageBox(_T("Set Camera Z3 Offset?"), MB_YESNO))
	//{
	//	m_editOffsetCameraZ3.GetWindowText(szMsg);
	//	AxmStatusGetCmdPos(DIRECT_AXIS_AJIN_CAMERA_Z3, &dCmdPos);
	//	CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z3] = _ttof(szMsg) - dCmdPos;
	//	szMsg.Format(_T("%10.5f"), CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z3]);
	//	m_editOffsetCameraZ3.SetWindowText(szMsg);
	//}
}


void CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCameraZ1OffsetSetZero()
{
	if (IDYES == AfxMessageBox(_T("Set Camera Z1 Offset to 0?"), MB_YESNO))
	{
		CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_CAMERA_Z1] = 0;
		m_editOffsetCameraZ1.SetWindowText(_T("0"));
	}
}


void CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCameraZ2OffsetSetZero()
{
	//if (IDYES == AfxMessageBox(_T("Set Camera Z2 Offset to 0?"), MB_YESNO))
	//{
	//	CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z2] = 0;
	//	m_editOffsetCameraZ2.SetWindowText(_T("0"));
	//}
}


void CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateCamera3dMainZOffsetSetZero()
{
	//if (IDYES == AfxMessageBox(_T("Set Camera Z3 Offset to 0?"), MB_YESNO))
	//{
	//	CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_AJIN_CAMERA_Z3] = 0;
	//	m_editOffsetCameraZ3.SetWindowText(_T("0"));
	//}
}


void CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateLaserFocusOffsetGlassGet()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.GetMainWnd();
#ifndef SIM_MODE
	m_editLaserFocusOffsetGlass.SetWindowText(_ToStr(_T("%.4f"), pDlg->m_pLaserDisp->GetData()));
#endif
}


void CVisionAgentSystem_CoordinateDlg::OnBnClickedButtonSystemCoordinateLaserFocusOffsetStickGet()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.GetMainWnd();
#ifndef SIM_MODE
	m_editLaserFocusOffsetStick.SetWindowText(_ToStr(_T("%.4f"), pDlg->m_pLaserDisp->GetData()));
#endif
}
