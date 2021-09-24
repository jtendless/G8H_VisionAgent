#pragma once

#include <windows.h>
#include <time.h>

static const char *pLlcErrOK =							"LLC is operational [OK].";
static const char *pLlcErrStatus =						"Failed to get LLC status.\n"
												"Check power supply or serial communication connection.";
static const char *pLlcErrSensorCom =					"There is no communication with LLC.\n";
static const char *pLlcErrMotorDisabled =				"Motor was not started yet or\n"
												"has been disabled by the command or\n"
												"by motor failure.";
static const char *pLlcErrLimitSwitch =				"The limit switch has been activated.";
static const char *pLlcErrPeakCurrExceeded =			"The peak current has been exceeded.\n"
												"Possible reasons are:\n" 
												"- drive malfunction\n"
												"- bad tuning of the current controller.";
static const char *pLlcErrInhibit =					"Inhibit. The motor movement is temporarily inhibited.";
static const char *pLlcErrSpeedTracking =				"Speed tracking error exceeded speed error limit.\n"
												"This may occur due to:\n"
												"- Bad tuning of the speed controller\n"
												"- Too tight a speed error tolerance\n"
												"- Inability of motor to accelerate to the required speed due to\n" 
												"  too low a line voltage or not a powerful enough motor\n";
static const char *pLlcErrPositionTracking =			"Position tracking error exceeded position error limit.\n"
												"This may occur due to:\n"
												"- Bad tuning of the position or speed controller\n"
												"- Too tight a position error tolerance\n"
												"- Abnormal motor load, or reaching a mechanical limit\n";
static const char *pLlcErrUnderVoltage =				"Under voltage. The power supply is shut down or\n"
												"it has too high an output impedance.";
static const char *pLlcErrOverVoltage =				"Over voltage. The voltage of the power supply is too high, or\n"
												"the servo drive did not succeed in absorbing the kinetic energy while braking a load.\n"
												"A shunt resistor may be required.";
static const char *pLlcErrShortCircuit =				"Short circuit. The motor or its wiring may be defective, or\n"
												"the drive is faulty.";
static const char *pLlcErrOverheating =				"Temperature. Drive overheating.\n"
												"The environment is too hot, or lacks heat removal.\n"
												"There may be a large thermal resistance between\n"
												"the drive and its mounting.";
static const char *pLlcErrElectricalZero =				"Failed to find the electrical zero of the motor in an attempt to\n"
												"start it with an incremental encoder.\n"
												"The reason may be that the applied motor current did not\n"
												"suffice for moving the motor from its position or\n"
												"there is wiring problem with UVW or encoder connectors.";
static const char *pLlcErrSpeedLimit =					"Speed limit exceeded.\n"
												"This may occur due to\n"
												"bad tuning of the speed controller.";
static const char *pLlcErrMotorStuck =					"Motor stuck - the motor is powered but is not moving.\n"
												"The reason may be that there is wiring problem with\n"
												"power supply, UVW or encoder connectors.";
static const char *pLlcErrPositionlimit =				"Position limit exceeded.";
static const char *pLlcErrStartMotor =					"Cannot start motor.";
static const char *pLlcErrStackOverflow =				"Stack overflow - fatal exception. This may occur if the CPU was\n"
												"subject to a load that it could not handle. Such a situation can\n"
												"arise only due to a software bug in the drive.";
static const char *pLlcErrCpuException =				"CPU exception - fatal exception. Something such as an attempt\n"
												"to divide in zero or another fatal firmware error has occurred.";

enum LlcErrCode
{
	LlcErrOK = 0,					// 0
// LLC not initilaized error
	LlcErrNotInitialized,			// 1
// LLC bad argument error
	LlcErrArgRange,					// 2
// communication errors
	LlcErrStatus,					// 3
	LlcErrSendFailure,				// 4
	LlcErrSensorCom,				// 5
	LlcErrCmndSyntax,				// 6
	LlcErrRecvLen,					// 7
	LlcErrRecvSyntax,				// 8
	LlcErrWhistleEC,				// 9
//	number of objectives error
	LlcErrObjectiveNum,				// 10
// offset file error
	LlcErrOffsetFile,				// 11
// homing failure error
	LlcErrHoming,					// 12
// move to target error
	LlcErrTargetPos,				// 13
// movement timeout
	LlcErrTimeout,					// 14
// hardware error
	LlcErrRecoveryFailed,			// 15
	LlcErrLimitSwitch,				// 16
	LlcErrMotorDisabled,			// 17
// hardware failure
	LlcErrPeakCurrExceeded,			// 18
	LlcErrInhibit,					// 19
	LlcErrSpeedTracking,			// 20
	LlcErrPositionTracking,			// 21
	LlcErrUnderVoltage,				// 22
	LlcErrOverVoltage,				// 23
	LlcErrShortCircuit,				// 24
	LlcErrOverheating,				// 25
	LlcErrElectricalZero,			// 26
	LlcErrSpeedLimit,				// 27
	LlcErrMotorStuck,				// 28
	LlcErrPositionlimit,			// 29
	LlcErrStartMotor,				// 30
// MFC firmware failure
	LlcErrStackOverflow,			// 31
	LlcErrCpuException				// 32
};

// SR - status register flags (received with "SR;" command)
#define LLC_SR_DR_FLAG		0x00000001	// drive error    (the same as in MF register shown below) - is ON when any of four shown below present
#define LLC_SR_DRUV_FLAG	0x00000003	// under voltage  (the same as in MF register shown below)
#define LLC_SR DROV_FLAG	0x00000005	// over voltage   (the same as in MF register shown below)
#define LLC_SR_DRSC_FLAG	0x0000000B	// short circuit  (the same as in MF register shown below)
#define LLC_SR_DROH_FLAG	0x0000000D	// overheating    (the same as in MF register shown below)
#define LLC_SR_MO_FLAG		0x00000010	// motor enable / disable status - can be obtain with "MO;" command too
#define LLC_SR_MF_FLAG		0x00000040	// motor failure - can be obtain with "MF;" command too
#define LLC_SR_MS_FLAG		0x0000C000	// motion status [00 = In Position; 01 = Off Position; 10 = In motion] - can be obtained with "MS;" command too
#define LLC_SR_PR_FLAG		0x00001000	// program running
#define LLC_SR_SL_FLAG		0x10000000	// limit switches
// MF - motor failure register flags (received with "MF;" command)
#define LLC_MF_PC_FLAG		0x00000008	// peak current exceeded
#define LLC_MF_IN_FLAG		0x00000010	// inhibit
#define LLC_MF_ST_FLAG		0x00000080	// speed tracking error
#define LLC_MF_PS_FLAG		0x00000100	// position tracking error
#define LLC_MF_DR_FLAG		0x00001000	// drive error    (the same as in SR register shown above) - is ON when any of four shown below present
#define LLC_MF_DRUV_FLAG	0x00003000	// under voltage  (the same as in SR register shown above)
#define LLC_MF_DROV_FLAG	0x00005000	// over voltage   (the same as in SR register shown above)
#define LLC_MF_DRSC_FLAG	0x0000B000	// short circuit  (the same as in SR register shown above)
#define LLC_MF_DROH_FLAG	0x0000D000	// overheating    (the same as in SR register shown above)
#define LLC_MF_EZ_FLAG		0x00010000	// electrical zero failure
#define LLC_MF_SL_FLAG		0x00020000	// speed limit failure
#define LLC_MF_SO_FLAG		0x00040000	// stack overflow
#define LLC_MF_CE_FLAG		0x00080000	// CPU exception
#define LLC_MF_MS_FLAG		0x00200000	// motor stuck
#define LLC_MF_PL_FLAG		0x00400000	// position limit exceeded
#define LLC_MF_SM_FLAG		0x20000000	// motor start failure

#define ENC_PULSE_PER_MM	10000	// number of motor pulses per milimeter
#define MAX_LLC_OBJ_NUM		8		// maximum number of possible LLC objectives
#define OBJECTIVE_PITCH		38		// distance between objectives
#define TIMER_INTERVAL		0.3f	// timer tick interval
#define TIMER_INTERVAL_X	1.0f	// timer interval when there is no communication with LLC

#define CTRL_DIMMED 1		// panel control dimmend
#define CTRL_NOTDIMMED 0	// panel control not dimmed
#define CTRL_VISIBLE 1		// panel control visible
#define CTRL_NOTVISIBLE 0	// panel control not visible
#define LED_ON 1			// led control in ON state
#define LED_OFF 0			// led control in OFF state
#define TOGGLE_ON  1		// toggle button in ON state
#define TOGGLE_OFF 0		// toggle button in OFF state
#define TIMER_ENABLED 1		// enable timer control
#define TIMER_DISABLED 0	// disable timer control


typedef struct
{
	char cLlcModel;						// available models
	float fObjPitch[MAX_LLC_OBJ_NUM];	// available pitches
} llcModel, *pLlcModel;

// error messages
static const int MaxInPositionRange = 50;
// maximum objective position offset in um = +/- 1 mm
static const int MaxPositionOffset = 1000;
// objective position limits in mm = +/- 2 mm
static const float ObjPosOffsetLimit = 2.0f;

static const llcModel llcModels[] = {{'C', {0.0f, 38.0f, 76.0f, 114.0f, 152.0f, 190.0f, 228.0f, 266.0f}},	// for objective number: 3, 4, 6, 8
							  {'D', {0.0f, 38.0f, 76.0f, 114.0f, 152.0f, 190.0f, 228.0f, 266.0f}},			// for objective number: 6 
							  {'E', {0.0f, 54.75f, 109.5f, 164.25f, 219.0f, 273.75f, 328.5f, 383.25f}},		// for objective number: 3 
							  {'F', {0.0f, 36.5f, 73.0f, 109.5f, 146.0f, 182.5f, 219.0f, 255.5f}},			// for objective number: 3
							  {'G', {0.0f, 36.5f, 73.0f, 109.5f, 146.0f, 182.5f, 219.0f, 255.5f}},			// for objective number: 4
							  {'H', {0.0f, 27.38f, 54.76f, 82.14f, 109.52f, 136.9f, 164.28f, 191.66f}},		// for objective number: 5
							  {'J', {0.0f, 41.0f, 82.0f, 123.0f, 164.0f, 205.0f, 246.0f, 287.0f}},			// for objective number: 4, 6, 8
							  {'K', {0.0f, 41.0f, 82.0f, 123.0f, 164.0f, 205.0f, 246.0f, 287.0f}}};			// for objective number: 6

//static float g_fObjPitch[MAX_LLC_OBJ_NUM] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

// movement activity structure
enum moveType
{
	MoveOff = 0,	// no moving request
	MoveHome,		// moving to home position
	MoveToTarget	// moving to objective or target position
};

struct _moveActivityStat
{
	int iMoveType;			// type of moving request - see above enumeration
	int iMoveTimeout;		// timeout for the requested type of moving
	clock_t lStartTime;		// moving start time
	int iCtrlId;			// control ID requested the movement
	int iButtonColor;		// control (button) original color
	char sButtonLabel[32];	// control (button) label text

};

// invalid panel handle value
#define INVALID_PANEL_HANDLE -1

#define INU_OFFSET
#define INU_EXPANSION

class __declspec(dllexport) CSol_LLC
{
public:
	
	/*
	// move to objective command button constant names
	const int iLlcObjCtrlNum[] = {PANELT_COMMANDBUTTON_O1, PANELT_COMMANDBUTTON_O2, PANELT_COMMANDBUTTON_O3, PANELT_COMMANDBUTTON_O4,
		PANELT_COMMANDBUTTON_O5, PANELT_COMMANDBUTTON_O6, PANELT_COMMANDBUTTON_O7, PANELT_COMMANDBUTTON_O8};

	// objective position numeric control constant names
	const int iLlcPosCtrlNum[] = {PANELT_NUMERIC_O1, PANELT_NUMERIC_O2, PANELT_NUMERIC_O3, PANELT_NUMERIC_O4,
		PANELT_NUMERIC_O5, PANELT_NUMERIC_O6, PANELT_NUMERIC_O7, PANELT_NUMERIC_O8};
		*/

	// variables
	// serial port handle
	HANDLE port_handle;
	// panel handles
	//static int	ph_main;
	//static int ph_led;
	// error message buffer
	char cErrMsg[512];
	// number of objectives (positions)
	int g_iObjNum;
	// max motor current in this session
	float g_fMaxCurr;
	// is home detection implemeted
	bool g_bIsHomeDetImpl;
	// last message displayed in the GUI panel
	const char *g_pLastMsg;
	bool g_bIsConnectedToLlc;
	double g_fTimerInterval;
	// critical section for communication
	CRITICAL_SECTION g_cs;

	float g_fObjPitch[MAX_LLC_OBJ_NUM];

	llcModel llc_offset;

	_moveActivityStat moveActivityStat;

private:
	int		m_RealCurrentObjective;
	int		m_CurrentObjective;
	int		m_MoveObjectiveFlag;

	int		m_HomeFlag;
	

	void	ClearPanelControls(void);

	bool	SetupSerialCommunication(void);
	bool	SerialCommMrClean(void);

	bool	GetForcerSerialNum(int *piForcerSN, int *piErrCode);
	void	getLlcParameters(void);
	bool	getLlcSpeed(int *piLlcSpeed, int *piErrCode);
	bool	getLlcAcceleration(int *piLlcAcceleration, int *piErrCode);
	bool	getLlcDeceleration(int *piLlcDeceleration, int *piErrCode);
	bool	getLlcSmoothFactor(int *piLlcSmoothFactor, int *piErrCode);

	bool	isLlcHomeDetectionImplemented(int *piErrCode);
	bool	GetNumberOfObjectives(int *piObjNum, int *piErrCode, char* sOffsetFile);

	bool	enableLlcMotor(int *piErrCode);
	bool	disableLlcMotor(int *piErrCode);

	bool	homeLlc(bool bWaitForEnd, int *piErrCode);
	bool	isLlcInHomePos(int *piErrCode);
	bool	moveLlcToObjective(int iObjectiveNumber, bool bWaitForEnd, int *piErrCode);
	bool	moveLlcToPosition(int iPosition, bool bWaitForEnd, int *piErrCode);
	bool	isLlcInTargetPosition(int *piErrCode);

	int		sendLlc(char *pToSend, char *pToRecv);

	bool	getLlcStatus(int *piErrCode, const char **ppErrMsg, int *piStatReg, int *piMtrFailureReg);
	bool    getLlcPosition(float *pfLlcPosition, int *piErrCode);
	bool	getLlcVelocity(float *pfLlcVelocity, int *piErrCode);
	bool	getLlcMotorCurrent(float *pfLlcMotorCurrent, int *piErrCode);
	void	checkLlcMotionActivity();

	bool	stopLlcMotion(int *piErrCode);

	
	bool	LLC_SetSpeed(int nSpeed);
	bool	LLC_SetAccel(int nAccel);
	bool	LLC_SetDecel(int nDecel);
	bool	LLC_SetSmoothFactor(int nSmoothFactor);
	

public:
	int		LLC_OpenComport(int ComNum, char* sOffsetFile = NULL, char* sParameterFile = NULL);
	int		LLC_CloseComport();
	
	int		LLC_MotorEnable();
	int		LLC_MotorDisable();
	int		LLC_MotorStop();

	int		LLC_MotorHome();

#ifdef INU_EXPANSION
	int		LLC_Get_HomeStatus();
	int		LLC_Get_CurrentObjective();

	int		LLC_Get_MotorStatus();
#endif

	bool	LLC_GetSpeed(int *piLlcSpeed);
	bool	LLC_GetAccel(int *piLlcAccel);
	bool	LLC_GetDecel(int *piLlcDecel);
	bool	LLC_GetSmoothFactor(int *piLlcSmoothFactor);

	int		LLC_MoveToObjective(int	ObjNum);
	int		LLC_MoveToPosition(double fPosition);

	int		LLC_LlcPeriodCheck();

	bool	LLC_IsConnected();
	bool	LLC_IsLLCMove();

	bool	LLC_GetLLC_Position(float *pfLlcPosition);
	
	CSol_LLC(void);
	~CSol_LLC(void);
};

