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

	int InitServer(int nPort, CString StrServerIPAddress); // ���� ������ �ʱ�ȭ �Ѵ�.
	
	void CleanUp(); // ������ ������ �ݰ� �޸𸮸� �����Ѵ�. 

	int SendData(CString &StrClientIPAddress, CString&  StrData); // ������ ����
	int SendDataEx(CString &StrClientIPAddress, char* chData, int nSize); // ������ ����
	void ReceiveData(CClientSocket* pRecSock, char* szRecieve); // ������ ����
	void Accept(); // ���ο� Ŭ���̾�Ʈ ���ӽ� ȣ��
	void CloseChild(CClientSocket* pCloseSock); // ����� ������ ������ ȣ��

	CListenSocket* m_pServer; // Ŭ���Ʈ�� ������ ���� ����(���)�ϴ� ���� ����
	CClientSocket* m_pChild; // ���ο� Ŭ���̾�Ʈ ���� �� �����Ǵ� �ڼ���
	CObList m_pSockList; // Ŭ���̾�Ʈ�� ����� �ڼ��ϵ��� ����

	//void OnSend(); // [������]��ư Ŭ����

	void CLOSE(); //m_hSocketWindow==NULL�� �ذ��ϱ����ؼ� 

	HWND m_hWnd;	

	int m_nPort;	
	int m_nConnect;
	CString m_StrServerIPAddress;
};

// Thread�� ����� �Լ� 
//DWORD ThreadWatchTCPIP(CTCPIP* pCTCPIP);

#endif // !defined(AFX_TCPIP_H__A62405EB_436A_4724_A368_19CA0865F221__INCLUDED_)
