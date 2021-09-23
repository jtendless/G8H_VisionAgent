// VisionAgentECSDfsDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentECSDfsDlg.h"
#include "afxdialogex.h"


// CVisionAgentECSDfsDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentECSDfsDlg, CDialogEx)

CVisionAgentECSDfsDlg::CVisionAgentECSDfsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_ECS_DFS_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_ECS_DFS_DIALOG, pParent);
}

CVisionAgentECSDfsDlg::~CVisionAgentECSDfsDlg()
{
}

void CVisionAgentECSDfsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentECSDfsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CVisionAgentECSDfsDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_FILE_UPLOAD, &CVisionAgentECSDfsDlg::OnBnClickedBtnFileUpload)
	ON_BN_CLICKED(IDC_BTN_FILE_DOWNLOAD, &CVisionAgentECSDfsDlg::OnBnClickedBtnFileDownload)
	ON_BN_CLICKED(IDC_BTN_NEW_FOLDER, &CVisionAgentECSDfsDlg::OnBnClickedBtnNewFolder)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_DFS_SAVE, &CVisionAgentECSDfsDlg::OnBnClickedBtnDfsSave)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CVisionAgentECSDfsDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_GET_DIR_INFO, &CVisionAgentECSDfsDlg::OnBnClickedBtnGetDirInfo)
END_MESSAGE_MAP()


// CVisionAgentECSDfsDlg 메시지 처리기입니다.


void CVisionAgentECSDfsDlg::OnBnClickedBtnConnect()
{
	ChangeData();

	Devs::m_pDfs.SetOpen(SharedInfo::m_sDfsPara.strIpAddress, SharedInfo::m_sDfsPara.strUserId, SharedInfo::m_sDfsPara.strUserPw, 21);


}

void CVisionAgentECSDfsDlg::OnBnClickedBtnClose()
{
	Devs::m_pDfs.SetClose();
}


void CVisionAgentECSDfsDlg::OnBnClickedBtnFileUpload()
{
	BOOL bResult = FALSE;
	CFileDialog dlg(TRUE, NULL, _T("Upload File"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Image Files (All Files (*.*))|*.*||"),
		this, 0, FALSE);

	
	if (dlg.DoModal() != IDOK)		return;

	OnBnClickedBtnConnect();

	CString strPath = dlg.GetPathName();
	CString strRmtPath;

	strRmtPath = Devs::m_pDfs.GetMakeDirName(strPath);
	bResult = Devs::m_pDfs.SetUpload(strPath, strRmtPath);

}


void CVisionAgentECSDfsDlg::OnBnClickedBtnFileDownload()
{
	CFileDialog dlg(FALSE, NULL, _T("Download File"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Image Files (All Files (*.*))|*.*||"),
		this, 0, FALSE);

	if (dlg.DoModal() != IDOK)		return;

	CString strPath = dlg.GetPathName();
	CString strRmtPath;

	Devs::m_pDfs.SetDownload(strRmtPath, strPath);
}


void CVisionAgentECSDfsDlg::OnBnClickedBtnNewFolder()
{
	CFolderPickerDialog dlg;

	if (dlg.DoModal() != IDOK)		return;

	CString strPath(dlg.GetPathName());
	CString strRmtPath;

	strRmtPath = Devs::m_pDfs.GetMakeDirName(strPath);
	Devs::m_pDfs.SetCreateDirectory(strRmtPath);
}


BOOL CVisionAgentECSDfsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitItem();
	
	SharedInfo::DfsInfoRead();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CVisionAgentECSDfsDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		ChangeUi();
	}

}

BOOL CVisionAgentECSDfsDlg::InitItem()
{
	m_IpCtrlIpAddress.SubclassDlgItem(IDC_IPADDRESS_DFS, this);
	m_EdtiUserId.SubclassDlgItem(IDC_EDIT_USER_ID, this);
	m_EdtiUserPw.SubclassDlgItem(IDC_EDIT_USER_PW, this);
	m_EditEqpId.SubclassDlgItem(IDC_EDIT_EQP_ID, this);
	m_EditUnitId.SubclassDlgItem(IDC_EDIT_UNIT_ID, this);
	m_EditStepId.SubclassDlgItem(IDC_EDIT_STEP_ID, this);
	m_EditProcessId.SubclassDlgItem(IDC_EDIT_PROCESS_ID, this);
	m_EditFrameId.SubclassDlgItem(IDC_EDIT_FRAME_ID, this);

	return TRUE;
}

BOOL CVisionAgentECSDfsDlg::ChangeUi()
{
	m_IpCtrlIpAddress.SetWindowTextW(SharedInfo::m_sDfsPara.strIpAddress);
	m_EdtiUserId.SetWindowTextW(SharedInfo::m_sDfsPara.strUserId);
	m_EdtiUserPw.SetWindowTextW(SharedInfo::m_sDfsPara.strUserPw);
	m_EditEqpId.SetWindowTextW(SharedInfo::m_sDfsPara.strEqpId);
	m_EditUnitId.SetWindowTextW(SharedInfo::m_sDfsPara.strUnitId);
	m_EditStepId.SetWindowTextW(SharedInfo::m_sDfsPara.strStepId);
	m_EditProcessId.SetWindowTextW(SharedInfo::m_sDfsPara.strProcessId);
	m_EditFrameId.SetWindowTextW(SharedInfo::m_sDfsPara.strFrameId);

	return TRUE;
}

BOOL CVisionAgentECSDfsDlg::ChangeData()
{
	CString strTemp = _T("");
	m_IpCtrlIpAddress.GetWindowTextW(strTemp);

	wsprintf(SharedInfo::m_sDfsPara.strIpAddress, _T("%s"), strTemp);

	m_EdtiUserId.GetWindowTextW(strTemp);
	wsprintf(SharedInfo::m_sDfsPara.strUserId, _T("%s"), strTemp);

	m_EdtiUserPw.GetWindowTextW(strTemp);
	wsprintf(SharedInfo::m_sDfsPara.strUserPw, _T("%s"), strTemp);

	m_EditEqpId.GetWindowTextW(strTemp);
	wsprintf(SharedInfo::m_sDfsPara.strEqpId, _T("%s"), strTemp);

	m_EditUnitId.GetWindowTextW(strTemp);
	wsprintf(SharedInfo::m_sDfsPara.strUnitId, _T("%s"), strTemp);

	m_EditStepId.GetWindowTextW(strTemp);
	wsprintf(SharedInfo::m_sDfsPara.strStepId, _T("%s"), strTemp);

	m_EditProcessId.GetWindowTextW(strTemp);
	wsprintf(SharedInfo::m_sDfsPara.strProcessId, _T("%s"), strTemp);

	m_EditFrameId.GetWindowTextW(strTemp);
	wsprintf(SharedInfo::m_sDfsPara.strFrameId, _T("%s"), strTemp);


	return TRUE;
}




void CVisionAgentECSDfsDlg::OnBnClickedBtnDfsSave()
{
	ChangeData();
	SharedInfo::DfsInfoSave();

	ChangeUi();
}




void CVisionAgentECSDfsDlg::OnBnClickedBtnGetDirInfo()
{
	CString strTemp = _T("");
	strTemp = SharedInfo::GetDfsFolderDir(_T("Test.bmp"));
	strTemp.MakeUpper();
	Devs::m_pDfs.SetUpload(_T("D:\\SAVE_IMAGE\\blob_.bmp"), strTemp);
}

