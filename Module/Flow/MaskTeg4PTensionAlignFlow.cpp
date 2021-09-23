#include "stdafx.h"
#include "MaskTeg4PTensionAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"
#include "VisionAgentDlg.h"

CMaskTeg4PTensionAlignFlow::CMaskTeg4PTensionAlignFlow()
{
	m_dDiffPos[0] = 0.;
	m_dDiffPos[1] = 0.;
	m_dDiffPos[2] = 0.;

	m_dTarget[0] = 0.;
	m_dTarget[1] = 0.;
	m_dTarget[2] = 0.;

	m_nAlignCnt = 0;
}

CMaskTeg4PTensionAlignFlow::~CMaskTeg4PTensionAlignFlow()
{
}

BOOL CMaskTeg4PTensionAlignFlow::InitProcess()
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
BOOL CMaskTeg4PTensionAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CMaskTeg4PTensionAlignFlow::Start(int nStep)
{
	memset(Devs::m_GantryMotion.m_dTpX, 0, sizeof(Devs::m_GantryMotion.m_dTpX));
	memset(Devs::m_GantryMotion.m_dTpY, 0, sizeof(Devs::m_GantryMotion.m_dTpY));

	m_bLaserFocusUseFlag = FALSE;
	m_bAutoFocusUseFlag = FALSE;

	switch (CModelData::m_PpaPara.Info.nPpaFocusType)
	{
	case eFocusType_Laser:
		m_bLaserFocusUseFlag = TRUE;
		m_bAutoFocusUseFlag = FALSE;
		break;

	case eFocusType_Image:
		m_bLaserFocusUseFlag = FALSE;
		m_bAutoFocusUseFlag = TRUE;
		break;

	case eFocusType_Both:
		m_bLaserFocusUseFlag = TRUE;
		m_bAutoFocusUseFlag = TRUE;
		break;
	}

	m_bFlowDone = FALSE;
	m_bStopBit = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_START"));
	return TRUE;
}
BOOL CMaskTeg4PTensionAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CMaskTeg4PTensionAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CMaskTeg4PTensionAlignFlow* pFlow = NULL;

	pFlow = (CMaskTeg4PTensionAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CMaskTeg4PTensionAlignFlow::ThreadFunctionEntry(VOID)
{
	ERROR_INFO resinfo;
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

	double RefT;
	double NewPositionT;
	double DiffT;
	double dRandNum;

	SYSTEMTIME st;
	int nReF = 0;
	int nIndex = 0;
	CString strTemp = _T("");
	INT nOkCnt = 0;

	double dPosX = 0.0, dPosY = 0.0;

	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IDLE:
		{
			break;
		}
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

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
			/////////

			SharedInfo::AlignCenterDiffInfoLoad(); //!!

			SharedInfo::nGantryZ1View = eViewReview10X;

			m_nAlignCnt = 0;

			//g_CommLight_8ch.SetLight_Review_Coaxial(0);
			//g_CommLight_12ch.SetLight_Review_Ring(0);
			//g_CommLight_8ch.SetLight_PreAlign(0, 0);

			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_AlignPara.Info.nEdge4PAlignBacklight; // 100;

			//g_CommMLCLedLight.BackLightOn(nBackLightVal);

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_INTERLOCK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_INTERLOCK"));
			break;
		}
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR:
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS:
			m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignCnt);
			m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignCnt);			
			
#if 0
			if (m_nAlignCnt == 0 || m_nAlignCnt == 1) //LEFT
			{
				m_dTargetPosX -= SharedInfo::AlignCenterDiffInfo.dDiff_Main2PAlignX;
				Str.Format(_T("Target Pos X:%.5f -> X:%.5f (- AlignCenterDiff X:%.5f)"), dPosX, m_dTargetPosX, SharedInfo::AlignCenterDiffInfo.dDiff_Main2PAlignX);
				Total_Msg(Str);
			}
			else if (m_nAlignCnt == 2 || m_nAlignCnt == 3) //RIGHT
			{
				m_dTargetPosX += SharedInfo::AlignCenterDiffInfo.dDiff_Main2PAlignX;
				Str.Format(_T("Target Pos X:%.5f -> X:%.5f (+ AlignCenterDiff X:%.5f)"), dPosX, m_dTargetPosX, SharedInfo::AlignCenterDiffInfo.dDiff_Main2PAlignX);
				Total_Msg(Str);
			}
			dPosX = m_dTargetPosX;
#endif

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
					SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS"));
				else
					SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS_CHECK);
			}
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS:
			//Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			//Sleep(20); //!!

			//SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS_CHECK"));
			//SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS_CHECK:
			//if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			//{
			//	SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_START, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_START"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS_CHECK);
			//}
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRAB_START, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_CHECK);
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRAB_START, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRAB_START"));
#endif
			break;

#pragma region //PPA Point Align
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRAB_START:
			Devs::m_GantryMotion.FindBlob_TagKey4PAlign_Review10X(&m_AlignVisionResultValue[0][m_nAlignCnt], &m_AlignVisionResultValue[1][m_nAlignCnt]);

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_nAlignCnt, m_AlignVisionResultValue[0][m_nAlignCnt], m_AlignVisionResultValue[1][m_nAlignCnt]);
			Total_Msg(Str);

			if (m_nAlignCnt == 3)
			{
				m_AlignVisionPreResultValue[0][m_nAlignCnt] = m_AlignVisionResultValue[0][m_nAlignCnt];
				m_AlignVisionPreResultValue[1][m_nAlignCnt] = m_AlignVisionResultValue[1][m_nAlignCnt];
				m_nAlignCnt = 0;

				Sleep(100);
				Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], TRUE);

				Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
				Total_Msg(Str);

				if (fabs(m_AlignVisionResultValue[0][0]) < 0.0008 && fabs(m_AlignVisionResultValue[0][1]) < 0.0008 && fabs(m_AlignVisionResultValue[0][2]) < 0.0008 && fabs(m_AlignVisionResultValue[0][3]) < 0.0008 && //X
					fabs(m_AlignVisionResultValue[1][0]) < 0.0008 && fabs(m_AlignVisionResultValue[1][1]) < 0.0008 && fabs(m_AlignVisionResultValue[1][2]) < 0.0008 && fabs(m_AlignVisionResultValue[1][3]) < 0.0008 && //Y
					fabs(m_dDiffPos[2]) <= 0.001) //T
				{
					SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS"));
				}
				else
				{
					SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS"));
				}
			}
			else
			{
				m_AlignVisionPreResultValue[0][m_nAlignCnt] = m_AlignVisionResultValue[0][m_nAlignCnt];
				m_AlignVisionPreResultValue[1][m_nAlignCnt] = m_AlignVisionResultValue[1][m_nAlignCnt];
				m_nAlignCnt++;
				Sleep(1000);
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS"));

			}
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS:
			//Devs::m_GripperZMotion.Move_GripperZ_TensionPos();

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK:
			//if (Devs::m_GripperZMotion.Is_GripperZ_TensionPos())
			//{
			//	SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_START, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_START"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK"));
			//}
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_START:
			Devs::m_StretchMotion.Gripper4PAlignTensionStretchMoveStart(m_AlignVisionResultValue);

			SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_DONE_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_DONE_CHECK:
			if (Devs::m_StretchMotion.Gripper4PAlignTensionStretchMoveDoneCheck())
			{
				Sleep(1000); //!!
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_START, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_DONE_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_DONE_CHECK"));
			}
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_START:
			//Devs::m_PitchMotion.Gripper4PAlignTensionPitchMoveStart(m_AlignVisionResultValue);

			SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_DONE_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_DONE_CHECK:
			if (Devs::m_StretchMotion.Gripper4PAlignTensionStretchMoveDoneCheck())
			{
				Sleep(1000); //!!
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_DONE_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_DONE_CHECK"));
			}
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS:
			//Devs::m_GripperZMotion.Move_GripperZ_ClampPos();

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS_CHECK:
			//if (Devs::m_GripperZMotion.Is_GripperZ_ClampPos())
			//{
			//	SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS_CHECK);
			//}
			break;

#pragma endregion
		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS_CHECK);
			}
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_DONE, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK);
			}
			break;

		case _eTENSION_MAIN_ALIGN_TEG_4P_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("TENSION_MAIN_ALIGN_TEG_4P_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IDLE, _T("_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IDLE"));
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

double CMaskTeg4PTensionAlignFlow::GetAlignPos_X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CMaskTeg4PTensionAlignFlow::GetAlignPos_Y(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}

BOOL CMaskTeg4PTensionAlignFlow::FlowInterlock()
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

	return TRUE;
}