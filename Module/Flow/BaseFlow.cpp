#include "stdafx.h"
#include "BaseFlow.h"
#include "Log/Logger.h"

CBaseFlow::CBaseFlow()
{

}


CBaseFlow::~CBaseFlow()
{
}
DWORD CBaseFlow::GetTimeOut()
{
	return m_dwTimeOut;
}
BOOL CBaseFlow::IsTimeOut()
{
	DWORD dwTimeOut = GetTimeOut();
	DWORD dwCheckTick = GetTickCount();

	if (m_bPauseTimeOutFlag == TRUE)
		return FALSE;
	if (dwTimeOut != INFINITE)
	{
		if (dwCheckTick - m_dwTimeTick == 0)
			return  FALSE;
		else if(dwCheckTick - m_dwTimeTick > dwTimeOut)
			return  TRUE;
		else
			return  FALSE;
	}
		
	else
		return FALSE;
}

void CBaseFlow::SetTimeOut(DWORD timeout)
{
	m_dwTimeOut = timeout;
	m_bPauseTimeOutFlag = FALSE;

}

void CBaseFlow::ResetTimeOut()
{
	m_dwTimeTick = GetTickCount();
	m_bPauseTimeOutFlag = FALSE;
}

void CBaseFlow::PauseTimeOut()
{
	m_bPauseTimeOutFlag = TRUE;
}

void CBaseFlow::SetCurrentStep(int nStep)
{
	m_nCurFlowStep = nStep;
	m_nCurFlowTotalStep = nStep;
}


void CBaseFlow::SetMachineStopFlag(BOOL *MachineStopFlag)
{
	m_pMachineStopFlag = MachineStopFlag;
}

BOOL CBaseFlow::GetMachineStopFlag()
{
	return *m_pMachineStopFlag;
}

int CBaseFlow::GetCurrentTotalStep()
{
	return m_nCurFlowTotalStep;
}
int CBaseFlow::GetCurrentFlowStep()
{
	return m_nCurFlowTotalStep;
}

BOOL CBaseFlow::SetTerminate(INT nValue)
{
	m_bTerminate = nValue;

	return TRUE;
}


void CBaseFlow::SetHandle(HANDLE hhandle)
{
	hMotionHandle = hhandle;
}


BOOL CBaseFlow::SetAlarm(LPCTSTR Msg)
{
	//	ASSERT(m_pMech);

	//if (Alarm::SetAlarm(msg, GetCurStepName(), NULL))
	//{
		// to-do
	//	Pause();
		//m_pMech->Buzzer1On();
		//m_pStateMan->NotifyAlarm();
	//SharedInfo::MachineState.bErrorFlag = TRUE;
	//Devs::StopAll();
	//Log_Msg(msg);

	SharedInfo::SetAlarm(Msg, 1);

	return FALSE;
}
int	CBaseFlow::GetThisStepGroupID(int nStep)
{
	int nReturnValue = 0;
	for (int i = 0; i < m_nMaxGroupCount; i++)
	{
		if (m_sGroupInfo[i].nStartStep <= nStep && m_sGroupInfo[i].nEndStep >= nStep)
		{
			nReturnValue = i;
			break;
		}
		
	}
	return nReturnValue;
}
int CBaseFlow::ResetCompleteFlag()
{
	for (int i = 0; i < m_nMaxGroupCount; i++)
		m_sGroupInfo[i].m_bCompleteFlag = FALSE;
	return 0;
}
#if 0
int	CBaseFlow::SetGroupStep(int nManualGroupID, BOOL bManualStepFlag)
{

	m_nGroupStepID = nManualGroupID;
	m_nCurFlowStep = m_sGroupInfo[m_nGroupStepID].nStartStep;
	m_nCurFlowTotalStep = m_sGroupInfo[m_nGroupStepID].nStartStep;
	m_bManualStepFlag = bManualStepFlag;
	SetStep(m_sGroupInfo[m_nGroupStepID].nStartStep, m_sGroupInfo[m_nGroupStepID].strGroupName);
	return 0;
}

int CBaseFlow::SetStep(int nStep,  LPCTSTR name )
{
	CString szMsg;
	int nThisStepGroupID = GetThisStepGroupID(nStep);
	ResetCompleteFlag();
	if (m_bManualStepFlag == TRUE && m_nGroupStepID != nThisStepGroupID)
	{
		
		m_bManualStepFlag = FALSE;
		m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = FALSE;
		m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = TRUE;
		return 0;
	}
	else
	{
		m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = TRUE;
		m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = FALSE;
	}
	ResetTimeOut();
	SetTimeOut(TIME_OUT_DEFAULT);
	//LOG_Msg(MSG_LEVEL2, _T("SetStep %s(%d) [%s]"), GetName(), nStep, m_seqName.c_str());
	if (!name)
		m_seqName = _T("");
	else
		m_seqName = name;
	Process_Msg(_T("SetStep (%d)[%s]"), nStep, m_seqName.c_str());

	m_nCurFlowStep = nStep;
	m_nCurFlowTotalStep = nStep;

	m_nRepeatCnt = 0;
	SetEvent(hMotionHandle);
	//SharedInfo::MachineState.bSemiAutoRunFlag = TRUE;
	return 0;
}


int CBaseFlow::SetCheckStep(int nStep, LPCTSTR name)
{
	int nThisStepGroupID = GetThisStepGroupID(nStep);
	ResetCompleteFlag();
	if (m_bManualStepFlag == TRUE && m_nGroupStepID != nThisStepGroupID)
	{		
		m_bManualStepFlag = FALSE;
		m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = FALSE;
		m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = TRUE;
		return 0;
	}
	else
	{
		m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = TRUE;
		m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = FALSE;
	}
	if (m_nRepeatCnt == 0)
	{
		if (!name)
			m_seqName = _T("");
		else
			m_seqName = name;
		Process_Msg(_T("SetCheckStep (%d)[%s]"), nStep, m_seqName.c_str());
	}
	m_nRepeatCnt++;
	m_nCurFlowTotalStep = nStep;
	SetEvent(hMotionHandle);

	return 0;
	
}
#else

int CBaseFlow::SetGroupStep(int nManualGroupID, BOOL bManualStepFlag)
{
	SharedInfo::bMachineStopFlag = FALSE; //Add

	m_nGroupStepID = nManualGroupID;
	m_nCurFlowStep = m_sGroupInfo[m_nGroupStepID].nStartStep;
	m_nCurFlowTotalStep = m_sGroupInfo[m_nGroupStepID].nStartStep;
	m_bManualStepFlag = bManualStepFlag;
	SetStep(m_sGroupInfo[m_nGroupStepID].nStartStep, m_sGroupInfo[m_nGroupStepID].strGroupName);
	return 0;
}


int CBaseFlow::SetStep(int nStep, LPCTSTR name)
{
	CString strTemp = _T("");
	int nThisStepGroupID = GetThisStepGroupID(nStep);
	ResetCompleteFlag();

	//m_nDisplayGroupStepID = nThisStepGroupID;

	if (m_nGroupStepID != nThisStepGroupID)
	{
		if (m_bManualStepFlag == TRUE)
		{
			m_bManualStepFlag = FALSE;
			m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = FALSE;
			m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = TRUE;
			return 0;
		}
		else
		{
			m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = FALSE;
			m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = TRUE;
			m_nGroupStepID = nThisStepGroupID;

		}


	}
	else
	{

		m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = TRUE;
		m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = FALSE;
	}

	ResetTimeOut();
	SetTimeOut(TIME_OUT_DEFAULT);
	//LOG_Msg(MSG_LEVEL2, _T("SetStep %s(%d) [%s]"), GetName(), nStep, m_seqName.c_str());
	if (!name)
		m_seqName = _T("");
	else
		m_seqName = name;
	
	strTemp.Format(_T("SetStep (%d)[%s]"), nStep, m_seqName);
	Process_Msg(strTemp);

	m_nCurFlowStep = nStep;
	m_nCurFlowTotalStep = nStep;

	m_nRepeatCnt = 0;
	SetEvent(hMotionHandle);
	//SharedInfo::MachineState.bSemiAutoRunFlag = TRUE;
	return 0;
}


int CBaseFlow::SetCheckStep(int nStep, LPCTSTR name)
{
	CString strTemp = _T("");
	int nThisStepGroupID = GetThisStepGroupID(nStep);
	ResetCompleteFlag();
	if (m_nGroupStepID != nThisStepGroupID)
		//if (m_nGroupStepID != nThisStepGroupID)
	{
		if (m_bManualStepFlag == TRUE)
		{
			m_bManualStepFlag = FALSE;
			m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = FALSE;
			m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = TRUE;
			return 0;
		}
		else
		{
			m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = FALSE;
			m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = TRUE;
			m_nGroupStepID = nThisStepGroupID;

		}

	}
	else
	{
		m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = TRUE;
		m_sGroupInfo[m_nGroupStepID].m_bCompleteFlag = FALSE;
	}

	if (m_nRepeatCnt == 0)
	{
		if (!name)
			m_seqName = _T("");
		else
			m_seqName = name;

		strTemp.Format(_T("SetCheckStep (%d)[%s]"), nStep, m_seqName);
		Process_Msg(strTemp);
	}
	m_nRepeatCnt++;
	m_nCurFlowTotalStep = nStep;
	SetEvent(hMotionHandle);

	return 0;

}

#endif


int CBaseFlow::SetStop()
{

	CString szMsg;
	ResetTimeOut();
	SetTimeOut(TIME_OUT_DEFAULT);
	//LOG_Msg(MSG_LEVEL2, _T("SetStep %s(%d) [%s]"), GetName(), nStep, m_seqName.c_str());
	
	//Log_Msg(_T("SetStop"));
	
	
	//m_nCurStep = 1;

	SetEvent(hMotionHandle);

	return 0;
}
int	CBaseFlow::SetFinish()
{
	
	m_sGroupInfo[m_nGroupStepID].m_bProcessingFlag = FALSE;
	return 0;
}