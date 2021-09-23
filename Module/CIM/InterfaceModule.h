#pragma once

class CInterfaceModule
{
public:
	CInterfaceModule();
	~CInterfaceModule();

	BOOL InitProcess();
	BOOL EndProcess();

	//Receive Thread.
	CWinThread*		pThread;
	VOID					ThreadFunctionEntry(VOID);
	static UINT			ThreadFunction(LPVOID lpParam);

	BOOL				m_ThreadFinish;
	BOOL				m_ThreadFinishOk;
	///////////////////////////////////////////////////////////////
};

