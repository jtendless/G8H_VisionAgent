#include "stdafx.h"
#include "InterfaceModule.h"


CInterfaceModule::CInterfaceModule()
{
}


CInterfaceModule::~CInterfaceModule()
{

}

BOOL CInterfaceModule::InitProcess()
{
	pThread = AfxBeginThread(ThreadFunction, this);

	return TRUE;
}

BOOL CInterfaceModule::EndProcess()
{
	m_ThreadFinish = FALSE;

	do
	{
		Sleep(10);
	} while (m_ThreadFinishOk == FALSE);

	return TRUE;

}

UINT CInterfaceModule::ThreadFunction(LPVOID lpParam)
{
	CInterfaceModule* pModule = NULL;

	pModule->m_ThreadFinishOk = FALSE;

	pModule = (CInterfaceModule*)lpParam;

	pModule->ThreadFunctionEntry();

	pModule->m_ThreadFinishOk = TRUE;

	return 0;
}

VOID CInterfaceModule::ThreadFunctionEntry(VOID)
{
	CString szMsg = _T("");

	while (m_ThreadFinish)
	{
		//연결 초기화 될때까지 Wait

		Sleep(100);
	}
}
