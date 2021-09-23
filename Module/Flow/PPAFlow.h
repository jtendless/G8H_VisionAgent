#pragma once

class CPPAFlow : public CBaseFlow
{
public:
	CPPAFlow();
	~CPPAFlow();

private:
	BOOL			m_FlowFinish;

	void(*m_StateComplete)(void *pArgument);

	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);

public:
	BOOL			m_bFlowDone;
	BOOL			m_bStopBit;

	BOOL InitProcess();
	BOOL EndProcess();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }
	BOOL			IsFlowDone() { return m_bFlowDone; }

	BOOL			Start();
	BOOL			Stop();

	enum ePPA
	{
		_ePPA_FLOW_IDLE = 0,
		_ePPA_FLOW_START,

		_ePPA_FLOW_DONE,
		_ePPA_FLOW_STOP,


	//	[5. PPA] //SOFTWARE ��� ����, LASER FOCUS, IMAGE FOCUS ���
	//BOX CAMERA Y WAIT POS(CYD CHECK) �׻� �ϴ� WAIT POS ����

	//	UNLOADER VAC OFF
	//	BLOW ON
	//	BLOW OFF
	//	UNLOADER CYD UP
	//	UNLOADER Z UP
	//	UNLOADER Y WAIT

	//	LOADER VAC OFF
	//	BLOW ON
	//	BLOW OFF
	//	LOADER CYD UP
	//	LOADER Z UP

	//	CAMERA Z ALL UP
	//	GANTRY XY WAIT

	//	CLAMP OFF
	//	GRIPPER UP
	//	STRETCH WAIT
	//	PITCH WAIT

	//	//
	//	GANTRY XY PPA POS
	//	BACKLIGHT X PPA POS
	//	GANTRY Z1 INSPECTION POS
	//	LASER FOUSING
	//	IMAGE FOCUSING
	//	GRAB
	//	GRAB CHECK
	//	PPA

	//	GANTRY Z WAIT POS(Option)
	//	���� GANTRY XY PPA POS...

	//	�Ϸ� ��
	//	GANTRY Z1 WAIT POS
	//	GANTRY XY WAIT POS
	};
};

