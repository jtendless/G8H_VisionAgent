// TCPIP.h: interface for the CTCPIP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPIP_H__A62405EB_436A_4724_A368_19CA0865F221__INCLUDED_)
#define AFX_TCPIP_H__A62405EB_436A_4724_A368_19CA0865F221__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListenSocket.h"
#include "ClientSocket.h"
#include "ModbusData.h"
#include "../../Module/Common/ServerInterface.h"

class CTCPIP : public CAsyncSocket
{
public:
	CTCPIP();
	CTCPIP(HWND hWnd);	
	virtual ~CTCPIP();

	char m_chReceiveData[1024];
	int m_nFuncAddr;
	int m_nReturn;
	byte m_byArg[1024];

	CModbusData m_ModbusData;
	CServerInterface  m_ServerInterface;
	void *m_pParentDlg;	
	
	////////////////////////////////////////////////////////	
	int SetParentDlg(void *pDlg);

	int InitServer(int nPort, CString StrServerIPAddress); // 서버 소켓을 초기화 한다.
	
	void CleanUp(); // 생성된 소켓을 닫고 메모리를 해제한다. 

	int SendData(CString &StrClientIPAddress, CString&  StrData); // 데이터 전송
	int SendDataEx(CString &StrClientIPAddress, char* chData, int nSize); // 데이터 전송
	void ReceiveData(CClientSocket* pRecSock, char* szRecieve); // 데이터 수신
	void Accept(); // 새로운 클라이언트 접속시 호출
	void CloseChild(CClientSocket* pCloseSock); // 연결된 소켓이 닫히면 호출

	CListenSocket* m_pServer; // 클라언트의 접속을 위해 리슨(대기)하는 서버 소켓
	CClientSocket* m_pChild; // 새로운 클라이언트 접속 후 생성되는 자소켓
	CObList m_pSockList; // 클라이언트와 연결된 자소켓들을 관리

	//void OnSend(); // [보내기]버튼 클릭시

	void CLOSE(); //m_hSocketWindow==NULL을 해결하기위해서 

	HWND m_hWnd;	

	int m_nPort;	
	int m_nConnect;
	CString m_StrServerIPAddress;
};

// Thread로 사용할 함수 
//DWORD ThreadWatchTCPIP(CTCPIP* pCTCPIP);

#endif // !defined(AFX_TCPIP_H__A62405EB_436A_4724_A368_19CA0865F221__INCLUDED_)
