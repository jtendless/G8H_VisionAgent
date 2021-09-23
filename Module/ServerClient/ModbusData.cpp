#include "stdafx.h"
#include "ModbusData.h"
#include "Common/CommonDefine.h"
#include "Log/Logger.h"


CModbusData::CModbusData(void)
{
	m_nWriteMode = 0;
	ModbusInit();
}

CModbusData::~CModbusData(void)
{
}

void CModbusData::ModbusInit()
{
	m_nTransactionID = 0;
	m_nProtocolID = 0;
	m_nLength = 0;
	m_nUnitID = 1;
	m_nReadFC = 3;
	m_nWriteFC = 16;

	m_nSendTransactionID = m_nTransactionID;
	m_nSendProtocolID = m_nProtocolID;
	m_nSendLength = 0;
	m_nSendUnitID = m_nUnitID;
	m_nSendFC = 0;
	m_nSendFuncAddr = 0;

	m_nReciveCnt = 0;
	m_nAfterFilterCnt = 0;
}


int CModbusData::SendStatusSocketDataEx(int nFuncAddr, int nReturn,int nSize, int nReadWrite, byte* pbySendData)
{
	m_nSendTransactionID = m_nTransactionID;
	m_nSendLength = nSize + 6;
	m_nSendFC = (nReadWrite == 0) ? m_nReadFC : m_nWriteFC;
	m_nSendFuncAddr = nFuncAddr;

	pbySendData[0] = ((m_nTransactionID >> 8) & 0xFF);
	pbySendData[1] = (m_nTransactionID & 0xFF);
	pbySendData[2] = ((m_nSendProtocolID >> 8) & 0xFF);
	pbySendData[3] = (m_nSendProtocolID & 0xFF);
	pbySendData[4] = ((m_nSendLength >> 8) & 0xFF);
	pbySendData[5] = (m_nSendLength & 0xFF);
	pbySendData[6] = m_nSendUnitID;
	pbySendData[7] = m_nSendFC;
	pbySendData[8] = ((m_nSendFuncAddr >> 8) & 0xFF);
	pbySendData[9] = (m_nSendFuncAddr & 0xFF);
	pbySendData[10] = ((nReturn >> 8) & 0xFF);
	pbySendData[11] = (nReturn & 0xFF);

	m_nTransactionID++;
	m_nTransactionID = m_nTransactionID % 10000;

	//TRACE(_T("m_nTransactionID = %d \n"), m_nTransactionID);

	
	LRCEncoderEx(pbySendData, nSize + 12);

	if (nReadWrite == 1) m_nWriteMode = 1;
	else m_nWriteMode = 0;

	return nSize + 13;
}

int CModbusData::SendDataEx(int nFuncAddr, int nReturn, byte* pby, int nSize, int nReadWrite, byte* pbySendData)
{
	m_nSendTransactionID = m_nTransactionID;
	m_nSendLength = nSize+6;
	m_nSendFC = (nReadWrite==0)? m_nReadFC : m_nWriteFC;
	m_nSendFuncAddr = nFuncAddr;

	pbySendData[0] = ((m_nTransactionID>>8) & 0xFF);
	pbySendData[1] = (m_nTransactionID & 0xFF);
	pbySendData[2] = ((m_nSendProtocolID>>8) & 0xFF);
	pbySendData[3] = (m_nSendProtocolID & 0xFF);
	pbySendData[4] = ((m_nSendLength>>8) & 0xFF);
	pbySendData[5] = (m_nSendLength & 0xFF);
	pbySendData[6] = m_nSendUnitID;
	pbySendData[7] = m_nSendFC;
	pbySendData[8] = ((m_nSendFuncAddr>>8) & 0xFF);
	pbySendData[9] = (m_nSendFuncAddr & 0xFF);
	pbySendData[10] = ((nReturn >> 8) & 0xFF);
	pbySendData[11] = (nReturn & 0xFF);
	
	m_nTransactionID++;
	m_nTransactionID = m_nTransactionID%10000;

	//TRACE(_T("m_nTransactionID = %d \n"), m_nTransactionID);

	memcpy(pbySendData+12, pby, nSize);
	LRCEncoderEx(pbySendData, nSize+12);

	if (nReadWrite == 1) m_nWriteMode = 1;
	else m_nWriteMode = 0;

	return nSize+13;
}

int CModbusData::ReceiveDataEx(char* pchReceiveData, int* pnFuncAddr, int* pnReturn, byte* pby)
{	
	int n;
	int nLength;	
	CString Str;
	
	//Log_Msg(_T("Recive Data #%d, Length : %d"), m_nReciveCnt++, sizeof(pchReceiveData));
	//if (m_nReciveCnt == 99999999)
	//	m_nReciveCnt = 0;

	nLength = *(pchReceiveData+4)<<8&0xFF00;
	nLength |= *(pchReceiveData+5)&0x00FF;

	
	
	if (nLength < 4 || 10000 < nLength)
	{
		Str.Format(_T("Data Filter Size : %d"), sizeof(pchReceiveData));
		Etc_Msg(Str);
		return FMM_COMM_ERROR_SIZE;
	}

	//	
	//Log_Msg(_T("Filter Data #%d, Length : %d"), m_nAfterFilterCnt++, sizeof(pchReceiveData));
	//if (m_nAfterFilterCnt == 99999999)
	//	m_nAfterFilterCnt = 0;

	if (LRCDecoderEx(pchReceiveData, nLength + 6) == 0) 
		return FMM_COMM_ERROR_LRC;

	n = *(pchReceiveData+0)<<8&0xFF00;
	n |= *(pchReceiveData+1)&0x00FF;
	//if (m_nWriteMode == 1 && m_nSendTransactionID != n)  return IQC_COMM_ERROR_TRANSACTION_ID;

	//TRACE(_T("m_nSendTransactionID=%d, n=%d \n"), m_nSendTransactionID, n);

	n = *(pchReceiveData+2)<<8&0xFF00;
	n |= *(pchReceiveData+3)&0x00FF;
	//if (m_nWriteMode == 1 && m_nSendProtocolID != n) return IQC_COMM_ERROR_PROTOCOL_ID;

	n = *(pchReceiveData+6);
	//if (m_nWriteMode == 1 && m_nSendUnitID != n) return IQC_COMM_ERROR_UNIT_ID;

	n = *(pchReceiveData+7);
	//if (m_nWriteMode == 1 && m_nSendFC != n) return IQC_COMM_ERROR_FC;

	n = *(pchReceiveData+8)<<8&0xFF00;
	n |= *(pchReceiveData+9)&0x00FF;
	//if (m_nWriteMode == 1 && m_nSendFuncAddr != n) return IQC_COMM_FUNCTION_ADDR;
	
	*pnFuncAddr = n;

	if (n == 30)
	{
		Str.Format(_T("Ajin Func %d"), n);
		Etc_Msg(Str);
	}

	if (n == 64)
	{
		Str.Format(_T("Umac Func %d"), n);
		Etc_Msg(Str);
	}

	if (n >= 300 && n <= 301)
	{
		Str.Format(_T("Vision Func %d"), n);
		Etc_Msg(Str);
	}
	
	*pnReturn = *(pchReceiveData+10)<<8&0xFF00;
	*pnReturn |= *(pchReceiveData+11)&0x00FF;


	pby = (byte*)pchReceiveData + 12;
	//memcpy(pby, pchReceiveData+12, nLength-6);

	return FMM_SUCCESS;	
}


int CModbusData::LRCEncoderEx(byte* pbyData, int nSize)
{
	int i;
	unsigned char uchLRC = 0;

	for(i=0; i<nSize; i++){
		uchLRC += *(pbyData+i);
	}

	uchLRC = ((unsigned char)(-((char)uchLRC)));
	*(pbyData+nSize) = uchLRC;
	*(pbyData+nSize+1) = 0;
	return 1; 
}

int CModbusData::LRCDecoderEx(char* pch, int nSize)
{
	int i;
	
	unsigned char uchLRC = 0;
	unsigned char uchReceiveLRC = 0;

	uchReceiveLRC = *(pch+nSize);

	for(i=0; i<nSize; i++){
		uchLRC += *(pch+i);
	}

	uchLRC = ((unsigned char)(-((char)uchLRC)));

	if(uchLRC == uchReceiveLRC) return TRUE;
	else return FALSE;
}