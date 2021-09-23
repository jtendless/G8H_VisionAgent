#include "stdafx.h"
#include "MaskPreTensionAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"
#include "VisionAgentDlg.h"

CMaskPreTensionAlignFlow::CMaskPreTensionAlignFlow()
{
	m_dDiffPos[0] = 0.;
	m_dDiffPos[1] = 0.;
	m_dDiffPos[2] = 0.;

	m_dTarget[0] = 0.;
	m_dTarget[1] = 0.;
	m_dTarget[2] = 0.;

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


CMaskPreTensionAlignFlow::~CMaskPreTensionAlignFlow()
{
}

BOOL CMaskPreTensionAlignFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eTENSION_PRE_ALIGN_2P_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eTENSION_PRE_ALIGN_2P_FLOW_INTERLOCK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY;
	m_sGroupInfo[nGroupIndex].nEndStep = _eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Other Axis Ready"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS;
	m_sGroupInfo[nGroupIndex].nEndStep = _eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. PreTensionAlign"), nGroupIndex + 1);
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
BOOL CMaskPreTensionAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CMaskPreTensionAlignFlow::Start(int nStep)
{
	memset(Devs::m_GantryMotion.m_dTpX, 0, sizeof(Devs::m_GantryMotion.m_dTpX));
	memset(Devs::m_GantryMotion.m_dTpY, 0, sizeof(Devs::m_GantryMotion.m_dTpY));

	m_bLaserFocusUseFlag = FALSE;
	m_bAutoFocusUseFlag = FALSE;

	//switch (CModelData::m_PpaPara.Info.nPpaFocusType)
	//{
	//case 0:
	//	m_bLaserFocusUseFlag = TRUE;
	//	m_bAutoFocusUseFlag = FALSE;
	//	break;

	//case 1:
	//	m_bLaserFocusUseFlag = FALSE;
	//	m_bAutoFocusUseFlag = TRUE;
	//	break;

	//case 2:
	//	m_bLaserFocusUseFlag = TRUE;
	//	m_bAutoFocusUseFlag = TRUE;
	//	break;
	//}

	m_bFlowDone = FALSE;
	m_bStopBit = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eTENSION_PRE_ALIGN_2P_FLOW_START"));
	return TRUE;
}
BOOL CMaskPreTensionAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CMaskPreTensionAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CMaskPreTensionAlignFlow* pFlow = NULL;

	pFlow = (CMaskPreTensionAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CMaskPreTensionAlignFlow::ThreadFunctionEntry(VOID)
{
	ERROR_INFO resinfo;
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	int		nRtn;
	BOOL	bComplete_Step = FALSE;
	CString Str = _T("");

	double dRefPos[4][2] = { 0.0, };
	double dActPos[4][2] = { 0.0, };

	double dPosX = 0.0, dPosY = 0.0;

	double RefT;
	double NewPositionT;
	double DiffT;
	double dRandNum;

	SYSTEMTIME st;
	int nReF = 0;
	int nIndex = 0;
	CString strTemp = _T("");
	INT nOkCnt = 0;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eTENSION_PRE_ALIGN_2P_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eTENSION_PRE_ALIGN_2P_FLOW_IDLE:
		{
			break;
		}
		case _eTENSION_PRE_ALIGN_2P_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
					break;
				}
			}
#endif

#if 0
			m_AlignPointValue[0][0] = CModelData::m_AtMaterialPara.Info.dAlignLeftHoleX * STICK_FLIP_XY;
			m_AlignPointValue[1][0] = CModelData::m_AtMaterialPara.Info.dAlignLeftHoleY * STICK_FLIP_XY;

			m_AlignPointValue[0][1] = CModelData::m_AtMaterialPara.Info.dAlignRightHoleX * STICK_FLIP_XY;
			m_AlignPointValue[1][1] = CModelData::m_AtMaterialPara.Info.dAlignRightHoleY * STICK_FLIP_XY;
#else //KJT 20210330
			m_AlignPointValue[0][0] = CModelData::m_MaterialPara.Info.dAlignLeftHoleX * STICK_FLIP_XY;
			m_AlignPointValue[1][0] = CModelData::m_MaterialPara.Info.dAlignLeftHoleY * STICK_FLIP_XY;

			m_AlignPointValue[0][1] = CModelData::m_MaterialPara.Info.dAlignRightHoleX * STICK_FLIP_XY;
			m_AlignPointValue[1][1] = CModelData::m_MaterialPara.Info.dAlignRightHoleY * STICK_FLIP_XY;
#endif
			///////////

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

			SharedInfo::LightAllOff();
			//Sleep(500);
			//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L);
			//Sleep(500);

			//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L);
			//Sleep(10);
			//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
			//Sleep(10);
			//g_CommZomm_Ring.SetLight_Zoom_Ring(CModelData::m_AlignPara.Info.nPreAlignRing_L);
			//Sleep(10);
			//g_CommZomm_Ring.Zoom_Light_On(TRUE);

			g_CommLoader_Light.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L); //KJT 20210728

			SharedInfo::nGantryZ1View = eViewPreAlign;

			//!!
			Devs::m_MappingProc.ReleaseSWMapping(eMAPPING_ID_10X);
			Devs::m_MappingProc.ReleaseXYTAlignData(eMAPPING_ID_10X);

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_INTERLOCK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_INTERLOCK"));
			break;
		}
		
		case _eTENSION_PRE_ALIGN_2P_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY, _T("_eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 0);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY, _T("_eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 2);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 1);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS:
			//if (m_nAlignPoint == 0)
				//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L);
			//else //if (m_nAlignPoint == 1)
				//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_R, CModelData::m_AlignPara.Info.nPreAlignRing_R);

			if (m_nAlignPoint == 0)
			{
				//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L);
				//Sleep(10);
				//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
				//Sleep(10);
				//g_CommZomm_Ring.SetLight_Zoom_Ring(CModelData::m_AlignPara.Info.nPreAlignRing_L);
				//Sleep(10);
				//g_CommZomm_Ring.Zoom_Light_On(TRUE);

				g_CommLoader_Light.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L); //KJT 20210728
			}
			else
			{
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

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				//SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z1_INSPECTION_POS_1ST, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z1_INSPECTION_POS_1ST"));
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 3);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS_CHECK"));
			}
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST:
			Devs::m_GantryMotion.Move_GantryZ1_PreAlign_Pos();
			Sleep(20); //!!

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_PreAlign_Pos())
			{
				Sleep(3000); //!!
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRAB_START, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 4);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_Z2_INSPECTION_POS_1ST_CHECK"));
			}
			break;

#pragma region //Tension Pre Align
		case _eTENSION_PRE_ALIGN_2P_FLOW_GRAB_START:
			SharedInfo::bPreAlignGrabDone = FALSE;

			nRtn = Devs::m_GantryMotion.FindHoleBlob_2P_PreAlign(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint], m_nAlignPoint);

			if (nRtn == FALSE)
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
				break;
			}

			SharedInfo::dPreAlignVisionResultValue[0][m_nAlignPoint] = m_AlignVisionResultValue[0][m_nAlignPoint];
			SharedInfo::dPreAlignVisionResultValue[1][m_nAlignPoint] = m_AlignVisionResultValue[1][m_nAlignPoint];

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_AlignVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRAB_DONE_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GRAB_DONE_CHECK:
			SharedInfo::bPreAlignGrabDone = TRUE;

			if ((m_bDirReverse == FALSE && m_nAlignPoint == 1) || (m_bDirReverse == TRUE && m_nAlignPoint == 0))
			{
				SharedInfo::nPreAlignCurCount++;
				Str.Format(_T("AlignCurCount:%d Diff X[0]:%.5f, Y[0]:%.5f, X[1]:%.5f, Y[1]:%.5f"), SharedInfo::nPreAlignCurCount, m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1]);
				Total_Msg(Str);

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
				Total_Msg(Str);

				if (fabs(m_AlignVisionResultValue[0][0]) < (float)CModelData::m_AlignPara.Info.dPreAlignTargetX &&
					fabs(m_AlignVisionResultValue[0][1]) < (float)CModelData::m_AlignPara.Info.dPreAlignTargetX &&//X
					fabs(m_AlignVisionResultValue[1][0]) < (float)CModelData::m_AlignPara.Info.dPreAlignTargetY &&
					fabs(m_AlignVisionResultValue[1][1]) < (float)CModelData::m_AlignPara.Info.dPreAlignTargetY && //Y
					(fabs(m_dDiffPos[2]) < 0.001 || (360 - fabs(m_dDiffPos[2])) < 0.001)) //KJT 20210319
				{
					SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS, _T("_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS"));
				}
				else
				{
					SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS"));
				}
			}
			else
			{
				if (m_bDirReverse == FALSE)
					m_nAlignPoint = 1;
				else
					m_nAlignPoint = 0;

				Sleep(1000);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS"));

			}
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS:
//#pragma region //AutoRun, ManualRun Interlock
//			if (SharedInfo::bPreAlignGrabDone == FALSE ||
//				(m_bDirReverse == FALSE && m_nAlignPoint == 0) || (m_bDirReverse == TRUE && m_nAlignPoint == 1))
//			{
//				Total_Msg(_T("PreAlign All Grab Done False !!"));
//				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
//				break;
//			}
//#pragma endregion

			Devs::m_GripperZMotion.Move_GripperLeftZ_TensionPos();
			Sleep(10);
			//Devs::m_GripperZMotion.Move_GripperRightZ_TensionPos();

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_TensionPos() && Devs::m_GripperZMotion.Is_GripperRightZ_TensionPos())
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_START, _T("_eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 5);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK"));
			}
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_START:
//#pragma region //AutoRun, ManualRun Interlock
//			if (SharedInfo::bPreAlignGrabDone == FALSE ||
//				(m_bDirReverse == FALSE && m_nAlignPoint == 0) || (m_bDirReverse == TRUE && m_nAlignPoint == 1))
//			{
//				Total_Msg(_T("PreAlign All Grab Done False !!"));
//				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
//				break;
//			}
//#pragma endregion

			Devs::m_StretchMotion.Gripper2PAlignTensionStretchMoveStart(m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[0][1]);

			SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_DONE_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_DONE_CHECK:
			if (Devs::m_StretchMotion.Gripper2PAlignTensionStretchMoveDoneCheck())
			{
				Sleep(1000); //!!
				//SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_PITCH_TENSTION_START, _T("_eTENSION_PRE_ALIGN_2P_FLOW_PITCH_TENSTION_START"));				
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_DONE_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 6);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_DONE_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_STRETCH_TENSTION_DONE_CHECK"));
			}
			break;

		//case _eTENSION_PRE_ALIGN_2P_FLOW_PITCH_TENSTION_START:
//#pragma region //AutoRun, ManualRun Interlock
//			if (SharedInfo::bPreAlignGrabDone == FALSE ||
//				(m_bDirReverse == FALSE && m_nAlignPoint == 0) || (m_bDirReverse == TRUE && m_nAlignPoint == 1))
//			{
//				Total_Msg(_T("PreAlign All Grab Done False !!"));
//				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
//				break;
//			}
//#pragma endregion

			//Devs::m_PitchMotion.Gripper2PAlignTensionPitchMoveStart(m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[1][1]);
			//SharedInfo::bPreAlignGrabDone = FALSE;

			//SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_PITCH_TENSTION_DONE_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_PITCH_TENSTION_DONE_CHECK"));
			//SetTimeOut(TIME_OUT_MOTION);
			//break;

		//case _eTENSION_PRE_ALIGN_2P_FLOW_PITCH_TENSTION_DONE_CHECK:
			//if (Devs::m_PitchMotion.Gripper2PAlignTensionPitchMoveDoneCheck())
			//{
			//	Sleep(1000); //!!
			//	SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_PITCH_TENSTION_DONE_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_PITCH_TENSTION_DONE_CHECK"));
			//}
			//break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_ClampPos();
			Sleep(10);
			//Devs::m_GripperZMotion.Move_GripperRightZ_ClampPos();

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_ClampPos() && Devs::m_GripperZMotion.Is_GripperRightZ_ClampPos())
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GANTRY_XY_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 7);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_GRIPPER_Z_CLAMP_POS_CHECK"));
			}
			break;

#pragma endregion
		case _eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 8);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_Z2_WAIT_POS_CHECK"));
			}
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_DONE, _T("_eTENSION_PRE_ALIGN_2P_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out"), eTENSION_PRE_ALIGN_2P_FLOW + 9);
				SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_ERROR, _T("_eTENSION_PRE_ALIGN_2P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eTENSION_PRE_ALIGN_2P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_ERROR:
			break;

		case _eTENSION_PRE_ALIGN_2P_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("TENSION_PRE_ALIGN_2P_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eTENSION_PRE_ALIGN_2P_FLOW_IDLE, _T("_eTENSION_PRE_ALIGN_2P_FLOW_IDLE"));
			break;
		}

		default:
		{
			break;
		}
		}

		Sleep(100); //!!
	}
}

double CMaskPreTensionAlignFlow::GetAlignPos_X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	dPos -= CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	return dPos;
}
double CMaskPreTensionAlignFlow::GetAlignPos_Y(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	dPos -= CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;
	return dPos;
}

BOOL CMaskPreTensionAlignFlow::FlowInterlock()
{
	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	Total_Msg(_T("Check Pickup Unit Backward !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Unsafe Pos Detect Sensor !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Backward Detect Sensor !!!"));
	//	return FALSE;
	//}

	//if (Devs::m_ClampMotion.Is_ClampOn_Active() != TRUE)
	//{
	//	Total_Msg(_T("Check Acitve Clamp On !!!"));
	//	return FALSE;
	//}

	//if (Devs::m_GripperZMotion.Is_GripperZ_ClampPos() == FALSE)
	//{
	//	Total_Msg(_T("Check Gripper Z Clamp Pos !!!"));
	//	return FALSE;
	//}

	return TRUE;
}
