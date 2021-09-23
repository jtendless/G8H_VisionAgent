#pragma once

#define DEFAULT_VEL_GANTRY_XY_MAX		200.0
#define DEFAULT_VEL_INSPECTION_CAMERA_Z_MAX		60.0
#define DEFAULT_VEL_TRANSFER_Z_MAX		70.0
#define DEFAULT_VEL_BACKLIGHT_X_MAX		200.0
#define DEFAULT_VEL_GRIPPER_CLAMP_MAX	10.0
#define DEFAULT_VEL_GRIPPER_STRETCH_MAX	30.0
#define DEFAULT_VEL_GRIPPER_PITCH_MAX	30.0
#define DEFAULT_VEL_GRIPPER_WEDGE_Z_MAX		20.0
#define DEFAULT_VEL_BOX_ALIGN_CAMERA_Y_MAX		100.0
#define DEFAULT_VEL_TRANSFER_Y_MAX		200.0
#define DEFAULT_VEL_MAGAZINE_LIFT_Z_MAX		20.0
#define DEFAULT_VEL_INKJET_Y_MAX				20.0
#define DEFAULT_VEL_TRANSFER_X_MAX		200.0
#define DEFAULT_VEL_STAGE_XYT_MAX		20.0
#define DEFAULT_VEL_ETC_MAX				20.0


#define DEFAULT_VEL_WORK_DIV	1.0 
#define DEFAULT_VEL_GANTRY_XY									(DEFAULT_VEL_GANTRY_XY_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_INSPECTION_CAMERA_Z				(DEFAULT_VEL_INSPECTION_CAMERA_Z_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_TRANSFER_Z								(DEFAULT_VEL_TRANSFER_Z_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_BACKLIGHT_X								(DEFAULT_VEL_BACKLIGHT_X_MAX/DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_GRIPPER_CLAMP							(DEFAULT_VEL_GRIPPER_CLAMP_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_GRIPPER_STRETCH						(DEFAULT_VEL_GRIPPER_STRETCH_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_GRIPPER_PITCH							(DEFAULT_VEL_GRIPPER_PITCH_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_GRIPPER_WEDGE_Z						(DEFAULT_VEL_GRIPPER_WEDGE_Z_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_BOX_ALIGN_CAMERA_Y					(DEFAULT_VEL_BOX_ALIGN_CAMERA_Y_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_TRANSFER_Y								(DEFAULT_VEL_TRANSFER_Y_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_MAGAZINE_LIFT_Z						(DEFAULT_VEL_MAGAZINE_LIFT_Z_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_INKJET_Y										(DEFAULT_VEL_INKJET_Y_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_TRANSFER_X								(DEFAULT_VEL_TRANSFER_X_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_STAGE_XYT									(DEFAULT_VEL_STAGE_XYT_MAX / DEFAULT_VEL_WORK_DIV)
#define DEFAULT_VEL_ETC												(DEFAULT_VEL_ETC_MAX / DEFAULT_VEL_WORK_DIV)

//--------------------------------------------
typedef struct MACHINE_DATA_MOTOR_T
{
	double dSafetyPosMin[AXIS_MAX];
	double dSafetyPosMax[AXIS_MAX];
	double dOriginPos[AXIS_MAX];
	double dMaxVel[AXIS_MAX];
	double dAutoVel[AXIS_MAX];
	double dAutoAccel[AXIS_MAX];
	double dAutoDecel[AXIS_MAX];
	double dManualHighVel[AXIS_MAX];
	double dManualHighAccel[AXIS_MAX];
	double dManualHighDecel[AXIS_MAX];
	double dManualMediumVel[AXIS_MAX];
	double dManualMediumAccel[AXIS_MAX];
	double dManualMediumDecel[AXIS_MAX];
	double dManualLowVel[AXIS_MAX];
	double dManualLowAccel[AXIS_MAX];
	double dManualLowDecel[AXIS_MAX];
}CMachineDataMotorInfo, *pMachineDataMotorInfo;
class CMachineDataMotor
{
public:
	CMachineDataMotor() {}
	~CMachineDataMotor() {}
public:
	CMachineDataMotorInfo Info;
	CMachineDataMotorInfo DefaultInfo;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};
//--------------------------------------------
class CMachineData
{
public:
	static CMachineDataMotor				m_MachineDataMotor;
public:
	CMachineData();
	~CMachineData();

	static void Initialize(void);
	static void Finalize(void);
	static void Save();
	static void Load();
};