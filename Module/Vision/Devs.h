#pragma once


#include "SharedInfo.h"
//#include "../Module/Log/UserLog.h"
#include "DirectoryManager/FileManager.h"
#include "Common/CommonDefine.h"
#include "Common/ClientInterface.h"

#include "mil.h"

//#include "Vision/MappingProc.h"

#include "CIM/CimModule.h"
#include "FTP/CommFTP.h"
#include "FTP/Hash.h"
#include "FTP/Define_FTP.h"

//class CWkLibVision;

#pragma region //Motion
#include "Motion/BaseMotion.h"
#include "Motion/JogMotion.h"
#include "Motion/Frame_Unit_Motion.h"
#include "Motion/GantryMotion.h"
//#include "Motion/BoxMotion.h"
#include "Motion/ClampMotion.h"
#include "Motion/StretchMotion.h"
#include "Motion/GripperZMotion.h"
#include "Motion/InspectionStageMotion.h"
#pragma endregion

#pragma region //Flow
#include "Flow/Origin_AllAxis_Flow.h"
#pragma endregion

class CMotionModule;
class Devs
{
public:
	Devs();
	~Devs();
	
	static void Initialize(void);
	static void Finalize(void);

	static void Reset(void);
	static void StopAll(void);
		
public:
	//Client Interface
	static CClientInterface MotionIf;

#if 0
	//Awk Light Control
	static CWkLibBdc		*m_LightController;
	static CWkLibPua310		*m_Pua310;
#endif
	static CSocketManager m_SocketLoaderBarCode;

#ifndef MIL_NOT_USE
	static CWkLibVision*	m_Camera10X;

	static CWkLibVision*	m_Camera6G_LT;
	static CWkLibVision*	m_Camera6G_RT;
	static CWkLibVision*	m_Camera6G_RB;
	static CWkLibVision*	m_Camera6G_LB;

	static CWkLibVision*	m_Camera8G_LT;
	static CWkLibVision*	m_Camera8G_RT;
	static CWkLibVision*	m_Camera8G_RB;
	static CWkLibVision*	m_Camera8G_LB;
	   
	static MIL_ID			MilApplication;
	static MIL_ID			MilSysSol0;
	static MIL_ID			MilSysSol1;
	static MIL_ID			MilSysSol2;

	static MIL_ID			MilDigCam6G_LT;
	static MIL_ID			MilDigCam6G_RT;
	static MIL_ID			MilDigCam6G_RB;
	static MIL_ID			MilDigCam6G_LB;

	static MIL_ID			MilDigCam8G_LT;
	static MIL_ID			MilDigCam8G_RT;
	static MIL_ID			MilDigCam8G_RB;
	static MIL_ID			MilDigCam8G_LB;

	//static MIL_ID			MilDigReview10X;
#endif

#pragma region //Motion
	static CBaseMotion				m_BaseMotion;
	static CJogMotion				m_JogMotion;
	static CGantryMotion			m_GantryMotion;
	static CClampMotion				m_ClampMotion;
	static CStretchMotion			m_StretchMotion;
	static CGripperZMotion			m_GripperZMotion;
	static CInspectionStageMotion	m_InspectionStageMotion;
#pragma endregion

#pragma region //Flow
	static COrigin_AllAxis_Flow			m_Origin_AllAxis_Flow;
#pragma endregion
		
#pragma region //Cim
	static CCimModule			CimMotion;
	static CCommFTP		Devs::m_pDfs;

	static void MachineStatusChange(MACHINE_STATUS_ENUM MachineStatus);

	static BOOL	TowerLampControl(int Status);
	//static BOOL SetJobDataAtoB(PMATERIAL_DATA_A JobDataA, PMATERIAL_DATA_B JobDataB); //B12 Not Use //KJT 20210325
	static void GenerateBCDField(PTIME_BCD BCDData);
	static void GenerateSVList(PSV_LIST SVList);
#pragma endregion

	//Folder Manager
	static CFileManager			m_FolderManager;

	static CMappingProc			m_MappingProc;

#if 0
	//Module
	static CMotionModule		m_MotionModule;
#endif

	static CWinThread* m_pMonitoringThread;
	static int m_nIsRunningMonitoringThread;
	static int m_nStopMonitoringThread;

	static bool m_bEntry;

	//Machine State Check
	static VOID MachineStateCheck(void);

	static INT GetMainStep();
	static INT GetSubStep();

	static CString FindCurrentRecipeName(int nRecipeID);
	static int FindCurrentRecipeID(CString strRecipeName);
	static int FindRecipeID(WORD wRecipeID);
	static BOOL GetIsAlignSitck(int nRecipeID);
	static BOOL DuplicateModelNameCheck(CString strRecipeName); //KJT 20210410

	static BOOL Delay(DOUBLE nTime)
	{
		INT nStart = GetTickCount();
		while (TRUE)
		{
			PeekAndPump();

			if (nTime < GetTickCount() - nStart)
				break;

			Sleep(10);
		}

		return TRUE;
	}

	static BOOL Delay(BOOL bCondition)
	{
		INT nStart = GetTickCount();
		while (TRUE)
		{
			PeekAndPump();

			if (bCondition)
				break;

			Sleep(10);
		}

		return TRUE;
	}

	static void	PeekAndPump()
	{
		MSG		msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!AfxGetThread()->PumpMessage()) break;
		}
	}
};

UINT AppMonitoringThreadProc(LPVOID lpParam);