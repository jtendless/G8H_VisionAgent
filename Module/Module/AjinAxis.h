typedef struct _tagstAjinChk{
	int nAxisNo = -1;
	int nSlaveNo = -1;
	int nItem = -1;
}stAjinChk;

enum{
	_ChkLimitSignal = 0,
	_ChkVelocity,
	_ChkHomeLimitPos,
	_ChkGantryServoOn,
	_ChkGantryHome,
	_ChkFinish
};



#pragma once
class CAjinAxis
{

public:
	CAjinAxis();
	~CAjinAxis();

	stAjinChk m_AjinChk;

	CCriticalSection	m_CLock;
	int					m_nAXLOpen;
	int AjinPosMove(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel);
	int AjinRelMove(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel);
	BOOL AjinMoveStop(int nAxisNo);

	void Home(INT nIndex);
	void GantryHome(int nMaster, int nSlave);
	int AjinHomeStart(int nIndex);

	int m_nAxisNo;	
	double m_dVel;
	double m_dAccel;
	double m_dDecel;

	DWORD m_dwStatus;
	/*
	int SetAxisNo(int nAxisNo);
	int SetVel(double dVel);
	int SetAccel(double dAccel);
	int SetDecel(double dDecel);

	int GetServoOn(int* pnServoOn);
	int SetServoOn();
	int SetServoOff();

	int GetCmdPos(double* pdCmdPos);
	int GetActPos(double* pdActPos);

	int GetAlarm();
	int SetAlarmClear();

	int GetLimit(DWORD* pdwPLimit, DWORD* pdwNLimit);

	int MoveHomeSearch();

	int MoveStart(double dPos);
	int MoveStop();

	int EMGStop();
	*/
};

UINT AjinChkProc(LPVOID lpParam);