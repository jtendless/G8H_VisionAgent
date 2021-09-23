#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "MappingProc.h"
#include "Common/CommonDefine.h"
#include "Data/SystemData.h"

#include <math.h>
#include "Vision/Devs.h"

#include "mil.h"

//#define PI				3.14159265358979323846264338
//#define RADIAN			(PI / 180.0)
//#define DEGREE			(180.0 / PI)

CMappingProc* CMappingProc::instance = NULL;

/////////////////////////////////////////

CMappingProc::CMappingProc()
{	
	int i;

	m_nSWMappingCount = 0;
	m_nGlassMappingCount = 0;

	m_StrLogPath.Empty();

#ifndef SIM_MODE
	for (i = 0; i < MAX_MAPPING_ID_SIZE; i++)
	{
		m_MilSWMapping[i] = M_NULL;

		m_dSWMappingResX[i] = 1.0;
		m_dSWMappingResY[i] = 1.0;
		m_dInitSWMappingResX[i] = 1.0;
		m_dInitSWMappingResY[i] = 1.0;

		m_hSWMappingCSVFile[i].m_hFile = CFile::hFileNull;
		
		m_StrSWMappingCALFilePath[i].Empty();
		m_StrSWMappingCSVFilePath[i].Empty();
	}
	
	////////////////////////////////////////////////////
	for(i=0; i<MAX_MAPPING_ID_SIZE; i++)
	{
		m_MilGlassMapping[i] = M_NULL;

		m_dGlassMappingResX[i] = 1.0;
		m_dGlassMappingResY[i] = 1.0;
		m_dInitGlassMappingResX[i] = 1.0;
		m_dInitGlassMappingResY[i] = 1.0;

		m_hGlassMappingCSVFile[i].m_hFile = CFile::hFileNull;

		m_StrGlassMappingCALFilePath[i].Empty();		
		m_StrGlassMappingCSVFilePath[i].Empty();
				
	}	

	////////////////////////////////////////////////////
	memset(m_dGlassMappingMotorX, 0x00, sizeof(m_dGlassMappingMotorX));
	memset(m_dGlassMappingMotorY, 0x00, sizeof(m_dGlassMappingMotorY));
	memset(m_dGlassMappingPixelX, 0x00, sizeof(m_dGlassMappingPixelX));
	memset(m_dGlassMappingPixelY, 0x00, sizeof(m_dGlassMappingPixelY));

	memset(m_dSWMappingMotorX, 0x00, sizeof(m_dSWMappingMotorX));
	memset(m_dSWMappingMotorY, 0x00, sizeof(m_dSWMappingMotorY));
	memset(m_dSWMappingPixelX, 0x00, sizeof(m_dSWMappingPixelX));
	memset(m_dSWMappingPixelY, 0x00, sizeof(m_dSWMappingPixelY));
#endif
}

CMappingProc::~CMappingProc()
{
#ifndef SIM_MODE
	ReleaseSWMapping();
	ReleaseGlassMapping(-1);
#endif
}

CMappingProc* CMappingProc::Create()
{
	if (!instance)
	{
		instance = new CMappingProc;
		if (instance)
		{
			instance->Init();
		}
	}
	return instance;
}

CMappingProc* CMappingProc::GetInstance()
{
	return instance;
}

void CMappingProc::Delete()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

int CMappingProc::Init()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int i;
	CString szPath;

	m_StrLogPath.Format(_T("%s\\LOG\\Mapping"), SharedInfo::VisionAgentPath);

	for (i = 0; i < MAX_MAPPING_ID_SIZE; i++)
	{
		szPath.Format(_T("\\Data\\Mapping\\SWMapping_%d.Txt"), i);
		m_StrSWMappingCALFilePath[i].Format(_T("%s%s"), SharedInfo::VisionAgentPath, szPath);
	}

	for(i=0; i<MAX_MAPPING_ID_SIZE; i++)
	{
		szPath.Format(_T("\\Data\\Mapping\\GlassMapping_%d.Txt"), i);
		m_StrGlassMappingCALFilePath[i].Format(_T("%s%s"), SharedInfo::VisionAgentPath, szPath);
	}

	////////////////////////////////////////////
#ifndef SIM_MODE
	InitializeSWMapping(-1);
	InitializeGlassMapping(-1);

	if (m_MilSWMapping == M_NULL)
	{
		Vision_Msg(_T(" SWMapping : McalAlloc()  error"));
	}

	for(i=0; i<MAX_MAPPING_ID_SIZE; i++)
	{
		if (m_MilGlassMapping[i] == M_NULL)
		{
			Vision_Msg(_T(" GlassMapping_%d : McalAlloc()  error"), i);
		}
	}
#endif
	return -1;
}


int CMappingProc::InitializeSWMapping(int nMappingID /* = -1*/)
{
	int i;
#ifndef SIM_MODE
	ReleaseSWMapping(nMappingID);
#if 0
	if (nMappingID == -1)
	{
		for (i = 0; i < MAX_MAPPING_ID_SIZE; i++)
		{
			if (m_MilSWMapping[i] == M_NULL)
			{
				//sunghaklee(10.25)
				//theApp.MilSysSol0 :½Ã½ºÅÛ ID¿¡ ¸Â°Ô ¼öÁ¤ ÇÊ¿ä
				McalAlloc(theApp.MilSysSol0, M_LINEAR_INTERPOLATION, M_DEFAULT, &m_MilSWMapping[i]);
			}
		}
	}
	else
	{
		if (m_MilSWMapping[nMappingID] == M_NULL)
		{
			//sunghaklee(10.25)
			//theApp.MilSysSol0 :½Ã½ºÅÛ ID¿¡ ¸Â°Ô ¼öÁ¤ ÇÊ¿ä
			McalAlloc(theApp.MilSysSol0, M_LINEAR_INTERPOLATION, M_DEFAULT, &m_MilSWMapping[nMappingID]);
		}
	}
#endif
	ReleaseSWMappingCSVFile(nMappingID);
#endif
	return TRUE;
}

int CMappingProc::InitializeGlassMapping(int nMappingID /* = -1*/)
{
	int i;
#ifndef SIM_MODE
	ReleaseGlassMapping(nMappingID);
#if 1
	if(nMappingID == -1)
	{
		for(i=0; i<MAX_MAPPING_ID_SIZE; i++)
		{
			if (m_MilGlassMapping[i] == M_NULL)
			{
				//sunghaklee(10.25)
				//theApp.MilSysSol0 :½Ã½ºÅÛ ID¿¡ ¸Â°Ô ¼öÁ¤ ÇÊ¿ä
				McalAlloc(Devs::MilSysSol1, M_LINEAR_INTERPOLATION, M_DEFAULT, &m_MilGlassMapping[i]);
			}
		}
	}
	else
	{
		if (m_MilGlassMapping[nMappingID] == M_NULL)
		{
			//sunghaklee(10.25)
			//theApp.MilSysSol0 :½Ã½ºÅÛ ID¿¡ ¸Â°Ô ¼öÁ¤ ÇÊ¿ä
			McalAlloc(Devs::MilSysSol1, M_LINEAR_INTERPOLATION, M_DEFAULT, &m_MilGlassMapping[nMappingID]);
		}
	}	
#endif
	ReleaseGlassMappingCSVFile(nMappingID);
#endif
	return TRUE;
}


int CMappingProc::ReleaseSWMapping(int nMappingID /*= -1*/)
{
	int i;
#ifndef SIM_MODE
	if (nMappingID == -1)
	{
		for (i = 0; i < MAX_MAPPING_ID_SIZE; i++)
		{
			if (m_MilSWMapping[i])
			{
				::McalFree(m_MilSWMapping[i]);
				m_MilSWMapping[i] = M_NULL;
			}
		}
	}
	else
	{
		if (m_MilSWMapping[nMappingID])
		{
			::McalFree(m_MilSWMapping[nMappingID]);
			m_MilSWMapping[nMappingID] = M_NULL;
		}
	}

	ReleaseSWMappingCSVFile();
#endif
	return TRUE;
}

int CMappingProc::ReleaseGlassMapping(int nMappingID /*= -1*/)
{
	int i;
#ifndef SIM_MODE
	if(nMappingID == -1)
	{
		for(i=0; i<MAX_MAPPING_ID_SIZE; i++)
		{
			if (m_MilGlassMapping[i])
			{
				::McalFree(m_MilGlassMapping[i]);
				m_MilGlassMapping[i] = M_NULL;
			}
		}		
	}
	else
	{		
		if (m_MilGlassMapping[nMappingID])
		{
			::McalFree(m_MilGlassMapping[nMappingID]);
			m_MilGlassMapping[nMappingID] = M_NULL;
		}		
	}

	ReleaseGlassMappingCSVFile(nMappingID);
#endif
	return TRUE;
}

int CMappingProc::ReleaseSWMappingCSVFile(int nMappingID /*= -1*/)
{
	int i;
#ifndef SIM_MODE
	if (nMappingID == -1)
	{
		for (i = 0; i < MAX_MAPPING_ID_SIZE; i++)
		{
			if (m_hSWMappingCSVFile[i].m_hFile != CFile::hFileNull)
			{
				m_hSWMappingCSVFile[i].Close();
				m_hSWMappingCSVFile[i].m_hFile = CFile::hFileNull;
			}
		}
	}
	else
	{
		if (m_hSWMappingCSVFile[nMappingID].m_hFile != CFile::hFileNull)
		{
			m_hSWMappingCSVFile[nMappingID].Close();
			m_hSWMappingCSVFile[nMappingID].m_hFile = CFile::hFileNull;
		}
	}
#endif
	return TRUE;
}

int CMappingProc::ReleaseGlassMappingCSVFile(int nMappingID /*= -1*/)
{
	int i;
#ifndef SIM_MODE
	if(nMappingID == -1)
	{
		for(i=0; i<MAX_MAPPING_ID_SIZE; i++)
		{
			if (m_hGlassMappingCSVFile[i].m_hFile != CFile::hFileNull)
			{
				m_hGlassMappingCSVFile[i].Close();
				m_hGlassMappingCSVFile[i].m_hFile = CFile::hFileNull;
			}
		}
	}
	else
	{
		if (m_hGlassMappingCSVFile[nMappingID].m_hFile != CFile::hFileNull)
		{
			m_hGlassMappingCSVFile[nMappingID].Close();
			m_hGlassMappingCSVFile[nMappingID].m_hFile = CFile::hFileNull;
		}
	}
#endif
	return TRUE;
}

int CMappingProc::SaveSWMappingFile(int nMappingID /*= -1*/)
{
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int i;
#ifndef SIM_MODE
	if (nMappingID == -1)
	{
		for (i = 0; i < MAX_MAPPING_ID_SIZE; i++)
		{
			if (M_NULL == m_MilSWMapping[i])	return FALSE;

			::McalSave(_bstr_t(m_StrSWMappingCALFilePath[i]), m_MilSWMapping[i], M_DEFAULT);
		}
	}
	else
	{
		if (M_NULL == m_MilSWMapping[nMappingID])	return FALSE;

		::McalSave(_bstr_t(m_StrSWMappingCALFilePath[nMappingID]), m_MilSWMapping[nMappingID], M_DEFAULT);
	}
#endif
	return TRUE;
}

int CMappingProc::SaveGlassMappingFile(int nMappingID /*= -1*/)
{
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int i;
#ifndef SIM_MODE
	if(nMappingID == -1)
	{
		for(i=0; i<MAX_MAPPING_ID_SIZE; i++)
		{
			if (m_MilGlassMapping[i] == M_NULL)	return FALSE;

			::McalSave(_bstr_t(m_StrGlassMappingCALFilePath[i]), m_MilGlassMapping[i], M_DEFAULT);
		}
	}
	else
	{
		if (m_MilGlassMapping[nMappingID] == M_NULL)	return FALSE;

		::McalSave(_bstr_t(m_StrGlassMappingCALFilePath[nMappingID]), m_MilGlassMapping[nMappingID], M_DEFAULT);
	}
#endif
	return TRUE;
}

int CMappingProc::SaveBackUpMappingFile(int nMappingID)
{
#ifndef SIM_MODE
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	CTime time;
	CString StrGlassMappingBackUpFilePath = _T("");
	CString StrTemp = _T("");
	time = CTime::GetCurrentTime();

	StrTemp.Format(_T("\\Data\\Mapping\\BackUp\\%04d%02d%02d_%02d%02d%02d_GlassMapping_%d.Txt"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(),nMappingID);
	StrGlassMappingBackUpFilePath.Format(_T("%s%s"), SharedInfo::VisionAgentPath, StrTemp);

	if (m_MilGlassMapping[nMappingID] == M_NULL)	return FALSE;

	::McalSave(_bstr_t(StrGlassMappingBackUpFilePath), m_MilGlassMapping[nMappingID], M_DEFAULT);
#endif
	return TRUE;
}

int CMappingProc::LoadSWMappingFile(int nMappingID /*= -1*/)
{
#ifndef SIM_MODE
#if 0
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int i;
	double dbPixelSx = 0;
	double dbPixelSy = 0;

	if (nMappingID == -1)
	{
		for (i = 0; i < MAX_MAPPING_ID_SIZE; i++)
		{
			if (M_NULL == m_MilSWMapping[i])	return FALSE;

			if (GetFindFile(m_StrSWMappingCALFilePath[i]) == FALSE)
			{
				m_dSWMappingResX[i] = m_dInitSWMappingResX[i];
				m_dSWMappingResY[i] = m_dInitSWMappingResY[i];
				return FALSE;
			}

			if (m_MilSWMapping[i] != M_NULL)
			{
				::McalFree(m_MilSWMapping[i]);
				m_MilSWMapping[i] = M_NULL;
			}

			//sunghaklee(10.25)
			//theApp.MilSysSol0 :½Ã½ºÅÛ ID¿¡ ¸Â°Ô ¼öÁ¤ ÇÊ¿ä
			if (::McalRestore((_bstr_t)m_StrSWMappingCALFilePath[i], theApp.MilSysSol0, M_DEFAULT, &m_MilSWMapping[i]) == M_NULL) return FALSE;

			::McalInquire(m_MilSWMapping[i], M_PIXEL_SIZE_X, &dbPixelSx);
			::McalInquire(m_MilSWMapping[i], M_PIXEL_SIZE_Y, &dbPixelSy);

			m_dSWMappingResX[i] = dbPixelSx;
			m_dSWMappingResY[i] = dbPixelSy;
		}
	}
	else
	{
		if (M_NULL == m_MilSWMapping[nMappingID])	return FALSE;

		if (GetFindFile(m_StrSWMappingCALFilePath[nMappingID]) == FALSE)
		{
			m_dSWMappingResX[nMappingID] = m_dInitSWMappingResX[nMappingID];
			m_dSWMappingResY[nMappingID] = m_dInitSWMappingResY[nMappingID];
			return FALSE;
		}

		if (m_MilSWMapping[nMappingID] != M_NULL)
		{
			::McalFree(m_MilSWMapping[nMappingID]);
			m_MilSWMapping[nMappingID] = M_NULL;
		}

		//sunghaklee(10.25)
		//theApp.MilSysSol0 :½Ã½ºÅÛ ID¿¡ ¸Â°Ô ¼öÁ¤ ÇÊ¿ä
		if (::McalRestore((_bstr_t)m_StrSWMappingCALFilePath[nMappingID], theApp.MilSysSol0, M_DEFAULT, &m_MilSWMapping[nMappingID]) == M_NULL) return FALSE;

		::McalInquire(m_MilSWMapping[nMappingID], M_PIXEL_SIZE_X, &dbPixelSx);
		::McalInquire(m_MilSWMapping[nMappingID], M_PIXEL_SIZE_Y, &dbPixelSy);

		m_dSWMappingResX[nMappingID] = dbPixelSx;
		m_dSWMappingResY[nMappingID] = dbPixelSy;
	}
#endif
#endif
	return TRUE;
}

int CMappingProc::LoadGlassMappingFile(int nMappingID /*= -1*/)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	CString szMsg;
	int i;
	double dbPixelSx = 0;
	double dbPixelSy = 0;
#ifndef SIM_MODE

	if(nMappingID == -1)
	{
		for (i = 0; i < MAX_MAPPING_ID_SIZE; i++)
		{
			if (m_MilGlassMapping[i] == M_NULL)
			{
				szMsg.Format(_T("[LoadGlassMappingFile_%d] : Fail(ID NULL"), i);
				Vision_Msg(szMsg);
				return FALSE;
			}

			if (GetFindFile(m_StrGlassMappingCALFilePath[i]) == FALSE)
			{
				m_dGlassMappingResX[i] = m_dInitGlassMappingResX[i];
				m_dGlassMappingResY[i] = m_dInitGlassMappingResY[i];

				szMsg.Format(_T("[LoadGlassMappingFile_%d] : Fail(No File)"), i);
				Vision_Msg(szMsg);
				return FALSE;
			}

			if (m_MilGlassMapping[i] != M_NULL)
			{
				::McalFree(m_MilGlassMapping[i]);
				m_MilGlassMapping[i] = M_NULL;
			}

			//sunghaklee(10.25)
			//theApp.MilSysSol0 :½Ã½ºÅÛ ID¿¡ ¸Â°Ô ¼öÁ¤ ÇÊ¿ä
			if (::McalRestore((_bstr_t)m_StrGlassMappingCALFilePath[i], Devs::MilSysSol1, M_DEFAULT, &m_MilGlassMapping[i]) == M_NULL)
			{
				szMsg.Format(_T("[LoadGlassMappingFile_%d] : Fail(Restore"), i);
				Vision_Msg(szMsg);
				return FALSE;
			}

			::McalInquire(m_MilGlassMapping[i], M_PIXEL_SIZE_X, &dbPixelSx);
			::McalInquire(m_MilGlassMapping[i], M_PIXEL_SIZE_Y, &dbPixelSy);

			m_dGlassMappingResX[i] = dbPixelSx;
			m_dGlassMappingResY[i] = dbPixelSy;

			szMsg.Format(_T("[LoadGlassMappingFile_%d] : Success"), i);
			Vision_Msg(szMsg);
		}
	}
	else
	{
		if (m_MilGlassMapping[nMappingID] == M_NULL)
		{
			szMsg.Format(_T("[LoadGlassMappingFile_%d] : Fail(ID NULL"), nMappingID);
			Vision_Msg(szMsg);
			return FALSE;
		}

		if (GetFindFile(m_StrGlassMappingCALFilePath[nMappingID]) == FALSE)
		{
			m_dGlassMappingResX[nMappingID] = m_dInitGlassMappingResX[nMappingID];
			m_dGlassMappingResY[nMappingID] = m_dInitGlassMappingResY[nMappingID];

			szMsg.Format(_T("[LoadGlassMappingFile_%d] : Fail(No File"), nMappingID);
			Vision_Msg(szMsg);
			return FALSE;
		}

		if (m_MilGlassMapping[nMappingID] != M_NULL)
		{
			::McalFree(m_MilGlassMapping[nMappingID]);
			m_MilGlassMapping[nMappingID] = M_NULL;
		}

		//sunghaklee(10.25)
		//theApp.MilSysSol0 :½Ã½ºÅÛ ID¿¡ ¸Â°Ô ¼öÁ¤ ÇÊ¿ä
		if (::McalRestore((_bstr_t)m_StrGlassMappingCALFilePath[nMappingID], Devs::MilSysSol1, M_DEFAULT, &m_MilGlassMapping[nMappingID]) == M_NULL)
		{
			szMsg.Format(_T("[LoadGlassMappingFile_%d] : Fail(Restore"), nMappingID);
			Vision_Msg(szMsg);
		
			return FALSE;
		}

		::McalInquire(m_MilGlassMapping[nMappingID], M_PIXEL_SIZE_X, &dbPixelSx);
		::McalInquire(m_MilGlassMapping[nMappingID], M_PIXEL_SIZE_Y, &dbPixelSy);

		m_dGlassMappingResX[nMappingID] = dbPixelSx;
		m_dGlassMappingResY[nMappingID] = dbPixelSy;

		szMsg.Format(_T("[LoadGlassMappingFile_%d] : Success"), nMappingID);
		Vision_Msg(szMsg);
	}
#endif

	return TRUE;
}

int CMappingProc::GetFindFile(CString szFile)
{
	BOOL  bFind = FALSE;
	CFileFind finder;

	bFind = finder.FindFile(szFile);
	finder.Close();

	return bFind;
}

BOOL CMappingProc::SaveSWMappingCSV(CString szFilePath, BOOL bAdd)
{
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int i;
	CStdioFile file;
	double dFx, dFy, dMx, dMy;
	CString szData;

	WORD wMode = CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone;
	if (bAdd)	wMode |= CFile::modeNoTruncate;

	if (!file.Open(szFilePath, wMode))	return FALSE;

	if (bAdd)		file.SeekToEnd();

	for (i = 0; i < m_nSWMappingCount; i++)
	{
		dFx = m_dSWMappingPixelX[i];
		dFy = m_dSWMappingPixelY[i];
		dMx = m_dSWMappingMotorX[i];
		dMy = m_dSWMappingMotorY[i];

		//No, World X, World Y, Calib X, Calib Y, Calib Z, Target X, Target Y, Find X, Find Y
		szData.Format(_T("%d, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf\n"), i + 1,
			dMx, dMy, dMx, dMy, m_dSWMappingPoint[i].z, dFx, dFy, dFx - dMx, dFy - dMy);
		file.WriteString(szData);
	}
	file.Close();

	return TRUE;
}

BOOL CMappingProc::SaveGlassMappingCSV(int nMappingID, CString szFilePath, BOOL bAdd)
{
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int i;
	CStdioFile file;
	double dFx, dFy, dMx, dMy;
	CString szData;

	WORD wMode = CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone;
	if (bAdd)	wMode |= CFile::modeNoTruncate;

	if (!file.Open(szFilePath, wMode))	return FALSE;

	if (bAdd)		file.SeekToEnd();

	for (i = 0; i < m_nGlassMappingCount; i++)
	{
		dFx = m_dGlassMappingPixelX[i];
		dFy = m_dGlassMappingPixelY[i];
		dMx = m_dGlassMappingMotorX[i];
		dMy = m_dGlassMappingMotorY[i];

		//No, World X, World Y, Calib X, Calib Y, Calib Z, Target X, Target Y, Find X, Find Y
		szData.Format(_T("%d, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf\n"), i + 1,
			dMx, dMy, dMx, dMy, m_dGlassMappingPoint[i].z, dFx, dFy, dFx - dMx, dFy - dMy);
		file.WriteString(szData);
	}
	file.Close();

	return TRUE;
}

BOOL CMappingProc::LoadSWMappingCSV(int nMappingID, CString szFilePath, int &nReadCount)
{
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int j;
	CStdioFile	file;
	CFileFind	finder;
	BOOL bResult;
	BOOL bRead = TRUE;
	CString strPath, strReadLine, strToken;
	double dFx, dFy, dMx, dMy;

	nReadCount = 0;

	bResult = finder.FindFile(szFilePath);
	if (!bResult)	return FALSE;

	if (!file.Open(szFilePath, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone))	return FALSE;

	bRead = file.ReadString(strReadLine); //! Header
	while (bRead)
	{
		bRead = file.ReadString(strReadLine);
		if (strReadLine.GetLength() <= 5 || bRead == FALSE){
			bRead = FALSE;
			break;
		}

		for (j = 0; AfxExtractSubString(strToken, strReadLine, j, ','); j++)
		{
			switch (j)
			{
			case 1:		dMx = _ttof(strToken);	break;
			case 2:		dMy = _ttof(strToken);	break;
			case 6:		dFx = _ttof(strToken);	break;
			case 7:		dFy = _ttof(strToken);	break;
			default:	continue;
			}
		}

		SetSWMapping_CalibData(nMappingID, nReadCount, dFx, dFy, dMx, dMy);
		nReadCount++;
	}
	file.Close();

	return TRUE;
}

BOOL CMappingProc::LoadGlassMappingCSV(int nMappingID, CString szFilePath, int &nReadCount)
{
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int j;
	CStdioFile	file;
	CFileFind	finder;
	BOOL bResult;
	BOOL bRead = TRUE;
	CString strPath, strReadLine, strToken;
	double dFx, dFy, dMx, dMy;

	nReadCount = 0;

	bResult = finder.FindFile(szFilePath);
	if (!bResult)	return FALSE;

	if (!file.Open(szFilePath, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone))	return FALSE;

	bRead = file.ReadString(strReadLine); //! Header
	while (bRead)
	{
		bRead = file.ReadString(strReadLine);
		if (strReadLine.GetLength() <= 5 || bRead == FALSE){
			bRead = FALSE;
			break;
		}

		for (j = 0; AfxExtractSubString(strToken, strReadLine, j, ','); j++)
		{
			switch (j)
			{
			case 1:		dMx = _ttof(strToken);	break;
			case 2:		dMy = _ttof(strToken);	break;
			case 6:		dFx = _ttof(strToken);	break;
			case 7:		dFy = _ttof(strToken);	break;
			default:	continue;
			}
		}

		SetGlassMapping_CalibData(nMappingID, nReadCount, dFx, dFy, dMx, dMy);
		nReadCount++;
	}
	file.Close();

	return TRUE;
}

BOOL CMappingProc::SaveSWMappingCSVEx(int nMappingID, CFile *pFile, CString szText, BOOL bOverWrite /*= FALSE*/)
{
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	BOOL bSuccess = FALSE;
	if (szText.IsEmpty())	return bSuccess;

	if (pFile[nMappingID].m_hFile != CFile::hFileNull && pFile[nMappingID].GetFilePath() != m_StrSWMappingCSVFilePath[nMappingID])
	{
		pFile[nMappingID].Close();
		pFile[nMappingID].m_hFile = CFile::hFileNull;
	}

	if (pFile[nMappingID].m_hFile == CFile::hFileNull)
	{
		if (!pFile[nMappingID].Open(m_StrSWMappingCSVFilePath[nMappingID], CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone | CFile::modeNoTruncate))
			return bSuccess;

		pFile[nMappingID].SeekToEnd();
	}

	if (bOverWrite)		pFile[nMappingID].SeekToBegin();
	INT nLen = szText.GetLength() + 1;
	CHAR *pszMbTxt = new CHAR[nLen];
	ZeroMemory(pszMbTxt, sizeof(CHAR)* nLen);

	bSuccess = (nLen == UnicodeToMultiByte(_bstr_t(szText), pszMbTxt)) ? TRUE : FALSE;
	if (bSuccess)
	{
		//pFile->Write(pszMbTxt, sizeof(CHAR) * nLen);
		pFile[nMappingID].Write(pszMbTxt, (UINT)strlen(pszMbTxt));
	}

	delete[] pszMbTxt;

	return bSuccess;
}
// m_StrLogPath
//BOOL CMappingProc::SaveGlassMappingCSVEx(int nMappingID, CFile *pFile, CString szText, BOOL bOverWrite /*= FALSE*/)
//{
//	//CVisionAgentDlg *pVisionAgentDlg;
//	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//
//	BOOL bSuccess = FALSE;
//	if (szText.IsEmpty())
//	{
//		Vision_Msg(_T("szText Empty"));
//		return bSuccess;
//	}
//
//	if (pFile[nMappingID].m_hFile != CFile::hFileNull && pFile[nMappingID].GetFilePath() != m_StrGlassMappingCSVFilePath[nMappingID])
//	{
//		pFile[nMappingID].Close();
//		pFile[nMappingID].m_hFile = CFile::hFileNull;
//	}
//
//	if (pFile[nMappingID].m_hFile == CFile::hFileNull)
//	{
//		if (!pFile[nMappingID].Open(m_StrGlassMappingCSVFilePath[nMappingID], CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone | CFile::modeNoTruncate))
//		{
//			Vision_Msg(_T("File Open File"));
//			return bSuccess;
//		}
//		pFile[nMappingID].SeekToEnd();
//	}
//
//
//		pFile[nMappingID].SeekToBegin();
//
//	pFile[nMappingID].Write(pszMbTxt, (UINT)strlen(pszMbTxt));
//	
//	delete[] pszMbTxt;
//	
//	return bSuccess;
//}

BOOL CMappingProc::SaveGlassMappingCSVEx(int nMappingID, CFile *pFile, CString szText, BOOL bOverWrite /*= FALSE*/)
{
	BOOL bSuccess = FALSE;
	if (szText.IsEmpty())	return bSuccess;

	FILE * fp = NULL;
	CFileFind	finder;
	CString strFile, strPath;

	strFile.Format(_T("%s"), m_StrGlassMappingCSVFilePath[nMappingID]);

	BOOL	bFindFile = finder.FindFile(strFile);
	finder.Close();

	if (bFindFile)	fp = _wfopen(strFile, _T("at+"));
	else			fp = _wfopen(strFile, _T("wt"));

	fwprintf(fp, szText);

	fclose(fp);

	return bSuccess;
}

int CMappingProc::GetSWMapping_CalibPosXY(int nMappingID, double *dPosX, double *dPosY)
{
	CString Str = _T("");
	double  dOrgX = 0.0, dOrgY = 0.0;
	double  dCalbX = 0.0, dCalbY = 0.0;

	dOrgX = dCalbX = *dPosX;
	dOrgY = dCalbY = *dPosY;

	GetSWMapping_WorldToPixel(nMappingID, dCalbX, dCalbY);

	//if (fabs(*dPosX - dCalbX) < 1.0 && fabs(*dPosY - dCalbY) < 1.0)
	if (fabs(*dPosX - dCalbX) < 2.0 && fabs(*dPosY - dCalbY) < 2.0)
	{
		*dPosX = dCalbX;
		*dPosY = dCalbY;
	}

	Str.Format(_T("GetSWMapping_CalibPosXY X:%.5f, Y:%.5f => X:%.5f, Y:%.5f"), dOrgX, dOrgY, dCalbX, dCalbY);
	Total_Msg(Str);

	return TRUE;
}

int CMappingProc::GetGlassMapping_CalibPosXY(int nMappingID, double *dPosX, double *dPosY)
{
	CString Str = _T("");
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	double  dOrgX = 0.0, dOrgY = 0.0;
	double  dCalbX = 0.0, dCalbY = 0.0;

	//if (pVisionAgentDlg->m_SystemParaData.m_GlassMappingInfo.m_nGlassMappingUsage == FALSE) return FALSE;

	dOrgX = dCalbX = *dPosX;
	dOrgY = dCalbY = *dPosY;

	GetGlassMapping_WorldToPixel(nMappingID, dCalbX, dCalbY);

	//if (fabs(*dPosX - dCalbX) < 1.0 && fabs(*dPosY - dCalbY) < 1.0)
	if (fabs(*dPosX - dCalbX) < 2.0 && fabs(*dPosY - dCalbY) < 2.0)
	{
		*dPosX = dCalbX;
		*dPosY = dCalbY;
	}

	//Str.Format(_T("GetGlassMapping_CalibPosXY X:%.5f, Y:%.5f => X:%.5f, Y:%.5f"), dOrgX, dOrgY, dCalbX, dCalbY);
	//Total_Msg(Str);

	return TRUE;
}

int CMappingProc::GetSWMapping_PixelToWorld(int nMappingID, double& x, double& y)
{
	CString Str = _T("");
	double dOrgX = 0.0, dOrgY = 0.0;
	double dbValX = 0.0, dbValY = 0.0;
#ifndef SIM_MODE
	if (m_MilSWMapping[nMappingID] == M_NULL) return FALSE;

	dOrgX = x;
	dOrgY = y;

	::McalTransformCoordinate(m_MilSWMapping[nMappingID], M_PIXEL_TO_WORLD, dOrgX, dOrgY, &dbValX, &dbValY);

	x = dbValX;
	y = dbValY;

	Str.Format(_T("GetSWMapping_PixelToWorld] X:%.5f, Y:%.5f => X:%.5f, Y:%.5f"), dOrgX, dOrgY, dbValX, dbValY);
	Total_Msg(Str);
#endif
	return TRUE;
}

int CMappingProc::GetGlassMapping_PixelToWorld(int nMappingID, double& x, double& y)
{
	CString Str = _T("");
	double dOrgX = 0.0, dOrgY = 0.0;
	double dbValX = 0.0, dbValY = 0.0;
#ifndef SIM_MODE
	if (m_MilGlassMapping[nMappingID] == M_NULL) return FALSE;

	dOrgX = x;
	dOrgY = y;

	::McalTransformCoordinate(m_MilGlassMapping[nMappingID], M_PIXEL_TO_WORLD, dOrgX, dOrgY, &dbValX, &dbValY);

	x = dbValX;
	y = dbValY;

	Str.Format(_T("GetGlassMapping_PixelToWorld] X:%.5f, Y:%.5f => X:%.5f, Y:%.5f"), dOrgX, dOrgY, dbValX, dbValY);
	Total_Msg(Str);
#endif
	return TRUE;
}

int CMappingProc::GetSWMapping_WorldToPixel(int nMappingID, double& x, double& y)
{
	CString Str = _T("");
	double dOrgX = 0.0, dOrgY = 0.0;
	double dbValX = 0.0, dbValY = 0.0;
#ifndef SIM_MODE
	if (m_MilSWMapping[nMappingID] == M_NULL)	return FALSE;

	dOrgX = x;
	dOrgY = y;

	::McalTransformCoordinate(m_MilSWMapping[nMappingID], M_WORLD_TO_PIXEL, dOrgX, dOrgY, &dbValX, &dbValY);

	x = dbValX;
	y = dbValY;

	Str.Format(_T("GetSWMapping_WorldToPixel] X:%.5f, Y:%.5f => X:%.5f, Y:%.5f"), dOrgX, dOrgY, dbValX, dbValY);
	Total_Msg(Str);
#endif
	return TRUE;
}

int CMappingProc::GetGlassMapping_WorldToPixel(int nMappingID, double& x, double& y)
{
	CString Str = _T("");
	double dOrgX = 0.0, dOrgY = 0.0;
	double dbValX = 0.0, dbValY = 0.0;
#ifndef SIM_MODE
	if (m_MilGlassMapping[nMappingID] == M_NULL)	return FALSE;

	dOrgX = x;
	dOrgY = y;

	::McalTransformCoordinate(m_MilGlassMapping[nMappingID], M_WORLD_TO_PIXEL, dOrgX, dOrgY, &dbValX, &dbValY);

	x = dbValX;
	y = dbValY;

	//Str.Format(_T("GetGlassMapping_WorldToPixel] X:%.5f, Y:%.5f => X:%.5f, Y:%.5f"), dOrgX, dOrgY, dbValX, dbValY);
	//Total_Msg(Str);
#endif
	return TRUE;
}

int CMappingProc::Calculate_SWMapping(int nMappingID, int nCount, double* dMotorX, double* dMotorY, double* dPixelX, double* dPixelY, double dOrgX, double dOrgY, BOOL bRelativeOrign)
{
#ifndef SIM_MODE
#if 0
	Vision_Msg(_T("[SW_MAPPING] Calculate_SWMapping Begin"));

	if (m_MilSWMapping[nMappingID] == M_NULL)	return FALSE;
	if (nCount <= 0)			return FALSE;

	try
	{
		//MFTYPE32 void MFTYPE McalList(MIL_ID CalibrationId,
		//const double * XPixArray,
		//const double * YPixArray,
		//const double * XWorldArray,
		//const double * YWorldArray,
		//const double * ZWorldArray,
		//MIL_INT   NumData,
		//MIL_INT   Operation,
		//MIL_INT   ControlFlag);

		Vision_Msg(_T("[SW_MAPPING_%d] McalList = %d"), nMappingID, nCount);

		McalList(m_MilSWMapping[nMappingID], dPixelX, dPixelY, dMotorX, dMotorY, M_NULL, nCount, M_DEFAULT, M_DEFAULT);
	}
	catch (COleDispatchException *Exception)
	{
		TCHAR szMsg[MAX_PATH];
		Exception->GetErrorMessage(szMsg, MAX_PATH);
		Exception->Delete();
		return FALSE;
	}

	// calibration results
	MIL_DOUBLE	dbPixelSizeX, dbPixelSizeY;
	MIL_DOUBLE	dbAveragePixelError, dbAverageWorldError;
	MIL_DOUBLE	dbMaximumPixelError, dbMaximumWorldError;
	MIL_DOUBLE	dbPixelAspectRatio, dbOriginAngle;
	MIL_DOUBLE	dbOriginX, dbOriginY;

	long bRet = (LONG)::McalInquire(m_MilSWMapping[nMappingID], M_CALIBRATION_SUCCESSFUL, M_NULL);
	if (bRet == 0)	return FALSE;

	::McalInquire(m_MilSWMapping[nMappingID], M_PIXEL_SIZE_X, &dbPixelSizeX);
	::McalInquire(m_MilSWMapping[nMappingID], M_PIXEL_SIZE_Y, &dbPixelSizeY);
	::McalInquire(m_MilSWMapping[nMappingID], M_AVERAGE_PIXEL_ERROR, &dbAveragePixelError);
	::McalInquire(m_MilSWMapping[nMappingID], M_AVERAGE_WORLD_ERROR, &dbAverageWorldError);
	::McalInquire(m_MilSWMapping[nMappingID], M_MAXIMUM_PIXEL_ERROR, &dbMaximumPixelError);
	::McalInquire(m_MilSWMapping[nMappingID], M_MAXIMUM_WORLD_ERROR, &dbMaximumWorldError);
	::McalInquire(m_MilSWMapping[nMappingID], M_ASPECT_RATIO, &dbPixelAspectRatio);
	::McalInquire(m_MilSWMapping[nMappingID], M_RELATIVE_ORIGIN_ANGLE, &dbOriginAngle);
	::McalInquire(m_MilSWMapping[nMappingID], M_RELATIVE_ORIGIN_X, &dbOriginX);
	::McalInquire(m_MilSWMapping[nMappingID], M_RELATIVE_ORIGIN_Y, &dbOriginY);

	// set origin center position
	if (bRelativeOrign) {
		::McalTransformCoordinate(m_MilSWMapping[nMappingID], M_PIXEL_TO_WORLD, dOrgX, dOrgY, &dbOriginX, &dbOriginY);
		::McalRelativeOrigin(m_MilSWMapping[nMappingID], dbOriginX, dbOriginY, M_NULL, 0, M_DEFAULT);
	}

	m_dSWMappingResX[nMappingID] = dbPixelSizeX;
	m_dSWMappingResY[nMappingID] = dbPixelSizeY;


	Vision_Msg(_T("[SW_MAPPING_%d] Calculate_SWMapping End"), nMappingID);
#endif
#endif
	return TRUE;
}

int CMappingProc::Calculate_GlassMapping(int nMappingID, int nCount, double* dMotorX, double* dMotorY, double* dPixelX, double* dPixelY, double dOrgX, double dOrgY, BOOL bRelativeOrign)
{
	CString szMsg;
#ifndef SIM_MODE
#if 1
	szMsg.Format(_T("[GLASS_MAPPING_%d] Calculate_GlassMapping Begin"), nMappingID);
	Vision_Msg(szMsg);
	if (m_MilGlassMapping[nMappingID] == M_NULL)	return FALSE;
	if (nCount <= 0)			return FALSE;

	try
	{
		//MFTYPE32 void MFTYPE McalList(MIL_ID CalibrationId,
		//const double * XPixArray,
		//const double * YPixArray,
		//const double * XWorldArray,
		//const double * YWorldArray,
		//const double * ZWorldArray,
		//MIL_INT   NumData,
		//MIL_INT   Operation,
		//MIL_INT   ControlFlag);

		szMsg.Format(_T("[GLASS_MAPPING_%d] McalList = %d"), nMappingID, nCount);
		Vision_Msg(szMsg);
		McalList(m_MilGlassMapping[nMappingID], dPixelX, dPixelY, dMotorX, dMotorY, M_NULL, nCount, M_DEFAULT, M_DEFAULT);
	}
	catch (COleDispatchException *Exception)
	{
		TCHAR szMsg[MAX_PATH];
		Exception->GetErrorMessage(szMsg, MAX_PATH);
		Exception->Delete();
		return FALSE;
	}

	// calibration results
	MIL_DOUBLE	dbPixelSizeX, dbPixelSizeY;
	MIL_DOUBLE	dbAveragePixelError, dbAverageWorldError;
	MIL_DOUBLE	dbMaximumPixelError, dbMaximumWorldError;
	MIL_DOUBLE	dbPixelAspectRatio, dbOriginAngle;
	MIL_DOUBLE	dbOriginX, dbOriginY;

	long bRet = (LONG)::McalInquire(m_MilGlassMapping[nMappingID], M_CALIBRATION_STATUS, M_NULL);
	if (bRet == 0)	return FALSE;

	::McalInquire(m_MilGlassMapping[nMappingID], M_PIXEL_SIZE_X, &dbPixelSizeX);
	::McalInquire(m_MilGlassMapping[nMappingID], M_PIXEL_SIZE_Y, &dbPixelSizeY);
	::McalInquire(m_MilGlassMapping[nMappingID], M_AVERAGE_PIXEL_ERROR, &dbAveragePixelError);
	::McalInquire(m_MilGlassMapping[nMappingID], M_AVERAGE_WORLD_ERROR, &dbAverageWorldError);
	::McalInquire(m_MilGlassMapping[nMappingID], M_MAXIMUM_PIXEL_ERROR, &dbMaximumPixelError);
	::McalInquire(m_MilGlassMapping[nMappingID], M_MAXIMUM_WORLD_ERROR, &dbMaximumWorldError);
	::McalInquire(m_MilGlassMapping[nMappingID], M_ASPECT_RATIO, &dbPixelAspectRatio);
	::McalInquire(m_MilGlassMapping[nMappingID], M_RELATIVE_ORIGIN_ANGLE, &dbOriginAngle);
	::McalInquire(m_MilGlassMapping[nMappingID], M_RELATIVE_ORIGIN_X, &dbOriginX);
	::McalInquire(m_MilGlassMapping[nMappingID], M_RELATIVE_ORIGIN_Y, &dbOriginY);

	// set origin center position
	if (bRelativeOrign) {
		::McalTransformCoordinate(m_MilGlassMapping[nMappingID], M_PIXEL_TO_WORLD, dOrgX, dOrgY, &dbOriginX, &dbOriginY);
		::McalRelativeOrigin(m_MilGlassMapping[nMappingID], dbOriginX, dbOriginY, M_NULL, 0, M_DEFAULT);
	}

	m_dGlassMappingResX[nMappingID] = dbPixelSizeX;
	m_dGlassMappingResY[nMappingID] = dbPixelSizeY;

	szMsg.Format(_T("[GLASS_MAPPING_%d] Calculate_GlassMapping End"), nMappingID);
	Vision_Msg(szMsg);
#endif
#endif
	return TRUE;
}

int CMappingProc::CloseSWMapping_CalibData(int nMappingID, double dOrgCx, double dOrgCy)
{
	if (Calculate_SWMapping(nMappingID, m_nSWMappingCount, m_dSWMappingMotorX, m_dSWMappingMotorY, m_dSWMappingPixelX, m_dSWMappingPixelY, dOrgCx, dOrgCy, FALSE))
	{
		SaveSWMappingFile();
		return TRUE;
	}

	return FALSE;
}

int CMappingProc::CloseGlassMapping_CalibData(int nMappingID, double dOrgCx, double dOrgCy)
{
	/*
	double dNewMotorX[4] = { 0.0 };
	double dNewMotorY[4] = { 0.0 };

	double dNewPixelX[4] = { 0.0 };
	double dNewPixelY[4] = { 0.0 };


	dNewMotorX[0] = m_dGlassMappingMotorX[0];
	dNewMotorX[1] = m_dGlassMappingMotorX[1];
	dNewMotorX[2] = m_dGlassMappingMotorX[3];
	dNewMotorX[3] = m_dGlassMappingMotorX[2];

	dNewMotorY[0] = m_dGlassMappingMotorY[0];
	dNewMotorY[1] = m_dGlassMappingMotorY[1];
	dNewMotorY[2] = m_dGlassMappingMotorY[3];
	dNewMotorY[3] = m_dGlassMappingMotorY[2];


	dNewPixelX[0] = m_dGlassMappingPixelX[0];
	dNewPixelX[1] = m_dGlassMappingPixelX[1];
	dNewPixelX[2] = m_dGlassMappingPixelX[3];
	dNewPixelX[3] = m_dGlassMappingPixelX[2];

	dNewPixelY[0] = m_dGlassMappingPixelY[0];
	dNewPixelY[1] = m_dGlassMappingPixelY[1];
	dNewPixelY[2] = m_dGlassMappingPixelY[3];
	dNewPixelY[3] = m_dGlassMappingPixelY[2];


	if (Calculate_GlassMapping(4, dNewMotorX, dNewMotorY, dNewPixelX, dNewPixelY, dOrgCx, dOrgCy, FALSE))
	*/

	if (Calculate_GlassMapping(nMappingID, m_nGlassMappingCount, m_dGlassMappingMotorX, m_dGlassMappingMotorY, m_dGlassMappingPixelX, m_dGlassMappingPixelY, dOrgCx, dOrgCy, FALSE))
	{
		SaveGlassMappingFile(nMappingID);
		SaveBackUpMappingFile(nMappingID);
		return TRUE;
	}

	return FALSE;
}

CDMPoint CMappingProc::GetSWMapping_Num2MotorPos(int nMappingID, int nX, int nY)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int nCountX = MAX_SWMAPPING_POINT_COUNT_X;
	int nCountY = MAX_SWMAPPING_POINT_COUNT_Y;

	CDMPoint stPoint;
	memset(&stPoint, 0x00, sizeof(stPoint));

	if (nX < 0 || nX >= nCountX)	return stPoint;
	if (nY < 0 || nY >= nCountY)	return stPoint;

	stPoint = m_dSWMappingPoint[nY*nCountX + nX];

	return stPoint;
}

CDMPoint CMappingProc::GetGlassMapping_Num2MotorPos(int nMappingID, int nX, int nY)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	
//TODO_parkcm Ä«¿îÅÍ ÀÔ·Â ÇÊ¿ä 

#if 1
	int nCountX = CSystemData::m_Stage.Info.m_nParameterCountX;
	int nCountY = CSystemData::m_Stage.Info.m_nParameterCountY;
#endif

	CDMPoint stPoint;
	memset(&stPoint, 0x00, sizeof(stPoint));

	if (nX < 0 || nX >= nCountX)	return stPoint;
	if (nY < 0 || nY >= nCountY)	return stPoint;

	stPoint = m_dGlassMappingPoint[nY*nCountX + nX];

	return stPoint;
}

int CMappingProc::SetSWMapping_RelativeOrigin(int nMappingID, double dOffsetX, double dOffsetY, double dOffsetZ, double dAngle)
{
#ifndef SIM_MODE
	if (m_MilSWMapping[nMappingID] == M_NULL)	return FALSE;

	try
	{
		::McalRelativeOrigin(m_MilSWMapping[nMappingID], dOffsetX, dOffsetY, dOffsetZ, dAngle, M_DEFAULT);
	}
	catch (COleDispatchException *Exception)
	{
		TCHAR szMsg[MAX_PATH];
		Exception->GetErrorMessage(szMsg, MAX_PATH);
		Exception->Delete();
		return FALSE;
	}
#endif
	return TRUE;
}

int CMappingProc::SetGlassMapping_RelativeOrigin(int nMappingID, double dOffsetX, double dOffsetY, double dOffsetZ, double dAngle)
{
#ifndef SIM_MODE
	if (m_MilGlassMapping[nMappingID] == M_NULL)	return FALSE;

	try
	{
		::McalRelativeOrigin(m_MilGlassMapping[nMappingID], dOffsetX, dOffsetY, dOffsetZ, dAngle, M_DEFAULT);
	}
	catch (COleDispatchException *Exception)
	{
		TCHAR szMsg[MAX_PATH];
		Exception->GetErrorMessage(szMsg, MAX_PATH);
		Exception->Delete();
		return FALSE;
	}
#endif
	return TRUE;
}

int CMappingProc::SetSWMapping_RelativeAngleOrigin(int nMappingID, double dAngle)
{
#ifndef SIM_MODE
	if (m_MilSWMapping[nMappingID] == M_NULL)	return FALSE;

	try
	{
		::McalControl(m_MilSWMapping[nMappingID], M_RELATIVE_ORIGIN_ANGLE, dAngle);
	}
	catch (COleDispatchException *Exception)
	{
		TCHAR szMsg[MAX_PATH];
		Exception->GetErrorMessage(szMsg, MAX_PATH);
		Exception->Delete();
		return FALSE;
	}
#endif
	return TRUE;
}


int CMappingProc::SetGlassMapping_RelativeAngleOrigin(int nMappingID, double dAngle)
{
#ifndef SIM_MODE
	if (m_MilGlassMapping[nMappingID] == M_NULL)	return FALSE;

	try
	{
		::McalControl(m_MilGlassMapping[nMappingID], M_RELATIVE_ORIGIN_ANGLE, dAngle);
	}
	catch (COleDispatchException *Exception)
	{
		TCHAR szMsg[MAX_PATH];
		Exception->GetErrorMessage(szMsg, MAX_PATH);
		Exception->Delete();
		return FALSE;
	}

#endif
	return TRUE;
}


int CMappingProc::MakeSWMapping_CalibPoint(int nMappingID)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int x, y;
	int nCountX = MAX_SWMAPPING_POINT_COUNT_X;
	int nCountY = MAX_SWMAPPING_POINT_COUNT_Y;
	//TODO_parkcm Æ÷Áö¼Ç ÀÔ·Â ÇÊ¿ä
#if 0
	double dPitchX = pVisionAgentDlg->m_SystemParaData.m_SWMappingInfo.m_dSWMappingPitchX;// (dSizeX - dStartX * 2) / (nCountX - 1);
	double dPitchY = pVisionAgentDlg->m_SystemParaData.m_SWMappingInfo.m_dSWMappingPitchY;// (dSizeY - dStartY * 2) / (nCountY - 1);
	double dStartX = pVisionAgentDlg->m_SystemParaData.m_SWMappingInfo.m_dSWMappingStartPosX;
	double dStartY = pVisionAgentDlg->m_SystemParaData.m_SWMappingInfo.m_dSWMappingStartPosY;
	double dPosZ = pVisionAgentDlg->m_SystemParaData.m_SWMappingInfo.m_dSWMappingStartPosZ;
#endif
	double dPitchX = 0;
	double dPitchY = 0;
	double dStartX = 0;
	double dStartY = 0;
	double dPosZ = 0;
	if (nCountX < 2 || nCountY < 2)				return FALSE;

	memset(&m_dSWMappingPoint, 0x00, sizeof(m_dSWMappingPoint));

	for (y = 0; y < nCountY; y++)
	{
		for (x = 0; x < nCountX; x++)
		{
			m_dSWMappingPoint[nCountX * y + x].x = dStartX + dPitchX * x;
			m_dSWMappingPoint[nCountX * y + x].y = dStartY + dPitchY * y;
			m_dSWMappingPoint[nCountX * y + x].z = dPosZ;
		}
	}

	return TRUE;
}

int CMappingProc::MakeGlassMapping_CalibPoint(int nMappingID)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int x, y;
	//TODO_parkcm Æ÷Áö¼Ç ÀÔ·Â ÇÊ¿ä
#if 1
	int nCountX = CSystemData::m_Stage.Info.m_nParameterCountX;
	int nCountY = CSystemData::m_Stage.Info.m_nParameterCountY;
	double dPitchX = CSystemData::m_Stage.Info.m_dParameterPitchX;// (dSizeX - dStartX * 2) / (nCountX - 1);
	double dPitchY = CSystemData::m_Stage.Info.m_dParameterPitchY;// (dSizeY - dStartY * 2) / (nCountY - 1);
	double dStartX = CSystemData::m_Stage.Info.m_dParameterStartX;
	double dStartY = CSystemData::m_Stage.Info.m_dParameterStartY;
	double dPosZ = 0.0;
#else
	int nCountX = 0;
	int nCountY =0;
	double dPitchX =0;// (dSizeX - dStartX * 2) / (nCountX - 1);
	double dPitchY = 0;// (dSizeY - dStartY * 2) / (nCountY - 1);
	double dStartX =0;
	double dStartY = 0;
	double dPosZ = 0.0;
#endif
	

	//if (nCountX < 2 || nCountY < 2)				return FALSE;
	if (nCountX >= MAX_GLASS_MAPPING_COUNT)
		return FALSE;

	memset(&m_dGlassMappingPoint, 0x00, sizeof(m_dGlassMappingPoint));

	//Caution
	//dPitchY *= -1.0;

	for (y = 0; y < nCountY; y++)
	{
		for (x = 0; x < nCountX; x++)
		{
			m_dGlassMappingPoint[nCountX * y + x].x = dStartX + dPitchX * x;
			m_dGlassMappingPoint[nCountX * y + x].y = dStartY + dPitchY * y;
			m_dGlassMappingPoint[nCountX * y + x].z = dPosZ;
		}
	}

	return TRUE;
}

//int CMappingProc::CalibSWMapping_Main(int nRepeatCount)
//{
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	//bool bStopFlag = FALSE;
	//int x, y;
	//int nMaxCountX = MAX_SWMAPPING_POINT_COUNT_X;
	//int nMaxCountY = MAX_SWMAPPING_POINT_COUNT_Y;
	//int nUseX = 0, nUseY = 0;
	//double	dRadian = 0;
	//double  dCurrX, dCurrY;

	//CTime time;
	//CString szMsg;
	//CString szPath;
	//szMsg.Empty();

	//InitializeSWMapping();
	//MakeSWMapping_CalibPoint();

	//time = CTime::GetCurrentTime();

	//szPath.Format(_T("\\Log_SW_%04d%02d%02d_%02d%02d%02d.csv"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	//m_StrSWMappingCSVFilePath.Format(_T("%s%s"), m_StrLogPath, szPath);

	//szMsg.Format(_T("No, World X, World Y, Calib X, Calib Y, Calib Z, Target X, Target Y, Find X, Find Y\n"));
	//SaveSWMappingCSVEx(&m_hSWMappingCSVFile, szMsg, TRUE);

	//m_nSWMappingCount = 0;

	//for (y = 0; y < nMaxCountY; y++)
	//{
	//	if (bStopFlag)		break;

	//	for (x = 0; x < nMaxCountX; x++)
	//	{
	//		nUseY = y;
	//		if (y % 2 != 0)		nUseX = nMaxCountX - 1 - x;
	//		else				nUseX = x;

	//		if (CalibSWMappingExec(nUseX, nUseY) == FALSE)
	//		{
	//			dCurrX = SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_GANTRY_X_MF];
	//			dCurrY = SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_VIRTUAL_GANTRY_B];

	//			Vision_Msg(_T("[SW_MAPPING] Hole is not found. skip...mask x[%.3f]y[%.3f]"), dCurrX, dCurrY);
	//			bStopFlag = TRUE;
	//			y = nMaxCountY + 1;
	//			break;
	//		}

	//		//if (GetThread_PauseCheck() == FALSE)
	//		//{
	//		//	bStopFlag = TRUE;
	//		//	y = nMaxCountY + 1;
	//		//	break;
	//		//}

	//		Sleep(100);
	//	}
	//}

	//ReleaseSWMappingCSVFile();

	//if (bStopFlag == TRUE)	return FALSE;

	//CloseSWMapping_CalibData(0.0, 0.0);

	//Vision_Msg(_T("[SW_MAPPING] Complete Mapping Calibration.[REPEAT:%d]"), nRepeatCount + 1);

	//return TRUE;
//}

int CMappingProc::CalibSWMapping_MainBegin(int nMappingID)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	bool bStopFlag = FALSE;
	//int x, y;
	int nMaxCountX = MAX_SWMAPPING_POINT_COUNT_X;
	int nMaxCountY = MAX_SWMAPPING_POINT_COUNT_Y;
	int nUseX = 0, nUseY = 0;
	double	dRadian = 0;
	//double  dCurrX, dCurrY;

	CTime time;
	CString szMsg;
	CString szPath;
	szMsg.Empty();

	InitializeSWMapping(nMappingID);
	MakeSWMapping_CalibPoint(nMappingID);
	szMsg.Format(_T("[SW_MAPPING_%d] Begin SW Mapping Calibration."), nMappingID);
	Vision_Msg(szMsg);

	time = CTime::GetCurrentTime();

	szPath.Format(_T("\\Log_SW(%d)_%04d%02d%02d_%02d%02d%02d.csv"), nMappingID, time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	m_StrSWMappingCSVFilePath[nMappingID].Format(_T("%s%s"), m_StrLogPath, szPath);

	szMsg.Format(_T("No, World X, World Y, Calib X, Calib Y, Calib Z, Target X, Target Y, Find X, Find Y\n"));
	SaveSWMappingCSVEx(nMappingID, m_hSWMappingCSVFile, szMsg, TRUE);

	m_nSWMappingCount = 0;

	/*
	for (y = 0; y < nMaxCountY; y++)
	{
	if (bStopFlag)		break;

	for (x = 0; x < nMaxCountX; x++)
	{
	nUseY = y;
	if (y % 2 != 0)		nUseX = nMaxCountX - 1 - x;
	else				nUseX = x;

	if (CalibSWMappingExec(nUseX, nUseY) == FALSE)
	{
	dCurrX = pVisionAgentDlg->m_dUmacActPos[2];
	dCurrY = pVisionAgentDlg->m_dUmacActPos[0];

	Vision_Msg(_T("[SW_MAPPING] Hole is not found. skip...mask x[%.3f]y[%.3f]"), dCurrX, dCurrY);
	bStopFlag = TRUE;
	y = nMaxCountY + 1;
	break;
	}

	//if (GetThread_PauseCheck() == FALSE)
	//{
	//	bStopFlag = TRUE;
	//	y = nMaxCountY + 1;
	//	break;
	//}

	Sleep(100);
	}
	}

	ReleaseSWMappingCSVFile();

	if (bStopFlag == TRUE)	return FALSE;

	CloseSWMapping_CalibData(0.0, 0.0);

	Vision_Msg(_T("[SW_MAPPING] Complete Mapping Calibration.[REPEAT:%d]"), nRepeatCount + 1);
	*/

	return TRUE;
}

int CMappingProc::CalibSWMapping_MainSetData(int nMappingID, int nCount, double dPixelX, double dPixelY, double dMotorX, double dMotorY)
{
	CString szMsg;
	szMsg.Format(_T("[SW_MAPPING(%d)] Motor = %.5f, %.5f Pixel = %.5f, %.5f"), nCount, dMotorX, dMotorY, dPixelX, dPixelY);
	Vision_Msg(szMsg);

	SetSWMapping_CalibData(nMappingID, nCount, dPixelX, dPixelY, dMotorX, dMotorY);

	return TRUE;
}

int CMappingProc::CalibSWMapping_MainEnd(int nMappingID)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	bool bStopFlag = FALSE;
	//int x, y;
	int nMaxCountX = MAX_SWMAPPING_POINT_COUNT_X;
	int nMaxCountY = MAX_SWMAPPING_POINT_COUNT_Y;
	int nUseX = 0, nUseY = 0;
	double	dRadian = 0;
	//double  dCurrX, dCurrY;

	CTime time;
	CString szMsg;
	CString szPath;
	szMsg.Empty();

	/*
	time = CTime::GetCurrentTime();

	szPath.Format(_T("\\Log_SW_%04d%02d%02d_%02d%02d%02d.csv"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	m_StrSWMappingCSVFilePath.Format(_T("%s%s"), m_StrLogPath, szPath);

	szMsg.Format(_T("No, World X, World Y, Calib X, Calib Y, Calib Z, Target X, Target Y, Find X, Find Y\n"));
	SaveSWMappingCSVEx(&m_hGlassMappingCSVFile, szMsg, TRUE);

	m_nSWMappingCount = 0;

	for (y = 0; y < nMaxCountY; y++)
	{
	if (bStopFlag)		break;

	for (x = 0; x < nMaxCountX; x++)
	{
	nUseY = y;
	if (y % 2 != 0)		nUseX = nMaxCountX - 1 - x;
	else				nUseX = x;

	if (CalibSWMappingExec(nUseX, nUseY) == FALSE)
	{
	dCurrX = pVisionAgentDlg->m_dUmacActPos[2];
	dCurrY = pVisionAgentDlg->m_dUmacActPos[0];

	Vision_Msg(_T("[SW_MAPPING] Hole is not found. skip...mask x[%.3f]y[%.3f]"), dCurrX, dCurrY);
	bStopFlag = TRUE;
	y = nMaxCountY + 1;
	break;
	}

	//if (GetThread_PauseCheck() == FALSE)
	//{
	//	bStopFlag = TRUE;
	//	y = nMaxCountY + 1;
	//	break;
	//}

	Sleep(100);
	}
	}
	*/

	ReleaseSWMappingCSVFile(nMappingID);

	if (bStopFlag == TRUE)	return FALSE;

	CloseSWMapping_CalibData(nMappingID, 0.0, 0.0);

	szMsg.Format(_T("[SW_MAPPING_%d] End SW Mapping Calibration."), nMappingID);
	Vision_Msg(szMsg);

	return TRUE;
}

//int CMappingProc::CalibGlassMapping_Main(int nMappingID, int nRepeatCount)
//{
//	CVisionAgentDlg *pVisionAgentDlg;
//	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//
//	bool bStopFlag = FALSE;
//	int x, y;
//	int nMaxCountX = 0 ;
//	int nMaxCountY = 0;
//#if 0
//	int nMaxCountX = CMachineData::Stage.m_dParameterCountX;
//	int nMaxCountY = CMachineData::Stage.m_dParameterCountY;
//#endif
//	int nUseX = 0, nUseY = 0;
//	double	dRadian = 0;
//	double  dCurrX, dCurrY;
//
//	CTime time;
//	CString szMsg;
//	CString szPath;
//	szMsg.Empty();
//
//	//if (pVisionAgentDlg->m_SystemParaData.m_GlassMappingInfo.m_nGlassMappingUsage == FALSE) return FALSE;
//
//	InitializeGlassMapping(nMappingID);
//	MakeGlassMapping_CalibPoint(nMappingID);
//
//	time = CTime::GetCurrentTime();
//
//	szPath.Format(_T("\\Log_Glass_%04d%02d%02d_%02d%02d%02d.csv"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
//	m_StrGlassMappingCSVFilePath[nMappingID].Format(_T("%s%s"), m_StrLogPath, szPath);
//
//	szMsg.Format(_T("No, World X, World Y, Calib X, Calib Y, Calib Z, Target X, Target Y, Find X, Find Y, Temp, EncX, EncY \n")); // 180207 modify by L
//	SaveGlassMappingCSVEx(nMappingID, &m_hGlassMappingCSVFile[nMappingID], szMsg, TRUE);
//
//	m_nGlassMappingCount = 0;
//
//	for (y = 0; y < nMaxCountY; y++)
//	{
//		if (bStopFlag)		break;
//
//		for (x = 0; x < nMaxCountX; x++)
//		{
//			nUseY = y;
//			if (y % 2 != 0)		nUseX = nMaxCountX - 1 - x;
//			else				nUseX = x;
//
//			if (CalibGlassMappingExec(nMappingID, nUseX, nUseY) == FALSE)
//			{
//				dCurrX = SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_GANTRY_X_MF];
//				dCurrY = SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_VIRTUAL_GANTRY_B];
//
//				Vision_Msg(_T("[GLASS_MAPPING] Hole is not found. skip...mask x[%.3f]y[%.3f]"), dCurrX, dCurrY);
//
//				bStopFlag = TRUE;
//				y = nMaxCountY + 1;
//				break;
//			}
//
//			//if (GetThread_PauseCheck() == FALSE)
//			//{
//			//	bStopFlag = TRUE;
//			//	y = nMaxCountY + 1;
//			//	break;
//			//}
//
//			Sleep(100);
//		}
//	}
//
//	ReleaseGlassMappingCSVFile(nMappingID);
//
//	if (bStopFlag == TRUE)	return FALSE;
//
//	CloseGlassMapping_CalibData(nMappingID, 0.0, 0.0);
//
//	Vision_Msg(_T("[GLASS_MAPPING_%d] Complete Mapping Calibration.[REPEAT:%d]"),nMappingID, nRepeatCount + 1);

//	return TRUE;
//}


int CMappingProc::CalibGlassMapping_MainBegin(int nMappingID, int nCount, int nVerification /*= 0*/)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	bool bStopFlag = FALSE;
	//int x, y;
	int nMaxCountX = 0;
	int nMaxCountY = 0;
#if 0
	int nMaxCountX = CMachineData::Stage.m_dParameterCountX;
	int nMaxCountY = CMachineData::Stage.m_dParameterCountY;
#endif
	int nUseX = 0, nUseY = 0;
	double	dRadian = 0;
	//double  dCurrX, dCurrY;

	CTime time;
	CString szMsg;
	CString szPath;
	szMsg.Empty();

	//if (pVisionAgentDlg->m_SystemParaData.m_GlassMappingInfo.m_nGlassMappingUsage == FALSE) return FALSE;

	// AO¨öA ¢¬¡¤A¨ö
	/*if (nVerification == FALSE)
	{
		InitializeGlassMapping();
	}*/

	//MakeGlassMapping_CalibPoint(nMappingID);

	Vision_Msg(_T("[GLASS_MAPPING_%d] Begin Glass Mapping Calibration."), nMappingID);
	
	time = CTime::GetCurrentTime();

	if (nVerification == 0)
	{
		szPath.Format(_T("\\Log_Glass(%d)_%04d%02d%02d_%02d%02d%02d_Cnt(%d).csv"), nMappingID, time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), nCount);
		m_StrGlassMappingCSVFilePath[nMappingID].Format(_T("%s%s"), m_StrLogPath, szPath);
	}
	else
	{
		szPath.Format(_T("\\Log_Glass(%d)_%04d%02d%02d_%02d%02d%02d_Cnt(%d)_Verify.csv"), nMappingID, time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), nCount);
		m_StrGlassMappingCSVFilePath[nMappingID].Format(_T("%s%s"), m_StrLogPath, szPath);
	}

	szMsg.Format(_T("No,"));
	szMsg.Append(_T("World X,"));
	szMsg.Append(_T("World Y,"));
	szMsg.Append(_T("Calib X,"));
	szMsg.Append(_T("Calib Y,"));
	szMsg.Append(_T("Calib Z,"));
	szMsg.Append(_T("Target X,"));
	szMsg.Append(_T("Target Y,"));
	szMsg.Append(_T("Find X,"));
	szMsg.Append(_T("Find Y,"));
	szMsg.Append(_T("dScore,"));
	szMsg.Append(_T("dScale,"));

	for (int i = 0; i < 12; i++)
	{
		szMsg.AppendFormat(_T("Temp %d,"), i + 1);
	}

	szMsg.Append(_T("nRealAxisX,"));
	szMsg.Append(_T("nRealAxisY,"));
	szMsg.Append(_T("nRealAxisZ\n"));
	
	SaveGlassMappingCSVEx(nMappingID, m_hGlassMappingCSVFile, szMsg);

	m_nGlassMappingCount = 0;

	/*
	for (y = 0; y < nMaxCountY; y++)
	{
	if (bStopFlag)		break;

	for (x = 0; x < nMaxCountX; x++)
	{
	nUseY = y;
	if (y % 2 != 0)		nUseX = nMaxCountX - 1 - x;
	else				nUseX = x;

	if (CalibGlassMappingExec(nUseX, nUseY) == FALSE)
	{
	dCurrX = pVisionAgentDlg->m_dUmacActPos[2];
	dCurrY = pVisionAgentDlg->m_dUmacActPos[0];

	Vision_Msg(_T("[GLASS_MAPPING] Hole is not found. skip...mask x[%.3f]y[%.3f]"), dCurrX, dCurrY);

	bStopFlag = TRUE;
	y = nMaxCountY + 1;
	break;
	}

	//if (GetThread_PauseCheck() == FALSE)
	//{
	//	bStopFlag = TRUE;
	//	y = nMaxCountY + 1;
	//	break;
	//}

	Sleep(100);
	}
	}

	ReleaseGlassMappingCSVFile(nMappingID);

	if (bStopFlag == TRUE)	return FALSE;

	CloseGlassMapping_CalibData(0.0, 0.0);

	Vision_Msg(_T("[SW_MAPPING] Complete Mapping Calibration.[REPEAT:%d]"), nRepeatCount + 1);
	*/

	return TRUE;
}

int CMappingProc::CalibGlassMapping_MainGetData(int nMappingID, double dPosX, double dPosY, double dDiffX, double dDiffY, double dScore, double dScale, int nVerification)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int nIndex;
	CString szMsg, str;
	double dWaitZ = 0.0;
	CDMPoint dMovePos;
	double dRealX, dRealY;
	double dPixelX, dPixelY;
	double dMaskX, dMaskY;
	double dCalibX, dCalibY;
	double dCurrX, dCurrY;
	CGlassMark GlassMark;

	int nAxisX, nAxisY, nAxisZ;

	BOOL bFind = FALSE;
	szMsg.Empty();


	switch (nMappingID)
	{
	case eMAPPING_ID_10X:
		nAxisX = REMOTE_AXIS_UMAC_GANTRY_X;
		nAxisY = REMOTE_AXIS_UMAC_GANTRY_Y1;
		nAxisZ = DIRECT_AXIS_CAMERA_Z1;
	}
	
	//! Measure Position Move Axis-X,Y
	dRealX = dPosX;
	dRealY = dPosY;
	
	if (nVerification == TRUE)
		GetGlassMapping_CalibPosXY(nMappingID, &dRealX, &dRealY);
	else
		GetGlassMapping_WorldToPixel(nMappingID, dRealX, dRealY);

	//Sleep(10);

	double pointX = dDiffX;
	double pointY = dDiffY;

	//! Calibration Data Set
	dCurrX = dRealX;
	dCurrY = dRealY;

	dMaskX = dPosX;
	dMaskY = dPosY;
	
	//sunghaklee(10.25)
	dPixelX = dCurrX + pointX;
	dPixelY = dCurrY + pointY;
	//sunghaklee(2021.04.22)
	//dPixelX = SharedInfo::UmacActPos[nAxisX] + pointX;
	//dPixelY = SharedInfo::UmacActPos[nAxisY] + pointY;

	str.Format(_T("Blob_XY Abs(mm) : %12.6f, %12.6f"), dPixelX, dPixelY);
	Vision_Msg(str);

	dCalibX = dRealX;
	dCalibY = dRealY;

	nIndex = m_nGlassMappingCount;
	m_dGlassMappingPoint[nIndex].z = SharedInfo::VisionAxisCmdPos[nAxisZ];
	
	szMsg.Format(_T("%d,"), nIndex + 1);
	szMsg.AppendFormat(_T("%12.6f,"), dMaskX);
	szMsg.AppendFormat(_T("%12.6f,"), dMaskY);
	szMsg.AppendFormat(_T("%12.6f,"), dCalibX);
	szMsg.AppendFormat(_T("%12.6f,"), dCalibY);

	szMsg.AppendFormat(_T("%12.6f,"), m_dGlassMappingPoint[nIndex].z);
	szMsg.AppendFormat(_T("%12.6f,"), dPixelX);
	szMsg.AppendFormat(_T("%12.6f,"), dPixelY);
	szMsg.AppendFormat(_T("%12.6f,"), dPixelX - dCurrX);
	szMsg.AppendFormat(_T("%12.6f,"), dPixelY - dCurrY);
	//szMsg.AppendFormat(_T("%12.6f,"), pointX);
	//szMsg.AppendFormat(_T("%12.6f,"), pointY);
	szMsg.AppendFormat(_T("%12.6f,"), dScore);
	szMsg.AppendFormat(_T("%12.6f,"), dScale);

	for (int i = 0; i < 12; i++)
	{		
		szMsg.AppendFormat(_T("%4.2f,"), g_CommTempTur.m_dTempValue[i]);
	}

	szMsg.AppendFormat(_T("%12.6f,"), SharedInfo::UmacActPos[nAxisX]);
	szMsg.AppendFormat(_T("%12.6f,"), SharedInfo::UmacActPos[nAxisY]);
	szMsg.AppendFormat(_T("%12.6f\n"), SharedInfo::VisionAxisCmdPos[nAxisZ]);

	Vision_Msg(szMsg);
	SaveGlassMappingCSVEx(nMappingID, m_hGlassMappingCSVFile, szMsg);

	////////////////////////////////////////////////////
	if (nVerification == FALSE)
		SetGlassMapping_CalibData(nMappingID, nIndex, dPixelX, dPixelY, dMaskX, dMaskY);

	if (FALSE == bFind)	
		return FALSE;
	else
		return true;
}

int CMappingProc::CalibGlassMapping_MainEnd(int nMappingID, int nVerification /*= 0*/)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	bool bStopFlag = FALSE;
	//int x, y;
	int nMaxCountX;
	int nMaxCountY;
#if 0
	int nMaxCountX = CMachineData::Stage.m_dParameterCountX;
	int nMaxCountY = CMachineData::Stage.m_dParameterCountY;
#endif
	int nUseX = 0, nUseY = 0;
	double	dRadian = 0;
	///double  dCurrX, dCurrY;

	CTime time;
	CString szMsg;
	CString szPath;
	CString strTemp;
	szMsg.Empty();
	
	ReleaseGlassMappingCSVFile(nMappingID);

	if (bStopFlag == TRUE)	return FALSE;

	if (nVerification == FALSE)
	{
		if (!CloseGlassMapping_CalibData(nMappingID, 0.0, 0.0))
		{
			strTemp.Format(_T("[GLASS_MAPPING_%d] Glass Mapping Calibration FAIL."), nMappingID);
			Vision_Msg(strTemp);
			Devs::StopAll();
			return SharedInfo::SetAlarm(0);			
		}
	}

	strTemp.Format(_T("[GLASS_MAPPING_%d] End of Glass Mapping Calibration."), nMappingID);
	Vision_Msg(strTemp);

	return TRUE;
}


//int CMappingProc::CalibSWMappingExec(int nCountX, int nCountY)
//{
//	CVisionAgentDlg *pVisionAgentDlg;
//	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//
//	int i, nIndex;
//	CString szMsg;
//	double dWaitZ = 0.0;
//	CDMPoint dMovePos;
//	double dRealX, dRealY;
//	//double dPixelX, dPixelY;
//	double dMaskX, dMaskY;
//	double dCalibX, dCalibY;
//	double dCurrX, dCurrY;
//	double dResolX = PPA_X10_PIXEL2MM_X;
//	double dResolY = PPA_X10_PIXEL2MM_Y;
//	double dImgSizeX = PPA_IMAGE_X;
//	double dImgSizeY = PPA_IMAGE_Y;
//
//	int nAxisNo;
//	double dPos, dVel, dAccel, dDecel;
//
//	BOOL bFind = FALSE;
//	szMsg.Empty();
//
//	dMovePos = GetSWMapping_Num2MotorPos(nCountX, nCountY);
//	//! Measure Position Move Axis-X,Y
//	dRealX = dMovePos.x;	dRealY = dMovePos.y;
//	GetSWMapping_WorldToPixel(dRealX, dRealY);
//
//	//if (MoveGantry(dRealX, dRealY, false, FALSE) == FALSE)		return FALSE;
//	//TODO_parkcm ÀÌµ¿ ÇÔ¼ö ±¸Çö ÇÊ¿ä 
//#if 0
//	nAxisNo = _UMAC_GANTRY_Y1;
//	dPos = dRealY;
//	dVel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[UMAC_CCD_YL];
//	dAccel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorAcc[UMAC_CCD_YL];
//	dDecel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorDec[UMAC_CCD_YL];
//	pVisionAgentDlg->m_ClientInterface.UmacPosMove(nAxisNo, dPos, dVel, dAccel, dDecel, 0);
//
//	Sleep(10);
//
//	nAxisNo = _AXIS_GANTRY_X;
//	dPos = dRealX;
//	dVel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[UMAC_CCD_X];
//	dAccel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorAcc[UMAC_CCD_X];
//	dDecel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorDec[UMAC_CCD_X];
//	pVisionAgentDlg->m_ClientInterface.UmacPosMove(nAxisNo, dPos, dVel, dAccel, dDecel, 0);
//
//	Sleep(10);
//
//	//if (MoveCameraZ(dMovePos.z, true) == FALSE)	return FALSE;
//
//	nAxisNo;// = _AXIS_CAMERA_Z1;
//	dPos = dMovePos.z;
//	dVel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[MOTOR_VISION_CCD_ZL];
//	dAccel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorAcc[MOTOR_VISION_CCD_ZL];
//	dDecel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorDec[MOTOR_VISION_CCD_ZL];
//	pVisionAgentDlg->m_ClientInterface.AxisPosMove(nAxisNo, dPos, dVel, dAccel, dDecel, 0);
//#endif
//	//! Find Mark Search
//	for (i = 0; i < 5; i++)
//	{
//		Sleep(1000);
//
//		//bFind = GetHoleMeasure(stFind);
//		if (TRUE == bFind)		break;
//	}
//	if (FALSE == bFind)		return FALSE;
//
//	//! Calibration Data Set
//	//dWorldX = g_clMotionSet.m_clMotorInfo[nAxisX].dActualPos;
//	//dWorldY = g_clMotionSet.m_clMotorInfo[nAxisY].dActualPos;
//	//dPixelX = dWorldX + (g_clVision->m_clImgSize[nCh].x / 2 - stFind.m_cdFindMark.x) * g_clSystemData.m_clCamera.m_dpResol[nCh].x;
//	//dPixelY = dWorldY + (g_clVision->m_clImgSize[nCh].y / 2 - stFind.m_cdFindMark.y) * g_clSystemData.m_clCamera.m_dpResol[nCh].x;
//
//	dCurrX = SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_GANTRY_X_MF];
//	dCurrY = SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_VIRTUAL_GANTRY_B];
//	dMaskX = dMovePos.x;
//	dMaskY = dMovePos.y;
//	//dPixelX = dCurrX + (stFind.m_cdFindMark.x - dImgSizeX / 2) / 2 * dResolX;
//	//dPixelY = dCurrY + (dImgSizeY / 2 - stFind.m_cdFindMark.y) / 2 * dResolY;
//	//	dPixelX = dCurrX + (dImgSizeX / 2 - FindMark.x) * dResolX;
//	//	dPixelY = dCurrY + (dImgSizeY / 2 - FindMark.y) * dResolY;
//
//	dCalibX = dRealX;// dPixelX - (dPixelX - dWorldX);
//	dCalibY = dRealY;// dPixelY - (dPixelY - dWorldY);
//
//	nIndex = m_nSWMappingCount;
//	//szMsg.Format(_T("%d, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf\n"), nIndex + 1,
//	//	dMaskX, dMaskY, dCalibX, dCalibY, m_dSWMappingPoint[nIndex].z,
//	//	dPixelX, dPixelY, dPixelX - dCurrX, dPixelY - dCurrY);
//
//	SaveSWMappingCSVEx(&m_hSWMappingCSVFile, szMsg);
//
//	////////////////////////////////////////////////////
//	//SetSWMapping_CalibData(nIndex, dPixelX, dPixelY, dMaskX, dMaskY);
//
//	return true;
//}

//int CMappingProc::CalibGlassMappingExec(int nMappingID, int nCountX, int nCountY)
//{
//	CVisionAgentDlg *pVisionAgentDlg;
//	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//
//	int i, nIndex;
//	CString szMsg;
//	double dWaitZ = 0.0;
//	CDMPoint dMovePos;
//	double dRealX, dRealY;
//	//double dPixelX, dPixelY;
//	double dMaskX, dMaskY;
//	double dCalibX, dCalibY;
//	double dCurrX, dCurrY;
//	double dResolX = PPA_X10_PIXEL2MM_X;
//	double dResolY = PPA_X10_PIXEL2MM_Y;
//	double dImgSizeX = PPA_IMAGE_X;
//	double dImgSizeY = PPA_IMAGE_Y;
//
//	int nAxisNo;
//	double dPos, dVel, dAccel, dDecel;
//
//	BOOL bFind = FALSE;
//	szMsg.Empty();
//
//	dMovePos = GetGlassMapping_Num2MotorPos(nMappingID, nCountX, nCountY);
//	//! Measure Position Move Axis-X,Y
//	dRealX = dMovePos.x;	dRealY = dMovePos.y;
//	GetGlassMapping_WorldToPixel(nMappingID, dRealX, dRealY);
//
//	//if (MoveGantry(dRealX, dRealY, false, FALSE) == FALSE)		return FALSE;
//	//TODO_parkcm ÀÌµ¿ ÇÔ¼ö ±¸Çö ÇÊ¿ä 
//#if 0
//	nAxisNo = _UMAC_GANTRY_Y1;
//	dPos = dRealY;
//	dVel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[UMAC_CCD_YL];
//	dAccel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorAcc[UMAC_CCD_YL];
//	dDecel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorDec[UMAC_CCD_YL];
//	pVisionAgentDlg->m_ClientInterface.UmacPosMove(nAxisNo, dPos, dVel, dAccel, dDecel, 0);
//
//	Sleep(10);
//
//	nAxisNo = _AXIS_GANTRY_X;
//	dPos = dRealX;
//	dVel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[UMAC_CCD_X];
//	dAccel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorAcc[UMAC_CCD_X];
//	dDecel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorDec[UMAC_CCD_X];
//	pVisionAgentDlg->m_ClientInterface.UmacPosMove(nAxisNo, dPos, dVel, dAccel, dDecel, 0);
//
//	Sleep(10);
//
//	//if (MoveCameraZ(dMovePos.z, true) == FALSE)	return FALSE;
//
//	nAxisNo;// = _AXIS_CAMERA_Z1;
//	dPos = dMovePos.z;
//	dVel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[MOTOR_VISION_CCD_ZL];
//	dAccel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorAcc[MOTOR_VISION_CCD_ZL];
//	dDecel = pVisionAgentDlg->m_VelocityData.m_WorkVelocity.m_dMotorDec[MOTOR_VISION_CCD_ZL];
//	pVisionAgentDlg->m_ClientInterface.AxisPosMove(nAxisNo, dPos, dVel, dAccel, dDecel, 0);
//#endif
//	//! Find Mark Search
//	for (i = 0; i < 5; i++)
//	{
//		Sleep(1000);
//
//		//bFind = GetHoleMeasure(stFind);
//		if (TRUE == bFind)		break;
//	}
//	if (FALSE == bFind)		return FALSE;
//
//	//! Calibration Data Set
//	//dWorldX = g_clMotionSet.m_clMotorInfo[nAxisX].dActualPos;
//	//dWorldY = g_clMotionSet.m_clMotorInfo[nAxisY].dActualPos;
//	//dPixelX = dWorldX + (g_clVision->m_clImgSize[nCh].x / 2 - stFind.m_cdFindMark.x) * g_clSystemData.m_clCamera.m_dpResol[nCh].x;
//	//dPixelY = dWorldY + (g_clVision->m_clImgSize[nCh].y / 2 - stFind.m_cdFindMark.y) * g_clSystemData.m_clCamera.m_dpResol[nCh].x;
//
//	dCurrX = SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_GANTRY_X_MF];
//	dCurrY = SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_VIRTUAL_GANTRY_B];
//	dMaskX = dMovePos.x;
//	dMaskY = dMovePos.y;
//	//dPixelX = dCurrX + (stFind.m_cdFindMark.x - dImgSizeX / 2) / 2 * dResolX;
//	//dPixelY = dCurrY + (dImgSizeY / 2 - stFind.m_cdFindMark.y) / 2 * dResolY;
//	//	dPixelX = dCurrX + (dImgSizeX / 2 - m_cdFindMark.x) * dResolX;
//	//	dPixelY = dCurrY + (dImgSizeY / 2 - m_cdFindMark.y) * dResolY;
//
//	dCalibX = dRealX;// dPixelX - (dPixelX - dWorldX);
//	dCalibY = dRealY;// dPixelY - (dPixelY - dWorldY);
//
//	nIndex = m_nGlassMappingCount;
//	/*szMsg.Format(_T("%d, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf, %.05lf\n"), nIndex + 1,
//	dMaskX, dMaskY, dCalibX, dCalibY, m_dGlassMappingPoint[nIndex].z,
//	dPixelX, dPixelY, dPixelX - dCurrX, dPixelY - dCurrY);*/
//
//	SaveGlassMappingCSVEx(nMappingID, &m_hGlassMappingCSVFile[nMappingID], szMsg);
//
//	////////////////////////////////////////////////////
//	//SetGlassMapping_CalibData(nIndex, dPixelX, dPixelY, dMaskX, dMaskY);
//
//	return true;
//}

void CMappingProc::SetSWMapping_CalibData(int nMappingID, int nCount, double dPixelX, double dPixelY, double dMotorX, double dMotorY)
{
	if (nCount < 0)		return;
	if (nCount >= MAX_SWMAPPING_POINT_COUNT_X * MAX_SWMAPPING_POINT_COUNT_Y)	return;

	m_nSWMappingCount = nCount + 1;

	m_dSWMappingMotorX[nCount] = dMotorX;
	m_dSWMappingMotorY[nCount] = dMotorY;
	m_dSWMappingPixelX[nCount] = dPixelX;
	m_dSWMappingPixelY[nCount] = dPixelY;
}

void CMappingProc::SetGlassMapping_CalibData(int nMappingID, int nCount, double dPixelX, double dPixelY, double dMotorX, double dMotorY)
{
	CString szMsg;
	if (nCount < 0)		return;
	if (nCount >= MAX_GLASS_MAPPING_COUNT)	return;

	szMsg.Format(_T("[SetGlassMapping_CalibData] nCount = %d"), nCount);

	Vision_Msg(szMsg);
	m_nGlassMappingCount = nCount + 1;

	m_dGlassMappingMotorX[nCount] = dMotorX;
	m_dGlassMappingMotorY[nCount] = dMotorY;
	m_dGlassMappingPixelX[nCount] = dPixelX;
	m_dGlassMappingPixelY[nCount] = dPixelY;
}


int CMappingProc::ReleaseXYTAlignData(int nMappingID /*= -1*/)
{
	int i;	

	if (nMappingID == -1)
	{
		for (i = 0; i < MAX_XYTALIGN_ID_SIZE; i++)
		{
			m_XYTAlignData[i].dOriginX = 0.0;
			m_XYTAlignData[i].dOriginY = 0.0;
			m_XYTAlignData[i].dRotAngle = 0.0;
		}
	}
	else
	{
		m_XYTAlignData[nMappingID].dOriginX = 0.0;
		m_XYTAlignData[nMappingID].dOriginY = 0.0;
		m_XYTAlignData[nMappingID].dRotAngle = 0.0;
	}

	return TRUE;
}

int CMappingProc::GetXYTAlign_CalibPosXY(int nMappingID, double *dPosX, double *dPosY)
{
	double  dCalbX = 0.0, dCalbY = 0.0;
	CString szMsg;
	szMsg.Format(_T("[GetXYTAlign_CalibPosXY_%d] In_Pos = %.5f, %.5f]"), nMappingID, *dPosX, *dPosY);
	Vision_Msg(szMsg);
#if 0
	dCalbY =  m_XYTAlignData[nMappingID].dOriginX - (sin(m_XYTAlignData[nMappingID].dRotAngle)*(*dPosX) + cos(m_XYTAlignData[nMappingID].dRotAngle)*(*dPosY));
	dCalbY = -dCalbY;
	dCalbX = cos(m_XYTAlignData[nMappingID].dRotAngle)*(*dPosX) - sin(m_XYTAlignData[nMappingID].dRotAngle)*(*dPosY) + m_XYTAlignData[nMappingID].dOriginY;
#else

	dCalbX = cos(m_XYTAlignData[nMappingID].dRotAngle)*(*dPosX) - sin(m_XYTAlignData[nMappingID].dRotAngle)*(*dPosY) + m_XYTAlignData[nMappingID].dOriginX;
	dCalbY = sin(m_XYTAlignData[nMappingID].dRotAngle)*(*dPosX) + cos(m_XYTAlignData[nMappingID].dRotAngle)*(*dPosY) + m_XYTAlignData[nMappingID].dOriginY ;
	

#endif
	//if (fabs(*dPosX - dCalbX) < 1.0 && fabs(*dPosY - dCalbY) < 1.0)
	if (fabs(*dPosX - dCalbX) < 2.0 && fabs(*dPosY - dCalbY) < 2.0)
	{
		*dPosX = dCalbX;
		*dPosY = dCalbY;
	}

	Vision_Msg(_T("[GetXYTAlign_CalibPosXY_%d] Out_Pos = %.5f, %.5f]"), nMappingID, *dPosX, *dPosY);

	return TRUE;
}

void CMappingProc::MakeXYTAlignData(int nMappingID, double dCmdPointXY[4][2], double dActPointXY[4][2])
{
	double dPointXY[4][2] = { 0.0 };
	double dX = 0.0, dY = 0.0, dT = 0.0;
	DOUBLE dCenterPosX, dCenterPosY;
	double dPosErrorX = 0;
	double dPosErrorY = 0;
	DOUBLE dDistance = 0;
		
	m_XYTAlignData[nMappingID].dOriginX = 0.0;
	m_XYTAlignData[nMappingID].dOriginY = 0.0;
	m_XYTAlignData[nMappingID].dRotAngle = 0.0;

	Make2PointAlignData(nMappingID, 0, dCmdPointXY[0], dCmdPointXY[1], dActPointXY[0], dActPointXY[1], &dX, &dY, &dT);
	m_XYTAlignData[nMappingID].dOriginX += dX;
	m_XYTAlignData[nMappingID].dOriginY += dY;
	m_XYTAlignData[nMappingID].dRotAngle += dT;

	Make2PointAlignData(nMappingID, 1, dCmdPointXY[2], dCmdPointXY[1], dActPointXY[2], dActPointXY[1], &dX, &dY, &dT);
	m_XYTAlignData[nMappingID].dOriginX += dX;
	m_XYTAlignData[nMappingID].dOriginY += dY;
	m_XYTAlignData[nMappingID].dRotAngle += dT;

	Make2PointAlignData(nMappingID, 2, dCmdPointXY[3], dCmdPointXY[2], dActPointXY[3], dActPointXY[2], &dX, &dY, &dT);
	m_XYTAlignData[nMappingID].dOriginX += dX;
	m_XYTAlignData[nMappingID].dOriginY += dY;
	m_XYTAlignData[nMappingID].dRotAngle += dT;

	Make2PointAlignData(nMappingID, 3, dCmdPointXY[3], dCmdPointXY[0], dActPointXY[3], dActPointXY[0], &dX, &dY, &dT);
	m_XYTAlignData[nMappingID].dOriginX += dX;
	m_XYTAlignData[nMappingID].dOriginY += dY;
	m_XYTAlignData[nMappingID].dRotAngle += dT;
	

	m_XYTAlignData[nMappingID].dOriginX /= 4.0;
	m_XYTAlignData[nMappingID].dOriginY /= 4.0;
	m_XYTAlignData[nMappingID].dRotAngle /= 4.0;

	//DO NOT USE!!
	//---
	//dCenterPosX = (dCmdPointXY[0][0] + dCmdPointXY[1][0] + dCmdPointXY[2][0] + dCmdPointXY[3][0]) * 0.25;
	//dCenterPosY = (dCmdPointXY[0][1] + dCmdPointXY[1][1] + dCmdPointXY[2][1] + dCmdPointXY[3][1]) * 0.25;

	//dDistance = sqrt((dCenterPosX * dCenterPosX + dCenterPosY * dCenterPosY));

	//dPosErrorX = dDistance * sin(dT);
	//dPosErrorY = dPosErrorX * tan(dT / 2);

	//if (dCenterPosY < 0)
	//{
	//	dPosErrorX *= (-1);
	//	dPosErrorY *= (-1);
	//}
	////---
	//m_XYTAlignData[nMappingID].dOriginX += dPosErrorX;
	//m_XYTAlignData[nMappingID].dOriginY += dPosErrorY;

	Vision_Msg(_T("[MakeXYTAlignData_%d] XYT = %.5f, %.5f, %.5f]"), nMappingID, m_XYTAlignData[nMappingID].dOriginX, m_XYTAlignData[nMappingID].dOriginY, m_XYTAlignData[nMappingID].dRotAngle*TO_DEGREE);
}


void CMappingProc::Make2PointVertiXYTAlignData(int nMappingID, double dCmdPointXY[2][2], double dActPointXY[2][2])
{
	double dPointXY[4][2] = { 0.0 };
	double dX = 0.0, dY = 0.0, dT = 0.0;
	DOUBLE dCenterPosX, dCenterPosY;
	double dPosErrorX = 0;
	double dPosErrorY = 0;
	DOUBLE dDistance = 0;
	
	m_XYTAlignData[nMappingID].dOriginX = 0.0;
	m_XYTAlignData[nMappingID].dOriginY = 0.0;
	m_XYTAlignData[nMappingID].dRotAngle = 0.0;

	Make2PointAlignData(nMappingID, 0, dCmdPointXY[1], dCmdPointXY[0], dActPointXY[1], dActPointXY[0], &dX, &dY, &dT);
	
	m_XYTAlignData[nMappingID].dOriginX += dX;
	m_XYTAlignData[nMappingID].dOriginY += dY;
	m_XYTAlignData[nMappingID].dRotAngle += dT;
	
	//DO NOT USE!!
	//dCenterPosX = ((dCmdPointXY[1][0] + dCmdPointXY[0][0]) * 0.5);
	//dCenterPosY = ((dCmdPointXY[1][1] + dCmdPointXY[0][1]) * 0.5);

	//dDistance = sqrt((dCenterPosX * dCenterPosX + dCenterPosY * dCenterPosY));

	//dPosErrorY = dDistance * sin(dT);
	//dPosErrorX = dPosErrorY * tan(dT / 2);

	//if (dCenterPosX > 0)
	//{
	//	dPosErrorX *= (-1);
	//	dPosErrorY *= (-1);
	//}

	//m_XYTAlignData[nMappingID].dOriginX = dX + dPosErrorX;
	//m_XYTAlignData[nMappingID].dOriginY = dY + dPosErrorY;
	//m_XYTAlignData[nMappingID].dRotAngle = dT;

	Vision_Msg(_T("[MakeXYTAlignData_%d] XYT = %.5f, %.5f, %.5f]"), nMappingID, m_XYTAlignData[nMappingID].dOriginX, m_XYTAlignData[nMappingID].dOriginY, m_XYTAlignData[nMappingID].dRotAngle*TO_DEGREE);
}

void CMappingProc::Make2PointHoriXYTAlignData(int nMappingID, double dCmdPointXY[2][2], double dActPointXY[2][2])
{
	double dPointXY[4][2] = { 0.0 };
	double dX = 0.0, dY = 0.0, dT = 0.0;
	DOUBLE dCenterPosX, dCenterPosY;

	double dPosErrorX = 0;
	double dPosErrorY = 0;
	DOUBLE dDistance = 0;

	m_XYTAlignData[nMappingID].dOriginX = 0.0;
	m_XYTAlignData[nMappingID].dOriginY = 0.0;
	m_XYTAlignData[nMappingID].dRotAngle = 0.0;

	Make2PointAlignData(nMappingID, 0, dCmdPointXY[0], dCmdPointXY[1], dActPointXY[0], dActPointXY[1], &dX, &dY, &dT);

	m_XYTAlignData[nMappingID].dOriginX = dX;
	m_XYTAlignData[nMappingID].dOriginY = dY;
	m_XYTAlignData[nMappingID].dRotAngle = dT;

	//DO NOT USE!!
	//dCenterPosX = ((dCmdPointXY[1][0] + dCmdPointXY[0][0]) * 0.5);
	//dCenterPosY = ((dCmdPointXY[1][1] + dCmdPointXY[0][1]) * 0.5);

	//dDistance = sqrt((dCenterPosX * dCenterPosX + dCenterPosY * dCenterPosY));

	//dPosErrorX = dDistance * sin(dT);
	//dPosErrorY = dPosErrorX * tan(dT / 2);

	//if (dCenterPosY < 0)
	//{
	//	dPosErrorX *= (-1);
	//	dPosErrorY *= (-1);
	//}

	//m_XYTAlignData[nMappingID].dOriginX = dX + dPosErrorX;
	//m_XYTAlignData[nMappingID].dOriginY = dY + dPosErrorY;
	//m_XYTAlignData[nMappingID].dRotAngle = dT;

	Vision_Msg(_T("[MakeXYTAlignData_%d] XYT = %.5f, %.5f, %.5f]"), nMappingID, m_XYTAlignData[nMappingID].dOriginX, m_XYTAlignData[nMappingID].dOriginY, m_XYTAlignData[nMappingID].dRotAngle*TO_DEGREE);
}

void CMappingProc::Make2PointAlignData(int nMappingID, int nNo, double dRefLeftXY[2], double dRefRightXY[2], double dObjLeftXY[2], double dObjRightXY[2], double *dX, double *dY, double *dT)
{
	double dRefXCenter = (dRefLeftXY[0] + dRefRightXY[0]) * 0.5;
	double dRefYCenter = (dRefLeftXY[1] + dRefRightXY[1]) * 0.5;
	double dObjXCenter = (dObjLeftXY[0] + dObjRightXY[0]) * 0.5;
	double dObjYCenter = (dObjLeftXY[1] + dObjRightXY[1]) * 0.5;

	*dX = dObjXCenter - dRefXCenter;
	*dY = dObjYCenter - dRefYCenter;

	//*dX = dObjLeftXY[0] - dRefLeftXY[0];
	//*dY = dObjLeftXY[1] - dRefLeftXY[1];
	//
	//*dX += dObjRightXY[0] - dRefRightXY[0];
	//*dY += dObjRightXY[1] - dRefRightXY[1];

	//*dX /= 2;
	//*dY /= 2;

	double dObjTilt = atan2((dObjRightXY[1] - dObjLeftXY[1]), (dObjRightXY[0] - dObjLeftXY[0]));
	double dRefTilt = atan2((dRefRightXY[1] - dRefLeftXY[1]), (dRefRightXY[0] - dRefLeftXY[0]));

	*dT = (dObjTilt - dRefTilt);
}

int CMappingProc::UnicodeToMultiByte(TCHAR *pSrc, CHAR *pDest, INT nLength/* = MAX_PATH*/)
{
	int nSize = 0;
	if (pSrc || pDest)
		nSize = ::WideCharToMultiByte(CP_ACP, 0, pSrc, -1, pDest, nLength, NULL, NULL);

	return nSize;
}



void CMappingProc::GetStandardDeviation(double *dX, double *dY, int nCnt, double *dResultX, double *dResultY)
{
	double dSumX = 0., dSumY = 0.;
	double dAverageX = 0., dAverageY = 0.;
	double dVarX = 0., dVarY = 0.;
	for (int i = 0; i < nCnt; i++)
	{
		dSumX += dX[i];
		dSumY += dY[i];
	}
	dAverageX = dSumX / nCnt;
	dAverageY = dSumY / nCnt;

	//Ç¥ÁØÆíÂ÷
	dSumX = 0;
	dSumY = 0;

	for (int i = 0; i < nCnt; i++)
	{
		dSumX += (dX[i] - dAverageX) * (dX[i] - dAverageX);
		dSumY += (dY[i] - dAverageY) * (dY[i] - dAverageY);
	}

	dVarX = sqrt(dSumX / nCnt);
	dVarY = sqrt(dSumY / nCnt);

	*dResultX = dVarX;
	*dResultY = dVarY;
}

BOOL CMappingProc::Get2PointMappingOffsetY(int nMappingID, double dBasePointX, double dOffsetPointX, double dPointY, double *dOffsetY)
{
	double dBasePositionX = dBasePointX;
	double dBasePositionY = dPointY;
	double dOffsetPositionX = dOffsetPointX;
	double dOffsetPositionY = dPointY;

	GetGlassMapping_CalibPosXY(nMappingID, &dBasePositionX, &dBasePositionY);
	GetGlassMapping_CalibPosXY(nMappingID, &dOffsetPositionX, &dOffsetPositionY);

	*dOffsetY = dOffsetPositionY - dBasePositionY;

	if (*dOffsetY > 1)
	{
		*dOffsetY = 0;
		return FALSE;
	}
	return TRUE;
}

BOOL CMappingProc::Get2PointSwAlignOffsetY(int nMappingID, double dBasePointX, double dOffsetPointX, double dPointY, double *dOffsetY)
{
	double dBasePositionX = dBasePointX;
	double dBasePositionY = dPointY;
	double dOffsetPositionX = dOffsetPointX;
	double dOffsetPositionY = dPointY;

	GetSWMapping_CalibPosXY(nMappingID, &dBasePositionX, &dBasePositionY);
	GetSWMapping_CalibPosXY(nMappingID, &dOffsetPositionX, &dOffsetPositionY);

	*dOffsetY = dOffsetPositionY - dBasePositionY;

	if (*dOffsetY > 1)
	{
		*dOffsetY = 0;
		return FALSE;
	}
	return TRUE;
}

BOOL CMappingProc::Get2PointXytAlignOffsetY(int nMappingID, double dBasePointX, double dOffsetPointX, double dPointY, double *dOffsetY)
{
	double dBasePositionX = dBasePointX;
	double dBasePositionY = dPointY;
	double dOffsetPositionX = dOffsetPointX;
	double dOffsetPositionY = dPointY;

	GetXYTAlign_CalibPosXY(nMappingID, &dBasePositionX, &dBasePositionY);
	GetXYTAlign_CalibPosXY(nMappingID, &dOffsetPositionX, &dOffsetPositionY);

	*dOffsetY = dOffsetPositionY - dBasePositionY;

	if (*dOffsetY > 1)
	{
		*dOffsetY = 0;
		return FALSE;
	}
	return TRUE;
}

