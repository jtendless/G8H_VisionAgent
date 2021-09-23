// Manual_Sub_Stretch_Fixed_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Stretch_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Stretch_Fixed_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Stretch_Fixed_Pos, CDialogEx)

CManual_Sub_Stretch_Fixed_Pos::CManual_Sub_Stretch_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_STRETCH_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_STRETCH_FIXED_POS, pParent);
}

CManual_Sub_Stretch_Fixed_Pos::~CManual_Sub_Stretch_Fixed_Pos()
{
}

void CManual_Sub_Stretch_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Stretch_Fixed_Pos, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_FIXED_SAVE, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchFixedSave)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_WAIT_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_FORWARD_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_BACKWARD_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_WAIT_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_FORWARD_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_BACKWARD_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_WAIT_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_FORWARD_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_BACKWARD_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_WAIT_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_FORWARD_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_BACKWARD_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_WAIT_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_FORWARD_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_BACKWARD_POS_STRETCH_LEFT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_WAIT_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_FORWARD_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_BACKWARD_POS_STRETCH_RIGHT, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_WAIT_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_FORWARD_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_BACKWARD_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_WAIT_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_FORWARD_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_BACKWARD_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_WAIT_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_FORWARD_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_BACKWARD_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_WAIT_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchRight3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_FORWARD_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchRight3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_GET_BACKWARD_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_WAIT_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_FORWARD_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_BACKWARD_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_WAIT_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_FORWARD_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_BACKWARD_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_WAIT_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_FORWARD_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_BACKWARD_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_WAIT_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchRight3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_FORWARD_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchRight3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_SET_BACKWARD_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_WAIT_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_FORWARD_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_BACKWARD_POS_STRETCH_LEFT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_WAIT_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_FORWARD_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_BACKWARD_POS_STRETCH_LEFT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_WAIT_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_FORWARD_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_BACKWARD_POS_STRETCH_RIGHT2, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_WAIT_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_FORWARD_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_STRETCH_MOVE_BACKWARD_POS_STRETCH_RIGHT3, &CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight3)
END_MESSAGE_MAP()


// CManual_Sub_Stretch_Fixed_Pos 메시지 처리기

BOOL CManual_Sub_Stretch_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Stretch_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE) return;
	CRect	RectSaveBtn;
	int		nOffset = 5;
	int		nBtnSize_X = 100;
	int		nBtnSize_Y = 50;
	RectSaveBtn.left = cx - nOffset - nBtnSize_X;
	RectSaveBtn.top = cy - nOffset - nBtnSize_Y;
	RectSaveBtn.right = cx - nOffset;
	RectSaveBtn.bottom = cy - nOffset;
	GetDlgItem(IDC_BUTTON_MANUAL_SUB_STRETCH_FIXED_SAVE)->MoveWindow(RectSaveBtn);
}
//------------------------------------------------------------------
void CManual_Sub_Stretch_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
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
//------------------------------------------------------------------
void	CManual_Sub_Stretch_Fixed_Pos::InitCtrl()
{
	m_stcPos[_eSTRETCH_LEFT_1_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_WAIT_POS_STRETCH_LEFT, this);
	m_stcPos[_eSTRETCH_LEFT_1_FWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_FORWARD_POS_STRETCH_LEFT, this);
	m_stcPos[_eSTRETCH_LEFT_1_BWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_BACKWARD_POS_STRETCH_LEFT, this);

	m_stcPos[_eSTRETCH_RIGHT_1_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_WAIT_POS_STRETCH_RIGHT, this);
	m_stcPos[_eSTRETCH_RIGHT_1_FWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_FORWARD_POS_STRETCH_RIGHT, this);
	m_stcPos[_eSTRETCH_RIGHT_1_BWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_BACKWARD_POS_STRETCH_RIGHT, this);

	//21.04.03 sjc
	m_stcPos[_eSTRETCH_LEFT_2_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_WAIT_POS_STRETCH_LEFT2, this);
	m_stcPos[_eSTRETCH_LEFT_2_FWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_FORWARD_POS_STRETCH_LEFT2, this);
	m_stcPos[_eSTRETCH_LEFT_2_BWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_BACKWARD_POS_STRETCH_LEFT2, this);

	m_stcPos[_eSTRETCH_RIGHT_2_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_WAIT_POS_STRETCH_RIGHT2, this);
	m_stcPos[_eSTRETCH_RIGHT_2_FWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_FORWARD_POS_STRETCH_RIGHT2, this);
	m_stcPos[_eSTRETCH_RIGHT_2_BWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_BACKWARD_POS_STRETCH_RIGHT2, this);

	m_stcPos[_eSTRETCH_LEFT_3_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_WAIT_POS_STRETCH_LEFT3, this);
	m_stcPos[_eSTRETCH_LEFT_3_FWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_FORWARD_POS_STRETCH_LEFT3, this);
	m_stcPos[_eSTRETCH_LEFT_3_BWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_BACKWARD_POS_STRETCH_LEFT3, this);

	m_stcPos[_eSTRETCH_RIGHT_3_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_WAIT_POS_STRETCH_RIGHT3, this);
	m_stcPos[_eSTRETCH_RIGHT_3_FWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_FORWARD_POS_STRETCH_RIGHT3, this);
	m_stcPos[_eSTRETCH_RIGHT_3_BWD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_CURRENT_BACKWARD_POS_STRETCH_RIGHT3, this);


	//
	m_editPos[_eSTRETCH_LEFT_1_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_WAIT_POS_STRETCH_LEFT, this);
	m_editPos[_eSTRETCH_LEFT_1_FWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_FORWARD_POS_STRETCH_LEFT, this);
	m_editPos[_eSTRETCH_LEFT_1_BWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_BACKWARD_POS_STRETCH_LEFT, this);

	m_editPos[_eSTRETCH_RIGHT_1_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_WAIT_POS_STRETCH_RIGHT, this);
	m_editPos[_eSTRETCH_RIGHT_1_FWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_FORWARD_POS_STRETCH_RIGHT, this);
	m_editPos[_eSTRETCH_RIGHT_1_BWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_BACKWARD_POS_STRETCH_RIGHT, this);

	//21.04.03 sjc
	m_editPos[_eSTRETCH_LEFT_2_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_WAIT_POS_STRETCH_LEFT2, this);
	m_editPos[_eSTRETCH_LEFT_2_FWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_FORWARD_POS_STRETCH_LEFT2, this);
	m_editPos[_eSTRETCH_LEFT_2_BWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_BACKWARD_POS_STRETCH_LEFT2, this);

	m_editPos[_eSTRETCH_RIGHT_2_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_WAIT_POS_STRETCH_RIGHT2, this);
	m_editPos[_eSTRETCH_RIGHT_2_FWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_FORWARD_POS_STRETCH_RIGHT2, this);
	m_editPos[_eSTRETCH_RIGHT_2_BWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_BACKWARD_POS_STRETCH_RIGHT2, this);
	
	m_editPos[_eSTRETCH_LEFT_3_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_WAIT_POS_STRETCH_LEFT3, this);
	m_editPos[_eSTRETCH_LEFT_3_FWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_FORWARD_POS_STRETCH_LEFT3, this);
	m_editPos[_eSTRETCH_LEFT_3_BWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_BACKWARD_POS_STRETCH_LEFT3, this);

	m_editPos[_eSTRETCH_RIGHT_3_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_WAIT_POS_STRETCH_RIGHT3, this);
	m_editPos[_eSTRETCH_RIGHT_3_FWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_FORWARD_POS_STRETCH_RIGHT3, this);
	m_editPos[_eSTRETCH_RIGHT_3_BWD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_STRETCH_BACKWARD_POS_STRETCH_RIGHT3, this);

}
//------------------------------------------------------------------
BOOL	CManual_Sub_Stretch_Fixed_Pos::Is_Comp_Usable()
{
	if (GetDlgItem(IDC_BUTTON_MANUAL_SUB_STRETCH_FIXED_SAVE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Stretch_Fixed_Pos::InitPara()
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_WaitPos);
	m_stcPos[_eSTRETCH_LEFT_1_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_ForwardPos);
	m_stcPos[_eSTRETCH_LEFT_1_FWD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_BackwardPos);
	m_stcPos[_eSTRETCH_LEFT_1_BWD_POS].SetWindowText(Str);
	//21.04.03 sjc
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_WaitPos);
	m_stcPos[_eSTRETCH_LEFT_2_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_ForwardPos);
	m_stcPos[_eSTRETCH_LEFT_2_FWD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_BackwardPos);
	m_stcPos[_eSTRETCH_LEFT_2_BWD_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_WaitPos);
	m_stcPos[_eSTRETCH_LEFT_3_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_ForwardPos);
	m_stcPos[_eSTRETCH_LEFT_3_FWD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_BackwardPos);
	m_stcPos[_eSTRETCH_LEFT_3_BWD_POS].SetWindowText(Str);
	//
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_WaitPos);
	m_stcPos[_eSTRETCH_RIGHT_1_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_ForwardPos);
	m_stcPos[_eSTRETCH_RIGHT_1_FWD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_BackwardPos);
	m_stcPos[_eSTRETCH_RIGHT_1_BWD_POS].SetWindowText(Str);
	//21.04.03 sjc
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_WaitPos);
	m_stcPos[_eSTRETCH_RIGHT_2_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_ForwardPos);
	m_stcPos[_eSTRETCH_RIGHT_2_FWD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_BackwardPos);
	m_stcPos[_eSTRETCH_RIGHT_2_BWD_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_WaitPos);
	m_stcPos[_eSTRETCH_RIGHT_3_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_ForwardPos);
	m_stcPos[_eSTRETCH_RIGHT_3_FWD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_BackwardPos);
	m_stcPos[_eSTRETCH_RIGHT_3_BWD_POS].SetWindowText(Str);
}
//------------------------------------------------------------------
void CManual_Sub_Stretch_Fixed_Pos::CheckChangeData()
{
	CString Str;

	m_stcPos[_eSTRETCH_LEFT_1_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_WaitPos = _ttof(Str);
	m_stcPos[_eSTRETCH_LEFT_1_FWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_ForwardPos = _ttof(Str);
	m_stcPos[_eSTRETCH_LEFT_1_BWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_BackwardPos = _ttof(Str);
	//21.04.03 sjc
	m_stcPos[_eSTRETCH_LEFT_2_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_WaitPos = _ttof(Str);
	m_stcPos[_eSTRETCH_LEFT_2_FWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_ForwardPos = _ttof(Str);
	m_stcPos[_eSTRETCH_LEFT_2_BWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_BackwardPos = _ttof(Str);

	m_stcPos[_eSTRETCH_LEFT_3_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_WaitPos = _ttof(Str);
	m_stcPos[_eSTRETCH_LEFT_3_FWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_ForwardPos = _ttof(Str);
	m_stcPos[_eSTRETCH_LEFT_3_BWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_BackwardPos = _ttof(Str);
	//
	m_stcPos[_eSTRETCH_RIGHT_1_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_WaitPos = _ttof(Str);
	m_stcPos[_eSTRETCH_RIGHT_1_FWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_ForwardPos = _ttof(Str);
	m_stcPos[_eSTRETCH_RIGHT_1_BWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_BackwardPos = _ttof(Str);
	//21.04.03 sjc
	m_stcPos[_eSTRETCH_RIGHT_2_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_WaitPos = _ttof(Str);
	m_stcPos[_eSTRETCH_RIGHT_2_FWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_ForwardPos = _ttof(Str);
	m_stcPos[_eSTRETCH_RIGHT_2_BWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_BackwardPos = _ttof(Str);

	m_stcPos[_eSTRETCH_RIGHT_3_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_WaitPos = _ttof(Str);
	m_stcPos[_eSTRETCH_RIGHT_3_FWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_ForwardPos = _ttof(Str);
	m_stcPos[_eSTRETCH_RIGHT_3_BWD_POS].GetWindowText(Str);
	CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_BackwardPos = _ttof(Str);
}

void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchFixedSave()
{
	CheckChangeData();
	CManualData::m_ManualDataStretch.Save();

	AfxMessageBox(_T("Save Ok"));
}

#pragma region //Get
void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L1));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_1_WAIT_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L1));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_1_FWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L1));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_1_BWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchRight()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R1));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_1_WAIT_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchRight()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R1));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_1_FWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R1));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_1_BWD_POS].SetWindowText(Str);
#endif
}
#pragma endregion

#pragma region //Set
void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_1_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_1_FWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left Pos Set Click (Fwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_1_BWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left Pos Set Click (Bwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchRight()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_1_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Right Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchRight()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_1_FWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Right Pos Set Click (Fwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_1_BWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Right Pos Set Click (Bwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}
#pragma endregion

#pragma region //Move
void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_Left((enum_eGRIPPER_ROW)eGRIPPER_ROW1) != TRUE)
	{
		AfxMessageBox(_T("Check Left 1 Clamp Off !!!"));
		return;
	}

	Str.Format(_T("Stretch Left 1 Move Wait Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_WaitPos_L((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_WaitPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW1);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	Str.Format(_T("Stretch Left 1 Move Fwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc del
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
		//if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		//{
			//Devs::m_StretchMotion.Stretch_FwdPos_L((enum_eGRIPPER_ROW)i);
		//}
	//}
	Devs::m_StretchMotion.Stretch_FwdPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW1);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	Str.Format(_T("Stretch Left 1 Move Bwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_BwdPos_L((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_BwdPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW1);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_Right((enum_eGRIPPER_ROW)eGRIPPER_ROW1) != TRUE)
	{
		AfxMessageBox(_T("Check 1 Right Clamp Off !!!"));
		return;
	}

	Str.Format(_T("Stretch Right 1 Move Wait Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_WaitPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_WaitPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW1);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	//21.04.03 sjc
	Str.Format(_T("Stretch Right 1 Move Fwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_FwdPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_FwdPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW1);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	//21.04.03 sjc
	Str.Format(_T("Stretch Right 1 Move Bwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_BwdPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_BwdPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW1);
}
#pragma endregion

//21.04.03 sjc GET
void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft2()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L2));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_2_WAIT_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft2()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L2));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_2_FWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft2()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L2));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_2_BWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft3()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L3));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_3_WAIT_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft3()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L3));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_3_FWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft3()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L3));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_LEFT_3_BWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchRight2()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R2));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_2_WAIT_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchRight2()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R2));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_2_FWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight2()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R2));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_2_BWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetWaitPosStretchRight3()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R3));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_3_WAIT_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetForwardPosStretchRight3()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R3));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_3_FWD_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight3()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R3));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eSTRETCH_RIGHT_3_BWD_POS].SetWindowText(Str);
#endif
}

//21.04.03 sjc SET
void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft2()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_2_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left 2 Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft2()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_2_FWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left 2 Pos Set Click (Fwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft2()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_2_BWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left 2 Pos Set Click (Bwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft3()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_3_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left 3 Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft3()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_3_FWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left 3 Pos Set Click (Fwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft3()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_LEFT_3_BWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Left 3 Pos Set Click (Bwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchRight2()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_2_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Right 2 Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchRight2()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_2_FWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Total_Msg(_T("[Manual-Stretch-Fixed] Stretch Right 2 Pos Set Click (Fwd Pos : %.5f)"), dPos);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight2()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_2_BWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Right 2 Pos Set Click (Bwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetWaitPosStretchRight3()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_3_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Right 3 Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetForwardPosStretchRight3()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_3_FWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Right 3 Pos Set Click (Fwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight3()
{
	CString Str = _T("");

	int nIndex = _eSTRETCH_RIGHT_3_BWD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	Str.Format(_T("[Manual-Stretch-Fixed] Stretch Right 3 Pos Set Click (Bwd Pos : %.5f)"), dPos);
	Total_Msg(Str);
}

//21.04.03 sjc MOVE
void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_Left((enum_eGRIPPER_ROW)eGRIPPER_ROW2) != TRUE)
	{
		AfxMessageBox(_T("Check Left 2 Clamp Off !!!"));
		return;
	}

	Str.Format(_T("Stretch Left 2 Move Wait Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_WaitPos_L((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_WaitPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW2);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	Str.Format(_T("Stretch Left 2 Move Fwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc del
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
		//if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		//{
			//Devs::m_StretchMotion.Stretch_FwdPos_L((enum_eGRIPPER_ROW)i);
		//}
	//}
	Devs::m_StretchMotion.Stretch_FwdPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW2);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	Str.Format(_T("Stretch Left 2 Move Bwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_BwdPos_L((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_BwdPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW2);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft3()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_Left((enum_eGRIPPER_ROW)eGRIPPER_ROW3) != TRUE)
	{
		AfxMessageBox(_T("Check Left 3 Clamp Off !!!"));
		return;
	}

	Str.Format(_T("Stretch Left 3 Move Wait Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_WaitPos_L((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_WaitPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW3);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft3()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	Str.Format(_T("Stretch Left 3 Move Fwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc del
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
		//if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		//{
			//Devs::m_StretchMotion.Stretch_FwdPos_L((enum_eGRIPPER_ROW)i);
		//}
	//}
	Devs::m_StretchMotion.Stretch_FwdPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW3);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft3()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	Str.Format(_T("Stretch Left 3 Move Bwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
	//21.04.03 sjc
	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_BwdPos_L((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_BwdPos_L((enum_eGRIPPER_ROW)eGRIPPER_ROW3);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_Right((enum_eGRIPPER_ROW)eGRIPPER_ROW2) != TRUE)
	{
		AfxMessageBox(_T("Check 2 Right Clamp Off !!!"));
		return;
	}

	Str.Format(_T("Stretch Right 2 Move Wait Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_WaitPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_WaitPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW2);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	//21.04.03 sjc
	Str.Format(_T("Stretch Right 2 Move Fwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_FwdPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_FwdPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW2);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	//21.04.03 sjc
	Str.Format(_T("Stretch Right 2 Move Bwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_BwdPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_BwdPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW2);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight3()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_Right((enum_eGRIPPER_ROW)eGRIPPER_ROW1) != TRUE)
	{
		AfxMessageBox(_T("Check 3 Right Clamp Off !!!"));
		return;
	}

	Str.Format(_T("Stretch Right 3 Move Wait Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_WaitPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_WaitPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW3);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight3()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	//21.04.03 sjc
	Str.Format(_T("Stretch Right 3 Move Fwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_FwdPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_FwdPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW3);
}


void CManual_Sub_Stretch_Fixed_Pos::OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight3()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	//21.04.03 sjc
	Str.Format(_T("Stretch Right 3 Move Bwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
	//	{
	//		Devs::m_StretchMotion.Stretch_BwdPos_R((enum_eGRIPPER_ROW)i);
	//	}
	//}
	Devs::m_StretchMotion.Stretch_BwdPos_R((enum_eGRIPPER_ROW)eGRIPPER_ROW3);
}
