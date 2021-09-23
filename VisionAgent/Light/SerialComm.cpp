#include "stdafx.h"
#include "SerialComm.h"
#include "UserTimer.h"

///////////////////////////////////////////////////////////////////////
CSerialComm::CSerialComm()
{
	m_hPort = NULL;
	m_nLastError = PORT_NOT_READY;
	m_pbtDataRead = NULL;	
	m_nReadInterval = 0;
}	

CSerialComm::~CSerialComm()
{
	m_hPort = NULL;
	if(m_pbtDataRead != NULL)	delete [] m_pbtDataRead;
}

int CSerialComm::OpenPort(CString stPortName, DWORD dwMaxReadSize)
{
	m_dwMaxReadSize = dwMaxReadSize;

	if (m_hPort != NULL) 
		return	m_nLastError = PORT_OPEN_ERROR;

	m_hPort = CreateFile(stPortName.operator LPCTSTR(),
						GENERIC_READ | GENERIC_WRITE,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL);	
	
	if(m_hPort == INVALID_HANDLE_VALUE) 
		return	m_nLastError = PORT_OPEN_ERROR;
	else										
		m_nLastError = PORT_OK;
		
	m_nLastError = ConfigPort();

	if(!m_nLastError) {
		if(m_pbtDataRead == NULL) m_pbtDataRead = new BYTE[m_dwMaxReadSize];
		if(m_pbtDataRead != NULL) ZeroMemory(m_pbtDataRead, m_dwMaxReadSize);
		else					  m_nLastError = PORT_NOT_READY;
	}
	
	return m_nLastError;
}

int CSerialComm::ConfigPort()
{
	return	m_nLastError;
}

int CSerialComm::ClosePort()
{
	if(m_hPort == NULL)		m_nLastError = PORT_OK;
	else {
		if(m_hPort == INVALID_HANDLE_VALUE) {
			m_hPort = NULL;
			m_nLastError = PORT_OK;
		}
		else {	// m_hPort != NULL
			if(!PurgeComm(m_hPort, PURGE_TXCLEAR | PURGE_RXCLEAR))
				return	(m_nLastError = PORT_CONFIGURE_ERROR);
			if(!CloseHandle(m_hPort))	m_nLastError = PORT_CLOSE_ERROR;
			else {
				m_nLastError = PORT_OK;
				m_hPort = NULL;
			}
		}
	}

	return m_nLastError;
}

int CSerialComm::ReadPort()
{
	COMSTAT		ComStat;
	DWORD		dwErrorFlags = 0;
	DWORD		dwBytesToRead = 0;
	DWORD		dwBytesRead = 0;
	BYTE*		pbtReadOneTime = NULL;
	int			nReadSeq = 0;
	BOOL		bIsSeqEnd = FALSE;
	BOOL		bWaitFirstChar = TRUE;
	CUserTimer	tmrCheck(2000);

	pbtReadOneTime = new BYTE[m_dwMaxReadSize];
	m_dwTotalReadBytes = 0;

	tmrCheck.SetTimer();

	while(!m_nLastError && !bIsSeqEnd) {
		switch(nReadSeq) {
			case 0:		// check if any byte is in the buffer
				if(!ClearCommError(m_hPort, &dwErrorFlags, &ComStat))
					m_nLastError = PORT_COMSTAT_ACESS_ERROR;
				nReadSeq = 10;
				break;
			case 10:	// if nothing is in the buffer, end sequence
				dwBytesToRead = min(m_dwMaxReadSize, ComStat.cbInQue);
				if(dwBytesToRead == 0) {
					if(bWaitFirstChar) {
						if(tmrCheck.CheckTimeOut()) m_nLastError = PORT_READ_ERROR;
						else {
							nReadSeq = 0;
							break;
						}
					}
					else bIsSeqEnd = TRUE;
				}
				else {
					if(bWaitFirstChar)	bWaitFirstChar = FALSE;
				}
				nReadSeq = 20;
				break;
			case 20:	// read port
				if(!ReadFile(m_hPort, pbtReadOneTime, dwBytesToRead, &dwBytesRead, NULL))
					m_nLastError = PORT_READ_ERROR;
				Sleep(m_nReadInterval);
				nReadSeq = 30;				
				break;
			case 30:	// copy data from temp storage to member storage
				CopyMemory(&m_pbtDataRead[m_dwTotalReadBytes], pbtReadOneTime, dwBytesRead);
				m_dwTotalReadBytes += dwBytesRead;
					
				nReadSeq = 0;
				break;
			default: 
				break;
		}
	}

	if(pbtReadOneTime != NULL) {
		delete [] pbtReadOneTime;
		pbtReadOneTime = NULL;
	}

	return m_nLastError;
}

int CSerialComm::WritePort(char *pData, int nSize)
{
	DWORD	dwByteWritten = 0;

	if (!WriteFile(m_hPort, pData, nSize, &dwByteWritten, NULL)) {
		m_nLastError = PORT_WRITE_ERROR;
	}

	return m_nLastError;
}

int CSerialComm::WritePort(CString stDataToWrite)
{
	DWORD	dwByteWritten = 0;

	if (!WriteFile(m_hPort, stDataToWrite.operator LPCTSTR(), stDataToWrite.GetLength(), &dwByteWritten, NULL))	{
		m_nLastError = PORT_WRITE_ERROR;
	}

	return m_nLastError;
}


int CSerialComm::CleanPort()
{
	if(!PurgeComm(m_hPort, PURGE_TXCLEAR|PURGE_RXCLEAR)) return	(m_nLastError = PORT_CLEAN_ERROR);
		
	m_dwTotalReadBytes = 0;

	if(m_pbtDataRead != NULL) ZeroMemory(m_pbtDataRead, m_dwMaxReadSize);
	
	return m_nLastError;
}
