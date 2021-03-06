#pragma once

#include "../Control/ColorButton.h"
#include "../Control/ColorStatic.h"

#define FILENAME_MODELDATA		_T("Model.ini") 
#define FILENAME_SYSTEMDATA		_T("System.ini") 

#define FILENAME_LOG_PATH		_T("\\Log") 

#define LOG_NAME_AUTO		_T("\\Auto") 
#define LOG_NAME_OP			_T("\\Op") 


#define FILENAME_IMAGE_PATH		_T("\\Image") 
//#define FILENAME_FILM_ALIGN_IMAGE_PATH		_T("\\Image") 
//#define FILENAME_INSPECT_IMAGE_PATH		_T("\\Image") 
//#define FILENAME_HOLE_MARK_IMAGE_PATH		_T("\\Image") 


//#include "../Module/Control/ColorButton.h"
#include "../Control/ColorStatic.h"

#define LOW_SPEED			0
#define MEDIUM_SPEED		1
#define HIGH_SPEED			2

#define DIR_FORWARD			0
#define DIR_BACKWARD		1

//////////////////////////////////////////////////////////////////////////
/// Define
#define WM_CHECKSTATUS		(WM_USER+300)
#define NULL_DLG							-1
#define MAIN_STATUS_DLG						0
#define MOTION_DLG							1
#define DIO_DLG								2
#define AIO_DLG								3
#define CONFIGURATION_DLG					4
#define LABELING_DLG						5
#define MAX_DIALOG_SIZE						6

#define UVW_ANGLE_X1		123.232
#define UVW_ANGLE_X2		303.232
#define UVW_ANGLE_Y		236.768

//#define UVW_RADIUS		693.397
#define UVW_RADIUS		346.699


#define _CREATE_FOLDER(str)	{\
	CFileFind	cFileFind;\
	if (cFileFind.FindFile(str) == false)\
	CreateDirectory(str, NULL);\
	cFileFind.Close();	}\

#ifndef VISION_AGENT_STATE_MENU_BTN_DEF
	#define VISION_AGENT_STATE_MENU_BTN_DEF
	typedef enum eVISION_AGENT_STATE_MENU_BTN
	{
		STATE_MENU_USER_MODE,		
		STATE_MENU_MODEL_NAME,
		STATE_MENU_BOX_ID,
		STATE_MENU_CST_ID,
		STATE_MENU_CST_DETECT,
		STATE_MENU_LASER_FOCUS,
		STATE_MENU_PICKUP_UNIT,
		STATE_MENU_CLAMP,
		STATE_MENU_STRETCHER,		
		STATE_MENU_AOI_CONNECT,
		STATE_MENU_AOI_READY_STATE,
		STATE_MENU_USER_ID,
		STATE_MENU_3D_INIT,
		STATE_MENU_MAIN_TEMPER,
		MAX_STATE_MENU_STC
	}STATE_MENU_BTN;
#endif

#ifndef VISION_AGENT_MAIN_MENU_BTN_DEF
#define VISION_AGENT_MAIN_MENU_BTN_DEF
	typedef enum eMAIN_MENU_BTN
	{
		MAIN_MENU_MODEL_BTN,
		MAIN_MENU_MANUAL_BTN,
		MAIN_MENU_MACHINE_BTN,
		MAIN_MENU_COMMUNICATION_BTN,
		MAIN_MENU_MEASUREMENT_BTN,
		MAIN_MENU_SYSTME_BTN,

		MAIN_MENU_SCREEN_SAVER_BTN,

		//20.09.17 sjc add
		MAIN_MENU_ALARAM_BTN,
		MAIN_MENU_RESET_BTN,
		//
		MAIN_MENU_READY_BTN,

		MAIN_MENU_AUTO_RUN_BTN,
		
		MAIN_MENU_ECS_BTN,

		MAIN_MENU_STOP_BTN,
		
		MAX_MAIN_MENU_BTN
	}MAIN_MENU_BTN;
#endif

typedef enum eLIGHT_NUM
{
	ALL_LIGHT,
	AXIS_LIGHT_1 = 1,
	AXIS_LIGHT_2,
	BACK_LIGHT,

	MAX_LIGHT
}LIGHT_NUM;

typedef enum enum_KIND_OF_FIND
{
	eAUTO,
	ePATTERN= 1,
	
}KIND_OF_FIND;

//System Option Comport
#if 0 //KJT Not Use
//PLC ????.
typedef struct stuct_LB_LTM
{
	//400
	WORD PC_ALIGN_STANBY : 1;
	WORD PC_ALIGN_FILM_MARK_OK : 1;
	WORD PC_ALIGN_GLASS_MARK_OK : 1;
	WORD PC_INSPECT_MARK_OK : 1;
	WORD PC_ALIGN_FILM_BUSY : 1;
	WORD PC_ALIGN_GLASS_BUSY : 1;
	WORD PC_INSPECT_BUSY : 1;
	WORD PC_ALIGN_FILM_NG : 1;
	WORD PC_ALIGN_GLASS_NG : 1;
	WORD PC_INSPECT_NG : 1;
	WORD PC_RESERVED0 : 6;

	//410
	WORD PC_RESERVED1_1 : 3;
	WORD PC_ALIGN_FILM_ALIGN_OK : 1;
	WORD PC_ALIGN_GLASS_ALIGN_OK : 1;
	WORD PC_INSPECT_OK : 1;
	WORD PC_HOLE_MARK_CHECK_BUSY : 1;
	WORD PC_HOLE_MARK_CHECK_OK : 1;
	WORD PC_HOLE_MARK_CHECK_FORCE_OK : 1;
	WORD PC_HOLE_MARK_CHECK_NG : 1;
	WORD PC_RESERVED1_2 : 6;

	//420
	WORD PC_RESERVED2 : 16;

	//430
	WORD PC_RESERVED3 : 16;

	//440------------------------------------------------------------------------------------------
	WORD PC_RESERVED4_1 : 1;
	WORD PC_ALIGN_FILM_RUN_REPLY : 1;
	WORD PC_ALIGN_GLASS_RUN_REPLY : 1;
	WORD PC_INSPECT_RUN_REPLY : 1;

	WORD PC_ALIGN_FILM_MOVE_OK_REPLY : 1;
	WORD PC_ALIGN_GLASS_MOVE_OK_REPLY : 1;
	WORD PC_INSPECT_MOVE_OK_REPLY : 1;

	WORD PC_ALIGN_FILM_RESET_REPLY : 1;
	WORD PC_ALIGN_GLASS_RESET_REPLY : 1;
	WORD PC_INSPECT_RESET_REPLY : 1;
	WORD PC_RESERVED4_2 : 6;


	//450
	WORD PC_ALIGN_FILM_PROCESS_REPLY : 1;
	WORD PC_ALIGN_GLASS_PROCESS_REPLY : 1;
	WORD PC_INSPECT_PROCESS_REPLY : 1;
	WORD PC_RESERVED5 : 7;

	//460
	WORD PC_FLOW_AUTO_RUN_START_REPLY : 1;
	WORD PC_AUTO_RUN_DONE_REPLY : 1;
	WORD PC_RESERVED6_1 : 1;
	WORD PC_STATE_PLC_MODE_CHANGE_REPLY : 1;
	WORD PC_STATE_DOOR_CHANGE_REPLY : 1;
	WORD PC_STATE_EMS_CHANGE_REPLY : 1;
	WORD PC_RESERVED6_2 : 1;
	WORD PC_RECIPE_CHANGE_REPLY : 1;
	WORD PC_RECIPE_DELETE_REPLY : 1;
	WORD PC_RECIPE_ADD_REPLY : 1;
	WORD PC_RESERVED6_3 : 6;
	 
	//470
	WORD PC_RESERVED7_1 : 16;

	//480
	WORD PC_RESERVED8_1 : 16;

	//490
	WORD PC_STATE_ALIVE : 1;
	WORD PC_STATE_WORK_AUTHORITY_CHANGE : 1;
	WORD PC_STATE_PC_MODE_CHANGE : 1;
	WORD PC_CIM_DATA_WRITE : 1;
	WORD PC_RESERVED9_1 : 1;
	WORD PC_RECIPE_CHANGE_NG : 1;
	WORD PC_RECIPE_CHANGE_DEL_NG : 1;
	WORD PC_RECIPE_CHANGE_ADD_NG : 1;
	WORD PC_RESERVED9_2 : 8;
}LB_LTM, *pLB_LTM;

typedef struct struct_ALIGN_DATA_DD_3_AXIS
{
	INT32 X;
	INT32 Y;
	INT32 T;
}ALIGN_DATA_DD_3_AXIS, *pALIGN_DATA_DD_3_AXIS;

typedef struct struct_ALIGN_DATA_UVW_3_AXIS
{
	INT32 X1;
	INT32 X2;
	INT32 Y1;
}ALIGN_DATA_UVW_3_AXIS, *pALIGN_DATA_UVW_3_AXIS;

typedef struct struct_ALIGN_DATA_UVW_4_AXIS
{
	INT32 X1;
	INT32 Y1;
	INT32 X2;
	INT32 Y2;
}ALIGN_DATA_UVW_4_AXIS, *pALIGN_DATA_UVW_4_AXIS;

typedef struct struct_VISION_DATA
{
	INT32 X1;
	INT32 Y1;
	INT32 X2;
	INT32 Y2;
}VISION_DATA, *pVISION_DATA;

typedef struct stuct_LW_LTM
{
	//25400
	ALIGN_DATA_DD_3_AXIS PC_FILM_STAGE_DATA;
	WORD PC_DATA_RESERVED[4];

	//25410
	ALIGN_DATA_UVW_3_AXIS PC_GLASS_STAGE_DATA;
	WORD PC_DATA_RESERVED1[4];

	//25420
	VISION_DATA PC_DATA_HOLE_MARK_RESULT;
	WORD PC_DATA_RESERVED2[2];

	//25430
	WORD PC_DATA_NG_ALARM_CODE;
	WORD PC_DATA_AUTHORITY_MODE;
	WORD PC_DATA_WOKER_ID[6];
	WORD PC_DATA_RESERVED3[2];

	//25440
	WORD PC_DATA_PC_MODE_CHANGE;
	WORD PC_DATA_RESERVED4[9];

	//25450
	ALIGN_DATA_DD_3_AXIS PC_FILM_ALIGN_OFFSET_DATA;
	WORD PC_DATA_RESERVED5[4];
	
	//25460
	WORD PC_DATA_RESERVED6[10];

	//25470
	WORD PC_DATA_RESERVED7[10];

	//25480
	WORD PC_DATA_RESERVED8[10];

	//25490
	WORD PC_DATA_RESERVED9[10];

}LW_LTM, *pLW_LTM;

typedef struct stuct_LB_MTL
{
	//200
	WORD PLC_ALIGN_STANBY : 1;
	WORD PLC_ALIGN_FILM_ALIGN_RUN : 1;
	WORD PLC_ALIGN_GLASS_ALIGN_RUN : 1;
	WORD PLC_INSPECT_RUN : 1;
	WORD PLC_ALIGN_FILM_MOVE_OK : 1;
	WORD PLC_ALIGN_GLASS_MOVE_OK : 1;
	WORD PLC_INSPECT_MOVE_OK : 1;
	WORD PLC_ALIGN_FILM_RESET : 1;
	WORD PLC_ALIGN_GLASS_RESET : 1;
	WORD PLC_INSPECT_RESET : 1;
	WORD PLC_RESERVED0 : 6;

	//210
	WORD PLC_ALIGN_FILM_PROCESS : 1;
	WORD PLC_ALIGN_GLASS_PROCESS : 1;
	WORD PLC_INSPECT_PROCESS : 1;
	WORD PLC_HOLE_MARK_CHECK : 1;
	WORD PLC_RESERVED1_1 : 1;
	WORD PLC_HOLE_MARK_CHECK_RESET : 1;
	WORD PLC_RESERVED1_2 : 10;

	//220
	WORD PLC_RESERVED2 : 16;

	//230
	WORD PLC_RESERVED3 : 16;

	//240
	WORD PLC_RESERVED4_1 : 1;
	WORD PLC_ALIGN_FILM_MARK_OK_REPLY : 1;
	WORD PLC_ALIGN_GLASS_MARK_OK_REPLY : 1;
	WORD PLC_INSPECT_MARK_OK_REPLY : 1;

	WORD PLC_ALIGN_FILM_BUSY_REPLY : 1;
	WORD PLC_ALIGN_GLASS_BUSY_REPLY : 1;
	WORD PLC_INSPECT_BUSY_REPLY : 1;

	WORD PLC_ALIGN_FILM_NG_REPLY : 1;
	WORD PLC_ALIGN_GLASS_NG_REPLY : 1;
	WORD PLC_INSPECT_NG_REPLY : 1;
	WORD PLC_RESERVED4_2 : 6;

	//250
	WORD PLC_ALIGN_FILM_ALIGN_OK_REPLY : 1;
	WORD PLC_ALIGN_GLASS_ALIGN_OK_REPLY : 1;
	WORD PLC_INSPECT_OK_REPLY : 1;
	WORD PLC_RESERVED5 : 13;

	//260
	WORD PLC_STATE_ALIVE_CHECK : 1;
	WORD PLC_STATE_WORK_AUTHORITY_CHANGE_REPLY : 1;
	WORD PLC_STATE_PC_MODE_CHANGE_REPLY : 1;
	WORD PLC_RESERVED6_1 : 1;
	WORD PLC_OFFSET_DATA_WRITE_REQUEST : 1;
	WORD PLC_RESERVED6_2 : 1;
	WORD PLC_RECIPE_CHANGE_NG_REPLY : 1;
	WORD PLC_RECIPE_DELETE_NG_REPLY : 1;
	WORD PLC_RECIPE_ADD_NG_REPLY : 1;
	WORD PLC_RESERVED6_3 : 7;

	//270
	WORD PLC_RESERVED7_1 : 16;

	//280
	WORD PLC_RESERVED8_1 : 16;

	//290
	WORD PLC_AUTO_RUN : 1;
	WORD PLC_AUTO_RUN_DONE : 1;
	WORD PLC_RESERVED9_1 : 1;
	
	WORD PLC_RECIPE_CHANGE : 1;
	WORD PLC_RECIPE_DELETE : 1;
	WORD PLC_RECIPE_ADD : 1;

	WORD PLC_RESERVED9_2 : 1;

	WORD PLC_STATE_MODE_CHANGE : 1;
	WORD PLC_STATE_DOOR_CHANGE : 1;
	WORD PLC_STATE_EMS_CHANGE : 1;

	WORD PLC_RESERVED9_3 : 6;

}LB_MTL, *pLB_MTL;

typedef struct stuct_GANTRY_2_HEAD
{
	INT32 Y1;
	INT32 Y2;
	INT32 X1;
	INT32 X2;
	INT32 RESERVED;
	INT32 Z1;
	INT32 Z2;
}GANTRY_2_HEAD, *pGANTRY_2_HEAD;

typedef struct stuct_LW_MTL
{
	//25000
	ALIGN_DATA_DD_3_AXIS PLC_DATA_FILM_ALIGN_MOTOR_POS;
	INT32 PLC_DATA_FILM_CAMERA_Y1;
	INT32 PLC_DATA_FILM_CAMERA_Y2;

	//25010
	ALIGN_DATA_UVW_3_AXIS PLC_DATA_GLASS_ALIGN_MOTOR_POS;
	WORD PLC_DATA_RESERVED1[4];

	//25020
	INT32 PLC_DATA_DRUM_X_AXIS;
	INT32 PLC_DATA_GLASS_CAMERA_Y1_AXIS;
	INT32 PLC_DATA_GLASS_CAMERA_Y2_AXIS;
	WORD PLC_DATA_RESERVED2[4];

	//25030
	WORD PLC_DATA_ALIGN_FILM_NUM;
	WORD PLC_DATA_RESERVED3_1;
	WORD PLC_DATA_INSPECT_FILM_POS_NUM;
	WORD PLC_DATA_INSPECT_FILM_NUM;
	WORD PLC_DATA_RESERVED3_2[6];

	//25040
	WORD PLC_DATA_RESERVED4[10];

	//25050
	WORD PLC_DATA_RESERVED5[10];

	//25060
	WORD PLC_DATA_RESERVED6[10];

	//25070 ~ 25080
	WORD PLC_DATA_PANEL_ID[20];

	//25090
	WORD PLC_DATA_RECIPE_CHANGE_NUMBER;
	WORD PLC_DATA_RECIPE_DELETE_NUMBER;
	WORD PLC_DATA_RECIPE_ADD_NUMBER;

	WORD PLC_DATA_PLC_MODE;
	WORD PLC_DATA_DOOR_OPEN_STATE;
	WORD PLC_DATA_EMS_STATE;
	WORD PLC_DATA_RESERVED7[4];
}LW_MTL, *pLW_MTL;


//25500 ~ 25799
typedef struct struct_LW_OFFSET_UNIT
{
	INT32 CELL_OFFSET_LT_X;
	INT32 CELL_OFFSET_LT_Y;

	INT32 CELL_OFFSET_LB_X;
	INT32 CELL_OFFSET_LB_Y;
	
	WORD RESERVED_1[2];

	INT32 CELL_OFFSET_RT_X;
	INT32 CELL_OFFSET_RT_Y;

	INT32 CELL_OFFSET_RB_X;
	INT32 CELL_OFFSET_RB_Y;

	WORD RESERVED_2[2];

	INT32 CELL_X;
	INT32 CELL_Y;
	INT32 CELL_T;

	WORD RESERVED_3[4];

}LW_OFFSET_UNIT, *pLW_OFFSET_UNIT;

typedef struct stuct_LW_RESULT_DATA
{
	LW_OFFSET_UNIT RESULT_DATA[10];
}LW_RESULT_DATA, *pLW_RESULT_DATA;


//PLC Address Define
#define LB_LTM_START_ADDRESS																	0x400
#define LB_MTL_START_ADDRESS																	0x200


#define LW_LTM_START_ADDRESS																	0x6338
#define LW_MTL_START_ADDRESS																	0x61A8

#define LW_DATA_START_ADDRESS																0x639C
																				

//LW_ADRRESS
enum enum_LB_LTM_ADDRESS
{
	//400
	ePC_ALIGN_STANBY = 0x400,
	eALIGN_FILM_MARK_OK,
	eALIGN_GLASS_MARK_OK,
	eINSPECT_MARK_OK,
	eALIGN_FILM_BUSY,
	eALIGN_GLASS_BUSY,
	eINSPECT_BUSY,
	eALIGN_FILM_NG,
	eALIGN_GLASS_NG,
	eINSPECT_NG,

	//410
	eALIGN_FILM_ALIGN_OK = 0x413,
	eALIGN_GLASS_ALIGN_OK,
	eINSPECT_OK,
	eHOLE_MARK_CHECK_BUSY,
	eHOLE_MARK_CHECK_OK,
	eHOLE_MARK_CHECK_FORCE_OK,
	eHOLE_MARK_CHECK_NG,

	//440------------------------------------------------------------------------------------------
	eALIGN_FILM_RUN_REPLY = 0x441,
	eALIGN_GLASS_RUN_REPLY,
	eINSPECT_RUN_REPLY,
	eALIGN_FILM_MOVE_OK_REPLY,
	eALIGN_GLASS_MOVE_OK_REPLY,
	eINSPECT_MOVE_OK_REPLY,
	eALIGN_FILM_RESET_REPLY,
	eALIGN_GLASS_RESET_REPLY,
	eINSPECT_RESET_REPLY,

	//450
	eALIGN_FILM_PROCESS_REPLY = 0x450,
	eALIGN_GLASS_PROCESS_REPLY,
	eINSPECT_PROCESS_REPLY,

	//460
	eFLOW_AUTO_RUN_START_REPLY = 0x460,
	eAUTO_RUN_DONE_REPLY,
	eSTATE_PLC_MODE_CHANGE_REPLY = 0x463,
	eSTATE_DOOR_CHANGE_REPLY,
	eSTATE_EMS_CHANGE_REPLY,
	eRECIPE_CHANGE_REPLY = 0x467,
	eRECIPE_DELETE_REPLY,
	eRECIPE_ADD_REPLY,

	//490
	eSTATE_ALIVE = 0x490,
	eSTATE_WORK_AUTHORITY_CHANGE,
	eSTATE_PC_MODE_CHANGE,
	eOFFSET_DATA_WRITE_REPLY,
	eRECIPE_CHANGE_NG = 0x495,
	eRECIPE_CHANGE_DEL_NG,
	eRECIPE_CHANGE_ADD_NG,
};

enum enum_LB_MTL_ADDRESS
{
	//200
	ePLC_ALIGN_STANBY = 0x200,
	eALIGN_FILM_ALIGN_RUN,
	eALIGN_GLASS_ALIGN_RUN,
	eINSPECT_RUN,
	eALIGN_FILM_MOVE_OK,
	eALIGN_GLASS_MOVE_OK,
	eINSPECT_MOVE_OK,
	eALIGN_FILM_RESET,
	eALIGN_GLASS_RESET,
	eINSPECT_RESET,

	//210
	eALIGN_FILM_PROCESS = 0x210,
	eALIGN_GLASS_PROCESS,
	eINSPECT_PROCESS,
	eHOLE_MARK_CHECK,
	
	eHOLE_MARK_CHECK_RESET = 0x215,

	//240
	eALIGN_FILM_MARK_OK_REPLY = 0x241,
	eALIGN_GLASS_MARK_OK_REPLY,
	eINSPECT_MARK_OK_REPLY,
	eALIGN_FILM_BUSY_REPLY,
	eALIGN_GLASS_BUSY_REPLY,
	eINSPECT_BUSY_REPLY,
	eALIGN_FILM_NG_REPLY,
	eALIGN_GLASS_NG_REPLY,
	eINSPECT_NG_REPLY,

	//250
	eALIGN_FILM_ALIGN_OK_REPLY = 0x250,
	eALIGN_GLASS_ALIGN_OK_REPLY,
	eINSPECT_OK_REPLY,

	//260
	eSTATE_ALIVE_CHECK = 0x260,
	eSTATE_WORK_AUTHORITY_CHANGE_REPLY,
	eSTATE_PC_MODE_CHANGE_REPLY,
	eCIM_DATA_WRITE_REQUEST = 0x264,
	eRECIPE_CHANGE_NG_REPLY = 0x266,
	eRECIPE_DELETE_NG_REPLY,
	eRECIPE_ADD_NG_REPLY,

	//290
	eAUTO_RUN = 0x290,
	eAUTO_RUN_DONE,
	eRECIPE_CHANGE = 0x293,
	eRECIPE_DELETE,
	eRECIPE_ADD,
	eSTATE_MODE_CHANGE = 297,
	eSTATE_DOOR_CHANGE,
	eSTATE_EMS_CHANGE,
};

enum enum_LW_LTM_ADDRESS
{
	//25400
	eFILM_STAGE_DATA = 0x6338,
	//25410
	eGLASS_STAGE_DATA = 0x6342,

	//25420
	eHOLE_MARK_RESULT = 0x634C,


	//25430
	eNG_ALARM_CODE = 0x6356,
	eAUTHORITY_MODE,
	eWOKER_ID,

	//25440
	ePC_MODE_CHANGE = 0x6360,
	ePC_FILM_ALIGN_OFFSET_DATA = 0x636A,
};

enum enum_LW_MTL_ADDRESS
{
	//25000
	eFILM_MOTOR_POS = 0x61A8,
	eFILM_GANTRY_Y1 = 0x61AE,
	eFILM_GANTRY_Y2 = 0x61B0,

	//25010
	eGLASS_MOTOR_POS = 0x61B2,

	//25020
	eDRUM_X_AXIS = 0x61BC,
	eDRUM_Y1_AXIS = 0x61BE,
	eDRUM_Y2_AXIS = 0x61C0,

	//25030
	eALIGN_FILM_NUM = 0x61C6,
	eINSPECT_FILM_POS_NUM = 0x61C8,
	eINSPECT_FILM_NUM,

	//25070 ~ 25080
	ePANEL_ID = 0x61EE,

	//25090
	eRECIPE_CHANGE_NUMBER = 0x6202,
	eRECIPE_DELETE_NUMBER,
	eRECIPE_ADD_NUMBER,
	ePLC_MODE,
	eDOOR_OPEN_STATE,
	eEMS_STATE,

};
#endif

#define PLC_TO_PC_TRANSFER_VALUE 0.0001
#define PC_TO_PLC_TRANSFER_VALUE 10000


//???? ???? ????.
#define BK_GND			RGB(35, 35, 35)									//background

#define STATEBAR_NAME_RGB		RGB(160, 160, 160)			//?????? ???? TEXT
#define STATEBAR_NAME_BK_RGB	RGB(45, 45, 45)					//?????? ???? background
#define STATEBAR_VALUE_RGB		RGB(200, 200, 200)			//?????? ?? ???? TEXT
#define STATEBAR_VALUE_BK_RGB	RGB(90, 90, 90)					//?????? ?? background
#define STATEBAR_VALUE_GREEN  RGB(0, 128,0)					//Green
#define STATEBAR_VALUE_RED  RGB(200, 0,0)					//Red

#define BTN_LAMP_ON				RGB(255, 128, 0) //??????
#define BTN_LAMP_OFF			RGB(128, 128, 128) //??????

const COLORREF CLOUDBLUE = RGB(128, 184, 223);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF BLACK = RGB(1, 1, 1);
const COLORREF DKGRAY = RGB(128, 128, 128);
//const COLORREF LLTGRAY = RGB(220, 220, 220);
const COLORREF LLTGRAY = RGB(225, 225, 225);
const COLORREF LTGRAY = RGB(192, 192, 192);
const COLORREF YELLOW = RGB(255, 255, 0);
const COLORREF DKYELLOW = RGB(128, 128, 0);
const COLORREF RED = RGB(255, 0, 0);
const COLORREF DKRED = RGB(128, 0, 0);
const COLORREF BLUE = RGB(0, 0, 255);
const COLORREF LBLUE = RGB(192, 192, 255);
const COLORREF DKBLUE = RGB(0, 0, 128);
const COLORREF CYAN = RGB(0, 255, 255);
const COLORREF DKCYAN = RGB(0, 128, 128);
const COLORREF GREEN = RGB(0, 255, 0);
const COLORREF DKGREEN = RGB(0, 128, 0);
const COLORREF MAGENTA = RGB(255, 0, 255);
const COLORREF DKMAGENTA = RGB(128, 0, 128);


//////////////////////////////////////////////////////////////////
//Set Time-Out
#define TIME_OUT_CYLINDER	(30 * 1000)			// mse
#define TIME_OUT_MOTION		(3 * 60 * 1000)	// msec
#define TIME_OUT_FORCE_CONTROL		(20 * 60 * 1000)	// msec
#define TIME_OUT_DUAL		(60 * 60 * 1000)	// msec
#define TIME_OUT_STATE		(1 * 60 * 1000)	// msec 5Min.
#define TIME_OUT_WELDING	(1 * 20 * 1000)	// msec
#define TIME_OUT_MOTION_X	(1 * 60 * 1000)	// msec
#define TIME_OUT_COMUNICATION (3  * 1000)	// msec
#define TIME_OUT_PROCESSING (5 * 1000) //msec

#define TIME_OUT_MAPPING		(48 * 60 * 60 * 1000)	// msec

#define TIME_OUT_PULSE (3  * 100)	// msec

#define TIME_OUT_DELAY (30*1000) //msec

#define TIME_OUT_LOADING_DELAY (15*1000) //msec

#define TIME_OUT_ROBOT_INTERFACE (10 * 60 * 1000)	// msec)

#define TIME_OUT_STRETCH_ZERO	(5  * 1000)		// msec
#define TIME_OUT_STRETCH	(1 * 15 * 1000)		// msec
#define TIME_OUT_ORIGIN		(2 * 60 * 1000)		// msec
#define TIME_OUT_STANDBY	TIME_OUT_MOTION		//( 1 * 60 * 1000)   // msec
#define TIME_OUT_UNCLAMP	(1 * 5 * 1000)		// msec
#define TIME_OUT_CF_WAIT	(20 * 1000)		// msec //180410 KJT 30->20 (by LCJ)

#define TIME_OUT_AUTO_SEQ		(20 * 60 * 1000)	// msec
#define BARCODE_DELAY (100) //msec

#define TIME_OUT_DD_90	(600*1000) //msec

enum enum_VisionAlarmCode
{
	eNONE,
	SCORE_TOP_LIMIT,
	SCORE_BOTTOM_LIMIT,
	eFIND_TOP_FAIL,
	eFIND_BOTTOM_FAIL,
	eCAM_VALUE_OVER,
	eALIGN_DATA_LIMIT,
	eMARK_SIZE_ERROR,
	eINSPECT_RESULT_ERROR,
	eRECIPE_CHANGE_ERROR = 20,
	eALARM_MAX,
};

enum enum_LIGHT_NUM
{
	eLIGHT_TOP_FILM_AXIS = 1,
	eLIGHT_BOTTOM_FILM_AXIS,
	eLIGHT_TOP_GLASS_AXIS,
	eLIGHT_BOTTOM_GLASS_AXIS,

	eLIGHT_TOP_FILM_RING,
	eLIGHT_BOTTOM_FILM_RING,
	eLIGHT_TOP_GLASS_RING,
	eLIGHT_BOTTOM_GLASS_RING,
};

#define FILM_MAX_NUM			10
#define FILM_MAX_ROI_NUM		8