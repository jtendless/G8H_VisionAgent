#include "stdafx.h"
#include "MaskPreAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CMaskPreAlignFlow::CMaskPreAlignFlow()
{
	m_dDiffPos[0] = 0.0;
	m_dDiffPos[1] = 0.0;
	m_dDiffPos[2] = 0.0;

	m_dTarget[0] = 0.0;
	m_dTarget[1] = 0.0;
	m_dTarget[2] = 0.0;

	m_nAlignPoint = 0;
	m_bDirReverse = FALSE;

	m_AlignPointValue[0][0] = 0.0;
	m_AlignPointValue[1][0] = 0.0;
	m_AlignPointValue[0][1] = 0.0;
	m_AlignPointValue[1][1] = 0.0;

	m_AlignVisionResultValue[0][0] = 0.0;
	m_AlignVisionResultValue[1][0] = 0.0;
	m_AlignVisionResultValue[0][1] = 0.0;
	m_AlignVisionResultValue[1][1] = 0.0;
}


CMaskPreAlignFlow::~CMaskPreAlignFlow()
{
}

BOOL CMaskPreAlignFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eMASK_PRE_ALIGN_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eMASK_PRE_ALIGN_FLOW_INTERLOCK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_nMaxGroupCount = nGroupIndex;
#pragma endregion

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}
BOOL CMaskPreAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eMASK_PRE_ALIGN_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CMaskPreAlignFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eMASK_PRE_ALIGN_FLOW_START"));
	return TRUE;
}
BOOL CMaskPreAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT CMaskPreAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CMaskPreAlignFlow* pFlow = NULL;

	pFlow = (CMaskPreAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CMaskPreAlignFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1, nRtn;
	BOOL	bComplete_Step = FALSE;
	CString Str = _T("");
	double dDiffXTemp = 0.0;
	double dPosX = 0.0, dPosY = 0.0;
	//KJT 20210304
	double dVel[3] = { 1.0, 1.0, 1.0 };
	double dAcc[3] = { 2.0, 2.0, 2.0 };
	double dDecel[3] = { 2.0, 2.0, 2.0 };
	
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)AfxGetMainWnd();
	SYSTEMTIME st;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eMASK_PRE_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eMASK_PRE_ALIGN_FLOW_IDLE:
		{
			break;
		}
		case _eMASK_PRE_ALIGN_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = ePRE_ALIGN_FLOW;

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
					break;
				}
			}
#endif
			m_AlignPointValue[0][0] = CModelData::m_MaterialPara.Info.dAlignLeftHoleX * STICK_FLIP_XY;
			m_AlignPointValue[1][0] = CModelData::m_MaterialPara.Info.dAlignLeftHoleY * STICK_FLIP_XY;

			m_AlignPointValue[0][1] = CModelData::m_MaterialPara.Info.dAlignRightHoleX * STICK_FLIP_XY;
			m_AlignPointValue[1][1] = CModelData::m_MaterialPara.Info.dAlignRightHoleY * STICK_FLIP_XY;
			/////////////

			SharedInfo::nGantryZ1View = eViewPreAlign;

			m_nAlignPoint = 0;
			m_bDirReverse = FALSE;			

			m_AlignVisionResultValue[0][0] = 0.0;
			m_AlignVisionResultValue[1][0] = 0.0;
			m_AlignVisionResultValue[0][1] = 0.0;
			m_AlignVisionResultValue[1][1] = 0.0;

			SharedInfo::dPreAlignVisionResultValue[0][0] = m_AlignVisionResultValue[0][0];
			SharedInfo::dPreAlignVisionResultValue[1][0] = m_AlignVisionResultValue[1][0];
			SharedInfo::dPreAlignVisionResultValue[0][1] = m_AlignVisionResultValue[0][1];
			SharedInfo::dPreAlignVisionResultValue[1][1] = m_AlignVisionResultValue[1][1];			
			SharedInfo::nPreAlignCurCount = 0;

			GetLocalTime(&st);
			m_strFilePath.Format(_T("%s\\Result\\MaskAlign\\MaskPreAlign_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::VisionAgentPath, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);


			SharedInfo::LightAllOff();
			Sleep(500);
			//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L);
			//Sleep(500);

			Devs::m_MappingProc.ReleaseSWMapping(eMAPPING_ID_10X); //!! KJT 20200913
			Devs::m_MappingProc.ReleaseXYTAlignData(eMAPPING_ID_10X); //!! KJT 20200913

			SetStep(_eMASK_PRE_ALIGN_FLOW_INTERLOCK, _T("_eMASK_PRE_ALIGN_FLOW_INTERLOCK"));
			break;
			
		case _eMASK_PRE_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::nPrevFlowID == eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW) //KJT 20210326
					SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS"));
				else
					SetStep(_eMASK_PRE_ALIGN_FLOW_UNLOADER_READY, _T("_eMASK_PRE_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eMASK_PRE_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eMASK_PRE_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_PRE_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_UNLOADER_READY_CHECK : Time Out"), ePRE_ALIGN_FLOW + 0);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case _eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eMASK_PRE_ALIGN_FLOW_LOADER_READY, _T("_eMASK_PRE_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), ePRE_ALIGN_FLOW + 3);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eMASK_PRE_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eMASK_PRE_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_PRE_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_LOADER_READY_CHECK : Time Out"), ePRE_ALIGN_FLOW + 1);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS:
			if (m_nAlignPoint == 0)
			{
				//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L);

				//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L);
				//Sleep(10);
				//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
				//Sleep(10);
				//g_CommZomm_Ring.SetLight_Zoom_Ring(CModelData::m_AlignPara.Info.nPreAlignRing_L);
				//Sleep(10);
				//g_CommZomm_Ring.Zoom_Light_On(TRUE);

				g_CommLoader_Light.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L); //KJT 20210728
			}
			else //if (m_nAlignPoint == 1)
			{
				//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_R, CModelData::m_AlignPara.Info.nPreAlignRing_R);

				//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(CModelData::m_AlignPara.Info.nPreAlignCoAxial_R);
				//Sleep(10);
				//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
				//Sleep(10);
				//g_CommZomm_Ring.SetLight_Zoom_Ring(CModelData::m_AlignPara.Info.nPreAlignRing_R);
				//Sleep(10);
				//g_CommZomm_Ring.Zoom_Light_On(TRUE);

				g_CommLoader_Light.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L); //KJT 20210728
			}			

			m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
			m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!
			
			SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_POS, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS_CHECK : Time Out"), ePRE_ALIGN_FLOW + 4);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS_CHECK"));
			}
			break;

		case _eMASK_PRE_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_POS:
			Devs::m_GantryMotion.Move_GantryZ1_PreAlign_Pos();

			SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_POS_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_PRE_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_PreAlign_Pos())
			{
				Sleep(100); //!!
				SetStep(_eMASK_PRE_ALIGN_FLOW_GRAB_START, _T("_eMASK_PRE_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_GANTRY_Z2_PRE_ALIGN_POS_CHECK : Time Out"), ePRE_ALIGN_FLOW + 5);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_POS_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_POS_CHECK"));
			}
			break;

		case _eMASK_PRE_ALIGN_FLOW_GRAB_START:
			SharedInfo::bPreAlignGrabDone = FALSE;

			nRtn = Devs::m_GantryMotion.FindHoleBlob_2P_PreAlign(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint], m_nAlignPoint);

			if (nRtn == 0)
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_GRAB_START : Grab Error"), ePRE_ALIGN_FLOW + 6);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
				break;
			}

			SharedInfo::dPreAlignVisionResultValue[0][m_nAlignPoint] = m_AlignVisionResultValue[0][m_nAlignPoint];
			SharedInfo::dPreAlignVisionResultValue[1][m_nAlignPoint] = m_AlignVisionResultValue[1][m_nAlignPoint];

			Str.Format(_T("AlignPoint:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_AlignVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			SetStep(_eMASK_PRE_ALIGN_FLOW_GRAB_DONE_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eMASK_PRE_ALIGN_FLOW_GRAB_DONE_CHECK:
			SharedInfo::bPreAlignGrabDone = TRUE;

			//KJT 20210310
			if (m_AlignVisionResultValue[0][m_nAlignPoint] == 0 || m_AlignVisionResultValue[1][m_nAlignPoint] == 0)
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_GRAB : Retry Over !!"), ePRE_ALIGN_FLOW + 7);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
				break;
			}
			else
			{
				if ((m_bDirReverse == FALSE && m_nAlignPoint == 1) || (m_bDirReverse == TRUE && m_nAlignPoint == 0))
				{
					SharedInfo::nPreAlignCurCount++;
					Str.Format(_T("AlignCurCount:%d Diff X[0]:%.5f, Y[0]:%.5f, X[1]:%.5f, Y[1]:%.5f"), SharedInfo::nPreAlignCurCount, m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1]);
					Vision_Msg(Str);

					if (m_bDirReverse == FALSE)
					{
						m_bDirReverse = TRUE;
						m_nAlignPoint = 1;
					}
					else
					{
						m_bDirReverse = FALSE;
						m_nAlignPoint = 0;
					}

					Sleep(100);
					Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], TRUE);

					Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
					Vision_Msg(Str);

					dDiffXTemp = m_AlignVisionResultValue[0][0] + m_AlignVisionResultValue[0][1];
					Str.Format(_T("Diff_X:%.5f"), dDiffXTemp);
					Vision_Msg(Str);

					if (dDiffXTemp < (float)CModelData::m_AlignPara.Info.dPreAlignTargetX &&
						fabs(m_AlignVisionResultValue[1][0]) < (float)CModelData::m_AlignPara.Info.dPreAlignTargetY &&
						fabs(m_AlignVisionResultValue[1][1]) < (float)CModelData::m_AlignPara.Info.dPreAlignTargetY
						&&
						(fabs(m_dDiffPos[2]) < 0.001 || (360 - fabs(m_dDiffPos[2])) < 0.001)) //KJT 20210319
					{
						SharedInfo::LightAllOff(); //KJT 20210226

						SaveMaskPreAlignResult();

						SetStep(_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
					}
					else
					{
						SetStep(_eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START, _T("_eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START"));
					}
				}
				else
				{
					if (m_bDirReverse == FALSE)
						m_nAlignPoint = 1;
					else
						m_nAlignPoint = 0;

					//Sleep(1000);
					SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS"));
				}
			}
			break;

		case _eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START:
		{
#if 0
#pragma region //AutoRun, ManualRun Interlock
			if (SharedInfo::bPreAlignGrabDone == FALSE ||
				(m_bDirReverse == FALSE && m_nAlignPoint == 0) || (m_bDirReverse == TRUE && m_nAlignPoint == 1))
			{
				Total_Msg(_T("PreAlign All Grab Done False !!"));
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
				break;
			}
#pragma endregion
#endif

#if UVW_MOVE_TYPE //KJT 20210322
			double dRefPos[4][2] = { 0.0, };
			double dActPos[4][2] = { 0.0, };

			//0:LB, 1:LT, 2:RT, 3:RB
			dRefPos[0][0] = m_AlignPointValue[0][0];
			dRefPos[0][1] = m_AlignPointValue[1][0];

			dRefPos[1][0] = m_AlignPointValue[0][0];
			dRefPos[1][1] = m_AlignPointValue[1][0] + 200.0;

			dRefPos[2][0] = m_AlignPointValue[0][1];
			dRefPos[2][1] = m_AlignPointValue[1][1] + 200.0;

			dRefPos[3][0] = m_AlignPointValue[0][1];
			dRefPos[3][1] = m_AlignPointValue[1][1];


			dActPos[0][0] = m_AlignPointValue[0][0] + m_AlignVisionResultValue[0][0];
			dActPos[0][1] = m_AlignPointValue[1][0] + m_AlignVisionResultValue[1][0];

			dActPos[1][0] = m_AlignPointValue[0][0];
			dActPos[1][1] = m_AlignPointValue[1][0] + 200.0;

			dActPos[2][0] = m_AlignPointValue[0][1];
			dActPos[2][1] = m_AlignPointValue[1][1] + 200.0;

			dActPos[3][0] = m_AlignPointValue[0][1] + m_AlignVisionResultValue[0][1];
			dActPos[3][1] = m_AlignPointValue[1][1] + m_AlignVisionResultValue[1][1];

			Devs::m_InspectionStageMotion.UVWStageAlignMove(0, dRefPos, dActPos);
#else //KJT 20210304. FMM
			Devs::m_InspectionStageMotion.UVWStagePosMove(m_dDiffPos, dVel, dAcc, dDecel);
#endif
			SharedInfo::bPreAlignGrabDone = FALSE;

			SetStep(_eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
		}
			break;

		case _eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK:
#if UVW_MOVE_TYPE //KJT 20210322
			if (Devs::m_InspectionStageMotion.IsUVWStagePos(m_dDiffPos) == TRUE)
#else //KJT 20210304. FMM
			if (Devs::m_InspectionStageMotion.IsUVWStagePos())
#endif
			{
				SetStep(_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS, _T("_eMASK_PRE_ALIGN_FLOW_GANTRY_XY_PRE_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK : Time Out"), ePRE_ALIGN_FLOW + 8);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			}
			break;

		case _eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			SetStep(_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			
			break;

		case _eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::Active.ProcessEndFlow != eCOMBO_AUTO_RUN_FLOW_PRE_ALIGN)
					SetStep(_eMASK_PRE_ALIGN_FLOW_DONE, _T("_eMASK_PRE_ALIGN_FLOW_DONE"));
				else
					SetStep(_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK : Time Out"), ePRE_ALIGN_FLOW + 9);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			}
			break;

		case _eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eMASK_PRE_ALIGN_FLOW_DONE, _T("_eMASK_PRE_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out"), ePRE_ALIGN_FLOW + 10);
				SetStep(_eMASK_PRE_ALIGN_FLOW_ERROR, _T("_eMASK_PRE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMASK_PRE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eMASK_PRE_ALIGN_FLOW_ERROR:
			break;

		case _eMASK_PRE_ALIGN_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = ePRE_ALIGN_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("MASK_PRE_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eMASK_PRE_ALIGN_FLOW_IDLE, _T("_eMASK_PRE_ALIGN_FLOW_IDLE"));
			break;
		}

		default:
		{
			break;
		}
		}

		Sleep(50); //!!
	}
}

//DO NOT USE
BOOL CMaskPreAlignFlow::GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT)
{

	double dVel[3] = { 1., };
	double dAcc[3] = { 2., };
	double dDecel[3] = { 2., };

	double R;

	double dError;
#if 0
	double RefT[2], NewPositionT[2], DiffT[2], DiffPosition[3] = { 0, };
	for (int i = 0; i < 2; i++)
	{




		RefT[i] = atan((dRefPosX[i] / dRefPosY[i]));
		NewPositionT[i] = atan((dRefPosX[i] + dDiffPosX[i]) / (dRefPosY[i] + dDiffPosY[i]));
		DiffT[i] = NewPositionT[i] - RefT[i];
		DiffPosition[0] += dDiffPosX[i];
		DiffPosition[1] += dDiffPosY[i];
		DiffPosition[2] += DiffT[i];


	}
	*ResultX = DiffPosition[0] / 2;
	*ResultY = DiffPosition[1] / 2;
	*ResultT = DiffPosition[2] / 2 * (180. / PI);
	//*ResultX = -*ResultX;
	//*ResultY = -*ResultY;
	//*ResultT = -*ResultT;
#else
	double RefT, NewPositionT, DiffT[2], DiffPosition[3] = { 0, };
	RefT = atan2((dRefPosY[1] - dRefPosY[0]), (dRefPosX[1] - dRefPosX[0]));


	NewPositionT = atan2((dRefPosY[1] + dDiffPosY[1]) - (dRefPosY[0] + dDiffPosY[0])
		, (dRefPosX[1] + dDiffPosX[1]) - (dRefPosX[0] + dDiffPosX[0]));

	for (int i = 0; i < 2; i++)
	{


		DiffPosition[0] += dDiffPosX[i];
		DiffPosition[1] += dDiffPosY[i];



	}
	DiffPosition[2] = NewPositionT - RefT;
	*ResultX = DiffPosition[0] / 2;
	*ResultY = DiffPosition[1] / 2;
	*ResultT = DiffPosition[2] * (180. / PI);
#endif
	*ResultX = *ResultX * (-1);
	*ResultY = *ResultY * (-1);
	*ResultT = *ResultT * (-1);

	Total_Msg(_T("PreAlign Result X : %.5f, Y : %.5f, T : %.7f"), *ResultX, *ResultY, *ResultT);

#if 0
	R = sqrt(dRefPosX[0] * dRefPosX[0] + dRefPosY[1] * dRefPosY[1]);
	*dErrorX = fabs(*ResultX) + fabs(R * (*ResultT / (180. / PI) * 2));
	*dErrorY = fabs(*ResultY) + fabs(R * (*ResultT / (180. / PI) * 2));

#endif
	dError = sqrt(*ResultX  * *ResultX + *ResultY * *ResultY);
#if 1

#endif




	//Total_Msg(_T("MFA Align Error X : %.5f, Y : %.5f, E : %.5f"), *dErrorX, *dErrorY, dError);


	return TRUE;
}
double CMaskPreAlignFlow::GetAlignPos_X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	dPos -= CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	return dPos;
}
double CMaskPreAlignFlow::GetAlignPos_Y(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	dPos -= CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;
	return dPos;
}

BOOL CMaskPreAlignFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("MaskPreAlignFlow"), ePRE_ALIGN_FLOW, 30) == FALSE)
	{
		return FALSE;
	}
	
	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	SharedInfo::SetAlarm(_T("ePRE_ALIGN_FLOW CstPickUnit Backward Error"), ePRE_ALIGN_FLOW + 9);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("ePRE_ALIGN_FLOW CST Unsafe Pos Error"), ePRE_ALIGN_FLOW + 10);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("ePRE_ALIGN_FLOW CST Backward Detect Error"), ePRE_ALIGN_FLOW + 11);
	//	return FALSE;
	//}

	return TRUE;
}

int CMaskPreAlignFlow::SaveMaskPreAlignResult()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)AfxGetMainWnd();

	CString strLastCnt;
	SYSTEMTIME st;
	GetLocalTime(&st);

	CStdioFile f, flog;
	CString str;
	CString StrTitle;
	string strMaskID[100];
	int i = 0;

	if (!f.Open(m_strFilePath, CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		if (f.Open(m_strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			StrTitle.Format(_T("Date, Left_Target_Pos_X, Left_Target_Pos_Y, Right_Target_Pos_X, Right_Target_Pos_Y, Target_X, Target_Y, Left_Diff_X, Left_Diff_Y, Right_Diff_X, Right_Diff_Y\n"));
			f.WriteString(StrTitle);
		}
		else
		{
			TRACE("File Open Faile~!!\r\n");
			return false;
		}
	}

	f.SeekToEnd();

	str.Format(_T("%02d%02d%02d,"), st.wHour, st.wMinute, st.wSecond);
	str.AppendFormat(_T("%.5f,"), m_AlignPointValue[0][0]);
	str.AppendFormat(_T("%.5f,"), m_AlignPointValue[1][0]);
	str.AppendFormat(_T("%.5f,"), m_AlignPointValue[0][1]);
	str.AppendFormat(_T("%.5f,"), m_AlignPointValue[1][1]);

	str.AppendFormat(_T("%.5f,"), CModelData::m_AlignPara.Info.dPreAlignTargetX);
	str.AppendFormat(_T("%.5f,"), CModelData::m_AlignPara.Info.dPreAlignTargetY);
	
	str.AppendFormat(_T("%.5f,"), m_AlignVisionResultValue[0][0]);
	str.AppendFormat(_T("%.5f,"), m_AlignVisionResultValue[1][0]);
	str.AppendFormat(_T("%.5f,"), m_AlignVisionResultValue[0][1]);
	str.AppendFormat(_T("%.5f,"), m_AlignVisionResultValue[1][1]);

	f.WriteString(str);
	f.Close();

	return 0;
}