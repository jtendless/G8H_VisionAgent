#pragma once
//! File Transfer Protocol
#include <afxinet.h> //FTP

class CCommFTP
{
public:
	CCommFTP(void);
	virtual ~CCommFTP(void);

public:
	TCHAR*				GetInfo_IP()			{ return m_szFtpIp; }
	CString				GetInfo_Root()			{ return m_szRoot; }
	CInternetSession*	GetInfo_INetSession()	{ return m_pINetSess; }
	CFtpConnection*		GetInfo_Connect()		{ return m_pFtpCon; }
	CFtpFileFind*		GetInfo_FileFind()		{ return m_pFtpFileFind; }

public:
	BOOL	SetOpen(CString szFtpIp, CString szFtpId, CString szFtpPw, INT nPort);
	BOOL	SetClose();

	BOOL	SetUpload(CString szPath, CString szRmtPath);
	BOOL	SetUpload(CFile *pf_Upload, CString szRmtPath);
	BOOL	SetDownload(CString szRmtPath, CString szPath);

	CString	GetMakeDirName(CString szPath);
	void	SetCreateDirectory(CString szRmtPath, BOOL bFolder = TRUE);
	void	SetDeleteDirectory(CString szPath, CString *pszFtpPath = NULL);

private:
	CInternetSession	*m_pINetSess;
	CFtpConnection		*m_pFtpCon;
	CFtpFileFind		*m_pFtpFileFind;

	TCHAR	m_szFtpIp[MAX_PATH];
	TCHAR	m_szFtpId[MAX_PATH];
	TCHAR	m_szFtpPw[MAX_PATH];

	INT		m_nPort;

	CString m_szRoot;
};