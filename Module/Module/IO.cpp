#include "stdafx.h"
#include "IO.h"

UINT IOCheckThread(LPVOID lpParam)
{
	CIO* pIO = (CIO*)lpParam;

	//int i, nStatus;
	double dSamplingTime = 10.0;

	pIO->m_nIsRunningIOCheckThread = 1;
	while (!pIO->m_nStopIOCheckThread)
	{
		// Use Ajinextek Dll IO Check
	}

	pIO->m_nIsRunningIOCheckThread = 0;
	pIO->m_pIOCheckThread = NULL;
	return 0;
}

CIO::CIO()
{	
	int i, j;

	m_pIOCheckThread = NULL;
	m_nStopIOCheckThread = 1;
	m_nIsRunningIOCheckThread = 0;
	
	for (i = 0; i < 8; i++){
		for (j = 0; j < 16; j++){
			m_nInputActiveLevel[i][j] = 1;
			m_nOutputActiveLevel[i][j] = 1;

			m_nPrevInput[i][j] = 0;
			m_nPrevOutput[i][j] = 0;

			m_nInput[i][j] = 0;
			m_nOutput[i][j] = 0;
		}
	}
		
	for (i = 0; i < 2; i++){
		for (j = 0; j < 16; j++){
			m_nPrevAnalogInput[i][j] = 0;
			m_nAnalogInput[i][j] = 0;
		}
	}
}


CIO::~CIO()
{
	StopIOCheck();
}


int CIO::StartIOCheck()
{
	if (m_pIOCheckThread == NULL){
		m_nStopIOCheckThread = 0;
		m_pIOCheckThread = AfxBeginThread(IOCheckThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		Sleep(100);
		m_pIOCheckThread->ResumeThread();
	}
	return 0;
}


int CIO::StopIOCheck()
{
	int i;

	if (m_pIOCheckThread != NULL){
		i = 0;
		m_nStopIOCheckThread = 1;
		do{
			i++;
			Sleep(100);
		} while (m_nIsRunningIOCheckThread == 1 && i < 30);
	}
	
	return 0;
}


int CIO::GetAnalogInputBit(int nWordNo, int nBitNo)
{
	if (nWordNo < 0 || 2 < nWordNo) return -1;
	if (nBitNo < 0 || 16 < nBitNo) return -1;

	return m_nAnalogInput[nWordNo][nBitNo];
}


int CIO::GetActiveInputBit(int nWordNo, int nBitNo)
{	
	if (nWordNo < 0 || 8 < nWordNo) return -1;
	if (nBitNo < 0 || 16 < nBitNo) return -1;

	return (m_nInputActiveLevel[nWordNo][nBitNo] == m_nInput[nWordNo][nBitNo]) ? 1 : 0;
}


int CIO::GetActiveOutputBit(int nWordNo, int nBitNo)
{
	if (nWordNo < 0 || 8 < nWordNo) return -1;
	if (nBitNo < 0 || 16 < nBitNo) return -1;

	return (m_nOutputActiveLevel[nWordNo][nBitNo] == m_nOutput[nWordNo][nBitNo]) ? 1 : 0;
}


int CIO::SetActiveOutputBit(int nWordNo, int nBitNo)
{
	if (nWordNo < 0 || 8 < nWordNo) return -1;
	if (nBitNo < 0 || 16 < nBitNo) return -1;

	// Use Ajinextek Dll IO Set
	return 0;
}


int CIO::SetNonActiveOutputBit(int nWordNo, int nBitNo)
{
	if (nWordNo < 0 || 8 < nWordNo) return -1;
	if (nBitNo < 0 || 16 < nBitNo) return -1;

	// Use Ajinextek Dll IO Set
	return 0;
}