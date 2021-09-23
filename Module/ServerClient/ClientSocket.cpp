// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ClientSocket.h"
#include "TCPIP.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket(CTCPIP *pTCPIP)
{
	m_pTCPIP = pTCPIP;
}

CClientSocket::~CClientSocket()
{
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

// �����Ͱ� ���޵Ǹ� ȣ��Ǵ� �뺸 �Լ�
void CClientSocket::OnReceive(int nErrorCode) 
{
	CSocket::OnReceive(nErrorCode);

	CString StrIP;
	//UINT nPort;

	//memset(m_chReceiveData, 0, sizeof(m_chReceiveData));
	
	Receive(m_chReceiveData, sizeof(m_chReceiveData));	
	
	//GetPeerName(StrIP, nPort); // ������ IP �ּҿ� ��Ʈ ��ȣ ����
	//lstrcpyn(m_StrClientIPAddress.GetBuffer(StrIP.GetLength() + 1), StrIP, StrIP.GetLength() + 1);	
	//m_StrClientIPAddress.ReleaseBuffer();

	//((CNetworkMotionDlg *) (((CNetworkMotionApp*)AfxGetApp())->m_pMainWnd))->ReceiveData(this, temp);
	m_pTCPIP->ReceiveData(this, m_chReceiveData);
}

// ����� ������ ������ ȣ��Ǵ� �뺸 �Լ�
void CClientSocket::OnClose(int nErrorCode) 
{
	CSocket::OnClose(nErrorCode);

	// ���� ���ϰ� ����� �ڼ��Ͽ� ���� ó���Ѵ�. 	
	//((CNetworkMotionDlg *) (((CNetworkMotionApp*)AfxGetApp())->m_pMainWnd))->CloseChild(this); 
	//AfxMessageBox("Ŭ���̾�Ʈ�κ��� ������ ������ϴ�.");

	m_pTCPIP->CloseChild(this); 
}
