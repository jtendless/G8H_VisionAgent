// VisionAgentECSErrorDlg.cpp : ±¸Çö ÆÄÀÏÀÔ´Ï´Ù.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentECSErrorDlg.h"
#include "VisionAgentDlg.h"
#include "afxdialogex.h"


// CVisionAgentECSErrorDlg ´ëÈ­ »óÀÚÀÔ´Ï´Ù.

IMPLEMENT_DYNAMIC(CVisionAgentECSErrorDlg, CDialogEx)

CVisionAgentECSErrorDlg::CVisionAgentECSErrorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_ECS_ERROR_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_ECS_ERROR_DIALOG, pParent);
}

CVisionAgentECSErrorDlg::~CVisionAgentECSErrorDlg()
{
}

void CVisionAgentECSErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CVisionAgentECSErrorDlg::InitListControlPara()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str;

	CRect Rect;
	GetDlgItem(IDC_LIST_ECS_RECIPE_DATA)->GetClientRect(&Rect);
	int nPreSize = Rect.Width() - 250;

	CImageList m_ImageList;
	CString strTeg[ALARM_LISTCTRL_MAX_COL] = { _T("No"),_T("Time"), _T("Code"),_T("Type"), _T("Status"), _T("Unit") ,_T("Message") ,_T("Clearable") };
	CString strComboData[3] = { _T("Warning"), _T("Alarm"), _T("NA") };

	INT nColSize[ALARM_LISTCTRL_MAX_COL];
	COLORREF m_BkColor[ALARM_LISTCTRL_MAX_COL];
	COLORREF m_TextColor[ALARM_LISTCTRL_MAX_COL];
	INT nInpuMethod[ALARM_LISTCTRL_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE };

	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	m_pListCtrl = new CCommonListCtrl;
	m_pListCtrl->SubclassDlgItem(IDC_LIST_ECS_RECIPE_DATA, this);

	/// Setting
	m_pListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	for (int i = 0; i < ALARM_LISTCTRL_MAX_COL; i++)
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

	m_pListCtrl->SetListColumn(strTeg, nColSize, ALARM_LISTCTRL_MAX_COL, m_BkColor, m_TextColor, nInpuMethod);
	m_pListCtrl->SetColData(1, 3, strComboData);
	m_pListCtrl->m_nListCnt = 0;
}

void CVisionAgentECSErrorDlg::ChangeUI()
{
	int nRowCount = 0;
	CString szMsg[ALARM_LISTCTRL_MAX_COL] = { _T(""), };

	m_pListCtrl->DeleteAllItems();

	nRowCount = m_pListCtrl->GetMaxListCount();

	for (int nRowCount = 0; nRowCount < ALARM_LISTCTRL_MAX_ROW; nRowCount++)
	{
		szMsg[0].Format(_T("%d"), nRowCount + 1);
		m_pListCtrl->AddListData(nRowCount, szMsg);
	}
}

//void CVisionAgentECSErrorDlg::InitSpread()
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

BEGIN_MESSAGE_MAP(CVisionAgentECSErrorDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ECS_ERROR_ALL_CLEAR_BTN, &CVisionAgentECSErrorDlg::OnBnClickedEcsErrorAllClearBtn)
	ON_BN_CLICKED(IDC_ECS_ERROR_CLEAR_BTN, &CVisionAgentECSErrorDlg::OnBnClickedEcsErrorClearBtn)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_ECS_RECIPE_DATA, &CVisionAgentECSErrorDlg::OnNMClickListRecipeData)
END_MESSAGE_MAP()


// CVisionAgentECSErrorDlg ¸Þ½ÃÁö Ã³¸®±âÀÔ´Ï´Ù.


BOOL CVisionAgentECSErrorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ¿©±â¿¡ Ãß°¡ ÃÊ±âÈ­ ÀÛ¾÷À» Ãß°¡ÇÕ´Ï´Ù.
	//InitSpread();
	InitListControlPara();
	ChangeUI();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ¿¹¿Ü: OCX ¼Ó¼º ÆäÀÌÁö´Â FALSE¸¦ ¹ÝÈ¯ÇØ¾ß ÇÕ´Ï´Ù.
}


void CVisionAgentECSErrorDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: ¿©±â¿¡ ¸Þ½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	if (bShow == TRUE)
		SetTimer(1, 100, NULL);
	else
		KillTimer(1);
}


void CVisionAgentECSErrorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ¿©±â¿¡ ¸Þ½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº»°ªÀ» È£ÃâÇÕ´Ï´Ù.
	CString szMsg[ALARM_LISTCTRL_MAX_COL] = { 0, };
	
	if (nIDEvent == 1)
	{
		//m_spread->SetData(1,  1, (LPCTSTR)T2A(szMsg));
		for (int i = 0; i < ALARM_LISTCTRL_MAX_ROW; i++)
		{
			if (CimInfo::AlarmBlock[i].AlarmStatus == 0)
			{
				memset(&CimInfo::AlarmBlock[i], 0x0, sizeof(LW_LTM_ALARM_BLOCK));
				szMsg[0].Format(_T(""));
				szMsg[1].Format(_T(""));
				szMsg[2].Format(_T(""));
				szMsg[3].Format(_T(""));
				szMsg[4].Format(_T(""));
				szMsg[5].Format(_T(""));
				szMsg[6].Format(_T(""));
			}
			else
			{
				szMsg[0].Format(_T("%2d/%2d/%2d %2d:%2d:%2d"), CimInfo::AlarmOccuredTime[i].GetYear(), CimInfo::AlarmOccuredTime[i].GetMonth(), CimInfo::AlarmOccuredTime[i].GetDay(), CimInfo::AlarmOccuredTime[i].GetHour(), CimInfo::AlarmOccuredTime[i].GetMinute(), CimInfo::AlarmOccuredTime[i].GetSecond());
				szMsg[1].Format(_T("%d"), CimInfo::AlarmBlock[i].AlarmCode);
				if (CimInfo::AlarmBlock[i].AlarmType == 0)
					szMsg[2].Format(_T("Warning"));
				else if (CimInfo::AlarmBlock[i].AlarmType == 1)
					szMsg[2].Format(_T("Alarm"));
				else
					szMsg[2].Format(_T("NA"));
				
				szMsg[3].Format(_T("%d"), CimInfo::AlarmBlock[i].AlarmStatus);
				szMsg[4].Format(_T("%d"), CimInfo::AlarmBlock[i].AlarmUnitNumber);
				szMsg[5].Format(_T("%S"), (char*)CimInfo::AlarmBlock[i].AlarmText);
	
	
	
	
	
	
			}
			m_pListCtrl->SetItemTextEx(i, 1, szMsg[0]);
			m_pListCtrl->SetItemTextEx(i, 2, szMsg[1]);
			m_pListCtrl->SetItemTextEx(i, 3, szMsg[2]);
			m_pListCtrl->SetItemTextEx(i, 4, szMsg[3]);
			m_pListCtrl->SetItemTextEx(i, 5, szMsg[4]);
			m_pListCtrl->SetItemTextEx(i, 6, szMsg[5]);
	


		}
	}
	CDialogEx::OnTimer(nIDEvent);
	
}



void CVisionAgentECSErrorDlg::OnBnClickedEcsErrorAllClearBtn()
{
	if (IDOK != AfxMessageBox(_T("ECS Error All Clear?"), MB_OKCANCEL)) return;
	
	for (int i = 0; i < ALARM_LISTCTRL_MAX_ROW; i++)
	{
		if(CimInfo::AlarmBlock[i].AlarmStatus != 0)
			Devs::CimMotion.CIMAlarmAllResetMessage();
	}
	
	Etc_Msg(_T("[Cim] Send : Alarm State Change Report"));
}


void CVisionAgentECSErrorDlg::OnBnClickedEcsErrorClearBtn()
{
	if (IDOK != AfxMessageBox(_T("ECS Error Clear?"), MB_OKCANCEL)) return;

	INT nPos = m_pListCtrl->GetSelectedItemNumber();
	if (nPos < 0 || nPos > 100 )
	{
		AfxMessageBox(_T("Select Alarm ID"));
		return;
	}

	if (CimInfo::AlarmBlock[nPos].AlarmStatus == 0)
	{
		AfxMessageBox(_T("Selected Alarm is None"));
		return;
	}

	Devs::CimMotion.CIMAlarmResetMessage(nPos);
	
	Etc_Msg(_T("[Cim] Send : Alarm State Change Report"));
}



void CVisionAgentECSErrorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pListCtrl != NULL)
		delete m_pListCtrl;
}


void CVisionAgentECSErrorDlg::OnNMClickListRecipeData(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pListCtrl->m_nSelectedItemNumber = pNMItemActivate->iItem;
	*pResult = 0;
}
