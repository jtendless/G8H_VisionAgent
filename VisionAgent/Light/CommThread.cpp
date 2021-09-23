#include "stdafx.h"
#include "CommThread.h"


//	Queue
void CQueue::Clear()
{
	m_iHead = m_iTail =0;
	memset(buff,0,BUFF_SIZE);
}

CQueue::CQueue()
{
	Clear();
}

int CQueue::GetSize()
{
	return (m_iHead - m_iTail + BUFF_SIZE) % BUFF_SIZE;
}

BOOL CQueue::PutByte(BYTE b)
{
	if(GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] =b;
	m_iHead %= BUFF_SIZE;
	return TRUE;
}

BOOL CQueue::GetByte(BYTE *pb)
{
	if(GetSize() == 0) return FALSE;
	*pb = buff[m_iTail++];
	m_iTail %= BUFF_SIZE;
	return TRUE;
}



// CommThread

CCommThread::CCommThread()
{
	m_bConnected = FALSE;
	m_hCommWnd = NULL;
	m_nType = 0;
}

CCommThread::~CCommThread()
{
}


BOOL CCommThread::OpenPort(CString strPortName, 
					   DWORD dwBaud, BYTE byData, BYTE byStop, BYTE byParity )
{
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
	DWORD			dwThreadID;

	if(m_hCommWnd == NULL) return FALSE;

	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;

	if ( !(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) ) 	
	{
		return FALSE;
	}

	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;

	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		return FALSE;
	}

	m_sPortName = strPortName;

	m_hComm = CreateFile( m_sPortName, 
						  GENERIC_READ | GENERIC_WRITE, 0, NULL,
						  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
						  NULL);

	
//		if (m_hComm == (HANDLE) -1)
//		{
//			AfxMessageBox("fail Port open");
//			return FALSE;
//		}
	
	SetCommMask( m_hComm, EV_RXCHAR);	
	SetupComm( m_hComm, BUFF_SIZE, BUFF_SIZE);	
	PurgeComm( m_hComm,					
			   PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_9600 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	
	SetCommTimeouts( m_hComm, &timeouts);

	dcb.DCBlength = sizeof(DCB);
	GetCommState( m_hComm, &dcb);	
	
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = byData;
	dcb.Parity = byParity;
	dcb.StopBits = byStop;

	if( !SetCommState( m_hComm, &dcb) )	
	{
		return FALSE;
	}

	m_bConnected = TRUE;
	m_hThreadWatchComm = CreateThread( NULL, 0, 
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm, 
									   this, 0, &dwThreadID);

	if (! m_hThreadWatchComm)
	{
		ClosePort();
		return FALSE;
	}
	check = FALSE;

	return TRUE;
}
	
void CCommThread::ClosePort()
{
	m_bConnected = FALSE;
	
	SetCommMask( m_hComm, 0);
	PurgeComm( m_hComm,	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	
	CloseHandle(m_hComm);
}

DWORD CCommThread::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten, dwError, dwErrorFlags;
	COMSTAT	comstat;

	if( !m_bConnected )		
	{
		return 0;
	}

	if( !WriteFile( m_hComm, pBuff, nToWrite, &dwWritten, &m_osWrite))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, TRUE))
			{
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}

	return dwWritten;
}

DWORD CCommThread::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead,dwError, dwErrorFlags;
	COMSTAT comstat;

	ClearCommError( m_hComm, &dwErrorFlags, &comstat);

	dwRead = comstat.cbInQue;
	if(dwRead > 0)
	{
		if( !ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead) )
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	return dwRead;
}

DWORD	ThreadWatchComm(CCommThread* pComm)
{
	DWORD           dwEvent;
	OVERLAPPED      os;
	BOOL            bOk = TRUE;
	BYTE            buff[2048];
	DWORD           dwRead;

	memset( &os, 0, sizeof(OVERLAPPED));

	if( !(os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL)) )
	{
		bOk = FALSE;
	}

	if( !SetCommMask( pComm->m_hComm, EV_RXCHAR) )
	{
		bOk = FALSE;
	}

	if( !bOk )
	{
		AfxMessageBox(_T("Error while creating ThreadWatchComm, ") + pComm->m_sPortName);
		return FALSE;
	}
  
	while (pComm->m_bConnected)
	{
		dwEvent = 0;

		WaitCommEvent( pComm->m_hComm, &dwEvent, NULL);

		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			do
			{
				dwRead = pComm->ReadComm( buff, 2048);
				if(BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwRead)
				{
					for( WORD i = 0; i < dwRead; i++ )
					{
						pComm->m_QueueRead.PutByte(buff[i]);
					}
				}
				else
				{
					//AfxMessageBox(_T("buff full"));
					pComm->m_QueueRead.Clear();
				}
			} while(dwRead);
		//	::PostMessage(pComm->m_hCommWnd, NAMSG_COMM_READ, (WPARAM)(pComm->m_hComm), 0);
			::SendMessage(pComm->m_hCommWnd, UM_SERIAL_COMMAND_MSG, (WPARAM)(pComm->m_nType), 0);
		}
		Sleep(0);
	}
   
	CloseHandle( os.hEvent);
	pComm->m_hThreadWatchComm = NULL;

	return TRUE;
}

BOOL CCommThread::OpenPort()
{
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
	DWORD			dwThreadID;

	if(m_hCommWnd == NULL) return FALSE;

	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	if ( !(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) ) 	
	{
		return FALSE;
	}

	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		return FALSE;
	}
	
	m_hComm = CreateFile( m_strPort, 
						  GENERIC_READ | GENERIC_WRITE, 0, NULL,
						  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
						  NULL);

	SetCommMask( m_hComm, EV_RXCHAR);	
	SetupComm( m_hComm, BUFF_SIZE, BUFF_SIZE);	

	PurgeComm( m_hComm,					
			   PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_9600 / m_iBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	
	SetCommTimeouts( m_hComm, &timeouts);
	dcb.DCBlength = sizeof(DCB);
	GetCommState( m_hComm, &dcb);	
	dcb.BaudRate = m_iBaud;
	dcb.ByteSize = m_iData;
	dcb.Parity = m_iParity;
	dcb.StopBits = m_iStop;

	if( !SetCommState( m_hComm, &dcb) )	
	{
		return FALSE;
	}

	m_bConnected = TRUE;
	m_hThreadWatchComm = CreateThread( NULL, 0, 
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm, 
									   this, 0, &dwThreadID);

	if (! m_hThreadWatchComm)
	{
		ClosePort();
		return FALSE;
	}
	check = FALSE;

	return TRUE;
}
