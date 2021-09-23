#include "stdAfx.h"
#include "UmacAxis.h"
#include "Runtime.h"
CUmacAxis::CUmacAxis(void)
{
	m_bOpen			= FALSE;
	m_hPmacLib		= NULL;
	m_bDeviceOpen	= FALSE;
	
	m_dTargetPosX	= 0.0;
	m_dTargetPosY	= 0.0;	
		
}


CUmacAxis::~CUmacAxis(void)
{
//	pDlg->m_nStopStatusThread = TRUE;
}


BOOL CUmacAxis::UmacOpen(BOOL bOpen)
{
	if( bOpen )
	{
		for( int i = 0; i < 3; i++ )
		{
			if (!m_hPmacLib)
			{
				m_hPmacLib		= OpenRuntimeLink();
				break;
			}
			Sleep(5);
		}

		if (!m_hPmacLib)
		{
			return FALSE;
		}

		//m_dwDeviceID		= DeviceSelect(NULL);
		m_bDeviceOpen	= DeviceOpen(0);

		if (m_bDeviceOpen == 0) return FALSE;
	}
	else
	{
		if (m_bDeviceOpen)
		{
			DeviceClose(0);
		}

		if (m_hPmacLib)
		{
			CloseRuntimeLink();
		}
	}

	return TRUE;
}

VOID  CUmacAxis::AxisCmdResponse(CString strSender, CString &strRecver)
{
	INT		nRet = 0;
	CHAR	szResponse[255] = {0,};
	USES_CONVERSION;

	nRet	= DeviceGetResponseEx(0, szResponse, 255, T2A(strSender));
	strRecver = A2T(szResponse);
}

//Do not use
// POT, NOT, Vel Zero, ServoOn, Amp Enable, Inpos, FloErr, Amp Alarm, Home, ParsingErr, CmdPos, ActPos, ActVel
//연속 Gantry만 적용 가능.
void CUmacAxis::GetStatus(INT32 nAxis)
{
	CString strAxis, strCmd;
	strAxis.Format(_T("%d"), nAxis);

	strCmd.Append(_T("M"));	// M Adress
	strCmd.Append(strAxis);	// Axis No

	//AxisCmdResponse( CString strSender, CString &strRecver)
}

//Index Axis(0~)
//연속 Gantry만 적용 가능.
BOOL CUmacAxis::IsPOT(INT32 nAxis)
{
	int nRealNo = 0;
	BOOL bTemp = FALSE;
	BOOL bTemp2 = FALSE;
	BOOL bTemp3 = FALSE;

	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_VERTUAL] == -1)
		nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];
	else{
		nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_VERTUAL];
	
	
	}
	CString strAxis, strSender, strRecver;

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));		// M Adress
	strSender.Append(strAxis);		// Axis No
	//strSender.Append(_T("31"));	// Address No
	strSender.Append(_T("21"));		// Address No

	AxisCmdResponse( strSender, strRecver);
	
	bTemp2 = (BOOL)_ttoi(strRecver);

	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_VERTUAL] != -1)
	{
		strSender = _T("");
		strAxis.Format(_T("%d"), nRealNo + 1);

		strSender.Append(_T("M"));		// M Adress
		strSender.Append(strAxis);		// Axis No
		//strSender.Append(_T("31"));	// Address No
		strSender.Append(_T("21"));		// Address No

		AxisCmdResponse(strSender, strRecver);

		bTemp3 = (BOOL)_ttoi(strRecver);

		bTemp = bTemp2 || bTemp3;

		strRecver.Format(_T("%d"), bTemp);
	}

	return (BOOL) _ttoi(strRecver);
}

//Index Axis(0~)
BOOL CUmacAxis::IsNOT(INT32 nAxis)
{
	int nRealNo = 0;

	BOOL bTemp = FALSE;
	BOOL bTemp2 = FALSE;
	BOOL bTemp3 = FALSE;

	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_VERTUAL] == -1)
		nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];
	else
		nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_VERTUAL];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));		// M Adress
	strSender.Append(strAxis);		// Axis No
	//strSender.Append(_T("32"));	// Address No
	strSender.Append(_T("22"));		// Address No

	AxisCmdResponse( strSender, strRecver);

	bTemp2 = (BOOL)_ttoi(strRecver);

	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_VERTUAL] != -1)
	{
		strSender = _T("");
		strAxis.Format(_T("%d"), nRealNo + 1);

		strSender.Append(_T("M"));		// M Adress
		strSender.Append(strAxis);		// Axis No
		//strSender.Append(_T("31"));	// Address No
		strSender.Append(_T("22"));		// Address No

		AxisCmdResponse(strSender, strRecver);

		bTemp3 = (BOOL)_ttoi(strRecver);

		bTemp = bTemp2 || bTemp3;

		strRecver.Format(_T("%d"), bTemp);
	}

	return (BOOL) _ttoi(strRecver);
}

//Index Axis(0~)
BOOL CUmacAxis::IsHome(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("20"));	// Address No

	AxisCmdResponse(strSender, strRecver);

	return (BOOL)_ttoi(strRecver);
}

//Index Axis(0~)
BOOL CUmacAxis::IsSpeedZero(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("33"));	// Address No

	AxisCmdResponse( strSender, strRecver);

	return (BOOL)_ttoi(strRecver);
}

//Index Axis(0~)
BOOL CUmacAxis::IsServoOn(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("38"));	// Address No

	AxisCmdResponse( strSender, strRecver);

	return (BOOL) _ttoi(strRecver);
}

//Index Axis(0~)
BOOL CUmacAxis::IsAmpEnable(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("39"));	// Address No

	AxisCmdResponse( strSender, strRecver);

	return (BOOL) _ttoi(strRecver);
}

//Index Axis(0~)
BOOL CUmacAxis::IsInPosition(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("40"));	// Address No

	AxisCmdResponse( strSender, strRecver);

	return (BOOL) _ttoi(strRecver);
}

//Do not use
LONG CUmacAxis::GetFollowError(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("42"));	// Address No

	AxisCmdResponse( strSender, strRecver);

	return (LONG) _ttoi(strRecver);
}

//Index Axis(0~)
LONG CUmacAxis::GetAmpAlarm(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	LONG	nAlarm;

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("43"));	// Address No

	AxisCmdResponse( strSender, strRecver);
	nAlarm	= (LONG) _ttoi(strRecver);
	
	return 0;
}

//Index Axis(0~)
BOOL CUmacAxis::IsHomeComplete(INT32 nAxis)
{
	BOOL nComplete = FALSE;
	BOOL nCompletePM = FALSE;
	BOOL nCompletePS = FALSE;
	BOOL nCompleteM = FALSE;


	CString strAxis, strSender, strRecver;
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_HOME_NO];
	
	strSender.Format(_T("P%d"), nRealNo);
	AxisCmdResponse( strSender, strRecver);

	nCompletePM = (BOOL)_ttoi(strRecver);

	nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_HOME_NO_SLAVE];
	strSender.Format(_T("P%d"), nRealNo);
	AxisCmdResponse(strSender, strRecver);

	nCompletePS = (BOOL)_ttoi(strRecver);

	nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Format(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("45"));	// Address No
	AxisCmdResponse(strSender, strRecver);

	nCompleteM = (BOOL)_ttoi(strRecver);

	nComplete = nCompletePM && nCompletePS && nCompleteM;

	return nComplete;
}


BOOL CUmacAxis::HomeCompReset(INT32 nAxis)
{
	CString strAxis, strSender, strRecver;
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_HOME_NO];

	strSender.Format(_T("P%d=0"), nRealNo);
	AxisCmdResponse(strSender, strRecver);


	nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_HOME_NO_SLAVE];
	strSender.Format(_T("P%d=0"), nRealNo);
	AxisCmdResponse(strSender, strRecver);
	
	return 0;
}

//Index Axis(0~)
BOOL CUmacAxis::IsHoming(INT32 nAxis)
{
	CString strAxis, strSender, strRecver;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_HOME_NO];

	strSender.Format(_T("P%d"), nRealNo + 1);

	AxisCmdResponse(strSender, strRecver);

	return (BOOL) _ttoi(strRecver);
}

//Do not use
LONG CUmacAxis::GetPhasingError(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("48"));	// Address No

	AxisCmdResponse( strSender, strRecver);

	return (LONG) _ttoi(strRecver);
}

//Real axis
LONGLONG CUmacAxis::GetPosBias(INT nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("64"));	// Address No

	AxisCmdResponse( strSender, strRecver);
	LONGLONG dBias = (LONGLONG) _ttof(strRecver);

	return dBias;
}

//Real axis
LONG CUmacAxis::GetAddrI08Value(INT nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("08"));	// Address No

	AxisCmdResponse( strSender, strRecver);
	LONG lI08 = (LONG) _ttoi(strRecver);

	return lI08;
}

//Real axis
LONG CUmacAxis::GetAddrI09Value(INT nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("09"));	// Address No

	AxisCmdResponse(strSender, strRecver);
	LONG lI09 = (LONG)_ttoi(strRecver);

	return lI09;
}

//Real axis
LONG CUmacAxis::GetAddrI10Value(INT nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));		// M Adress
	//strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("10"));		// Address No

	AxisCmdResponse(strSender, strRecver);
	LONG l10 = (LONG)_ttoi(strRecver);

	return l10;
}

//Real axis
// Position Calc Variable
LONGLONG  CUmacAxis::GetCalTable(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("69"));	// Address No

	AxisCmdResponse( strSender, strRecver);
	LONGLONG dTable = (LONGLONG) _ttof(strRecver);

	return dTable;
}

//Index Axis(0~)
DOUBLE CUmacAxis::GetInitActPosition(INT32 nAxis)
{		
	//Awk 함수	용도 확인 필히 해 볼 것.
	//m_dTargetPos[nAxis] = GetActPosition(nAxis);
	//m_dPrevActPos[nAxis] = m_dTargetPos[nAxis];

	return 0.0;
}

//Index Axis(0~)
DOUBLE CUmacAxis::GetActPosition(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("62"));	// Address No

	AxisCmdResponse( strSender, strRecver);


	//Awk 카운터 -> mm로 계산 해서 넣어주기.

	DOUBLE dAddrM69 = (DOUBLE)GetCalTable(nAxis);
	DOUBLE dAddrM64 = (DOUBLE)GetPosBias(nAxis);
	DOUBLE dAddrM62 = (DOUBLE)_ttof(strRecver);
	DOUBLE dAddrI08 = GetAddrI08Value(nAxis);

	//if( nAxis == UMACAxisY )
	//{
	//	//TRACE(_T("M64:%d, M62:%d, I08:%d\n"), dAddrM64, dAddrM62, (LONG)dAddrI08);
	//}
	LONGLONG lCTS = (LONGLONG)(dAddrM62 / (dAddrI08 * 32));

	DOUBLE dMM = CtsToMM(nAxis, lCTS);
	
	return dMM;
}

//Index Axis(0~)
DOUBLE CUmacAxis::GetCmdPosition(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));	// M Adress
	strSender.Append(strAxis);	// Axis No
	strSender.Append(_T("61"));	// Address No

	AxisCmdResponse( strSender, strRecver);

	//LONGLONG dAddrM69 = (ULONGLONG)GetCalTable(nAxis);			//보상 교정
	//LONGLONG dAddrM64 = (LONGLONG)GetPosBias(nAxis);				//위치 편향 
				

	//if( nAxis == UMACAxisY )
	//{
	//	//TRACE(_T("M64:%d, M62:%d, I08:%d\n"), dAddrM64, dAddrM62, (LONG)dAddrI08);
	//}
	DOUBLE dAddrM61 = _ttof(strRecver);					//실제 위치
	DOUBLE dAddrI08 = GetAddrI08Value(nAxis);

	LONGLONG lCTS = (LONGLONG)(dAddrM61 / (dAddrI08 * 32));
	DOUBLE dMM = CtsToMM(nAxis, lCTS);

	return dMM;
}

//Index Axis(0~)
DOUBLE CUmacAxis::GetActVelocity(INT32 nAxis)
{
	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("M"));		// M Adress
	strSender.Append(strAxis);		// Axis No
	strSender.Append(_T("66"));		// Address No
	//strSender.Append(_T("74"));	// Address No		평균실제속도

	AxisCmdResponse( strSender, strRecver);

	DOUBLE dAddrI10 = GetAddrI10Value(nAxis);
	DOUBLE dAddrM66 = _ttoi(strRecver);
	DOUBLE dAddrI09 = GetAddrI09Value(nAxis);

	LONGLONG lCTS = (LONGLONG)(dAddrM66 / (dAddrI09 * 32));
	DOUBLE dMM = CtsToMM(nAxis, lCTS);

	return dMM;
}

//Plc 
void CUmacAxis::HomeStart(INT32 nAxis)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_PLC_NO];

	CString strAxis, strSender, strRecver;

	strSender.Format(_T("ena plc %d"), nRealNo);

	AxisCmdResponse(strSender, strRecver);
	
}

//Plc 
void CUmacAxis::HomeStop(INT32 nAxis)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS])
	{
		int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_PLC_NO];
		CString strAxis, strSender, strRecver;
		strSender.Format(_T("dis plc %d"), nRealNo);
		AxisCmdResponse(strSender, strRecver);
	}
}

//Real Axis
void CUmacAxis::Reset()
{
	CString strSender, strRecver;

	strSender = _T("$$$");
	
	AxisCmdResponse(strSender, strRecver);
}

//Real, Virtual Axis
void CUmacAxis::ServoOn(INT32 nAxis, BOOL bOnOff)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = 0;

	nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];
	
	CString strAxis, strSender, strRecver;

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("#"));		// M Adress
	strSender.Append(strAxis);		// Axis No

	if (bOnOff)
	{
		strSender.Append(_T(" $"));// Address No
	}
	else
	{
		strSender.Append(_T(" K"));	// Address No		
	}
	AxisCmdResponse(strSender, strRecver);


	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_VERTUAL] != NoUse)
	{
		nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_VERTUAL];

		strSender = _T("");
		strAxis.Format(_T("%d"), nRealNo);

		strSender.Append(_T("#"));		// M Adress
		strSender.Append(strAxis);		// Axis No

		if (bOnOff)
		{
			strSender.Append(_T(" $"));// Address No
		}
		else
		{
			strSender.Append(_T(" K"));	// Address No		
		}

		AxisCmdResponse(strSender, strRecver);

		strSender = _T("");
		strAxis.Format(_T("%d"), nRealNo + 1);

		strSender.Append(_T("#"));		// M Adress
		strSender.Append(strAxis);		// Axis No

		if (bOnOff)
		{
			strSender.Append(_T(" $"));// Address No
		}
		else
		{
			strSender.Append(_T(" K"));	// Address No		
		}

		AxisCmdResponse(strSender, strRecver);
	}
}

//동작 함수.
//Real, Virtual Axis
VOID CUmacAxis::Jog(INT32 nAxis, BOOL bDirPluse)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("#"));				// M Adress
	strSender.Append(strAxis);					// Axis No

	if (bDirPluse)
	{
		strSender.Append(_T(" J+"));			// Address No
	}
	else
	{
		strSender.Append(_T(" J-"));			// Address No
	}

	AxisCmdResponse(strSender, strRecver);
}

VOID CUmacAxis::MovePos(INT32 nAxis, DOUBLE dPos)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];
	
	LONGLONG lCtn = MMToCts(nAxis, dPos);

	CString strAxis, strSender, strRecver;
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("#"));							// M Adress
	strSender.Append(strAxis);								// Axis No
	strSender.Append(_T(" J"));							// Address No
	strSender.Append(_T("="));							// Operation	
	strSender.AppendFormat(_T("%d"), lCtn);

	AxisCmdResponse(strSender, strRecver);

}

VOID CUmacAxis::RelMovePos(INT32 nAxis, DOUBLE dPos)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	LONGLONG lCtn = MMToCts(nAxis, dPos);

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];
	
	CString strAxis, strSender, strRecver;

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("#"));							// M Adress
	strSender.Append(strAxis);							// Axis No
	strSender.Append(_T(" J"));							// Address No	
	strSender.Append(_T(":"));							// Operation(Rel Move)
	strSender.AppendFormat(_T("%d"), lCtn);

	AxisCmdResponse(strSender, strRecver);
	
}

//Real, Virtual Axis (mm/sec로 넣기)
VOID CUmacAxis::SetVel(INT32 nAxis, DOUBLE dVel)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;

	LONGLONG lctsVel = MMToCts(nAxis, dVel / 1000);				
	
	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));					// I Adress
	strSender.Append(strAxis);					// Axis No
	strSender.Append(_T("22"));					// Address No			Cnt/msec
	strSender.Append(_T("="));					// Operation	
	strSender.AppendFormat(_T("%d"), lctsVel);	// Value

	AxisCmdResponse(strSender, strRecver);
	
}

//Real, Virtual Axis (Count/msec^2으로 넣기)
VOID CUmacAxis::SetGravityAccDec(INT32 nAxis, LONG dAccDcc)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;

	LONG lAcc = dAccDcc;					

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));							// I Adress
	strSender.Append(strAxis);							// Axis No
	strSender.Append(_T("19"));						// Address No				
	strSender.Append(_T("="));						// Operation
	strSender.AppendFormat(_T("%d"), lAcc);	// Value

	AxisCmdResponse(strSender, strRecver);
}

//Real, Virtual Axis 감속 시간으로 입력 sec
VOID CUmacAxis::SetAccDecTime(INT32 nAxis, LONG lSec)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;

	LONG lAcc = lSec * 1000;							//msec로 변환.

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));						// I Adress
	strSender.Append(strAxis);							// Axis No
	strSender.Append(_T("20"));						// Address No				msec 가속 시간.
	strSender.Append(_T("="));						// Operation
	strSender.AppendFormat(_T("%d"), lAcc);	// Value

	AxisCmdResponse(strSender, strRecver);
}

//Awking S - Curve 단위 확인해서 정해진 데이터에 맞게 S - Curve 들어갈 수 있도록 확인.
//Real, Virtual Axis (sec로 넣기)
VOID CUmacAxis::SetSCurve(INT32 nAxis, LONG lsec)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;

	LONG lDcc = lsec * 1000;									//msec로 변환.					

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));									// M Adress
	strSender.Append(strAxis);									// Axis No
	strSender.Append(_T("21"));								// Address No
	strSender.Append(_T("="));								// Operation
	strSender.AppendFormat(_T("%d"), lDcc);			// Value

	AxisCmdResponse( strSender, strRecver);
}

VOID CUmacAxis::SetSafytyMotionPara(INT32 nAxis, DOUBLE dVel)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;

	//100mm/s일때 1초 기준. msec.
	LONG AccDecTime = (LONG)(dVel * 1000 / 100);

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));										// M Adress
	strSender.Append(strAxis);										// Axis No
	strSender.Append(_T("20"));										// Address No
	strSender.Append(_T("="));										// Operation
	strSender.AppendFormat(_T("%d"), AccDecTime);			// Value
		
	AxisCmdResponse(strSender, strRecver);
	

	strSender = _T("");

	//S- Curve는 가감속 시간의 40%
	LONG lSCurveTime = (LONG)(AccDecTime * 0.4);

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("I"));										// M Adress
	strSender.Append(strAxis);										// Axis No
	strSender.Append(_T("21"));										// Address No
	strSender.Append(_T("="));										// Operation
	strSender.AppendFormat(_T("%d"), lSCurveTime);			// Value

	AxisCmdResponse(strSender, strRecver);

}

////////////////////////////////////////////////////////////////////////////////
//Index Axis(0~)
void CUmacAxis::ResetHomeState(INT32 nAxis)
{
	//Awk 함수용도 확인.
}

//Real, Virtual Axis
VOID CUmacAxis::Stop(INT32 nAxis)
{
	if (m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_CONTROL_AXIS] == NoUse)
		return;

	int nRealNo = m_Umac.nUmacInfo[nAxis].nUmacAxisMap[UMAC_REAL_AXIS];

	CString strAxis, strSender, strRecver;

	strAxis.Format(_T("%d"), nRealNo);

	strSender.Append(_T("#"));		// M Adress
	strSender.Append(strAxis);			// Axis No
	strSender.Append(_T(" J/"));		// Address No
	
	AxisCmdResponse( strSender, strRecver);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// 상위 함수////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Real, Virtual Axis 상위함수
VOID CUmacAxis::JogMove(INT32 nAxis, DOUBLE dVel, DOUBLE dAccel, DOUBLE dDecel, BOOL bPress)
{
	if (bPress)
	{
		SetVel(nAxis, fabs(dVel));

		//Awking Safety Acc Dcc로 변경
		SetSafytyMotionPara(nAxis, fabs(dVel));
		
		// Jog direction
		if (dVel < 0)
		{
			Jog(nAxis, FALSE);
		}
		else
		{
			Jog(nAxis, TRUE);
		}
	}
	else
	{
		Stop(nAxis);
	}
}

//Real, Virtual Axis 상위 함수.
VOID CUmacAxis::PosMove(INT32 nAxis, DOUBLE dVel, DOUBLE dAccel, DOUBLE dDecel, DOUBLE dPos)
{
	//Awk
	SetVel(nAxis, fabs(dVel));
	SetSafytyMotionPara(nAxis, dVel);
	/*
	//Real, Virtual Axis
	int nIndex = (int)SharedInfo::GetEnumAxisNoByActualAxis((enum_REMOTE_AXIS_UMAC)nAxis);
	MovePos(nAxis, dPos - CMachineData::m_MachineDataMotor.Info.dOriginPos[nAxis]);
	*/
}

//Real, Virtual Axis 상위함수.
VOID CUmacAxis::RelMove(INT32 nAxis, DOUBLE dVel, DOUBLE dAccel, DOUBLE dDecel, DOUBLE dPos)
{
	//Awk
	SetVel(nAxis, fabs(dVel));
	SetSafytyMotionPara(nAxis, fabs(dVel));

	//Real, Virtual Axis
	RelMovePos(nAxis, dPos);
}

//Index Axis(0~) 상위함수
BOOL CUmacAxis::IsDone(INT32 nAxis)
{
	BOOL bDone = IsInPosition(nAxis);

	//Awking 위치 이동 완료 및 Inposition Check Code 추가.

	return bDone;
}

//상위함수.
INT CUmacAxis::Delay(int ms)
{
	MSG  wndMsg;
	DWORD dwSTick, dwEtick;

	dwSTick = GetTickCount();
	while (1)
	{
		Sleep(1);

		if (::PeekMessage(&wndMsg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&wndMsg);
			::DispatchMessage(&wndMsg);
		}

		dwEtick = GetTickCount();
		dwEtick -= dwSTick;
		//if (dwEtick > ms) break;
		if (dwEtick > (DWORD)ms) break;
	}

	return 0;
}

//상위 함수. 
DOUBLE CUmacAxis::CtsToMM(int nIdx, LONGLONG lcts)
{
	int nResolution = m_Umac.nUmacInfo[nIdx].nUmacAxisMap[UMAC_RESOLUTION];

	DOUBLE dMM = (DOUBLE)(lcts / (DOUBLE)nResolution);	
	
	return dMM;
}

//상위함수.
LONGLONG CUmacAxis::MMToCts(int nIdx, DOUBLE dMM)
{
	int nResolution = m_Umac.nUmacInfo[nIdx].nUmacAxisMap[UMAC_RESOLUTION];

	LONGLONG lCts = (LONGLONG)(dMM * nResolution);	
	
	return lCts;
}

INT CUmacAxis::IsIsolatorAlarm()
{
	CString strAxis, strSender, strRecver;
	
	strSender.Append(_T("P"));		
	strSender.Append(_T("8000"));		// Address No

	AxisCmdResponse(strSender, strRecver);
	INT nP8000 = (INT)_ttoi(strRecver);

	if (nP8000 == 0)
		return 0;
	else
	{
		return 1;
	}
	
}