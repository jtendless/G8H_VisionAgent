#include "stdafx.h"
#include "LoaderMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"
#include "Data/MachineData.h"
#include "Data/ModelData.h"

CLoaderMotion::CLoaderMotion()
{
}


CLoaderMotion::~CLoaderMotion()
{
}

BOOL CLoaderMotion::InitProcess()
{
	//m_bTerminate = FALSE;
	m_StateFinish = TRUE;
	
	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	hMotionHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hMotionHandle);
	pMotionThread = AfxBeginThread(MotionThreadFunction, this);// , THREAD_PRIORITY_ABOVE_NORMAL);

	return TRUE;
}

BOOL CLoaderMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(eLOADER_MOTION_IDLE, FALSE);

	if (hMotionHandle != NULL)
	{
		CloseHandle(hMotionHandle);
		hMotionHandle = NULL;
	}
#if 0
	do
	{
		Sleep(10);
	} while (m_bTerminate == 0);
#endif
	//delete this;

	return TRUE;
}

BOOL CLoaderMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CLoaderMotion::MotionThreadFunction(LPVOID lpParam)
{
	CLoaderMotion* pLoaderMotion = NULL;

	pLoaderMotion = (CLoaderMotion*)lpParam;

	pLoaderMotion->MotionThreadFunctionEntry();

	pLoaderMotion->m_bTerminate = 1;

	return 0;
}

VOID CLoaderMotion::MotionThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;

	while (m_StateFinish)
	{
		WaitForSingleObject(hMotionHandle, INFINITE);
		ResetEvent(hMotionHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eLOADER_MOTION_IDLE); //KJT 20210318
			continue; //!!
		}

	
		switch (GetCurrentTotalStep())
		{
		case eLOADER_MOTION_IDLE:			
			break;

		case eLOADER_MOTION_ERROR:
			break;
		
		case eLOADER_MOTION_DONE:
			m_bMotionDone = TRUE;
			SetStep(eLOADER_MOTION_IDLE, _T("eLOADER_MOTION_IDLE"));
			break;

		case eLOADER_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;
		}
	}
}

BOOL CLoaderMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CLoaderMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//현재 모터의 파라미터 받아오기
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//해당 모터에 파라미터 전달
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CLoaderMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

#pragma region //Loader Z
//Move
BOOL CLoaderMotion::LoaderZ_WaitPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Z Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderZ_StickLoadInBox1stPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInBox1st_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Z Move To Stick Load In Box 1st Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderZ_Vibration_Pos() //KJT 20210317
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Z Move To Vibration Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderZ_PaperUnloadPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_PaperUnloader_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Z Move To Paper Unload Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderZ_StickUnloadToStagePos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnloadToStage_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Z Move To Stick Unload To Stage Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderZ_StickLoadInStage1stPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInStage1st_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Z Move To Stick Load In Stage 1st Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CLoaderMotion::LoaderZ_StickUnloadToBoxPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnoadToBox_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Z Move To Stick Unload To Box Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//MoveDone Check
BOOL CLoaderMotion::Is_LoaderZ_WaitPos()
{
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderZ_StickLoadInBox1stPos()
{
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInBox1st_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderZ_Vibration_Pos() //KJT 20210317
{
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderZ_PaperUnloadPos()
{
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_PaperUnloader_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderZ_StickUnloadToStagePos()
{
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnloadToStage_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderZ_StickLoadInStage1stPos()
{
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInStage1st_Pos;
	return IsMoveDone(eAxis, dPos);
}

BOOL CLoaderMotion::Is_LoaderZ_StickUnloadToBoxPos()
{
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnoadToBox_Pos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //Loader Sub Z(ZL,ZR) // 21.02.05 sjc // 21.02.28 sjc
//Move
//BOOL CLoaderMotion::LoaderZL_WaitPos()
//{
//	CString Str = _T("");
//	enum_Axis eAxis = AXIS_LOADER_ZL;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Wait_Pos;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Loader ZL Move To Wait Pos (Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
//BOOL CLoaderMotion::LoaderZR_WaitPos()
//{
//	CString Str = _T("");
//	enum_Axis eAxis = AXIS_LOADER_ZR;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Wait_Pos;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Loader ZR Move To Wait Pos (Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
//
//BOOL CLoaderMotion::LoaderZL_DownPos()
//{
//	CString Str = _T("");
//	enum_Axis eAxis = AXIS_LOADER_ZL;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Down_Pos;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Loader ZL Move To Down Pos (Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
//BOOL CLoaderMotion::LoaderZR_DownPos()
//{
//	CString Str = _T("");
//	enum_Axis eAxis = AXIS_LOADER_ZR;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Down_Pos;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Loader ZR Move To Down Pos (Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
////MoveDone Check
//BOOL CLoaderMotion::Is_LoaderZL_WaitPos()
//{
//	enum_Axis eAxis = AXIS_LOADER_ZL;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Wait_Pos;
//	return IsMoveDone(eAxis, dPos);
//}
//BOOL CLoaderMotion::Is_LoaderZR_WaitPos()
//{
//	enum_Axis eAxis = AXIS_LOADER_ZR;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Wait_Pos;
//	return IsMoveDone(eAxis, dPos);
//}
//BOOL CLoaderMotion::Is_LoaderZL_DownPos()
//{
//	enum_Axis eAxis = AXIS_LOADER_ZL;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Down_Pos;
//	return IsMoveDone(eAxis, dPos);
//}
//BOOL CLoaderMotion::Is_LoaderZR_DownPos()
//{
//	enum_Axis eAxis = AXIS_LOADER_ZR;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Down_Pos;
//	return IsMoveDone(eAxis, dPos);
//}
#pragma endregion

#pragma region //Loader X
//Move
BOOL CLoaderMotion::LoaderX_WaitPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_X;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderX_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader X Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderX_AlignPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_X;
	double dPos = CModelData::m_ModelSubManualPara.Info.dStickLoaderX_AlignPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader X Move To Align Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderX_StickPickUpPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_X;
	double dPos = CModelData::m_ModelSubManualPara.Info.dStickLoaderX_PickUpPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader X Move To StickPickUp Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//MoveDone Check
BOOL CLoaderMotion::Is_LoaderX_WaitPos()
{
	enum_Axis eAxis = AXIS_LOADER_X;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderX_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL  CLoaderMotion::Is_LoaderX_AlignPos()
{
	enum_Axis eAxis = AXIS_LOADER_X;
	double dPos = CModelData::m_ModelSubManualPara.Info.dStickLoaderX_AlignPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL  CLoaderMotion::Is_LoaderX_StickPickUpPos()
{
	enum_Axis eAxis = AXIS_LOADER_X;
	double dPos = CModelData::m_ModelSubManualPara.Info.dStickLoaderX_PickUpPos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //Loader Y //21.02.15 sjc
//Move
BOOL CLoaderMotion::LoaderY_WaitPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Y Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderY_Stick_LoadPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Load_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Y Move To Stick Loading Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderY_Stick_UnloadPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Unload_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Y Move To Stick Unloading Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderY_Paper_LoadPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Paper_Load_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Y Move To Paper Loading Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderY_Paper_UnloadPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Paper_Unload_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Y Move To Paper Unloading Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CLoaderMotion::LoaderY_Inspection_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Inspection_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Y Move To Box Align Inspect Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//21.02.26 sjc
BOOL CLoaderMotion::LoaderZ_Inspection_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Inspection_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Loader Z Move To Box Align Inspect Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//Check
BOOL CLoaderMotion::Is_LoaderY_WaitPos()
{
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderY_Stick_LoadPos()
{
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Load_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderY_Stick_UnloadPos()
{
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Unload_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderY_Paper_LoadPos()
{
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Paper_Load_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderY_Paper_UnloadPos()
{
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Paper_Unload_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CLoaderMotion::Is_LoaderY_Inspection_Pos()
{
	enum_Axis eAxis = AXIS_LOADER_YL;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Inspection_Pos;
	return IsMoveDone(eAxis, dPos);
}
//21.02.26 sjc
BOOL CLoaderMotion::Is_LoaderZ_Inspection_Pos()
{
	enum_Axis eAxis = AXIS_LOADER_Z;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Inspection_Pos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //IO
//Loader Vac
BOOL	CLoaderMotion::Stick_Vac_On(int nFinger)
{
	CString Str = _T("LD Stick Vac On (");
	int i = 0;
	int vac_num[5] = { _DOUT_LD_STICK_VAC_1 ,_DOUT_LD_STICK_VAC_2 ,_DOUT_LD_STICK_VAC_3 ,_DOUT_LD_STICK_VAC_4, _DOUT_LD_STICK_VAC_5 };
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			SetDOutputBitValue((enum_Do)vac_num[i], TRUE);
			Str.AppendFormat(_T("%d, "), i + 1);
			Sleep(10);
		}
	}
	Str.AppendFormat(_T(")"));
	Total_Msg(Str);

	return TRUE;
}
BOOL	CLoaderMotion::Stick_Vac_Off(int nFinger)
{
	Stick_Blow_On();
	Sleep(1000);
	int vac_num[5] = { _DOUT_LD_STICK_VAC_1 ,_DOUT_LD_STICK_VAC_2 ,_DOUT_LD_STICK_VAC_3 ,_DOUT_LD_STICK_VAC_4, _DOUT_LD_STICK_VAC_5 };
	CString Str = _T("LD Stick Vac Off (");
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			SetDOutputBitValue((enum_Do)vac_num[i], FALSE);
			Str.AppendFormat(_T("%d, "), i + 1);
			Sleep(10);
		}
	}
	Str.AppendFormat(_T(")"));
	Total_Msg(Str);

	Sleep(1000);
	Stick_Blow_Off();

	return TRUE;
}
BOOL	CLoaderMotion::Stick_Active_Vac_On()
{
	int nFinger = (CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick1 << 0) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick2 << 1) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick3 << 2) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick4 << 3) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick5 << 4);
	
	Devs::m_LoaderMotion.Stick_Vac_On(nFinger);
	return TRUE;
}
BOOL	CLoaderMotion::Stick_Active_Vac_Off()
{
	int nFinger = (CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick1 << 0) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick2 << 1) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick3 << 2) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick4 << 3) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick5 << 4);

	Devs::m_LoaderMotion.Stick_Vac_Off(nFinger);
	return TRUE;
}
BOOL	CLoaderMotion::Stick_Blow_On()
{
	SetDOutputBitValue((enum_Do)_DOUT_STICK_LD_BLOW, TRUE);
	Sleep(10);
	
	Total_Msg(_T("LD Stick Purge On"));
	return TRUE;
}
BOOL	CLoaderMotion::Stick_Blow_Off()
{
	SetDOutputBitValue((enum_Do)_DOUT_STICK_LD_BLOW, FALSE);
	Sleep(10);

	Total_Msg(_T("LD Stick Purge Off"));
	return TRUE;
}
BOOL	CLoaderMotion::Stick_All_Vac_On()
{
	BOOL bRtn = Stick_Vac_On(eVAC_LOADER_STICK_ALL);

	//Total_Msg(_T("LD Stick All Vac On"));
	return bRtn;
}
BOOL	CLoaderMotion::Stick_All_Vac_Off()
{
	BOOL bRtn = Stick_Vac_Off(eVAC_LOADER_STICK_ALL);

	//Total_Msg(_T("LD Stick All Vac Off"));
	return bRtn;
}
BOOL	CLoaderMotion::Is_Stick_Vac_On(int nFinger)
{
#ifdef SIM_MODE
	return TRUE;
#endif

	int i = 0;

	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			//if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 + (i*2)] == FALSE || SharedInfo::DInputValue[_DIN_LD_STICK_VAC_2 + (i*2)] == FALSE)
			//if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 + i] == FALSE )
			if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 - i] == FALSE) //KJT 20210723 Junying
				return FALSE;
		}
	}

	return TRUE;
}
BOOL	CLoaderMotion::Is_Stick_Vac_Off(int nFinger)
{
#ifdef SIM_MODE
	return TRUE;
#endif

	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			//if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 + (i * 2)] == TRUE || SharedInfo::DInputValue[_DIN_LD_STICK_VAC_2 + (i * 2)] == TRUE)
			//	return FALSE;

			//if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 + i] == TRUE)
			if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 - i] == TRUE) //KJT 20210723 Junying
				return FALSE;
		}
	}

	return TRUE;
}
BOOL	CLoaderMotion::Is_Stick_Active_Vac_On()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//sunghaklee : Imsi
	//return TRUE;

	int nFinger = (CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick1 << 0) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick2 << 1) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick3 << 2) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick4 << 3) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick5 << 4);

	if (Devs::m_LoaderMotion.Is_Stick_Vac_On(nFinger))
		return TRUE;
	else
		return FALSE;
}
BOOL	CLoaderMotion::Is_Stick_Active_Vac_Off()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//sunghaklee : Imsi
	//return TRUE;

	int nFinger = (CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick1 << 0) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick2 << 1) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick3 << 2) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick4 << 3) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick5 << 4);

	if (Devs::m_LoaderMotion.Is_Stick_Vac_Off(nFinger))
		return TRUE;
	else
		return FALSE;
}
BOOL	CLoaderMotion::Is_Stick_Blow_On()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//int i = 0;
	//for (i = 0; i < 5; i++)
	//{
	//	if (nFinger >> i & 1 == 1)
	//	{
	//		if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1_OUTPUT + i] == FALSE)
	//			return FALSE;
	//	}
	//}

	return TRUE;
}
BOOL	CLoaderMotion::Is_Stick_Blow_Off()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//int i = 0;
	//for (i = 0; i < 5; i++)
	//{
	//	if (nFinger >> i & 1 == 1)
	//	{
	//		if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1_OUTPUT + i] == TRUE)
	//			return FALSE;
	//	}
	//}

	return TRUE;
}
BOOL	CLoaderMotion::Is_Stick_All_Vac_On()
{
	BOOL bRtn = Is_Stick_Vac_On(eVAC_LOADER_STICK_ALL);

	return bRtn;
}
BOOL	CLoaderMotion::Is_Stick_All_Vac_Off()
{
	BOOL bRtn = Is_Stick_Vac_Off(eVAC_LOADER_STICK_ALL);

	return bRtn;
}
BOOL	CLoaderMotion::Paper_Vac_On(int nFinger)
{
	//CString Str = _T("LD Paper Vac On (");
	//int i = 0;
	//int vacDoutNum[4] = { _DOUT_LD_PAPER_VAC_1 ,_DOUT_LD_PAPER_VAC_2,_DOUT_LD_PAPER_VAC_3,_DOUT_LD_PAPER_VAC_4};
	//for (i = 0; i < 4; i++)
	//{
	//	if (((nFinger >> i) & 1) == 1)
	//	{
	//		SetDOutputBitValue((enum_Do)(vacDoutNum[i]), TRUE);
	//		Str.AppendFormat(_T("%d, "), i + 1);
	//		Sleep(10);
	//	}
	//}
	//Str.AppendFormat(_T(")"));
	//Total_Msg(Str);

	return TRUE;
}
BOOL	CLoaderMotion::Paper_Vac_Off(int nFinger)
{
	//Paper_Blow_On();
	//Sleep(1000);
	//int vacDoutNum[4] = { _DOUT_LD_PAPER_VAC_1 ,_DOUT_LD_PAPER_VAC_2,_DOUT_LD_PAPER_VAC_3,_DOUT_LD_PAPER_VAC_4 };
	//CString Str = _T("LD Paper Vac Off (");
	//int i = 0;
	//for (i = 0; i < 4; i++)
	//{
	//	if (((nFinger >> i) & 1) == 1)
	//	{
	//		SetDOutputBitValue((enum_Do)(vacDoutNum[i]), FALSE);
	//		Str.AppendFormat(_T("%d, "), i + 1);
	//		Sleep(10);
	//	}
	//}
	//Str.AppendFormat(_T(")"));
	//Total_Msg(Str);

	//Sleep(1000);
	//Paper_Blow_Off();

	return TRUE;
}
BOOL	CLoaderMotion::Paper_Active_Vac_On()
{	
	int nFinger = (CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper1 << 0) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper2 << 1) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper3 << 2) | 
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper4 << 3);

	Devs::m_LoaderMotion.Paper_Vac_On(nFinger);
	return TRUE;
}
BOOL	CLoaderMotion::Paper_Active_Vac_Off()
{
	int nFinger = (CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper1 << 0) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper2 << 1) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper3 << 2) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper4 << 3);

	Devs::m_LoaderMotion.Paper_Vac_Off(nFinger);
	return TRUE;
}
BOOL	CLoaderMotion::Paper_Blow_On()
{
	//SetDOutputBitValue((enum_Do)_DOUT_LD_PAPER_PURGE_1, TRUE);
	//Sleep(10);
	//SetDOutputBitValue((enum_Do)_DOUT_LD_PAPER_PURGE_2, TRUE);
	//Sleep(10);
	//SetDOutputBitValue((enum_Do)_DOUT_LD_PAPER_PURGE_3, TRUE);
	//Sleep(10);
	//SetDOutputBitValue((enum_Do)_DOUT_LD_PAPER_PURGE_4, TRUE);

	Total_Msg(_T("LD Paper Blow On"));
	return TRUE;
}
BOOL	CLoaderMotion::Paper_Blow_Off()
{
	//SetDOutputBitValue((enum_Do)_DOUT_LD_PAPER_PURGE_1, FALSE);
	//Sleep(10);
	//SetDOutputBitValue((enum_Do)_DOUT_LD_PAPER_PURGE_2, FALSE);
	//Sleep(10);
	//SetDOutputBitValue((enum_Do)_DOUT_LD_PAPER_PURGE_3, FALSE);
	//Sleep(10);
	//SetDOutputBitValue((enum_Do)_DOUT_LD_PAPER_PURGE_4, FALSE);


	Total_Msg(_T("LD Paper Blow Off"));
	return TRUE;
}
BOOL	CLoaderMotion::Paper_All_Vac_On()
{
	BOOL bRtn = Paper_Vac_On(eVAC_LOADER_PAPER_ALL);

	//Total_Msg(_T("LD Paper All Vac On"));
	return bRtn;
}
BOOL	CLoaderMotion::Paper_All_Vac_Off()
{
	BOOL bRtn = Paper_Vac_Off(eVAC_LOADER_PAPER_ALL);

	//Total_Msg(_T("LD Paper All Vac Off"));
	return bRtn;
}
BOOL	CLoaderMotion::Is_Paper_Vac_On(int nFinger)
{
#ifdef SIM_MODE
	return TRUE;
#endif

	int i = 0;
	for (i = 0; i < 4; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			//if (SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + (i*2)] == FALSE && SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_2 + (i * 2)] == FALSE)
			//if (SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + i] == FALSE)
			//	return FALSE;
		}
	}

	return TRUE;
}
BOOL	CLoaderMotion::Is_Paper_Vac_Off(int nFinger)
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//sunghaklee : Imsi
	//return TRUE;

	int i = 0;
	for (i = 0; i < 4; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			//if (SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + (i * 2)] == TRUE && SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_2 + (i * 2)] == TRUE)
			//if (SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + i] == TRUE)
			//	return FALSE;
		}
	}

	return TRUE;
}
BOOL	CLoaderMotion::Is_Paper_Active_Vac_On()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//sunghaklee : Imsi
	//return TRUE;

	int nFinger = (CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper1 << 0) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper2 << 1) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper3 << 2) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper4 << 3);

	if (Devs::m_LoaderMotion.Is_Paper_Vac_On(nFinger))
		return TRUE;
	else
		return FALSE;
}
BOOL	CLoaderMotion::Is_Paper_Active_Vac_Off()
{
#ifdef SIM_MODE
	return TRUE;
#endif
	//sunghaklee : Imsi
	//return TRUE;

	int nFinger = (CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper1 << 0) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper2 << 1) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper3 << 2) |
		(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper4 << 3);

	if (Devs::m_LoaderMotion.Is_Paper_Vac_Off(nFinger))
		return TRUE;
	else
		return FALSE;
}
BOOL	CLoaderMotion::Is_Paper_Blow_On()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//int nFinger = eFinger;
	//int i = 0;
	//for (i = 0; i < 4; i++)
	//{
	//	if (nFinger >> i & 1 == 1)
	//	{
	//		if (SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1_2_OUTPUT + i] == FALSE)
	//			return FALSE;
	//	}
	//}

	return TRUE;
}
BOOL	CLoaderMotion::Is_Paper_Blow_Off()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//int nFinger = eFinger;
	//int i = 0;
	//for (i = 0; i < 4; i++)
	//{
	//	if (nFinger >> i & 1 == 1)
	//	{
	//		if (SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1_2_OUTPUT + i] == TRUE)
	//			return FALSE;
	//	}
	//}

	return TRUE;
}
//BOOL	CLoaderMotion::Is_Paper_All_Vac_On()
//{
//	BOOL bRtn = Is_Paper_Vac_On(eVAC_LOADER_PAPER_ALL);
//
//	return bRtn;
//}
//BOOL	CLoaderMotion::Is_Paper_All_Vac_Off()
//{
//	BOOL bRtn = Is_Paper_Vac_Off(eVAC_LOADER_PAPER_ALL);
//
//	return bRtn;
//}

BOOL    CLoaderMotion::Is_PaperBox_Fwd()
{
	//if (SharedInfo::DInputValue[_DIN_LOAD_PAPER_BOX_FWD] == TRUE)
	//{
	//	return TRUE;
	//}

	return FALSE;
}

//Loader Cylinder UpDown
BOOL	CLoaderMotion::Cylinder_Up()
{
	//21.02.04 sjc temp
	return TRUE;
	//SetDOutputBitValue((enum_Do)(_DOUT_LD_CYLINDER_DOWN_LR), FALSE);
	//Sleep(200);
	//SetDOutputBitValue((enum_Do)(_DOUT_LD_CYLINDER_UP_LR), TRUE);

	//Total_Msg(_T("LD Cylinder Up"));
	//return TRUE;
}
BOOL	CLoaderMotion::Is_Cylinder_Up()
{
	//21.02.04 sjc temp
	return TRUE;
	//if ((SharedInfo::DInputValue[_DIN_LD_CYLINDER_DOWN_L] == FALSE && SharedInfo::DInputValue[_DIN_LD_CYLINDER_DOWN_R] == FALSE) &&
	//	(SharedInfo::DInputValue[_DIN_LD_CYLINDER_UP_L] == TRUE && SharedInfo::DInputValue[_DIN_LD_CYLINDER_UP_R] == TRUE))
	//	return TRUE;
	//else
	//	return FALSE;
}
BOOL	CLoaderMotion::Cylinder_Down()
{
	//21.02.04 sjc temp
	return TRUE;
	//SetDOutputBitValue((enum_Do)(_DOUT_LD_CYLINDER_UP_LR), FALSE);
	//Sleep(200);
	//SetDOutputBitValue((enum_Do)(_DOUT_LD_CYLINDER_DOWN_LR), TRUE);

	//Total_Msg(_T("LD Cylinder Down"));
	//return TRUE;
}
BOOL	CLoaderMotion::Is_Cylinder_Down()
{
	//21.02.04 sjc temp
	return TRUE;
	//if ((SharedInfo::DInputValue[_DIN_LD_CYLINDER_DOWN_L] == TRUE && SharedInfo::DInputValue[_DIN_LD_CYLINDER_DOWN_R] == TRUE) &&
	//	(SharedInfo::DInputValue[_DIN_LD_CYLINDER_UP_L] == FALSE && SharedInfo::DInputValue[_DIN_LD_CYLINDER_UP_R] == FALSE))
	//	return TRUE;
	//else
	//	return FALSE;
}
BOOL	CLoaderMotion::Ionizer_On()
{
	SetDOutputBitValue((enum_Do)(_DOUT_IONIZER_SOL_OFF), FALSE);
	Sleep(200);
	SetDOutputBitValue((enum_Do)(_DOUT_IONIZER_SOL_ON), TRUE);
	Sleep(200);

	Total_Msg(_T("Ionizer On"));
	return TRUE;
}
BOOL	CLoaderMotion::Is_Ionizer_On()
{
	if (SharedInfo::DOutputValue[_DOUT_IONIZER_SOL_OFF] == FALSE &&
		SharedInfo::DOutputValue[_DOUT_IONIZER_SOL_ON] == TRUE )
		return TRUE;
	else
		return FALSE;
}
BOOL	CLoaderMotion::Ionizer_Off()
{

	SetDOutputBitValue((enum_Do)(_DOUT_IONIZER_SOL_ON), FALSE);
	Sleep(200);
	SetDOutputBitValue((enum_Do)(_DOUT_IONIZER_SOL_OFF), TRUE);
	Sleep(200);

	Total_Msg(_T("Ionizer Off"));
	return TRUE;
}
BOOL	CLoaderMotion::Is_Ionizer_Off()
{
	if (SharedInfo::DOutputValue[_DOUT_IONIZER_SOL_OFF] == TRUE &&
		SharedInfo::DOutputValue[_DOUT_IONIZER_SOL_ON] == FALSE)
		return TRUE;
	else
		return FALSE;
}

BOOL	CLoaderMotion::CheckLoaderFlowInterlock(CString StrFlow, int nFlow, int nStartNo)
{
	CString Str;

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(AXIS_LOADER_Z) == FALSE)
	{
		Str.Format(_T("%s : Check Loader Z Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 0);		
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_LOADER_X) == FALSE)
	{
		//21.02.23 sjc temp del
		Str.Format(_T("%s : Check Loader X Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 1);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_LOADER_YL) == FALSE)
	{
		//21.02.23 sjc
		Str.Format(_T("%s : Check Loader YL Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 2);
		return FALSE;
	}


	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_LOADER_Z) == FALSE)
	{
		Str.Format(_T("%s : Check Loader Z Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 9);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_LOADER_X) == FALSE)
	{
		//21.02.23 SJC temp del
		Str.Format(_T("%s : Check Loader X Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 10);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_LOADER_YL) == FALSE)
	{
		//21.02.23 sjc
		Str.Format(_T("%s : Check Loader YL Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 11);
		return FALSE;
	}

	return TRUE;
}

#pragma endregion