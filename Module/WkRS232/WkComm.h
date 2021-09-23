#ifndef MY_COMM
#define MY_COMM

#pragma once

#include <afxmt.h>

#define MAXBUF         204800
#define InBufSize      204800
#define OutBufSize     204800
#define ASCII_XON      0x11
#define ASCII_XOFF     0x13

#define COMM_STX	0x02
#define COMM_ETX	0x03
#define COMM_LF		0x0A
#define COMM_CR	0x0D

#define WM_MYRECEIVE		(WM_USER+1) //데이터 수신 메시지
#define WM_MYCLOSE_DP     (WM_USER+2) //종료 메시지

// CWkComm 명령 대상입니다.



class CWkComm : public CCmdTarget
{
	DECLARE_DYNAMIC(CWkComm)

public:
	CWkComm();
	virtual ~CWkComm();

public:
    HANDLE  m_hComDev;
    HWND    m_hWnd;


    BOOL    m_bIsOpenned;
    CString m_sComPort;
    CString m_sBaudRate;
    CString m_sParity;
    CString m_sDataBit;
    CString m_sStopBit;
    BOOL    m_bFlowChk;

	BOOL m_bComChk;

    OVERLAPPED m_OLR,m_OLW;
    char    m_sInBuf[MAXBUF];
	CString m_strbuf;
	CString m_strResult;
    int     m_nLength;
    CEvent* m_pEvent;

	// Operations

public:
    void Clear();
   
    BOOL Send(LPSTR outbuf, int len);
    BOOL Create(HWND hWnd);
    void HandleClose();
    void Close();
    void ResetSerial();
    CWkComm(CString port,CString baudrate,CString parity,CString databit,CString stopbit);
	int DataAssembly(LPSTR szbuf, int len);
	CString GetReceiveData(void);

protected:
	DECLARE_MESSAGE_MAP()
	
};

#endif