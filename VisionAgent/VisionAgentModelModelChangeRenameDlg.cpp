// VisionAgentModelModelChangeRenameDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentModelModelChangeRenameDlg.h"
#include "VisionAgentModelModelChangeDlg.h"
#include "VisionAgentModelModelChangeNewDlg.h"

#include "afxdialogex.h"


// CVisionAgentModelModelChangeRenameDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentModelModelChangeRenameDlg, CDialogEx)

CVisionAgentModelModelChangeRenameDlg::CVisionAgentModelModelChangeRenameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisionAgentModelModelChangeNewDlg::IDD, pParent)
{
	m_pParent = (CVisionAgentModelModelChangeDlg*)pParent;
}

CVisionAgentModelModelChangeRenameDlg::~CVisionAgentModelModelChangeRenameDlg()
{
}

void CVisionAgentModelModelChangeRenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentModelModelChangeRenameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_NEW_BTN_OK, &CVisionAgentModelModelChangeRenameDlg::OnBnClickedVisonAgentModelModelChangeNewBtnOk)
	ON_BN_CLICKED(IDC_MODEL_CHANGE_NEW_CLOSE_BTN, &CVisionAgentModelModelChangeRenameDlg::OnBnClickedModelChangeNewCloseBtn)
END_MESSAGE_MAP()


// CVisionAgentModelModelChangeRenameDlg 메시지 처리기입니다.


void CVisionAgentModelModelChangeRenameDlg::OnBnClickedVisonAgentModelModelChangeNewBtnOk()
{
	CString strTemp = _T("");
	GetDlgItemText(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_NEW_EDIT_NAME, strTemp);
	m_pParent->RenameDirectoryFile(strTemp);

	CDialogEx::OnOK();
}


BOOL CVisionAgentModelModelChangeRenameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString strTemp = _T("");
	m_pParent->m_ComboModelNames.GetWindowTextW(strTemp);

	SetDlgItemTextW(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_RENAME_EDIT_BASE_MODEL, strTemp);

	//KJT 20210410
	GetDlgItem(IDC_VISON_AGENT_MODEL_MODEL_CHANGE_NEW_EDIT_NO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_NEW_MODEL_IS_ALIGN_STICK)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CVisionAgentModelModelChangeRenameDlg::OnBnClickedModelChangeNewCloseBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CDialogEx::OnCancel();
}

