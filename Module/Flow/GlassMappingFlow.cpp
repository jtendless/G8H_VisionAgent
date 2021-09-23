// GlassMappingFlow.cpp


#include "stdafx.h"
#include "GlassMappingFlow.h"
#include "VisionAgentDlg.h"
#include "../Vision/Devs.h"
#include "../../VisionAgent/VisionAgent.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "Data/SystemData.h"
#include "CamAreaModul.h"
#include "FmmLight1.h"

//#include "../Module/Object/ProcessStep.h"
//#include "../Module/Vision/MappingProc.h"

CGlassMappingFlow::CGlassMappingFlow()
{
}

CGlassMappingFlow::~CGlassMappingFlow()
{

}


BOOL CGlassMappingFlow::InitProcess()
{	
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bFlowDone = TRUE;
	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);

	//SetProcessLog(&Process_Msg);
	//SetAlarmLog(&LogMsg_Alarm);

	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
#ifndef SIM_MODE
	pMappingProc = &Devs::m_MappingProc;
#endif
	return TRUE;
}

BOOL CGlassMappingFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(eGLASS_MAPPING_IDLE, FALSE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	do
	{
		Sleep(10);

	} while (m_bTerminate == 0);

	//delete this;

	return TRUE;

	//	SetStep(eGLASS_MAPPING_EXIT, FALSE);
	return TRUE;
}
BOOL CGlassMappingFlow::Start()
{
	m_nMappingID = 0;

	m_bIndividualFlag = TRUE;
	m_bFlowDone = FALSE;
	m_nVerification = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;

	m_bLaserFocusUseFlag = FALSE;
	m_bAutoFocusUseFlag = FALSE;

	switch (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType)
	{
	case eFocusType_Laser:
		m_bLaserFocusUseFlag = TRUE;
		m_bAutoFocusUseFlag = FALSE; //KJT 20210820
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

	SetStep(eGLASS_MAPPING_START, _T("eGLASS_MAPPING_START"));
	return TRUE;
}
BOOL CGlassMappingFlow::Stop()
{	
	m_nGrabRetryCnt = 0;

	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
BOOL CGlassMappingFlow::IsFlowDone()
{
	return m_bFlowDone;
}
UINT CGlassMappingFlow::ThreadFunction(LPVOID lpParam)
{
	CGlassMappingFlow* pGlassMapping= NULL;

	pGlassMapping = (CGlassMappingFlow*)lpParam;

	pGlassMapping->ThreadFunctionEntry();

	pGlassMapping->m_bTerminate = 1;

	return 0;
}

BOOL CGlassMappingFlow::IsFlowRun()
{ 
	if (GetCurrentFlowStep() > eGLASS_MAPPING_IDLE) 
		return TRUE;
	else
		return FALSE;

}
VOID CGlassMappingFlow::ThreadFunctionEntry(VOID)
{
	int i = 0;
	double dMotorXY[4][2] = { {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
	double dPixelXY[4][2] = { {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
	double dPosX[2] = { 0.0, 0.0 };
	double dPosY = 0.0, dPosZ1 = 0.0;
	CString str = _T("");
	double R = 0.0;
	BOOL bResult = FALSE;
#ifndef SIM_MODE
	stModResult ModResult;
#endif
	DOUBLE dVisionResult[2] = { 0.0, 0.0 };
	int CellCntX = 0, CellCntY = 0;
	int nActualStick = 0;
	CString szMsg = _T(""), Str = _T("");
	BOOL bFlag = TRUE;
	double dMappingX[MAX_GLASS_MAPPING_COUNT];
	double dMappingY[MAX_GLASS_MAPPING_COUNT];

	double dPreLapse, dLapse = 0.0;
	LARGE_INTEGER freq, start, end;

	SYSTEMTIME st;
	GetLocalTime(&st);
	CString StrDirPath = _T(""), StrFilePath = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;
			SetCurrentStep(eGLASS_MAPPING_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eGLASS_MAPPING_IDLE:
			break;

		case eGLASS_MAPPING_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			m_timeStart_1Cycle = m_timeStart; //KJT 20210417

			Process_Msg(_T("---- Glass Mapping START-----"));

			//Devs::m_MappingProc.ReleaseSWMapping(eMAPPING_ID_10X); //!! KJT 20200419
			//Devs::m_MappingProc.ReleaseXYTAlignData(eMAPPING_ID_10X); //!! KJT 20200419

			SharedInfo::nGantryZ1View = eViewReview10X;

			m_bCalibDone = FALSE;

			//ReviewCamPosMove = &CGantryMotion::Move_GantryXYZ_Review10X;
			//IsReviewCamPosMove = &CGantryMotion::Is_MoveDone;

			m_bStopBit = FALSE;
		
			m_nMaxMappingCnt = SharedInfo::m_nMappingTableCnt;

			//sunghaklee(2021.04.21)
			m_nMappingPointCntX = 0;
			m_nMappingPointCntY = 0;
			m_nMaxMappingPointCntX = SharedInfo::m_nMaxMappingCountX;
			m_nMaxMappingPointCntY = SharedInfo::m_nMaxMappingCountY;

			//if (CSystemData::m_Stage.Info.m_nCalibRepeat < 1)
			//	CSystemData::m_Stage.Info.m_nCalibRepeat = 1;

			//m_nMaxRepeatCnt = CSystemData::m_Stage.Info.m_nCalibRepeat;

			//m_nRepeatCnt = 0;
			m_nGrabRetryCnt = 0;

			//KJT 20210315 FMM
			dPreVisionResult[0] = 0;
			dPreVisionResult[1] = 0;

			SharedInfo::LightAllOff(); //KJT 20210311

			//sunghaklee(2021.04.21)
			m_nMappingRepeatCnt = 0;
			m_nVerificationRepeatCnt = 0;
			m_nMaxMappingRepeatCnt = CSystemData::m_Stage.Info.m_nMappingRepeatCount;
			m_nMaxVerificationRepeatCnt = CSystemData::m_Stage.Info.m_nVerificationRepeatCount;
#ifndef SIM_MODE
			pMappingProc->ReleaseSWMapping(m_nMappingID);
			pMappingProc->ReleaseXYTAlignData(m_nMappingID); //!! KJT 20200419
			pMappingProc->ReleaseGlassMapping(m_nMappingID);
			pMappingProc->MakeGlassMapping_CalibPoint(m_nMappingID);

			pMappingProc->InitializeGlassMapping(m_nMappingID);
#endif
			m_nMappingCnt = 0;

			//21.02.22 sjc
			//g_CommMLCLedLight.AoiLightOff();
			//g_CommMLCLedLight.BackLightOff();
			//Sleep(500);
			//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
			//Sleep(30);
			//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);
			//Sleep(500);
			//Other Light Off


			//int nVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
			//g_CommBack_Light.BackLightOn(nVal);
			//Sleep(50);
			//g_CommZomm_Ring.Zoom_Light_On(FALSE);
			//Sleep(50);
			//g_CommZomm_Coaxial.Zoom_Light_On(FALSE);
			//Sleep(50);
			////Light On
			//g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);

			SetStep(eGLASS_MAPPING_INTERLOCK_CHECK, _T("eGLASS_MAPPING_INTERLOCK_CHECK"));
			break;
		}
		case eGLASS_MAPPING_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetStep(eGLASS_MAPPING_GANTRY_ZX_READY, _T("eGLASS_MAPPING_GANTRY_ZX_READY"));
			}
			break;

#pragma region //Gantry ZX Ready
		case eGLASS_MAPPING_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(eGLASS_MAPPING_GANTRY_ZX_READY_CHECK, _T("eGLASS_MAPPING_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_MAPPING_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(eGLASS_MAPPING_UNLOADER_READY, _T("eGLASS_MAPPING_UNLOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GANTRY_ZX_READY_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 3);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_GANTRY_ZX_READY_CHECK, _T("eGLASS_MAPPING_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Unloader Ready
		case eGLASS_MAPPING_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(eGLASS_MAPPING_UNLOADER_READY_CHECK, _T("eGLASS_MAPPING_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_MAPPING_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(eGLASS_MAPPING_LOADER_READY, _T("eGLASS_MAPPING_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_UNLOADER_READY_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 0);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_UNLOADER_READY_CHECK, _T("eGLASS_MAPPING_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case eGLASS_MAPPING_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(eGLASS_MAPPING_LOADER_READY_CHECK, _T("eGLASS_MAPPING_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_MAPPING_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(eGLASS_MAPPING_GLASS_ALIGN, _T("eGLASS_MAPPING_GLASS_ALIGN"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_LOADER_READY_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 1);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_LOADER_READY_CHECK, _T("eGLASS_MAPPING_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion


			//21.03.05 sjc add
		//case eGLASS_MAPPING_VERTICAL_ALIGN:			
		//	Devs::m_VerticalAlignFlow.Start(eMAPPING_ID_PreAlign);
		//	SetStep(eGLASS_MAPPING_VERTICAL_ALIGN_CHECK, _T("eGLASS_MAPPING_VERTICAL_ALIGN_CHECK"));
		//	SetTimeOut(TIME_OUT_FORCE_CONTROL);
		//	break;

		//case eGLASS_MAPPING_VERTICAL_ALIGN_CHECK:
		//	if (Devs::m_VerticalAlignFlow.IsFlowDone())
		//	{
		//		SetStep(eGLASS_MAPPING_GLASS_ALIGN, _T("eGLASS_MAPPING_GLASS_ALIGN"));
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SharedInfo::SetAlarm(_T("eGLASS_MAPPING_VERTICAL_ALIGN_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 4);
		//		SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(eGLASS_MAPPING_VERTICAL_ALIGN_CHECK, _T("eGLASS_MAPPING_VERTICAL_ALIGN_CHECK"));
		//	}
		//	break;

		case eGLASS_MAPPING_GLASS_ALIGN:
			if (CSystemData::m_Stage.Info.m_nMappingMainAlign == 1)
			{
				Devs::m_GlassAlignFlow.SetPreAlignUseMode(CSystemData::m_Stage.Info.m_nMappingPreAlign);
				Devs::m_GlassAlignFlow.Start();

				SetStep(eGLASS_MAPPING_GLASS_ALIGN_CHECK, _T("eGLASS_MAPPING_GLASS_ALIGN_CHECK"));
				SetTimeOut(TIME_OUT_FORCE_CONTROL);
			}
			else
			{
				SharedInfo::nPrevFlowID = eGLASS_MAPPING_FLOW; //KJT 20210326
				SetStep(eGLASS_MAPPING_XYTALIGN_START, _T("eGLASS_MAPPING_XYTALIGN_START"));

				//SetStep(eGLASS_MAPPING_START_READY, _T("eGLASS_MAPPING_START_READY"));
				SetTimeOut(TIME_OUT_FORCE_CONTROL);
			}			
			break;

		case eGLASS_MAPPING_GLASS_ALIGN_CHECK:
			if (Devs::m_GlassAlignFlow.IsFlowDone())
			{
				SharedInfo::nPrevFlowID = eGLASS_MAPPING_FLOW; //KJT 20210326
				SetStep(eGLASS_MAPPING_XYTALIGN_START, _T("eGLASS_MAPPING_XYTALIGN_START"));

				//SetStep(eGLASS_MAPPING_START_READY, _T("eGLASS_MAPPING_START_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GLASS_ALIGN_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 5);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_GLASS_ALIGN_CHECK, _T("eGLASS_MAPPING_GLASS_ALIGN_CHECK"));
			}
			break;

		case eGLASS_MAPPING_XYTALIGN_START: //*******************************// //KJT 20210419 Add
#ifndef SIM_MODE
			pMappingProc->ReleaseSWMapping(eMAPPING_ID_10X); //!! KJT 20200913
			pMappingProc->ReleaseXYTAlignData(eMAPPING_ID_10X); //!! KJT 20200913
#endif
			Devs::m_SwAlignFlow.m_eSwAlignType = eSwAlign_Glass;
			Devs::m_SwAlignFlow.Start(Devs::m_SwAlignFlow._eSW_ALIGN_FLOW_START);

			SetStep(eGLASS_MAPPING_XYTALIGN_DONE_CHECK, _T("eGLASS_MAPPING_XYTALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION * 2);
			break;

		case eGLASS_MAPPING_XYTALIGN_DONE_CHECK:
			if (Devs::m_SwAlignFlow.IsFlowDone())
			{
				//SharedInfo::LightAllOff(); //KJT 20210311

				//if (bBacklightUse) //KJT 20210318
				//if (0) //KJT 20210318
				//{
					//for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
					//	nBackLightVal[i] = 20;

					//g_CommMLCLedLight.BackLightOn(nBackLightVal);
					//Sleep(500);
				//}
				//else
				//{
				//	Sleep(500);
					//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
				//	Sleep(30);
					//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);
				//	Sleep(500);
				//}

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignLightType == eLight_Back)
				{
					SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nVerticalMainAlignBackLight);
				}
				else
				{
					g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
				}


				if (m_nMappingCnt == 0)
					SetStep(eGLASS_MAPPING_START_READY, _T("eGLASS_MAPPING_START_READY"));
				else
					SetStep(eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS, _T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_XYTALIGN_DONE_CHECK, _T("eGLASS_MAPPING_XYTALIGN_DONE_CHECK"));
			}
			break;

		case eGLASS_MAPPING_START_READY:
			m_nMappingPointIndexX = 0;
			m_nMappingPointIndexY = 0;
			m_nMappingPointCntX = 0;
			m_nMappingPointCntY = 0;

			m_nMappingCnt = 0;

			//Light On
			//g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
#ifndef SIM_MODE

			if (m_nMappingRepeatCnt >= m_nMaxMappingRepeatCnt) m_nVerification = TRUE;
			else m_nVerification = FALSE;

			if (m_nVerification == TRUE)
			{
				pMappingProc->InitializeGlassMapping(m_nMappingID);
				if (pMappingProc->LoadGlassMappingFile(m_nMappingID) == FALSE)
				{
					AfxMessageBox(_T("Glass Mapping Data is not exist"));
					SharedInfo::SetAlarm(_T("eGLASS_MAPPING_START_READY : Mapping Data"), eGLASS_MAPPING_FLOW + 6);
					SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
					break;
				}
			}
			//else
			//{
			//	if (m_bCalibDone == TRUE && CSystemData::m_Stage.Info.m_nCalibVerify == TRUE)
			//	{
			//		pMappingProc->InitializeGlassMapping(m_nMappingID);
			//		if (pMappingProc->LoadGlassMappingFile(m_nMappingID) == FALSE)
			//		{
			//			AfxMessageBox(_T("Glass Mapping Data is not exist"));
			//			SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			//			break;
			//		}
			//	}
			//	else
			//	{
			//		pMappingProc->InitializeGlassMapping(m_nMappingID);
			//		if (m_nRepeatCnt != 0)
			//		{
			//			if (pMappingProc->LoadGlassMappingFile(m_nMappingID) == FALSE)
			//			{
			//				AfxMessageBox(_T("Glass Mapping Data is not exist"));
			//				break;
			//			}
			//		}
			//		else
			//			pMappingProc->MakeGlassMapping_CalibPoint(m_nMappingID);
			//	}
			//}

			if(m_nVerification == FALSE) pMappingProc->CalibGlassMapping_MainBegin(m_nMappingID, m_nMappingRepeatCnt, m_nVerification);
			else pMappingProc->CalibGlassMapping_MainBegin(m_nMappingID, m_nVerificationRepeatCnt, m_nVerification);
#endif
			SetStep(eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS, _T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS"));
			break;

		case eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS:	
			//sunghaklee(2021.04.21)
			m_nMappingPointIndexY = m_nMappingPointCntY;
			if (m_nMappingPointCntY % 2 != 0)	m_nMappingPointIndexX = m_nMaxMappingPointCntX - 1 - m_nMappingPointCntX;
			else								m_nMappingPointIndexX = m_nMappingPointCntX;
#ifndef SIM_MODE
			m_dCDMPoint = pMappingProc->GetGlassMapping_Num2MotorPos(m_nMappingID, m_nMappingPointIndexX, m_nMappingPointIndexY);
#endif
			m_dPosX = m_dCDMPoint.x;	m_dPosY = m_dCDMPoint.y;

			//m_dPosX = SharedInfo::m_sMappingTable[m_nMappingCnt].dPosX + SharedInfo::m_sMappingTable[m_nMappingCnt].dErrorX;
			//m_dPosY = SharedInfo::m_sMappingTable[m_nMappingCnt].dPosY + SharedInfo::m_sMappingTable[m_nMappingCnt].dErrorY;
			m_dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Mapping_Review_Pos; //!!

#if 1 //Skip Area
			//if (m_dPosY < -70.0 && m_dPosY > 0.0)
			//{
			//	m_nMappingCnt++;
			//	m_nMappingCnt++;
			//	SetStep(eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS, _T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS"));
			//	break;
			//}
#endif

			bFlag = TRUE;
			if (m_dPosX < CModelData::m_GlassPara.Info.dGlassAlignMark_LT_X)
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS : Mapping Pos LT_X"), eGLASS_MAPPING_FLOW + 7);
				Str.Format(_T("Mapping Pos Error !! (Target PosX:%.5f, SafetyMinPosX:%.5f)"), m_dPosX, CModelData::m_GlassPara.Info.dGlassAlignMark_LT_X);
				bFlag = FALSE;
			}
			else if (m_dPosX > CModelData::m_GlassPara.Info.dGlassAlignMark_RT_X)
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS : Mapping Pos RT_X"), eGLASS_MAPPING_FLOW + 8);
				Str.Format(_T("Mapping Pos Error !! (Target PosX:%.5f, SafetyMaxPosX:%.5f)"), m_dPosX, CModelData::m_GlassPara.Info.dGlassAlignMark_RT_X);
				bFlag = FALSE;
			}
			else if (m_dPosY > CModelData::m_GlassPara.Info.dGlassAlignMark_LT_Y)
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS : Mapping Pos LT_Y"), eGLASS_MAPPING_FLOW + 9);
				Str.Format(_T("Mapping Pos Error !! (Target PosY:%.5f, SafetyMinPosY:%.5f)"), m_dPosY, CModelData::m_GlassPara.Info.dGlassAlignMark_LT_Y);
				bFlag = FALSE;
			}
			else if (m_dPosY < CModelData::m_GlassPara.Info.dGlassAlignMark_LB_Y)
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS : Mapping Pos LB_Y"), eGLASS_MAPPING_FLOW + 10);
				Str.Format(_T("Mapping Pos Error !! (Target PosY:%.5f, SafetyMaxPosY:%.5f)"), m_dPosY, CModelData::m_GlassPara.Info.dGlassAlignMark_LB_Y);
				bFlag = FALSE;
			}
			if (bFlag == FALSE)
			{
				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS : Mapping Pos"), eGLASS_MAPPING_FLOW + 11);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
				break;
			}

			//m_dRefPosX = m_dPosX;
			//m_dRefPosY = m_dPosY;
#ifndef SIM_MODE
			//if (m_bCalibDone == TRUE && CSystemData::m_Stage.Info.m_nCalibVerify == TRUE)
			//{
			//	pMappingProc->GetXYTAlign_CalibPosXY(1, &m_dPosX, &m_dPosY);
			//	pMappingProc->GetGlassMapping_CalibPosXY(m_nMappingID, &m_dPosX, &m_dPosY);
			//}
			//else
			//{
			//	if (m_nVerification == TRUE)
			//	{
			//		pMappingProc->GetXYTAlign_CalibPosXY(1, &m_dPosX, &m_dPosY);
			//		pMappingProc->GetGlassMapping_CalibPosXY(m_nMappingID, &m_dPosX, &m_dPosY);
			//	}
			//	else
			//	{
			//		pMappingProc->GetGlassMapping_WorldToPixel(m_nMappingID, m_dPosX, m_dPosY);
			//	}
			//}

			pMappingProc->GetGlassMapping_CalibPosXY(m_nMappingID, &m_dPosX, &m_dPosY);
			pMappingProc->GetXYTAlign_CalibPosXY(eMAPPING_ID_10X, &m_dPosX, &m_dPosY);

			m_dRefPosX = m_dPosX;
			m_dRefPosY = m_dPosY;
			
#endif
			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dPosY);
			Sleep(20); //!!

			SetStep(eGLASS_MAPPING_GANTRY_XY_MAPPING_POS_CHECK, _T("eGLASS_MAPPING_GANTRY_XY_MAPPING_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_MAPPING_GANTRY_XY_MAPPING_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dPosY))
			{
#if 0
				//Sleep(500);
				//SetStep(eGLASS_MAPPING_GANTRY_Z1_INSPECTION_POS, _T("eGLASS_MAPPING_GANTRY_Z1_INSPECTION_POS"));
				SetStep(eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS, _T("eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS"));
#else //KJT 20210721
				Sleep(500); //!!

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both || CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Laser)
					SetStep(eGLASS_MAPPING_LASER_FOCUS_START, _T("eGLASS_MAPPING_LASER_FOCUS_START"));
				else if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Image)
					SetStep(eGLASS_MAPPING_IMAGE_FOCUS_START, _T("eGLASS_MAPPING_IMAGE_FOCUS_START"));
				else
					SetStep(eGLASS_MAPPING_VISION_GRAB, _T("eGLASS_MAPPING_VISION_GRAB"));
#endif
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GANTRY_XY_MAPPING_POS_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 12);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_GANTRY_XY_MAPPING_POS_CHECK);
			}
			break;

		case eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS:
			//21.02.23 sjc			
			Devs::m_GantryMotion.Move_GantryZ1_InspectionMapping_Pos();
			Sleep(20); //!!

			SetStep(eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS_CHECK, _T("eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS_CHECK:
			//21.02.23 sjc
			//if (Devs::m_GantryMotion.Is_GantryZ3_InspectionReview_Pos())
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionMapping_Pos())
			{
				Sleep(500); //!!

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both || CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Laser)
					SetStep(eGLASS_MAPPING_LASER_FOCUS_START, _T("eGLASS_MAPPING_LASER_FOCUS_START"));
				else if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Image)
					SetStep(eGLASS_MAPPING_IMAGE_FOCUS_START, _T("eGLASS_MAPPING_IMAGE_FOCUS_START"));
				else
					SetStep(eGLASS_MAPPING_VISION_GRAB, _T("eGLASS_MAPPING_VISION_GRAB"));

			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 13);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS_CHECK, _T("eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS_CHECK"));
			}
			break;

		case eGLASS_MAPPING_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove(1);//Glass

			SetStep(eGLASS_MAPPING_LASER_FOCUS_CHECK, _T("eGLASS_MAPPING_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_MAPPING_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eGLASS_MAPPING_IMAGE_FOCUS_START, _T("eGLASS_MAPPING_IMAGE_FOCUS_START"));
				else
					SetStep(eGLASS_MAPPING_VISION_GRAB, _T("eGLASS_MAPPING_VISION_GRAB"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_LASER_FOCUS_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 14);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_LASER_FOCUS_CHECK, _T("eGLASS_MAPPING_LASER_FOCUS_CHECK"));
			}
			break;

		case eGLASS_MAPPING_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			switch (m_nMappingID)
			{
#if 0 //KJT 20210820 Junying Not Use
			case eMAPPING_ID_20X:
#ifndef SIM_MODE
				//g_pReview20x->m_bAfEnd = FALSE;
				//g_pReview20x->AutofoucsRun(eViewReview20X);
#endif
				break;
#endif
			case eMAPPING_ID_10X:
			case eMAPPING_ID_20X: //KJT 20210820 Add
			case eMAPPING_ID_50X: //KJT 20210820 Add
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
				break;
			}
#endif

			SetStep(eGLASS_MAPPING_IMAGE_FOCUS_CHECK, _T("eGLASS_MAPPING_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_MAPPING_IMAGE_FOCUS_CHECK:
			bResult = FALSE;
#if 1
			switch (m_nMappingID)
			{
#if 0 //KJT 20210820 Junying Not Use
			case eMAPPING_ID_20X:
#ifndef SIM_MODE
				//if (g_pReview20x->m_bAfEnd == TRUE)
#endif
				{
					bResult = TRUE;
				}
				break;
#endif
			case eMAPPING_ID_10X:
			case eMAPPING_ID_20X: //KJT 20210820 Add
			case eMAPPING_ID_50X: //KJT 20210820 Add
#ifndef SIM_MODE
				if (g_pReview10x->m_bAfEnd == TRUE)
#endif
				{
					bResult = TRUE;
				}
				break;
			}
#else
			bResult = TRUE;
#endif
			if (bResult == TRUE)
			{
				m_nGrabRetryCnt = 0; 
				m_nDelayCnt = 0;

				Sleep(500); //!!
				SetStep(eGLASS_MAPPING_VISION_GRAB, _T("eGLASS_MAPPING_VISION_GRAB"));
				
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_IMAGE_FOCUS_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 15);
				SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_IMAGE_FOCUS_CHECK, _T("eGLASS_MAPPING_IMAGE_FOCUS_CHECK"));
			}
			break;

		case eGLASS_MAPPING_VISION_GRAB:
#ifndef SIM_MODE

			dVisionResult[0] = 0.0;
			dVisionResult[1] = 0.0;
		
			ModCirclePara.dRadius = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX / 2;
			switch (m_nMappingID)
			{
#if 0 //KJT 20210820 Junying Not Use
			case eMAPPING_ID_20X:
				Sleep(100);
				m_CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold;// CModelData::m_GlassPara.Info.nBrightness20XThreshold;
				ModResult = Devs::m_Camera20X->FindModCircleFind(ModCirclePara);
				Sleep(200);
				m_ModelFindData = Devs::m_Camera20X->GetModelFindData();
				break;
#endif
			case eMAPPING_ID_10X:
			case eMAPPING_ID_20X: //KJT 20210820 Add
			case eMAPPING_ID_50X: //KJT 20210820 Add
				Sleep(100);
				m_CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold;// CModelData::m_GlassPara.Info.nBrightness10XThreshold;
				ModResult = Devs::m_Camera10X->FindModCircleFind(ModCirclePara);
				Sleep(200);
				m_ModelFindData = Devs::m_Camera10X->GetModelFindData();
				break;
			}

			SharedInfo::SaveImage(_STORAGE_GLASE_REVIEW);

			if (ModResult.bResult == FALSE) //KJT 20210404
			{
				m_nGrabRetryCnt++;
				if (m_nGrabRetryCnt > 3)
				{
					SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
					break;
				}

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both || CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Laser)
					SetStep(eGLASS_MAPPING_LASER_FOCUS_START, _T("eGLASS_MAPPING_LASER_FOCUS_START"));
				else if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Image)
					SetStep(eGLASS_MAPPING_IMAGE_FOCUS_START, _T("eGLASS_MAPPING_IMAGE_FOCUS_START"));
				else
					SetStep(eGLASS_MAPPING_VISION_GRAB, _T("eGLASS_MAPPING_VISION_GRAB"));

				break;
			}
			else
				m_nGrabRetryCnt = 0;

			dVisionResult[0] = m_ModelFindData.dPosX;
			dVisionResult[1] = m_ModelFindData.dPosY;	
			
			m_BlobData.dMarkSizeX = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX;
			m_BlobData.dMarkSizeY = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeY;
#endif
#if 0
			//KJT 20210315
			if ((m_nMappingRepeatCnt + m_nVerificationRepeatCnt) != 0 &&
				(m_nMappingCnt != 0 && ((fabs(dVisionResult[0]) >= 100 || fabs(dVisionResult[1]) >= 100)))) //KJT 20210417
#else
			if ((m_nMappingRepeatCnt + m_nVerificationRepeatCnt) != 0 &&
				(m_ModelFindData.dScore < 90.0 || //CSystemData::m_Stage.Info.m_dTargetScore
				fabs(1.0 - m_ModelFindData.dScale) > 0.1)) //Score:90, Scale +-0.1 //CSystemData::m_Stage.Info.m_dTargetScale
#endif
			{
				m_nGrabRetryCnt++;

#ifndef SIM_MODE //KJT 20210320
#if 1
				GetLocalTime(&st);
				StrDirPath.Format(_T("%s\\GrabError\\%04d%02d%02d"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH, st.wYear, st.wMonth, st.wDay);
				::CreateDirectory(StrDirPath, NULL);
				dPosZ1 = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
				StrFilePath.Format(_T("%s\\1_Mapping_X%.5f_Y%.5f_Z%.5f_Retry%d.png"), StrDirPath, m_dRefPosX, m_dRefPosY, dPosZ1, m_nGrabRetryCnt);
				Devs::m_Camera10X->SaveDisplayImage(StrFilePath);
#endif
#endif
				if (m_nGrabRetryCnt > 10)
				{
					m_nGrabRetryCnt = 0;
#if 0
					SharedInfo::SetAlarm(_T("eGLASS_MAPPING_VISION_GRAB : Retry Count"), eGLASS_MAPPING_FLOW + 16);
					SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
					break;
#else //KJT 20210724
					bPassGrab = FALSE;
					SetStep(eGLASS_MAPPING_CALC_MAPPING_DATA, _T("eGLASS_MAPPING_CALC_MAPPING_DATA"));
					break;
#endif
				}
				else
				{
					if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both || CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Laser)
						SetStep(eGLASS_MAPPING_LASER_FOCUS_START, _T("eGLASS_MAPPING_LASER_FOCUS_START"));
					else if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Image)
						SetStep(eGLASS_MAPPING_IMAGE_FOCUS_START, _T("eGLASS_MAPPING_IMAGE_FOCUS_START"));
					else
						SetStep(eGLASS_MAPPING_VISION_GRAB, _T("eGLASS_MAPPING_VISION_GRAB"));
					break;
				}
			}
#if 1 //KJT 20210820 Use
			//else if ((m_nMappingRepeatCnt + m_nVerificationRepeatCnt) == 0 && m_nGrabRetryCnt == 0) //KJT 20210315 FMM
			//{
			//	m_nGrabRetryCnt++;

			//	SetStep(eGLASS_MAPPING_VISION_GRAB, _T("eGLASS_MAPPING_VISION_GRAB"));
			//}
			else if ((m_nMappingRepeatCnt + m_nVerificationRepeatCnt) != 0 &&
				//(m_nMappingCnt != 0 && (fabs(dPreVisionResult[0] - dVisionResult[0]) > 0.0005 || //KJT 20210417
				//	fabs(dPreVisionResult[1] - dVisionResult[1]) > 0.0005))) //KJT 20210315 FMM
				(m_nMappingCnt != 0 && (fabs(dPreVisionResult[0] - dVisionResult[0]) > 0.001 || //KJT 20210417
					fabs(dPreVisionResult[1] - dVisionResult[1]) > 0.001))) //KJT 20210315 FMM
			{
				m_nGrabRetryCnt++;

				str.Format(_T("m_nGrabRetryCnt = %d, X_Offset = %.5f, Y_Offset = %.5f\n"), fabs(dPreVisionResult[0] - dVisionResult[0]), fabs(dPreVisionResult[1] - dVisionResult[1]));
				Total_Msg(str);

#ifndef SIM_MODE //KJT 20210320
#if 1
				GetLocalTime(&st);
				StrDirPath.Format(_T("%s\\GrabError\\%04d%02d%02d"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH, st.wYear, st.wMonth, st.wDay);
				::CreateDirectory(StrDirPath, NULL);
				dPosZ1 = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
				StrFilePath.Format(_T("%s\\2_Mappping_X%.5f_Y%.5f_Z%.5f_Retry%d.png"), StrDirPath, m_dRefPosX, m_dRefPosY, dPosZ1, m_nGrabRetryCnt);
				Devs::m_Camera10X->SaveDisplayImage(StrFilePath);
#endif
#endif
				if (m_nGrabRetryCnt > 3 || (dPreVisionResult[0] == 0.0 && dPreVisionResult[1] == 0.0))
				{
					m_nGrabRetryCnt = 0;
					dPreVisionResult[0] = dVisionResult[0];
					dPreVisionResult[1] = dVisionResult[1];
					bPassGrab = FALSE;
					SetStep(eGLASS_MAPPING_CALC_MAPPING_DATA, _T("eGLASS_MAPPING_CALC_MAPPING_DATA"));
					break;
				}
				else
				{
					SetStep(eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS, _T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS"));
				}
			}
#endif
			else
			{
				//KJT 20210315 FMM
				dPreVisionResult[0] = dVisionResult[0];
				dPreVisionResult[1] = dVisionResult[1];
				bPassGrab = TRUE;
				SetStep(eGLASS_MAPPING_CALC_MAPPING_DATA, _T("eGLASS_MAPPING_CALC_MAPPING_DATA"));
			}
			break;

		case eGLASS_MAPPING_CALC_MAPPING_DATA:
#ifndef SIM_MODE
			if (bPassGrab) //KJT 20210724 Add
				pMappingProc->CalibGlassMapping_MainGetData(m_nMappingID, m_dRefPosX, m_dRefPosY, m_ModelFindData.dPosX, m_ModelFindData.dPosY, m_ModelFindData.dScore, m_ModelFindData.dScale, m_nVerification);

			SharedInfo::m_sMappingTable[m_nMappingCnt].dResultX = m_ModelFindData.dPosX;
			SharedInfo::m_sMappingTable[m_nMappingCnt].dResultY = m_ModelFindData.dPosY;

#endif
			m_nMappingCnt++;

			if (++m_nMappingPointCntX >= m_nMaxMappingPointCntX)
			{
				m_nMappingPointCntX = 0;

				if (++m_nMappingPointCntY >= m_nMaxMappingPointCntY)
				{
					SharedInfo::CalTactTime(_T("GLASS_MAPPING_FLOW (1Cycle)"), m_timeStart_1Cycle); //KJT 20210417
					m_timeStart_1Cycle = CTime::GetCurrentTime(); //KJT 20210417

					if (m_nVerification == FALSE)
					{
#ifndef SIM_MODE
						pMappingProc->CalibGlassMapping_MainEnd(m_nMappingID, FALSE);
#endif
						if (++m_nMappingRepeatCnt >= m_nMaxMappingRepeatCnt)
						{
							if (m_nVerificationRepeatCnt < m_nMaxVerificationRepeatCnt)
							{
								m_nVerification = TRUE;

								m_nResultCnt = 0;
								for (int i = 0; i < m_nMaxMappingCnt; i++)
								{
									dMappingX[m_nResultCnt] = SharedInfo::m_sMappingTable[i].dResultX;
									dMappingY[m_nResultCnt] = SharedInfo::m_sMappingTable[i].dResultY;
									m_nResultCnt++;
								}
#ifndef SIM_MODE
								pMappingProc->GetStandardDeviation(dMappingX, dMappingY, m_nResultCnt, &m_MappingResultX, &m_MappingResultY);
								m_MappingResultX = m_MappingResultX * 3;
								m_MappingResultY = m_MappingResultY * 3;
#endif	
								SetStep(eGLASS_MAPPING_START_READY, _T("eGLASS_MAPPING_START_READY"));

								//DO NOT USE
								//m_nMappingCnt = 0;
								//SharedInfo::nPrevFlowID = eGLASS_MAPPING_FLOW; //KJT 20210326
								//SetStep(eGLASS_MAPPING_XYTALIGN_START, _T("eGLASS_MAPPING_XYTALIGN_START"));
							}
							//end of Glass Mapping
							else
							{
								if (CSystemData::m_Stage.Info.m_nApplyMappingResult == TRUE)
								{
#ifndef SIM_MODE
									pMappingProc->InitializeGlassMapping(m_nMappingID);
									if (pMappingProc->LoadGlassMappingFile(m_nMappingID) == FALSE)
									{
										AfxMessageBox(_T("Glass Mapping Data is not exist"));
										SharedInfo::SetAlarm(_T("eGLASS_MAPPING_CALC_MAPPING_DATA : Mapping Data"), eGLASS_MAPPING_FLOW + 17);
										SetStep(eGLASS_MAPPING_ERROR, _T("eGLASS_MAPPING_ERROR"));
										break;
									}
#endif
								}

								SetStep(eGLASS_MAPPING_Z_MOVE_FINISH_UP_POS, _T("eGLASS_MAPPING_Z_MOVE_FINISH_UP_POS"));
							}
						}
						else
						{
							SetStep(eGLASS_MAPPING_START_READY, _T("eGLASS_MAPPING_START_READY"));

							//DO NOT USE
							//m_nMappingCnt = 0;
							//SharedInfo::nPrevFlowID = eGLASS_MAPPING_FLOW; //KJT 20210326
							//SetStep(eGLASS_MAPPING_XYTALIGN_START, _T("eGLASS_MAPPING_XYTALIGN_START"));
						}
					}
					//m_nVerification is TRUE
					else
					{
#ifndef SIM_MODE
						pMappingProc->CalibGlassMapping_MainEnd(m_nMappingID, TRUE);
#endif
						if (++m_nVerificationRepeatCnt >= m_nMaxVerificationRepeatCnt)
						{
							m_nResultCnt = 0;
							for (int i = 0; i < m_nMaxMappingCnt; i++)
							{
								dMappingX[m_nResultCnt] = SharedInfo::m_sMappingTable[i].dResultX;
								dMappingY[m_nResultCnt] = SharedInfo::m_sMappingTable[i].dResultY;
								m_nResultCnt++;
							}
#ifndef SIM_MODE
							pMappingProc->GetStandardDeviation(dMappingX, dMappingY, m_nResultCnt, &m_MappingResultX, &m_MappingResultY);
							m_MappingResultX = m_MappingResultX * 3;
							m_MappingResultY = m_MappingResultY * 3;
#endif	

							SetStep(eGLASS_MAPPING_Z_MOVE_FINISH_UP_POS, _T("eGLASS_MAPPING_Z_MOVE_FINISH_UP_POS"));
						}
						else
						{
							SetStep(eGLASS_MAPPING_START_READY, _T("eGLASS_MAPPING_START_READY"));

							//DO NOT USE
							//m_nMappingCnt = 0;
							//SharedInfo::nPrevFlowID = eGLASS_MAPPING_FLOW; //KJT 20210326
							//SetStep(eGLASS_MAPPING_XYTALIGN_START, _T("eGLASS_MAPPING_XYTALIGN_START"));
						}
					}					
				}
				else
				{					
					if (CSystemData::m_Stage.Info.m_nXYTIntervalCount > 0 && m_nMappingCnt % CSystemData::m_Stage.Info.m_nXYTIntervalCount == 0)  //KJT 20210419
					{
						SharedInfo::nPrevFlowID = eGLASS_MAPPING_FLOW; //KJT 20210326

						SetStep(eGLASS_MAPPING_XYTALIGN_START, _T("eGLASS_MAPPING_XYTALIGN_START"));
					}
					else
					{
						SetStep(eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS, _T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS"));
					}
				}
			}
			else
			{
				if (CSystemData::m_Stage.Info.m_nXYTIntervalCount > 0 && m_nMappingCnt % CSystemData::m_Stage.Info.m_nXYTIntervalCount == 0)  //KJT 20210419
				{
					SharedInfo::nPrevFlowID = eGLASS_MAPPING_FLOW; //KJT 20210326

					SetStep(eGLASS_MAPPING_XYTALIGN_START, _T("eGLASS_MAPPING_XYTALIGN_START"));
				}
				else
				{
					SetStep(eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS, _T("eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS"));
				}
			}
			break;

		case eGLASS_MAPPING_Z_MOVE_FINISH_UP_POS:
			Devs::m_GantryMotion.Move_GantryZ1_Wait_Pos();

			SetStep(eGLASS_MAPPING_Z_FINISH_UP_POS_CHECK, FALSE);
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_MAPPING_Z_FINISH_UP_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_Wait_Pos())
			{
				SetStep(eGLASS_MAPPING_DONE, _T("eGLASS_MAPPING_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_MAPPING_Z_FINISH_UP_POS_CHECK : Time Out"), eGLASS_MAPPING_FLOW + 18);
				SetStep(eGLASS_MAPPING_Z_MOVE_FINISH_UP_POS, FALSE);
			}
			else
			{
				SetCheckStep(eGLASS_MAPPING_Z_FINISH_UP_POS_CHECK);
			}

		case eGLASS_MAPPING_DONE:
			
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("GLASS_MAPPING_FLOW"), m_timeStart); //KJT 20210329

			SetStep(eGLASS_MAPPING_IDLE, _T("eGLASS_MAPPING_IDLE"));

			break;
		}

		Sleep(100); //!!
	}
}

BOOL CGlassMappingFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("GlassMappingFlow"), eGLASS_MAPPING_FLOW, 30) == FALSE)
	{
		return FALSE;
	}	
	
	//temp del
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

	return TRUE;
}