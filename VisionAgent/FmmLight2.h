#pragma once
#include "Light/CommThread.h"

class FmmLight2
{
public:
	FmmLight2();
	~FmmLight2();

	UINT Init(int stn, HWND hWnd, int type);
	UINT AnalyzeCom(void);
	UINT ReadBuffer(void);
	UINT SetComPort(CString strComPort, int iBaud, int iData, int iStop, int iParity);
	UINT SaveConfigInfo(void);

public:
	CCommThread		m_Comm;
	BOOL			isInitialised;

	double m_dLaserValue;

	double GetDataReceive();

private:
	UINT LoadConfigInfo(int com);
	UINT NewConfigInfo(void);

	int				m_iStationNo;

public:
	BOOL	SetLightBright(unsigned int nCh, unsigned int nVal);		// Light Data º¯°æ
	BOOL	SetLightOnOff(unsigned int nCh, bool bOn);					// Light On/Off
	BOOL	SetLightOnOff(unsigned int nCh, bool bOn, unsigned int nVal);
	BOOL	SetLaserSend(unsigned int nCh, unsigned int nVal);
	int SetValue(int type, int val);
	int SetMove(int type, double val);
	int SetHome(int type, int val);
	int SetStop(int type, int val);
	int GetPos();
};


extern FmmLight2    g_pLaserFocus;


