#pragma once

class CMelsecBase
{
public:
	CMelsecBase();
	~CMelsecBase();

	enum
	{
		_PLC_DEV_TYPE_X = 1,
		_PLC_DEV_TYPE_Y = 2,
		_PLC_DEV_TYPE_D = 13,
		_PLC_DEV_TYPE_R = 22,
		_PLC_DEV_TYPE_B = 23,
		_PLC_DEV_TYPE_W = 24,
	};

	INT m_nConnected;
	short m_sChannelNo;
	long m_lChannelPath;
	long m_lNetworkNo;
	long m_lStationNo;

	CCriticalSection m_Critical;

	//Basic
	int MelsecOpen(short sChannelNo, long lChannelPath, long lNetworkNo, long lStationNo);
	int MelsecClose();
	int MelsecSendData(int nDevType, int nDevNo, long lDataSize, VOID *lData);
	int MelsecReceiveData(int nDevType, int nDevNo, long plDataSize, VOID *plData);
	int MelsecReadData(int nDevType, int nDevNo, long plDataSize, VOID *plData);
	int MelsecSendBit(int nDevType, int nDevNo, BOOL bVaue);
	BOOL MelsecReadBit(int nDevType, int nDevNo);

	//Device Reset
	int DeviceReset();


	//Wk 추가 함수. ----------------------------------------
	//LB	
	int LBBitWrite(int nAddr, BOOL bValue);
	int LBBitRead(int nAddr);

	//LB	
	int LBWrite(int nAddr, void* pValue, int nSize);
	int LBRead(int nAddr, void* pValue, int nSize);

	//LW	
	int LWWrite(int nAddr, void* pValue, int nSize);
	int LWRead(int nAddr, void* pValue, int nSize);

	//추가 함수. END----------------------------------------
};

