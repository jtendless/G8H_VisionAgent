#pragma once
#include "stdafx.h"
#include "Secs.h"
#include "../Module/Log/Logger.h"
//#include "stateManager.h"	//20171213 jinsnuk
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include <stdlib.h> 
#include <string.h>
#include <afxinet.h>

CSecs *CSecs::instance = NULL;
CSecs::CSecs()
{
}
CSecs::~CSecs()
{
}
CSecs* CSecs::Create()
{
	if (!instance)
	{
		instance = new CSecs;
	}

	return instance;
}
CSecs* CSecs::GetInstance()
{
	if (!instance)
	{
		instance = new CSecs;
	}

	return instance;
}
void CSecs::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}
//void CSecs::SecsInitialize()
//{
//	//USES_CONVERSION;
//	//CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//	//SecsInitialized = true;
//	//CString cstr;
//	//int i;
//	////20171213 jinsuk
//	////m_PORT
//	//for (i = 1; i <= PORT_COUNT; i++){
//	//	pDlg->m_PORT[i].ID[0] = i;
//	//	strcpy(pDlg->m_PORT[i].STATUS, "I");
//	//	strcpy(pDlg->m_PORT[i].STATE, "LR");
//	//}
//
//	////m_EQP
//	//strcpy(pDlg->m_EQP.STATUS, "I");
//
//	////m_LOT
//	//pDlg->m_LOT.MQTY[0] = 0;
//
//	////m_POSITION
//	//for (i = 0; i < POSITION_COUNT; i++){
//	//	pDlg->m_POSITION[i].ID[0] = i + 1;
//	//	strcpy(pDlg->m_POSITION[i].STICKID, "");
//	//}
//
//	//Total_Msg(_T(" Secs Parameter Initialized !"));
//}


////////======== ftp start ========
//int  CSecs::SaveTPDFile()
//{
//	CVisionAgentDlg *pDlg;
//	pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//
//	CStdioFile OutFile;
//	CString Str;
//	TCHAR tchPathName[256];
//
//	if (pDlg->m_TPD.m_nNo == 1)
//	{
//		if (OutFile.Open((LPCTSTR)tchPathName, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE) return 0;
//#ifdef _LGD_E6_IQC_
//		//아래 줄 바꾸지 말것
//		Str.Format(_T("`NO[C7CSTI0101]`,`MACHINEUNIT[C7CSTI0101]`,`TIME[C7CSTI0101]`,`LOTID[BODY01]`,`CSTID[BODY01]`,`PPID[BODY01]`,`STEP[BODY01]`,`PRCID[BODY01]`,`SLOTID[BODY01]`,`GLSID[BODY01]`,`EQPSTATUS[BODY01]`,`KEYID[BODY01]`,\
//`TEMP_1[BODY01]`,`TEMP_2[BODY01]`,`TEMP_3[BODY01]`,`TEMP_4[BODY01]`,`TEMP_5[BODY01]`,`TEMP_6[BODY01]`,`TEMP_7[BODY01]`,`TEMP_8[BODY01]`,`TEMP_9[BODY01]`,`TEMP_10[BODY01]`,`TEMP_11[BODY01]`,`TEMP_12[BODY01]`,\
//`GF_L01[BODY01]`,`GF_L02[BODY01]`,`GF_L03[BODY01]`,`GF_L04[BODY01]`,`GF_R01[BODY01]`,`GF_R02[BODY01]`,`GF_R03[BODY01]`,`GF_R04[BODY01]`,\
//`MAIN_CDA[BODY01]`,`MAIN_N2[BODY01]`,`MAIN_VAC[BODY01]`,\
//`MAIN_CENTERING_BASE[BODY01]`,`MAIN_CENTERING_PUSH[BODY01]`,`MAIN_BALL_UP[BODY01]`,`AIR_BEARING_MAIN[BODY01]`,`AIR_BEARING_SUB[BODY01]`,\
//`GANTRY_X11[BODY01]`,`GANTRY_X12[BODY01]`,`GANTRY_Y1[BODY01]`,`GANTRY_Y2[BODY01]`,\
//`ISOLATER_CH1[BODY01]`,`ISOLATER_CH2[BODY01]`,`ISOLATER_CH3[BODY01]`,`ISOLATER_MAIN[BODY01]`,\
//`GANTRY_X1_LF[BODY01]`,`GANTRY_Y1_LF[BODY01]`,`GANTRY_Y2_LF[BODY01]`,`GANTRY_RIGHT_ANGLE_CHECK[BODY01]`,\
//`GRIPPER_L1_SERVO_LF[BODY01]`,`GRIPPER_L2_SERVO_LF[BODY01]`,`GRIPPER_L3_SERVO_LF[BODY01]`,`GRIPPER_L4_SERVO_LF[BODY01]`,`GRIPPER_R1_SERVO_LF[BODY01]`,`GRIPPER_R2_SERVO_LF[BODY01]`,`GRIPPER_R3_SERVO_LF[BODY01]`,`GRIPPER_R4_SERVO_LF[BODY01]`,\
//`PITCH_L1_SERVO_LF[BODY01]`,`PITCH_L2_SERVO_LF[BODY01]`,`PITCH_L3_SERVO_LF[BODY01]`,`PITCH_L4_SERVO_LF[BODY01]`,`PITCH_R1_SERVO_LF[BODY01]`,`PITCH_R2_SERVO_LF[BODY01]`,`PITCH_R3_SERVO_LF[BODY01]`,`PITCH_R4_SERVO_LF[BODY01]`,\
//`BACK_LIGHT_X1_SERVO_LF[BODY01]`,`FRAME_Z_SERVO_LF[BODY01]`\n")); //0824 서종천 temp_1~12 를 1~7까지로 바꿈 (E61, 온도센서 7개)
//
//#else
//		//아래 줄 바꾸지 말것
//		Str.Format(_T("`NO[C5CSTI0101]`,`MACHINEUNIT[C5CSTI0101]`,`TIME[C5CSTI0101]`,`LOTID[BODY]`,`CSTID[BODY]`,`PPID[BODY]`,`STEP[BODY]`,`PRCID[BODY]`,`SLOTID[BODY]`,`GLSID[BODY]`,`EQPSTATUS[BODY]`,`KEYID[BODY]`,\
//					  					  `TEMP_1[BODY]`,`TEMP_2[BODY]`,`TEMP_3[BODY]`,`TEMP_4[BODY]`,`TEMP_5[BODY]`,`TEMP_6[BODY]`,`TEMP_7[BODY]`,`TEMP_8[BODY]`,`TEMP_9[BODY]`,`TEMP_10[BODY]`,`TEMP_11[BODY]`,`TEMP_12[BODY]`,\
//										  					  `GF_L01[BODY]`,`GF_L02[BODY]`,`GF_L03[BODY]`,`GF_L04[BODY]`,`GF_R01[BODY]`,`GF_R02[BODY]`,`GF_R03[BODY]`,`GF_R04[BODY]`,\
//															  					  `MAIN_CDA[BODY]`,`MAIN_N2[BODY]`,`MAIN_VAC[BODY]`,\
//																				  					  `MAIN_CENTERING_BASE[BODY]`,`MAIN_CENTERING_PUSH[BODY]`,`MAIN_BALL_UP[BODY]`,`AIR_BEARING_MAIN[BODY]`,`AIR_BEARING_SUB[BODY]`,\
//																									  					  `GANTRY_X11[BODY]`,`GANTRY_X12[BODY]`,`GANTRY_Y1[BODY]`,`GANTRY_Y2[BODY]`,\
//																														  					  `ISOLATER_CH1[BODY]`,`ISOLATER_CH2[BODY]`,`ISOLATER_CH3[BODY]`,`ISOLATER_MAIN[BODY]`,\
//																																			  					  `GANTRY_X1_LF[BODY]`,`GANTRY_Y1_LF[BODY]`,`GANTRY_Y2_LF[BODY]`,`GANTRY_RIGHT_ANGLE_CHECK[BODY]`,\
//																																								  					  `GRIPPER_L1_SERVO_LF[BODY]`,`GRIPPER_L2_SERVO_LF[BODY]`,`GRIPPER_L3_SERVO_LF[BODY]`,`GRIPPER_L4_SERVO_LF[BODY]`,`GRIPPER_R1_SERVO_LF[BODY]`,`GRIPPER_R2_SERVO_LF[BODY]`,`GRIPPER_R3_SERVO_LF[BODY]`,`GRIPPER_R4_SERVO_LF[BODY]`,\
//																																													  					  `PITCH_L1_SERVO_LF[BODY]`,`PITCH_L2_SERVO_LF[BODY]`,`PITCH_L3_SERVO_LF[BODY]`,`PITCH_L4_SERVO_LF[BODY]`,`PITCH_R1_SERVO_LF[BODY]`,`PITCH_R2_SERVO_LF[BODY]`,`PITCH_R3_SERVO_LF[BODY]`,`PITCH_R4_SERVO_LF[BODY]`,\
//																																																		  					  `BACK_LIGHT_X1_SERVO_LF`,`FRAME_Z_SERVO_LF`\n"));
//
//#endif
//
//		OutFile.WriteString(Str);
//	}
//	else
//	{
//		if (OutFile.Open((LPCTSTR)tchPathName, CFile::modeWrite | CFile::modeNoTruncate | CFile::typeText) == FALSE) return 0;
//
//		OutFile.SeekToEnd();
//	}
//
//
//#ifdef _LGD_E6_IQC_
//	//아래 줄 바꾸지 말것
//	Str.Format(_T("`%d`,`C7CSTI0101`,`%s`,`%s`,`%s`,`%s`,``,`%s`,`%s`,`%s`,``,``,\
//`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,\
//`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//`%.3f`,`%.3f`,`%.3f`,\
//`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//`%.3f`,`%.3f`\n"),
//	pDlg->m_TPD.m_nNo, pDlg->m_TPD.m_StrTime, pDlg->m_TPD.m_StrLOTID, pDlg->m_TPD.m_StrCSTID, pDlg->m_TPD.m_StrPPID, pDlg->m_TPD.m_StrPRCID, pDlg->m_TPD.m_StrSLOTID, pDlg->m_TPD.m_StrGLSID, \
//	pDlg->m_TPD.m_dTEMP[0], pDlg->m_TPD.m_dTEMP[1], pDlg->m_TPD.m_dTEMP[2], pDlg->m_TPD.m_dTEMP[3], pDlg->m_TPD.m_dTEMP[4], pDlg->m_TPD.m_dTEMP[5], pDlg->m_TPD.m_dTEMP[6], pDlg->m_TPD.m_dTEMP[7], pDlg->m_TPD.m_dTEMP[8], pDlg->m_TPD.m_dTEMP[9], pDlg->m_TPD.m_dTEMP[10], pDlg->m_TPD.m_dTEMP[11], \
//	pDlg->m_TPD.m_dGF_L01, pDlg->m_TPD.m_dGF_L02, pDlg->m_TPD.m_dGF_L03, pDlg->m_TPD.m_dGF_L04, pDlg->m_TPD.m_dGF_R01, pDlg->m_TPD.m_dGF_R02, pDlg->m_TPD.m_dGF_R03, pDlg->m_TPD.m_dGF_R04, \
//	pDlg->m_TPD.m_dMAIN_CDA, pDlg->m_TPD.m_dMAIN_N2, pDlg->m_TPD.m_dMAIN_VAC, \
//	pDlg->m_TPD.m_dMAIN_CENTERING_BASE, pDlg->m_TPD.m_dMAIN_CENTERING_PUSH, pDlg->m_TPD.m_dMAIN_BALL_UP, pDlg->m_TPD.m_dAIR_BEARING_MAIN, pDlg->m_TPD.m_dAIR_BEARING_SUB, \
//	pDlg->m_TPD.m_dGANTRY_X11, pDlg->m_TPD.m_dGANTRY_X12, pDlg->m_TPD.m_dGANTRY_Y1, pDlg->m_TPD.m_dGANTRY_Y2, \
//	pDlg->m_TPD.m_dISOLATER_CH1, pDlg->m_TPD.m_dISOLATER_CH2, pDlg->m_TPD.m_dISOLATER_CH3, pDlg->m_TPD.m_dISOLATER_MAIN, \
//	pDlg->m_TPD.m_dGANTRY_X1_LF, pDlg->m_TPD.m_dGANTRY_Y1_LF, pDlg->m_TPD.m_dGANTRY_Y2_LF, pDlg->m_TPD.m_dGANTRY_RIGHT_ANGLE_CHECK, \
//	pDlg->m_TPD.m_dGRIPPER_L1_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_L2_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_L3_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_L4_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_R1_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_R2_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_R3_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_R4_SERVO_LF, \
//	pDlg->m_TPD.m_dPITCH_L1_SERVO_LF, pDlg->m_TPD.m_dPITCH_L2_SERVO_LF, pDlg->m_TPD.m_dPITCH_L3_SERVO_LF, pDlg->m_TPD.m_dPITCH_L4_SERVO_LF, pDlg->m_TPD.m_dPITCH_R1_SERVO_LF, pDlg->m_TPD.m_dPITCH_R2_SERVO_LF, pDlg->m_TPD.m_dPITCH_R3_SERVO_LF, pDlg->m_TPD.m_dPITCH_R4_SERVO_LF, \
//	pDlg->m_TPD.m_dBACK_LIGHT_X1_SERVO_LF, pDlg->m_TPD.m_dFRAME_Z_SERVO_LF);
//
//#else
//	//아래 줄 바꾸지 말것
//	Str.Format(_T("`%d`,`C5CSTI0101`,`%s`,``,``,`%s`,``,``,``,`%s`,``,``,\
//				  				  `%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,`%.2f`,\
//								  				  `%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//												  				  `%.3f`,`%.3f`,`%.3f`,\
//																  				  `%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//																				  				  `%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//																								  				  `%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//																												  				  `%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//																																  				  `%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//																																				  				  `%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,`%.3f`,\
//																																								  				  `%.3f`,`%.3f`\n"), \
//																																												  pDlg->m_TPD.m_nNo, pDlg->m_TPD.m_StrTime, pDlg->m_TPD.m_StrPPID, pDlg->m_TPD.m_StrGLSID, \
//																																												  pDlg->m_TPD.m_dTEMP_1, pDlg->m_TPD.m_dTEMP_2, pDlg->m_TPD.m_dTEMP_3, pDlg->m_TPD.m_dTEMP_4, pDlg->m_TPD.m_dTEMP_5, pDlg->m_TPD.m_dTEMP_6, pDlg->m_TPD.m_dTEMP_7, pDlg->m_TPD.m_dTEMP_8, pDlg->m_TPD.m_dTEMP_9, pDlg->m_TPD.m_dTEMP_10, pDlg->m_TPD.m_dTEMP_11, pDlg->m_TPD.m_dTEMP_12, \
//																																												  pDlg->m_TPD.m_dGF_L01, pDlg->m_TPD.m_dGF_L02, pDlg->m_TPD.m_dGF_L03, pDlg->m_TPD.m_dGF_L04, pDlg->m_TPD.m_dGF_R01, pDlg->m_TPD.m_dGF_R02, pDlg->m_TPD.m_dGF_R03, pDlg->m_TPD.m_dGF_R04, \
//																																												  pDlg->m_TPD.m_dMAIN_CDA, pDlg->m_TPD.m_dMAIN_N2, pDlg->m_TPD.m_dMAIN_VAC, \
//																																												  pDlg->m_TPD.m_dMAIN_CENTERING_BASE, pDlg->m_TPD.m_dMAIN_CENTERING_PUSH, pDlg->m_TPD.m_dMAIN_BALL_UP, pDlg->m_TPD.m_dAIR_BEARING_MAIN, pDlg->m_TPD.m_dAIR_BEARING_SUB, \
//																																												  pDlg->m_TPD.m_dGANTRY_X11, pDlg->m_TPD.m_dGANTRY_X12, pDlg->m_TPD.m_dGANTRY_Y1, pDlg->m_TPD.m_dGANTRY_Y2, \
//																																												  pDlg->m_TPD.m_dISOLATER_CH1, pDlg->m_TPD.m_dISOLATER_CH2, pDlg->m_TPD.m_dISOLATER_CH3, pDlg->m_TPD.m_dISOLATER_MAIN, \
//																																												  pDlg->m_TPD.m_dGANTRY_X1_LF, pDlg->m_TPD.m_dGANTRY_Y1_LF, pDlg->m_TPD.m_dGANTRY_Y2_LF, pDlg->m_TPD.m_dGANTRY_RIGHT_ANGLE_CHECK, \
//																																												  pDlg->m_TPD.m_dGRIPPER_L1_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_L2_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_L3_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_L4_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_R1_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_R2_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_R3_SERVO_LF, pDlg->m_TPD.m_dGRIPPER_R4_SERVO_LF, \
//																																												  pDlg->m_TPD.m_dPITCH_L1_SERVO_LF, pDlg->m_TPD.m_dPITCH_L2_SERVO_LF, pDlg->m_TPD.m_dPITCH_L3_SERVO_LF, pDlg->m_TPD.m_dPITCH_L4_SERVO_LF, pDlg->m_TPD.m_dPITCH_R1_SERVO_LF, pDlg->m_TPD.m_dPITCH_R2_SERVO_LF, pDlg->m_TPD.m_dPITCH_R3_SERVO_LF, pDlg->m_TPD.m_dPITCH_R4_SERVO_LF, \
//																																												  pDlg->m_TPD.m_dBACK_LIGHT_X1_SERVO_LF, pDlg->m_TPD.m_dFRAME_Z_SERVO_LF);
//
//#endif
//
//	OutFile.WriteString(Str);
//
//	OutFile.Close();
//
//	if (pDlg->m_TPD.m_nNo == 60)
//	{
//		CString localpath;
//		CString serverpath;
//		CString filename;
//#ifdef _LGD_E6_IQC2_
//		wsprintf(tchPathName, _T("D:\\TPD\\C7CSTI0201_%s.TPD"), pDlg->m_TPD.m_StrFilePathName);
//#else
//		wsprintf(tchPathName, _T("D:\\TPD\\C7CSTI0101_%s.TPD"), pDlg->m_TPD.m_StrFilePathName);
//#endif
//
//		if (pDlg->m_bConnectFtp == TRUE)
//		{
//#ifdef _LGD_E6_IQC_
//			localpath.Format(_T("D:\\TPD"));
//	#ifdef _LGD_E6_IQC2_
//				filename.Format(_T("C7CSTI0201_%s.TPD"), pDlg->m_TPD.m_StrFilePathName);
//				//serverpath.Format(_T("/test/AA/BB"));
//				serverpath.Format(_T("/C7CSTI02"));
//	#else
//				filename.Format(_T("C7CSTI0101_%s.TPD"), pDlg->m_TPD.m_StrFilePathName);
//				//serverpath.Format(_T("/test/AA/BB"));
//				serverpath.Format(_T("/C7CSTI01"));
//	#endif
//#else
//			//예전 프로그램에서 E5 부분 넣어놓기 0207 서종천
//#endif
//			ftpPut(filename, localpath, serverpath);
//		}
//
//		::DeleteFile(tchPathName);
//	}
//
//
//	//Total_Msg(_T("SaveTPDFile : %s"), (LPCTSTR)tchPathName);
//
//	return 0;
//}

//void CSecs::ftpTest()
//{
//	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//
//	//ftpOpen();
//
//	CString localpath;
//	CString serverpath;
//
//	localpath.Format(_T("%s\\Data\\SECS"), pDlg->m_StrVisionAgentPath);
//	serverpath.Format(_T("/test/AA/BB"));
//	ftpPut(L"ftpsample.txt", localpath, serverpath);
//
//	//ftpClose();
//}
//void CSecs::ftpOpen()
//{
//#ifdef _LGD_E6_IQC_
//	CString ftpip = L"172.25.201.103";		//TPD SERVER
//	CString ftpid = L"ews_ftp01";
//	CString ftppw = L"Qwer123$";
//#else
//	CString ftpip = L"10.24.130.65";		//TPD SERVER
//	CString ftpid = L"ftpewse1";
//	CString ftppw = L"qhdks2009";
//#endif
//
//	//
//	CString str;
//
//	if (m_pSession == NULL || m_pFtpCon == NULL)
//	{
//		Total_Msg(_T(" Try FTP Server Connection ..."));
//	}
//	try
//	{
//		if (m_pSession == NULL)
//		{
//			m_pSession = new CInternetSession();
//			Total_Msg(_T(" FTP CInternetSession created "));
//		}
//		if (m_pFtpCon == NULL) {
//			m_pFtpCon = m_pSession->GetFtpConnection(ftpip, ftpid, ftppw, 21, false);
//			str.Format(_T(" FTP Server [%s] Connected "), ftpip);
//			Total_Msg(str);
//		}
//	}
//	catch (CInternetException* e)
//	{
//		e->ReportError();
//		e->Delete();
//		str.Format(_T(" FTP Server [%s] Connection Error"), ftpip);
//		Total_Msg(str);
//		Alarm_Msg(str);
//
//		ftpClose();
//	}
//}
//void CSecs::ftpClose()
//{
//	if (m_pSession != NULL){
//		m_pSession->Close();
//		delete m_pSession;
//		m_pSession = NULL;
//		Total_Msg(_T(" Ftp Session Closed "));
//
//	}
//	if (m_pFtpCon != NULL){
//		m_pFtpCon->Close();
//		delete m_pFtpCon;
//		m_pFtpCon = NULL;
//		Total_Msg(_T(" Ftp Closed "));
//	}
//
//	if (m_pFileFind != NULL)
//		delete[] m_pFileFind;
//}
//void CSecs::ftpPut(CString filename, CString localpath, CString serverpath)
//{
//	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//
//	CString strTargetFile, strLocalFile, strDir;
//	int nPos, nPosfind;
//
//	if (m_pFtpCon)
//	{
//		if (!m_pFileFind)
//			m_pFileFind = new CFtpFileFind(m_pFtpCon);
//
//		CFtpFileFind finder(m_pFtpCon);
//
//		if (!finder.FindFile((LPCTSTR)serverpath))	// 폴더 못찾으면 생성
//		{
//			nPos = 2;
//			do
//			{
//				nPosfind = serverpath.Find(L"/", nPos);
//				strDir = serverpath.Left(nPosfind);
//				if (nPosfind>0) strDir = serverpath.Left(nPosfind);
//				else strDir = serverpath;
//				nPos = nPosfind + 1;
//
//				//Total_Msg(_T(" check Dir : %s "), strDir);
//				if (!m_pFtpCon->SetCurrentDirectory(strDir)) //실패하면(없으면)
//				{
//					if (m_pFtpCon->CreateDirectory(strDir))
//					{
//						Total_Msg(_T(" Server CreateDirectory [%s] Success"), strDir);
//					}
//					else
//					{
//						Total_Msg(_T(" Server CreateDirectory [%s] Fail"), strDir);
//						Alarm_Msg(_T(" Server CreateDirectory [%s] Fail"), strDir);
//					}
//				}
//			} while (nPosfind > 0);
//		}
//
//		strLocalFile.Format(_T("%s\\%s"), localpath, filename);
//		strTargetFile.Format(_T("%s/%s"), serverpath, filename);
//
//		try
//		{
//			if (m_pFtpCon->PutFile(strLocalFile, strTargetFile)) // 업로드
//			{
//				Total_Msg(_T(" Ftp Put [%s]"), strTargetFile);
//			}
//			else
//			{
//				Total_Msg(_T(" Failure.. Ftp Put [%s]"), strLocalFile);
//				Alarm_Msg(_T(" Failure.. Ftp Put [%s]"), strLocalFile);
//			}
//		}
//		catch (CInternetException* e)
//		{
//			Total_Msg(_T(" Ftp Upload Error!"));
//			Alarm_Msg(_T(" Ftp Upload Error!"));
//			e->ReportError();
//			e->Delete();
//		}
//	}
//	else {
//		Total_Msg(_T(" Ftp Server Not Connected !"));
//		Alarm_Msg(_T(" Ftp Server Not Connected !"));
//	}
//}
////////======== ftp end ========

void CSecs::Start()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

#if defined(SIM_MODE)
	nReturn = 0;
#else
	//  Start the XCom1 control
	nReturn = pDlg->m_XComPro.Start();
#endif

	if (nReturn == 0) {
		pDlg->m_XcomStarted = true;
		Total_Msg(_T("SECS XComPro started successfully"));
	}
	else {
		Total_Msg(_T("SECS XComPro start Failure : %d"), nReturn);
		Alarm_Msg(_T("SECS XComPro start Failure : %d"), nReturn);
	}


}
void CSecs::Stop()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	// Stop the XCom control
	pDlg->m_XComPro.Stop();
	pDlg->m_XcomStarted = false;
	Total_Msg(_T("SECS XComPro Stopped"));
}




//void CSecs::Pkg_E6_AreYouThere()
//{
//	if (PackageStep == 1) {
//		RecvFlag[1][2] = FALSE;
//		S1F1(); PackageStep = 2;
//	}
//	else if (PackageStep == 2 && RecvFlag[1][2]) {
//		PackageStep = 0;
//	}
//}
//void CSecs::Pkg_E6_EcsRestart()
//{
//	USES_CONVERSION;
//	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//	CString state;
//	if (PackageStep == 1) { S1F1();  PackageStep++; }   //Are You There
//	else if (PackageStep == 2 && RecvFlag[1][2]) {
//		strcpy(pDlg->m_EQP.STATE, "0"); //0=online remote
//		RecvFlag[2][62] = FALSE;
//		S2F61();  PackageStep++;   //Control State Report
//	}
//	else if (PackageStep == 3 && RecvFlag[2][62]) { RecvFlag[2][64] = FALSE;  S2F63();  PackageStep++; }  //Equipment Operation Mode Report
//	else if (PackageStep == 4 && RecvFlag[2][64]) { RecvFlag[2][18] = FALSE;  S2F17();  PackageStep++; }  //Date and Time Request
//	else if (PackageStep == 5 && RecvFlag[2][18]) { RecvFlag[1][86] = FALSE;  S1F85();  PackageStep++; }	// port id 1, idle, id 2 idle
//	else if (PackageStep == 6 && RecvFlag[1][86]) { 
//		RecvFlag[1][84] = FALSE; 
//		int nPort = pDlg->m_EQP.PORTID[0];
//		state = "UC";
//		pDlg->m_PORT[nPort].ID[0] = 1;
//		strcpy(pDlg->m_PORT[nPort].STATE ,W2A(state));
//		S1F83();
//		pDlg->m_PORT[nPort].ID[0] = 2;
//		S1F83();
//		PackageStep++; 
//	}
//	else if (PackageStep == 7 && RecvFlag[1][84]) { RecvFlag[1][62] = FALSE;  S1F61();  PackageStep++; }  //All Equipment Status Data Report
//	else if (PackageStep == 8 && RecvFlag[1][62]) { RecvFlag[1][92] = FALSE;  S1F91();  PackageStep++; }  //All Glass Position Data Report
//	else if (PackageStep == 9 && RecvFlag[1][92]) { 
//		RecvFlag[1][84] = FALSE;
//		int nPort = pDlg->m_EQP.PORTID[0];
//		state = "LR";
//		pDlg->m_PORT[nPort].ID[0] = 1;
//		strcpy(pDlg->m_PORT[nPort].STATE, W2A(state));
//		S1F83();
//		pDlg->m_PORT[nPort].ID[0] = 2;
//		S1F83();
//		PackageStep++;
//	} 
//	else if (PackageStep == 10 && RecvFlag[1][84]){ PackageStep = 0; } // 끝
//
//
//}

void CSecs::LogSecsMsg(CString strFunc, CString strMsg)
{
	if (bLogWrite) Total_Msg(strMsg);
}
static CString BinaryString(BYTE * bString, long lSize)
{
	CString cstring = L"";
	char stemp[6];
	for (long i = 0; i < lSize; i++) {
		sprintf(stemp, " %02x", bString[i]);
		cstring += stemp;
	}
	return  cstring;
}
long CSecs::XcomMake(long * lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;

	//if (!SecsInitialized) SecsInitialize();		//파라메타 초기화

	if (!pDlg->m_XcomInitialized)
	{
		Total_Msg(_T("SECS: [Warning] Cannot send xcom message because HSMS is not selected yet"));
		Alarm_Msg(_T("SECS: [Warning] Cannot send xcom message because HSMS is not selected yet"));
		return 1;
	}
	//nReturn = pDlg->m_XComPro.MakeSecsMsg((long *)lMsgId, nDevId, nStrm, nFunc, 0);	//20180109 jinsuk수정
	nReturn = pDlg->m_XComPro.MakeSecsMsg((long *)lMsgId, nDevId, nStrm, nFunc, lSysByte);	//20180109 jinsuk수정
	if (!nReturn) {
		sMsg.Format(_T("  Make Message S%dF%d "), nStrm, nFunc);
		LogSecsMsg(L"Make", sMsg);
	}
	else
	{
		Total_Msg(_T("  Make Message failed (error=%d"), nReturn);
		Alarm_Msg(_T("  Make Message failed (error=%d"), nReturn);
	}
	return nReturn;
}
void CSecs::XcomSend(long lMsgId, short nStrm, short nFunc)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;

	nReturn = pDlg->m_XComPro.Send(lMsgId);
	if (nReturn == 0) {
		sMsg.Format(_T("  ==Send[S%dF%d]=="), nStrm, nFunc);
		LogSecsMsg(L"Send", sMsg);
	}
	else {
		Total_Msg(_T("  ==Send[S%dF%d] failed (error=%d)== "), nStrm, nFunc, nReturn);
		Alarm_Msg(_T("  ==Send[S%dF%d] failed (error=%d)== "), nStrm, nFunc, nReturn);
	}
	sendSFmsg.Format(_T("S%dF%d"), nStrm, nFunc);	//최근메시지 갱신
}
void CSecs::XcomReply(long lMsgId, short nStrm, short nFunc)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;

	nReturn = pDlg->m_XComPro.Send(lMsgId);
	if (nReturn == 0) {
		sMsg.Format(_T("  ==Reply[S%dF%d]== "), nStrm, nFunc);
		LogSecsMsg(L"Reply", sMsg);
	}
	else {
		Total_Msg(_T("  ==Reply[S%dF%d] failed (error=%d)=="), nStrm, nFunc, nReturn);
		Alarm_Msg(_T("  ==Reply[S%dF%d] failed (error=%d)=="), nStrm, nFunc, nReturn);
	}
	sendSFmsg.Format(_T("S%dF%d"), nStrm, nFunc);	//최근메시지 갱신
}
void CSecs::XcomAck(CString strAck)
{
	LogSecsMsg(L"Ack", strAck);
}
long CSecs::XcomAscii(long lMsgId, CString str, long lCount)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	USES_CONVERSION;
	int i;
	CString sMsg;
	int nlen = str.GetLength();
	char* pstr = W2A(str.GetBuffer(nlen));
	for (i = 0; i < nlen; i++) buffer[i] = pstr[i];
	for (i = nlen; i < lCount; i++) buffer[i] = ' ';
	buffer[lCount] = NULL;
	nReturn = pDlg->m_XComPro.SetAsciiItem(lMsgId, (signed char*)buffer, lCount);
	sMsg.Format(_T("   SetAscii [%s] :%d "), str, lCount, nReturn);
	LogSecsMsg(L"Body", sMsg);

	return nReturn;
}
long CSecs::XcomAscii(long lMsgId, char* str, long lCount)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	USES_CONVERSION;
	CString sMsg, cstr = A2W(str);
	int i;
	int nlen = (int)strlen(str);
	for (i = 0; i < nlen; i++) buffer[i] = str[i];
	for (i = nlen; i < lCount; i++) buffer[i] = ' ';
	buffer[lCount] = NULL;
	nReturn = pDlg->m_XComPro.SetAsciiItem(lMsgId, (signed char*)buffer, lCount);
	sMsg.Format(_T("   SetAscii [%s] :%d "), cstr, lCount, nReturn);
	LogSecsMsg(L"Body", sMsg);
	return nReturn;
}
long CSecs::XcomAscii(long lMsgId, float fnum, long lCount)
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int i;
	CString sMsg;
	char* str = _gcvt(fnum, lCount, buffer);
	int nlen = (int)strlen(str);
	for (i = nlen; i < lCount; i++) buffer[i] = ' ';
	buffer[lCount] = NULL;
	nReturn = pDlg->m_XComPro.SetAsciiItem(lMsgId, (signed char*)buffer, lCount);
	sMsg.Format(_T("   SetAscii [%s] :%d "), A2W(buffer), lCount, nReturn);
	LogSecsMsg(L"Body", sMsg);
	return nReturn;
}
long CSecs::XcomBinary(long lMsgId, unsigned char* puValue, long lCount)
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg, cstr;

	nReturn = pDlg->m_XComPro.SetBinaryItem(lMsgId, puValue, lCount);
	cstr = BinaryString(puValue, lCount);
	sMsg.Format(_T("   SetBinary [%s] :%d "), cstr, nReturn);
	LogSecsMsg(L"Body", sMsg);
	return nReturn;
}
long CSecs::XcomU2(long lMsgId, unsigned short * plValue, long lCount)
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;
	nReturn = pDlg->m_XComPro.SetU2Item(lMsgId, plValue, lCount);
	sMsg.Format(_T("   SetU2 [%d] :%d"), *plValue, nReturn);
	LogSecsMsg(L"Body", sMsg);
	return nReturn;
}
long CSecs::XcomList(long lMsgId, long nItems)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;
	nReturn = pDlg->m_XComPro.SetListItem(lMsgId, nItems);
	sMsg.Format(_T("   SetList [%d] :%d"), nItems, nReturn);
	LogSecsMsg(L"List", sMsg);
	return nReturn;
}
long CSecs::XcomGetList(long lMsgId, long * pnItems)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;

	nReturn = pDlg->m_XComPro.GetListItem(lMsgId, pnItems);
	sMsg.Format(_T("   GetList [%d] :%d"), *pnItems, nReturn);
	LogSecsMsg(L"List", sMsg);
	return nReturn;
}
long CSecs::XcomGetAscii(long lMsgId, char * pszValue, long * plCount, long lSize)
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;

	nReturn = pDlg->m_XComPro.GetAsciiItem(lMsgId, (signed char*)pszValue, plCount, lSize);
	sMsg.Format(_T("   GetAscii [%s] :%d"), A2W(pszValue), nReturn);
	LogSecsMsg(L"Body", sMsg);
	return nReturn;
}
long CSecs::XcomGetU2(long lMsgId, unsigned short * plValue, long * plCount, long lSize)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;

	nReturn = pDlg->m_XComPro.GetU2Item(lMsgId, plValue, plCount, lSize);
	sMsg.Format(_T("   GetU2 [%d] :%d"), *plValue, nReturn);
	LogSecsMsg(L"Body", sMsg);
	return nReturn;
}
long CSecs::XcomGetBinary(long lMsgId, unsigned char * pnValue, long * plCount, long lSize)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg, cstr = L"";
	char stemp[6];
	nReturn = pDlg->m_XComPro.GetBinaryItem(lMsgId, pnValue, plCount, lSize);
	for (long i = 0; i < *plCount; i++) {
		sprintf(stemp, " %02x", pnValue[i]);
		cstr += stemp;
	}
	sMsg.Format(_T("   GetBinary [%s] :%d"), cstr, nReturn);
	LogSecsMsg(L"Body", sMsg);
	return nReturn;
}
void CSecs::XcomMsgClose(long lMsgId)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString sMsg;
	pDlg->m_XComPro.CloseSecsMsg(lMsgId);
	sMsg.Format(_T("  Close Message"));
	LogSecsMsg(L"Close", sMsg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CSecs::SFAllClear()
{
	for (int i = 0; i <= 15; i++)
		for (int j = 0; j <= 99; i++)
			RecvFlag[i][j] = FALSE;
}

void CSecs::SFClear(short nStrm, short nFunc)
{
	RecvFlag[nStrm][nFunc] = FALSE;
}

////S1F93명령받았을때
//void CSecs::RecvHostCommand()
//{
//	USES_CONVERSION;
//	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//	CString strcmd;
//
//	strcmd = A2W(pDlg->m_ECSMSG.RCMD);
//	strcmd.Trim();
//
//	if (pDlg->m_PORT[nLoadPort].STATUS[0] == 'R') {	//LoadPort에 올렸을때만
//		if (strcmd == "START") {
//			EqpEvent(L"ProcessStart");
//		}
//		else if (strcmd == "CANCEL") {
//			EqpEvent(L"ProcessCancel");
//		}
//	}
//	else  //LoadPort 비었을 때 (unloadport일때)
//	{
//		if (pDlg->m_PORT[nUnloadPort].STATUS[0] == 'R') {	//LoadPort에 올렸을때만
//			if (strcmd == "START") {
//				EqpEvent(L"BoxUnloadOut");
//			}
//			else if (strcmd == "CANCEL") {
//				//-------미정의-------
//			}
//		}
//	}
//}

////MES로부터 수신한 Lot정보(recipe, 각stickid, qty,..)를 설비에 반영
//void CSecs::ApplyLSD()
//{
//	USES_CONVERSION;
//	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//	int i, j, k, stickNo;
//	CString sItem, sValue, s1, s2;
//	CString strRecipe, strTemp;;
//	
//	//Stick 수량
//	//pStateManager->SetMaskPaperCount(3);	//Paper 수량
//	pStateManager->SetSlotCount(7);		//Slot  수량
//	pStateManager->SetMaskNo(0);			//Stick No = 0
//	pStateManager->SetMaskPaperNo(0);		//Paper No = 0
//
//	Total_Msg(_T("Apply_LSD num=[%d]"), pDlg->m_LOT.NUMLSD);
//
//	//각 SLOT의 STICKID, STICKNO
//	for (i = 0, j = 0; i < pDlg->m_LOT.NUMLSD; i++)
//	{
//		sItem = A2W(pDlg->m_LSD[i].ITEM);
//		sValue = A2W(pDlg->m_LSD[i].VALUE);
//		AfxExtractSubString(s1, sItem, 0, _T('_'));
//		AfxExtractSubString(s2, sItem, 1, _T('_'));
//		if (s1.Left(3) == L"FMM") {
//
//			for (k = 0; k < s2.GetLength(); k++) {
//				if (s2[k] == ' ') {
//					s2 = s2.Left(k); break;
//				}
//			}
//			for (k = 0; k < sValue.GetLength(); k++) {
//				if (sValue[k] == ' ') {
//					sValue = sValue.Left(k); break;
//				}
//			}
//			stickNo = _tstoi((LPTSTR)(LPCTSTR)s2);
//
//			//if (s1.GetLength() > 0) sprintf(pDlg->m_SLOT[j].STICKID, W2A(sValue));
//
//			if (s1.GetLength() > 0)
//			{
//				pDlg->m_SLOT[j].INTSITCKID = _tstoi((LPTSTR)(LPCTSTR)sValue.Right(2));; //0704 서종천
//				sprintf(pDlg->m_SLOT[j].STICKID, W2A(sValue));
//			}
//			if (s2.GetLength() > 0) sprintf(pDlg->m_SLOT[j].STICKNO, W2A(s2));
//
//			//sunghaklee:2018.06.08
//
//			if (nUnloadPort == 2)
//			//if (j % 2 == 0)
//			{
//				sprintf(pDlg->m_SLOT[j].STICKJUDGE, "G");
//			}
//			else
//			{
//				sprintf(pDlg->m_SLOT[j].STICKJUDGE, "N");
//			}
//
//			Total_Msg(_T("  LSD [%d][%s][%s]"), j, s2, sValue);
//
//			j++;
//		}
//		//Total_Msg(_T("Apply_LSD [%d][%s][%s]"), j-1,s2, sValue);
//		pDlg->nNumStick = j;
//	}
//	char temp1[10][30];
//	char temp2[10][30];
//	for (int i = 0; i < pDlg->nNumStick; i++){
//		//strcpy(temp1[i], pDlg->m_SLOT[i].STICKID);
//		//strcpy(temp2[i], pDlg->m_SLOT[i].STICKNO);
//		strcpy(temp1[i], pDlg->m_SLOT[pDlg->m_SLOT[i].INTSITCKID].STICKID);
//		strcpy(temp2[i], pDlg->m_SLOT[pDlg->m_SLOT[i].INTSITCKID].STICKNO);
//	}
//	for (int i = 0; i < pDlg->nNumStick; i++){
//		strcpy(pDlg->m_SLOT[i].STICKID, temp1[pDlg->nNumStick -1 - i]);
//		strcpy(pDlg->m_SLOT[i].STICKNO, temp2[pDlg->nNumStick-1 - i]);
//
//		//pDlg->m_BoxInfo.m_StrStickID[i] = A2W(pDlg->m_SLOT[i].STICKID); 임시 삭제 필요시 추가
//	}
//	
//	////RECIPE
//	//strRecipe = A2W(pDlg->m_LOT.RECIPE);
//	//if (pDlg->MES_SetRecipe(strRecipe)) {
//	//	strTemp.Format(_T("Warning! Recipe[%s] Para File Not Found!"), strRecipe);
//	//	AfxMessageBox(strTemp);
//	//}
//
//	////참고, 받은LOT정보
//	//XcomGetAscii(lMsgId, pDlg->m_LOT.MLOTKIND, &lSize, 8);
//	//XcomGetAscii(lMsgId, pDlg->m_LOT.MCSTID, &lSize, 20);
//	//XcomGetAscii(lMsgId, pDlg->m_LOT.MLOTID, &lSize, 30);
//	//XcomGetAscii(lMsgId, pDlg->m_LOT.CMD, &lSize, 6);
//	//XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 8);
//}
//
////STICK별 결과(STICKJUDGE)를 LSD에 반영
//void CSecs::Put_LSD()
//{
//	USES_CONVERSION;
//	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//	int i, j, k, stickNo;
//	CString sItem, sValue, s1, s2;
//	CString strRecipe, strTemp;;
//
//	pDlg->m_LOT.NUMLSD = pDlg->m_LOT.MQTY[0];
//
//	for (i = 0; i < pDlg->m_LOT.MQTY[0]; i++)
//	{
//		sprintf(pDlg->m_LSD[i].ITEM, "FMM_%s", pDlg->m_SLOT[i].STICKNO);
//		sprintf(pDlg->m_LSD[i].VALUE, "%s_%s_%s_Y", pDlg->m_SLOT[i].STICKID, pDlg->m_SLOT[i].STICKNO, pDlg->m_SLOT[i].STICKJUDGE);
//	}
//	//각 SLOT의 STICKID, STICKNO
//	for (i = 0, j = 0; i < pDlg->m_LOT.NUMLSD; i++)
//	{
//		sItem = A2W(pDlg->m_LSD[i].ITEM);
//		sValue = A2W(pDlg->m_LSD[i].VALUE);
//		AfxExtractSubString(s1, sItem, 0, _T('_'));
//		AfxExtractSubString(s2, sItem, 1, _T('_'));
//		if (s1.Left(3) == L"FMM") {
//
//			for (k = 0; k < s2.GetLength(); k++) {
//				if (s2[k] == ' ') {
//					s2 = s2.Left(k); break;
//				}
//			}
//			sprintf(pDlg->m_LSD[i].VALUE, "%s_%s_%s_Y", pDlg->m_SLOT[j].STICKID, pDlg->m_SLOT[j].STICKNO, pDlg->m_SLOT[j].STICKJUDGE);
//			j++;
//		}
//	}
//}

//APD StickParameter update
void CSecs::SetAPDStickParameter()
{
	return;
	//USES_CONVERSION;
	//CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	//int nCellCountX = pDlg->m_ModelParaData.m_NewStickInfo.m_nCellCountXY[0];
	//int nDivCountXY = pDlg->m_InspectParaData.m_NewStickInfo.m_nDivCountXY; //2X2, 3X3, 5X5

	//int nDivXY = 2;
	//if (nDivCountXY == 1) nDivXY = 3;
	//if (nDivCountXY == 2) nDivXY = 5;

	//int i;
	//int nSlotNo = pStateManager->GetMaskNo();

	//sprintf(pDlg->m_APD.STICKID, pDlg->m_SLOT[nSlotNo].STICKID);
	//sprintf(pDlg->m_APD.STICK_JUDGE, pDlg->m_SLOT[nSlotNo].GLSJUDGE);
	//sprintf(pDlg->m_APD.STRAIGHT, "");
	//sprintf(pDlg->m_APD.STICK_NG_CNT, "");
	//sprintf(pDlg->m_APD.FINE_KEY_ALIGN_X, "");
	//sprintf(pDlg->m_APD.FINE_KEY_ALIGN_Y, "");
	//sprintf(pDlg->m_APD.FINE_KEY_ALIGN_T, "");

	//for (i = 1; i <= 15; i++) {
	//	sprintf(pDlg->m_APD.LTP[i], "");
	//}
	//for (i = 1; i <= 40; i++) {
	//	sprintf(pDlg->m_APD.STP[i], "");
	//}
	//for (i = 1; i <= 4; i++) {
	//	sprintf(pDlg->m_APD.TF_LC[i], "");
	//}
	//for (i = 1; i <= 4; i++) {
	//	sprintf(pDlg->m_APD.TF_RC[i], "");
	//}

	//pDlg->m_APD.NUMPPA = 20 + (14 * nCellCountX * nDivXY * nDivXY); //Summary=20, 한포인트당 있는 파라미터 개수(14)*Cell수 * x분할수 * y분할수
}

//--Xcom에 LSD 기록
void  CSecs::XcomWriteLSD()
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	//XcomList(lMsgId, pDlg->m_LOT.NUMLSD);
	//for (int i = 0; i < pDlg->m_LOT.NUMLSD; i++)
	//{
	//	XcomList(lMsgId, 2);
	//	XcomAscii(lMsgId, pDlg->m_LSD[i].ITEM, 24);
	//	XcomAscii(lMsgId, pDlg->m_LSD[i].VALUE, 160);
	//}
	//test 용 값입력
	char item[2][2] = { {"1"} ,{"2"} };
	char value[2][2] = { {"3"} ,{"4"} };

	XcomList(lMsgId, 0);
	//for (int i = 0; i < 2; i++)
	//{
	//	XcomList(lMsgId, 2);
	//	XcomAscii(lMsgId, item[i], 24);
	//	XcomAscii(lMsgId, value[i], 160);
	//}
}
//--Xcom에 APD 기록
void CSecs::XcomWriteAPD()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	char str[40];
	int nCount;
	//
	SetAPDStickParameter();

	//nCount = (nCount * 4)*4 * 2;//TP 찍은 갯수 * 4 (X,Y,dx,dy) * 2(일반, 인장)
	////APD Parameter 총 갯수
	//pDlg->m_APD.NUMAPD = pDlg->m_APD.NUMSTICKINFO + pDlg->m_APD.NUMPPA + pDlg->m_APD.NUMAOI + pDlg->m_APD.NUM3D + 5 + nCount;//5는 장비정보(머신명,라인,등)
	//Total_Msg(_T("%d, %d, %d, %d"), pDlg->m_APD.NUMSTICKINFO , pDlg->m_APD.NUMPPA , pDlg->m_APD.NUMAOI , pDlg->m_APD.NUM3D);

	XcomList(lMsgId, 2); 
	//임시 추가
	//XcomList(lMsgId, 219);
	
	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "Test", 40);
	XcomAscii(lMsgId, "Test2", 40);
	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "Test3", 40);
	XcomAscii(lMsgId, "Test4", 40);


	//XcomWriteStickParameter();
	//XcomWriteMeasureParameter();
	//XcomWrite_InspectData();
}

void  CSecs::XcomWriteParam(char* strItem, char* strValue)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, strItem, 40);
	XcomAscii(lMsgId, strValue, 40);

}
void  CSecs::XcomWriteParam(char* strItem, float fValue)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	char strTemp[40];
	sprintf(strTemp, "%.5f", fValue);
	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, strItem, 40);
	XcomAscii(lMsgId, strTemp, 40);

}

//--Xcom에 스틱정보 기록
void CSecs::XcomWriteStickParameter()
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int i;
	char strTemp[40];

	/*XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "STICKID", 40);
	XcomAscii(lMsgId, pDlg->m_APD.STICKID, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "STICK_JUDGE", 40);
	XcomAscii(lMsgId, pDlg->m_APD.STICK_JUDGE, 40);
	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "STRAIGHT", 40);
	XcomAscii(lMsgId, pDlg->m_APD.STRAIGHT, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "STICK_NG_CNT", 40);
	XcomAscii(lMsgId, pDlg->m_APD.STICK_NG_CNT, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "FINE_KEY_ALIGN_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.FINE_KEY_ALIGN_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "FINE_KEY_ALIGN_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.FINE_KEY_ALIGN_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "FINE_KEY_ALIGN_T", 40);
	XcomAscii(lMsgId, pDlg->m_APD.FINE_KEY_ALIGN_T, 40);

	for (i = 1; i <= 15; i++) {
		sprintf(strTemp, "LTP_%02d", i);
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, strTemp, 40);
		XcomAscii(lMsgId, pDlg->m_APD.LTP[i], 40);
	}
	for (i = 1; i <= 40; i++) {
		sprintf(strTemp, "STP_%02d", i);
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, strTemp, 40);
		XcomAscii(lMsgId, pDlg->m_APD.STP[i], 40);
	}
	for (i = 1; i <= 4; i++) {
		sprintf(strTemp, "TF_LC_%02d", i);
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, strTemp, 40);
		XcomAscii(lMsgId, pDlg->m_APD.TF_LC[i], 40);
	}
	for (i = 1; i <= 4; i++) {
		sprintf(strTemp, "TF_RC_%02d", i);
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, strTemp, 40);
		XcomAscii(lMsgId, pDlg->m_APD.TF_RC[i], 40);
	}

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_PO_LT_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_PO_LT_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_PO_LT_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_PO_LT_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_PO_RT_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_PO_RT_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_PO_RT_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_PO_RT_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_PO_LB_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_PO_LB_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_PO_LB_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_PO_LB_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_PO_RB_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_PO_RB_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_PO_RB_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_PO_RB_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_POE_LT_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_POE_LT_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_POE_LT_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_POE_LT_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_POE_RT_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_POE_RT_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_POE_RT_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_POE_RT_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_POE_LB_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_POE_LB_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_POE_LB_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_POE_LB_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_POE_RB_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_POE_RB_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_POE_RB_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_POE_RB_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_CDE_LT_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_CDE_LT_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_CDE_LT_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_CDE_LT_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_CDE_RT_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_CDE_RT_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_CDE_RT_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_CDE_RT_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_CDE_LB_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_CDE_LB_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_CDE_LB_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_CDE_LB_Y, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_CDE_RB_X", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_CDE_RB_X, 40);

	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, "AK_CDE_RB_Y", 40);
	XcomAscii(lMsgId, pDlg->m_APD.AK_CDE_RB_Y, 40);*/
}

//--Xcom에 측정결과 기록
void CSecs::XcomWriteMeasureParameter()
{
	//USES_CONVERSION;
	//CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	//CDefect* pDefect = CDefect::GetInstance();


	//int nC, nDx, nDy;
	//int nNumCell = 5, nNumDX = 2, nNumDY = 2;
	//char strItem[40], strValue[40];
	//double dPpaX_Avg = 0.0, dPpaX_Max = 0.0, dPpaX_Min = 0.0, dPpaX_Sig = 0.0, dPpaY_Avg = 0.0, dPpaY_Max = 0.0, dPpaY_Min = 0.0, dPpaY_Sig = 0.0, dPpaZ_Avg = 0.0, dPpaZ_Max = 0.0, dPpaZ_Min = 0.0, dPpaZ_Sig = 0.0;
	//double dCDX_Avg = 0.0, dCDX_Max = 0.0, dCDX_Min = 0.0, dCDX_Sig = 0.0, dCDY_Avg = 0.0, dCDY_Max = 0.0, dCDY_Min = 0.0, dCDY_Sig = 0.0;
	//int ppa_count=0, ppa_at_count=0;
	//vNewPPADefectList list = pDefect->GetDefectData_NewPPA();
	//vNewPPADefectList list_AT = pDefect->GetDefectData_NewPPAAT();

	//vNewPPADefectList::iterator iter = list.begin();
	//vNewPPADefectList::iterator iter2 = list_AT.begin();

	//double dPpaX, dPpaY, dCdX, dCdY, dPpaZ, dPpaX_AT, dPpaY_AT, dCdX_AT, dCdY_AT, dPpaZ_AT;

	//for (int i = 0; i < list.size(); i++)
	//{
	//	dPpaX = list.at(i).dPpaXAvg;
	//	dPpaY = list.at(i).dPpaYAvg;
	//	dCdX = list.at(i).dCdWidthAvg;
	//	dCdY = list.at(i).dCdHeightAvg;
	//	dPpaZ = list.at(i).dPpaZAvg;
	//	
	//	ppa_count++;
	//	dPpaX_Avg = dPpaX_Avg + dPpaX;
	//	dPpaY_Avg = dPpaY_Avg + dPpaY;
	//	dPpaZ_Avg = dPpaZ_Avg + dPpaZ;
	//	dCDX_Avg = dCDX_Avg + dCdX;
	//	dCDY_Avg = dCDY_Avg + dCdY;

	//	if (dPpaX_Max < dPpaX){
	//		dPpaX_Max = dPpaX;
	//	}
	//	else if (dPpaX_Min > dPpaX){
	//		dPpaX_Min = dPpaX;
	//	}

	//	if (dPpaY_Max < dPpaY){
	//		dPpaY_Max = dPpaY;
	//	}
	//	else if (dPpaY_Min > dPpaY){
	//		dPpaY_Min = dPpaY;
	//	}

	//	if (dPpaZ_Max < dPpaZ){
	//		dPpaZ_Max = dPpaZ;
	//	}
	//	else if (dPpaZ_Min > dPpaZ){
	//		dPpaZ_Min = dPpaZ;
	//	}

	//	if (dCDX_Max < dCdX){
	//		dCDX_Max = dCdX;
	//	}
	//	else if (dCDX_Min > dCdX){
	//		dCDX_Min = dCdX;
	//	}

	//	if (dCDY_Max < dCdY){
	//		dCDY_Max = dCdY;
	//	}
	//	else if (dCDY_Min > dCdY){
	//		dCDY_Min = dCdY;
	//	}
	//}

	//for (int i = 0; i < list_AT.size();i++)
	//{
	//	dPpaX_AT = list_AT.at(i).dPpaXAvg;
	//	dPpaY_AT = list_AT.at(i).dPpaYAvg;
	//	dCdX_AT = list_AT.at(i).dCdWidthAvg;
	//	dCdY_AT = list_AT.at(i).dCdHeightAvg;
	//	dPpaZ_AT = list_AT.at(i).dPpaZAvg;
	//	ppa_at_count++;
	//	dPpaX_Avg = dPpaX_Avg + dPpaX_AT;
	//	dPpaY_Avg = dPpaY_Avg + dPpaY_AT;
	//	dPpaZ_Avg = dPpaZ_Avg + dPpaZ_AT;
	//	dCDX_Avg = dCDX_Avg + dCdX_AT;
	//	dCDY_Avg = dCDY_Avg + dCdY_AT;

	//	if (dPpaX_Max < dPpaX_AT){
	//		dPpaX_Max = dPpaX_AT;
	//	}
	//	else if (dPpaX_Min > dPpaX_AT){
	//		dPpaX_Min = dPpaX_AT;
	//	}

	//	if (dPpaY_Max < dPpaY_AT){
	//		dPpaY_Max = dPpaY_AT;
	//	}
	//	else if (dPpaY_Min > dPpaY_AT){
	//		dPpaY_Min = dPpaY_AT;
	//	}

	//	if (dPpaZ_Max < dPpaZ_AT){
	//		dPpaZ_Max = dPpaZ_AT;
	//	}
	//	else if (dPpaZ_Min > dPpaZ_AT){
	//		dPpaZ_Min = dPpaZ_AT;
	//	}

	//	if (dCDX_Max < dCdX_AT){
	//		dCDX_Max = dCdX_AT;
	//	}
	//	else if (dCDX_Min > dCdX_AT){
	//		dCDX_Min = dCdX_AT;
	//	}

	//	if (dCDY_Max < dCdY_AT){
	//		dCDY_Max = dCdY_AT;
	//	}
	//	else if (dCDY_Min > dCdY_AT){
	//		dCDY_Min = dCdY_AT;
	//	}
	//}

	//dPpaX_Avg = dPpaX_Avg / (ppa_at_count + ppa_count);
	//dPpaY_Avg = dPpaY_Avg / (ppa_at_count + ppa_count);
	//dPpaZ_Avg = dPpaZ_Avg / (ppa_at_count + ppa_count);
	//dCDX_Avg = dCDX_Avg / (ppa_at_count + ppa_count);
	//dCDY_Avg = dCDY_Avg / (ppa_at_count + ppa_count);
	//Total_Msg(_T("ppa_at_count = %d, ppa_count = %d "), ppa_at_count, ppa_count);

	//for (int i = 0; i < list.size(); i++)
	//{
	//	dPpaX = dPpaX_Avg-list.at(i).dPpaXAvg;
	//	dPpaY = dPpaY_Avg- list.at(i).dPpaYAvg;
	//	dCdX = dCDX_Avg- list.at(i).dCdWidthAvg;
	//	dCdY = dCDY_Avg- list.at(i).dCdHeightAvg;
	//	dPpaZ = dPpaZ_Avg-list.at(i).dPpaZAvg;
	//	
	//	dPpaX_Sig += dPpaX*dPpaX;
	//	dPpaY_Sig +=dPpaY*dPpaY;
	//	dPpaZ_Sig += dPpaZ*dPpaZ;
	//	dCDX_Sig += dCdX*dCdX;
	//	dCDY_Sig += dCdY*dCdY;
	//}

	//for (int i = 0; i < list_AT.size(); i++)
	//{
	//	dPpaX_AT = dPpaX_Avg - list_AT.at(i).dPpaXAvg;
	//	dPpaY_AT = dPpaY_Avg - list_AT.at(i).dPpaYAvg;
	//	dCdX_AT = dCDX_Avg - list_AT.at(i).dCdWidthAvg;
	//	dCdY_AT = dCDY_Avg - list_AT.at(i).dCdHeightAvg;
	//	dPpaZ_AT = dPpaZ_Avg - list_AT.at(i).dPpaZAvg;

	//	dPpaX_Sig += dPpaX_AT*dPpaX_AT;
	//	dPpaY_Sig += dPpaY_AT*dPpaY_AT;
	//	dPpaZ_Sig += dPpaZ_AT*dPpaZ_AT;
	//	dCDX_Sig += dCdX_AT*dCdX_AT;
	//	dCDY_Sig += dCdY_AT*dCdY_AT;
	//}

	//dPpaX_Sig = dPpaX_Sig / ((ppa_at_count + ppa_count) - 1);
	//dPpaY_Sig = dPpaY_Sig / ((ppa_at_count + ppa_count) - 1);
	//dPpaZ_Sig = dPpaZ_Sig / ((ppa_at_count + ppa_count) - 1);
	//dCDX_Sig = dCDX_Sig / ((ppa_at_count + ppa_count) - 1);
	//dCDY_Sig = dCDY_Sig / ((ppa_at_count + ppa_count) - 1);

	//dPpaX_Sig = sqrt(dPpaX_Sig);
	//dPpaY_Sig = sqrt(dPpaY_Sig);
	//dPpaZ_Sig = sqrt(dPpaZ_Sig);
	//dCDX_Sig = sqrt(dCDX_Sig);
	//dCDY_Sig = sqrt(dCDY_Sig);

	//XcomWriteParam("STICK_PPAX_AVG", dPpaX_Avg);
	//XcomWriteParam("STICK_PPAX_MAX", dPpaX_Max);
	//XcomWriteParam("STICK_PPAX_MIN", dPpaX_Min);
	//XcomWriteParam("STICK_PPAX_SIG", dPpaX_Sig);
	//XcomWriteParam("STICK_PPAY_AVG", dPpaY_Avg);
	//XcomWriteParam("STICK_PPAY_MAX", dPpaY_Max);
	//XcomWriteParam("STICK_PPAY_MIN", dPpaY_Min);
	//XcomWriteParam("STICK_PPAX_SIG", dPpaY_Sig);
	//XcomWriteParam("STICK_PPAZ_AVG", dPpaZ_Avg);
	//XcomWriteParam("STICK_PPAZ_MAX", dPpaZ_Max);
	//XcomWriteParam("STICK_PPAZ_MIN", dPpaZ_Min);
	//XcomWriteParam("STICK_PPAZ_SIG", dPpaZ_Sig);
	//XcomWriteParam("STICK_CDX_AVG", dCDX_Avg);
	//XcomWriteParam("STICK_CDX_MAX", dCDX_Max);
	//XcomWriteParam("STICK_CDX_MIN", dCDX_Min);
	//XcomWriteParam("STICK_CDX_SIG", dCDX_Sig);
	//XcomWriteParam("STICK_CDY_AVG", dCDY_Avg);
	//XcomWriteParam("STICK_CDY_MAX", dCDY_Max);
	//XcomWriteParam("STICK_CDY_MIN", dCDY_Min);
	//XcomWriteParam("STICK_CDY_SIG", dCDY_Sig);
}

//검사결과를 XCOM으로 기록
void CSecs::XcomWrite_InspectData()
{
	//CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	//CDefect* pDefect = CDefect::GetInstance();
	//CProcessStep* pProcessStep = CProcessStep::GetInstance();
	//char strItem[40], strValue[40];
	////double dValue[30][5][5] = { 0.0 };//30 : x 열 최대 갯수, 5 : Y 행 최대 갯수, 5 : ppa x,y,z avg, cd height, width 5개 항목 
	//vNewPPADefectList list = pDefect->GetDefectData_NewPPA();
	//vNewPPADefectList list_AT = pDefect->GetDefectData_NewPPAAT();
	//vNewPPADefectList listTP = pDefect->GetDefectData_NewPPATP();
	//vNewPPADefectList listTP_AT = pDefect->GetDefectData_NewPPAATTP();
	//int nDefectCount = (int)list.size();

	//int nCellCountX = pDlg->m_ModelParaData.m_NewStickInfo.m_nCellCountXY[0];
	//int nDivCountXY = pDlg->m_InspectParaData.m_NewStickInfo.m_nDivCountXY; //2X2, 3X3, 5X5

	//int nDivXY = 2;
	//if (nDivCountXY == 1) nDivXY = 3;
	//if (nDivCountXY == 2) nDivXY = 5;
	//int nCount;
	////double dPosX = 0.0, dPosY = 0.0;
	//double dPpaX, dPpaY, dCdX, dCdY, dPpaZ, dPpaX_AT, dPpaY_AT, dCdX_AT, dCdY_AT, dPpaZ_AT;
	//int nCell, nDy, nDx, nY1Pos, nPos;
	//UINT nCellX = 0, nCellY = 0, nDivX = 0, nDivY = 0;
	//
	//double dPosX = 0.0, dPosY = 0.0, dPosX_AT = 0.0, dPosY_AT = 0.0;

	//pProcessStep->GetTPCount(&nCount);
	//nCount = (nCount * 4);//TP 찍은 갯수
	//vNewPPADefectList::iterator iter = list.begin();
	//vNewPPADefectList::iterator iter2 = list_AT.begin();
	//vNewPPADefectList::iterator iterTP = listTP.begin();
	//vNewPPADefectList::iterator iterATTP = listTP_AT.begin();
	//int i, j, k, m, n;

	//for (i = 0; i < nCount; i++)
	//{
	//
	//	if (i >= listTP.size())
	//	{
	//		dPpaX = 0.0;
	//		dPpaY = 0.0;
	//		dPosX = 0.0;
	//		dPosY = 0.0;
	//	}
	//	else
	//	{
	//		pProcessStep->GetTPPos(i, &dPosX, &dPosY);
	//		dPpaX = listTP.at(i).dPpaXAvg;
	//		dPpaY = listTP.at(i).dPpaYAvg;
	//		dPosX = dPosX * 1000;//mm >> um
	//		dPosY = dPosY * 1000;
	//	}
	//	if (i >= listTP_AT.size())
	//	{
	//		dPpaX_AT = 0.0;
	//		dPpaY_AT = 0.0;
	//		dPosX_AT = 0.0;
	//		dPosY_AT = 0.0;
	//	}
	//	else
	//	{
	//		pProcessStep->GetTPPos(i, &dPosX_AT, &dPosY_AT);
	//		dPpaX_AT = listTP_AT.at(i).dPpaXAvg;
	//		dPpaY_AT = listTP_AT.at(i).dPpaYAvg;
	//		dPosX_AT = dPosX_AT * 1000;//mm >>um
	//		dPosY_AT = dPosY_AT * 1000;
	//	}
	//	sprintf(strItem, "STICK_TP%02d_X", i+1);
	//	sprintf(strValue, "%.5f", dPpaX);
	//	pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//	sprintf(strItem, "STICK_TP%02d_Y", i+1);
	//	sprintf(strValue, "%.5f", dPpaY);
	//	pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//	sprintf(strItem, "STICK_AT_TP%02d_X", i+1);
	//	sprintf(strValue, "%.5f", dPpaX_AT);
	//	pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//	sprintf(strItem, "STICK_AT_TP%02d_Y", i+1);
	//	sprintf(strValue, "%.5f", dPpaY_AT);
	//	pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//	sprintf(strItem, "STICK_TP%02d_DX", i + 1);
	//	sprintf(strValue, "%.5f", dPosX);
	//	pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//	sprintf(strItem, "STICK_TP%02d_DY", i + 1);
	//	sprintf(strValue, "%.5f", dPosY);
	//	pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//	sprintf(strItem, "STICK_AT_TP%02d_DX", i + 1);
	//	sprintf(strValue, "%.5f", dPosX_AT);
	//	pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//	sprintf(strItem, "STICK_AT_TP%02d_DY", i + 1);
	//	sprintf(strValue, "%.5f", dPosY_AT);
	//	pDlg->m_pSecs->XcomWriteParam(strItem, strValue);



	//}

	//for (i = 0; i < nDivXY; i++)
	//{
	//	m = (nCellCountX * nDivXY)*i;
	//	n = (nCellCountX * nDivXY)*(i + 1);

	//	if (i % 2 == 0)	//k는 x 열 , i는 y 행, j는 nPos
	//	{
	//		for (j = m, k = 0; j < n; j++, k++)
	//		{	
	//			nDx = k % nDivXY;
	//			nCell = k / nDivXY;
	//			if (j >= list.size()){ // 일반 ppa
	//				dPpaX = 0.0;
	//				dPpaY = 0.0;
	//				dCdX = 0.0;
	//				dCdY = 0.0;
	//				dPpaZ = 0.0;
	//			}
	//			else
	//			{
	//				dPpaX = list.at(j).dPpaXAvg;
	//				dPpaY = list.at(j).dPpaYAvg;
	//				dCdX = list.at(j).dCdWidthAvg;
	//				dCdY = list.at(j).dCdHeightAvg;
	//				dPpaZ = list.at(j).dPpaZAvg;
	//				pProcessStep->GetInspectPpaCellNo(j, &nCellX, &nCellY, &nDivX, &nDivY);
	//				pProcessStep->GetPPAPos(nCellX, nCellY, nDivX, nDivY, &dPosX, &dPosY);
	//			}

	//			if (j >= list_AT.size()){// 인장 ppa
	//				dPpaX_AT = 0.0;
	//				dPpaY_AT = 0.0;
	//				dCdX_AT = 0.0;
	//				dCdY_AT = 0.0;
	//				dPpaZ_AT = 0.0;
	//			}
	//			else
	//			{
	//				dPpaX_AT = list_AT.at(j).dPpaXAvg;
	//				dPpaY_AT = list_AT.at(j).dPpaYAvg;
	//				dCdX_AT = list_AT.at(j).dCdWidthAvg;
	//				dCdY_AT = list_AT.at(j).dCdHeightAvg;
	//				dPpaZ_AT = list_AT.at(j).dPpaZAvg;
	//			}
	//			//sprintf(strItem, "C%02dD%d%d_DESIGN_X", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strItem, "C%02dD%d%d_DESIGN_X", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPosX);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_DESIGN_Y", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPosY);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_AT_DESIGN_X", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPosX_AT);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_AT_DESIGN_Y", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPosY_AT);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAX", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaX);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAY", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaY);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_CDX", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dCdX);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_CDY", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dCdY);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAZ", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaZ);
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_CDX_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dCdX_AT);		//임시
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_CDY_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dCdY_AT);		//임시
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAX_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaX_AT);		//임시
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAY_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaY_AT);		//임시
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAZ_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaZ_AT);		//임시
	//			XcomWriteParam(strItem, strValue);
	//		}
	//	}
	//	else
	//	{
	//		for (j = n - 1, k = 0; j >= m; j--, k++)
	//		{
	//			nCell = k / nDivXY;
	//			if (j >= list.size()){ // 일반 ppa
	//				dPpaX = 0.0;
	//				dPpaY = 0.0;
	//				dCdX = 0.0;
	//				dCdY = 0.0;
	//				dPpaZ = 0.0;
	//			}
	//			else
	//			{
	//				dPpaX = list.at(j).dPpaXAvg;
	//				dPpaY = list.at(j).dPpaYAvg;
	//				dCdX = list.at(j).dCdWidthAvg;
	//				dCdY = list.at(j).dCdHeightAvg;
	//				dPpaZ = list.at(j).dPpaZAvg;
	//			}

	//			if (j >= list_AT.size()) // 인장 ppa
	//			{
	//				dPpaX_AT = 0.0;
	//				dPpaY_AT = 0.0;
	//				dCdX_AT = 0.0;
	//				dCdY_AT = 0.0;
	//				dPpaZ_AT = 0.0;
	//			}
	//			else{ 
	//				dPpaX_AT = list_AT.at(j).dPpaXAvg;
	//				dPpaY_AT = list_AT.at(j).dPpaYAvg;
	//				dCdX_AT = list_AT.at(j).dCdWidthAvg;
	//				dCdY_AT = list_AT.at(j).dCdHeightAvg;
	//				dPpaZ_AT = list_AT.at(j).dPpaZAvg;
	//				pProcessStep->GetATInspectPpaCellNo(j, &nCellX, &nCellY, &nDivX, &nDivY);
	//				pProcessStep->GetATPPAPos(nCellX, nCellY, nDivX, nDivY, &dPosX_AT, &dPosY_AT);
	//			}

	//			sprintf(strItem, "C%02dD%d%d_DESIGN_X", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strItem, "C%02dD%d%d_DESIGN_X", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPosX);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_DESIGN_Y", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPosY);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_AT_DESIGN_X", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPosX_AT);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_AT_DESIGN_Y", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPosY_AT);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);


	//			sprintf(strItem, "C%02dD%d%d_PPAX", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaX);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAY", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaY);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_CDX", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dCdX);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_CDY", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dCdY);
	//			pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAZ", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaZ);
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_CDX_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dCdX_AT);		//임시
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_CDY_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dCdY_AT);		//임시
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAX_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaX_AT);		//임시
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAY_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaY_AT);		//임시
	//			XcomWriteParam(strItem, strValue);

	//			sprintf(strItem, "C%02dD%d%d_PPAZ_AT", nCell + 1, nDx + 1, i + 1);
	//			sprintf(strValue, "%.5f", dPpaZ_AT);		//임시
	//			XcomWriteParam(strItem, strValue);
	//		}
	//	}
	//}




	////for (nCell = 0; nCell < nCellCountX; nCell++)
	////{
	////	for (nDy = 0; nDy < nDivXY; nDy++)
	////	{
	////		nY1Pos = (nCell * nDivXY * nDivXY) + (nDy * nDivXY);

	////		//if (nDy % 2 == 0)
	////		//{
	////			for (nDx = 0; nDx < nDivXY; nDx++)
	////			{
	////				nPos = nY1Pos + nDx;	//일반적
	////				if (nDy % 2 == 1) {
	////					nPos = nY1Pos + nDivXY - nDx - 1;	 //홀수줄일때 순서바뀜
	////				}

	////				if (nPos < list.size())
	////				{
	////					dPpaX = list.at(nPos).dPpaXAvg;
	////					dPpaY = list.at(nPos).dPpaYAvg;
	////					dCdX = list.at(nPos).dCdWidthAvg;
	////					dCdY = list.at(nPos).dCdHeightAvg;
	////					dPpaZ = list.at(nPos).dPpaZAvg;
	////				}
	////				else {
	////					dPpaX = 0.0;
	////					dPpaY = 0.0;
	////					dCdX = 0.0;
	////					dCdY = 0.0;
	////					dPpaZ = 0.0;
	////				}
	////				if (nPos < list_AT.size()){
	////					dPpaX_AT = list_AT.at(nPos).dPpaXAvg;
	////					dPpaY_AT = list_AT.at(nPos).dPpaYAvg;
	////					dCdX_AT = list_AT.at(nPos).dCdWidthAvg;
	////					dCdY_AT = list_AT.at(nPos).dCdHeightAvg;
	////					dPpaZ_AT = list_AT.at(nPos).dPpaZAvg;
	////				}
	////				else{
	////					dPpaX_AT = 0.0;
	////					dPpaY_AT = 0.0;
	////					dCdX_AT = 0.0;
	////					dCdY_AT = 0.0;
	////					dPpaZ_AT = 0.0;
	////				}

	////				sprintf(strItem, "C%02dD%d%d_PPAX", nCell+1, nDx+1, nDy+1);
	////				sprintf(strValue, "%.5f", dPpaX);
	////				pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	////				sprintf(strItem, "C%02dD%d%d_PPAY", nCell + 1, nDx + 1, nDy + 1);
	////				sprintf(strValue, "%.5f", dPpaY);
	////				pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	////				sprintf(strItem, "C%02dD%d%d_CDX", nCell + 1, nDx + 1, nDy + 1);
	////				sprintf(strValue, "%.5f", dCdX);
	////				pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	////				sprintf(strItem, "C%02dD%d%d_CDY", nCell + 1, nDx + 1, nDy + 1);
	////				sprintf(strValue, "%.5f", dCdY);
	////				pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	////				sprintf(strItem, "C%02dD%d%d_PPAZ", nCell + 1, nDx + 1, nDy + 1);
	////				sprintf(strValue, "%.5f", dPpaZ);
	////				XcomWriteParam(strItem, strValue);

	////				if (1){
	////					sprintf(strItem, "C%02dD%d%d_CDX_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", dCdX_AT);		//임시
	////					XcomWriteParam(strItem, strValue);

	////					sprintf(strItem, "C%02dD%d%d_CDY_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", dCdY_AT);		//임시
	////					XcomWriteParam(strItem, strValue);

	////					sprintf(strItem, "C%02dD%d%d_PPAX_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", dPpaX_AT);		//임시
	////					XcomWriteParam(strItem, strValue);

	////					sprintf(strItem, "C%02dD%d%d_PPAY_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", dPpaY_AT);		//임시
	////					XcomWriteParam(strItem, strValue);

	////					sprintf(strItem, "C%02dD%d%d_PPAZ_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", dPpaZ_AT);		//임시
	////					XcomWriteParam(strItem, strValue);
	////				}
	////				else{
	////					sprintf(strItem, "C%02dD%d%d_CDX_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", "");		//임시
	////					XcomWriteParam(strItem, strValue);

	////					sprintf(strItem, "C%02dD%d%d_CDY_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", "");		//임시
	////					XcomWriteParam(strItem, strValue);

	////					sprintf(strItem, "C%02dD%d%d_PPAX_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", "");		//임시
	////					XcomWriteParam(strItem, strValue);

	////					sprintf(strItem, "C%02dD%d%d_PPAY_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", "");		//임시
	////					XcomWriteParam(strItem, strValue);

	////					sprintf(strItem, "C%02dD%d%d_PPAZ_AT", nCell + 1, nDx + 1, nDy + 1);
	////					sprintf(strValue, "%.5f", "");		//임시
	////					XcomWriteParam(strItem, strValue);
	////				}
	////			}
	////		}
	////	//}
	////}
}

//검사결과를 XCOM으로 기록
void CSecs::XcomWrite_InspectATData()
{
	//CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	//CDefect* pDefect = CDefect::GetInstance();

	//char strItem[40], strValue[40];

	//vNewPPADefectList list = pDefect->GetDefectData_NewPPAAT();
	//int nDefectCount = (int)list.size();

	//int nCellCountX = pDlg->m_ModelParaData.m_NewStickInfo.m_nCellCountXY[0];
	//int nDivCountXY = pDlg->m_InspectParaData.m_NewStickInfo.m_nDivCountXY; //2X2, 3X3, 5X5

	//int nDivXY = 2;
	//if (nDivCountXY == 1) nDivXY = 3;
	//if (nDivCountXY == 2) nDivXY = 5;


	//double dPpaX, dPpaY, dCdX, dCdY;
	//int nCell, nDy, nDx, nY1Pos, nPos;

	//vNewPPADefectList::iterator iter = list.begin();

	//for (nCell = 0; nCell < nCellCountX; nCell++)
	//{
	//	for (nDy = 0; nDy < nDivXY; nDy++)
	//	{
	//		nY1Pos = (nCell * nDivXY * nDivXY) + (nDy * nDivXY);

	//		if (nDy % 2 == 0)
	//		{
	//			for (nDx = 0; nDx < nDivXY; nDx++)
	//			{
	//				nPos = nY1Pos + nDx;	//일반적
	//				if (nDy % 2 == 1) {
	//					nPos = nY1Pos + nDivXY - nDx - 1;	 //홀수줄일때 순서바뀜
	//				}

	//				if (nPos < list.size())
	//				{
	//					dPpaX = list.at(nPos).dPpaXAvg;
	//					dPpaY = list.at(nPos).dPpaYAvg;
	//					dCdX = list.at(nPos).dCdWidthAvg;
	//					dCdY = list.at(nPos).dCdHeightAvg;
	//				}
	//				else {
	//					dPpaX = 0.0;
	//					dPpaY = 0.0;
	//					dCdX = 0.0;
	//					dCdY = 0.0;
	//				}

	//				sprintf(strItem, "C%02dD%d%d_PPAX", nCell, nDx, nDy);
	//				sprintf(strValue, "%.5f", list.at(nPos).dPpaXAvg);
	//				pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//				sprintf(strItem, "C%02dD%d%d_PPAY", nCell, nDx, nDy);
	//				sprintf(strValue, "%.5f", list.at(nPos).dPpaYAvg);
	//				pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//				sprintf(strItem, "C%02dD%d%d_CDX", nCell, nDx, nDy);
	//				sprintf(strValue, "%.5f", list.at(nPos).dCdWidthAvg);
	//				pDlg->m_pSecs->XcomWriteParam(strItem, strValue);

	//				sprintf(strItem, "C%02dD%d%d_CDY", nCell, nDx, nDy);
	//				sprintf(strValue, "%.5f", list.at(nPos).dCdHeightAvg);
	//				pDlg->m_pSecs->XcomWriteParam(strItem, strValue);
	//			}
	//		}
	//	}
	//}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/* Are You There */
void CSecs::S1F1()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 1;
	nFunc = 1;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S1F1recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomMsgClose(lMsgId);
	//
	S1F2(lSysByte);
}

/* On Line Data */
void CSecs::S1F2(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 1;
	nFunc = 2;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 0);
	//XcomList(lMsgId, 2);
	//XcomAscii(lMsgId,"model", 8);			//Equipment Model Type 
	//XcomAscii(lMsgId, "code", 6);		//Sofware revision code
	XcomReply(lMsgId, nStrm, nFunc);	//Reply
}
void CSecs::S1F2recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	XcomMsgClose(lMsgId);
}

#ifndef TRUE



/* All Equipment Status Report */
void CSecs::S1F61()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numIon = IONIZER_COUNT;

	int nUnit, nIon;
	int nUnitCount = 1;
	nStrm = 1;
	nFunc = 61;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	XcomList(lMsgId, 2);
	XcomList(lMsgId, nUnitCount);
	for (nUnit = 0; nUnit < nUnitCount; nUnit++){
		XcomList(lMsgId, 2);
		//XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);		//수정 20180117 jinsuk
		XcomAscii(lMsgId, pDlg->m_EQP.STATUS, 1);
	}
	XcomList(lMsgId, numIon);
	for (nIon = 0; nIon < numIon; nIon++){
		XcomList(lMsgId, 2);
		//pDlg->m_IONIZER[nIon].IONIZERID[0] = 100;
		//pDlg->m_IONIZER[nIon].IONIZERSTATUS[0] = 'D';

		XcomBinary(lMsgId, pDlg->m_IONIZER[nIon].IONIZERID, 1);
		XcomAscii(lMsgId, pDlg->m_IONIZER[nIon].IONIZERSTATUS, 1);
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}

void CSecs::S1F62recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* All Equipment Status Request */
void CSecs::S1F63recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomMsgClose(lMsgId);
	S1F64(lSysByte);

}
void CSecs::S1F64(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	int nUnitCount = 1;
	int nUnit, nIon;
	nStrm = 1;
	nFunc = 64;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte)) return;	//MakeMsg
	XcomList(lMsgId, 2);
	XcomList(lMsgId, nUnitCount);
	for (nUnit = 0; nUnit < nUnitCount; nUnit++){
		XcomList(lMsgId, 2);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomAscii(lMsgId, pDlg->m_EQP.EQPSTATUS, 1);
	}
	XcomList(lMsgId, IONIZER_COUNT);
	for (nIon = 0; nIon < IONIZER_COUNT; nIon++){
		XcomList(lMsgId, 2);
		XcomBinary(lMsgId, pDlg->m_IONIZER[nIon].IONIZERID, 1);
		XcomAscii(lMsgId, pDlg->m_IONIZER[nIon].IONIZERSTATUS, 1);
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}

/* All Glass Position Data Report */
void CSecs::S1F67()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 1;
	nFunc = 67;
	int nPos, nGlass;
	int numPosition = POSITION_COUNT;
	int numGlass = pDlg->m_LOT.SLOT[0];	//글라스=스틱 갯수

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg	

	XcomList(lMsgId, numPosition);
	for (nPos = 0; nPos < numPosition; nPos++)
	{
		XcomList(lMsgId, 3);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomBinary(lMsgId, pDlg->m_POSITION[nPos].ID, 1);
		XcomList(lMsgId, numGlass);
		for (nGlass = 0; nGlass < numGlass; nGlass++)
		{
			XcomU2(lMsgId, &pDlg->m_GLASS[nGlass].GLSCODE, 1);
		}
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S1F68recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Change Glass Count Send  */
void CSecs::S1F69recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	WORD u2;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &u2, &lSize, 1);
	XcomGetBinary(lMsgId, pDlg->m_LOT.GLSCNT, &lSize, 1);
	XcomMsgClose(lMsgId);
	//
	S1F70(lSysByte);
}
void CSecs::S1F70(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 1;
	long nFunc = 70;

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Remained Glass Count Request  */
void CSecs::S1F71()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 1;
	nFunc = 71;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S1F72recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lCnt, 16);
	XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.REMAINGLSCNT, &lCnt, 1);
	XcomMsgClose(lMsgId);
}

/* Monitoring Lot Status Data Send   */
void CSecs::S1F73recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.MLOTSTATUS, &lSize, 1);
	XcomMsgClose(lMsgId);
	//
	S1F74(lSysByte);
}
void CSecs::S1F74(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 1;
	long nFunc = 74;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Ionizer Status Report  */
void CSecs::S1F75()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	int nIon;
	nStrm = 1;
	nFunc = 75;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomList(lMsgId, IONIZER_COUNT);
	for (nIon = 0; nIon < IONIZER_COUNT; nIon++){
		XcomList(lMsgId, 2);
		XcomBinary(lMsgId, pDlg->m_IONIZER[nIon].IONIZERID, 1);
		XcomAscii(lMsgId, pDlg->m_IONIZER[nIon].IONIZERSTATUS, 1);
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S1F76recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Equipment’s Part Data Report  */
void CSecs::S1F77()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numPosition = POSITION_COUNT;
	long numGlass = GLASS_COUNT;
	int nPos, nGlass;
	nStrm = 1;
	nFunc = 77;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	XcomList(lMsgId, numPosition);
	for (nPos = 0; nPos < numPosition; nPos++)
	{
		XcomList(lMsgId, 3);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomBinary(lMsgId, pDlg->m_POSITION[nPos].ID, 1);
		XcomList(lMsgId, numGlass);
		for (nGlass = 0; nGlass < numGlass; nGlass++)
		{
			XcomList(lMsgId, 2);
			XcomAscii(lMsgId, pDlg->m_GLASS[nGlass].CRRID, 6);
			XcomU2(lMsgId, &pDlg->m_GLASS[nGlass].GLSCODE, 1);
		}
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S1F78recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Monitoring Lot Status Data Send   */
void CSecs::S1F79recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.BLOTTYPE, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.BLOTSTATUS, &lSize, 1);
	XcomMsgClose(lMsgId);
	//
	S1F80(lSysByte);
}
void CSecs::S1F80(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 1;
	long nFunc = 80;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Monitoring Lot Status Data Send   */
void CSecs::S1F81recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int nPort = pDlg->m_EQP.PORTID[0];

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 14);
	XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_PORT[nPort].STATE, &lSize, 2);
	XcomGetAscii(lMsgId, pDlg->m_PORT[nPort].LOTSTATE, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_PORT[nPort].CSTMAP, &lSize, 40);
	XcomGetAscii(lMsgId, pDlg->m_PORT[nPort].SELECTEDMAP, &lSize, 40);
	XcomMsgClose(lMsgId);
	//
	S1F82(lSysByte);
}
void CSecs::S1F82(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 1;
	long nFunc = 80;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Port State Data Report */
void CSecs::S1F83()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 1;
	nFunc = 83;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	int nPort = pDlg->m_EQP.PORTID[0];

	XcomList(lMsgId, 5);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.CSTID, 14);
	XcomBinary(lMsgId, pDlg->m_PORT[nPort].ID, 1);
	XcomAscii(lMsgId, pDlg->m_PORT[nPort].STATE, 2);
	XcomAscii(lMsgId, pDlg->m_EQP.TRSMODE, 1);
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S1F84recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int nPort = pDlg->m_EQP.PORTID[0];

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lSize, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lSize, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Port Status Change Data Report */
void CSecs::S1F85()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 1;
	nFunc = 85;
	int nPort;
	long numPort = PORT_COUNT;

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);				// L 2
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);			// pDlg->m_EQP.UNITID
	XcomList(lMsgId, numPort);

	//20171213 jinsuk
	//for (nPort = 0; nPort< numPort; nPort++)		
	for (nPort = 1; nPort <= numPort; nPort++)
	{
		XcomList(lMsgId, 2);
		XcomBinary(lMsgId, pDlg->m_PORT[nPort].ID, 1);		// ALCD
		XcomAscii(lMsgId, pDlg->m_PORT[nPort].STATUS, 1);
	}
	//
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S1F86recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int nPort = pDlg->m_EQP.PORTID[0];

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lSize, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lSize, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Lot State Change Report  */
void CSecs::S1F87()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 1;
	nFunc = 87;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 5);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.CSTID, 14);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTSTATE, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S1F88recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lSize, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lSize, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}


/* Mask Data Report   */
void CSecs::S1F89()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 1;
	nFunc = 89;
	long numMask = 0;
	int nMask;
	char masksheetid[20];

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.MASKID, 14);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomList(lMsgId, numMask);
	for (nMask = 0; nMask < numMask; nMask++)
	{
		XcomAscii(lMsgId, masksheetid, 20);
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S1F90recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lSize, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lSize, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}


/* All Mask Position Data Report  (only use in E6) */
void CSecs::S1F91()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CStateManager *pStateManager = CStateManager::GetInstance();

	nStrm = 1;
	nFunc = 91;
	long numPosition = POSITION_COUNT;
	long numMask = 1;
	int nPos;
	char masksheetid[20] = "";
	int nMask = pStateManager->GetMaskNo();		//현재 Stick 순번

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, numPosition);
	for (nPos = 0; nPos < numPosition; nPos++)
	{
		XcomList(lMsgId, 4);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomBinary(lMsgId, pDlg->m_POSITION[nPos].ID, 1); 
		//XcomAscii(lMsgId, pDlg->m_LOT.MASKID, 14);
		XcomAscii(lMsgId, pDlg->m_LOT.MCSTID, 14);
		XcomList(lMsgId, numMask);
		for (nMask = 1; nMask <= numMask; nMask++)
		{
			XcomAscii(lMsgId, pDlg->m_SLOT[nMask].STICKID, 20);
		}
	}
	XcomSend(lMsgId, nStrm, nFunc);
}

void CSecs::S1F91(int num)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CStateManager *pStateManager = CStateManager::GetInstance();

	nStrm = 1;
	nFunc = 91;
	long numPosition = POSITION_COUNT;
	int nPos;
	char masksheetid[20] = "";
	int nMask = num;

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, numPosition);
	for (nPos = 0; nPos < numPosition; nPos++)
	{
		XcomList(lMsgId, 4);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomBinary(lMsgId, pDlg->m_POSITION[nPos].ID, 1);
		XcomAscii(lMsgId, pDlg->m_LOT.MCSTID, 14);

		XcomList(lMsgId, 1);
		if (num = 0)
			XcomAscii(lMsgId, "", 20);
		else
			XcomAscii(lMsgId, pDlg->m_POSITION[nMask].STICKID, 20);

	}
	XcomSend(lMsgId, nStrm, nFunc);
}

void CSecs::S1F92recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lSize, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC1[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Host Command Send  */
void CSecs::S1F93recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString strcmd;

	XcomGetList(lMsgId, &lists);
	XcomGetAscii(lMsgId, pDlg->m_ECSMSG.RCMD, &lSize, 6);
	XcomGetList(lMsgId, &lists);
	XcomGetAscii(lMsgId, pDlg->m_LOT.MASKID, &lSize, 14);
	XcomGetList(lMsgId, &lists);
	XcomGetAscii(lMsgId, pDlg->m_ECSMSG.MSG, &lSize, 3);
	XcomGetAscii(lMsgId, pDlg->m_ECSMSG.HOSTMSG, &lSize, 120);
	XcomMsgClose(lMsgId);
	//
	S1F94(lSysByte);
	//
	RecvHostCommand();
}
void CSecs::S1F94(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 1;
	long nFunc = 94;

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Date and Time Request */
void CSecs::S2F17()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 17;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);		// pDlg->m_EQP.UNITID
	XcomSend(lMsgId, nStrm, nFunc);		//SendMsg
}
void CSecs::S2F18recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CString cstr;
	char curtime[15];
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetAscii(lMsgId, curtime, &lSize, 14);
	XcomMsgClose(lMsgId);
}

/* Loopback Diagnostic Request */
void CSecs::S2F25()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 25;
	BYTE bTemp[11] = { 1, 2, 3, 4, 5, 11, 12, 13, 14, 15 };
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomBinary(lMsgId, bTemp, 10);				//Any binary string
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F25recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	BYTE BStr[12];
	long lCnt;
	nReturn = XcomGetBinary(lMsgId, BStr, &lCnt, 10);
	XcomMsgClose(lMsgId);

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc + 1, lSysByte);
	XcomBinary(lMsgId, BStr, 10);
	//
	S2F26(BStr);
}
void CSecs::S2F26(BYTE* byteStr)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 26;
	if (byteStr != NULL) {
		if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
		XcomBinary(lMsgId, byteStr, 10);
		XcomSend(lMsgId, nStrm, nFunc);
	}
}
void CSecs::S2F26recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	BYTE BStr[12];
	nReturn = XcomGetBinary(lMsgId, BStr, &lCnt, 10);
	XcomMsgClose(lMsgId);
}

/*  Date and Time Data Send  */
void CSecs::S2F31recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	char cTime[15];
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	pDlg->m_XComPro.GetAsciiItem(lMsgId, (signed char *)cTime, &lCnt, 14);
	XcomMsgClose(lMsgId);
	//
	S2F32(lSysByte);
}

/*  Date and Time Acknowledge  */
void CSecs::S2F32(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 2;
	long nFunc = 32;
	pDlg->m_ECSMSG.ACKC2[0] = 0;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, 1);
	XcomReply(lMsgId, nStrm, nFunc);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomAck(strAck);
}

/* S2F61... Control State Change Request	0=Online-Remote 1=Online-Local 2=Offline */
void CSecs::S2F61()
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 61;

	//Total_Msg(_T("  st:%s"), A2W(pDlg->m_EQP.STATE));
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.STATE, 1);	// STATE
	XcomSend(lMsgId, nStrm, nFunc);


}
void CSecs::S2F62recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2A, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2A[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* S2F63...  EquipmentOperation Mode Report */
void CSecs::S2F63()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 63;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);		// UNITID
	XcomAscii(lMsgId, pDlg->m_EQP.OPMODE, 1);	// OPMODE
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F64recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2A, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2A[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Local LOT Status Change Request */
void CSecs::S2F65()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 65;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 5);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.ENDFLAG, 1);	//EndFlag N:NormalEnd P:OperatorEnd
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F66recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Cycle Stop Status Report  */
void CSecs::S2F67()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 67;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_LOT.CSSTATUS, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F68recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}


/* Unload Glass Data Request  */
void CSecs::S2F69recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, &lCnt, 1);
	Total_Msg(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomMsgClose(lMsgId);
	//
	S2F70();
}
void CSecs::S2F70()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 2;
	nFunc = 70;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* LOT End Glass Injection Send  */
void CSecs::S2F71recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lCnt, 16);
	XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lCnt, 14);
	XcomGetAscii(lMsgId, pDlg->m_EQP.ENDFLAG, &lCnt, 1);
	XcomMsgClose(lMsgId);
	//
	S2F72(lSysByte);
}
void CSecs::S2F72(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 2;
	nFunc = 72;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}


/* Chemical Change Status Report */
void CSecs::S2F75()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 75;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.CHEMCH, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F76recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Glass Call Request  */
void CSecs::S2F77()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 77;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 3);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.STAGEID, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.TARGETID, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F78recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Lost Glass Data Request  */
void CSecs::S2F79()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 2;
	nFunc = 79;
	int nGls = 0;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_GLASS[nGls].GLSID, 16);
	XcomU2(lMsgId, &pDlg->m_GLASS[nGls].GLSCODE, 1);
	XcomAscii(lMsgId, pDlg->m_GLASS[nGls].REQOPTION, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F80recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists, lSize, numSubgls, numLsd, numGsd;
	int nGls = 0, nSubgls, nLsd, nGsd;
	char cItem[25], cValue[41];
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, &lCnt, 1);
	XcomGetList(lMsgId, &lists);
	if (0 < lists)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
		XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_LOT.SLOTID, &lSize, 3);
		XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 24);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 8);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSODR, &lSize, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSID, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSJUDGE, &lSize, 2);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PNLIF, &lSize, 800);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].SUBMDLIF, &lSize, 400);
		XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
		XcomGetU2(lMsgId, &pDlg->m_GLASS[nGls].GLSCODE, &lCnt, 1);
		XcomGetBinary(lMsgId, pDlg->m_GLASS[nGls].REINPUT, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSTKICK, &lSize, 5);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PARTNUM, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PRODTYPE, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].ATTRIBUTE, &lSize, 12);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSTYPE, &lSize, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].KEYID, &lSize, 32);
		XcomGetList(lMsgId, &numSubgls);
		for (nSubgls = 0; nSubgls < numSubgls; nSubgls++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBGLSID, &lSize, 16);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBGLSJUDGE, &lSize, 2);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBPNLIF, &lSize, 400);
		}
		XcomGetList(lMsgId, &numLsd);
		for (nLsd = 0; nLsd < numLsd; nLsd++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, cItem, &lSize, 24);
			XcomGetAscii(lMsgId, cValue, &lSize, 40);
			/*************/
		}
		XcomGetList(lMsgId, &numGsd);
		for (nGsd = 0; nGsd < numGsd; nGsd++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, cItem, &lSize, 24);
			XcomGetAscii(lMsgId, cValue, &lSize, 40);
			/*************/
		}
	}
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Injecting Glass Data Request  */
void CSecs::S2F83()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 83;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.STAGEID, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F84recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists, lSize, numSubgls, numLsd, numGsd;
	int nGls = 0, nSubgls, nLsd, nGsd;
	char cItem[25], cValue[41];

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.STAGEID, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.GLSSTATUS, &lSize, 1);
	XcomGetList(lMsgId, &lists);
	if (lists == 1)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
		XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_LOT.SLOTID, &lSize, 3);
		XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 24);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 8);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSODR, &lSize, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSID, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSJUDGE, &lSize, 2);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PNLIF, &lSize, 800);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].SUBMDLIF, &lSize, 400);
		XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
		XcomGetU2(lMsgId, &pDlg->m_GLASS[nGls].GLSCODE, &lCnt, 1);
		XcomGetBinary(lMsgId, pDlg->m_GLASS[nGls].REINPUT, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSTKICK, &lSize, 5);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PARTNUM, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PRODTYPE, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].ATTRIBUTE, &lSize, 12);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSTYPE, &lSize, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].KEYID, &lSize, 32);
		XcomGetList(lMsgId, &numSubgls);
		for (nSubgls = 0; nSubgls < numSubgls; nSubgls++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBGLSID, &lSize, 16);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBGLSJUDGE, &lSize, 2);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBPNLIF, &lSize, 400);
		}
		XcomGetList(lMsgId, &numLsd);
		for (nLsd = 0; nLsd < numLsd; nLsd++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, cItem, &lSize, 24);
			XcomGetAscii(lMsgId, cValue, &lSize, 40);
			/*****추가수정필요*****/
		}
		XcomGetList(lMsgId, &numGsd);
		for (nGsd = 0; nGsd < numGsd; nGsd++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, cItem, &lSize, 24);
			XcomGetAscii(lMsgId, cValue, &lSize, 40);
			/*****추가수정필요*****/
		}
	}
	XcomMsgClose(lMsgId);
}

/* Unload Process Report  */
void CSecs::S2F85()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 85;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 3);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.UNLOADSTATUS, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.UNLOADTYPE, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S2F86recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Load Glass Data Send  */
void CSecs::S2F87recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists, lSize, numSubgls, numLsd, numGsd;
	int nGls = 0, nSubgls, nLsd, nGsd;
	char cItem[25], cValue[41];

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.STAGEID, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.GLSSTATUS, &lSize, 1);
	XcomGetList(lMsgId, &lists);
	if (0 < lists)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
		XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_LOT.SLOTID, &lSize, 3);
		XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 24);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 8);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSODR, &lSize, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSID, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSJUDGE, &lSize, 2);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PNLIF, &lSize, 800);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].SUBMDLIF, &lSize, 400);
		XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
		XcomGetU2(lMsgId, &pDlg->m_GLASS[nGls].GLSCODE, &lCnt, 1);
		XcomGetBinary(lMsgId, pDlg->m_GLASS[nGls].REINPUT, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSTKICK, &lSize, 5);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PARTNUM, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].PRODTYPE, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].ATTRIBUTE, &lSize, 12);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].GLSTYPE, &lSize, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nGls].KEYID, &lSize, 32);
		XcomGetList(lMsgId, &numSubgls);
		for (nSubgls = 0; nSubgls < numSubgls; nSubgls++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBGLSID, &lSize, 16);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBGLSJUDGE, &lSize, 2);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBPNLIF, &lSize, 400);
		}
		XcomGetList(lMsgId, &numLsd);
		for (nLsd = 0; nLsd < numLsd; nLsd++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, cItem, &lSize, 24);
			XcomGetAscii(lMsgId, cValue, &lSize, 40);
			/*************/
		}
		XcomGetList(lMsgId, &numGsd);
		for (nGsd = 0; nGsd < numGsd; nGsd++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, cItem, &lSize, 24);
			XcomGetAscii(lMsgId, cValue, &lSize, 40);
			/*************/
		}
	}
	Total_Msg(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomMsgClose(lMsgId);
	//
	S2F88(lSysByte);
}
void CSecs::S2F88(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 2;
	nFunc = 88;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.STAGEID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Batch Job(Glass Injection) End Data Send  */
void CSecs::S2F89recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.BATCHFLAG, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
	XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 14);
	XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
	XcomMsgClose(lMsgId);
	//
	S2F90(lSysByte);
}
void CSecs::S2F90(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 2;
	nFunc = 90;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* PD Down Request  */
void CSecs::S2F91recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_ECSMSG.RCMD, &lSize, 6);
	XcomGetAscii(lMsgId, pDlg->m_ECSMSG.HOSTMSG, &lSize, 120);
	XcomMsgClose(lMsgId);
	//
	S2F92(lSysByte);
}
void CSecs::S2F92(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 2;
	nFunc = 92;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Various Data Report */
void CSecs::S2F93()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 93;
	long numSlot = SLOT_COUNT;
	int nSlot;

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	XcomList(lMsgId, 3);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomU2(lMsgId, &pDlg->m_EQP.CEID, 1);

	XcomList(lMsgId, numSlot);
	for (nSlot = 0; nSlot < numSlot; nSlot++)
	{
		XcomList(lMsgId, 7);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].SLOTID, 48);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].GLSID, 48);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].GLSJUDGE, 48);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].PNLIF1, 400);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].PNLIF2, 400);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].SUBMDLIF1, 200);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].SUBMDLIF2, 200);
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S2F94recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetU2(lMsgId, &pDlg->m_EQP.CEID, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, &lCnt, 1);
	Total_Msg(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomMsgClose(lMsgId);
}


/* Chemical Change Enable Request */
void CSecs::S2F95()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 95;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S2F96recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, &lCnt, 1);
	Total_Msg(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC2[0]);
	XcomMsgClose(lMsgId);
}

/* Chemical Change Enable Send */
void CSecs::S2F97recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_EQP.PERMITCD, &lCnt, 1);
	XcomMsgClose(lMsgId);
	//
	S2F98(lSysByte);
}
void CSecs::S2F98(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 2;
	nFunc = 98;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC2, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* Material Unload Report */
void CSecs::S3F53()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CStateManager *pStateManager = CStateManager::GetInstance();

	//strcpy(pDlg->m_POSITION[1].STICKID, pDlg->m_SLOT[pStateManager->GetMaskNo() - 1].STICKID);

	nStrm = 3;
	nFunc = 53;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	int nLsd;
	int numLSD = pDlg->m_LOT.NUMLSD;
	int nSlot;

	nSlot = pStateManager->GetMaskNo();	//0~9번임
	pDlg->m_LOT.SLOT[0] = nSlot + 1;	//1~10번
	pDlg->m_LOT.PORTID[0] = nUnloadPort;

	XcomList(lMsgId, 8);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.MCSTID, 20);
	XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].STICKID, 30);
	XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8);
	XcomBinary(lMsgId, pDlg->m_LOT.PORTID, 1);
	XcomBinary(lMsgId, pDlg->m_LOT.SLOT, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPE, 24);
	XcomList(lMsgId, numLSD);
	for (nLsd = 0; nLsd < numLSD; nLsd++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, pDlg->m_LSD[nLsd].ITEM, 24);
		XcomAscii(lMsgId, pDlg->m_LSD[nLsd].VALUE, 40);
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S3F54recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC3, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC3[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Mask Port Data Report  */
void CSecs::S3F63()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 3;
	nFunc = 63;
	int nGsd = 0;

	int nSlot = pDlg->m_EQP.PORTID[0];	//선택포트번호로..
	long numGsd = pDlg->m_SLOT[0].NUMGSD;

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	XcomList(lMsgId, 10);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.MASKID, 30);
	XcomAscii(lMsgId, pDlg->m_LOT.MASKSLOTID, 3);
	XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8);
	XcomBinary(lMsgId, pDlg->m_EQP.DICODE, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.MASKPROC, 1);
	XcomU2(lMsgId, &pDlg->m_LOT.MASKCODE_U2, 1);
	XcomList(lMsgId, numGsd);
	for (nGsd = 0; nGsd < numGsd; nGsd++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, pDlg->m_GSD[nSlot][nGsd].ITEM, 20);
		XcomAscii(lMsgId, pDlg->m_GSD[nSlot][nGsd].VALUE, 40);
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S3F64recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC3, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC3[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Material Location Data Send  */
void CSecs::S3F71()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 3;
	nFunc = 71;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	XcomList(lMsgId, 3);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.MLOTID, 30);
	XcomAscii(lMsgId, pDlg->m_LOT.MASKSLOTID, 3);
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S3F72recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC3, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC3[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Material Process Data Send */
void CSecs::S3F73()
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CStateManager *pStateManager = CStateManager::GetInstance();
	nStrm = 3;
	nFunc = 73;

	//HOST ONLINE CHECK
	if (pDlg->m_EQP.STATE[0] == '2')
		sprintf(pDlg->m_LOT.MODECODE, "%s", W2A(L"F"));
	else
		sprintf(pDlg->m_LOT.MODECODE, "%s", W2A(L"H"));

	int nSlot = pStateManager->GetMaskNo();	//SlotNo는 0~9번임

	//==============
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 8);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.MODECODE, 1);

	//XcomAscii(lMsgId, pDlg->m_LOT.MLOTID, 30);
	XcomAscii(lMsgId, pDlg->m_LOT.MLOTID, 30);	//LOTID대신 STICKID로 변경. 20180119 jinsuk -> Stick Item으로 변경-> MLOT ID로 변경 18
	//XcomAscii(lMsgId, pDlg->m_LOT.MCSTID, 30);	//확인용 위 삭제 이 line 추가 0724 서종천
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPE, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8); // 1203 E6 공정번호 10200(백광열선임) 고정
	XcomAscii(lMsgId, pDlg->m_LOT.KEYID, 32);

	XcomWriteLSD();	//Xcom에 LSD를 Write

	XcomWriteAPD();	//Xcom에 APD(stick정보+측정결과)를 Write

	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S3F74recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC3, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC3[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* MaterialEstimatedCancelReport */
void CSecs::S3F75()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	long numLSD = LSD_COUNT;
	int nLsd;
	char sItem[24] = "MLSDITEM";
	char sValue[40] = "MLSDVALUE";

	nStrm = 3;
	nFunc = 75;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.MLOTKIND, 8);
	XcomAscii(lMsgId, pDlg->m_LOT.MLOTID, 30);

	XcomList(lMsgId, numLSD);
	for (nLsd = 0; nLsd< numLSD; nLsd++)
	{
		XcomList(lMsgId, 2);
		/***추가수정필요***/
		XcomAscii(lMsgId, sItem, 24);
		XcomAscii(lMsgId, sValue, 40);
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S3F76recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC3, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC3[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* S3F81... Equipment Material State Report */
void CSecs::S3F81()
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 3;
	nFunc = 81;

	pDlg->m_EQP.PORTID[0] = 1;  //Loadport

	//==================================
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 10);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_LOT.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.MLOTKIND, 8);
	XcomAscii(lMsgId, pDlg->m_LOT.MCSTID, 20);
	XcomAscii(lMsgId, pDlg->m_LOT.MLOTID, 30);
	XcomAscii(lMsgId, pDlg->m_LOT.MLOTSTATE, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPE, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8);
	XcomBinary(lMsgId, pDlg->m_LOT.MQTY, 1);
	XcomList(lMsgId, pDlg->m_LOT.NUMLSD);	//L,p [ p = the number of LSD ] 
	for (int i = 0; i < pDlg->m_LOT.NUMLSD; i++) {
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, pDlg->m_LSD[i].ITEM, 24);
		XcomAscii(lMsgId, pDlg->m_LSD[i].VALUE, 40);
		//Total_Msg(_T("    LSD %s=[%s]"), A2W(pDlg->m_LSD[i].ITEM), A2W(pDlg->m_LSD[i].VALUE));
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S3F82recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC3, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC3[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

// Material Data Send 
void CSecs::S3F83recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	short i;
	long numLsd, numStick, numtemp;
	char sitem[251], svalue[251];
	WORD nU2;
	CString cStr;

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &nU2, &lCnt, 1);	//pDlg->m_EQP.UNITID
	XcomGetBinary(lMsgId, pDlg->m_LOT.PORTID, &lCnt, 1);		//port
	XcomGetAscii(lMsgId, pDlg->m_LOT.MLOTKIND, &lSize, 8);
	XcomGetAscii(lMsgId, pDlg->m_LOT.MCSTID, &lSize, 20);
	XcomGetAscii(lMsgId, pDlg->m_LOT.MLOTID, &lSize, 30);
	XcomGetAscii(lMsgId, pDlg->m_LOT.CMD, &lSize, 6);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPE, &lSize, 24);
	XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 8);
	XcomGetAscii(lMsgId, pDlg->m_LOT.MODECODE, &lSize, 1);
	XcomGetBinary(lMsgId, pDlg->m_LOT.MQTY, &lCnt, 1);

	pDlg->m_ECSMSG.ACKC3[0] = 0;

	XcomGetList(lMsgId, &numLsd);
	for (i = 0; i < numLsd; i++)
	{
		XcomGetList(lMsgId, &numtemp);
		XcomGetAscii(lMsgId, pDlg->m_LSD[i].ITEM, &lSize, 24);
		XcomGetAscii(lMsgId, pDlg->m_LSD[i].VALUE, &lSize, 40);
		Total_Msg(_T("RECV LSD %s=[%s]"), A2W(pDlg->m_LSD[i].ITEM), A2W(pDlg->m_LSD[i].VALUE));
	}
	if (lists == 12)
	{
		XcomGetList(lMsgId, &numStick);
		pDlg->nNumStick = numStick;
		for (i = 0; i < numStick && i < SLOT_COUNT; i++) {
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, pDlg->m_SLOT[i].STICKITEM, &lSize, 250);
			XcomGetAscii(lMsgId, pDlg->m_SLOT[i].STICKVALUE, &lSize, 250);
		}
	}
	//----
	XcomMsgClose(lMsgId);
	//
	S3F84(lSysByte);

	//LoadPort에 올렸을때만 LSD를 반영함
	//if (pDlg->m_PORT[nLoadPort].STATUS[0] == 'R')
	//{
		pDlg->m_LOT.NUMLSD = numLsd;
		ApplyLSD();
	//}
}
void CSecs::S3F84(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 3;
	long nFunc = 84;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC3, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* S3F87... Material ID Report */
void CSecs::S3F87()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 3;
	nFunc = 87;

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 5);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.MLOTKIND, 8);
	XcomAscii(lMsgId, pDlg->m_LOT.MCSTID, 20);
	XcomAscii(lMsgId, pDlg->m_LOT.MCSTTYPE, 5);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S3F88recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC3, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC3[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}


//All Material Position Data Report 
void CSecs::S3F91()
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	nStrm = 3;
	nFunc = 91;
	int nSheet, nPos;
	//
	long numPosition = POSITION_COUNT;				//Materialsheet count
	char matid[30] = "STICK";
	char matsheetid[30] = "";

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;

	XcomList(lMsgId, numPosition);
	for (nPos = 0; nPos < numPosition; nPos++)
	{
		XcomList(lMsgId, 4);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomBinary(lMsgId, pDlg->m_POSITION[nPos].ID, 1);
		XcomAscii(lMsgId, pDlg->m_POSITION[nPos].STICKID, 30);
		XcomList(lMsgId, 0);
		//for (nSheet = 0; nSheet < pDlg->m_POSITION[nPos].SHEETCOUNT[0]; nSheet++)
		//{
		//	XcomAscii(lMsgId, pDlg->m_POSITION[nPos].STICKID, 30);
		//}
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S3F92recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC1, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC3[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* S5F1...ErrorReport */
void CSecs::S5F1()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 5;
	nFunc = 1;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	//
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.ALCD, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.ALID, 10);
	XcomAscii(lMsgId, pDlg->m_EQP.ALTX, 120);
	XcomSend(lMsgId, nStrm, nFunc);
}

void CSecs::S5F1(BYTE alcd, char* alid, char* altx)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 5;
	nFunc = 1;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	//
	pDlg->m_EQP.ALCD[0] = alcd;
	strcpy(pDlg->m_EQP.ALID, alid);
	strcpy(pDlg->m_EQP.ALTX, altx);
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.ALCD, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.ALID, 10);
	XcomAscii(lMsgId, pDlg->m_EQP.ALTX, 120);
	XcomSend(lMsgId, nStrm, nFunc);
	if (1)//pDlg->m_EQP.ALID != "993" || pDlg->m_EQP.ALID != "994" || pDlg->m_EQP.ALID != "995" || pDlg->m_EQP.ALID != "996" )
	{//993~996 정지버튼시 클리어 되면 안됨
		for (int i = 0; i < 100; i++){
			if (pDlg->m_alram[i].existFlag == FALSE)
			{
				pDlg->m_alram[i].alcd[0] = pDlg->m_EQP.ALCD[0]-128;
				strcpy(pDlg->m_alram[i].alid, pDlg->m_EQP.ALID);
				strcpy(pDlg->m_alram[i].altx, pDlg->m_EQP.ALTX);
				pDlg->m_alram[i].existFlag = TRUE;
				break;
			}
		}
	}

	if (strcmp(pDlg->m_EQP.ALID, "6") != 0 && strcmp(pDlg->m_EQP.ALID, "993") != 0 && strcmp(pDlg->m_EQP.ALID, "996") != 0)
	{
		pDlg->m_EQP.STATUS[0] = 'D';
		S6F91();
	}
}

void CSecs::S5F1RESET(BYTE alcd, char* alid, char* altx){
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 5;
	nFunc = 1;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	//
	pDlg->m_EQP.ALCD[0] = alcd;
	strcpy(pDlg->m_EQP.ALID, alid);
	strcpy(pDlg->m_EQP.ALTX, altx);
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.ALCD, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.ALID, 10);
	XcomAscii(lMsgId, pDlg->m_EQP.ALTX, 120);
	XcomSend(lMsgId, nStrm, nFunc);
	
	if (pDlg->m_EQP.ALID != "6" || pDlg->m_EQP.ALID != "993" || pDlg->m_EQP.ALID != "996")
	{
		pDlg->m_EQP.STATUS[0] = 'I';
		S6F91();
	}
}
void CSecs::S5F2recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC5, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC5[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}


/* Chemical Change Enable Send */
void CSecs::S6F61()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 6;
	nFunc = 61;
	int nStage;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomList(lMsgId, STAGE_COUNT);
	for (nStage = 0; nStage < STAGE_COUNT; nStage++){
		XcomBinary(lMsgId, pDlg->m_STAGE[nStage].STAGEID, 1);
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S6F62recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Unload Glass Data Report  */
void CSecs::S6F63()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 6;
	nFunc = 63;
	char sItem[25];
	char sValue[41];
	long numStage = 0;
	int nStage, nSubgls, nGsd;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomList(lMsgId, numStage);
	for (nStage = 0; nStage < numStage; nStage++)
	{
		XcomList(lMsgId, 24);
		XcomBinary(lMsgId, pDlg->m_STAGE[nStage].STAGEID, 1);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].GLSODR, 1);
		XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
		XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
		XcomAscii(lMsgId, pDlg->m_LOT.CSTID, 14);
		XcomAscii(lMsgId, pDlg->m_LOT.SLOTID, 3);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].GLSID, 16);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].PNLIF, 800);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].SUBMDLIF, 400);
		XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8);
		XcomBinary(lMsgId, pDlg->m_EQP.DICODE, 1);
		XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
		XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].GLSJUDGE, 2);
		XcomAscii(lMsgId, pDlg->m_LOT.PARTNUM, 14);
		XcomAscii(lMsgId, pDlg->m_LOT.PRODTYPE, 16);
		XcomAscii(lMsgId, pDlg->m_LOT.ATTRIBUTE, 12);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].GLSTYPE, 1);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].GLSPROC, 1);
		XcomU2(lMsgId, &pDlg->m_GLASS[nStage].GLSCODE, 1);
		XcomU2(lMsgId, &pDlg->m_GLASS[nStage].DEST, 1);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].KEYID, 32);
		XcomList(lMsgId, SUBGLS_COUNT);
		for (nSubgls = 0; nSubgls < SUBGLS_COUNT; nSubgls++){
			XcomList(lMsgId, 3);
			XcomAscii(lMsgId, pDlg->m_SUBGLS[nStage][nSubgls].SUBGLSID, 16);
			XcomAscii(lMsgId, pDlg->m_SUBGLS[nStage][nSubgls].SUBGLSJUDGE, 2);
			XcomAscii(lMsgId, pDlg->m_SUBGLS[nStage][nSubgls].SUBPNLIF, 400);
		}
		XcomList(lMsgId, GSD_COUNT);
		for (nGsd = 0; nGsd < GSD_COUNT; nGsd++){
			XcomList(lMsgId, 2);
			/************/
			XcomAscii(lMsgId, sItem, 24);
			XcomAscii(lMsgId, sValue, 40);
		}
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
void CSecs::S6F64recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/*  LOT End Data Send   */
void CSecs::S6F65recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lists, lCnt, lSize, numSlot, numSubgls;
	nStrm = 6;
	nFunc = 65;
	long numStage = 0;
	int nSlot, nSubgls;

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.STAGEID, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 1);
	XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_EQP.ENDFLAG, &lSize, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.MULTIFLAG, &lSize, 1);

	XcomGetList(lMsgId, &numSlot);
	for (nSlot = 0; nSlot < numSlot; nSlot++)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nSlot].GLSODR, &lSize, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.SLOTID, &lSize, 3);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nSlot].GLSID, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 24);
		XcomGetBinary(lMsgId, pDlg->m_SLOT[nSlot].GLSEXIST, &lCnt, 1);
		XcomGetBinary(lMsgId, pDlg->m_SLOT[nSlot].GLSSELECTED, &lCnt, 1);
		XcomGetBinary(lMsgId, pDlg->m_SLOT[nSlot].GLSEXIST, &lCnt, 1);
		XcomGetU2(lMsgId, &pDlg->m_SLOT[nSlot].PROCUNITID, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nSlot].GLSJUDGE, &lSize, 2);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nSlot].PNLIF, &lSize, 800);
		XcomGetAscii(lMsgId, pDlg->m_GLASS[nSlot].SUBMDLIF, &lSize, 400);
		XcomGetList(lMsgId, &numSubgls);
		for (nSubgls = 0; nSubgls < numSubgls; nSubgls++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nSlot][nSubgls].SUBGLSID, &lSize, 16);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nSlot][nSubgls].SUBGLSJUDGE, &lSize, 2);
			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nSlot][nSubgls].SUBPNLIF, &lSize, 400);
		}
	}
	XcomMsgClose(lMsgId);
	//
	S6F66(lSysByte);
}
void CSecs::S6F66(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 6;
	nFunc = 66;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte)) return;
	XcomList(lMsgId, 5);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Glass Move Request  */
void CSecs::S6F67()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 6;
	nFunc = 67;
	long numStage = STAGE_COUNT;
	int nStage;

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomList(lMsgId, numStage);
	for (nStage = 0; nStage < numStage; nStage++)
	{
		XcomList(lMsgId, 6);
		XcomBinary(lMsgId, pDlg->m_STAGE[nStage].STAGEID, 1);
		XcomAscii(lMsgId, pDlg->m_STAGE[nStage].GLSMVSTATUS, 1);
		XcomU2(lMsgId, &pDlg->m_STAGE[nStage].LDGLSCODE, 1);
		XcomU2(lMsgId, &pDlg->m_STAGE[nStage].UDGLSCODE, 1);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].GLSID, 16);
		XcomAscii(lMsgId, pDlg->m_GLASS[nStage].GLSJUDGE, 2);
	}
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg
}
/* recv ACKC6  */
void CSecs::S6F68recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Cassette Map Request  */
void CSecs::S6F69()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 6;
	nFunc = 69;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S6F70recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists, lSize;
	int nCass;

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	for (nCass = 0; nCass < CASSETTE_COUNT; nCass++)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
		XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_CASSETTE[nCass].CSTID, &lSize, 14);
		XcomGetBinary(lMsgId, pDlg->m_CASSETTE[nCass].ID, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_CASSETTE[nCass].MAP, &lSize, 40);
		XcomGetAscii(lMsgId, pDlg->m_CASSETTE[nCass].CSTREADY, &lSize, 1);
	}
	XcomMsgClose(lMsgId);
}

/* Sampling Slot Request  */
void CSecs::S6F71()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	int nStage = 0;	//수정필요
	nStrm = 6;
	nFunc = 71;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 3);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_STAGE[nStage].STAGEID, 1);
	XcomList(lMsgId, 5);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.CSTID, 14);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.SLOTID, 3);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* recv ACKC6A  */
void CSecs::S6F72recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6A, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6A[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}


/* Glass Actual Processing Data Report  */
void CSecs::S6F73()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	int nSubgls, nGsd, nParam;
	int nGls = 0;	//수정필요
	long numParam = 0;

	char sItem[24], sValue[40];

	nStrm = 6;
	nFunc = 73;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;

	XcomList(lMsgId, 9);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.CSTID, 14);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8);
	XcomAscii(lMsgId, pDlg->m_LOT.SLOTID, 3);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomList(lMsgId, 8);
	XcomAscii(lMsgId, pDlg->m_GLASS[nGls].GLSID, 16);
	XcomAscii(lMsgId, pDlg->m_GLASS[nGls].GLSJUDGE, 2);
	XcomAscii(lMsgId, pDlg->m_GLASS[nGls].PNLIF, 800);
	XcomAscii(lMsgId, pDlg->m_GLASS[nGls].SUBMDLIF, 400);
	XcomU2(lMsgId, &pDlg->m_GLASS[nGls].GLSCODE, 1);
	XcomAscii(lMsgId, pDlg->m_GLASS[nGls].KEYID, 32);
	XcomList(lMsgId, SUBGLS_COUNT);
	for (nSubgls = 0; nSubgls < SUBGLS_COUNT; nSubgls++)
	{
		XcomList(lMsgId, 3);
		XcomAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBGLSID, 16);
		XcomAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBGLSJUDGE, 2);
		XcomAscii(lMsgId, pDlg->m_SUBGLS[nGls][nSubgls].SUBPNLIF, 400);
	}
	XcomList(lMsgId, GSD_COUNT);
	for (nGsd = 0; nGsd < GSD_COUNT; nGsd++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, sItem, 24);
		XcomAscii(lMsgId, sValue, 40);
		/***추가코딩필요***/
	}

	XcomList(lMsgId, numParam);
	for (nParam = 0; nParam < numParam; nParam++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, sItem, 24);
		XcomAscii(lMsgId, sValue, 40);
		/***추가코딩필요***/
	}
	XcomSend(lMsgId, nStrm, nFunc);
}

/* recv ACKC6  */
void CSecs::S6F74recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Glass Actual Processing Data Report  */
void CSecs::S6F83()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	int nParam;
	int nLsd;
	int nGls = 0;
	long numParam = 0;
	long numLsd = LSD_COUNT;
	char sItem[24], sValue[40], sName[40];

	nStrm = 6;
	nFunc = 83;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;

	XcomList(lMsgId, 10);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomAscii(lMsgId, pDlg->m_LOT.CSTID, 14);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomAscii(lMsgId, pDlg->m_GLASS[nGls].KEYID, 16);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTJUDGE, 2);
	XcomList(lMsgId, numLsd);
	for (nLsd = 0; nLsd < numLsd; nLsd++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, sItem, 24);
		XcomAscii(lMsgId, sValue, 40);
		/***추가코딩필요***/
	}
	XcomList(lMsgId, numParam);
	for (nParam = 0; nParam < numParam; nParam++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, sName, 40);
		XcomAscii(lMsgId, sValue, 40);
		/***추가코딩필요***/
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
/* recv ACKC6  */
void CSecs::S6F84recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Dummy Lot Request  */
void CSecs::S6F85()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	nStrm = 6;
	nFunc = 85;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
/* recv ACKC6  */
void CSecs::S6F86recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Rework Request */
void CSecs::S6F89()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId, numSlot = SLOT_COUNT;
	int nSlot;
	nStrm = 6;
	nFunc = 89;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 5);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.RESERVECD, 1);

	XcomList(lMsgId, numSlot);
	for (nSlot = 0; nSlot < numSlot; nSlot++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].SLOTID, 3);
		XcomBinary(lMsgId, pDlg->m_SLOT[nSlot].SELECTED, 1);
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
/* recv ACKC6  */
void CSecs::S6F90recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Equipment Status Change Report */
void CSecs::S6F91()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId;
	char STATUSPRE = pDlg->m_EQP.STATUS[0];
	char STATUS = pDlg->m_EQP.STATUS[0];
	nStrm = 6;
	nFunc = 91;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	//
	XcomList(lMsgId, 4);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.STATUS, 1);	// STATUS
	if (STATUS == 'R' || STATUS == 'I')
	{
		sprintf(pDlg->m_EQP.ALID, "0");
		sprintf(pDlg->m_EQP.ALTX, "");
	}
	XcomAscii(lMsgId, pDlg->m_EQP.ALID, 10);	// ALID
	XcomAscii(lMsgId, pDlg->m_EQP.ALTX, 120);	// ALTX

	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg

}
void CSecs::S6F92recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}


/* Equipment Status Change Report */
void CSecs::S6F93()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId, numSlot = SLOT_COUNT;
	nStrm = 6;
	nFunc = 93;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 6);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.GLSID, 16);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.SCRPTYPE, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.SCRPCODE, 4);
	XcomSend(lMsgId, nStrm, nFunc);
}
/* recv ACKC6  */
void CSecs::S6F94recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Equipment Status Change Report */
void CSecs::S6F95()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId, numSlot = SLOT_COUNT;
	nStrm = 6;
	nFunc = 95;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.OCRSTATUS, 1);
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S6F96recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Chamber Status Change Report  */
void CSecs::S6F97()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numChamber = CHAMBER_COUNT;
	int nCham;
	nStrm = 6;
	nFunc = 97;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, numChamber);
	for (nCham = 0; nCham < numChamber; nCham++)
	{
		XcomList(lMsgId, 2);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomAscii(lMsgId, pDlg->m_CHAMBER[nCham].CMSTATUS, 1);
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S6F98recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numChamber;
	int nCham;
	WORD unitid;

	XcomGetList(lMsgId, &numChamber);
	for (nCham = 0; nCham < numChamber; nCham++)
	{
		XcomList(lMsgId, 2);
		XcomU2(lMsgId, &unitid, 1);
		XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC6, 1);
	}
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC6[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Current EPPD Request */
void CSecs::S7F19recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomMsgClose(lMsgId);
	//----
	S7F20(lSysByte);
}
void CSecs::S7F20(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 7;
	long nFunc = 62;
	char recipe[24] = "recipe";	//수정필요
	long numRecipe = 0;	//수정필요
	int nRecipe;

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomList(lMsgId, numRecipe);
	for (nRecipe = 0; nRecipe < numRecipe; nRecipe++){
		XcomAscii(lMsgId, recipe, 24);
	}
	XcomReply(lMsgId, nStrm, nFunc);
}


/* Recipe ID Confirm Request */
void CSecs::S7F61recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int nLsd, nSlot, nSubgls, nGsd;
	long numLsd, numSlot, numSubgls, numGsd;
	CString strItem, strValue;

	XcomGetList(lMsgId, &lists);
	if (lists == 15) {
		XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
		XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 24);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 8);
		XcomGetBinary(lMsgId, pDlg->m_LOT.PORTID, &lCnt, 1);
		XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.GLSTHICK, &lSize, 5);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PARTNUM, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PRODTYPE, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_LOT.ATTRIBUTE, &lSize, 12);
		XcomGetAscii(lMsgId, pDlg->m_LOT.MODECODE, &lSize, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.MULTIFLAG, &lSize, 1);
		XcomGetList(lMsgId, &numLsd);
		//pDlg->m_LOT.NUMLSD = numLsd;
		//for (nLsd = 0; nLsd < numLsd; nLsd++) {
		//	XcomGetList(lMsgId, &lists);
		//	XcomGetAscii(lMsgId, pDlg->m_LSD[nLsd].ITEM, &lSize, 24);
		//	XcomGetAscii(lMsgId, pDlg->m_LSD[nLsd].VALUE, &lSize, 40);
		//}
		XcomGetList(lMsgId, &numSlot);
		//pDlg->m_LOT.NUMSLOT = numSlot;
		//for (nSlot = 0; nSlot < numSlot; nSlot++) {
		//	XcomGetList(lMsgId, &lists);
		//	if (lists == 11){
		//		XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].SLOTID, &lSize, 3);
		//		XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].SLTLOTID, &lSize, 16);
		//		XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].GLSID, &lSize, 16);
		//		XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].SRECIPEID, &lSize, 24);
		//		XcomGetBinary(lMsgId, pDlg->m_SLOT[nSlot].GLSEXIST, &lSize, 1);
		//		XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].GLSJUDGE, &lSize, 2);
		//		XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].PARTNUM, &lSize, 14);
		//		XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].PNLIF, &lSize, 800);
		//		XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].SUBMDLIF, &lSize, 400);
		//		XcomGetList(lMsgId, &numSubgls);
		//		pDlg->m_SLOT[nSlot].NUMSUBGLS = numSubgls;
		//		for (nSubgls = 0; nSubgls < numSubgls; nSubgls++)
		//		{
		//			XcomGetList(lMsgId, &lists);
		//			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nSlot][nSubgls].SUBGLSID, &lSize, 16);
		//			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nSlot][nSubgls].SUBGLSJUDGE, &lSize, 2);
		//			XcomGetAscii(lMsgId, pDlg->m_SUBGLS[nSlot][nSubgls].SUBPNLIF, &lSize, 400);
		//		}
		//		XcomGetList(lMsgId, &numGsd);
		//		pDlg->m_SLOT[nSlot].NUMGSD = numGsd;
		//		for (nGsd = 0; nGsd < numGsd; nGsd++)
		//		{
		//			XcomGetList(lMsgId, &lists);
		//			XcomGetAscii(lMsgId, pDlg->m_GSD[nSlot][nGsd].ITEM, &lSize, 24);
		//			XcomGetAscii(lMsgId, pDlg->m_GSD[nSlot][nGsd].VALUE, &lSize, 40);
		//		}
		//	}
		//}
	}
	//----
	XcomMsgClose(lMsgId);
	//----
	S7F62(lSysByte);
}
void CSecs::S7F62(long lSysByte)
{
	USES_CONVERSION;
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int nSlot;
	long numSlot;
	long nStrm = 7;
	long nFunc = 62;

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 8);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_LOT.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomAscii(lMsgId, pDlg->m_EQP.SAMPLINGFLAG, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC7M, 1);

	numSlot = pDlg->m_LOT.NUMSLOT;
	XcomList(lMsgId, numSlot);
	for (nSlot = 0; nSlot < numSlot; nSlot++){
		XcomList(lMsgId, 3);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].SLOTID, 3);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].SRECIPEID, 24);
		XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC7S, 1);
	}
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Sampling Data Report  */
void CSecs::S7F63()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long  lMsgId, numSlot = SLOT_COUNT;
	int nSlot;
	nStrm = 7;
	nFunc = 63;
	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
	XcomList(lMsgId, 6);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);

	XcomList(lMsgId, numSlot);
	for (nSlot = 0; nSlot < numSlot; nSlot++)
	{
		XcomList(lMsgId, 4);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].SLOTID, 3);
		XcomAscii(lMsgId, pDlg->m_SLOT[nSlot].SRECIPEID, 24);
		XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC7S, 1);
		XcomBinary(lMsgId, pDlg->m_SLOT[nSlot].SELECTED, 1);
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
/* recv ACKC6  */
void CSecs::S7F64recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lCnt, 16);
	XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_ECSMSG.ACKC7, &lCnt, 1);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_ECSMSG.ACKC7[0]);
	XcomAck(strAck);
	XcomMsgClose(lMsgId);
}

/* Current Recipe Group List Request  */
void CSecs::S7F67recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomMsgClose(lMsgId);
	//----
	S7F68(lSysByte);
}
void CSecs::S7F68(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int nGroup;
	long numGroup = 0;
	long nStrm = 7;
	long nFunc = 68;
	char strGroup[12] = "group";

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomList(lMsgId, numGroup);
	for (nGroup = 0; nGroup < numGroup; nGroup++){
		XcomAscii(lMsgId, strGroup, 12);
	}
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Current Recipe ID List Request by Grou  */
void CSecs::S7F69recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lCnt, lists, lSize;
	char strGroupid[12];
	long numGroup;
	int nGroup;
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetList(lMsgId, &numGroup);
	for (nGroup = 0; nGroup < numGroup; nGroup++){
		XcomGetAscii(lMsgId, strGroupid, &lSize, 12);
		/****/
	}
	XcomMsgClose(lMsgId);
	//----
	S7F70(lSysByte);
}
void CSecs::S7F70(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lMsgId;
	long numGroup = 0;
	int nGroup;
	long nStrm = 7;
	long nFunc = 70;
	char strGroupid[12] = "group";		//추가수정필요

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomList(lMsgId, numGroup);
	for (nGroup = 0; nGroup < numGroup; nGroup++){
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, strGroupid, 12);
		XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
		/***추가수정필요***/
	}
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Recipe Body Request  */
void CSecs::S7F77recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lists, lSize, lCnt;

	XcomGetList(lMsgId, &lists);
	if (lists == 8) {
		XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
		XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 24);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 8);
		XcomGetBinary(lMsgId, pDlg->m_LOT.PORTID, &lCnt, 1);
		XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PRODTYPE, &lSize, 16);
	}
	//----
	XcomMsgClose(lMsgId);
	S7F78(lSysByte);
}
void CSecs::S7F78(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 7;
	long nFunc = 78;

	int nStep, nUnit, nParm;
	long numUnit = 0, numStep = 0, numParm = 0;	//수정필요
	char strStep[15] = "";			//수정필요
	char sName[25];
	char sValue[25];

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 9);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.CSTID, 14);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.PRODTYPE, 16);
	XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomList(lMsgId, numUnit);
	for (nUnit = 0; nUnit < numUnit; nUnit++){
		XcomList(lMsgId, 6);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomAscii(lMsgId, pDlg->m_EQP.LOWERRECIPEID, 24);
		XcomAscii(lMsgId, pDlg->m_EQP.LOWERRECIPEIDVER, 12);
		XcomAscii(lMsgId, pDlg->m_EQP.LEVEL, 1);
		XcomAscii(lMsgId, pDlg->m_EQP.RECIPEIDTYPE, 1);
		XcomList(lMsgId, numStep);
		for (nStep = 0; nStep < numStep; nStep++){
			XcomList(lMsgId, 2);
			XcomAscii(lMsgId, strStep, 14);
			XcomList(lMsgId, numParm);
			for (nParm = 0; nParm < numParm; nParm++){
				XcomList(lMsgId, 2);
				XcomAscii(lMsgId, sName, 24);
				XcomAscii(lMsgId, sValue, 24);
				/***추가코딩필요***/
			}
		}
	}
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Multi Recipe Information Send */
void CSecs::S7F79recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numSlot;
	int nSlot;
	XcomGetList(lMsgId, &lists);
	if (lists == 5) {
		XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
		XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
		XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
		XcomGetU2(lMsgId, &pDlg->m_LOT.LOTNUMBER, &lCnt, 1);
		XcomGetList(lMsgId, &numSlot);
		for (nSlot = 0; nSlot < numSlot; nSlot++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, pDlg->m_SLOT[nSlot].SLOTID, &lSize, 3);
			XcomGetBinary(lMsgId, pDlg->m_SLOT[nSlot].SELECTED, &lCnt, 1);
			XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 24);
			XcomGetBinary(lMsgId, pDlg->m_SLOT[nSlot].SAMPLECODE, &lCnt, 1);
		}
	}
	//----
	XcomMsgClose(lMsgId);
	S7F80(lSysByte);
}
void CSecs::S7F80(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 7;
	long nFunc = 80;

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC7, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Equipment Constant Recipe Request */
void CSecs::S7F81recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	XcomGetList(lMsgId, &lists);
	if (lists == 6) {
		XcomGetAscii(lMsgId, pDlg->m_LOT.LOTID, &lSize, 16);
		XcomGetAscii(lMsgId, pDlg->m_LOT.CSTID, &lSize, 14);
		XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lSize, 24);
		XcomGetAscii(lMsgId, pDlg->m_LOT.PRCID, &lSize, 8);
		XcomGetBinary(lMsgId, pDlg->m_EQP.PORTID, &lCnt, 1);
		XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	}
	//----
	XcomMsgClose(lMsgId);
	//
	S7F82(lSysByte);
}
void CSecs::S7F82(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 7;
	long nFunc = 82;
	int nUnit, nStep, nPara;
	long numUnit = 1;
	long numStep = 0, numPara = 0;
	char sStep[14] = "step";
	char sName[24], sValue[24];

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 8);
	XcomAscii(lMsgId, pDlg->m_LOT.LOTID, 16);
	XcomAscii(lMsgId, pDlg->m_LOT.CSTID, 14);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, 12);
	XcomAscii(lMsgId, pDlg->m_LOT.PRCID, 8);
	XcomBinary(lMsgId, pDlg->m_EQP.PORTID, 1);
	XcomU2(lMsgId, &pDlg->m_EQP.CONTROLID, 1);
	XcomList(lMsgId, numUnit);
	for (nUnit = 0; nUnit < numUnit; nUnit++)
	{
		XcomList(lMsgId, 6);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomAscii(lMsgId, pDlg->m_EQP.LOWERRECIPEID, 24);
		XcomAscii(lMsgId, pDlg->m_EQP.LOWERRECIPEIDVER, 12);
		XcomAscii(lMsgId, pDlg->m_EQP.LEVEL, 1);
		XcomAscii(lMsgId, pDlg->m_EQP.RECIPEIDTYPE, 1);
		XcomList(lMsgId, numStep);
		for (nStep = 0; nStep < numStep; nStep++)
		{
			XcomList(lMsgId, 2);
			XcomAscii(lMsgId, sStep, 14);
			XcomList(lMsgId, numPara);
			for (nPara = 0; nPara < numPara; nPara++)
			{
				XcomList(lMsgId, 2);
				XcomAscii(lMsgId, sName, 24);
				XcomAscii(lMsgId, sValue, 24);
				/***추가수정필요****/
			}
		}
	}
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Unrecognized Device ID  */
void CSecs::S9F1()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lMsgId;
	long nStrm = 9;
	long nFunc = 1;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* Unrecognized Stream Type  */
void CSecs::S9F3()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lMsgId;
	long nStrm = 9;
	long nFunc = 3;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* Unrecognized Function Type  */
void CSecs::S9F5()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lMsgId;
	long nStrm = 9;
	long nFunc = 5;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* Illegal Data  */
void CSecs::S9F7()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lMsgId;
	long nStrm = 9;
	long nFunc = 7;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* Transaction Timer Timeout  */
void CSecs::S9F9()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lMsgId;
	long nStrm = 9;
	long nFunc = 9;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* Data Too Long  */
void CSecs::S9F11()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lMsgId;
	long nStrm = 9;
	long nFunc = 11;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* Conversation Timeout  */
void CSecs::S9F13()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long lMsgId;
	long nStrm = 9;
	long nFunc = 13;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0);
	XcomList(lMsgId, 2);
	XcomAscii(lMsgId, pDlg->m_EQP.MEXP, 6);
	XcomAscii(lMsgId, pDlg->m_EQP.EDID, 14);
	XcomSend(lMsgId, nStrm, nFunc);
}

/* Terminal Display, Single  */
void CSecs::S10F3recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	BYTE TID[1];
	char TEXT[80];
	XcomGetList(lMsgId, &lists);
	XcomGetBinary(lMsgId, TID, &lCnt, 1);
	XcomGetAscii(lMsgId, TEXT, &lSize, 80);
	XcomMsgClose(lMsgId);
	//
	S10F4(lSysByte);
}
void CSecs::S10F4(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 10;
	long nFunc = 4;
	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomBinary(lMsgId, pDlg->m_ECSMSG.ACKC10, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Current Recipe ID List Request   */
void CSecs::S15F65recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomMsgClose(lMsgId);
	//
	S15F66(lSysByte);
}
void CSecs::S15F66(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 15;
	long nFunc = 66;
	long numRecipe = 1, numRver = 1;
	int nRecipe, nRver;

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomList(lMsgId, numRecipe);
	for (nRecipe = 0; nRecipe < numRecipe; nRecipe++)
	{
		XcomList(lMsgId, 3);
		XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
		XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, 1);
		XcomList(lMsgId, numRver);
		for (nRver = 0; nRver < numRver; nRver++)
		{
			XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, 12);
		}
	}
	XcomReply(lMsgId, nStrm, nFunc);
}


/* Recipe List Report Request  */
void CSecs::S15F71recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numEsd;;
	int nEsd;
	char sItem[24], sValue[40];

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_EQP.LEVEL, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, &lCnt, 1);
	XcomGetList(lMsgId, &numEsd);
	for (nEsd = 0; nEsd < numEsd; nEsd++)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, sItem, &lCnt, 24);
		XcomGetAscii(lMsgId, sValue, &lCnt, 40);
		/***추가수정필요***/
	}
	XcomMsgClose(lMsgId);
	//
	S15F72(lSysByte);
}
void CSecs::S15F72(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 15;
	long nFunc = 72;
	int nRecipe, nRver, nEsd;
	long numRecipe = 1, numRver = 1;
	long numEsd = 0;
	char sName[24], sValue[40];

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomList(lMsgId, numRecipe);
	for (nRecipe = 0; nRecipe < numRecipe; nRecipe++)
	{
		XcomList(lMsgId, 5);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
		XcomAscii(lMsgId, pDlg->m_EQP.LEVEL, 1);
		XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, 1);
		XcomList(lMsgId, numRver);
		for (nRver = 0; nRver < numRver; nRver++)
		{
			XcomList(lMsgId, 2);
			XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, 12);
			XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDSTATUS, 1);
		}
	}
	XcomList(lMsgId, numEsd);
	for (nEsd = 0; nEsd < numEsd; nEsd++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, sName, 24);	//ESDITEM
		XcomAscii(lMsgId, sValue, 40);
		/***추가수정필요****/
	}
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Lower Recipe List Report Request  */
void CSecs::S15F73recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numEsd;;
	int nEsd;
	char sItem[24], sValue[40];

	XcomGetList(lMsgId, &lists);
	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lCnt, 24);
	XcomGetAscii(lMsgId, pDlg->m_EQP.LEVEL, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, &lCnt, 12);
	XcomGetList(lMsgId, &numEsd);
	for (nEsd = 0; nEsd < numEsd; nEsd++)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, sItem, &lCnt, 24);
		XcomGetAscii(lMsgId, sValue, &lCnt, 40);
		/***추가수정필요***/
	}
	XcomMsgClose(lMsgId);
	//
	S15F74(lSysByte);
}
void CSecs::S15F74(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 15;
	long nFunc = 74;
	int nRecipe, nRver, nEsd;
	long numRecipe = 1, numRver = 1;
	long numEsd = 0;
	char sName[24], sValue[40];

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomList(lMsgId, numRecipe);
	for (nRecipe = 0; nRecipe < numRecipe; nRecipe++)
	{
		XcomList(lMsgId, 5);
		XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
		XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
		XcomAscii(lMsgId, pDlg->m_EQP.LEVEL, 1);
		XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, 1);
		XcomList(lMsgId, numRver);
		for (nRver = 0; nRver < numRver; nRver++)
		{
			XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, 12);
		}
	}
	XcomList(lMsgId, numEsd);
	for (nEsd = 0; nEsd < numEsd; nEsd++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, sName, 24);	//ESDITEM
		XcomAscii(lMsgId, sValue, 40);
		/***추가수정필요****/
	}
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Recipe Parameter Report Request  */
void CSecs::S15F75recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numEsd;;
	int nEsd;
	char sItem[24], sValue[40];

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lCnt, 24);
	XcomGetAscii(lMsgId, pDlg->m_EQP.LEVEL, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, &lCnt, 12);
	XcomGetList(lMsgId, &numEsd);
	for (nEsd = 0; nEsd < numEsd; nEsd++)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, sItem, &lCnt, 24);
		XcomGetAscii(lMsgId, sValue, &lCnt, 40);
		/***추가수정필요***/
	}
	XcomMsgClose(lMsgId);
	//
	S15F76(lSysByte);
}
void CSecs::S15F76(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 15;
	long nFunc = 76;
	int nParm, nEsd, nStep;
	long numParm = 1;
	long numEsd = 0, numStep = 0;

	char parName[24] = "paramname";
	char parValue[24] = "parmavlaue";
	char esdItem[24] = "esditem";
	char esdValue[40] = "esdvalue";
	char sStep[14] = "step";

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 2);
	XcomList(lMsgId, 6);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_EQP.LEVEL, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, 12);

	XcomList(lMsgId, numStep);
	for (nStep = 0; nStep < numStep; nStep++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, sStep, 14);
		XcomList(lMsgId, numParm);
		for (nParm = 0; nParm < numParm; nParm++)
		{
			XcomList(lMsgId, 2);
			XcomAscii(lMsgId, parName, 24);	//PPARMNAME
			XcomAscii(lMsgId, parValue, 24);
			/***추가수정필요****/
		}
	}
	XcomList(lMsgId, numEsd);
	for (nEsd = 0; nEsd < numEsd; nEsd++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, esdItem, 24);	//ESDITEM
		XcomAscii(lMsgId, esdValue, 40);
		/***추가수정필요****/
	}
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Recipe Parameter Change Send  */
void CSecs::S15F77recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long numEsd, numPara, numStep = 0;
	int nStep, nPara, nEsd;
	char parName[24], parValue[24];
	char esdItem[24], esdValue[40];
	char sStep[14];

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDCMD, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lCnt, 24);
	XcomGetAscii(lMsgId, pDlg->m_EQP.LEVEL, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, &lCnt, 12);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, &lCnt, 1);
	XcomGetList(lMsgId, &numStep);
	for (nStep = 0; nStep < numStep; nStep++)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, sStep, &lCnt, 14);
		XcomGetList(lMsgId, &numPara);
		for (nPara = 0; nPara < numPara; nPara++)
		{
			XcomGetList(lMsgId, &lists);
			XcomGetAscii(lMsgId, parName, &lCnt, 24);
			XcomGetAscii(lMsgId, parValue, &lCnt, 24);
			/***추가수정필요***/
		}
		/***추가수정필요***/
	}

	XcomGetList(lMsgId, &numEsd);
	for (nEsd = 0; nEsd < numEsd; nEsd++)
	{
		XcomGetList(lMsgId, &lists);
		XcomGetAscii(lMsgId, esdItem, &lCnt, 24);
		XcomGetAscii(lMsgId, esdValue, &lCnt, 40);
		/***추가수정필요***/
	}
	XcomMsgClose(lMsgId);
	//
	S15F78(lSysByte);
}
void CSecs::S15F78(long lSysByte)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 15;
	long nFunc = 78;

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, lSysByte);
	XcomList(lMsgId, 6);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_EQP.LEVEL, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, 12);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, 1);
	XcomBinary(lMsgId, pDlg->m_EQP.REACK, 1);
	XcomReply(lMsgId, nStrm, nFunc);
}

/* Recipe Parameter Change Report */
void CSecs::S15F79()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	long nStrm = 15;
	long nFunc = 79;
	long numEsd = 0, numPara = 0, numStep = 0;
	int nStep, nPara, nEsd;
	char parName[24] = "paramname";
	char parValue[24] = "parmavlaue";
	char esdItem[24] = "esditem";
	char esdValue[40] = "esdvalue";
	char sStep[14] = "step";

	XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0);
	XcomList(lMsgId, 8);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDCMD, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);
	XcomAscii(lMsgId, pDlg->m_EQP.LEVEL, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, 12);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, 1);
	XcomList(lMsgId, numStep);
	for (nStep = 0; nStep < numStep; nStep++)
	{
		XcomList(lMsgId, 2);
		XcomAscii(lMsgId, sStep, 14);
		XcomList(lMsgId, numPara);
		for (nPara = 0; nPara < numPara; nPara++)
		{
			XcomList(lMsgId, 2);
			/**추가수정필요**/
			XcomAscii(lMsgId, parName, 24);
			XcomAscii(lMsgId, parValue, 24);
		}
	}
	XcomList(lMsgId, numEsd);
	for (nEsd = 0; nEsd < numEsd; nEsd++)
	{
		XcomList(lMsgId, 2);
		/**추가수정필요**/
		XcomAscii(lMsgId, esdItem, 24);
		XcomAscii(lMsgId, esdValue, 40);
	}
	XcomSend(lMsgId, nStrm, nFunc);
}
void CSecs::S15F80recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	XcomGetList(lMsgId, &lists);
	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEID, &lCnt, 24);
	XcomGetAscii(lMsgId, pDlg->m_EQP.LEVEL, &lCnt, 1);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDVER, &lCnt, 12);
	XcomGetAscii(lMsgId, pDlg->m_LOT.RECIPEIDTYPE, &lCnt, 1);
	XcomGetBinary(lMsgId, pDlg->m_EQP.PHACK, &lCnt, 1);
	XcomMsgClose(lMsgId);
	strAck.Format(_T("   Receive Ack : %d "), pDlg->m_EQP.PHACK[0]);
	XcomAck(strAck);
}
/* S15F75... SEND DATA */
void CSecs::S15F75A(float dx[], float dy[], int xlength, int ylength)
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	long  lMsgId;
	nStrm = 15;
	nFunc = 75;

	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;	//MakeMsg
	//
	XcomList(lMsgId, 6);
	XcomU2(lMsgId, &pDlg->m_EQP.UNITID, 1);
	XcomAscii(lMsgId, pDlg->m_LOT.RECIPEID, 24);		// recpieid 
	XcomAscii(lMsgId, L"a", 1);							// level
	XcomAscii(lMsgId, L"b", 1);							// type 
	XcomAscii(lMsgId, L"abcd", 12);						// RECIPEIDVER 
	XcomList(lMsgId, xlength * 2);		// L n 
	for (int i = 0; i < xlength; i++){
		XcomList(lMsgId, 2);			// L 2
		XcomAscii(lMsgId, L"dx", 24);					// ESDITEM
		XcomAscii(lMsgId, dy[i], 40);					// ESDVALUE

		XcomList(lMsgId, 2);			// L 2
		XcomAscii(lMsgId, L"dy", 24);					// ESDITEM
		XcomAscii(lMsgId, dy[i], 40);					// ESDVALUE
	}
	//
	XcomSend(lMsgId, nStrm, nFunc);	//SendMsg

}
#endif // 0
/* SECS Event */
void CSecs::SecsEventXcomproctrl1(short nEventId, long lParam)
{
	CVisionAgentDlg* pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	//Total_Msg(_T("called SecsEvent~ [%d], [%d]"), nEventId, lParam);

	//--일정횟수 이상 동일 event 발생시 Log 찍지 않게 20171211 jinsuk
	bEvent_Log_Flag = true;
	if (nEventId != nEventIdold) nSameEventCount = 0;
	else {
		if (nSameEventCount++ >= 10) bEvent_Log_Flag = false;
	}

	if (nEventId == 203) { //  T3 timeout...
		if (bEvent_Log_Flag)
		{
			Total_Msg(_T("[ECS ALARM] T3 timeout alarm occurs"));
			Alarm_Msg(_T("[ECS ALARM] T3 timeout alarm occurs"));
		}
	}
	else if (nEventId == 102) {    //  NOT_SELECTED...
		m_SECSCommunicationOK = false;
		if (bEvent_Log_Flag)
		{
			Total_Msg(_T("[ECS EVENT] Not selected event happens"));
			Alarm_Msg(_T("[ECS EVENT] Not selected event happens"));
		}
	}
	else if (nEventId == 101) {    //  NOT_CONNECTED...
		m_SECSCommunicationOK = false;
		if (bEvent_Log_Flag)
		{
			Total_Msg(_T("[ECS EVENT] Not connected event happens"));
			Alarm_Msg(_T("[ECS EVENT] Not connected event happens"));
		}
	}
	else if (nEventId == 103) {    //  SELECTED...
		m_SECSCommunicationOK = true;
		if (bEvent_Log_Flag)
		{
			Total_Msg(_T("[ECS EVENT] Selected event happens"));
			Alarm_Msg(_T("[ECS EVENT] Selected event happens"));
		}

		//ECS Connect 시 자동으로 ReStart package 전송
		//EqpEvent(L"EcsRestart");
	}
	else if (nEventId == 216) {
		m_SECSCommunicationOK = false;
		if (bEvent_Log_Flag)
		{
			Total_Msg(_T("[ECS EVENT] XCom Key(Usb-type) Not Found"));
			Alarm_Msg(_T("[ECS EVENT] XCom Key(Usb-type) Not Found"));
		}
	}
	else if (nEventId == 217) {
		m_SECSCommunicationOK = false;
		if (bEvent_Log_Flag)
		{
			Total_Msg(_T("[ECS EVENT] Invalid Message ID (code=%d)"), nEventId);
			Alarm_Msg(_T("[ECS EVENT] Invalid Message ID (code=%d)"), nEventId);
		}
	}
	else {
		if (bEvent_Log_Flag)
		{
			Total_Msg(_T("[ECS EVENT] Code=%d, Parameter=%d"), nEventId, lParam);
			Alarm_Msg(_T("[ECS EVENT] Code=%d, Parameter=%d"), nEventId, lParam);
		}
	}
	nEventIdold = nEventId;
}

/* Msg Recived */
void CSecs::SecsMsgXcomproctrl1()
{
	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	short   nWbit, nDevId;
	long    lMsgId, lSysByte;
	long	nItems = 0;
	WORD    nU2 = 0;
	CString cstr;
	//메시지 받으면 동작하는 부분 ex s1f2 수신할때 할 동작 nStrm 1 nFunc 2에다가 삽입
	while (pDlg->m_XComPro.LoadSecsMsg(&lMsgId, &nDevId, &nStrm, &nFunc, &lSysByte, &nWbit) >= 0)
	{

		cstr.Format(_T("  ==Received[S%dF%d]=="), nStrm, nFunc);
		LogSecsMsg(L"Recive", cstr);

		if (nFunc == 0) {
			Total_Msg(_T("   Received Abort Transaction "));
			XcomMsgClose(lMsgId);
		}
		else if (nStrm == 1)
		{
			if (nFunc == 1) {
				S1F1recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 2) {
				S1F2recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			/*else if (nFunc == 62) {
				S1F62recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 63) {
				S1F63recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 68) {
				S1F68recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 69) {
				S1F69recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 72) {
				S1F72recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 73) {
				S1F73recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 76) {
				S1F76recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 78) {
				S1F78recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 79) {
				S1F79recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 81) {
				S1F81recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 84) {
				S1F84recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 86) {
				S1F86recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 88) {
				S1F88recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 92) {
				S1F92recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 93) {
				S1F93recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
		}
		else if (nStrm == 2)
		{
			if (nFunc == 18) {
				S2F18recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 25) {
				S2F25recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 26) {
				S2F26recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 31) {
				S2F31recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 62) {
				S2F62recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 64) {
				S2F64recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 66) {
				S2F66recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 68) {
				S2F68recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 69) {
				S2F69recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 71) {
				S2F71recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 76) {
				S2F76recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 78) {
				S2F78recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 80) {
				S2F80recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 84) {
				S2F84recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 86) {
				S2F86recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 87) {
				S2F87recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 89) {
				S2F89recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 91) {
				S2F91recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 94) {
				S2F94recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 96) {
				S2F96recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 97) {
				S2F97recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}*/
		}
		else if (nStrm == 3)
		{
/*			if (nFunc == 54) {
				S3F54recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 64) {
				S3F64recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 72) {
				S3F72recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}
			else if (nFunc == 74) {
				S3F74recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			}*/
			//else if (nFunc == 76) {
			//	S3F76recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			//}
			//else if (nFunc == 82) {
			//	S3F82recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			//}
			//else if (nFunc == 83) {
			//	S3F83recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			//}
			//else if (nFunc == 88) {
			//	S3F88recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			//}
			//else if (nFunc == 92) {
			//	S3F92recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
			//}
		}
		//else if ((nStrm == 5) && (nFunc == 2)) {
		//	S5F2recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//}
		//else if (nStrm == 6)
		//{
		//	if (nFunc == 62) {
		//		S6F62recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 64) {
		//		S6F64recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 65) {
		//		S6F65recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 68) {
		//		S6F68recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 70) {
		//		S6F70recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 72) {
		//		S6F72recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 74) {
		//		S6F74recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 84) {
		//		S6F84recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 86) {
		//		S6F86recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 90) {
		//		S6F90recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 92) {
		//		S6F92recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 94) {
		//		S6F94recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 96) {
		//		S6F96recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 98) {
		//		S6F98recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//}
		//else if (nStrm == 7)
		//{
		//	if (nFunc == 19) {
		//		S7F19recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 61) {
		//		S7F61recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 64) {
		//		S7F64recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 69) {
		//		S7F69recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 77) {
		//		S7F77recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 79) {
		//		S7F79recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 81) {
		//		S7F81recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//}
		//else if (nStrm == 10)
		//{
		//	if (nFunc == 3) {
		//		S10F3recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//}
		//else if (nStrm == 15)
		//{
		//	if (nFunc == 65) {
		//		S15F65recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 71) {
		//		S15F71recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 73) {
		//		S15F73recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 75) {
		//		S15F75recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 77) {
		//		S15F77recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 80) {
		//		S15F80recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 81) {
		//		//S15F81recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 95) {
		//		//S15F95recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 97) {
		//		//S15F97recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//	else if (nFunc == 100) {
		//		//S15F100recv(lMsgId, nDevId, nStrm, nFunc, lSysByte, nWbit);
		//	}
		//}
		//else {
			Total_Msg(_T("SECS: Received S%dF%d "), nStrm, nFunc);
			Total_Msg(_T("SECS: Undefined message received (S%dF%d)"), nStrm, nFunc);
			Alarm_Msg(_T("SECS: Undefined message received (S%dF%d)"), nStrm, nFunc);
			XcomMsgClose(lMsgId);
		//}
		//----
		RecvFlag[nStrm][nFunc] = TRUE;	//메시지 수신체크
		//recvSFmsg.Format(_T("S%dF%d"), nStrm, nFunc);	
		//Total_Msg(_T(" --recv : %s"), recvSFmsg);
	}
	//
}

/* Material Process Data Send */
//void CSecs::S3F73()
//{
//	USES_CONVERSION;
//	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//	nStrm = 3;
//	nFunc = 73;
//
//	//HOST ONLINE CHECK
//	//if (pDlg->m_EQP.STATE[0] == '2')
//	//	sprintf(pDlg->m_LOT.MODECODE, "%s", W2A(L"F"));
//	//else
//	//	sprintf(pDlg->m_LOT.MODECODE, "%s", W2A(L"H"));
//	//21.06.17 sjc test용
//	WORD unitID = 1301;
//	//WORD MLOTID = 100;
//	SharedInfo::RevLoadMaskData;
//	char prcCode[8];
//	 
//	//==============
//	if (XcomMake(&lMsgId, MYDEVICEID, nStrm, nFunc, 0)) return;
//	XcomList(lMsgId, 8);
//	XcomU2(lMsgId, &unitID, 1);//Unit id
//	XcomAscii(lMsgId, "N", 1);//Mode code
//	XcomAscii(lMsgId, SharedInfo::Active.strFrameName, 30);//mlotid
//	XcomAscii(lMsgId, "1", 24);//Recipe	
//	XcomAscii(lMsgId, (char)SharedInfo::RevLoadMaskData.ProcessingCode, 8); // prcid
//	XcomAscii(lMsgId, "", 32);//key id
//
//	XcomWriteLSD();	//Xcom에 LSD를 Write
//
//	XcomWriteAPD();	//Xcom에 APD(stick정보+측정결과)를 Write
//
//	XcomSend(lMsgId, nStrm, nFunc);
//}
//void CSecs::S3F74recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit)
//{
//	CVisionAgentDlg * pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//	BYTE ack[2];
//	XcomGetList(lMsgId, &lists);
//	XcomGetU2(lMsgId, &UnitId, &lCnt, 1);
//	XcomGetBinary(lMsgId, ack, &lCnt, 1);
//	strAck.Format(_T("   Receive Ack : %d "), ack[0]);
//	XcomAck(strAck);
//	XcomMsgClose(lMsgId);
//}