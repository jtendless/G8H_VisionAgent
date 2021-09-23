#include "stdafx.h"
#include "MotionModule.h"
#include "../Common/CommonDefine.h"
#include "../Module/UmacAxis.h"
#include "../Module/AjinAxis.h"
#include "../Module/IO.h"
#include "Vision/SharedInfo.h"
#include "Data/MachineData.h"

CMotionModule::CMotionModule()
{

}
//----------------------------------------------------------------
CMotionModule::~CMotionModule()
{
	delete m_pUmacAxis;
	delete m_pAjinAxis;
	delete m_pIO;
}
//----------------------------------------------------------------
void CMotionModule::InitializeAcl()
{
	m_pUmacAxis = new CUmacAxis();
	m_pUmacAxis->UmacOpen(TRUE);
	if (m_pUmacAxis->m_bDeviceOpen == FALSE)
	{
		AfxMessageBox(_T("Umac is not opened."));
	}
	else
	{
		AfxMessageBox(_T("Umac is not opened."));
	}

	m_pAjinAxis = new CAjinAxis();

	//if (AxlOpen(7) != AXT_RT_SUCCESS)
	if (AxlOpenNoReset(7) != AXT_RT_SUCCESS)
	{
		m_pAjinAxis->m_nAXLOpen = AxlIsOpened();
		AfxMessageBox(_T("Axl is not opened."));
	}
	else
	{
		m_pAjinAxis->m_nAXLOpen = 1;
		/*
		GetBoardInfo();
		SetBoardConfigure();
		GetMotionPara();

		LoadAjinHomeParameter();
		*/
		//AxmGantrySetEnable(GANTRY_MASTER_AXIS, GANTRY_SLAVE_AXIS, 0, 0.0, 0.0);
		for (int i = 0; i < REMOTE_AXIS_MAX; i++)
		{
			AxmMotSetAbsRelMode(i, 0);					//abs
		}
		AfxMessageBox(_T("Axl is opened."));
	}
	m_pIO = new CIO;
	m_pIO->StartIOCheck();
}
//----------------------------------------------------------------
UINT Status_Umac_Thread_Proc(LPVOID lpParam) //KJT 20200812
{
	CMotionModule	*Module = (CMotionModule*)lpParam;
	int nSamplingTime = 50;// 100;
	int i;
	int nBaseBitNo = 0;
	int nBaseDWordBitNo = 0;
	int nDWordNo = 0;
	int nSystemHomeStatus;
	int nSystemHomeSignal;
	int nSystemPLimitSignal;
	int nSystemNLimitSignal;
	int nSystemServoOnStatus;
	int nSystemAlarmStatus;
	int nSystemMotionDoneStatus;
	int nSystemStatus;//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

	DWORD dwDInputValue = 0;
	DWORD dwDOutputValue = 0;
	double dActPos = 0;
	double dCmdPos = 0;
	double dCmdVel = 0;
	double dVolt = 0;
	double dTempVolt = 0;

	//DWORD dwPositiveStatus, dwNegativeStatus;
	DWORD dwStatus;


	if (SharedInfo::Is_Umac_Open == 1)
	{
		for (i = 0; i < REMOTE_AXIS_UMAC_MAX; i++)
		{
			//Awk 의미 확인. Umac 초기 상태 체크?
			//j = m_Umac.nUmacAxisNo[i];
			//pDlg->m_pUmacAxis->GetInitActPosition(j);

			//pDlg->m_pUmacAxis->GetInitActPosition(i);

			//Sleep(0);
		}
	}

	Module->m_nIs_Running_Status_Umac_Thread = 1;

	while (!Module->m_nStop_Status_Umac_Thread)
	{
		if (Module->m_nStop_Status_Umac_Thread == TRUE) break;

		if (SharedInfo::Is_Umac_Open == 1)
		{
			nSystemHomeStatus = 1;					//All 
			nSystemHomeSignal = 0;					//Any
			nSystemPLimitSignal = 0;					//Any
			nSystemNLimitSignal = 0;					//Any
			nSystemServoOnStatus = 1;				//All
			nSystemAlarmStatus = 0;					//Any
			nSystemMotionDoneStatus = 1;			//All
			nSystemStatus = 0;							//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

			//UMAC
			for (i = 0; i < REMOTE_AXIS_UMAC_MAX; i++)
			{
				if (Module->m_nStop_Status_Umac_Thread == TRUE) break;

				dActPos = Module->m_pUmacAxis->GetActPosition(i);
				dCmdPos = Module->m_pUmacAxis->GetCmdPosition(i);

				//KJT 20200812
				//Awk Position Offset Data Matching 하기.
				int nIndex = (int)SharedInfo::GetUmacAxisNoByActualAxis((enum_REMOTE_AXIS_UMAC)i);
				//SharedInfo::UmacHomeStatus[i] = dActPos + CMachineData::m_MachineDataMotor.Info.dOriginPos[nIndex];
				SharedInfo::UmacCmdPos[i] = dCmdPos;/// +CMachineData::m_MachineDataMotor.Info.dOriginPos[nIndex];
				SharedInfo::UmacCmdVel[i] = Module->m_pUmacAxis->GetActVelocity(i);
				SharedInfo::UmacHomeStatus[i] = Module->m_pUmacAxis->IsHomeComplete(i);
				SharedInfo::UmacHomeSignal[i] = Module->m_pUmacAxis->IsHome(i);
				SharedInfo::UmacPLimitSignal[i] = Module->m_pUmacAxis->IsPOT(i);
				SharedInfo::UmacNLimitSignal[i] = Module->m_pUmacAxis->IsNOT(i);
				SharedInfo::UmacServoOnStatus[i] = Module->m_pUmacAxis->IsAmpEnable(i);
				SharedInfo::UmacAlarmStatus[i] = Module->m_pUmacAxis->GetAmpAlarm(i);
				SharedInfo::UmacInMotionStatus[i] = !Module->m_pUmacAxis->IsDone(i);
				SharedInfo::Umac_Isolator_Alarm = Module->m_pUmacAxis->IsIsolatorAlarm();

				if (SharedInfo::UmacHomeStatus[i] == 1)
				{
					if (SharedInfo::UmacServoOnStatus[i] == 0 || SharedInfo::UmacAlarmStatus[i] == 1)
					{
						Module->m_pUmacAxis->HomeCompReset(i);
					}
				}

				if (SharedInfo::UmacHomeStatus[i] == 0)		nSystemHomeStatus = 0;
				if (SharedInfo::UmacHomeSignal[i] == 1)		nSystemHomeSignal = 0;
				if (SharedInfo::UmacPLimitSignal[i] == 1)	nSystemPLimitSignal = 1;
				if (SharedInfo::UmacNLimitSignal[i] == 1)	nSystemNLimitSignal = 1;
				if (SharedInfo::UmacServoOnStatus[i] == 0)	nSystemServoOnStatus = 0;
				if (SharedInfo::UmacAlarmStatus[i] == 1)		nSystemAlarmStatus = 1;
				if (SharedInfo::UmacInMotionStatus[i] == 1)	nSystemMotionDoneStatus = 0;

				dwStatus = 0; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus					

				if (SharedInfo::UmacHomeStatus[i] == 1)
				{
					dwStatus = (dwStatus | (0x01 << 0));
				}
				if (SharedInfo::UmacServoOnStatus[i] == 1)
				{
					dwStatus = (dwStatus | (0x01 << 1));
				}
				if (SharedInfo::UmacAlarmStatus[i] == 1)
				{
					dwStatus = (dwStatus | (0x01 << 2));
				}
				if (SharedInfo::UmacInMotionStatus[i] == 0)
				{
					dwStatus = (dwStatus | (0x01 << 3));
				}

				SharedInfo::UmacStatus[i] = dwStatus;

				//Sleep(0);
				Sleep(1);
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////

			Sleep(nSamplingTime);

		}//while (!pDlg->m_nStopStatusThread)			
	}
	Module->m_nIs_Running_Status_Umac_Thread = 0;

	return 0;
}
//---------------------------------------------------------------------