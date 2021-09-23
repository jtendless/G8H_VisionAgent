#include "stdafx.h"
#include "FileManager.h"

CFileManager::CFileManager()
{

}

CFileManager::~CFileManager()
{

}

bool CFileManager::setFolderPath(CString strFolderPath)
{
	m_strFolderPath = strFolderPath;
	return TRUE;
}

bool CFileManager::ListUpFolderName()
{
	CFileFind finder;
	CString strDirName;
	CString strTemp;
	strTemp.Format(_T("%s\\*.*"), m_strFolderPath);
	m_strArray_FolderList.RemoveAll();

	BOOL bWorking = finder.FindFile(strTemp);
	while (bWorking)
	{
		//Sleep(10);
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory())
		{
			strDirName = finder.GetFileName();
			if (strDirName == _T(".") || strDirName == _T("..")) continue;
			m_strArray_FolderList.Add(strDirName);
		}
	}

	return TRUE;
}

BOOL CFileManager::CheckOverTimeFolderName(int nPeriod, CString &strResult)
{
	CString strTemp;
	CString strList;
	INT nMonthNum;
	INT nDeleteMonth;
	SYSTEMTIME st;
	GetLocalTime(&st);
	INT nYear = st.wYear;
	   
	for (int i = 0; i < m_strArray_FolderList.GetSize(); i++)
	{
		for (int j = 0; j < nPeriod; j++)
		{
			nDeleteMonth = (int)st.wMonth - (int)nPeriod - j;
			nYear = st.wYear;
			if (nDeleteMonth <= 0)
			{
				nYear -= 1;
				nDeleteMonth = 12 + nDeleteMonth;
			}
			strTemp.Format(_T("%04d%02d"), nYear, nDeleteMonth);
			strList = m_strArray_FolderList.GetAt(i);
			if (strTemp.Compare(strList) == 0)		//Same
			{
				//한번에 하나씩 뽑아서 삭제.
				strResult = strTemp;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CFileManager::DeleteDirectoryFile(CString RootDir)
{
	if (RootDir == _T("") || RootDir == _T(".") || RootDir == _T(".."))
	{
		AfxMessageBox(_T("It's not Selected Model"));
		return FALSE;
	}

	BOOL bRval = FALSE;
	CString szRoot = _T("");

	// ÇØ´ç µð·ºÅä¸®ÀÇ ¸ðµç ÆÄÀÏÀ» °Ë»çÇÑ´Ù.
	szRoot.Format(_T("%s\\*.*"), RootDir);
	CFileFind find;
	bRval = find.FindFile(szRoot);
	if (bRval == FALSE)
	{
		return bRval;
	}
	while (bRval)
	{
		bRval = find.FindNextFile();
		// . or .. ÀÎ °æ¿ì ¹«½Ã ÇÑ´Ù.  
		if (find.IsDots() == FALSE)
		{
			// Directory Delete.
			if (find.IsDirectory())
			{
				DeleteDirectoryFile(find.GetFilePath());
			}
			// File Delete 
			else
			{
				SetFileAttributes(find.GetFilePath(), FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
				bRval = DeleteFile(find.GetFilePath());
			}
		}
	}
	find.Close();

	SetFileAttributes(RootDir, FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
	bRval = RemoveDirectory(RootDir);
	return bRval;
}

bool CFileManager::doDeleteOverTimeFolder(int nMonth)
{
	CString strFolderName;
	CString strTemp;
	BOOL bResult = FALSE;

	ListUpFolderName();

	bResult = CheckOverTimeFolderName(nMonth, strFolderName);
	strTemp.Format(_T("%s\\%s"), m_strFolderPath, strFolderName);
	if (bResult)
	{
		DeleteDirectoryFile(strTemp);
	}

	return TRUE;
}

