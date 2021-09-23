#include "stdafx.h"
#include "FileIni.h"


C_FileIni::C_FileIni()
{
}


C_FileIni::~C_FileIni()
{
}


CString	C_FileIni::_GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault)
{
	TCHAR	pBuf[1024];
	::GetPrivateProfileString(lpszSection, lpszEntry, lpszDefault, pBuf, 1024, m_file);
	return pBuf;
}

BOOL	C_FileIni::_WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue)
{
	return ::WritePrivateProfileString(lpszSection, lpszEntry, lpszValue, m_file);
}

int		C_FileIni::_GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault)
{
	return ::GetPrivateProfileInt(lpszSection, lpszEntry, nDefault, m_file);
}

BOOL	C_FileIni::WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue)
{
	CString strTemp = _T("");
	strTemp.Format(_T("%d"), nValue);
	return ::WritePrivateProfileString(lpszSection, lpszEntry, strTemp, m_file);
}

double	C_FileIni::GetProfileDouble(LPCTSTR lpszSection, LPCTSTR lpszEntry, double fDefault)
{
	CString strTemp = _T("");
	TCHAR	pBuf[1024];
	::GetPrivateProfileString(lpszSection, lpszEntry, strTemp, pBuf, 1024, m_file);
	return _wtof(pBuf);
}

BOOL	C_FileIni::WriteProfileDouble(LPCTSTR lpszSection, LPCTSTR lpszEntry, double fValue)
{
	CString strTemp = _T("");
	strTemp.Format(_T("%lf"), fValue);
	return ::WritePrivateProfileString(lpszSection, lpszEntry, strTemp, m_file);
}


