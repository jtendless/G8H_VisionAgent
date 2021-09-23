// VisionAgentLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentLogDlg.h"
#include "afxdialogex.h"


// CVisionAgentLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentLogDlg, CDialogEx)

CVisionAgentLogDlg::CVisionAgentLogDlg(CWnd* pParent, INT nIndex)
	: CDialogEx(CVisionAgentLogDlg::IDD, pParent)
{
	m_Index = nIndex;
	Create(CVisionAgentLogDlg::IDD, pParent);
}

CVisionAgentLogDlg::~CVisionAgentLogDlg()
{
}

void CVisionAgentLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY_LIST, m_HistoryListCtrl);
}


BEGIN_MESSAGE_MAP(CVisionAgentLogDlg, CDialogEx)
	ON_WM_SIZE()
	ON_MESSAGE(UPDATEDATA_LOG, &CVisionAgentLogDlg::UpdateLogView)//

END_MESSAGE_MAP()


// CVisionAgentLogDlg 메시지 처리기입니다.
BOOL CVisionAgentLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_nInsertItemNum = 0;
	m_HistoryListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ImageList.Create(1, 20, ILC_COLOR, 1, 1);
	m_HistoryListCtrl.SetImageList(&m_ImageList, LVSIL_SMALL);
	AddListColumn();

	CRect ItemRect;
	m_HistoryListCtrl.GetItemRect(0, ItemRect, LVIR_BOUNDS);
	//m_ItemSize = CSize(0, ItemRect.Height() * 1024);
	m_ItemSize = CSize(0, 10 * 1024);

	CLogger* pLogger = CLogger::GetInstance();
	pLogger->SetMsgListener((en_LOG_LIST)m_Index, this->GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.

}

BOOL CVisionAgentLogDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE))
		{
			return true;
		}
	}

	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// CVisionAgentLogDlg 메시지 처리기입니다.
LRESULT CVisionAgentLogDlg::UpdateLogView(WPARAM wParam, LPARAM lParam)
{
	CLogger *pLog = CLogger::GetInstance();
	BOOL bResult = FALSE;
	TMsgBuffer mesgs;

	if (pLog)
	{
		bResult = pLog->GetDispLogData((en_LOG_LIST)m_Index, mesgs);
	}

	if (bResult)
	{
		TMsgBuffer::iterator iter = mesgs.begin();
		CString strLog;
		//int index = 0;
		for (; iter != mesgs.end(); iter++)
		{
			//if (index == m_nInsertItemNum)
			{
				strLog = iter->c_str();
				if (strLog.GetLength() > 13)
				{
					AddListData(strLog.Mid(0, 14), strLog.Mid(15, strLog.GetLength()));
				}
			}
			//index++;
		}
	}

	return 0;
}

void CVisionAgentLogDlg::AddListData(CString StrTime, CString Str)
{
	LV_ITEM lvitem;
	int curitem = 0;

	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;

	for (int j = 0; j < 2; j++)
	{
		lvitem.iItem = (j == 0) ? m_nInsertItemNum : curitem;
		lvitem.iSubItem = j;

		switch (j)
		{
		case 0:
			//lvitem.pszText= (LPSTR)(LPCSTR)m_StrTime;	
			lvitem.pszText = StrTime.GetBuffer(StrTime.GetLength());
			curitem = m_HistoryListCtrl.InsertItem(&lvitem);
			break;
		case 1:
			lvitem.pszText = Str.GetBuffer(Str.GetLength());
			m_HistoryListCtrl.SetItem(&lvitem);
			break;
		}
	}
	m_HistoryListCtrl.Scroll(m_ItemSize);

	if (++m_nInsertItemNum > DISP_LOG_NUM_MAX)
	{
		m_nInsertItemNum = 0; m_HistoryListCtrl.DeleteAllItems();
	}

	//if (++m_nInsertItemNum > DISP_LOG_NUM_MAX) 
	//{ 
	//	m_HistoryListCtrl.DeleteItem(0);
	//	m_nInsertItemNum = DISP_LOG_NUM_MAX;
	//}
}

void CVisionAgentLogDlg::AddListColumn()
{
	LV_COLUMN lvcolumn;
	//char *listcolumn[2]={"Time", "Message"};
	TCHAR *listcolumn[2] = { _T("Time"), _T("Message") };
	//int width[2] = { 120, 480 };
	int width[2] = { 90, 880 };

	for (int i = 0; i < 2; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT;//CENTER;
		//lvcolumn.pszText = listcolumn[i];
		lvcolumn.pszText = (LPWSTR)listcolumn[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = width[i];

		m_HistoryListCtrl.InsertColumn(i, &lvcolumn);
	}
}

void CVisionAgentLogDlg::ClearListData()
{
	m_HistoryListCtrl.DeleteAllItems();
	m_nInsertItemNum = 0;
}

void CVisionAgentLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetSafeHwnd() == NULL)
		return;

	if (GetDlgItem(IDC_HISTORY_LIST)->GetSafeHwnd() == NULL) return;
	GetDlgItem(IDC_HISTORY_LIST)->MoveWindow(0, 0, cx, cy);

}