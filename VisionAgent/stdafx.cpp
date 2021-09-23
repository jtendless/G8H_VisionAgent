
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// VisionAgent.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"
#include <io.h>

//-----------------------------------------------------------------------------------------------
bool FileExist(LPCTSTR lpPathName)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;

	if ((hFind = ::FindFirstFile(lpPathName, &fd)) != INVALID_HANDLE_VALUE) {

		FindClose(hFind);

		return TRUE;

	}
	return FALSE;
}
//-----------------------------------------------------------------------------------------------
CString GetHomeDir()
{
	TCHAR path[_MAX_PATH];

	::GetModuleFileName(NULL, path, _MAX_PATH);

	CString strPath = _T("");
	strPath = path;
	int i = strPath.ReverseFind('\\');

	strPath = strPath.Left(i);
	strPath = strPath + _T("\\");
	return strPath;
}
//-----------------------------------------------------------------------------------------------
bool	DirectoryExist(CString DirPath)
{
	int nRslt = 0;
	nRslt = GetFileAttributes(DirPath);
	return (nRslt >= 0);
}
//-----------------------------------------------------------------------------------------------
bool	DeleteDir(CString DirPath)
{
	if (DirPath == _T(""))
	{
		return FALSE;
	}

	BOOL bRval = FALSE;
	int nRval = 0;
	CString szNextDirPath = _T("");
	CString szRoot = _T("");
	CFileFind FileFind;

	// Directory�� ���� �ϴ��� Ȯ�� �˻� 
	bRval = DirectoryExist(DirPath);

	if (bRval == FALSE)
	{
		return (bRval != TRUE);
	}
	DirPath = DirPath + _T("\\*.*");
	bRval = FileFind.FindFile(DirPath);
	while (bRval)
	{
		bRval = FileFind.FindNextFile();

		// . or .. �� ��� �����Ѵ�. 
		if (FileFind.IsDots() == TRUE)
		{
			continue;
		}

		// Directory �� ��� 
		if (FileFind.IsDirectory())
		{
			szNextDirPath.Format(_T("%s\\*.*"), FileFind.GetFilePath());

			// Recursion function ȣ�� 
			DeleteDir(szNextDirPath);
		}

		// file�� ��� 
		else
		{
			//���� ���� 
			SetFileAttributes(FileFind.GetFilePath(), FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
			::DeleteFile(FileFind.GetFilePath());
		}
	}

	szRoot = FileFind.GetRoot();
	FileFind.Close();

	SetFileAttributes(szRoot, FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
	bRval = RemoveDirectory(szRoot);

	return (bRval != TRUE);
}
//--------------------------------------------------------------------
BOOL IsSameDirectory(CString StrLocation)
{
	CFileFind find;
	CString   strTemp = StrLocation;
	CString	  strTempFileName;
	BOOL      bFind;

	if (strTemp[strTemp.GetLength() - 1] == '\\')
		strTemp += "*.*";
	else
		strTemp += "\\*.*";

	bFind = find.FindFile(strTemp);

	while (bFind)
	{
		bFind = find.FindNextFile();

		//if( find.IsDirectory() && !find.IsDots() )
		if (find.IsDirectory())
		{
			return TRUE;
		}
	}

	return FALSE;
}
//------------------------------------------------------------------