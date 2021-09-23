#pragma once
#include "../Common/CommonDefine.h"

#define	MAX_MODULE_SIZE			20
#define	MAX_DI_SIZE				256
#define	MAX_DO_SIZE				256
#define	MAX_AI_SIZE				80
#define	MAX_DINPUT_DWORD_SIZE	4
#define	MAX_DOUTPUT_DWORD_SIZE	8
class CSensing
{
	/*----Sensor Input & Sig Output----*/
public:
	CSensing();
	~CSensing();
private:
	HANDLE			hHandle;
	BOOL			m_StateFinish;

	int				m_nMax_DI_Size;
	int				m_nDI_ModuleNo[MAX_DI_SIZE];
	int				m_nDI_Size[MAX_MODULE_SIZE];
	int				m_nMax_DI_Module_Size;
	int				m_nDInputValue[MAX_DI_SIZE];
	DWORD			m_dwDInputDWordValue[MAX_DINPUT_DWORD_SIZE];
	

	int				m_nMax_DO_Size;
	int				m_nDO_ModuleNo[MAX_DO_SIZE];
	int				m_nDO_Size[MAX_MODULE_SIZE];
	int				m_nMax_DO_Module_Size;
	int				m_nDOutputValue[MAX_DO_SIZE];
	DWORD			m_dwDOutputDWordValue[MAX_DOUTPUT_DWORD_SIZE];

	int				m_nMax_AI_Size;
	int				m_nAI_ModuleNo[MAX_AI_SIZE];
	int				m_nAI_Size[MAX_MODULE_SIZE];
	int				m_nMax_AI_Module_Size;
	double			m_dAInputValue[MAX_AI_SIZE];
	double			m_dAInputOffset[MAX_AI_SIZE];
	double			m_dAInputCALScale[MAX_AI_SIZE];
	double			m_dAInputCALOffset[MAX_AI_SIZE];
	int				m_nAInputCALApply[MAX_AI_SIZE];

	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);

public:
	BOOL	InitProcess();
	BOOL	EndProcess();

	BOOL	Init_DI_Board();
	BOOL	Init_DO_Board();
	BOOL	Init_AI_Board();

	BOOL	Start();
	BOOL	Stop();

	BOOL	Is_Dig_Input(int nBit);
	BOOL	Set_Dig_Output(int nBit, bool bOnOff);
};
