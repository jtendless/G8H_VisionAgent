#include "stdafx.h"
#include "Sensing.h"
#include "../Dll/Ajin/include/AXD.h"	
#include "../Dll/Ajin/include/AXA.h"	
//-----------------------------------------------------------------------------//
CSensing::CSensing()
{

}
//-----------------------------------------------------------------------------
CSensing::~CSensing()
{

}
//-----------------------------------------------------------------------------
BOOL CSensing::InitProcess()
{	
	m_StateFinish			= TRUE;
	m_nMax_DI_Size			= 0;
	m_nMax_DI_Module_Size	= 0;
	for (int i = 0; i < MAX_MODULE_SIZE; i++)
	{
		m_nDI_Size[i] = 0;
	}
	for (int i = 0; i < MAX_DI_SIZE; i++)
	{
		m_nDI_ModuleNo[i] = 0;
	}

	m_nMax_DO_Size			= 0;
	m_nMax_DO_Module_Size	= 0;
	for (int i = 0; i < MAX_MODULE_SIZE; i++)
	{
		m_nDO_Size[i] = 0;
	}
	for (int i = 0; i < MAX_DO_SIZE; i++)
	{
		m_nDO_ModuleNo[i] = 0;
	}

	m_nMax_AI_Size			= 0;
	m_nMax_AI_Module_Size	= 0;
	for (int i = 0; i < MAX_MODULE_SIZE; i++)
	{
		m_nAI_Size[i] = 0;
	}
	for (int i = 0; i < MAX_AI_SIZE; i++)
	{
		m_nAI_ModuleNo[i] = 0;
	}
	for (int i = 0; i < MAX_AI_SIZE; i++)
	{
		m_dAInputOffset[i]		= 0.0;
		m_dAInputCALScale[i]	= 1.0;
		m_dAInputCALOffset[i]	= 0.0;
		m_nAInputCALApply[i]	= 0;
	}

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);

	pThread = AfxBeginThread(ThreadFunction, this);
	return TRUE;
}
//-----------------------------------------------------------------------------
BOOL CSensing::EndProcess()
{
	m_StateFinish = FALSE;

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
BOOL	CSensing::Init_DI_Board()
{
	long	lModuleCount	= 0;
	long	lCount			= 0;
	int		nDInputIndex	= 0;
	AxdInfoGetModuleCount(&lModuleCount);
	for (int i = 0; i < lModuleCount; i++)
	{
		//Input
		AxdInfoGetInputCount(i, &lCount);
		m_nMax_DI_Size += lCount;
		for (int j = 0; j < lCount; j++)
		{
			m_nDI_ModuleNo[nDInputIndex++] = i;
		}

		m_nDI_Size[m_nMax_DI_Module_Size] = lCount;

		m_nMax_DI_Module_Size++;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
BOOL	CSensing::Init_DO_Board()
{
	long	lModuleCount	= 0;
	long	lCount			= 0;
	int		nDOnputIndex	= 0;
	AxdInfoGetModuleCount(&lModuleCount);
	for (int i = 0; i < lModuleCount; i++)
	{		
		//Output
		AxdInfoGetOutputCount(i, &lCount);
		m_nMax_DO_Size += lCount;
		for (int j = 0; j < lCount; j++)
		{
			m_nDO_ModuleNo[nDOnputIndex++] = i;
		}

		m_nDO_Size[m_nMax_DO_Module_Size] = lCount;

		m_nMax_DO_Module_Size++;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
BOOL	CSensing::Init_AI_Board()
{
	long	lModuleCount = 0;
	long	lCount = 0;
	int		nAi_Index = 0;
	AxaInfoGetModuleCount(&lModuleCount);
	for (int i = 0; i < lModuleCount; i++)
	{
		//Input
		AxaInfoGetInputCount(i, &lCount);
		m_nMax_AI_Size += lCount;
		for (int j = 0; j < lCount; j++)
		{
			m_nAI_ModuleNo[nAi_Index++] = i;
		}

		m_nAI_Size[m_nMax_AI_Module_Size] = lCount;
		m_nMax_AI_Module_Size++;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
BOOL CSensing::Start()
{
	return TRUE;
}
//-----------------------------------------------------------------------------
BOOL CSensing::Stop()
{
	return TRUE;
}
//-----------------------------------------------------------------------------
UINT CSensing::ThreadFunction(LPVOID lpParam)
{
	CSensing* pFlow = NULL;

	pFlow = (CSensing*)lpParam;

	pFlow->ThreadFunctionEntry();

	return 0;
}
//-----------------------------------------------------------------------------
BOOL	CSensing::Is_Dig_Input(int nBit)
{
	BOOL	bFlag = m_nDInputValue[nBit];
	return	bFlag;
}
//-----------------------------------------------------------------------------
BOOL	CSensing::Set_Dig_Output(int nBit, bool bOnOff)
{
	if ((nBit >= MAX_DOUTPUT_SIZE) || (nBit < 0))
	{
		return FALSE;
	}
		
	int nModuleNo = m_nDO_ModuleNo[nBit];
	int i, nSumDOutputSize = 0, nOffset = 0;

	for (i = 0; i < nModuleNo; i++)
	{
		nSumDOutputSize += m_nDO_ModuleNo[i];
	}

	//if (nSumDOutputSize > 0) nSumDOutputSize--;
	nOffset = nBit - nSumDOutputSize;

	AxdoWriteOutportBit(nModuleNo, nOffset, bOnOff);

	return TRUE;
}
//-----------------------------------------------------------------------------
VOID CSensing::ThreadFunctionEntry(VOID)
{
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();

	DWORD	dwDInputValue	= 0;
	DWORD	dwDOutputValue	= 0;
	DWORD	dwStatus;
	DWORD	dwValue;
	int		nBaseDWordBitNo = 0;
	int		nDWordNo		= 0;
	int		nBaseBitNo		= 0;
	double	dVolt			= 0.000;
	double	dTempVolt		= 0.00;
	while (m_StateFinish)
	{
		//DInput
		dwDInputValue = 0;
		nBaseDWordBitNo = 0;
		nDWordNo = 0;
		nBaseBitNo = 0;
		for (int i = 0; i < m_nMax_DI_Size; i++)
		{	
			if (m_nDI_Size[i] == 16)
			{
				AxdiReadInportWord(i, 0, &dwValue);

				for (int j = 0; j < 16; j++)
				{
					dwStatus = (dwValue & (0x01 << j));
					dwStatus = (dwStatus >> j);

					m_nDInputValue[nBaseBitNo + j] = dwStatus;

					if (dwStatus > 0)
					{
						dwDInputValue = dwDInputValue | (0x01 << nBaseDWordBitNo);
					}

					nBaseDWordBitNo++;

					if (nBaseDWordBitNo >= 32)
					{
						m_dwDInputDWordValue[nDWordNo] = dwDInputValue;
						dwDInputValue = 0;
						nBaseDWordBitNo = 0;
						nDWordNo++;
					}
				}

				nBaseBitNo += m_nDI_Size[i];
			}
			else if (m_nDI_Size[i] == 32)
			{
				AxdiReadInportDword(i, 0, &dwValue);

				for (int j = 0; j < 32; j++)
				{
					dwStatus = (dwValue & (0x01 << j));
					dwStatus = (dwStatus >> j);

					m_nDInputValue[nBaseBitNo + j] = dwStatus;

					if (dwStatus > 0)
					{
						dwDInputValue = dwDInputValue | (0x01 << nBaseDWordBitNo);
					}

					nBaseDWordBitNo++;

					if (nBaseDWordBitNo >= 32)
					{
						m_dwDInputDWordValue[nDWordNo] = dwDInputValue;
						dwDInputValue = 0;
						nBaseDWordBitNo = 0;
						nDWordNo++;
					}
				}
				nBaseBitNo += m_nDI_Size[i];
			}
			Sleep(0);
		}

		Sleep(1);

		//DOutput
		dwDOutputValue = 0;
		nBaseDWordBitNo = 0;
		nDWordNo = 0;
		nBaseBitNo = 0;
		for (int i = 0; i < m_nMax_DO_Module_Size; i++)
		{
			if (m_nDO_Size[i] == 16)
			{
				AxdoReadOutportWord(i, 0, &dwValue);

				for (int j = 0; j < 16; j++)
				{
					dwStatus = (dwValue & (0x01 << j));
					dwStatus = (dwStatus >> j);

					m_nDOutputValue[nBaseBitNo + j] = dwStatus;

					if (dwStatus > 0)
					{
						dwDOutputValue = dwDOutputValue | (0x01 << nBaseDWordBitNo);
					}

					nBaseDWordBitNo++;

					if (nBaseDWordBitNo >= 32)
					{
						m_dwDOutputDWordValue[nDWordNo] = dwDOutputValue;
						dwDOutputValue = 0;
						nBaseDWordBitNo = 0;
						nDWordNo++;
					}
				}

				nBaseBitNo += m_nDO_Size[i];
			}
			else if (m_nDO_Size[i] == 32)
			{
				AxdoReadOutportDword(i, 0, &dwValue);

				for (int j = 0; j < 32; j++)
				{
					dwStatus = (dwValue & (0x01 << j));
					dwStatus = (dwStatus >> j);

					m_nDOutputValue[nBaseBitNo + j] = dwStatus;

					if (dwStatus > 0)
					{
						dwDOutputValue = dwDOutputValue | (0x01 << nBaseDWordBitNo);
					}

					nBaseDWordBitNo++;

					if (nBaseDWordBitNo >= 32)
					{
						m_dwDOutputDWordValue[nDWordNo] = dwDOutputValue;
						dwDOutputValue = 0;
						nBaseDWordBitNo = 0;
						nDWordNo++;
					}
				}
				nBaseBitNo += m_nDO_Size[i];
			}
			Sleep(0);
		}

		Sleep(1);

		//AInput
		nBaseBitNo = 0;
		for (int i = 0; i < m_nMax_AI_Size; i++)
		{
			AxaiSwReadVoltage(i, &dVolt);

			dTempVolt = dVolt + m_dAInputOffset[i];

			if (m_nAInputCALApply[i] == TRUE)
			{
				m_dAInputValue[i] = dTempVolt * m_dAInputCALScale[i] + m_dAInputCALOffset[i];
			}
			else
			{
				m_dAInputValue[i] = dTempVolt;
			}
			Sleep(0);
		}

		Sleep(1);
	}
}
//-----------------------------------------------------------------------------//
