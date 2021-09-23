// MommunicationADDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "CommunicationAIODlg.h"
#include "afxdialogex.h"


// CCommunicationAIODlg 대화 상자

IMPLEMENT_DYNAMIC(CCommunicationAIODlg, CDialogEx)

CCommunicationAIODlg::CCommunicationAIODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_COMMUNICATION_AIO, pParent)
{
	Create(IDD_DLG_COMMUNICATION_AIO, pParent);
}

CCommunicationAIODlg::~CCommunicationAIODlg()
{
}

void CCommunicationAIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCommunicationAIODlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_COMMUNICATION_AI_PREVIOUS_BTN, &CCommunicationAIODlg::OnBnClickedCommunicationAiPreviousBtn)
	ON_BN_CLICKED(IDC_COMMUNICATION_AI_NEXT_BTN, &CCommunicationAIODlg::OnBnClickedCommunicationAiNextBtn)
END_MESSAGE_MAP()


// CCommunicationAIODlg 메시지 처리기
BOOL CCommunicationAIODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_nCardNoAI = 0;

	InitDlg();
	InitAiLabel();
	ChangeUI();

	return TRUE;
}
//-----------------------------------------------------------------------
void CCommunicationAIODlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE) 
	{
		SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);
	}
}
//-----------------------------------------------------------------------
BOOL	CCommunicationAIODlg::Is_Comp_Safe_Hwnd()
{
	if (GetDlgItem(IDC_STATIC_NAME_AI)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_AI)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_4)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_5)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_6)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_7)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_8)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_9)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_10)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_11)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_12)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_13)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_14)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_15)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NO_16)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_STATIC_AI_NAME_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_4)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_5)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_6)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_7)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_8)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_9)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_10)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_11)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_12)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_13)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_14)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_15)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_NAME_16)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_STATIC_AI_DATA_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_4)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_5)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_6)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_7)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_8)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_9)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_10)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_11)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_12)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_13)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_14)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_15)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_DATA_16)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_COMMUNICATION_AI_PREVIOUS_BTN)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_AI_CARD_NUM)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_AI_NEXT_BTN)->GetSafeHwnd() == NULL) return FALSE;
	
	return TRUE;
}
//-----------------------------------------------------------------------
void CCommunicationAIODlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Safe_Hwnd() == FALSE)
	{
		return;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nOffset = 5;
	int nComp_Size_X = ((cx / 2) - (nOffset * 10)) / 7;
	int nComp_Size_Y = (cy - (nOffset * 38)) / 18;
	int nName_Size_X = ((cx / 4) - (nOffset * 2)) / 5;
	int nLine_Size_X = nName_Size_X * 4;
	CRect	RectName, RectLine;
	CRect	RectAINo, RectAILabel, RectAIData;
	CRect	RectBtn_L, RectBtn_R, RectNo;
	RectName.left = nOffset;
	RectName.top = nOffset;
	RectName.right = RectName.left + nName_Size_X;
	RectName.bottom = RectName.top + nComp_Size_Y;
	GetDlgItem(IDC_STATIC_NAME_AI)->MoveWindow(RectName);

	RectLine.left = RectName.right + nOffset;
	RectLine.top = ((RectName.top + RectName.bottom) / 2) - 1;
	RectLine.right = (cx / 2) - nOffset;
	RectLine.bottom = ((RectName.top + RectName.bottom) / 2) + 1;
	GetDlgItem(IDC_STATIC_LINE_AI)->MoveWindow(RectLine);
	//-----------------------------
	RectAINo.left = RectName.left + (nOffset * 2);
	RectAINo.right = RectAINo.left + nComp_Size_X;
	RectAILabel.left = RectAINo.right + (nOffset * 2);
	RectAILabel.right = RectAILabel.left + (nComp_Size_X * 3) + (nOffset * 2);
	RectAIData.left = RectAILabel.right + (nOffset * 2);
	RectAIData.right = RectAIData.left + (nComp_Size_X * 3) + (nOffset * 2);

	RectAINo.top = RectName.bottom + (nOffset * 2);
	RectAINo.bottom = RectAINo.top + nComp_Size_Y;
	RectAILabel.top = RectAINo.top;
	RectAILabel.bottom = RectAINo.bottom;
	RectAIData.top = RectAINo.top;
	RectAIData.bottom = RectAINo.bottom;

	m_staticAiNo[0].MoveWindow(RectAINo);
	m_staticAiName[0].MoveWindow(RectAILabel);
	m_staticDataAiData[0].MoveWindow(RectAIData);
	for (int k = 1; k < AI_MODULE_SIZE; k++)
	{
		RectAINo.top = RectAINo.bottom + (nOffset * 2);
		RectAINo.bottom = RectAINo.top + nComp_Size_Y;
		RectAILabel.top = RectAINo.top;
		RectAILabel.bottom = RectAINo.bottom;
		RectAIData.top = RectAINo.top;
		RectAIData.bottom = RectAINo.bottom;

		m_staticAiNo[k].MoveWindow(RectAINo);
		m_staticAiName[k].MoveWindow(RectAILabel);
		m_staticDataAiData[k].MoveWindow(RectAIData);
	}
	RectBtn_L.top		= RectAINo.bottom + (nOffset * 2);
	RectBtn_L.bottom	= RectBtn_L.top + nComp_Size_Y;
	RectNo.top			= RectAINo.bottom + (nOffset * 2);
	RectNo.bottom		= RectBtn_L.top + nComp_Size_Y;
	RectBtn_R.top		= RectAINo.bottom + (nOffset * 2);
	RectBtn_R.bottom	= RectBtn_L.top + nComp_Size_Y;

	RectBtn_L.left		= RectAINo.left;
	RectBtn_L.right		= RectBtn_L.left + (nComp_Size_X * 2) + nOffset;
	RectNo.left			= RectBtn_L.right + (nOffset * 2);
	RectNo.right		= RectNo.left + (nComp_Size_X * 3) + (nOffset * 2);
	RectBtn_R.left		= RectNo.right + (nOffset * 2);
	RectBtn_R.right		= RectBtn_R.left + (nComp_Size_X * 2) + nOffset;
	GetDlgItem(IDC_COMMUNICATION_AI_PREVIOUS_BTN)->MoveWindow(RectBtn_L);
	GetDlgItem(IDC_STATIC_AI_CARD_NUM)->MoveWindow(RectNo);
	GetDlgItem(IDC_COMMUNICATION_AI_NEXT_BTN)->MoveWindow(RectBtn_R);
}
//-----------------------------------------------------------------------
void CCommunicationAIODlg::InitDlg()
{
	m_nCardNoAI = 0;
	
	m_staticAiNo[0].SubclassDlgItem(IDC_STATIC_AI_NO_1, this);
	m_staticAiNo[1].SubclassDlgItem(IDC_STATIC_AI_NO_2, this);
	m_staticAiNo[2].SubclassDlgItem(IDC_STATIC_AI_NO_3, this);
	m_staticAiNo[3].SubclassDlgItem(IDC_STATIC_AI_NO_4, this);
	m_staticAiNo[4].SubclassDlgItem(IDC_STATIC_AI_NO_5, this);
	m_staticAiNo[5].SubclassDlgItem(IDC_STATIC_AI_NO_6, this);
	m_staticAiNo[6].SubclassDlgItem(IDC_STATIC_AI_NO_7, this);
	m_staticAiNo[7].SubclassDlgItem(IDC_STATIC_AI_NO_8, this);
	m_staticAiNo[8].SubclassDlgItem(IDC_STATIC_AI_NO_9, this);
	m_staticAiNo[9].SubclassDlgItem(IDC_STATIC_AI_NO_10, this);
	m_staticAiNo[10].SubclassDlgItem(IDC_STATIC_AI_NO_11, this);
	m_staticAiNo[11].SubclassDlgItem(IDC_STATIC_AI_NO_12, this);
	m_staticAiNo[12].SubclassDlgItem(IDC_STATIC_AI_NO_13, this);
	m_staticAiNo[13].SubclassDlgItem(IDC_STATIC_AI_NO_14, this);
	m_staticAiNo[14].SubclassDlgItem(IDC_STATIC_AI_NO_15, this);
	m_staticAiNo[15].SubclassDlgItem(IDC_STATIC_AI_NO_16, this);

	m_staticAiName[0].SubclassDlgItem(IDC_STATIC_AI_NAME_1, this);
	m_staticAiName[1].SubclassDlgItem(IDC_STATIC_AI_NAME_2, this);
	m_staticAiName[2].SubclassDlgItem(IDC_STATIC_AI_NAME_3, this);
	m_staticAiName[3].SubclassDlgItem(IDC_STATIC_AI_NAME_4, this);
	m_staticAiName[4].SubclassDlgItem(IDC_STATIC_AI_NAME_5, this);
	m_staticAiName[5].SubclassDlgItem(IDC_STATIC_AI_NAME_6, this);
	m_staticAiName[6].SubclassDlgItem(IDC_STATIC_AI_NAME_7, this);
	m_staticAiName[7].SubclassDlgItem(IDC_STATIC_AI_NAME_8, this);
	m_staticAiName[8].SubclassDlgItem(IDC_STATIC_AI_NAME_9, this);
	m_staticAiName[9].SubclassDlgItem(IDC_STATIC_AI_NAME_10, this);
	m_staticAiName[10].SubclassDlgItem(IDC_STATIC_AI_NAME_11, this);
	m_staticAiName[11].SubclassDlgItem(IDC_STATIC_AI_NAME_12, this);
	m_staticAiName[12].SubclassDlgItem(IDC_STATIC_AI_NAME_13, this);
	m_staticAiName[13].SubclassDlgItem(IDC_STATIC_AI_NAME_14, this);
	m_staticAiName[14].SubclassDlgItem(IDC_STATIC_AI_NAME_15, this);
	m_staticAiName[15].SubclassDlgItem(IDC_STATIC_AI_NAME_16, this);

	m_staticDataAiData[0].SubclassDlgItem(IDC_STATIC_AI_DATA_1, this);
	m_staticDataAiData[1].SubclassDlgItem(IDC_STATIC_AI_DATA_2, this);
	m_staticDataAiData[2].SubclassDlgItem(IDC_STATIC_AI_DATA_3, this);
	m_staticDataAiData[3].SubclassDlgItem(IDC_STATIC_AI_DATA_4, this);
	m_staticDataAiData[4].SubclassDlgItem(IDC_STATIC_AI_DATA_5, this);
	m_staticDataAiData[5].SubclassDlgItem(IDC_STATIC_AI_DATA_6, this);
	m_staticDataAiData[6].SubclassDlgItem(IDC_STATIC_AI_DATA_7, this);
	m_staticDataAiData[7].SubclassDlgItem(IDC_STATIC_AI_DATA_8, this);
	m_staticDataAiData[8].SubclassDlgItem(IDC_STATIC_AI_DATA_9, this);
	m_staticDataAiData[9].SubclassDlgItem(IDC_STATIC_AI_DATA_10, this);
	m_staticDataAiData[10].SubclassDlgItem(IDC_STATIC_AI_DATA_11, this);
	m_staticDataAiData[11].SubclassDlgItem(IDC_STATIC_AI_DATA_12, this);
	m_staticDataAiData[12].SubclassDlgItem(IDC_STATIC_AI_DATA_13, this);
	m_staticDataAiData[13].SubclassDlgItem(IDC_STATIC_AI_DATA_14, this);
	m_staticDataAiData[14].SubclassDlgItem(IDC_STATIC_AI_DATA_15, this);
	m_staticDataAiData[15].SubclassDlgItem(IDC_STATIC_AI_DATA_16, this);

	for (int i = 0; i < AI_MODULE_SIZE; i++)
	{
		m_staticAiNo[i].SetBackgroundColor(LLTGRAY);
		m_staticAiNo[i].SetTextColor(RGB(1, 1, 1));

		m_staticAiName[i].SetBackgroundColor(DKCYAN);
		m_staticAiName[i].SetTextColor(RGB(255, 255, 255));

		m_staticDataAiData[i].SetBackgroundColor(DKGRAY);
		m_staticDataAiData[i].SetTextColor(RGB(255, 255, 255));
	}
}
//-----------------------------------------------------------------------
void CCommunicationAIODlg::InitAiLabel()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int		nLabel_Index = 0;
	for (int j = 0; j < AI_MODULE_CNT; j++)
	{
		for (int i = 0; i < AI_MODULE_SIZE; i++)
		{
			nLabel_Index = (j * AI_MODULE_SIZE) + i;
			//m_strAiLabel[nLabel_Index].Format(_T("%s"), SharedInfo::m_AInputName[nLabel_Index]);
			m_strAiLabel[nLabel_Index].Format(_T("%s"), pVisionAgentDlg->m_AInputLabel[nLabel_Index].m_StrLabel);
		}
	}
}
//-----------------------------------------------------------------------
void CCommunicationAIODlg::ChangeUI()
{
	CString strTemp;
	int nLabel_Index;
	for (int k = 0; k < AI_MODULE_SIZE; k++)
	{
		nLabel_Index = (m_nCardNoAI * AI_MODULE_SIZE) + k;
		m_staticAiName[k].SetWindowTextW(m_strAiLabel[nLabel_Index]);
	}
}
//-----------------------------------------------------------------------
void CCommunicationAIODlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTemp;
	for (int i = 0; i < AI_MODULE_SIZE; i++)
	{
		strTemp.Format(_T("%.5f"), SharedInfo::Get_AI_Data(i + AI_MODULE_SIZE * m_nCardNoAI));
		m_staticDataAiData[i].SetData(strTemp);
	}
	CDialogEx::OnTimer(nIDEvent);
}
//-----------------------------------------------------------------------

void CCommunicationAIODlg::OnBnClickedCommunicationAiPreviousBtn()
{
	CString strCardNo;
	m_nCardNoAI = m_nCardNoAI - 1;
	if (m_nCardNoAI < 0)
	{
		m_nCardNoAI = 0;
	}
	strCardNo.Format(_T("AI Card No %02d"), m_nCardNoAI);
	SetDlgItemTextW(IDC_STATIC_AI_CARD_NUM, strCardNo);
	ChangeUI();
}


void CCommunicationAIODlg::OnBnClickedCommunicationAiNextBtn()
{
	CString strCardNo;
	m_nCardNoAI = m_nCardNoAI + 1;
	if (m_nCardNoAI >= AI_MODULE_CNT)
	{
		m_nCardNoAI = AI_MODULE_CNT - 1;
	}
	strCardNo.Format(_T("AI Card No %02d"), m_nCardNoAI);
	SetDlgItemTextW(IDC_STATIC_AI_CARD_NUM, strCardNo);
	ChangeUI();
}
