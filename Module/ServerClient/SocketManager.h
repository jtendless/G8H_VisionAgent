// SocketManager.h: interface for the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
#define AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SocketComm.h"

#define MAX_PAKET_NUM			10000
#define WSA_VERSION				MAKEWORD(2,2)
#define WM_UPDATE_CONNECTION	WM_APP+0x1234

class CSocketManager : public CSocketComm  
{
public:
	CSocketManager();
	virtual ~CSocketManager();

	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	virtual void OnEvent(UINT uEvent, LPVOID lpvData);

	virtual int SendData(const CString* str);
	virtual int SendDataEx(char* chData, int nSize);
	virtual int GetReceiveData(char* chData);

	void SocketDataReceive(char* chData, int nCount);
	int ReceiveDataEx(char* pchReceiveData, int* pnFuncAddr, int* pnReturn, byte* pby);
	int LRCDecoderEx(char* pch, int nSize);

	int SetParentDlg(void *pDlg);	
	void *m_pParentDlg;


	int m_bIsReceiveData;
	DWORD m_dwCount;

	CString m_strSendData;

	char *m_chReceiveData;
	int m_nFuncAddr;
	int m_nReturn;
	byte *m_byArg;
	UINT m_unCurIndex;
};

#endif // !defined(AFX_SOCKETMANAGER_H__7403BD71_338A_4531_BD91_3D7E5B505793__INCLUDED_)
