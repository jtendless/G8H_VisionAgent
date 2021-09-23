#include "stdafx.h"
#include "CommFTP.h"


CCommFTP::CCommFTP()
{
	m_pINetSess		= NULL;
	m_pFtpCon		= NULL;
	m_pFtpFileFind	= NULL;

	_stprintf_s(m_szFtpIp, MAX_PATH, _T("%s"), _T(" "));
	_stprintf_s(m_szFtpId, MAX_PATH, _T("%s"), _T(" "));
	_stprintf_s(m_szFtpPw, MAX_PATH, _T("%s"), _T(" "));
	m_nPort = 0;
}

CCommFTP::~CCommFTP()
{
	SetClose();
}

BOOL CCommFTP::SetOpen(CString	szFtpIp, CString szFtpId, CString szFtpPw, INT nPort)
{
	CString szCurDir = _T("");

	SetClose();

	_stprintf_s(m_szFtpIp, MAX_PATH, _T("%s"), szFtpIp);
	_stprintf_s(m_szFtpId, MAX_PATH, _T("%s"), szFtpId);
	_stprintf_s(m_szFtpPw, MAX_PATH, _T("%s"), szFtpPw);

	m_nPort		= nPort;
	m_pINetSess = new CInternetSession;
	m_pINetSess->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);
	//m_pINetSess->SetOption(INTERNET_OPTION_KEEP_CONNECTION, 5000);

	try
	{
		m_pFtpCon = m_pINetSess->GetFtpConnection(szFtpIp, szFtpId, szFtpPw, (INTERNET_PORT)nPort, TRUE);
		m_pFtpCon->GetCurrentDirectory(szCurDir);
		m_szRoot = szCurDir;
	}
	catch (CInternetException* e)
	{
		SetClose();

		e->ReportError();
		e->Delete();

		return FALSE;
	}

	m_pFtpFileFind = new CFtpFileFind(m_pFtpCon);

	SetCreateDirectory(m_szRoot);

	return TRUE;
}

BOOL CCommFTP::SetClose()
{
	if (NULL != m_pFtpFileFind)
	{
		m_pFtpFileFind->Close();
		delete m_pFtpFileFind;
		m_pFtpFileFind = NULL;
	}

	if (NULL != m_pFtpCon)
	{
		m_pFtpCon->Close();
		delete m_pFtpCon;
		m_pFtpCon = NULL;
	}

	if (NULL != m_pINetSess)
	{
		m_pINetSess->Close();
		delete m_pINetSess;
		m_pINetSess = NULL;
	}

	return TRUE;
}

BOOL CCommFTP::SetUpload(CString szPath, CString szRmtPath)
{
	BOOL bSuccess = FALSE;

	if (!m_pFtpCon || szPath.IsEmpty() || szRmtPath.IsEmpty())	{ return FALSE; }

	SetCreateDirectory(szRmtPath, FALSE);

#if 1
	CFile			f_Upload;
	CInternetFile	*pf_Inet = NULL;

	if (!f_Upload.Open(szPath, CFile::modeRead | CFile::typeBinary)) { return FALSE; }

	pf_Inet = m_pFtpCon->OpenFile(szRmtPath, GENERIC_WRITE);
	if (!pf_Inet) { return FALSE; }

	INT dwSize		= 512 * 1000;	// 한 번에 전송할 크기
	INT dwTrSize	= dwSize;		// 한 번에 전송한 크기
	BYTE *pbyData	= new BYTE [dwSize];
	ZeroMemory(pbyData, sizeof(BYTE) * dwSize);

	while (dwTrSize) // dwTrSize > 0 일 때는 파일을 아직 더 읽어야 하는 경우임
	{	
		MSG msg;	// PumpMessage
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		dwTrSize = f_Upload.Read(pbyData, dwSize);
		if (dwTrSize) { pf_Inet->Write(pbyData, dwTrSize); }
	}

	f_Upload.Close();
	pf_Inet->Close();

	if (pbyData) { delete pbyData; pbyData = NULL; }
	if (pf_Inet) { delete pf_Inet; pf_Inet = NULL; }
#else
	bSuccess = m_pFtpCon->PutFile(szPath, szRmtPath);
#endif

	bSuccess = m_pFtpFileFind->FindFile(szRmtPath);

	return bSuccess;
}

BOOL CCommFTP::SetUpload(CFile *pf_Upload, CString szRmtPath)
{
	CInternetFile	*pf_Inet = NULL;
	if (!m_pFtpCon || !pf_Upload || szRmtPath.IsEmpty())	{ return FALSE; }

	SetCreateDirectory(szRmtPath, FALSE);
	
	pf_Inet = m_pFtpCon->OpenFile(szRmtPath, GENERIC_WRITE);
	if (!pf_Inet)
	{
		pf_Inet->Close();
		return FALSE;
	}

	INT dwSize		= 512 * 1000;	// 한 번에 전송할 크기
	INT dwTrSize	= dwSize;		// 한 번에 전송한 크기
	BYTE *pbyData	= new BYTE [dwSize];
	CString szMsg = _T("");
	ZeroMemory(pbyData, sizeof(BYTE) * dwSize);

	pf_Upload->SeekToBegin();

	while (dwTrSize) //dwTrSize > 0 일 때는 파일을 아직 더 읽어야 하는 경우임
	{		
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		dwTrSize = pf_Upload->Read(pbyData, dwSize);
		if (dwTrSize) { 
			try
			{
				pf_Inet->Write(pbyData, dwTrSize);
			}
			catch (CInternetException *ex)
			{
				szMsg.Format(_T("[TPD] TPD File Write Status : %d"), ex->m_dwError);
				AfxMessageBox(szMsg);			
			}
		}
	}

	pf_Upload->SeekToEnd();
	pf_Inet->Close();

	if (pbyData) { delete pbyData; pbyData = NULL; }
	if (pf_Inet) { delete pf_Inet; pf_Inet = NULL; }

	return m_pFtpFileFind->FindFile(szRmtPath);
}

BOOL CCommFTP::SetDownload(CString szRmtPath, CString szPath)
{
	BOOL bSuccess = FALSE;
	CFileFind fileFind;

	if (!m_pFtpCon) { return FALSE; }

	if (!m_pFtpFileFind->FindFile(szRmtPath)) { return FALSE; }

#if 1
	CFile			f_Download;
	CInternetFile	*pf_Inet = NULL;
	
	if(!f_Download.Open(szPath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone | CFile::typeBinary))
		return FALSE;

	pf_Inet = m_pFtpCon->OpenFile(szRmtPath, GENERIC_READ);
	if (!pf_Inet) { return FALSE; }

	INT dwSize		= 512 * 1000;	// 한 번에 전송할 크기
	INT dwTrSize	= dwSize;		// 한 번에 전송한 크기
	BYTE *pbyData	= new BYTE [dwSize];
	ZeroMemory(pbyData, sizeof(BYTE) * dwSize);

	while (dwTrSize) //dwTrSize > 0 일 때는 파일을 아직 더 읽어야 하는 경우임
	{	
		MSG msg;	// PumpMessage
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		dwTrSize = pf_Inet->Read(pbyData, dwSize);
		if (dwTrSize) { f_Download.Write(pbyData, dwTrSize); }
	}

	f_Download.Close();
	pf_Inet->Close();

	if (pbyData) { delete pbyData; pbyData = NULL; }
	if (pf_Inet) { delete pf_Inet; pf_Inet = NULL; }
#else
	bSuccess = m_pFtpCon->GetFile(szRmtPath, szPath);
#endif

	bSuccess = fileFind.FindFile(szPath);
	fileFind.Close();

	return bSuccess;
}


CString CCommFTP::GetMakeDirName(CString szPath)
{
	CString szRmtPath;

	szPath.Replace(_T("C:\\"), _T(""));
	szPath.Replace(_T("D:\\"), _T(""));
	szPath.Replace(_T("\\"), _T("/"));

	szRmtPath.Format(_T("%s/%s"), m_szRoot, szPath);
	szRmtPath.MakeUpper();

	return szRmtPath;
}


void CCommFTP::SetCreateDirectory(CString szRmtPath, BOOL bFolder/* = TRUE*/)
{
	CString szChk(szRmtPath);
	CString szDir;
	INT nIdx = 0, nCnt = 0;
	TCHAR tcGetAt;

	if (!m_pFtpCon || !m_pFtpFileFind)	{ return; }
	if (szChk.IsEmpty())				{ return; }

	szChk.Trim();
	szChk.MakeUpper();

	nCnt = szChk.GetLength();

	for (nIdx = 0; nIdx < nCnt; nIdx++)
	{
		tcGetAt = szChk.GetAt(nIdx);
		if (tcGetAt == '/')
		{
			szDir = szChk.Mid(0, nIdx + 1);
			m_pFtpCon->CreateDirectory(szDir);
		}
	}

	if (bFolder)
	{
		szDir = szChk;
		m_pFtpCon->CreateDirectory(szChk);
	}
}


void CCommFTP::SetDeleteDirectory(CString szPath, CString *pszFtpPath/* = NULL*/)
{
	CString szDir;
	CString szTestDir;

	if (!m_pFtpCon || !m_pFtpFileFind)	{ return; }

	m_pFtpCon->GetCurrentDirectory(szDir);

	szTestDir.Format(_T("%s/TEST"), szDir);
	m_pFtpCon->CreateDirectory(szTestDir);
}