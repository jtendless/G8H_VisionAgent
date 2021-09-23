/******************************************************************************
* @file     CSr1000Cmds.cpp
* @date     2018.03.
* @history
* sglee@raontek
******************************************************************************/

#include "stdafx.h"
#include "Sr1000Cmds.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CList<CSr1000CmdBase*> CSr1000CmdBase::m_CmdList;
int CSr1000CmdBase::m_nLastErrCode = 0;

CSr1000CmdBase::CSr1000CmdBase(LPCTSTR lpszFmtCmd/* = NULL*/, LPCTSTR lpszFmtRsp/* = NULL*/, LPCTSTR lpszFmtRst/* = NULL*/)
{
	m_strFmtCmd = lpszFmtCmd;
	m_strFmtRsp = lpszFmtRsp;
	m_strFmtRst = lpszFmtRst;

	m_eLastResult = eRESULT_NONE;
	m_eLastResponse = eRESPONSE_NONE;

	m_nLastErrCode = 0;

	m_CmdList.AddTail(this);
}

CSr1000CmdBase::~CSr1000CmdBase()
{
}

int CSr1000CmdBase::MakeCommand(LPTSTR lpBuffer, int nSize, ...)
{
	int nRet = 0;

	va_list args;
	va_start(args, nSize);

	nRet = _stprintf_s(lpBuffer, nSize, (LPCTSTR)m_strFmtCmd, args);

	va_end(args);

	return (nRet > 0) ? (0) : (-1);
}

void CSr1000CmdBase::Clear(void)
{ 
	m_eLastResponse = eRESPONSE_NONE; 
	m_eLastResult = eRESULT_NONE; 
}

int CSr1000CmdBase::Parse(LPCTSTR lpszData, int nSize)
{
	if (m_eLastResult == eRESULT_FAIL)
	{
		// Discard data.
		return 0;
	}

	if ((ExistCmdRsp() == true) && (m_eLastResponse == eRESPONSE_NONE))
	{
		ParseRsp(lpszData);
	}
	if ((ExistCmdRst() == true) && (m_eLastResult == eRESULT_NONE))
	{
		ParseRst(lpszData);
	}

	return 0;
}

int CSr1000CmdBase::ParseRsp(LPCTSTR lpszData)
{
	m_eLastResponse = eRESPONSE_OK;

	return _tcslen(lpszData);
}

int CSr1000CmdBase::ParseRst(LPCTSTR lpszData)
{
	m_eLastResult = eRESULT_SUCCESS;

	return _tcslen(lpszData);
}

/**
 * Commmand: Start reading
 */

CSr1000CmdStartReading::CSr1000CmdStartReading()
: CSr1000CmdBase(_T("LON"), _T(""), _T("%s"))
{
}
CSr1000CmdStartReading::~CSr1000CmdStartReading()
{
}

void CSr1000CmdStartReading::Clear(void)
{
	CSr1000CmdBase::Clear();

	bIsLastReadOk = false;
	strLastReadCode = _T("");
}

int CSr1000CmdStartReading::ParseRst(LPCTSTR lpszRst)
{
	CString strError(_T("ERROR"));

	if (strError.CompareNoCase(lpszRst) == 0)
	{
		strLastReadCode = _T("");
		bIsLastReadOk = false;

		m_eLastResult = eRESULT_FAIL;

		return 0;
	}

	strLastReadCode = lpszRst;
	bIsLastReadOk = true;

	m_eLastResult = eRESULT_SUCCESS;

	return 0;
}

/**
* Commmand: Reset
*/

CSr1000CmdReset::CSr1000CmdReset()
: CSr1000CmdBase(_T("RESET"), _T("%[^0-9]%d"), _T(""))
{
}
CSr1000CmdReset::~CSr1000CmdReset()
{
}

int CSr1000CmdReset::ParseRsp(LPCTSTR lpszRsp)
{
	TCHAR tBuffer[128] = { '\0', };

	CString strOk = _T("OK");
	CString strErr = _T("ERR");

	int nRet = 0;
	int nErrCode = 0;

	nRet = _stscanf_s(lpszRsp, (LPCTSTR)m_strFmtRsp, tBuffer, 128, &nErrCode);

	if (nRet < 0)
	{
		m_eLastResponse = eRESPONSE_NONE;
		m_eLastResult = eRESULT_FAIL;
		return -1;
	}
	
	if (strOk.CompareNoCase(tBuffer) == 0)
	{
		m_eLastResponse = eRESPONSE_OK;
		m_eLastResult = eRESULT_SUCCESS;

		nRet = 0;
	}
	else if (strErr.CompareNoCase(tBuffer) == 0)
	{
		m_nLastErrCode = nErrCode;

		m_eLastResponse = eRESPONSE_ERR;
		m_eLastResult = eRESULT_FAIL;

		nRet = 0;
	}
	else
	{
		m_eLastResponse = eRESPONSE_NONE;
		m_eLastResult = eRESULT_FAIL;

		nRet = -1;
	}

	return nRet;
}

#if 0
/**
 * Commmand: 
 */

CSr1000CmdFtune::CSr1000CmdFtune() 
: CSr1000CmdBase(_T("FTUNE"), _T("%[^,],%s"), _T("Focus Tuning %s"))
{

}
CSr1000CmdFtune::~CSr1000CmdFtune()
{

}

int CSr1000CmdFtune::ParseRsp(LPCTSTR lpszRsp)
{
	TCHAR tBuffer[128];
	TCHAR tBuffer2[128];
	int nRet;

	tBuffer[0] = '\0';
	tBuffer2[0] = '\0';

	nRet = _stscanf_s(lpszRsp, (LPCTSTR)m_strFmtRsp, tBuffer, 128, tBuffer2, 128);

	return nRet;
}

int CSr1000CmdFtune::ParseRst(LPCTSTR lpszRst)
{
	TCHAR tBuffer[128];
	int nRet;

	tBuffer[0] = '\0';

	nRet = _stscanf_s(lpszRst, (LPCTSTR)m_strFmtRst, tBuffer, 128);

	return nRet;
}
#endif