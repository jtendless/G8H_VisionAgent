// StretchParaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "StretchParaDlg.h"
#include "afxdialogex.h"


// CStretchParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CStretchParaDlg, CDialogEx)

CStretchParaDlg::CStretchParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_STRETCH_PARA_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_STRETCH_PARA_DIALOG, pParent);
}

CStretchParaDlg::~CStretchParaDlg()
{
}

void CStretchParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStretchParaDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_STRETCH_PARA_STEP_COUNT_SET, &CStretchParaDlg::OnBnClickedBtnStretchParaStepCountSet)
END_MESSAGE_MAP()


// CStretchParaDlg 메시지 처리기

BOOL CStretchParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();
	InitPara();	

	return TRUE;
}

void CStretchParaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CStretchParaDlg::InitCtrl()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int i, j;

#if 1
	m_chkUse[0].SubclassDlgItem(IDC_CHECK_STRETCH_PARA_USE1, this);
	m_chkUse[1].SubclassDlgItem(IDC_CHECK_STRETCH_PARA_USE2, this);
	m_chkUse[2].SubclassDlgItem(IDC_CHECK_STRETCH_PARA_USE3, this);
	//m_chkUse[3].SubclassDlgItem(IDC_CHECK_STRETCH_PARA_USE4, this);
	//m_chkUse[4].SubclassDlgItem(IDC_CHECK_STRETCH_PARA_USE5, this);
#ifdef GRIPPER_8
	m_chkUse[5].SubclassDlgItem(IDC_CHECK_STRETCH_PARA_USE6, this);
	m_chkUse[6].SubclassDlgItem(IDC_CHECK_STRETCH_PARA_USE7, this);
	m_chkUse[7].SubclassDlgItem(IDC_CHECK_STRETCH_PARA_USE8, this);
#endif

	m_editNewton[0][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW1, this);
	m_editNewton[0][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW2, this);
	m_editNewton[0][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW3, this);
	//m_editNewton[0][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW4, this);
	//m_editNewton[0][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[0][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW6, this);
	m_editNewton[0][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW7, this);
	m_editNewton[0][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW8, this);
#endif
	m_editNewton[1][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP2_ROW1, this);
	m_editNewton[1][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP2_ROW2, this);
	m_editNewton[1][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP2_ROW3, this);
	//m_editNewton[1][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP2_ROW4, this);
	//m_editNewton[1][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP2_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[1][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP2_ROW6, this);
	m_editNewton[1][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP2_ROW7, this);
	m_editNewton[1][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP2_ROW8, this);
#endif
	m_editNewton[2][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP3_ROW1, this);
	m_editNewton[2][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP3_ROW2, this);
	m_editNewton[2][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP3_ROW3, this);
	//m_editNewton[2][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP3_ROW4, this);
	//m_editNewton[2][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP3_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[2][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP3_ROW6, this);
	m_editNewton[2][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP3_ROW7, this);
	m_editNewton[2][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP3_ROW8, this);
#endif
	m_editNewton[3][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP4_ROW1, this);
	m_editNewton[3][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP4_ROW2, this);
	m_editNewton[3][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP4_ROW3, this);
	//m_editNewton[3][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP4_ROW4, this);
	//m_editNewton[3][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP4_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[3][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP4_ROW6, this);
	m_editNewton[3][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP4_ROW7, this);
	m_editNewton[3][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP4_ROW8, this);
#endif
	m_editNewton[4][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP5_ROW1, this);
	m_editNewton[4][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP5_ROW2, this);
	m_editNewton[4][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP5_ROW3, this);
	//m_editNewton[4][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP5_ROW4, this);
	//m_editNewton[4][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP5_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[4][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP5_ROW6, this);
	m_editNewton[4][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP5_ROW7, this);
	m_editNewton[4][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP5_ROW8, this);
#endif
	m_editNewton[5][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP6_ROW1, this);
	m_editNewton[5][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP6_ROW2, this);
	m_editNewton[5][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP6_ROW3, this);
	//m_editNewton[5][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP6_ROW4, this);
	//m_editNewton[5][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP6_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[5][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP6_ROW6, this);
	m_editNewton[5][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP6_ROW7, this);
	m_editNewton[5][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP6_ROW8, this);
#endif
	m_editNewton[6][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP7_ROW1, this);
	m_editNewton[6][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP7_ROW2, this);
	m_editNewton[6][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP7_ROW3, this);
	//m_editNewton[6][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP7_ROW4, this);
	//m_editNewton[6][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP7_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[6][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP7_ROW6, this);
	m_editNewton[6][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP7_ROW7, this);
	m_editNewton[6][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP7_ROW8, this);
#endif
	m_editNewton[7][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP8_ROW1, this);
	m_editNewton[7][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP8_ROW2, this);
	m_editNewton[7][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP8_ROW3, this);
	//m_editNewton[7][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP8_ROW4, this);
	//m_editNewton[7][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP8_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[7][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP8_ROW6, this);
	m_editNewton[7][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP8_ROW7, this);
	m_editNewton[7][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP8_ROW8, this);
#endif
	m_editNewton[8][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP9_ROW1, this);
	m_editNewton[8][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP9_ROW2, this);
	m_editNewton[8][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP9_ROW3, this);
	//m_editNewton[8][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP9_ROW4, this);
	//m_editNewton[8][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP9_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[8][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP9_ROW6, this);
	m_editNewton[8][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP9_ROW7, this);
	m_editNewton[8][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP9_ROW8, this);
#endif
	m_editNewton[9][0].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP10_ROW1, this);
	m_editNewton[9][1].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP10_ROW2, this);
	m_editNewton[9][2].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP10_ROW3, this);
	//m_editNewton[9][3].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP10_ROW4, this);
	//m_editNewton[9][4].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP10_ROW5, this);
#ifdef GRIPPER_8
	m_editNewton[9][5].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP10_ROW6, this);
	m_editNewton[9][6].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP10_ROW7, this);
	m_editNewton[9][7].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP10_ROW8, this);
#endif
#else
	//왜 안되지..
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < eGRIPPER_ROW_MAX; j++)
		{
			m_editNewton[i][j].SubclassDlgItem(IDC_EDIT_STRETCH_PARA_NEWTON_STEP1_ROW1 + (i * j), this);
			m_editNewton[i][j].SetWindowText(_T("1.0"));
		}
	}		
#endif

	m_editStepCount.SubclassDlgItem(IDC_EDIT_STRETCH_PARA_STEP_COUNT, this);
	m_btnStepCountSet.SubclassDlgItem(IDC_BTN_STRETCH_PARA_STEP_COUNT_SET, this);
	m_btnStepCountSet.SetColor(BLACK, LLTGRAY);
	m_editSpeedMax.SubclassDlgItem(IDC_EDIT_STRETCH_PARA_MAX_SPEED, this);
	m_editSpeedMin.SubclassDlgItem(IDC_EDIT_STRETCH_PARA_MIN_SPEED, this);
	m_editOkRange.SubclassDlgItem(IDC_EDIT_STRETCH_PARA_OK_RANGE, this);
	m_editDecelRange.SubclassDlgItem(IDC_EDIT_STRETCH_PARA_DECEL_RANGE, this);
	m_editReleaseForce.SubclassDlgItem(IDC_EDIT_STRETCH_PARA_RELEASE_FOCE, this);
	m_editMaxForce.SubclassDlgItem(IDC_EDIT_STRETCH_PARA_MAX_FORCE, this);

	return TRUE;
}

BOOL CStretchParaDlg::InitPara()
{
	int i, j;
	CString Str;

	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
			m_chkUse[i].SetCheck(1);
		else
			m_chkUse[i].SetCheck(0);
	}

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < eGRIPPER_ROW_MAX; j++)
		{
			Str.Format(_T("%.3f"), CModelData::m_StretchPara.Info.dStretchNewton[i][j]);
			m_editNewton[i][j].SetWindowText(Str);

			if (i < CModelData::m_StretchPara.Info.nStepCount)
				m_editNewton[i][j].EnableWindow(TRUE);
			else
				m_editNewton[i][j].EnableWindow(FALSE);
		}
	}

	m_editStepCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_StretchPara.Info.nStepCount));
	m_editSpeedMax.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_StretchPara.Info.dSpeedMax));
	m_editSpeedMin.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_StretchPara.Info.dSpeedMin));
	m_editOkRange.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_StretchPara.Info.dOkRange));
	m_editDecelRange.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_StretchPara.Info.dDecelRange));
	m_editReleaseForce.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_StretchPara.Info.dReleaseForce));
	m_editMaxForce.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_StretchPara.Info.dMaxForce));

	return TRUE;
}
BOOL CStretchParaDlg::CheckChangeData()
{
	CString Str = _T("");
	int i = 0, j = 0;

	m_editStepCount.GetWindowText(Str);
	CModelData::m_StretchPara.Info.nStepCount = _ttoi(Str);
	m_editSpeedMax.GetWindowText(Str);
	CModelData::m_StretchPara.Info.dSpeedMax = _ttof(Str);
	m_editSpeedMin.GetWindowText(Str);
	CModelData::m_StretchPara.Info.dSpeedMin = _ttof(Str);
	m_editOkRange.GetWindowText(Str);
	CModelData::m_StretchPara.Info.dOkRange = _ttof(Str);
	m_editDecelRange.GetWindowText(Str);
	CModelData::m_StretchPara.Info.dDecelRange = _ttof(Str);
	m_editReleaseForce.GetWindowText(Str);
	CModelData::m_StretchPara.Info.dReleaseForce = _ttof(Str);
	m_editMaxForce.GetWindowText(Str);
	CModelData::m_StretchPara.Info.dMaxForce = _ttof(Str);

	for (i = 0; i < CModelData::m_StretchPara.Info.nStepCount; i++)
	{
		for (j = 0; j < eGRIPPER_ROW_MAX; j++)
		{
			m_editNewton[i][j].GetWindowText(Str);
			CModelData::m_StretchPara.Info.dStretchNewton[i][j] = _ttof(Str);
		}
	}

	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		CModelData::m_StretchPara.Info.bStretchUse[i] = m_chkUse[i].GetCheck();
	}

	return TRUE;
}
BOOL CStretchParaDlg::SavePara()
{
	CString Str;
	int i = 0, j = 0;
	int nCount = 0;
	double dValue1 = 0.0, dValue2 = 0.0;

#pragma region StretchPara Interlock
	m_editStepCount.GetWindowText(Str);
	nCount = _tstoi((LPTSTR)(LPCTSTR)Str);
	if (nCount < 1 || nCount > 10)
	{
		Str.Format(_T("Step count가 잘못되었습니다. 1이상 %d이하여야 합니다."), 10);
		AfxMessageBox(Str);
		return FALSE;
	}

	m_editSpeedMax.GetWindowText(Str);
	dValue1 = _tstof(Str);
	if (dValue1 <= 0.0 || dValue1 > 0.1)
	{
		AfxMessageBox(_T("Max Speed가 잘못되었습니다. 0보다 크고 0.1 이하여야 합니다."));
		return FALSE;
	}

	m_editSpeedMin.GetWindowText(Str);
	dValue2 = _tstof(Str);
	if (dValue2 <= 0.0)
	{
		AfxMessageBox(_T("Min Speed가 잘못되었습니다. 0보다 커야 합니다."));
		return FALSE;
	}

	if (dValue1 < dValue2)
	{
		AfxMessageBox(_T("Max Speed가 Min Speed보다 작습니다."));
		return FALSE;
	}

	m_editOkRange.GetWindowText(Str);
	dValue1 = _tstof(Str);
	if (dValue1 <= 0.0)
	{
		AfxMessageBox(_T("Ok Range가 잘못되었습니다. 0보다 커야 합니다."));
		return FALSE;
	}

	m_editDecelRange.GetWindowText(Str);
	dValue2 = _tstof(Str);
	if (dValue2 <= 0.0)
	{
		AfxMessageBox(_T("Decel Range가 잘못되었습니다. 0보다 커야 합니다."));
		return FALSE;
	}

	if (dValue1 > dValue2)
	{
		AfxMessageBox(_T("Ok Range가 Decel Range보다 큽니다."));
		return FALSE;
	}

	m_editReleaseForce.GetWindowText(Str);
	dValue1 = _tstof(Str);
	if (dValue1 < 0.1)
	{
		AfxMessageBox(_T("Release Force가 잘못되었습니다. 0.1 이상이어야 합니다."));
		return FALSE;
	}

	m_editMaxForce.GetWindowText(Str);
	dValue1 = _tstof(Str);
	if (dValue1 >= 10.0)
	{
		AfxMessageBox(_T("Max Force가 잘못되었습니다. 10Newton 미만이어야 합니다."));
		return FALSE;
	}

	//Step Value
	m_editStepCount.GetWindowText(Str);
	nCount = _tstoi(Str);
	for (i = 0; i < nCount; i++)
	{
		if (m_chkUse[i].GetCheck())
		{
			for (j = 0; j < eGRIPPER_ROW_MAX; j++)
			{
				m_editNewton[i][j].GetWindowText(Str);
				dValue1 = _tstof(Str);
				if (dValue1 < 0.5)
				{
					AfxMessageBox(_T("Force Data가 잘못되었습니다. 0.5이상이어야 합니다."));
					return FALSE;
				}
			}
		}
	}
#pragma endregion

	CheckChangeData();

	BOOL bRtn = CModelData::m_StretchPara.Save();
	if (bRtn == TRUE)
	{
		double dStretchValue[MAX_STEP][eGRIPPER_ROW_MAX];
		memset(dStretchValue, 0x0, sizeof(dStretchValue));
		memcpy(dStretchValue, CModelData::m_StretchPara.Info.dStretchNewton, sizeof(CModelData::m_StretchPara.Info.dStretchNewton)); //??

		Devs::m_StretchMotion.StretchSetStepValue(CModelData::m_StretchPara.Info.nStepCount, dStretchValue);
		(20);
		Devs::m_StretchMotion.SendStretchSetPara();
		(20);

		AfxMessageBox(_T("Save Ok"));
	}
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}

void CStretchParaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CStretchParaDlg::BtnEnable(BOOL bEnable)
{
	int i = 0;

	if (bEnable)
	{
	}
	else
	{
	}
}


void CStretchParaDlg::OnBnClickedBtnStretchParaStepCountSet()
{
	int nValue, nCount;
	double dData[eGRIPPER_ROW_MAX + 1] = { 1.0 };
	CString Str;

	m_editStepCount.GetWindowText(Str);

	nValue = _tstoi((LPTSTR)(LPCTSTR)Str);

	if (nValue < 1 || nValue > 10)
	{
		AfxMessageBox(_T("Step count wrong"));
		return;
	}

	m_nStepCount = nValue;

	int i, j = 0;
	for (i = 0; i < 10; i++)
	{
		if (i < m_nStepCount)
		{
			for (j = 0; j < eGRIPPER_ROW_MAX; j++)
			{
				m_editNewton[i][j].EnableWindow(TRUE);
			}
		}
		else
		{
			for (j = 0; j < eGRIPPER_ROW_MAX; j++)
			{
				m_editNewton[i][j].EnableWindow(FALSE);
			}
		}
	}
}
