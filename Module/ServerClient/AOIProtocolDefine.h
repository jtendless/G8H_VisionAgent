#pragma once

#include <pshpack1.h>

#define MAX_FRAME_NUM 200//80
#define MAX_SCAN_NO 10
#define MAX_DEFECT_NO 50

typedef struct
{
#if 0
	BOOL bInspFinish;
	int nDefectTotCnt;
	int nFrameTotalCount[MAX_SCAN_NO];
	int nDefectCount[MAX_SCAN_NO][MAX_FRAME_NUM];
	int nLineIndex[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	//Grab Line Index Number				
	int nImageIndex[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	//Grab Process Image Index Number				

	int x[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 영상좌표				
	int y[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 영상좌표				
	int iWidth[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 폭(pixel)				
	int iHeight[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 높이(pixel)				
	int iArea[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 면적(pixel)				
	int nDefectType[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];//ex) 0:이물 1:과에칭, 2:미에칭				

	double dRealX[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 도면좌표(mm)				
	double dRealY[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 도면좌표(mm)				
	double dRealArea[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 면적(mm)				
	double dRealWidth[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 면적(mm)				
	double dRealHeight[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 면적(mm)				

	//int iBrightness[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	// 0:dark, 1:bright				
	//int iStrength[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	//				
	//int iMaxStrength[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO];	//				

	//char cFileName[MAX_SCAN_NO][MAX_FRAME_NUM][MAX_DEFECT_NO][256]; //Str.Format("Line%02d_Frame%03d_Defect%03d_X%.3f_Y%.3f_%d"), LineNo, FrameNo, DefectNo, dDefectPosX, dDefectPosY, nDefectType);
#else
	BOOL bInspFinish;
	int nDefectTotCnt;
	int nFrameTotalCount;
	int nDefectCount[MAX_FRAME_NUM];

	int nLineIndex;	//Grab Line Index Number //0~

	int x[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 영상좌표				
	int y[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 영상좌표				
	int iWidth[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 폭(pixel)				
	int iHeight[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 높이(pixel)				
	int iArea[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 면적(pixel)				
	int nDefectType[MAX_FRAME_NUM][MAX_DEFECT_NO];//ex) 0:이물 1:과에칭, 2:미에칭				

	double dRealX[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 도면좌표(mm)				
	double dRealY[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 도면좌표(mm)				
	double dRealArea[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 면적(mm)				
	double dRealWidth[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 면적(mm)				
	double dRealHeight[MAX_FRAME_NUM][MAX_DEFECT_NO];	// 면적(mm)
#endif
}stAOIDefecInfo;

class CAOIProtocolDefine
{
public:
	CAOIProtocolDefine(){}
	~CAOIProtocolDefine(){}

public:
	enum AOI_PACKET
	{
		AOI_PACKET_MAX_SIZE = 1024,
		AOI_PACKET_MAX_DATA_SIZE = 1008,
	};

	enum AOI_CMD
	{
		// Command Define
		AOI_CMD_RESERVED = 7,

		AOI_CMD_GET_MACHINE_STATUS_REQ = 5101, //AOI->VisionAgent
		AOI_CMD_GET_MACHINE_STATUS_RES = 5102, //VisionAgent->AOI

		AOI_CMD_GET_STICK_INFO_REQ = 5201, //AOI->VisionAgent
		AOI_CMD_GET_STICK_INFO_RES = 5202, //VisionAgent->AOI

		//AOI_CMD_MOVE_STOP_REQ = 5200,
		//AOI_CMD_MOVE_STOP_RES = 5201,

		//AOI_CMD_MOVE_ABS_REQ = 5300,
		//AOI_CMD_MOVE_ABS_RES = 5301,

		//AOI_CMD_ABS_TEACHING_POS_MOVE_REQ = 5310,
		//AOI_CMD_ABS_TEACHING_POS_MOVE_RES = 5311,

		//AOI_CMD_MOVE_REL_REQ = 5400,
		//AOI_CMD_MOVE_REL_RES = 5401,

		//AOI_CMD_MOVE_JOG_REQ = 5500,
		//AOI_CMD_MOVE_JOG_RES = 5501,

		AOI_CMD_SET_MOVE_DONE_REQ = 5600, //VisionAgent->AOI //Scan Done
		AOI_CMD_SET_MOVE_DONE_RES = 5601, //AOI->VisionAgent

		AOI_CMD_GET_MOTION_STATUS_REQ = 5700, //AOI->VisionAgent
		AOI_CMD_GET_MOTION_STATUS_RES = 5701, //VisionAgent->AOI

		AOI_CMD_INSPECTION_READY_REQ = 5800, //VisionAgent->AOI
		AOI_CMD_INSPECTION_READY_RES = 5801, //AOI->VisionAgent

		AOI_CMD_SET_SURFACE_INFO_REQ = 5900, //VisionAgent->AOI
		AOI_CMD_SET_SURFACE_INFO_RES = 5901, //AOI->VisionAgent

		AOI_CMD_INSPECTION_START_END_POS_INFO_REQ = 6000, //VisionAgent->AOI
		AOI_CMD_INSPECTION_START_END_POS_INFO_RES = 6001, //AOI->VisionAgent

		AOI_CMD_INSPECTION_START_REQ = 6100, //VisionAgent->AOI
		AOI_CMD_INSPECTION_START_RES = 6101, //AOI->VisionAgent

		AOI_CMD_INSPECTION_STOP_REQ = 6200, //VisionAgent->AOI
		AOI_CMD_INSPECTION_STOP_RES = 6201, //AOI->VisionAgent

		AOI_CMD_SET_DEFECT_INFO_REQ = 6400, //AOI->VisionAgent
		AOI_CMD_SET_DEFECT_INFO_RES = 6401, //VisionAgent->AOI

		AOI_CMD_DEFECT_POS_MOVE_REQ = 6500, //AOI->VisionAgent
		AOI_CMD_DEFECT_POS_MOVE_RES = 6501, //VisionAgent->AOI

		AOI_CMD_LIGHT_ONOFF_REQ = 6600, //AOI->VisionAgent
		AOI_CMD_LIGHT_ONOFF_RES = 6601, //VisionAgent->AOI

		AOI_CMD_GANTRY_XYZ_MOVE_DONE_REQ = 6700, //VisionAgent->AOI
		AOI_CMD_GANTRY_XYZ_MOVE_DONE_RES = 6701, //AOI->VisionAgent

		AOI_CMD_TO_MC_SCAN_REQ = 6800, //AOI->VisionAgent
		AOI_CMD_TO_MC_SCAN_RES = 6801, //VisionAgent->AOI

		AOI_CMD_TO_MC_SCAN_STOP_REQ = 6900, //AOI->VisionAgent
		AOI_CMD_TO_MC_SCAN_STOP_RES = 6901, //VisionAgent->AOI
	};

	//enum AOI_MACHINE_STATUS
	typedef enum
	{
		AOI_MACHINE_STATUS_NOT_READY = 0,
		AOI_MACHINE_STATUS_READY = 1,
	}enum_AOI_MACHINE_STATUS;

	typedef enum
	{
		AOI_INSPECTION_TYPE_SLOT = 0,
		AOI_INSPECTION_TYPE_PARTICLE,
	}enum_AOI_Inspection_Type;

	typedef enum
	{
		AOI_TEACHING_POS_WAIT = 0,
		AOI_TEACHING_POS_INSPECTION = 1,
	}enum_AOI_TEACHING_POS;

	enum AOI_ERROR_CODE
	{
		AOI_ERROR_CODE_SUCCESS = 0,

		AOI_ERROR_MOVE_FAIL_UNKOWN,
		AOI_ERROR_MOVE_FAIL_POS_LIMIT,
		AOI_ERROR_MOVE_FAIL_NEG_LIMIT,
		AOI_ERROR_MOVE_FAIL_SERVO_OFF,
		AOI_ERROR_MOVE_FAIL_NOT_HOME,
		AOI_ERROR_MOVE_FAIL_SW_POS_LIMIT,
		AOI_ERROR_MOVE_FAIL_SW_NEG_LIMIT,
		AOI_ERROR_NOT_READY,
		AOI_ERROR_AXIS_NUMBER_ERROR,
		AOI_ERROR_PROCESSING_MOVE_REQ,
		AOI_ERROR_TARGET_POS_ERROR,
		AOI_ERROR_TARGET_POS_MIN_ERROR_GANTRY_X,
		AOI_ERROR_TARGET_POS_MAX_ERROR_GANTRY_X,
		AOI_ERROR_TARGET_POS_MIN_ERROR_GANTRY_Y,
		AOI_ERROR_TARGET_POS_MAX_ERROR_GANTRY_Y,
		AOI_ERROR_TARGET_POS_MIN_ERROR_BACKLIGHT_X,
		AOI_ERROR_TARGET_POS_MAX_ERROR_BACKLIGHT_X,
		AOI_GET_MOTION_STATUS_FAIL,
	};

	enum JOG_DIRECTION
	{
		JOG_DIRECTION_POS = 1,
		JOG_DIRECTION_NEG = -1,
	};

	enum MOTION_PROFILE
	{
		MOTION_PROFILE_NORMAL = 0,
		MOTION_PROFILE_RUN,
		MOTION_PROFILE_ALIGN,
		MOTION_PROFILE_SCAN,
		MOTION_PROFILE_REVIEW,
	};

public:
	class CAOICommandPacket
	{
	public:
		CAOICommandPacket(void)
		{
			ResetData();
		};
		~CAOICommandPacket(void)
		{
			ResetData();
		};

	public:
		unsigned int   uiReserved;          			// TCP/IP Command ¿¹¾à¾î Always 7
		unsigned int   uiCommand;         				// TCP/IP Command
		unsigned int   uiDataSize;            			// µÚ¿¡ ¿À´Â Packet Size
		unsigned int   uiErrorCode;           			// Error Code, No Error : 0

		void ResetData()
		{
			uiReserved = 7;
			uiCommand = 0;
			uiDataSize = 0;
			uiErrorCode = 0;
		};
	};

	class CAOIPacket
	{
	public:
		CAOIPacket(void)
		{
			ResetAOIPacket();
		};
		~CAOIPacket(void)
		{
			ResetAOIPacket();
		};

	public:
		CAOICommandPacket	m_Command;
		char				m_szBuffer[AOI_PACKET_MAX_DATA_SIZE];

	public:
		void ResetAOIPacket()
		{
			m_Command.ResetData();
			ZeroMemory(m_szBuffer, sizeof(m_szBuffer));
		};
	};


#pragma region //Machine Status
	class CAOIGetMachineStatusReq
	{
	public:
		CAOIGetMachineStatusReq()
		{
			ResetData();
		}
		~CAOIGetMachineStatusReq()
		{
			ResetData();
		}
	public:

	public:
		void ResetData()
		{
		}
	};

	class CAOIGetMachineStatusRes
	{
	public:
		CAOIGetMachineStatusRes()
		{
			ResetData();
		}
		~CAOIGetMachineStatusRes()
		{
			ResetData();
		}
	public:
		int nMachineStatus;
		BOOL bMachineBusy;

	public:
		void ResetData()
		{
			nMachineStatus = AOI_MACHINE_STATUS_NOT_READY;
			bMachineBusy = TRUE;
		}
	};
#pragma endregion

#pragma region //Move Stop
	class CAOIStopReq
	{
	public:
		CAOIStopReq()
		{
			ResetData();
		}
		~CAOIStopReq()
		{
			ResetData();
		}
	public:
		int nAxis;
	public:
		void ResetData()
		{
			nAxis = AXIS_NONE;
		}
	};

	class CAOIStopRes
	{
	public:
		CAOIStopRes()
		{
			ResetData();
		}
		~CAOIStopRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		int nAxis;
	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			nAxis = AXIS_NONE;
		}
	};
#pragma endregion

#pragma region //Abs Move
	class CAOIMoveAbsReq
	{
	public:
		CAOIMoveAbsReq()
		{
			ResetData();
		}
		~CAOIMoveAbsReq()
		{
			ResetData();
		}
	public:
		int nAxis;
		double dTargetPosition;
		int nProfile;
		double dAccel;
		double dDecel;
		double dVel;

	public:
		void ResetData()
		{
			nAxis = AXIS_NONE;
			dTargetPosition = 0.0;
			nProfile = 0;
			dAccel = 0.0;
			dDecel = 0.0;
			dVel = 0.0;
		}
	};

	class CAOIMoveAbsRes
	{
	public:
		CAOIMoveAbsRes()
		{
			ResetData();
		}
		~CAOIMoveAbsRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;

		int nAxis;
		double dTargetPosition;
		int nProfile;
		double dAccel;
		double dDecel;
		double dVel;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			nAxis = AXIS_NONE;
			dTargetPosition = 0;
			nProfile = 0;
			dAccel = 0.0;
			dDecel = 0.0;
			dVel = 0.0;
		}
	};
#pragma endregion

#pragma region //Abs Teaching Move
	class CAOIAbsTeachingPosMoveReq
	{
	public:
		CAOIAbsTeachingPosMoveReq()
		{
			ResetData();
		}
		~CAOIAbsTeachingPosMoveReq()
		{
			ResetData();
		}
	public:
		int nAxis;
		enum_AOI_TEACHING_POS eTeachingPos;
		double dAccel;
		double dDecel;
		double dVel;

	public:
		void ResetData()
		{
			nAxis = AXIS_NONE;
			eTeachingPos = AOI_TEACHING_POS_WAIT;
			dAccel = 0.0;
			dDecel = 0.0;
			dVel = 0.0;
		}
	};

	class CAOIAbsTeachingPosMoveRes
	{
	public:
		CAOIAbsTeachingPosMoveRes()
		{
			ResetData();
		}
		~CAOIAbsTeachingPosMoveRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		int nAxis;
		enum_AOI_TEACHING_POS eTeachingPos;
		double dAccel;
		double dDecel;
		double dVel;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			nAxis = AXIS_NONE;
			eTeachingPos = AOI_TEACHING_POS_WAIT;
			dAccel = 0.0;
			dDecel = 0.0;
			dVel = 0.0;
		}
	};
#pragma endregion

#pragma region //Rel Move
	class CAOIMoveRelReq
	{
	public:
		CAOIMoveRelReq()
		{
			ResetData();
		}
		~CAOIMoveRelReq()
		{
			ResetData();
		}
	public:
		int nAxis;
		double dDist; //dTargetPosition;
		int nProfile;
		double dAccel;
		double dDecel;
		double dVel;

	public:
		void ResetData()
		{
			nAxis = AXIS_NONE;
			dDist = 0; //dTargetPosition = 0;
			nProfile = 0;
			dAccel = 0.0;
			dDecel = 0.0;
			dVel = 0.0;
		}
	};

	class CAOIMoveRelRes
	{
	public:
		CAOIMoveRelRes()
		{
			ResetData();
		}
		~CAOIMoveRelRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;

		int nAxis;
		double dDist; //dTargetPosition;
		int nProfile;
		double dAccel;
		double dDecel;
		double dVel;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			nAxis = AXIS_NONE;
			dDist = 0; //dTargetPosition = 0;
			nProfile = 0;
			dAccel = 0.0;
			dDecel = 0.0;
			dVel = 0.0;
		}
	};
#pragma endregion

#pragma region //Jog Move
	class CAOIJogReq
	{
	public:
		CAOIJogReq()
		{
			ResetData();
		}
		~CAOIJogReq()
		{
			ResetData();
		}
	public:
		int nAxis;
		int nDirection;
		int nProfile;
		double dAccel;
		double dDecel;
		double dVel;

	public:
		void ResetData()
		{
			nAxis = AXIS_NONE;
			nDirection = 0;
			nProfile = 0;
			dAccel = 0.0;
			dDecel = 0.0;
			dVel = 0.0;

		}
	};

	class CAOIJogRes
	{
	public:
		CAOIJogRes()
		{
			ResetData();
		}
		~CAOIJogRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;

		int nAxis;
		int nDirection;
		int nProfile;
		double dAccel;
		double dDecel;
		double dVel;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			nAxis = AXIS_NONE;
			nDirection = 0;
			nProfile = 0;
			dAccel = 0.0;
			dDecel = 0.0;
			dVel = 0.0;
		}
	};
#pragma endregion

#pragma region //Set Move Done
	class CAOISetMoveDoneReq
	{
	public:
		CAOISetMoveDoneReq()
		{
			ResetData();
		}
		~CAOISetMoveDoneReq()
		{
			ResetData();
		}
	public:
		enum_Axis eAxis;
		double dTargetPos;

	public:
		void ResetData()
		{
			eAxis = AXIS_NONE;
			dTargetPos = 0.0;
		}
	};

	class CAOISetMoveDoneRes
	{
	public:
		CAOISetMoveDoneRes()
		{
			ResetData();
		}
		~CAOISetMoveDoneRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
		}
	};
#pragma endregion

#pragma region //Motion Status
	class CAOIGetMotionStatusReq
	{
	public:
		CAOIGetMotionStatusReq()
		{
			ResetData();
		}
		~CAOIGetMotionStatusReq()
		{
			ResetData();
		}
	public:
		enum_Axis eAxis;

	public:
		void ResetData()
		{
			eAxis = AXIS_NONE;
		}
	};

	class CAOIGetMotionStatusRes
	{
	public:
		CAOIGetMotionStatusRes()
		{
			ResetData();
		}
		~CAOIGetMotionStatusRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		enum_Axis eAxis;
		double dActPos;
		double dCmdPos;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			eAxis = AXIS_NONE;
			dActPos = 0.0;
			dCmdPos = 0.0;
		}
	};
#pragma endregion

#pragma region //Inspection Ready
	class CAOIInspectionReadyReq
	{
	public:
		CAOIInspectionReadyReq()
		{
			ResetData();
		}
		~CAOIInspectionReadyReq()
		{
			ResetData();
		}
	public:

		BOOL bInspctionReadyReq;
		int nInspectionType;
		BOOL m_GlassMode;

	public:
		void ResetData()
		{
			bInspctionReadyReq = FALSE;
			nInspectionType = AOI_INSPECTION_TYPE_SLOT;
			m_GlassMode = FALSE;
		}
	};

	class CAOIInspectionReadyRes
	{
	public:
		CAOIInspectionReadyRes()
		{
			ResetData();
		}
		~CAOIInspectionReadyRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		BOOL bInspctionReadyOk;
		int nInspectionType;
		BOOL m_GlassMode;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			bInspctionReadyOk = FALSE;
			nInspectionType = AOI_INSPECTION_TYPE_SLOT;
			m_GlassMode = FALSE;
		}
	};
#pragma endregion

#pragma region //Surface Info
	class CAOISetSurfaceInfoReq
	{
	public:
		CAOISetSurfaceInfoReq()
		{
			ResetData();
		}
		~CAOISetSurfaceInfoReq()
		{
			ResetData();
		}

	public:
		double dStickSizeX;
		double dStickSizeY;
		double dStickLeftTopX;
		double dStickLeftTopY;
		int nCellCountX;
		int nCellCountY;
		double dFirstCellLeftTopX;		//mm
		double dFirstCellLeftTopY;		//mm
		double dCellPitch_X;			//mm
		double dCellPitch_Y;			//mm		
		int nCellNoX;
		int nCellNoY;
		double dCellLeftTopX[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];			//mm
		double dCellLeftTopY[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];			//mm
		double dCellSizeX[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];				//mm
		double dCellSizeY[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];				//mm
		double dSlotCenterShiftX[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];		//mm
		double dSlotCenterShiftY[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];		//mm
		double dSlotSizeX[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];				//mm
		double dSlotSizeY[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];				//mm
		double dSlotPitchX[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];			//mm
		double dSlotPitchY[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];			//mm
		double dSlotTotalPitchX[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];		//mm
		double dSlotTotalPitchY[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT];		//mm

		//double dAlignLeftHoleX;			//mm
		//double dAlignLeftHoleY;			//mm
		//double dAlignRightHoleX;		//mm
		//double dAlignRightHoleY;		//mm
		//double dTegKeyLT_X;				//mm
		//double dTegKeyLT_Y;				//mm
		//double dTegKeyLB_X;				//mm
		//double dTegKeyLB_Y;				//mm
		//double dTegKeyRT_X;				//mm
		//double dTegKeyRT_Y;				//mm
		//double dTegKeyRB_X;				//mm
		//double dTegKeyRB_Y;				//mm

		double dDefectSizeMin;			// Defect Spec
		int nSelectCellIndexX;
		int nSelectCellIndexY;

	public:
		void ResetData()
		{
			dStickSizeX = 0.0;
			dStickSizeY = 0.0;
			dStickLeftTopX = 0.0;
			dStickLeftTopY = 0.0;
			nCellCountX = 0;
			nCellCountY = 0;
			dFirstCellLeftTopX = 0.0;	//mm
			dFirstCellLeftTopY = 0.0;	//mm
			dCellPitch_X = 0.0;			//mm
			dCellPitch_Y = 0.0;			//mm		
			nCellNoX = 0;
			nCellNoY = 0;
			for (int i = 0; i < MAX_CELL_X_COUNT; i++)
			{
				for (int j = 0; j < MAX_CELL_Y_COUNT; j++)
				{
					dCellLeftTopX[i][j] = 0.0;		//mm
					dCellLeftTopY[i][j] = 0.0;		//mm
					dCellSizeX[i][j] = 0.0;			//mm
					dCellSizeY[i][j] = 0.0;			//mm
					dSlotCenterShiftX[i][j] = 0.0;	//mm
					dSlotCenterShiftY[i][j] = 0.0;	//mm
					dSlotSizeX[i][j] = 0.0;			//mm
					dSlotSizeY[i][j] = 0.0;			//mm
					dSlotPitchX[i][j] = 0.0;			//mm
					dSlotPitchY[i][j] = 0.0;			//mm
					dSlotTotalPitchX[i][j] = 0.0;		//mm
					dSlotTotalPitchY[i][j] = 0.0;		//mm					
				}
			}
			//dAlignLeftHoleX = 0.0;		//mm
			//dAlignLeftHoleY = 0.0;		//mm
			//dAlignRightHoleX = 0.0;		//mm
			//dAlignRightHoleY = 0.0;		//mm
			//dTegKeyLT_X = 0.0;			//mm
			//dTegKeyLT_Y = 0.0;			//mm
			//dTegKeyLB_X = 0.0;			//mm
			//dTegKeyLB_Y = 0.0;			//mm
			//dTegKeyRT_X = 0.0;			//mm
			//dTegKeyRT_Y = 0.0;			//mm
			//dTegKeyRB_X = 0.0;			//mm
			//dTegKeyRB_Y = 0.0;			//mm

			dDefectSizeMin = 0.05;
			nSelectCellIndexX = -1; //-1:All
			nSelectCellIndexY = -1; //-1:All
		}
	};

	class CAOISetSurfaceInfoRes 
	{
	public:
		CAOISetSurfaceInfoRes()
		{
			ResetData();
		}
		~CAOISetSurfaceInfoRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		BOOL bSurfaceInfoRecvOk;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			bSurfaceInfoRecvOk = FALSE;
		}
	};
#pragma endregion

#pragma region //Inspection Start, End Pos
	class CAOIInspectionStartEndPosReq
	{
	public:
		CAOIInspectionStartEndPosReq()
		{
			ResetData();
		}
		~CAOIInspectionStartEndPosReq()
		{
			ResetData();
		}

	public:
		void ResetData()
		{

		}
	};

	class CAOIInspectionStartEndPosRes
	{
	public:
		CAOIInspectionStartEndPosRes()
		{
			ResetData();
		}
		~CAOIInspectionStartEndPosRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		int nCamDir;
		int nScanLineIndex;
		int nMaxScanLineCount;
		double dInspectionStartPos[2]; //0:X, 1:Y
		double dInspectionEndPos[2]; //0:X, 1:Y

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			nCamDir = 0;
			nScanLineIndex = 0.0;
			nMaxScanLineCount = 0.0;
			dInspectionStartPos[0] = 0.0;
			dInspectionStartPos[1] = 0.0;
			dInspectionEndPos[0] = 0.0;
			dInspectionEndPos[1] = 0.0;
		}
	};
#pragma endregion

#pragma region //Inspection Start
	class CAOIInspectionStartReq
	{
	public:
		CAOIInspectionStartReq()
		{
			ResetData();
		}
		~CAOIInspectionStartReq()
		{
			ResetData();
		}
	public:
		BOOL bInspectionSkip;

	public:
		void ResetData()
		{
			bInspectionSkip = FALSE;
		}
	};

	class CAOIInspectionStartRes
	{
	public:
		CAOIInspectionStartRes()
		{
			ResetData();
		}
		~CAOIInspectionStartRes()
		{
			ResetData();
		}

	public:
		int nErrorCode;
		BOOL bInspectionSkip;
		BOOL bInspectonStartRecvOk;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			bInspectionSkip = FALSE;
			bInspectonStartRecvOk = FALSE;
		}
	};
#pragma endregion

#pragma region //Inspection Stop
	class CAOIInspectionStopReq
	{
	public:
		CAOIInspectionStopReq()
		{
			ResetData();
		}
		~CAOIInspectionStopReq()
		{
			ResetData();
		}

	public:
		void ResetData()
		{
		}
	};

	class CAOIInspectionStopRes
	{
	public:
		CAOIInspectionStopRes()
		{
			ResetData();
		}
		~CAOIInspectionStopRes()
		{
			ResetData();
		}

	public:
		int nErrorCode;
		BOOL bInspectonStopRecvOk;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			bInspectonStopRecvOk = 0;
		}
	};
#pragma endregion

#pragma region //Defect Info
	class CAOISetDefectInfoReq
	{
	public:
		CAOISetDefectInfoReq()
		{
			ResetData();
		}
		~CAOISetDefectInfoReq()
		{
			ResetData();
		}
	public:
		int nLineIndex;
		int nDefectCount;

	public:
		void ResetData()
		{
			nLineIndex = 0;
			nDefectCount = 0;
		}
	};

	class CAOISetDefectInfoRes
	{
	public:
		CAOISetDefectInfoRes()
		{
			ResetData();
		}
		~CAOISetDefectInfoRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		BOOL bDefectInfoRecvOk;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			bDefectInfoRecvOk = FALSE;
		}
	};
#pragma endregion

#pragma region //Defect Pos Move
	class CAOIDefectPosMoveReq
	{
	public:
		CAOIDefectPosMoveReq()
		{
			ResetData();
		}
		~CAOIDefectPosMoveReq()
		{
			ResetData();
		}
	public:
		int nLineIndex;
		int nFrameIndex;
		int nDefectIndex;
		double dPosX;
		double dPosY;
		BOOL bBackLightWith;

	public:
		void ResetData()
		{
			nLineIndex = 0;
			nFrameIndex = 0;
			nDefectIndex = 0;
			dPosX = 0.0;
			dPosY = 0.0;
			bBackLightWith = FALSE;
		}
	};

	class CAOIDefectPosMoveRes
	{
	public:
		CAOIDefectPosMoveRes()
		{
			ResetData();
		}
		~CAOIDefectPosMoveRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		int nLineIndex;
		int nFrameIndex;
		int nDefectIndex;
		double dPosX;
		double dPosY;
		BOOL bBackLightWith;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			nLineIndex = 0;
			nFrameIndex = 0;
			nDefectIndex = 0;
			dPosX = 0.0;
			dPosY = 0.0;
			bBackLightWith = FALSE;
		}
	};
#pragma endregion

#pragma region //Gantry XYZ Move Done
	class CAOIGantryMoveDoneReq
	{
	public:
		CAOIGantryMoveDoneReq()
		{
			ResetData();
		}
		~CAOIGantryMoveDoneReq()
		{
			ResetData();
		}
	public:
		double dTargetPosX;
		double dTargetPosY;
		double dTargetPosZ;

	public:
		void ResetData()
		{
			dTargetPosX = 0.0;
			dTargetPosY = 0.0;
			dTargetPosZ = 0.0;
		}
	};

	class CAOIGantryMoveDoneRes
	{
	public:
		CAOIGantryMoveDoneRes()
		{
			ResetData();
		}
		~CAOIGantryMoveDoneRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		double dTargetPosX;
		double dTargetPosY;
		double dTargetPosZ;
		BOOL bMoveDoneRecvOk;

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			dTargetPosX = 0.0;
			dTargetPosY = 0.0;
			dTargetPosZ =0.0;
			bMoveDoneRecvOk = FALSE;
		}
	};
#pragma endregion

#pragma region //AOI Inspection Req //<<
	class CAOI_MC_INSP_Req
	{
	public:
		CAOI_MC_INSP_Req()
		{
			ResetData();
		}
		~CAOI_MC_INSP_Req()
		{
			ResetData();
		}
	public:
		BOOL bAoiToMcInspReq;

	public:
		void ResetData()
		{
			bAoiToMcInspReq = FALSE;
		}
	};

	class CAOI_MC_INSP_Res
	{
	public:
		CAOI_MC_INSP_Res()
		{
			ResetData();
		}
		~CAOI_MC_INSP_Res()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		BOOL bAoiToMcInspRes;

	public:
		void ResetData()
		{
			nErrorCode = 0;
			bAoiToMcInspRes = FALSE;
		}
	};
#pragma endregion

#pragma region //AOI Scan Stop Req //<<
	class CAOIToMcScanStopReq
	{
	public:
		CAOIToMcScanStopReq()
		{
			ResetData();
		}
		~CAOIToMcScanStopReq()
		{
			ResetData();
		}

	public:
		void ResetData()
		{
		}
	};

	class CAOIToMcScanStopRes
	{
	public:
		CAOIToMcScanStopRes()
		{
			ResetData();
		}
		~CAOIToMcScanStopRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		BOOL bScanStopRecvOk;

	public:
		void ResetData()
		{
			nErrorCode = 0;
			bScanStopRecvOk = FALSE;
		}
	};
#pragma endregion

#pragma region //Light OnOff
	class CAOILightOnOffReq
	{
	public:
		CAOILightOnOffReq()
		{
			ResetData();
		}
		~CAOILightOnOffReq()
		{
			ResetData();
		}
	public:
		BOOL bUpperLightOnOff;
		BOOL bLowerLightOnOff;
		int nUpperValue[AOI_LIGHT_CH_COUNT];
		int nLowerValue[BACKLIGHT_CH_COUNT];

	public:
		void ResetData()
		{
			bUpperLightOnOff = FALSE;
			bLowerLightOnOff = FALSE;
			memset(nUpperValue, 0, sizeof(nUpperValue));
			memset(nLowerValue, 0, sizeof(nLowerValue));
		}
	};

	class CAOILightOnOffRes
	{
	public:
		CAOILightOnOffRes()
		{
			ResetData();
		}
		~CAOILightOnOffRes()
		{
			ResetData();
		}
	public:
		int nErrorCode;
		BOOL bUpperLightOnOff;
		BOOL bLowerLightOnOff;
		int nUpperValue[AOI_LIGHT_CH_COUNT];
		int nLowerValue[BACKLIGHT_CH_COUNT];

	public:
		void ResetData()
		{
			nErrorCode = AOI_ERROR_CODE_SUCCESS;
			bUpperLightOnOff = FALSE;
			bLowerLightOnOff = FALSE;
			memset(nUpperValue, 0, sizeof(nUpperValue));
			memset(nLowerValue, 0, sizeof(nLowerValue));
		}
	};
#pragma endregion
};


#include <poppack.h>