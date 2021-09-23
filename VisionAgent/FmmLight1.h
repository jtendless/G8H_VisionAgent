#pragma once
#include "Light/CommThread.h"


class FmmLight1
{
public:
	FmmLight1();
	~FmmLight1();

	UINT Init(int stn, HWND hWnd, int type);
	UINT Init_BackLight(int stn, HWND hWnd, int type);
	UINT AnalyzeCom(void);
	UINT ReadBuffer(void);
	//21.04.09 sjc
	UINT ReadBuffer(char* pbuf);
	UINT ReadAOILaserSensorBuff(CString Str);
	//
	UINT SetComPort(CString strComPort, int iBaud, int iData, int iStop, int iParity);
	UINT SaveConfigInfo(void);

public:
	CCommThread		m_Comm;
	BOOL			isInitialised;
	int					m_nCh;

private:
	UINT LoadConfigInfo(int com);
	UINT LoadConfigInfo_BackLight(int com);
	UINT NewConfigInfo(void);

	int				m_iStationNo;

public:

	BOOL	SetLightBright(unsigned int nCh, unsigned int nVal);		// Light Data 변경
	BOOL	SetLightOnOff(unsigned int nCh, bool bOn);					// Light On/Off
	BOOL	SetLightOnOff(unsigned int nCh, bool bOn, unsigned int nVal);
	BOOL	SetLaserSend(unsigned int nCh, unsigned int nVal);
	BOOL	SetTempSend(unsigned int nCh, unsigned int nVal);		// Light Data 변경
	int _httoi(const TCHAR *value);

	int SetValue(int type, int val);
	int SetValueBackLight(int nChStart, int nChEnd, int val);
	int SetMove(int type, double val);
	int SetHome(int type, int val);
	int SetStop(int type, int val);
	int GetPos();
#if 0
	int SetAignLightLeft(int CoAxial, int Ring);
	int SetAignLightRight(int CoAxial, int Ring);
	int SetReviewLight(int CoAxial, int Ring);
	int SetReviewLightLeft(int CoAxial, int Ring[8]);
	int SetReviewLightLeft(int CoAxial, int Ring);
	int SetReviewLightRight(int CoAxial, int Ring);
	int SetBackLightLeft(int val);
	int SetBackLightRight(int val);
#endif
	int SetLight_Review_Coaxial(int CoAxial);
	int SetLight_Review_Ring(int Ring);
	int SetLight_PreAlign(int CoAxial, int Ring);
	int SetLight_BoxAlignL(int CoAxial, int Ring);
	int SetLight_BoxAlignR(int CoAxial, int Ring);
	int SetBackLight(int nCh, int val);
	int SetAoiLight(int nCh, int val);
	int BackLightOn(int nVal[BACKLIGHT_CH_COUNT]);//7ch all use
	int BackLightOff();
	int AoiLightOn();
	int AoiLightOff();
	//21.02.16 sjc
	int SetLight_Review(int Ring, int CoAxial);//1~8 ring 12 = CoAxial
	int SetLight_Left_Loader(int Ring, int CoAxial);//Ring 1,2(L,R) Coaxial 5,6(L,R)
	int SetLight_Right_Loader(int Ring, int CoAxial);//Ring 1,2(L,R) Coaxial 5,6(L,R)
	//21.02.22 sjc
	int SetLight_Zoom_Ring(int Ring);
	int SetLight_Zoom_Coaxial(int Coaxial);
	int Zoom_Light_On(BOOL On);//On = 1, Off = 0;

	//21.04.09 sjc esc
	int Esc_Send_Msg(CString str);
	int AOI_Send_Msg(CString str);

	int AOI_Meas_Print(int headNum);
	int AOI_Timing_ON_OFF(int headNum, BOOL ON);
	int AOI_Auto_Zero_ON_OFF(int headNum, BOOL ON);
	int AOI_Reset(int headNum);
	int AOI_Program_Change(int programNum);
	int AOI_Program_Check();
	//

	double m_dTempValue[12];

};

//extern FmmLight1     g_CommLight_8ch;
//extern FmmLight1     g_CommLight_12ch;
//extern FmmLight1     g_CommMLCLedLight;  //BackLight, AOI Light
extern FmmLight1     g_CommTempTur;
//21.02.16 sjc
extern FmmLight1		g_CommReview_Light;
//extern FmmLight1		g_CommLoader_Light;
//extern FmmLight1		g_CommBack_Light;
//21.02.22 sjc
//extern FmmLight1	g_CommZomm_Ring;
//extern FmmLight1	g_CommZomm_Coaxial;

//21.04.03 sjc aoi laser
//extern FmmLight1	g_CommAOILaser;
//21.04.09 sjc 
//extern FmmLight1	g_CommESC;