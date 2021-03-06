#include "stdafx.h"
#include "ClientInterface.h"
#include "CommonDefine.h"
#include "VisionAgentDlg.h"
#include "Vision/SharedInfo.h"


#define MAX_COUNT	5000

CClientInterface::CClientInterface(void)
{
	m_pParentDlg = NULL;	
	
	
}

CClientInterface::~CClientInterface(void)
{	

}

int CClientInterface::SetParentDlg(void *pDlg)
{
	m_pParentDlg = pDlg;

	return TRUE;
}

int CClientInterface::Delay(double ms)
{
	//MSG  wndMsg;
	//DWORD dwSTick, dwEtick;
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;

	//dwSTick = GetTickCount();
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	while (1)
	{
		//Sleep(1);
		Sleep(0);
		//if (::PeekMessage(&wndMsg, NULL, 0, 0, PM_REMOVE))
		//{
		//	::TranslateMessage(&wndMsg);
		//	::DispatchMessage(&wndMsg);
		//}
		//dwEtick = GetTickCount();
		//dwEtick -= dwSTick;
		//if (dwEtick > ms) break;

		QueryPerformanceCounter(&end);
		dLapse = ((end.QuadPart - start.QuadPart) / (double)freq.QuadPart) * 1000;

		if (dLapse >= ms) break;
	}

	return 0;
}

BOOL CClientInterface::GetWriteCommStatus()
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	MSG wndMsg;

	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
			
	while (1)
	{
		if (pDlg->m_SocketWrite.m_bIsReceiveData == TRUE)
		{
			pDlg->m_SocketWrite.m_bIsReceiveData = FALSE;
			break;
		}

		QueryPerformanceCounter(&end);
		dLapse = ((end.QuadPart - start.QuadPart) / (double)freq.QuadPart) * 1000;
		
		//if (dLapse > 100.0) break;
		if (dLapse > 2000)
		{
			pDlg->m_SocketWrite.m_bIsReceiveData = TRUE;
			return FALSE;
		}
			
	}
	return TRUE;
}
int CClientInterface::SendWriteCommandData(int nFuncAddr, byte* pby, int nSize)
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;

	if (pDlg->m_nConnect == 0)
	{
		Total_Msg(_T("Network(192.168.1.101) not connected"));
		return FMM_SUCCESS;  //CYK 통신연결상태
	}
#if 0
	if (GetWriteCommStatus() == FALSE)
	{
		Total_Msg(_T("Write Com Time Out"));
		return FMM_COMM_TIME_OUT;
	}
#endif
	m_ClientMutex.Lock();

	//pDlg->m_SocketManager.m_bIsReceiveData = FALSE;

		//TRACE(_T("SendCommand : nFuncAddr = %d\n"), nFuncAddr);
	byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, 
	int nSendSize, nCount = 0;

	nSendSize = m_ControlWriteModbusData.SendDataEx(nFuncAddr, 0, pby, nSize, 1, bySendData);
	if (nSendSize < COM_BUF_SIZE)
	{
		pDlg->m_SocketWrite.SendDataEx((char*)bySendData, nSendSize);

	}
	else
	{
		Total_Msg(_T("Size Over"));
		pDlg->m_SocketWrite.m_bIsReceiveData = TRUE;

	}


	//Delay(0.5);z
	//Sleep(2.0);

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	//pDlg->m_SocketManager.m_bIsReceiveData = 0;

	m_ClientMutex.Unlock();

	while (pDlg->m_SocketWrite.m_bIsReceiveData == FALSE)
	{
		if (nCount > MAX_COUNT)
		{
			Total_Msg(_T("Send Write Com Time Out"));
			break;
		}

		nCount++;
		Sleep(1);
	}
	
	

	return FMM_SUCCESS;
}

BOOL CClientInterface::GetReceiveCommStatus()
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	MSG wndMsg;

	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	while (1)
	{
		if (pDlg->m_SocketReceive.m_bIsReceiveData == TRUE)
		{
			pDlg->m_SocketReceive.m_bIsReceiveData = FALSE;
			break;
		}

		QueryPerformanceCounter(&end);
		dLapse = ((end.QuadPart - start.QuadPart) / (double)freq.QuadPart) * 1000;

		//if (dLapse > 100.0) break;
		if (dLapse > 2000)
		{
			pDlg->m_SocketReceive.m_bIsReceiveData = TRUE;
			return FALSE;
		}

	}
	return TRUE;
}
int CClientInterface::SendReceiveCommandData(int nFuncAddr, byte* pby, int nSize)
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;

	

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;

	if (pDlg->m_nConnect == 0)
	{
		Total_Msg(_T("Network(192.168.1.101) not connected"));
		return FMM_SUCCESS;  //CYK 통신연결상태
	}

	if (GetReceiveCommStatus() == FALSE)
	{
		Total_Msg(_T("Receive Com Time Out"));
		return FMM_COMM_TIME_OUT;
	}

	m_ClientMutex.Lock();

	//pDlg->m_SocketManager.m_bIsReceiveData = FALSE;

	//TRACE(_T("SendCommand : nFuncAddr = %d\n"), nFuncAddr);
	byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, 
	int nSendSize, nCount = 0;



	nSendSize = m_ControlReceiveModbusData.SendDataEx(nFuncAddr, 0, pby, nSize, 1, bySendData);
	if (nSendSize < COM_BUF_SIZE)
	{
		pDlg->m_SocketReceive.SendDataEx((char*)bySendData, nSendSize);

	}
	else
	{
		Total_Msg(_T("Size Over"));
		pDlg->m_SocketReceive.m_bIsReceiveData = TRUE;

	}


	//Delay(0.5);z
	//Sleep(2.0);

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	//pDlg->m_SocketManager.m_bIsReceiveData = 0;
	m_ClientMutex.Unlock();

	while (pDlg->m_SocketReceive.m_bIsReceiveData == FALSE)
	{
		if (nCount > MAX_COUNT)
		{
			Total_Msg(_T("Send Receive Com Time Out"));
			break;
		}

		nCount++;
		Sleep(1);
	}

	

	return FMM_SUCCESS;
}




//typedef struct tag_SystemGetMaxAxisSize { int nMaxAxisSize; } st_SystemGetMaxAxisSize;
int CClientInterface::SystemGetMaxAxisSize(int nMaxAxisSize)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;
	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetMaxAxisSize stArg;	

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetMaxAxisSize_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetMaxAxisSize_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}


//typedef struct tag_SystemGetMaxDInputSize { int nMaxDInputSize; } st_SystemGetMaxDInputSize;
int CClientInterface::SystemGetMaxDInputSize(int nMaxDInputSize)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();
	
	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetMaxDInputSize stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetMaxDInputSize_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetMaxDInputSize_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetMaxDOutputSize { int nMaxDOutputSize; } st_SystemGetMaxDOutputSize;
int CClientInterface::SystemGetMaxDOutputSize(int nMaxDOutputSize)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();
	
	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;
	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetMaxDOutputSize stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetMaxDOutputSize_Func, (byte*)&stArg, sizeof(stArg));
	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetMaxDOutputSize_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetMaxAInputSize { int nMaxAInputSize; } st_SystemGetMaxAInputSize;
int CClientInterface::SystemGetMaxAInputSize(int nMaxAInputSize)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetMaxAInputSize stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetMaxAInputSize_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetMaxAInputSize_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetMaxAOutputSize { int nMaxAOutputSize; } st_SystemGetMaxAOutputSize;
int CClientInterface::SystemGetMaxAOutputSize(int nMaxAOutputSize)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();	

	//GetCommStatus();
	
	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;
	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetMaxAOutputSize stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetMaxAOutputSize_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetMaxAOutputSize_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetHomeStatus{ int nHomeStatus; } st_SystemGetHomeStatus;
int CClientInterface::SystemGetHomeStatus(int nHomeStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetHomeStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetHomeStatus_Func, (byte*)&stArg, sizeof(stArg));
	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetHomeStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetHomeSignal{ int nHomeSignal; } st_SystemGetHomeSignal;
int CClientInterface::SystemGetHomeSignal(int nHomeSignal)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetHomeSignal stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetHomeSignal_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetHomeSignal_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetLimitSignal{ int nPosSignal; int nNegSignal; } st_SystemGetLimitSignal;
int CClientInterface::SystemGetLimitSignal(int nPosSignal, int nNegSignal)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetLimitSignal stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetLimitSignal_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetLimitSignal_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	

	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetServoOnStatus{ int nStatus; } st_SystemGetServoOnStatus;
int CClientInterface::SystemSetServoOnStatus(int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemSetServoOnStatus stArg;
	stArg.nStatus = nStatus;
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemSetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetServoOnStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}
//typedef struct tag_SystemGetServoOnStatus{ int nStatus; } st_SystemGetServoOnStatus;
int CClientInterface::SystemGetServoOnStatus(int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;
		
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetServoOnStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));
	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetServoOnStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetAlarmStatus{ int nStatus; } st_SystemGetAlarmStatus;
int CClientInterface::SystemGetAlarmStatus(int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetAlarmStatus stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetAlarmStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetAlarmStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_SystemGetMotionDoneStatus{ int nStatus; } st_SystemGetMotionDoneStatus;
int CClientInterface::SystemGetMotionDoneStatus(int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetMotionDoneStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetMotionDoneStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetMotionDoneStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_SystemMoveStop{ int nSystemNo; } st_SystemMoveStop;
int CClientInterface::SystemMoveStop(int nSystemNo)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemMoveStop stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nSystemNo = nSystemNo;	

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(SystemMoveStop_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemMoveStop_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}



int CClientInterface::AjinMoveStop(int nSystemNo)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AjinMoveStop stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nSystemNo = nSystemNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AjinMoveStop_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemMoveStop_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}


//typedef struct tag_SystemGetStatus{ int nSystemNo; int nStatus; } st_SystemGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
int CClientInterface::SystemGetStatus(int nSystemNo, int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_SystemGetStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nSystemNo = nSystemNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(SystemGetStatus_Func, (byte*)&stArg, sizeof(stArg));
	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(SystemGetStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//Axis : 0 ~ MAX_UMAC_AXIS_SIZE OR Virtual Axis(21, 22, 23)
//typedef struct tag_UmacPosMove { int nAxisNo; double dPos; double dVel; double dAccel; double dDecel; int nAbsRelMode; int nBackLightMove; double dAOICamOffset; BOOL bDirBwd; int nBackLightFwdDelay; int nBackLightBwdDelay; double dBackLightFwdAccDccScale; dBackLightBwdAccDccScale} st_UmacPosMove; //KJT 202001113
int CClientInterface::UmacPosMove(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nAbsRelMode, int nBackLightMove/*= 0 */, double dAOICamOffset/* = 0*/, BOOL bDirBwd/* = FALSE*/, int nBackLightFwdDelay/* = 0*/, int nBackLightBwdDelay/* = 0*/, double dBackLightFwdAccDccScale/* = 1*/, double dBackLightBwdAccDccScale/* = 1*/) //KJT 20201113
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };	
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacPosMove stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.dPos = dPos;
	stArg.dVel = dVel;
	stArg.dAccel = dAccel;
	stArg.dDecel = dDecel;
	stArg.nAbsRelMode = nAbsRelMode;
	stArg.nBackLightMove = nBackLightMove; //KJT 20200824
	stArg.dAOICamOffset = dAOICamOffset; //KJT 20200929
	stArg.bDirBwd = bDirBwd;
	stArg.nBackLightFwdDelay = nBackLightFwdDelay; //KJT 20201113
	stArg.nBackLightBwdDelay = nBackLightBwdDelay;
	stArg.dBackLightFwdAccDccScale = dBackLightFwdAccDccScale; //KJT 20201113
	stArg.dBackLightBwdAccDccScale = dBackLightBwdAccDccScale;
	

	//Total_Msg(_T("UMAC Befor Send"));
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));
	
	SendWriteCommandData(UmacPosMove_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacPosMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

//Axis : 0 ~ MAX_UMAC_AXIS_SIZE OR Virtual Axis(21, 22, 23)
//typedef struct tag_UmacVelMove { int nAxisNo; double dVel; double dAccel; double dDecel; int nBackLightMove; } st_UmacVelMove; //KJT 20200929
int CClientInterface::UmacVelMove( int nAxisNo, double dVel, double dAccel, double dDecel, int nBackLightMove /*= 0*/) //KJT 20200929
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacVelMove stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;	
	stArg.dVel = dVel;
	stArg.dAccel = dAccel;
	stArg.dDecel = dDecel;	
	stArg.nBackLightMove = nBackLightMove; //KJT 20200824

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UmacVelMove_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacVelMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//Axis : 0 ~ MAX_UMAC_AXIS_SIZE OR Virtual Axis(21, 22, 23)
//typedef struct tag_UmacMoveStop { int nAxisNo; double dDecel; int nBackLightMove; } st_UmacMoveStop; //KJT 20200824
int CClientInterface::UmacMoveStop(int nAxisNo, double dDecel, int nBackLightMove /*= 0*/) //KJT 20200824
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacMoveStop stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;		
	stArg.dDecel = dDecel;
	stArg.nBackLightMove = nBackLightMove; //KJT 20200824

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UmacMoveStop_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacMoveStop_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}


//typedef struct tag_UmacHomeStart { int nAxisNo; } st_UmacHomeStart;
int CClientInterface::UmacHomeStart( int nAxisNo)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacHomeStart stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UmacHomeStart_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacHomeStart_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	//Total_Msg(_T("UmacHomeStart : Axis=%d"), nAxisNo);	// 20170821 by sbs

	return FMM_SUCCESS;
}

///typedef struct tag_UmacSetServoOnStatus { int nAxisNo; int nServoOnStatus; } st_UmacSetServoOnStatus;
int CClientInterface::UmacSetServoOnStatus(int nAxisNo, int nServoOnStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacSetServoOnStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.nServoOnStatus = nServoOnStatus;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UmacSetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacSetServoOnStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UmacSetAlarmClear { int nAxisNo; int nAlarmClear; } st_UmacSetAlarmClear;
int CClientInterface::UmacSetAlarmClear(int nAxisNo, int nAlarmClear)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacSetAlarmClear stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.nAlarmClear = nAlarmClear;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UmacSetAlarmClear_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacSetAlarmClear_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}


//typedef struct tag_UmacGetCmdPos{ int nAxisNo; double dPos; } st_UmacGetCmdPos;
int CClientInterface::UmacGetCmdPos( double dPos)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();
	DWORD TickCnt;

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;
	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetCmdPos stArg;
	//memset(&stArg, 0, sizeof(stArg));
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));
//	SharedInfo::TestTick = GetTickCount();
	SendReceiveCommandData(UmacGetCmdPos_Func, (byte*)&stArg, sizeof(stArg));

	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetCmdPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(1);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_UmacGetActPos{ int nAxisNo; double dPos; } st_UmacGetActPos;
int CClientInterface::UmacGetActPos(double dPos)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetActPos stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetActPos_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetActPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

//typedef struct tag_UmacGetCmdVel{ int nAxisNo; double dVel; } st_UmacGetCmdVel;
int CClientInterface::UmacGetCmdVel( double dVel)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;
		
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetCmdVel stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetCmdVel_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetCmdVel_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UmacGetHomeStatus{ int nAxisNo; int nHomeStatus; } st_UmacGetHomeStatus;
int CClientInterface::UmacGetHomeStatus(int nHomeStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetHomeStatus stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetHomeStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetHomeStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

//typedef struct tag_UmacGetHomeSignal{ int nAxisNo; int nHomeSignal; } st_UmacGetHomeSignal;
int CClientInterface::UmacGetHomeSignal(int nHomeSignal)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetHomeSignal stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetHomeSignal_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetHomeSignal_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UmacGetLimitSignal{ int nAxisNo; int nPosSignal; int nNegSignal; } st_UmacGetLimitSignal;
int CClientInterface::UmacGetLimitSignal( int nPosSignal, int nNegSignal)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetLimitSignal stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetLimitSignal_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetLimitSignal_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UmacGetServoOnStatus{ int nAxisNo; int nStatus; } st_UmacGetServoOnStatus;
int CClientInterface::UmacGetServoOnStatus( int nStatus )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetServoOnStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetServoOnStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UmacGetAlarmStatus{ int nAxisNo; int nStatus; } st_UmacGetAlarmStatus;
int CClientInterface::UmacGetAlarmStatus(  int nStatus )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetAlarmStatus stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetAlarmStatus_Func, (byte*)&stArg, sizeof(stArg));
	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetAlarmStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UmacGetMotionDoneStatus{ int nAxisNo; int nStatus; } st_UmacGetMotionDoneStatus;
int CClientInterface::UmacGetMotionDoneStatus( int nStatus )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetMotionDoneStatus stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetMotionDoneStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetMotionDoneStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}


//typedef struct tag_UmacGetStatus{ int nAxisNo; int nStatus; } st_UmacGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

int CClientInterface::UmacGetStatus(int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UmacGetStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UmacGetStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UmacGetStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AxisPosMove { int nAxisNo; double dPos; double dVel; double dAccel; double dDecel; int nAbsRelMode; } st_AxisPosMove;
int CClientInterface::AxisPosMove( int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nAbsRelMode )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();	

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisPosMove stArg;	

	//TRACE(_T(" AxisPosMove \n"));

	//pDlg->m_nSocketReceiveFlag = FALSE;	
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.dPos = dPos;
	stArg.dVel = dVel;
	stArg.dAccel = dAccel;
	stArg.dDecel = dDecel;
	stArg.nAbsRelMode = nAbsRelMode;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));
	
	SendWriteCommandData(AxisPosMove_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisPosMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//nSendSize = pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);
		
	//while ((/*pDlg->m_nSocketReceiveFlag_AxisMovePos == FALSE ||*/ pDlg->m_nSocketReceiveFlag == FALSE) && m_nCount < MAX_COUNT)
	//while ((pDlg->m_nSocketReceiveFlag_AxisMovePos == FALSE ) && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}
		
	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_AxisVelMove { int nAxisNo; double dVel; double dAccel; double dDecel; } st_AxisVelMove;
int CClientInterface::AxisVelMove( int nAxisNo, double dVel, double dAccel, double dDecel)
{	
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisVelMove stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.dVel = dVel;
	stArg.dAccel = dAccel;
	stArg.dDecel = dDecel;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AxisVelMove_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisVelMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)	
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AxisMoveStop { int nAxisNo; double dDecel; } st_AxisMoveStop;
int CClientInterface::AxisMoveStop(int nAxisNo, double dDecel)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisMoveStop stArg;

	//TRACE(_T(" AxisMoveStop \n"));

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.dDecel = dDecel;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AxisMoveStop_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisMoveStop_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_AxisHomeStart { int nAxisNo; } st_AxisHomeStart;
int CClientInterface::AxisHomeStart( int nAxisNo )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisHomeStart stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AxisHomeStart_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisHomeStart_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	//Total_Msg(_T("AxisHomeStart : Axis=%d"), nAxisNo);	// 20170821 by sbs

	return FMM_SUCCESS;
}

//typedef struct tag_AxisSignalSearch { int nAxisNo; double dVel; double dAccel; int nDetectSignal; int nSignalEdge; int nSignalMethod; } st_AxisSignalSearch;
int CClientInterface::AxisSignalSearch(int nAxisNo, double dVel, double dAccel, int nDetectSignal, int nSignalEdge, int nSignalMethod)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisSignalSearch stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.dVel = dVel;
	stArg.dAccel = dAccel;
	stArg.nDetectSignal = nDetectSignal;
	stArg.nSignalEdge = nSignalEdge;
	stArg.nSignalMethod = nSignalMethod;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AxisSignalSearch_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisSignalSearch_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

///typedef struct tag_AxisSetServoOnStatus { int nAxisNo; int nServoOnStatus; } st_AxisSetServoOnStatus;
int CClientInterface::AxisSetServoOnStatus(int nAxisNo, int nServoOnStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisSetServoOnStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.nServoOnStatus = nServoOnStatus;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AxisSetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisSetServoOnStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

//typedef struct tag_AxisSetAlarmClear { int nAxisNo; int nAlarmClear; } st_AxisSetAlarmClear;
int CClientInterface::AxisSetAlarmClear(int nAxisNo, int nAlarmClear)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisSetAlarmClear stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.nAlarmClear = nAlarmClear;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AxisSetAlarmClear_Func, (byte*)&stArg, sizeof(stArg));

	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisSetAlarmClear_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}


//typedef struct tag_AxisSetCmdPos{ int nAxisNo; double dPos; } st_AxisSetCmdPos;
int CClientInterface::AxisSetCmdPos(int nAxisNo, double dPos)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisSetCmdPos stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.dPos = dPos;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AxisSetCmdPos_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisSetCmdPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetCmdPos{ int nAxisNo; double dPos; } st_AxisGetCmdPos;
int CClientInterface::AxisGetCmdPos( double dPos )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetCmdPos stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	//SendCommandData(AxisGetCmdPos_Func, NULL, 0);
	SendReceiveCommandData(AxisGetCmdPos_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetCmdPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetCmdPos{ int nAxisNo; double dPos; } st_AxisGetCmdPos;
int CClientInterface::AxisGetActPos(double dPos)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetActPos stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetActPos_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetCmdPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetCmdVel{ int nAxisNo; double dVel; } st_AxisGetCmdVel;
int CClientInterface::AxisGetCmdVel(double dVel )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetCmdVel stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetCmdVel_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetCmdVel_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetHomeResult{ int nAxisNo; int nHomeResult; } st_AxisGetHomeResult;
int CClientInterface::AxisGetHomeResult(int nHomeStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetHomeResult stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetHomeResult_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetHomeStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetHomeStatus{ int nAxisNo; int nHomeStatus; } st_AxisGetHomeStatus;
int CClientInterface::AxisGetHomeStatus(int nHomeStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetHomeStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetHomeStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetHomeStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetHomeSignal{ int nAxisNo; int nHomeSignal; } st_AxisGetHomeSignal;
int CClientInterface::AxisGetHomeSignal(  int nHomeSignal)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetHomeSignal stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetHomeSignal_Func, (byte*)&stArg, sizeof(stArg));
	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetHomeSignal_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetLimitSignal{ int nAxisNo; int nPosSignal; int nNegSignal; } st_AxisGetLimitSignal;
int CClientInterface::AxisGetLimitSignal(int nPosSignal, int nNegSignal )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;
		
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetLimitSignal stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetLimitSignal_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetLimitSignal_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetServoOnStatus{ int nAxisNo; int nStatus; } st_AxisGetServoOnStatus;
int CClientInterface::AxisGetServoOnStatus( int nStatus )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetServoOnStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));

	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetServoOnStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetAlarmStatus{ int nAxisNo; int nStatus; } st_AxisGetAlarmStatus;
int CClientInterface::AxisGetAlarmStatus( int nStatus )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetAlarmStatus stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetAlarmStatus_Func, (byte*)&stArg, sizeof(stArg));
	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetAlarmStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

//typedef struct tag_AxisGetMotionDoneStatus{ int nAxisNo; int nStatus; } st_AxisGetMotionDoneStatus;
int CClientInterface::AxisGetMotionDoneStatus( int nStatus )
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetMotionDoneStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetMotionDoneStatus_Func, (byte*)&stArg, sizeof(stArg));
	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetMotionDoneStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}


//typedef struct tag_AxisGetStatus{ int nAxisNo; int nStatus; } st_AxisGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
int CClientInterface::AxisGetStatus(int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AxisGetStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AxisGetStatus_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AxisGetStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwSetAxisNo { int nUvwNo; int nUvwAxisNo[3]; } st_UvwSetAxisNo;
int CClientInterface::UvwSetAxisNo(int nUvwNo, int nUvwAxisNo[3])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwSetAxisNo stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;
	stArg.nUvwAxisNo[0] = nUvwAxisNo[0];
	stArg.nUvwAxisNo[1] = nUvwAxisNo[1];
	stArg.nUvwAxisNo[2] = nUvwAxisNo[2];	

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UvwSetAxisNo_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwSetAxisNo_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwPosMove { int nUvwNo; double dPos[3]; double dVel[3]; double dAccel[3]; double dDecel[3]; int nAbsRelMode; } st_UvwPosMove;
int CClientInterface::UvwPosMove(int nUvwNo, double dPos[3], double dVel[3], double dAccel[3], double dDecel[3], int nAbsRelMode)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;
	int i;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwPosMove stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	for (i = 0; i < 3; i++)
	{	
		stArg.dPos[i] = dPos[i];
		stArg.dVel[i] = dVel[i];
		stArg.dAccel[i] = dAccel[i];
		stArg.dDecel[i] = dDecel[i];
		stArg.nAbsRelMode = nAbsRelMode;
	}

#pragma region //KJT 20200904
	if (fabs(dPos[0]) < 0.000001)
	{
		SharedInfo::UvwCmdPos[nUvwNo][0] = 0.0;
	}

	if (fabs(dPos[1]) < 0.000001)
	{
		SharedInfo::UvwCmdPos[nUvwNo][1] = 0.0;
	}

	if (fabs(dPos[2]) < 0.000001)
	{
		SharedInfo::UvwCmdPos[nUvwNo][2] = 0.0;
	}
#pragma endregion

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UvwPosMove_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwPosMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}


//typedef struct tag_UvwPosMove { int nUvwNo; double dPos[3]; double dVel[3]; double dAccel[3]; double dDecel[3]; int nAbsRelMode; } st_UvwPosMove;
int CClientInterface::UvwZeroPosMove(int nUvwNo, double dPos[3], double dVel[3], double dAccel[3], double dDecel[3], int nAbsRelMode)
{
	////GetCommStatus();

	////m_ClientMutex.Lock();

	////GetCommStatus();

	////byte bySendData[MAX_PAKET_NUM] = { 0 };
	////byte byArgData[MAX_PAKET_NUM] = { 0 };
	////int i, nSendSize;
	//int i;

	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//st_UvwZeroPosMove stArg;

	////pDlg->m_nSocketReceiveFlag = FALSE;
	////m_nCount = 0;

	//stArg.nUvwNo = nUvwNo;

	//for (i = 0; i < 3; i++)
	//{
	//	stArg.dVel[i] = dVel[i];
	//	stArg.dAccel[i] = dAccel[i];
	//	stArg.dDecel[i] = dDecel[i];
	//	stArg.nAbsRelMode = nAbsRelMode;
	//}

	//if (fabs(dPos[0]) < 0.000001)
	//{
	//	pDlg->m_dUvwSumX[nUvwNo] = 0.0;
	//}

	//if (fabs(dPos[1]) < 0.000001)
	//{
	//	pDlg->m_dUvwSumY[nUvwNo] = 0.0;
	//}

	//if (fabs(dPos[2]) < 0.000001)
	//{
	//	pDlg->m_dUvwSumT[nUvwNo] = 0.0;
	//}

	////memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	//SendCommandData(UvwZeroPosMove_Func, (byte*)&stArg, sizeof(stArg));

	////nSendSize = pDlg->m_ModbusData.SendDataEx(UvwPosMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	////pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	////while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	////{
	////	m_nCount++;
	////	Sleep(0);
	////}

	////m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}



//typedef struct tag_UvwMoveStop { int nUvwNo; double dDecel[3]; } st_UvwMoveStop;
int CClientInterface::UvwMoveStop(int nUvwNo, double dDecel[3])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;
	int i;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwMoveStop stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	for (i = 0; i < 3; i++)
	{	
		stArg.dDecel[i] = dDecel[i];		
	}

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UvwMoveStop_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwMoveStop_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwHomeStart { int nUvwNo; int nAxisNo; } st_UvwHomeStart;
int CClientInterface::UvwHomeStart(int nUvwNo, int nAxisNo)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwHomeStart stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;
	stArg.nAxisNo = nAxisNo;
#if 0
	pDlg->m_dUvwSumX[nUvwNo] = 0.0;
	pDlg->m_dUvwSumY[nUvwNo] = 0.0;
	pDlg->m_dUvwSumT[nUvwNo] = 0.0;	
#endif
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UvwHomeStart_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwHomeStart_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	//Total_Msg(_T("UvwHomeStart : UVW=%d, Axis=%d"), nUvwNo, nAxisNo);	// 20170821 by sbs

	return FMM_SUCCESS;
}

//typedef struct tag_UvwSetServoOnStatus { int nUvwNo; int nAxisNo; int nServoOnStatus; } st_UvwSetServoOnStatus;
int CClientInterface::UvwSetServoOnStatus(int nUvwNo, int nAxisNo, int nServoOnStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwSetServoOnStatus stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;
	stArg.nAxisNo = nAxisNo;
	stArg.nServoOnStatus = nServoOnStatus;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UvwSetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwSetServoOnStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwSetAlarmClear { int nUvwNo; int nAxisNo; int nAlarmClear; } st_UvwSetAlarmClear;
int CClientInterface::UvwSetAlarmClear(int nUvwNo, int nAxisNo, int nAlarmClear)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwSetAlarmClear stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;
	stArg.nAxisNo = nAxisNo;
	stArg.nAlarmClear = nAlarmClear;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UvwSetAlarmClear_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwSetAlarmClear_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();	

	return FMM_SUCCESS;
}

//typedef struct tag_UvwSetCmdPos{ int nUvwNo; int nAxisNo; double dPos; } st_UvwSetCmdPos;
int CClientInterface::UvwSetCmdPos(int nUvwNo, int nAxisNo, double dPos)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwSetCmdPos stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;
	stArg.nAxisNo = nAxisNo;
	stArg.dPos = dPos;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UvwSetCmdPos_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwSetCmdPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

// typedef struct tag_UvwGetCmdPos { int nUvwNo; double dPos[3]; } st_UvwGetCmdPos;
int CClientInterface::UvwGetCmdPos(int nUvwNo, double dPos[3])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;
		
	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwGetCmdPos stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;
	//stArg.dPos[0] = dPos[0];
	//stArg.dPos[1] = dPos[1];
	//stArg.dPos[2] = dPos[2];

	stArg.dPos[0] = dPos[0];
	stArg.dPos[1] = dPos[1];
	stArg.dPos[2] = dPos[2];

	stArg.nUvwNo = nUvwNo;	
	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwGetCmdPos_Func, (byte*)&stArg, sizeof(stArg));

	
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetCmdPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;

}

//typedef struct tag_UvwGetCmdVel { int nUvwNo; double dVel[3]; } st_UvwGetCmdVel;
int CClientInterface::UvwGetCmdVel(int nUvwNo, double dPos[3])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;
		
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwGetCmdVel stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwGetCmdVel_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetCmdVel_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwGetHomeStatus{ int nUvwNo; int nStatus; } st_UvwGetHomeStatus;
int CClientInterface::UvwGetHomeStatus(int nUvwNo, int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwGetHomeStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwGetHomeStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetHomeStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwGetServoOnStatus{ int nUvwNo; int nStatus; } st_UvwGetServoOnStatus;
int CClientInterface::UvwGetServoOnStatus(int nUvwNo, int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwGetServoOnStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwGetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetServoOnStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwGetAlarmStatus{ int nUvwNo; int nStatus; } st_UvwGetAlarmStatus;
int CClientInterface::UvwGetAlarmStatus(int nUvwNo, int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwGetAlarmStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwGetAlarmStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetAlarmStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwGetMotionDoneStatus{ int nUvwNo; int nStatus; } st_UvwGetMotionDoneStatus;
int CClientInterface::UvwGetMotionDoneStatus(int nUvwNo, int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwGetMotionDoneStatus stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwGetMotionDoneStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetMotionDoneStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}


//typedef struct tag_UvwGetStatus{ int nUvwNo; int nStatus; } st_UvwGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
int CClientInterface::UvwGetStatus(int nUvwNo, int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwGetStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwGetStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwXYTSetZero { int nUvwNo; } st_UvwXYTSetZero; //KJT 20200820
int CClientInterface::UvwXYTSetZero(int nUvwNo)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwXYTSetZero stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwXYTSetZero_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwXYTSetZero_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_UvwGetTargetPos { int nUvwNo; } st_UvwGetTargetPos; //KJT 20200912
int CClientInterface::UvwGetTargetPos(int nUvwNo, double dPos[3])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwGetTargetPos stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwGetTargetPos_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetTargetPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_UvwTargetPosMove { int nUvwNo; } st_UvwTargetPosMove; //KJT 20201012
int CClientInterface::UvwTargetPosMove(int nUvwNo, double dPos[3])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwTargetPosMove stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nUvwNo = nUvwNo;
	stArg.dPos[0] = dPos[0];
	stArg.dPos[1] = dPos[1];
	stArg.dPos[2] = dPos[2];

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(UvwTargetPosMove_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetTargetPos_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//Uvwx
/////////////////////////////////////////////////
//typedef struct tag_UvwxSetAxisNo { int nUvwNo; int nUvwAxisNo[4]; } st_UvwxSetAxisNo;
int CClientInterface::UvwxSetAxisNo(int nUvwNo, int nUvwAxisNo[4])
{	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxSetAxisNo stArg;

	stArg.nUvwNo = nUvwNo;
	
	SendWriteCommandData(UvwxSetAxisNo_Func, (byte*)&stArg, sizeof(stArg));
	
	return FMM_SUCCESS;
}

//typedef struct tag_UvwxPosMove { int nUvwNo; double dPos[4]; double dVel[4]; double dAccel[4]; double dDecel[4]; int nAbsRelMode; } st_UvwxPosMove;
int CClientInterface::UvwxPosMove(int nUvwNo, double dPos[4], double dVel[4], double dAccel[4], double dDecel[4], int nAbsRelMode)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxPosMove stArg;
	int i;

	stArg.nUvwNo = nUvwNo;

	for (i = 0; i < 4; i++)
	{
		stArg.dPos[i] = dPos[i];
		stArg.dVel[i] = dVel[i];
		stArg.dAccel[i] = dAccel[i];
		stArg.dDecel[i] = dDecel[i];
		stArg.nAbsRelMode = nAbsRelMode;
	}
#if 0
	if (fabs(dPos[0]) < 0.000001)
	{
		pDlg->m_dUvwxSumX[nUvwNo] = 0.0;
	}

	if (fabs(dPos[1]) < 0.000001)
	{
		pDlg->m_dUvwxSumY[nUvwNo] = 0.0;
	}

	if (fabs(dPos[2]) < 0.000001)
	{
		pDlg->m_dUvwxSumT[nUvwNo] = 0.0;
	}
#endif
	SendWriteCommandData(UvwxPosMove_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}


//typedef struct tag_UvwxZeroPosMove { int nUvwNo; double dPos[4]; double dVel[4]; double dAccel[4]; double dDecel[4]; int nAbsRelMode; } st_UvwxZeroPosMove;
int CClientInterface::UvwxZeroPosMove(int nUvwNo, double dPos[4], double dVel[4], double dAccel[4], double dDecel[4], int nAbsRelMode)
{
	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//st_UvwxZeroPosMove stArg;
	//int i;

	//stArg.nUvwNo = nUvwNo;

	//for (i = 0; i < 3; i++)
	//{
	//	stArg.dPos[i] = dPos[i];
	//	stArg.dVel[i] = dVel[i];
	//	stArg.dAccel[i] = dAccel[i];
	//	stArg.dDecel[i] = dDecel[i];
	//	stArg.nAbsRelMode = nAbsRelMode;
	//}

	//if (fabs(dPos[0]) < 0.000001)
	//{
	//	pDlg->m_dUvwxSumX[nUvwNo] = 0.0;
	//}

	//if (fabs(dPos[1]) < 0.000001)
	//{
	//	pDlg->m_dUvwxSumY[nUvwNo] = 0.0;
	//}

	//if (fabs(dPos[2]) < 0.000001)
	//{
	//	pDlg->m_dUvwxSumT[nUvwNo] = 0.0;
	//}

	//SendCommandData(UvwxZeroPosMove_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}


//typedef struct tag_UvwxMoveStop { int nUvwNo; double dDecel[4]; } st_UvwxMoveStop;
int CClientInterface::UvwxMoveStop(int nUvwNo, double dDecel[4])
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxMoveStop stArg;

	stArg.nUvwNo = nUvwNo;

	SendWriteCommandData(UvwxMoveStop_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxHomeStart { int nUvwNo; int nAxisNo; } st_UvwxHomeStart;
int CClientInterface::UvwxHomeStart(int nUvwNo, int nAxisNo)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxHomeStart stArg;

	stArg.nUvwNo = nUvwNo;
	stArg.nAxisNo = nAxisNo;


	SendWriteCommandData(UvwxHomeStart_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxSetServoOnStatus { int nUvwNo; int nAxisNo; int nServoOnStatus; } st_UvwxSetServoOnStatus;
int CClientInterface::UvwxSetServoOnStatus(int nUvwNo, int nAxisNo, int nServoOnStatus)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxSetServoOnStatus stArg;

	stArg.nUvwNo = nUvwNo;

	SendWriteCommandData(UvwxSetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxSetAlarmClear { int nUvwNo; int nAxisNo; int nAlarmClear; } st_UvwxSetAlarmClear;
int CClientInterface::UvwxSetAlarmClear(int nUvwNo, int nAxisNo, int nAlarmClear)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxSetAlarmClear stArg;

	stArg.nUvwNo = nUvwNo;

	SendWriteCommandData(UvwxSetAlarmClear_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxSetCmdPos{ int nUvwNo; int nAxisNo; double dPos; } st_UvwxSetCmdPos;
int CClientInterface::UvwxSetCmdPos(int nUvwNo, int nAxisNo, double dPos)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxSetCmdPos stArg;

	stArg.nUvwNo = nUvwNo;

	SendWriteCommandData(UvwxSetCmdPos_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxGetCmdPos { int nUvwNo; double dPos[4]; } st_UvwxGetCmdPos;
int CClientInterface::UvwxGetCmdPos(int nUvwNo, double dPos[4])
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxGetCmdPos stArg;

	stArg.nUvwNo = nUvwNo;

	SendReceiveCommandData(UvwxGetCmdPos_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxGetCmdVel { int nUvwNo; double dVel[4]; } st_UvwxGetCmdVel;
int CClientInterface::UvwxGetCmdVel(int nUvwNo, double dVel[4])
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxGetCmdVel stArg;

	stArg.nUvwNo = nUvwNo;

	SendReceiveCommandData(UvwxGetCmdVel_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxGetHomeStatus{ int nUvwNo; int nStatus; } st_UvwxGetHomeStatus;
int CClientInterface::UvwxGetHomeStatus(int nUvwNo, int nStatus)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxGetHomeStatus stArg;

	stArg.nUvwNo = nUvwNo;

	SendReceiveCommandData(UvwxGetHomeStatus_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxGetServoOnStatus{ int nUvwNo; int nStatus; } st_UvwxGetServoOnStatus;
int CClientInterface::UvwxGetServoOnStatus(int nUvwNo, int nStatus)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxGetServoOnStatus stArg;

	stArg.nUvwNo = nUvwNo;

	SendReceiveCommandData(UvwxGetServoOnStatus_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxGetAlarmStatus{ int nUvwNo; int nStatus; } st_UvwxGetAlarmStatus;
int CClientInterface::UvwxGetAlarmStatus(int nUvwNo, int nStatus)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxGetAlarmStatus stArg;

	stArg.nUvwNo = nUvwNo;

	SendReceiveCommandData(UvwxGetAlarmStatus_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxGetMotionDoneStatus{ int nUvwNo; int nStatus; } st_UvwxGetMotionDoneStatus;
int CClientInterface::UvwxGetMotionDoneStatus(int nUvwNo, int nStatus)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxGetMotionDoneStatus stArg;

	stArg.nUvwNo = nUvwNo;

	SendReceiveCommandData(UvwxGetMotionDoneStatus_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_UvwxGetStatus{ int nUvwNo; int nStatus; } st_UvwxGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
int CClientInterface::UvwxGetStatus(int nUvwNo, int nStatus)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UvwxGetStatus stArg;

	stArg.nUvwNo = nUvwNo;

	SendReceiveCommandData(UvwxGetStatus_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}



//typedef struct tag_CoordinateSetAxisMap { int nCoordNo; int nAxisSize; int nAxisNo[8]; } st_CoordinateSetAxisMap;
int CClientInterface::CoordinateSetAxisMap(int nCoordNo, int nAxisSize, int nAxisNo[8])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;
	int i;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_CoordinateSetAxisMap stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nCoordNo = nCoordNo;
	stArg.nAxisSize = nAxisSize;

	for (i = 0; i < nAxisSize; i++)
	{
		stArg.nAxisNo[i] = nAxisNo[i];
	}

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(CoordinateSetAxisMap_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwPosMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_CoordinatePosMove { int nCoordNo; double dPos[8]; double dVel; double dAccel; double dDecel; int nAbsRelMode; } st_CoordinatePosMove;
int CClientInterface::CoordinatePosMove(int nCoordNo, double dPos[8], double dVel, double dAccel, double dDecel, int nAbsRelMode)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;
	int i;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_CoordinatePosMove stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nCoordNo = nCoordNo;

	for (i = 0; i < 8; i++)
	{
		stArg.dPos[i] = dPos[i];
	}

	stArg.dVel = dVel;
	stArg.dAccel = dAccel;
	stArg.dDecel = dDecel;
	stArg.nAbsRelMode = nAbsRelMode;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(CoordinatePosMove_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwPosMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_CoordinateMoveStop { int nCoordNo; double dDecel; } st_CoordinateMoveStop;
int CClientInterface::CoordinateMoveStop(int nCoordNo, double dDecel)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;
	int i;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_CoordinateMoveStop stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nCoordNo = nCoordNo;
	stArg.dDecel = dDecel;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(CoordinateMoveStop_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UvwPosMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_CoordinateIsBusy { int nCoordNo; int nStatus; } st_CoordinateIsBusy;
int CClientInterface::CoordinateIsBusy(int nCoordNo, int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int i, nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_CoordinateIsBusy stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nCoordNo = nCoordNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(CoordinateIsBusy_Func, (byte*)&stArg, sizeof(stArg));

	/*
	nSendSize = pDlg->m_ModbusData.SendDataEx(UvwGetStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	{
	m_nCount++;
	Sleep(0);
	}

	m_ClientMutex.Unlock();
	*/

	return FMM_SUCCESS;
}


//typedef struct tag_DInputGetBitValue { int nBit; int nValue; } st_DInputGetBitValue;
int CClientInterface::DInputGetBitValue(int nBit, int nValue)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_DInputGetBitValue stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;
	stArg.nValue = nValue;
	stArg.nBit = nBit;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(DInputGetBitValue_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(DInputGetBitValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_DInputGetDWordValue { int nDWord; DWORD dwValue; } st_DInputGetDWordValue;
int CClientInterface::DInputGetDWordValue(DWORD dwValue)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_DInputGetDWordValue stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//stArg.nDWord = nDWord;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(DInputGetDWordValue_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(DInputGetDWordValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//m_nCount++;
	//Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_DOutputGetBitValue { int nBit; int nValue; } st_DOutputGetBitValue;
int CClientInterface::DOutputGetBitValue(int nBit, int nValue)
{
//GetCommStatus();

//m_ClientMutex.Lock();

//GetCommStatus();

//byte bySendData[MAX_PAKET_NUM] = { 0 };
//byte byArgData[MAX_PAKET_NUM] = { 0 };
//int nSendSize;

CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
st_DOutputGetBitValue stArg;

//pDlg->m_nSocketReceiveFlag = FALSE;
//m_nCount = 0;
stArg.nValue = nValue;
stArg.nBit = nBit;

//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

SendReceiveCommandData(DOutputGetBitValue_Func, (byte*)&stArg, sizeof(stArg));

//nSendSize = pDlg->m_ModbusData.SendDataEx(DOutputGetBitValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
//{
//	m_nCount++;
//	Sleep(0);
//}

//m_ClientMutex.Unlock();

return FMM_SUCCESS;
}

//typedef struct tag_DOutputGetDWordValue { int nDWord; DWORD dwValue; } st_DOutputGetDWordValue;
int CClientInterface::DOutputGetDWordValue(DWORD dwValue)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_DOutputGetDWordValue stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//stArg.nDWord = nDWord;	

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(DOutputGetDWordValue_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(DOutputGetDWordValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_DOutputSetBitValue { int nBit; int nValue; } st_DOutputSetBitValue;
int CClientInterface::DOutputSetBitValue(int nBit, int nValue)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_DOutputSetBitValue stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nBit = nBit;
	stArg.nValue = nValue;

	//if (SharedInfo::DOutputValue[nBit] == nValue)
	//{
	//	return FMM_SUCCESS;
	//}
	//else
	//{
		SendWriteCommandData(DOutputSetBitValue_Func, (byte*)&stArg, sizeof(stArg));
	//}
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(DOutputSetBitValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AInputGetChannelValue { int nChannel; double dValue; } st_AInputGetChannelValue;
int CClientInterface::AInputGetChannelValue(double dValue)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AInputGetChannelValue stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

//	stArg.nChannel = nChannel;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AInputGetChannelValue_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AInputGetChannelValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AOutputGetChannelValue { int nChannel; double dValue; } st_AOutputGetChannelValue;
int CClientInterface::AOutputGetChannelValue( double dValue)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;
	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AOutputGetChannelValue stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	//stArg.nChannel = nChannel;
	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(AOutputGetChannelValue_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(AOutputGetChannelValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_AOutputSetChannelValue { int nChannel; double dValue; } st_AOutputSetChannelValue;
int CClientInterface::AOutputSetChannelValue(int nChannel, double dValue)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AOutputSetChannelValue stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nChannel = nChannel;
	stArg.dValue = dValue;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AOutputSetChannelValue_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AOutputSetChannelValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_StretchStart { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; } st_StretchStart;
int CClientInterface::ForceControlStart(int nIndex, int nAxisSize,  int nAxisNo[MAX_STRETCH_AXIS_SIZE], BOOL bReleaseFlag)
{
	

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ForceControlStart stArg;
	int i;

	stArg.nIndex = nIndex;
	stArg.nAxisSize = nAxisSize;
	stArg.bReleaseFlag = bReleaseFlag;

	for (i = 0; i < nAxisSize; i++)
	{
		stArg.nAxisNo[i] = nAxisNo[i];
	}
	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(ForceControlStart_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(StretchStart_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_StretchStop { int nAxisNo; double dDecel; } st_StretchStop;
int CClientInterface::ForceControlStop(int nIndex, int nAxisSize, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dDecel)
{
	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ForceControlStop stArg;


	int i;
	stArg.nIndex = nIndex;
	stArg.nAxisSize = nAxisSize;

	for (i = 0; i < nAxisSize; i++)
	{
		stArg.nAxisNo[i] = nAxisNo[i];
	}

	stArg.dDecel = dDecel;


	SendWriteCommandData(ForceControlStop_Func, (byte*)&stArg, sizeof(stArg));
		
	

	return FMM_SUCCESS;
}

//typedef struct tag_StretchSetPara { int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE]; int nStepCount; double dMaxSpeed; double dMinSpeed; double dOkRange; double dDecRange;  } st_StretchSetPara;
int CClientInterface::ForceControlSetPara(int nIndex, int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE], int nStepCount, double dMaxSpeed, double dMinSpeed, double dOkRange, double dDecRange)
{
	

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ForceControlSetPara stArg;
	
	stArg.nIndex = nIndex;
	int i;

	for (i = 0; i < MAX_STRETCH_AXIS_USE; i++)
	{
		stArg.nUsefulAxisNo[i] = nUsefulAxisNo[i];

		stArg.nUsefulAxisNo[i + MAX_STRETCH_AXIS_USE] = nUsefulAxisNo[i+ MAX_STRETCH_AXIS_USE];
	}
	
	stArg.nStepCount = nStepCount;
	stArg.dMaxSpeed = dMaxSpeed;
	stArg.dMinSpeed = dMinSpeed;
	stArg.dOkRange = dOkRange;
	stArg.dDecRange = dDecRange;

	SendWriteCommandData(ForceControlSetPara_Func, (byte*)&stArg, sizeof(stArg));
		
	return FMM_SUCCESS;
}


//typedef struct tag_StretchSetStepValue { int nStepNo; double dStepValue[MAX_STRETCH_AXIS_SIZE]; } st_StretchSetStepValue;
int CClientInterface::ForceControlSetStepValue(int nIndex, int nStepNo, double dStepValue[MAX_STEP][MAX_STRETCH_SIZE])
{
	

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ForceControlSetStepValue stArg;

	memset(stArg.dStepValue, 0, sizeof(stArg.dStepValue));

	int i, j;
	stArg.nIndex = nIndex;
	stArg.nStepNo = nStepNo;

	for (i = 0; i < stArg.nStepNo; i++)
	{
		for (j = 0; j < MAX_STRETCH_SIZE; j++)
		{
			stArg.dStepValue[i][j] = dStepValue[i][j];
			stArg.dStepValue[i][j+MAX_STRETCH_SIZE] = dStepValue[i][j];
		}
	}
	//}

	

	SendWriteCommandData(ForceControlSetStepValue_Func, (byte*)&stArg, sizeof(stArg));
	
	
	
	return FMM_SUCCESS;
}

//typedef struct tag_StretchGetValue { int nAxisNo;  double dCmdPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel[MAX_STRETCH_AXIS_SIZE]; double dStretchValue[MAX_STRETCH_AXIS_SIZE]; } st_StretchGetValue;
int CClientInterface::ForceControlGetValue(int nIndex, int nAxisNo, double dCmdPos[MAX_STRETCH_AXIS_SIZE], double dCmdVel[MAX_STRETCH_AXIS_SIZE], double dStretchValue[MAX_STRETCH_AXIS_SIZE])
{
	

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ForceControlGetValue stArg;

	stArg.nIndex = nIndex;
	stArg.nAxisNo = nAxisNo;
	SendReceiveCommandData(ForceControlGetValue_Func, (byte*)&stArg, sizeof(stArg));
		
	
	
	return FMM_SUCCESS;
}


//typedef struct tag_StretchGetStatus { int nAxisNo;  int nStatus; } st_StretchGetStatus;
int CClientInterface::ForceControlGetStatus(int nIndex, int nStatus[MAX_FORCE_CONTROL_SIZE])
{
	
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ForceControlGetStatus stArg;
	
	stArg.nIndex = nIndex;
	//stArg.nAxisNo = nAxisNo;

	
	SendReceiveCommandData(ForceControlGetStatus_Func, (byte*)&stArg, sizeof(stArg));
	
	return FMM_SUCCESS;
}



//typedef struct tag_CounterForceStart { int nAxisSize;  int nAxisNo[MAX_CounterForce_AXIS_SIZE]; } st_CounterForceStart;
int CClientInterface::CounterForceStart(int nAxisSize, int nAxisNo[MAX_COUNTER_FORCE_AXIS_SIZE])
{
	////GetCommStatus();

	////m_ClientMutex.Lock();

	////GetCommStatus();

	////byte bySendData[MAX_PAKET_NUM] = { 0 };
	////byte byArgData[MAX_PAKET_NUM] = { 0 };
	////int nSendSize;

	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//st_CounterForceStart stArg;
	//int i;

	////pDlg->m_nSocketReceiveFlag = FALSE;
	////m_nCount = 0;

	//stArg.nAxisSize = nAxisSize;

	//for (i = 0; i < nAxisSize; i++)
	//{
	//	stArg.nAxisNo[i] = nAxisNo[i];
	//}

	////memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	//SendCommandData(CounterForceStart_Func, (byte*)&stArg, sizeof(stArg));

	////nSendSize = pDlg->m_ModbusData.SendDataEx(CounterForceStart_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	////pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	////while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	////{
	////	m_nCount++;
	////	Sleep(0);
	////}

	////m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_CounterForceStop { int nAxisNo; double dDecel; } st_CounterForceStop;
int CClientInterface::CounterForceStop(int nAxisSize, int nAxisNo[MAX_COUNTER_FORCE_AXIS_SIZE], double dDecel)
{
	////GetCommStatus();

	////m_ClientMutex.Lock();

	////GetCommStatus();

	////byte bySendData[MAX_PAKET_NUM] = { 0 };
	////byte byArgData[MAX_PAKET_NUM] = { 0 };
	////int nSendSize;

	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//st_CounterForceStop stArg;

	////pDlg->m_nSocketReceiveFlag = FALSE;
	////m_nCount = 0;

	//int i;

	////pDlg->m_nSocketReceiveFlag = FALSE;
	////m_nCount = 0;

	//stArg.nAxisSize = nAxisSize;

	//for (i = 0; i < nAxisSize; i++)
	//{
	//	stArg.nAxisNo[i] = nAxisNo[i];
	//}

	//stArg.dDecel = dDecel;

	////memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	//SendCommandData(CounterForceStop_Func, (byte*)&stArg, sizeof(stArg));

	////nSendSize = pDlg->m_ModbusData.SendDataEx(CounterForceStop_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	////pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	////while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	////{
	////	m_nCount++;
	////	Sleep(0);
	////}

	////m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_CounterForceSetPara {  int nStepCount; double dMaxSpeed; double dMinSpeed; double dOkRange; double dDecRange;  } st_CounterForceSetPara;
int CClientInterface::CounterForceSetPara(int nStepCount, double dMaxSpeed, double dMinSpeed, double dOkRange, double dDecRange)
{


	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//st_CounterForceSetPara stArg;

	//

	//stArg.nStepCount = nStepCount;
	//stArg.dMaxSpeed = dMaxSpeed;
	//stArg.dMinSpeed = dMinSpeed;
	//stArg.dOkRange = dOkRange;
	//stArg.dDecRange = dDecRange;

	//SendCommandData(CounterForceSetPara_Func, (byte*)&stArg, sizeof(stArg));

	

	return FMM_SUCCESS;
}


//typedef struct tag_CounterForceSetStepValue { int nStepNo; double dStepValue[MAX_CounterForce_AXIS_SIZE]; } st_CounterForceSetStepValue;
int CClientInterface::CounterForceSetStepValue(int nStepNo, double dStepValue[MAX_COUNTER_FORCE_AXIS_SIZE])
{
	////GetCommStatus();

	////m_ClientMutex.Lock();

	////GetCommStatus();

	////byte bySendData[MAX_PAKET_NUM] = { 0 };
	////byte byArgData[MAX_PAKET_NUM] = { 0 };
	////int nSendSize;

	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//st_CounterForceSetStepValue stArg;

	////pDlg->m_nSocketReceiveFlag = FALSE;
	////m_nCount = 0;

	//int j;

	//stArg.nStepNo = nStepNo;

	////for (i = 0; i < MAX_STEP; i++)
	////{
	//for (j = 0; j < MAX_COUNTER_FORCE_AXIS_SIZE; j++)
	//{
	//	stArg.dStepValue[j] = dStepValue[j];
	//}
	////}

	////memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	//SendCommandData(CounterForceSetStepValue_Func, (byte*)&stArg, sizeof(stArg));

	////Total_Msg(_T("ClientInterface::CounterForceSetStepValue"));

	////nSendSize = pDlg->m_ModbusData.SendDataEx(CounterForceSetPara_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	////pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	////while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	////{
	////m_nCount++;
	////Sleep(0);
	////}

	////m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_CounterForceGetValue { int nAxisNo;  double dCmdPos[MAX_CounterForce_AXIS_SIZE]; double dCmdVel[MAX_CounterForce_AXIS_SIZE]; double dCounterForceValue[MAX_CounterForce_AXIS_SIZE]; } st_CounterForceGetValue;
int CClientInterface::CounterForceGetValue(int nAxisNo, double dCmdPos[MAX_COUNTER_FORCE_AXIS_SIZE], double dCmdVel[MAX_COUNTER_FORCE_AXIS_SIZE], double dCounterForceValue[MAX_COUNTER_FORCE_AXIS_SIZE], double dCounterForceTargetValue[MAX_COUNTER_FORCE_AXIS_SIZE])
{
	////GetCommStatus();

	////m_ClientMutex.Lock();

	////GetCommStatus();

	////byte bySendData[MAX_PAKET_NUM] = { 0 };
	////byte byArgData[MAX_PAKET_NUM] = { 0 };
	////int nSendSize;

	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//st_CounterForceGetValue stArg;

	////pDlg->m_nSocketReceiveFlag = FALSE;
	////m_nCount = 0;

	//stArg.nAxisNo = nAxisNo;

	////memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	//SendCommandData(CounterForceGetValue_Func, (byte*)&stArg, sizeof(stArg));

	////nSendSize = pDlg->m_ModbusData.SendDataEx(CounterForceGetValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	////pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	////while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	////{
	////	m_nCount++;
	////	Sleep(0);
	////}

	////m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}


//typedef struct tag_CounterForceGetStatus { int nAxisNo;  int nStatus; } st_CounterForceGetStatus;
int CClientInterface::CounterForceGetStatus(int nAxisNo, int nStatus)
{
	////GetCommStatus();

	////m_ClientMutex.Lock();

	////GetCommStatus();

	////byte bySendData[MAX_PAKET_NUM] = { 0 };
	////byte byArgData[MAX_PAKET_NUM] = { 0 };
	////int nSendSize;

	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//st_CounterForceGetStatus stArg;

	////pDlg->m_nSocketReceiveFlag = FALSE;
	////m_nCount = 0;

	//stArg.nAxisNo = nAxisNo;

	////memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	//SendCommandData(CounterForceGetStatus_Func, (byte*)&stArg, sizeof(stArg));

	////nSendSize = pDlg->m_ModbusData.SendDataEx(CounterForceGetStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	////pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	////while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	////{
	////	m_nCount++;
	////	Sleep(0);
	////}

	////m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_ClampStart { int nAxisNo; } st_ClampStart;
int CClientInterface::ClampStart(int nAxisNo)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampStart stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(ClampStart_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(ClampStart_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_UnClampStart { int nAxisNo; double dDecel; } st_UnClampStart;
int CClientInterface::UnClampStart(int nAxisNo, double dDecel)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_UnClampStart stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;
	stArg.dDecel = dDecel;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(UnClampStart_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(UnClampStart_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_ClampHomeStart { int nAxisNo; } st_ClampHomeStart;
int CClientInterface::ClampHomeStart(int nAxisNo)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampHomeStart stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;	

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(ClampHomeStart_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(ClampHomeStart_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_ClampSetPara { int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampSetPara;
int CClientInterface::ClampSetPara(int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetValue[MAX_STRETCH_AXIS_SIZE])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampSetPara stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	int i;

	for (i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
	{
		stArg.nUsefulAxisNo[i] = nUsefulAxisNo[i];
	}
	
	for (i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
	{
		stArg.dTargetValue[i] = dTargetValue[i];		
	}	

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(ClampSetPara_Func, (byte*)&stArg, sizeof(stArg));

	//nSendSize = pDlg->m_ModbusData.SendDataEx(ClampSetPara_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();

	return FMM_SUCCESS;
}

//typedef struct tag_ClampGetValue { int nAxisNo;  double dClampValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampGetValue;
int CClientInterface::ClampGetValue(int nAxisNo, double ddClampValue[MAX_STRETCH_AXIS_SIZE])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampGetValue stArg;
	
	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(ClampGetValue_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(ClampGetValue_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_ClampGetStatus{ int nAxisNo; int nStatus; } st_ClampGetStatus;
int CClientInterface::ClampGetStatus(int nAxisNo, int nStatus)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampGetStatus stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisNo = nAxisNo;

	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendReceiveCommandData(ClampGetStatus_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(ClampGetStatus_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

#if 1
//typedef struct tag_ClampTorqueMove { int nAxisNo; double dTorque; double dVel; int nAccFilterSel; int nGainSel; int nSpdLoopSel; } st_ClampTorqueMove;
int CClientInterface::ClampTorqueMove(int nAxisindex, int nStartAxisNo, double dTorque, double dVel, int nAccFilterSel, int nGainSel, int nSpdLoopSel)
{
	st_ClampTorqueMove stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisindex = nAxisindex;
	stArg.nStartAxisNo = nStartAxisNo;
	stArg.dTorque = dTorque;
	stArg.dVel = dVel;
	stArg.nAccFilterSel = nAccFilterSel;
	stArg.nGainSel = nGainSel;
	stArg.nSpdLoopSel = nSpdLoopSel;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(ClampTorqueMove_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_ClampTorqueMoveStop { int nAxisNo; int nMethod; } st_ClampTorqueMoveStop;
int CClientInterface::ClampTorqueMoveStop(int nAxisindex, int nStartAxisNo, int nMethod)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampTorqueMoveStop stArg;

	stArg.nAxisindex = nAxisindex;
	stArg.nStartAxisNo = nStartAxisNo;
	stArg.nMethod = nMethod;

	SendWriteCommandData(ClampTorqueMoveStop_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

#else

//typedef struct tag_ClampTorqueMove { int nAxisNo; double dTorque; double dVel; int nAccFilterSel; int nGainSel; int nSpdLoopSel; } st_ClampTorqueMove;
int CClientInterface::ClampTorqueMove(int nAxisindex, double dTorque, double dVel, int nAccFilterSel, int nGainSel, int nSpdLoopSel)
{
	st_ClampTorqueMove stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.nAxisindex = nAxisindex;
	stArg.dTorque = dTorque;
	stArg.dVel = dVel;
	stArg.nAccFilterSel = nAccFilterSel;
	stArg.nGainSel = nGainSel;
	stArg.nSpdLoopSel = nSpdLoopSel;


	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(ClampTorqueMove_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_ClampTorqueMoveStop { int nAxisNo; int nMethod; } st_ClampTorqueMoveStop;
int CClientInterface::ClampTorqueMoveStop(int nAxisindex, int nMethod)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampTorqueMoveStop stArg;

	stArg.nAxisindex = nAxisindex;
	stArg.nMethod = nMethod;

	SendWriteCommandData(ClampTorqueMoveStop_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}
#endif

//typedef struct tag_ClampTorqueSetRead { int nAxisNo; int nSelMon; } st_ClampTorqueSetRead;
int CClientInterface::ClampTorqueSetRead(int nAxisNo, int nSelMon)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampTorqueSetRead stArg;
	
	stArg.nAxisNo = nAxisNo;
	stArg.nSelMon = nSelMon;
	SendWriteCommandData(ClampTorqueSetRead_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}
//typedef struct tag_ClampTorqueRead { int nAxisNo; double dMonitorValue; } st_ClampTorqueRead;
int CClientInterface::ClampTorqueRead()
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ClampTorqueRead stArg;
	SendReceiveCommandData(ClampTorqueRead_Func, (byte*)&stArg, sizeof(stArg));
	return FMM_SUCCESS;
}

//typedef struct tag_AoiPosMove { double dPos[2]; double dVel[2]; double dAccel[2]; double dDecel[2]; int nAbsRelMode; } st_AoiPosMove;
int CClientInterface::AoiPosMove( double dPos[2], double dVel[2], double dAccel[2], double dDecel[2], int nAbsRelMode)
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AoiPosMove stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.dPos[0] = dPos[0];
	stArg.dPos[1] = dPos[1];

	stArg.dVel[0] = dVel[0];
	stArg.dVel[1] = dVel[1];

	stArg.dAccel[0] = dAccel[0];
	stArg.dAccel[1] = dAccel[1];

	stArg.dDecel[0] = dDecel[0];
	stArg.dDecel[1] = dDecel[1];

	stArg.nAbsRelMode = nAbsRelMode;
	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AoiPosMove_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AoiPosMove_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}

//typedef struct tag_AoiMoveStop { double dDecel[2]; } st_AoiMoveStop;
int CClientInterface::AoiMoveStop(double dDecel[2])
{
	//GetCommStatus();

	//m_ClientMutex.Lock();

	//GetCommStatus();

	//byte bySendData[MAX_PAKET_NUM] = { 0 };
	//byte byArgData[MAX_PAKET_NUM] = { 0 };
	//int nSendSize;

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_AoiMoveStop stArg;

	//pDlg->m_nSocketReceiveFlag = FALSE;
	//m_nCount = 0;

	stArg.dDecel[0] = dDecel[0];
	stArg.dDecel[1] = dDecel[1];
	
	//memcpy(byArgData, (byte*)&stArg, sizeof(stArg));

	SendWriteCommandData(AoiMoveStop_Func, (byte*)&stArg, sizeof(stArg));
		
	//nSendSize = pDlg->m_ModbusData.SendDataEx(AoiMoveStop_Func, 0, (byte*)&stArg, sizeof(stArg), 1, bySendData);
	//pDlg->m_SocketManager.SendDataEx((char*)bySendData, nSendSize);

	//while (pDlg->m_nSocketReceiveFlag == FALSE && m_nCount < MAX_COUNT)
	//{
	//	m_nCount++;
	//	Sleep(0);
	//}

	//m_ClientMutex.Unlock();
	
	return FMM_SUCCESS;
}


//typedef struct tag_PitchHomeStart { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; } st_PitchHomeStart;
//int CClientInterface::PitchHomeStart(int nAxisSize, int nAxisNo[MAX_STRETCH_AXIS_SIZE])
//{
//	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
//	//st_PitchHomeStart stArg;
//
//	//int i;
//
//	//stArg.nAxisSize = nAxisSize;
//	//for (i = 0; i < nAxisSize; i++)
//	//{
//	//	stArg.nAxisNo[i] = nAxisNo[i];
//	//}
//
//	//SendCommandData(PitchHomeStart_Func, (byte*)&stArg, sizeof(stArg));
//
//	return FMM_SUCCESS;
//}


//typedef struct tag_PitchMoveStop { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dDecel; } st_PitchStop;
//int CClientInterface::PitchMoveStop(int nAxisSize, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dDecel)
//{
//	//CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
//	//st_PitchMoveStop stArg;
//
//	//int i;
//
//	//stArg.nAxisSize = nAxisSize;
//	//for (i = 0; i < nAxisSize; i++)
//	//{
//	//	stArg.nAxisNo[i] = nAxisNo[i];
//	//}
//
//	//stArg.dDecel = dDecel;
//
//	//SendCommandData(PitchMoveStop_Func, (byte*)&stArg, sizeof(stArg));
//
//	return FMM_SUCCESS;
//}

//typedef struct tag_PitchPosMove { int nAxisIndex;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel; } st_PitchPosMove;
int CClientInterface::PitchPosMove(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE], double dCmdVel)
{
	st_PitchPosMove stArg;
	
	stArg.nAxisIndex = nAxisIndex;

	for (int i=0; i< MAX_STRETCH_AXIS_SIZE; i++)
	{
		stArg.nAxisNo[i] = nAxisNo[i];
		stArg.dTargetPos[i] = dTargetPos[i];
	}

	stArg.dCmdVel = dCmdVel;

	SendWriteCommandData(PitchPosMove_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_PitchPosMove { int nAxisIndex;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel; } st_PitchPosMove;
int CClientInterface::StretchPosMove(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE], double dCmdVel)
{
	st_StretchPosMove stArg;

	stArg.nAxisIndex = nAxisIndex;

	for (int i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
	{
		stArg.nAxisNo[i] = nAxisNo[i];
		stArg.dTargetPos[i] = dTargetPos[i];
	}

	stArg.dCmdVel = dCmdVel;

	SendWriteCommandData(StretchPosMove_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_PitchGetStatus { int nAxisNo;  int nStatus; } st_PitchGetStatus;
//int CClientInterface::PitchGetStatus(int nAxisNo, int nStatus)
//{
//	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
//	st_PitchGetStatus stArg;
//
//	stArg.nAxisNo = nAxisNo;
//
//	SendCommandData(PitchGetStatus_Func, (byte*)&stArg, sizeof(stArg));
//
//	return FMM_SUCCESS;
//}





//typedef struct tag_st_ForceData { double dCF_LoadcellForce[MAX_CF_NUM + MAX_CENTERING_NUM]; double dSF_LoadcellForce[MAX_SF_NUM]; } st_ForceData;
int CClientInterface::GetForceData()
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_ForceData stArg;
	SendReceiveCommandData(GetForceData_Func, (byte*)&stArg, sizeof(stArg));


	return FMM_SUCCESS;
}

//typedef struct tag_st_StretchForceZero { int nCh; } st_StretchForceZero;
int CClientInterface::StretchForceZero(int nForceNo)
{
	CString Str = _T("");
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_StretchForceZero stArg;
	stArg.nCh = nForceNo;

	Str.Format(_T("Stretch Force Zero: %d"), stArg.nCh);
	Total_Msg(Str);
	SendWriteCommandData(StretchForceZero_Func, (byte*)&stArg, sizeof(stArg));
	
	return FMM_SUCCESS;
}

//typedef struct tag_st_FrameForceZero { int nCh; } st_FrameForceZero;
int CClientInterface::FrameForceZero(int nForceNo)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_FrameForceZero stArg;
	SendWriteCommandData(FrameForceZero_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}


int CClientInterface::AjinGantryEnable(void *pArg)
{

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	tag_AjinGantryEnable stArg;
	SendWriteCommandData(AjinGantryEnable_Func, (byte*)&stArg, sizeof(stArg));


	return FMM_SUCCESS;
}


int CClientInterface::AjinGantryDisable(void *pArg)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	tag_AjinGantryDisable stArg;

	SendWriteCommandData(AjinGantryDisable_Func, (byte*)&stArg, sizeof(stArg));
	
	return FMM_SUCCESS;
}

int CClientInterface::CenteringPosMove(double *dPos)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	st_CenteringPosMove stArg;
	
	//
	stArg.dX = dPos[0];
	stArg.dY = dPos[1];
	stArg.dT = dPos[2];

	SendWriteCommandData(CenteringPosMove_Func, (byte*)&stArg, sizeof(stArg));
	
	return FMM_SUCCESS;
}

int CClientInterface::GetAllOtherAlarm()
{
	tag_OtherAlarm stArg;

	SendReceiveCommandData(GetOtherAlarm_Func, (byte*)&stArg, sizeof(stArg));

	return FMM_SUCCESS;
}

//typedef struct tag_st_GetLightState  { int nCameraIndex; int nLightValue[2]; bool bOnOff; bool bCtrlDone; } st_GetLightState;
//int CClientInterface::GetLightState(int nCameraIndex)
//{
//	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
//	st_GetLightState stArg;
//	int nSize = sizeof(stArg);
//
//
//	stArg.nCameraIndex = nCameraIndex;
//
//	SendVisionReceiveCommandData(GetLightState_Func, (byte*)&stArg, sizeof(stArg));
//
//	return FMM_SUCCESS;
//}