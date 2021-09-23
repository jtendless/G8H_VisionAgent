#include "stdafx.h"
#include "MaskTag4PAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CMaskTag4PAlignFlow::CMaskTag4PAlignFlow()
{
}


CMaskTag4PAlignFlow::~CMaskTag4PAlignFlow()
{
}

BOOL CMaskTag4PAlignFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}

BOOL CMaskTag4PAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CMaskTag4PAlignFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_START"));
	return TRUE;
}
BOOL CMaskTag4PAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CMaskTag4PAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CMaskTag4PAlignFlow* pFlow = NULL;

	pFlow = (CMaskTag4PAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CMaskTag4PAlignFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CString Str = _T("");

	double dRefPos[4][2] = { 0.0, };
	double dActPos[4][2] = { 0.0, };

	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eMASK_TAGKEY_4P_ALIGN_FLOW_IDLE:
		{
			break;
		}
		case _eMASK_TAGKEY_4P_ALIGN_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

#pragma region //TagKey
			if (CModelData::m_InspectionPara.Info.nStickTensionUseMode != eSTICK_TENSION_ALIGN)
			{
				//LB
				m_AlignPointValue[0][0] = CModelData::m_MaterialPara.Info.dTegkey_LB_X;
				m_AlignPointValue[1][0] = CModelData::m_MaterialPara.Info.dTegkey_LB_Y;
				//LT
				m_AlignPointValue[0][1] = CModelData::m_MaterialPara.Info.dTegkey_LT_X;
				m_AlignPointValue[1][1] = CModelData::m_MaterialPara.Info.dTegkey_LT_Y;
				//RT
				m_AlignPointValue[0][2] = CModelData::m_MaterialPara.Info.dTegkey_RT_X;
				m_AlignPointValue[1][2] = CModelData::m_MaterialPara.Info.dTegkey_RT_Y;
				//RB
				m_AlignPointValue[0][3] = CModelData::m_MaterialPara.Info.dTegkey_RB_X;
				m_AlignPointValue[1][3] = CModelData::m_MaterialPara.Info.dTegkey_RB_Y;
			}
			else
			{
				//LB
				m_AlignPointValue[0][0] = CModelData::m_AtMaterialPara.Info.dTegkey_LB_X;
				m_AlignPointValue[1][0] = CModelData::m_AtMaterialPara.Info.dTegkey_LB_Y;
				//LT
				m_AlignPointValue[0][1] = CModelData::m_AtMaterialPara.Info.dTegkey_LT_X;
				m_AlignPointValue[1][1] = CModelData::m_AtMaterialPara.Info.dTegkey_LT_Y;
				//RT
				m_AlignPointValue[0][2] = CModelData::m_AtMaterialPara.Info.dTegkey_RT_X;
				m_AlignPointValue[1][2] = CModelData::m_AtMaterialPara.Info.dTegkey_RT_Y;
				//RB
				m_AlignPointValue[0][3] = CModelData::m_AtMaterialPara.Info.dTegkey_RB_X;
				m_AlignPointValue[1][3] = CModelData::m_AtMaterialPara.Info.dTegkey_RB_Y;
			}
#pragma endregion


			SharedInfo::nGantryZ1View = eViewReview10X;

			m_AlignCnt = 0;

			//g_CommLight_8ch.SetLight_Review_Coaxial(0);
			//g_CommLight_12ch.SetLight_Review_Ring(0);
			//g_CommLight_8ch.SetLight_PreAlign(0, 0);

			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_AlignPara.Info.nEdge4PAlignBacklight; // 100;

			//g_CommMLCLedLight.BackLightOn(nBackLightVal);

			Devs::m_MappingProc.ReleaseSWMapping(eMAPPING_ID_10X); //!! KJT 20200913
			Devs::m_MappingProc.ReleaseXYTAlignData(eMAPPING_ID_10X); //!! KJT 20200913

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_INTERLOCK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_INTERLOCK"));
			break;
		}

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case _eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case _eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Pos(GetAlignPos_X(m_AlignCnt), TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetAlignPos_Y(m_AlignCnt));
			Sleep(20); //!!

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetAlignPos_X(m_AlignCnt)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetAlignPos_Y(m_AlignCnt)))
			{
				if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(GetAlignPos_X(m_AlignCnt)))
					SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS"));
				else
					SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_CHECK);
			}
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS:
			//Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS_CHECK:
			//if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			//{
			//	SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_START"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS_CHECK);
			//}
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_4P_GRAB_START, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_4P_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK);
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_4P_GRAB_START, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_4P_GRAB_START"));
#endif
			break;

#pragma region //PPA Point Align
		case _eMASK_TAGKEY_4P_ALIGN_FLOW_4P_GRAB_START:
			Devs::m_GantryMotion.FindBlob_TagKey4PAlign_Review10X(&m_AlignVisionResultValue[0][m_AlignCnt], &m_AlignVisionResultValue[1][m_AlignCnt]);

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_AlignCnt, m_AlignVisionResultValue[0][m_AlignCnt], m_AlignVisionResultValue[1][m_AlignCnt]);
			Total_Msg(Str);

			if (m_AlignCnt == 3)
			{
				m_AlignVisionPreResultValue[m_AlignCnt][0] = m_AlignVisionResultValue[0][m_AlignCnt];
				m_AlignVisionPreResultValue[m_AlignCnt][1] = m_AlignVisionResultValue[1][m_AlignCnt];
				m_AlignCnt = 0;

				Sleep(100);
				Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], TRUE);

				Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
				Total_Msg(Str);

				if (fabs(m_dDiffPos[0]) <= m_dTarget[0] && fabs(m_dDiffPos[1]) <= m_dTarget[1] && fabs(m_dDiffPos[2]) <= m_dTarget[2])
				{
					SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS"));
				}
				else
				{
					SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_4P_UVW_MOVE_START, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_4P_UVW_MOVE_START"));
				}
			}
			else
			{
				m_AlignVisionPreResultValue[0][m_AlignCnt] = m_AlignVisionResultValue[0][m_AlignCnt];
				m_AlignVisionPreResultValue[1][m_AlignCnt] = m_AlignVisionResultValue[1][m_AlignCnt];
				m_AlignCnt++;
				Sleep(1000);
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS"));

			}
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_4P_UVW_MOVE_START:
		{
			memset(dRefPos, 0, sizeof(dRefPos));
			memset(dActPos, 0, sizeof(dActPos));

			//0:LB, 1:LT, 2:RT, 3:RB
			dRefPos[0][0] = m_AlignPointValue[0][0];
			dRefPos[0][1] = m_AlignPointValue[1][0];

			dRefPos[1][0] = m_AlignPointValue[0][1];
			dRefPos[1][1] = m_AlignPointValue[1][1];

			dRefPos[2][0] = m_AlignPointValue[0][2];
			dRefPos[2][1] = m_AlignPointValue[1][2];

			dRefPos[3][0] = m_AlignPointValue[0][3];
			dRefPos[3][1] = m_AlignPointValue[1][3];


			dActPos[0][0] = m_AlignPointValue[0][0] + m_AlignVisionResultValue[0][0];
			dActPos[0][1] = m_AlignPointValue[1][0] + m_AlignVisionResultValue[1][0];

			dActPos[1][0] = m_AlignPointValue[0][1] + m_AlignVisionResultValue[0][1];
			dActPos[1][1] = m_AlignPointValue[1][1] + m_AlignVisionResultValue[1][1];

			dActPos[2][0] = m_AlignPointValue[0][2] + m_AlignVisionResultValue[0][2];
			dActPos[2][1] = m_AlignPointValue[1][2] + m_AlignVisionResultValue[1][2];

			dActPos[3][0] = m_AlignPointValue[0][3] + m_AlignVisionResultValue[0][3];
			dActPos[3][1] = m_AlignPointValue[1][3] + m_AlignVisionResultValue[1][3];

			Devs::m_InspectionStageMotion.UVWStageAlignMove(_e4Point_Align_Mode, dRefPos, dActPos);
			Sleep(500); //!!

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
		}
		break;
#pragma endregion

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK:
			if (Devs::m_InspectionStageMotion.IsUVWStagePos(m_dDiffPos) == TRUE)
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK);
			}
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS_CHECK);
			}
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_DONE, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK);
			}
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR:
			break;

		case _eMASK_TAGKEY_4P_ALIGN_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("MASK_TAGKEY_4P_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eMASK_TAGKEY_4P_ALIGN_FLOW_IDLE, _T("_eMASK_TAGKEY_4P_ALIGN_FLOW_IDLE"));
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

BOOL CMaskTag4PAlignFlow::GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT)
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

	Total_Msg(_T("Tagkey4PAlign Result X : %.5f, Y : %.5f, T : %.7f"), *ResultX, *ResultY, *ResultT);

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
double CMaskTag4PAlignFlow::GetAlignPos_X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CMaskTag4PAlignFlow::GetAlignPos_Y(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}

BOOL CMaskTag4PAlignFlow::FlowInterlock()
{
	CString Str = _T("");

	//if (SharedInfo::GetServoOnStatus(AXIS_GANTRY_X) != TRUE)
	//{
	//	Total_Msg(_T("Gantry X Servo On Check !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::GetServoOnStatus(AXIS_VIRTUAL_GANTRY_Y) != TRUE)
	//{
	//	Total_Msg(_T("Gantry Y Servo On Check !!!"));
	//	return FALSE;
	//}

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

	return TRUE;
}