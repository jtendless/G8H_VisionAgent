#pragma once


// CModelChangeDlg ��ȭ �����Դϴ�.

class CModelChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelChangeDlg)

public:
	CModelChangeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModelChangeDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MODEL_CHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
