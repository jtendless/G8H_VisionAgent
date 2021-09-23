// VisionAgentModelDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentModelModelChangeDlg.h"
#include "VisionAgentModelModelChangeNewDlg.h"
#include "VisionAgentModelModelChangeRenameDlg.h"
#include "CIM/CimInfo.h"
#include "afxdialogex.h"



// CVisionAgentModelModelChangeDlg 대화 상자

IMPLEMENT_DYNAMIC(CVisionAgentModelModelChangeDlg, CDialogEx)

CVisionAgentModelModelChangeDlg::CVisionAgentModelModelChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_MODEL_CHANGE_DIALOG, pParent)
{
	m_bDialog_Entry = FALSE;

	Create(IDD_MODEL_SUB_MODEL_CHANGE_DIALOG, pParent);
}

CVisionAgentModelModelChangeDlg::~CVisionAgentModelModelChangeDlg()
{
}

void CVisionAgentModelModelChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CVisionAgentModelModelChangeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_BTN_NEW, &CVisionAgentModelModelChangeDlg::OnBnClickedVisonAgentModelModelChangeBtnNew)
	ON_BN_CLICKED(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_BTN_LOAD, &CVisionAgentModelModelChangeDlg::OnBnClickedVisonAgentModelModelChangeBtnLoad)
	ON_BN_CLICKED(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_BTN_RENAME, &CVisionAgentModelModelChangeDlg::OnBnClickedVisonAgentModelModelChangeBtnRename)
	ON_BN_CLICKED(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_BTN_DELETE, &CVisionAgentModelModelChangeDlg::OnBnClickedVisonAgentModelModelChangeBtnDelete)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CVisionAgentModelModelChangeDlg 메시지 처리기
BOOL CVisionAgentModelModelChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	if (!m_bDialog_Entry)
	{
		InitCtrl();
		UpdateUI();
		CString str;
		WORD wRecipeID;
#if 0
		str.Format(_T("%S"), SharedInfo::m_MachineRecipeTable.strCurrentRecipeName);
		wRecipeID = Devs::FindCurrentRecipeID(str);
		m_StaticCurrentName.SetWindowTextW(str);
		str.Format(_T("%d"), wRecipeID);
		m_EditRecipeID.SetWindowText(str);
#else

		str = Devs::FindCurrentRecipeName(SharedInfo::Active.nActiveRecipeNum);
		m_StaticCurrentName.SetWindowTextW(str);
		str.Format(_T("%d"), SharedInfo::Active.nActiveRecipeNum);
		m_EditRecipeID.SetWindowText(str);
#endif

	}

	return TRUE;
}


void CVisionAgentModelModelChangeDlg::InitCtrl()
{
	m_bDialog_Entry = TRUE;

	m_ComboModelNames.SubclassDlgItem(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_COMBO_MODEL_NAMES, this);
	m_EditNumber.SubclassDlgItem(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_EDIT_NUMBER, this);
	m_EditStickRGB.SubclassDlgItem(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_EDIT_STICK_RGB, this);
	m_EditRecipeID.SubclassDlgItem(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_EDIT_RECIPE_ID, this);
	m_StaticCurrentName.SubclassDlgItem(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_STATIC_CURRENT_NAME, this);

	InitListControlPara();
}


void CVisionAgentModelModelChangeDlg::InitListControlPara()
{
	CRect Rect;
	GetDlgItem(IDC_LIST_MODEL_RECIPE_DATA)->GetClientRect(&Rect);
	int nPreSize = (Rect.Width() - 50) / (MODEL_CHANGE_SPREAD_MAX_COL - 1);

	CImageList m_ImageList;
	CString strTeg[MODEL_CHANGE_SPREAD_MAX_COL] = { _T("ID"), _T("Name"), _T("AlignStick"), _T("Used") };
	CString strFlag[2] = { _T("True"), _T("False") };
	CString strComboData[2] = { _T("NoUse"), _T("Use") };

	INT nColSize[MODEL_CHANGE_SPREAD_MAX_COL];
	COLORREF m_BkColor[MODEL_CHANGE_SPREAD_MAX_COL];
	COLORREF m_TextColor[MODEL_CHANGE_SPREAD_MAX_COL];
	INT nInpuMethod[MODEL_CHANGE_SPREAD_MAX_COL] = { eMETHOD_NO_USE, eMETHOD_NORMAL, eMETHOD_COMBO, eMETHOD_COMBO };

	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);

	
	m_pListCtrl = new CCommonListCtrl;
	m_pListCtrl->SubclassDlgItem(IDC_LIST_MODEL_RECIPE_DATA, this);

	/// Setting
	m_pListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	for (int i = 0; i < MODEL_CHANGE_SPREAD_MAX_COL; i++)
	{
		if (i == 0)
		{
			nColSize[i] = 50;
			m_BkColor[i] = RGB(215, 215, 215);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else if (i == 1)
		{
			nColSize[i] = (int)((Rect.Width() - 60) * 0.6);
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
		else
		{
			nColSize[i] = (int)((Rect.Width() - 60) * 0.2);
			m_BkColor[i] = RGB(126, 205, 150);
			m_TextColor[i] = RGB(0, 0, 0);
		}
	}

	m_pListCtrl->SetListColumn(strTeg, nColSize, MODEL_CHANGE_SPREAD_MAX_COL, m_BkColor, m_TextColor, nInpuMethod);
	m_pListCtrl->SetColData(2, 2, strFlag);
	m_pListCtrl->SetColData(3, 2, strComboData);
	m_pListCtrl->m_nListCnt = 0;
}


void CVisionAgentModelModelChangeDlg::OnBnClickedVisonAgentModelModelChangeBtnNew()
{
	CVisionAgentModelModelChangeNewDlg NewModel;
	CFile file;
	CString str, szFilePath, strNewDirName;
	CString Str1, Str2;

	//KJT 20210228
	CString StrPrevRecipeName = _T("");
	StrPrevRecipeName = SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum);

	NewModel.DoModal();
	if (NewModel.m_bOKFlag == TRUE)
	{
		strNewDirName.Format(_T("%s"), SharedInfo::GetModelDataFolder());
		strNewDirName.AppendFormat(_T("\\%s"), NewModel.m_strNewDirName);

		CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[NewModel.m_wRecipID] = TRUE;
		strcpy_s((char*)(CimInfo::m_MachineRecipeTable.strRecipeName + (NewModel.m_wRecipID)), NewModel.m_strNewDirName.GetLength() + 1, CT2A(NewModel.m_strNewDirName));
		CimInfo::m_MachineRecipeTable.wRecipeID[NewModel.m_wRecipID] = NewModel.m_wRecipID;
		CimInfo::m_MachineRecipeTable.bIsAlignStick[NewModel.m_wRecipID] = NewModel.m_bIsAlignStick;
		CimInfo::m_MachineRecipeTable.wRecipeCount++;


		//ToDo New 일 때 Active 모델까지 바꿔야 하나? - parkcm
		SharedInfo::Active.nActiveRecipeNum = NewModel.m_wRecipID;
		SharedInfo::ActiveInfoSave();
		//SharedInfo::LoadModelData(NewModel.m_strNewDirName);

		SharedInfo::SaveRecipeTable(); //KJT 20210326

		WORD wRecipeID;
		m_StaticCurrentName.SetWindowTextW(NewModel.m_strNewDirName);
		wRecipeID = Devs::FindCurrentRecipeID(NewModel.m_strNewDirName);
		str.Format(_T("%d"), wRecipeID);
		m_EditRecipeID.SetWindowText(str);
		NewDirectoryFile(strNewDirName);

#pragma region //KJT 20210228
		CString StrDirSource = _T(""), StrDirTarget = _T(""), StrFileSource = _T(""), StrFileTarget = _T("");
		TCHAR tchPathSource[256], tchPathTarget[256];
		StrDirSource.Format(_T("%s\\%s"), SharedInfo::GetModelDataFolder(), StrPrevRecipeName);
		StrDirTarget.Format(_T("%s\\%s"), SharedInfo::GetModelDataFolder(), NewModel.m_strNewDirName);

#if 1
		StrFileSource.Format(_T("%s\\AlignPara.dat"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\AlignPara.dat"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\AtMaterialPara.dat"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\AtMaterialPara.dat"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\Glass.dat"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\Glass.dat"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\InspectionPara.dat"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\InspectionPara.dat"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\MaterialPara.dat"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\MaterialPara.dat"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\PpaPara.dat"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\PpaPara.dat"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\StretchPara.dat"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\StretchPara.dat"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);
#endif

		StrFileSource.Format(_T("%s\\AlignPara.xml"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\AlignPara.xml"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\AtMaterialPara.xml"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\AtMaterialPara.xml"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\Glass.xml"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\Glass.xml"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\InspectionPara.xml"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\InspectionPara.xml"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\MaterialPara.xml"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\MaterialPara.xml"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\PpaPara.xml"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\PpaPara.xml"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);

		StrFileSource.Format(_T("%s\\StretchPara.xml"), StrDirSource);	//wsprintf(tchPathSource, StrFileSource);
		StrFileTarget.Format(_T("%s\\StretchPara.xml"), StrDirTarget);	//wsprintf(tchPathTarget, StrFileTarget);
		::CopyFile(StrFileSource, StrFileTarget, TRUE);
#pragma endregion

		ResetListCtrl();

		str.Format(_T("Create New Recipe Ok (Model Num:%d, Name:%s)"), NewModel.m_wRecipID, NewModel.m_strNewDirName);
		Total_Msg(str);
		//AfxMessageBox(str);
	}
}


void CVisionAgentModelModelChangeDlg::OnBnClickedVisonAgentModelModelChangeBtnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString strModelName, strMsg;
	CString strActiveModelName;
	CString str;
	WORD wRecipeID;

	int nSel = m_ComboModelNames.GetCurSel();
	m_ComboModelNames.GetLBText(nSel, strModelName);
	strMsg.Format(_T("Load?"), strModelName);

	if (IDYES == AfxMessageBox(strMsg, MB_YESNO))
	{
		m_StaticCurrentName.GetWindowText(strMsg);
		if (strMsg == strModelName)
			AfxMessageBox(_T("Same Model Name"));
		else
		{
		//	pVisionAgentDlg->LoadModelData(strModelName);
			//pVisionAgentDlg->LoadManualData();
			//pVisionAgentDlg->UpdateUI();

			//strcpy_s((char*)(&CimInfo::m_MachineRecipeTable.strCurrentRecipeName), strModelName.GetLength() + 1, CT2A(strModelName));

			m_StaticCurrentName.SetWindowTextW(strModelName);
			//RedrawWindow();
#if 1
			//Devs::CimMotion.ReportCurrentRecipeBlock(&CurrentRecipeBlock);
			//Devs::CimMotion.LWWrite(CURRENT_RECIPE_BLOCK_START_ADDRESS, &CurrentRecipeBlock, sizeof(LW_LTM_CURRENT_RECIPE_BLOCK));
			//CimInfo::m_LBLTM.bMachineEventCurrentRecipeIDChangeReport = TRUE;
			//Devs::CimMotion.LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
			//Devs::CimMotion.SetT1TimeOut();
#else
			UpdateUI();
#endif
			
		//	str.Format(_T("%d"), CurrentRecipeBlock.wRecipeID);
			wRecipeID = Devs::FindCurrentRecipeID(strModelName);
			str.Format(_T("%d"), wRecipeID);
			m_EditRecipeID.SetWindowText(str);
			
			strMsg.Format(_T("RecipeNum Change %d->%d"), SharedInfo::Active.nActiveRecipeNum, wRecipeID);
			Total_Msg(strMsg);

			//KJT 20210410
			SharedInfo::Active.nActiveRecipeNum = wRecipeID;
			SharedInfo::ActiveInfoSave();
			str = Devs::FindCurrentRecipeName(wRecipeID);
			SharedInfo::LoadModelData(str);

			CURRENT_RECIPE_NUMBER_CHANGE_REPORT_BLOCK CurrentRecipeBlock;
			CurrentRecipeBlock.RecipeNumber = SharedInfo::Active.nActiveRecipeNum;
			CurrentRecipeBlock.UnitNumber = 1;
			CurrentRecipeBlock.RecipeVersionSequenceNumber = 1;
			
			CurrentRecipeBlock.RecipeText = str[1];
			CurrentRecipeBlock.RecipeText <<= 8;
			CurrentRecipeBlock.RecipeText |= str[0];

			Devs::CimMotion.ReportCurrentRecipeNumberChangeBlock(CurrentRecipeBlock);
		}

	}



	//SetSpread();
	Invalidate(FALSE);

}


void CVisionAgentModelModelChangeDlg::OnBnClickedVisonAgentModelModelChangeBtnRename() //KJT 20210410
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	CVisionAgentModelModelChangeRenameDlg *RenameModel;

	CString strModelName = _T("");
	CString strTemp = _T("");
	m_ComboModelNames.GetWindowText(strModelName);
	if (SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum) == strModelName)
	{
		AfxMessageBox(_T("It is selected Model "));
		return;
	}

	RenameModel = new CVisionAgentModelModelChangeRenameDlg(this);
	RenameModel->DoModal();

	pVisionAgentDlg->ResetModel();


	UpdateUI();
}

BOOL CVisionAgentModelModelChangeDlg::RenameDirectoryFile(CString NewDirName)
{
	CFile file;
	CString strTemp = _T("");
	CString strTemp2 = _T("");
	CString strSelectedFolderDir = _T("");
	CString strNewDirName = _T(""), strOrgDirName = _T("");
	int nPreRecipeId = -1;

	m_ComboModelNames.GetWindowText(strSelectedFolderDir);

	int nNum = 0;
	BOOL bResult = TRUE;
#pragma region //KJT 20210614 Interlock
	NewDirName.MakeUpper();

	strTemp = NewDirName.Mid(2);
	nNum = _ttoi(strTemp);

	//m_EditNo.GetWindowText(szMsg);
	//wRecipID = _ttoi(szMsg);
	//wResult = Devs::FindRecipeID(wRecipID);

	if (NewDirName.GetLength() > 6)
	{
		bResult = FALSE;
		AfxMessageBox(_T("PPID length is not 6 (ex:AA0000) !!"));
	}
	else if (NewDirName[0] < 0x41 || NewDirName[0] > 0x5A)
	{
		bResult = FALSE;
		AfxMessageBox(_T("PPID first char is not A~Z !!"));
	}
	else if (NewDirName[1] < 0x41 || NewDirName[1] > 0x5A)
	{
		bResult = FALSE;
		AfxMessageBox(_T("PPID second char is not A~Z !!"));
	}
	else if (nNum < 0 || nNum > 9999)
	{
		bResult = FALSE;
		AfxMessageBox(_T("PPID Number is not 0~9999 !!"));
	}
	//else if (wResult != -1)
	//{
	//	bResult = FALSE;
	//	AfxMessageBox(_T("Recipe Table Already Use"));
	//}
	else if (Devs::DuplicateModelNameCheck(NewDirName) == FALSE)
	{
		bResult = FALSE;
		AfxMessageBox(_T("Same Model Name Alread Used"));
	}
	if (bResult == FALSE)
		return 0;
#pragma endregion

	strNewDirName.Format(_T("%s\\%s"), SharedInfo::GetModelDataFolder(), NewDirName);

	strOrgDirName.Format(_T("%s\\%s"), SharedInfo::GetModelDataFolder(), strSelectedFolderDir);

	nPreRecipeId = Devs::FindCurrentRecipeID(strSelectedFolderDir);
	//strcpy_s((char*)(CimInfo::m_MachineRecipeTable.strRecipeName + (nPreRecipeId - 1)), strTemp2.GetLength() + 1, CT2A(strTemp2));
	strcpy_s((char*)(CimInfo::m_MachineRecipeTable.strRecipeName + (nPreRecipeId)), NewDirName.GetLength() + 1, CT2A(NewDirName)); //KJT 20210409

	file.Rename(strOrgDirName, strNewDirName);

	SharedInfo::SaveRecipeTable();  //KJT 20210410;

#pragma region //Report To Cim //KJT 20210409
	RECIPE_CHANGE_REPORT_BLOCK MachineRecipeBlock;
	MachineRecipeBlock.RecipeNumber = nPreRecipeId;
	MachineRecipeBlock.RecipeText = 0;
	//KJT 20210408
	MachineRecipeBlock.RecipeText = NewDirName[1];
	MachineRecipeBlock.RecipeText <<= 8;
	MachineRecipeBlock.RecipeText |= NewDirName[0];

	MachineRecipeBlock.RecipeVersionSequenceNumber = 1;
	MachineRecipeBlock.UnitNumber = 1;
	memset(MachineRecipeBlock.OperatorID, 0x20, sizeof(MachineRecipeBlock.OperatorID)); //KJT 20210410
	memcpy(MachineRecipeBlock.OperatorID, SharedInfo::OperatorID, sizeof(MachineRecipeBlock.OperatorID));
	MachineRecipeBlock.RecipeChangeType = eChangeType_Edit;  //1: Generate, 2:Edit, 3:Delete

	Devs::CimMotion.ReportRecipeChangeBlock(MachineRecipeBlock);
#pragma endregion

	return 0;
}

//모델이 있는 Directory와 파일을 를 다 지우는 함수.(디렉토리 넣는 부분 주의 할 것)
BOOL CVisionAgentModelModelChangeDlg::DeleteDirectoryFile(LPCTSTR RootDir)
{
	if (RootDir == NULL)
	{
		AfxMessageBox(_T("It's not Selected Model"));
		return FALSE;
	}

	BOOL bRval = FALSE;
	CString szRoot = _T("");

	// ÇØ´ç µð·ºÅä¸®ÀÇ ¸ðµç ÆÄÀÏÀ» °Ë»çÇÑ´Ù.
	szRoot.Format(_T("%s\\*.*"), RootDir);
	CFileFind find;
	bRval = find.FindFile(szRoot);
	if (bRval == FALSE)
	{
		return bRval;
	}
	while (bRval)
	{
		bRval = find.FindNextFile();
		// . or .. ÀÎ °æ¿ì ¹«½Ã ÇÑ´Ù.  
		if (find.IsDots() == FALSE)
		{
			// Directory ÀÏ °æ¿ì Àç±ÍÈ£Ãâ ÇÑ´Ù.
			if (find.IsDirectory())
			{
				DeleteDirectoryFile(find.GetFilePath());
			}
			// fileÀÏ °æ¿ì »èÁ¦ 
			else
			{
				SetFileAttributes(find.GetFilePath(), FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
				bRval = DeleteFile(find.GetFilePath());
			}
		}
	}
	find.Close();

	SetFileAttributes(RootDir, FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
	bRval = RemoveDirectory(RootDir);
	return bRval;
}


void CVisionAgentModelModelChangeDlg::OnBnClickedVisonAgentModelModelChangeBtnDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	//int nTemp = m_ComboModelNames.GetCurSel();
	CString strCurrentModelName;
	CString strModelName = _T("");
	CString strTemp = _T("");
	m_ComboModelNames.GetWindowText(strModelName);
	WORD wRecipID;
	strCurrentModelName = Devs::FindCurrentRecipeName(SharedInfo::Active.nActiveRecipeNum);
	if (strCurrentModelName == strModelName)
	{
		AfxMessageBox(_T("It is selected Model "));
		return;
	}

	CString strMsg = _T("");
	m_ComboModelNames.GetWindowTextW(strMsg);
	strMsg.Format(_T("Delete? %s "), strMsg);

	if (IDYES == AfxMessageBox(strMsg, MB_YESNO))
	{
#if 0
		strTemp.Format(_T("%s\\%s"), SharedInfo::GetModelDataFolder(), strModelName);


		DeleteDirectoryFile(strTemp);
		pVisionAgentDlg->ResetModel();


		UpdateUI();
		wRecipID = SharedInfo::FindCurrentRecipeNumber(strModelName);
		SharedInfo::RemoveMachineRecipeTable(wRecipID);
		//	SharedInfo::RecipeCheck();

		//LW_LTM_MACHINE_RECIPE_BLOCK MachineRecipeBlock;
		CString str;

		//::CalcMachineRecipeTabe(&MachineRecipeBlock);
		//Devs::CimMotion.LWWrite(MACHINE_RECIPE_BLOCK_START_ADDRESS, &MachineRecipeBlock, sizeof(LW_LTM_MACHINE_RECIPE_BLOCK));
		//CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport = TRUE;
		//Devs::CimMotion.LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
		//Devs::CimMotion.SetT1TimeOut();
		//Devs::CimMotion.ReportRecipeListChangeBlock(&MachineRecipeBlock);

		WORD wRecipeID;
		wRecipeID = Devs::FindCurrentRecipeID(strCurrentModelName);
		str.Format(_T("%d"), wRecipeID);
		m_EditRecipeID.SetWindowText(str);
		//strcpy_s((char*)(&CimInfo::m_MachineRecipeTable.strCurrentRecipeName), strCurrentModelName.GetLength() + 1, CT2A(strCurrentModelName));
		ResetListCtrl();
#else //KJT 20210408
		strTemp.Format(_T("%s\\%s"), SharedInfo::GetModelDataFolder(), strModelName);
		wRecipID = SharedInfo::FindCurrentRecipeNumber(strModelName);

		//Delete
		DeleteDirectoryFile(strTemp);
		pVisionAgentDlg->ResetModel();

		UpdateUI();

		SharedInfo::RemoveMachineRecipeTable(wRecipID);

		CString str;

		WORD wRecipeID;
		wRecipeID = Devs::FindCurrentRecipeID(strCurrentModelName);
		str.Format(_T("%d"), wRecipeID);
		m_EditRecipeID.SetWindowText(str);
		//strcpy_s((char*)(&SharedInfo::m_MachineCameraRecipeTable.strCurrentRecipeName), strCurrentModelName.GetLength() + 1, CT2A(strCurrentModelName));
		ResetListCtrl();

		strTemp.Format(_T("%s\\%s"), SharedInfo::GetModelDataFolder(), strModelName);
		wRecipID = SharedInfo::FindCurrentRecipeNumber(strModelName);

#pragma region //Cim Report //KJT 20210410
		RECIPE_CHANGE_REPORT_BLOCK MachineRecipeBlock;
		memset(&MachineRecipeBlock, 0x0, sizeof(MachineRecipeBlock));
		MachineRecipeBlock.RecipeNumber = wRecipID;

		//KJT 20210408
		MachineRecipeBlock.RecipeText = strModelName[1];
		MachineRecipeBlock.RecipeText <<= 8;
		MachineRecipeBlock.RecipeText |= strModelName[0];

		MachineRecipeBlock.RecipeVersionSequenceNumber = 1; //KJT 20210409
		MachineRecipeBlock.UnitNumber = 1;
		MachineRecipeBlock.RecipeChangeType = eChangeType_Delete; //1: Generate, 2:Edit, 3:Delete
		memset(MachineRecipeBlock.OperatorID, 0x20, sizeof(MachineRecipeBlock.OperatorID)); //KJT 20210410
		memcpy(MachineRecipeBlock.OperatorID, SharedInfo::OperatorID, sizeof(MachineRecipeBlock.OperatorID));

		Devs::CimMotion.ReportRecipeChangeBlock(MachineRecipeBlock);
#pragma endregion
#endif
	}

	strMsg.Format(_T("Model Delete Ok (Model Num:%d, Name:%s)"), wRecipID, strModelName);
	Total_Msg(strMsg);
	//AfxMessageBox(strMsg);

	UpdateUI(); //KJT 20210328

	Invalidate(FALSE);
}


void CVisionAgentModelModelChangeDlg::SetInitListCtrl()
{
	CString szMsg[MODEL_CHANGE_SPREAD_MAX_COL] = { _T(""), };
	m_pListCtrl->DeleteAllListData();
	for (int i = 0; i < MAX_RECIPE_COUNT; i++)
	{
		for (int j = 0; j < MODEL_CHANGE_SPREAD_MAX_COL; j++)
		{
			szMsg[j] = _T("");
		}
		szMsg[0].Format(_T("%d"), i);

		if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] == 1)
		{
			szMsg[1].Format(_T("%S"), CimInfo::m_MachineRecipeTable.strRecipeName[i]);
		}

		if (CimInfo::m_MachineRecipeTable.bIsAlignStick[i])
			szMsg[2].Format(_T("True"));
		else
			szMsg[2].Format(_T("False"));

		if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i])
			szMsg[3].Format(_T("Use"));
		else
			szMsg[3].Format(_T("NoUse"));

		m_pListCtrl->AddListData(i, szMsg);
	}
}


void CVisionAgentModelModelChangeDlg::ResetListCtrl()
{
	CString szMsg[MODEL_CHANGE_SPREAD_MAX_COL] = { _T(""), };
	for (int i = 0; i < MAX_RECIPE_COUNT; i++)
	{
		for (int j = 0; j < MODEL_CHANGE_SPREAD_MAX_COL; j++)
		{
			szMsg[j] = _T("");
		}
		szMsg[0].Format(_T("%d"), i);

		if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] == 1)
		{
			szMsg[1].Format(_T("%S"), CimInfo::m_MachineRecipeTable.strRecipeName[i]);

			if (CimInfo::m_MachineRecipeTable.bIsAlignStick[i])
				szMsg[2].Format(_T("True"));
			else
				szMsg[2].Format(_T("False"));

			if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i])
				szMsg[3].Format(_T("Use"));
			else
				szMsg[3].Format(_T("NoUse"));
		}

		m_pListCtrl->UpdateListData(i, szMsg);
	}
}


void CVisionAgentModelModelChangeDlg::GetListCtrl()
{
	CFile file;
	CRect rect;
	CString szMsg;

	for (int i = 0; i < MAX_RECIPE_COUNT; i++)
	{
		szMsg = m_pListCtrl->GetItemText(i, 0);
		CimInfo::m_MachineRecipeTable.wRecipeID[i] = _ttoi(szMsg);

		szMsg = m_pListCtrl->GetItemText(i, 1);
		memcpy((char*)CimInfo::m_MachineRecipeTable.strRecipeName[i], (char*)CT2CA(szMsg), 100);

		szMsg = m_pListCtrl->GetItemText(i, 2);
		if (szMsg.Compare(_T("TRUE")))
			CimInfo::m_MachineRecipeTable.bIsAlignStick[i] = TRUE;
		else
			CimInfo::m_MachineRecipeTable.bIsAlignStick[i] = FALSE;

		szMsg = m_pListCtrl->GetItemText(i, 3);
		if (szMsg.Compare(_T("Use")))
		{
			CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] = FALSE;
		}
		else
		{
			CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] = TRUE;
		}

		if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] == FALSE && CimInfo::m_MachineRecipeTable.wRecipeID[i] != 0)
		{
			szMsg.Format(_T("%S"), CimInfo::m_MachineRecipeTable.strRecipeName[i]);
			CimInfo::m_MachineRecipeTable.wRecipeID[i] = 0;
			CimInfo::m_MachineRecipeTable.bIsAlignStick[i] = FALSE;
			memset(CimInfo::m_MachineRecipeTable.strRecipeName[i], 0x0, 100);
		}
	}

	SharedInfo::SaveRecipeTable(); //KJT 20210328

}


BOOL CVisionAgentModelModelChangeDlg::NewDirectoryFile(LPCTSTR RootDir)
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	if (RootDir == NULL)
	{
		return FALSE;
	}

	BOOL bRval = FALSE;

	bRval = CreateDirectory(RootDir, NULL);

	if (bRval)
	{
		//pVisionAgentDlg->SaveNewModelData(RootDir);
		//Manual Data는 System처럼 동작하도록 변경. 2018. 12. 23.
		//pVisionAgentDlg->SaveNewManualData(RootDir);
	}

	pVisionAgentDlg->ResetModel();


	UpdateUI();

	return bRval;
}



void CVisionAgentModelModelChangeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pListCtrl != NULL)
		delete m_pListCtrl;
}



void CVisionAgentModelModelChangeDlg::UpdateUI()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString strActiveModelName;
	CString strModelName = _T("");

	strActiveModelName = Devs::FindCurrentRecipeName(SharedInfo::Active.nActiveRecipeNum);
	m_ComboModelNames.ResetContent();
	//int Sisze = Devs::m_strModelNames.GetSize();
	//for (int i = 0; i < Devs::m_strModelNames.GetSize(); i++)
	for (int i = 0; i < MAX_RECIPE_COUNT; i++)
	{
		//CString strModelName = Devs::m_strModelNames.GetAt(i);
		if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] != TRUE)
			continue;

		strModelName.Format(_T("%S"), CimInfo::m_MachineRecipeTable.strRecipeName[i]);

		m_ComboModelNames.AddString(strModelName);
	}

	CString str;
	for (int i = 0; i < m_ComboModelNames.GetCount(); i++)
	{
		m_ComboModelNames.GetLBText(i, str);
		if (strActiveModelName == str)
		{
			m_ComboModelNames.SetCurSel(i);
			break;
		}
	}

	if (m_bDialog_Entry)
	{
		m_bDialog_Entry = !m_bDialog_Entry;
		SetInitListCtrl();
	}
	else
		ResetListCtrl();
}


void CVisionAgentModelModelChangeDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE)
	{
		UpdateUI();
	}

}
