#pragma once
class C_FileIni
{
public:
	CString	m_file;
	CString m_sec;

public:
	C_FileIni();
	~C_FileIni();
	
	CString	_GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = 0);
	BOOL	_WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue);
	int		_GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault = 0);
	BOOL	WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
	double	GetProfileDouble(LPCTSTR lpszSection, LPCTSTR lpszEntry, double fDefault = 0);
	BOOL	WriteProfileDouble(LPCTSTR lpszSection, LPCTSTR lpszEntry, double fValue);
};

