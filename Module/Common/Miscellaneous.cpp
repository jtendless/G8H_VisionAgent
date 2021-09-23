#include "stdafx.h"
#include "Miscellaneous.h"


Miscellaneous::Miscellaneous()
{
}


Miscellaneous::~Miscellaneous()
{
}

BOOL Miscellaneous::IsSameDirectory(CString StrLocation)
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

void Miscellaneous::GetExePath(CString& rStr)
{
	int i, nSize;
	TCHAR tchPathName[_MAX_PATH];
	GetModuleFileName(NULL, tchPathName, MAX_PATH);
	nSize = (int)wcslen(tchPathName);
	for (i = nSize; i >= 0; i--)
	{
		if (tchPathName[i] == '\\')
		{
			tchPathName[i] = NULL;
			break;
		}
	}

	rStr.Format(_T("%s"), tchPathName);
}
