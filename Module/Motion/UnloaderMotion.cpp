#include "stdafx.h"
#include "UnloaderMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"
#include "Data/ModelData.h"

CUnloaderMotion::CUnloaderMotion()
{
}


CUnloaderMotion::~CUnloaderMotion()
{
}


BOOL CUnloaderMotion::InitProcess()
{
	//m_bTerminate = FALSE;
	m_StateFinish = TRUE;
	
	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	m_dUnloaderY_StickUnloadGap = 10.0; //Temp

	hMotionHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hMotionHandle);
	pMotionThread = AfxBeginThread(MotionThreadFunction, this);// , THREAD_PRIORITY_ABOVE_NORMAL);

	return TRUE;
}

BOOL CUnloaderMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(eUNLOADER_MOTION_IDLE, FALSE);

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

BOOL CUnloaderMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CUnloaderMotion::MotionThreadFunction(LPVOID lpParam)
{
	CUnloaderMotion* pUnloaderMotion = NULL;

	pUnloaderMotion = (CUnloaderMotion*)lpParam;

	pUnloaderMotion->MotionThreadFunctionEntry();

	pUnloaderMotion->m_bTerminate = 1;

	return 0;
}

VOID CUnloaderMotion::MotionThreadFunctionEntry(VOID)
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

			SetCurrentStep(eUNLOADER_MOTION_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eUNLOADER_MOTION_IDLE:
			break;

		case eUNLOADER_MOTION_ERROR:
			break;

		case eUNLOADER_MOTION_DONE:
			m_bMotionDone = TRUE;
			SetStep(eUNLOADER_MOTION_IDLE, _T("eUNLOADER_MOTION_IDLE"));
			break;

		case eUNLOADER_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;
		}
	}
}

BOOL CUnloaderMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CUnloaderMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//현재 모터의 파라미터 받아오기
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//해당 모터에 파라미터 전달
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CUnloaderMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

BOOL CUnloaderMotion::GetUnloadYToCSTPos(double *pdTargetPosUldY)
{
	double dMaxWidth = 400.0; //Temp
	int nTargtFloor = 0; //Temp
	BOOL bResultExist = FALSE;

	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;
	for (int i = 0; i < MAX_CST_FLOOR; i++)
	{
		if (SharedInfo::CstStickExistInfo.bExistStick[nTargtFloor][i] == FALSE)
		{
			if (i == 0)
			{
				dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;
				bResultExist = TRUE;
				break;
			}
			else if (dPos + m_dUnloaderY_StickUnloadGap + CModelData::m_MaterialPara.Info.dStickSizeY < dMaxWidth)
			{
				dPos += (m_dUnloaderY_StickUnloadGap + CModelData::m_MaterialPara.Info.dStickSizeY);
				bResultExist = TRUE;
				break;
			}
		}
	}
	
	if (bResultExist)
	{
		*pdTargetPosUldY = dPos;
		return TRUE;
	}
	else
	{
		*pdTargetPosUldY = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
		return FALSE;
	}
}

#pragma region //PaperUnloader Y
//Move
BOOL CUnloaderMotion::PaperUnloaderY_All_Pos(double dPos)
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloaderY All Move To Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::PaperUnloaderY_All_WaitPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);

	//20210802 JINI
	if (bRtn == TRUE)
	{
		Sleep(100);
		eAxis = AXIS_UNLOADER_YR;
		bRtn = MoveAxis(eAxis, dPos);
	}

	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloader Y Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::PaperUnloaderY_All_LoadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloaderY All Move To Load Paper Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
BOOL CUnloaderMotion::PaperUnloaderY_All_LoadPaperWaitingPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Waiting_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloaderY All Move To Load Paper Waiting Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
BOOL CUnloaderMotion::PaperUnloaderY_All_UnloadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Unload_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloaderY All Move To Unload Paper Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
BOOL CUnloaderMotion::PaperUnloaderY_All_CassetteSafetyPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Cassette_Safety_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloaderY All Move To Cassette Safety Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
BOOL CUnloaderMotion::Move_UnloaderY_Pos(double dPos)
{
	//CString Str = _T("");
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//BOOL bRtn = MoveAxis(eAxis, dPos);
	//if (bRtn == TRUE)
	//{
	//	Str.Format(_T("PaperUnloader Y Move To Pos (Pos : %.5f)"), dPos);
	//	Total_Msg(Str);
	//}

	//return bRtn;
	return TRUE;
}
BOOL CUnloaderMotion::UnloaderY_WaitPos()
{
	//CString Str = _T("");
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos;
	//BOOL bRtn = MoveAxis(eAxis, dPos);
	//if (bRtn == TRUE)
	//{
	//	Str.Format(_T("PaperUnloader Y Move To Wait Pos (Pos : %.5f)"), dPos);
	//	Total_Msg(Str);
	//}

	//return bRtn;
	return TRUE;
}
BOOL CUnloaderMotion::GantryY_StickLoadInStagePos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_VIRTUAL_GANTRY_Y;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Stage_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("GantryY Move To Unloader Stick Load In Stage Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::GantryY_StickUnloadToCstPos(int nSlot)
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_VIRTUAL_GANTRY_Y;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;

	if (nSlot == 0)
		dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;
	else
		dPos = (m_dUnloaderY_StickUnloadGap + CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos) * nSlot;

	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("GantryY Move To Unloader Stick Unload To Cst Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
BOOL CUnloaderMotion::GantryY_StickLoadInCstPos(int nSlot)
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_VIRTUAL_GANTRY_Y;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos;

	if (nSlot == 0)
		dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos;
	else
		dPos = (m_dUnloaderY_StickUnloadGap + CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos) * nSlot;

	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("GantryY Move To Unloader Stick Load In Cst Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
BOOL CUnloaderMotion::GantryY_StickUnloadToStagePos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_VIRTUAL_GANTRY_Y;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Stage_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("GantryY Move To Unloader Stick Unload To Stage Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
BOOL CUnloaderMotion::Is_GantryY_StickLoadInStagePos()
{
	enum_Axis eAxis = AXIS_VIRTUAL_GANTRY_Y;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Stage_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_GantryY_StickUnloadToCstPos(int nSlot)
{
	enum_Axis eAxis = AXIS_VIRTUAL_GANTRY_Y;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;

	if (nSlot == 0)
		dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;
	else
		dPos = (m_dUnloaderY_StickUnloadGap + CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos) * nSlot;

	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_GantryY_StickLoadInCstPos(int nSlot)
{
	enum_Axis eAxis = AXIS_VIRTUAL_GANTRY_Y;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos;

	if (nSlot == 0)
		dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos;
	else
		dPos = (m_dUnloaderY_StickUnloadGap + CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos) * nSlot;

	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_GantryY_StickUnloadToStagePos()
{
	enum_Axis eAxis = AXIS_VIRTUAL_GANTRY_Y;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Stage_Pos;
	return IsMoveDone(eAxis, dPos);
}
//PaperUnloader X
BOOL CUnloaderMotion::PaperUnloaderX_All_WaitPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_XL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dPaperUnloader_XL_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);

	//20210802 JINI
	if (bRtn == TRUE)
	{
		Sleep(100);
		eAxis = AXIS_UNLOADER_XR;
		bRtn = MoveAxis(eAxis, dPos);
	}

	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloaderX All Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
BOOL CUnloaderMotion::PaperUnloaderX_All_PickUpPos()
{
	CString Str = _T("");

	double dPos = CModelData::m_ModelSubManualPara.Info.dPaperUnloaderX_PickUpPos;
	BOOL bRtn = MoveAxis(AXIS_UNLOADER_XL, dPos);
	if (bRtn)
	{
		Str.Format(_T("PaperUnloaderX All Move To PaperPickUp Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
//PaperUnloader YL
BOOL CUnloaderMotion::UnloaderY_LoadPaperPos()
{
	//CString Str = _T("");
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Pos;
	//BOOL bRtn = MoveAxis(eAxis, dPos);
	//if (bRtn == TRUE)
	//{
	//	Str.Format(_T("PaperUnloader Y Move To Load Paper Pos (Pos : %.5f)"), dPos);
	//	Total_Msg(Str);
	//}
	//return bRtn;

	return FALSE;
}

//MoveDone Check
//PaperUnloader YL
BOOL CUnloaderMotion::Is_PaperUnloaderY_All_Pos(double dPos)
{
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_PaperUnloaderY_All_WaitPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_PaperUnloaderY_All_LoadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_PaperUnloaderY_All_LoadPaperWaitingPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Waiting_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_PaperUnloaderY_All_UnloadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Unload_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_PaperUnloaderY_All_CassetteSafetyPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Cassette_Safety_Pos;
	return IsMoveDone(eAxis, dPos);
}

BOOL CUnloaderMotion::Is_UnloaderY_Pos(double dPos)
{
	enum_Axis eAxis = AXIS_UNLOADER_YL;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderY_WaitPos()
{
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos;
	//return IsMoveDone(eAxis, dPos);
	return FALSE;
}
BOOL CUnloaderMotion::Is_UnloaderY_LoadInStagePos()
{
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Stage_Pos;
	//return IsMoveDone(eAxis, dPos);
	return FALSE;
}
BOOL CUnloaderMotion::Is_UnloaderY_UnloadToCstPos(int nSlot)
{
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;

	//if (nSlot == 0)
	//	dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;
	//else
	//	dPos = (m_dUnloaderY_StickUnloadGap + CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos) * nSlot;
	//
	//return IsMoveDone(eAxis, dPos);
	return FALSE;
}
BOOL CUnloaderMotion::Is_UnloaderY_LoadInCstPos(int nSlot)
{
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos;

	//if (nSlot == 0)
	//	dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos;
	//else
	//	dPos = (m_dUnloaderY_StickUnloadGap + CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos) * nSlot;

	//return IsMoveDone(eAxis, dPos);

	return FALSE;
}
BOOL CUnloaderMotion::Is_UnloaderY_UnloadToStagePos()
{
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Stage_Pos;
	//return IsMoveDone(eAxis, dPos);
	return FALSE;
}

BOOL CUnloaderMotion::Is_UnloaderY_LoadPaperPos()
{
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Pos;
	//return IsMoveDone(eAxis, dPos);
	return FALSE;
}
BOOL CUnloaderMotion::Is_UnloaderY_UnloadPaperPos()
{
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Unload_Pos;
	//return IsMoveDone(eAxis, dPos);
	return FALSE;
}
BOOL CUnloaderMotion::Is_UnloaderY_CassetteSafetyPos()
{
	//enum_Axis eAxis = AXIS_UNLOADER_YL;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Cassette_Safety_Pos;
	//return IsMoveDone(eAxis, dPos);
	return FALSE;
}
//PaperUnloader X
BOOL CUnloaderMotion::Is_PaperUnloaderX_All_WaitPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_XL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dPaperUnloader_XL_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_PaperUnloaderX_All_PickUpPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_XL;
	double dPos = CModelData::m_ModelSubManualPara.Info.dPaperUnloaderX_PickUpPos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //StickUnloader X
//Move
BOOL CUnloaderMotion::UnloaderX_WaitPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_X;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("StickUnloader X Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::UnloaderX_PickUpPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_X;
	double dPos = CModelData::m_ModelSubManualPara.Info.dStickUnloaderX_PickUpPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader X Move To PickUp Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//MoveDone Check
BOOL CUnloaderMotion::Is_UnloaderX_WaitPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_X;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderX_PickUpPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_X;
	double dPos = CModelData::m_ModelSubManualPara.Info.dStickUnloaderX_PickUpPos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //MaskUnloader Z
//Move
BOOL CUnloaderMotion::UnloaderZ_WaitPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader Z Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::UnloaderZ_LoadInStagePos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Stage_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader Z Move To Load In Stage Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::UnloaderZ_UnloadToCstPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Cst_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader Z Move To Unload To Cst Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::UnloaderZ_LoadInCstPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Cst_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader Z Move To Load In Cst Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::UnloaderZ_UnloadToStagePos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Stage_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader Z Move To Unload To Stage Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::UnloaderZ_LoadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Load_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader Z Move To Load Paper Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CUnloaderMotion::UnloaderZ_UnloadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Unload_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader Z Move To Unload Paper Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CUnloaderMotion::UnloaderZ_Vibration_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Vibration_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("MaskUnloader Z Move To Vibration Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}


//MoveDone Check
//MaskUnloaderZ
BOOL CUnloaderMotion::Is_UnloaderZ_WaitPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderZ_LoadInStagePos()
{
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Stage_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderZ_UnloadToCstPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Cst_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderZ_LoadInCstPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Cst_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderZ_UnloadToStagePos()
{
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Stage_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderZ_LoadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Load_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderZ_UnloadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Unload_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CUnloaderMotion::Is_UnloaderZ_Vibration_Pos()
{
	enum_Axis eAxis = AXIS_UNLOADER_Z;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Vibration_Pos;
	return IsMoveDone(eAxis, dPos);
}

#pragma endregion
#pragma region //PaperUnloader Z
//Move
BOOL CUnloaderMotion::PaperUnloaderZ_All_WaitPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_ZL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);

	//20210802 jini
	if (bRtn == TRUE)
	{
		Sleep(100);
		eAxis = AXIS_UNLOADER_ZR;
		bRtn = MoveAxis(eAxis, dPos);
	}

	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloaderZ All Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CUnloaderMotion::PaperUnloaderZ_All_UnloadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_ZL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Unload_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("PaperUnloaderZ All Move To PaperUnload Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CUnloaderMotion::Is_PaperUnloaderZ_All_WaitPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_ZL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}

BOOL CUnloaderMotion::Is_PaperUnloaderZ_All_UnloadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_ZL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Unload_Pos;
	return IsMoveDone(eAxis, dPos);
}

BOOL CUnloaderMotion::Ionizer_On()
{
	SetDOutputBitValue((enum_Do)(_DOUT_IONIZER_SOL_OFF), FALSE);
	Sleep(200);
	SetDOutputBitValue((enum_Do)(_DOUT_IONIZER_SOL_ON), TRUE);
	Sleep(200);
	//SetDOutputBitValue((enum_Do)(_DOUT_ION_ON), FALSE);
	//Sleep(200);

	Total_Msg(_T("Ionizer On"));
	return TRUE;
}

BOOL CUnloaderMotion::Ionizer_Off()
{	
	SetDOutputBitValue((enum_Do)(_DOUT_IONIZER_SOL_ON), FALSE);
	Sleep(200);
	SetDOutputBitValue((enum_Do)(_DOUT_IONIZER_SOL_OFF), TRUE);
	Sleep(200);
	//SetDOutputBitValue((enum_Do)(_DOUT_ION_ON), FALSE);
	//Sleep(200);

	Total_Msg(_T("Ionizer Off"));
	return TRUE;
}

BOOL CUnloaderMotion::Is_Ionizer_On()
{
	if (SharedInfo::DOutputValue[_DOUT_IONIZER_SOL_OFF] == FALSE &&
		SharedInfo::DOutputValue[_DOUT_IONIZER_SOL_ON] == TRUE)
		return TRUE;
	else
		return FALSE;
}

BOOL CUnloaderMotion::Is_Ionizer_Off()
{
	if (SharedInfo::DOutputValue[_DOUT_IONIZER_SOL_ON] == FALSE &&
		SharedInfo::DOutputValue[_DOUT_IONIZER_SOL_OFF] == TRUE)
		return TRUE;
	else
		return FALSE;
}

#pragma endregion
#pragma region //IO
//Unloader Vac
BOOL	CUnloaderMotion::Stick_Vac_On(int nFinger)
{
	CString Str = _T("ULD Stick Vac On (");
	int i = 0;
	int vacDoutNum[5] = { _DOUT_ULD_STICK_VAC_1, _DOUT_ULD_STICK_VAC_2, _DOUT_ULD_STICK_VAC_3, _DOUT_ULD_STICK_VAC_4, _DOUT_ULD_STICK_VAC_5 };
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			SetDOutputBitValue((enum_Do)vacDoutNum[i], TRUE);
			Str.AppendFormat(_T("%d, "), i + 1);
			Sleep(10);
		}
	}
	Str.AppendFormat(_T(")"));
	Total_Msg(Str);

	return TRUE;
}
BOOL	CUnloaderMotion::Stick_Vac_Off(int nFinger)
{
	Stick_Blow_On();
	Sleep(1000);
	int vacDoutNum[5] = { _DOUT_ULD_STICK_VAC_1, _DOUT_ULD_STICK_VAC_2, _DOUT_ULD_STICK_VAC_3, _DOUT_ULD_STICK_VAC_4, _DOUT_ULD_STICK_VAC_5 };
	CString Str = _T("ULD Stick Vac Off (");
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			SetDOutputBitValue((enum_Do)vacDoutNum[i], FALSE);
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
BOOL	CUnloaderMotion::Stick_Active_Vac_On()
{
	int nFinger = (CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 << 0) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 << 1) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 << 2) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 << 3) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 << 4);

	Devs::m_UnloaderMotion.Stick_Vac_On(nFinger);
	return TRUE;
}
BOOL	CUnloaderMotion::Stick_Active_Vac_Off()
{
	int nFinger = (CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 << 0) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 << 1) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 << 2) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 << 3) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 << 4);

	Devs::m_UnloaderMotion.Stick_Vac_Off(nFinger);
	return TRUE;
}
BOOL	CUnloaderMotion::Stick_Blow_On()
{
	SetDOutputBitValue((enum_Do)_DOUT_STICK_ULD_BLOW, TRUE);
	Sleep(1);

	Total_Msg(_T("ULD Stick Blow On"));
	return TRUE;
}
BOOL	CUnloaderMotion::Stick_Blow_Off()
{
	SetDOutputBitValue((enum_Do)_DOUT_STICK_ULD_BLOW, FALSE);
	Sleep(1);

	Total_Msg(_T("ULD Stick Blow Off"));
	return TRUE;
}
BOOL	CUnloaderMotion::Stick_All_Vac_On()
{
	BOOL bRtn = Stick_Vac_On(eVAC_UNLOADER_STICK_ALL);
	return bRtn;
}
BOOL	CUnloaderMotion::Stick_All_Vac_Off()
{
	BOOL bRtn = Stick_Vac_Off(eVAC_UNLOADER_STICK_ALL);
	return bRtn;
}
BOOL	CUnloaderMotion::Is_Stick_Vac_On(int nFinger)
{
#ifdef SIM_MODE
	return TRUE;
#endif

	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			//if (SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 + (i * 2)] == FALSE || SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_2 + (i * 2)] == FALSE)
			//	return FALSE;

			//if (SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 + i] == FALSE)
			if (SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 - i] == FALSE) //KJT 20210723 Junying
				return FALSE;
		}
	}

	return TRUE;
}
BOOL	CUnloaderMotion::Is_Stick_Vac_Off(int nFinger)
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			//if (SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 + (i * 2)] == TRUE || SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_2 + (i * 2)] == TRUE)
			//	return FALSE;

			//if (SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 + i] == TRUE)
			if (SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 - i] == TRUE) //KJT 20210723 Junying
				return FALSE;
		}
	}

	return TRUE;
}
BOOL	CUnloaderMotion::Is_Stick_Active_Vac_On()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	int nFinger = (CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 << 0) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 << 1) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 << 2) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 << 3) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 << 4);

	if (Devs::m_UnloaderMotion.Is_Stick_Vac_On(nFinger))
		return TRUE;
	else
		return FALSE;
}
BOOL	CUnloaderMotion::Is_Stick_Active_Vac_Off()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	int nFinger = (CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 << 0) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 << 1) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 << 2) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 << 3) |
		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 << 4);

	if (Devs::m_UnloaderMotion.Is_Stick_Vac_Off(nFinger))
		return TRUE;
	else
		return FALSE;
}
BOOL	CUnloaderMotion::Is_Stick_Blow_On()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//int nFinger = eFinger;
	//int i = 0;
	//for (i = 0; i < 5; i++)
	//{
	//	if (nFinger >> i & 1 == 1)
	//	{
	//		if (SharedInfo::DInputValue[_DIN_ULD_VAC_1_OUTPUT + i] == FALSE)
	//			return FALSE;
	//	}
	//}

	return TRUE;
}
BOOL	CUnloaderMotion::Is_Stick_Blow_Off()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//int nFinger = eFinger;
	//int i = 0;
	//for (i = 0; i < 5; i++)
	//{
	//	if (nFinger >> i & 1 == 1)
	//	{
	//		if (SharedInfo::DInputValue[_DIN_ULD_VAC_1_OUTPUT + i] == TRUE)
	//			return FALSE;
	//	}
	//}

	return TRUE;
}
BOOL	CUnloaderMotion::Is_Stick_All_Vac_On()
{
	BOOL bRtn = Is_Stick_Vac_On(eVAC_UNLOADER_STICK_ALL);

	return bRtn;
}
BOOL	CUnloaderMotion::Is_Stick_All_Vac_Off()
{
	BOOL bRtn = Is_Stick_Vac_Off(eVAC_UNLOADER_STICK_ALL);

	return bRtn;
}

BOOL	CUnloaderMotion::PaperUnloader_Vac_On(int nFinger)
{
	CString Str = _T("PaperUnloader Vac On (");
	int i = 0;
	int vacDoutNum[5] = { _DOUT_ULD_PAPER_VAC_1 ,_DOUT_ULD_PAPER_VAC_2,_DOUT_ULD_PAPER_VAC_3_4,_DOUT_ULD_PAPER_VAC_5, _DOUT_ULD_PAPER_VAC_6 };
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			SetDOutputBitValue((enum_Do)vacDoutNum[i], TRUE);
			Str.AppendFormat(_T("%d, "), i + 1);
			Sleep(10);
		}
	}
	Str.AppendFormat(_T(")"));
	Total_Msg(Str);

	return TRUE;
}
BOOL	CUnloaderMotion::PaperUnloader_Vac_Off(int nFinger)
{
	Paper_Blow_On();
	Sleep(1000);
	int vacDoutNum[5] = { _DOUT_ULD_PAPER_VAC_1 ,_DOUT_ULD_PAPER_VAC_2,_DOUT_ULD_PAPER_VAC_3_4,_DOUT_ULD_PAPER_VAC_5, _DOUT_ULD_PAPER_VAC_6 };
	CString Str = _T("PaperUnloader Vac Off (");
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			SetDOutputBitValue((enum_Do)vacDoutNum[i], FALSE);
			Str.AppendFormat(_T("%d, "), i + 1);
			Sleep(10);
		}
	}
	Str.AppendFormat(_T(")"));
	Total_Msg(Str);

	Sleep(1000);
	Paper_Blow_Off();

	return TRUE;
}
BOOL	CUnloaderMotion::PaperUnloader_Active_Vac_On()
{
	int nFinger = (CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_1 << 0) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_2 << 1) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_3_4 << 2) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_5 << 3) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_6 << 4);

	Devs::m_UnloaderMotion.PaperUnloader_Vac_On(nFinger);
	return TRUE;
}
BOOL	CUnloaderMotion::PaperUnloader_Active_Vac_Off()
{
	int nFinger = (CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_1 << 0) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_2 << 1) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_3_4 << 2) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_5 << 3) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_6 << 4);

	Devs::m_UnloaderMotion.PaperUnloader_Vac_Off(nFinger);
	return TRUE;
}
BOOL	CUnloaderMotion::PaperUnloader_All_Vac_On()
{
	BOOL bRtn = PaperUnloader_Vac_On(eVAC_UNLOADER_PAPER_ALL);
	return bRtn;
}
BOOL	CUnloaderMotion::PaperUnloader_All_Vac_Off()
{
	BOOL bRtn = PaperUnloader_Vac_Off(eVAC_UNLOADER_PAPER_ALL);
	return bRtn;
}
BOOL	CUnloaderMotion::Is_PaperUnloader_Vac_On(int nFinger)
{
#ifdef SIM_MODE
	return TRUE;
#endif

	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			if (SharedInfo::DInputValue[_DIN_PAPER_VAC_LEFT_1 + i] == FALSE || SharedInfo::DInputValue[_DIN_PAPER_VAC_RIGHT_1 + i] == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}
BOOL	CUnloaderMotion::Is_PaperUnloader_Vac_Off(int nFinger)
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (((nFinger >> i) & 1) == 1)
		{
			if (SharedInfo::DInputValue[_DIN_PAPER_VAC_LEFT_1 + i] == TRUE || SharedInfo::DInputValue[_DIN_PAPER_VAC_RIGHT_1 + i] == TRUE)
				return FALSE;
		}
	}

	return TRUE;
}
BOOL	CUnloaderMotion::Is_PaperUnloader_Active_Vac_On()
{
#ifdef SIM_MODE
	return TRUE;
#endif
	
	int nFinger = (CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_1 << 0) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_2 << 1) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_3_4 << 2) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_5 << 3) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_6 << 4);

	if (Devs::m_UnloaderMotion.Is_PaperUnloader_Vac_On(nFinger))
		return TRUE;
	else
		return FALSE;
}
BOOL	CUnloaderMotion::Is_PaperUnloader_Active_Vac_Off()
{
	int nFinger = (CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_1 << 0) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_2 << 1) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_3_4 << 2) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_5 << 3) |
		(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_6 << 4);

	if (Devs::m_UnloaderMotion.Is_PaperUnloader_Vac_Off(nFinger))
		return TRUE;
	else
		return FALSE;
}

BOOL	CUnloaderMotion::Is_PaperUnloader_All_Vac_On()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	BOOL bRtn = Is_PaperUnloader_Vac_On(eVAC_UNLOADER_PAPER_ALL);
	return bRtn;
}
BOOL	CUnloaderMotion::Is_PaperUnloader_All_Vac_Off()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	BOOL bRtn = Is_PaperUnloader_Vac_Off(eVAC_UNLOADER_PAPER_ALL);
	return bRtn;
}
BOOL	CUnloaderMotion::Paper_Vac_On(int nFinger)
{
	//CString Str = _T("ULD Paper Vac On (");
	//int i = 0;
	//int vacDoutNum[5] = { _DOUT_ULD_PAPER_VAC_1 ,_DOUT_ULD_PAPER_VAC_2,_DOUT_ULD_PAPER_VAC_3_4,_DOUT_ULD_PAPER_VAC_5, _DOUT_ULD_PAPER_VAC_6 };
	//for (i = 0; i < 5; i++)
	//{
	//	if (((nFinger >> i) & 1) == 1)
	//	{
	//		SetDOutputBitValue((enum_Do)vacDoutNum[i], TRUE);
	//		Str.AppendFormat(_T("%d, "), i + 1);
	//		Sleep(10);
	//	}
	//}
	//Str.AppendFormat(_T(")"));
	//Total_Msg(Str);

	return TRUE;
}
BOOL	CUnloaderMotion::Paper_Vac_Off(int nFinger)
{
	//Paper_Blow_On();
	//Sleep(1000);
	//int vacDoutNum[5] = { _DOUT_ULD_PAPER_VAC_1 ,_DOUT_ULD_PAPER_VAC_2,_DOUT_ULD_PAPER_VAC_3_4,_DOUT_ULD_PAPER_VAC_5, _DOUT_ULD_PAPER_VAC_6 };
	//CString Str = _T("ULD Paper Vac Off (");
	//int i = 0;
	//for (i = 0; i < 5; i++)
	//{
	//	if (((nFinger >> i) & 1) == 1)
	//	{
	//		SetDOutputBitValue((enum_Do)vacDoutNum[i], FALSE);
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
//BOOL	CUnloaderMotion::Paper_Active_Vac_On()
//{
//	//int nFinger = (CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 << 0) |
//	//	(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 << 1) |
//	//	(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 << 2) |
//	//	(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 << 3);// |
//	//	//(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 << 4);
//
//	//Devs::m_UnloaderMotion.Paper_Vac_On(nFinger);
//	return TRUE;
//}
//BOOL	CUnloaderMotion::Paper_Active_Vac_Off()
//{
//	//int nFinger = (CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 << 0) |
//	//	(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 << 1) |
//	//	(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 << 2) |
//	//	(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 << 3);// |
//	//	//(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 << 4);
//
//	//Devs::m_UnloaderMotion.Paper_Vac_Off(nFinger);
//	return TRUE;
//}
BOOL	CUnloaderMotion::Paper_Blow_On()
{
	SetDOutputBitValue((enum_Do)_DOUT_PAPER_UNLOADER_BLOW, TRUE);
	Sleep(1);

	Total_Msg(_T("ULD Paper Blow On"));
	return TRUE;
}
BOOL	CUnloaderMotion::Paper_Blow_Off()
{
	SetDOutputBitValue((enum_Do)_DOUT_PAPER_UNLOADER_BLOW, FALSE);
	Sleep(1);
	Total_Msg(_T("ULD Paper Blow Off"));
	return TRUE;
}
BOOL	CUnloaderMotion::Paper_All_Vac_On()
{
	BOOL bRtn = Paper_Vac_On(eVAC_UNLOADER_STICK_ALL);
	return bRtn;
}
BOOL	CUnloaderMotion::Paper_All_Vac_Off()
{
	BOOL bRtn = Paper_Vac_Off(eVAC_UNLOADER_STICK_ALL);
	return bRtn;
}
//BOOL	CUnloaderMotion::Is_Paper_Vac_On(int nFinger)
//{
//#ifdef SIM_MODE
//	return TRUE;
//#endif
//
//	int i = 0;
//	for (i = 0; i < 4; i++)
//	{
//		if (((nFinger >> i) & 1) == 1)
//		{
//			//if (SharedInfo::DInputValue[_DIN_ULD_PAPER_VAC_1 + (i * 2)] == FALSE || SharedInfo::DInputValue[_DIN_ULD_PAPER_VAC_2 + (i * 2)] == FALSE)
//			//if (SharedInfo::DInputValue[_DIN_ULD_PAPER_VAC_1 + i] == FALSE)
//			//	return FALSE;
//		}
//	}
//
//	return TRUE;
//}
//BOOL	CUnloaderMotion::Is_Paper_Vac_Off(int nFinger)
//{
//	int i = 0;
//	for (i = 0; i < 4; i++)
//	{
//		if (((nFinger >> i) & 1) == 1)
//		{
//			//if (SharedInfo::DInputValue[_DIN_ULD_PAPER_VAC_1 + (i * 2)] == TRUE || SharedInfo::DInputValue[_DIN_ULD_PAPER_VAC_2 + (i * 2)] == TRUE)
//			//if (SharedInfo::DInputValue[_DIN_ULD_PAPER_VAC_1 + i] == TRUE)
//			//	return FALSE;
//		}
//	}
//
//	return TRUE;
//}
//BOOL	CUnloaderMotion::Is_Paper_Active_Vac_On()
//{
//#ifdef SIM_MODE
//	return TRUE;
//#endif
//
//	int nFinger = (CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 << 0) |
//		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 << 1) |
//		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 << 2) |
//		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 << 3);// |
//		//(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 << 4);
//
//	if (Devs::m_UnloaderMotion.Is_Paper_Vac_On(nFinger))
//		return TRUE;
//	else
		//return FALSE;
//}
//BOOL	CUnloaderMotion::Is_Paper_Active_Vac_Off()
//{
//#ifdef SIM_MODE
//	return TRUE;
//#endif
//
//	int nFinger = (CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 << 0) |
//		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 << 1) |
//		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 << 2) |
//		(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 << 3);// |
//		//(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 << 4);
//
//	if (Devs::m_UnloaderMotion.Is_Paper_Vac_Off(nFinger))
//		return TRUE;
//	else
//		return FALSE;
//}
//BOOL	CUnloaderMotion::Is_Paper_All_Vac_On()
//{
//	BOOL bRtn = Is_Paper_Vac_On(eVAC_UNLOADER_STICK_ALL);
//
//	return bRtn;
//}
//BOOL	CUnloaderMotion::Is_Paper_All_Vac_Off()
//{
//	BOOL bRtn = Is_Paper_Vac_Off(eVAC_UNLOADER_STICK_ALL);
//
//	return bRtn;
//}

BOOL	CUnloaderMotion::CheckUnloaderFlowInterlock(CString StrFlow, int nFlow, int nStartNo)
{
	CString Str;

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_Z) == FALSE)
	{
		Str.Format(_T("%s : Check Unloader Z Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 0);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_X) == FALSE)
	{
		//21.02.23 sjc temp del
		Str.Format(_T("%s : Check Unloader X Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 1);
		return FALSE;
	}	

	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_Z) == FALSE)
	{
		Str.Format(_T("%s : Check Unloader Z Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 5);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_X) == FALSE)
	{
		//21.02.23 SJC temp del
		Str.Format(_T("%s : Check Unloader X Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 6);
		return FALSE;
	}

	return TRUE;
}

BOOL	CUnloaderMotion::CheckPaperUnloaderFlowInterlock(CString StrFlow, int nFlow, int nStartNo)
{
	CString Str;

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_ZL) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader ZL Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 0);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_ZR) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader ZR Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 1);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_XL) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader XL Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 2);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_XR) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader XR Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 3);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_YL) == FALSE)
	{
		//21.02.23 sjc
		Str.Format(_T("%s : Check PaperUnloader YL Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 4);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_YR) == FALSE)
	{
		//21.02.23 sjc
		Str.Format(_T("%s : Check PaperUnloader YR Servo On !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 5);
		return FALSE;
	}

	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_ZL) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader ZL Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 6);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_ZR) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader ZR Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 7);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_XL) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader XL Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 8);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_XR) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader XR Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 9);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_YL) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader YL Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 10);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_YR) == FALSE)
	{
		Str.Format(_T("%s : Check PaperUnloader YR Home Status !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 11);
		return FALSE;
	}

	if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z1) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos - 0.002)
	{
		Str.Format(_T("%s : Check CameraZ1 Wait Pos !!!"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 14);
		return FALSE;
	}

	return TRUE;
}

BOOL CUnloaderMotion::UnloaderSubZL_LoadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_ZL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Load_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Unloader Sub ZL Move To Paper Load Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CUnloaderMotion::UnloaderSubZR_LoadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_ZR;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZR_Paper_Load_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Unloader Sub ZR Move To Paper Load Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CUnloaderMotion::UnloaderSubZL_UnloadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_ZL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Unload_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Unloader Sub ZL Move To Paper Unload Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CUnloaderMotion::UnloaderSubZR_UnloadPaperPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_UNLOADER_ZR;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZR_Paper_Unload_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Unloader Sub ZR Move To Paper Unload Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CUnloaderMotion::Is_UnloaderSubZL_LoadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_ZL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Load_Pos;
	return IsMoveDone(eAxis, dPos);
}

BOOL CUnloaderMotion::Is_UnloaderSubZR_LoadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_ZR;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZR_Paper_Load_Pos;
	return IsMoveDone(eAxis, dPos);
}

BOOL CUnloaderMotion::Is_UnloaderSubZL_UnloadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_ZL;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Unload_Pos;
	return IsMoveDone(eAxis, dPos);
}

BOOL CUnloaderMotion::Is_UnloaderSubZR_UnloadPaperPos()
{
	enum_Axis eAxis = AXIS_UNLOADER_ZR;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZR_Paper_Unload_Pos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion