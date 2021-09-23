// VisionAgentModelDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentAlarmDlg.h"
#include "afxdialogex.h"

// CVisionAgentAlarmDlg 대화 상자

IMPLEMENT_DYNAMIC(CVisionAgentAlarmDlg, CDialogEx)

CVisionAgentAlarmDlg::CVisionAgentAlarmDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISION_AGENT_ALARM_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_ALARM_DIALOG, pParent);
}

CVisionAgentAlarmDlg::~CVisionAgentAlarmDlg()
{
	alarmfont.DeleteObject();
}

void CVisionAgentAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentAlarmDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ALARM_CLOSE, &CVisionAgentAlarmDlg::OnBnClickedBtnAlarmClose)
	ON_BN_CLICKED(IDC_BTN_ALARM_RESET, &CVisionAgentAlarmDlg::OnBnClickedBtnAlarmReset)
END_MESSAGE_MAP()


// CVisionAgentAlarmDlg 메시지 처리기
BOOL CVisionAgentAlarmDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	//lf.lfHeight = 30;
	lf.lfHeight = 25;
	//_tcscpy_s(lf.lfFaceName, COUNTOF(lf.lfFaceName), "Arial");
	wcscpy(lf.lfFaceName, _T("Arial"));
	alarmfont.CreateFontIndirect(&lf);

	SharedInfo::LoadAlarmList();

	InitListControlPara();
	UpdateUI();

	return TRUE;
}


void CVisionAgentAlarmDlg::InitListControlPara()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str;

	CRect Rect;
	GetDlgItem(IDC_LIST_ALARM_DATA)->GetClientRect(&Rect);
	int nPreSize = 530;

	CImageList m_ImageList;
	CString strTeg[ALARM_LISTCTRL_MAX_COL] = { _T("No"), _T("Date"), _T("Time"), _T("Code"), _T("Level"), _T("Description") };
	CString strComboData[3] = { _T("Warning"), _T("Alarm"), _T("NA") };

	INT nColSize[ALARM_LISTCTRL_MAX_COL];
	COLORREF m_BkColor[ALARM_LISTCTRL_MAX_COL];
	COLORREF m_TextColor[ALARM_LISTCTRL_MAX_COL];
	INT nInpuMethod[ALARM_LISTCTRL_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE };

	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	m_pListCtrl = new CCommonListCtrl;
	m_pListCtrl->SubclassDlgItem(IDC_LIST_ALARM_DATA, this);

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
		else if (i == 5)
		{
			nColSize[i] = nPreSize;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else
		{
			nColSize[i] = 100;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
	}

	m_pListCtrl->SetListColumn(strTeg, nColSize, ALARM_LISTCTRL_MAX_COL, m_BkColor, m_TextColor, nInpuMethod);
	m_pListCtrl->SetColData(1, 3, strComboData);
	m_pListCtrl->m_nListCnt = 0;
}

void CVisionAgentAlarmDlg::UpdateUI()
{
	int nRowCount = 0;
	CString szMsg[ALARM_LISTCTRL_MAX_COL] = { _T(""), };

	m_pListCtrl->DeleteAllItems();

	//nRowCount = m_pListCtrl->GetMaxListCount();

	for (int i = ALARM_LISTCTRL_MAX_ROW - 1; i >= 0; i--)
	{
		if (i >= SharedInfo::AlarmCount)
			continue;

		szMsg[0].Format(_T("%d"), nRowCount + 1);
		szMsg[1].Format(_T("%s"), SharedInfo::AlarmList[i].AlarmDate);
		szMsg[2].Format(_T("%s"), SharedInfo::AlarmList[i].AlarmTime);
		szMsg[3].Format(_T("%d"), SharedInfo::AlarmList[i].AlarmCode);
		if(SharedInfo::AlarmList[i].AlarmLevel == 1)
			szMsg[4].Format(_T("%s"), _T("H"));
		else 
			szMsg[4].Format(_T("%s"), _T("L"));
		szMsg[5].Format(_T("%s"), SharedInfo::AlarmList[i].AlarmText);

		m_pListCtrl->AddListData(nRowCount, szMsg);
		nRowCount++;
	}

	Invalidate();
}


BOOL CVisionAgentAlarmDlg::SetAlarm(LPCTSTR Msg, UINT nErrCode/*=0*/)
{
	CVisionAgentDlg *pDlg;
	pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString strDate,  strTime, strTemp;
	LPCTSTR msg;
	UINT uLevel;

	SYSTEMTIME st;
	GetLocalTime(&st);
	GetAlarmLevelDescription(nErrCode, &uLevel, &msg);

	//if (pDlg->m_nVisionAgentAutoRun == TRUE)
	//{
	//	CStateManager *pStateManager = CStateManager::GetInstance();
	//	pDlg->m_nVisionAgentAutoRun = FALSE;

	//	nAutoRunStatus = 1;

	//	Sleep(10);

	//	pStateManager->StopSeq();
	//}

	if (Msg != _T(""))
		msg = Msg;

	if (m_nErrCode == nErrCode) return FALSE;

	m_nErrCode = nErrCode;
	m_msg = msg;

	strTemp.Format(_T("%s,%d,%d"), msg, nErrCode, uLevel);
	Alarm_Msg(strTemp);
	

	strDate.Format(_T("%04d-%02d-%02d"), st.wYear, st.wMonth, st.wDay);
	strTime.Format(_T("[%02d:%02d:%02d]"), st.wHour, st.wMinute, st.wSecond);
	SharedInfo::AlarmList[SharedInfo::AlarmCount].AlarmDate = strDate;
	SharedInfo::AlarmList[SharedInfo::AlarmCount].AlarmTime = strTime;
	SharedInfo::AlarmList[SharedInfo::AlarmCount].AlarmCode = nErrCode;
	SharedInfo::AlarmList[SharedInfo::AlarmCount].AlarmLevel = uLevel;
	SharedInfo::AlarmList[SharedInfo::AlarmCount].AlarmText = m_msg;

	SharedInfo::AlarmCount++;

	SharedInfo::SaveAlarmList();

	Sleep(10);
	
	Devs::m_JogMotion.StopAll();
	Devs::MotionIf.DOutputSetBitValue(_DOUT_TOWER_LAMP_RED, TRUE);

	return TRUE;
}

void CVisionAgentAlarmDlg::ShowAlarm(BOOL bVisible)
{
	if (bVisible)
	{
		ShowWindow(SW_SHOW);
		SetActiveWindow();

		Invalidate();
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
}

void CVisionAgentAlarmDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UpdateUI();
	}
}

void CVisionAgentAlarmDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == IDT_ALARM_BLINK)	// 20170801 by sbs
	{
		//if (IsWindowVisible())
		//{
		//	m_tick++;
		//	if (m_tick % 2)
		//		MessageBeep(MB_ICONASTERISK);

		//	Invalidate();
		//}
	}

	CDialog::OnTimer(nIDEvent);
}

void CVisionAgentAlarmDlg::OnPaint()
{
	CRect rc, rcBar;
	CPaintDC dc(this);

	GetDlgItem(IDC_STATIC_ALARM_MSG)->GetClientRect(&rc);

	CFont* pOldFont = dc.SelectObject(&alarmfont);

	if (!m_msg.IsEmpty())
	{
		CBrush br;
		br.CreateSolidBrush(RGB(200, 0, 0));
		dc.FillRect(&rc, &br);
		dc.SetTextColor(RGB(255, 255, 255));
		br.DeleteObject();
	}
	else
	{
		dc.SetTextColor(RGB(0, 0, 0));
	}

	dc.DrawEdge(&rc, BDR_SUNKENINNER, BF_RECT);
	dc.SetBkMode(TRANSPARENT);


	CSize textExt = dc.GetTextExtent(m_msg);

	if (textExt.cx < rc.Width())
	{
		dc.DrawText(m_msg, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		CRect rcText = rc;
		dc.DrawText(m_msg, &rcText, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);

		rc.top += (rc.Height() - rcText.Height()) >> 1;

		dc.DrawText(m_msg, &rc, DT_WORDBREAK | DT_CENTER/* | DT_VCENTER*/);
	}

	dc.SelectObject(pOldFont);
}

void CVisionAgentAlarmDlg::OnBnClickedBtnAlarmClose()
{
	ShowWindow(SW_HIDE);
}

void CVisionAgentAlarmDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pListCtrl != NULL)
		delete m_pListCtrl;
}

void CVisionAgentAlarmDlg::OnBnClickedBtnAlarmReset()
{
	if (IDOK != AfxMessageBox(_T("ECS Error All Clear?"), MB_OKCANCEL)) return;


	for (int i = ALARM_LISTCTRL_MAX_ROW - 1; i >= 0; i--)
	{
		if (i >= SharedInfo::AlarmCount)
			continue;
		
		//Devs::CimMotion.CIMAlarmAllResetMessage();

		SharedInfo::AlarmList[i].AlarmDate = _T("");
		SharedInfo::AlarmList[i].AlarmTime = _T("");
		SharedInfo::AlarmList[i].AlarmCode = 0;
		SharedInfo::AlarmList[i].AlarmLevel = 0;
		SharedInfo::AlarmList[i].AlarmText = _T("");


		SharedInfo::AlarmCount--;
	}

	m_nErrCode = 0;
	m_msg = _T("");

	SharedInfo::SaveAlarmList();

	SharedInfo::ResetAlarm();

	UpdateUI();

	Etc_Msg(_T("[Cim] Send : Alarm State Change Report"));

	ShowWindow(SW_HIDE);
}

//uLevel(0 == Light, 1 == Heavy)
void CVisionAgentAlarmDlg::GetAlarmLevelDescription(UINT nErrCode, UINT*  uLevel, LPCTSTR* msg)
{
	switch (nErrCode)
	{
	case 1:
		*uLevel = 0;
		*msg = _T("Check The Alarm State");
		break;
	case 2:
		*uLevel = 0;
		*msg = _T("Check Servo On/Off");
		break;
	case 3:
		*uLevel = 0;
		*msg = _T("System All Stop");
		break;
	case 4:
		*uLevel = 0;
		*msg = _T("[Interlock] Check The Z Up");
		break;
	case 5:
		*uLevel = 0;
		*msg = _T("[Interlock] Check Move Gantry Z Up or  Check Gantry Y Position");
		break;
	case 6:
		*uLevel = 0;
		*msg = _T("[Interlock] Check The Work Area");
		break;
	case 7:
		*uLevel = 0;
		*msg = _T("[Interlock] Check _DIN_EMO_ON");
		break;
	case 8:
		*uLevel = 0;
		*msg = _T("[Interlock] Check _DIN_EMS_ON");
		break;
	case 9:
		*uLevel = 0;
		*msg = _T("[Interlock] Check VPS");
		break;
	case 10:
		*uLevel = 0;
		*msg = _T("[Interlock] DOOR OPEN");
		break;
	//case 3:
	//	*uLevel = 0;
	//	*msg = ;
		//break;
	default:
		break;
	}
}
