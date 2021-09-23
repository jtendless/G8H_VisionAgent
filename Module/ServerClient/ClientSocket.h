#if !defined(AFX_CLIENTSOCKET_H__C1078344_1496_11D1_AF19_006097DCB62C__INCLUDED_)
#define AFX_CLIENTSOCKET_H__C1078344_1496_11D1_AF19_006097DCB62C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClientSocket.h : header file
//

#include <afxsock.h>		// MFC socket extensions
//#include <winsock2.h>
//#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


class CTCPIP;
/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSocket(CTCPIP *pTCPIP);
	virtual ~CClientSocket();

	CTCPIP *m_pTCPIP;
	CString m_StrClientIPAddress;

	char m_chReceiveData[10000];

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__C1078344_1496_11D1_AF19_006097DCB62C__INCLUDED_)
