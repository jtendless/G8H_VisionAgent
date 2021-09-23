// Manual_Sub_Clamp_Fixed_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Clamp_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Clamp_Fixed_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Clamp_Fixed_Pos, CDialogEx)

CManual_Sub_Clamp_Fixed_Pos::CManual_Sub_Clamp_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_CLAMP_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_CLAMP_FIXED_POS, pParent);
}
//------------------------------------------------------------------
CManual_Sub_Clamp_Fixed_Pos::~CManual_Sub_Clamp_Fixed_Pos()
{
}
//------------------------------------------------------------------
void CManual_Sub_Clamp_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//------------------------------------------------------------------
BOOL CManual_Sub_Clamp_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CManual_Sub_Clamp_Fixed_Pos, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_FIXED_SET_TORQUE, &CManual_Sub_Clamp_Fixed_Pos::OnBnClickedButtonManualSubClampFixedSetTorque)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_FIXED_POS_SAVE, &CManual_Sub_Clamp_Fixed_Pos::OnBnClickedButtonManualSubClampFixedPosSave)
END_MESSAGE_MAP()


// CManual_Sub_Clamp_Fixed_Pos 메시지 처리기

//------------------------------------------------------------------
void CManual_Sub_Clamp_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		InitPara();
	}
	else if (bShow == FALSE)
	{
	}
}
//------------------------------------------------------------------
void CManual_Sub_Clamp_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
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


	m_btnSave.MoveWindow(RectSaveBtn);
}
BOOL	CManual_Sub_Clamp_Fixed_Pos::Is_Comp_Usable()
{
	if (m_btnSave.GetSafeHwnd() == NULL) return FALSE;

	return TRUE;
}

void CManual_Sub_Clamp_Fixed_Pos::InitCtrl()
{
	m_stcClampTorque.SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_FIXED_CURRENT_TORQUE, this);
	m_editClampTorque.SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CLAMP_FIXED_CLAMP_TORQUE, this);

	m_btnSave.SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_CLAMP_FIXED_POS_SAVE, this);
	m_btnSave.SetColor(BLACK, LTGRAY);
}
void CManual_Sub_Clamp_Fixed_Pos::InitPara()
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), CManualData::m_ManualDataClamp.Info.m_dClampTorque);
	m_stcClampTorque.SetWindowText(Str);
}

void CManual_Sub_Clamp_Fixed_Pos::CheckChangeData()
{
	CString Str = _T("");
	m_stcClampTorque.GetWindowText(Str);
	CManualData::m_ManualDataClamp.Info.m_dClampTorque = _ttof(Str);
}

void CManual_Sub_Clamp_Fixed_Pos::OnBnClickedButtonManualSubClampFixedSetTorque()
{
	CString Str = _T(""), StrMsg = _T("");
	m_editClampTorque.GetWindowText(Str);
	m_stcClampTorque.SetWindowText(Str);

	double dTorque = _ttof(Str);
	StrMsg.Format(_T("[Manual-Clamp-Fixed] Clamp Torque Set Click (%.5f)"), dTorque);
	Total_Msg(StrMsg);
}

void CManual_Sub_Clamp_Fixed_Pos::OnBnClickedButtonManualSubClampFixedPosSave()
{
	Total_Msg(_T("[Manual-Clamp-Fixed] Save Click"));

	CheckChangeData();
	CManualData::m_ManualDataClamp.Save();

	AfxMessageBox(_T("Save Ok"));
}
