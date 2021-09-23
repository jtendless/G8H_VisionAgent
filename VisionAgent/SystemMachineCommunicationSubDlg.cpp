// SystemMachineSubDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "SystemMachineCommunicationSubDlg.h"
#include "afxdialogex.h"
#include "../Module/Data/SystemData.h"


// CSystemMachineCommunicationSubDlg 대화 상자

IMPLEMENT_DYNAMIC(CSystemMachineCommunicationSubDlg, CDialogEx)

CSystemMachineCommunicationSubDlg::CSystemMachineCommunicationSubDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_SYSTEM_SUB_MACHINE_COMMUNICATION_PAGE_1, pParent)
{
	Create(IDD_DLG_SYSTEM_SUB_MACHINE_COMMUNICATION_PAGE_1, pParent);
}
//------------------------------------------------------------------
CSystemMachineCommunicationSubDlg::~CSystemMachineCommunicationSubDlg()
{
}
//------------------------------------------------------------------
void CSystemMachineCommunicationSubDlg::ChangeUI()
{
	//저장된 데이터를 UI에 표시
}
//------------------------------------------------------------------
void CSystemMachineCommunicationSubDlg::ChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}
//------------------------------------------------------------------
void CSystemMachineCommunicationSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME_GANTRY_FLASH_PORT, m_stNaming_Gantry_Flash_Port);
	DDX_Control(pDX, IDC_COMBO_GANTRY_FLASH_PORT, m_cbxGantry_Flash_Port);
	DDX_Control(pDX, IDC_STATIC_NAME_MASK_FLASH_PORT, m_stNaming_Mask_Flash_Port);
	DDX_Control(pDX, IDC_COMBO_MASK_FLASH_PORT, m_cbxMask_Flash_Port);
	DDX_Control(pDX, IDC_STATIC_NAMING_BACK_FLASH_PORT, m_stNaming_Back_Light_Port);
	DDX_Control(pDX, IDC_COMBO_BACK_FLASH_PORT, m_cbxBack_Light_Port);
	DDX_Control(pDX, IDC_STATIC_NAME_LASER_DIST_PORT, m_stNaming_Laser_Dist_Port);
	DDX_Control(pDX, IDC_COMBO_LASER_DIST_PORT, m_cbxLaser_Dist_Port);
	DDX_Control(pDX, IDC_STATIC_NAME_BCR_IP, m_stNaming_BCR_IP);
	DDX_Control(pDX, IDC_EDIT_BCR_IP, m_edtBCR_IP);
	DDX_Control(pDX, IDC_STATIC_NAME_BCR_PORT, m_stNaming_BCR_Port);
	DDX_Control(pDX, IDC_EDIT_BCR_PORT, m_edtBCR_Port);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
}


BEGIN_MESSAGE_MAP(CSystemMachineCommunicationSubDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()	
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSystemMachineCommunicationSubDlg::OnBnClickedButtonSave)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSystemMachineCommunicationSubDlg 메시지 처리기
//------------------------------------------------------------------
BOOL CSystemMachineCommunicationSubDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	LOGFONT	T_Font, C_Font;
	CFont	TitleFont, CompoFont;
	
	memset(&T_Font, 0, sizeof(LOGFONT));
	T_Font.lfHeight = 20;
	T_Font.lfWeight = FW_HEAVY;
	TitleFont.CreateFontIndirect(&T_Font);

	memset(&C_Font, 0, sizeof(LOGFONT));
	C_Font.lfHeight = 15;
	C_Font.lfWeight = FW_DONTCARE;
	CompoFont.CreateFontIndirect(&C_Font);
	
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&CompoFont, TRUE);
	GetDlgItem(IDC_STATIC_TITLE_LINE)->SetFont(&CompoFont, TRUE);
	GetDlgItem(IDC_STATIC_NAME_GANTRY_FLASH)->SetFont(&CompoFont, TRUE);
	GetDlgItem(IDC_STATIC_NAME_MASK_FLASH)->SetFont(&CompoFont, TRUE);
	GetDlgItem(IDC_STATIC_NAME_BACK_FLASH)->SetFont(&CompoFont, TRUE);
	GetDlgItem(IDC_STATIC_NAME_LASER_DISTANCE)->SetFont(&CompoFont, TRUE);	
	GetDlgItem(IDC_STATIC_NAME_BCR)->SetFont(&CompoFont, TRUE);

	m_stNaming_Gantry_Flash_Port.SetFont(&CompoFont, TRUE);
	m_stNaming_Mask_Flash_Port.SetFont(&CompoFont, TRUE); 
	m_stNaming_Back_Light_Port.SetFont(&CompoFont, TRUE); 
	m_stNaming_Laser_Dist_Port.SetFont(&CompoFont, TRUE);
	m_stNaming_BCR_IP.SetFont(&CompoFont, TRUE);
	m_stNaming_BCR_Port.SetFont(&CompoFont, TRUE);

	m_cbxGantry_Flash_Port.SetFont(&CompoFont, TRUE);	
	m_cbxMask_Flash_Port.SetFont(&CompoFont, TRUE);	
	m_cbxBack_Light_Port.SetFont(&CompoFont, TRUE);	
	m_cbxLaser_Dist_Port.SetFont(&CompoFont, TRUE);	
	m_edtBCR_IP.SetFont(&CompoFont, TRUE);	
	m_edtBCR_Port.SetFont(&CompoFont, TRUE);

	m_btnSave.SetFont(&CompoFont, TRUE);

	CString strPort = _T("");
	for (int i = 0; i < 10; i++)
	{
		strPort.Format(_T("COM%d"), i + 1);
		m_cbxGantry_Flash_Port.AddString(strPort);
		m_cbxMask_Flash_Port.AddString(strPort);
		m_cbxBack_Light_Port.AddString(strPort);
		m_cbxLaser_Dist_Port.AddString(strPort);
	}
	ChangeUI();

	return TRUE; 
}
//------------------------------------------------------------------
void CSystemMachineCommunicationSubDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	int		nOffset = 5;
	CRect	Rect_Name, Rect_Line;
	CRect	Rect_Item_Title, Rect_Item_Name, Rect_Item;	
	CRect	Rect_Save_Btn;
	int		nDlg_Center_X		= cx / 2;
	int		nNaming_Height		= 25;	
	int		nSave_Btn_Size_X	= 100;
	int		nSave_Btn_Size_Y	= 50;
	int		nComp_Size_X		= (nDlg_Center_X - (nOffset * 6)) / 5;
	int		nComp_Size_Y		= nNaming_Height;

	if (GetDlgItem(IDC_STATIC_TITLE)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_TITLE_LINE)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAME_GANTRY_FLASH)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAME_GANTRY_FLASH_PORT)->GetSafeHwnd() == NULL) return;	
	if (GetDlgItem(IDC_STATIC_NAME_MASK_FLASH)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAMING_MASK_FLASH_PORT)->GetSafeHwnd() == NULL) return;		
	if (GetDlgItem(IDC_STATIC_NAME_BACK_FLASH)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAMING_BACK_FLASH_PORT)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAME_LASER_DISTANCE)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAME_LASER_DIST_PORT)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAME_BCR)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAMING_BCR_IP)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_NAMING_BCR_PORT)->GetSafeHwnd() == NULL) return;
	
	Rect_Name.left = nOffset;
	Rect_Name.top = nOffset;
	Rect_Name.right = Rect_Name.left + nComp_Size_X * 2;
	Rect_Name.bottom = Rect_Name.top + nNaming_Height;
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(Rect_Name);
	
	Rect_Line.left = Rect_Name.right + nOffset;
	Rect_Line.top = ((Rect_Name.bottom + Rect_Name.top) / 2) - 1;
	Rect_Line.right = nDlg_Center_X - nOffset;
	Rect_Line.bottom = ((Rect_Name.bottom + Rect_Name.top) / 2) + 1;
	GetDlgItem(IDC_STATIC_TITLE_LINE)->MoveWindow(Rect_Line);
	//-----------------------
	Rect_Item_Title.left	= Rect_Name.left;
	Rect_Item_Title.top		= Rect_Name.bottom + nOffset;
	Rect_Item_Title.right	= Rect_Item_Title.left + (nComp_Size_X * 3) + (nOffset * 2);
	Rect_Item_Title.bottom	= Rect_Item_Title.top + nNaming_Height;
	GetDlgItem(IDC_STATIC_NAME_GANTRY_FLASH)->MoveWindow(Rect_Item_Title);

	Rect_Item_Name.left		= Rect_Item_Title.left;
	Rect_Item_Name.top		= Rect_Item_Title.bottom + nOffset;
	Rect_Item_Name.right	= Rect_Item_Name.left + (nComp_Size_X * 1) + (nOffset * 0);
	Rect_Item_Name.bottom	= Rect_Item_Name.top + nNaming_Height;	
	m_stNaming_Gantry_Flash_Port.MoveWindow(Rect_Item_Name);

	Rect_Item.left			= Rect_Item_Name.right + nOffset;
	Rect_Item.top			= Rect_Item_Name.top;
	Rect_Item.right			= Rect_Item.left + (nComp_Size_X * 2) + (nOffset * 1);
	Rect_Item.bottom		= Rect_Item_Name.bottom;
	m_cbxGantry_Flash_Port.MoveWindow(Rect_Item);
	//-----------------
	Rect_Item_Title.top		= Rect_Item.bottom + nOffset;	
	Rect_Item_Title.bottom	= Rect_Item_Title.top + nNaming_Height;
	GetDlgItem(IDC_STATIC_NAME_MASK_FLASH)->MoveWindow(Rect_Item_Title);

	Rect_Item_Name.top		= Rect_Item_Title.bottom + nOffset;
	Rect_Item_Name.bottom	= Rect_Item_Name.top + nNaming_Height;
	m_stNaming_Mask_Flash_Port.MoveWindow(Rect_Item_Name);

	Rect_Item.top			= Rect_Item_Name.top;
	Rect_Item.bottom		= Rect_Item_Name.bottom;
	m_cbxMask_Flash_Port.MoveWindow(Rect_Item);
	//--------------
	Rect_Item_Title.top		= Rect_Item.bottom + nOffset;
	Rect_Item_Title.bottom	= Rect_Item_Title.top + nNaming_Height;
	GetDlgItem(IDC_STATIC_NAME_BACK_FLASH)->MoveWindow(Rect_Item_Title);

	Rect_Item_Name.top		= Rect_Item_Title.bottom + nOffset;
	Rect_Item_Name.bottom	= Rect_Item_Name.top + nNaming_Height;
	m_stNaming_Back_Light_Port.MoveWindow(Rect_Item_Name);

	Rect_Item.top			= Rect_Item_Name.top;
	Rect_Item.bottom		= Rect_Item_Name.bottom;
	m_cbxBack_Light_Port.MoveWindow(Rect_Item);
	//-----------------------------
	Rect_Item_Title.top = Rect_Item.bottom + nOffset;
	Rect_Item_Title.bottom = Rect_Item_Title.top + nNaming_Height;
	GetDlgItem(IDC_STATIC_NAME_LASER_DISTANCE)->MoveWindow(Rect_Item_Title);

	Rect_Item_Name.top = Rect_Item_Title.bottom + nOffset;
	Rect_Item_Name.bottom = Rect_Item_Name.top + nNaming_Height;
	m_stNaming_Laser_Dist_Port.MoveWindow(Rect_Item_Name);

	Rect_Item.top = Rect_Item_Name.top;
	Rect_Item.bottom = Rect_Item_Name.bottom;
	m_cbxLaser_Dist_Port.MoveWindow(Rect_Item);
	//-----------------------------
	Rect_Item_Title.top = Rect_Item.bottom + nOffset;
	Rect_Item_Title.bottom = Rect_Item_Title.top + nNaming_Height;
	GetDlgItem(IDC_STATIC_NAME_BCR)->MoveWindow(Rect_Item_Title);

	Rect_Item_Name.top = Rect_Item_Title.bottom + nOffset;
	Rect_Item_Name.bottom = Rect_Item_Name.top + nNaming_Height;
	m_stNaming_BCR_IP.MoveWindow(Rect_Item_Name);

	Rect_Item.top = Rect_Item_Name.top;
	Rect_Item.bottom = Rect_Item_Name.bottom;
	m_edtBCR_IP.MoveWindow(Rect_Item);

	Rect_Item_Name.top = Rect_Item_Name.bottom + nOffset;
	Rect_Item_Name.bottom = Rect_Item_Name.top + nNaming_Height;
	m_stNaming_BCR_Port.MoveWindow(Rect_Item_Name);

	Rect_Item.top = Rect_Item.bottom + nOffset;
	Rect_Item.bottom = Rect_Item.top + nNaming_Height;
	m_edtBCR_Port.MoveWindow(Rect_Item);
	//-----------------------------
	Rect_Save_Btn.left		= cx - nSave_Btn_Size_X - nOffset;
	Rect_Save_Btn.top		= cy - nSave_Btn_Size_Y - nOffset;
	Rect_Save_Btn.right		= Rect_Save_Btn.left + nSave_Btn_Size_X;
	Rect_Save_Btn.bottom	= Rect_Save_Btn.top + nSave_Btn_Size_Y;
	m_btnSave.MoveWindow(Rect_Save_Btn);
}
//------------------------------------------------------------------
void CSystemMachineCommunicationSubDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	ChangeUI();

	if (bShow)
	{
		
		//SetTimer(1, 100, NULL);
	}
	else
	{
		//KillTimer(1);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
//------------------------------------------------------------------
void CSystemMachineCommunicationSubDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
void CSystemMachineCommunicationSubDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChangeData();
}
//------------------------------------------------------------------