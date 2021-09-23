

#pragma once
////////////////////////////////////////////////////////////////////////
#define ON_LINE		1
#define OFF_LINE		0

//////////////////////////////////////////////////////////////////////////
/// Define
#define NULL_DLG								-1
#define MAIN_STATUS_DLG				0
#define MOTION_DLG							1
#define DIO_DLG								2
#define AIO_DLG								3
#define FUNCTION_DLG						4
#define LABELING_DLG						5
#define MAX_DIALOG_SIZE				6

#define SF		0
#define CF		1

#define FORCE_CONTROL_DEC_RATE		0.01



//////////////////////////////////////////////////////////////////////////
/// Message
#define WM_NUMBER_KEYPAD				(WM_USER+200)
#define WM_CHAR_KEYPAD					(WM_USER+201)

#define KOREAN							0
#define ENGLISH							1

#define MAX_VISION_AXIS_SIZE		 2

//Dual Gantry UMac Axis 정리.
//Gantry 1	 //	Gantry 2	//	Gripper 1	//	Gripper 2	//	Gantry 1	//	Gantry 1
//Y1	Y2	     //  Y5	Y6	    //   Y3	Y4    //   Y7  Y8	    //  X1 X2 X3  //  X4 X5 X6
// 1   2	     //   3	 4	    //    5	 6	    //   7    8	    //   9  10 11	//  12 13 14

//Max Module Size.
#define MAX_UMAC_AXIS_SIZE					32
#define USE_UMAC_WHOLE_SIZE					(14+4)
#define USE_UMAC_AXIS_SIZE					14					//Awk Dual Gantry 적용. 

//총 점수.
#define MAX_AXIS_SIZE						128

#define MAX_DINPUT_SIZE					256
#define MAX_DOUTPUT_SIZE					128
#define MAX_AINPUT_SIZE					80
#define MAX_AOUTPUT_SIZE					8

#define MAX_COORDINATE						6
#define MAX_COORDINATE_AXIS_SIZE			8
//총 점수 Display
#define REAL_AXIS_SIZE						102
//WK 추가.(보드당 점수)
#define AI_DATA_NUM						16
#define AO_DATA_NUM						8
#define DI_DATA_NUM						32
#define DO_DATA_NUM						32
#define MOTION_NUM							16

//Active, Label, Real, Plc, Home
#define UMAC_CONTROL_AXIS					0
#define UMAC_VERTUAL						1	
#define UMAC_REAL_AXIS						2
#define UMAC_PLC_NO						3
#define UMAC_HOME_NO						4
#define UMAC_HOME_NO_SLAVE					5
#define UMAC_RESOLUTION					6

#define	Use								1
#define NoUse								-1
////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_DOUTPUT_DWORD_SIZE				4
#define MAX_DINPUT_DWORD_SIZE				8

#define MAX_MODULE_SIZE					20

#define UMAC_AXIS_Y1						1
#define UMAC_AXIS_Y2						2
#define UMAC_AXIS_Y						21

#define UMAC_AXIS_X						3

//#define MASK_UVW							0
//#define MAX_UVW							1
//
//#define FRAME_UVW							0
//#define MAX_UVWX							1

#define	MAX_UVW_NUM						1

#define MAX_CENTERING_NUM					8
#define MAX_CF_NUM							6

#define MAX_FORCE_CONTROL_UNIT_NUM			5

#define SF_FRONT							0
#define SF_BACK							1
#define COUNTER_FORCE						2
#define CENTERING_X						3
#define CENTERING_Y						4



#define MAX_SF_NUM							16		

#define MAX_UVW_AXIS_SIZE					3
#define MAX_UVWX_AXIS_SIZE					4

#define MAX_STRETCH						2
#define MAX_STEP							30


#define MAX_STRETCH_AXIS_SIZE				16
#define MAX_STRETCH_AXIS_USE				8

#define MAX_FORCE_CONTROL_SIZE				8

#define FORCE_CONTROL_STATUS_IDLE			100
#define FORCE_CONTROL_STATUS_EMG			200
#define FORCE_CONTROL_STATUS_SUCCESS		300
#define FORCE_CONTROL_STATUS_FAIL			400

#define STRETCH_THREAD_IDLE					-1
#define STRETCH_THREAD_RUN					0
#define STRETCH_THREAD_STOP					1

#define CLAMP_STATUS_HOME					0
#define CLAMP_STATUS_CLAMP					1
#define CLAMP_STATUS_UNCLAMP				2
#define CLAMP_STATUS_FAIL					3


#define GANTRY_MASTER_AXIS					26
#define GANTRY_SLAVE_AXIS					27

#define AUTO_MODE							0
#define MANUAL_MODE						1

#define BK_GND	RGB(255,255,255)

typedef enum _CAM_Z_MOVE_POSITON
{
	CAM_Z_MOVE_POSITON_FOCUS = 0,
	CAM_Z_MOVE_POSITON_WAIT,
	CAM_Z_MOVE_POSITON_UP,
	CAM_Z_MOVE_POSITON_DOWN,
	CAM_Z_MOVE_POSITON_MAX,			

}CAM_Z_MOVE_POSITON, *PCAM_Z_MOVE_POSITON;



typedef enum _CAM_SELECT_Z
{
	CAM_SELECT_Z1 = 0,
	CAM_SELECT_Z2,
	CAM_SELECT_ZMAX,

}CAM_SELECT_Z, *PCAM_SELECT_Z;

typedef enum _AXIS_SELECT
{
	AXIS_SELECT_X = 0,
	AXIS_SELECT_Y,
	//AXIS_SELECT_Z,
	AXIS_SELECT_MAX,

}AXIS_SELECT, *PAXIS_SELECT;

typedef enum _L_R_SELECT
{
	L_R_SELECT_L = 0,
	L_R_SELECT_R,
	L_R_SELECT_MAX,

}L_R_SELECT, *PL_R_SELECT;


typedef enum _GUN_CAM_SELECT
{
	GUN_CAM_SELECT_GUN = 0,
	GUN_CAM_SELECT_CAM,
	CGUN_CAM_SELECT_MAX,

}GUN_CAM_SELECT, *PGUN_CAM_SELECT;

typedef enum _WELDING_POSITON
{
	WELDING_POSITON_0 = 0,
	WELDING_POSITON_1,
	WELDING_POSITON_2,
	WELDING_POSITON_3,
	WELDING_POSITON_4,
	WELDING_POSITON_5,
	WELDING_POSITON_6,
	WELDING_POSITON_7,
	WELDING_POSITON_8,
	WELDING_POSITON_9,
	WELDING_POSITON_MAX,

}WELDING_POSITON, *PWELDING_POSITON;

