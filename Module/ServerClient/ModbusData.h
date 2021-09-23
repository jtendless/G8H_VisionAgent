#pragma once

class CModbusData
{
public:
	CModbusData(void);
	~CModbusData(void);

	void ModbusInit();
	int SendStatusSocketDataEx(int nFuncAddr, int nReturn, int nSize, int nReadWrite, byte* pbySendData);
	int SendDataEx(int nFuncAddr, int nReturn, byte* pby, int nSize, int nReadWrite, byte* pbySendData);	
	int ReceiveDataEx(char *chReceiveData, int* pnFuncAddr, int* pnReturn, byte* pby);	
		
	int LRCEncoderEx(byte* pbyData, int nSize);		
	int LRCDecoderEx(char* pch, int nSize);

	int m_nReciveCnt;
	int m_nAfterFilterCnt;

	int m_nWriteMode;

	int m_nTransactionID;
	int m_nProtocolID;
	int m_nLength;
	int m_nUnitID;
	int m_nReadFC;
	int m_nWriteFC;

	int m_nSendTransactionID;
	int m_nSendProtocolID;
	int m_nSendLength;
	int m_nSendUnitID;
	int m_nSendFC;	
	int m_nSendFuncAddr;
};

