// SocketManager.cpp: implementation of the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SocketManager.h"
#include "../Vision/SharedInfo.h"
#include "VisionAgentDlg.h"
//#include "../VisionAgentDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketManager::CSocketManager()
{
	m_bIsReceiveData = 0;
	m_pParentDlg = NULL;
}


CSocketManager::~CSocketManager()
{
	if (m_chReceiveData !=NULL)
		memset(m_chReceiveData, 0, sizeof(char)*MAX_PAKET_NUM);
}

int CSocketManager::SetParentDlg(void *pDlg)
{
	m_pParentDlg = pDlg;

	return 1;
}


void CSocketManager::OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount)
{
	LPBYTE lpData = lpBuffer;
	dwCount -= 2;

	if (dwCount >= MAX_PAKET_NUM) dwCount = dwCount - 1;

	lpBuffer[dwCount] = 0;

	m_dwCount = dwCount;

	SocketDataReceive((char*)lpBuffer, m_dwCount);

	m_bIsReceiveData = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// OnEvent
// Send message to parent window to indicate connection status
void CSocketManager::OnEvent(UINT uEvent, LPVOID lpvData)
{
	switch (uEvent){
		case EVT_CONSUCCESS:
			//AppendMessage( _T("Connection Established\r\n") );
			break;
		case EVT_CONFAILURE:
			//AppendMessage( _T("Connection Failed\r\n") );
			break;
		case EVT_CONDROP:
			//AppendMessage( _T("Connection Abandonned\r\n") );
			break;
		case EVT_ZEROLENGTH:
			//AppendMessage( _T("Zero Length Message\r\n") );
			break;
		default:
			//TRACE("Unknown Socket event\n");
			break;
	}
}

int CSocketManager::SendData(const CString* str)
{
	BYTE byBuffer[MAX_PAKET_NUM] = { 0 };
	CString strText = *str;

	int nLen = strText.GetLength();

	if (nLen > 0){
		m_strSendData = strText;
		strText += _T("\r\n");
		nLen = strText.GetLength() + 1;
		USES_CONVERSION;
		strcpy_s(reinterpret_cast<LPSTR>(byBuffer), MAX_PAKET_NUM, T2CA(strText));
		return WriteComm(byBuffer, nLen, INFINITE);
	}

	return 0;
}


int CSocketManager::SendDataEx(char* chData, int nSize)
{	
	if (nSize > 0){
		*(chData + nSize + 0) = '\r';
		*(chData + nSize + 1) = '\n';
		*(chData + nSize + 2) = 0;
		nSize += 3;

		return WriteComm((LPBYTE)chData, nSize, INFINITE);
	}

	return 0;
}


int CSocketManager::GetReceiveData(char* chData)
{
	if (m_bIsReceiveData == 0){
		memset(m_chReceiveData, 0, sizeof(m_chReceiveData));
		return FALSE;
	}

	memcpy(chData, m_chReceiveData, sizeof(m_chReceiveData));
	memset(m_chReceiveData, 0, sizeof(m_chReceiveData));

	m_bIsReceiveData = 0;
	return TRUE;
}

void CSocketManager::SocketDataReceive(char* chData, int nCount)
{
	CString Str;
	int i, nRtn;
	char *pReceiveData;
	m_chReceiveData = chData;
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)m_pParentDlg;
	//memcpy(m_chReceiveData, m_SocketManager.m_chReceiveData, nCount);
	m_nFuncAddr = UNKNOWN_SHM_FUNCTION;
	nRtn = ReceiveDataEx(m_chReceiveData, &m_nFuncAddr, &m_nReturn, m_byArg);
	m_byArg = (byte*)(m_chReceiveData + 12);

	if (m_nFuncAddr == UNKNOWN_SHM_FUNCTION)
		return;

	if (nRtn != FMM_SUCCESS)
	{
		Str.Format(_T("Error % d : nRtn = %d"), m_nFuncAddr, nRtn);
		Etc_Msg(Str);
	}
	if (nRtn == FMM_SUCCESS)
	{
		//Log_Msg(_T("Receive Data : %d"), m_nFuncAddr);
		switch (m_nFuncAddr)
		{
			//typedef struct tag_SystemGetMaxAxisSize { int nMaxAxisSize; } st_SystemGetMaxAxisSize;
		case SystemGetMaxAxisSize_Func:
		{
			st_SystemGetMaxAxisSize stArg;

			stArg = *((st_SystemGetMaxAxisSize*)(void*)m_byArg);
			SharedInfo::MaxAxisSize = stArg.nMaxAxisSize;
			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetMaxDInputSize { int nMaxDInputSize; } st_SystemGetMaxDInputSize;
		case SystemGetMaxDInputSize_Func:
		{
			st_SystemGetMaxDInputSize stArg;

			stArg = *((st_SystemGetMaxDInputSize*)(void*)m_byArg);

			SharedInfo::MaxDInputSize = stArg.nMaxDInputSize;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetMaxDOutputSize { int nMaxDOutputSize; } st_SystemGetMaxDOutputSize;
		case SystemGetMaxDOutputSize_Func:
		{
			st_SystemGetMaxDOutputSize stArg;

			stArg = *((st_SystemGetMaxDOutputSize*)(void*)m_byArg);
			SharedInfo::MaxDOutputSize = stArg.nMaxDOutputSize;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetMaxAInputSize { int nMaxAInputSize; } st_SystemGetMaxAInputSize;
		case SystemGetMaxAInputSize_Func:
		{
			st_SystemGetMaxAInputSize stArg;

			stArg = *((st_SystemGetMaxAInputSize*)(void*)m_byArg);
			SharedInfo::MaxAInputSize = stArg.nMaxAInputSize;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetMaxAOutputSize { int nMaxAOutputSize; } st_SystemGetMaxAOutputSize;
		case SystemGetMaxAOutputSize_Func:
		{
			st_SystemGetMaxAOutputSize stArg;

			stArg = *((st_SystemGetMaxAOutputSize*)(void*)m_byArg);
			SharedInfo::MaxAOutputSize = stArg.nMaxAOutputSize;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetHomeStatus{ int nHomeStatus; } st_SystemGetHomeStatus;
		case SystemGetHomeStatus_Func:
		{
			st_SystemGetHomeStatus stArg;

			stArg = *((st_SystemGetHomeStatus*)(void*)m_byArg);
			SharedInfo::SystemHomeStatus = stArg.nHomeStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetHomeSignal{ int nHomeSignal; } st_SystemGetHomeSignal;
		case SystemGetHomeSignal_Func:
		{
			st_SystemGetHomeSignal stArg;

			stArg = *((st_SystemGetHomeSignal*)(void*)m_byArg);
			SharedInfo::SystemHomeSignal = stArg.nHomeSignal;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetLimitSignal{ int nPosSignal; int nNegSignal; } st_SystemGetLimitSignal;
		case SystemGetLimitSignal_Func:
		{
			st_SystemGetLimitSignal stArg;

			stArg = *((st_SystemGetLimitSignal*)(void*)m_byArg);
			SharedInfo::SystemPLimitSignal = stArg.nPosSignal;
			SharedInfo::SystemNLimitSignal = stArg.nNegSignal;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetServoOnStatus{ int nStatus; } st_SystemGetServoOnStatus;
		case SystemGetServoOnStatus_Func:
		{
			st_SystemGetServoOnStatus stArg;

			stArg = *((st_SystemGetServoOnStatus*)(void*)m_byArg);
			SharedInfo::SystemServoOnStatus = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetAlarmStatus{ int nStatus; } st_SystemGetAlarmStatus;
		case SystemGetAlarmStatus_Func:
		{
			st_SystemGetAlarmStatus stArg;

			stArg = *((st_SystemGetAlarmStatus*)(void*)m_byArg);
			SharedInfo::SystemAlarmStatus = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetMotionDoneStatus{ int nStatus; } st_SystemGetMotionDoneStatus;
		case SystemGetMotionDoneStatus_Func:
		{
			st_SystemGetMotionDoneStatus stArg;

			stArg = *((st_SystemGetMotionDoneStatus*)(void*)m_byArg);
			SharedInfo::SystemMotionDoneStatus = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemMoveStop{ int nSystemNo; } st_SystemMoveStop;
		case SystemMoveStop_Func:
		{
			//st_SystemMoveStop stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_SystemGetStatus{ int nSystemNo; int nStatus; } st_SystemGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
		case SystemGetStatus_Func:
		{
			st_SystemGetStatus stArg;

			stArg = *((st_SystemGetStatus*)(void*)m_byArg);
			SharedInfo::SystemStatus = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UmacPosMove { int nAxisNo; double dPos; double dVel; double dAccel; double dDecel; int nAbsRelMode; int nBackLightMove; double dAOICamOffset; BOOL bDirBwd; int nBackLightFwdDelay; int nBackLightBwdDelay; double dBackLightFwdAccDccScale; double dBackLightBwdAccDccScale; } st_UmacPosMove; //KJT 20200929
		case UmacPosMove_Func:
		{
			//st_UmacPosMove stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacVelMove { int nAxisNo; double dVel; double dAccel; double dDecel; int nBackLightMove; } st_UmacVelMove; //KJT 20200929
		case UmacVelMove_Func:
		{
			//st_UmacVelMove stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacMoveStop { int nAxisNo; double dDecel; int nBackLightMove; } st_UmacMoveStop; //KJT 20200824
		case UmacMoveStop_Func:
		{
			//st_UmacMoveStop stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacHomeStart { int nAxisNo; } st_UmacHomeStart;
		case UmacHomeStart_Func:
		{
			//st_UmacHomeStart stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacSetServoOnStatus { int nAxisNo; int nServoOnStatus; } st_UmacSetServoOnStatus;
		case UmacSetServoOnStatus_Func:
		{
			//st_UmacSetServoOnStatus stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacSetAlarmClear { int nAxisNo; int nAlarmClear; } st_UmacSetAlarmClear;
		case UmacSetAlarmClear_Func:
		{
			//st_UmacSetAlarmClear stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		// typedef struct tag_UmacGetCmdPos{ int nAxisNo; double dPos; } st_UmacGetCmdPos;
		case UmacGetCmdPos_Func:
		{
			st_UmacGetCmdPos stArg;

			stArg = *((st_UmacGetCmdPos*)(void*)m_byArg);
			//m_dRemoteAxisUmacCmdPos[stArg.nAxisNo] = stArg.dPos;

			//SharedInfo::dConnectionCheckTimer = GetTickCount();

			memcpy(SharedInfo::UmacCmdPos, stArg.dPos, sizeof(double)*MAX_UMAC_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		// typedef struct tag_UmacGetActPos{ int nAxisNo; double dPos; } st_UmacGetActPos;
		case UmacGetActPos_Func:
		{
			st_UmacGetActPos stArg;

			stArg = *((st_UmacGetActPos*)(void*)m_byArg);
			//m_dRemoteAxisUmacActPos[stArg.nAxisNo] = stArg.dPos;
			memcpy(SharedInfo::UmacActPos, stArg.dPos, sizeof(double)*MAX_UMAC_AXIS_SIZE);
			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacGetCmdVel{ int nAxisNo; double dVel; } st_UmacGetCmdVel;
		case UmacGetCmdVel_Func:
		{
			st_UmacGetCmdVel stArg;

			stArg = *((st_UmacGetCmdVel*)(void*)m_byArg);
			//m_dRemoteAxisUmacCmdVel[stArg.nAxisNo] = stArg.dVel;
			memcpy(SharedInfo::UmacCmdVel, stArg.dVel, sizeof(double)*MAX_UMAC_AXIS_SIZE);
			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacGetHomeStatus{ int nAxisNo; int nHomeStatus; } st_UmacGetHomeStatus;
		case UmacGetHomeStatus_Func:
		{
			st_UmacGetHomeStatus stArg;

			stArg = *((st_UmacGetHomeStatus*)(void*)m_byArg);
			//m_nRemoteAxisUmacHomeStatus[stArg.nAxisNo] = stArg.nHomeStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacGetHomeSignal{ int nAxisNo; int nHomeSignal; } st_UmacGetHomeSignal;
		case UmacGetHomeSignal_Func:
		{
			st_UmacGetHomeSignal stArg;

			stArg = *((st_UmacGetHomeSignal*)(void*)m_byArg);
			//m_nRemoteAxisUmacHomeSignal[stArg.nAxisNo] = stArg.nHomeSignal;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacGetLimitSignal{ int nAxisNo; int nPosSignal; int nNegSignal; } st_UmacGetLimitSignal;
		case UmacGetLimitSignal_Func:
		{
			st_UmacGetLimitSignal stArg;

			stArg = *((st_UmacGetLimitSignal*)(void*)m_byArg);
			//m_nRemoteAxisUmacPLimitSignal[stArg.nAxisNo] = stArg.nPosSignal;
			//m_nRemoteAxisUmacNLimitSignal[stArg.nAxisNo] = stArg.nNegSignal;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacGetServoOnStatus{ int nAxisNo; int nStatus; } st_UmacGetServoOnStatus;
		case UmacGetServoOnStatus_Func:
		{
			st_UmacGetServoOnStatus stArg;

			stArg = *((st_UmacGetServoOnStatus*)(void*)m_byArg);
			//m_nRemoteAxisUmacServoOnStatus[stArg.nAxisNo] = stArg.nStatus;
			//pDlg->m_nSocketReceiveFlag = TRUE;

			break;
		}
		//typedef struct tag_UmacGetAlarmStatus{ int nAxisNo; int nStatus; } st_UmacGetAlarmStatus;
		case UmacGetAlarmStatus_Func:
		{
			st_UmacGetAlarmStatus stArg;

			stArg = *((st_UmacGetAlarmStatus*)(void*)m_byArg);
			//m_nRemoteAxisUmacAlarmStatus[stArg.nAxisNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UmacGetMotionDoneStatus{ int nAxisNo; int nStatus; } st_UmacGetMotionDoneStatus;
		case UmacGetMotionDoneStatus_Func:
		{
			st_UmacGetMotionDoneStatus stArg;

			stArg = *((st_UmacGetMotionDoneStatus*)(void*)m_byArg);
			//m_nRemoteAxisUmacInMotionStatus[stArg.nAxisNo] = !stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UmacGetStatus{ int nAxisNo; int nStatus; } st_UmacGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
		case UmacGetStatus_Func:
		{
			st_UmacGetStatus stArg;
			BOOL bFlag = TRUE;

			stArg = *((st_UmacGetStatus*)(void*)m_byArg);

			memcpy(SharedInfo::UmacStatus, stArg.nStatus, sizeof(int)* MAX_UMAC_AXIS_SIZE);
			for (int i = 0; i < MAX_UMAC_AXIS_SIZE; i++)
			{
				SharedInfo::UmacHomeStatus[i] = (SharedInfo::UmacStatus[i] >> 0) & 0x01;
				SharedInfo::UmacServoOnStatus[i] = (SharedInfo::UmacStatus[i] >> 1) & 0x01;
				SharedInfo::UmacAlarmStatus[i] = (SharedInfo::UmacStatus[i] >> 2) & 0x01;
				SharedInfo::UmacInMotionStatus[i] = !((SharedInfo::UmacStatus[i] >> 3) & 0x01);

				//20201030 KJT Add
				if (i == REMOTE_UMAC_GANTRY_X || i == REMOTE_UMAC_GANTRY_VIRTUAL_Y)
				{
					if (!SharedInfo::UmacHomeStatus[i] || !SharedInfo::UmacServoOnStatus[i] || SharedInfo::UmacAlarmStatus[i] || SharedInfo::UmacInMotionStatus[i])
					{
						bFlag = FALSE;
					}
				}
			}
#ifndef SIM_MODE
			SharedInfo::bRemoteUmacSystemReadyStatus = bFlag; //20201030 KJT Add
#else
			SharedInfo::bRemoteUmacSystemReadyStatus = TRUE;
#endif

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisPosMove { int nAxisNo; double dPos; double dVel; double dAccel; double dDecel; int nAbsRelMode; } st_AxisPosMove;
		case AxisPosMove_Func:
		{
			//st_AxisPosMove stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisVelMove { int nAxisNo; double dVel; double dAccel; double dDecel; } st_AxisVelMove;
		case AxisVelMove_Func:
		{
			//st_AxisVelMove stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisMoveStop { int nAxisNo; double dDecel; } st_AxisMoveStop;
		case AxisMoveStop_Func:
		{
			//st_AxisMoveStop stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisHomeStart { int nAxisNo; } st_AxisHomeStart;
		case AxisHomeStart_Func:
		{
			//st_AxisHomeStart stArg;
//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_AxisSignalSearch { int nAxisNo; double dVel; double dAccel; int nDetectSignal; int nSignalEdge; int nSignalMethod; } st_AxisSignalSearch;
		case AxisSignalSearch_Func:
		{
			//st_AxisSignalSearch stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_AxisSetServoOnStatus { int nAxisNo; int nServoOnStatus; } st_AxisSetServoOnStatus;
		case AxisSetServoOnStatus_Func:
		{
			//st_AxisSetServoOnStatus stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisSetAlarmClear { int nAxisNo; int nAlarmClear; } st_AxisSetAlarmClear;
		case AxisSetAlarmClear_Func:
		{
			//st_AxisSetAlarmClear stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_AxisSetCmdPos{ int nAxisNo; double dPos; } st_AxisSetCmdPos;
		case AxisSetCmdPos_Func:
		{
			st_AxisSetCmdPos stArg;

			stArg = *((st_AxisSetCmdPos*)(void*)m_byArg);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetCmdPos{ int nAxisNo; double dPos; } st_AxisGetCmdPos;
		case AxisGetCmdPos_Func:
		{
			st_AxisGetCmdPos stArg;

			stArg = *((st_AxisGetCmdPos*)(void*)m_byArg);
			memcpy(SharedInfo::AxisCmdPos, stArg.dPos, sizeof(double)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetActPos{ int nAxisNo; double dPos; } st_AxisGetCmdPos;
#if 1
		case AxisGetActPos_Func:
		{
			st_AxisGetActPos stArg;

			stArg = *((st_AxisGetActPos*)(void*)m_byArg);
			memcpy(SharedInfo::AxisActPos, stArg.dPos, sizeof(double)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
#endif

		//typedef struct tag_AxisGetCmdVel{ int nAxisNo; double dVel; } st_AxisGetCmdVel;
		case AxisGetCmdVel_Func:
		{
			st_AxisGetCmdVel stArg;

			stArg = *((st_AxisGetCmdVel*)(void*)m_byArg);
			memcpy(SharedInfo::AxisCmdVel, stArg.dVel, sizeof(double)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetHomeResult{ int nAxisNo; int nHomeResult; } st_AxisGetHomeResult;
		case AxisGetHomeResult_Func:
		{
			st_AxisGetHomeResult stArg;

			stArg = *((st_AxisGetHomeResult*)(void*)m_byArg);
			memcpy(SharedInfo::AxisHomeResult, stArg.nHomeResult, sizeof(int)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetHomeStatus{ int nAxisNo; int nHomeStatus; } st_AxisGetHomeStatus;
		case AxisGetHomeStatus_Func:
		{
			st_AxisGetHomeStatus stArg;

			stArg = *((st_AxisGetHomeStatus*)(void*)m_byArg);
			memcpy(SharedInfo::AxisHomeStatus, stArg.nHomeStatus, sizeof(int)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetHomeSignal{ int nAxisNo; int nHomeSignal; } st_AxisGetHomeSignal;
		case AxisGetHomeSignal_Func:
		{
			st_AxisGetHomeSignal stArg;

			stArg = *((st_AxisGetHomeSignal*)(void*)m_byArg);
			memcpy(SharedInfo::AxisHomeSignal, stArg.nHomeSignal, sizeof(int)*MAX_AXIS_SIZE);


			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetLimitSignal{ int nAxisNo; int nPosSignal; int nNegSignal; } st_AxisGetLimitSignal;
		case AxisGetLimitSignal_Func:
		{
			st_AxisGetLimitSignal stArg;

			stArg = *((st_AxisGetLimitSignal*)(void*)m_byArg);
			memcpy(SharedInfo::AxisPLimitSignal, stArg.nPosSignal, sizeof(int)*MAX_AXIS_SIZE);
			memcpy(SharedInfo::AxisNLimitSignal, stArg.nNegSignal, sizeof(int)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetServoOnStatus{ int nAxisNo; int nStatus; } st_AxisGetServoOnStatus;
		case AxisGetServoOnStatus_Func:
		{
			st_AxisGetServoOnStatus stArg;

			stArg = *((st_AxisGetServoOnStatus*)(void*)m_byArg);
			memcpy(SharedInfo::AxisServoOnStatus, stArg.nStatus, sizeof(int)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetAlarmStatus{ int nAxisNo; int nStatus; } st_AxisGetAlarmStatus;
		case AxisGetAlarmStatus_Func:
		{
			st_AxisGetAlarmStatus stArg;

			stArg = *((st_AxisGetAlarmStatus*)(void*)m_byArg);
			memcpy(SharedInfo::AxisAlarmStatus, stArg.nStatus, sizeof(int)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AxisGetMotionDoneStatus{ int nAxisNo; int nStatus; } st_AxisGetMotionDoneStatus;
		case AxisGetMotionDoneStatus_Func:
		{
			st_AxisGetMotionDoneStatus stArg;

			stArg = *((st_AxisGetMotionDoneStatus*)(void*)m_byArg);
			memcpy(SharedInfo::AxisInMotionStatus, stArg.nStatus, sizeof(int)*MAX_AXIS_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_AxisGetStatus{ int nAxisNo; int nStatus; } st_AxisGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
		case AxisGetStatus_Func:
		{
			st_AxisGetStatus stArg;
			BOOL bFlag = TRUE;

			stArg = *((st_AxisGetStatus*)(void*)m_byArg);

			memcpy(SharedInfo::AxisStatus, stArg.nStatus, sizeof(int)*MAX_AXIS_SIZE);
			for (int i = 0; i < MAX_AXIS_SIZE; i++)
			{
				SharedInfo::AxisHomeStatus[i] = (SharedInfo::AxisStatus[i] >> 0) & 0x01;
				SharedInfo::AxisServoOnStatus[i] = (SharedInfo::AxisStatus[i] >> 1) & 0x01;
				SharedInfo::AxisAlarmStatus[i] = (SharedInfo::AxisStatus[i] >> 2) & 0x01;
				SharedInfo::AxisInMotionStatus[i] = !((SharedInfo::AxisStatus[i] >> 3) & 0x01);

				if (!SharedInfo::AxisHomeStatus[i] || !SharedInfo::AxisServoOnStatus[i] || SharedInfo::AxisAlarmStatus[i] || SharedInfo::AxisInMotionStatus[i])
				{
					bFlag = FALSE;
				}
			}
#ifndef SIM_MODE
			SharedInfo::bRemoteAjinSystemReadyStatus = bFlag; //20201030 KJT Add
#else
			SharedInfo::bRemoteAjinSystemReadyStatus = TRUE;
#endif

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwSetAxisNo { int nUvwNo; int nUvwAxisNo[3]; } st_UvwSetAxisNo;
		case UvwSetAxisNo_Func:
		{
			//st_UvwSetAxisNo stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwPosMove { int nUvwNo; double dPos[3]; double dVel[3]; double dAccel[3]; double dDecel[3]; int nAbsRelMode; } st_UvwPosMove;
		case UvwPosMove_Func:
		{
			//st_UvwPosMove stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwMoveStop { int nUvwNo; double dDecel[3]; } st_UvwMoveStop;
		case UvwMoveStop_Func:
		{
			//st_UvwMoveStop stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwHomeStart { int nUvwNo; int nAxisNo; } st_UvwHomeStart;
		case UvwHomeStart_Func:
		{
			//st_UvwHomeStart stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwSetServoOnStatus { int nUvwNo; int nAxisNo; int nServoOnStatus; } st_UvwSetServoOnStatus;
		case UvwSetServoOnStatus_Func:
		{
			//st_UvwSetServoOnStatus stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwSetAlarmClear { int nUvwNo; int nAxisNo; int nAlarmClear; } st_UvwSetAlarmClear;
		case UvwSetAlarmClear_Func:
		{
			//st_UvwSetAlarmClear stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwSetCmdPos{ int nUvwNo; int nAxisNo; double dPos; } st_UvwSetCmdPos;
		case UvwSetCmdPos_Func:
		{
			//st_UvwSetCmdPos stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwGetCmdPos { int nUvwNo; double dPos[3]; } st_UvwGetCmdPos;
		case UvwGetCmdPos_Func:
		{
			st_UvwGetCmdPos stArg;

			stArg = *((st_UvwGetCmdPos*)(void*)m_byArg);

			SharedInfo::UvwCmdPos[stArg.nUvwNo][0] = stArg.dPos[0];
			SharedInfo::UvwCmdPos[stArg.nUvwNo][1] = stArg.dPos[1];					
			SharedInfo::UvwCmdPos[stArg.nUvwNo][2] = stArg.dPos[2];			
			

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwGetCmdVel { int nUvwNo; double dVel[3]; } st_UvwGetCmdVel;
		case UvwGetCmdVel_Func:
		{
			st_UvwGetCmdVel stArg;

			stArg = *((st_UvwGetCmdVel*)(void*)m_byArg);

			//m_dUvwCmdVel[stArg.nUvwNo][0] = stArg.dVel[0];
			//m_dUvwCmdVel[stArg.nUvwNo][1] = stArg.dVel[1];
			//m_dUvwCmdVel[stArg.nUvwNo][2] = stArg.dVel[2];

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwGetHomeStatus{ int nUvwNo; int nStatus; } st_UvwGetHomeStatus;
		case UvwGetHomeStatus_Func:
		{
			st_UvwGetHomeStatus stArg;

			stArg = *((st_UvwGetHomeStatus*)(void*)m_byArg);

			//			m_nUvwHomeStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwGetServoOnStatus{ int nUvwNo; int nStatus; } st_UvwGetServoOnStatus;
		case UvwGetServoOnStatus_Func:
		{
			st_UvwGetServoOnStatus stArg;

			stArg = *((st_UvwGetServoOnStatus*)(void*)m_byArg);

			//		m_nUvwServoOnStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwGetAlarmStatus{ int nUvwNo; int nStatus; } st_UvwGetAlarmStatus;
		case UvwGetAlarmStatus_Func:
		{
			st_UvwGetAlarmStatus stArg;

			stArg = *((st_UvwGetAlarmStatus*)(void*)m_byArg);

			//			m_nUvwAlarmStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwGetMotionDoneStatus{ int nUvwNo; int nStatus; } st_UvwGetMotionDoneStatus;
		case UvwGetMotionDoneStatus_Func:
		{
			st_UvwGetMotionDoneStatus stArg;

			stArg = *((st_UvwGetMotionDoneStatus*)(void*)m_byArg);

			SharedInfo::UvwMotionDoneStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UvwGetStatus{ int nUvwNo; int nStatus; } st_UvwGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
		case UvwGetStatus_Func:
		{
			st_UvwGetStatus stArg;

			stArg = *((st_UvwGetStatus*)(void*)m_byArg);

			//			m_nUvwStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwXYTSetZero { int nUvwNo; } st_UvwXYTSetZero; //KJT 20200820
		case UvwXYTSetZero_Func:
		{
			tag_UvwXYTSetZero stArg;

			stArg = *((tag_UvwXYTSetZero*)(void*)m_byArg);

			break;
		}

		//typedef struct tag_UvwGetTargetPos { int nUvwNo; } st_UvwGetTargetPos; //KJT 20200912
		case UvwGetTargetPos_Func:
		{
			tag_UvwGetTargetPos stArg;

			stArg = *((tag_UvwGetTargetPos*)(void*)m_byArg);
			
			SharedInfo::dUVWTargetPos[stArg.nUvwNo][0] = stArg.dPos[0];
			SharedInfo::dUVWTargetPos[stArg.nUvwNo][1] = stArg.dPos[1];
			SharedInfo::dUVWTargetPos[stArg.nUvwNo][2] = stArg.dPos[2];

			break;
		}

		//typedef struct tag_UvwTargetPosMove { int nUvwNo; } st_UvwTargetPosMove; //KJT 20201012
		case UvwTargetPosMove_Func:
		{
			//tag_UvwTargetPosMove stArg;

			//stArg = *((tag_UvwTargetPosMove*)(void*)m_byArg);

			break;
		}

		//Uvwx
		//typedef struct tag_UvwxSetAxisNo { int nUvwNo; int nUvwAxisNo[4]; } st_UvwxSetAxisNo;
		case UvwxSetAxisNo_Func:
		{
			//st_UvwxSetAxisNo stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxPosMove { int nUvwNo; double dPos[4]; double dVel[4]; double dAccel[4]; double dDecel[4]; int nAbsRelMode; } st_UvwxPosMove;
		case UvwxPosMove_Func:
		{
			//st_UvwxPosMove stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxMoveStop { int nUvwNo; double dDecel[4]; } st_UvwxMoveStop;
		case UvwxMoveStop_Func:
		{
			//st_UvwxMoveStop stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxHomeStart { int nUvwNo; int nAxisNo; } st_UvwxHomeStart;
		case UvwxHomeStart_Func:
		{
			//st_UvwxHomeStart stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxSetServoOnStatus { int nUvwNo; int nAxisNo; int nServoOnStatus; } st_UvwxSetServoOnStatus;
		case UvwxSetServoOnStatus_Func:
		{
			//st_UvwxSetServoOnStatus stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxSetAlarmClear { int nUvwNo; int nAxisNo; int nAlarmClear; } st_UvwxSetAlarmClear;
		case UvwxSetAlarmClear_Func:
		{
			//st_UvwxSetAlarmClear stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;									   break;
		}
		//typedef struct tag_UvwxSetCmdPos{ int nUvwNo; int nAxisNo; double dPos; } st_UvwxSetCmdPos;
		case UvwxSetCmdPos_Func:
		{
			//st_UvwxSetCmdPos stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxGetCmdPos { int nUvwNo; double dPos[4]; } st_UvwxGetCmdPos;
		case UvwxGetCmdPos_Func:
		{
			st_UvwxGetCmdPos stArg;

			stArg = *((st_UvwxGetCmdPos*)(void*)m_byArg);

			//m_dUvwxCmdPos[stArg.nUvwNo][0] = stArg.dPos[0];
			//m_dUvwxCmdPos[stArg.nUvwNo][1] = stArg.dPos[1];
			//m_dUvwxCmdPos[stArg.nUvwNo][2] = stArg.dPos[2];
			//m_dUvwxCmdPos[stArg.nUvwNo][3] = stArg.dPos[3];

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxGetCmdVel { int nUvwNo; double dVel[4]; } st_UvwxGetCmdVel;
		case UvwxGetCmdVel_Func:
		{
			st_UvwxGetCmdVel stArg;

			stArg = *((st_UvwxGetCmdVel*)(void*)m_byArg);

			//m_dUvwxCmdVel[stArg.nUvwNo][0] = stArg.dVel[0];
			//m_dUvwxCmdVel[stArg.nUvwNo][1] = stArg.dVel[1];
			//m_dUvwxCmdVel[stArg.nUvwNo][2] = stArg.dVel[2];
			//m_dUvwxCmdVel[stArg.nUvwNo][3] = stArg.dVel[3];

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxGetHomeStatus{ int nUvwNo; int nStatus; } st_UvwxGetHomeStatus;
		case UvwxGetHomeStatus_Func:
		{
			st_UvwxGetHomeStatus stArg;

			stArg = *((st_UvwxGetHomeStatus*)(void*)m_byArg);

			//			m_nUvwxHomeStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxGetServoOnStatus{ int nUvwNo; int nStatus; } st_UvwxGetServoOnStatus;
		case UvwxGetServoOnStatus_Func:
		{
			st_UvwxGetServoOnStatus stArg;

			stArg = *((st_UvwxGetServoOnStatus*)(void*)m_byArg);

			//			m_nUvwxServoOnStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxGetAlarmStatus{ int nUvwNo; int nStatus; } st_UvwxGetAlarmStatus;
		case UvwxGetAlarmStatus_Func:
		{
			st_UvwxGetAlarmStatus stArg;

			stArg = *((st_UvwxGetAlarmStatus*)(void*)m_byArg);

			//			m_nUvwxAlarmStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxGetMotionDoneStatus{ int nUvwNo; int nStatus; } st_UvwxGetMotionDoneStatus;
		case UvwxGetMotionDoneStatus_Func:
		{
			st_UvwxGetMotionDoneStatus stArg;

			stArg = *((st_UvwxGetMotionDoneStatus*)(void*)m_byArg);

			//			m_nUvwxMotionDoneStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_UvwxGetStatus{ int nUvwNo; int nStatus; } st_UvwxGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
		case UvwxGetStatus_Func:
		{
			st_UvwxGetStatus stArg;

			stArg = *((st_UvwxGetStatus*)(void*)m_byArg);

			//			m_nUvwxStatus[stArg.nUvwNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_DInputGetBitValue { int nBit; int nValue; } st_DInputGetBitValue;
		case DInputGetBitValue_Func:
		{
			st_DInputGetBitValue stArg;

			stArg = *((st_DInputGetBitValue*)(void*)m_byArg);
			//			m_nDInputValue[stArg.nBit] = stArg.nValue;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_DInputGetDWordValue { int nDWord; DWORD dwValue; } st_DInputGetDWordValue;
		case DInputGetDWordValue_Func:
		{
			st_DInputGetDWordValue stArg;

			stArg = *((st_DInputGetDWordValue*)(void*)m_byArg);
			//			m_dwDInputDWordValue[stArg.nDWord] = stArg.dwValue;

			memcpy(SharedInfo::DInputValue, stArg.dwValue, sizeof(int) * _DIN_MAX);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_DOutputGetBitValue { int nBit; int nValue; } st_DOutputGetBitValue;
		case DOutputGetBitValue_Func:
		{
			st_DOutputGetBitValue stArg;

			stArg = *((st_DOutputGetBitValue*)(void*)m_byArg);
			//			m_nDOutputValue[stArg.nBit] = stArg.nValue;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_DOutputGetDWordValue { int nDWord; DWORD dwValue; } st_DOutputGetDWordValue;
		case DOutputGetDWordValue_Func:
		{
			st_DOutputGetDWordValue stArg;

			stArg = *((st_DOutputGetDWordValue*)(void*)m_byArg);
			//			m_dwDOutputDWordValue[stArg.nDWord] = stArg.dwValue;

			memcpy(SharedInfo::DOutputValue, stArg.dwValue, sizeof(int) * _DOUT_MAX);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_DOutputSetBitValue { int nBit; int nValue; } st_DOutputSetBitValue;
		case DOutputSetBitValue_Func:
		{
			//st_DOutputSetBitValue stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_AInputGetChannelValue { int nChannel; double dValue; } st_AInputGetChannelValue;
		case AInputGetChannelValue_Func:
		{
			st_AInputGetChannelValue stArg;

			stArg = *((st_AInputGetChannelValue*)(void*)m_byArg);
			//			m_dAInputValue[stArg.nChannel] = stArg.dValue;

			memcpy(SharedInfo::AInputValue, stArg.dValue, sizeof(double) * MAX_AINPUT_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AOutputGetChannelValue { int nChannel; double dValue; } st_AOutputGetChannelValue;
		case AOutputGetChannelValue_Func:
		{
			st_AOutputGetChannelValue stArg;

			stArg = *((st_AOutputGetChannelValue*)(void*)m_byArg);

			//			m_dAOutputValue[stArg.nChannel] = stArg.dValue;
			memcpy(SharedInfo::AOutputValue, stArg.dValue, sizeof(double) * MAX_AOUTPUT_SIZE);

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_AOutputSetChannelValue { int nChannel; double dValue; } st_AOutputSetChannelValue;
		case AOutputSetChannelValue_Func:
		{
			//st_AOutputSetChannelValue stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_StretchStart { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; } st_StretchStart;
		case ForceControlStart_Func:
		{
			//st_StretchStart stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_StretchStop { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dDecel; } st_StretchStop;			
		case ForceControlStop_Func:
		{
			//st_StretchStop stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_StretchSetPara { int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE]; int nStepCount; double dMaxSpeed; double dMinSpeed; double dOkRange; double dDecRange; } st_StretchSetPara;
		case ForceControlSetPara_Func:
		{
			//st_StretchSetPara stArg;
		//	StretchSetParaFlag = TRUE;
//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_StretchSetStepValue { int nStepNo; double dStepValue[MAX_STRETCH_AXIS_SIZE]; } st_StretchSetStepValue;
		case ForceControlSetStepValue_Func:
		{
			//st_StretchSetStepValue stArg;
		   // StretchSetStepValueFlag = TRUE;
//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_StretchGetValue { int nAxisNo;  double dCmdPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel[MAX_STRETCH_AXIS_SIZE]; double dStretchValue[MAX_STRETCH_AXIS_SIZE]; } st_StretchGetValue;
		case ForceControlGetValue_Func:
		{
			st_ForceControlGetValue stArg;

			stArg = *((st_ForceControlGetValue *)(void*)m_byArg);

			//Pos
			for (i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
			{
				SharedInfo::dStretchCmdPos[i] = stArg.dCmdPos[i];
			}

			//Vel
			for (i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
			{
				SharedInfo::dStretchCmdVel[i] = stArg.dCmdVel[i];
			}

			//Value
			for (i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
			{
				SharedInfo::dStretchValue[i] = stArg.dForceControlValue[i];
			}
#if 0
			//Target Value
			for (i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
			{
				SharedInfo::dStretchTargetValue[i] = stArg.dStretchTargetValue[i];
			}
#endif
			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_StretchGetStatus { int nAxisNo;  int nStatus; } st_StretchGetStatus;
		case ForceControlGetStatus_Func:
		{
			st_ForceControlGetStatus stArg;

			stArg = *((st_ForceControlGetStatus *)(void*)m_byArg);

			switch (stArg.nIndex)
			{
			case 0:
				for (int i = 0; i < MAX_STRETCH_AXIS_USE; i++)
				{
					SharedInfo::nStretchStatus[i] = stArg.nStatus[i];
					SharedInfo::nStretchStatus[i + MAX_STRETCH_AXIS_USE] = stArg.nStatus[i + MAX_STRETCH_AXIS_USE];
				}
				break;
			case 1:
				//for (int i = 0; i < MAX_STRETCH_AXIS_USE; i++)
				//{
				//	SharedInfo::nStretchStatus[i + MAX_STRETCH_AXIS_USE] = stArg.nStatus[i + MAX_STRETCH_AXIS_USE];
				//}
				break;
			case 2:
				//for (int i = 0; i < MAX_STRETCH_AXIS_USE; i++)
				//{
				//	SharedInfo::nCFStatus[i] = stArg.nStatus[i];
				//}
				break;
			case 3:
				//for (int i = 0; i < MAX_CENTERING_NUM; i++)
				//{
				//	SharedInfo::nCenteringStatusX[i] = stArg.nStatus[i];
				//}
				break;
			case 4:
				//for (int i = 0; i < MAX_CENTERING_NUM; i++)
				//{
				//	SharedInfo::nCenteringStatusY[i] = stArg.nStatus[i];
				//}
				break;
			default:
				break;
			}
			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}



		////typedef struct tag_CounterForceStart { int nAxisSize;  int nAxisNo[MAX_CounterForce_AXIS_SIZE]; } st_CounterForceStart;
		//case CounterForceStart_Func:
		//{
		//	//st_CounterForceStart stArg;

		//	
		//	break;
		//}

		////typedef struct tag_CounterForceStop { int nAxisSize;  int nAxisNo[MAX_CounterForce_AXIS_SIZE]; double dDecel; } st_CounterForceStop;			
		//case CounterForceStop_Func:
		//{
		//	//st_CounterForceStop stArg;

		//	
		//	break;
		//}

		////typedef struct tag_CounterForceSetPara { int nUsefulAxisNo[MAX_CounterForce_AXIS_SIZE]; int nStepCount; double dMaxSpeed; double dMinSpeed; double dOkRange; double dDecRange; } st_CounterForceSetPara;
		//case CounterForceSetPara_Func:
		//{
		//	//st_CounterForceSetPara stArg;
		//	CounterForceSetParaFlag = TRUE;
		//	
		//	break;
		//}

		////typedef struct tag_CounterForceSetStepValue { int nStepNo; double dStepValue[MAX_CounterForce_AXIS_SIZE]; } st_CounterForceSetStepValue;
		//case CounterForceSetStepValue_Func:
		//{
		//	//st_CounterForceSetStepValue stArg;
		//	CounterForceSetStepValueFlag = TRUE;
		//	
		//	break;
		//}

		////typedef struct tag_CounterForceGetValue { int nAxisNo;  double dCmdPos[MAX_CounterForce_AXIS_SIZE]; double dCmdVel[MAX_CounterForce_AXIS_SIZE]; double dCounterForceValue[MAX_CounterForce_AXIS_SIZE]; } st_CounterForceGetValue;
		//case CounterForceGetValue_Func:
		//{
		//	st_CounterForceGetValue stArg;

		//	stArg = *((st_CounterForceGetValue *)(void*)m_byArg);

		//	//Pos
		//	for (i = 0; i < MAX_COUNTER_FORCE_AXIS_SIZE; i++)
		//	{
		//		m_dCounterForceCmdPos[i] = stArg.dCmdPos[i];
		//	}

		//	//Vel
		//	for (i = 0; i < MAX_COUNTER_FORCE_AXIS_SIZE; i++)
		//	{
		//		m_dCounterForceCmdVel[i] = stArg.dCmdVel[i];
		//	}

		//	//Value
		//	for (i = 0; i < MAX_COUNTER_FORCE_AXIS_SIZE; i++)
		//	{
		//		m_dCounterForceValue[i] = stArg.dCounterForceValue[i];
		//	}

		//	//Target Value
		//	for (i = 0; i < MAX_COUNTER_FORCE_AXIS_SIZE; i++)
		//	{
		//		m_dCounterForceTargetValue[i] = stArg.dCounterForceTargetValue[i];
		//	}

		//	
		//	break;
		//}

		////typedef struct tag_CounterForceGetStatus { int nAxisNo;  int nStatus; } st_CounterForceGetStatus;
		//case CounterForceGetStatus_Func:
		//{
		//	//st_CounterForceGetStatus stArg;

		//	//stArg = *((st_CounterForceGetStatus *)(void*)m_byArg);
		//	//int AxisNo = stArg.nAxisNo - _AXIS_COUNTER_FORCE_L1;
		//	//m_nCounterForceStatus[AxisNo] = stArg.nStatus;
		//	//
		//	break;
		//}
		//typedef struct tag_ClampStart { int nAxisNo; } st_ClampStart;
		case ClampStart_Func:
		{
			//st_ClampStart stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_UnClampStart { int nAxisNo; double dDecel; } st_UnClampStart;
		case UnClampStart_Func:
		{
			//st_UnClampStart stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_ClampHomeStart { int nAxisNo; } st_ClampHomeStart;
		case ClampHomeStart_Func:
		{
			//st_ClampHomeStart stArg;

//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_ClampSetPara { int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampSetPara;
		case ClampSetPara_Func:
		{
			//st_ClampSetPara stArg;
		  //  ClampSetParaFlag = TRUE;
//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_ClampGetValue { int nAxisNo;  double dClampValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampGetValue;
		case ClampGetValue_Func:
		{
			st_ClampGetValue stArg;

			stArg = *((st_ClampGetValue *)(void*)m_byArg);

			//Value
			for (i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
			{
				//   m_dClampValue[i] = stArg.dClampValue[i];
			}

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		//typedef struct tag_ClampGetStatus{ int nAxisNo; int nStatus; } st_ClampGetStatus;
		case ClampGetStatus_Func:
		{
			st_ClampGetStatus stArg;

			stArg = *((st_ClampGetStatus *)(void*)m_byArg);

			//m_nClampStatus[stArg.nAxisNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		//typedef struct tag_ClampTorqueMove { int nAxisNo; double dTorque; double dVel; int nAccFilterSel; int nGainSel; int nSpdLoopSel; } st_ClampTorqueMove;
		case ClampTorqueMove_Func:
		{
			st_ClampTorqueMove stArg;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;


		}
		// typedef struct tag_ClampTorqueMoveStop { int nAxisNo; int nMethod; } st_ClampTorqueMoveStop;
		case ClampTorqueMoveStop_Func:
		{
			st_ClampTorqueMoveStop stArg;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;


		}
		//typedef struct tag_ClampTorqueSetRead { int nAxisNo; int nSelMon; } st_ClampTorqueSetRead;
		case ClampTorqueSetRead_Func:
		{
			st_ClampTorqueSetRead stArg;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;


		}


		//typedef struct tag_ClampTorqueRead { int nAxisNo; double dMonitorValue; } st_ClampTorqueRead;
		case ClampTorqueRead_Func:
		{
			st_ClampTorqueRead stArg;

			stArg = *((st_ClampTorqueRead *)(void*)m_byArg);
			memcpy(SharedInfo::m_nClampTorquedMonitorValue, stArg.dMonitorValue, sizeof(double)* MAX_STRETCH_AXIS_SIZE);

			//for (int i = 0; i < MAX_STRETCH_AXIS_SIZE; i++)
			//	SharedInfo::m_nClampTorquedMonitorValue[i] = (SharedInfo::m_nClampTorquedMonitorValue[i] / 0x40000000) * 100;

			//
			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}

		case GetOtherAlarm_Func:
		{
			st_OtherAlarm stArg;

			stArg = *((st_OtherAlarm *)(void*)m_byArg);

			memcpy(SharedInfo::m_nOtherAlarm, stArg.Alarm, sizeof(st_OtherAlarm));

			break;
		}
		//int ClampTorqueRead(int nAxisNo, double dMonitorValue);

		//case PitchHomeStart_Func:
		//{
		//	//st_PitchHomeStart stArg;

		//	
		//	break;
		//}

		////typedef struct tag_PitchMoveStop { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dDecel; } st_PitchStop;
		//case PitchMoveStop_Func:
		//{
		//	//st_PitchMoveStop stArg;

		//	
		//	break;
		//}

		//typedef struct tag_PitchPosMove { int nAxisIndex;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel; } st_PitchPosMove;
		case PitchPosMove_Func:
		{
			st_PitchPosMove stArg;

			
			break;
		}

		//typedef struct tag_StretchPosMove { int nAxisIndex;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel; } st_StretchPosMove;
		case StretchPosMove_Func:
		{
			st_PitchPosMove stArg;


			break;
		}

		////typedef struct tag_PitchGetStatus { int nAxisNo;  int nStatus; } st_PitchGetStatus;
		//case PitchGetStatus_Func:
		//{
		//	//st_PitchGetStatus stArg;

		//	//stArg = *((st_PitchGetStatus *)(void*)m_byArg);

		//	//m_nPitchStatus[stArg.nAxisNo - _AXIS_GRIP_PITCH_L1] = stArg.nStatus;

		//	//
		//	break;
		//}

		case VisionFind_Func:
		{
			st_VisionFind stArg;

			stArg = *((st_VisionFind *)(void*)m_byArg);
			//Log_Msg(_T("Vision Find Receive"));
			SharedInfo::bAlignVisionReceiveFlag = TRUE;
			break;
		}

		case VisionReturn_Func:
		{
			st_VisionReturn stArg;

			stArg = *((st_VisionReturn *)(void*)m_byArg);
			for (int i = 0; i < 2; i++)
			{
				SharedInfo::AlignCamMarkPos[i] = stArg.dMarkPixelPos[i];
				SharedInfo::AlignCamMarkCD[i] = stArg.dMarkCD[i];
			}
			SharedInfo::AlignCamScore = stArg.dScore;
			SharedInfo::bResult = stArg.bResult;
			// Log_Msg(_T("Vision Data Receive"));
			SharedInfo::bAlignVisionReceiveFlag = TRUE;
			break;
		}


		case GetForceData_Func:
		{
			st_ForceData stArg;

			stArg = *((st_ForceData *)(void*)m_byArg);
			//	memcpy(SharedInfo::m_nClampTorquedMonitorValue, stArg.dMonitorValue, sizeof(double) * MAX_STRETCH_AXIS_SIZE);


			//memcpy(SharedInfo::dCF_LoadcellForce, stArg.dCF_LoadcellForce, sizeof(double)*(MAX_CF_NUM + MAX_CENTERING_NUM));
			//memcpy(SharedInfo::dSF_LoadcellForce, stArg.dSF_LoadcellForce, sizeof(double)*MAX_SF_NUM);
			memset(SharedInfo::dSF_LoadcellForce, 0x0, sizeof(double)*MAX_SF_NUM); //KJT 20210727 Temp


			//pDlg->m_nSocketReceiveFlag = TRUE;
			//
			break;
		}

		case StretchForceZero_Func:
		{
			st_StretchForceZero stArg;
			stArg = *((st_StretchForceZero *)(void*)m_byArg);
			break;
		}

		case CoordinateIsBusy_Func:
		{
			tag_CoordinateIsBusy stArg;

			stArg = *((tag_CoordinateIsBusy *)(void*)m_byArg);


			//SharedInfo::CoodinateReceive[stArg.nCoordNo] = stArg.nStatus;

			//pDlg->m_nSocketReceiveFlag = TRUE;
			break;
		}
		case SetLight_Func:
		{
			st_SetLight stArg;

			stArg = *((st_SetLight *)(void*)m_byArg);

			SharedInfo::bAlignVisionSetLightFlag = TRUE;
			break;
		}
		case LightOn_Func:
		{

			SharedInfo::bAlignVisionLightOnFlag = TRUE;
			break;
		}
		//case GetLightState_Func:
		//{
		//	st_GetLightState stArg;

		//	stArg = *((st_GetLightState *)(void*)m_byArg);
		//	SharedInfo::bAlignVisionGetLightOnOff = stArg.bOnOff;
		//	SharedInfo::bAlignVisionLightOnFlag = TRUE;
		//	break;
		//}
		default:
		{
			Str.Format(_T("Receive Fail %d"), m_nFuncAddr);
			Etc_Msg(Str);
			break;
		}
		}
	}


}

int CSocketManager::ReceiveDataEx(char* pchReceiveData, int* pnFuncAddr, int* pnReturn, byte* pby)
{
	int n;
	int nLength;

	nLength = *(pchReceiveData + 4) << 8 & 0xFF00;
	nLength |= *(pchReceiveData + 5) & 0x00FF;
	if (nLength < 4 || COM_BUF_SIZE < nLength) 
		return FMM_COMM_ERROR_SIZE;

	if (LRCDecoderEx(pchReceiveData, nLength + 6) == 0) 
		return FMM_COMM_ERROR_LRC;

	n = *(pchReceiveData + 0) << 8 & 0xFF00;
	n |= *(pchReceiveData + 1) & 0x00FF;
	//if (m_nWriteMode == 1 && m_nSendTransactionID != n)  return IQC_COMM_ERROR_TRANSACTION_ID;

	//TRACE(_T("m_nSendTransactionID=%d, n=%d \n"), m_nSendTransactionID, n);

	n = *(pchReceiveData + 2) << 8 & 0xFF00;
	n |= *(pchReceiveData + 3) & 0x00FF;
	//if (m_nWriteMode == 1 && m_nSendProtocolID != n) return IQC_COMM_ERROR_PROTOCOL_ID;

	n = *(pchReceiveData + 6);
	//if (m_nWriteMode == 1 && m_nSendUnitID != n) return IQC_COMM_ERROR_UNIT_ID;

	n = *(pchReceiveData + 7);
	//if (m_nWriteMode == 1 && m_nSendFC != n) return IQC_COMM_ERROR_FC;

	n = *(pchReceiveData + 8) << 8 & 0xFF00;
	n |= *(pchReceiveData + 9) & 0x00FF;
	//if (m_nWriteMode == 1 && m_nSendFuncAddr != n) return IQC_COMM_FUNCTION_ADDR;

	*pnFuncAddr = n;

	*pnReturn = *(pchReceiveData + 10) << 8 & 0xFF00;
	*pnReturn |= *(pchReceiveData + 11) & 0x00FF;

	pby = (byte*)(pchReceiveData + 12);

	//memcpy(pby, pchReceiveData+12, nLength-6);

	return FMM_SUCCESS;
}
int CSocketManager::LRCDecoderEx(char* pch, int nSize)
{
	int i;

	unsigned char uchLRC = 0;
	unsigned char uchReceiveLRC = 0;

	uchReceiveLRC = *(pch + nSize);

	for (i = 0; i < nSize; i++) {
		uchLRC += *(pch + i);
	}

	uchLRC = ((unsigned char)(-((char)uchLRC)));

	if (uchLRC == uchReceiveLRC) return TRUE;
	else return FALSE;
}