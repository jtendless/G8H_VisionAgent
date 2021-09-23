// CommunicationDIODlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "CommunicationDIODlg.h"
#include "afxdialogex.h"
#include "../Module/Motion/BaseMotion.h"

// CCommunicationDIODlg 대화 상자

IMPLEMENT_DYNAMIC(CCommunicationDIODlg, CDialogEx)

CCommunicationDIODlg::CCommunicationDIODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_COMMUNICATION_DIO, pParent)
{
	Create(IDD_DLG_COMMUNICATION_DIO, pParent);
}

CCommunicationDIODlg::~CCommunicationDIODlg()
{
}

void CCommunicationDIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CCommunicationDIODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_nCardNoDI = 0;
	m_nCardNoDO	= 0;

	InitDlg();
	InitDiLabel();
	InitDoLabel();
	ChangeUI();

	m_pBaseMotion = &Devs::m_JogMotion;

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCommunicationDIODlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_COMMUNICATION_DI_PREVIOUS_BTN, &CCommunicationDIODlg::OnBnClickedCommunicationDiPreviousBtn)
	ON_BN_CLICKED(IDC_COMMUNICATION_DI_NEXT_BTN, &CCommunicationDIODlg::OnBnClickedCommunicationDiNextBtn)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_PREVIOUS_BTN, &CCommunicationDIODlg::OnBnClickedCommunicationDoPreviousBtn)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_NEXT_BTN, &CCommunicationDIODlg::OnBnClickedCommunicationDoNextBtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_1, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn1)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_2, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn2)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_3, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn3)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_4, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn4)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_5, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn5)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_6, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn6)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_7, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn7)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_8, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn8)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_9, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn9)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_10, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn10)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_11, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn11)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_12, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn12)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_13, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn13)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_14, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn14)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_15, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn15)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_16, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn16)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_17, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn17)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_18, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn18)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_19, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn19)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_20, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn20)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_21, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn21)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_22, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn22)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_23, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn23)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_24, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn24)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_25, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn25)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_26, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn26)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_27, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn27)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_28, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn28)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_29, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn29)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_30, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn30)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_31, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn31)
	ON_BN_CLICKED(IDC_COMMUNICATION_DO_BTN_32, &CCommunicationDIODlg::OnBnClickedCommunicationDoBtn32)

END_MESSAGE_MAP()


// CCommunicationDIODlg 메시지 처리기

//----------------------------------------------------------------
BOOL CCommunicationDIODlg::Is_Comp_Safe_Hwnd()
{
	if (GetDlgItem(IDC_STATIC_NAME_DI)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_DI)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_NAME_DO)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_DO)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_4)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_5)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_6)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_7)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_8)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_9)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_10)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_11)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_12)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_13)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_14)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_15)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_16)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_17)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_18)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_19)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_20)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_21)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_22)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_22)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_23)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_24)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_25)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_26)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_27)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_28)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_29)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_30)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_31)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DI_LED_32)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_COM_DO_LED_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_4)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_5)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_6)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_7)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_8)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_9)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_10)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_11)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_12)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_13)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_14)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_15)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_16)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_17)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_18)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_19)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_20)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_21)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_22)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_22)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_23)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_24)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_25)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_26)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_27)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_28)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_29)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_30)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_31)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COM_DO_LED_32)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_STATIC_DI_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_4)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_5)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_6)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_7)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_8)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_9)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_10)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_11)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_12)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_13)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_14)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_15)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_16)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_17)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_18)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_19)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_20)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_21)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_22)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_22)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_23)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_24)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_25)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_26)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_27)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_28)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_29)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_30)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_31)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_32)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_4)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_5)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_6)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_7)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_8)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_9)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_10)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_11)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_12)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_13)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_14)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_15)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_16)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_17)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_18)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_19)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_20)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_21)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_22)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_22)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_23)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_24)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_25)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_26)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_27)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_28)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_29)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_30)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_31)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_BTN_32)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_COMMUNICATION_DI_PREVIOUS_BTN)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DI_CARD_NUM)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DI_NEXT_BTN)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_COMMUNICATION_DO_PREVIOUS_BTN)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_DO_CARD_NUM)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMMUNICATION_DO_NEXT_BTN)->GetSafeHwnd() == NULL) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Safe_Hwnd() == FALSE)
	{
		return;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nOffset			= 5;
	int nComp_Size_X = ((cx / 4) - (nOffset * 10)) / 5;
	int nComp_Size_Y = (cy - (nOffset * 38)) / 18;
	int nName_Size_X = ((cx / 4) - (nOffset * 2)) / 5;
	int nLine_Size_X = nName_Size_X * 4;
	CRect	RectName, RectLine;
	CRect	RectLed, RectLabel;
	CRect	RectBtn_L, RectBtn_R, RectNo;
	RectName.left	= nOffset;
	RectName.top	= nOffset;
	RectName.right	= RectName.left + nName_Size_X;
	RectName.bottom	= RectName.top + nComp_Size_Y;
	GetDlgItem(IDC_STATIC_NAME_DI)->MoveWindow(RectName);

	RectLine.left	= RectName.right + nOffset;
	RectLine.top	= ((RectName.top + RectName.bottom) / 2) - 1;
	RectLine.right	= (cx / 2) - nOffset;
	RectLine.bottom	= ((RectName.top + RectName.bottom) / 2) + 1;
	GetDlgItem(IDC_STATIC_LINE_DI)->MoveWindow(RectLine);
	//---------------
	RectLed.left		= RectName.left + (nOffset * 2);	
	RectLed.right		= RectLed.left + nComp_Size_X;	
	RectLabel.left		= RectLed.right + (nOffset * 2);	
	RectLabel.right		= RectLabel.left + (nComp_Size_X * 4) + (nOffset * 3);
	
	RectLed.top			= RectName.bottom + (nOffset * 2);
	RectLed.bottom		= RectLed.top + nComp_Size_Y;
	RectLabel.top		= RectLed.top;
	RectLabel.bottom	= RectLed.bottom;

	m_ledDI[0].MoveWindow(RectLed);
	m_staticDI[0].MoveWindow(RectLabel); 
	for (int k = 1; k < 16; k++)
	{
		RectLed.top			= RectLed.bottom + (nOffset * 2);
		RectLed.bottom		= RectLed.top + nComp_Size_Y;
		RectLabel.top		= RectLed.top;
		RectLabel.bottom	= RectLed.bottom;
		m_ledDI[k].MoveWindow(RectLed);
		m_staticDI[k].MoveWindow(RectLabel);
	}
	//----------------
	RectLed.left	= RectLabel.right + (nOffset * 2);	
	RectLed.right	= RectLed.left + nComp_Size_X;
	RectLabel.left	= RectLed.right + (nOffset * 2);
	RectLabel.right = RectLabel.left + (nComp_Size_X * 4) + (nOffset * 3);

	RectLed.top			= RectName.bottom + (nOffset * 2);
	RectLed.bottom		= RectLed.top + nComp_Size_Y;
	RectLabel.top		= RectLed.top;
	RectLabel.bottom	= RectLed.bottom;
	m_ledDI[16].MoveWindow(RectLed);
	m_staticDI[16].MoveWindow(RectLabel);
	for (int k = 17; k < 32; k++)
	{
		RectLed.top			= RectLed.bottom + (nOffset * 2);
		RectLed.bottom		= RectLed.top + nComp_Size_Y;
		RectLabel.top		= RectLed.top;
		RectLabel.bottom	= RectLed.bottom;
		m_ledDI[k].MoveWindow(RectLed);
		m_staticDI[k].MoveWindow(RectLabel);
	}
	//------------------
	RectName.left		= (cx / 2) + nOffset;
	RectName.top		= nOffset;
	RectName.right		= RectName.left + nName_Size_X;
	RectName.bottom		= RectName.top + nComp_Size_Y;
	GetDlgItem(IDC_STATIC_NAME_DO)->MoveWindow(RectName);

	RectLine.left		= RectName.right + nOffset;
	RectLine.top		= ((RectName.top + RectName.bottom) / 2) - 1;
	RectLine.right		= cx - nOffset;
	RectLine.bottom		= ((RectName.top + RectName.bottom) / 2) + 1;
	GetDlgItem(IDC_STATIC_LINE_DO)->MoveWindow(RectLine);

	//---------------
	RectLed.left = RectName.left + (nOffset * 2);
	RectLed.right = RectLed.left + nComp_Size_X;
	RectLabel.left = RectLed.right + (nOffset * 2);
	RectLabel.right = RectLabel.left + (nComp_Size_X * 4) + (nOffset * 3);

	RectLed.top = RectName.bottom + (nOffset * 2);
	RectLed.bottom = RectLed.top + nComp_Size_Y;
	RectLabel.top = RectLed.top;
	RectLabel.bottom = RectLed.bottom;

	m_ledDO[0].MoveWindow(RectLed);
	m_btnDO[0].MoveWindow(RectLabel);
	for (int k = 1; k < 16; k++)
	{
		RectLed.top = RectLed.bottom + (nOffset * 2);
		RectLed.bottom = RectLed.top + nComp_Size_Y;
		RectLabel.top = RectLed.top;
		RectLabel.bottom = RectLed.bottom;
		m_ledDO[k].MoveWindow(RectLed);
		m_btnDO[k].MoveWindow(RectLabel);
	}
	//----------------
	RectLed.left = RectLabel.right + (nOffset * 2);
	RectLed.right = RectLed.left + nComp_Size_X;
	RectLabel.left = RectLed.right + (nOffset * 2);
	RectLabel.right = RectLabel.left + (nComp_Size_X * 4) + (nOffset * 3);

	RectLed.top = RectName.bottom + (nOffset * 2);
	RectLed.bottom = RectLed.top + nComp_Size_Y;
	RectLabel.top = RectLed.top;
	RectLabel.bottom = RectLed.bottom;
	m_ledDO[16].MoveWindow(RectLed);
	m_btnDO[16].MoveWindow(RectLabel);
	for (int k = 17; k < 32; k++)
	{
		RectLed.top = RectLed.bottom + (nOffset * 2);
		RectLed.bottom = RectLed.top + nComp_Size_Y;
		RectLabel.top = RectLed.top;
		RectLabel.bottom = RectLed.bottom;
		m_ledDO[k].MoveWindow(RectLed);
		m_btnDO[k].MoveWindow(RectLabel);
	}
	//------------------
	int	nBtn_Size_X = ((cx / 2) - (nOffset * 10)) / 4;
	RectBtn_L.top		= cy - nOffset - nComp_Size_Y;
	RectBtn_L.bottom	= RectBtn_L.top + nComp_Size_Y;
	RectNo.top			= RectBtn_L.top;
	RectNo.bottom		= RectBtn_L.bottom;
	RectBtn_R.top		= RectBtn_L.top;
	RectBtn_R.bottom	= RectBtn_L.bottom;

	RectBtn_L.left		= nOffset;	
	RectBtn_L.right		= RectBtn_L.left + nBtn_Size_X;	
	RectNo.left			= RectBtn_L.right + (nOffset * 2);
	RectNo.right		= RectNo.left + (nBtn_Size_X * 2) + nOffset;
	RectBtn_R.left		= RectNo.right + nOffset;
	RectBtn_R.right		= RectBtn_R.left + nBtn_Size_X;

	GetDlgItem(IDC_COMMUNICATION_DI_PREVIOUS_BTN)->MoveWindow(RectBtn_L);
	GetDlgItem(IDC_STATIC_DI_CARD_NUM)->MoveWindow(RectNo);
	GetDlgItem(IDC_COMMUNICATION_DI_NEXT_BTN)->MoveWindow(RectBtn_R);

	//-------------
	RectBtn_L.left		= (cx / 2) + nOffset;	
	RectBtn_L.right		= RectBtn_L.left + nBtn_Size_X;
	RectNo.left			= RectBtn_L.right + (nOffset * 2);
	RectNo.right		= RectNo.left + (nBtn_Size_X * 2) + nOffset;
	RectBtn_R.left		= RectNo.right + nOffset;
	RectBtn_R.right		= RectBtn_R.left + nBtn_Size_X;
	GetDlgItem(IDC_COMMUNICATION_DO_PREVIOUS_BTN)->MoveWindow(RectBtn_L);
	GetDlgItem(IDC_STATIC_DO_CARD_NUM)->MoveWindow(RectNo);
	GetDlgItem(IDC_COMMUNICATION_DO_NEXT_BTN)->MoveWindow(RectBtn_R);
	
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE) 
	{
		InitDiLabel();
		InitDoLabel();
		ChangeUI();

		SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);
	}
}
//----------------------------------------------------------------
void CCommunicationDIODlg::InitDlg()
{
	m_ledDI[0].SubclassDlgItem(IDC_COM_DI_LED_1, this);
	m_ledDI[1].SubclassDlgItem(IDC_COM_DI_LED_2, this);
	m_ledDI[2].SubclassDlgItem(IDC_COM_DI_LED_3, this);
	m_ledDI[3].SubclassDlgItem(IDC_COM_DI_LED_4, this);
	m_ledDI[4].SubclassDlgItem(IDC_COM_DI_LED_5, this);
	m_ledDI[5].SubclassDlgItem(IDC_COM_DI_LED_6, this);
	m_ledDI[6].SubclassDlgItem(IDC_COM_DI_LED_7, this);
	m_ledDI[7].SubclassDlgItem(IDC_COM_DI_LED_8, this);
	m_ledDI[8].SubclassDlgItem(IDC_COM_DI_LED_9, this);
	m_ledDI[9].SubclassDlgItem(IDC_COM_DI_LED_10, this);
	m_ledDI[10].SubclassDlgItem(IDC_COM_DI_LED_11, this);
	m_ledDI[11].SubclassDlgItem(IDC_COM_DI_LED_12, this);
	m_ledDI[12].SubclassDlgItem(IDC_COM_DI_LED_13, this);
	m_ledDI[13].SubclassDlgItem(IDC_COM_DI_LED_14, this);
	m_ledDI[14].SubclassDlgItem(IDC_COM_DI_LED_15, this);
	m_ledDI[15].SubclassDlgItem(IDC_COM_DI_LED_16, this);
	m_ledDI[16].SubclassDlgItem(IDC_COM_DI_LED_17, this);
	m_ledDI[17].SubclassDlgItem(IDC_COM_DI_LED_18, this);
	m_ledDI[18].SubclassDlgItem(IDC_COM_DI_LED_19, this);
	m_ledDI[19].SubclassDlgItem(IDC_COM_DI_LED_20, this);
	m_ledDI[20].SubclassDlgItem(IDC_COM_DI_LED_21, this);
	m_ledDI[21].SubclassDlgItem(IDC_COM_DI_LED_22, this);
	m_ledDI[22].SubclassDlgItem(IDC_COM_DI_LED_23, this);
	m_ledDI[23].SubclassDlgItem(IDC_COM_DI_LED_24, this);
	m_ledDI[24].SubclassDlgItem(IDC_COM_DI_LED_25, this);
	m_ledDI[25].SubclassDlgItem(IDC_COM_DI_LED_26, this);
	m_ledDI[26].SubclassDlgItem(IDC_COM_DI_LED_27, this);
	m_ledDI[27].SubclassDlgItem(IDC_COM_DI_LED_28, this);
	m_ledDI[28].SubclassDlgItem(IDC_COM_DI_LED_29, this);
	m_ledDI[29].SubclassDlgItem(IDC_COM_DI_LED_30, this);
	m_ledDI[30].SubclassDlgItem(IDC_COM_DI_LED_31, this);
	m_ledDI[31].SubclassDlgItem(IDC_COM_DI_LED_32, this);

	m_ledDO[0].SubclassDlgItem(IDC_COM_DO_LED_1, this);
	m_ledDO[1].SubclassDlgItem(IDC_COM_DO_LED_2, this);
	m_ledDO[2].SubclassDlgItem(IDC_COM_DO_LED_3, this);
	m_ledDO[3].SubclassDlgItem(IDC_COM_DO_LED_4, this);
	m_ledDO[4].SubclassDlgItem(IDC_COM_DO_LED_5, this);
	m_ledDO[5].SubclassDlgItem(IDC_COM_DO_LED_6, this);
	m_ledDO[6].SubclassDlgItem(IDC_COM_DO_LED_7, this);
	m_ledDO[7].SubclassDlgItem(IDC_COM_DO_LED_8, this);
	m_ledDO[8].SubclassDlgItem(IDC_COM_DO_LED_9, this);
	m_ledDO[9].SubclassDlgItem(IDC_COM_DO_LED_10, this);
	m_ledDO[10].SubclassDlgItem(IDC_COM_DO_LED_11, this);
	m_ledDO[11].SubclassDlgItem(IDC_COM_DO_LED_12, this);
	m_ledDO[12].SubclassDlgItem(IDC_COM_DO_LED_13, this);
	m_ledDO[13].SubclassDlgItem(IDC_COM_DO_LED_14, this);
	m_ledDO[14].SubclassDlgItem(IDC_COM_DO_LED_15, this);
	m_ledDO[15].SubclassDlgItem(IDC_COM_DO_LED_16, this);
	m_ledDO[16].SubclassDlgItem(IDC_COM_DO_LED_17, this);
	m_ledDO[17].SubclassDlgItem(IDC_COM_DO_LED_18, this);
	m_ledDO[18].SubclassDlgItem(IDC_COM_DO_LED_19, this);
	m_ledDO[19].SubclassDlgItem(IDC_COM_DO_LED_20, this);
	m_ledDO[20].SubclassDlgItem(IDC_COM_DO_LED_21, this);
	m_ledDO[21].SubclassDlgItem(IDC_COM_DO_LED_22, this);
	m_ledDO[22].SubclassDlgItem(IDC_COM_DO_LED_23, this);
	m_ledDO[23].SubclassDlgItem(IDC_COM_DO_LED_24, this);
	m_ledDO[24].SubclassDlgItem(IDC_COM_DO_LED_25, this);
	m_ledDO[25].SubclassDlgItem(IDC_COM_DO_LED_26, this);
	m_ledDO[26].SubclassDlgItem(IDC_COM_DO_LED_27, this);
	m_ledDO[27].SubclassDlgItem(IDC_COM_DO_LED_28, this);
	m_ledDO[28].SubclassDlgItem(IDC_COM_DO_LED_29, this);
	m_ledDO[29].SubclassDlgItem(IDC_COM_DO_LED_30, this);
	m_ledDO[30].SubclassDlgItem(IDC_COM_DO_LED_31, this);
	m_ledDO[31].SubclassDlgItem(IDC_COM_DO_LED_32, this);

	m_staticDI[0].SubclassDlgItem(IDC_STATIC_DI_1, this);
	m_staticDI[1].SubclassDlgItem(IDC_STATIC_DI_2, this);
	m_staticDI[2].SubclassDlgItem(IDC_STATIC_DI_3, this);
	m_staticDI[3].SubclassDlgItem(IDC_STATIC_DI_4, this);
	m_staticDI[4].SubclassDlgItem(IDC_STATIC_DI_5, this);
	m_staticDI[5].SubclassDlgItem(IDC_STATIC_DI_6, this);
	m_staticDI[6].SubclassDlgItem(IDC_STATIC_DI_7, this);
	m_staticDI[7].SubclassDlgItem(IDC_STATIC_DI_8, this);
	m_staticDI[8].SubclassDlgItem(IDC_STATIC_DI_9, this);
	m_staticDI[9].SubclassDlgItem(IDC_STATIC_DI_10, this);
	m_staticDI[10].SubclassDlgItem(IDC_STATIC_DI_11, this);
	m_staticDI[11].SubclassDlgItem(IDC_STATIC_DI_12, this);
	m_staticDI[12].SubclassDlgItem(IDC_STATIC_DI_13, this);
	m_staticDI[13].SubclassDlgItem(IDC_STATIC_DI_14, this);
	m_staticDI[14].SubclassDlgItem(IDC_STATIC_DI_15, this);
	m_staticDI[15].SubclassDlgItem(IDC_STATIC_DI_16, this);
	m_staticDI[16].SubclassDlgItem(IDC_STATIC_DI_17, this);
	m_staticDI[17].SubclassDlgItem(IDC_STATIC_DI_18, this);
	m_staticDI[18].SubclassDlgItem(IDC_STATIC_DI_19, this);
	m_staticDI[19].SubclassDlgItem(IDC_STATIC_DI_20, this);
	m_staticDI[20].SubclassDlgItem(IDC_STATIC_DI_21, this);
	m_staticDI[21].SubclassDlgItem(IDC_STATIC_DI_22, this);
	m_staticDI[22].SubclassDlgItem(IDC_STATIC_DI_23, this);
	m_staticDI[23].SubclassDlgItem(IDC_STATIC_DI_24, this);
	m_staticDI[24].SubclassDlgItem(IDC_STATIC_DI_25, this);
	m_staticDI[25].SubclassDlgItem(IDC_STATIC_DI_26, this);
	m_staticDI[26].SubclassDlgItem(IDC_STATIC_DI_27, this);
	m_staticDI[27].SubclassDlgItem(IDC_STATIC_DI_28, this);
	m_staticDI[28].SubclassDlgItem(IDC_STATIC_DI_29, this);
	m_staticDI[29].SubclassDlgItem(IDC_STATIC_DI_30, this);
	m_staticDI[30].SubclassDlgItem(IDC_STATIC_DI_31, this);
	m_staticDI[31].SubclassDlgItem(IDC_STATIC_DI_32, this);

	m_btnDO[0].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_1, this);
	m_btnDO[1].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_2, this);
	m_btnDO[2].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_3, this);
	m_btnDO[3].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_4, this);
	m_btnDO[4].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_5, this);
	m_btnDO[5].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_6, this);
	m_btnDO[6].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_7, this);
	m_btnDO[7].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_8, this);
	m_btnDO[8].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_9, this);
	m_btnDO[9].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_10, this);
	m_btnDO[10].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_11, this);
	m_btnDO[11].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_12, this);
	m_btnDO[12].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_13, this);
	m_btnDO[13].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_14, this);
	m_btnDO[14].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_15, this);
	m_btnDO[15].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_16, this);
	m_btnDO[16].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_17, this);
	m_btnDO[17].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_18, this);
	m_btnDO[18].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_19, this);
	m_btnDO[19].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_20, this);
	m_btnDO[20].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_21, this);
	m_btnDO[21].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_22, this);
	m_btnDO[22].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_23, this);
	m_btnDO[23].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_24, this);
	m_btnDO[24].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_25, this);
	m_btnDO[25].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_26, this);
	m_btnDO[26].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_27, this);
	m_btnDO[27].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_28, this);
	m_btnDO[28].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_29, this);
	m_btnDO[29].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_30, this);
	m_btnDO[30].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_31, this);
	m_btnDO[31].SubclassDlgItem(IDC_COMMUNICATION_DO_BTN_32, this);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::InitDiLabel()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int		nLabel_Index = 0;
	for (int j = 0; j < DI_MODULE_CNT; j++)
	{
		for (int i = 0; i < DIO_MODULE_SIZE; i++)
		{
			nLabel_Index = (j * DIO_MODULE_SIZE) + i;
			//m_strDI_Label[nLabel_Index].Format(_T("%s"), SharedInfo::m_DInputName[nLabel_Index]);
			m_strDI_Label[nLabel_Index].Format(_T("%s"), pVisionAgentDlg->m_DInputLabel[nLabel_Index].m_StrLabel);
		}
	}
}
//----------------------------------------------------------------
void CCommunicationDIODlg::InitDoLabel()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int		nLabel_Index = 0;
	for (int j = 0; j < DO_MODULE_CNT; j++)
	{
		for (int i = 0; i < DIO_MODULE_SIZE; i++)
		{
			nLabel_Index = (j * DIO_MODULE_SIZE) + i;
			//m_strDO_Label[nLabel_Index].Format(_T("%s"), SharedInfo::m_DOutputName[nLabel_Index]);
			m_strDO_Label[nLabel_Index].Format(_T("%s"), pVisionAgentDlg->m_DOutputLabel[nLabel_Index].m_StrLabel); //KJT 20210422
		}
	}
}
//----------------------------------------------------------------
void CCommunicationDIODlg::SetDo(UINT nNum, BOOL bOnOff)
{
	SharedInfo::Set_Dig_Output(nNum, bOnOff);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::ChangeUI()
{
	int nLabel_Index;
	for (int k = 0; k < DIO_MODULE_SIZE; k++)
	{
		nLabel_Index = (m_nCardNoDI * DIO_MODULE_SIZE) + k;
		m_staticDI[k].SetWindowTextW(m_strDI_Label[nLabel_Index]);

		nLabel_Index = (m_nCardNoDO * DIO_MODULE_SIZE) + k;
		m_btnDO[k].SetWindowTextW(m_strDO_Label[nLabel_Index]);
	}
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDiPreviousBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strCardNo;
	m_nCardNoDI = m_nCardNoDI - 1;
	if (m_nCardNoDI < 0)
	{
		m_nCardNoDI = 0;
	}
	strCardNo.Format(_T("DI Card No %02d"), m_nCardNoDI);
	SetDlgItemTextW(IDC_STATIC_DI_CARD_NUM, strCardNo);
	ChangeUI();
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDiNextBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strCardNo;
	m_nCardNoDI = m_nCardNoDI + 1;
	if (m_nCardNoDI >= DI_MODULE_CNT)
	{
		m_nCardNoDI = DI_MODULE_CNT - 1;
	}
	strCardNo.Format(_T("DI Card No %02d"), m_nCardNoDI);
	SetDlgItemTextW(IDC_STATIC_DI_CARD_NUM, strCardNo);
	ChangeUI();
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoPreviousBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strCardNo;
	m_nCardNoDO = m_nCardNoDO - 1;
	if (m_nCardNoDO < 0)
	{
		m_nCardNoDO = 0;
	}
	strCardNo.Format(_T("DO Card No %02d"), m_nCardNoDO);
	SetDlgItemTextW(IDC_STATIC_DO_CARD_NUM, strCardNo);
	ChangeUI();
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoNextBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strCardNo;
	m_nCardNoDO = m_nCardNoDO + 1;
	if (m_nCardNoDO >= DO_MODULE_CNT)
	{
		m_nCardNoDO = DO_MODULE_CNT - 1;
	}
	strCardNo.Format(_T("DO Card No %02d"), m_nCardNoDO);
	SetDlgItemTextW(IDC_STATIC_DO_CARD_NUM, strCardNo);
	ChangeUI();
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nLabel_Index;
	BOOL	bIsDIO = FALSE;	
	for (int k = 0; k < DIO_MODULE_SIZE; k++)
	{
		nLabel_Index = (m_nCardNoDI * DIO_MODULE_SIZE) + k;
		bIsDIO = SharedInfo::Is_Dig_Input(nLabel_Index);
		if (bIsDIO == TRUE)
		{
			m_ledDI[k].SetBackgroundColor(GREEN);
		}
		else
		{
			m_ledDI[k].SetBackgroundColor(BTN_LAMP_OFF);
		}

		nLabel_Index = (m_nCardNoDO * DIO_MODULE_SIZE) + k;
		bIsDIO = SharedInfo::Is_Dig_Output(nLabel_Index);
		if (bIsDIO == TRUE)
		{
			m_ledDO[k].SetBackgroundColor(GREEN);
		}
		else
		{
			m_ledDO[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 0;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 1;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 2;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 3;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 4;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 5;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 6;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 7;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 8;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 9;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 10;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn12()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 11;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn13()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 12;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn14()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 13;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn15()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 14;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn16()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 15;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn17()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 16;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn18()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 17;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn19()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 18;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn20()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 19;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn21()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 20;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn22()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 21;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn23()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 22;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn24()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 23;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn25()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 24;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn26()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 25;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn27()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 26;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn28()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 27;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn29()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 28;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn30()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 29;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn31()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 30;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------
void CCommunicationDIODlg::OnBnClickedCommunicationDoBtn32()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	int nDoNum = m_nCardNoDO * DIO_MODULE_SIZE + 31;
	int nIs_DO = 0;
	nIs_DO = SharedInfo::Is_Dig_Output(nDoNum);
	SetDo(nDoNum, !nIs_DO);
}
//----------------------------------------------------------------