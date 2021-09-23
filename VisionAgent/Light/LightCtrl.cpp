// LightCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "../MaskInspection.h"
#include "LightCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLightCtrl*		g_pLVSup = NULL;
CLightCtrl*		g_pLVSdown = NULL;
CLightCtrl*		g_pLvncnt2 = NULL;
CLightCtrl*     g_pFokLight = NULL;
/*CLightCtrl*     g_pSonyAf=NULL;*/


/////////////////////////////////////////////////////////////////////////////
// CLightCtrl
CLightCtrl::CLightCtrl()
{
	m_nCommDelay = 5;	
	m_Fok = FALSE;
}

CLightCtrl::~CLightCtrl()
{
}
/////////////////////////////////////////////////////////////////////////////
// CLightCtrl message handlers
int CLightCtrl::ConfigPort()
{
	COMMTIMEOUTS stcrCommTimeOuts;
	DCB stcrDCB;

	if(!SetupComm(m_hPort, 2046, 2046)) return	(m_nLastError = PORT_CONFIGURE_ERROR);
	if(!PurgeComm(m_hPort, PURGE_TXCLEAR | PURGE_RXCLEAR)) {
		return	(m_nLastError = PORT_CONFIGURE_ERROR);
	}

	stcrCommTimeOuts.ReadIntervalTimeout = MAXDWORD;	//20;
	stcrCommTimeOuts.ReadTotalTimeoutMultiplier = 0;	//10;
	stcrCommTimeOuts.ReadTotalTimeoutConstant = 0;		//100;
	stcrCommTimeOuts.WriteTotalTimeoutMultiplier= 0;	//10;
	stcrCommTimeOuts.WriteTotalTimeoutConstant = 20;

	if(!SetCommTimeouts(m_hPort, &stcrCommTimeOuts)) 
		return	(m_nLastError = PORT_CONFIGURE_ERROR);
	
	FillMemory(&stcrDCB, sizeof(stcrDCB), 0);

	if(!GetCommState(m_hPort, &stcrDCB)) {
		return	(m_nLastError = PORT_CONFIGURE_ERROR);
	}


	if(m_Fok) {
	
		stcrDCB.DCBlength = sizeof(DCB);
		stcrDCB.BaudRate =	CBR_4800;
		stcrDCB.ByteSize =	8;
		stcrDCB.Parity	=	NOPARITY;
		stcrDCB.StopBits =	ONESTOPBIT;

	//	AfxMessageBox("fok");


	}else {
		stcrDCB.DCBlength = sizeof(DCB);
		stcrDCB.BaudRate =	CBR_9600;
		stcrDCB.ByteSize =	8;
		stcrDCB.Parity	=	NOPARITY;
		stcrDCB.StopBits =	ONESTOPBIT;

	}

	if(!SetCommState(m_hPort, &stcrDCB)) {
		return	(m_nLastError = PORT_CONFIGURE_ERROR);
	}

	return m_nLastError;
}

BOOL CLightCtrl::InitLightCtrl()
{
	// 초기화 
	return TRUE;
}

BOOL CLightCtrl::CheckLightCtrl()
{
	return TRUE;
}

void CLightCtrl::LightCtrl(int nChanel, int nValue)
{
	CString csSendData = _T("");

	if (!m_nLastError ==PORT_OK) return;

	if (nChanel ==4 ) {
		
		csSendData.Format("cRDC%d%C",nValue,CR);    // 조도 Setting 완료..

	}else if(nChanel==5) {
		csSendData.Format("%d%C",nValue,CR);    // 현미경 조명

	}else {

		csSendData.Format(":1W%d%03d%C%C",nChanel+11,nValue,CR,LF);    // 조도 Setting 완료..

	}
//	csSendData.Format("setbrightness 0 %d%c",nValue,0x0D);	

	WritePort(csSendData);	
	Sleep(m_nCommDelay);
}

void CLightCtrl::FokSend(int nValue)
{

	CString csSendData = _T("");
    csSendData.Format("%c",nValue);    // 조도 Setting 완료..
	WritePort(csSendData);	
	Sleep(m_nCommDelay);
}

void CLightCtrl::FokOn()
{
   BOOL ret;
   ret = EscapeCommFunction(m_hPort,CLRDTR);
   if (ret== TRUE){
//	   AfxMessageBox("CLEAR");
	   TRACE("CLEAR DTR SUCCESS");
   }
}

void CLightCtrl::FokOff()
{

	BOOL ret;
	ret = EscapeCommFunction(m_hPort,SETDTR);
	if (ret== TRUE){
		TRACE("SET DTR SUCCESS");
	}
}


void CLightCtrl::LightCtrlOFF()
{
	CString csSendData = _T("");

	if (!m_nLastError ==PORT_OK) return;


		csSendData.Format(":1W11000,000,000,000%C%C",CR,LF);    // 조도 Setting 완료..

	
	//	csSendData.Format("setbrightness 0 %d%c",nValue,0x0D);	

	WritePort(csSendData);	
	Sleep(m_nCommDelay);
}

void CLightCtrl::ReturnValue(int nIndex)
{

}


void CLightCtrl::LaserON()
{

	CString csSendData = _T("");
	 csSendData.Format("A1");    // 조도 Setting 완료..
	WritePort(csSendData);	
	Sleep(m_nCommDelay);
}

void CLightCtrl::LaserOff()
{

	CString csSendData = _T("");
	csSendData.Format("A0");    
	WritePort(csSendData);	
	Sleep(m_nCommDelay);
}
void CLightCtrl::SonyAFSTOP()
{

	CString csSendData = _T("");
	csSendData.Format("B");    // 조도 Setting 완료..
	WritePort(csSendData);	
	Sleep(m_nCommDelay);

}
void CLightCtrl::SonyAfMove(int nDirection,int Pos)
{
	CString csSendData = _T("");
	if (nDirection==0)  csSendData.Format("D%d%c",Pos,CR);    // 조도 Setting 완료..
	else csSendData.Format("U%d%c",Pos,CR);  
	// 조도 Setting 완료..
	WritePort(csSendData);	
	Sleep(m_nCommDelay);
}

void CLightCtrl::SonyAutoFocus()
{
	CString csSendData = _T("");
	csSendData.Format("@G");   
	WritePort(csSendData);	
	Sleep(m_nCommDelay);
}

void CLightCtrl::SonyAFHome()
{
// 	CString csSendData = _T("");
// 	csSendData.Format("H");   
// 	WritePort(csSendData);	
// 	Sleep(m_nCommDelay);
 }