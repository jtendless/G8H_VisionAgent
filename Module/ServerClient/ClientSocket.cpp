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

// 데이터가 전달되면 호출되는 통보 함수
void CClientSocket::OnReceive(int nErrorCode) 
{
	CSocket::OnReceive(nErrorCode);

	CString StrIP;
	//UINT nPort;

	//memset(m_chReceiveData, 0, sizeof(m_chReceiveData));
	
	Receive(m_chReceiveData, sizeof(m_chReceiveData));	
	
	//GetPeerName(StrIP, nPort); // 상대방의 IP 주소와 포트 번호 얻음
	//lstrcpyn(m_StrClientIPAddress.GetBuffer(StrIP.GetLength() + 1), StrIP, StrIP.GetLength() + 1);	
	//m_StrClientIPAddress.ReleaseBuffer();

	//((CNetworkMotionDlg *) (((CNetworkMotionApp*)AfxGetApp())->m_pMainWnd))->ReceiveData(this, temp);
	m_pTCPIP->ReceiveData(this, m_chReceiveData);
}

// 연결된 소켓이 닫히면 호출되는 통보 함수
void CClientSocket::OnClose(int nErrorCode) 
{
	CSocket::OnClose(nErrorCode);

	// 닫힌 소켓과 연결된 자소켓에 대해 처리한다. 	
	//((CNetworkMotionDlg *) (((CNetworkMotionApp*)AfxGetApp())->m_pMainWnd))->CloseChild(this); 
	//AfxMessageBox("클라이언트로부터 접속이 끊겼습니다.");

	m_pTCPIP->CloseChild(this); 
}
