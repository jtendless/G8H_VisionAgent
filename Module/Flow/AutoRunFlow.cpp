#include "stdafx.h"
#include "AutoRunFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "FmmLight1.h"

CAutoRunFlow::CAutoRunFlow()
{
}


CAutoRunFlow::~CAutoRunFlow()
{
}

BOOL CAutoRunFlow::InitProcess()
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

BOOL CAutoRunFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eAUTO_RUN_FLOW_START, FALSE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CAutoRunFlow::Start()
{
	if (SharedInfo::MachineState.bErrorFlag == TRUE)
	{
		AfxMessageBox(_T("Machine State Error !!!"));
		return FALSE;
	}

	if (SharedInfo::MachineState.bAutoRunFlag == TRUE)
	{
		AfxMessageBox(_T("bAutoRunFlag is TRUE"));
		return FALSE;
	}

	if (SharedInfo::MachineState.bSemiAutoRunFlag == TRUE) //KJT 29210416
	{
		AfxMessageBox(_T("bSemiAutoRunFlag is TRUE"));
		return FALSE;
	}

	if (SharedInfo::bRemoteAjinSystemReadyStatus == FALSE)
	{
		AfxMessageBox(_T("bRemoteAjinSystemReadyStatus is FALSE"));
		return FALSE;
	}
	if (SharedInfo::bRemoteUmacSystemReadyStatus == FALSE)
	{
		AfxMessageBox(_T("bRemoteUmacSystemReadyStatus is FALSE"));
		return FALSE;
	}
	if (SharedInfo::bDirectAjinSystemReadyStatus == FALSE)
	{
		AfxMessageBox(_T("bDirectAjinSystemReadyStatus is FALSE"));
		return FALSE;
	}

	SharedInfo::MachineState.bAutoRunFlag = TRUE;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SharedInfo::Active.bStickTensionOnceDone = FALSE;

	m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
	m_timeCycleStart = m_timeStart; //KJT 20210415

	switch (SharedInfo::Active.ProcessStartFlow)
	{
	case eCOMBO_AUTO_RUN_FLOW_BOX_ALIGN:
		SetStep(_eAUTO_RUN_FLOW_BOX_ALIGN_START, _T("_eAUTO_RUN_FLOW_BOX_ALIGN_START"));
		break;

	case eCOMBO_AUTO_RUN_FLOW_STICK_PAPER_LOAD_UNLOAD:
		SetStep(_eAUTO_RUN_FLOW_STICK_PAPER_LOAD_START, _T("_eAUTO_RUN_FLOW_STICK_PAPER_LOAD_START"));
		break;

	case eCOMBO_AUTO_RUN_FLOW_PRE_ALIGN:
		SetStep(_eAUTO_RUN_FLOW_PRE_ALIGN_START, _T("_eAUTO_RUN_FLOW_PRE_ALIGN_START"));
		break;

	case eCOMBO_AUTO_RUN_FLOW_MAIN_ALIGN:
		SetStep(_eAUTO_RUN_FLOW_MAIN_ALIGN_START, _T("_eAUTO_RUN_FLOW_MAIN_ALIGN_START"));
		break;	

	//case eCOMBO_AUTO_RUN_FLOW_SW_ALIGN: //KJT 20210315
	//	SetStep(_eAUTO_RUN_FLOW_SW_ALIGN_START, _T("_eAUTO_RUN_FLOW_SW_ALIGN_START"));
	//	break;

	case eCOMBO_AUTO_RUN_FLOW_TP: //KJT 20210406
		SetStep(_eAUTO_RUN_FLOW_TP_START, _T("_eAUTO_RUN_FLOW_TP_START"));
		break;	

	case eCOMBO_AUTO_RUN_FLOW_PPA:
		SetStep(_eAUTO_RUN_FLOW_PPA_START, _T("_eAUTO_RUN_FLOW_PPA_START"));
		break;

	//case eCOMBO_AUTO_RUN_FLOW_AOI:
	//	SetStep(_eAUTO_RUN_FLOW_AOI_START, _T("_eAUTO_RUN_FLOW_AOI_INSPECTION_START"));
	//	break;

	//case eCOMBO_AUTO_RUN_FLOW_AOI_REVIEW:
	//	SetStep(_eAUTO_RUN_FLOW_AOI_REVIEW_START, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_START"));
	//	break;

	//case eCOMBO_AUTO_RUN_FLOW_3D:
	//	SetStep(_eAUTO_RUN_FLOW_3D_START, _T("_eAUTO_RUN_FLOW_3D_START"));
	//	break;

	case eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST:
		SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
		break;

#pragma region //At Material Para
	case eCOMBO_AUTO_RUN_FLOW_STICK_CLAMP_TENSION:
		SetStep(_eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_START, _T("_eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_START"));
		break;

	case eCOMBO_AUTO_RUN_FLOW_PRE_TENSION_ALIGN:
		SetStep(_eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_START, _T("_eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_START"));
		break;

	case eCOMBO_AUTO_RUN_FLOW_MAIN_TENSION_ALIGN:
		SetStep(_eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_START, _T("_eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_START"));
		break;

	case eCOMBO_AUTO_RUN_FLOW_EDGE_TENSION_ALIGN:
		SetStep(_eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_START, _T("_eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_START"));
		break;

	case eCOMBO_AUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP:
		SetStep(_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START, _T("_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START"));
		break;
#pragma endregion

	case eCOMBO_AUTO_RUN_FLOW_STICK_TENSION_ONCE: //KJT 20210406
		SetStep(_eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_START, _T("_eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_START"));
		break;
	}

	return TRUE;
}
BOOL CAutoRunFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CAutoRunFlow::ThreadFunction(LPVOID lpParam)
{
	CAutoRunFlow* pFlow = NULL;

	pFlow = (CAutoRunFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CAutoRunFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	DWORD	dPrevTime, dCurrentTime;
	int nHour, nMin, nSec;
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eAUTO_RUN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}
		
		switch (GetCurrentTotalStep())
		{
		case _eAUTO_RUN_FLOW_IDLE:
		{
			break;
		}
		case _eAUTO_RUN_FLOW_START:
		{
			break;
		}

		case _eAUTO_RUN_FLOW_BOX_ALIGN_START:
			Devs::m_BoxAlignFlow.Start(Devs::m_BoxAlignFlow._eBOX_ALIGN_FLOW_START);

			SetStep(_eAUTO_RUN_FLOW_BOX_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_BOX_ALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_BOX_ALIGN_DONE_CHECK:
			if (Devs::m_BoxAlignFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_BOX_ALIGN)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_PAPER_LOAD_UNLOAD;
					SharedInfo::Active.ProcessStep = 1;
					SharedInfo::ActiveInfoSave();
					SetStep(_eAUTO_RUN_FLOW_STICK_PAPER_LOAD_START, _T("_eAUTO_RUN_FLOW_STICK_PAPER_LOAD_START"));
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_BOX_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_BOX_ALIGN_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_STICK_PAPER_LOAD_START:
			Devs::m_StickPaperLoadFlow.Start(); //KJT 20210807 Junying TPCD

			SetStep(_eAUTO_RUN_FLOW_STICK_PAPER_LOAD_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_PAPER_LOAD_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE); //TIME_OUT_FLOW //Temp
			break;

		case _eAUTO_RUN_FLOW_STICK_PAPER_LOAD_DONE_CHECK:
			if (Devs::m_StickPaperLoadFlow.IsFlowDone()) //KJT 20210807 Junying TPCD
			{
				SetStep(_eAUTO_RUN_FLOW_STICK_PAPER_UNLOAD_START, _T("_eAUTO_RUN_FLOW_STICK_PAPER_UNLOAD_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_STICK_PAPER_LOAD_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_PAPER_LOAD_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_STICK_PAPER_UNLOAD_START:
			Devs::m_StickPaperUnloadFlow.Start(); //KJT 20210807 Junying TPCD

			SetStep(_eAUTO_RUN_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE); //TIME_OUT_FLOW //Temp
			break;

		case _eAUTO_RUN_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK:
			if (Devs::m_StickPaperUnloadFlow.IsFlowDone()) //KJT 20210807 Junying TPCD
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_STICK_PAPER_LOAD_UNLOAD)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.bStickTensionOnceDone = FALSE;

					SharedInfo::Active.ProcessStep = 1;
					if (CModelData::m_InspectionPara.Info.bOnlyUnloadModePreAlignUse)
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_PRE_ALIGN;
						//SetStep(_eAUTO_RUN_FLOW_PRE_ALIGN_START, _T("_eAUTO_RUN_FLOW_PRE_ALIGN_START")); //Need Align Test
					}
					else
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
						SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
					}
					SharedInfo::ActiveInfoSave();
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_PRE_ALIGN_START:
			Devs::m_MaskPreAlignFlow.Start(SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_PRE_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_PRE_ALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_PRE_ALIGN_DONE_CHECK:
			if (Devs::m_MaskPreAlignFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_PRE_ALIGN)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{					
					SharedInfo::Active.ProcessStep = 1;
					if (CModelData::m_InspectionPara.Info.bOnlyUnloadingMode)
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
						SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
					}
					else
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_MAIN_ALIGN;							
						SetStep(_eAUTO_RUN_FLOW_MAIN_ALIGN_START, _T("_eAUTO_RUN_FLOW_MAIN_ALIGN_START"));						
					}
					SharedInfo::ActiveInfoSave();
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_PRE_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_PRE_ALIGN_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_MAIN_ALIGN_START:
			Devs::m_MaskMain2PAlignFlow.Start(SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_MAIN_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_MAIN_ALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_MAIN_ALIGN_DONE_CHECK:
			if (Devs::m_MaskMain2PAlignFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_MAIN_ALIGN)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.ProcessStep = 1;
					if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ONCE && SharedInfo::Active.bStickTensionOnceDone == FALSE) //KJT 20210406
					{
						//SharedInfo::Active.bStickTensionOnceDone = FALSE;
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_TENSION_ONCE;
						SetStep(_eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_START, _T("_eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_START"));
					}
					else if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN) //!!
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_CLAMP_TENSION;
						SetStep(_eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_START, _T("_eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_START"));
					}					
					else
					{	
						//if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse)
						//{
						//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_SW_ALIGN;
						//	SetStep(_eAUTO_RUN_FLOW_SW_ALIGN_START, _T("_eAUTO_RUN_FLOW_SW_ALIGN_START"));
						//}
						if (CModelData::m_InspectionPara.Info.bTPUse)
						{
							SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_TP;
							SetStep(_eAUTO_RUN_FLOW_TP_START, _T("_eAUTO_RUN_FLOW_TP_START"));
						}
						else if (CModelData::m_InspectionPara.Info.bPPAUse)
						{
							SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_PPA;
							SetStep(_eAUTO_RUN_FLOW_PPA_START, _T("_eAUTO_RUN_FLOW_PPA_START"));
						}
						//else if (CModelData::m_InspectionPara.Info.bAOIUse)
						//{
						//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI;
						//	SetStep(_eAUTO_RUN_FLOW_AOI_START, _T("_eAUTO_RUN_FLOW_AOI_START"));
						//}
						//else if (CModelData::m_InspectionPara.Info.bAOIReviewUse)
						//{
						//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI_REVIEW;
						//	SetStep(_eAUTO_RUN_FLOW_AOI_REVIEW_START, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_START"));
						//}
						//else if (CModelData::m_InspectionPara.Info.b3dFlowUse)
						//{
						//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_3D;
						//	SetStep(_eAUTO_RUN_FLOW_3D_START, _T("_eAUTO_RUN_FLOW_3D_START"));
						//}
						else
						{
							SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
							SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
						}
					}
					SharedInfo::ActiveInfoSave();
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_MAIN_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_MAIN_ALIGN_DONE_CHECK"));
			}
			break;				

		//case _eAUTO_RUN_FLOW_SW_ALIGN_START: //KJT 20210314
		//	Devs::m_SwAlignFlow.m_eSwAlignType = eSwAlign_EdgeSlot; //KJT 20210419
		//	Devs::m_SwAlignFlow.Start(SharedInfo::Active.ProcessStep);

		//	SetStep(_eAUTO_RUN_FLOW_SW_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_SW_ALIGN_DONE_CHECK"));
		//	SetTimeOut(TIME_OUT_STATE);
		//	break;

		//case _eAUTO_RUN_FLOW_SW_ALIGN_DONE_CHECK: //KJT 20210314
		//	if (Devs::m_SwAlignFlow.IsFlowDone())
		//	{
		//		if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_SW_ALIGN)
		//		{
		//			SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
		//			break;
		//		}
		//		else
		//		{
		//			SharedInfo::Active.ProcessStep = 1;
		//			if (CModelData::m_InspectionPara.Info.bTPUse)
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_TP;
		//				SetStep(_eAUTO_RUN_FLOW_TP_START, _T("_eAUTO_RUN_FLOW_TP_START"));
		//			}
		//			else if (CModelData::m_InspectionPara.Info.bPPAUse)
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_PPA;
		//				SetStep(_eAUTO_RUN_FLOW_PPA_START, _T("_eAUTO_RUN_FLOW_PPA_START"));
		//			}
		//			else if (CModelData::m_InspectionPara.Info.bAOIUse)
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI;
		//				SetStep(_eAUTO_RUN_FLOW_AOI_START, _T("_eAUTO_RUN_FLOW_AOI_START"));
		//			}
		//			else if (CModelData::m_InspectionPara.Info.bAOIReviewUse)
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI_REVIEW;
		//				SetStep(_eAUTO_RUN_FLOW_AOI_REVIEW_START, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_START"));
		//			}
		//			else if (CModelData::m_InspectionPara.Info.b3dFlowUse)
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_3D;
		//				SetStep(_eAUTO_RUN_FLOW_3D_START, _T("_eAUTO_RUN_FLOW_3D_START"));
		//			}
		//			else
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
		//				SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
		//			}
		//			SharedInfo::ActiveInfoSave();
		//		}
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eAUTO_RUN_FLOW_SW_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_SW_ALIGN_DONE_CHECK"));
		//	}
		//	break;

		case _eAUTO_RUN_FLOW_TP_START: //KJT 20210407
			if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
				Devs::m_InspectTPFlow.Start(eAT_TP, SharedInfo::Active.ProcessStep);
			else
				Devs::m_InspectTPFlow.Start(eNORAML_TP, SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_TP_DONE_CHECK, _T("_eAUTO_RUN_FLOW_TP_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_TP_DONE_CHECK: //KJT 20210407
			if (Devs::m_InspectTPFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_TP)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{					
					SharedInfo::Active.ProcessStep = 1;
					if (CModelData::m_InspectionPara.Info.bPPAUse)
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_PPA;
						SetStep(_eAUTO_RUN_FLOW_PPA_START, _T("_eAUTO_RUN_FLOW_PPA_START"));
					}
					//else if (CModelData::m_InspectionPara.Info.bAOIUse)
					//{
					//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI;
					//	SetStep(_eAUTO_RUN_FLOW_AOI_START, _T("_eAUTO_RUN_FLOW_AOI_START"));
					//}
					//else if (CModelData::m_InspectionPara.Info.bAOIReviewUse)
					//{
					//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI_REVIEW;
					//	SetStep(_eAUTO_RUN_FLOW_AOI_REVIEW_START, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_START"));
					//}
					//else if (CModelData::m_InspectionPara.Info.b3dFlowUse)
					//{
					//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_3D;
					//	SetStep(_eAUTO_RUN_FLOW_3D_START, _T("_eAUTO_RUN_FLOW_3D_START"));
					//}
					else
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
						SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
					}
					SharedInfo::ActiveInfoSave();
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_TP_DONE_CHECK, _T("_eAUTO_RUN_FLOW_TP_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_PPA_START:
			if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
				Devs::m_InspectPpaFlow.Start(eAT_PPA, SharedInfo::Active.ProcessStep);
			else
				Devs::m_InspectPpaFlow.Start(eNORAML_PPA, SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_PPA_DONE_CHECK, _T("_eAUTO_RUN_FLOW_PPA_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_PPA_DONE_CHECK:
			if (Devs::m_InspectPpaFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_PPA)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.ProcessStep = 1;
					if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
					{
						//if (CModelData::m_InspectionPara.Info.bAOIUse)
						//{
						//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI;
						//	SetStep(_eAUTO_RUN_FLOW_AOI_START, _T("_eAUTO_RUN_FLOW_AOI_START"));
						//}
						//else if (CModelData::m_InspectionPara.Info.bAOIReviewUse)
						//{
						//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI_REVIEW;
						//	SetStep(_eAUTO_RUN_FLOW_AOI_REVIEW_START, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_START"));
						//}
						//else if (CModelData::m_InspectionPara.Info.b3dFlowUse)
						//{
						//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_3D;
						//	SetStep(_eAUTO_RUN_FLOW_3D_START, _T("_eAUTO_RUN_FLOW_3D_START"));
						//}
						//else
						{
							SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
							SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
						}
					}
					else
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP;
						SetStep(_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START, _T("_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START"));
					}
					SharedInfo::ActiveInfoSave();
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_PPA_DONE_CHECK, _T("_eAUTO_RUN_FLOW_PPA_DONE_CHECK"));
			}
			break;

		//case _eAUTO_RUN_FLOW_AOI_START:
		//	Devs::m_AoiFlow.Start(SharedInfo::Active.ProcessStep);

		//	SetStep(_eAUTO_RUN_FLOW_AOI_DONE_CHECK, _T("_eAUTO_RUN_FLOW_AOI_DONE_CHECK"));
		//	SetTimeOut(TIME_OUT_STATE);
		//	break;

		//case _eAUTO_RUN_FLOW_AOI_DONE_CHECK:
		//	if (Devs::m_AoiFlow.IsFlowDone())
		//	{
		//		//if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_AOI)
		//		//{
		//		//	SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
		//		//	break;
		//		//}
		//		//else
		//		{
		//			SharedInfo::Active.ProcessStep = 1;
		//			//if (CModelData::m_InspectionPara.Info.bAOIReviewUse)
		//			//{
		//			//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI_REVIEW;
		//			//	SetStep(_eAUTO_RUN_FLOW_AOI_REVIEW_START, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_START"));
		//			//}
		//			//else if (CModelData::m_InspectionPara.Info.b3dFlowUse)
		//			//{
		//			//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_3D;
		//			//	SetStep(_eAUTO_RUN_FLOW_3D_START, _T("_eAUTO_RUN_FLOW_3D_START"));
		//			//}
		//			//else
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
		//				SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
		//			}
		//			SharedInfo::ActiveInfoSave();
		//		}
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eAUTO_RUN_FLOW_AOI_DONE_CHECK, _T("_eAUTO_RUN_FLOW_AOI_DONE_CHECK"));
		//	}
		//	break;

		//case _eAUTO_RUN_FLOW_AOI_REVIEW_START:
		//	Devs::m_AoiReviewFlow.Start(SharedInfo::Active.ProcessStep);

		//	SetStep(_eAUTO_RUN_FLOW_AOI_REVIEW_DONE_CHECK, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_DONE_CHECK"));
		//	SetTimeOut(TIME_OUT_STATE);
		//	break;

		//case _eAUTO_RUN_FLOW_AOI_REVIEW_DONE_CHECK:
		//	if (Devs::m_AoiReviewFlow.IsFlowDone())
		//	{
		//		//if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_AOI_REVIEW)
		//		//{
		//		//	SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
		//		//	break;
		//		//}
		//		//else
		//		{
		//			SharedInfo::Active.ProcessStep = 1;
		//			//if (CModelData::m_InspectionPara.Info.b3dFlowUse)
		//			//{
		//			//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_3D;
		//			//	SetStep(_eAUTO_RUN_FLOW_3D_START, _T("_eAUTO_RUN_FLOW_3D_START"));
		//			//}
		//			//else
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
		//				SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
		//			}
		//			SharedInfo::ActiveInfoSave();
		//		}
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eAUTO_RUN_FLOW_AOI_REVIEW_DONE_CHECK, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_DONE_CHECK"));
		//	}
		//	break;

		//case _eAUTO_RUN_FLOW_3D_START:
		//	if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
		//		Devs::m_3DFlow.Start(eAT_3D, SharedInfo::Active.ProcessStep);
		//	else
		//		Devs::m_3DFlow.Start(eNORAML_3D, SharedInfo::Active.ProcessStep);

		//	SetStep(_eAUTO_RUN_FLOW_3D_DONE_CHECK, _T("_eAUTO_RUN_FLOW_3D_DONE_CHECK"));
		//	SetTimeOut(TIME_OUT_STATE);
		//	break;

		//case _eAUTO_RUN_FLOW_3D_DONE_CHECK:
		//	if (Devs::m_3DFlow.IsFlowDone())
		//	{
		//		if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_3D)
		//		{
		//			SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
		//			break;
		//		}
		//		else
		//		{
		//			//KJT 20210406
		//			SharedInfo::Active.ProcessStep = 1;
		//			if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN) //!!
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP;
		//				SetStep(_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START, _T("_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START"));
		//			}
		//			else
		//			{
		//				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
		//				SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
		//			}
		//			SharedInfo::ActiveInfoSave();
		//		}
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eAUTO_RUN_FLOW_3D_DONE_CHECK, _T("_eAUTO_RUN_FLOW_3D_DONE_CHECK"));
		//	}
		//	break;

		case _eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START:
			Devs::m_StickUnloadInStageToCstFlow.Start();

			SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_DONE_CHECK:
#if 0
			if (Devs::m_StickUnloadInStageToCstFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST)
				{
					if (SharedInfo::BoxStickExistInfo.nStickCount > 0 && SharedInfo::BoxStickExistInfo.bUse[SharedInfo::BoxStickExistInfo.nStickCount - 1]) //KJT 20210421
					{
						SharedInfo::CalTactTime(_T("AUTO_RUN_FLOW (1Cycle)"), m_timeCycleStart); //KJT 20210415
						m_timeCycleStart = CTime::GetCurrentTime(); //KJT 20210415

						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_PAPER_UNLOAD; //Default B12 IQC
						SharedInfo::Active.ProcessStep = 1;
						SetStep(_eAUTO_RUN_FLOW_PAPER_UNLOAD_START, _T("_eAUTO_RUN_FLOW_PAPER_UNLOAD_START"));
					}
					else
					{
						SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					}
				}
				else
				{
					SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_PAPER_UNLOAD; //Default B12 IQC
					SharedInfo::Active.ProcessStep = 1;
					SetStep(_eAUTO_RUN_FLOW_PAPER_UNLOAD_START, _T("_eAUTO_RUN_FLOW_PAPER_UNLOAD_START"));
				}
				SharedInfo::ActiveInfoSave();
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_DONE_CHECK"));
			}
#endif
			if (Devs::m_StickUnloadInStageToCstFlow.GetCurrentFlowStep() > Devs::m_StickUnloadInStageToCstFlow._eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS &&
				Devs::m_UnloaderMotion.Is_GantryY_StickUnloadToCstPos(0) &&
				SharedInfo::BoxStickExistInfo.nStickCount > 0 && SharedInfo::BoxStickExistInfo.bUse[eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount]) //KJT 20210421
			{
				SharedInfo::CalTactTime(_T("AUTO_RUN_FLOW (1Cycle)"), m_timeCycleStart); //KJT 20210415
				m_timeCycleStart = CTime::GetCurrentTime(); //KJT 20210415

				SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_BOX_ALIGN;
				SharedInfo::Active.ProcessStep = 1;
				SetStep(_eAUTO_RUN_FLOW_BOX_ALIGN_START, _T("_eAUTO_RUN_FLOW_BOX_ALIGN_START"));
			}
			else if (Devs::m_StickUnloadInStageToCstFlow.IsFlowDone())
			{
				SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_DONE_CHECK"));
			}
			break;

#pragma region //Tension Flow
		case _eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_START:
			Devs::m_StickClampTensionFlow.Start(SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_DONE_CHECK:
			if (Devs::m_StickClampTensionFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_STICK_CLAMP_TENSION)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_PRE_TENSION_ALIGN;
					SharedInfo::Active.ProcessStep = 1;
					SharedInfo::ActiveInfoSave();
					SetStep(_eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_START, _T("_eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_START"));
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_CLAMP_TENSION_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_START:
			Devs::m_MaskPreTensionAlignFlow.Start(SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_DONE_CHECK:
			if (Devs::m_MaskPreTensionAlignFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_PRE_TENSION_ALIGN)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_MAIN_TENSION_ALIGN;
					SharedInfo::Active.ProcessStep = 1;
					SharedInfo::ActiveInfoSave();
					SetStep(_eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_START, _T("_eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_START"));
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_PRE_TENSION_ALIGN_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_START:
			Devs::m_MaskMain2PTensionAlignFlow.Start(SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_DONE_CHECK:
			if (Devs::m_MaskMain2PTensionAlignFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_MAIN_TENSION_ALIGN)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_EDGE_TENSION_ALIGN;
					SharedInfo::Active.ProcessStep = 1;
					SharedInfo::ActiveInfoSave();
					SetStep(_eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_START, _T("_eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_START"));
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_MAIN_TENSION_ALIGN_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_START:
			Devs::m_MaskEdgeTensionAlignFlow.Start(SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_DONE_CHECK:
			if (Devs::m_MaskEdgeTensionAlignFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_EDGE_TENSION_ALIGN)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.ProcessStep = 1;
					//if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse)
					//{
					//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_SW_ALIGN;
					//	SetStep(_eAUTO_RUN_FLOW_SW_ALIGN_START, _T("_eAUTO_RUN_FLOW_SW_ALIGN_START"));
					//}
					if (CModelData::m_InspectionPara.Info.bTPUse) //KJT 20210406
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_TP;
						SetStep(_eAUTO_RUN_FLOW_TP_START, _T("_eAUTO_RUN_FLOW_TP_START"));
					}					
					else if (CModelData::m_InspectionPara.Info.bPPAUse)
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_PPA;
						SetStep(_eAUTO_RUN_FLOW_PPA_START, _T("_eAUTO_RUN_FLOW_PPA_START"));
					}
					//else if (CModelData::m_InspectionPara.Info.bAOIUse)
					//{
					//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI;
					//	SetStep(_eAUTO_RUN_FLOW_AOI_START, _T("_eAUTO_RUN_FLOW_AOI_START"));
					//}
					//else if (CModelData::m_InspectionPara.Info.bAOIReviewUse)
					//{
					//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_AOI_REVIEW;
					//	SetStep(_eAUTO_RUN_FLOW_AOI_REVIEW_START, _T("_eAUTO_RUN_FLOW_AOI_REVIEW_START"));
					//}
					//else if (CModelData::m_InspectionPara.Info.b3dFlowUse)
					//{
					//	SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_3D;
					//	SetStep(_eAUTO_RUN_FLOW_3D_START, _T("_eAUTO_RUN_FLOW_3D_START"));
					//}
					//else
					{
						SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP;
						SetStep(_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START, _T("_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START"));
					}
					SharedInfo::ActiveInfoSave();
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_DONE_CHECK, _T("_eAUTO_RUN_FLOW_EDGE_TENSION_ALIGN_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_START:
			Devs::m_StickReleaseUnclampFlow.Start(SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_DONE_CHECK:
			if (Devs::m_StickReleaseUnclampFlow.IsFlowDone())
			{
				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
					break;
				}
				else
				{
					SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST;
					SharedInfo::Active.ProcessStep = 1;
					SharedInfo::ActiveInfoSave();
					SetStep(_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START, _T("_eAUTO_RUN_FLOW_STICK_UNLOAD_IN_STAGE_TO_CST_START"));
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_DONE_CHECK, _T("_eAUTO_RUN_FLOW_STICK_RELEASE_UNCLAMP_DONE_CHECK"));
			}
			break;
#pragma endregion

		case _eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_START: //KJT 20210406
			Devs::m_StickClampTensionUnclampFlow.Start(SharedInfo::Active.ProcessStep);

			SetStep(_eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_DONE_CHECK, _T("_eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_DONE_CHECK: //KJT 20210406
			if (Devs::m_StickClampTensionUnclampFlow.IsFlowDone())
			{
				SharedInfo::Active.bStickTensionOnceDone = TRUE; //KJT 20210406

				if (SharedInfo::Active.ProcessEndFlow == eCOMBO_AUTO_RUN_FLOW_STICK_TENSION_ONCE)
				{
					SetStep(_eAUTO_RUN_FLOW_DONE, _T("_eAUTO_RUN_FLOW_DONE"));
				}
				else
				{
					SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_MAIN_ALIGN;
					SharedInfo::Active.ProcessStep = 1;
					SetStep(_eAUTO_RUN_FLOW_MAIN_ALIGN_START, _T("_eAUTO_RUN_FLOW_MAIN_ALIGN_START"));
				}
				SharedInfo::ActiveInfoSave();
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_RUN_FLOW_ERROR, _T("_eAUTO_RUN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_DONE_CHECK, _T("_eAUTO_RUN_FLOW_SITCK_TENSION_ONCE_DONE_CHECK"));
			}
			break;

		case _eAUTO_RUN_FLOW_ERROR:
			
			break;

		case _eAUTO_RUN_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::Active.ProcessStartFlow = eCOMBO_AUTO_RUN_FLOW_BOX_ALIGN; //Default Junying TPCD
			SharedInfo::ActiveInfoSave();

			//Devs::CimMotion.SetMachineAutoModeOnOff(FALSE);

			SharedInfo::CalTactTime(_T("AUTO_RUN_FLOW"), m_timeStart); //KJT 20210329
			
			SetStep(_eAUTO_RUN_FLOW_IDLE, _T("_eAUTO_RUN_FLOW_IDLE"));
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