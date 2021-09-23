#if !defined(AFX_LIGHTCTRL_H__43DF822C_6E8D_460C_931E_C8E9C13E7749__INCLUDED_)
#define AFX_LIGHTCTRL_H__43DF822C_6E8D_460C_931E_C8E9C13E7749__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SerialComm.h"



/////////////////////////////////////////////////////////////////////////////
// CLightCtrl window
class CLightCtrl : public CSerialComm
{
private:
	int m_nCommDelay;

public:
	CLightCtrl();
	virtual ~CLightCtrl();

	BOOL m_bNicon;

	BOOL m_Fok;

	BOOL InitLightCtrl();
	int  ConfigPort();
	BOOL CheckLightCtrl();
	void LightCtrl(int nChanel, int nValue);
	void ReturnValue(int nIndex);
	void LightCtrlOFF();
	void FokSend(int nValue);
	void FokOn();
	void FokOff();

	void SonyAutoFocus();
	void LaserON();
	void LaserOff();
	void SonyAFSTOP();
	void SonyAfMove(int nDirection,int Pos);
	void SonyAFHome();
	
	//{{AFX_VIRTUAL(CLightCtrl)
	//}}AFX_VIRTUAL
};

extern CLightCtrl*		g_pLVSup;
extern CLightCtrl*		g_pLVSdown;
extern CLightCtrl*		g_pLvncnt2;
extern CLightCtrl*		g_pFokLight;
/*extern CLightCtrl*		g_pSonyAf;*/


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTCTRL_H__43DF822C_6E8D_460C_931E_C8E9C13E7749__INCLUDED_)
