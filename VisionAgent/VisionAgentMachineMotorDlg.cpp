// VisionAgentModelDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentMachineMotorDlg.h"
#include "afxdialogex.h"


// CVisionAgentMachineMotorDlg 대화 상자

IMPLEMENT_DYNAMIC(CVisionAgentMachineMotorDlg, CDialogEx)

CVisionAgentMachineMotorDlg::CVisionAgentMachineMotorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISION_AGENT_MACHINE_MOTOR_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_MACHINE_MOTOR_DIALOG, pParent);
}

CVisionAgentMachineMotorDlg::~CVisionAgentMachineMotorDlg()
{
}

void CVisionAgentMachineMotorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentMachineMotorDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_MACHINE_MOTOR_UPDATE_BTN, &CVisionAgentMachineMotorDlg::OnBnClickedMachineMotorUpdateBtn)
	//ON_NOTIFY(NM_CLICK, IDC_LIST_RECIPE_DATA, &CVisionAgentMachineMotorDlg::OnNMClickVisonAgentModelStickList)
	ON_MESSAGE(WM_CLICK, OnListCtrlClick)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CVisionAgentMachineMotorDlg 메시지 처리기
BOOL CVisionAgentMachineMotorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();
	InitSpread();
	InitListControlPara();
	InitDefaultPara();

	return TRUE;
}

void CVisionAgentMachineMotorDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		InitDefaultPara();
		InitUI();
	}
	else if (bShow == FALSE)
	{
	}
}


void CVisionAgentMachineMotorDlg::InitSpread()
{
	//CRect rect;

	//USES_CONVERSION;

	//m_procsTexts.Add(_T("No"));
	//m_procsTexts.Add(_T("WorkSpeed"));
	//m_procsTexts.Add(_T("Acc"));
	//m_procsTexts.Add(_T("Dec"));
	//m_procsTexts.Add(_T("JogHigh"));
	//m_procsTexts.Add(_T("JogMidium"));
	//m_procsTexts.Add(_T("JogLow"));
	//m_procsTexts.Add(_T("SafeMin"));
	//m_procsTexts.Add(_T("SafeMax"));
	//m_procsTexts.Add(_T("OriginPos"));

	//m_spread = (TSpread*)GetDlgItem(IDC_MOTOR_PARA_CST);
	//	m_spread->SetBool(SSB_HORZSCROLLBAR, FALSE);
	//m_spread->SetMaxRows(AXIS_MAX - 3);
	//m_spread->SetMaxCols(MAX_MOTOR_PARA_LIST_QUAN - 1);

	//m_spread->GetClientRect(&rect);
	//m_spread->SetColHeaderDisplay(SS_HEADERDISPLAY_LETTERS);
	//m_spread->SetColWidthInPixels(0, 50);

	//for (int i = 0; i < MAX_MOTOR_PARA_LIST_QUAN; i++)
	//{
 //		if (i == 1)
	//		m_spread->SetColWidthInPixels(i, (rect.Width() / MAX_MOTOR_PARA_LIST_QUAN) * 1.5);
	//	else if(i != 0)
	//		m_spread->SetColWidthInPixels(i, rect.Width() / MAX_MOTOR_PARA_LIST_QUAN);
	//		

	//	m_spread->SetData(i, 0, (LPCTSTR)T2A(m_procsTexts.GetAt(i)));
	//}


}

void CVisionAgentMachineMotorDlg::InitCtrl()
{
	m_bDialog_Entry = TRUE;

	m_stcName.SubclassDlgItem(IDC_MACHINE_MOTOR_NAME_STC, this);
	m_EditAutoVel.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_AUTO_VEL, this);
	m_EditAutoAccel.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_AUTO_ACCEL, this);
	m_EditAutoDecel.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_AUTO_DECEL, this);
	m_EditManualHighVel.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_MANUAL_HIGH_VEL, this);
	m_EditManualMediumVel.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_MANUAL_MEDIUM_VEL, this);
	m_EditManualLowVel.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_MANUAL_LOW_VEL, this);
	m_EditSafetyPosMin.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_SAFETY_POS_MIN, this);
	m_EditSafetyPosMax.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_SAFETY_POS_MAX, this);
	m_EditOrginPos.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_ORGIN_POS, this);
	m_EditMaxVel.SubclassDlgItem(IDC_EDIT_MACHINE_MOTOR_MAX_VEL, this);
}

void CVisionAgentMachineMotorDlg::InitDefaultPara()
{
	CString Str;

	Str = m_AxisName[0];
	Str.Format(Str);
	m_stcName.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoVel[0]);
	m_EditAutoVel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoAccel[0]);
	m_EditAutoAccel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoDecel[0]);
	m_EditAutoDecel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualHighVel[0]);
	m_EditManualHighVel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualMediumVel[0]);
	m_EditManualMediumVel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualLowVel[0]);
	m_EditManualLowVel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[0]);
	m_EditSafetyPosMin.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[0]);
	m_EditSafetyPosMax.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dOriginPos[0]);
	m_EditOrginPos.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dMaxVel[0]);
	m_EditMaxVel.SetWindowText(Str);
}

void CVisionAgentMachineMotorDlg::InitListControlPara()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str;

	CRect Rect;
	GetDlgItem(IDC_VISION_AGENT_MACHINE_MOTOR_LIST)->GetClientRect(&Rect);
	int nPreSize = (Rect.Width() - 50) / (MAX_MOTOR_PARA_LIST_QUAN - 1);

	CImageList m_ImageList;
	CString strTeg[MAX_MOTOR_PARA_LIST_QUAN] = { _T("No"), _T("Name"), _T("WorkSpeed"), _T("Acc"), _T("Dec"), _T("JogHigh"), _T("JogMidium"), _T("JogLow"), _T("SafeMin"), _T("SafeMax"), _T("OriginPos"), _T("VelocityMax") };
	//CString strComboData[2] = { _T("Image"), _T("Laser") };

	INT nColSize[MAX_MOTOR_PARA_LIST_QUAN];
	COLORREF m_BkColor[MAX_MOTOR_PARA_LIST_QUAN];
	COLORREF m_TextColor[MAX_MOTOR_PARA_LIST_QUAN];
	INT nInpuMethod[MAX_MOTOR_PARA_LIST_QUAN] = { eMETHOD_NO_USE, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL };

	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	m_pListCtrl = new CCommonListCtrl;
	m_pListCtrl->SubclassDlgItem(IDC_VISION_AGENT_MACHINE_MOTOR_LIST, this);

	/// Setting
	m_pListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	for (int i = 0; i < MAX_MOTOR_PARA_LIST_QUAN; i++)
	{
		if (i == 0)
		{
			nColSize[i] = 50;
			m_BkColor[i] = RGB(215, 215, 215);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else if (i == 1)
		{
			nColSize[i] = 220;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else
		{
			nColSize[i] = nPreSize;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
	}

	m_pListCtrl->SetListColumn(strTeg, nColSize, MAX_MOTOR_PARA_LIST_QUAN, m_BkColor, m_TextColor, nInpuMethod);
	//m_pListCtrl->SetColData(3, 2, strComboData);
	m_pListCtrl->m_nListCnt = 0;

	m_AxisName[AXIS_GANTRY_Y1] = _T("AXIS_GANTRY_Y1");
	m_AxisName[AXIS_GANTRY_Y2] = _T("AXIS_GANTRY_Y2 ");
	m_AxisName[AXIS_GANTRY_X] = _T("AXIS_GANTRY_X ");
	m_AxisName[AXIS_CAMERA_Z1] = _T("AXIS_CAMERA_Z1");
	m_AxisName[AXIS_CAMERA_Z2] = _T("AXIS_CAMERA_Z2");

	//TO DO

	InitUI();
}

void CVisionAgentMachineMotorDlg::OnBnClickedMachineMotorUpdateBtn()
{
	if (CheckChangeData()) //KJT 20210807
	{
		UpdateUI();
	}
}

void CVisionAgentMachineMotorDlg::ChangeSpreadData()
{
	//HGLOBAL hText;
	//BYTE  bstrCellData[20] = {};
	//LPTSTR strCellData;
	//CString szMsg = _T("");
	int nRowCount = 0;
	CString szMsg[MAX_MOTOR_PARA_LIST_QUAN] = { _T(""), };
	nRowCount = m_pListCtrl->GetMaxListCount();
	//
	//	
	//USES_CONVERSION;

	//hText = GlobalAlloc(GHND, sizeof(TCHAR)*(10 + 1));
	//strCellData = (LPTSTR)GlobalLock(hText);

	for (int nRowCount = 0; nRowCount < AXIS_MAX - 3; nRowCount++)
	{
		szMsg[0].Format(_T("%d"), nRowCount + 1);
		szMsg[1] = m_AxisName[nRowCount];

		m_pListCtrl->AddListData(nRowCount, szMsg);

		//	m_spread->SetData(1, i + 1, (LPCTSTR)T2A(szMsg));

	}
	//GlobalUnlock(hText); 	GlobalFree(hText);
}

void CVisionAgentMachineMotorDlg::ChangeSelSpreadData(INT nSelNum)
{

}

void CVisionAgentMachineMotorDlg::InitUI()
{

	int nRowCount = 0;
	CString szMsg[MAX_MOTOR_PARA_LIST_QUAN] = { _T(""), };

	m_pListCtrl->DeleteAllItems();

	nRowCount = m_pListCtrl->GetMaxListCount();

	for (int nRowCount = 0; nRowCount < AXIS_MAX; nRowCount++)
	{
		////
		if (CMachineData::m_MachineDataMotor.Info.dAutoVel[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dAutoVel[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dAutoVel[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dAutoAccel[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dAutoAccel[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dAutoAccel[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dAutoDecel[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dAutoDecel[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dAutoDecel[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dManualHighVel[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dManualHighVel[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dManualHighVel[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dManualMediumVel[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dManualMediumVel[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dManualMediumVel[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dManualLowVel[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dManualLowVel[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dManualLowVel[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dSafetyPosMin[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dSafetyPosMax[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dOriginPos[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dOriginPos[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dOriginPos[nRowCount]; }
		if (CMachineData::m_MachineDataMotor.Info.dMaxVel[nRowCount] == 0) { CMachineData::m_MachineDataMotor.Info.dMaxVel[nRowCount] = CMachineData::m_MachineDataMotor.DefaultInfo.dMaxVel[nRowCount]; }

		////
		szMsg[0].Format(_T("%d"), nRowCount + 1);
		szMsg[1] = m_AxisName[nRowCount];
		szMsg[2].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoVel[nRowCount]);
		szMsg[3].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoAccel[nRowCount]);
		szMsg[4].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoDecel[nRowCount]);
		szMsg[5].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualHighVel[nRowCount]);
		szMsg[6].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualMediumVel[nRowCount]);
		szMsg[7].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualLowVel[nRowCount]);
		szMsg[8].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[nRowCount]);
		szMsg[9].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[nRowCount]);
		szMsg[10].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dOriginPos[nRowCount]);
		szMsg[11].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dMaxVel[nRowCount]);

		m_pListCtrl->AddListData(nRowCount, szMsg);
	}
}

void CVisionAgentMachineMotorDlg::UpdateUI()
{
	int nRowCount = m_pListCtrl->GetSelectedItemNumber();
	if (nRowCount < 0)
		return;

	CString szMsg[MAX_MOTOR_PARA_LIST_QUAN] = { _T(""), };
	szMsg[0].Format(_T("%d"), nRowCount + 1);

	szMsg[1] = m_AxisName[nRowCount];
	szMsg[2].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoVel[nRowCount]);
	szMsg[3].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoAccel[nRowCount]);
	szMsg[4].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoDecel[nRowCount]);
	szMsg[5].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualHighVel[nRowCount]);
	szMsg[6].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualMediumVel[nRowCount]);
	szMsg[7].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualLowVel[nRowCount]);
	szMsg[8].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[nRowCount]);
	szMsg[9].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[nRowCount]);
	szMsg[10].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dOriginPos[nRowCount]);
	szMsg[11].Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dMaxVel[nRowCount]);
	m_pListCtrl->UpdateListData(nRowCount, szMsg);
}

BOOL CVisionAgentMachineMotorDlg::CheckChangeData()
{
	CString Str;
	double dVel_PaperUnloaderY = 0.0, dVel_LoaderY = 0.0;

	int nRowCount = m_pListCtrl->GetSelectedItemNumber();

	if (nRowCount < 0)
		return FALSE;

	//21.02.09 sjc add
	if (nRowCount == AXIS_GANTRY_Y1 || nRowCount == AXIS_GANTRY_Y2 )
	{
		CMachineData::m_MachineDataMotor.Info.dAutoVel[nRowCount] = CMachineData::m_MachineDataMotor.Info.dAutoVel[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dAutoAccel[nRowCount] = CMachineData::m_MachineDataMotor.Info.dAutoAccel[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dAutoDecel[nRowCount] = CMachineData::m_MachineDataMotor.Info.dAutoDecel[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dManualHighVel[nRowCount] = CMachineData::m_MachineDataMotor.Info.dManualHighVel[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dManualMediumVel[nRowCount] = CMachineData::m_MachineDataMotor.Info.dManualMediumVel[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dManualLowVel[nRowCount] = CMachineData::m_MachineDataMotor.Info.dManualLowVel[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[nRowCount] = CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[nRowCount] = CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dOriginPos[nRowCount] = CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_GANTRY_Y1];
		CMachineData::m_MachineDataMotor.Info.dMaxVel[nRowCount] = CMachineData::m_MachineDataMotor.Info.dMaxVel[AXIS_GANTRY_Y1];
		Total_Msg(_T("Gantry Y1,2 Can't Change. Change Virtual Y"));
		System_Msg(_T("Gantry Y1,2 Can't Change. Change Virtual Y"));

		return FALSE;
	}
	else
	{
		m_EditAutoVel.GetWindowText(Str);		CMachineData::m_MachineDataMotor.Info.dAutoVel[nRowCount] = _ttof(Str);
		m_EditAutoAccel.GetWindowText(Str);		CMachineData::m_MachineDataMotor.Info.dAutoAccel[nRowCount] = _ttof(Str);
		m_EditAutoDecel.GetWindowText(Str);		CMachineData::m_MachineDataMotor.Info.dAutoDecel[nRowCount] = _ttof(Str);
		m_EditManualHighVel.GetWindowText(Str);	CMachineData::m_MachineDataMotor.Info.dManualHighVel[nRowCount] = _ttof(Str);
		m_EditManualMediumVel.GetWindowText(Str);	CMachineData::m_MachineDataMotor.Info.dManualMediumVel[nRowCount] = _ttof(Str);
		m_EditManualLowVel.GetWindowText(Str);	CMachineData::m_MachineDataMotor.Info.dManualLowVel[nRowCount] = _ttof(Str);
		m_EditSafetyPosMin.GetWindowText(Str);	CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[nRowCount] = _ttof(Str);
		m_EditSafetyPosMax.GetWindowText(Str);	CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[nRowCount] = _ttof(Str);
		m_EditOrginPos.GetWindowText(Str);	CMachineData::m_MachineDataMotor.Info.dOriginPos[nRowCount] = _ttof(Str);
		m_EditMaxVel.GetWindowText(Str);		CMachineData::m_MachineDataMotor.Info.dMaxVel[nRowCount] = _ttof(Str);
	}
	if(nRowCount == AXIS_GANTRY_Y1)
	{
		CMachineData::m_MachineDataMotor.Info.dAutoVel[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dAutoVel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dAutoAccel[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dAutoAccel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dAutoDecel[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dAutoDecel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dManualHighVel[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dManualHighVel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dManualMediumVel[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dManualMediumVel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dManualLowVel[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dManualLowVel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dOriginPos[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dMaxVel[AXIS_GANTRY_Y1] = CMachineData::m_MachineDataMotor.Info.dMaxVel[nRowCount];

		CMachineData::m_MachineDataMotor.Info.dAutoVel[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dAutoVel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dAutoAccel[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dAutoAccel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dAutoDecel[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dAutoDecel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dManualHighVel[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dManualHighVel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dManualMediumVel[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dManualMediumVel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dManualLowVel[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dManualLowVel[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dOriginPos[nRowCount];
		CMachineData::m_MachineDataMotor.Info.dMaxVel[AXIS_GANTRY_Y2] = CMachineData::m_MachineDataMotor.Info.dMaxVel[nRowCount];
	}

	return TRUE;
}

//void CVisionAgentMachineMotorDlg::OnNMClickVisonAgentModelStickList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
//	CString szMsg;
//	m_ListClickIndex = pNMItemActivate->iItem;
//	szMsg.Format(_T("%d"), m_ListClickIndex + 1);
//	//m_StaticMaskNo.SetWindowText(szMsg);
//	SetItemValue(m_ListClickIndex);
//	*pResult = 0;
//}

void CVisionAgentMachineMotorDlg::SetItemValue(int StickIndex)
{
	CString Str;

	Str = m_AxisName[StickIndex];
	Str.Format(Str);
	m_stcName.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoVel[StickIndex]);
	m_EditAutoVel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoAccel[StickIndex]);
	m_EditAutoAccel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoDecel[StickIndex]);
	m_EditAutoDecel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualHighVel[StickIndex]);
	m_EditManualHighVel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualMediumVel[StickIndex]);
	m_EditManualMediumVel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualLowVel[StickIndex]);
	m_EditManualLowVel.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[StickIndex]);
	m_EditSafetyPosMax.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[StickIndex]);
	m_EditSafetyPosMin.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dOriginPos[StickIndex]);
	m_EditOrginPos.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dMaxVel[StickIndex]);
	m_EditMaxVel.SetWindowText(Str);
}





BOOL CVisionAgentMachineMotorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/*if()
	CRect Rect;
	m_pListCtrl->GetClientRect()*/
	return CDialogEx::PreTranslateMessage(pMsg);
}

LRESULT CVisionAgentMachineMotorDlg::OnListCtrlClick(WPARAM wParam, LPARAM lParam)
{
	int index = (int)wParam;
	SetItemValue(index);

	return 0;
}

void CVisionAgentMachineMotorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pListCtrl != NULL)
		delete m_pListCtrl;
}
