#include "stdafx.h"
#include "FmmLight2.h"

#define	STX							0x02
#define	ETX							0x03
#define	CR							0x0D
#define	LF							0x0A

//BDC-4LR 조명 컨트롤러 테스트 

FmmLight2    g_pLaserFocus;

FmmLight2::FmmLight2()
{
	}


FmmLight2::~FmmLight2()
{
}

UINT FmmLight2::Init(int stn, HWND hWnd,int type)
{
	// Load COM port information from configuration file.

	m_iStationNo = stn;
	m_Comm.m_hCommWnd = hWnd;
	m_Comm.m_nType = type;

	LoadConfigInfo(stn);



	if (!m_Comm.OpenPort()) {
		AfxMessageBox(_T("error"));
		return 1;
	}
	else
	{
		TRACE(_T("JFCC[%d]: %s port open successed.\n"), stn, m_Comm.m_strPort);
		///	AfxMessageBox("1234");
		return 0;
	}
}

UINT FmmLight2::SetComPort(CString strComPort, int iBaud, int iData, int iStop, int iParity)
{
	m_Comm.ClosePort();

	m_Comm.m_strPort = strComPort;
	m_Comm.m_iBaud = iBaud;
	m_Comm.m_iData = iData;
	m_Comm.m_iStop = iStop;
	m_Comm.m_iParity = iParity;

	if (!m_Comm.OpenPort()) {
		AfxMessageBox(_T("1234"));
		return 1;
	}

	return 0;
}

BOOL FmmLight2::SetLaserSend(unsigned int nCh, unsigned int nVal)
{
	if (!m_Comm.m_bConnected) {
		//	AfxMessageBox(_T("error"));
		return 1;
	}
	char	pBuf[50] = { 0, };
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);
	if (nCh == 0) sprintf(pBuf, "MEASURE%c", CR);
	//	sprintf(pBuf, "DATAGET%c",CR);
	//	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

//	Sleep(100);
	return TRUE;
}


UINT FmmLight2::SaveConfigInfo(void)
{
	CString path, section;
	// 	TCHAR	exepath[MAX_PATH];
	// 
	// 	GetModuleFileName(NULL, exepath, sizeof(exepath));
	// 	path = exepath;
	// 	int i = path.ReverseFind('\\');
	// 	path = path.Left(i);
	// 
	// 	path.Append(_T("\\Config\\Config.ini"));
	// 
	// 	CPathT<CString> tPath(path);
	// 
	// 	if(!tPath.FileExists())
	// 		NewConfigInfo();
	// 
	// 	CIniUtil * p_ini = new CIniUtil(path);
	// 
	// 	section.Format(_T("JFCC_%d"), m_iStationNo);
	// 
	// 	CString tmp;
	// 	p_ini->WriteString(section, _T("COMPORT"), m_Comm.m_strPort);
	// 	tmp.Format(_T("%d"), m_Comm.m_iBaud);
	// 	p_ini->WriteString(section, _T("BaudRate"), tmp);
	// 	tmp.Format(_T("%d"), m_Comm.m_iData);
	// 	p_ini->WriteString(section, _T("DataBit"), tmp);
	// 	tmp.Format(_T("%d"), m_Comm.m_iStop);
	// 	p_ini->WriteString(section, _T("StopBit"), tmp);
	// 	tmp.Format(_T("%d"), m_Comm.m_iParity);
	// 	p_ini->WriteString(section, _T("Parity"), tmp);
	// 
	// 	delete p_ini;

	return 0;
}

UINT FmmLight2::LoadConfigInfo(int com)
{
	 	CString path;
	// 	TCHAR	exepath[MAX_PATH];
	// 
	// 	GetModuleFileName(NULL, exepath, sizeof(exepath));
	// 	path = exepath;
	// 	int i = path.ReverseFind('\\');
	// 	path = path.Left(i);
	// 
	// 	path.Append(_T("\\Config\\Config.ini"));
	// 
	// 	CPathT<CString> tPath(path);
	// 
	// 	if(!tPath.FileExists())
	// 		NewConfigInfo();
	// 
	// 	CIniUtil * p_ini = new CIniUtil(path);
	// 
	// 	section.Format(_T("JFCC_%d"), m_iStationNo);
	path.Format(_T("\\\\.\\COM%d"), com);
	m_Comm.m_strPort = path;
	m_Comm.m_iBaud = 38400;
	m_Comm.m_iData = 8;
	m_Comm.m_iStop = 0;
	m_Comm.m_iParity = 0;



	return 0;
}

UINT FmmLight2::NewConfigInfo(void)
{
	return 0;
}

UINT FmmLight2::AnalyzeCom(void)
{
	if (!m_Comm.m_bConnected)
		return 1;

	return 0;
}

BOOL FmmLight2::SetLightBright(unsigned int nCh, unsigned int nVal)
{
	if (!m_Comm.m_bConnected) {
		//	AfxMessageBox(_T("error"));
		return 1;
	}
	char	pBuf[50] = { 0, };
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);
	sprintf(pBuf, "%c50%x%x%x%x%c", STX, nVal, nVal, nVal, nVal, ETX);
	//	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	Sleep(100);
	return TRUE;
}

// // DON'T USE
BOOL FmmLight2::SetLightOnOff(unsigned int nCh, bool bOn)
{
	if (!m_Comm.m_bConnected) {
		//	AfxMessageBox(_T("error"));
		return 1;
	}
	char	pBuf[50] = { 0, };
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);
	if (bOn)
		sprintf(pBuf, "%c%02dON%d%c", STX, nCh, 1, ETX);
	else
		sprintf(pBuf, "%c%02dON%d%c", STX, nCh, 1, ETX);
	//	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return TRUE;
}

// DON'T USE
BOOL FmmLight2::SetLightOnOff(unsigned int nCh, bool bOn, unsigned int nVal)
{
	if (!m_Comm.m_bConnected) {
		//	AfxMessageBox(_T("error"));
		return 1;
	}
	char	pBuf[50] = { 0, };
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);
	sprintf(pBuf, "%c%02dON%d%c", STX, nCh, 1, CR);
	//	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);


	return TRUE;
}


UINT FmmLight2::ReadBuffer(void)
{
	int		ret = 0;
	int		nByte;
	char	tmpBuff[4096] = { 0, };
	char	tmpNBuf[32] = { 0, };
//	m_dLaserValue = 0;
	double  dTemp = 0;

	nByte = m_Comm.m_QueueRead.GetSize();

	if (nByte < 5) return 1;				// Why Queue size is 0 ??

	strncpy(tmpBuff, (char*)m_Comm.m_QueueRead.buff, nByte);

	//	if(*(char*)(m_Comm.m_QueueRead.buff + nByte - 2) != '\r') return 2;
	//	if(*(char*)(m_Comm.m_QueueRead.buff + nByte - 1) != '\n') return 3;



	/*
	0	0	D	A	T	=	O	K	CR	LF

	-> OK
	0	0	L	E	D	=	O	K	CR	LF
	0	0	L	I	F	=	O	K	CR	LF
	0	0	T	E	M	=	O	K	CR	LF
	-> NG
	0	0	L	E	D	=	N	G	CR	LF
	0	0	L	I	F	=	N	G	CR	LF
	0	0	T	E	M	=	N	G	CR	LF

	0	0	T	C	L	=	O	K	CR	LF
	0	0	U	S	E	=	*	*	*	*	*	CR	LF
	*/


//	strncpy(tmpNBuf, tmpBuff, nByte - 1);
	dTemp = atof(tmpBuff);
	double nVal;
	
	nVal = (double)dTemp / 1000000.0;
	// 	CString csTemp;
	// 	csTemp.Format(_T("%.3f"),dTemp);
	// //	AfxMessageBox(csTemp);

	//	g_pEqp->m_motion.m_dSonyPos = dTemp;
	//	g_pEqp->m_motion.MotInfo[4].CurPos = g_pEqp->m_motion.m_dSonyPos*0.00005;
	if (nVal >= 2147)
	{
		nVal = 0;	// Error value 20170827 by sbs

		//m_dMeasureVal = nVal;
	}
	else
	{
		if (nVal > 1.75) nVal = 1.75;
		if (nVal < -1.75) nVal = -1.75;

		// = dVal;
	}
	//CString csMsg;
	//csMsg.Format(_T("레이저변위센서 =%.4f"), nVal);
	

	m_dLaserValue = nVal;

	//Log_Msg(csMsg);


	m_Comm.m_QueueRead.Clear();

	return 0;



	m_Comm.m_QueueRead.Clear();

	return 0;
}
double FmmLight2::GetDataReceive()
{
	return m_dLaserValue;
}

int FmmLight2::SetValue(int type, int val)
{
	char	pBuf[5] = { 0, };
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);

	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}

int FmmLight2::SetHome(int type, int val)
{
	char	pBuf[5] = { 0, };
	sprintf(pBuf, "H");

	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}

int FmmLight2::SetStop(int type, int val)
{
	char	pBuf[5] = { 0, };
	sprintf(pBuf, "B");

	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}

int FmmLight2::SetMove(int type, double val)
{
	char	pBuf[10] = { 0, };
	sprintf(pBuf, "G%d%c", (int)val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}

int FmmLight2::GetPos()
{
	char	pBuf[5] = { 0, };
	sprintf(pBuf, "G%c", CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}