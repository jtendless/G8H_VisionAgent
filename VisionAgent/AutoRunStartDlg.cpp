// AutoRunStartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "AutoRunStartDlg.h"
#include "afxdialogex.h"


// CAutoRunStartDlg dialog

IMPLEMENT_DYNAMIC(CAutoRunStartDlg, CDialogEx)

CAutoRunStartDlg::CAutoRunStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_AUTO_RUN, pParent)
{

}

CAutoRunStartDlg::~CAutoRunStartDlg()
{
}

void CAutoRunStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoRunStartDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &CAutoRunStartDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTO_RUN_START_FLOW, &CAutoRunStartDlg::OnCbnSelchangeComboAutoRunStartFlow)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTO_RUN_END_FLOW, &CAutoRunStartDlg::OnCbnSelchangeComboAutoRunEndFlow)
	ON_BN_CLICKED(IDCANCEL, &CAutoRunStartDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL CAutoRunStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

//Flow
#define STR_AUTO_FLOW_NAME_PAPER_UNLOAD					_T("Paper Unload")
#define STR_AUTO_FLOW_NAME_BOX_ALIGN					_T("Box Align")
//#define STR_AUTO_FLOW_NAME_STICK_LOAD_IN_BOX_TO_STAGE	_T("Stick Load In Box To Stage")
#define STR_AUTO_FLOW_NAME_STICK_PAPER_LOAD_UNLOAD		_T("Stick Paper Load Unload")
#define STR_AUTO_FLOW_NAME_PRE_ALIGN					_T("Pre Align")
#define STR_AUTO_FLOW_NAME_MAIN_ALIGN					_T("Main Align")
//#define STR_AUTO_FLOW_NAME_SW_ALIGN						_T("SW Align")
#define STR_AUTO_FLOW_NAME_TP							_T("TP") 
#define STR_AUTO_FLOW_NAME_PPA							_T("PPA")
#define STR_AUTO_FLOW_NAME_AOI							_T("AOI")
#define STR_AUTO_FLOW_NAME_AOI_REVIEW					_T("AOI Review")
#define STR_AUTO_FLOW_NAME_3D							_T("3D")
#define STR_AUTO_FLOW_NAME_STICK_UNLOAD_IN_STAGE_TO_CST	_T("Stick Unload In Stage To Cst")

//Tension Flow
#define STR_AUTO_FLOW_NAME_STICK_CLAMP_TENSION			_T("Stick Clamp Tension")
#define STR_AUTO_FLOW_NAME_PRE_TENSION_ALIGN			_T("Pre Tension Align")
#define STR_AUTO_FLOW_NAME_MAIN_TENSION_ALIGN			_T("Main Tension Align")
#define STR_AUTO_FLOW_NAME_EDGE_TENSION_ALIGN			_T("Edge Tension Align")
#define STR_AUTO_FLOW_NAME_STICK_RELEASE_UNCLAMP		_T("Stick Release Unclamp")

#define STR_AUTO_FLOW_NAME_STICK_CLAMP_TENSION_UNCLAMP	_T("Stick Tension Once") //KJT 20210406

BOOL CAutoRunStartDlg::InitCtrl()
{
	CString Str = _T("");
	int nNum = 1;

	m_comboStartFlow.SubclassDlgItem(IDC_COMBO_AUTO_RUN_START_FLOW, this);
	m_comboStep.SubclassDlgItem(IDC_COMBO_AUTO_RUN_STEP, this);
	m_comboEndFlow.SubclassDlgItem(IDC_COMBO_AUTO_RUN_END_FLOW, this);

	m_comboStartFlow.ResetContent();
	if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
	{
		nNum = 1;

		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_BOX_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_PAPER_LOAD_UNLOAD);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_CLAMP_TENSION);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_PRE_TENSION_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_MAIN_TENSION_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_EDGE_TENSION_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;

		//if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse) //KJT 20210315
		//{
		//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_SW_ALIGN);
		//	m_comboStartFlow.AddString(Str); nNum++;
		//}
		if (CModelData::m_InspectionPara.Info.bTPUse) //KJT 20210406
		{
			Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_TP);
			m_comboStartFlow.AddString(Str); nNum++;
		}		
		if (CModelData::m_InspectionPara.Info.bPPAUse) //KJT 20210315
		{
			Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_PPA);
			m_comboStartFlow.AddString(Str); nNum++;
		}
		//if (CModelData::m_InspectionPara.Info.bAOIUse) //KJT 20210315
		//{
		//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_AOI);
		//	m_comboStartFlow.AddString(Str); nNum++;
		//}
		//if (CModelData::m_InspectionPara.Info.bAOIReviewUse) //KJT 20210315
		//{
		//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_AOI_REVIEW);
		//	m_comboStartFlow.AddString(Str); nNum++;
		//}
		//if (CModelData::m_InspectionPara.Info.b3dFlowUse) //KJT 20210315
		//{
		//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_3D);
		//	m_comboStartFlow.AddString(Str); nNum++;
		//}
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_RELEASE_UNCLAMP);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_UNLOAD_IN_STAGE_TO_CST);
		m_comboStartFlow.AddString(Str); nNum++;
	}
	else if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ONCE)
	{
		nNum = 1;

		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_BOX_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_PAPER_LOAD_UNLOAD);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_PRE_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_MAIN_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;

		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_CLAMP_TENSION_UNCLAMP);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_MAIN_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;

		//if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse) //KJT 20210315
		//{
		//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_SW_ALIGN);
		//	m_comboStartFlow.AddString(Str); nNum++;
		//}
		if (CModelData::m_InspectionPara.Info.bTPUse) //KJT 20210406
		{
			Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_TP);
			m_comboStartFlow.AddString(Str); nNum++;
		}
		if (CModelData::m_InspectionPara.Info.bPPAUse) //KJT 20210315
		{
			Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_PPA);
			m_comboStartFlow.AddString(Str); nNum++;
		}
		//if (CModelData::m_InspectionPara.Info.bAOIUse) //KJT 20210315
		//{
		//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_AOI);
		//	m_comboStartFlow.AddString(Str); nNum++;
		//}
		//if (CModelData::m_InspectionPara.Info.bAOIReviewUse) //KJT 20210315
		//{
		//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_AOI_REVIEW);
		//	m_comboStartFlow.AddString(Str); nNum++;
		//}
		//if (CModelData::m_InspectionPara.Info.b3dFlowUse) //KJT 20210315
		//{
		//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_3D);
		//	m_comboStartFlow.AddString(Str); nNum++;
		//}
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_UNLOAD_IN_STAGE_TO_CST);
		m_comboStartFlow.AddString(Str); nNum++;
	}
	else //if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_NO)
	{
		nNum = 1;

		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_BOX_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_PAPER_LOAD_UNLOAD);
		m_comboStartFlow.AddString(Str); nNum++;
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_PRE_ALIGN);
		m_comboStartFlow.AddString(Str); nNum++;

		if (CModelData::m_InspectionPara.Info.bOnlyUnloadingMode == FALSE)
		{
			Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_MAIN_ALIGN);
			m_comboStartFlow.AddString(Str); nNum++;

			//if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse) //KJT 20210315
			//{
			//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_SW_ALIGN);
			//	m_comboStartFlow.AddString(Str); nNum++;
			//}
			if (CModelData::m_InspectionPara.Info.bTPUse) //KJT 20210406
			{
				Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_TP);
				m_comboStartFlow.AddString(Str); nNum++;
			}
			if (CModelData::m_InspectionPara.Info.bPPAUse) //KJT 20210315
			{
				Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_PPA);
				m_comboStartFlow.AddString(Str); nNum++;
			}
			//if (CModelData::m_InspectionPara.Info.bAOIUse) //KJT 20210315
			//{
			//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_AOI);
			//	m_comboStartFlow.AddString(Str); nNum++;
			//}
			//if (CModelData::m_InspectionPara.Info.bAOIReviewUse) //KJT 20210315
			//{
			//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_AOI_REVIEW);
			//	m_comboStartFlow.AddString(Str); nNum++;
			//}
			//if (CModelData::m_InspectionPara.Info.b3dFlowUse) //KJT 20210315
			//{
			//	Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_3D);
			//	m_comboStartFlow.AddString(Str); nNum++;
			//}
		}
		Str.Format(_T("%d. %s"), nNum, STR_AUTO_FLOW_NAME_STICK_UNLOAD_IN_STAGE_TO_CST);
		m_comboStartFlow.AddString(Str); nNum++;
	}

	m_comboStartFlow.SetCurSel(0);

	int nCount = m_comboStartFlow.GetCount();
	m_comboEndFlow.ResetContent();
	for (int i = 0; i < nCount; i++)
	{
		m_comboStartFlow.GetLBText(i, Str);
		m_comboEndFlow.AddString(Str);
	}
	m_comboEndFlow.SetCurSel(nCount - 1);

	return TRUE;
}
BOOL CAutoRunStartDlg::InitPara()
{
	CString Str = _T(""), Str1 = _T(""), Str2 = _T("");

	m_OKFlag = FALSE;

	if (SharedInfo::Active.ProcessStartFlow < 0)
		SharedInfo::Active.ProcessStartFlow = 0;

	Str1 = GetFlowName(SharedInfo::Active.ProcessStartFlow);
	for (int i = 0; i < m_comboStartFlow.GetCount(); i++)
	{
		m_comboStartFlow.GetLBText(i, Str2);
		if (_tcsstr(Str2, Str1) != NULL)
		{
			m_comboStartFlow.SetCurSel(i);
			break;
		}
	}

	m_comboStep.ResetContent();
	switch (SharedInfo::Active.ProcessStartFlow)
	{
		//TO DO

	//case eCOMBO_AUTO_RUN_FLOW_STICK_TENSION_ONCE: //KJT 20210406
	//	//for (int i = 0; i < Devs::m_StickReleaseUnclampFlow.m_nMaxGroupCount; i++)
	//	for (int i = 0; i < 1; i++)
	//	{
	//		m_comboStep.AddString(Devs::m_StickClampTensionUnclampFlow.m_sGroupInfo[i].strGroupName);
	//	}
		//break;
	}
	m_comboStep.SetCurSel(0);

	int nCount = m_comboStartFlow.GetCount();
	m_comboEndFlow.ResetContent();
	for (int i = 0; i < nCount; i++)
	{
		m_comboStartFlow.GetLBText(i, Str);
		m_comboEndFlow.AddString(Str);
	}
	m_comboEndFlow.SetCurSel(nCount - 1);

	return TRUE;
}

void CAutoRunStartDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

enum_AutoRunFlowName CAutoRunStartDlg::GetFlowNum(CString strFlowName)
{
	enum_AutoRunFlowName eFlow = eCOMBO_AUTO_RUN_FLOW_NONE; //Default
	CString Str = strFlowName;

	
	eFlow = eCOMBO_AUTO_RUN_FLOW_NONE;

	return eFlow;
}

CString CAutoRunStartDlg::GetFlowName(int nFlow)
{
	CString Str = _T("");

	switch (nFlow)
	{
	//case eCOMBO_AUTO_RUN_FLOW_PAPER_UNLOAD:
	//	Str.Format(_T("%s"), STR_AUTO_FLOW_NAME_PAPER_UNLOAD);
	//	break;
	

	default:
		Str.Format(_T("%s"), STR_AUTO_FLOW_NAME_PAPER_UNLOAD);
		break;
	}

	return Str;
}

void CAutoRunStartDlg::OnBnClickedOk()
{
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();

	if (IDOK != AfxMessageBox(_T("Auto Run Start ?"), MB_OKCANCEL))
		return;

	int nCurSel = m_comboStartFlow.GetCurSel();
	CString Str = _T("");
	m_comboStartFlow.GetLBText(nCurSel, Str);

	SharedInfo::Active.ProcessStartFlow = GetFlowNum(Str);	

	int nStep = m_comboStep.GetCurSel();

	switch (SharedInfo::Active.ProcessStartFlow)
	{

		//TO DO
	}

	nCurSel = m_comboEndFlow.GetCurSel();
	m_comboEndFlow.GetLBText(nCurSel, Str);
	SharedInfo::Active.ProcessEndFlow = GetFlowNum(Str);
	if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_NONE)
		SharedInfo::Active.ProcessEndFlow = eCOMBO_AUTO_RUN_FLOW_NONE;

	SharedInfo::ActiveInfoSave();

	//Devs::CimMotion.SetMachineAutoModeOnOff(TRUE);
	m_OKFlag = TRUE;

	CDialogEx::OnOK();
}


void CAutoRunStartDlg::OnCbnSelchangeComboAutoRunStartFlow()
{
	int nCurSel = m_comboStartFlow.GetCurSel();
	CString Str = _T("");
	m_comboStartFlow.GetLBText(nCurSel, Str);

	m_nStartFlow = GetFlowNum(Str);
	if (m_nStartFlow == eCOMBO_AUTO_RUN_FLOW_NONE)
	{		
		//m_nStartFlow = eCOMBO_AUTO_RUN_FLOW_BOX_ALIGN;
	}

	//m_nEndFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;

	SharedInfo::Active.ProcessStartFlow = m_nStartFlow;

	InitPara();
	SharedInfo::ActiveInfoSave();
}


void CAutoRunStartDlg::OnCbnSelchangeComboAutoRunEndFlow()
{
	if (m_comboEndFlow.GetCurSel() < m_comboStartFlow.GetCurSel())
	{
		m_nEndFlow = m_nStartFlow;
		m_comboEndFlow.SetCurSel(m_nEndFlow);
		return;
	}

	m_nEndFlow = m_comboEndFlow.GetCurSel();
	SharedInfo::ActiveInfoSave();
}

void CAutoRunStartDlg::OnBnClickedCancel()
{
	m_OKFlag = FALSE;
	
	CDialogEx::OnCancel();
}
