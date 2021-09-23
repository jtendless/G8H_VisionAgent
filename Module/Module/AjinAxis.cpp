#include "stdafx.h"
#include "AjinAxis.h"
#include "math.h"
#include "../Log/Logger.h"

//#define PI				3.14159265358979323846264338
//#define TO_RADIAN			(PI / 180.0)
//#define TO_DEGREE			(180.0 / PI)

CAjinAxis::CAjinAxis()
{

}


CAjinAxis::~CAjinAxis()
{

}

int CAjinAxis::AjinPosMove(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel)
{
	//DWORD dwStart = GetTickCount();
	//TRACE(_T("Start Time : %d\n"), dwStart);

	double dTargetPos = 0.0;

	//if (nAxisNo == _AXIS_INSPECT_UPDOWN)
	//{
	//	dTargetPos = dPos - pMotionAgentDlg->m_dAxisPosOffset[nAxisNo];
	//	dTargetPos = dTargetPos / tan(8.0 * RADIAN);

	//	//dPos = dPos / tan(8.0 * RADIAN);
	//}
	//else
	//{
	dTargetPos = dPos - CMachineData::m_MachineDataMotor.Info.dOriginPos[nAxisNo];
	//dTargetPos = dPos;
	//}	

	AxmMoveStartPos(nAxisNo, dTargetPos, dVel, dAccel, dDecel);

	//long nAxis = nAxisNo;
	//m_AjinChk.nAxisNo = nAxis;
	//m_AjinChk.nItem = _ChkVelocity;

	//AfxBeginThread(AjinChkProc, (LPVOID)pMotionAgentDlg);

	//DWORD dwEnd = GetTickCount() - dwStart;
	//TRACE(_T("Spend Time : %d\n"), dwEnd);

	return 0;
}

int CAjinAxis::AjinRelMove(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel)
{
	DWORD dwStart = GetTickCount();
	TRACE(_T("Start Time : %d\n"), dwStart);

	double dCmdPos = 0.0;
	double dTargetPos = 0.0;

	AxmStatusGetCmdPos(nAxisNo, &dCmdPos);

	//if (nAxisNo == _AXIS_INSPECT_UPDOWN)
	//{	
	//	dPos = dPos / tan(8.0 * RADIAN);
	//}

	dTargetPos = dCmdPos + dPos;// -pMotionAgentDlg->m_dAxisPosOffset[nAxisNo];

	AxmMoveStartPos(nAxisNo, dTargetPos, dVel, dAccel, dDecel);

	//long nAxis = nAxisNo;
	//m_AjinChk.nAxisNo = nAxis;
	//m_AjinChk.nItem = _ChkVelocity;

	//AfxBeginThread(AjinChkProc, (LPVOID)pMotionAgentDlg);

	DWORD dwEnd = GetTickCount() - dwStart;
	TRACE(_T("Spend Time : %d\n"), dwEnd);

	return 0;
}

BOOL CAjinAxis::AjinMoveStop(int nAxisNo)
{
	AxmMoveSStop(nAxisNo);
	return TRUE;
}

/*
int CSingleAxis::SetAxisNo(int nAxisNo)
{
	m_nAxisNo = nAxisNo;

	return 0;
}


int CSingleAxis::SetVel(double dVel)
{
	m_dVel = dVel;
	return 0;
}


int CSingleAxis::SetAccel(double dAccel)
{
	m_dAccel = dAccel;
	return 0;
}


int CSingleAxis::SetDecel(double dDecel)
{
	m_dDecel = dDecel;
	return 0;
}


int CSingleAxis::SetServoOn()
{
	// Use Ajinextek Dll Servo On

	AxmSignalServoOn(m_nAxisNo, TRUE);

	return 0;
}


int CSingleAxis::SetServoOff()
{
	// Use Ajinextek Dll Servo Off

	AxmSignalServoOn(m_nAxisNo, FALSE);

	return 0;
}


int CSingleAxis::GetAlarm()
{
	// Use Ajinextek Dll Alarm Check

	AxmSignalReadServoAlarm(m_nAxisNo, &m_dwStatus);

	return m_dwStatus;
}


int CSingleAxis::SetAlarmClear()
{
	// Use Ajinextek Dll Alarm Clear

	AxmSignalServoAlarmReset(m_nAxisNo, TRUE);

	Sleep(250);

	AxmSignalServoAlarmReset(m_nAxisNo, FALSE);

	return 0;
}

int CSingleAxis::GetLimit(DWORD* pdwPLimit, DWORD* pdwNLimit)
{
	AxmSignalReadLimit(m_nAxisNo, pdwPLimit, pdwNLimit);

	return 0;
}

int CSingleAxis::MoveHomeSearch()
{
	// Use Ajinextek Dll Move Home Search

	m_dwStatus = AxmHomeSetStart(m_nAxisNo);

	return m_dwStatus;
}


int CSingleAxis::MoveStart(double dPos)
{
	// Use Ajinextek Dll Move Start

	//m_dwStatus = AxmMoveStartPos(m_nAxisNo, dPos, m_dVel, m_dAccel, m_dDecel);

	return 0;
}


int CSingleAxis::MoveStop()
{
	// Use Ajinextek Dll Move Stop

	AxmMoveSStop(m_nAxisNo);

	return 0;
}

int CSingleAxis::EMGStop()
{
	// Use Ajinextek Dll EMG Stop

	AxmMoveEStop(m_nAxisNo);

	return 0;
}
*/

void CAjinAxis::Home(INT nIndex)
{
	int nAxis = nIndex;

	//AjinHomeStart(nAxis);
}

void CAjinAxis::GantryHome(int nMaster, int nSlave)
{
	m_AjinChk.nAxisNo = nMaster;
	m_AjinChk.nSlaveNo = nSlave;
	m_AjinChk.nItem = _ChkGantryServoOn;
}

int CAjinAxis::AjinHomeStart(int nIndex)
{
	DWORD dwStart = GetTickCount();

	TRACE(_T("Start Function : %d\n"), dwStart);

	//Home Method 정보.
	long lAxisNo = nIndex;
	long lpHmDir = -1;
	DWORD upHomeSignal = -1;
	DWORD upZphas = -1;
	double dpHomeClrTime = 0.0;
	double dpHomeOffset = 0.0;

	//홈 모션 정보.
	double dpVelFirst = 0.0;
	double dpVelSecond = 0.0;
	double dpVelThird = 0.0;
	double dpVelLast = 0.0;
	double dpAccFirst = 0.0;
	double dpAccSecond = 0.0;
	
	//Awk Home 동작 시 Servo On Check.
	if (SharedInfo::AxisServoOnStatus[nIndex] == FALSE)
	{
		return TRUE;
	}

	AxmHomeGetMethod(lAxisNo, &lpHmDir, &upHomeSignal, &upZphas, &dpHomeClrTime, &dpHomeOffset);

	AxmHomeGetVel(lAxisNo, &dpVelFirst, &dpVelSecond, &dpVelThird, &dpVelLast, &dpAccFirst, &dpAccSecond);

	if (upHomeSignal == PosEndLimit || upHomeSignal == NegEndLimit)
	{
		//Direct Home Function Start.
		AxmHomeSetStart(lAxisNo);
	}
	else{
		if (lpHmDir == 1){
			AxmMoveSignalSearch(lAxisNo, -dpVelFirst, dpAccFirst, NegEndLimit, UP_EDGE, EMERGENCY_STOP);
		}
		else{
			AxmMoveSignalSearch(lAxisNo, dpVelFirst, dpAccFirst, PosEndLimit, UP_EDGE, EMERGENCY_STOP);
		}
		

		m_AjinChk.nAxisNo = lAxisNo;
		m_AjinChk.nItem = _ChkLimitSignal;

		//원점복귀 Thread 구동 Cbsing_20200625
	}
	
	DWORD dwEnd = GetTickCount() - dwStart;
	TRACE(_T("Spend Time : %d\n"), dwEnd);


	return 0;
}

UINT AjinChkProc(LPVOID lpParam)
{
	/*
	pMain->m_pAjinAxis->m_CLock.Lock();

	int nAxisNo = pMain->m_pAjinAxis->m_AjinChk.nAxisNo;
	int nSlaveNo = pMain->m_pAjinAxis->m_AjinChk.nSlaveNo;
	int nItem = pMain->m_pAjinAxis->m_AjinChk.nItem;
	DWORD pLimit = -1;
	DWORD nLimit = -1;
	DWORD uCRCOnOff = 0;
	INT nCnt = 0;
	DOUBLE dLimitPos = 0.0;
	DOUBLE dCurrentDist = 0.0;
	double dMasterPos = 0.0;
	double dSlavePos = 0.0;
	if (nItem == -1)
		return 1;

	pMain->m_pAjinAxis->m_CLock.Unlock();

	//DWORD dwWhile = GetTickCount();
	//TRACE(_T("While Start : %d"), dwWhile);

	while (1)
	{
		switch (nItem)
		{
			case _ChkLimitSignal:
			{
				while (1)
				{
					nCnt = 0;
					if (nCnt == 2000)
						return 1;

					Sleep(1000);
					//AxmSignalReadLimit(nAxisNo, &pLimit, &nLimit);
					pLimit = pMain->m_nAxisPLimitSignal[nAxisNo];
					nLimit = pMain->m_nAxisNLimitSignal[nAxisNo];

					if (pLimit == 1 || nLimit == 1)
					{
						break;
					}

				}

				//Sleep(100);
				dLimitPos = pMain->m_dAxisActPos[nAxisNo];

				AxmHomeSetStart(nAxisNo);
				if (pMain->m_pAjinAxis->m_AjinChk.nSlaveNo != -1)
				{
					nItem = _ChkHomeLimitPos;
					break;
				}


				nItem = _ChkFinish;
				break;
			}
			case _ChkVelocity:
			{
				nCnt = 0;
				Sleep(100);
				while (1)
				{
					if (nCnt == 2000)
						return 1;

					Sleep(100);

					if (pMain->m_dAxisCmdVel[nAxisNo] == 0)
						break;

					nCnt++;
				}

				AxmMoveEStop(nAxisNo);
				Log_Msg(_T("Velo Stop"));
				nItem = _ChkFinish;
				break;

			}
			case _ChkHomeLimitPos:
			{
				nCnt = 0;
				while (1)
				{
					if (nCnt == 2000)
						return 1;

					dCurrentDist = pMain->m_dAxisActPos[nAxisNo] - dLimitPos;
					if (fabs(dCurrentDist) > 100)
						break;

					Sleep(100);
					nCnt++;
				}

				AxmMoveEStop(nAxisNo);
				Log_Msg(_T("Home Stop"));
				nItem = _ChkFinish;
				break;
			}

			case _ChkGantryServoOn:
			{
				//Awk 아진 Home 동작 시 Servo On Check.
				AxmMoveSStop(nSlaveNo);
				Sleep(100);
				//if (pMain->m_nAxisServoOnStatus[nAxisNo] == FALSE )
				//{
				AxmSignalServoOn(nAxisNo, TRUE);
				Sleep(100);
				//}
				//if (pMain->m_nAxisServoOnStatus[nSlaveNo] == FALSE)
				//{
				AxmSignalServoOn(nSlaveNo, TRUE);
				Sleep(100);
				//			}

				AxmGantrySetDisable(pMain->m_pAjinAxis->m_AjinChk.nAxisNo, pMain->m_pAjinAxis->m_AjinChk.nSlaveNo);
				Sleep(100);
				AxmHomeSetResult(pMain->m_pAjinAxis->m_AjinChk.nAxisNo, HOME_ERR_USER_BREAK);
				Sleep(100);
				AxmHomeSetResult(pMain->m_pAjinAxis->m_AjinChk.nSlaveNo, HOME_ERR_USER_BREAK);

				Sleep(100);
				nItem = _ChkGantryHome;
				break;
			}
			case _ChkGantryHome:
			{
				pMain->m_pAjinAxis->AjinHomeStart(nAxisNo);
				Sleep(100);
				pMain->m_pAjinAxis->AjinHomeStart(nSlaveNo);

				nCnt = 0;
				while (1)
				{
					if (nCnt == 2000)
						return 1;

					if (pMain->m_nAxisHomeStatus[nAxisNo] && pMain->m_nAxisHomeStatus[nSlaveNo])
						break;

					Sleep(100);
					nCnt++;
				}

				Sleep(1000);
				dMasterPos = pMain->m_dAxisCmdPos[nAxisNo];
				dSlavePos = pMain->m_dAxisCmdPos[nSlaveNo];
				if (dMasterPos >= dSlavePos)
					pMain->m_pAjinAxis->AjinPosMove(nSlaveNo, dMasterPos, 5, 100, 200);
				else
					pMain->m_pAjinAxis->AjinPosMove(nAxisNo, dSlavePos, 5, 100, 200);

				nCnt = 0;
				while (1)
				{
					if (nCnt == 2000)
						return 1;
					if (pMain->m_nAxisInMotionStatus[nAxisNo] == 0 && pMain->m_nAxisInMotionStatus[nSlaveNo] == 0)
						break;

					Sleep(100);
					nCnt++;
				}

				Sleep(2000);
				AxmGantrySetEnable(nAxisNo, nSlaveNo, 0, 0, 0);

				nItem = _ChkFinish;
				break;
			}
			case _ChkFinish:
			{
				return 0;
			}
		}
		Sleep(100);
		
	}
	*/
	return 0;
}


