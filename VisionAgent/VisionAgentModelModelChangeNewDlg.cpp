// VisionAgentModel_ModelChangeNewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentModelModelChangeNewDlg.h"
#include "VisionAgentModelModelChangeDlg.h"
#include "afxdialogex.h"


// CVisionAgentModelModelChangeNewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentModelModelChangeNewDlg, CDialogEx)

CVisionAgentModelModelChangeNewDlg::CVisionAgentModelModelChangeNewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisionAgentModelModelChangeNewDlg::IDD, pParent)
{
	m_pParent = (CVisionAgentModelModelChangeDlg*)pParent;

}

CVisionAgentModelModelChangeNewDlg::~CVisionAgentModelModelChangeNewDlg()
{
}

void CVisionAgentModelModelChangeNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentModelModelChangeNewDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MODEL_CHANGE_NEW_CLOSE_BTN, &CVisionAgentModelModelChangeNewDlg::OnBnClickedModelChangeNewCloseBtn)
	ON_BN_CLICKED(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_NEW_BTN_OK, &CVisionAgentModelModelChangeNewDlg::OnBnClickedVisonAgentModelModelChangeNewBtnOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CVisionAgentModelModelChangeNewDlg 메시지 처리기입니다.


BOOL CVisionAgentModelModelChangeNewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strTemp = _T("");



	
	strTemp = Devs::FindCurrentRecipeName(SharedInfo::Active.nActiveRecipeNum);
	
	
	SetDlgItemTextW(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_NEW_EDIT_NAME, strTemp);


	m_EditNo.SubclassDlgItem(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_NEW_EDIT_NO, this);
	m_checkIsAlignStick.SubclassDlgItem(IDC_CHECK_NEW_MODEL_IS_ALIGN_STICK, this);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CVisionAgentModelModelChangeNewDlg::InitCtrl()
{
	CString strTemp = _T("");

}

void CVisionAgentModelModelChangeNewDlg::InitDefaultPara()
{

}

void CVisionAgentModelModelChangeNewDlg::OnBnClickedModelChangeNewCloseBtn()
{
	m_bOKFlag = FALSE;
	CDialogEx::OnCancel();
}


void CVisionAgentModelModelChangeNewDlg::OnBnClickedVisonAgentModelModelChangeNewBtnOk()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	//LW_LTM LWLTM;
	//RECIPE_CHANGE_REPORT_BLOCK MachineRecipeBlock;
	CString strTemp = _T("");
	CString strNewDirName = _T("");
	WORD wRecipID;
	CString szMsg;
	int wResult;
	CFile file;
	m_wRecipID = -1;
	m_bIsAlignStick = 0;
	m_EditNo.GetWindowText(szMsg);
	wRecipID = _ttoi(szMsg);
	wResult = Devs::FindRecipeID(wRecipID);
	if (wResult != -1)
	{
		AfxMessageBox(_T("Recipe Table Already Use"));
	}
	else
	{

		m_bOKFlag = TRUE;
		m_wRecipID = wRecipID;
		m_bIsAlignStick = m_checkIsAlignStick.GetCheck();
		GetDlgItemTextW(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_NEW_EDIT_NAME, m_strNewDirName);

		//m_pParent->NewDirectoryFile(strTemp);

		//	CSystemData::m_Option.Info.m_strActiveModelName = strNewDirName;

#if 1
			//MachineRecipeBlock.RecipeChangeType = 1;
			//MachineRecipeBlock.RecipeNumber = wRecipID;
			//sprintf(&MachineRecipeBlock.RecipeText, m_strNewDirName,
			//memcpy(&MachineRecipeBlock.RecipeText, Devs::CimMotion.ConvertPlcString(m_strNewDirName), 1);

			//Recipe Change Report
			//MachineRecipeBlock.RecipeText = htons(MachineRecipeBlock.RecipeText);
			//Devs::CimMotion.ReportRecipeChangeBlock(MachineRecipeBlock);
#endif

	}
	CDialogEx::OnOK();
}





void CVisionAgentModelModelChangeNewDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다

}
