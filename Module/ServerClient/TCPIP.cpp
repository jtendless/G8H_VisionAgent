// TCPIP.cpp: implementation of the CTCPIP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCPIP.h"
#include "../../Module/Common/ReturnDefine.h"
//#include "../../MotionAgent/MotionAgentDlg.h"
#include "../Module/Log/Logger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTCPIP::CTCPIP()
{
	m_pParentDlg = NULL;

	m_nPort = 2000;
	m_pServer = NULL;
	m_pChild = NULL;
	
	m_nConnect = 0;
}

CTCPIP::CTCPIP(HWND hWnd)
{
	m_pParentDlg = NULL;

	m_hWnd = hWnd;

	m_nPort = 2000;
	m_pServer = NULL;
	m_pChild = NULL;		

	m_nConnect = 0;
}

CTCPIP::~CTCPIP()
{
	CleanUp();
}

void CTCPIP::CLOSE()
{
	CleanUp();
}

int CTCPIP::SetParentDlg(void *pDlg)
{
	m_pParentDlg = pDlg;

	m_ServerInterface.SetParentDlg(pDlg);

	return TRUE;
}

// 추가된 코드 내용 
int CTCPIP::InitServer(int nPort, CString StrServerIPAddress)
{
	int nError;

	m_nPort = nPort;
	m_StrServerIPAddress = StrServerIPAddress;
	
	if(m_pServer==NULL) m_pServer = new CListenSocket(this); // 리슨(대기)하는 서버 소켓 객체
	
	// Socket을 생성하고 Listen 상태로...
	if(m_pServer->Create(m_nPort)) // 포트 번호 2000으로 서버 소켓 생성
	{	
		if(m_pServer->Listen()) // 클라이언트의 연결 요청을 기다리며 대기한다.
		{	
			//AfxMessageBox(_T("Create Completed !"));	
			return TRUE;
		}
		else
		{
			CleanUp();			
			return FALSE;
		}
	}
	else
	{		
		AfxMessageBox(_T("Create Failure !"));
		nError = GetLastError();
		CleanUp();
		return FALSE;
	}

	return FALSE;
}

void CTCPIP::Accept()
{
	CClientSocket* pChild = new CClientSocket(this);
	
	if(m_pServer->Accept(*pChild)) 
	{
		m_pSockList.AddTail(pChild); // 생성된 자소켓을 리스트에 추가
		//int nCount = m_pSockList.GetCount(); 
		//SetDlgItemInt(IDC_USERCOUNT, nCount); // 현재 접속된 클라이언트 수 출력				
		//AfxMessageBox(_T(" Accept Success !"));

		Total_Msg(_T("Client is connected."));
	}
	else
	{
		AfxMessageBox(_T("Accept Failure !"));
		delete pChild;
	}
}

int CTCPIP::SendData(CString &StrClientIPAddress, CString &StrData)
{
	CString StrIP, StrSendData;
	//int nErrorCode;

	lstrcpyn(StrIP.GetBuffer(StrClientIPAddress.GetLength()+1), (LPTSTR)(LPCTSTR)StrClientIPAddress, StrClientIPAddress.GetLength()+1);
	StrIP.ReleaseBuffer();

	lstrcpyn(StrSendData.GetBuffer(StrData.GetLength()+1), (LPTSTR)(LPCTSTR)StrData, StrData.GetLength()+1);
	StrSendData.ReleaseBuffer();
	
	// 서버에 접속중인 모든 클라이언트에 데이터를 전송한다.
	int nBytesSent = 0;

	CClientSocket* pChild=NULL;
	POSITION pos = m_pSockList.GetHeadPosition();
	while(pos != NULL)
	{
		m_nConnect = 1;

		pChild = (CClientSocket*)m_pSockList.GetAt(pos);
		
		//if(pChild==NULL) AfxMessageBox(" pChild==NULL ");

		if (!m_StrServerIPAddress.Compare(_T("0.0.0.0")) || !m_StrServerIPAddress.Compare(_T("255.255.255.255")))
		{
			if(!StrIP.Compare(pChild->m_StrClientIPAddress))
			{				
				//if((nBytesSent = pChild->Send((LPCSTR)StrSendData, StrSendData.GetLength()+1)) == SOCKET_ERROR) return -1;

				nBytesSent = pChild->Send((LPTSTR)(LPCTSTR)StrSendData, StrSendData.GetLength() + 1);

				//if(nBytesSent == SOCKET_ERROR)
				//{
				//	nErrorCode = pChild->GetLastError();
				//
				//	CString StrTraceValue;
				//	StrTraceValue.Format(" TCPIP(SEND) ERROR(%d): ", nErrorCode);															
				//	e_cMotionTrace=(LPSTR)(LPCTSTR)StrTraceValue;					
				//	::SendMessage(hTRACEWnd, WM_MOTION_TRACE, 0, 0);
				//	Sleep(0);
				//
				//	return -1;
				//}

				break;
			}
		}
		else
		{
			//if((nBytesSent = pChild->Send((LPCSTR)StrSendData, StrSendData.GetLength()+1)) == SOCKET_ERROR) return -1;

			nBytesSent = pChild->Send((LPTSTR)(LPCTSTR)StrSendData, StrSendData.GetLength() + 1);

			//if(nBytesSent == SOCKET_ERROR)
			//{
			//	nErrorCode = pChild->GetLastError();
			//
			//	CString StrTraceValue;
			//	StrTraceValue.Format(" TCPIP(SEND) ERROR(%d): ", nErrorCode);															
			//	e_cMotionTrace=(LPSTR)(LPCTSTR)StrTraceValue;					
			//	::SendMessage(hTRACEWnd, WM_MOTION_TRACE, 0, 0);
			//	Sleep(0);
			//
			//	return -1;
			//}
		}

		m_pSockList.GetNext(pos);
	}

	// 전송한 데이터를 리스트 박스에 추가한다.
	//((CListBox *)GetDlgItem(IDC_RECEIVE_LIST))->InsertString(-1, strData);
	//((CListBox*)GetDlgItem(IDC_RECEIVE_LIST))->SetTopIndex(((CListBox*)GetDlgItem(IDC_RECEIVE_LIST))->GetCount()-1);

	return nBytesSent;
}

int  CTCPIP::SendDataEx(CString &StrClientIPAddress, char* chData, int nSize) // 데이터 전송
{
	//sunghaklee:2018.01.14
	//CMotionAgentDlg *pDlg = (CMotionAgentDlg *)m_pParentDlg;	
	//if (pDlg->m_nAXLOpen == 0) return 0;

	CString StrIP, StrSendData;
	//int nErrorCode;

	if (nSize > 0){
		*(chData + nSize + 0) = '\r';
		*(chData + nSize + 1) = '\n';
		*(chData + nSize + 2) = 0;
		nSize += 3;		
	}

	//lstrcpyn(StrIP.GetBuffer(StrClientIPAddress.GetLength() + 1), (LPTSTR)(LPCTSTR)StrClientIPAddress, StrClientIPAddress.GetLength() + 1);
	//StrIP.ReleaseBuffer();

	
	// 서버에 접속중인 모든 클라이언트에 데이터를 전송한다.
	int nBytesSent = 0;

	CClientSocket* pChild = NULL;
	POSITION pos = m_pSockList.GetHeadPosition();
	while (pos != NULL)
	{
		m_nConnect = 1;

		pChild = (CClientSocket*)m_pSockList.GetAt(pos);

		//if(pChild==NULL) AfxMessageBox(" pChild==NULL ");

		if (!m_StrServerIPAddress.Compare(_T("0.0.0.0")) || !m_StrServerIPAddress.Compare(_T("255.255.255.255")))
		{
			if (!StrIP.Compare(pChild->m_StrClientIPAddress))
			{
				//if((nBytesSent = pChild->Send((LPCSTR)StrSendData, StrSendData.GetLength()+1)) == SOCKET_ERROR) return -1;

				nBytesSent = pChild->Send((LPBYTE)chData, nSize);

				//if(nBytesSent == SOCKET_ERROR)
				//{
				//	nErrorCode = pChild->GetLastError();
				//
				//	CString StrTraceValue;
				//	StrTraceValue.Format(" TCPIP(SEND) ERROR(%d): ", nErrorCode);															
				//	e_cMotionTrace=(LPSTR)(LPCTSTR)StrTraceValue;					
				//	::SendMessage(hTRACEWnd, WM_MOTION_TRACE, 0, 0);
				//	Sleep(0);
				//
				//	return -1;
				//}

				break;
			}
		}
		else
		{
			//if((nBytesSent = pChild->Send((LPCSTR)StrSendData, StrSendData.GetLength()+1)) == SOCKET_ERROR) return -1;

			nBytesSent = pChild->Send((LPBYTE)chData, nSize);

			//if(nBytesSent == SOCKET_ERROR)
			//{
			//	nErrorCode = pChild->GetLastError();
			//
			//	CString StrTraceValue;
			//	StrTraceValue.Format(" TCPIP(SEND) ERROR(%d): ", nErrorCode);															
			//	e_cMotionTrace=(LPSTR)(LPCTSTR)StrTraceValue;					
			//	::SendMessage(hTRACEWnd, WM_MOTION_TRACE, 0, 0);
			//	Sleep(0);
			//
			//	return -1;
			//}
		}

		m_pSockList.GetNext(pos);
	}

	return nBytesSent;
}

void CTCPIP::ReceiveData(CClientSocket* pRecSock, char* szRecieve)
{
    CString StrIP;	
	//UINT nPort;
	//int i, nSize, nRtn;
	int nSize, nRtn;
	byte bySendData[1024] = { 0 };
	
	//sunghaklee:2018.01.14
	//CMotionAgentDlg *pDlg = (CMotionAgentDlg *)m_pParentDlg;
	//if (pDlg->m_nAXLOpen == 0) return;

	//pRecSock->GetPeerName(StrIP, nPort); // 상대방의 IP 주소와 포트 번호 얻음

	//StrIP = "[ " + StrIP + " ] " + szRecieve;

	//if(m_StrServerIPAddress.Compare(_T("0.0.0.0")) && m_StrServerIPAddress.Compare(_T("255.255.255.255"))) 
	//{
		//if(m_StrServerIPAddress.Compare(StrIP)) return;	
	//}

	//nSize = strlen(szRecieve);		
	
	memcpy(m_chReceiveData, pRecSock->m_chReceiveData, sizeof(pRecSock->m_chReceiveData));	
	nRtn = m_ModbusData.ReceiveDataEx(m_chReceiveData, &m_nFuncAddr, &m_nReturn, m_byArg);

	//TRACE(_T("m_nFuncAddr = %d\n"), m_nFuncAddr);

	if (nRtn == RET_SUCCESS && m_nFuncAddr < MAX_SHM_FUNCTION)
	{
		nRtn = m_ServerInterface.ExecShmFuncTable(m_nFuncAddr, m_byArg);// &stArg);

		nSize = m_ModbusData.SendDataEx(m_nFuncAddr, nRtn, (byte*)m_byArg, m_ServerInterface.m_nArgSize, 0, bySendData);
		SendDataEx(StrIP, (char*)bySendData, nSize);

		//m_chkNetworkStatus.SetCheck(FALSE);
	}
	else
	{
		TRACE(_T("Error : m_nFuncAddr = %d\n"), m_nFuncAddr);

		nSize = m_ModbusData.SendDataEx(MAX_SHM_FUNCTION, nRtn, (byte*)m_byArg, /*m_ServerInterface.m_nArgSize*/128, 0, bySendData);
		SendDataEx(StrIP, (char*)bySendData, nSize);
	}

	//st_AxisPosMove stArg;
	//stArg = *((st_AxisPosMove*)(void*)m_byArg);	
	//stArg.dVel = 123.456;	
	//nSize = m_ModbusData.SendDataEx(AxisPosMove_Func, nRtn, (byte*)&stArg, sizeof(stArg), 0, bySendData);	
	//SendDataEx(StrIP, (char*)bySendData, nSize);
	
	//CMotionDlg GetDlgItem()
	
	/*
	// 수신한 데이터를 서버에 접속중인 다른 클라이언트에 전송한다.
	CClientSocket* pChild_1;
	POSITION pos = m_pSockList.GetHeadPosition();								
	while( pos != NULL)  
	{
		pChild_1 = (CClientSocket*)m_pSockList.GetAt(pos);
		if(pChild_1 != pRecSock)
		{
			pChild_1->Send(szRecieve, sizeof(szRecieve));
		}
		m_pSockList.GetNext(pos);
	}
	*/
}

void CTCPIP::CleanUp()
{	
	// 자소켓을 관리하는 리스트를 모두 제거하는 부분
	CClientSocket* pChild;

	while(!m_pSockList.IsEmpty())
	{   
		pChild = (CClientSocket*)m_pSockList.RemoveHead();
		pChild->ShutDown(2);
		delete pChild;
		pChild = NULL;
	}

	// 서버 소켓 제거
	if(m_pServer != NULL) m_pServer->ShutDown(2);
	
	if(m_pServer) delete m_pServer;

	m_pServer = NULL;
}

void CTCPIP::CloseChild(CClientSocket* pCloseSock)
{
	//AfxMessageBox("연결된 상대방 소켓 닫힘");

	Total_Msg(_T("Client is disconnected."));

	// 현재 닫힌 소켓을 리스트에서 제거한다.
	CClientSocket* pChild;

	POSITION pos = m_pSockList.GetHeadPosition();								
	while( pos != NULL)
	{
		pChild = (CClientSocket*)m_pSockList.GetAt(pos);
		if(pChild == pCloseSock) 
		{
			m_pSockList.RemoveAt(pos);
			delete pChild;
			break;
		}
		m_pSockList.GetNext(pos);
	}	

	//int nCount = m_pSockList.GetCount(); 
	//SetDlgItemInt(IDC_USERCOUNT, nCount); // 현재 접속된 클라이언트 수 출력
}