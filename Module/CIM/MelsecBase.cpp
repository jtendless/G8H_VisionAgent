#include "stdafx.h"
#include "MelsecBase.h"

CMelsecBase::CMelsecBase()
{
	m_sChannelNo = 0;
	m_lChannelPath = 0;
	m_lNetworkNo = 0;
	m_lStationNo = 0;

	m_nConnected = FALSE;
}

CMelsecBase::~CMelsecBase()
{
}

int CMelsecBase::MelsecOpen(short sChannelNo, long lChannelPath, long lNetworkNo, long lStationNo) //KJT 20210416
{
	short	ret = 0;

	m_sChannelNo = sChannelNo;
	m_lChannelPath = lChannelPath;
	m_lNetworkNo = lNetworkNo;
	m_lStationNo = lStationNo;

#if !CIM_SKIP_MODE
	ret = mdOpen(m_sChannelNo, -1, &m_lChannelPath);	//	open 1st MNETG board	
#endif

	if (ret == 0)
	{
		m_nConnected = TRUE;		
	}
	else
	{
		m_nConnected = FALSE;
	}

	return m_nConnected;
}
int CMelsecBase::MelsecClose() //KJT 20210416
{
	short	ret = 0;

#if !CIM_SKIP_MODE
	ret = mdClose(m_lChannelPath);
#endif

	if (ret == 0)
	{
		m_nConnected = FALSE;
	}
	else
	{
		AfxMessageBox(_T("Melsec Close Error"));
	}

	return ret;
}
int CMelsecBase::MelsecSendData(int nDevType, int nDevNo, long lDataSize, VOID *lData) //KJT 20210416
{
	long lRtn = 0;
	long lStationNo;
	long lNetworkNo;

	if (!m_nConnected) return -1;
	if (m_lChannelPath == NULL)  return -1;

	m_Critical.Lock();
	
	lStationNo = m_lStationNo;
	lNetworkNo = m_lNetworkNo;

#if !CIM_SKIP_MODE
	lRtn = mdSendEx(m_lChannelPath, lNetworkNo, lStationNo, nDevType, nDevNo, &lDataSize, lData);
#endif

	m_Critical.Unlock();

	return (int)lRtn;
}
int CMelsecBase::MelsecSendBit(int nDevType, int nDevNo, BOOL bVaue) //KJT 20210416
{
	long lRtn = 0;
	long lStationNo;
	long lNetworkNo;
	long plDataSize = 1;
	if (!m_nConnected) return -1;
	if (m_lChannelPath == NULL)  return -1;

	m_Critical.Lock();

	lStationNo = m_lStationNo;
	lNetworkNo = m_lNetworkNo;

#if !CIM_SKIP_MODE
	if (bVaue == TRUE)
		lRtn = mdDevSetEx(m_lChannelPath, lNetworkNo, lStationNo, nDevType, nDevNo);
	else
		lRtn = mdDevRstEx(m_lChannelPath, lNetworkNo, lStationNo, nDevType, nDevNo);
#endif

	//lRtn = mdSendEx(m_lChannelPath, m_lNetworkNo, lStationNo, nDevType, nDevNo, &lDataSize, &lData);
	//lRtn = mdSendEx(m_lChannelPath, 3, 1, nDevType, nDevNo, &lDataSize, &lData);

	m_Critical.Unlock();

	return (int)lRtn;
}
int CMelsecBase::MelsecReceiveData(int nDevType, int nDevNo, long plDataSize, VOID *plData) //KJT 20210416
{
	long lRtn = 0;
	long lStationNo;
	long lNetworkNo;

	BYTE sData[3000];
	DWORD IData[4]; //IData[2];

	if (!m_nConnected) return -1;
	if (m_lChannelPath == NULL)  return -1;

	m_Critical.Lock();

	lStationNo = m_lStationNo;
	lNetworkNo = m_lNetworkNo;

#if !CIM_SKIP_MODE
	lRtn = mdReceiveEx(m_lChannelPath, lNetworkNo, lStationNo, nDevType, nDevNo, &plDataSize, sData);
#endif

	//lRtn = mdReceiveEx(m_lChannelPath, m_lNetworkNo, m_lStationNo, nDevType, nDevNo, plDataSize,  plData); // long typeA¨¬ 1word¢¥UA¡×¡Æ¨£AI ¢¬©ªA¨¢A¨ö
	memcpy(plData, sData, plDataSize);

	m_Critical.Unlock();

	return (int)lRtn;
}
BOOL CMelsecBase::MelsecReadBit(int nDevType, int nDevNo) //KJT 20210416
{
	long lRtn;
	long lStationNo;
	long lNetworkNo;
	long lDevNo;
	long plDataSize = 1;
	BYTE sData = 0;
	DWORD IData[4]; //IData[2];
	lDevNo = nDevNo - (nDevNo % 8);
	if (!m_nConnected) return -1;
	if (m_lChannelPath == NULL)  return -1;

	m_Critical.Lock();

	lStationNo = m_lStationNo;
	lNetworkNo = m_lNetworkNo;

#if !CIM_SKIP_MODE
	lRtn = mdReceiveEx(m_lChannelPath, lNetworkNo, lStationNo, nDevType, lDevNo, &plDataSize, &sData);
	//lRtn = mdReceiveEx(m_lChannelPath, m_lNetworkNo, m_lStationNo, nDevType, nDevNo, plDataSize,  plData); // long typeA¨¬ 1word¢¥UA¡×¡Æ¨£AI ¢¬©ªA¨¢A¨ö
#endif

	m_Critical.Unlock();

	return(sData >> (nDevNo - lDevNo) & 0x1);
}
int CMelsecBase::MelsecReadData(int nDevType, int nDevNo, long pDataSize, VOID *plData) //KJT 20210416
{
	long lRtn = 0;
	long lStationNo;
	long lNetworkNo;
	long plDataSize = pDataSize;
	BYTE sData[3000];
	DWORD IData[4]; //IData[2];

	if (!m_nConnected) return -1;
	if (m_lChannelPath == NULL)  return -1;

	m_Critical.Lock();

	lStationNo = m_lStationNo;
	lNetworkNo = m_lNetworkNo;

#if !CIM_SKIP_MODE
	lRtn = mdReceiveEx(m_lChannelPath, lNetworkNo, lStationNo, nDevType, nDevNo, &plDataSize, plData);
	//lRtn = mdReceiveEx(m_lChannelPath, m_lNetworkNo, m_lStationNo, nDevType, nDevNo, plDataSize,  plData); // long typeA¨¬ 1word¢¥UA¡×¡Æ¨£AI ¢¬©ªA¨¢A¨ö
#endif

	m_Critical.Unlock();

	return (int)lRtn;
}

int CMelsecBase::DeviceReset() //KJT 20210416
{
	long lRtn = 0;
	long lStationNo;
	long lNetworkNo;
	long plDataSize = 1;
	if (!m_nConnected) return -1;
	if (m_lChannelPath == NULL)  return -1;

	m_Critical.Lock();
	
	lStationNo = m_lStationNo;
	lNetworkNo = m_lNetworkNo;

#if !CIM_SKIP_MODE
	lRtn = mdBdRst(m_lChannelPath);
	
	//lRtn = mdSendEx(m_lChannelPath, m_lNetworkNo, lStationNo, nDevType, nDevNo, &lDataSize, &lData);
	//lRtn = mdSendEx(m_lChannelPath, 3, 1, nDevType, nDevNo, &lDataSize, &lData);
#endif

	m_Critical.Unlock();

	return (int)lRtn;
}


int CMelsecBase::LBBitWrite(int nAddr, BOOL bValue)
{
	int nRtn;
	nRtn = MelsecSendBit(_PLC_DEV_TYPE_B, nAddr, bValue);
	return nRtn;
}
BOOL CMelsecBase::LBBitRead(int nAddr)
{
	BOOL bValue;
	bValue = MelsecReadBit(_PLC_DEV_TYPE_B, nAddr);
	return bValue;
}

int CMelsecBase::LBWrite(int nAddr, void* pValue, int nSize)
{
	int nRtn = 0;
	if (m_nConnected == TRUE)
		nRtn = MelsecSendData(_PLC_DEV_TYPE_B, nAddr, nSize, pValue);
	return nRtn;
}

int CMelsecBase::LBRead(int nAddr, void* pValue, int nSize)
{
	int nRtn;
	nRtn = MelsecReadData(_PLC_DEV_TYPE_B, nAddr, nSize, pValue);
	return nRtn;
}

int CMelsecBase::LWWrite(int nAddr, void* pValue, int nSize)
{
	int nRtn;
	nRtn = MelsecSendData(_PLC_DEV_TYPE_W, nAddr, nSize, pValue);
	return nRtn;
}

int CMelsecBase::LWRead(int nAddr, void* pValue, int nSize)
{
	int nRtn;
	nRtn = MelsecReadData(_PLC_DEV_TYPE_W, nAddr, nSize, pValue);
	return nRtn;
}