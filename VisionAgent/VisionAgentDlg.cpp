
// VisionAgentDlg.cpp : ±¸Çö ÆÄÀÏ
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "afxdialogex.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "Motion/BaseMotion.h"
#include "ModelDlg.h"
#include "ManualDlg.h"
#include "SystemDlg.h"
#include "MeasurementDlg.h"
#include "CommunicationDlg.h"
#include "VisionAgentDlg.h"
#include "MachineDlg.h"
#include "VisionAgentAlarmDlg.h"
#include "VisionAgentProcessDlg.h"
//#include "VisionAgentECSDlg.h"
#include "AutoRunStartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT MonitoringThreadProc(LPVOID lpParam)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)lpParam;
	int status[MAX_FORCE_CONTROL_SIZE] = { 0, };
	int nSamplingTime = 0;
	//	int nInPos;
	int nBaseBitNo = 0;
	int nSystemHomeStatus = 0;
	int nSystemHomeSignal = 0;
	int nSystemPLimitSignal = 0;
	int nSystemNLimitSignal = 0;
	int nSystemServoOnStatus = 0;
	int nSystemAlarmStatus = 0;
	int nSystemMotionDoneStatus = 0;
	//	double dCmdPos, dCmdVel, dActPos;
	double dPos[3] = { 0, };
	//double dVolt;
	CString Str;

	DWORD TickTmp, Tick;
	//pVisionAgentDlg->TempurInterval = 60000;

	//	DWORD dwStatus, dwValue;

	double dLapse = 0.0;

	bool ConnectFlag = FALSE;
	LARGE_INTEGER start, end;
	//	DWORD TickCnt;
	DWORD dwResult;
	//	MOTION_INFO mi;	
	DWORD TempTickTmp, TempTick = 0;
	CString szMsg;
	CString strTemp = _T("");
	pVisionAgentDlg->m_nIsRunningMonitoringThread = 1;

	while (!pVisionAgentDlg->m_nStopMonitoringThread)
	{

		TickTmp = GetTickCount();

		TempTickTmp = GetTickCount();
#if 1
		if (TempTickTmp - TempTick > SharedInfo::TempurInterval)
		{
			TempTick = TempTickTmp;
			pVisionAgentDlg->SaveTempur();

		}
#endif

		if (pVisionAgentDlg->m_nConnect == 1)
		{
#ifndef SIM_MODE
#if 1
			g_CommTempTur.SetTempSend(0, 0);
#endif
#if 1
			if (pVisionAgentDlg->m_pLaserDisp != NULL)
			{
				if (pVisionAgentDlg->m_pLaserDisp->m_bIsOpenned) {
					strTemp = _T("");
					SharedInfo::m_dLaserDispFVal = pVisionAgentDlg->m_pLaserDisp->GetData();
				}
			}
#endif
#endif

			nSamplingTime = 1;
			//Umac
			if (pVisionAgentDlg->m_nStopMonitoringThread == 1) break;

			Devs::MotionIf.UmacGetCmdPos(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.UmacGetActPos(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.UmacGetCmdVel(0);
			Sleep(nSamplingTime);

			Devs::MotionIf.UmacGetHomeSignal(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.UmacGetLimitSignal(0, 0);
			Sleep(nSamplingTime);
			Devs::MotionIf.UmacGetStatus(0);
			Sleep(nSamplingTime);

#if 1
			//Ajin
			if (pVisionAgentDlg->m_nStopMonitoringThread == 1) break;
			Devs::MotionIf.AxisGetActPos(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.AxisGetCmdPos(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.AxisGetCmdVel(0);
			Sleep(nSamplingTime);

			Devs::MotionIf.AxisGetHomeResult(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.AxisGetHomeSignal(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.AxisGetLimitSignal(0, 0);
			Sleep(nSamplingTime);
			Devs::MotionIf.AxisGetStatus(0);
			Sleep(nSamplingTime);

			Devs::MotionIf.ClampTorqueRead();
			Sleep(nSamplingTime);
			Devs::MotionIf.AInputGetChannelValue(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.DInputGetDWordValue(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.AOutputGetChannelValue(0);
			Sleep(nSamplingTime);
			Devs::MotionIf.DOutputGetDWordValue(0);
			Sleep(nSamplingTime);


			if (pVisionAgentDlg->m_nStopMonitoringThread == 1) break;
			Devs::MotionIf.ForceControlGetStatus(0, status);
			Sleep(nSamplingTime);
			//if (pVisionAgentDlg->m_nStopMonitoringThread == 1) break;
			//Devs::MotionIf.ForceControlGetStatus(1, status);
			//Sleep(nSamplingTime);
			//if (pVisionAgentDlg->m_nStopMonitoringThread == 1) break;
			//Devs::MotionIf.ForceControlGetStatus(2, status);
			//Sleep(nSamplingTime);
			//if (pVisionAgentDlg->m_nStopMonitoringThread == 1) break;
			//Devs::MotionIf.ForceControlGetStatus(3, status);
			//Sleep(nSamplingTime);
			//if (pVisionAgentDlg->m_nStopMonitoringThread == 1) break;
			//Devs::MotionIf.ForceControlGetStatus(4, status);
			//Sleep(nSamplingTime);

			Devs::MotionIf.GetForceData();
			Sleep(nSamplingTime);

#if 1
			Devs::MotionIf.UvwGetCmdPos(MASK_UVW, dPos);
			Sleep(nSamplingTime);

			Devs::MotionIf.UvwGetCmdPos(FRAME_UVW, dPos);
			Sleep(nSamplingTime);
#endif
#if 0
			Devs::MotionIf.UvwGetTargetPos(MASK_UVW, dPos);
			Sleep(nSamplingTime);

			Devs::MotionIf.UvwGetTargetPos(FRAME_UVW, dPos);
			Sleep(nSamplingTime);
#endif

			Devs::MotionIf.GetAllOtherAlarm();
			Sleep(nSamplingTime);

			SharedInfo::SystemHomeStatus = nSystemHomeStatus;
			SharedInfo::SystemHomeSignal = nSystemHomeSignal;
			SharedInfo::SystemNLimitSignal = nSystemNLimitSignal;
			SharedInfo::SystemPLimitSignal = nSystemPLimitSignal;
			SharedInfo::SystemServoOnStatus = nSystemServoOnStatus;
			SharedInfo::SystemAlarmStatus = nSystemAlarmStatus;
			SharedInfo::SystemMotionDoneStatus = nSystemMotionDoneStatus;

			Tick = GetTickCount() - TickTmp;
			//Etc_Msg(_T("Tick : %d"), tick);
			QueryPerformanceCounter(&end);
			//dLapse = ((end.QuadPart - start.QuadPart) / (double)freq.QuadPart) * 1000;   // 문제??


#endif
		}
		else if (pVisionAgentDlg->m_nConnect == 1 && SharedInfo::MaxAxisSize < 1)
		{
			pVisionAgentDlg->GetNetworkStatus();
			Devs::MotionIf.SystemGetMaxAxisSize(0);

			Sleep(nSamplingTime);

			pVisionAgentDlg->GetNetworkStatus();
			Devs::MotionIf.SystemGetMaxDInputSize(0);

			Sleep(nSamplingTime);

			pVisionAgentDlg->GetNetworkStatus();
			Devs::MotionIf.SystemGetMaxDOutputSize(0);
			Sleep(nSamplingTime);

			pVisionAgentDlg->GetNetworkStatus();
			Devs::MotionIf.SystemGetMaxAInputSize(0);
			Sleep(nSamplingTime);


			pVisionAgentDlg->GetNetworkStatus();
			Devs::MotionIf.SystemGetMaxAOutputSize(0);
			Sleep(nSamplingTime);

#if 1


#endif
		}

		//Sleep(nSamplingTime);
		//tick = GetTickCount() - ticktmp;
	//	Etc_Msg(_T("Tick : %d"), tick);
		//if (pVisionAgentDlg->m_ImageView)
		//	pVisionAgentDlg->m_ImageView.Invalidate();

		//	if (pStateMan) pStateMan->SetEvent();
	}

	pVisionAgentDlg->m_nIsRunningMonitoringThread = 0;
	//	GetWindowRect
	return 0;
}



UINT AjinStatusThreadProc(LPVOID lpParam)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)lpParam;

	int nSamplingTime = 10;
	int nInPos;
	int nBaseBitNo = 0;
	int nSystemHomeStatus;
	int nSystemHomeSignal;
	int nSystemPLimitSignal;
	int nSystemNLimitSignal;
	int nSystemServoOnStatus;
	int nSystemAlarmStatus;
	int nSystemMotionDoneStatus;
	//	double dPos[3];
	double dCmdPos, dCmdVel, dActPos;
	//double dVolt;
	CString Str;
	DWORD dwStatus, dwValue;

	double dLapse = 0.0;

	bool ConnectFlag = FALSE;
	//	LARGE_INTEGER start, end;
	DWORD dwResult;
	//CStateManager* pStateMan = CStateManager::GetInstance();
	MOTION_INFO mi;

	//CProcessStep* pProcessStep = CProcessStep::GetInstance();
//	DWORD ticktmp, tick;

	BOOL bFlag = TRUE;


	pVisionAgentDlg->m_nIsRunningStatusThread = 1;

	while (!pVisionAgentDlg->m_nStopStatusThread)
	{
		dwResult = GetTickCount();
#if 0
#ifndef SIM_MODE
		if (dwResult - SharedInfo::dConnectionCheckTimer > TIME_OUT_CONNECT && SharedInfo::dConnectionCheckTimer != 0)
		{
			Etc_Msg(_T("Connection Fail\n"));
			pVisionAgentDlg->m_nConnect = 0;
			pVisionAgentDlg->dConnectionCheckTimer = GetTickCount();
			pVisionAgentDlg->ConnectWorkNetwork();
		}
#endif
#endif

		if (pVisionAgentDlg->m_nVisionMaxAxisSize > 1)
		{
			bFlag = TRUE;
			//ticktmp = GetTickCount();== 0
			for (int i = 0; i < DIRECT_AXIS_MAX; i++)
			{
				if (pVisionAgentDlg->m_nStopStatusThread == 1) break;

				AxmStatusGetActPos(i, &dActPos);
				AxmStatusGetCmdPos(i, &dCmdPos);
				AxmStatusReadVel(i, &dCmdVel);
								
				SharedInfo::VisionAxisActPos[i] = dActPos;
				SharedInfo::VisionAxisCmdPos[i] = dCmdPos + CSystemData::m_Coordinate.Info.dOffsetCameraZ[i];

				SharedInfo::VisionAxisCmdVel[i] = dCmdVel;

				AxmHomeGetResult(i, &dwStatus);
				SharedInfo::VisionAxisHomeResult[i] = dwStatus;

				if (dwStatus == HOME_SUCCESS)
				{
					SharedInfo::VisionAxisHomeStatus[i] = 1;
				}
				else
				{
					SharedInfo::VisionAxisHomeStatus[i] = 0;
					nSystemHomeStatus = 0;
				}

				mi.dwMask = 0x1F; // 모든 상태 반환			
				AxmStatusReadMotionInfo(i, &mi);

				SharedInfo::VisionAxisPLimitSignal[i] = (mi.dwMechSig >> 0) & 0x01;
				SharedInfo::VisionAxisNLimitSignal[i] = (mi.dwMechSig >> 1) & 0x01;
				SharedInfo::VisionAxisHomeSignal[i] = (mi.dwMechSig >> 7) & 0x01;
				SharedInfo::VisionAxisAlarmStatus[i] = (mi.dwMechSig >> 4) & 0x01;
				nInPos = (mi.dwMechSig >> 5) & 0x01;

				if (SharedInfo::VisionAxisHomeSignal[i] == 1) nSystemHomeSignal = 1;
				if (SharedInfo::VisionAxisPLimitSignal[i] == 1) nSystemPLimitSignal = 1;
				if (SharedInfo::VisionAxisNLimitSignal[i] == 1) nSystemNLimitSignal = 1;
				if (SharedInfo::VisionAxisAlarmStatus[i] == 1) nSystemAlarmStatus = 1;

				AxmSignalIsServoOn(i, &dwStatus);

				SharedInfo::VisionAxisServoOnStatus[i] = dwStatus;

				if (SharedInfo::VisionAxisServoOnStatus[i] == 0) nSystemServoOnStatus = 0;

				AxmStatusReadInMotion(i, &dwStatus);

				SharedInfo::VisionAxisInMotionStatus[i] = (dwStatus | (dwStatus & (nInPos)));

				if (SharedInfo::VisionAxisInMotionStatus[i] == 1) nSystemMotionDoneStatus = 0;

				dwStatus = 0; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus					

				if (SharedInfo::VisionAxisHomeSignal[i] == 1)
				{
					dwStatus = (dwStatus | (0x01 << 0));
				}
				if (SharedInfo::VisionAxisServoOnStatus[i] == 1)
				{
					dwStatus = (dwStatus | (0x01 << 1));
				}
				if (SharedInfo::VisionAxisAlarmStatus[i] == 1)
				{
					dwStatus = (dwStatus | (0x01 << 2));
				}
				if (SharedInfo::VisionAxisInMotionStatus[i] == 0)
				{
					dwStatus = (dwStatus | (0x01 << 3));
				}

				SharedInfo::VisionAxisStatus[i] = dwStatus;

#pragma region //20201030 KJT Add
				if (/*!SharedInfo::VisionAxisHomeStatus[i] || */!SharedInfo::VisionAxisServoOnStatus[i] || SharedInfo::VisionAxisAlarmStatus[i] || SharedInfo::VisionAxisInMotionStatus[i])
				{
					bFlag = FALSE;
				}
#ifndef SIM_MODE
				SharedInfo::bDirectAjinSystemReadyStatus = bFlag;
#else
				SharedInfo::bDirectAjinSystemReadyStatus = TRUE;
#endif
#pragma endregion

				//KJT 20210520 AWK
				if (SharedInfo::VisionAxisServoOnStatus[i] == 0)
				{
					if (SharedInfo::VisionAxisHomeStatus[i] == 1)
						AxmHomeSetResult(i, HOME_ERR_USER_BREAK);
				}

				//Sleep(1);
			}

			Sleep(nSamplingTime);
			//tick = GetTickCount() - ticktmp;
			//Etc_Msg(_T("Tick : %d"), tick);
			//if (pVisionAgentDlg->m_ImageView)
			//	pVisionAgentDlg->m_ImageView.Invalidate();

			//	if (pStateMan) pStateMan->SetEvent();

			//Ssmin AjinRecovery
			if (pVisionAgentDlg->m_bHomeChk == FALSE)
			{
				pVisionAgentDlg->m_bHomeChk = TRUE;
				pVisionAgentDlg->LoadAjinHomeParameter(); //KJT 20210520 AWK
				pVisionAgentDlg->AjinHomeRecovery();
			}
			else
			{
#if 0
				pVisionAgentDlg->SaveAjinHomeParameter();
#else //KJT 20210520 AWK
				pVisionAgentDlg->SaveAjinHomeParameterTempFile();
				pVisionAgentDlg->CopyTempFile();
#endif
			}

			for (int i = 0; i < MAX_VISION_AXIS_SIZE; i++)
			{
				if (SharedInfo::VisionAxisServoOnStatus[i] == 0)
				{
					if (SharedInfo::VisionAxisHomeStatus[i] == 1)
						AxmHomeSetResult(i, HOME_ERR_USER_BREAK);
				}
			}
		}

	}

	pVisionAgentDlg->m_nIsRunningStatusThread = 0;
	//	GetWindowRect
	return 0;
}

UINT SaftyThreadProc(LPVOID lpParam)
{
	enum_Axis eAxis = AXIS_NONE;

	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)lpParam;


	//	double dPos[3];
	double dCheckPos = 0, dCmdVel = 0;
	//double dVolt;
	CString Str;
	//	DWORD dwStatus, dwValue;

	double dLapse = 0.0;

	//	DWORD dwResult;

	Safety SafetyChk;

	//KJT 20210313
	DWORD tickDoorOpenOutput[4], tick[4], DoorOpenTimeout[4] = { 10000, 30000, 15000, 15000 }; //Front, Back, Left, Right

	Sleep(1000);

	//	DWORD ticktmp, tick;
	pVisionAgentDlg->m_nIsRunningSaftyThread = 1;

	while (!pVisionAgentDlg->m_nStopSaftyThread)
	{
		if (pVisionAgentDlg->m_nConnect == 0)
		{
			Sleep(1000);
			continue;
		}
		if (pVisionAgentDlg->m_nStopSaftyThread == 1)
			break;

		if (SharedInfo::GetAlarm() == TRUE)
		{
			//ticktmp = GetTickCount();
			//if (ticktmp - tick > 30000)
			//{
			//	//TT
			//	SharedInfo::MachineState.bErrorFlag = TRUE;
			//}
			//Sleep(500);
			Sleep(1000);
			continue;
		}
			
		//Door
		if (!SafetyChk.DoorCheck())
		{
			pVisionAgentDlg->bDoorOpenFlag = TRUE;
			continue;
		}
		else
		{
			pVisionAgentDlg->bDoorOpenFlag = FALSE;
		}

		//Gantry Pressure
		if (!SafetyChk.GantryPresureCheck())
		{
			continue;
		}
	
		//EMO Check.
		if (!SafetyChk.EmergercyCheck())
		{
			continue;
		}

		//항온기 온도 체크
		if (!SafetyChk.TemperCheck())
		{
			continue;
		}

		//EFU 체크
		if (!SafetyChk.EFUCheck())
		{
			continue;
		}

		//AIR DRYER 체크
		if (!SafetyChk.AIR_DRYERCheck())
		{
			continue;
		}
#if 0
		//ELBC Check.
		if (!SafetyChk.GantryAirBearingCheck())
		{
			continue;
		}

		//VSP 알람.
		if (!SafetyChk.VpsCheck())
		{
			continue;
		}
		//Gripper Z Gantry Break;


		//Backlight 충돌 IO
		if (!SafetyChk.BacklightCollisionCheck())
		{
			continue;
		}

		

		//모터.
		for (int i = 0; i < AXIS_VIRTUAL_GRIPPER_Y; i++)
		{
			eAxis = (enum_Axis)i;

			//Gripper Z축은 Gantry로 Left와 Gantry Break 신호로 같이 체크.
			if (eAxis == AXIS_GRIPPER_Z_R || eAxis == AXIS_GRIPPER_Z_R)
				continue;



			//Pusher No Use
			if (eAxis >= AXIS_GRIPPER_PUSHER_L1_FB && eAxis <= AXIS_GRIPPER_PUSHER_R2_UD)
				continue;

			//Home / Servo On Check.
			if (!SafetyChk.AxisReadyCheck(eAxis))
			{
				break;
			}
		}

		//Motor Pos interlock (Jog Interlock)
		if (SharedInfo::m_eAxisJog == AXIS_GRIPPER_Y_L || SharedInfo::m_eAxisJog == AXIS_GRIPPER_Y_R)
		{
			dCheckPos = SharedInfo::GetActPos(SharedInfo::m_eAxisJog);
		}
		else if (SharedInfo::m_eAxisJog == AXIS_VIRTUAL_GRIPPER_Y)
		{
			dCheckPos = SharedInfo::GetActPos(AXIS_GRIPPER_Y_L);
		}

		else
		{
			dCheckPos = SharedInfo::GetCmdPos(SharedInfo::m_eAxisJog);
		}


#ifdef SAFETY_USE
		if (!SafetyChk.AxisAllMotionSafetyCheck(SharedInfo::m_eAxisJog, dCheckPos))
		{
			SharedInfo::m_eAxisJogInterlock = SharedInfo::m_eAxisJog;
			SharedInfo::m_nJogInterlockDir = SharedInfo::m_nJogDir;

			//Jog Stop
			Devs::m_JogMotion.JogStop(SharedInfo::m_eAxisJog);
			//SharedInfo::m_eAxisJog = AXIS_NONE;
			continue;
		}
#endif
#endif

		//Last Check Motion Done.
		//if (!Devs::IsMotionDone())
		//{
		//	SharedInfo::MachineState.bSemiAutoRunFlag = TRUE;
		//}
		//else
		//{
		//	SharedInfo::MachineState.bSemiAutoRunFlag = FALSE;
		//}
		Sleep(500);
	}
	pVisionAgentDlg->m_nIsRunningSaftyThread = 0;
	return 0;
}

void CVisionAgentDlg::AjinHomeRecovery()
{
	CString strTemp1 = _T("");
	CString strTemp2 = _T("");

	for (int i = 0; i < MAX_VISION_AXIS_SIZE; i++)
	{
		strTemp1.Format(_T("%.5f"), m_dAxisCmdFinishPos[i]);
		strTemp2.Format(_T("%.5f"), SharedInfo::VisionAxisCmdPos[i]);

		if ((BOOL)SharedInfo::VisionAxisServoOnStatus[i] && m_bAxisFinalHomeStatus[i])
		{
			//if (_ttof(strTemp2) <= (_ttof(strTemp1) + 0.002) && _ttof(strTemp2) >= (_ttof(strTemp1) - 0.002))
			if (fabs(_ttof(strTemp2) - _ttof(strTemp1)) < 0.002)
			{
				AxmHomeSetResult(i, HOME_SUCCESS);
			}
		}
	}
}

int CVisionAgentDlg::SaveAjinHomeParameter()
{
	for (int i = 0; i < DIRECT_AXIS_MAX; i++)
	{
		SharedInfo::DirectAixsHome.Info.dCmdPos[i] = m_dAxisCmdFinishPos[i];
		SharedInfo::DirectAixsHome.Info.bHomeStatus[i] = m_bAxisFinalHomeStatus[i];
	}

	SharedInfo::DirectAixsHome.Save();
	return 0;
}

int CVisionAgentDlg::SaveAjinHomeParameterTempFile() //KJT 20210520 AWK
{
	CStdioFile OutFile;
	CString StrData, strPath;
	int i;
	strPath.Format(_T("%s"), SharedInfo::VisionAgentPath);
	strPath.AppendFormat(_T("\\Data\\"));
	::CreateDirectory(strPath, NULL);
	strPath.AppendFormat(_T("Axis_Data\\"));
	::CreateDirectory(strPath, NULL);
	strPath.AppendFormat(_T("Axis_Data_Temp.txt"));

	if (OutFile.Open(strPath, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE) return 0;

	StrData.Format(_T("#BEGIN\n"));
	OutFile.WriteString(StrData);

	for (i = 0; i < DIRECT_AXIS_MAX; i++)
	{
		StrData.Format(_T("[COM_POS%d]\t%.5f\n"), i, SharedInfo::VisionAxisCmdPos[i]);
		OutFile.WriteString(StrData);

		StrData.Format(_T("[HOME_STATUS%d]\t%d\n"), i, SharedInfo::VisionAxisHomeStatus[i]);
		OutFile.WriteString(StrData);
	}

	StrData.Format(_T("#END\n"));
	OutFile.WriteString(StrData);

	OutFile.Close();

	return 0;
}

int CVisionAgentDlg::CopyTempFile() //KJT 20210520 AWK
{
	CString StrData, strOldPath, strNewPath;
	int i;
	strOldPath.Format(_T("%s"), SharedInfo::VisionAgentPath);
	strOldPath.AppendFormat(_T("\\Data\\"));
	::CreateDirectory(strOldPath, NULL);
	strOldPath.AppendFormat(_T("Axis_Data\\"));
	::CreateDirectory(strOldPath, NULL);

	strNewPath = strOldPath;

	strOldPath.AppendFormat(_T("Axis_Data_Temp.txt"));
	strNewPath.AppendFormat(_T("Axis_Data.txt"));

	::CopyFile(strOldPath, strNewPath, FALSE);

	return 0;
}

int CVisionAgentDlg::LoadAjinHomeParameter()
{
	CStdioFile InFile;
	CString strIndex = _T("");
	CString strSrc = _T("");
	CString strResult = _T("");
	TCHAR tchPathName[256];
	int nIndex = 0;
	int nFind = -1;

	SharedInfo::DirectAixsHome.Load();

	for (int i = 0; i < DIRECT_AXIS_MAX; i++)
	{
		m_dAxisCmdFinishPos[i] = SharedInfo::DirectAixsHome.Info.dCmdPos[i];
		m_bAxisFinalHomeStatus[i] = SharedInfo::DirectAixsHome.Info.bHomeStatus[i];
	}

	return 0;

}
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ´ëÈ­ »óÀÚ µ¥ÀÌÅÍÀÔ´Ï´Ù.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	// DDX/DDV Áö¿øÀÔ´Ï´Ù.

// ±¸ÇöÀÔ´Ï´Ù.
protected:
	DECLARE_MESSAGE_MAP()
public:
};
//---------------------------------------------------------------------
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}
//---------------------------------------------------------------------
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//---------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)	

END_MESSAGE_MAP()


// CVisionAgentDlg ´ëÈ­ »óÀÚ
//---------------------------------------------------------------------
CVisionAgentDlg::CVisionAgentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisionAgentDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hWnd = NULL;
	
#ifndef MIL_NOT_USE
	Devs::MilSysSol0 = NULL;
	Devs::MilSysSol1 = NULL;
	Devs::MilSysSol2 = NULL;

	Devs::MilDigCam6G_LT = NULL;
	Devs::MilDigCam6G_RT = NULL;
	Devs::MilDigCam6G_RB = NULL;
	Devs::MilDigCam6G_LB = NULL;

	Devs::MilDigCam8G_LT = NULL;
	Devs::MilDigCam8G_RT = NULL;
	Devs::MilDigCam8G_RB = NULL;
	Devs::MilDigCam8G_LB = NULL;

	//Devs::MilDigReview10X = NULL;
#endif
	
	m_nAutoCnt = 0;
	m_nCurLogDlg = 0;
}
//---------------------------------------------------------------------
CVisionAgentDlg::~CVisionAgentDlg()
{
}
//---------------------------------------------------------------------
void CVisionAgentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RDO_CAMERA_VIEW_6G, m_radioCamView6G);
	DDX_Control(pDX, IDC_RDO_CAMERA_VIEW_8G, m_radioCamView8G);
	DDX_Control(pDX, IDC_CHECK_SHOW_PROCESS_SUB, m_CheckProcessDlg);
}
//---------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CVisionAgentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_MESSAGE(UM_SERIAL_COMMAND_MSG, &CVisionAgentDlg::OnReceiveCommand)
	ON_STN_CLICKED(IDC_STATIC_MODEL_BTN, &CVisionAgentDlg::OnStnClickedStaticModelBtn)
	ON_STN_CLICKED(IDC_STATIC_MANUAL_BTN, &CVisionAgentDlg::OnStnClickedStaticManualBtn)
	ON_STN_CLICKED(IDC_STATIC_COMMUNICATION_BTN, &CVisionAgentDlg::OnStnClickedStaticCommunicationBtn)
	ON_STN_CLICKED(IDC_STATIC_SYSTEM_BTN, &CVisionAgentDlg::OnStnClickedStaticSystemBtn)
	ON_STN_CLICKED(IDC_STATIC_HANSONG_TITLE, &CVisionAgentDlg::OnStnClickedStaticHansongTitle)
	ON_STN_CLICKED(IDC_STATIC_STOP_BTN, &CVisionAgentDlg::OnStnClickedStaticStopBtn)
//	ON_STN_CLICKED(IDC_STATIC_MAIN_TITLE, &CVisionAgentDlg::OnStnClickedStaticMainTitle)
	ON_STN_CLICKED(IDC_STATIC_MEASUREMENT_BTN, &CVisionAgentDlg::OnStnClickedStaticMeasurementBtn)
	ON_STN_CLICKED(IDC_STATIC_AUTO_RUN_BTN, &CVisionAgentDlg::OnStnClickedStaticAutoRunBtn)
	ON_STN_CLICKED(IDC_STATIC_AUTO_RUN_DISPLAY, &CVisionAgentDlg::OnStnClickedStaticAutoRunDisplay)
	ON_STN_DBLCLK(IDC_STATIC_AUTO_RUN_DISPLAY, &CVisionAgentDlg::OnStnDblclickStaticAutoRunDisplay)
	ON_STN_CLICKED(IDC_STATIC_READY_BTN, &CVisionAgentDlg::OnStnClickedStaticReadyBtn)
	ON_STN_CLICKED(IDC_LOG_ALL, &CVisionAgentDlg::OnStnClickedLogAll)
	ON_STN_CLICKED(IDC_LOG_PROCESS, &CVisionAgentDlg::OnStnClickedLogProcess)
	ON_STN_CLICKED(IDC_LOG_SYSTEM, &CVisionAgentDlg::OnStnClickedLogSystem)
	ON_STN_CLICKED(IDC_LOG_VISION, &CVisionAgentDlg::OnStnClickedLogVision)
	ON_STN_CLICKED(IDC_LOG_ETC, &CVisionAgentDlg::OnStnClickedLogEtc)
	ON_STN_CLICKED(IDC_LOG_ALARM, &CVisionAgentDlg::OnStnClickedLogAlarm)
	ON_BN_CLICKED(IDC_CHECK_SHOW_PROCESS_SUB, &CVisionAgentDlg::OnBnClickedCheckShowProcessSub)
	ON_STN_CLICKED(IDC_STATIC_MACHINE_BTN, &CVisionAgentDlg::OnStnClickedStaticMachineBtn)
	ON_BN_CLICKED(IDC_RDO_CAMERA_VIEW_6G, &CVisionAgentDlg::OnBnClickedRdoCamView6g)
	ON_BN_CLICKED(IDC_RDO_CAMERA_VIEW_8G, &CVisionAgentDlg::OnBnClickedRdoCamView8g)
	ON_STN_DBLCLK(IDC_STATIC_MAIN_TITLE, &CVisionAgentDlg::OnStnDblclickStaticMainTitle)
	ON_STN_CLICKED(IDC_STATIC_MAIN_ALARM, &CVisionAgentDlg::OnStnClickedStaticMainAlarm)
	ON_STN_CLICKED(IDC_STATIC_ECS_BTN, &CVisionAgentDlg::OnStnClickedStaticEcsBtn)
	
END_MESSAGE_MAP()
//---------------------------------------------------------------------
// CVisionAgentDlg ¸Þ½ÃÁö Ã³¸®±â

BOOL CVisionAgentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ½Ã½ºÅÛ ¸Þ´º¿¡ "Á¤º¸..." ¸Þ´º Ç×¸ñÀ» Ãß°¡ÇÕ´Ï´Ù.

	// IDM_ABOUTBOX´Â ½Ã½ºÅÛ ¸í·É ¹üÀ§¿¡ ÀÖ¾î¾ß ÇÕ´Ï´Ù.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Å« ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.
	SetIcon(m_hIcon, FALSE);		// ÀÛÀº ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.

	//20201106
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	unsigned int Resolution = __min(__max(tc.wPeriodMin, 0), tc.wPeriodMax);
	timeBeginPeriod(Resolution);

	m_bDisplay = TRUE;

	CString szMsg = _T(""), Str = _T("");
	CFile file;
	TCHAR tchPathName[_MAX_PATH];
#pragma region	// Log Setting----------------------------------------------------------------
	int i, nSize;
	CRect re;

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
	SharedInfo::VisionAgentPath.Format(_T("%s"), tchPathName);

	CLogDefine::Initialize();

	if (CLogDefine::LoggerPtr)
	{
		CString strPath;
		//sunghaklee(2018.12.26)
		//strPath.Format(_T("%s\\LOG\\Vision"), SharedInfo::VisionAgentPath);

		static TCHAR pBuf[256] = { 0, };
		GetModuleFileName(NULL, pBuf, sizeof(pBuf));
		PathRemoveFileSpec(pBuf);
		//PathRemoveFileSpec(pBuf);
		//PathRemoveFileSpec(pBuf);
		strPath.Format(_T("%s\\Log"), pBuf);
		if (IsSameDirectory(strPath) == FALSE)
		{
			CreateDirectory(strPath, NULL);
		}

		CLogDefine::LoggerPtr->SetLogPath(strPath);
	}
#pragma endregion

	MakeDefaultDir();

#ifndef MIL_NOT_USE //Vision-----------------------------------------------------------------------------------
	CString strDcfFileCam6G_LT = SharedInfo::VisionAgentPath + _T("\\Data\\DCF\\GIGE_DEV0_Cam6G_LT.dcf");
	CString strDcfFileCam6G_RT = SharedInfo::VisionAgentPath + _T("\\Data\\DCF\\GIGE_DEV0_Cam6G_RT.dcf");
	CString strDcfFileCam6G_RB = SharedInfo::VisionAgentPath + _T("\\Data\\DCF\\GIGE_DEV0_Cam6G_RB.dcf");
	CString strDcfFileCam6G_LB = SharedInfo::VisionAgentPath + _T("\\Data\\DCF\\GIGE_DEV0_Cam6G_LB.dcf");

	CString strDcfFileCam8G_LT = SharedInfo::VisionAgentPath + _T("\\Data\\DCF\\GIGE_DEV0_Cam8G_LT.dcf");
	CString strDcfFileCam8G_RT = SharedInfo::VisionAgentPath + _T("\\Data\\DCF\\GIGE_DEV0_Cam8G_RT.dcf");
	CString strDcfFileCam8G_RB = SharedInfo::VisionAgentPath + _T("\\Data\\DCF\\GIGE_DEV0_Cam8G_RB.dcf");
	CString strDcfFileCam8G_LB = SharedInfo::VisionAgentPath + _T("\\Data\\DCF\\GIGE_DEV0_Cam8G_LB.dcf");
	
	if (MappAlloc(M_DEFAULT, &Devs::MilApplication) == M_NULL) {
		AfxMessageBox(_T("[MIL APP ALLOC DEBUG] Mil Application Memory Alloc Error"));
		//		return -1;
	}
	else
	{
		MappControl(M_ERROR, M_PRINT_DISABLE);
		//MappControl(M_ERROR, M_PRINT_ENABLE);
	}

#pragma region //6G
	if (MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV0, M_COMPLETE, &Devs::MilSysSol0) != M_NULL)
	{
		if (!MdigAlloc(Devs::MilSysSol0, M_DEV0, strDcfFileCam6G_LT, M_DEFAULT, &Devs::MilDigCam6G_LT))
			Vision_Msg(_T("Init Camera 6G LT Error"));
		else
		{
			Vision_Msg(_T("Init Camera 6G LT Success"));
			MdigControl(Devs::MilDigCam6G_LT, M_GRAB_DIRECTION_X, M_REVERSE);
			MdigControl(Devs::MilDigCam6G_LT, M_GRAB_DIRECTION_Y, M_REVERSE);
		}
	}
	else
	{
		MsysAlloc(M_SYSTEM_HOST, M_DEV0, M_COMPLETE, &Devs::MilSysSol0);
	}

	if (MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV1, M_COMPLETE, &Devs::MilSysSol0) != M_NULL)
	{
		if (!MdigAlloc(Devs::MilSysSol0, M_DEV1, strDcfFileCam6G_RT, M_DEFAULT, &Devs::MilDigCam6G_RT))
			Vision_Msg(_T("Init Camera 6G RT Error"));
		else
		{
			Vision_Msg(_T("Init Camera 6G RT Success"));
			MdigControl(Devs::MilDigCam6G_RT, M_GRAB_DIRECTION_X, M_REVERSE);
			MdigControl(Devs::MilDigCam6G_RT, M_GRAB_DIRECTION_Y, M_REVERSE);
		}
	}
	else
	{
		MsysAlloc(M_SYSTEM_HOST, M_DEV1, M_COMPLETE, &Devs::MilSysSol0);
	}

	if (MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV2, M_COMPLETE, &Devs::MilSysSol0) != M_NULL)
	{
		if (!MdigAlloc(Devs::MilSysSol0, M_DEV2, strDcfFileCam6G_RB, M_DEFAULT, &Devs::MilDigCam6G_RB))
			Vision_Msg(_T("Init Camera 6G RB Error"));
		else
		{
			Vision_Msg(_T("Init Camera 6G RB Success"));
			MdigControl(Devs::MilDigCam6G_RB, M_GRAB_DIRECTION_X, M_REVERSE);
			MdigControl(Devs::MilDigCam6G_RB, M_GRAB_DIRECTION_Y, M_REVERSE);
		}
	}
	else
	{
		MsysAlloc(M_SYSTEM_HOST, M_DEV2, M_COMPLETE, &Devs::MilSysSol0);
	}

	if (MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV3, M_COMPLETE, &Devs::MilSysSol0) != M_NULL)
	{
		if (!MdigAlloc(Devs::MilSysSol0, M_DEV3, strDcfFileCam6G_LB, M_DEFAULT, &Devs::MilDigCam6G_LB))
			Vision_Msg(_T("Init Camera 6G LB Error"));
		else
		{
			Vision_Msg(_T("Init Camera 6G LB Success"));
			MdigControl(Devs::MilDigCam6G_LB, M_GRAB_DIRECTION_X, M_REVERSE);
			MdigControl(Devs::MilDigCam6G_LB, M_GRAB_DIRECTION_Y, M_REVERSE);
		}
	}
	else
	{
		MsysAlloc(M_SYSTEM_HOST, M_DEV3, M_COMPLETE, &Devs::MilSysSol0);
	}
#pragma endregion

#pragma region //8G
	if (MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV0, M_COMPLETE, &Devs::MilSysSol1) != M_NULL)
	{
		if (!MdigAlloc(Devs::MilSysSol1, M_DEV0, strDcfFileCam8G_LT, M_DEFAULT, &Devs::MilDigCam8G_LT))
			Vision_Msg(_T("Init Camera 8G LT Error"));
		else
		{
			Vision_Msg(_T("Init Camera 8G LT Success"));
			MdigControl(Devs::MilDigCam8G_LT, M_GRAB_DIRECTION_X, M_REVERSE);
			MdigControl(Devs::MilDigCam8G_LT, M_GRAB_DIRECTION_Y, M_REVERSE);
		}
	}
	else
	{
		MsysAlloc(M_SYSTEM_HOST, M_DEV0, M_COMPLETE, &Devs::MilSysSol1);
	}

	if (MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV1, M_COMPLETE, &Devs::MilSysSol1) != M_NULL)
	{
		if (!MdigAlloc(Devs::MilSysSol1, M_DEV1, strDcfFileCam8G_RT, M_DEFAULT, &Devs::MilDigCam8G_RT))
			Vision_Msg(_T("Init Camera 8G RT Error"));
		else
		{
			Vision_Msg(_T("Init Camera 8G RT Success"));
			MdigControl(Devs::MilDigCam8G_RT, M_GRAB_DIRECTION_X, M_REVERSE);
			MdigControl(Devs::MilDigCam8G_RT, M_GRAB_DIRECTION_Y, M_REVERSE);
		}
	}
	else
	{
		MsysAlloc(M_SYSTEM_HOST, M_DEV1, M_COMPLETE, &Devs::MilSysSol1);
	}

	if (MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV2, M_COMPLETE, &Devs::MilSysSol1) != M_NULL)
	{
		if (!MdigAlloc(Devs::MilSysSol1, M_DEV2, strDcfFileCam8G_RB, M_DEFAULT, &Devs::MilDigCam8G_RB))
			Vision_Msg(_T("Init Camera 8G RB Error"));
		else
		{
			Vision_Msg(_T("Init Camera 8G RB Success"));
			MdigControl(Devs::MilDigCam8G_RB, M_GRAB_DIRECTION_X, M_REVERSE);
			MdigControl(Devs::MilDigCam8G_RB, M_GRAB_DIRECTION_Y, M_REVERSE);
		}
	}
	else
	{
		MsysAlloc(M_SYSTEM_HOST, M_DEV2, M_COMPLETE, &Devs::MilSysSol1);
	}

	if (MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV3, M_COMPLETE, &Devs::MilSysSol1) != M_NULL)
	{
		if (!MdigAlloc(Devs::MilSysSol1, M_DEV3, strDcfFileCam8G_LB, M_DEFAULT, &Devs::MilDigCam8G_LB))
			Vision_Msg(_T("Init Camera 8G LB Error"));
		else
		{
			Vision_Msg(_T("Init Camera 8G LB Success"));
			MdigControl(Devs::MilDigCam8G_LB, M_GRAB_DIRECTION_X, M_REVERSE);
			MdigControl(Devs::MilDigCam8G_LB, M_GRAB_DIRECTION_Y, M_REVERSE);
		}
	}
	else
	{
		MsysAlloc(M_SYSTEM_HOST, M_DEV3, M_COMPLETE, &Devs::MilSysSol1);
	}
#pragma endregion
	
	//6G
	Devs::m_Camera6G_LT = new CWkLibVision(0, Devs::MilApplication, Devs::MilSysSol0, Devs::MilDigCam6G_LT);
	Devs::m_Camera6G_LT->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	Devs::m_Camera6G_LT->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LT, this);

	Devs::m_Camera6G_RT = new CWkLibVision(1, Devs::MilApplication, Devs::MilSysSol0, Devs::MilDigCam6G_RT);
	Devs::m_Camera6G_RT->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	Devs::m_Camera6G_RT->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RT, this);

	Devs::m_Camera6G_RB = new CWkLibVision(2, Devs::MilApplication, Devs::MilSysSol0, Devs::MilDigCam6G_RB);
	Devs::m_Camera6G_RB->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	Devs::m_Camera6G_RB->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RB, this);

	Devs::m_Camera6G_LB = new CWkLibVision(3, Devs::MilApplication, Devs::MilSysSol0, Devs::MilDigCam6G_LB);
	Devs::m_Camera6G_LB->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	Devs::m_Camera6G_LB->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LB, this);

	//8G
	Devs::m_Camera8G_LT = new CWkLibVision(4, Devs::MilApplication, Devs::MilSysSol0, Devs::MilDigCam8G_LT);
	Devs::m_Camera8G_LT->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	Devs::m_Camera8G_LT->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LT, this);

	Devs::m_Camera8G_RT = new CWkLibVision(5, Devs::MilApplication, Devs::MilSysSol0, Devs::MilDigCam8G_RT);
	Devs::m_Camera8G_RT->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	Devs::m_Camera8G_RT->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RT, this);

	Devs::m_Camera8G_RB = new CWkLibVision(6, Devs::MilApplication, Devs::MilSysSol0, Devs::MilDigCam8G_RB);
	Devs::m_Camera8G_RB->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	Devs::m_Camera8G_RB->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RB, this);

	Devs::m_Camera8G_LB = new CWkLibVision(7, Devs::MilApplication, Devs::MilSysSol0, Devs::MilDigCam8G_LB);
	Devs::m_Camera8G_LB->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	Devs::m_Camera8G_LB->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LB, this);

	//Devs::m_Camera10X = new CWkLibVision(0, Devs::MilApplication, Devs::MilSysSol1, Devs::MilDigReview10X);
	//Devs::m_Camera10X->SetCameraSize(CAM_BUF_SIZE_X_5M, CAM_BUF_SIZE_Y_5M);
	//Devs::m_Camera10X->SubclassDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RT, this);

	//g_pReview10x = new CCamAreaModul(0, Devs::MilSysSol1, Devs::MilDigReview10X, DIRECT_AXIS_CAMERA_Z1);
	//g_pReview10x->Create(NULL, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, CRect(0, 0, 0, 0), this, 25005);

	
#endif

#ifndef SIM_MODE
#pragma region  //Light
	//g_CommLight_8ch.Init(COM_PORT_LIGHT_8CH, this->m_hWnd, 0);
	//g_CommLight_12ch.Init(COM_PORT_LIGHT_12CH, this->m_hWnd, 0);
	//g_CommMLCLedLight.Init(COM_PORT_MLC_LIGHT, this->m_hWnd, 0);
	//21.02.16 sjc
	//g_CommBack_Light.Init(COM_PORT_BACK_LIGHT, this->m_hWnd, 0);
	//g_CommReview_Light.Init(COM_PORT_REVIEW_LIGHT, this->m_hWnd, 0);
	//g_CommLoader_Light.Init(COM_PORT_LOADER_LIGHT, this->m_hWnd, 0);

	//g_CommZomm_Ring.Init(COM_PORT_ZOOM_RING, this->m_hWnd, 0);
	//g_CommZomm_Coaxial.Init(COM_PORT_ZOOM_COAXIAL, this->m_hWnd, 0);
	
	g_CommTempTur.Init(COM_PORT_TEMPER, this->m_hWnd, 0);
	//21.04.03 sjc aoi laser sensor
	//g_CommAOILaser.Init(COM_PORT_AOI_LASER_FOCUS, this->m_hWnd, 0);

	//SharedInfo::nAutoFocusCameraMode = eViewReview10X;

	SharedInfo::TempurInterval = 60000; //1Min
	//21.04.09 sjc
	//g_CommESC.Init(COM_PORT_ESC, this->m_hWnd, 0);

#pragma endregion
#endif

	//CimInfo::Initialize();

	//AddListColumn();
	SharedInfo::Initialize();
	SharedInfo::ActiveInfoLoad();
	SharedInfo::ResultInfoLoad();

	SharedInfo::LoadRecipeTable();
	szMsg = SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum);

	SharedInfo::InitModelData();
	SharedInfo::LoadModelData(szMsg);
	SharedInfo::LoadSystemData();
	SharedInfo::LoadManualData();
	SharedInfo::LoadMachineData();
	
	Devs::Initialize();

	SharedInfo::FindModelNames();

	LoadAxisLabelParameter();
	LoadDInputLabelParameter();
	LoadDOutputLabelParameter();
	LoadAInputLabelParameter();
	LoadAOutputLabelParameter();

#pragma region Simulation View
	//CRect rect;
	//GetDlgItem(IDC_STATIC_VISION_AGENT_SIMULATION_VIEW)->GetWindowRect(&rect);
	m_VisionAgentSimulationViewDlg.Create(IDD_VISION_AGENT_SIMULATION_VIEW_DIALOG, this);
	//m_VisionAgentSimulationViewDlg.SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL);
	//m_VisionAgentSimulationViewDlg.MoveWindow(&rect);
#pragma endregion

	////
	m_StrMotFilePath.Format(_T("%s\\Data\\Ajin\\AjinPara.mot"), SharedInfo::VisionAgentPath);

#ifndef SIM_MODE
	if (AxlOpenNoReset(7) != AXT_RT_SUCCESS)
	//if(AxlOpen(7) != AXT_RT_SUCCESS)
	{
		Alarm_Msg(_T("Axl is not opened."));
	}
	else
	{
		m_nAXLOpen = 1;
		GetBoardInfo();
		GetMotionPara();
		LoadAjinHomeParameter();

		for (int i = 0; i < m_nVisionMaxAxisSize; i++)
		{
			AxmMotSetAbsRelMode(i, 0);//abs
		}

		Etc_Msg(_T("Axl is opened."));
	}
#endif
	
	//Etc_Msg();
	DialogInit();
	NetworkInit();
	InitSubDlg();
	Init_Log_Dlg();
	ShowWindow(SW_SHOWMAXIMIZED);

	m_radioCamView6G.SetCheck(TRUE);

	m_ePrevCamViewMode = eCamView_NONE;
	SharedInfo::eCamViewMode = eCamView_6G;

#ifndef SIM_MODE
	m_pLaserDisp = new CWkLibLaserDispOm(this);
	m_pLaserDisp->CreateControl();
	m_pLaserDisp->OpenPort(COM_PORT_LASER_FOCUS, _T("38400"));
#endif

	//Network
	m_nConnect = 0;
	m_bConnectWorkNetwork = FALSE;
	//	m_nSocketReceiveFlag = TRUE;
	m_SocketWrite.SetParentDlg(this);
	Devs::MotionIf.SetParentDlg(this);

#ifndef SIM_MODE
	ConnectWorkNetwork();	//#####
	m_nRetryCnt = 0;
	while (1)
	{
		if (m_nConnect == 1)
			break;

		if (m_nRetryCnt >= 50)
		{
			break;
		}
		m_nRetryCnt++;
		Sleep(100);
	}

	if (m_nConnect)
	{
#if 0
		double dPosUvw[3] = { 0.0, 0.0, 0.0 };
		Devs::MotionIf.UvwGetCmdPos(MASK_UVW, dPosUvw);
		Sleep(20);

		Devs::MotionIf.UvwGetCmdPos(FRAME_UVW, dPosUvw);
		Sleep(20);
#endif

		m_nStopMonitoringThread = 0;
		m_pMonitoringThread = AfxBeginThread(MonitoringThreadProc, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, CREATE_SUSPENDED);
		Sleep(100);
		m_pMonitoringThread->ResumeThread();

		Sleep(1000);
		m_nStopStatusThread = 0;
		m_pStatusThread = AfxBeginThread(AjinStatusThreadProc, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, CREATE_SUSPENDED);
		Sleep(100);
		m_pStatusThread->ResumeThread();

		Sleep(1000);

		m_nStopSaftyThread = 0;
		m_pSaftyThread = AfxBeginThread(SaftyThreadProc, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, CREATE_SUSPENDED);
		Sleep(100);
		m_pSaftyThread->ResumeThread();
	}
#endif

	SetDefaultOutput();

	System_Msg(_T("---------- VisionAgent Start ----------"));

#ifdef GRIPPER_0
	CModelData::m_InspectionPara.Info.nStickTensionUseMode = eSTICK_TENSION_NO;
#endif

	SetTimer(1, 100, NULL);
	//21.07.29 sjc hsms
#ifndef SIM_MODE
#if 0 //Temp
//--XComPro Init
	Xcom_Init();

	//--SECS
	//테스트 준비 안되서 임시 삭제
	m_pSecs = CSecs::Create();
	if (m_pSecs)
	{
		m_pSecs->SetMainDlgHandle(this);
		m_pSecs->SetMainDlgHWnd(this->m_hWnd);
		m_pSecs->Start();
	}
	//--
	m_pSecs->S1F1();//21.07.14 서종천
#endif
#endif
	//
	return TRUE;  
}
//---------------------------------------------------------------------
void CVisionAgentDlg::NetworkInit()
{

}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ±×¸®±â¸¦ À§ÇÑ µð¹ÙÀÌ½º ÄÁÅØ½ºÆ®ÀÔ´Ï´Ù.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Å¬¶óÀÌ¾ðÆ® »ç°¢Çü¿¡¼­ ¾ÆÀÌÄÜÀ» °¡¿îµ¥¿¡ ¸ÂÃä´Ï´Ù.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ¾ÆÀÌÄÜÀ» ±×¸³´Ï´Ù.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//---------------------------------------------------------------------
HCURSOR CVisionAgentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::DialogInit()
{
	//메인 상태바
	CRect rect;
	LOGFONT LogoMainFont, LogoHansongFont, StateBarFont, MainMenuFont, AutoRunDisp,FlowFont,FlowProcessFont,QuickDataPos, NamingFont;
	CString strTemp = _T("");
	memset(&MainMenuFont, 0, sizeof(LOGFONT));
	MainMenuFont.lfHeight = 20;
	MainMenuFont.lfWeight = FW_NORMAL;
	m_fontMainMenu.CreateFontIndirect(&MainMenuFont);

	//메인 상태바
	memset(&LogoMainFont, 0, sizeof(LOGFONT));
	LogoMainFont.lfHeight = 30;
	LogoMainFont.lfWeight = FW_HEAVY;
	m_fontStcMainLogo.CreateFontIndirect(&LogoMainFont);

	memset(&LogoHansongFont, 0, sizeof(LOGFONT));
	LogoHansongFont.lfHeight = 30;
	LogoHansongFont.lfWeight = FW_HEAVY;
	m_fontStcHansongLogo.CreateFontIndirect(&LogoHansongFont);

	memset(&StateBarFont, 0, sizeof(LOGFONT));
	StateBarFont.lfHeight = 15;
	StateBarFont.lfWeight = FW_NORMAL;
	m_fontStateBar.CreateFontIndirect(&StateBarFont);

	memset(&AutoRunDisp, 0, sizeof(LOGFONT));
	AutoRunDisp.lfHeight = 40;
	AutoRunDisp.lfWeight = FW_HEAVY;
	m_fontAutoRunDisp.CreateFontIndirect(&AutoRunDisp);

	memset(&NamingFont, 0, sizeof(LOGFONT));
	NamingFont.lfHeight = 20;
	NamingFont.lfWeight = FW_HEAVY;
	m_fontNaming.CreateFontIndirect(&NamingFont);

	memset(&FlowFont, 0, sizeof(LOGFONT));
	FlowFont.lfHeight = 15;
	FlowFont.lfWeight = 100;
	m_fontFlow.CreateFontIndirect(&FlowFont);

	memset(&FlowProcessFont, 0, sizeof(LOGFONT));
	FlowProcessFont.lfHeight = 20;
	FlowProcessFont.lfWeight = 400;
	m_fontFlowPrcess.CreateFontIndirect(&FlowProcessFont);

	memset(&QuickDataPos, 0, sizeof(LOGFONT));
	QuickDataPos.lfHeight = 16;
	QuickDataPos.lfWeight = 400;
	m_fontQuickData.CreateFontIndirect(&QuickDataPos);

	//Title----------------------------------------------------------------------------------------------------------------------------------
	m_stcMainTitle.SubclassDlgItem(IDC_STATIC_MAIN_TITLE, this);
	m_stcMainTitle.SetParaChangeColor(BK_GND);
	m_stcMainTitle.SetParaOriginColor(STATEBAR_NAME_BK_RGB);
	m_stcMainTitle.SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcMainTitle.SetTextColor(RGB(4, 131, 206));
	m_stcMainTitle.SetFont(&m_fontStcMainLogo, TRUE);
	m_stcMainTitle.SetData(_T("G8H"));

	//Hansong Title----------------------------------------------------------------------------------------------------------------------
	m_stcHansongTitle.SubclassDlgItem(IDC_STATIC_HANSONG_TITLE, this);
	m_stcHansongTitle.SetParaChangeColor(BK_GND);
	m_stcHansongTitle.SetParaOriginColor(STATEBAR_NAME_BK_RGB);
	m_stcHansongTitle.SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcHansongTitle.SetTextColor(RGB(100, 100, 100));
	m_stcHansongTitle.SetFont(&m_fontStcHansongLogo, TRUE);
	m_stcHansongTitle.SetData(_T("HSNEOTECH"));

	//Auto Run Display --------------------------------------------------------------------------------
	m_stcAutoRunDisp.SubclassDlgItem(IDC_STATIC_AUTO_RUN_DISPLAY, this);
	m_stcAutoRunDisp.SetParaOriginColor(RGB(45, 45, 45));
	m_stcAutoRunDisp.SetParaChangeColor(RGB(150, 150, 150));
	m_stcAutoRunDisp.SetBackgroundColor(RGB(45, 45, 45));
	m_stcAutoRunDisp.SetTextColor(RGB(255, 255, 255));
	m_stcAutoRunDisp.SetFont(&m_fontAutoRunDisp, TRUE);
	m_stcAutoRunDisp.SetData(_T("Stop"));
	m_stcAutoRunDisp.SetActButton(FALSE);
	m_stcAutoRunDisp.SetForegroundWindow();


	//Naming --------------------------------------------------------------------------------------------------------
	//Naming Review10X Camera --------------------------------------------------------------------------------
	m_stcCameraViewMode_Naming.SubclassDlgItem(IDC_STATIC_NAMING_CAMERA_VIEW_MODE, this);
	m_stcCameraViewMode_Naming.SetParaOriginColor(RGB(45, 45, 45));
	m_stcCameraViewMode_Naming.SetParaChangeColor(RGB(45, 45, 45));
	m_stcCameraViewMode_Naming.SetBackgroundColor(RGB(45, 45, 45));
	m_stcCameraViewMode_Naming.SetTextColor(RGB(255, 255, 255));
	m_stcCameraViewMode_Naming.SetFont(&m_fontNaming, TRUE);
	m_stcCameraViewMode_Naming.SetData(_T("Camera View Mode"));
	m_stcCameraViewMode_Naming.SetActButton(FALSE);
	m_stcCameraViewMode_Naming.SetForegroundWindow();
	
	//Naming Log --------------------------------------------------------------------------------
	m_stcLogNaming.SubclassDlgItem(IDC_STATIC_NAMING_LOG, this);
	m_stcLogNaming.SetParaOriginColor(RGB(45, 45, 45));
	m_stcLogNaming.SetParaChangeColor(RGB(45, 45, 45));
	m_stcLogNaming.SetBackgroundColor(RGB(45, 45, 45));
	m_stcLogNaming.SetTextColor(RGB(255, 255, 255));
	m_stcLogNaming.SetFont(&m_fontNaming, TRUE);
	m_stcLogNaming.SetData(_T("LOG"));
	m_stcLogNaming.SetActButton(FALSE);
	m_stcLogNaming.SetForegroundWindow();

#pragma region //Status Bar
	//User Mode
	m_stcStateBar_Name[STATE_MENU_USER_MODE].SubclassDlgItem(IDC_STATIC_USER_MODE, this);
	m_stcStateBar_Name[STATE_MENU_USER_MODE].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_USER_MODE].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_USER_MODE].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_USER_MODE].SetData(_T("User Mode"));
	m_stcStateBar_Value[STATE_MENU_USER_MODE].SubclassDlgItem(IDC_STATIC_USER_MODE_STATE, this);
	m_stcStateBar_Value[STATE_MENU_USER_MODE].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_USER_MODE].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_USER_MODE].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_USER_MODE].SetData(_T("Engineer"));

	//User ID
	m_stcStateBar_Name[STATE_MENU_USER_ID].SubclassDlgItem(IDC_STATIC_USER_ID, this);
	m_stcStateBar_Name[STATE_MENU_USER_ID].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_USER_ID].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_USER_ID].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_USER_ID].SetData(_T("Zoom"));
	m_stcStateBar_Value[STATE_MENU_USER_ID].SubclassDlgItem(IDC_STATIC_USER_ID_STATE, this);
	m_stcStateBar_Value[STATE_MENU_USER_ID].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_USER_ID].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_USER_ID].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_USER_ID].SetData(_T("Disconnected"));

	//Model Name
	m_stcStateBar_Name[STATE_MENU_MODEL_NAME].SubclassDlgItem(IDC_STATIC_MODEL_NAME, this);
	m_stcStateBar_Name[STATE_MENU_MODEL_NAME].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_MODEL_NAME].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_MODEL_NAME].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_MODEL_NAME].SetData(_T("Model Name"));
	m_stcStateBar_Value[STATE_MENU_MODEL_NAME].SubclassDlgItem(IDC_STATIC_MODEL_NAME_STATE, this);
	m_stcStateBar_Value[STATE_MENU_MODEL_NAME].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_MODEL_NAME].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_MODEL_NAME].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_MODEL_NAME].SetData(_T(""));

	//BOX ID
	m_stcStateBar_Name[STATE_MENU_BOX_ID].SubclassDlgItem(IDC_STATIC_BOX_ID, this);
	m_stcStateBar_Name[STATE_MENU_BOX_ID].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_BOX_ID].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_BOX_ID].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_BOX_ID].SetData(_T("BOX ID"));
	m_stcStateBar_Value[STATE_MENU_BOX_ID].SubclassDlgItem(IDC_STATIC_BOX_ID_STATE, this);
	m_stcStateBar_Value[STATE_MENU_BOX_ID].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_BOX_ID].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_BOX_ID].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_BOX_ID].SetData(_T("BOX"));

	//CST ID
	m_stcStateBar_Name[STATE_MENU_CST_ID].SubclassDlgItem(IDC_STATIC_CST_ID, this);
	m_stcStateBar_Name[STATE_MENU_CST_ID].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_CST_ID].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_CST_ID].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_CST_ID].SetData(_T("CST ID"));
	m_stcStateBar_Value[STATE_MENU_CST_ID].SubclassDlgItem(IDC_STATIC_CST_ID_STATE, this);
	m_stcStateBar_Value[STATE_MENU_CST_ID].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_CST_ID].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_CST_ID].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_CST_ID].SetData(_T("CST"));

	//CST Detect
	m_stcStateBar_Name[STATE_MENU_CST_DETECT].SubclassDlgItem(IDC_STATIC_CST_DETECT, this);
	m_stcStateBar_Name[STATE_MENU_CST_DETECT].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_CST_DETECT].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_CST_DETECT].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_CST_DETECT].SetData(_T("CST Detect"));
	m_stcStateBar_Value[STATE_MENU_CST_DETECT].SubclassDlgItem(IDC_STATIC_CST_DETECT_STATE, this);
	m_stcStateBar_Value[STATE_MENU_CST_DETECT].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_CST_DETECT].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_CST_DETECT].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_CST_DETECT].SetData(_T("Off"));

	//Laser Focus
	m_stcStateBar_Name[STATE_MENU_LASER_FOCUS].SubclassDlgItem(IDC_STATIC_LASER_FOCUS, this);
	m_stcStateBar_Name[STATE_MENU_LASER_FOCUS].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_LASER_FOCUS].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_LASER_FOCUS].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_LASER_FOCUS].SetData(_T("Laser Focus"));
	m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SubclassDlgItem(IDC_STATIC_LASER_FOCUS_STATE, this);
	m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetData(_T("Off"));

	//PickUp Unit
	m_stcStateBar_Name[STATE_MENU_PICKUP_UNIT].SubclassDlgItem(IDC_STATIC_PICKUP_UNIT, this);
	m_stcStateBar_Name[STATE_MENU_PICKUP_UNIT].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_PICKUP_UNIT].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_PICKUP_UNIT].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_PICKUP_UNIT].SetData(_T("PickUp Unit"));
	m_stcStateBar_Value[STATE_MENU_PICKUP_UNIT].SubclassDlgItem(IDC_STATIC_PICKUP_UNIT_STATE, this);
	m_stcStateBar_Value[STATE_MENU_PICKUP_UNIT].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_PICKUP_UNIT].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_PICKUP_UNIT].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_PICKUP_UNIT].SetData(_T("Fwd/Bwd"));

	//Clamp
	m_stcStateBar_Name[STATE_MENU_CLAMP].SubclassDlgItem(IDC_STATIC_CLAMP, this);
	m_stcStateBar_Name[STATE_MENU_CLAMP].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_CLAMP].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_CLAMP].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_CLAMP].SetData(_T("Clamp"));
	m_stcStateBar_Value[STATE_MENU_CLAMP].SubclassDlgItem(IDC_STATIC_CLAMP_STATE, this);
	m_stcStateBar_Value[STATE_MENU_CLAMP].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_CLAMP].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_CLAMP].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_CLAMP].SetData(_T("Clamp/Unclamp"));

	//Stretcher
	m_stcStateBar_Name[STATE_MENU_STRETCHER].SubclassDlgItem(IDC_STATIC_STRETCHER, this);
	m_stcStateBar_Name[STATE_MENU_STRETCHER].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_STRETCHER].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_STRETCHER].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_STRETCHER].SetData(_T("Stretcher"));
	m_stcStateBar_Value[STATE_MENU_STRETCHER].SubclassDlgItem(IDC_STATIC_STRETCHER_STATE, this);
	m_stcStateBar_Value[STATE_MENU_STRETCHER].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_STRETCHER].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_STRETCHER].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_STRETCHER].SetData(_T("Fwd/Bwd"));

	//AOI Connect Status
	m_stcStateBar_Name[STATE_MENU_AOI_CONNECT].SubclassDlgItem(IDC_STATIC_AOI_CONNECT, this);
	m_stcStateBar_Name[STATE_MENU_AOI_CONNECT].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_AOI_CONNECT].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_AOI_CONNECT].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_AOI_CONNECT].SetData(_T("AOI Connect"));
	m_stcStateBar_Value[STATE_MENU_AOI_CONNECT].SubclassDlgItem(IDC_STATIC_AOI_CONNECT_STATE, this);
	m_stcStateBar_Value[STATE_MENU_AOI_CONNECT].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_AOI_CONNECT].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_AOI_CONNECT].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_AOI_CONNECT].SetData(_T("Disconnected"));

	//AOI Ready Status
	m_stcStateBar_Name[STATE_MENU_AOI_READY_STATE].SubclassDlgItem(IDC_STATIC_AOI_READY_NAME, this);
	m_stcStateBar_Name[STATE_MENU_AOI_READY_STATE].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_AOI_READY_STATE].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_AOI_READY_STATE].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_AOI_READY_STATE].SetData(_T("AOI State"));
	m_stcStateBar_Value[STATE_MENU_AOI_READY_STATE].SubclassDlgItem(IDC_STATIC_AOI_READY_NAME_STATE, this);
	m_stcStateBar_Value[STATE_MENU_AOI_READY_STATE].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_AOI_READY_STATE].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_AOI_READY_STATE].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_AOI_READY_STATE].SetData(_T("Not Ready"));

	//3D Init Status
	m_stcStateBar_Name[STATE_MENU_3D_INIT].SubclassDlgItem(IDC_STATIC_3D_INITIAL, this);
	m_stcStateBar_Name[STATE_MENU_3D_INIT].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_3D_INIT].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_3D_INIT].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_3D_INIT].SetData(_T("3D Camera"));
	m_stcStateBar_Value[STATE_MENU_3D_INIT].SubclassDlgItem(IDC_STATIC_3D_INITIAL_STATE, this);
	m_stcStateBar_Value[STATE_MENU_3D_INIT].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_3D_INIT].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_3D_INIT].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_3D_INIT].SetData(_T("Disconnected"));

	//Main Temper
	m_stcStateBar_Name[STATE_MENU_MAIN_TEMPER].SubclassDlgItem(IDC_STATIC_MAIN_TEMPER, this);
	m_stcStateBar_Name[STATE_MENU_MAIN_TEMPER].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcStateBar_Name[STATE_MENU_MAIN_TEMPER].SetTextColor(STATEBAR_NAME_RGB);
	m_stcStateBar_Name[STATE_MENU_MAIN_TEMPER].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Name[STATE_MENU_MAIN_TEMPER].SetData(_T("Temper"));
	m_stcStateBar_Value[STATE_MENU_MAIN_TEMPER].SubclassDlgItem(IDC_STATIC_MAIN_TEMPER_STATE, this);
	m_stcStateBar_Value[STATE_MENU_MAIN_TEMPER].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
	m_stcStateBar_Value[STATE_MENU_MAIN_TEMPER].SetTextColor(STATEBAR_VALUE_RGB);
	m_stcStateBar_Value[STATE_MENU_MAIN_TEMPER].SetFont(&m_fontStateBar, TRUE);
	m_stcStateBar_Value[STATE_MENU_MAIN_TEMPER].SetData(_T("0.0"));
#pragma endregion

#pragma region //메인버튼
	//Model Button
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SubclassDlgItem(IDC_STATIC_MODEL_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SetParaOriginColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SetParaChangeColor(RGB(150, 150, 150));
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SetBackgroundColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SetData(_T("Model"));
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].SetForegroundWindow();
	
	//Manual Button
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SubclassDlgItem(IDC_STATIC_MANUAL_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SetParaOriginColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SetParaChangeColor(RGB(150, 150, 150));
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SetBackgroundColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SetData(_T("Manual"));
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_MANUAL_BTN].SetForegroundWindow();

	//Machine Button
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SubclassDlgItem(IDC_STATIC_MACHINE_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SetParaOriginColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SetBackgroundColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SetParaChangeColor(RGB(150, 150, 150));
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SetData(_T("Machine"));
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_MACHINE_BTN].SetForegroundWindow();

	//Communication Button
	m_stc_btnMainMenu[MAIN_MENU_COMMUNICATION_BTN].SubclassDlgItem(IDC_STATIC_COMMUNICATION_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_COMMUNICATION_BTN].SetBackgroundColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_COMMUNICATION_BTN].SetParaChangeColor(RGB(150, 150, 150));
	m_stc_btnMainMenu[MAIN_MENU_COMMUNICATION_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_COMMUNICATION_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_COMMUNICATION_BTN].SetData(_T("Communication"));
	m_stc_btnMainMenu[MAIN_MENU_COMMUNICATION_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_COMMUNICATION_BTN].SetForegroundWindow();
	
	//Measurement Button
	m_stc_btnMainMenu[MAIN_MENU_MEASUREMENT_BTN].SubclassDlgItem(IDC_STATIC_MEASUREMENT_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_MEASUREMENT_BTN].SetBackgroundColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_MEASUREMENT_BTN].SetParaChangeColor(RGB(150, 150, 150));
	m_stc_btnMainMenu[MAIN_MENU_MEASUREMENT_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_MEASUREMENT_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_MEASUREMENT_BTN].SetData(_T("Measurement"));
	m_stc_btnMainMenu[MAIN_MENU_MEASUREMENT_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_MEASUREMENT_BTN].SetForegroundWindow();

	//System Button
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SubclassDlgItem(IDC_STATIC_SYSTEM_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SetBackgroundColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SetParaChangeColor(RGB(150, 150, 150));
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SetForegroundWindow();
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SetData(_T("System"));
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_SYSTME_BTN].SetForegroundWindow();

	//Ready Button
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SubclassDlgItem(IDC_STATIC_READY_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SetParaOriginColor(RGB(0, 70, 0));
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SetParaChangeColor(RGB(0, 100, 0));
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SetBackgroundColor(RGB(0, 70, 0));
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SetData(_T("Ready"));
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_READY_BTN].SetForegroundWindow();

	//Auto Run Button
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SubclassDlgItem(IDC_STATIC_AUTO_RUN_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SetParaOriginColor(RGB(0, 0, 70));
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SetParaChangeColor(RGB(0, 0, 140));
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SetForegroundWindow();
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SetData(_T("Auto Run")); 
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_AUTO_RUN_BTN].SetBackgroundColor(RGB(0, 0, 70));

	//ECS Button
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SubclassDlgItem(IDC_STATIC_ECS_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SetParaOriginColor(RGB(230, 128, 0));
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SetParaChangeColor(RGB(250, 128, 0));
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SetBackgroundColor(RGB(230, 128, 0));
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SetTextColor(RGB(0, 0, 0));
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SetData(_T("Door On/Off"));
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_ECS_BTN].SetForegroundWindow();

	//Stop Button
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SubclassDlgItem(IDC_STATIC_STOP_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SetParaOriginColor(RGB(230, 0, 0));
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SetParaChangeColor(RGB(250, 0, 0));
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SetBackgroundColor(RGB(230, 0, 0));
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SetData(_T("Stop"));
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_STOP_BTN].SetForegroundWindow();

	//Screen Saver Button
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SubclassDlgItem(IDC_STATIC_SCREEN_SAVER_BTN, this);
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SetParaOriginColor(RGB(128, 128, 0));
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SetParaChangeColor(RGB(158, 158, 0));
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SetBackgroundColor(RGB(128, 128, 0));
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SetData(_T("Screen Saver"));
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_SCREEN_SAVER_BTN].SetForegroundWindow();

	//20.09.17 SJC Alaram btn add
	m_stc_btnMainMenu[MAIN_MENU_ALARAM_BTN].SubclassDlgItem(IDC_STATIC_MAIN_ALARM, this);
	m_stc_btnMainMenu[MAIN_MENU_ALARAM_BTN].SetBackgroundColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_ALARAM_BTN].SetParaChangeColor(RGB(150, 150, 150));
	m_stc_btnMainMenu[MAIN_MENU_ALARAM_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_ALARAM_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_ALARAM_BTN].SetData(_T("Alaram"));
	m_stc_btnMainMenu[MAIN_MENU_ALARAM_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_ALARAM_BTN].SetForegroundWindow();

	//20.09.17 SJC reset btn add
	m_stc_btnMainMenu[MAIN_MENU_RESET_BTN].SubclassDlgItem(IDC_STATIC_MAIN_RESET, this);
	m_stc_btnMainMenu[MAIN_MENU_RESET_BTN].SetBackgroundColor(RGB(120, 120, 120));
	m_stc_btnMainMenu[MAIN_MENU_RESET_BTN].SetParaChangeColor(RGB(150, 150, 150));
	m_stc_btnMainMenu[MAIN_MENU_RESET_BTN].SetTextColor(RGB(200, 200, 200));
	m_stc_btnMainMenu[MAIN_MENU_RESET_BTN].SetFont(&m_fontMainMenu, TRUE);
	m_stc_btnMainMenu[MAIN_MENU_RESET_BTN].SetData(_T("Reset"));
	m_stc_btnMainMenu[MAIN_MENU_RESET_BTN].SetActButton(TRUE);
	m_stc_btnMainMenu[MAIN_MENU_RESET_BTN].SetForegroundWindow();
#pragma endregion

	m_stcStateBar_Name[STATE_MENU_AOI_CONNECT].ShowWindow(SW_HIDE);
	m_stcStateBar_Name[STATE_MENU_AOI_READY_STATE].ShowWindow(SW_HIDE);
	m_stcStateBar_Name[STATE_MENU_3D_INIT].ShowWindow(SW_HIDE);
	m_stcStateBar_Value[STATE_MENU_AOI_CONNECT].ShowWindow(SW_HIDE);
	m_stcStateBar_Value[STATE_MENU_AOI_READY_STATE].ShowWindow(SW_HIDE);
	m_stcStateBar_Value[STATE_MENU_3D_INIT].ShowWindow(SW_HIDE);

}
//---------------------------------------------------------------------
BOOL CVisionAgentDlg::PreTranslateMessage(MSG* pMsg)
{

	switch (pMsg->wParam)
	{
	case VK_RETURN:
			return TRUE;
				
	case VK_ESCAPE:
		return TRUE;
	}
		
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CVisionAgentDlg::StateDisplay()
{
	CString strTemp = _T("");
	INT nTemp = 0;
	BOOL bClamp = FALSE, bUnclamp = FALSE, bFwd = FALSE, bBwd = FALSE;

	if (m_ePrevCamViewMode != SharedInfo::eCamViewMode)
	{
		ChangeCamera(SharedInfo::eCamViewMode);

		if (SharedInfo::eCamViewMode == eCamView_6G)
		{
			m_radioCamView6G.SetCheck(TRUE);
			m_radioCamView8G.SetCheck(FALSE);
		}
		else if (SharedInfo::eCamViewMode == eCamView_8G)
		{

			m_radioCamView8G.SetCheck(TRUE);
			m_radioCamView6G.SetCheck(FALSE);
		}
	}
	m_ePrevCamViewMode = SharedInfo::eCamViewMode;

	//Model name
	//strTemp.Format(_T("%S"), SharedInfo::m_MachineRecipeTable.strRecipeName[SharedInfo::Active.nActiveRecipeNum]);
	//m_stcStateBar_Value[STATE_MENU_MODEL_NAME].SetData(strTemp);


#pragma region //Laser Focus Value
#ifndef SIM_MODE
	if (m_pLaserDisp)
		strTemp.Format(_T("%.4f"), m_pLaserDisp->GetData());
#endif
	double dValue = _ttof(strTemp);
	if (m_dPrevLaserFocusValue != dValue)
	{
		if (dValue == 0.0)
		{
			m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetWindowText(_T("OFF"));
			m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetBackgroundColor(RGB(200, 0, 0));
			m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetTextColor(WHITE);
		}
		else
		{
			m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetWindowText(strTemp);
			m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetBackgroundColor(RGB(0, 200, 0));
			m_stcStateBar_Value[STATE_MENU_LASER_FOCUS].SetTextColor(BLACK);
		}
	}
	m_dPrevLaserFocusValue = dValue;
#pragma endregion

#pragma region //Clamp
	bClamp = Devs::m_ClampMotion.Is_ClampOn_Active();
	bUnclamp = Devs::m_ClampMotion.Is_ClampOff_Active();
	if (m_nPrevClampState != 1 && !bClamp && !bUnclamp)
	{
		m_nPrevClampState = 1;
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetData(_T(""));
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetTextColor(STATEBAR_VALUE_RGB);
	}
	else if (m_nPrevClampState != 2 && bClamp)
	{
		m_nPrevClampState = 2;
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetData(_T("Clamp"));
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetBackgroundColor(RGB(0, 200, 0));
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetTextColor(BLACK);
	}
	else if (m_nPrevClampState != 3 && bUnclamp)
	{
		m_nPrevClampState = 3;
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetData(_T("Unclamp"));
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetBackgroundColor(RGB(0, 200, 0));
		m_stcStateBar_Value[STATE_MENU_CLAMP].SetTextColor(BLACK);
	}
#pragma endregion

#pragma region //Stretch
	bFwd = Devs::m_StretchMotion.Is_Stretch_FwdPos_Active();
	bBwd = Devs::m_StretchMotion.Is_Stretch_BwdPos_Active();
	if (m_nPrevStretchState != 1 && !bFwd && !bBwd)
	{
		m_nPrevStretchState = 1;
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetData(_T(""));
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetBackgroundColor(STATEBAR_VALUE_BK_RGB);
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetTextColor(STATEBAR_VALUE_RGB);
	}
	else if (m_nPrevStretchState != 2 && bFwd)
	{
		m_nPrevStretchState = 2;
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetData(_T("Fwd"));
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetBackgroundColor(RGB(0, 200, 0));
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetTextColor(BLACK);
	}
	else if (m_nPrevStretchState != 3 && bBwd)
	{
		m_nPrevStretchState = 3;
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetData(_T("Bwd"));
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetBackgroundColor(RGB(0, 200, 0));
		m_stcStateBar_Value[STATE_MENU_STRETCHER].SetTextColor(BLACK);
	}
#pragma endregion

	strTemp.Format(_T("%.2f"), g_CommTempTur.m_dTempValue[MAIN_TEMPERATURE_NO]);
	m_stcStateBar_Value[STATE_MENU_MAIN_TEMPER].SetWindowText(strTemp);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::AlarmDisplay()
{
	if (SharedInfo::GetAlarm())
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(200, 0, 0));
		m_stcAutoRunDisp.SetData(_T("ALARM"));
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 10)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN"));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 20)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN."));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 30)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN.."));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 40)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN..."));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 50)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN...."));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 60)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN....."));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 70)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN......"));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 80)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN......."));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 90)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN........"));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt <= 100)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN........."));
		m_nAutoCnt++;
	}
	else if ((SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag) && m_nAutoCnt > 100)
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(0, 150, 0));
		m_stcAutoRunDisp.SetData(_T("RUN"));
		m_nAutoCnt = 0;
	}
	else
	{
		m_stcAutoRunDisp.SetBackgroundColor(RGB(45, 45, 45));
		m_stcAutoRunDisp.SetData(_T("STOP"));
	}
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnTimer(UINT_PTR nIDEvent)
{	
	CString strTemp = _T("");
	
	if (!m_bEntry)
	{
		m_bEntry = TRUE;
		Devs::m_bEntry = TRUE;
	}
	//Work Mode
	if (nIDEvent == 1)
	{
		//-----------------------------------------------------------------------------------------------
		//Alarm State
		Devs::MachineStateCheck();
		AlarmDisplay();
		StateDisplay();
		LogInUserID();
	}
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetSafeHwnd() == NULL)
		return;

	if (GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LT)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RT)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RB)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LB)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LT)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RT)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RB)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LB)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_RDO_CAMERA_VIEW_6G)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_RDO_CAMERA_VIEW_8G)->GetSafeHwnd() == NULL) return;
	//if (m_VisionAgentSimulationViewDlg.GetSafeHwnd() == NULL) return;

	//if (GetDlgItem(IDC_STATIC_MEASUREMENT_BTN)->GetSafeHwnd() == NULL) return;
	//if (GetDlgItem(IDC_STATIC_LOG_SUB)->GetSafeHwnd() == NULL) return;

	//------------------------------------------------------------------------------------------------------
	//Dialog Size 지정.
	
	CRect MonitorRect;
	CRect CustomerTitleRect;
	CRect HansongTitleRect;
	CRect StateBarNameRect;
	CRect StateBarValueRect;
	CRect MainBtnRect;
	CRect SubWndChkBtnRect;
	CRect Rect[2], CemeraRect[6], LogRect, MachineRect;
	CRect AutoRunDisplayRect;
	CRect QuickDataListRect;

	CRect Log_NamingRect;
	//CRect FlowStateRect[6];

	GetClientRect(&MonitorRect);

	//Main State Display Rect -------------------------------------------------------------
	CustomerTitleRect.top = 0;
	CustomerTitleRect.bottom = MonitorRect.Height() / 20;
	CustomerTitleRect.left = 1;
	CustomerTitleRect.right = MonitorRect.Width() / 14;
	
	HansongTitleRect.top = 0;
	HansongTitleRect.bottom = MonitorRect.Height() / 20;
	HansongTitleRect.right = MonitorRect.right - 1;
	HansongTitleRect.left = MonitorRect.Width() * 10 / 11;


	m_stcMainTitle.MoveWindow(CustomerTitleRect);
	m_stcHansongTitle.MoveWindow(HansongTitleRect);
	
	LONG lSizeX = ((HansongTitleRect.left - CustomerTitleRect.right) - ((MAX_STATE_MENU_STC - 3) * RESOURCE_SPACE)) / (MAX_STATE_MENU_STC - 3);
	LONG lSizeY = CustomerTitleRect.Height() / 2.2;

	//Auto Run Display -----------------------------------------------------------------------------
	AutoRunDisplayRect.top = HansongTitleRect.bottom + 1;
	AutoRunDisplayRect.bottom = AutoRunDisplayRect.top + lSizeY * 2;
	AutoRunDisplayRect.right = HansongTitleRect.right;
	AutoRunDisplayRect.left = HansongTitleRect.left;

	m_stcAutoRunDisp.MoveWindow(AutoRunDisplayRect);

	StateBarNameRect.top = 0;
	StateBarNameRect.bottom = lSizeY;
	StateBarNameRect.left = CustomerTitleRect.right + RESOURCE_SPACE;
	StateBarNameRect.right = StateBarNameRect.left + lSizeX;

	StateBarValueRect.top = StateBarNameRect.bottom + RESOURCE_SPACE;
	StateBarValueRect.bottom = StateBarValueRect.top + lSizeY;
	StateBarValueRect.left = CustomerTitleRect.right + RESOURCE_SPACE;
	StateBarValueRect.right = StateBarValueRect.left + lSizeX;

	m_stcStateBar_Name[STATE_MENU_USER_MODE].MoveWindow(StateBarNameRect);
	m_stcStateBar_Value[STATE_MENU_USER_MODE].MoveWindow(StateBarValueRect);

	for (int i = STATE_MENU_MODEL_NAME; i < MAX_STATE_MENU_STC; i++)
	{
		if (i == STATE_MENU_AOI_CONNECT || i == STATE_MENU_AOI_READY_STATE || i == STATE_MENU_3D_INIT)
		{
			continue;
		}
		else if (i == STATE_MENU_MAIN_TEMPER)
		{
			StateBarNameRect.left += lSizeX + RESOURCE_SPACE;
			StateBarNameRect.right = HansongTitleRect.left - RESOURCE_SPACE;

			StateBarValueRect.left += lSizeX + RESOURCE_SPACE;
			StateBarValueRect.right = HansongTitleRect.left - RESOURCE_SPACE;
		}
		else
		{
			StateBarNameRect.left += lSizeX + RESOURCE_SPACE;
			StateBarNameRect.right += lSizeX + RESOURCE_SPACE;

			StateBarValueRect.left += lSizeX + RESOURCE_SPACE;
			StateBarValueRect.right += lSizeX + RESOURCE_SPACE;
		}

		m_stcStateBar_Name[i].MoveWindow(StateBarNameRect);
		m_stcStateBar_Value[i].MoveWindow(StateBarValueRect);
	}

	/*
	int WholeSizeY = (MonitorRect.bottom - CustomerTitleRect.bottom - RESOURCE_SPACE * 77) / 2;
	int WholeSizeX = WholeSizeY * 1600 / 1200;
	*/
	CRect Review10X_NamingRect;
	CRect rectCam6G_LT, rectCam6G_RT, rectCam6G_LB, rectCam6G_RB;
	CRect rectCam8G_LT, rectCam8G_RT, rectCam8G_LB, rectCam8G_RB;
	CRect rectCamSelect_6G, rectCamSelect_8G;
	CRect SimulationViewRect;
	int	nCamDisp_Size_X, nCamDisp_Size_Y;
	int	nNaming_Start_X, nNaming_Start_Y;
	int	nNaming_Size_Y = 30;
	int nRidioCamSelectSizeX, nRidioCamSelectSizeY;
	nRidioCamSelectSizeX = 100;
	nRidioCamSelectSizeY = nNaming_Size_Y;
	
	nCamDisp_Size_X = (HansongTitleRect.left - MonitorRect.left) - (RESOURCE_SPACE * 3);
	nCamDisp_Size_X = nCamDisp_Size_X * 0.44;
	nCamDisp_Size_Y = (MonitorRect.bottom - HansongTitleRect.bottom - (nNaming_Size_Y * 2)) * 0.6 - 10;
	nNaming_Start_X = MonitorRect.left + RESOURCE_SPACE;
	nNaming_Start_Y = HansongTitleRect.bottom + RESOURCE_SPACE;

	//Review10X Nameing & Camera
	Review10X_NamingRect.left = nNaming_Start_X + RESOURCE_SPACE;
	Review10X_NamingRect.right = Review10X_NamingRect.left + (nCamDisp_Size_X) + RESOURCE_SPACE - 100;
	Review10X_NamingRect.top = nNaming_Start_Y;// +RESOURCE_SPACE;
	Review10X_NamingRect.bottom = Review10X_NamingRect.top + nNaming_Size_Y;
	m_stcCameraViewMode_Naming.MoveWindow(Review10X_NamingRect);

	//6G LT
	rectCam6G_LT.left = Review10X_NamingRect.left;
	rectCam6G_LT.right = (Review10X_NamingRect.right - Review10X_NamingRect.left) / 2 - RESOURCE_SPACE;
	rectCam6G_LT.top = Review10X_NamingRect.bottom + RESOURCE_SPACE;
	rectCam6G_LT.bottom = rectCam6G_LT.top + ((Review10X_NamingRect.right - Review10X_NamingRect.left) / 2 * CAM_BUF_SIZE_Y_5M / CAM_BUF_SIZE_X_5M);
	GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LT)->MoveWindow(rectCam6G_LT);

	//6G RT
	rectCam6G_RT.left = rectCam6G_LT.right + RESOURCE_SPACE;
	rectCam6G_RT.right = Review10X_NamingRect.right;
	rectCam6G_RT.top = rectCam6G_LT.top;
	rectCam6G_RT.bottom = rectCam6G_LT.bottom;
	GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RT)->MoveWindow(rectCam6G_RT);

	//6G LB
	rectCam6G_LB.left	= rectCam6G_LT.left;
	rectCam6G_LB.right = rectCam6G_LT.right;
	rectCam6G_LB.top = rectCam6G_LT.bottom + RESOURCE_SPACE;
	rectCam6G_LB.bottom = rectCam6G_LB.top + (rectCam6G_LT.bottom - rectCam6G_LT.top);
	GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LB)->MoveWindow(rectCam6G_LB);

	//6G RB
	rectCam6G_RB.left = rectCam6G_RT.left;
	rectCam6G_RB.right = rectCam6G_RT.right;
	rectCam6G_RB.top = rectCam6G_LB.top;
	rectCam6G_RB.bottom = rectCam6G_LB.bottom;
	GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RB)->MoveWindow(rectCam6G_RB);
	
	//8G LT
	rectCam8G_LT.left = rectCam6G_LT.left;
	rectCam8G_LT.right = rectCam6G_LT.right;
	rectCam8G_LT.top = rectCam6G_LT.top;
	rectCam8G_LT.bottom = rectCam6G_LT.bottom;
	GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LT)->MoveWindow(rectCam8G_LT);

	//8G RT
	rectCam8G_RT.left = rectCam6G_RT.left;
	rectCam8G_RT.right = rectCam6G_RT.right;
	rectCam8G_RT.top = rectCam6G_RT.top;
	rectCam8G_RT.bottom = rectCam6G_RT.bottom;
	GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RT)->MoveWindow(rectCam8G_RT);

	//8G RB
	rectCam8G_RB.left = rectCam6G_RB.left;
	rectCam8G_RB.right = rectCam6G_RB.right;
	rectCam8G_RB.top = rectCam6G_RB.top;
	rectCam8G_RB.bottom = rectCam6G_RB.bottom;
	GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RB)->MoveWindow(rectCam8G_RB);

	//8G LB
	rectCam8G_LB.left = rectCam6G_LB.left;
	rectCam8G_LB.right = rectCam6G_LB.right;
	rectCam8G_LB.top = rectCam6G_LB.top;
	rectCam8G_LB.bottom = rectCam6G_LB.bottom;
	GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LB)->MoveWindow(rectCam8G_LB);

	//Cam Select 6G
	rectCamSelect_6G.left = rectCam6G_LB.left;
	rectCamSelect_6G.right = rectCamSelect_6G.left + 100;
	rectCamSelect_6G.top = rectCam6G_LB.bottom + RESOURCE_SPACE;
	rectCamSelect_6G.bottom = rectCamSelect_6G.top + 30;
	GetDlgItem(IDC_RDO_CAMERA_VIEW_6G)->MoveWindow(rectCamSelect_6G);

	//Cam Select 8G
	rectCamSelect_8G.left = rectCamSelect_6G.right + RESOURCE_SPACE;
	rectCamSelect_8G.right = rectCamSelect_8G.left + 100;
	rectCamSelect_8G.top = rectCamSelect_6G.top;
	rectCamSelect_8G.bottom = rectCamSelect_6G.bottom;
	GetDlgItem(IDC_RDO_CAMERA_VIEW_8G)->MoveWindow(rectCamSelect_8G);


	//Simulation View
	SimulationViewRect.left = rectCam6G_RT.right + RESOURCE_SPACE;
	SimulationViewRect.right = HansongTitleRect.left - RESOURCE_SPACE; // SimulationViewRect.left + Review10X_NamingRect.Width();
	SimulationViewRect.top = Review10X_NamingRect.top + 25; //Review10X_CamRect.top;//Review10X_NamingRect.top;
	SimulationViewRect.bottom = rectCam6G_RB.bottom;
	m_VisionAgentSimulationViewDlg.MoveWindow(SimulationViewRect);
	m_VisionAgentSimulationViewDlg.SetWindowPos(NULL, SimulationViewRect.left, SimulationViewRect.top, SimulationViewRect.right - SimulationViewRect.left, SimulationViewRect.bottom - SimulationViewRect.top, NULL);
	m_VisionAgentSimulationViewDlg.ShowWindow(SW_SHOW);

	//Sub Window Check Button -------------------------------------------------------------------------
	SubWndChkBtnRect.top = AutoRunDisplayRect.bottom;
	SubWndChkBtnRect.bottom = SubWndChkBtnRect.top + (lSizeY * 2);
	SubWndChkBtnRect.left = HansongTitleRect.left;
	SubWndChkBtnRect.right = HansongTitleRect.right;

	m_CheckProcessDlg.MoveWindow(SubWndChkBtnRect);

	//Awking
	MainBtnRect.top = SubWndChkBtnRect.bottom + lSizeY;
	MainBtnRect.bottom = MainBtnRect.top + (lSizeY * 2);
	MainBtnRect.left = HansongTitleRect.left;
	MainBtnRect.right = HansongTitleRect.right;

	m_stc_btnMainMenu[MAIN_MENU_MODEL_BTN].MoveWindow(MainBtnRect);

	for (int i = MAIN_MENU_MANUAL_BTN; i < MAIN_MENU_READY_BTN; i++)
	{
		MainBtnRect.top += (lSizeY * 2 + RESOURCE_SPACE);
		MainBtnRect.bottom += (lSizeY * 2 + RESOURCE_SPACE);
		m_stc_btnMainMenu[i].MoveWindow(MainBtnRect);
	}

	MainBtnRect.top += lSizeY; // (lSizeY * 2 + 30);
	MainBtnRect.bottom += lSizeY; // (lSizeY * 2 + 30);

	for (int i = MAIN_MENU_READY_BTN; i < MAX_MAIN_MENU_BTN; i++)
	{
		MainBtnRect.top += (lSizeY * 2 + RESOURCE_SPACE);
		MainBtnRect.bottom += (lSizeY * 2 + RESOURCE_SPACE);
		m_stc_btnMainMenu[i].MoveWindow(MainBtnRect);

		if (i == MAIN_MENU_STOP_BTN)
		{
			MainBtnRect.bottom = MonitorRect.bottom - RESOURCE_SPACE;
			MainBtnRect.top = MainBtnRect.bottom - lSizeY * 2;

			m_stc_btnMainMenu[i].MoveWindow(MainBtnRect);
		}
	}

	//--------------------------------------------------------------------------------------------
	//Naming_Log
	//20.09.17 sjc change 
	Log_NamingRect.left		= SimulationViewRect.left;
	Log_NamingRect.right	= SimulationViewRect.right;
	Log_NamingRect.top		= SimulationViewRect.bottom + RESOURCE_SPACE;
	Log_NamingRect.bottom	= Log_NamingRect.top + nNaming_Size_Y;
	m_stcLogNaming.MoveWindow(Log_NamingRect);

	LogRect.left	= Log_NamingRect.left;
	LogRect.right	= Log_NamingRect.right;
	LogRect.top		= Log_NamingRect.bottom + RESOURCE_SPACE;
	LogRect.bottom	= MonitorRect.bottom - nNaming_Size_Y - (RESOURCE_SPACE * 2);
	GetDlgItem(IDC_STATIC_LOG_SUB)->MoveWindow(LogRect);
	m_LogSize = LogRect;

	CRect	RectLogBtn;
	double	dLogBtn_Size_X = (LogRect.right - LogRect.left - (RESOURCE_SPACE * 6)) / MAX_LOG_LIST;//20.09.17 sjc 7->MAX_LOG_LIST
	RectLogBtn.left = LogRect.left;
	RectLogBtn.top = LogRect.bottom + RESOURCE_SPACE;
	RectLogBtn.right = RectLogBtn.left + dLogBtn_Size_X;
	RectLogBtn.bottom = MonitorRect.bottom - RESOURCE_SPACE;
	for (int k = 0; k < MAX_LOG_LIST; k++)
	{
		RectLogBtn.left = LogRect.left + (int)(dLogBtn_Size_X * k);
		RectLogBtn.right = RectLogBtn.left + dLogBtn_Size_X;
		m_btnLogSelect[k].MoveWindow(RectLogBtn);
	}
	RectLogBtn.right	= LogRect.right - RESOURCE_SPACE;
	RectLogBtn.left		= RectLogBtn.right - (int)(dLogBtn_Size_X);
	
	//m_btnLogViewer.MoveWindow(RectLogBtn);


	ShowLogDlg(0);
	Invalidate(false);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::InitSubDlg()
{
	m_pModelDlg = new CModelDlg(this);
	m_pModelDlg->ShowWindow(SW_HIDE);
	m_bShowModelModeless = FALSE;

	m_pManualDlg = new CManualDlg(this);
	m_pManualDlg->ShowWindow(SW_HIDE);
	m_bShowManualModeless = FALSE;

	m_pCommunicationDlg = new CCommunicationDlg(this);
	m_pCommunicationDlg->ShowWindow(SW_HIDE);
	m_bShowCommunicationModeless = FALSE;

	m_pSystemDlg = new CSystemDlg(this);
	m_pSystemDlg->ShowWindow(SW_HIDE);
	m_bShowSystemModeless = FALSE;

	m_pMeasurementDlg = new CMeasurementDlg(this);
	m_pMeasurementDlg->ShowWindow(SW_HIDE);
	m_bShowMeasurementModeless = FALSE;

	m_pMahcineDlg = new CMachineDlg(this);
	m_pMahcineDlg->ShowWindow(SW_HIDE);
	m_bShowMachineModeless = FALSE;

	m_pAlarmDlg = new CVisionAgentAlarmDlg(this);
	m_pAlarmDlg->ShowWindow(SW_HIDE);
	m_bShowAlarmModeless = FALSE;
	
	m_pProcessDlg = new CVisionAgentProcessDlg(this);
	m_pProcessDlg->ShowWindow(SW_HIDE);
	m_bShowProcessDlg = FALSE;

	//m_pECSDlg = new CVisionAgentECSDlg(this);
	//m_pECSDlg->ShowWindow(SW_HIDE);
	//m_bShowECSModeless = FALSE;

	m_pSafetyMapDlg = new CVisionAgentSafetyMap(this);
	m_pSafetyMapDlg->ShowWindow(SW_HIDE);
	m_bShowSafetyMapModeless = FALSE;

}
//-------------------------------------------------------------------
void	CVisionAgentDlg::Init_Log_Dlg()
{
	m_VisionAgentLogAllDlg = new CVisionAgentLogDlg(this, LOG_ALL);

	m_VisionAgentLogProcessDlg = new CVisionAgentLogDlg(this, LOG_PROCESS);

	m_VisionAgentLogVisionDlg = new CVisionAgentLogDlg(this, LOG_VISION);

	m_VisionAgentLogSystemDlg = new CVisionAgentLogDlg(this, LOG_SYSTEM);

	m_VisionAgentLogEtcDlg = new CVisionAgentLogDlg(this, LOG_ETC);

	m_VisionAgentLogAlarmDlg = new CVisionAgentLogDlg(this, LOG_ALARM);

	m_btnLogSelect[0].SubclassDlgItem(IDC_LOG_ALL, this);
	m_btnLogSelect[1].SubclassDlgItem(IDC_LOG_PROCESS, this);
	m_btnLogSelect[2].SubclassDlgItem(IDC_LOG_SYSTEM, this);
	m_btnLogSelect[3].SubclassDlgItem(IDC_LOG_VISION, this);
	m_btnLogSelect[4].SubclassDlgItem(IDC_LOG_ETC, this);
	m_btnLogSelect[5].SubclassDlgItem(IDC_LOG_ALARM, this);
	for (int k = 0; k < 6; k++)
	{
		m_btnLogSelect[k].SetBackgroundColor(RGB(170, 170, 170));
		m_btnLogSelect[k].SetTextColor(RGB(255, 255, 255));
		m_btnLogSelect[k].SetFont(&m_fontMainMenu, TRUE);
	}	
	
}
//-------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticModelBtn()
{
	m_bShowModelModeless = !m_bShowModelModeless;
	m_pModelDlg->RecalcLayout();
	m_pModelDlg->ShowWindow(m_bShowModelModeless);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticCommunicationBtn()
{
	m_bShowCommunicationModeless = !m_bShowCommunicationModeless;
//	m_pCommunicationDlg->RecalcLayout();
	m_pCommunicationDlg->ShowWindow(m_bShowCommunicationModeless);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticManualBtn()
{
	m_bShowManualModeless = !m_bShowManualModeless;
	m_pManualDlg->RecalcLayout();
	m_pManualDlg->ShowWindow(m_bShowManualModeless);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticSystemBtn()
{
	m_bShowSystemModeless = !m_bShowSystemModeless;
	m_pSystemDlg->RecalcLayout();
	m_pSystemDlg->ShowWindow(m_bShowSystemModeless);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticMachineBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bShowMachineModeless = !m_bShowMachineModeless;
	m_pMahcineDlg->RecalcLayout();
	m_pMahcineDlg->ShowWindow(m_bShowMachineModeless);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticHansongTitle()
{
	AfxMessageBox(_T("Test"));
}
//---------------------------------------------------------------------
//void CVisionAgentDlg::OnStnClickedStaticMainTitle()
//{ 
//#if 0
//	Devs::m_Pua310->OpenControlWindow();
//#endif
//}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticMeasurementBtn()
{
	m_bShowMeasurementModeless = !m_bShowMeasurementModeless;
	m_pMeasurementDlg->RecalcLayout();
	m_pMeasurementDlg->ShowWindow(m_bShowMeasurementModeless);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticAutoRunDisplay()
{
	//SharedInfo::ResetAlarm();
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnDblclickStaticAutoRunDisplay()
{
	if (SharedInfo::GetAlarm())
	{
		SharedInfo::ResetAlarm();
	}
}
//---------------------------------------------------------------------
void CVisionAgentDlg::LogInUserID()
{
#if 0
	CString  strTemp = _T("");
	strTemp = Devs::m_Pua310->GetUserId();

	//Awking Log
	if (m_strOldTemp!= strTemp)
	{
		if (strTemp==_T(""))
		{
			m_strOldTemp = strTemp;
		}
		else
		{
			m_strOldTemp = strTemp;		
		}
	}
#endif
}

BOOL CVisionAgentDlg::DestroyWindow()
{
	KillTimer(1);

	if (m_pModelDlg != NULL)
	{
		m_pModelDlg->DestroyWindow();
		delete m_pModelDlg;
	}

	if (m_pManualDlg != NULL)
	{
		m_pManualDlg->DestroyWindow();
		delete m_pManualDlg;
	}

	if (m_pSystemDlg != NULL)
	{
		m_pSystemDlg->DestroyWindow();
		delete m_pSystemDlg;
	}

	if (m_pMeasurementDlg != NULL)
	{
		m_pMeasurementDlg->DestroyWindow();
		delete m_pMeasurementDlg;
	}

	if (m_pCommunicationDlg != NULL)
	{
		m_pCommunicationDlg->DestroyWindow();
		delete m_pCommunicationDlg;
	}

	if (m_pMahcineDlg != NULL)
	{
		m_pMahcineDlg->DestroyWindow();
		delete m_pMahcineDlg;
	}

	if (m_pAlarmDlg)
	{
		m_pAlarmDlg->DestroyWindow();
		delete m_pAlarmDlg;
	}

	if (m_pProcessDlg)
	{
		m_pProcessDlg->DestroyWindow();
		delete m_pProcessDlg;
	}

	//if (m_pECSDlg)
	//{
	//	m_pECSDlg->DestroyWindow();
	//	delete m_pECSDlg;
	//}

	if (m_VisionAgentLogAllDlg)
	{
		m_VisionAgentLogAllDlg->DestroyWindow();
		delete m_VisionAgentLogAllDlg;
	}

	if (m_VisionAgentLogProcessDlg)
	{
		m_VisionAgentLogProcessDlg->DestroyWindow();
		delete m_VisionAgentLogProcessDlg;
	}

	if (m_VisionAgentLogVisionDlg)
	{
		m_VisionAgentLogVisionDlg->DestroyWindow();
		delete m_VisionAgentLogVisionDlg;
	}

	if (m_VisionAgentLogSystemDlg)
	{
		m_VisionAgentLogSystemDlg->DestroyWindow();
		delete m_VisionAgentLogSystemDlg;
	}

	if (m_VisionAgentLogEtcDlg)
	{
		m_VisionAgentLogEtcDlg->DestroyWindow();
		delete m_VisionAgentLogEtcDlg;
	}

	if (m_VisionAgentLogAlarmDlg)
	{
		m_VisionAgentLogAlarmDlg->DestroyWindow();
		delete m_VisionAgentLogAlarmDlg;
	}

	m_VisionAgentSimulationViewDlg.DestroyWindow();
	//CimInfo::Finalize();
	SharedInfo::Finalize();
	//Devs::Finalize();	
	Devs::m_JogMotion.StopAll();

#ifndef MIL_NOT_USE
	if (Devs::m_Camera6G_LT != NULL)
		delete Devs::m_Camera6G_LT;
	if (Devs::m_Camera6G_RT != NULL)
		delete Devs::m_Camera6G_RT;
	if (Devs::m_Camera6G_RB != NULL)
		delete Devs::m_Camera6G_RB;
	if (Devs::m_Camera6G_LB != NULL)
		delete Devs::m_Camera6G_LB;

	if (Devs::m_Camera8G_LT != NULL)
		delete Devs::m_Camera8G_LT;
	if (Devs::m_Camera8G_RT != NULL)
		delete Devs::m_Camera8G_RT;
	if (Devs::m_Camera8G_RB != NULL)
		delete Devs::m_Camera8G_RB;
	if (Devs::m_Camera8G_LB != NULL)
		delete Devs::m_Camera8G_LB;

	//if (Devs::m_Camera10X != NULL)
	//	delete Devs::m_Camera10X;

	MdispFree(Devs::MilDigCam6G_LT);
	MdispFree(Devs::MilDigCam6G_RT);
	MdispFree(Devs::MilDigCam6G_RB);
	MdispFree(Devs::MilDigCam6G_LB);

	MdispFree(Devs::MilDigCam8G_LT);
	MdispFree(Devs::MilDigCam8G_RT);
	MdispFree(Devs::MilDigCam8G_RB);
	MdispFree(Devs::MilDigCam8G_LB);

	//MdispFree(Devs::MilDigReview10X);

	MsysFree(Devs::MilSysSol0);
	MsysFree(Devs::MilSysSol1);
	MsysFree(Devs::MilSysSol2);

	MappFree(Devs::MilApplication);
#endif

	CLogDefine::Finalize();

	return CDialogEx::DestroyWindow();
}
//---------------------------------------------------------------------
//동작 버튼------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticReadyBtn()
{
	//if (IDYES == AfxMessageBox(_T("Ready Flow Start ?"), MB_YESNO))
	//{
	//	Devs::m_ReadyFlow.Start();
	//}
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticAutoRunBtn()
{
	//21.02.26 sjc temp del
	if (SharedInfo::GetAlarm())
	{
		AfxMessageBox(_T("MachineState ERROR !!!"));
	}
	if (SharedInfo::bMachineStopFlag == FALSE)
	{
		AfxMessageBox(_T("bMachineStopFlag FALSE !!"));
		return;
	}
	if (!SharedInfo::bRemoteAjinSystemReadyStatus)
	{
		AfxMessageBox(_T("bRemoteAjinSystemReadyStatus FALSE !!"));
		return;
	}
	if (!SharedInfo::bRemoteUmacSystemReadyStatus)
	{
		AfxMessageBox(_T("bRemoteUmacSystemReadyStatus FALSE !!"));
		return;
	}
	if (!SharedInfo::bDirectAjinSystemReadyStatus)
	{
		AfxMessageBox(_T("bDirectAjinSystemReadyStatus FALSE !!"));
		return;
	}

	CAutoRunStartDlg AutoRunStartDlg;

	AutoRunStartDlg.DoModal();
	if (AutoRunStartDlg.m_OKFlag == TRUE)
	{
		//Devs::m_AutoRunFlow.Start();
	}
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedStaticStopBtn()
{
	Devs::m_JogMotion.StopAll();

	Total_Msg(_T("[MAIN] Stop Button Click"));
}
void CVisionAgentDlg::OnStnClickedLogAll()
{
	ShowLogDlg(LOG_ALL);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedLogProcess()
{
	ShowLogDlg(LOG_PROCESS);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedLogSystem()
{
	ShowLogDlg(LOG_SYSTEM);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedLogVision()
{
	ShowLogDlg(LOG_VISION);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedLogEtc()
{
	ShowLogDlg(LOG_ETC);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedLogAlarm()
{
	ShowLogDlg(LOG_ALARM);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnStnClickedLogViewer()
{
}
//---------------------------------------------------------------------
void	CVisionAgentDlg::ShowLogDlg(int nDlgNo)
{
	int i;

	m_VisionAgentLogAllDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogProcessDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogVisionDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogSystemDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogEtcDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogAlarmDlg->ShowWindow(SW_HIDE);

	for (int i = 0; i < MAX_LOG_LIST; i++)
	{
		m_btnLogSelect[i].SetBackgroundColor(RGB(170, 170, 170));
	}

	m_nCurLogDlg = nDlgNo;

	switch (m_nCurLogDlg)
	{
	case LOG_ALL:
	{
		m_pCurLogDlg = m_VisionAgentLogAllDlg;

		m_btnLogSelect[LOG_ALL].SetBackgroundColor(RGB(0xff, 0x66, 0));
		break;
	}
	case LOG_PROCESS:
	{
		m_pCurLogDlg = m_VisionAgentLogProcessDlg;

		m_btnLogSelect[LOG_PROCESS].SetBackgroundColor(RGB(0xff, 0x66, 0));
		break;
	}
	case LOG_VISION:
	{
		m_pCurLogDlg = m_VisionAgentLogVisionDlg;

		m_btnLogSelect[LOG_VISION].SetBackgroundColor(RGB(0xff, 0x66, 0));
		break;
	}
	case LOG_SYSTEM:
	{
		m_pCurLogDlg = m_VisionAgentLogSystemDlg;

		m_btnLogSelect[LOG_SYSTEM].SetBackgroundColor(RGB(0xff, 0x66, 0));
		break;
	}
	case LOG_ETC:
	{
		m_pCurLogDlg = m_VisionAgentLogEtcDlg;

		m_btnLogSelect[LOG_ETC].SetBackgroundColor(RGB(0xff, 0x66, 0));
		break;
	}
	case LOG_ALARM:
	{
		m_pCurLogDlg = m_VisionAgentLogAlarmDlg;
		m_btnLogSelect[LOG_ALARM].SetBackgroundColor(RGB(0xff, 0x66, 0));

		break;
	}
	}
	m_pCurLogDlg->MoveWindow(&m_LogSize);
	m_pCurLogDlg->ShowWindow(SW_SHOW);
}
//---------------------------------------------------------------------
void	CVisionAgentDlg::HideLogDlg()
{
	m_VisionAgentLogAllDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogProcessDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogVisionDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogSystemDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogEtcDlg->ShowWindow(SW_HIDE);
	m_VisionAgentLogAlarmDlg->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------
void CVisionAgentDlg::OnBnClickedCheckShowProcessSub()
{
	m_bShowProcessDlg = !m_bShowProcessDlg;

	if (m_bShowProcessDlg)
	{	
		m_pProcessDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pProcessDlg->ShowWindow(SW_HIDE);
	}	
}
//---------------------------------------------------------------------
UINT Status_Ajin_Thread_Proc(LPVOID lpParam)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg*)lpParam;
	while (1)
	{
		Sleep(1);
	}
	return 0;
}
//---------------------------------------------------------------------
UINT Safety_Thread_Proc(LPVOID lpParam)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg*)lpParam;
	while (1)
	{
		Sleep(1);
	}
	return 0;
}
//---------------------------------------------------------------------
UINT Data_Thread_Proc(LPVOID lpParam)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg*)lpParam;
	while (1)
	{
		Sleep(1);
	}
	return 0;
}
//---------------------------------------------------------------------

void CVisionAgentDlg::OnBnClickedRdoCamView6g()
{
	SharedInfo::eCamViewMode = eCamView_6G;
}


void CVisionAgentDlg::OnBnClickedRdoCamView8g()
{
	SharedInfo::eCamViewMode = eCamView_8G;
}

void CVisionAgentDlg::ChangeCamera(int nCamNo)
{
	switch (nCamNo)
	{
	case eCamView_6G:
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LB)->ShowWindow(SW_SHOW);		

		m_stcCameraViewMode_Naming.SetData(_T("6G"));
		break;
	
	case eCamView_8G:
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_RB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_6G_CAM_LB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_RB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMERA_DISPALY_8G_CAM_LB)->ShowWindow(SW_SHOW);

		m_stcCameraViewMode_Naming.SetData(_T("8G"));
		break;
	}
}

int CVisionAgentDlg::GetBoardInfo()
{
	long lAxisCount;
	int nDInputIndex = 0;
	int nDOutputIndex = 0;
	int nAInputIndex = 0;
	int nAOutputIndex = 0;
	CString Str;

	m_nVisionMaxAxisSize = 0;

	//Motion
	AxmInfoGetAxisCount(&lAxisCount);
	m_nVisionMaxAxisSize = lAxisCount;

	Str.Format(_T("Motion Axis Size = %d"), m_nVisionMaxAxisSize);
	Etc_Msg(Str);

	return 1;
}


int CVisionAgentDlg::GetMotionPara()
{
	DWORD dwRet;
	CString file;

	file.Format(_T("%s\\Data\\Ajin\\%s"), SharedInfo::GetExeFilePath(), _T("AjinPara.mot"));

	USES_CONVERSION;
	char * szfile = T2A(file);

	//dwRet = AxmMotLoadParaAll((char *)_ToMbc(file));	
	dwRet = AxmMotLoadParaAll(szfile);

	if (dwRet == 0)
	{
		Etc_Msg(_T("Loading Motion Para Success"));
	}
	else
	{
		Etc_Msg(_T("Loading Motion Para Fail"));
	}

	return dwRet;
}
BOOL CVisionAgentDlg::ConnectWorkNetwork()
{
	CString strServerIP, strServerPort, str, strStatePort, strVisionReceivePort, strVisionWritePort, strBarCodeIP, strBarCodePort;
	strServerPort.Format(_T("2000"));
	strStatePort.Format(_T("2001"));
	strVisionWritePort.Format(_T("2002"));
	strVisionReceivePort.Format(_T("2003"));

	strServerIP.Format(_T("192.168.1.101"));

	//strServerIP.Format(_T("127.0.0.1"));

	//Awking 14_Test.
	//strServerIP.Format(_T("192.168.0.159"));

	WSADATA WSAData = { 0 };
	if (0 != WSAStartup(WSA_VERSION, &WSAData)) {
		if (LOBYTE(WSAData.wVersion) != LOBYTE(WSA_VERSION) || HIBYTE(WSAData.wVersion) != HIBYTE(WSA_VERSION)) {
			AfxMessageBox(_T("Incorrect version of WS2_32.dll found"));
		}
		WSACleanup();
	}
	m_SocketWrite.SetServerState(FALSE);
	m_SocketWrite.SetSmartAddressing(FALSE);

	m_nPrevConnect = 0;
	m_nConnect = 0;
	m_nConnect = m_SocketWrite.ConnectTo(strServerIP, strServerPort, AF_INET, SOCK_STREAM);
	if (m_nConnect && m_SocketWrite.WatchComm()) {
		m_SocketWrite.GetPeerName(m_SockPeer);

		//SetProcessMsg(_T("Network(127.0.0.1) connected"));
		Etc_Msg(_T("Network(192.168.0.1) connected"));
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetBackgroundColor(DKGREEN);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetTextColor(WHITE);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetWindowText(_T("On"));

	}
	else
	{
		//SetProcessMsg(_T("Network(127.0.0.1) connection fail"));
		Etc_Msg(_T("Network(192.168.0.1) connection fail"));
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetBackgroundColor(DKRED);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetTextColor(YELLOW);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetWindowText(_T("OFF"));


		m_bConnectWorkNetwork = FALSE;
		//CStateManager* pStateMan = CStateManager::GetInstance();
		//pStateMan->SetEvent();

	}

	//Control Receive
	m_nStateConnect = 0;
	m_nStateConnect = m_SocketReceive.ConnectTo(strServerIP, strStatePort, AF_INET, SOCK_STREAM);
	if (m_nStateConnect && m_SocketReceive.WatchComm()) {
		m_SocketReceive.GetPeerName(m_SockPeer);

		//SetProcessMsg(_T("Network(127.0.0.1) connected"));
		Etc_Msg(_T("State Network(192.168.0.1) connected"));
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetBackgroundColor(DKGREEN);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetTextColor(WHITE);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetWindowText(_T("On"));

	}
	else
	{
		//SetProcessMsg(_T("Network(127.0.0.1) connection fail"));
		Etc_Msg(_T("State Network(192.168.0.1) connection fail"));
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetBackgroundColor(DKRED);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetTextColor(YELLOW);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetWindowText(_T("OFF"));


		m_bStateConnectWorkNetwork = FALSE;
		//CStateManager* pStateMan = CStateManager::GetInstance();
		//pStateMan->SetEvent();

	}
#if 0
#ifndef SIM_MODE
#pragma region //Barcode
	
	Devs::m_SocketLoaderBarCode.SetServerState(FALSE);
	Devs::m_SocketLoaderBarCode.SetSmartAddressing(FALSE);

	Devs::m_SocketLoaderBarCode.SetServerState(FALSE);
	Devs::m_SocketLoaderBarCode.SetSmartAddressing(FALSE);
	strBarCodePort.Format(_T("9004"));
	//21.02.08 sjc 192.168.1.201 -> 192.168.111.2
	strBarCodeIP.Format(_T("192.168.100.100"));
	m_nLoaderBarCodeConnect = 0;
	m_nLoaderBarCodeConnect = Devs::m_SocketLoaderBarCode.ConnectTo(strBarCodeIP, strBarCodePort, AF_INET, SOCK_STREAM);
	if (m_nLoaderBarCodeConnect && Devs::m_SocketLoaderBarCode.WatchComm()) {
		Devs::m_SocketLoaderBarCode.GetPeerName(m_SockPeer);

		m_nLoaderBarCodeConnect = 1;
		//Devs::m_SocketLoaderBarCode.bBarCodeFlag = true;
		//SetProcessMsg(_T("Network(127.0.0.1) connected"));
		Etc_Msg(_T("Loader Barcode Network(192.168.100.100) connected"));
	}
	else
	{
		//SetProcessMsg(_T("Network(127.0.0.1) connection fail"));
		Etc_Msg(_T("Loader Barcode Network(192.168.100.100) connection fail"));
		//CStateManager* pStateMan = CStateManager::GetInstance();
		//pStateMan->SetEvent();
	}
	

#pragma endregion

	//Vision Receive

	m_nVisionConnect = 0;
	m_nVisionConnect = m_SocketVisionReceive.ConnectTo(strServerIP, strVisionReceivePort, AF_INET, SOCK_STREAM);
	if (m_nVisionConnect && m_SocketVisionReceive.WatchComm()) {
		m_SocketVisionReceive.GetPeerName(m_SockPeer);

		//m_nVisionConnect = 1;

		//SetProcessMsg(_T("Network(127.0.0.1) connected"));
		Etc_Msg(_T("Vision Network(192.168.1.101) connected"));
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetBackgroundColor(GREEN);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetTextColor(WHITE);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetWindowText(_T("On"));

	}
	else
	{
		//SetProcessMsg(_T("Network(127.0.0.1) connection fail"));
		Etc_Msg(_T("Vision Network(192.168.1.101) connection fail"));
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetBackgroundColor(RED);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetTextColor(YELLOW);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetWindowText(_T("OFF"));


		m_bStateConnectWorkNetwork = FALSE;
		//CStateManager* pStateMan = CStateManager::GetInstance();
		//pStateMan->SetEvent();

	}


	//Vision Write = 0;
	m_nVisionConnect = 0;
	m_nVisionConnect = m_SocketVisionWrite.ConnectTo(strServerIP, strVisionWritePort, AF_INET, SOCK_STREAM);
	if (m_nVisionConnect && m_SocketVisionWrite.WatchComm()) {
		m_SocketVisionWrite.GetPeerName(m_SockPeer);

		//SetProcessMsg(_T("Network(127.0.0.1) connected"));
		Etc_Msg(_T("Vision Network(192.168.1.101) connected"));
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetBackgroundColor(GREEN);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetTextColor(WHITE);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetWindowText(_T("On"));

	}
	else
	{
		//SetProcessMsg(_T("Network(127.0.0.1) connection fail"));
		Etc_Msg(_T("Vision Network(192.168.1.101) connection fail"));
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetBackgroundColor(RED);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetTextColor(YELLOW);
		//m_stcStateBar_Value[VISION_AGENT_STATE_MENU_NETWORK_STC].SetWindowText(_T("OFF"));


		m_bStateConnectWorkNetwork = FALSE;
		//CStateManager* pStateMan = CStateManager::GetInstance();
		//pStateMan->SetEvent();

	}

	strBarCodeIP.Format(_T("192.168.2.202"));
	m_nFrameBarcodeConnect = 0;
	m_nFrameBarcodeConnect = Devs::m_SocketFrameBarCode.ConnectTo(strBarCodeIP, strBarCodePort, AF_INET, SOCK_STREAM);
	if (m_nFrameBarcodeConnect && Devs::m_SocketFrameBarCode.WatchComm()) {
		Devs::m_SocketFrameBarCode.GetPeerName(m_SockPeer);
		//Devs::m_SocketFrameBarCode.bBarCodeFlag = true;
		m_nFrameBarcodeConnect = 1;

		//SetProcessMsg(_T("Network(127.0.0.1) connected"));
		Etc_Msg(_T("Frame Barcode Network(192.168.2.202) connected"));


	}
	else
	{
		//SetProcessMsg(_T("Network(127.0.0.1) connection fail"));
		Etc_Msg(_T("Frame Barcode Network(192.168.2.202) connection fail"));



		//CStateManager* pStateMan = CStateManager::GetInstance();
		//pStateMan->SetEvent();

	}


	strBarCodeIP.Format(_T("192.168.2.203"));
	m_nMaskBarcodeConnect = 0;
#if 0
	m_nMaskBarcodeConnect = Devs::m_SocketMaskBarCode.ConnectTo(strBarCodeIP, strBarCodePort, AF_INET, SOCK_STREAM);
	if (m_nMaskBarcodeConnect && Devs::m_SocketMaskBarCode.WatchComm()) {
		Devs::m_SocketMaskBarCode.GetPeerName(m_SockPeer);
		Devs::m_SocketMaskBarCode.bBarCodeFlag = true;
		m_nMaskBarcodeConnect = 1;

		//SetProcessMsg(_T("Network(127.0.0.1) connected"));
		Etc_Msg(_T("Mask Barcode Network(192.168.2.203) connected"));


	}
	else
	{
		//SetProcessMsg(_T("Network(127.0.0.1) connection fail"));
		Etc_Msg(_T("Mask Barcode Network(192.168.2.203) connection fail"));



		//CStateManager* pStateMan = CStateManager::GetInstance();
		//pStateMan->SetEvent();

	}
#endif
#endif
#endif

	m_bConnectWorkNetwork = TRUE;
	m_bStateConnectWorkNetwork = TRUE;
	m_bVisionConnectWorkNetwork = TRUE;

	//StretchSetStepValue();
	//StretchSetPara();
	//ClampSetPara();

	//CStateManager* pStateMan = CStateManager::GetInstance();
	//pStateMan->SetEvent();


	return TRUE;
}
void CVisionAgentDlg::GetNetworkStatus()
{

}

BOOL CVisionAgentDlg::SetDefaultOutput()
{
	//MC
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC20, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC21, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC22, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC23, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC24, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC25, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC26, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC27, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC28, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC29, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MC30, TRUE);
	Sleep(20);

	//Gantry Relay
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_RELAY_1, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_RELAY_2, TRUE);
	Sleep(20);
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_RELAY_3, TRUE);
	Sleep(20);

	return TRUE;
}

void CVisionAgentDlg::OnStnDblclickStaticMainTitle()
{
	OnCancel();
}

void CVisionAgentDlg::OnCancel()
{
	int nValue = MessageBox(_T("<<<<< Program Close >>>>>\r\n\r\nDo you want to close?"), NULL, MB_YESNO | MB_DEFBUTTON2 | MB_ICONINFORMATION);
	if (nValue == IDYES)
	{
		//if (CanExit())
		{
			Process_Msg(_T("<<---------------------------------------------------------------------------------"));
			Vision_Msg(_T("<<---------------------------------------------------------------------------------"));
			System_Msg(_T("<<---------------------------------------------------------------------------------"));
			Etc_Msg(_T("<<---------------------------------------------------------------------------------"));
			Alarm_Msg(_T("<<---------------------------------------------------------------------------------"));
			//LogMsg_Cim(_T("<<---------------------------------------------------------------------------------"));
			Total_Msg(_T("<< End Program MotionAgent"));
			
			Devs::m_JogMotion.StopAll();

			Sleep(100);

			m_nConnect = FALSE;

			CDialogEx::OnCancel();
		}
	}
}



void CVisionAgentDlg::OnStnClickedStaticMainAlarm()
{
	Total_Msg(_T("[MAIN] Alarm Button Click"));

	m_bShowAlarmModeless = !m_pAlarmDlg->IsWindowVisible();
	//m_pAlarmDlg->RecalcLayout();
	m_pAlarmDlg->ShowWindow(m_bShowAlarmModeless);
}

void CVisionAgentDlg::OnStnClickedStaticEcsBtn()
{
	//20210802 jini
#if 0
	 //door open add
	CString str;
	if (SharedInfo::DOutputValue[_DOUT_FRONT_DOOR_OPEN] == TRUE || SharedInfo::DOutputValue[_DOUT_RIGHT_DOOR_OPEN] == TRUE ||
		SharedInfo::DOutputValue[_DOUT_BACK_DOOR_OPEN] == TRUE || SharedInfo::DOutputValue[_DOUT_LEFT_DOOR_OPEN] == TRUE)
	{
		str.Format(_T("Door Close?"));
		if (IDOK != AfxMessageBox(str, MB_OKCANCEL)) return;
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_FRONT_DOOR_OPEN, FALSE);
		Sleep(10);
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_RIGHT_DOOR_OPEN, FALSE);
		Sleep(10);
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BACK_DOOR_OPEN, FALSE);
		Sleep(10);
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_LEFT_DOOR_OPEN, FALSE);
		Total_Msg(_T("All Door Closed"));
		//Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT, FALSE);
		//Total_Msg(_T("Box Laser Point Off"));
	}
	else
	{
		str.Format(_T("Door Open?"));
		if (IDOK != AfxMessageBox(str, MB_OKCANCEL)) return;
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_FRONT_DOOR_OPEN, TRUE);
		Sleep(10);
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_RIGHT_DOOR_OPEN, TRUE);
		Sleep(10);
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BACK_DOOR_OPEN, TRUE);
		Sleep(10);
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_LEFT_DOOR_OPEN, TRUE);
		Total_Msg(_T("All Door Opend"));
		//Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT, TRUE);
		//Total_Msg(_T("Box Laser Point On"));
	}
#else
	m_bShowSafetyMapModeless = !m_pSafetyMapDlg->IsWindowVisible();
	m_pSafetyMapDlg->ShowWindow(m_bShowSafetyMapModeless);
#endif
}

void CVisionAgentDlg::ResetModel()
{
	CFileFind finder;
	CString strPathFind;
	CString strDirName;
	int Size;

	SharedInfo::m_strModelNames.RemoveAll();
	strPathFind.Format(_T("%s\\*.*"), SharedInfo::GetModelDataFolder());
	BOOL bWorking = finder.FindFile(strPathFind);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory())
		{
			strDirName = finder.GetFileName();
			if (strDirName == _T(".") || strDirName == _T("..")) continue;
			SharedInfo::m_strModelNames.Add(strDirName);
			Size = SharedInfo::m_strModelNames.GetSize();
		}
	}

}

#pragma region //Label
int CVisionAgentDlg::SaveAxisLabelParameter()
{
	CStdioFile OutFile;
	CString StrData;
	TCHAR tchPathName[256];
	int i;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_AXIS);

	if (OutFile.Open((LPCTSTR)tchPathName, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE) return 0;

	StrData.Format(_T("#BEGIN\n"));
	OutFile.WriteString(StrData);

	for (i = 0; i < MAX_AXIS_SIZE; i++)
	{
		StrData.Format(_T("[AXIS%d]\t%s\n"), i, m_AxisLabel[i].m_StrLabel);
		OutFile.WriteString(StrData);
	}

	StrData.Format(_T("#END"));
	OutFile.WriteString(StrData);

	OutFile.Close();

	return 0;
}

int CVisionAgentDlg::LoadAxisLabelParameter()
{
	CStdioFile InFile;
	CString strIndex = _T("");
	CString strSrc = _T("");
	CString strResult = _T("");
	TCHAR tchPathName[256];
	int nIndex = 0;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_AXIS);
	if (InFile.Open((LPCTSTR)tchPathName, CFile::modeRead | CFile::typeText) == FALSE)
		return 0;

	while (InFile.ReadString(strSrc) != FALSE) {
		strSrc.TrimLeft();
		strSrc.TrimRight();

		if (!strSrc.Compare(_T("#BEGIN")) || strSrc.GetLength() < 1) continue;
		if (!strSrc.Compare(_T("#END")) || strSrc == EOF) break;

		strIndex.Format(_T("[AXIS%d]"), nIndex);

		strResult = LoadFileData(&InFile, strSrc, strIndex);

		m_AxisLabel[nIndex].m_StrLabel = strResult;

		nIndex++;
	}

	InFile.Close();

	return 0;

}

int CVisionAgentDlg::SaveDInputLabelParameter()
{
	CStdioFile OutFile;
	CString StrData;
	TCHAR tchPathName[256];
	int i;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_DINPUT);

	if (OutFile.Open((LPCTSTR)tchPathName, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE) return 0;

	StrData.Format(_T("#BEGIN\n"));
	OutFile.WriteString(StrData);

	for (i = 0; i < MAX_DINPUT_SIZE; i++)
	{
		StrData.Format(_T("[INPUT%d]\t%s\n"), i, m_DInputLabel[i].m_StrLabel);
		OutFile.WriteString(StrData);
	}

	StrData.Format(_T("#END"));
	OutFile.WriteString(StrData);

	OutFile.Close();

	return 0;
}

int CVisionAgentDlg::LoadDInputLabelParameter()
{
	CStdioFile InFile;
	CString strIndex = _T("");
	CString strSrc = _T("");
	CString strResult = _T("");
	TCHAR tchPathName[256];
	int nIndex = 0;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_DINPUT);
	if (InFile.Open((LPCTSTR)tchPathName, CFile::modeRead | CFile::typeText) == FALSE)
		return 0;

	while (InFile.ReadString(strSrc) != FALSE) {
		strSrc.TrimLeft();
		strSrc.TrimRight();

		if (!strSrc.Compare(_T("#BEGIN")) || strSrc.GetLength() < 1) continue;
		if (!strSrc.Compare(_T("#END")) || strSrc == EOF) break;

		strIndex.Format(_T("[INPUT%d]"), nIndex);

		strResult = LoadFileData(&InFile, strSrc, strIndex);

		m_DInputLabel[nIndex].m_StrLabel = strResult;

		nIndex++;
	}

	InFile.Close();

	return 0;
}


int CVisionAgentDlg::SaveDOutputLabelParameter()
{
	CStdioFile OutFile;
	CString StrData;
	TCHAR tchPathName[256];
	int i;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_DOUTPUT);

	if (OutFile.Open((LPCTSTR)tchPathName, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE) return 0;

	StrData.Format(_T("#BEGIN\n"));
	OutFile.WriteString(StrData);

	for (i = 0; i < MAX_DOUTPUT_SIZE; i++)
	{
		StrData.Format(_T("[OUTPUT%d]\t%s\n"), i, m_DOutputLabel[i].m_StrLabel);
		OutFile.WriteString(StrData);
	}

	StrData.Format(_T("#END"));
	OutFile.WriteString(StrData);

	OutFile.Close();

	return 0;
}


int CVisionAgentDlg::LoadDOutputLabelParameter()
{
	CStdioFile InFile;
	CString strIndex = _T("");
	CString strSrc = _T("");
	CString strResult = _T("");
	TCHAR tchPathName[256];
	int nIndex = 0;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_DOUTPUT);
	if (InFile.Open((LPCTSTR)tchPathName, CFile::modeRead | CFile::typeText) == FALSE)
		return 0;

	while (InFile.ReadString(strSrc) != FALSE) {
		strSrc.TrimLeft();
		strSrc.TrimRight();

		if (!strSrc.Compare(_T("#BEGIN")) || strSrc.GetLength() < 1) continue;
		if (!strSrc.Compare(_T("#END")) || strSrc == EOF) break;

		strIndex.Format(_T("[OUTPUT%d]"), nIndex);

		strResult = LoadFileData(&InFile, strSrc, strIndex);

		m_DOutputLabel[nIndex].m_StrLabel = strResult;

		nIndex++;
	}

	InFile.Close();

	return 0;
}

int CVisionAgentDlg::SaveAInputLabelParameter()
{
	CStdioFile OutFile;
	CString StrData;
	TCHAR tchPathName[256];
	int i;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_AINPUT);

	if (OutFile.Open((LPCTSTR)tchPathName, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE) return 0;

	StrData.Format(_T("#BEGIN\n"));
	OutFile.WriteString(StrData);

	for (i = 0; i < MAX_AINPUT_SIZE; i++)
	{
		StrData.Format(_T("[INPUT%d]\t%s\n"), i, m_AInputLabel[i].m_StrLabel);
		OutFile.WriteString(StrData);
	}

	StrData.Format(_T("#END"));
	OutFile.WriteString(StrData);

	OutFile.Close();

	return 0;
}

int CVisionAgentDlg::LoadAInputLabelParameter()
{
	CStdioFile InFile;
	CString strIndex = _T("");
	CString strSrc = _T("");
	CString strResult = _T("");
	TCHAR tchPathName[256];
	int nIndex = 0;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_AINPUT);
	if (InFile.Open((LPCTSTR)tchPathName, CFile::modeRead | CFile::typeText) == FALSE)
		return 0;

	while (InFile.ReadString(strSrc) != FALSE) {
		strSrc.TrimLeft();
		strSrc.TrimRight();

		if (!strSrc.Compare(_T("#BEGIN")) || strSrc.GetLength() < 1) continue;
		if (!strSrc.Compare(_T("#END")) || strSrc == EOF) break;

		strIndex.Format(_T("[INPUT%d]"), nIndex);

		strResult = LoadFileData(&InFile, strSrc, strIndex);

		m_AInputLabel[nIndex].m_StrLabel = strResult;

		nIndex++;
	}

	InFile.Close();

	return 0;
}

int CVisionAgentDlg::SaveAOutputLabelParameter()
{
	CStdioFile OutFile;
	CString StrData;
	TCHAR tchPathName[256];
	int i;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_AOUTPUT);

	if (OutFile.Open((LPCTSTR)tchPathName, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE) return 0;

	StrData.Format(_T("#BEGIN\n"));
	OutFile.WriteString(StrData);

	for (i = 0; i < MAX_AOUTPUT_SIZE; i++)
	{
		StrData.Format(_T("[OUTPUT%d]\t%s\n"), i, m_AOutputLabel[i].m_StrLabel);
		OutFile.WriteString(StrData);
	}

	StrData.Format(_T("#END"));
	OutFile.WriteString(StrData);

	OutFile.Close();

	return 0;
}

int CVisionAgentDlg::LoadAOutputLabelParameter()
{
	CStdioFile InFile;
	CString strIndex = _T("");
	CString strSrc = _T("");
	CString strResult = _T("");
	TCHAR tchPathName[256];
	int nIndex = 0;

	wsprintf(tchPathName, _T("%s\\%s"), SharedInfo::GetExeFilePath(), SharedInfo::STR_DATA_LABEL_AOUTPUT);
	if (InFile.Open((LPCTSTR)tchPathName, CFile::modeRead | CFile::typeText) == FALSE)
		return 0;

	while (InFile.ReadString(strSrc) != FALSE) {
		strSrc.TrimLeft();
		strSrc.TrimRight();

		if (!strSrc.Compare(_T("#BEGIN")) || strSrc.GetLength() < 1) continue;
		if (!strSrc.Compare(_T("#END")) || strSrc == EOF) break;

		strIndex.Format(_T("[OUTPUT%d]"), nIndex);

		strResult = LoadFileData(&InFile, strSrc, strIndex);

		m_AOutputLabel[nIndex].m_StrLabel = strResult;

		nIndex++;
	}

	InFile.Close();

	return 0;
}

CString CVisionAgentDlg::LoadFileData(CStdioFile* csfInFile, CString strSrcData, CString strCompData)
{
	int nPos = -1;
	int nDataLenth = 0;
	CString strResult = _T("");

	nPos = strSrcData.Find(strCompData);
	strResult = _T("-1");
	if (nPos != -1)
	{
		nPos = strSrcData.Find(_T("\t")) + 1;
		if (nPos != -1)
		{
			//TRACE(_T("DOutputLabel = %s \n"), strSrcData);
			nDataLenth = strSrcData.GetLength() - strCompData.GetLength();
			strResult = strSrcData.Mid(nPos, nDataLenth);
			strResult.TrimLeft();
			strResult.TrimRight();
		}
	}
	return strResult;
}
#pragma endregion

int CVisionAgentDlg::SaveTempur()
{
	CString strLastCnt;

	SYSTEMTIME st;

	GetLocalTime(&st);

	CStdioFile f, flog;
	CString str;
	CString StrTitle;
	string strMaskID[100];
	CString path;
	TCHAR	exepath[MAX_PATH];
	GetModuleFileName(NULL, exepath, sizeof(exepath));
	path = exepath;
	int i = path.ReverseFind('\\');
	path = path.Left(i);
	path.AppendFormat(_T("\\Data\\Tempur\\Tempur_%04d%02d%02d.csv"), st.wYear, st.wMonth, st.wDay);

	CString strTemp = path;

	if (!f.Open(strTemp, CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		if (f.Open(strTemp, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			//StrTitle.Format(_T("ModelID ,%s\n"), strMaskID);
			//f.WriteString(StrTitle);		
			StrTitle.Format(_T("Date"));

			for (int i = 0; i < 12; i++)
			{
				StrTitle.AppendFormat(_T(",Temp%d"), i + 1);
			}
			StrTitle.AppendFormat(_T("\n"));
			f.WriteString(StrTitle);
		}

		else {
			TRACE("File Open Faile~!!\r\n");
			return false;
		}
	}

	f.SeekToEnd();
	str.Format(_T("%04d%02d%02d_%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	for (int i = 0; i < 12; i++)
	{
		str.AppendFormat(_T(",%.02f"), g_CommTempTur.m_dTempValue[i]);
	}

	str.AppendFormat(_T("\n"));
	f.WriteString(str);
	f.Close();

	return 0;
}

LRESULT CVisionAgentDlg::OnReceiveCommand(WPARAM wParam, LPARAM lParam)
{
	CString str;
	g_CommTempTur.ReadBuffer();
	//g_CommESC.ReadBuffer(m_pch);
	//g_CommAOILaser.ReadAOILaserSensorBuff(str);
	return 0;
}

BOOL CVisionAgentDlg::MakeDefaultDir()
{
	CString Str = _T("");

	Str = SharedInfo::STR_SAVE_IMAGE_DIR_PATH;
	::CreateDirectory(Str, NULL);

	Str.AppendFormat(_T("\\AOI"));
	::CreateDirectory(Str, NULL);
	Str.Format(_T("D:\\SAVE_IMAGE\\AOI\\Defect"));
	::CreateDirectory(Str, NULL);
	Str.Format(_T("D:\\SAVE_IMAGE\\AOI\\Review"));
	::CreateDirectory(Str, NULL);

	Str = _T("D:\\SAVE_IMAGE");
	Str.AppendFormat(_T("\\3D"));
	::CreateDirectory(Str, NULL);

	Str = SharedInfo::GetExeFilePath();
	Str.AppendFormat(_T("\\Data"));
	::CreateDirectory(Str, NULL);
	Str.AppendFormat(_T("\\Tempur"));
	::CreateDirectory(Str, NULL);

	Str = SharedInfo::GetExeFilePath();
	Str.AppendFormat(_T("\\dat"));
	::CreateDirectory(Str, NULL);

	Str = SharedInfo::GetExeFilePath();
	Str.AppendFormat(_T("\\xml"));
	::CreateDirectory(Str, NULL);

	return TRUE;
}

//21.07.29 sjc hsms
BEGIN_EVENTSINK_MAP(CVisionAgentDlg, CDialogEx)
	ON_EVENT(CVisionAgentDlg, IDC_XCOMPROCTRL1, 1, CVisionAgentDlg::SecsEventXcomproctrl1, VTS_I2 VTS_I4)
	ON_EVENT(CVisionAgentDlg, IDC_XCOMPROCTRL1, 2, CVisionAgentDlg::SecsMsgXcomproctrl1, VTS_NONE)
END_EVENTSINK_MAP()


void CVisionAgentDlg::SecsEventXcomproctrl1(short nEventId, long lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pSecs)
	{
		m_pSecs->SecsEventXcomproctrl1(nEventId, lParam);
	}
	else
	{
		Total_Msg(_T("Error! Host Not Connected!"));
	}
}


void CVisionAgentDlg::SecsMsgXcomproctrl1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pSecs)
	{
		m_pSecs->SecsMsgXcomproctrl1();
	}
	else
	{
		Total_Msg(_T("Error! Host Not Connected!"));
	}
}

void CVisionAgentDlg::Xcom_Init()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	CString   str, strFile;
	int         nReturn;

	m_XcomInitialized = false;
	m_XcomStarted = false;
	CString m_StrPath;
	//아래 부분 cfg 넣을 위치랑 파일 이름 수정해서 넣어주세요.
	//m_StrPath.Format(_T("D:\\Data\\SYSTEM\\EQPSECS.cfg"));
	m_StrPath.Format(_T("%s\\Data\\SYSTEM\\EQPSECS.cfg"), SharedInfo::VisionAgentPath);

	//  Initialize the XCom control.
	if ((nReturn = m_XComPro.Initialize(m_StrPath)) == 0) {
		m_XcomInitialized = true;
		Total_Msg(_T("SECS XComPro initialized successfully"));
		Total_Msg(_T("SECS XComPro path = [%s]"), m_StrPath);
		if (m_pSecs)
		{
			m_pSecs->Start();  //시작
		}
	}
	else {
		//m_SECSCommunicationOK = false;
		str.Format(_T("Fail to initialize SECS XComPro : %d "), nReturn);
		Total_Msg(str);
	}
}