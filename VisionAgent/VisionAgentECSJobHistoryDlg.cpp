// VisionAgentECSJobHistoryDlg.cpp : ±¸Çö ÆÄÀÏÀÔ´Ï´Ù.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentECSJobHistoryDlg.h"
#include "VisionAgentDlg.h"
#include "afxdialogex.h"

// CVisionAgentECSJobHistoryDlg ´ëÈ­ »óÀÚÀÔ´Ï´Ù.

IMPLEMENT_DYNAMIC(CVisionAgentECSJobHistoryDlg, CDialogEx)

CVisionAgentECSJobHistoryDlg::CVisionAgentECSJobHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_ECS_JOB_HISTORY_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_ECS_JOB_HISTORY_DIALOG, pParent);
}

CVisionAgentECSJobHistoryDlg::~CVisionAgentECSJobHistoryDlg()
{
}

void CVisionAgentECSJobHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CVisionAgentECSJobHistoryDlg::InitListControlPara()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str;

	CRect Rect;
	GetDlgItem(IDC_LIST_RECIPE_DATA)->GetClientRect(&Rect);
	int nPreSize = Rect.Width() - 250;

	CImageList m_ImageList;
	CString strTeg[JOB_HISTORY_LISTCTRL_MAX_COL] = { _T("No"),_T("Time"), _T("Job ID") };
	CString strComboData[3] = { _T("Warning"), _T("Alarm"), _T("NA") };

	INT nColSize[JOB_HISTORY_LISTCTRL_MAX_COL];
	COLORREF m_BkColor[JOB_HISTORY_LISTCTRL_MAX_COL];
	COLORREF m_TextColor[JOB_HISTORY_LISTCTRL_MAX_COL];
	INT nInpuMethod[JOB_HISTORY_LISTCTRL_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE };

	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	m_pListCtrl = new CCommonListCtrl;
	m_pListCtrl->SubclassDlgItem(IDC_LIST_RECIPE_DATA, this);

	/// Setting
	m_pListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	for (int i = 0; i < JOB_HISTORY_LISTCTRL_MAX_COL; i++)
	{
		if (i == 0)
		{
			nColSize[i] = 50;
			m_BkColor[i] = RGB(215, 215, 215);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else if (i == 1)
		{
			nColSize[i] = 150;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else if (i == 6)
		{
			nColSize[i] = nPreSize;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}

		else
		{
			nColSize[i] = 80;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
	}

	m_pListCtrl->SetListColumn(strTeg, nColSize, JOB_HISTORY_LISTCTRL_MAX_COL, m_BkColor, m_TextColor, nInpuMethod);
	m_pListCtrl->SetColData(1, 3, strComboData);
	m_pListCtrl->m_nListCnt = 0;
}

void CVisionAgentECSJobHistoryDlg::ChangeUI()
{
	int nRowCount = 0;
	CString szMsg[JOB_HISTORY_LISTCTRL_MAX_COL] = { _T(""), };

	m_pListCtrl->DeleteAllItems();

	nRowCount = m_pListCtrl->GetMaxListCount();

	for (int nRowCount = 0; nRowCount < JOB_HISTORY_LISTCTRL_MAX_ROW; nRowCount++)
	{
		szMsg[0].Format(_T("%d"), nRowCount + 1);
		m_pListCtrl->AddListData(nRowCount, szMsg);
	}
}

//void CVisionAgentECSJobHistoryDlg::InitSpread()
//{
//	CRect rect;
//	CString szMsg, szMsgTmp;
//	USES_CONVERSION;
//
//
//	
//	int RowCnt = 1;;
//
//	m_procsTexts.Add(_T("No"));
//	m_procsTexts.Add(_T("Type"));
//	m_procsTexts.Add(_T("Code"));
//	m_procsTexts.Add(_T("Message"));
//
//	m_spread = (TSpread*)GetDlgItem(IDD_ECS_ERROR_CST);
//	m_spread->SetBool(SSB_HORZSCROLLBAR, FALSE);
//	m_spread->SetMaxRows(100);
//	m_spread->SetMaxCols(3);
//	for (int i = 0; i < 4; i++)
//	{
//
//		m_spread->SetData(i, 0, (LPCTSTR)T2A(m_procsTexts.GetAt(i)));
//	}
//	m_spread->GetClientRect(&rect);
//	m_spread->SetColHeaderDisplay(SS_HEADERDISPLAY_LETTERS);
//	
//	m_spread->SetColWidthInPixels(1, 50);
//
//	m_spread->SetColWidthInPixels(2, 50);
//
//	m_spread->SetColWidthInPixels(3, rect.Width() - 100);
//
//}

BEGIN_MESSAGE_MAP(CVisionAgentECSJobHistoryDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ECS_ERROR_ALL_CLEAR_BTN, &CVisionAgentECSJobHistoryDlg::OnBnClickedEcsErrorAllClearBtn)
	ON_BN_CLICKED(IDC_ECS_ERROR_CLEAR_BTN, &CVisionAgentECSJobHistoryDlg::OnBnClickedEcsErrorClearBtn)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_RECIPE_DATA, &CVisionAgentECSJobHistoryDlg::OnNMClickListRecipeData)
END_MESSAGE_MAP()


// CVisionAgentECSJobHistoryDlg ¸Þ½ÃÁö Ã³¸®±âÀÔ´Ï´Ù.


BOOL CVisionAgentECSJobHistoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ¿©±â¿¡ Ãß°¡ ÃÊ±âÈ­ ÀÛ¾÷À» Ãß°¡ÇÕ´Ï´Ù.
	//InitSpread();
	InitListControlPara();
	ChangeUI();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ¿¹¿Ü: OCX ¼Ó¼º ÆäÀÌÁö´Â FALSE¸¦ ¹ÝÈ¯ÇØ¾ß ÇÕ´Ï´Ù.
}


void CVisionAgentECSJobHistoryDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: ¿©±â¿¡ ¸Þ½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	if (bShow == TRUE)
		SetTimer(1, 100, NULL);
	else
		KillTimer(1);
}


void CVisionAgentECSJobHistoryDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ¿©±â¿¡ ¸Þ½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº»°ªÀ» È£ÃâÇÕ´Ï´Ù.
	CString szMsg[JOB_HISTORY_LISTCTRL_MAX_COL] = { 0, };
	char ConvertValue[20];
	if (nIDEvent == 1)
	{
		//m_spread->SetData(1,  1, (LPCTSTR)T2A(szMsg));
		for (int i = 0; i < JOB_HISTORY_LISTCTRL_MAX_ROW; i++)
		{
			memset(ConvertValue, 0x0, sizeof(ConvertValue));
			if (!memcmp(SharedInfo::StoredJob[i].MaskJobDataBlock.Mask_JobID , ConvertValue, sizeof(ConvertValue)))
			{
				//memset(&CimInfo::AlarmBlock[i], 0x0, sizeof(LW_LTM_ALARM_BLOCK));
				szMsg[0].Format(_T(""));
				szMsg[1].Format(_T(""));
				szMsg[2].Format(_T(""));
	
			}
			else
			{
				szMsg[0].Format(_T("%2d/%2d/%2d %2d:%2d:%2d"), CimInfo::AlarmOccuredTime[i].GetYear(), CimInfo::AlarmOccuredTime[i].GetMonth(), CimInfo::AlarmOccuredTime[i].GetDay(), CimInfo::AlarmOccuredTime[i].GetHour(), CimInfo::AlarmOccuredTime[i].GetMinute(), CimInfo::AlarmOccuredTime[i].GetSecond());
				memcpy(ConvertValue, SharedInfo::StoredJob[i].MaskJobDataBlock.Mask_JobID, sizeof(SharedInfo::StoredJob[i].MaskJobDataBlock.Mask_JobID));
				szMsg[1].Format(_T("%S"), ConvertValue);
			}
			m_pListCtrl->SetItemTextEx(i, 1, szMsg[0]);
			m_pListCtrl->SetItemTextEx(i, 2, szMsg[1]);
		}
	}
	CDialogEx::OnTimer(nIDEvent);

}



void CVisionAgentECSJobHistoryDlg::OnBnClickedEcsErrorAllClearBtn()
{

	if (IDOK != AfxMessageBox(_T("Remove?"), MB_OKCANCEL)) return;
	CString szMsg;
	MASK_JOB_MANUAL_MOVE_REPORT_BLOCK MaskManualReportBlock;

	for (int i = 0; i < 20; i++)
	{
		if (!memcmp(CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, SharedInfo::StoredJob[i].MaskJobDataBlock.Mask_JobID, sizeof(CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID)))
		{
			for (int j = i; j < 20; j++)
			{
				memcpy(&SharedInfo::StoredJob[j], &SharedInfo::StoredJob[j + 1], sizeof(SharedInfo::StoredJob[j]));
			}
			memset(&SharedInfo::StoredJob[19], 0x0, sizeof(SharedInfo::StoredJob[19]));
			break;
		}
	}

	MaskManualReportBlock.JobPosition = 0;
	MaskManualReportBlock.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	memcpy(MaskManualReportBlock.MaskJobID, CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(CimInfo::MaskJobData.MaskJobDataBlock));
	memcpy((BYTE*)MaskManualReportBlock.OperatorID, ConvertPlcString(szMsg), 10);
	MaskManualReportBlock.OperatorID;
	MaskManualReportBlock.ReportOption = 2;
	MaskManualReportBlock.SlotNumber = 1;
	MaskManualReportBlock.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	MaskManualReportBlock.UnitNumber_or_PortNumber = 1;
	MaskManualReportBlock.Uni_or_Port = 1;
	memset(&CimInfo::MaskJobData, 0x0, sizeof(CimInfo::MaskJobData));
	Devs::CimMotion.ReportJobManualMove(MaskManualReportBlock);

	Etc_Msg(_T("[Cim] Send : Job Manual Move Report"));
}


void CVisionAgentECSJobHistoryDlg::OnBnClickedEcsErrorClearBtn()
{
	if (IDOK != AfxMessageBox(_T("Recovery?"), MB_OKCANCEL)) return;
	CString szMsg;
	MASK_JOB_MANUAL_MOVE_REPORT_BLOCK MaskManualReportBlock;
	INT nPos = m_pListCtrl->GetSelectedItemNumber();
	if (nPos < 0 || nPos > 100)
	{
		AfxMessageBox(_T("Select Job ID"));
		return;
	}

	GetDlgItem(IDC_ECS_JOB_HISTORY_OPERATOR_ID_EDIT)->GetWindowText(szMsg);

	if (CimInfo::AlarmBlock[nPos].AlarmStatus == 0)
	{
		AfxMessageBox(_T("Selected Job is None"));
		return;
	}
	memcpy(&CimInfo::MaskJobData, &SharedInfo::StoredJob[nPos], sizeof(CimInfo::MaskJobData));

	MaskManualReportBlock.JobPosition = 0;
	MaskManualReportBlock.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	memcpy(MaskManualReportBlock.MaskJobID, CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(CimInfo::MaskJobData.MaskJobDataBlock));
	memcpy((BYTE*)MaskManualReportBlock.OperatorID, ConvertPlcString(szMsg), 10);
	MaskManualReportBlock.OperatorID;
	MaskManualReportBlock.ReportOption = 3;
	MaskManualReportBlock.SlotNumber = 1;
	MaskManualReportBlock.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	MaskManualReportBlock.UnitNumber_or_PortNumber=1;
	MaskManualReportBlock.Uni_or_Port= 1;
	Devs::CimMotion.ReportJobManualMove(MaskManualReportBlock);

	Etc_Msg(_T("[Cim] Send : Job Manual Move Report"));
}



void CVisionAgentECSJobHistoryDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pListCtrl != NULL)
		delete m_pListCtrl;
}


void CVisionAgentECSJobHistoryDlg::OnNMClickListRecipeData(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pListCtrl->m_nSelectedItemNumber = pNMItemActivate->iItem;
	*pResult = 0;
}


char* CVisionAgentECSJobHistoryDlg::ConvertPlcString(CString strData)
{
	char cTemp[100];
	memset(cTemp, 0x00, sizeof(cTemp));
	sprintf(cTemp, "%s", (char*)CT2CA(strData));
	return cTemp;
}