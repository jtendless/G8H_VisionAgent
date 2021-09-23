#include "stdafx.h"
#include "FmmLight1.h"

#define	STX							0x02
#define	ETX							0x03
#define	CR							0x0D
#define	LF							0x0A

//FmmLight1     g_CommLight_8ch;
//FmmLight1     g_CommLight_12ch;
//FmmLight1     g_CommMLCLedLight; //BackLight, AOI Light
FmmLight1     g_CommTempTur;
//21.02.16 sjc
FmmLight1		g_CommReview_Light;
//FmmLight1		g_CommLoader_Light;
//FmmLight1		g_CommBack_Light;
//FmmLight1		g_CommZomm_Ring;	//PreAlign Cam Light
//FmmLight1		g_CommZomm_Coaxial; //PreAlign Cam Light
//21.04.03 sjc aoi laser
//FmmLight1		g_CommAOILaser;
//21.04.09 sjc ESC
//FmmLight1		g_CommESC;

FmmLight1::FmmLight1()
{
	for (int i = 0; i < 9; i++) {
		m_dTempValue[i] = 0.0;
	}

}

FmmLight1::~FmmLight1()
{
}

UINT FmmLight1::Init(int stn, HWND hWnd, int type)
{
	// Load COM port information from configuration file.
	m_Comm.m_hCommWnd = hWnd;
	m_Comm.m_nType = type;
	m_nCh = 1;
	LoadConfigInfo(stn);//baud rate setting
#ifndef SIM_MODE
	if (!m_Comm.OpenPort()) { //port open
		AfxMessageBox(_T("error"));
		return 1;
	}
	else
	{
		TRACE(_T("JFCC[%d]: %s port open successed.\n"), stn, m_Comm.m_strPort);
		return 0;
	}
#else
	return 0;
#endif
}

UINT FmmLight1::Init_BackLight(int stn, HWND hWnd, int type)
{
	// Load COM port information from configuration file.
	m_Comm.m_hCommWnd = hWnd;
	m_Comm.m_nType = type;
	m_nCh = 1;
	LoadConfigInfo_BackLight(stn);
#ifndef SIM_MODE
	if (!m_Comm.OpenPort()) {
		AfxMessageBox(_T("error"));
		return 1;
	}
	else
	{
		TRACE(_T("JFCC[%d]: %s port open successed.\n"), stn, m_Comm.m_strPort);
		return 0;
	}
#else
	return 0;
#endif
}

UINT FmmLight1::SetComPort(CString strComPort, int iBaud, int iData, int iStop, int iParity)
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

UINT FmmLight1::SaveConfigInfo(void)
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

UINT FmmLight1::LoadConfigInfo(int com)
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

	m_Comm.m_iData = 8;
	m_Comm.m_iStop = 0;
	//m_Comm.m_iStop = 1;
	m_Comm.m_iParity = 0;


	//21.02.22 sjc
	if (com == COM_PORT_ZOOM_COAXIAL || com == COM_PORT_ZOOM_RING)
	{
		m_Comm.m_iBaud = 9600;
	}
	//21.04.03 sjc aoi laser
	else if (com == COM_PORT_AOI_LASER_FOCUS)
	{
		m_Comm.m_iBaud = 9600;	
	}
	//21.04.09 sjc
	else if (com == COM_PORT_ESC)
	{
		m_Comm.m_iBaud = 9600;
		//m_Comm.m_iStop = 2;
	}
	else
	{
		m_Comm.m_iBaud = 19200;
	}
	
	  //m_Comm.m_iBaud = 19200;
//	m_Comm.m_iBaud = 38400;


	return 0;
}
UINT FmmLight1::LoadConfigInfo_BackLight(int com)
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
	m_Comm.m_iBaud = 19200;   //m_Comm.m_iBaud = 19200;
//	m_Comm.m_iBaud = 38400;
	m_Comm.m_iData = 8;
	m_Comm.m_iStop = 1;
	m_Comm.m_iParity = 0;

	return 0;
}

UINT FmmLight1::NewConfigInfo(void)
{
	return 0;
}

UINT FmmLight1::AnalyzeCom(void)
{
	if (!m_Comm.m_bConnected)
		return 1;

	return 0;
}

UINT FmmLight1::ReadBuffer(void)
{
	int		ret = 0;
	int		nByte;
	char	tmpBuff[4096] = { 0, };
	char	tmpNBuf[1000] = { 0, };
	int nIndex = 0;

	CString  tmpcsBuff;
	CString tmp;
	int  nTemp[9] = { 0, };

	nByte = m_Comm.m_QueueRead.GetSize();

	//if (nByte < 57) return 1;				// Why Queue size is 0 ??
	if (nByte < 200) return 1;				// Why Queue size is 0 ??

	strncpy(tmpBuff, (char*)m_Comm.m_QueueRead.buff, nByte);

	tmpcsBuff = tmpBuff;
	nIndex = tmpcsBuff.Find(_T(",OK"));
	//	if (nIndex < 0) return 1;				// Why Queue size is 0 ??

	// 일단 OK 값 확인 후 자리수 맞게 4개 읽어와서 16진수 값을 9개씩  읽어와서 9개 배열에 넣어준다.
	// 헉....  1시간 삽질했다..
	//tmp = tmpcsBuff.Mid(nIndex + 4, 4);
	tmp = tmpcsBuff.Mid(1, 4);

	//21.03.02 SJC / 100. -> /10. (because Hansong Jeon Jin Hwan B)
	
	tmp = tmpcsBuff.Mid(nIndex + 4, 4);
	m_dTempValue[0] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 9, 4);
	m_dTempValue[1] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 14, 4);
	m_dTempValue[2] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 19, 4);
	m_dTempValue[3] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 24, 4);
	m_dTempValue[4] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 29, 4);
	m_dTempValue[5] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 34, 4);
	m_dTempValue[6] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 39, 4);
	m_dTempValue[7] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 44, 4);
	m_dTempValue[8] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 49, 4);
	m_dTempValue[9] = _httoi(tmp) / 100.;
	
	//Awking Data 확인 필요.
	tmp = tmpcsBuff.Mid(nIndex + 54, 4);
	m_dTempValue[10] = _httoi(tmp) / 100.;

	tmp = tmpcsBuff.Mid(nIndex + 59, 4);
	m_dTempValue[11] = _httoi(tmp) / 100.;
	


	//_httoi(tmp)

	//CString csTemp;
	//csTemp.Format(_T("1= %.2f,2=%.2f,3=%.2f,4=%.2f,5=%.2f,6=%.2f,7=%.2f,8=%.2f,9=%.2f"), m_dTempValue[0], m_dTempValue[1], m_dTempValue[2], m_dTempValue[3], m_dTempValue[4], m_dTempValue[5], m_dTempValue[6], m_dTempValue[7], m_dTempValue[8]);
	//Log_Msg(csTemp);	// 20170821 by sbs 
	//	AfxMessageBox(csTemp);

	//	g_pEqp->m_motion.m_dSonyPos = dTemp;
	//	g_pEqp->m_motion.MotInfo[4].CurPos = g_pEqp->m_motion.m_dSonyPos*0.00005;

	m_Comm.m_QueueRead.Clear();
	return 0;


}

UINT FmmLight1::ReadBuffer(char* pbuf)
{
	int		ret = 0;
	int		nByte;
	char	tmpBuff[4096] = { 0, };
	char	tmpNBuf[1000] = { 0, };
	int nIndex = 0;

	CString  tmpcsBuff;
	CString tmp;
	int  nTemp[9] = { 0, };

	nByte = m_Comm.m_QueueRead.GetSize();

	//if (nByte < 57) return 1;				// Why Queue size is 0 ??
	if (nByte < 1) return 1;				// Why Queue size is 0 ??
	memset(pbuf, 0, 1000);
	strncpy(tmpBuff, (char*)m_Comm.m_QueueRead.buff, nByte);
	strncpy(pbuf, (char*)m_Comm.m_QueueRead.buff, nByte);

	tmpcsBuff = tmpBuff;
	m_Comm.m_QueueRead.Clear();
	return 0;
}

UINT FmmLight1::ReadAOILaserSensorBuff(CString Str)
{
	int		ret = 0;
	int		nByte;
	char	tmpBuff[4096] = { 0, };
	char	tmpNBuf[1000] = { 0, };
	int nIndex = 0;
	CVisionAgentDlg *pDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	CString  tmpcsBuff;
	CString tmp;
	int  nTemp[9] = { 0, };

	nByte = m_Comm.m_QueueRead.GetSize();

	//if (nByte < 57) return 1;				// Why Queue size is 0 ??
	if (nByte < 1) return 1;				// Why Queue size is 0 ??

	strncpy(tmpBuff, (char*)m_Comm.m_QueueRead.buff, nByte);

	
	Str = tmpcsBuff = tmpBuff;
	if (tmpBuff[0] == 'M')//MEAS OUT
	{
		if (tmpBuff[1] == '0')//head 1,2
		{
			Str=tmpcsBuff.Mid(3, 8);
			pDlg->m_AOILaserValue[0]=_ttof(Str);
			Str = tmpcsBuff.Mid(12, 8);
			pDlg->m_AOILaserValue[1] = _ttof(Str);
		}
		else if(tmpBuff[1] == '1')//head 1(one)
		{
			Str = tmpcsBuff.Mid(3, 8);
			pDlg->m_AOILaserValue[0] = _ttof(Str);
		}
		else if (tmpBuff[1] == '2')// head 2 (one)
		{
			Str = tmpcsBuff.Mid(3, 8);
			pDlg->m_AOILaserValue[1] = _ttof(Str);
		}
	}
	else if (tmpBuff[0] == 'T')//TIMING ON/OFF
	{
		if (tmpBuff[1] == '0')
		{
			Total_Msg(_T("AOI Sensor Timing Off"));
		}
		else
		{
			Total_Msg(_T("AOI Sensor Timing On"));
		}
	}
	else if (tmpBuff[0] == 'V')
	{
		if (tmpBuff[1] == 'R')//VR reset ok
		{
			Total_Msg(_T("AOI Sensor Reset"));
		}
		else//auto Zero on
		{
			Total_Msg(_T("AOI Sensor Auto Zero On"));
		}
	}
	else if (tmpBuff[0] == 'W')//auto timing off
	{
		Total_Msg(_T("AOI Sensor Auto Zero Off"));
	}
	else if (tmpBuff[0] == 'K')//panel lock
	{
		Total_Msg(_T("AOI Sensor Panel Lock/Unlock"));
	}
	else if (tmpBuff[0] == 'P')
	{
		if (tmpBuff[1] == 'W')//program change
		{
			Total_Msg(_T("AOI Sensor Program change"));
		}
		else if (tmpBuff[1] == 'R')//program check
		{
			tmp.Format(_T("AOI Sensor Program %c Check"),tmpBuff[3]);
			Total_Msg(tmp);
		}
	}
	//else if (tmpBuff[0] == 'D')
	//{
	//	if (tmpBuff[1] == 'O')//data print
	//	{

	//	}
	//	else if (tmpBuff[1] == 'Q')//data clear
	//	{

	//	}
	//}
	//else if (tmpBuff[0] == 'A')
	//{
	//	if (tmpBuff[1] == 'S')//data storage start
	//	{

	//	}
	//	else if (tmpBuff[1] == 'P')//data storage Stop
	//	{

	//	}
	//	if (tmpBuff[1] == 'Q')//data storage reset
	//	{

	//	}
	//	else if (tmpBuff[1] == 'P')//data storage data print
	//	{

	//	}
	//}

	m_Comm.m_QueueRead.Clear();
	return 0;
}

BOOL FmmLight1::SetTempSend(unsigned int nCh, unsigned int nVal)
{
	if (!m_Comm.m_bConnected) {
		//	AfxMessageBox(_T("error"));
		return 1;
	}
	unsigned char csum;
	char	pBuf[100] = { 0, };
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);
	if (m_nCh == 1)
		m_nCh = 2;
	else
		m_nCh = 1;
	
		sprintf(pBuf, "%c01RSD,12,0001C6%c%c", STX, CR, LF);

	UINT ntemp = strlen(pBuf);
	//	csum = CalcChecksum(pBuf, ntemp);

	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	Sleep(100);



	return TRUE;
}

int FmmLight1::_httoi(const TCHAR *value)
{
	struct CHexMap
	{
		TCHAR chr;
		int value;
	};
	const int HexMapL = 16;
	CHexMap HexMap[HexMapL] =
	{
		{ '0', 0 }, { '1', 1 },
		{ '2', 2 }, { '3', 3 },
		{ '4', 4 }, { '5', 5 },
		{ '6', 6 }, { '7', 7 },
		{ '8', 8 }, { '9', 9 },
		{ 'A', 10 }, { 'B', 11 },
		{ 'C', 12 }, { 'D', 13 },
		{ 'E', 14 }, { 'F', 15 }
	};
	TCHAR *mstr = _tcsupr(_tcsdup(value));
	TCHAR *s = mstr;
	int result = 0;
	if (*s == '0' && *(s + 1) == 'X') s += 2;
	bool firsttime = true;
	while (*s != '\0')
	{
		bool found = false;
		for (int i = 0; i < HexMapL; i++)
		{
			if (*s == HexMap[i].chr)
			{
				if (!firsttime) result <<= 4;
				result |= HexMap[i].value;
				found = true;
				break;
			}
		}
		if (!found) break;
		s++;
		firsttime = false;
	}
	free(mstr);
	return result;
}

// 채널 Data 변경
BOOL FmmLight1::SetLightBright(unsigned int nCh, unsigned int nVal)
{
	if (!m_Comm.m_bConnected) {
	//	AfxMessageBox(_T("error"));
		return 1;
	}
	char	pBuf[50] = { 0, };
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);
	sprintf(pBuf, "%c%02dWR%03d%c", STX, nCh, nVal, ETX);
	//	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	Sleep(100);
	return TRUE;
}

BOOL FmmLight1::SetLaserSend(unsigned int nCh, unsigned int nVal)
{
	if (!m_Comm.m_bConnected) {
		//	AfxMessageBox(_T("error"));
		return 1;
	}
	char	pBuf[50] = { 0, };
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);
	if (nCh == 0) sprintf(pBuf, "MEASURE%c",CR);
//	sprintf(pBuf, "DATAGET%c",CR);
	//	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	Sleep(100);
	return TRUE;
}

// 채널 On/Off
	BOOL FmmLight1::SetLightOnOff(unsigned int nCh, bool bOn)
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

// 채널 On/Off
	BOOL FmmLight1::SetLightOnOff(unsigned int nCh, bool bOn, unsigned int nVal)
{
		if (!m_Comm.m_bConnected) {
		//	AfxMessageBox(_T("error"));
			return 1;
		}
		char	pBuf[50] = { 0, };
		//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

		//	else sprintf(pBuf, "U%d%c", val, CR);
		sprintf(pBuf, "%c%02dWR%03d%c", STX, nCh, nVal, ETX);
		//	sprintf(pBuf, "%d%c", val, CR);
		UINT ntemp = strlen(pBuf);
		DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);


	return TRUE;
}

int FmmLight1::SetValue(int type, int val)
{
#ifdef SIM_MODE
	return 1;
#endif

	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("Light Connect Error !!"));
		return 1;
	}
	char	pBuf[15] = { 0, }; //50
//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

//	else sprintf(pBuf, "U%d%c", val, CR);
	sprintf(pBuf, "%c%02dWR%03d%c", STX, type+1, val, ETX);
//	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);
	Sleep(20); //!!

	return 0;
}
int FmmLight1::SetValueBackLight(int nChStart, int nChEnd, int val)
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("Light Connect Error !!"));
		return 1;
	}
	char	pBuf[10] = { 0, }; //50
	//	if (type == 0) sprintf(pBuf, "D%d%c", val, CR);

	//	else sprintf(pBuf, "U%d%c", val, CR);
	//sprintf(pBuf, "%c%02dWR%03d%c", STX, type + 1, val, ETX);
	sprintf(pBuf, "WC02N%c", CR);
	//	sprintf(pBuf, "%d%c", val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}

#if 0
int  FmmLight1::SetAignLightLeft(int CoAxial, int Ring)
{
	// ALIGN // 
	SetValue(0, Ring);
	Sleep(30);
	SetValue(4, CoAxial);
	return 0;
}
int  FmmLight1::SetAignLightRight(int CoAxial, int Ring)
{

	SetValue(1, Ring);
	Sleep(30);
	SetValue(5, CoAxial);

	return 0;
}
int  FmmLight1::SetReviewLight(int CoAxial, int Ring)
{
	// REVIEW 링 8채널
	for (int i = 0; i < 8; i++) {
		SetValue(i, Ring);
		Sleep(30);
	}
	// REVIEW 동축 1채널
	SetValue(8, CoAxial);

	return 0;
}
int  FmmLight1::SetReviewLightLeft(int CoAxial, int Ring[8])
{
	// REVIEW 링 8채널
	SetValue(0, Ring[0]);
	SetValue(1, Ring[1]);
	SetValue(2, Ring[2]);
	SetValue(3, Ring[3]);
	SetValue(4, Ring[4]);
	SetValue(5, Ring[5]);
	SetValue(6, Ring[6]);
	SetValue(7, Ring[7]);
	// REVIEW 동축 1채널
	SetValue(9, CoAxial);

	return 0;
}

int  FmmLight1::SetReviewLightLeft(int CoAxial, int Ring)
{
	// REVIEW 링 8채널
	SetValue(0, Ring);
	SetValue(1, Ring);
	SetValue(2, Ring);
	SetValue(3, Ring);
	SetValue(4, Ring);
	SetValue(5, Ring);
	SetValue(6, Ring);
	SetValue(7, Ring);
	// REVIEW 동축 1채널
	SetValue(8, CoAxial);

	return 0;
}

int  FmmLight1::SetReviewLightRight(int CoAxial, int Ring)
{
	// REVIEW 링 8채널
	SetValue(9, Ring);	
	// REVIEW 동축 1채널
	SetValue(10, CoAxial);

	return 0;
}
int  FmmLight1::SetBackLightLeft(int val)
{
	// BackLIght 4채널
	for (int i = 0; i < 2; i++) {
		SetValue(i, val);
		Sleep(30);
	}
	return 0;
}
int  FmmLight1::SetBackLightRight(int val)
{
	// BackLIght 4채널
	for (int i = 2; i < 4; i++) {
		SetValue(i, val);
		Sleep(30);
	}
	return 0;
}
#endif

int FmmLight1::SetLight_Review_Coaxial(int CoAxial)
{
	CString Str = _T("");
	SetValue(eLIGHT_8CH_REVIEW_COAXIAL, CoAxial);

	Str.Format(_T("SetLight_Review Coaxial:%d"), CoAxial);
	Total_Msg(Str);

	return 0;
}
int FmmLight1::SetLight_Review_Ring(int Ring)
{
	CString Str = _T("");

	SetValue(eLIGHT_12CH_REVIEW_RING_1, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_12CH_REVIEW_RING_2, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_12CH_REVIEW_RING_3, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_12CH_REVIEW_RING_4, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_12CH_REVIEW_RING_5, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_12CH_REVIEW_RING_6, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_12CH_REVIEW_RING_7, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_12CH_REVIEW_RING_8, Ring);

	Str.Format(_T("SetLight_Review_Ring 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d"), Ring, Ring, Ring, Ring, Ring, Ring, Ring, Ring);
	Total_Msg(Str);

	return 0;
}
int FmmLight1::SetLight_PreAlign(int CoAxial, int Ring)
{
	CString Str = _T("");

	//SetValue(eLIGHT_8CH_PREALIGN_REVIEW_RING, Ring);
	//Sleep(20); //!!
	//SetValue(eLIGHT_8CH_PREALIGN_COAXIAL, CoAxial);

	//Str.Format(_T("SetLight_PreAlign Coaxial:%d, Ring:%d"), CoAxial, Ring);
	//Total_Msg(Str);

	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("PreAlign, Loader Light Connect Error !!"));
		return 1;
	}
	char	pBuf[15] = { 0, }; //50
	//Setting ring  //Ring 1,2(L,R) Coaxial 5,6(L,R)
	sprintf(pBuf, "%c%02dWR%03d%c", STX, 1, Ring, ETX);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);
	Sleep(20); //!!

	//Setting CoAxial //Ring 1,2(L,R) Coaxial 5,6(L,R)
	sprintf(pBuf, "%c%02dWR%03d%c", STX, 5, CoAxial, ETX);
	ntemp = strlen(pBuf);
	ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	Str.Format(_T("Set PreAlgin Light Ring : %d, Coaxial : %d"), Ring, CoAxial);
	Total_Msg(Str);

	return 0;
}
int FmmLight1::SetLight_BoxAlignL(int CoAxial, int Ring)
{
	CString Str = _T("");

	SetValue(eLIGHT_8CH_BOX_ALIGN_L_RING, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_8CH_BOX_ALIGN_L_COAXIAL, CoAxial);

	Str.Format(_T("SetLight_BoxAlignL Coaxial:%d, Ring:%d"), CoAxial, Ring);
	Total_Msg(Str);

	return 0;
}
int FmmLight1::SetLight_BoxAlignR(int CoAxial, int Ring)
{
	CString Str = _T("");

	SetValue(eLIGHT_8CH_BOX_ALIGN_R_RIGN, Ring);
	Sleep(20); //!!
	SetValue(eLIGHT_8CH_BOX_ALIGN_R_COALIAL, CoAxial);

	Str.Format(_T("SetLight_BoxAlignR Coaxial:%d, Ring:%d"), CoAxial, Ring);
	Total_Msg(Str);

	return 0;
}

int  FmmLight1::SetBackLight(int nCh, int val)
{ 
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("BackLight Connected Error !!"));
		return 1;
	}
	//21.02.16 sjc del
	//nCh += eBACKLIGHT_CH1;

	char	pBuf[50] = { 0, };
	//21.02.16 sjc
	sprintf(pBuf, "%c%02dWR%03d%c", STX, nCh, val, ETX); //ch 1~7 use
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}
int FmmLight1::BackLightOn(int nVal[BACKLIGHT_CH_COUNT])
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("BackLight Connected Error !!"));
		return 1;
	}

	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	{
		SetBackLight(i+1, nVal[i]);
		Sleep(20); //!!
	}

	char	pBuf4[10] = { 0, }; //50
	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)//ch 1~7
	{
		//21.02.16 sjc
		sprintf(pBuf4, "%c%02dON%c", STX, 1 + i, TRUE, ETX);
		//sprintf(pBuf4, "WC%02dN%c", 1 + i, CR);
		UINT ntemp = strlen(pBuf4);
		DWORD ret = m_Comm.WriteComm((BYTE*)pBuf4, (DWORD)ntemp);
		Sleep(30); //!!
	}

	return 0;
}
int FmmLight1::BackLightOff()
{
#ifdef SIM_MODE
	return 1;
#endif

	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("BackLight Connected Error !!"));
		return 1;
	}

	//sprintf(pBuf, "WC99D%c", CR); //All Off	

	char	pBuf4[10] = { 0, }; //50
	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	{
		SetBackLight(i + 1, BACKLIGHT_OFF_VALUE);
		Sleep(20); //!!
	}

	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	{
		sprintf(pBuf4, "%c%02dON%c", STX, 1 + i, FALSE, ETX);
		UINT ntemp = strlen(pBuf4);
		DWORD ret = m_Comm.WriteComm((BYTE*)pBuf4, (DWORD)ntemp);
		Sleep(20); //!!
	}

	return 0;
}
int  FmmLight1::SetAoiLight(int nCh, int val)
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("AOI Light Connected Error !!"));
		return 1;
	}

	nCh += eAOI_LIGHT_CH1;

	char	pBuf[50] = { 0, };
	sprintf(pBuf, "WD%02d%04d%c", nCh, val, CR); //ch 12~20 Set Value
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);
	Sleep(20); //!!

	return 0;
}
int FmmLight1::AoiLightOn()
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("AOI Light Connected Error !!"));
		return 1;
	}

	//sprintf(pBuf, "WC99D%c", CR); //All Off	

	char	pBuf4[10] = { 0, }; //50
	for (int i = 0; i < AOI_LIGHT_CH_COUNT; i++)
	{
		sprintf(pBuf4, "WC%02dN%c", eAOI_LIGHT_CH1 + i, CR);
		UINT ntemp = strlen(pBuf4);
		DWORD ret = m_Comm.WriteComm((BYTE*)pBuf4, (DWORD)ntemp);
		Sleep(20); //!!
	}

	return 0;
}
int FmmLight1::AoiLightOff()
{
#ifdef SIM_MODE
	return 1;
#endif

	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("AOI Light Connected Error !!"));
		return 1;
	}

	//sprintf(pBuf, "WC99D%c", CR); //All Off	

	char	pBuf4[10] = { 0, }; 
	for (int i = 0; i < AOI_LIGHT_CH_COUNT; i++)
	{
		sprintf(pBuf4, "WC%02dD%c", eAOI_LIGHT_CH1 + i, CR);
		UINT ntemp = strlen(pBuf4);
		DWORD ret = m_Comm.WriteComm((BYTE*)pBuf4, (DWORD)ntemp);
		Sleep(20); //!!
	}

	return 0;
}

int FmmLight1::SetHome(int type, int val)
{
	char	pBuf[5] = { 0, };
	sprintf(pBuf, "H");

	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}

int FmmLight1::SetStop(int type, int val)
{
	char	pBuf[5] = { 0, };
	sprintf(pBuf, "B");

	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}

int FmmLight1::SetMove(int type, double val)
{
	char	pBuf[10] = { 0, };
	sprintf(pBuf, "G%d%c", (int)val, CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}

int FmmLight1::GetPos()
{
	char	pBuf[5] = { 0, };
	sprintf(pBuf, "G%c", CR);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	return 0;
}
//21.02.16 sjc
int FmmLight1::SetLight_Review(int Ring, int CoAxial)//1~8 ring 12 = CoAxial
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("Review Light Connect Error !!"));
		return 1;
	}
	char	pBuf[15] = { 0, }; //50
	//Setting ring
	for (int i = 0; i < 8; i++)
	{
		sprintf(pBuf, "%c%02dWR%03d%c", STX, i + 1, Ring, ETX);
		UINT ntemp = strlen(pBuf);
		DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);
		Sleep(20); //!!
	}
	//Setting CoAxial
	sprintf(pBuf, "%c%02dWR%03d%c", STX, 12 , CoAxial, ETX);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	CString Str = _T("");
	Str.Format(_T("Set Review Light Ring : %d, Coaxial : %d"), Ring, CoAxial);
	Total_Msg(Str);
	return 0;
}

int FmmLight1::SetLight_Left_Loader(int Ring, int CoAxial)//Ring 1,2(L,R) Coaxial 5,6(L,R)
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("Loader Light Connect Error !!"));
		return 1;
	}
	char	pBuf[15] = { 0, }; //50
	//Setting ring //Ring 1,2(L,R) Coaxial 5,6(L,R)
	sprintf(pBuf, "%c%02dWR%03d%c", STX, 2, Ring, ETX);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);
	Sleep(20); //!!

	CString Str = _T("");
	//Setting CoAxial //Ring 1,2(L,R) Coaxial 5,6(L,R)
	sprintf(pBuf, "%c%02dWR%03d%c", STX, 6, CoAxial, ETX);
	ntemp = strlen(pBuf);
	ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);
	Str.Format(_T("Set Left Loader Light Ring : %df, Coaxial : %d"), Ring, CoAxial);
	Total_Msg(Str);
	return 0;
}

int FmmLight1::SetLight_Right_Loader(int Ring, int CoAxial)//Ring 1,2(L,R) Coaxial 5,6(L,R)
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("Loader Light Connect Error !!"));
		return 1;
	}
	char	pBuf[15] = { 0, }; //50
	//Setting ring  //Ring 1,2(L,R) Coaxial 5,6(L,R)
	sprintf(pBuf, "%c%02dWR%03d%c", STX, 3, Ring, ETX);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);
	Sleep(20); //!!

	//Setting CoAxial //Ring 1,2(L,R) Coaxial 5,6(L,R)
	sprintf(pBuf, "%c%02dWR%03d%c", STX, 7, CoAxial, ETX);
	ntemp = strlen(pBuf);
	ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	CString Str = _T("");
	Str.Format(_T("Set Right Loader Light Ring : %d, Coaxial : %d"), Ring, CoAxial);
	Total_Msg(Str);
	return 0;
}

int FmmLight1::SetLight_Zoom_Ring(int Ring)
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("Zoom Ring Light Connect Error !!"));
		return 1;
	}
	char	pBuf[15] = { 0, }; 
	sprintf(pBuf, "[01%03d",Ring);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf,(DWORD)ntemp);
	
	CString Str;
	Str.Format(_T("Set Zoom Camera Ring Light %d"),Ring);
	Total_Msg(Str);
	return ret;
}

int FmmLight1::SetLight_Zoom_Coaxial(int Coaxial)
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("Zoom Coaxial Light Connect Error !!"));
		return 1;
	}
	char	pBuf[15] = { 0, };
	sprintf(pBuf, "[01%03d", Coaxial);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	CString Str;
	Str.Format(_T("Set Zoom Camera Coaxial Light %d"), Coaxial);
	Total_Msg(Str);
	return ret;
}

int FmmLight1::Zoom_Light_On(BOOL On)//On = 1 Off = 0
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("Zoom Light Connect Error !!"));
		return 1;
	}
	char	pBuf[15] = { 0, };
	sprintf(pBuf, "]01%d", On);
	UINT ntemp = strlen(pBuf);
	DWORD ret = m_Comm.WriteComm((BYTE*)pBuf, (DWORD)ntemp);

	CString Str;
	if (On == TRUE)
	{
		Str.Format(_T("Zoom Camera Light On"));
	}
	else
	{
		Str.Format(_T("Zoom Camera Light Off"));
	}
	Total_Msg(Str);
	return ret;
}

int FmmLight1::Esc_Send_Msg(CString str)
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("ESC Connect Error !!"));
		return 1;
	}
	char pch[50];
	USES_CONVERSION;
	memset(pch, 0, sizeof(pch));
	char* pcBuf = W2A(str.GetBuffer());

	if (strlen(pcBuf) < sizeof(pch))
		memcpy(pch, pcBuf, strlen(pcBuf));
	else
		memcpy(pch, pcBuf, sizeof(pch));

	str.ReleaseBuffer(); //!!

	char strLF[2];
	UINT ntemp = strlen(pch);
	sprintf(strLF, "%c", LF);
	pch[ntemp] = strLF[0];
	DWORD ret = m_Comm.WriteComm((BYTE*)pch, (DWORD)ntemp+1);

	return TRUE;

}

int FmmLight1::AOI_Send_Msg(CString str)
{
	if (!m_Comm.m_bConnected) {
		Total_Msg(_T("AOI Sensor Connect Error !!"));
		return 1;
	}
	char pch[50];
	USES_CONVERSION;
	memset(pch, 0, sizeof(pch));
	char* pcBuf = W2A(str.GetBuffer());

	if (strlen(pcBuf) < sizeof(pch))
		memcpy(pch, pcBuf, strlen(pcBuf));
	else
		memcpy(pch, pcBuf, sizeof(pch));

	char strCR[2];
	UINT ntemp = strlen(pch);
	sprintf(strCR, "%c", CR);
	pch[ntemp] = strCR[0];
	DWORD ret = m_Comm.WriteComm((BYTE*)pch, (DWORD)ntemp + 1);

	return TRUE;
}

int FmmLight1::AOI_Meas_Print(int headNum)
{
	CString str;
	str.Format(_T("M%d"), headNum);
	AOI_Send_Msg(str);
	return TRUE;
}
int FmmLight1::AOI_Timing_ON_OFF(int headNum, BOOL ON)
{
	CString str;
	str.Format(_T("T%d,%d"), ON, headNum);
	
	AOI_Send_Msg(str);
	return TRUE;
}
int FmmLight1::AOI_Auto_Zero_ON_OFF(int headNum, BOOL ON)
{
	CString str;
	if (ON == TRUE)
	{
		str.Format(_T("V%d"), headNum);
	}
	else
	{
		str.Format(_T("W%d"), headNum);
	}
	AOI_Send_Msg(str);
	return TRUE;
}
int FmmLight1::AOI_Reset(int headNum)
{
	CString str;
	str.Format(_T("VR,%d"),  headNum);
	AOI_Send_Msg(str);
	return TRUE;
}
int FmmLight1::AOI_Program_Change(int programNum)
{
	CString str;
	str.Format(_T("PW,%d"), programNum);
	AOI_Send_Msg(str);
	return TRUE;
}
int FmmLight1::AOI_Program_Check()
{
	AOI_Send_Msg(_T("PR"));
	return TRUE;
}