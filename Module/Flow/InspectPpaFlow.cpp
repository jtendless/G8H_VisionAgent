/******************************************************************************
* @file     InspectPpaFlow.cpp
* @date     
* @history
*
******************************************************************************/

#include "stdafx.h"
#include "InspectPpaFlow.h"
#include "VisionAgentDlg.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "FmmLight1.h"

//#include "../Module/Object/ProcessStep.h"
//#include "../Module/Vision/MappingProc.h"



CInspectPpaFlow::CInspectPpaFlow()
{
	m_nAllPpaMaskCnt = 0;

	m_nRepeatCount = 0;
}

CInspectPpaFlow::~CInspectPpaFlow()
{

}

BOOL CInspectPpaFlow::MotionDone()
{
	return m_bMotionDone;

}

BOOL CInspectPpaFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_StateFinish = TRUE;
	m_bTerminate = FALSE;
	m_bMotionDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eINSPECT_PPA_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eINSPECT_PPA_FLOW_INTERLOCK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eINSPECT_PPA_FLOW_GANTRY_ZX_READY_CHECK;
	m_sGroupInfo[nGroupIndex].nEndStep = _eINSPECT_PPA_FLOW_UNLOADER_READY;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Other Axis Ready"), nGroupIndex + 1);
	nGroupIndex++;

	m_nMaxGroupCount = nGroupIndex;
#pragma endregion

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);
	
	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);

	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);

		
	return TRUE;
}

BOOL CInspectPpaFlow::EndProcess()
{
	m_StateFinish = FALSE;

	SetStep(_eINSPECT_PPA_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CInspectPpaFlow::Start(enum_PPA_Type PPAIndex, int nStep, int nRepeat/* = 0*/)
{		
	memset(Devs::m_GantryMotion.m_dTpX, 0, sizeof(Devs::m_GantryMotion.m_dTpX));
	memset(Devs::m_GantryMotion.m_dTpY, 0, sizeof(Devs::m_GantryMotion.m_dTpY));

	m_nKindOfPpaIndex = PPAIndex;

	m_nRepeatCount = nRepeat;
	m_nCurRepeatCount = 0;

	m_bMotionDone = FALSE;
	m_bStopBit = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eINSPECT_PPA_FLOW_START"));
	return TRUE;
}
BOOL CInspectPpaFlow::Stop()
{
	Devs::m_GantryMotion.Stop();
	
	//m_bMotionDone = FALSE;
	SharedInfo::bMachineStopFlag = TRUE;
	//SharedInfo::MachineState.bSemiAutoRunFlag = FALSE;
	return TRUE;
}
UINT CInspectPpaFlow::ThreadFunction(LPVOID lpParam)
{
	CInspectPpaFlow* pInspectPpaFlow = NULL;

	pInspectPpaFlow = (CInspectPpaFlow*)lpParam;

	pInspectPpaFlow->ThreadFunctionEntry();

	pInspectPpaFlow->m_bTerminate = 1;

	return 0;
}


VOID CInspectPpaFlow::ThreadFunctionEntry(VOID)
{
	ERROR_INFO resinfo;
	double DiffPosition[3] = { 0, };

	double dUVWX[3];
	double AlignError[2], TargetError, ErrorResult;


	double dPosX;
	double dPosY;
	double dPosZ = 0.0;

	CString str;
	double R;
	BOOL bResult, bMoveEnd, bFirstMask = FALSE;


	int CellCntX, CellCntY;
	int nActualStick;

	double RefT;
	double NewPositionT;
	double DiffT;
	double dRandNum;
	m_nGrabRetryCnt = 0;
	SYSTEMTIME st;
	int nReF = 0;
	int nIndex = 0;
	CString strTemp = _T(""), Str = _T("");
	INT nOkCnt = 0;
	BOOL bRtn = FALSE;

	double dCellSumData[100][2];
	int nMaskFigure = 0;
#ifndef SIM_MODE
	//CCalcu Calcu; //KJT 20210430 Hide
#endif

	int nRing = 0, nCoaxial = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	while (m_StateFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eINSPECT_PPA_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eINSPECT_PPA_FLOW_IDLE:
		{
			break;
		}

		case _eINSPECT_PPA_FLOW_START:

			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = ePPA_FLOW;

			//KJT 20210402
			bRtn = SharedInfo::FindFloorSlotUnloadToCst(&m_eTargetFloor/*, &m_eTargetSlot*/);
			if (bRtn == FALSE)
			{
				m_eTargetFloor = eCASSETTE_FLOOR_NONE;
				//m_eTargetSlot = eCASSETTE_SLOT_NONE;
				//Total_Msg(_T("PPA After Cst Target Floor, Slot Unknown !!"));
				Total_Msg(_T("PPA After Cst Target Floor Unknown !!"));
				//break; //KJT 20210412 Hide
			}

			//Awking 저장 Path 위치 이동.	
			m_bDirectionFlag = FALSE;
			nIndex = 0;
			GetLocalTime(&st);
			TCHAR	exepath[MAX_PATH];
			GetModuleFileName(NULL, exepath, sizeof(exepath));
			m_path = exepath;
			nReF = m_path.ReverseFind('\\');
			m_path = m_path.Left(nReF);
			m_logpath = m_path;

			//KJT 20210402
			switch (m_nKindOfPpaIndex)
			{
			case eNORAML_PPA:
				m_path.AppendFormat(_T("\\Result\\NormalPPA\\NormalPPA_%s_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::Active.tchStickId, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				m_logpath.AppendFormat(_T("\\Result\\NormalPPA\\NormalPPA_%s_%04d%02d%02d.log"), SharedInfo::Active.tchStickId, st.wYear, st.wMonth, st.wDay);
				//m_strDfsFileName.Format(_T("[Inspect]_InspectPPA.csv"));
				//m_strDfsFileName = SharedInfo::GetDfsFileName(m_strDfsFileName);

				break;

			case eAT_PPA:
				m_path.AppendFormat(_T("\\Result\\ATPPA\\AtPPA_%s_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::Active.tchStickId, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				m_logpath.AppendFormat(_T("\\Result\\ATPPA\\AtPPA_%s_%04d%02d%02d.log"), SharedInfo::Active.tchStickId, st.wYear, st.wMonth, st.wDay);
				//m_strDfsFileName.Format(_T("[Sheet%02d]_ClampOffPPA.csv"), m_nActiveStick + 1);
				//m_strDfsFileName = SharedInfo::GetDfsFileName(m_strDfsFileName);

				break;
			}
			//ERROR_INFO resinfo;
			//SavePpaResult(resinfo);

			memset(m_ResultIndividual_CdX, 0x0, sizeof(m_ResultIndividual_CdX));
			memset(m_ResultIndividual_CdY, 0x0, sizeof(m_ResultIndividual_CdY));

			SharedInfo::LightAllOff();

#if 0
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_PpaPara.Info.nPpaBacklight;

			nRing = CModelData::m_PpaPara.Info.nPpaRing;
			nCoaxial = CModelData::m_PpaPara.Info.nPpaCoAxial;

			//Sleep(500);
			//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_PpaPara.Info.nPpaCoAxial);
			//Sleep(30);
			//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_PpaPara.Info.nPpaRing);
			//Sleep(30);
			//g_CommMLCLedLight.BackLightOn(nBackLightVal);

			if (CModelData::m_PpaPara.Info.nPpaLightType == eLight_Back)
			{
				if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
				{
					for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
						nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx20BackLightScale;
				}
				else if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview50X)
				{
					for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
						nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx50BackLightScale;
				}

				g_CommBack_Light.BackLightOn(nBackLightVal);
				Sleep(30);
			}
			else
			{
				if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
				{
					nRing *= CModelData::m_AlignPara.Info.dx20RingScale;
					nCoaxial *= CModelData::m_AlignPara.Info.dx20CoAxialScale;
				}
				else if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview50X)
				{
					nRing *= CModelData::m_AlignPara.Info.dx50RingScale;
					nCoaxial *= CModelData::m_AlignPara.Info.dx50CoAxialScale;
				}

				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(30);
			}
#else //KJT 20210824
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_PpaPara.Info.nPpaBacklight[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

			nRing = CModelData::m_PpaPara.Info.nPpaRing[CModelData::m_InspectionPara.Info.nMeasureCameraMode];
			nCoaxial = CModelData::m_PpaPara.Info.nPpaCoAxial[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

			if (CModelData::m_PpaPara.Info.nPpaLightType == eLight_Back)
			{
				g_CommBack_Light.BackLightOn(nBackLightVal);
				Sleep(30);
			}
			else
			{
				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(30);
			}
#endif

			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					Alarm_Msg(_T("LoadGlassMappingFile Fail !!"));
					SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_START : Mapping Data"), ePPA_FLOW + 0);
					SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
					break;
				}
			}			
			
			SetStep(_eINSPECT_PPA_FLOW_INTERLOCK, _T("_eINSPECT_PPA_FLOW_INTERLOCK"));
			break;

		case _eINSPECT_PPA_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
			}
			else
			{
				//if (SharedInfo::MachineState.bAutoRunFlag == TRUE && (SharedInfo::nPrevFlowID == eTP_FLOW || SharedInfo::nPrevFlowID == eMAIN_ALIGN_FLOW))
				//{
				//	if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse == TRUE)
				//		SetStep(_eINSPECT_PPA_FLOW_SW_ALIGN_START, _T("_eINSPECT_PPA_FLOW_SW_ALIGN_START"));
				//	else
				//		SetStep(_eINSPECT_PPA_FLOW_PPA_POS_CALC, _T("_eINSPECT_PPA_FLOW_PPA_POS_CALC"));
				//}
				//else
					SetStep(_eINSPECT_PPA_FLOW_UNLOADER_READY, _T("_eINSPECT_PPA_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eINSPECT_PPA_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eINSPECT_PPA_FLOW_UNLOADER_READY_CHECK, _T("_eINSPECT_PPA_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eINSPECT_PPA_FLOW_GANTRY_ZX_READY, _T("_eINSPECT_PPA_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_UNLOADER_READY_CHECK : Time Out"), ePPA_FLOW + 1);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_UNLOADER_READY_CHECK, _T("_eINSPECT_PPA_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case _eINSPECT_PPA_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eINSPECT_PPA_FLOW_GANTRY_ZX_READY_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eINSPECT_PPA_FLOW_LOADER_READY, _T("_eINSPECT_PPA_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), ePPA_FLOW + 4);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_ZX_READY_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eINSPECT_PPA_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eINSPECT_PPA_FLOW_LOADER_READY_CHECK, _T("_eINSPECT_PPA_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_LOADER_READY_CHECK : Time Out"), ePPA_FLOW + 2);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_LOADER_READY_CHECK, _T("_eINSPECT_PPA_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse == TRUE)
					SetStep(_eINSPECT_PPA_FLOW_SW_ALIGN_START, _T("_eINSPECT_PPA_FLOW_SW_ALIGN_START"));
				else
					SetStep(_eINSPECT_PPA_FLOW_PPA_POS_CALC, _T("_eINSPECT_PPA_FLOW_PPA_POS_CALC"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eINSPECT_PPA_FLOW_SW_ALIGN_START:
			Devs::m_SwAlignFlow.m_eSwAlignType = eSwAlign_EdgeSlot; //KJT 20210419
			Devs::m_SwAlignFlow.Start(Devs::m_SwAlignFlow._eSW_ALIGN_FLOW_START);

			SetStep(_eINSPECT_PPA_FLOW_SW_ALIGN_DONE_CHECK, _T("_eINSPECT_PPA_FLOW_SW_ALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eINSPECT_PPA_FLOW_SW_ALIGN_DONE_CHECK:					
			if (Devs::m_SwAlignFlow.IsFlowDone())
			{
#if 0
				for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
					nBackLightVal[i] = CModelData::m_PpaPara.Info.nPpaBacklight;

				nRing = CModelData::m_PpaPara.Info.nPpaRing;
				nCoaxial = CModelData::m_PpaPara.Info.nPpaCoAxial;				

				if (CModelData::m_PpaPara.Info.nPpaLightType == eLight_Back)
				{
					if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
					{
						for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
							nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx20BackLightScale;
					}
					else if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview50X)
					{
						for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
							nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx50BackLightScale;
					}

					g_CommBack_Light.BackLightOn(nBackLightVal);
					Sleep(30);
				}
				else
				{
					if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
					{
						nRing *= CModelData::m_AlignPara.Info.dx20RingScale;
						nCoaxial *= CModelData::m_AlignPara.Info.dx20CoAxialScale;
					}
					else if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview50X)
					{
						nRing *= CModelData::m_AlignPara.Info.dx50RingScale;
						nCoaxial *= CModelData::m_AlignPara.Info.dx50CoAxialScale;
					}

					g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
					Sleep(30);
				}
#else //KTJ 20210824
				for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
					nBackLightVal[i] = CModelData::m_PpaPara.Info.nPpaBacklight[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

				nRing = CModelData::m_PpaPara.Info.nPpaRing[CModelData::m_InspectionPara.Info.nMeasureCameraMode];
				nCoaxial = CModelData::m_PpaPara.Info.nPpaCoAxial[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

				if (CModelData::m_PpaPara.Info.nPpaLightType == eLight_Back)
				{
					g_CommBack_Light.BackLightOn(nBackLightVal);
					Sleep(30);
				}
				else
				{
					g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
					Sleep(30);
				}
#endif

				SetCheckStep(_eINSPECT_PPA_FLOW_PPA_POS_CALC, _T("_eINSPECT_PPA_FLOW_PPA_POS_CALC"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_SW_ALIGN_DONE_CHECK : Time Out"), ePPA_FLOW + 5);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_SW_ALIGN_DONE_CHECK, _T("_eINSPECT_PPA_FLOW_SW_ALIGN_DONE_CHECK"));
			}
			break;
			
#pragma region //Gantry XYZ First Pos Move
		case _eINSPECT_PPA_FLOW_PPA_POS_CALC: //KJT 20210305
			if (m_nKindOfPpaIndex == eAT_PPA)
				bResult = Devs::m_GantryMotion.MakeAtPpaPosition(CModelData::m_PpaPara.Info.nDivX + 1, CModelData::m_PpaPara.Info.nDivY + 1);
			else
				bResult = Devs::m_GantryMotion.MakeNormalPpaPosition(CModelData::m_PpaPara.Info.nDivX + 1, CModelData::m_PpaPara.Info.nDivY + 1);

			if (bResult == FALSE)
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_PPA_POS_CALC : Calc Error"), ePPA_FLOW + 6);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			
			m_nResultIndex = 0;
			//m_vPPApList = Devs::m_GantryMotion.m_vPPApList;
			//m_vPPApResultList = Devs::m_GantryMotion.m_vPPApResultList;

			m_nCellIndexX = 0;
			m_nCellIndexY = 0;
			m_nPatIndexX = 0;
			m_nPatIndexY = 0;
			m_bDirectionFlag = FALSE;
			m_nPpaIndex = 0;
			m_nMaxPpaCount = Devs::m_GantryMotion.m_nMaxPpaCnt;
		
			SetStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
			break;

		case _eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST:
			m_dTargetPosX = dPosX = Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dPosX;
			m_dTargetPosY = dPosY = Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dPosY;
			
			if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			{
				Devs::m_GantryMotion.ConvertTo20XPos(&m_dTargetPosX, &m_dTargetPosY);
			}

			//SharedInfo::GetMappingPos(CModelData::m_InspectionPara.Info.bAlignDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312
			SharedInfo::GetMappingPos(CModelData::m_InspectionPara.Info.bSWAlignFlowUse, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312
		
			m_AlignPointValue[0] = m_dTargetPosX;
			m_AlignPointValue[1] = m_dTargetPosY;
						
			m_dMappingMovePosX = m_AlignPointValue[0];
			m_dMappingMovePosY = m_AlignPointValue[1];
			
			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20);
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);

			SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (CModelData::m_PpaPara.Info.nPpaLightType == eLight_Back)
				{
					if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
					{
						SetStep(_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK"));
					}
					else
						SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
				}
				else
				{
					SetStep(_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK : Time Out"), ePPA_FLOW + 7);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			}
			break;

#if 0 //KJT 20210724 Not Use
		case _eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(500); //!!

				SetStep(_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK : Time Out"), ePPA_FLOW + 8);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK"));
			}
			break;
#endif
#pragma endregion

#if 0 //KJT 20210313 //Not Use
		case _eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_2ND:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				SetStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK"));
			}
			break;
#endif

		case _eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND:
			m_dTargetPosX = dPosX = Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dPosX;
			m_dTargetPosY = dPosY = Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dPosY;

			if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			{
				Devs::m_GantryMotion.ConvertTo20XPos(&m_dTargetPosX, &m_dTargetPosY);
			}

			//SharedInfo::GetMappingPos(CModelData::m_InspectionPara.Info.bAlignDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312
			SharedInfo::GetMappingPos(CModelData::m_InspectionPara.Info.bSWAlignFlowUse, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312

			m_AlignPointValue[0] = m_dTargetPosX;
			m_AlignPointValue[1] = m_dTargetPosY;

			m_dMappingMovePosX = m_AlignPointValue[0];
			m_dMappingMovePosY = m_AlignPointValue[1];

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20);
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);

			SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (CModelData::m_PpaPara.Info.nPpaLightType == eLight_Back)
				{
					if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
					{
						Sleep(500); //!!

						SetStep(_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK"));
					}
					else
						SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
				}
				else
				{
					SetStep(_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK : Time Out"), ePPA_FLOW + 9);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			}
			break;

		case _eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK:
			if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Both || CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Laser)
				SetStep(_eINSPECT_PPA_FLOW_LASER_FOCUS_START, _T("_eINSPECT_PPA_FLOW_LASER_FOCUS_START"));
			else if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Image)
				SetStep(_eINSPECT_PPA_FLOW_IMAGE_FOCUS_START, _T("_eINSPECT_PPA_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(_eINSPECT_PPA_FLOW_GRAB_START, _T("_eINSPECT_PPA_FLOW_GRAB_START"));
			break;

		case _eINSPECT_PPA_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(_eINSPECT_PPA_FLOW_LASER_FOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_AlignPara.Info.nMain2PAlignFocusType == eFocusType_Both)
					SetStep(_eINSPECT_PPA_FLOW_IMAGE_FOCUS_START, _T("_eINSPECT_PPA_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eINSPECT_PPA_FLOW_GRAB_START, _T("_eINSPECT_PPA_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_LASER_FOCUS_CHECK : Time Out"), ePPA_FLOW + 10);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_LASER_FOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eINSPECT_PPA_FLOW_IMAGE_FOCUS_START:
			Total_Msg(_T("Auto Focus Start"));		

#ifndef SIM_MODE
			//if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			//{
			//	g_pReview20x->m_bAfEnd = FALSE;
			//	g_pReview20x->AutofoucsRun(eViewReview20X);
			//	Sleep(100);
			//}
			//else
			{
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
				Sleep(100);
			}
#endif
			SetCheckStep(_eINSPECT_PPA_FLOW_IMAGE_FOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_DUAL);
			break;

		case _eINSPECT_PPA_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			//if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			//{
			//	bResult = g_pReview20x->m_bAfEnd;
			//}
			//else
			{
				bResult = g_pReview10x->m_bAfEnd;
			}			
#else
			bResult = TRUE;
#endif
			if (bResult == TRUE)
			{
				SetStep(_eINSPECT_PPA_FLOW_GRAB_START, _T("_eINSPECT_PPA_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_IMAGE_FOCUS_CHECK : Time Out"), ePPA_FLOW + 11);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_IMAGE_FOCUS_CHECK, _T("_eINSPECT_PPA_FLOW_IMAGE_FOCUS_CHECK"));
			}
			break;

		case  _eINSPECT_PPA_FLOW_GRAB_START:
#ifndef SIM_MODE
			//if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			//{
			//	m_CameraInfo = Devs::m_Camera20X->GetCameraInfo();
			//	m_CameraInfo.nBlackWhite = CModelData::m_PpaPara.Info.nPpaBlackWhiteType;
			//	m_CameraInfo.nBin = CModelData::m_PpaPara.Info.nPpaThreshold;
			//	Devs::m_Camera20X->SetCameraInfo(m_CameraInfo);
			//	m_BlobData = Devs::m_Camera20X->GetBlobData();

			//	if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
			//	{
			//		m_BlobData.dMarkSizeX = CModelData::m_AtMaterialPara.Info.dSlotSizeX[0][0];
			//		m_BlobData.dMarkSizeY = CModelData::m_AtMaterialPara.Info.dSlotSizeY[0][0];
			//		m_BlobData.dPitchX = CModelData::m_AtMaterialPara.Info.dSlotPitchX[0][0];
			//		m_BlobData.dPitchY = CModelData::m_AtMaterialPara.Info.dSlotPitchY[0][0];
			//	}
			//	else
			//	{
			//		m_BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
			//		m_BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
			//		m_BlobData.dPitchX = CModelData::m_MaterialPara.Info.dSlotPitchX[0][0];
			//		m_BlobData.dPitchY = CModelData::m_MaterialPara.Info.dSlotPitchY[0][0];
			//	}

			//	//KJT 20210308
			//	//m_BlobData.nQuantityX = CModelData::m_PpaPara.Info.nDivX + 1; //KJT 20210726
			//	//m_BlobData.nQuantityY = CModelData::m_PpaPara.Info.nDivY + 1;
			//	SharedInfo::GetSlotQtyXY(&m_BlobData.nQuantityX, &m_BlobData.nQuantityY);

			//	m_BlobData.dRangeRateX = 0.8;
			//	m_BlobData.dRangeRateY = 0.8;

			//	Devs::m_Camera20X->SetBlobData(m_BlobData);
			//	stResult = Devs::m_Camera20X->FindBlobPpa();
			//}
			//else
			{
				m_CameraInfo = Devs::m_Camera10X->GetCameraInfo();
				m_CameraInfo.nBlackWhite = CModelData::m_PpaPara.Info.nPpaBlackWhiteType;
				m_CameraInfo.nBin = CModelData::m_PpaPara.Info.nPpaThreshold[CModelData::m_InspectionPara.Info.nStickTensionUseMode]; //KJT 20210824

#if 0//KJT 20210728 Junying
				double dResX = 0.0, dResY = 0.0;
				SharedInfo::GetReviewCamResolution(SharedInfo::nGantryZ1View, &dResX, &dResY);
				m_CameraInfo.dResolX = dResX;
				m_CameraInfo.dResolY = dResY;
#endif

				Devs::m_Camera10X->SetCameraInfo(m_CameraInfo);
				m_BlobData = Devs::m_Camera10X->GetBlobData();

				if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
				{
					m_BlobData.dMarkSizeX = CModelData::m_AtMaterialPara.Info.dSlotSizeX[0][0];
					m_BlobData.dMarkSizeY = CModelData::m_AtMaterialPara.Info.dSlotSizeY[0][0];
					m_BlobData.dPitchX = CModelData::m_AtMaterialPara.Info.dSlotPitchX[0][0];
					m_BlobData.dPitchY = CModelData::m_AtMaterialPara.Info.dSlotPitchY[0][0];
				}
				else
				{
					m_BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
					m_BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
					m_BlobData.dPitchX = CModelData::m_MaterialPara.Info.dSlotPitchX[0][0];
					m_BlobData.dPitchY = CModelData::m_MaterialPara.Info.dSlotPitchY[0][0];
				}

				//KJT 20210308
				//m_BlobData.nQuantityX = CModelData::m_PpaPara.Info.nDivX + 1; //KJT 20210726
				//m_BlobData.nQuantityY = CModelData::m_PpaPara.Info.nDivY + 1;
				SharedInfo::GetSlotQtyXY(&m_BlobData.nQuantityX, &m_BlobData.nQuantityY);

				m_BlobData.dRangeRateX = 0.8;
				m_BlobData.dRangeRateY = 0.8;

				Devs::m_Camera10X->SetBlobData(m_BlobData);
				stResult = Devs::m_Camera10X->FindBlobPpa2();
			}			

			if (stResult.bResult == FALSE) //KJT 20210404
			{
				m_nGrabRetryCnt++;
				if (m_nGrabRetryCnt > 3)
				{
					SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_GRAB_START : Retry Count"), ePPA_FLOW + 12);
					SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
					break;
				}
				//KJT 20210313
				if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Both || CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Laser)
					SetStep(_eINSPECT_PPA_FLOW_LASER_FOCUS_START, _T("_eINSPECT_PPA_FLOW_LASER_FOCUS_START"));
				else if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Image)
					SetStep(_eINSPECT_PPA_FLOW_IMAGE_FOCUS_START, _T("_eINSPECT_PPA_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eINSPECT_PPA_FLOW_GRAB_START, _T("_eINSPECT_PPA_FLOW_GRAB_START"));

				break;
			}
			Sleep(50);

			m_AlignVisionResultPpaValue[0] = stResult.dPosX;
			m_AlignVisionResultPpaValue[1] = stResult.dPosY;

			m_AlignVisionResultCdValue[0] = stResult.dCdX;
			m_AlignVisionResultCdValue[1] = stResult.dCdY;

			for (int j = 0; j < ((CModelData::m_PpaPara.Info.nDivX + 1) * (CModelData::m_PpaPara.Info.nDivY + 1)); j++) //KJT 20210726
			{
				for (int k = 0; k < 4; k++)
				{
					m_AlignVisionResultCornerRValue[j][k] = Devs::m_Camera10X->m_dCornerRadius[j][k];
				}
			}			
#else
			//m_AlignVisionResultValue[0] = SIM_VISION_RESULT / round(rand());
			//m_AlignVisionResultValue[1] = SIM_VISION_RESULT / round(rand());
			dRandNum = (GetTickCount64() % 10) + 1;

			m_AlignVisionResultPpaValue[0] = dRandNum * SIM_VISION_RESULT;
			m_AlignVisionResultPpaValue[1] = dRandNum * SIM_VISION_RESULT;
#endif
			//PPA Cal
			m_PpaResult[m_nResultIndex][0] = m_AlignVisionResultPpaValue[0];
			m_PpaResult[m_nResultIndex][1] = m_AlignVisionResultPpaValue[1];

			SetStep(_eINSPECT_PPA_FLOW_GRAB_DONE_CHECK, _T("_eINSPECT_PPA_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eINSPECT_PPA_FLOW_GRAB_DONE_CHECK:
			m_AlignVisionPreResultValue[0] = m_AlignVisionResultPpaValue[0];
			m_AlignVisionPreResultValue[1] = m_AlignVisionResultPpaValue[1];
			m_nGrabRetryCnt = 0;

			//Data Display.
			Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dResultPpaX = m_AlignVisionResultPpaValue[0];
			Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dResultPpaY = m_AlignVisionResultPpaValue[1];
			Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dResultCdX = m_AlignVisionResultCdValue[0];
			Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dResultCdY = m_AlignVisionResultCdValue[1];

			//KJT 20210524
			memcpy(Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dResultIndividual_CdX, m_ResultIndividual_CdX, sizeof(m_ResultIndividual_CdX));
			memcpy(Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dResultIndividual_CdY, m_ResultIndividual_CdY, sizeof(m_ResultIndividual_CdY));
			
			//KJT 20210518
			if (m_nPatIndexX == 0 && m_nPatIndexY == 0)
			{
				m_dPosZ_FirstPoint = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_AJIN_CAMERA_Z1];
				Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dResultPpaZ = 0.0;
			}
			else
			{
				Devs::m_GantryMotion.PPAPos[m_nCellIndexX][m_nCellIndexY][m_nPatIndexX][m_nPatIndexY].dResultPpaZ = m_dPosZ_FirstPoint - SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_AJIN_CAMERA_Z1];
			}

			//Data Save.
			resinfo.csMaskID.Format(_T("%s"), SharedInfo::Active.tchStickId); //KJT 20210309
			resinfo.csKeyType = CString("INSPECT PPA");
			resinfo.nKeyID = m_nPpaIndex;

			resinfo.dPPA_RefPos[0] = m_AlignPointValue[0];
			resinfo.dPPA_RefPos[1] = m_AlignPointValue[1];
			resinfo.dPPA_Result[0] = m_AlignPointValue[0] + m_AlignVisionResultPpaValue[0];
			resinfo.dPPA_Result[1] = m_AlignPointValue[1] + m_AlignVisionResultPpaValue[1];
			resinfo.dPPA_X_AVE = m_AlignVisionResultPpaValue[0];
			resinfo.dPPA_Y_AVE = m_AlignVisionResultPpaValue[1];
			resinfo.dCD_X_AVE = m_AlignVisionResultCdValue[0];
			resinfo.dCD_Y_AVE = m_AlignVisionResultCdValue[1];
			//판정을 위한 데이터 수집.
			m_dPpaResult[m_nPpaIndex][0] = m_AlignVisionResultPpaValue[0];
			m_dPpaResult[m_nPpaIndex][1] = m_AlignVisionResultPpaValue[1];

			m_dCdResult[m_nPpaIndex][0] = m_AlignVisionResultCdValue[1];
			m_dCdResult[m_nPpaIndex][1] = m_AlignVisionResultCdValue[1];
			
			for (int j = 0; j < ((CModelData::m_PpaPara.Info.nDivX + 1) * (CModelData::m_PpaPara.Info.nDivY + 1)); j++) //KJT 20210726
			{
				for (int k = 0; k < 4; k++)
				{
					m_dCornerRResult[m_nPpaIndex][j][k] = m_AlignVisionResultCornerRValue[j][k];
				}
			}

			//dPosZ = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_AJIN_CAMERA_Z1];
			dPosZ = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_AJIN_CAMERA_Z1];
			resinfo.dZfoucus = dPosZ;
#if 1
			for (int i = 0; i < MAX_STRETCH_SIZE; i++)
			{
				resinfo.dLoadCell[i] = SharedInfo::dSF_LoadcellForce[i];
				resinfo.dLoadCell[i + MAX_STRETCH_SIZE] = SharedInfo::dSF_LoadcellForce[i + MAX_STRETCH_SIZE];
			}
#endif
			//Awking 1번만 저장
			//SavePpaResult(resinfo);
//			CopyToDispData(m_nPpaIndex, resinfo);
			Str.Format(_T("PPA Index:%d"), m_nPpaIndex);
			Total_Msg(Str);
			bResult = FALSE;
			if (m_bDirectionFlag == FALSE)
			{
				m_nPatIndexX++;
				m_nPpaIndex++;
				//Cell 안 Pattern X방향 끝.
				if (m_nPatIndexX == Devs::m_GantryMotion.m_nMaxPatCntX)
				{
					m_nPatIndexX = 0;
					m_nCellIndexX++;
					//Cell X 끝.
					if (m_nCellIndexX == Devs::m_GantryMotion.m_nMaxCellCntX)
					{
						//nIndex = (Devs::m_GantryMotion.m_nMaxCellCntY - 1) * m_nCellIndexY + m_nPatIndexY;

						Devs::m_GantryMotion.m_dTpX[m_nPatIndexY] =
							Devs::m_GantryMotion.PPAPos[Devs::m_GantryMotion.m_nMaxCellCntX - 1][m_nCellIndexY][Devs::m_GantryMotion.m_nMaxPatCntX - 1][m_nPatIndexY].dResultPpaX -
							Devs::m_GantryMotion.PPAPos[0][m_nCellIndexY][0][m_nPatIndexY].dResultPpaX;
						//Pattern Y방향.
						m_nPatIndexY++;
						m_bDirectionFlag = TRUE;
						m_nCellIndexX = Devs::m_GantryMotion.m_nMaxCellCntX - 1;
						m_nPatIndexX = Devs::m_GantryMotion.m_nMaxPatCntX - 1;
						m_nPpaIndex += (Devs::m_GantryMotion.m_nMaxPatCntX) * (Devs::m_GantryMotion.m_nMaxCellCntX) - 1;
						if (m_nPatIndexY == Devs::m_GantryMotion.m_nMaxPatCntY)
						{

							m_nPatIndexY = 0;
							m_nCellIndexY++;
							//Cell Y 끝.
							if (m_nCellIndexY == Devs::m_GantryMotion.m_nMaxCellCntY)
							{
								for (int i = 0; i < Devs::m_GantryMotion.m_nMaxCellCntX; i++)
								{
									for (int j = 0; j < Devs::m_GantryMotion.m_nMaxPatCntX; j++)
									{
										//nIndex = i * (Devs::m_GantryMotion.m_nMaxCellCntX - 1) + j;
										Devs::m_GantryMotion.m_dTpY[nIndex] =
											Devs::m_GantryMotion.PPAPos[i][Devs::m_GantryMotion.m_nMaxCellCntY - 1][j][Devs::m_GantryMotion.m_nMaxPatCntX - 1].dResultPpaY -
											Devs::m_GantryMotion.PPAPos[i][0][j][0].dResultPpaY;

										nIndex++;
									}
								}
								bResult = TRUE;
							}

						}

					}

				}
			}
			else
			{
				m_nPatIndexX--;
				m_nPpaIndex--;
				//Cell 안 Pattern X방향 끝.
				if (m_nPatIndexX < 0)
				{
					m_nPatIndexX = Devs::m_GantryMotion.m_nMaxPatCntX - 1;
					m_nCellIndexX--;
					//Cell X 끝.
					if (m_nCellIndexX < 0)
					{
						//Pattern Y방향.
						Devs::m_GantryMotion.m_dTpX[m_nPatIndexY] =
							Devs::m_GantryMotion.PPAPos[Devs::m_GantryMotion.m_nMaxCellCntX - 1][m_nCellIndexY][Devs::m_GantryMotion.m_nMaxPatCntX - 1][m_nPatIndexY].dResultPpaX -
							Devs::m_GantryMotion.PPAPos[0][m_nCellIndexY][0][m_nPatIndexY].dResultPpaX;

						m_nPatIndexY++;
						m_bDirectionFlag = FALSE;
						m_nCellIndexX = 0;
						m_nPatIndexX = 0;
						m_nPpaIndex += (Devs::m_GantryMotion.m_nMaxPatCntX) * (Devs::m_GantryMotion.m_nMaxCellCntX) + 1;
						if (m_nPatIndexY == Devs::m_GantryMotion.m_nMaxPatCntY)
						{
							m_nPatIndexY = 0;
							m_nCellIndexY++;
							//Cell Y 끝.
							if (m_nCellIndexY == Devs::m_GantryMotion.m_nMaxCellCntY)
							{
								for (int i = 0; i < Devs::m_GantryMotion.m_nMaxCellCntX; i++)
								{
									for (int j = 0; j < Devs::m_GantryMotion.m_nMaxPatCntX; j++)
									{
										nIndex = i * (Devs::m_GantryMotion.m_nMaxCellCntX - 1) + j;
										Devs::m_GantryMotion.m_dTpY[nIndex] =
											Devs::m_GantryMotion.PPAPos[i][Devs::m_GantryMotion.m_nMaxCellCntY - 1][j][Devs::m_GantryMotion.m_nMaxPatCntY - 1].dResultPpaY -
											Devs::m_GantryMotion.PPAPos[i][0][j][0].dResultPpaY;
									}
								}

								bResult = TRUE;
							}
						}
					}
				}
			}

			//SharedInfo::UpdateAllPpaTopData(resinfo);

			if (bResult == TRUE)
			{
				SavePpaResult(resinfo);

				SetPPAJudgeResult();

				//g_CommLight_8ch.SetLight_Review_Coaxial(0);
				//Sleep(30);
				//g_CommLight_12ch.SetLight_Review_Ring(0);
				//Sleep(30);
				//g_CommMLCLedLight.BackLightOff();

				g_CommReview_Light.SetLight_Review(0, 0);
				Sleep(30);
				g_CommBack_Light.BackLightOff();
				Sleep(30);

				SetStep(_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS, _T("_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS"));
			}
			else
			{
				m_nResultIndex++;
				SetStep(_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			}			
			break;

		case _eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			SetStep(_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, FALSE);
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::Active.ProcessEndFlow != eCOMBO_AUTO_RUN_FLOW_PPA)
					SetStep(_eINSPECT_PPA_FLOW_DONE, _T("_eINSPECT_PPA_FLOW_DONE"));
				else
					SetStep(_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK : Time Out"), ePPA_FLOW + 13);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			}
			break;

		case _eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eINSPECT_PPA_FLOW_DONE, _T("_eINSPECT_PPA_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out"), ePPA_FLOW + 14);
				SetStep(_eINSPECT_PPA_FLOW_ERROR, _T("_eINSPECT_PPA_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eINSPECT_PPA_FLOW_ERROR:
			break;

		case _eINSPECT_PPA_FLOW_DONE:
			SharedInfo::nPrevFlowID = ePPA_FLOW; //KJT 20210326

			m_bMotionDone = TRUE;

			SharedInfo::CalTactTime(_T("INSPECT_PPA_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eINSPECT_PPA_FLOW_IDLE, _T("_eINSPECT_PPA_FLOW_IDLE"));
			break;
		}
		
		Sleep(100); //!!
	}
}

int CInspectPpaFlow::SavePpaResult(ERROR_INFO resinfo) //KJT 20210402
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
	CString strTemp = _T("");



#if 0
	if (m_bAllPpaFlag == TRUE)
		strTemp = SharedInfo::AllPPAPath;
	else
#endif
		strTemp= m_path;

	CString strPath = SharedInfo::VisionAgentPath; // GetHomeDir();
	strPath.AppendFormat(_T("Result\\"));
	::CreateDirectory(strPath, NULL);
	strPath.AppendFormat(_T("Inspect\\"));
	::CreateDirectory(strPath, NULL);

	if (!f.Open(strTemp, CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		if (f.Open(strTemp, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
#if 0 //FMM
			if (m_bAllPpaFlag == TRUE)
			{
				StrTitle.Format(_T("%s,PPA X"), resinfo.csMaskID);
#if 0
				for (int i = 1; i <= Devs::m_GantryMotion.m_nMaxCellCntX * (CModelData::Inspect.DivXY + 1); i++)
					StrTitle.AppendFormat(_T(","), resinfo.csMaskID);
#endif
				StrTitle.AppendFormat(_T("PPA Y\n"));
				f.WriteString(StrTitle);
			}
			else
#endif
			{
				StrTitle.AppendFormat(_T("Mask,%s\n"), resinfo.csMaskID);
				StrTitle.AppendFormat(_T("Cst Floor,%d\n"), m_eTargetFloor + 1); //KJT 20210402
				//StrTitle.AppendFormat(_T("Cst Slot,%d\n\n"), m_eTargetSlot + 1);

				f.WriteString(StrTitle);
			}			
		}
		else
		{
			TRACE("File Open Faile~!!\r\n");
			return false;
		}
	}

	f.SeekToEnd();
	
	INT nCellQuanX = CModelData::m_MaterialPara.Info.nCellCountX;
	INT nCellQuanY = CModelData::m_MaterialPara.Info.nCellCountY;
#if 0
	INT nPatQuanX = CModelData::Inspect.DivXY + 1;
	INT nPatQuanY = CModelData::Inspect.DivXY + 1;
#else
	INT nPatQuanX = CModelData::m_PpaPara.Info.nDivX + 1; //KJT 20210726
	INT nPatQuanY = CModelData::m_PpaPara.Info.nDivY + 1;
#endif
	int nPos = (nCellQuanX * nCellQuanY * nPatQuanX * nPatQuanY) * (_ttoi(resinfo.csMaskID) - 1);

	int nIndex1 = nPos;
	int nIndex2 = nPos;
	int nIndex3 = nPos;

#if 0 //FMM
	if (m_bAllPpaFlag == TRUE)
	{
		str.Format(_T(""));
		{
			str.AppendFormat(_T("Mask, %s"), resinfo.csMaskID);
#if 0
			for (int j = 0; j < CModelData::Inspect.DivXY + 1; j++)
#else
			for (int j = 0; j < CModelData::m_PpaPara.Info.nDivX + 1; j++) //KJT 20210726
#endif
			{
				str.AppendFormat(_T(","));
				for (int i = 0; i < Devs::m_GantryMotion.m_nMaxCellCntX * (CModelData::m_PpaPara.Info.nDivY + 1); i++) //KJT 20210726
				{
					str.AppendFormat(_T("%10.1f,"), SharedInfo::m_pPpaResult[nIndex1].dResultPpaX * 1000 * STICK_FLIP_XY); //KJT 20210318
					nIndex1++;
				}

				for (int i = 0; i < Devs::m_GantryMotion.m_nMaxCellCntX * (CModelData::m_PpaPara.Info.nDivY + 1); i++) //KJT 20210726
				{
					str.AppendFormat(_T("%10.1f,"), SharedInfo::m_pPpaResult[nIndex2].dResultPpaY * 1000 * STICK_FLIP_XY); //KJT 20210318
					nIndex2++;
				}

				for (int i = 0; i < Devs::m_GantryMotion.m_nMaxCellCntX * (CModelData::PpaPara.Info.nDivY + 1); i++) //KJT 20210726
				{
					str.AppendFormat(_T("%10.1f,"), SharedInfo::m_pPpaResult[nIndex3].dResultPpaZ * 1000);
					nIndex3++;
				}
				str.AppendFormat(_T("\n"));
			}
		}
	}
	else
#endif
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//PPA X
		str.Format(_T("PPA X\nPPA\n"));
#if 0
		for (int i = 0; i < CModelData::Inspect.DivXY + 1; i++)
#else
		for (int i = 0; i < CModelData::m_PpaPara.Info.nDivX + 1; i++) //KJT 20210726
#endif
		{
			for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
			{
#if 0
				for (int k = 0; k < CModelData::Inspect.DivXY + 1; k++)
#else
				for (int k = 0; k < CModelData::m_PpaPara.Info.nDivY + 1; k++) //KJT 20210726
#endif
				{
					str.AppendFormat(_T("%10.1f,"), Devs::m_GantryMotion.PPAPos[j][0][k][i].dResultPpaX * 1000 * STICK_FLIP_XY); //KJT 20210318
				}
			}
			str.AppendFormat(_T("\n"));
		}

		//CD X
		str.AppendFormat(_T("CD\n"));
		for (int i = 0; i < CModelData::m_PpaPara.Info.nDivX + 1; i++) //KJT 20210726
		{
			for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
			{
				for (int k = 0; k < CModelData::m_PpaPara.Info.nDivY + 1; k++) //KJT 20210726
				{
					if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN) //KJT 20210406
						str.AppendFormat(_T("%10.1f,"), (CModelData::m_AtMaterialPara.Info.dSlotSizeX[0][0] - Devs::m_GantryMotion.PPAPos[j][0][k][i].dResultCdX) * 1000);
					else
						str.AppendFormat(_T("%10.1f,"), (CModelData::m_MaterialPara.Info.dSlotSizeX[0][0] - Devs::m_GantryMotion.PPAPos[j][0][k][i].dResultCdX) * 1000);
				}
			}
			str.AppendFormat(_T("\n"));
		}

		//TP X
		str.AppendFormat(_T("TP\n"));
		for (int i = 0; i < CModelData::m_PpaPara.Info.nDivX + 1; i++) //KJT 20210726
		{
			str.AppendFormat(_T("%10.1f\n"), Devs::m_GantryMotion.m_dTpX[i] * 1000);
		}

		///////////////////////////////////////////////////////////////////////////////////////////

		//PPA Y
		str.AppendFormat(_T("\nPPA Y\nPPA\n"));
		for (int i = 0; i < CModelData::m_PpaPara.Info.nDivX + 1; i++) //KJT 20210726
		{
			for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
			{
				for (int k = 0; k < CModelData::m_PpaPara.Info.nDivY + 1; k++) //KJT 20210726
				{
					str.AppendFormat(_T("%10.1f,"), Devs::m_GantryMotion.PPAPos[j][0][k][i].dResultPpaY * 1000 * STICK_FLIP_XY); //KJT 20210318
				}
			}
			str.AppendFormat(_T("\n"));
		}

		//CD Y
		str.AppendFormat(_T("CD\n"));
		for (int i = 0; i < CModelData::m_PpaPara.Info.nDivX + 1; i++) //KJT 20210726
		{
			for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
			{
				for (int k = 0; k < CModelData::m_PpaPara.Info.nDivY + 1; k++) //KJT 20210726
				{
					if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN) //KJT 20210406
						str.AppendFormat(_T("%10.1f,"), (CModelData::m_AtMaterialPara.Info.dSlotSizeY[0][0] - Devs::m_GantryMotion.PPAPos[j][0][k][i].dResultCdY) * 1000);
					else
						str.AppendFormat(_T("%10.1f,"), (CModelData::m_MaterialPara.Info.dSlotSizeY[0][0] - Devs::m_GantryMotion.PPAPos[j][0][k][i].dResultCdY) * 1000);
				}
			}
			str.AppendFormat(_T("\n"));
		}	

		//TP Y
		str.AppendFormat(_T("TP\n"));
		for (int i = 0; i < (CModelData::m_PpaPara.Info.nDivY + 1) * Devs::m_GantryMotion.m_nMaxCellCntX; i++) //KJT 20210726
		{
			str.AppendFormat(_T("%10.1f,"), Devs::m_GantryMotion.m_dTpY[i] * 1000);
		}
		str.AppendFormat(_T("\n"));

		///////////////////////////////////////////////////////////////////////////////////////////
		//PPA Z
		str.AppendFormat(_T("\nPPA Z\nPPA\n"));
		for (int i = 0; i < CModelData::m_PpaPara.Info.nDivX + 1; i++) //KJT 20210726
		{
			for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
			{
				for (int k = 0; k < CModelData::m_PpaPara.Info.nDivY + 1; k++) //KJT 20210726
				{
					str.AppendFormat(_T("%10.1f,"), Devs::m_GantryMotion.PPAPos[j][0][k][i].dResultPpaZ * 1000);
				}
			}
			str.AppendFormat(_T("\n"));
		}

		str.AppendFormat(_T("\n"));

		//Corner R
		//for (int i = 0; i < CModelData::m_PpaPara.Info.nDivX + 1; i++) //KJT 20210726
		//{
		//	for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
		//	{
		//		for (int k = 0; k < CModelData::m_PpaPara.Info.nDivY + 1; k++) //KJT 20210726
		//		{
		//			str.AppendFormat(_T("%10.1f,"), Devs::m_GantryMotion.PPAPos[j][0][k][i].dResultPpaY * 1000 * STICK_FLIP_XY); //KJT 20210318
		//		}
		//	}
		//	str.AppendFormat(_T("\n"));
		//		}

		str.AppendFormat(_T("\nCorner\nCorner_R_#0\n"));
		for (int i = 0; i < m_nPpaIndex; i++)
		{
			for (int j = 0; j < ((CModelData::m_PpaPara.Info.nDivX + 1) * (CModelData::m_PpaPara.Info.nDivY + 1)); j++) //KJT 20210726
			{
				for (int k = 0; k < 4; k++)
				{
					str.AppendFormat(_T("%10.1f,"), m_dCornerRResult[i][j][k] * 1000);
				}
			}
			str.AppendFormat(_T("\nCorner_R_#%d\n"), i+1);
		}

		str.AppendFormat(_T("\n"));
		

#if 0 //Temp
		//SF
		for (int i = 0; i < MAX_STRETCH_SIZE; i++)
			str.AppendFormat(_T("ST Tension%d LR,%10.5f,%10.5f\n"), i + 1, resinfo.dLoadCell[i], resinfo.dLoadCell[i + MAX_STRETCH_SIZE]);
		str.AppendFormat(_T("\n"));

		//Temperature
		str.AppendFormat(_T("Temperatue,"));
		for (int i = 0; i < 12; i++)
			str.AppendFormat(_T("%4.2f,"), g_CommTempTur.m_dTempValue[i]);
#endif
	}
	
	f.WriteString(str);
	f.Close();

	return 0;
}

int CInspectPpaFlow::CopyToDispData(int nIndex, ERROR_INFO resinfo)
{

	CVisionAgentDlg* pMain = (CVisionAgentDlg *)AfxGetMainWnd();
	
	//if (pGantry == &Devs::GantryTopMotion)
	//{
	//	SharedInfo::ResultTopDisp[nIndex].dPosX = resinfo.dPPA_RefPos[0];
	//	SharedInfo::ResultTopDisp[nIndex].dPosY = resinfo.dPPA_RefPos[1];
	//	SharedInfo::ResultTopDisp[nIndex].dPpaX = resinfo.dPPA_Result[0] - resinfo.dPPA_RefPos[0];
	//	SharedInfo::ResultTopDisp[nIndex].dPpaY = resinfo.dPPA_Result[1] - resinfo.dPPA_RefPos[1];
	//	SharedInfo::ResultTopDisp[nIndex].dPpaZ = resinfo.dZfoucus;
	//	SharedInfo::ResultTopDisp[nIndex].dCdX = resinfo.dTargetCD[0];
	//	SharedInfo::ResultTopDisp[nIndex].dCdY = resinfo.dTargetCD[1];
	//	SharedInfo::ResultTopDisp[nIndex].dResultCdX = resinfo.dCD_X_AVE;
	//	SharedInfo::ResultTopDisp[nIndex].dResultCdY = resinfo.dCD_Y_AVE;
	//}
	//else
	//{
	//	SharedInfo::ResultBottomDisp[nIndex].dPosX = resinfo.dPPA_RefPos[0];
	//	SharedInfo::ResultBottomDisp[nIndex].dPosY = resinfo.dPPA_RefPos[1];
	//	SharedInfo::ResultBottomDisp[nIndex].dPpaX = resinfo.dPPA_Result[0] - resinfo.dPPA_RefPos[0];
	//	SharedInfo::ResultBottomDisp[nIndex].dPpaY = resinfo.dPPA_Result[1] - resinfo.dPPA_RefPos[1];
	//	SharedInfo::ResultBottomDisp[nIndex].dPpaZ = resinfo.dZfoucus;
	//	SharedInfo::ResultBottomDisp[nIndex].dCdX = resinfo.dTargetCD[0];
	//	SharedInfo::ResultBottomDisp[nIndex].dCdY = resinfo.dTargetCD[1];
	//	SharedInfo::ResultBottomDisp[nIndex].dResultCdX = resinfo.dCD_X_AVE;
	//	SharedInfo::ResultBottomDisp[nIndex].dResultCdY = resinfo.dCD_Y_AVE;
	//}

#if 0
	/pMain->m_pProcessDlg->m_pPpaTopDlg->Invalidate(FALSE);
#endif
	return 0;
}

BOOL CInspectPpaFlow::SetPPAJudgeResult()
{
	CString Str = _T(""), Str2 = _T(""), Str3 = _T("");
	double dResultX = 0.0, dResultY = 0.0, dTargetX = 0.0, dTargetY = 0.0;
	int nGrade = eGRADE_NONE;

	for (int n = 0; n < Devs::m_GantryMotion.m_nMaxCellCntY; n++)
	{
		for (int i = 0; i < CModelData::m_PpaPara.Info.nDivY + 1; i++)
		{
			for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
			{
				for (int k = 0; k < CModelData::m_PpaPara.Info.nDivX + 1; k++)
				{
					for (int grade = eGRADE_F; grade >= eGRADE_S; grade--)
					{
						//PPA
						dResultX = fabs(Devs::m_GantryMotion.PPAPos[j][n][k][i].dResultPpaX);
						dResultY = fabs(Devs::m_GantryMotion.PPAPos[j][n][k][i].dResultPpaY);
						dTargetX = CModelData::m_InspectionPara.Info.dGrade_PpaTargetX[grade];
						dTargetY = CModelData::m_InspectionPara.Info.dGrade_PpaTargetX[grade];
						if (dResultX < dTargetX && dResultY < dTargetY)
						{
							if (grade > nGrade)
							{
								nGrade = grade;
								Str.Format(_T("StickID:%s PPA Result Grade %s (PPA TargetX:%.5f, TargetY:%.5f, ResultX:%.5f, Result:%.5f"),
									SharedInfo::Active.tchStickId, SharedInfo::ChangeGradeIntToStr((enum_Grade)grade), dTargetX, dTargetY, dResultX, dResultY);
								Total_Msg(Str);
							}
						}

						//CD
						dResultX = CModelData::m_AtMaterialPara.Info.dSlotSizeX[j][n] - Devs::m_GantryMotion.PPAPos[j][n][k][i].dResultCdX;
						dResultY = CModelData::m_AtMaterialPara.Info.dSlotSizeY[j][n] - Devs::m_GantryMotion.PPAPos[j][n][k][i].dResultCdY;
						dTargetX = CModelData::m_InspectionPara.Info.dGrade_CdTargetX[grade];
						dTargetY = CModelData::m_InspectionPara.Info.dGrade_CdTargetY[grade];
						if (dResultX < dTargetX && dResultY < dTargetY)
						{
							if (nGrade <= grade)
							{
								nGrade = grade;
								Str.Format(_T("StickID:%s PPA Result Grade %s (CD TargetX:%.5f, TargetY:%.5f, ResultX:%.5f, Result:%.5f"),
									SharedInfo::Active.tchStickId, SharedInfo::ChangeGradeIntToStr((enum_Grade)grade), dTargetX, dTargetY, dResultX, dResultY);
								Total_Msg(Str);
							}
						}

						//TP
						dResultX = Devs::m_GantryMotion.m_dTpX[k];
						dResultY = Devs::m_GantryMotion.m_dTpY[i];
						dTargetX = CModelData::m_InspectionPara.Info.dGrade_TpTargetX[grade];
						dTargetY = CModelData::m_InspectionPara.Info.dGrade_TpTargetY[grade];
						if (dResultX < dTargetX && dResultY < dTargetY)
						{
							if (nGrade <= grade)
							{
								nGrade = grade;
								Str.Format(_T("StickID:%s PPA Result Grade %s (TP TargetX:%.5f, TargetY:%.5f, ResultX:%.5f, Result:%.5f"),
									SharedInfo::Active.tchStickId, SharedInfo::ChangeGradeIntToStr((enum_Grade)grade), dTargetX, dTargetY, dResultX, dResultY);
								Total_Msg(Str);
							}
						}
					}
				}
			}
		}
	}

	SharedInfo::Active.nGrade_PPA = nGrade;

	SharedInfo::ActiveInfoSave();

	return TRUE;
}

BOOL CInspectPpaFlow::TpCheck(INT nMaxCnt)
{
	
	return TRUE;
}

BOOL CInspectPpaFlow::CdCheck(INT nMaxCnt)
{
#if 0
	DOUBLE dTargetCdX = CModelData::m_AlignPara.FineTargetCdX;
	DOUBLE dTargetCdY = CModelData::m_AlignPara.FineTargetCdY;
#else
	DOUBLE dTargetCdX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
	DOUBLE dTargetCdY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
#endif

	DOUBLE dSizeCdX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
	DOUBLE dSizeCdY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
	for (int i = 0; i < nMaxCnt; i++)
	{
		if (fabs(m_dCdResult[i][0] - dSizeCdX) > dTargetCdX || fabs(m_dCdResult[i][1] - dSizeCdY) > dTargetCdY)
		{
			Total_Msg(_T("%d CD Size NG"), i);
			return FALSE;
		}
	}
	return TRUE;
}
BOOL CInspectPpaFlow::PpaCheck(INT nMaxCnt)
{
#if 0
	DOUBLE dTargetPpaX = CModelData::m_AlignPara.FineTargetPpaX;
	DOUBLE dTargetPpaY = CModelData::m_AlignPara.FineTargetPpaY;
#else
	DOUBLE dTargetPpaX = 0;
	DOUBLE dTargetPpaY = 0;
#endif
	
	for (int i = 0; i < nMaxCnt; i++)
	{
		if (fabs(m_dPpaResult[i][0]) > dTargetPpaX || fabs(m_dPpaResult[i][1]) > dTargetPpaY)
		{
			Total_Msg(_T("%d CD Size NG"), i);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CInspectPpaFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("InspectPpaFlow"), ePPA_FLOW, 30) == FALSE)
	{
		return FALSE;
	}


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
