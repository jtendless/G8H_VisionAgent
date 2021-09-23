#include "stdafx.h"
#include "UserTimer.h"

///////////////////////////////////////////////////////////////////////
CUserTimer::CUserTimer(DWORD dwTimeOut)
{
	m_bLock = FALSE;
	m_dwTimeStamp = 0;
	m_dwTimeCompensator = 0;
	m_dwTimeOut = dwTimeOut;
}

CUserTimer::~CUserTimer()
{
}

int CUserTimer::SetTimer()
{
	// Timer�� set �Ǿ��ִ� ���¿����� �ٽ� set �� �� ����.
	if(m_bLock)	return TIMER_NG;

	m_dwTimeStamp = GetTickCount();
	m_dwTimeCompensator = MAXDWORD - m_dwTimeStamp;
	m_bLock = TRUE;

	return TIMER_OK;	
}

int CUserTimer::GetLapTime(DWORD* pdLapTime)
{
	DWORD dwTimeCurr;

	// Timer�� set �Ǿ����� ������, lap time�� ���� �� ����.
	if(!m_bLock) return	TIMER_NG;

	dwTimeCurr = GetTickCount();
	if(m_dwTimeStamp > dwTimeCurr)	dwTimeCurr += m_dwTimeCompensator;
	*pdLapTime = dwTimeCurr - m_dwTimeStamp;
	
	return TIMER_OK;
}

int CUserTimer::ReleaseTimer()
{
	// Timer�� set �Ǿ����� ������ �˸���.
	if(!m_bLock) return TIMER_NG;

	m_bLock = FALSE;

	return TIMER_OK;	
}

BOOL CUserTimer::CheckTimeOut()
{
	DWORD dwTimeCurr;

	// Timer�� set �Ǿ����� ������, lap time�� ���� �� ����.
	ASSERT(m_bLock);

	dwTimeCurr = GetTickCount();
	if(m_dwTimeStamp > dwTimeCurr)	dwTimeCurr += m_dwTimeCompensator;
	if(m_dwTimeOut < (dwTimeCurr - m_dwTimeStamp)) return TRUE;
	else return FALSE;
}

void CUserTimer::SetTimeOut(DWORD dwTimeOut)
{
	ASSERT(!m_bLock);

	m_dwTimeOut = dwTimeOut;
}
