// MeasurementDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "MeasurementDlg.h"
#include "afxdialogex.h"

// CMeasurementDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMeasurementDlg, CDialogEx)

CMeasurementDlg::CMeasurementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_MASUREMENT_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_MASUREMENT_DIALOG, pParent);
}

CMeasurementDlg::~CMeasurementDlg()
{

}

void CMeasurementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CMeasurementDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMeasurementDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE_1, &CMeasurementDlg::OnBnClickedButtonSubPage1)
	ON_BN_CLICKED(IDC_BUTTON_MEASUREMENT_BRIGHTNESS, &CMeasurementDlg::OnBnClickedButtonMeasurementBrightness)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE_2, &CMeasurementDlg::OnBnClickedButtonSubPage2)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE_3, &CMeasurementDlg::OnBnClickedButtonSubPage3)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE_4, &CMeasurementDlg::OnBnClickedButtonSubPage4)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE_5, &CMeasurementDlg::OnBnClickedButtonSubPage5)
END_MESSAGE_MAP()

// CMeasurementDlg 메시지 처리기입니다.
//------------------------------------------------------------------
BOOL CMeasurementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	Dialog_Init();

	return TRUE;  
}
//------------------------------------------------------------------
void CMeasurementDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Safe_Hwnd() == FALSE) return;
	
#if 1
	int nOffset = 5;
	int nLamp_Size = 5;
	int nBtn_Size_X = 100;
	int nBtn_Size_Y = 50;
	CRect RectBtn, RectLamp;	
	CRect RectSubDlg;

#pragma region //Brightness
	RectBtn.left = nOffset * 2;
	RectBtn.top = nOffset;
	RectBtn.right = RectBtn.left + nBtn_Size_X;
	RectBtn.bottom = RectBtn.top + nBtn_Size_Y;
	m_btnMeasurement[MEASUREMENT_BRIGHTNESS_DLG].MoveWindow(RectBtn);

	RectLamp.left = RectBtn.left;
	RectLamp.top = RectBtn.top + nLamp_Size;
	RectLamp.right = RectBtn.right;
	RectLamp.bottom = RectBtn.bottom + nLamp_Size;
	m_stcMeasurement_Dlg_Lamp[MEASUREMENT_BRIGHTNESS_DLG].MoveWindow(RectLamp);
#pragma endregion

	//--------------------------
	CRect RectLine_W, RectLine_H;
	RectLine_W.left = nOffset;
	RectLine_W.top = RectLamp.bottom + nOffset;
	RectLine_W.right = cx - nOffset - nBtn_Size_X - nLamp_Size - nOffset - 2 - nOffset;
	RectLine_W.bottom = RectLine_W.top + 2;
	GetDlgItem(IDC_STATIC_LINE_W)->MoveWindow(RectLine_W);

	RectLine_H.left = RectLine_W.right + nOffset;
	RectLine_H.top = RectLine_W.bottom + nOffset;
	RectLine_H.right = RectLine_H.left + 2;
	RectLine_H.bottom = cy - nOffset - nBtn_Size_Y - nOffset;
	GetDlgItem(IDC_STATIC_LINE_H)->MoveWindow(RectLine_H);
	//--------------------------
	RectLamp.left = RectLine_H.right + nOffset;
	RectLamp.top = RectLine_H.top + nOffset;
	RectLamp.right = RectLamp.left + nBtn_Size_X;
	RectLamp.bottom = RectLamp.top + nBtn_Size_Y;
	RectBtn.left = RectLamp.left + nLamp_Size;
	RectBtn.top = RectLamp.top;
	RectBtn.right = RectLamp.right + nLamp_Size;
	RectBtn.bottom = RectLamp.bottom;
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_1].MoveWindow(RectBtn);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_1].MoveWindow(RectLamp);

	RectLamp.left = RectLine_H.right + nOffset;
	RectLamp.top = RectLamp.top + nOffset;
	RectLamp.right = RectLamp.left + nBtn_Size_X;
	RectLamp.bottom = RectLamp.bottom + nBtn_Size_Y;
	RectBtn.left = RectLamp.left + nLamp_Size;
	RectBtn.top = RectLamp.top;
	RectBtn.right = RectLamp.right + nLamp_Size;
	RectBtn.bottom = RectLamp.bottom;
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_2].MoveWindow(RectBtn);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_2].MoveWindow(RectLamp);

	RectLamp.left = RectLine_H.right + nOffset;
	RectLamp.top = RectLamp.top + nOffset;
	RectLamp.right = RectLamp.left + nBtn_Size_X;
	RectLamp.bottom = RectLamp.bottom + nBtn_Size_Y;
	RectBtn.left = RectLamp.left + nLamp_Size;
	RectBtn.top = RectLamp.top;
	RectBtn.right = RectLamp.right + nLamp_Size;
	RectBtn.bottom = RectLamp.bottom;
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_3].MoveWindow(RectBtn);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_3].MoveWindow(RectLamp);

	RectLamp.left = RectLine_H.right + nOffset;
	RectLamp.top = RectLamp.top + nOffset;
	RectLamp.right = RectLamp.left + nBtn_Size_X;
	RectLamp.bottom = RectLamp.bottom + nBtn_Size_Y;
	RectBtn.left = RectLamp.left + nLamp_Size;
	RectBtn.top = RectLamp.top;
	RectBtn.right = RectLamp.right + nLamp_Size;
	RectBtn.bottom = RectLamp.bottom;
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_4].MoveWindow(RectBtn);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_4].MoveWindow(RectLamp);

	RectLamp.left = RectLine_H.right + nOffset;
	RectLamp.top = RectLamp.top + nOffset;
	RectLamp.right = RectLamp.left + nBtn_Size_X;
	RectLamp.bottom = RectLamp.bottom + nBtn_Size_Y;
	RectBtn.left = RectLamp.left + nLamp_Size;
	RectBtn.top = RectLamp.top;
	RectBtn.right = RectLamp.right + nLamp_Size;
	RectBtn.bottom = RectLamp.bottom;
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_5].MoveWindow(RectBtn);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_5].MoveWindow(RectLamp);

	//--------------------------
	RectBtn.left = cx - nOffset - nBtn_Size_X;
	RectBtn.top = cy - nOffset - nBtn_Size_Y;
	RectBtn.right = cx - nOffset;
	RectBtn.bottom = cy - nOffset;
	GetDlgItem(IDC_BUTTON_CLOSE)->MoveWindow(RectBtn);
	//--------------------------
	RectSubDlg.left = RectLine_W.left + nOffset;
	RectSubDlg.top = RectLine_W.bottom + nOffset;
	RectSubDlg.right = RectLine_H.left - nOffset;
	RectSubDlg.bottom = RectLine_H.bottom - nOffset;
	GetDlgItem(IDC_STATIC_GROUP_BOX_MEASUREMENT_SUB_DLG)->MoveWindow(RectSubDlg);

	GetDlgItem(IDC_STATIC_GROUP_BOX_MEASUREMENT_SUB_DLG)->GetWindowRect(&RectSubDlg);
	ScreenToClient(RectSubDlg);

	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
#endif
}
//------------------------------------------------------------------
void CMeasurementDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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
void CMeasurementDlg::Dialog_Init()
{
	CRect rect;

	m_btnMeasurement[MEASUREMENT_BRIGHTNESS_DLG].SubclassDlgItem(IDC_BUTTON_MEASUREMENT_BRIGHTNESS, this);

	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_1].SubclassDlgItem(IDC_BUTTON_SUB_PAGE_1, this);
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_2].SubclassDlgItem(IDC_BUTTON_SUB_PAGE_2, this);
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_3].SubclassDlgItem(IDC_BUTTON_SUB_PAGE_3, this);
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_4].SubclassDlgItem(IDC_BUTTON_SUB_PAGE_4, this);
	m_btnSubMeasurement[MEASUREMENT_SUB_PAGE_5].SubclassDlgItem(IDC_BUTTON_SUB_PAGE_5, this);

	////
	m_stcMeasurement_Dlg_Lamp[MEASUREMENT_BRIGHTNESS_DLG].SubclassDlgItem(IDC_STATIC_LAMP_MEASUREMENT_BRIGHTNESS, this);
	m_stcMeasurement_Dlg_Lamp[MEASUREMENT_BRIGHTNESS_DLG].SetBackgroundColor(BTN_LAMP_OFF);

	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_1].SubclassDlgItem(IDC_STATIC_SUB_PAGE_LAMP_1, this);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_1].SetBackgroundColor(BTN_LAMP_OFF);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_2].SubclassDlgItem(IDC_STATIC_SUB_PAGE_LAMP_2, this);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_2].SetBackgroundColor(BTN_LAMP_OFF);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_3].SubclassDlgItem(IDC_STATIC_SUB_PAGE_LAMP_3, this);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_3].SetBackgroundColor(BTN_LAMP_OFF);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_4].SubclassDlgItem(IDC_STATIC_SUB_PAGE_LAMP_4, this);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_4].SetBackgroundColor(BTN_LAMP_OFF);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_5].SubclassDlgItem(IDC_STATIC_SUB_PAGE_LAMP_5, this);
	m_stcMeasurement_Sub_Dlg_Lamp[MEASUREMENT_SUB_PAGE_5].SetBackgroundColor(BTN_LAMP_OFF);

	int ntop = 50;
	int nleft = 250; //200
	int nRight = 0;
	int nbottom = 0;

	GetDlgItem(IDC_STATIC_GROUP_BOX_MEASUREMENT_SUB_DLG)->GetWindowRect(&rect);

	m_BrightnessDlg.Create(IDD_VISION_AGENT_MEASUREMENT_BRIGHTNESS_DIALOG, this);
	m_BrightnessDlg.SetWindowPos(NULL, rect.left - nleft, rect.top - ntop, rect.right - (rect.left), rect.bottom - (rect.top), NULL);
}

BOOL CMeasurementDlg::InitPara()
{
	m_nCurrentNo = 0;
	m_nCurrentSubNo = MEASUREMENT_SUB_PAGE_1;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);

	return TRUE;
}

BOOL CMeasurementDlg::Is_Comp_Safe_Hwnd()
{
	if (GetDlgItem(IDC_BUTTON_MEASUREMENT_BRIGHTNESS)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MEASUREMENT_BRIGHTNESS)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_BUTTON_SUB_PAGE_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SUB_PAGE_LAMP_1)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_STATIC_LINE_W)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_H)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_GROUP_BOX_MEASUREMENT_SUB_DLG)->GetSafeHwnd() == NULL) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------
void CMeasurementDlg::ShowDlg(int nDlgNo, int nSubDlgNo)
{
	CString Str = _T("");

	Dlg_HideWindow();
	for (int k = 0; k < MAX_MEASUREMENT_SUB_DLG; k++)
	{
		Str.Format(_T("Page%d"), k + 1);
		m_btnSubMeasurement[k].SetWindowText(Str);
		m_btnSubMeasurement[k].EnableWindow(FALSE);
		m_stcMeasurement_Sub_Dlg_Lamp[k].EnableWindow(FALSE);
	}

	for (int k = 0; k < MAX_MEASUREMENT_DLG; k++)
	{
		if (k == nDlgNo)
		{
			m_stcMeasurement_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcMeasurement_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	for (int k = 0; k < MAX_MEASUREMENT_SUB_DLG; k++)
	{
		if (k == nSubDlgNo)
		{
			m_stcMeasurement_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcMeasurement_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	switch (nDlgNo)
	{
	case MEASUREMENT_BRIGHTNESS_DLG:
	{
		if (nSubDlgNo == MEASUREMENT_SUB_PAGE_1)
		{
			m_BrightnessDlg.ShowWindow(SW_SHOW);
		}
		break;
	}
	}

	for (int k = 0; k < MAX_MEASUREMENT_DLG; k++)
	{
		m_btnMeasurement[k].SetFocus();
	}
	for (int k = 0; k < MAX_MEASUREMENT_SUB_DLG; k++)
	{
		m_btnSubMeasurement[k].SetFocus();
	}
}
//------------------------------------------------------------------
BOOL CMeasurementDlg::RecalcLayout()
{

	return TRUE;
}
//------------------------------------------------------------------
BOOL CMeasurementDlg::ShowData()
{
	return TRUE;
}
//------------------------------------------------------------------
void	CMeasurementDlg::ChangeUI()
{
	//저장된 데이터를 UI에 표시
}
//--------------------------------------------------------
void	CMeasurementDlg::ChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}
//--------------------------------------------------------
void CMeasurementDlg::Dlg_HideWindow()
{
	m_BrightnessDlg.ShowWindow(SW_HIDE);
}
//------------------------------------------------------------------
BOOL CMeasurementDlg::DestroyWindow()
{
	m_BrightnessDlg.DestroyWindow();

	return CDialogEx::DestroyWindow();
}

void CMeasurementDlg::OnBnClickedButtonMeasurementBrightness()
{
	m_nCurrentNo = MEASUREMENT_BRIGHTNESS_DLG;
	m_nCurrentSubNo = MEASUREMENT_SUB_PAGE_1;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//------------------------------------------------------------------
void CMeasurementDlg::OnBnClickedButtonClose()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowMeasurementModeless = FALSE;

	OnCancel();
}
//------------------------------------------------------------------
void CMeasurementDlg::OnCancel()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowMeasurementModeless = FALSE;

	CDialogEx::OnCancel();
}
//------------------------------------------------------------------
void CMeasurementDlg::OnBnClickedButtonSubPage1()
{
	if (m_nCurrentNo == 0 && m_nCurrentSubNo != MEASUREMENT_SUB_PAGE_1)
	{
		m_nCurrentNo = 0;
		m_nCurrentSubNo = MEASUREMENT_SUB_PAGE_1;
		ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
	}
}


void CMeasurementDlg::OnBnClickedButtonSubPage2()
{
	if (m_nCurrentNo == 0 && m_nCurrentSubNo != MEASUREMENT_SUB_PAGE_2)
	{
		m_nCurrentNo = 0; // MEASUREMENT_INSPECT_DLG;
		m_nCurrentSubNo = MEASUREMENT_SUB_PAGE_2;
		ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
	}
}


void CMeasurementDlg::OnBnClickedButtonSubPage3()
{
	if (m_nCurrentNo == 0 && m_nCurrentSubNo != MEASUREMENT_SUB_PAGE_3)
	{
		m_nCurrentNo = 0;
		m_nCurrentSubNo = MEASUREMENT_SUB_PAGE_3;
		ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
	}
}


void CMeasurementDlg::OnBnClickedButtonSubPage4()
{
	if (m_nCurrentNo == 0 && m_nCurrentSubNo != MEASUREMENT_SUB_PAGE_4)
	{
		m_nCurrentNo = 0;
		m_nCurrentSubNo = MEASUREMENT_SUB_PAGE_4;
		ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
	}
}


void CMeasurementDlg::OnBnClickedButtonSubPage5()
{
}
