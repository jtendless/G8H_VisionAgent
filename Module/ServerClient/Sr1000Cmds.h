/******************************************************************************
* @file     CSr1000Cmds.h
* @date     2018.03.
* @history
* sglee@raontek
******************************************************************************/

#pragma once


class CSr1000CmdBase
{
public:
	CSr1000CmdBase(LPCTSTR lpszFmtCmd = NULL, LPCTSTR lpszFmtRsp = NULL, LPCTSTR lpszFmtRst = NULL);
	virtual ~CSr1000CmdBase();

protected:
	static CList<CSr1000CmdBase*> m_CmdList;
	static int m_nLastErrCode;

protected:
	CString m_strFmtCmd;
	CString m_strFmtRsp;
	CString m_strFmtRst;

	int m_eLastResult;
	int m_eLastResponse;

public:
	enum eRESULT
	{
		eRESULT_NONE,
		eRESULT_SUCCESS,
		eRESULT_FAIL,
		eRESULT_MAX
	};

	enum eRESPONSE
	{
		eRESPONSE_NONE,
		eRESPONSE_OK,
		eRESPONSE_ERR,
		eRESPONSE_MAX
	};

protected:
	virtual int ParseRsp(LPCTSTR lpszData);
	virtual int ParseRst(LPCTSTR lpszData);

public:
	virtual int MakeCommand(LPTSTR lpBuffer, int nSize, ...);
	virtual void Clear(void);

	int Parse(LPCTSTR lpszData, int nSize);

public:
	bool ExistCmdFmt(void) { return !m_strFmtCmd.IsEmpty(); }
	bool ExistCmdRsp(void) { return !m_strFmtRsp.IsEmpty(); }
	bool ExistCmdRst(void) { return !m_strFmtRst.IsEmpty(); }

	int GetLastResponse(void) { return m_eLastResponse; }
	int GetLastResult(void)	{ return m_eLastResult; }

	void SetLastResponse(int eResponse = eRESPONSE_NONE) { m_eLastResponse = eResponse; }
	void SetLastResult(int eResult = eRESULT_NONE)	{ m_eLastResult = eResult; }

	
public:
	static int GetCommandCount(void)	{ return m_CmdList.GetCount(); }
	static int GetLastErrCode(void) { return m_nLastErrCode; }
};

/**
* Commmand: Start reading
*/

class CSr1000CmdStartReading : public CSr1000CmdBase
{
public:
	CSr1000CmdStartReading();
	~CSr1000CmdStartReading();

private:
	CString strLastReadCode;
	bool bIsLastReadOk;

public:
	virtual void Clear(void);

public:
	int ParseRst(LPCTSTR lpszRst);

public:
	LPCTSTR GetLastCode(void) { return (LPCTSTR)strLastReadCode; }
	bool IsLastReadOk(void) { return bIsLastReadOk; }
};

/**
* Commmand: Reset
*/

class CSr1000CmdReset : public CSr1000CmdBase
{
public:
	CSr1000CmdReset();
	~CSr1000CmdReset();

public:
	int ParseRsp(LPCTSTR lpszRsp);

};

#if 0
class CSr1000CmdFtune : public CSr1000CmdBase
{
public:
	CSr1000CmdFtune();
	~CSr1000CmdFtune();

public:
	int MakeCommand(LPTSTR lpBuffer, int nSize, ...);
	int ParseRsp(LPCTSTR lpszRsp);
	int ParseRst(LPCTSTR lpszRst);

public:
};
#endif