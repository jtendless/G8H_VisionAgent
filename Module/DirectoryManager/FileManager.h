#pragma once

class CFileManager
{
public :
	CFileManager();
	~CFileManager();

private :
	CStringArray m_strArray_FolderList;

	CString m_strFolderPath;
	BOOL	CheckOverTimeFolderName(int nPeriod, CString &strResult);
	bool		ListUpFolderName();
	BOOL	DeleteDirectoryFile(CString RootDir);

public :

	bool setFolderPath(CString strFolderPath);
	bool doDeleteOverTimeFolder(int nPeriod);
};

