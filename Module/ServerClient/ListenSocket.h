#if !defined(AFX_LISTENSOCKET_H__C1078343_1496_11D1_AF19_006097DCB62C__INCLUDED_)
#define AFX_LISTENSOCKET_H__C1078343_1496_11D1_AF19_006097DCB62C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListenSocket.h : header file
//

#include <afxsock.h>		// MFC socket extensions
#pragma comment(lib, "ws2_32.lib")


class CTCPIP;
/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CListenSocket(CTCPIP *pTCPIP);	
	virtual ~CListenSocket();

	CTCPIP *m_pTCPIP;	
// Overrides
public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__C1078343_1496_11D1_AF19_006097DCB62C__INCLUDED_)
