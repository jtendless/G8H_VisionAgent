#include "stdafx.h"
#include "BoxAlignFlow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"
#include "Motion/BoxMotion.h"
#include "Data/ManualData.h"
#include "Data/ModelData.h"
#include "FmmLight1.h"

CBoxAlignFlow::CBoxAlignFlow()
{
	m_dDiffPos[0] = 0.0;
	m_dDiffPos[1] = 0.0;
	m_dDiffPos[2] = 0.0;

	m_dTarget[0] = 0.0;
	m_dTarget[1] = 0.0;
	m_dTarget[2] = 0.0;

	m_AlignCnt = 0;

	m_AlignPointValue[0][0] = -600.0;
	m_AlignPointValue[1][0] = 0.0;

	m_AlignPointValue[0][1] = 600.0;
	m_AlignPointValue[1][1] = 0.0;

	m_AlignVisionResultValue[0][0] = 0.0;
	m_AlignVisionResultValue[1][0] = 0.0;
	m_AlignVisionResultValue[0][1] = 0.0;
	m_AlignVisionResultValue[1][1] = 0.0;
}


CBoxAlignFlow::~CBoxAlignFlow()
{
}

BOOL CBoxAlignFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	m_sGroupInfo[0].m_bProcessingFlag = FALSE;
	m_sGroupInfo[0].nStartStep = _eBOX_ALIGN_FLOW_START;
	m_sGroupInfo[0].nEndStep = _eBOX_ALIGN_FLOW_INTERLOCK_CHECK;
	m_sGroupInfo[0].strGroupName.Format(_T("1. Start - Ready"));

	m_nMaxGroupCount = 4;
#pragma endregion

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	return TRUE;
}
BOOL CBoxAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eBOX_ALIGN_FLOW_IDLE);

	do
	{
		Sleep(10);
	} while (IsTerminate() == 0);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}

	return TRUE;
}
BOOL CBoxAlignFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eBOX_ALIGN_FLOW_START"));
	return TRUE;
}
BOOL CBoxAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CBoxAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CBoxAlignFlow* pFlow = NULL;

	pFlow = (CBoxAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CBoxAlignFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();
	double dVel[3] = { 1.0, 1.0, 1.0 };
	double dAccel[3] = { 2.0, 2.0, 2.0 };
	double dDecel[3] = { 2.0, 2.0, 2.0 };
	CString Str = _T("");
	double dDiffXTemp = 0.0;
	int nRtnLeft, nRtnRight;

	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)AfxGetMainWnd();
	SYSTEMTIME st;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eBOX_ALIGN_FLOW_IDLE); //KJT 20210318
						
			Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT_ON, TRUE);

			continue; //!!
		}
		

		switch (GetCurrentTotalStep())
		{
		case _eBOX_ALIGN_FLOW_IDLE:
		{
			break;
		}
		case _eBOX_ALIGN_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
						
			m_AlignPointValue[0][0] = (CModelData::m_AtMaterialPara.Info.dStickSizeX / 2) * (-1); //-600.0; //KJT 20210308
			m_AlignPointValue[1][0] = 0.0;

			m_AlignPointValue[0][1] = (CModelData::m_AtMaterialPara.Info.dStickSizeX / 2); // 600.0; //KJT 20210308
			m_AlignPointValue[1][1] = 0.0;

			m_AlignVisionResultValue[0][0] = 0.0;
			m_AlignVisionResultValue[1][0] = 0.0;
			m_AlignVisionResultValue[0][1] = 0.0;
			m_AlignVisionResultValue[1][1] = 0.0;

			GetLocalTime(&st);
			m_strFilePath.Format(_T("%s\\Result\\BoxAlign\\BoxAlign_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::VisionAgentPath, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);


			Str.Format(_T("dStickSizeX: %.5f"), CModelData::m_AtMaterialPara.Info.dStickSizeX);
			Total_Msg(Str);

			if (CModelData::m_AtMaterialPara.Info.dStickSizeX < 1.0)
			{
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
				break;
			}

			m_bBoxAlignGrabDone = FALSE;

			SetStep(_eBOX_ALIGN_FLOW_INTERLOCK_CHECK, _T("_eBOX_ALIGN_FLOW_INTERLOCK_CHECK"));
			break;

		case _eBOX_ALIGN_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetAlarm(_T("ERROR : _eBOX_ALIGN_FLOW_INTERLOCK_CHECK"));
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SharedInfo::LightAllOff();
				Sleep(500);

				g_CommLoader_Light.SetLight_Left_Loader(CModelData::m_AlignPara.Info.nBoxAlignLeftRing, CModelData::m_AlignPara.Info.nBoxAlignLeftCoAxial);
				//g_CommLight_8ch.SetLight_BoxAlignL(CModelData::m_AlignPara.Info.nBoxAlignLeftCoAxial, CModelData::m_AlignPara.Info.nBoxAlignLeftRing);
				Sleep(20);
				//g_CommLight_8ch.SetLight_BoxAlignR(CModelData::m_AlignPara.Info.nBoxAlignRightCoAxial, CModelData::m_AlignPara.Info.nBoxAlignRightRing);
				g_CommLoader_Light.SetLight_Right_Loader(CModelData::m_AlignPara.Info.nBoxAlignRightRing, CModelData::m_AlignPara.Info.nBoxAlignRightCoAxial);
				Sleep(20);
								
				Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT_ON, FALSE);
				Sleep(20);
				
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE)
					SetStep(_eBOX_ALIGN_FLOW_LOADER_Z_READY, _T("_eBOX_ALIGN_FLOW_LOADER_Z_READY"));
				else
					SetStep(_eBOX_ALIGN_FLOW_UNLOADER_READY, _T("_eBOX_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eBOX_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eBOX_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eBOX_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY, _T("_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_UNLOADER_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 3);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eBOX_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZXY Ready
		case _eBOX_ALIGN_FLOW_GANTRY_ZXY_READY:
			Devs::m_Ready_GantryAvoidBoxFlow.Start();

			SetStep(_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY_CHECK, _T("_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_GANTRY_ZXY_READY_CHECK:
			if (Devs::m_Ready_GantryAvoidBoxFlow.IsFlowDone())
			{
				SetStep(_eBOX_ALIGN_FLOW_LOADER_Z_READY, _T("_eBOX_ALIGN_FLOW_LOADER_Z_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 4);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY_CHECK, _T("_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eBOX_ALIGN_FLOW_LOADER_Z_READY:
			//Devs::m_Ready_LoaderZXFlow.Start();
			Devs::m_LoaderMotion.LoaderZ_WaitPos();
			Sleep(10); //!!
						
			SetStep(_eBOX_ALIGN_FLOW_LOADER_Z_READY_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_Z_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_LOADER_Z_READY_CHECK:
			//if (Devs::m_Ready_LoaderZXFlow.IsFlowDone())
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				SetStep(_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY, _T("_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_LOADER_Z_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_LOADER_SUB_Z_UP_CHECK"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_LOADER_Z_READY_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_Z_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY:
			Devs::m_Ready_PaperUnloaderZXFlow.Start();

			SetStep(_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY_CHECK, _T("_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderZXFlow.IsFlowDone())
			{
				SetStep(_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS, _T("_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY_CHECK, _T("_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY_CHECK"));
			}
			break;

		case _eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS:
			m_dPrevPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
			if (m_dPrevPos < CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Waiting_Pos)
			{
				Devs::m_UnloaderMotion.PaperUnloaderY_All_LoadPaperWaitingPos();
				Sleep(20);
				SetStep(_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS_CHECK, _T("_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS_CHECK"));
			}
			else
			{
				Devs::m_UnloaderMotion.PaperUnloaderY_All_LoadPaperWaitingPos();
				Sleep(20);
				SetStep(_eBOX_ALIGN_FLOW_UVW_WAIT_POS, _T("_eBOX_ALIGN_FLOW_UVW_WAIT_POS"));
			}
			break;

		case _eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS_CHECK:
			m_dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
			if (m_dCurPos > m_dPrevPos + 100.0)
			{
				SetStep(_eBOX_ALIGN_FLOW_UVW_WAIT_POS, _T("_eBOX_ALIGN_FLOW_UVW_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS_CHECK, _T("_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS_CHECK"));
			}
			break;
#pragma endregion

		case _eBOX_ALIGN_FLOW_UVW_WAIT_POS: //KJT 20210316
			Devs::m_BoxMotion.LoadingStageUVW_WaitPos();
			Sleep(10);

			SetStep(_eBOX_ALIGN_FLOW_UVW_WAIT_POS_CHECK, _T("_eBOX_ALIGN_FLOW_UVW_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_UVW_WAIT_POS_CHECK:
			if (Devs::m_BoxMotion.Is_LoadingStageUVW_WaitPos())
			{
				SetStep(_eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS, _T("_eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_UVW_WAIT_POS_CHECK : Time Out"), eBOX_ALIGN_FLOW + 6);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_UVW_WAIT_POS_CHECK, _T("_eBOX_ALIGN_FLOW_UVW_WAIT_POS_CHECK"));
			}
			break;

		case _eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS:
			Devs::m_LoaderMotion.LoaderY_Inspection_Pos();

			SetStep(_eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_Inspection_Pos())
			{
				m_nGrabRetryCount = 0;
				SetStep(_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS, _T("_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_LOADER_Y_INSPECTION_POS_CHECK : Time Out"), eBOX_ALIGN_FLOW + 7);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS_CHECK"));
			}
			break;

		case _eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS:
			Devs::m_LoaderMotion.LoaderX_AlignPos();

			SetStep(_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_AlignPos())
			{
				m_nGrabRetryCount = 0;
				SetStep(_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS, _T("_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS_CHECK : Time Out"), eBOX_ALIGN_FLOW + 7);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS_CHECK"));
			}
			break;

		case _eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS:
			//21.02.26 sjc temp del
			Devs::m_LoaderMotion.LoaderZ_Inspection_Pos();

			SetStep(_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS_CHECK:
			//21.02.26 sjc temp del
			if (Devs::m_LoaderMotion.Is_LoaderZ_Inspection_Pos())			
			{
				m_nGrabRetryCount = 0;
				SetStep(_eBOX_ALIGN_FLOW_GRAB_START, _T("_eBOX_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS_CHECK : Time Out"), eBOX_ALIGN_FLOW + 8);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS_CHECK"));
			}
			break;
		case _eBOX_ALIGN_FLOW_GRAB_START:
			nRtnLeft = Devs::m_BoxMotion.FindBoxAlignPattern_Left(&m_AlignVisionResultValue[0][0], &m_AlignVisionResultValue[1][0]);
			nRtnRight = Devs::m_BoxMotion.FindBoxAlignPattern_Right(&m_AlignVisionResultValue[0][1], &m_AlignVisionResultValue[1][1]);

			if (nRtnLeft == FALSE || nRtnRight == FALSE)
			{				
				Total_Msg(_T("FindBoxAlignPattern Error"));
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_GRAB_START : Find Error !!"), eBOX_ALIGN_FLOW + 9);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
				break;
			}			

			Str.Format(_T("Diff Left X:%.5f, Y:%.5f, Right X:%.5f, Y:%.5f"), m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1]);
			//Total_Msg(Str);
			Vision_Msg(Str);

			Devs::m_BoxMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], TRUE);

			Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
			//Total_Msg(Str);
			Vision_Msg(Str);

#pragma region //Retry Interlock
			if (m_nGrabRetryCount < 3 && (fabs(m_AlignVisionResultValue[1][0]) > 6.5 || fabs(m_AlignVisionResultValue[1][1]) > 6.5))
			{
				Sleep(500);
				Str.Format(_T("Grab Error !! Retry (%d/3)!!"), m_nGrabRetryCount + 1);
				Total_Msg(Str);
				m_nGrabRetryCount++;
				SetStep(_eBOX_ALIGN_FLOW_GRAB_START, _T("_eBOX_ALIGN_FLOW_GRAB_START"));
				break;
			}
			else if (m_nGrabRetryCount >= 3)
			{
				Str.Format(_T("Grab Error !! Retry Over (%d/3)!!"), m_nGrabRetryCount);
				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_GRAB_START : Find Error !!"), eBOX_ALIGN_FLOW + 10);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
				break;
			}
#pragma endregion

			dDiffXTemp = m_AlignVisionResultValue[0][0] + m_AlignVisionResultValue[0][1];
			Str.Format(_T("Target_X : %.5f, Target_Y : %.5f, %.5f,  Diff_X:%.5f"), CModelData::m_AlignPara.Info.dBoxAlignLeftTargetX, 
				CModelData::m_AlignPara.Info.dBoxAlignLeftTargetY, CModelData::m_AlignPara.Info.dBoxAlignRightTargetY, dDiffXTemp);
			//Total_Msg(Str);
			Vision_Msg(Str);

			if (dDiffXTemp < CModelData::m_AlignPara.Info.dBoxAlignLeftTargetX && //X
				fabs(m_AlignVisionResultValue[1][0]) < CModelData::m_AlignPara.Info.dBoxAlignLeftTargetY && 
				fabs(m_AlignVisionResultValue[1][1]) < CModelData::m_AlignPara.Info.dBoxAlignRightTargetY && //Y
				fabs(m_dDiffPos[2]) < 0.1)
			{
				SaveBoxAlignResult();

				//21.03.01 sjc
				//g_CommLight_8ch.SetLight_BoxAlignL(0, 0);
				//Sleep(20);
				//g_CommLight_8ch.SetLight_BoxAlignR(0, 0);
				//Sleep(20);
				g_CommLoader_Light.SetLight_Left_Loader(0, 0);
				Sleep(20);
				g_CommLoader_Light.SetLight_Right_Loader(0, 0);

				Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT_ON, FALSE);

				SetStep(_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND, _T("_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND"));
			}
			else
			{
				SetStep(_eBOX_ALIGN_FLOW_UVW_MOVE_START, _T("_eBOX_ALIGN_FLOW_UVW_MOVE_START"));
			}
			break;

		case _eBOX_ALIGN_FLOW_UVW_MOVE_START:
		{
			double dRefPos[4][2] = { 0.0, };
			double dActPos[4][2] = { 0.0, };

			//0:LB, 1:LT, 2:RT, 3:RB(Usage : LT, RT)
			dRefPos[0][0] = m_AlignPointValue[0][0]; //X
			dRefPos[0][1] = m_AlignPointValue[1][0]; //Y

			dRefPos[1][0] = 0.0;
			dRefPos[1][1] = 0.0;

			dRefPos[2][0] = 0.0;
			dRefPos[2][1] = 0.0;

			dRefPos[3][0] = m_AlignPointValue[0][1];//X
			dRefPos[3][1] = m_AlignPointValue[1][1];//Y



			dActPos[0][0] = dRefPos[0][0] + m_AlignVisionResultValue[0][0];
			dActPos[0][1] = dRefPos[0][1] + m_AlignVisionResultValue[1][0];

			dActPos[1][0] = dRefPos[1][0];
			dActPos[1][1] = dRefPos[1][1];

			dActPos[2][0] = dRefPos[2][0];
			dActPos[2][1] = dRefPos[2][1];

			dActPos[3][0] = dRefPos[3][0] + m_AlignVisionResultValue[0][1];
			dActPos[3][1] = dRefPos[3][1] + m_AlignVisionResultValue[1][1];

			//Usage : LT, RT(Horizontal Align)
			Devs::m_BoxMotion.UVWStageAlignMove(_eHorizontal_Align_Mode, dRefPos, dActPos);
			Sleep(100); //!!

			SetStep(_eBOX_ALIGN_FLOW_UVW_MOVE_CHECK, _T("_eBOX_ALIGN_FLOW_UVW_MOVE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);	
		}
			break;

		case _eBOX_ALIGN_FLOW_UVW_MOVE_CHECK:
			if (Devs::m_BoxMotion.IsUVWStagePos(m_dDiffPos) == TRUE)
			{
				SetStep(_eBOX_ALIGN_FLOW_GRAB_START, _T("_eBOX_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_UVW_MOVE_CHECK : Time Out"), eBOX_ALIGN_FLOW + 11);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_UVW_MOVE_CHECK, _T("_eBOX_ALIGN_FLOW_UVW_MOVE_CHECK"));
			}
			break;

		case _eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND:
			Devs::m_LoaderMotion.LoaderZ_WaitPos();
			Sleep(10); //!!

			SetStep(_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				SetStep(_eBOX_ALIGN_FLOW_DONE, _T("_eBOX_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND_CHECK : Time Out"), eBOX_ALIGN_FLOW + 12);
				SetStep(_eBOX_ALIGN_FLOW_ERROR, _T("_eBOX_ALIGN_FLOW_LOADER_SUB_Z_UP_CHECK"));
			}
			else
			{
				SetCheckStep(_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND_CHECK, _T("_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND_CHECK"));
			}
			break;

		case _eBOX_ALIGN_FLOW_ERROR:
			Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT_ON, TRUE);
			break;

		case _eBOX_ALIGN_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eBOX_ALIGN_FLOW; //KJT 20210326

			Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT_ON, TRUE);
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("BOX_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eBOX_ALIGN_FLOW_IDLE, _T("_eBOX_ALIGN_FLOW_IDLE"));
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

BOOL CBoxAlignFlow::FlowInterlock()
{
	CString Str = _T("");

#ifndef SIM_MODE
	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("BoxAlignFlow"), eBOX_ALIGN_FLOW, 30) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("BoxAlignFlow"), eBOX_ALIGN_FLOW, 50) == FALSE)
	{
		return FALSE;
	}

	//21.02.04 sjc no jig lock sensor
	//if (SharedInfo::DInputValue[BOX_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Box Stage Jig Lock Sensor !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[PAPER_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Paper Jig Lock Sensor !!!"));
	//	return FALSE;
	//}

	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	Total_Msg(_T("Check Pickup Unit Backward !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_2] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Unsafe Pos Detect Sensor !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_1] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Backward Detect Sensor !!!"));
	//	return FALSE;
	//}
	//21.02.04 sjc no box cam servo
	//if (SharedInfo::GetServoOnStatus(AXIS_BOX_ALIGN_CAMERA_YL) != TRUE)
	//{
	//	Total_Msg(_T("Box Align YL Servo On Check !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::GetServoOnStatus(AXIS_BOX_ALIGN_CAMERA_YR) != TRUE)
	//{
	//	Total_Msg(_T("Box Align YR Servo On Check !!!"));
	//	return FALSE;
	//}
#endif

	return TRUE;
}


int CBoxAlignFlow::SaveBoxAlignResult()
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
			StrTitle.Format(_T("Date, Left_Target_X, Left_Target_Y, Right_Target_X, Right_Target_Y, Left_Diff_X, Left_Diff_Y, Right_Diff_X, Right_Diff_Y\n"));
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
	str.AppendFormat(_T("%.5f,"), CModelData::m_AlignPara.Info.dBoxAlignLeftTargetX);
	str.AppendFormat(_T("%.5f,"), CModelData::m_AlignPara.Info.dBoxAlignLeftTargetY);
	str.AppendFormat(_T("%.5f,"), CModelData::m_AlignPara.Info.dBoxAlignRightTargetX);
	str.AppendFormat(_T("%.5f,"), CModelData::m_AlignPara.Info.dBoxAlignRightTargetY);

	str.AppendFormat(_T("%.5f,"), m_AlignVisionResultValue[0][0]);
	str.AppendFormat(_T("%.5f,"), m_AlignVisionResultValue[1][0]);
	str.AppendFormat(_T("%.5f,"), m_AlignVisionResultValue[0][1]);
	str.AppendFormat(_T("%.5f,"), m_AlignVisionResultValue[1][1]);
	
	f.WriteString(str);
	f.Close();

	return 0;
}