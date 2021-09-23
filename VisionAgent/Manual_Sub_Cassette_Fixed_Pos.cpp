// Manual_Sub_Cassette_Fixed_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Cassette_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Cassette_Fixed_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Cassette_Fixed_Pos, CDialogEx)

CManual_Sub_Cassette_Fixed_Pos::CManual_Sub_Cassette_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_CASSETTE_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_CASSETTE_FIXED_POS, pParent);
}

CManual_Sub_Cassette_Fixed_Pos::~CManual_Sub_Cassette_Fixed_Pos()
{
}

void CManual_Sub_Cassette_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Cassette_Fixed_Pos, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_FIXED_POS_SAVE, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteFixedPosSave)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_GET_WAIT_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGetWaitPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_GET_SLOT_FIRST_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGetSlotFirstPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_GET_1FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGet1floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_GET_2FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGet2floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_GET_3FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGet3floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_GET_4FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGet4floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_SET_WAIT_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSetWaitPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_SET_1FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSet1floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_SET_2FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSet2floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_SET_3FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSet3floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_SET_4FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSet4floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MOVE_WAIT_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMoveWaitPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MOVE_1FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMove1floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MOVE_2FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMove2floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MOVE_3FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMove3floorPosCassetteZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MOVE_4FLOOR_POS_CASSETTE_Z, &CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMove4floorPosCassetteZ)
END_MESSAGE_MAP()


// CManual_Sub_Cassette_Fixed_Pos 메시지 처리기

BOOL CManual_Sub_Cassette_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		InitPara();

		//SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		//KillTimer(1);
	}
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
	int nOffset = 5;
	CRect	RectSaveBtn;
	int		nBtnSize_X = 100;
	int		nBtnSize_Y = 50;
	RectSaveBtn.left = cx - nOffset - nBtnSize_X;
	RectSaveBtn.top = cy - nOffset - nBtnSize_Y;
	RectSaveBtn.right = cx - nOffset;
	RectSaveBtn.bottom = cy - nOffset;
	GetDlgItem(IDC_BUTTON_MANUAL_SUB_CASSETTE_FIXED_POS_SAVE)->MoveWindow(RectSaveBtn);
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Fixed_Pos::OnTimer(UINT_PTR nIDEvent)
{
	//if (Devs::m_JogMotion.IsMotionDone(AXIS_LOADING_STAGE_X1) == TRUE)

	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
void	CManual_Sub_Cassette_Fixed_Pos::InitCtrl()
{
	//Stc
	m_stcPos[_eCASSETTE_Z_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CASSETTE_CURRENT_WAIT_POS_CASSETTE_Z, this);
	m_stcPos[_eCASSETTE_Z_SLOT_FIRST_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CASSETTE_CURRENT_SLOT_FIRST_POS_CASSETTE_Z, this);
	m_stcPos[_eCASSETTE_Z_1FLOOR_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CASSETTE_CURRENT_1FLOOR_POS_CASSETTE_Z, this);
	m_stcPos[_eCASSETTE_Z_2FLOOR_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CASSETTE_CURRENT_2FLOOR_POS_CASSETTE_Z, this);
	m_stcPos[_eCASSETTE_Z_3FLOOR_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CASSETTE_CURRENT_3FLOOR_POS_CASSETTE_Z, this);
	m_stcPos[_eCASSETTE_Z_4FLOOR_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CASSETTE_CURRENT_4FLOOR_POS_CASSETTE_Z, this);
	m_stcPos[_eCASSETTE_Z_5FLOOR_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CASSETTE_CURRENT_5FLOOR_POS_CASSETTE_Z, this);
	m_stcPos[_eCASSETTE_Z_6FLOOR_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CASSETTE_CURRENT_6FLOOR_POS_CASSETTE_Z, this);

	//Edit
	m_editPos[_eCASSETTE_Z_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_WAIT_POS_CASSETTE_Z, this);
	m_editPos[_eCASSETTE_Z_SLOT_FIRST_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_SLOT_FIRST_POS_CASSETTE_Z, this);
	m_editPos[_eCASSETTE_Z_1FLOOR_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_1FLOOR_POS_CASSETTE_Z, this);
	m_editPos[_eCASSETTE_Z_2FLOOR_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_2FLOOR_POS_CASSETTE_Z, this);
	m_editPos[_eCASSETTE_Z_3FLOOR_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_3FLOOR_POS_CASSETTE_Z, this);
	m_editPos[_eCASSETTE_Z_4FLOOR_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_4FLOOR_POS_CASSETTE_Z, this);
	m_editPos[_eCASSETTE_Z_5FLOOR_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_5FLOOR_POS_CASSETTE_Z, this);
	m_editPos[_eCASSETTE_Z_6FLOOR_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_6FLOOR_POS_CASSETTE_Z, this);
}
//------------------------------------------------------------------
BOOL	CManual_Sub_Cassette_Fixed_Pos::Is_Comp_Usable()
{
	if (GetDlgItem(IDC_BUTTON_MANUAL_SUB_CASSETTE_FIXED_POS_SAVE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Fixed_Pos::InitPara()
{
	CString Str = _T("");

	//Cassette Z
	Str.Format(_T("%.5f"), CManualData::m_ManualDataCassette.Info.m_dCassetteZ_Wait_Pos);
	m_stcPos[_eCASSETTE_Z_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataCassette.Info.m_dCassetteZ_1Floor_Pos);
	m_stcPos[_eCASSETTE_Z_1FLOOR_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataCassette.Info.m_dCassetteZ_2Floor_Pos);
	m_stcPos[_eCASSETTE_Z_2FLOOR_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataCassette.Info.m_dCassetteZ_3Floor_Pos);
	m_stcPos[_eCASSETTE_Z_3FLOOR_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataCassette.Info.m_dCassetteZ_4Floor_Pos);
	m_stcPos[_eCASSETTE_Z_4FLOOR_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataCassette.Info.m_dCassetteZ_5Floor_Pos);
	m_stcPos[_eCASSETTE_Z_5FLOOR_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataCassette.Info.m_dCassetteZ_6Floor_Pos);
	m_stcPos[_eCASSETTE_Z_6FLOOR_POS].SetWindowText(Str);
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Fixed_Pos::CheckChangeData()
{
	CString Str = _T("");

	//Cassette Z
	m_stcPos[_eCASSETTE_Z_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataCassette.Info.m_dCassetteZ_Wait_Pos = _ttof(Str);
	m_stcPos[_eCASSETTE_Z_1FLOOR_POS].GetWindowText(Str);
	CManualData::m_ManualDataCassette.Info.m_dCassetteZ_1Floor_Pos = _ttof(Str);
	m_stcPos[_eCASSETTE_Z_2FLOOR_POS].GetWindowText(Str);
	CManualData::m_ManualDataCassette.Info.m_dCassetteZ_2Floor_Pos = _ttof(Str);
	m_stcPos[_eCASSETTE_Z_3FLOOR_POS].GetWindowText(Str);
	CManualData::m_ManualDataCassette.Info.m_dCassetteZ_3Floor_Pos = _ttof(Str);
	m_stcPos[_eCASSETTE_Z_4FLOOR_POS].GetWindowText(Str);
	CManualData::m_ManualDataCassette.Info.m_dCassetteZ_4Floor_Pos = _ttof(Str);
	m_stcPos[_eCASSETTE_Z_5FLOOR_POS].GetWindowText(Str);
	CManualData::m_ManualDataCassette.Info.m_dCassetteZ_5Floor_Pos = _ttof(Str);
	m_stcPos[_eCASSETTE_Z_6FLOOR_POS].GetWindowText(Str);
	CManualData::m_ManualDataCassette.Info.m_dCassetteZ_6Floor_Pos = _ttof(Str);

}
enum_Axis CManual_Sub_Cassette_Fixed_Pos::GetAxisNo(enum_Cassette_Axis eCassetteAxis, CString *strDiscription)
{
	CString Str = _T("");

	enum_Axis eAxis = AXIS_NONE;
	switch (eCassetteAxis)
	{
	case _eMANUAL_CASSETTE_AXIS_Z:		eAxis = AXIS_MAGAZINE_LIFT_Z; Str = _T("Cassette Z");  break;
	}

	*strDiscription = Str;

	return eAxis;
}

BOOL CManual_Sub_Cassette_Fixed_Pos::ManualAbsMove(enum_Cassette_Axis eCassetteAxis, double dPos)
{
	CString strAxisName = _T(""), Str = _T("");
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = GetAxisNo(eCassetteAxis, &strAxisName);
	double dCurPos = 0.0;

	SharedInfo::GetManualSpeed(eAxis, eAXIS_SPEED_MEDIUM, &dVel, &dAccel, &dDecel);

	Str.Format(_T("%s Abs Move To Pos: %.5f Start?"), strAxisName, dPos);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		dCurPos = SharedInfo::GetCmdPos(eAxis);

		Devs::m_JogMotion.AbsMove(eAxis, dPos, dVel, dAccel, dDecel);

		Str.Format(_T("[Manual-Cassette-Fixed] %s Abs Move %.5f -> %.5f"), strAxisName, dCurPos, dPos);
		Total_Msg(Str);
	}

	return TRUE;
}

double CManual_Sub_Cassette_Fixed_Pos::GetTargetPos(enum_Cassette_Pos eCassettePos)
{
	CString Str = _T("");
	double dPos = 0.0;
	m_editPos[eCassettePos].GetWindowText(Str);
	dPos = _ttof(Str);

	return dPos;
}

void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteFixedPosSave()
{
	CheckChangeData();
	CManualData::m_ManualDataCassette.Save();

	AfxMessageBox(_T("Save Ok"));
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGetWaitPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_MAGAZINE_LIFT_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eCASSETTE_Z_WAIT_POS].SetWindowText(Str);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGetSlotFirstPosCassetteZ()
{
	// TODO: Add your control notification handler code here
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGet1floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_MAGAZINE_LIFT_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eCASSETTE_Z_1FLOOR_POS].SetWindowText(Str);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGet2floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_MAGAZINE_LIFT_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eCASSETTE_Z_2FLOOR_POS].SetWindowText(Str);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGet3floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_MAGAZINE_LIFT_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eCASSETTE_Z_3FLOOR_POS].SetWindowText(Str);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteGet4floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_MAGAZINE_LIFT_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eCASSETTE_Z_4FLOOR_POS].SetWindowText(Str);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSetWaitPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eCASSETTE_Z_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Cassette-Fixed] Cassette Z Pos Set Click (Wait Pos : %.5f)"), dPos);
	StrMsg.Format(StrMsg);
	Total_Msg(StrMsg);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSet1floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eCASSETTE_Z_1FLOOR_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Cassette-Fixed] Cassette Z Pos Set Click (1Floor Pos : %.5f)"), dPos);
	StrMsg.Format(StrMsg);
	Total_Msg(StrMsg);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSet2floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eCASSETTE_Z_2FLOOR_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Cassette-Fixed] Cassette Z Pos Set Click (2Floor Pos : %.5f)"), dPos);
	StrMsg.Format(StrMsg);
	Total_Msg(StrMsg);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSet3floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eCASSETTE_Z_3FLOOR_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Cassette-Fixed] Cassette Z Pos Set Click (3Floor Pos : %.5f)"), dPos);
	StrMsg.Format(StrMsg);
	Total_Msg(StrMsg);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteSet4floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eCASSETTE_Z_4FLOOR_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Cassette-Fixed] Cassette Z Pos Set Click (4Floor Pos : %.5f)"), dPos);
	StrMsg.Format(StrMsg);
	Total_Msg(StrMsg);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMoveWaitPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	double dPos = GetTargetPos(_eCASSETTE_Z_WAIT_POS);
	ManualAbsMove(_eMANUAL_CASSETTE_AXIS_Z, dPos);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMove1floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	double dPos = GetTargetPos(_eCASSETTE_Z_1FLOOR_POS);
	ManualAbsMove(_eMANUAL_CASSETTE_AXIS_Z, dPos);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMove2floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	double dPos = GetTargetPos(_eCASSETTE_Z_2FLOOR_POS);
	ManualAbsMove(_eMANUAL_CASSETTE_AXIS_Z, dPos);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMove3floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here

	double dPos = GetTargetPos(_eCASSETTE_Z_3FLOOR_POS);
	ManualAbsMove(_eMANUAL_CASSETTE_AXIS_Z, dPos);
}


void CManual_Sub_Cassette_Fixed_Pos::OnBnClickedButtonManualSubCassetteMove4floorPosCassetteZ()
{
	// TODO: Add your control notification handler code here
	double dPos = GetTargetPos(_eCASSETTE_Z_4FLOOR_POS);
	ManualAbsMove(_eMANUAL_CASSETTE_AXIS_Z, dPos);
}
