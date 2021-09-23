// VisionAgentECSJobManagementDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentECSJobManagementDlg.h"
#include "afxdialogex.h"


// CVisionAgentECSJobManagementDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentECSJobManagementDlg, CDialogEx)

CVisionAgentECSJobManagementDlg::CVisionAgentECSJobManagementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_ECS_JOB_MANAGEMENT_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_ECS_JOB_MANAGEMENT_DIALOG, pParent);
}

CVisionAgentECSJobManagementDlg::~CVisionAgentECSJobManagementDlg()
{
}

void CVisionAgentECSJobManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentECSJobManagementDlg, CDialogEx)
#if 1
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_ECS_JOB_DATA_REQUEST_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataRequestBtn)
	ON_BN_CLICKED(IDC_ECS_JOB_DATA_SEND_OUT_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataSendOutBtn)
	ON_BN_CLICKED(IDC_ECS_JOB_DATA_FETCHED_OUT_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataFetchedOutBtn)
	ON_BN_CLICKED(IDC_ECS_JOB_DATA_CHANGE_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataChangeBtn)
	ON_BN_CLICKED(IDC_ECS_JOB_DATA_STORED_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataStoredBtn)
	ON_BN_CLICKED(IDC_ECS_PROCESS_START_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsProcessStartBtn)
	ON_BN_CLICKED(IDC_ECS_PROCESS_END_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsProcessEndBtn)
	ON_BN_CLICKED(IDC_ECS_JOB_JUDGE_REPORT_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobJudgeReportBtn)
	ON_BN_CLICKED(IDC_ECS_PROCESS_DATA_REPORT_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsProcessDataReportBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_SAVE_ECS_JOB_DATA, &CVisionAgentECSJobManagementDlg::OnBnClickedBtnSaveEcsJobData)
#endif
	
	ON_BN_CLICKED(IDC_ECS_JOB_DATA_RECEIVE_BTN, &CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataReceiveBtn)
END_MESSAGE_MAP()


// CVisionAgentECSJobManagementDlg 메시지 처리기입니다.


BOOL CVisionAgentECSJobManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitListControlPara();
	//InitSpread();

	m_JobIDEdit.SubclassDlgItem(IDC_ECS_JOB_ID_EIDT, this);
	m_JobCodeLotSeqEdit.SubclassDlgItem(IDC_ECS_JOB_LOT_SEQ_EIDT, this);
	m_JobCodeSlotSeqEdit.SubclassDlgItem(IDC_ECS_JOB_SLOT_SEQ_EIDT, this);
	m_GlassRadio.SubclassDlgItem(IDC_ECS_GLASS_RADIO, this);
	m_GlassRadio.SetCheck(TRUE);

	Devs::CimMotion.LoadMaskJobData();
	//szMsg.Format(_T("%s\\dat\\FrameJobDataA.dat"), SharedInfo::VisionAgentPath);
	//if (file.Open(szMsg, CFile::modeRead) == FALSE)
	//	file.Open(szMsg, CFile::modeRead | CFile::modeCreate);
	//file.Read(&CimInfo::JobDataA, sizeof(MATERIAL_DATA_A));
	//file.Close();
	//Devs::CimMotion.LoadJobDataB();
	//szMsg.Format(_T("%s\\dat\\FrameJobDataB.dat"), SharedInfo::VisionAgentPath);
	//if (file.Open(szMsg, CFile::modeRead) == FALSE)
	//	file.Open(szMsg, CFile::modeRead | CFile::modeCreate);
	//file.Read(&CimdInfo::JobDataB, sizeof(MATERIAL_DATA_B));
	//file.Close();
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
#if 1

void CVisionAgentECSJobManagementDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString szMsg;
	CFile file;
	if (bShow == TRUE)
	{
	

		SetCimJobDataToListCtrl(m_pStageListCtrl, CimInfo::MaskJobData);
		//SetSpread(m_Stagespread, CimInfo::JobDataA);
		SetTimer(1, 100, NULL);
	}
	else
		KillTimer(1);
}


void CVisionAgentECSJobManagementDlg::OnTimer(UINT_PTR nIDEvent)
{
	LW_MTL_JOB_DATA_REQUEST_REPLY_BLOCK JobData;
	POSITION_JOB_BLOCK PositinJob;
	JOB_COUNT_BLOCK JobCount;
	CString szMsg;
	if (nIDEvent == 1)
	{
		memset(&PositinJob, 0x00, sizeof(PositinJob));
		GetDlgItem(IDC_ECS_JOB_LOT_SEQ_EIDT)->GetWindowText(szMsg);
		PositinJob.Position_1LotSeqNumber = _ttoi(szMsg);
		GetDlgItem(IDC_ECS_JOB_SLOT_SEQ_EIDT)->GetWindowText(szMsg);
		PositinJob.Position_1SlotSeqNumber = _ttoi(szMsg);
		JobCount.ProductJobCount = SharedInfo::m_ProductJobCount;
		JobCount.DummyJobCount = SharedInfo::m_DummyJobCount;

		Devs::CimMotion.ReportJobCntBlock(JobCount);
		Devs::CimMotion.LWWrite(POSITION_JOB_BLOCK_START_ADDRESS, &PositinJob, sizeof(PositinJob));

		//Devs::CimMotion.LWRead(JOB_DATA_REQUEST_REPLY_BLOCK_START_ADDRESS, &JobData, sizeof(LW_MTL_JOB_DATA_REQUEST_REPLY_BLOCK));

		//Devs::CimMotion.LWRead(JOB_DATA_REQUEST_REPLY_BLOCK_START_ADDRESS, &JobData, sizeof(LW_MTL_JOB_DATA_REQUEST_REPLY_BLOCK));
		
		
		//SetCimJobDataToListCtrl(m_pStageListCtrl, CimInfo::MaskJobData);
		
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CVisionAgentECSJobManagementDlg::InitListControlPara()
{
	// SimListCtrl
	CRect Rect;
	GetDlgItem(IDC_VISION_AGENT_ECS_JOB_MANAGEMENT_CIM_LIST)->GetClientRect(&Rect);
	int nPreSize = (Rect.Width() - 100) / (ECS_JOB_MANAGEMENT_LIST_MAX_COL - 1);

	CImageList m_ImageList;
	CString strTeg[ECS_JOB_MANAGEMENT_LIST_MAX_COL] = { _T("Address"), _T("Item"), _T("Value") };
	//CString strComboData[2] = { _T("Image"), _T("Laser") };

	INT nColSize[ECS_JOB_MANAGEMENT_LIST_MAX_COL];
	COLORREF m_BkColor[ECS_JOB_MANAGEMENT_LIST_MAX_COL];
	COLORREF m_TextColor[ECS_JOB_MANAGEMENT_LIST_MAX_COL];
	INT nInpuMethod[ECS_JOB_MANAGEMENT_LIST_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NO_USE };

	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	m_pCimListCtrl = new CCommonListCtrl;
	m_pCimListCtrl->SubclassDlgItem(IDC_VISION_AGENT_ECS_JOB_MANAGEMENT_CIM_LIST, this);

	/// Setting
	m_pCimListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pCimListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	for (int i = 0; i < ECS_JOB_MANAGEMENT_LIST_MAX_COL; i++)
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

	m_pCimListCtrl->SetListColumn(strTeg, nColSize, ECS_JOB_MANAGEMENT_LIST_MAX_COL, m_BkColor, m_TextColor, nInpuMethod);
	//m_pSimListCtrl->SetColData(3, 2, strComboData);
	m_pCimListCtrl->m_nListCnt = 0;

	// StageListCtrl
	//CRect Rect;
	GetDlgItem(IDC_VISION_AGENT_ECS_JOB_MANAGEMENT_STAGE_LIST)->GetClientRect(&Rect);
	//int nPreSize = (Rect.Width() - 50) / (FLATNESS_SPREAD_MAX_COL - 1);

	//CImageList m_ImageList;
	//CString strTeg[FLATNESS_SPREAD_MAX_COL] = { _T("No"), _T("PosX"), _T("PosY"), _T("Tool"), _T("Axis"), _T("Ring"), _T("nThreshold"), _T("ResultZ") };
	//CString strComboData[2] = { _T("Image"), _T("Laser") };

	//INT nColSize[FLATNESS_SPREAD_MAX_COL];
	//COLORREF m_BkColor[FLATNESS_SPREAD_MAX_COL];
	//COLORREF m_TextColor[FLATNESS_SPREAD_MAX_COL];
	INT nStageInputMethod[ECS_JOB_MANAGEMENT_LIST_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NO_USE, eMETHOD_NORMAL };

	//m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	m_pStageListCtrl = new CCommonListCtrl;
	m_pStageListCtrl->SubclassDlgItem(IDC_VISION_AGENT_ECS_JOB_MANAGEMENT_STAGE_LIST, this);

	/// Setting
	m_pStageListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pStageListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	for (int i = 0; i < ECS_JOB_MANAGEMENT_LIST_MAX_COL; i++)
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

	m_pStageListCtrl->SetListColumn(strTeg, nColSize, ECS_JOB_MANAGEMENT_LIST_MAX_COL, m_BkColor, m_TextColor, nStageInputMethod);
	//m_pStageListCtrl->SetColData(3, 2, strComboData);
	
	m_pStageListCtrl->m_nListCnt = 0;

	InitSpreadContent();
}

void CVisionAgentECSJobManagementDlg::InitSpreadContent()
{
	CRect rect;
	CString szMsg;
	USES_CONVERSION;

	int MemoryAddress;
	int RowCnt = 0;


	
	//총 Raw 수.
	for (int i = 0; i < ECS_JOB_MANAGEMENT_LIST_MAX_RAW; i++)
	{
		//m_Cimspread->SetData(i, 0, m_procsTexts.GetAt(i));
		m_pCimListCtrl->InsertItem(i, _T(""));
		szMsg.Format(_T("%d"), i + 1);
		m_pStageListCtrl->InsertItem(i, szMsg);
	}

	//m_procsTexts.Add(_T("Address"));
	//m_procsTexts.Add(_T("Item"));
	//m_procsTexts.Add(_T("Value"));

	//for (int i = 0; i < 3; i++)
	//{
	//	//m_Cimspread->SetData(i, 0, m_procsTexts.GetAt(i));
	//	m_pCimListCtrl->SetItemTextEx(0, i, m_procsTexts.GetAt(i));
	//}

	MemoryAddress = 0x18512;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("PRODID"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++; 

	MemoryAddress = MemoryAddress + 10;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("OPERID"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 5;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Lot ID"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 10;
	for (int i = 0; i < 10; i++)
	{
		
		szMsg.Format(_T("0x%X"), MemoryAddress);
		m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
		szMsg.Format(_T("PPID%2d_1"), i + 1);
		m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
		m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
		RowCnt++;
		MemoryAddress = MemoryAddress++;
		szMsg.Format(_T("0x%X"), MemoryAddress);
		m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
		szMsg.Format(_T("PPID%2d_2"), i + 1);
		m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
		m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
		RowCnt++;
		MemoryAddress = MemoryAddress++;
	}


	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Job Type"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Job ID"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 10;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Lot Sequence Number"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Slot Sequence Number"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;	

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Job Judge Code"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	
	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Job Grade Code"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;


	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Processing Flag"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Inspection Flag"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Skip Flag"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Job Size"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Tickness"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Limit Count"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Processing Count"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;


	MemoryAddress = MemoryAddress + 1;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Inspection Judge Data"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 3;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Offset X"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 5;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Offset Y"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 5;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Offset Theta"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 5;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Loading Chamber ID"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 10;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Option Value"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;

	MemoryAddress = MemoryAddress + 10;
	szMsg.Format(_T("0x%X"), MemoryAddress);
	m_pCimListCtrl->SetItemTextEx(RowCnt, 0, szMsg);
	szMsg.Format(_T("Reserved"));
	m_pCimListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	m_pStageListCtrl->SetItemTextEx(RowCnt, 1, szMsg);
	RowCnt++;


}


void CVisionAgentECSJobManagementDlg::SetCimJobDataToListCtrl(CCommonListCtrl*	Spread, MASK_JOB_DATA pJobData)
{
	CRect rect;
	CString szMsg, szMsgTmp;
	USES_CONVERSION;
	MASK_JOB_DATA JobData;
	memcpy(&JobData, &pJobData, sizeof(MASK_JOB_DATA));
	int RowCnt = 0;
	char temp[2];
	char ConvertValue[100];
	temp[0] = 0x20;
	temp[1] = 0x20;
	WORD Temp;
	int nCnt;
	memcpy((char*)&Temp, temp, sizeof(WORD));


	for (int i = 0; i < 10; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_PRODID[i] == Temp)
			JobData.MaskJobDataBlock.Mask_PRODID[i] = 0x0;
	}
	szMsg.Format(_T("%S"), (char*)JobData.MaskJobDataBlock.Mask_PRODID);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;


	for (int i = 0; i < 5; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_OperID[i] == Temp)
			JobData.MaskJobDataBlock.Mask_OperID[i] = 0x0;
	}
	szMsg.Format(_T("%S"), (char*)JobData.MaskJobDataBlock.Mask_OperID);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;


	for (int i = 0; i < 10; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_LotID[i] == Temp)
			JobData.MaskJobDataBlock.Mask_LotID[i] = 0x0;
	}
	szMsg.Format(_T("%S"), (char*)JobData.MaskJobDataBlock.Mask_LotID);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	nCnt = 0;
	for (int i = 0; i < 10; i++)
	{
		memset(ConvertValue, 0x0, sizeof(ConvertValue));
		memcpy(ConvertValue, &JobData.MaskJobDataBlock.Mask_PPID01_1 + nCnt, sizeof(JobData.MaskJobDataBlock.Mask_PPID01_1));
		szMsg.Format(_T("%S"), ConvertValue);
		Spread->SetItemTextEx(RowCnt, 2, szMsg);
		RowCnt++;
		szMsg.Format(_T("%d"), *(&JobData.MaskJobDataBlock.Mask_PPID01_2 + nCnt));
		Spread->SetItemTextEx(RowCnt, 2, szMsg);
		RowCnt++;
		nCnt += 2;
	}

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_Job_Type);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	for (int i = 0; i < 10; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_JobID[i] == Temp)
			JobData.MaskJobDataBlock.Mask_JobID[i] = 0x0;
	}
	szMsg.Format(_T("%S"), (char*)JobData.MaskJobDataBlock.Mask_JobID);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_LotSequenceNumber);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_SlotSequenceNumber);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	memset(ConvertValue, 0x0, sizeof(ConvertValue));
	memcpy(ConvertValue, &JobData.MaskJobDataBlock.Mask_JobJudgeCode, sizeof(JobData.MaskJobDataBlock.Mask_JobJudgeCode));
	szMsg.Format(_T("%S"), ConvertValue);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	memset(ConvertValue, 0x0, sizeof(ConvertValue));
	memcpy(ConvertValue, &JobData.MaskJobDataBlock.Mask_JobGradeCode, sizeof(JobData.MaskJobDataBlock.Mask_JobGradeCode));
	szMsg.Format(_T("%S"), ConvertValue);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_ProcessingFlag);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_InspectionFlag);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_SkipFlag);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_JobSize);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_JobThickness);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_LimitCount);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;


	szMsg.Format(_T("%d"), JobData.MaskJobDataBlock.Mask_ProcessingCount);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;


	for (int i = 0; i < 3; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_InspectionJudgeData[i] == Temp)
			JobData.MaskJobDataBlock.Mask_InspectionJudgeData[i] = 0x0;
	}
	szMsg.Format(_T(""));
	szMsg.Format(_T("%S"), (char*)JobData.MaskJobDataBlock.Mask_InspectionJudgeData);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	for (int i = 0; i < 5; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_OffsetX[i] == Temp)
			JobData.MaskJobDataBlock.Mask_OffsetX[i] = 0x0;
	}
	memset(ConvertValue, 0x0, sizeof(ConvertValue));
	memcpy(ConvertValue, JobData.MaskJobDataBlock.Mask_OffsetX, sizeof(JobData.MaskJobDataBlock.Mask_OffsetX));
	szMsg.Format(_T("%S"), ConvertValue);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	for (int i = 0; i < 5; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_OffsetY[i] == Temp)
			JobData.MaskJobDataBlock.Mask_OffsetY[i] = 0x0;
	}
	memset(ConvertValue, 0x0, sizeof(ConvertValue));
	memcpy(ConvertValue, JobData.MaskJobDataBlock.Mask_OffsetY, sizeof(JobData.MaskJobDataBlock.Mask_OffsetY));
	szMsg.Format(_T("%S"), ConvertValue);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	for (int i = 0; i < 5; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_OffsetTheta[i] == Temp)
			JobData.MaskJobDataBlock.Mask_OffsetTheta[i] = 0x0;
	}
	memset(ConvertValue, 0x0, sizeof(ConvertValue));
	memcpy(ConvertValue, JobData.MaskJobDataBlock.Mask_OffsetTheta, sizeof(JobData.MaskJobDataBlock.Mask_OffsetTheta));
	szMsg.Format(_T("%S"), ConvertValue);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;


	for (int i = 0; i < 10; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_LoadingChamberID[i] == Temp)
			JobData.MaskJobDataBlock.Mask_LoadingChamberID[i] = 0x0;
	}
	
	memset(ConvertValue, 0x0, sizeof(ConvertValue));
	memcpy(ConvertValue, JobData.MaskJobDataBlock.Mask_LoadingChamberID, sizeof(JobData.MaskJobDataBlock.Mask_LoadingChamberID));
	szMsg.Format(_T("%S"), ConvertValue);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	for (int i = 0; i < 10; i++)
	{
		if (JobData.MaskJobDataBlock.Mask_OptionValue[i] == Temp)
			JobData.MaskJobDataBlock.Mask_OptionValue[i] = 0x0;
	}
	memset(ConvertValue, 0x0, sizeof(ConvertValue));
	memcpy(ConvertValue, JobData.MaskJobDataBlock.Mask_OptionValue, sizeof(JobData.MaskJobDataBlock.Mask_OptionValue));
	szMsg.Format(_T("%S"), ConvertValue);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

	for (int i = 0; i < 23; i++)
	{
		if (JobData.MaskJobDataBlock.Reserved[i] == Temp)
			JobData.MaskJobDataBlock.Reserved[i] = 0x0;
	}
	szMsg.Format(_T(""));
	szMsg.Format(_T("%S"), (char*)JobData.MaskJobDataBlock.Reserved);
	Spread->SetItemTextEx(RowCnt, 2, szMsg);
	RowCnt++;

}

char* CVisionAgentECSJobManagementDlg::ConvertPlcString(CString strData)
{
	char cTemp[100];
	memset(cTemp, 0x00, sizeof(cTemp));
	sprintf(cTemp, "%s", (char*)CT2CA(strData));
	return cTemp;
}

void CVisionAgentECSJobManagementDlg::GetJobDataFromSpread(CCommonListCtrl*	Spread, PMASK_JOB_DATA pJobData)
{
	CString szMsg, szMsgTmp;
	char cTemp[100];
	INT RowCnt = 0;
	INT Cnt;
	WORD wValue[100];
	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_PRODID, ConvertPlcString(szMsg), 10);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);	
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_OperID, ConvertPlcString(szMsg), 5);
	RowCnt++;
	
	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_LotID, ConvertPlcString(szMsg), 10);
	RowCnt++;
		

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID01_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID01_1, szMsg, szMsg.GetLength());
	
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID01_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID02_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID02_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID02_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID03_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID03_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID03_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID04_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID04_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID04_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID05_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID05_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID05_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID06_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID06_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID06_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID07_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID07_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID07_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID08_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID08_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID08_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID09_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID09_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID09_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memset(&pJobData->MaskJobDataBlock.Mask_PPID10_1, 0x0, 1);
	memcpy(&pJobData->MaskJobDataBlock.Mask_PPID10_1, szMsg, szMsg.GetLength());
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_PPID10_2 = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_Job_Type = _ttoi(szMsg);
	RowCnt++;
	
	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_JobID, ConvertPlcString(szMsg), 10);
	RowCnt++;	
	
	szMsg = Spread->GetItemText(RowCnt, 2);		
	pJobData->MaskJobDataBlock.Mask_LotSequenceNumber = _ttoi(szMsg);
	RowCnt++;
	
	szMsg = Spread->GetItemText(RowCnt, 2);	
	pJobData->MaskJobDataBlock.Mask_SlotSequenceNumber = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_JobJudgeCode = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_JobGradeCode = _ttoi(szMsg);
	RowCnt++;
	
	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_ProcessingFlag = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_InspectionFlag = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_SkipFlag = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_JobSize = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_JobThickness = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_LimitCount = _ttoi(szMsg);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	pJobData->MaskJobDataBlock.Mask_ProcessingCount = _ttoi(szMsg);
	RowCnt++;

	for (int i = 0; i < 3; i++)
	{
		szMsg = Spread->GetItemText(RowCnt, 2);
		pJobData->MaskJobDataBlock.Mask_InspectionJudgeData[i] = _ttoi(szMsg);
		RowCnt++;
	}

	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_OffsetX, ConvertPlcString(szMsg), 5);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_OffsetY, ConvertPlcString(szMsg), 5);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_OffsetTheta, ConvertPlcString(szMsg), 5);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_LoadingChamberID, ConvertPlcString(szMsg), 10);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Mask_OptionValue, ConvertPlcString(szMsg), 10);
	RowCnt++;

	szMsg = Spread->GetItemText(RowCnt, 2);
	memcpy((BYTE*)pJobData->MaskJobDataBlock.Reserved, ConvertPlcString(szMsg), 23);
	RowCnt++;
}
//
//
//void CVisionAgentECSJobManagementDlg::GetSpread(TSpread*	Spread, PMATERIAL_DATA_B pJobData)
//{
//	CRect rect;
//	CString szMsg, szMsgTmp;
//	USES_CONVERSION;
//	char StringValue[20];
//	HGLOBAL hText;
//	LPTSTR strCellData;
//	int nValue;
//	int TextCnt = 0;
//	int RowCnt = 1;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	memcpy((char*)pJobData->wLotID, (char*)strCellData, 20);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	memcpy((char*)pJobData->wMeterialID, (char*)strCellData, 20);
//	RowCnt++;
//
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	memcpy((char*)pJobData->wMeterialID, (char*)strCellData, 10);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->wLotSequenceNo = _ttoi(szMsg);
//	RowCnt++;
//
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->wSlotSequenceNo = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->wMeterialJudgeCode = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->wMeterialGradeCode = _ttoi(szMsg);
//	RowCnt++;
//
//
//
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	memcpy((char*)pJobData->wProdID, (char*)strCellData, 20);
//	RowCnt++;
//
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	AfxExtractSubString(szMsgTmp, szMsg, 0, '/');
//	pJobData->wProcessingFlag[0] = _ttoi(szMsgTmp);
//	AfxExtractSubString(szMsgTmp, szMsg, 1, '/');
//	pJobData->wProcessingFlag[1] = _ttoi(szMsgTmp);
//	RowCnt++;
//
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	AfxExtractSubString(szMsgTmp, szMsg, 0, '/');
//	pJobData->wInspectionJudgeData[0] = _ttoi(szMsgTmp);
//	AfxExtractSubString(szMsgTmp, szMsg, 1, '/');
//	pJobData->wInspectionJudgeData[1] = _ttoi(szMsgTmp);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	AfxExtractSubString(szMsgTmp, szMsg, 0, '/');
//	pJobData->wSkipFlag[0] = _ttoi(szMsgTmp);
//	AfxExtractSubString(szMsgTmp, szMsg, 1, '/');
//	pJobData->wSkipFlag[1] = _ttoi(szMsgTmp);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	AfxExtractSubString(szMsgTmp, szMsg, 0, '/');
//	pJobData->wInspectionFlag[0] = _ttoi(szMsgTmp);
//	AfxExtractSubString(szMsgTmp, szMsg, 1, '/');
//	pJobData->wInspectionFlag[1] = _ttoi(szMsgTmp);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->wMode = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	AfxExtractSubString(szMsgTmp, szMsg, 0, '/');
//	pJobData->wMeterialSizeCode[0] = _ttoi(szMsgTmp);
//	AfxExtractSubString(szMsgTmp, szMsg, 1, '/');
//	pJobData->wMeterialSizeCode[1] = _ttoi(szMsgTmp);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wFirstLotMaterialCode = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wLastLotMaterial = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wDummyMaterial = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wMaterailTicknessCode = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wFirstRecipeMaterialInOneLot = _ttoi(szMsg);
//	RowCnt++;
//
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wLastRecipeMaterialInOneLot = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wAssebled = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wMaterialAngle = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wMaterialFlip = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wFirstJobMaterialInOneLot = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wLastJobMaterialInOneLot = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->unDummyDataType.Bit.wPortNoOfMaterialSuppliedForSputterNECVD = _ttoi(szMsg);
//	RowCnt++;
//
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->wProcessingCount = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	AfxExtractSubString(szMsgTmp, szMsg, 0, '.');
//	pJobData->wMaskOffsetX[0] = _ttoi(szMsgTmp);
//	AfxExtractSubString(szMsgTmp, szMsg, 1, '.');
//	pJobData->wMaskOffsetX[1] = _ttoi(szMsgTmp);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	AfxExtractSubString(szMsgTmp, szMsg, 0, '.');
//	pJobData->wMaskOffsetY[0] = _ttoi(szMsgTmp);
//	AfxExtractSubString(szMsgTmp, szMsg, 1, '.');
//	pJobData->wMaskOffsetY[1] = _ttoi(szMsgTmp);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	AfxExtractSubString(szMsgTmp, szMsg, 0, '.');
//	pJobData->wMaskOffsetT[0] = _ttoi(szMsgTmp);
//	AfxExtractSubString(szMsgTmp, szMsg, 1, '.');
//	pJobData->wMaskOffsetT[1] = _ttoi(szMsgTmp);
//	RowCnt++;
//
//
//	for (int i = 0; i < 3; i++)
//	{
//
//		
//		
//		Spread->GetData(2, RowCnt, strCellData);
//		
//		
//		AfxExtractSubString(szMsgTmp, szMsg, 0, '.');
//		pJobData->wOptionData[i][0] = _ttoi(szMsgTmp);
//		AfxExtractSubString(szMsgTmp, szMsg, 1, '.');
//		pJobData->wOptionData[i][1] = _ttoi(szMsgTmp);
//		RowCnt++;
//
//	}
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->wCoverUsedCount = _ttoi(szMsg);
//	RowCnt++;
//
//	
//	
//	Spread->GetData(2, RowCnt, strCellData);
//	
//	
//	pJobData->wHousingUsedCount = _ttoi(szMsg);
//	RowCnt++;
//
//}

void CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataRequestBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg, szMsg2;
	if (IDOK != AfxMessageBox(_T("Job Data Request?"), MB_OKCANCEL)) return;

	
	memset(&CimInfo::JobDataRequestBlock, 0x0, sizeof(MASK_JOB_DATA_REQUEST_BLOCK));
    
	char StringValue[20];
	memset(StringValue, 0x0, 20);

	m_JobIDEdit.GetWindowText(szMsg);
	if (szMsg == _T(""))
	{
		m_JobCodeLotSeqEdit.GetWindowText(szMsg);
		m_JobCodeSlotSeqEdit.GetWindowText(szMsg2);
		if (szMsg == _T("") && szMsg2 == _T(""))
		{
			AfxMessageBox(_T("Job ID/Code Field is Empty"));
			return;
		}
			
		else
		{
			if (m_GlassRadio.GetCheck() == TRUE)
			{
				CimInfo::JobDataRequestBlock.RequestOption = 4;
			}
			else
			{
				CimInfo::JobDataRequestBlock.RequestOption = 2;
			}

			CimInfo::JobDataRequestBlock.LotSequenceNumber = _ttoi(szMsg);
			CimInfo::JobDataRequestBlock.SlotSequenceNumber = _ttoi(szMsg2);
		}
	}	
	else
	{
		if (m_GlassRadio.GetCheck() == TRUE)
		{
			CimInfo::JobDataRequestBlock.RequestOption = 2;
		}
		else
		{
			CimInfo::JobDataRequestBlock.RequestOption = 1;
		}
		strcpy_s(StringValue, szMsg.GetLength() + 1, CT2A(szMsg));
		memcpy((char*)CimInfo::JobDataRequestBlock.RequestMaskJobID, StringValue, 10);
	}

	//memset(JobDataRequestBlock.RequestJobID, 0x01, sizeof(WORD) * 10);
	
	if (m_GlassRadio.GetCheck() == TRUE)
	{
		CimInfo::JobDataRequestBlock.SlotNumber = 1;
	}
	else
	{
		CimInfo::JobDataRequestBlock.SlotNumber = 1;
	}

	CimInfo::JobDataRequestBlock.UnitNumber = 1;

	Devs::CimMotion.RequestEcsJobData(CimInfo::JobDataRequestBlock);
	m_JobCodeLotSeqEdit.GetWindowText(szMsg);
	m_JobCodeSlotSeqEdit.GetWindowText(szMsg2);
	szMsg.Append(szMsg2);

	memcpy((BYTE*)CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, ConvertPlcString(szMsg), szMsg.GetLength());
	//CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID =
	Etc_Msg(_T("[Cim] Send : Job Data Request"));
}

void CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataStoredBtn()
{
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Stored Job Data Report?"), MB_OKCANCEL)) return;
	
	Devs::CimMotion.StoredEcsJobData();
}

void CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataSendOutBtn()
{
	JOB_COUNT_BLOCK JobCountBlock;
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Send Out Job Data Report?"), MB_OKCANCEL)) return;

	if (SharedInfo::m_ProductJobCount < 1)
	{
		AfxMessageBox(_T("Job Data is Empty"));
	}
	else
	{
		CimInfo::MaskJobData.MaskJobDataBlock.Mask_ProcessingCount = 0;
		CimInfo::MaskJobData.MaskJobDataBlock.Mask_ProcessingFlag += 16;						//16더해서 보고.		
		CimInfo::MaskJobData.MaskJobDataBlock.Mask_InspectionJudgeData[0] = JOB_JUDGE_GOOD;
		CimInfo::MaskJobData.MaskJobDataBlock.Mask_InspectionJudgeData[1] = 0;
		//Devs::SetJobDataAtoB(&CimInfo::JobDataA, &CimdInfo::JobDataB);

		Devs::CimMotion.m_bSentOutJobReportCompleteFlag = FALSE;
		//Devs::CimMotion.LWWrite(JOB_DATA_BLOCK_START_ADDRESS, &CimInfo::JobDataA, sizeof(MATERIAL_DATA_A));

		//SharedInfo::m_ProductJobCount = 0;
		//SharedInfo::m_DummyJobCount = 0;
		//Awking Need Check.
		SharedInfo::m_ProductJobCount = 0;
		JobCountBlock.DummyJobCount = 0;
		JobCountBlock.ProductJobCount = SharedInfo::m_ProductJobCount;

		Devs::CimMotion.ReportSentOutEcsJobData(&CimInfo::MaskJobData, JobCountBlock);

		//Devs::CimMotion.ReportSentOutEcsJobData();
	}
}


void CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataFetchedOutBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDOK != AfxMessageBox(_T("Fetched Out Job Data Report?"), MB_OKCANCEL)) return;


	Devs::CimMotion.FetchedOutEcsJobData();
}


void CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataChangeBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDOK != AfxMessageBox(_T("Job Data Change?"), MB_OKCANCEL)) return;
	
	//MATERIAL_DATA_A JobDataSendBlock;
	MASK_JOB_DATA_CHANGE_REPORT_BLOCK JobInfo;
	//2020은 PLC에서 공백.
	//memset(&JobDataSendBlock, 0x2020, sizeof(JobDataSendBlock));
	

	GetJobDataFromSpread(m_pStageListCtrl, &CimInfo::MaskJobData);

	memcpy(&JobInfo.MaskJobData, &CimInfo::MaskJobData, sizeof(JobInfo.MaskJobData));
	Devs::CimMotion.ReportJobDataChangeBlock(JobInfo);
}


void CVisionAgentECSJobManagementDlg::OnBnClickedEcsProcessStartBtn()
{
	if (IDOK != AfxMessageBox(_T("Process Start Report?"), MB_OKCANCEL)) return;

	Devs::CimMotion.SetStartProcess();
}


void CVisionAgentECSJobManagementDlg::OnBnClickedEcsProcessEndBtn()
{
	
	if (IDOK != AfxMessageBox(_T("Process End Report?"), MB_OKCANCEL)) return;
	Devs::CimMotion.SetEndProcess();
}


void CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobJudgeReportBtn()
{
	
	if (IDOK != AfxMessageBox(_T("Job Judge Report?"), MB_OKCANCEL)) return;
	Devs::CimMotion.SetJobJudge();
}



void CVisionAgentECSJobManagementDlg::OnBnClickedEcsProcessDataReportBtn()
{
	if (IDOK != AfxMessageBox(_T("Job Judge Report?"), MB_OKCANCEL)) return;
	Devs::CimMotion.SetProcessData();

}


void CVisionAgentECSJobManagementDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pCimListCtrl != NULL)
		delete m_pCimListCtrl;
	if (m_pStageListCtrl != NULL)
		delete m_pStageListCtrl;
}


void CVisionAgentECSJobManagementDlg::OnBnClickedBtnSaveEcsJobData()
{
	GetJobDataFromSpread(m_pStageListCtrl , &CimInfo::MaskJobData),
	Devs::CimMotion.SaveMaskJobData();
	
}

#endif

void CVisionAgentECSJobManagementDlg::OnBnClickedEcsJobDataReceiveBtn()
{
	// TODO: Add your control notification handler code here
	CString szMsg;
	if (IDOK != AfxMessageBox(_T("Received Job Data Report?"), MB_OKCANCEL)) return;

	Devs::CimMotion.ReceivedEcsJobData();
}
