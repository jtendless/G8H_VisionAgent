// VisionAgentECSSheetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentECSSheetDlg.h"
#include "afxdialogex.h"


// CVisionAgentECSSheetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentECSSheetDlg, CDialogEx)

CVisionAgentECSSheetDlg::CVisionAgentECSSheetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_ECS_SHEET_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_ECS_SHEET_DIALOG, pParent);
}

CVisionAgentECSSheetDlg::~CVisionAgentECSSheetDlg()
{
}

void CVisionAgentECSSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentECSSheetDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MATERIAL_COUNT_CHANGE_BTN, &CVisionAgentECSSheetDlg::OnBnClickedMaterialCountChangeBtn)
	ON_BN_CLICKED(IDC_MATERIAL_STATUS_CHANGE_BTN, &CVisionAgentECSSheetDlg::OnBnClickedMaterialStatusChangeBtn)
	ON_BN_CLICKED(IDC_SHEET_MOVE_IN_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetMoveInBtn)
	ON_BN_CLICKED(IDC_SHEET_MOVE_OUT_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetMoveOutBtn)
	ON_BN_CLICKED(IDC_SHEET_INFORMATION_REQUEST_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetInformationRequestBtn)
	ON_BN_CLICKED(IDC_SHEET_INFORMATION_REQUEST_BTN2, &CVisionAgentECSSheetDlg::OnBnClickedSheetInformationUpdateBtn)
	ON_BN_CLICKED(IDC_SHEET_INFORMATION_REMOVE_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetInformationRemoveBtn)
	ON_WM_DESTROY()

	ON_BN_CLICKED(IDC_MAGAZINE_PROCESS_COMPLETE_REPORT_BTN_1, &CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn1)
	ON_BN_CLICKED(IDC_MAGAZINE_PROCESS_COMPLETE_REPORT_BTN_2, &CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn2)
	ON_BN_CLICKED(IDC_MAGAZINE_PROCESS_COMPLETE_REPORT_BTN_3, &CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn3)
	ON_BN_CLICKED(IDC_MAGAZINE_PROCESS_COMPLETE_REPORT_BTN_4, &CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn4)
	ON_BN_CLICKED(IDC_MAGAZINE_PROCESS_COMPLETE_REPORT_BTN_5, &CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn5)
	ON_BN_CLICKED(IDC_MAGAZINE_PROCESS_COMPLETE_REPORT_BTN_6, &CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn6)
	ON_BN_CLICKED(IDC_MAGAZINE_DATA_REQUEST_BTN, &CVisionAgentECSSheetDlg::OnBnClickedMagazineDataRequestBtn)
	ON_BN_CLICKED(IDC_SHEET_INFORMATION_DOWNLOAD_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetInformationDownloadBtn)
	ON_BN_CLICKED(IDC_SHEET_MASK_LOAD_REQUEST_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetMaskLoadRequestBtn)
	ON_BN_CLICKED(IDC_SHEET_MASK_UNLOAD_REQUEST_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetMaskUnloadRequestBtn)
	ON_BN_CLICKED(IDC_SHEET_MASK_LOAD_COMPLETE_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetMaskLoadCompleteBtn)
	ON_BN_CLICKED(IDC_SHEET_MASK_UNLOAD_COMPLETE_BTN, &CVisionAgentECSSheetDlg::OnBnClickedSheetMaskUnloadCompleteBtn)
	ON_BN_CLICKED(IDC_MATERIAL_JUDGE_RESULT_BTN, &CVisionAgentECSSheetDlg::OnBnClickedMaterialJudgeResultBtn)
END_MESSAGE_MAP()


// CVisionAgentECSSheetDlg 메시지 처리기입니다.


BOOL CVisionAgentECSSheetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString szMsg;
	CFile file;
	szMsg.Format(_T("%s\\dat\\SheetInfo.dat"), SharedInfo::VisionAgentPath);
	if (file.Open(szMsg, CFile::modeRead) == FALSE)
		file.Open(szMsg, CFile::modeRead | CFile::modeCreate);
	file.Read(&CimInfo::JobDataA, sizeof(MATERIAL_DATA_A));
	file.Close();
	//InitSpread();
	InitList();

	SetCimUI(m_pCimListCtrl, CimInfo::SheetInfo);
	SetMahcineUI(m_pStageListCtrl, CimInfo::SheetInfo);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CVisionAgentECSSheetDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString szMsg;
	CFile file;
	if (bShow == TRUE)
	{	
	
		//SetUI(m_pStageListCtrl, CimInfo::SheetInfo);
		//SetUI(m_pCimListCtrl, CimInfo::SheetInfo);
		SetMachineList(m_pStageListCtrl, CimInfo::SheetInfo);
		SetTimer(1, 100, NULL);
	
	}
	else
		KillTimer(1);
}


void CVisionAgentECSSheetDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	SHEET_INFORMATION_BLOCK 	SheetInfo;
	memset(&SheetInfo, 0, sizeof(SheetInfo));
	if (nIDEvent == 1)
	{
		Devs::CimMotion.LWRead(SHEET_INFORMATION_DOWNLOAD_REPLY_BLOCK_START_ADDRESS, &SheetInfo, sizeof(SheetInfo));
		//Devs::CimMotion.LWRead(SHEET_INFORMATION_DOWNLOAD_REPLY_BLOCK_START_ADDRESS, &SheetInfo, sizeof(SHEET_INFORMATION_BLOCK));
		SetCimList(m_pCimListCtrl, SheetInfo);
		//SetSpread(m_Cimspread, SheetInfo);
		if (CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialSheetDataDownloadRequestReply == TRUE && SheetInfo.ReturnCode == 1)
			SetMachineList(m_pStageListCtrl, CimInfo::SheetInfo);
			//	SetSpread(m_Stagespread, CimInfo::SheetInfo);
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CVisionAgentECSSheetDlg::InitList()
{
	// SimListCtrl
	CRect Rect;
	GetDlgItem(IDC_VISION_AGENT_ECS_SHEET_CIM_LIST)->GetClientRect(&Rect);
	int nPreSize = (Rect.Width() - 100) / (ECS_SHEET_LIST_MAX_COL - 1);

	CImageList m_ImageList;
	CString strTeg[ECS_SHEET_LIST_MAX_COL] = { _T("Address"), _T("Item"), _T("Value") };
	//CString strComboData[2] = { _T("Image"), _T("Laser") };

	INT nColSize[ECS_SHEET_LIST_MAX_COL];
	COLORREF m_BkColor[ECS_SHEET_LIST_MAX_COL];
	COLORREF m_TextColor[ECS_SHEET_LIST_MAX_COL];
	INT nInpuMethod[ECS_SHEET_LIST_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE };

	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	m_pCimListCtrl = new CCommonListCtrl;
	m_pCimListCtrl->SubclassDlgItem(IDC_VISION_AGENT_ECS_SHEET_CIM_LIST, this);

	/// Setting
	m_pCimListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pCimListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	for (int i = 0; i < ECS_SHEET_LIST_MAX_COL; i++)
	{
		if (i == 0)
		{
			nColSize[i] = 100;
			m_BkColor[i] = RGB(215, 215, 215);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else
		{
			nColSize[i] = nPreSize;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
	}

	m_pCimListCtrl->SetListColumn(strTeg, nColSize, ECS_SHEET_LIST_MAX_COL, m_BkColor, m_TextColor, nInpuMethod);
	//m_pSimListCtrl->SetColData(3, 2, strComboData);
	m_pCimListCtrl->m_nListCnt = 0;

	// StageListCtrl
	//CRect Rect;
	GetDlgItem(IDC_VISION_AGENT_ECS_SHEET_STAGE_LIST)->GetClientRect(&Rect);
	//int nPreSize = (Rect.Width() - 50) / (FLATNESS_SPREAD_MAX_COL - 1);

	//CImageList m_ImageList;
	//CString strTeg[FLATNESS_SPREAD_MAX_COL] = { _T("No"), _T("PosX"), _T("PosY"), _T("Tool"), _T("Axis"), _T("Ring"), _T("nThreshold"), _T("ResultZ") };
	//CString strComboData[2] = { _T("Image"), _T("Laser") };

	//INT nColSize[FLATNESS_SPREAD_MAX_COL];
	//COLORREF m_BkColor[FLATNESS_SPREAD_MAX_COL];
	//COLORREF m_TextColor[FLATNESS_SPREAD_MAX_COL];
	//INT nInpuMethod[FLATNESS_SPREAD_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_COMBO, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL, eMETHOD_NORMAL };

	//m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	m_pStageListCtrl = new CCommonListCtrl;
	m_pStageListCtrl->SubclassDlgItem(IDC_VISION_AGENT_ECS_SHEET_STAGE_LIST, this);

	/// Setting
	m_pStageListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pStageListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	INT nStageInpuMethod[ECS_SHEET_LIST_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NORMAL };


	for (int i = 0; i < ECS_SHEET_LIST_MAX_COL; i++)
	{
		if (i == 0)
		{
			nColSize[i] = 100;
			m_BkColor[i] = RGB(215, 215, 215);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else
		{
			nColSize[i] = nPreSize;
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
	}

	m_pStageListCtrl->SetListColumn(strTeg, nColSize, ECS_SHEET_LIST_MAX_COL, m_BkColor, m_TextColor, nStageInpuMethod);
	//m_pStageListCtrl->SetColData(3, 2, strComboData);
	m_pStageListCtrl->m_nListCnt = 0;


	int nRowCount = 0;
	int nMemoryAddress;
}

void CVisionAgentECSSheetDlg::SetCimUI(CCommonListCtrl *ListCtrl, SHEET_INFORMATION_BLOCK SheetInfo)
{
	int nRowCount = 0;
	int nMemoryAddress;
	CString szMsg[ECS_SHEET_LIST_MAX_COL] = { _T(""), };
	char temp[2];
	temp[0] = 0x20;
	temp[1] = 0x20;
	WORD Temp;
	memcpy((char*)&Temp, temp, sizeof(WORD));

	ListCtrl->DeleteAllItems();

	nRowCount = ListCtrl->GetMaxListCount();

	nMemoryAddress = 0x115E4;
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("Lot SeqNo"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.LotSeqNo);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("Slot Seq No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.SlotSeqNo);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("Unit No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.UnitNo);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("Slot No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.SlotNo);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	for (int i = 0; i < 32; i++)
	{
		szMsg[0].Format(_T("0x%X"), nMemoryAddress);
		szMsg[1].Format(_T("Sheet%d ID"), i + 1);
		for (int j = 0; j < 10; j++)
		{
			if (SheetInfo.SheetID[i][j] == Temp)
				SheetInfo.SheetID[i][j] = 0x0;
		}
		szMsg[2].Format(_T("%S"), (char*)SheetInfo.SheetID[i]);
		ListCtrl->AddListData(nRowCount, szMsg);
		nMemoryAddress = nMemoryAddress + 10;
		nRowCount++;
	}


	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("ReturnCode"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.ReturnCode);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;
}


void CVisionAgentECSSheetDlg::SetMahcineUI(CCommonListCtrl *ListCtrl, SHEET_INFORMATION_BLOCK SheetInfo)
{
	int nRowCount = 0;
	int nMemoryAddress;
	CString szMsg[ECS_SHEET_LIST_MAX_COL] = { _T(""), };
	char temp[2];
	temp[0] = 0x20;
	temp[1] = 0x20;
	WORD Temp;
	memcpy((char*)&Temp, temp, sizeof(WORD));

	ListCtrl->DeleteAllItems();

	nRowCount = ListCtrl->GetMaxListCount();

	nMemoryAddress = 1;
	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("Lot SeqNo"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.LotSeqNo);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("Slot Seq No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.SlotSeqNo);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("Unit No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.UnitNo);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("Slot No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.SlotNo);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	for (int i = 0; i < 32; i++)
	{
		szMsg[0].Format(_T("%d"), nMemoryAddress);
		szMsg[1].Format(_T("Sheet%d ID"), i + 1);
		for (int j = 0; j < 10; j++)
		{
			if (SheetInfo.SheetID[i][j] == Temp)
				SheetInfo.SheetID[i][j] = 0x0;
		}
		szMsg[2].Format(_T("%S"), (char*)SheetInfo.SheetID[i]);
		ListCtrl->AddListData(nRowCount, szMsg);
		nMemoryAddress = nMemoryAddress + 1;
		nRowCount++;
	}


	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("ReturnCode"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.ReturnCode);
	ListCtrl->AddListData(nRowCount, szMsg);
	nRowCount++;
}

void CVisionAgentECSSheetDlg::SetCimList(CCommonListCtrl *ListCtrl, SHEET_INFORMATION_BLOCK SheetInfo)
{
	int nRowCount = 0;
	int nMemoryAddress;
	CString szMsg[ECS_SHEET_LIST_MAX_COL] = { _T(""), };
	char temp[2];
	temp[0] = 0x20;
	temp[1] = 0x20;
	WORD Temp;
	memcpy((char*)&Temp, temp, sizeof(WORD));

	//ListCtrl->DeleteAllItems();

	//nRowCount = ListCtrl->GetMaxListCount();

	nMemoryAddress = 0x115E4;
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("Lot SeqNo"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.LotSeqNo);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("Slot Seq No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.SlotSeqNo);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("Unit No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.UnitNo);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("Slot No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.SlotNo);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	for (int i = 0; i < 32; i++)
	{
		szMsg[0].Format(_T("0x%X"), nMemoryAddress);
		szMsg[1].Format(_T("Sheet%d ID"), i + 1);
		for (int j = 0; j < 10; j++)
		{
			if (SheetInfo.SheetID[i][j] == Temp)
				SheetInfo.SheetID[i][j] = 0x0;
		}
		szMsg[2].Format(_T("%S"), SheetInfo.SheetID[i]);
		//ListCtrl->AddListData(nRowCount, szMsg);
		//ListCtrl->UpdateListData(nRowCount, szMsg);
		ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
		ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
		ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
		nMemoryAddress = nMemoryAddress + 10;
		nRowCount++;
	}
	
		
	szMsg[0].Format(_T("0x%X"), nMemoryAddress);
	szMsg[1].Format(_T("ReturnCode"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.ReturnCode);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;
}


void CVisionAgentECSSheetDlg::SetMachineList(CCommonListCtrl *ListCtrl, SHEET_INFORMATION_BLOCK SheetInfo)
{
	int nRowCount = 0;
	int nMemoryAddress;
	CString szMsg[ECS_SHEET_LIST_MAX_COL] = { _T(""), };
	char temp[2];
	temp[0] = 0x20;
	temp[1] = 0x20;
	WORD Temp;
	memcpy((char*)&Temp, temp, sizeof(WORD));

	//ListCtrl->DeleteAllItems();

	//nRowCount = ListCtrl->GetMaxListCount();

	nMemoryAddress = 1;
	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("Lot SeqNo"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.LotSeqNo);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("Slot Seq No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.SlotSeqNo);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("Unit No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.UnitNo);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("Slot No"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.SlotNo);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;

	nMemoryAddress = nMemoryAddress + 1;
	for (int i = 0; i < 32; i++)
	{
		szMsg[0].Format(_T("%d"), nMemoryAddress);
		szMsg[1].Format(_T("Sheet%d ID"), i + 1);
		for (int j = 0; j < 10; j++)
		{
			if (SheetInfo.SheetID[i][j] == Temp)
				SheetInfo.SheetID[i][j] = 0x0;
		}
		szMsg[2].Format(_T("%S"), (char*)SheetInfo.SheetID[i]);
		//ListCtrl->AddListData(nRowCount, szMsg);
		//ListCtrl->UpdateListData(nRowCount, szMsg);
		ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
		ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
		ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
		nMemoryAddress = nMemoryAddress + 1;
		nRowCount++;
	}


	szMsg[0].Format(_T("%d"), nMemoryAddress);
	szMsg[1].Format(_T("ReturnCode"));
	szMsg[2].Format(_T("%d"), (char*)SheetInfo.ReturnCode);
	//ListCtrl->AddListData(nRowCount, szMsg);
	//ListCtrl->UpdateListData(nRowCount, szMsg);
	ListCtrl->SetItemTextEx(nRowCount, 0, szMsg[0]);
	ListCtrl->SetItemTextEx(nRowCount, 1, szMsg[1]);
	ListCtrl->SetItemTextEx(nRowCount, 2, szMsg[2]);
	nRowCount++;
}


void CVisionAgentECSSheetDlg::OnBnClickedMaterialCountChangeBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
		
	if (IDOK != AfxMessageBox(_T("Material Count Change Report?"), MB_OKCANCEL)) return;
	MATERIAL_COUNT_CHANGE_REPORT_BLOCK MaterialCountChangeBlock;

	memset(&MaterialCountChangeBlock, 0x0, sizeof(LW_LTM_MATERIAL_COUNT_MACHINE_BLOCK));
	GetDlgItem(IDC_MATERIAL_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)MaterialCountChangeBlock.MaterialID, szMsg.GetLength() + 1, CT2A(szMsg));
	GetDlgItem(IDC_MATERIAL_COUNT_CHANGE_EDIT)->GetWindowText(szMsg);
	
	MaterialCountChangeBlock.MaterialCount = _ttoi(szMsg);
	MaterialCountChangeBlock.SlotNumber = 1;
	MaterialCountChangeBlock.UnitNumber = 1;

	Devs::CimMotion.ReportMaterialCountBlock(&MaterialCountChangeBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedMaterialStatusChangeBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Material Status Change Report?"), MB_OKCANCEL)) return;

	GetDlgItem(IDC_MATERIAL_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SharedInfo::MaterialStatus.MaterialID, szMsg.GetLength() + 1, CT2A(szMsg));
	GetDlgItem(IDC_MATERIAL_STATUS_EDIT)->GetWindowText(szMsg);
	SharedInfo::MaterialStatus.MaterialStatus = _ttoi(szMsg);
	SharedInfo::MaterialStatus.UnitNumber = 1;
	SharedInfo::MaterialStatus.UnloadingCode = 1;
	SharedInfo::MaterialStatus.MaterialType = 4;
	SharedInfo::MaterialStatus.SlotNumber = 1;
	SharedInfo::MaterialStatus.TankID[0] = 'ta';
	SharedInfo::MaterialStatus.TankID[1] = 'nk';
	SharedInfo::MaterialStatus.TankID[2] = 'id';
	SharedInfo::MaterialStatus.TankID[3] = '\r';

	Devs::CimMotion.ReportMaterialStatusBlock(&SharedInfo::MaterialStatus);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetMoveInBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString szMsg;
	SHEET_MOVE_IN_REPORT_BLOCK SheetMoveInBlock;
	if (IDOK != AfxMessageBox(_T("Sheet Move In Report?"), MB_OKCANCEL)) return;

	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetMoveInBlock.SheetID, szMsg.GetLength() + 1, CT2A(szMsg));
	GetDlgItem(IDC_SHEET_MAGAZINE_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetMoveInBlock.SheetMagazineID, szMsg.GetLength() + 1, CT2A(szMsg));
	GetDlgItem(IDC_SHEET_MAGAZINE_SLOT_NO_EDIT)->GetWindowText(szMsg);
	SheetMoveInBlock.SheetMagazineSlotNumber = _ttoi(szMsg);
	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetMoveInBlock.SheetCassetteID, szMsg.GetLength() + 1, CT2A(szMsg));
	
	Devs::CimMotion.ReportSheetMoveInBlock(SheetMoveInBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetMoveOutBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	SHEET_MOVE_OUT_REPORT_BLOCK SheetMoveOutBlock;
	if (IDOK != AfxMessageBox(_T("Sheet Move Out Report?"), MB_OKCANCEL)) return;

	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetMoveOutBlock.SheetID, szMsg.GetLength() + 1, CT2A(szMsg));
	GetDlgItem(IDC_SHEET_MAGAZINE_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetMoveOutBlock.SheetMagazineID, szMsg.GetLength() + 1, CT2A(szMsg));
	GetDlgItem(IDC_SHEET_MAGAZINE_SLOT_NO_EDIT)->GetWindowText(szMsg);
	SheetMoveOutBlock.SheetMagazineSlotNumber = _ttoi(szMsg);
	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetMoveOutBlock.SheetCassetteID, szMsg.GetLength() + 1, CT2A(szMsg));

	Devs::CimMotion.ReportSheetMoveOutBlock(SheetMoveOutBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetInformationRequestBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	SHEET_INFORMATION_BLOCK SheetInformationRequestBlock;
	if (IDOK != AfxMessageBox(_T("Sheet Information Request?"), MB_OKCANCEL)) return;

	
	GetDlgItem(IDC_SHEET_LOT_SEQ_EDIT)->GetWindowText(szMsg);
	SheetInformationRequestBlock.LotSeqNo = _ttoi(szMsg);

	GetDlgItem(IDC_SHEET_SLOT_SEQ_EDIT)->GetWindowText(szMsg);
	SheetInformationRequestBlock.SlotSeqNo = _ttoi(szMsg);

	GetDlgItem(IDC_SHEET_UNIT_NO_EDIT)->GetWindowText(szMsg);
	SheetInformationRequestBlock.UnitNo= _ttoi(szMsg);
	GetDlgItem(IDC_SHEET_SLOT_NO_EDIT)->GetWindowText(szMsg);
	SheetInformationRequestBlock.SlotNo = _ttoi(szMsg);
	
	Devs::CimMotion.RequestSheetInformation(&SheetInformationRequestBlock);
}

char* CVisionAgentECSSheetDlg::ConvertPlcString(CString strData)
{
	char cTemp[100];
	memset(cTemp, 0x00, sizeof(cTemp));
	sprintf(cTemp, "%s", (char*)CT2CA(strData));
	return cTemp;
}

void CVisionAgentECSSheetDlg::GetMachineList(CCommonListCtrl *ListCtrl, PSHEET_INFORMATION_BLOCK pSheetInfo)
{
	CString szMsg, szMsgTmp;
	char StringValue[20];
	int nValue;
	int TextCnt = 0;
	int RowCnt = 0;

	szMsg = ListCtrl->GetItemText(RowCnt, 2);
	pSheetInfo->LotSeqNo = _ttoi(szMsg);
	RowCnt++;
	
	szMsg = ListCtrl->GetItemText(RowCnt, 2);
	pSheetInfo->SlotSeqNo = _ttoi(szMsg);
	RowCnt++;
	
	 szMsg = ListCtrl->GetItemText(RowCnt, 2);
	pSheetInfo->UnitNo = _ttoi(szMsg);
	RowCnt++;
	
	 szMsg = ListCtrl->GetItemText(RowCnt, 2);
	pSheetInfo->SlotNo = _ttoi(szMsg);
	RowCnt++;

	for (int i = 0; i < 32; i++)
	{
		 szMsg = ListCtrl->GetItemText(RowCnt, 2);
		memcpy((char*)pSheetInfo->SheetID[i], ConvertPlcString(szMsg), 20);
		RowCnt++;
	}

	 szMsg = ListCtrl->GetItemText(RowCnt, 2);
	pSheetInfo->ReturnCode = _ttoi(szMsg);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetInformationUpdateBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	CString szMsg;
	METERIAL_SHEET_DATA_UPDATE_REPORT_BLOCK SheetInfo;
	if (IDOK != AfxMessageBox(_T("Sheet Data Update?"), MB_OKCANCEL)) return;


	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetInfo.Sheet_10ID, szMsg.GetLength() + 1, CT2A(szMsg));
	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetInfo.MaskID, szMsg.GetLength() + 1, CT2A(szMsg));
	SheetInfo.Sheet_10PositionNo = 1;


	GetDlgItem(IDC_SHEET_UNIT_NO_EDIT)->GetWindowText(szMsg);
	SheetInfo.UnitNumber = _ttoi(szMsg);
	GetDlgItem(IDC_SHEET_SLOT_NO_EDIT)->GetWindowText(szMsg);
	SheetInfo.SlotNumber = _ttoi(szMsg);

	Devs::CimMotion.UpdateSheetInformation(SheetInfo);


}


void CVisionAgentECSSheetDlg::OnBnClickedSheetInformationRemoveBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SHEET_INFORMATION_BLOCK SheetInformationRequestBlock;
	if (IDOK != AfxMessageBox(_T("Sheet Information Remove?"), MB_OKCANCEL)) return;

	Devs::CimMotion.RemoveSheetInformation();
}


void CVisionAgentECSSheetDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pCimListCtrl != NULL)
		delete m_pCimListCtrl;
	if (m_pStageListCtrl != NULL)
		delete m_pStageListCtrl;
}

void CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Magazine Process Complete Report #1?"), MB_OKCANCEL)) return;

	MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteReportSubBlock;
	MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteReportBlock;

	memset(&MagazineProcessCompleteReportSubBlock, 0x0, sizeof(MagazineProcessCompleteReportSubBlock));
	memset(&MagazineProcessCompleteReportBlock, 0x0, sizeof(MagazineProcessCompleteReportBlock));

	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportSubBlock.MaterialCassetteID, ConvertPlcString(szMsg), 20);


	GetDlgItem(IDC_SHEET_MAGAZINE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialMagazineID, ConvertPlcString(szMsg), 20);
	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialSheetID_1, ConvertPlcString(szMsg), 20);
	MagazineProcessCompleteReportBlock.MaterialSheetType_1 = 2;
	MagazineProcessCompleteReportBlock.MaterialSheetJudgeResult_1 = 1;
	Devs::CimMotion.ReportMagazineProcessCompleteBlock_1(MagazineProcessCompleteReportBlock, MagazineProcessCompleteReportSubBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Magazine Process Complete Report #2?"), MB_OKCANCEL)) return;



	MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteReportSubBlock;
	MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteReportBlock;

	memset(&MagazineProcessCompleteReportSubBlock, 0x0, sizeof(MagazineProcessCompleteReportSubBlock));
	memset(&MagazineProcessCompleteReportBlock, 0x0, sizeof(MagazineProcessCompleteReportBlock));

	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportSubBlock.MaterialCassetteID, ConvertPlcString(szMsg), 20);


	GetDlgItem(IDC_SHEET_MAGAZINE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialMagazineID, ConvertPlcString(szMsg), 20);
	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialSheetID_1, ConvertPlcString(szMsg), 20);
	MagazineProcessCompleteReportBlock.MaterialSheetType_2 = 2;
	MagazineProcessCompleteReportBlock.MaterialSheetJudgeResult_2 = 1;
	Devs::CimMotion.ReportMagazineProcessCompleteBlock_2(MagazineProcessCompleteReportBlock, MagazineProcessCompleteReportSubBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Magazine Process Complete Report #1?"), MB_OKCANCEL)) return;


	MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteReportSubBlock;
	MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteReportBlock;

	memset(&MagazineProcessCompleteReportSubBlock, 0x0, sizeof(MagazineProcessCompleteReportSubBlock));
	memset(&MagazineProcessCompleteReportBlock, 0x0, sizeof(MagazineProcessCompleteReportBlock));

	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportSubBlock.MaterialCassetteID, ConvertPlcString(szMsg), 20);


	GetDlgItem(IDC_SHEET_MAGAZINE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialMagazineID, ConvertPlcString(szMsg), 20);
	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialSheetID_1, ConvertPlcString(szMsg), 20);
	MagazineProcessCompleteReportBlock.MaterialSheetType_3 = 2;
	MagazineProcessCompleteReportBlock.MaterialSheetJudgeResult_3 = 1;
	Devs::CimMotion.ReportMagazineProcessCompleteBlock_3(MagazineProcessCompleteReportBlock, MagazineProcessCompleteReportSubBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Magazine Process Complete Report #1?"), MB_OKCANCEL)) return;


	MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteReportSubBlock;
	MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteReportBlock;

	memset(&MagazineProcessCompleteReportSubBlock, 0x0, sizeof(MagazineProcessCompleteReportSubBlock));
	memset(&MagazineProcessCompleteReportBlock, 0x0, sizeof(MagazineProcessCompleteReportBlock));

	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportSubBlock.MaterialCassetteID, ConvertPlcString(szMsg), 20);


	GetDlgItem(IDC_SHEET_MAGAZINE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialMagazineID, ConvertPlcString(szMsg), 20);
	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialSheetID_1, ConvertPlcString(szMsg), 20);
	MagazineProcessCompleteReportBlock.MaterialSheetType_4 = 2;
	MagazineProcessCompleteReportBlock.MaterialSheetJudgeResult_4 = 1;
	Devs::CimMotion.ReportMagazineProcessCompleteBlock_4(MagazineProcessCompleteReportBlock, MagazineProcessCompleteReportSubBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Magazine Process Complete Report #1?"), MB_OKCANCEL)) return;

	MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteReportSubBlock;
	MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteReportBlock;

	memset(&MagazineProcessCompleteReportSubBlock, 0x0, sizeof(MagazineProcessCompleteReportSubBlock));
	memset(&MagazineProcessCompleteReportBlock, 0x0, sizeof(MagazineProcessCompleteReportBlock));

	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportSubBlock.MaterialCassetteID, ConvertPlcString(szMsg), 20);

	
	GetDlgItem(IDC_SHEET_MAGAZINE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialMagazineID, ConvertPlcString(szMsg), 20);
	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialSheetID_1, ConvertPlcString(szMsg), 20);
	MagazineProcessCompleteReportBlock.MaterialSheetType_5 = 2;
	MagazineProcessCompleteReportBlock.MaterialSheetJudgeResult_5 = 1;
	Devs::CimMotion.ReportMagazineProcessCompleteBlock_5(MagazineProcessCompleteReportBlock, MagazineProcessCompleteReportSubBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedMagazineProcessCompleteReportBtn6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Magazine Process Complete Report #1?"), MB_OKCANCEL)) return;


	MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteReportSubBlock;
	MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteReportBlock;

	memset(&MagazineProcessCompleteReportSubBlock, 0x0, sizeof(MagazineProcessCompleteReportSubBlock));
	memset(&MagazineProcessCompleteReportBlock, 0x0, sizeof(MagazineProcessCompleteReportBlock));

	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportSubBlock.MaterialCassetteID, ConvertPlcString(szMsg), 20);


	GetDlgItem(IDC_SHEET_MAGAZINE_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialMagazineID, ConvertPlcString(szMsg), 20);
	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	memcpy((char*)MagazineProcessCompleteReportBlock.MaterialSheetID_1, ConvertPlcString(szMsg), 20);
	MagazineProcessCompleteReportBlock.MaterialSheetType_5 = 2;
	MagazineProcessCompleteReportBlock.MaterialSheetJudgeResult_5 = 1;
	Devs::CimMotion.ReportMagazineProcessCompleteBlock_6(MagazineProcessCompleteReportBlock, MagazineProcessCompleteReportSubBlock);

}


void CVisionAgentECSSheetDlg::OnBnClickedMagazineDataRequestBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Magazine Data Request?"), MB_OKCANCEL)) return;


	MAGAZINE_DATA_REQUEST_BLOCK MagazineDataRequestBlock;


	GetDlgItem(IDC_SHEET_CASSETTE_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)MagazineDataRequestBlock.CassetteID, szMsg.GetLength() + 1, CT2A(szMsg));

	Devs::CimMotion.ReportMagazineDataRequestBlock(MagazineDataRequestBlock);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetInformationDownloadBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;
	MATERIAL_SHEET_DATA_DOWNLOAD_REQUEST_BLOCK SheetInfo;
	if (IDOK != AfxMessageBox(_T("Sheet Data Download?"), MB_OKCANCEL)) return;



	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);
	strcpy_s((char*)SheetInfo.MaskID, szMsg.GetLength() + 1, CT2A(szMsg));
	

	GetDlgItem(IDC_SHEET_UNIT_NO_EDIT)->GetWindowText(szMsg);
	SheetInfo.UnitNumber = _ttoi(szMsg);
	GetDlgItem(IDC_SHEET_SLOT_NO_EDIT)->GetWindowText(szMsg);
	SheetInfo.SlotNumber = _ttoi(szMsg);

	Devs::CimMotion.DownloadSheetInformation(SheetInfo);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetMaskLoadRequestBtn()
{
	// TODO: Add your control notification handler code here
	CString szMsg;
	MASK_LOAD_REQUEST_BLOCK SheetInfo;
	if (IDOK != AfxMessageBox(_T("Mask Load Request?"), MB_OKCANCEL)) return;



	GetDlgItem(IDC_SHEET_ID_EDIT)->GetWindowText(szMsg);

	memcpy(SheetInfo.MaskJobID, CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(SheetInfo.MaskJobID));
	//strcpy_s((char*)SheetInfo.MaskJobID, szMsg.GetLength() + 1, CT2A(szMsg));
	SheetInfo.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	SheetInfo.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	SheetInfo.UnitNumber = 1;
	Devs::CimMotion.MaskLoadRequestBlock(SheetInfo);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetMaskUnloadRequestBtn()
{
	// TODO: Add your control notification handler code here

	CString szMsg;
	MASK_UNLOAD_REQUEST_BLOCK SheetInfo;
	if (IDOK != AfxMessageBox(_T("Mask Unload Request?"), MB_OKCANCEL)) return;

	memcpy(SheetInfo.MaskJobID, CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(SheetInfo.MaskJobID));
	//strcpy_s((char*)SheetInfo.MaskJobID, szMsg.GetLength() + 1, CT2A(szMsg));
	SheetInfo.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	SheetInfo.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	SheetInfo.UnitNumber = 1;
	Devs::CimMotion.MaskUnloadRequestBlock(SheetInfo);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetMaskLoadCompleteBtn()
{
	// TODO: Add your control notification handler code here
	CString szMsg;
	MASK_LOAD_COMPLETED_REPORT_BLOCK SheetInfo;
	if (IDOK != AfxMessageBox(_T("Mask Load Complete?"), MB_OKCANCEL)) return;



	memcpy(SheetInfo.MaskJobID, CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(SheetInfo.MaskJobID));
	//strcpy_s((char*)SheetInfo.MaskJobID, szMsg.GetLength() + 1, CT2A(szMsg));
	SheetInfo.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	SheetInfo.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	SheetInfo.UnitNumber = 1;
	Devs::CimMotion.MaskLoadCompleteBlock(SheetInfo);
}


void CVisionAgentECSSheetDlg::OnBnClickedSheetMaskUnloadCompleteBtn()
{
	// TODO: Add your control notification handler code here
	CString szMsg;
	MASK_UNLOAD_COMPLETED_REPORT_BLOCK SheetInfo;
	if (IDOK != AfxMessageBox(_T("Mask Unload Complete?"), MB_OKCANCEL)) return;



	memcpy(SheetInfo.MaskJobID, CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(SheetInfo.MaskJobID));
	//strcpy_s((char*)SheetInfo.MaskJobID, szMsg.GetLength() + 1, CT2A(szMsg));
	SheetInfo.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	SheetInfo.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	SheetInfo.UnitNumber = 1;
	SheetInfo.UnloadingCode = 1;
	Devs::CimMotion.MaskUnoadCompleteBlock(SheetInfo);
}


void CVisionAgentECSSheetDlg::OnBnClickedMaterialJudgeResultBtn()
{
	if (IDOK != AfxMessageBox(_T("Material Judge Report?"), MB_OKCANCEL)) return;
	Devs::CimMotion.SetMaterialJudge();
}
