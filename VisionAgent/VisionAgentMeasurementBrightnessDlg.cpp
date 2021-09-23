// VisionAgentModelDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentMeasurementBrightnessDlg.h"
#include "afxdialogex.h"


// CVisionAgentMeasurementBrightnessDlg 대화 상자

IMPLEMENT_DYNAMIC(CVisionAgentMeasurementBrightnessDlg, CDialogEx)

CVisionAgentMeasurementBrightnessDlg::CVisionAgentMeasurementBrightnessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISION_AGENT_MEASUREMENT_BRIGHTNESS_DIALOG, pParent)
{

}

CVisionAgentMeasurementBrightnessDlg::~CVisionAgentMeasurementBrightnessDlg()
{
}

void CVisionAgentMeasurementBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentMeasurementBrightnessDlg, CDialogEx)
	ON_COMMAND_RANGE(IDC_BTN_REVIEW_COAXIAL_DOWN_10, IDC_BTN_BOX_ALIGN_R_RING_SET_255, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedUpDownBtnBtn)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_LIGHT_OFF_ALL, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnLightOffAll)
	ON_BN_CLICKED(IDC_LIGHT_ON_BACKLIGHT_BTN, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedLightOnBacklightBtn)
	ON_BN_CLICKED(IDC_LIGHT_OFF_BACKLIGHT_BTN, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedLightOffBacklightBtn)
	ON_BN_CLICKED(IDC_LIGHT_ON_AOI_LIGHT_ON_BTN, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedLightOnAoiLightOnBtn)
	ON_BN_CLICKED(IDC_LIGHT_ON_AOI_LIGHT_OFF_BTN, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedLightOnAoiLightOffBtn)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_REVIEW_10X_LIGHT_ON, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessReview10xLightOn)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_PRE_ALIGN_LIGHT_ON, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessPreAlignLightOn)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_BOX_ALIGN_LEFT_LIGHT_ON, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessBoxAlignLeftLightOn)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_BOX_ALIGN_RIGHT_LIGHT_ON, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessBoxAlignRightLightOn)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_REVIEW_10X_LIGHT_OFF, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessReview10xLightOff)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_PRE_ALIGN_LIGHT_OFF, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessPreAlignLightOff)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_BOX_ALIGN_LEFT_LIGHT_OFF, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessBoxAlignLeftLightOff)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_BOX_ALIGN_RIGHT_LIGHT_OFF, &CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessBoxAlignRightLightOff)
END_MESSAGE_MAP()


// CVisionAgentMeasurementBrightnessDlg 메시지 처리기
BOOL CVisionAgentMeasurementBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	CString szMsg;
	
	
	szMsg.Format(_T("0"));

	GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->SetWindowText(szMsg);
	GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->SetWindowText(szMsg);
	szMsg.Format(_T("50"));
	GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->SetWindowText(szMsg);
	szMsg.Format(_T("0"));
	GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->SetWindowText(szMsg);
	
	
	GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->SetWindowText(szMsg);
	GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->SetWindowText(szMsg);


	GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->SetWindowText(szMsg);
	GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->SetWindowText(szMsg);
	GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->SetWindowText(szMsg);
	GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->SetWindowText(szMsg);


	GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->SetWindowText(szMsg);
	GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->SetWindowText(szMsg);

	m_editAoiLightVal[eAOI_LIGHT_CH1].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH1, this);
	m_editAoiLightVal[eAOI_LIGHT_CH2].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH2, this);
	m_editAoiLightVal[eAOI_LIGHT_CH3].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH3, this);
	m_editAoiLightVal[eAOI_LIGHT_CH4].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH4, this);
	m_editAoiLightVal[eAOI_LIGHT_CH5].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH5, this);
	m_editAoiLightVal[eAOI_LIGHT_CH6].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH6, this);
	m_editAoiLightVal[eAOI_LIGHT_CH7].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH7, this);
	m_editAoiLightVal[eAOI_LIGHT_CH8].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH8, this);
	m_editAoiLightVal[eAOI_LIGHT_CH9].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH9, this);
	m_editAoiLightVal[eAOI_LIGHT_CH10].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH10, this);
	m_editAoiLightVal[eAOI_LIGHT_CH11].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH11, this);
	m_editAoiLightVal[eAOI_LIGHT_CH12].SubclassDlgItem(IDC_EDIT_AOI_LIGHT_CH12, this);

	for (int i = 0; i < AOI_LIGHT_CH_COUNT; i++)
	{
		m_editAoiLightVal[i].SetWindowText(_T("0"));
	}

	return TRUE;
}




void CVisionAgentMeasurementBrightnessDlg::OnBnClickedUpDownBtnBtn(UINT uID)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nValue = 10;
	CString szMsg;

	switch (uID)
	{
	case IDC_BTN_REVIEW_COAXIAL_DOWN_10:
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_BACKLIGHT_DOWN_10:
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_RING_DOWNN_10:
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) -10;
		if (nValue < 50)
			nValue = 50;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->SetWindowText(szMsg);
		break;

	case IDC_10X_L_RING_OUT_2_DN10_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_3_DN10_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) -10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_4_DN10_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) -10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_1_DN10_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) -10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue );
		GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_2_DN10_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_3_DN10_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_4_DN10_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_COAXIAL_DOWN_10:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_BACKLIGHT_DOWN_10:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_RING_DOWN_10:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->SetWindowText(szMsg);
		break;

	//case IDC_BTN_BOX_ALIGN_L_RING_DOWN_1:
	//	GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->GetWindowText(szMsg);
	//	nValue = _ttoi(szMsg) - 10;
	//	if (nValue < 0)
	//		nValue = 0;
	//	szMsg.Format(_T("%d"), nValue);
	//	GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->SetWindowText(szMsg);
	//	break;
	case IDC_10X_R_RING_OUT_3_DN10_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_4_DN10_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_1_DN10_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_2_DN10_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_3_DN10_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_4_DN10_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_COAXIAL_DOWN_10:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_RING_DOWN_10:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_COAXIAL_DOWN_10:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_RING_DOWN_10:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 10;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->SetWindowText(szMsg);
		break;


	case IDC_BTN_REVIEW_COAXIAL_DOWN_1:
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_BACKLIGHT_DOWNN_1:
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_RING_DOWN_1:
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 50)
			nValue = 50;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_2_DN1_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_3_DN1_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_4_DN1_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_1_DN1_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_2_DN1_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_3_DN1_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_4_DN1_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_COAXIAL_DOWN_1:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_BACKLIGHT_DOWN_1:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->SetWindowText(szMsg);
		break;
	
	case IDC_BTN_BOX_ALIGN_L_RING_DOWN_1:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->SetWindowText(szMsg);
		break;

	case IDC_10X_R_RING_OUT_2_DN1_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_3_DN1_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_4_DN1_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_1_DN1_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_2_DN1_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_3_DN1_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_4_DN1_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_COAXIAL_DOWN_1:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_RING_DOWN_1:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_COAXIAL_DOWN_1:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_RING_DOWN_1:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) - 1;
		if (nValue < 0)
			nValue = 0;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->SetWindowText(szMsg);
		break;







	case IDC_BTN_REVIEW_COAXIAL_UP_10:
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 100)
			nValue = 100;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_BACKLIGHT_UP_10:
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_RING_UP_10:
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 800)
			nValue = 800;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_2_UP10_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_3_UP10_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_4_UP10_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_1_UP10_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_2_UP10_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_3_UP10_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_4_UP10_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_COAXIAL_UP_10:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_BACKLIGHT_UP_10:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_RING_UP_10:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_2_UP10_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_3_UP10_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_4_UP10_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_1_UP10_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_2_UP10_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_3_UP10_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_4_UP10_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_COAXIAL_UP_10:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_RING_UP_10:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_COAXIAL_UP_10:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_RING_UP_10:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 10;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->SetWindowText(szMsg);
		break;





		
	case IDC_BTN_REVIEW_COAXIAL_UP_1:
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 100)
			nValue = 100;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_BACKLIGHT_UP_1:
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_RING_UP_1:
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 800)
			nValue = 800;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_2_UP1_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_3_UP1_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_OUT_4_UP1_BTN:
		GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_OUT_4_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_1_UP1_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_1_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_2_UP1_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_3_UP1_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_L_RING_IN_4_UP1_BTN:
		GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_L_RING_IN_4_EDIT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_COAXIAL_UP_1:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_BACKLIGHT_UP_1:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_RING_UP_1:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_2_UP1_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_3_UP1_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_OUT_4_UP1_BTN:
		GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_OUT_4_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_1_UP1_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_1_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_2_UP1_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_2_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_3_UP1_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_3_EDIT)->SetWindowText(szMsg);
		break;
	case IDC_10X_R_RING_IN_4_UP1_BTN:
		GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_10X_R_RING_IN_4_EDIT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_COAXIAL_UP_1:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_RING_UP_1:
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_COAXIAL_UP_1:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_RING_UP_1:
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->GetWindowText(szMsg);
		nValue = _ttoi(szMsg) + 1;
		if (nValue > 255)
			nValue = 255;
		szMsg.Format(_T("%d"), nValue);
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->SetWindowText(szMsg);
		break;
			   

	case IDC_BTN_REVIEW_COAXIAL_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_RING_SET_0:
		szMsg.Format(_T("50"));
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_BACKLIGHT_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_COAXIAL_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_RING_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_BACKLIGHT_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_COAXIAL_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_RING_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_COAXIAL_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_RING_SET_0:
		szMsg.Format(_T("0"));
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_COAXIAL_SET_255:
		szMsg.Format(_T("100"));
		GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_RING_SET_255:
		szMsg.Format(_T("800"));
		GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->SetWindowText(szMsg);
		break;

	case IDC_BTN_REVIEW_BACKLIGHT_SET_255:
		szMsg.Format(_T("255"));
		GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_COAXIAL_SET_255:
		szMsg.Format(_T("255"));
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_L_RING_SET_255:
		szMsg.Format(_T("255"));
		GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_BACKLIGHT_SET_255:
		szMsg.Format(_T("255"));
		GetDlgItem(IDC_EDIT_PRE_ALIGN_BACKLIGHT)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_COAXIAL_SET_255:
		szMsg.Format(_T("255"));
		GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_PRE_ALIGN_RING_SET_255:
		szMsg.Format(_T("255"));
		GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_COAXIAL_SET_255:
		szMsg.Format(_T("255"));
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->SetWindowText(szMsg);
		break;

	case IDC_BTN_BOX_ALIGN_R_RING_SET_255:
		szMsg.Format(_T("255"));
		GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->SetWindowText(szMsg);
		break;
	}
}

void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnLightOffAll()
{
	//21.03.01 sjc
	SharedInfo::LightAllOff();

	//g_CommLight_8ch.SetLight_PreAlign(0, 0);
	//Sleep(100); //!!
	//g_CommLight_8ch.SetLight_Review_Coaxial(0);
	//Sleep(100); //!!
	//g_CommLight_12ch.SetLight_Review_Ring(0);
	//Sleep(100); //!!
	//g_CommLight_8ch.SetLight_BoxAlignL(0, 0);
	//Sleep(100); //!!
	//g_CommLight_8ch.SetLight_BoxAlignR(0, 0);
	//Sleep(100); //!!
	//g_CommMLCLedLight.AoiLightOff();
	//Sleep(100);
	//g_CommMLCLedLight.BackLightOff();
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedLightOnBacklightBtn()
{
	CString Str = _T("");
	GetDlgItem(IDC_EDIT_REVIEW_BACKLIGHT)->GetWindowText(Str);

	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	{
		nBackLightVal[i] = _ttoi(Str);
	}

	//g_CommBack_Light.BackLightOn(nBackLightVal);
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedLightOffBacklightBtn()
{
	//g_CommBack_Light.BackLightOff();
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedLightOnAoiLightOffBtn()
{
	//21.03.01 SJC TEMP DEL
	//g_CommMLCLedLight.AoiLightOff();
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedLightOnAoiLightOnBtn()
{
	CString Str = _T("");
	int nValue = 0;

	for (int i = 0; i < AOI_LIGHT_CH_COUNT; i++)
	{
		m_editAoiLightVal[eAOI_LIGHT_CH1 + i].GetWindowText(Str);
		nValue = _ttoi(Str);
		//21.03.01 SJC TEMP DEL
		//g_CommMLCLedLight.SetAoiLight(i, nValue);
		Sleep(10);
	}

	//g_CommMLCLedLight.AoiLightOn();
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessReview10xLightOn()
{
	CString Str = _T("");
	int Coaxial, Ring[8];

	//Review10x
	GetDlgItem(IDC_EDIT_REVIEW_COAXIAL)->GetWindowText(Str);
	Coaxial = _ttoi(Str);
	GetDlgItem(IDC_EDIT_REVIEW_RING_OUT_1)->GetWindowText(Str);
	Ring[0] = _ttoi(Str);

	g_CommReview_Light.SetLight_Review(Ring[0],Coaxial);


}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessPreAlignLightOn()
{
	CString Str = _T("");
	int Coaxial, Ring;

	//21.02.22 sjc
	//PreAlign
	//GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->GetWindowText(Str);
	//Coaxial = _ttoi(Str);
	//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(Coaxial);
	//Sleep(10);
	//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
	//GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->GetWindowText(Str);
	//Ring = _ttoi(Str);
	//g_CommZomm_Ring.SetLight_Zoom_Ring(Ring);
	//Sleep(10);
	//g_CommZomm_Ring.Zoom_Light_On(TRUE);

	//GetDlgItem(IDC_EDIT_PRE_ALIGN_COAXIAL)->GetWindowText(Str);
	//Coaxial = _ttoi(Str);

	//GetDlgItem(IDC_EDIT_PRE_ALIGN_RING)->GetWindowText(Str);
	//Ring = _ttoi(Str);

	//g_CommLoader_Light.SetLight_PreAlign(Coaxial, Ring);
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessBoxAlignLeftLightOn()
{
	CString Str = _T("");
	int Coaxial, Ring[8];

	//Box Align L
	//GetDlgItem(IDC_EDIT_BOX_ALIGN_L_COAXIAL)->GetWindowText(Str);
	//Coaxial = _ttoi(Str);
	//GetDlgItem(IDC_EDIT_BOX_ALIGN_L_RING)->GetWindowText(Str);
	//Ring[0] = _ttoi(Str);
	//g_CommLoader_Light.SetLight_Left_Loader( Ring[0], Coaxial);
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessBoxAlignRightLightOn()
{
	CString Str = _T("");
	int Coaxial, Ring;

	//Box Align R
	//GetDlgItem(IDC_EDIT_BOX_ALIGN_R_COAXIAL)->GetWindowText(Str);
	//Coaxial = _ttoi(Str);
	//GetDlgItem(IDC_EDIT_BOX_ALIGN_R_RING)->GetWindowText(Str);
	//Ring = _ttoi(Str);
	//g_CommLoader_Light.SetLight_Right_Loader(Ring, Coaxial);
}

void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessReview10xLightOff()
{
	g_CommReview_Light.SetLight_Review(0, 0);

	//21.03.01 SJC
	//g_CommLoader_Light.SetLight_Right_Loader(0, 0);//box align right off
	//g_CommLight_8ch.SetLight_BoxAlignR(0, 0);
	//g_CommLight_8ch.SetLight_Review_Coaxial(0);
	//Sleep(100); //!!
	//g_CommLight_12ch.SetLight_Review_Ring(0);
}

void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessPreAlignLightOff()
{
	//21.02.22 sjc
	//PreAlign
	//g_CommZomm_Coaxial.Zoom_Light_On(FALSE);
	//Sleep(10);
	//g_CommZomm_Ring.Zoom_Light_On(FALSE);

	//g_CommLoader_Light.SetLight_PreAlign(0, 0);
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessBoxAlignLeftLightOff()
{
	//g_CommLoader_Light.SetLight_Left_Loader(0, 0);
}


void CVisionAgentMeasurementBrightnessDlg::OnBnClickedBtnBrightnessBoxAlignRightLightOff()
{
	//g_CommLoader_Light.SetLight_Right_Loader(0, 0);
}
