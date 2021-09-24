/******************************************************************************
 *	
 *	(C) Copyright WDI 2012
 *	
 ******************************************************************************
 *
 *	FILE:		atf_def.h
 *
 *	PROJECT:	AFT Sensors
 *
 *	SUBPROJECT:	.
 *
 *	Description: ATF related definitions
 *	
 ******************************************************************************
 *	
 *	Change Activity
 *	Defect  Date       Developer        Description
 *	Number  DD/MM/YYYY Name
 *	======= ========== ================ =======================================
 *          19/04/2012 Chris O.        Initial version
 *                                     
 *****************************************************************************/

#pragma once

#ifdef __cplusplus
	extern "C" {
#endif

#define MAX_NAMEDPIPE_PATH 279 // 2 + 15 + 1 + 4 + 1 + 256; \\ServerName\pipe\PipeName
#define NAMEDPIPE_NAME_DEF "ATFCommandPipe"
#define NAMEDPIPE_TIMEOUT 20000
#define NAMEDPIPE_CLIENT_ID_DEF 1
#define NAMEDPIPE_PACKET_INDEX_DEF 1
#define NAMEDPIPE_PACKET_ID_DEF 0
#define NAMEDPIPE_COMMAND_LENGTH ( (((DtWordEnm)&DtDataType)>>4) * MAX_SCANLINE_LENGTH) // 8000, cf. ReadScanline()
#define MAX_NAMEDPIPE_RETRIES 1 // single attempt only
#define NAMEDPIPE_PACKET_REFRESH_DELAY 50
#define NAMEDPIPE_PACKET_REFRESH_DELAY_VARIANCE 5
#define NAMEDPIPE_PACKET_ARRAY_ACCESS_RETRIES 100

static const DWORD 	DeviceID_DevAtf = 1; // cf. enum DeviceId from AgisDefs.h

// data type
typedef enum 
{
	DtNoDataEnm					= 0x00,
	DtByteEnm					= 0x10,
	DtWordEnm					= 0x20,
	DtDwordEnm					= 0x30,
	DtDataType					= 0x30,
	DtArrayEnm					= 0x40,
	DtOffsetEnm					= 0x80,
	DtSignedEnm					= 0x80,
	DtLastDataEnm				= 0x80,
} EppDataType;

// sensor status packed data
typedef struct 
{
	unsigned short  miv : 1;
	unsigned short  in_focus : 1;
	unsigned short  sync : 1;
	unsigned short  laser_enabled : 1;
	unsigned short  invalid_data : 1;
			 short  position : 11; 
} RsData, *RsDataPtr;
// sensor position max value
#define MAX_RS_POS  511
// sensor position min value
#define MIN_RS_POS  -512

// fpga config flags
enum FpgaConfigFlagsEnm 
{
    FpgaConfig_Analog             = 0x00000001,
    FpgaConfig_MtrCtl             = 0x00000002,
    FpgaConfig_XY_MtrCtl          = 0x00000004,
    FpgaConfig_Std_Mcm            = 0x00000008,
    FpgaConfig_Maaf               = 0x00000010,
    FpgaConfig_Mfc_Mcm            = 0x00000020,
    FpgaConfig_StepDir_Mcm        = 0x00000040,
    FpgaConfig_HW_Link_Mcm        = 0x00000080,
    FpgaConfig_Any_Mcm            = 0x0000007e,

	FpgaConfigMfc_Led1            = 0x00000100,
    FpgaConfigMfc_Led2            = 0x00000200,
    FpgaConfigMfc_Led3            = 0x00000400,
    FpgaConfigMfc_12VReg          = 0x00000800,
    FpgaConfigMfc_Epld            = 0x00001000,
    FpgaConfigMfc_Whistle         = 0x00002000,
    FpgaConfigMfc_IntZDrive       = 0x00004000,
    FpgaConfigMfc_Reserved        = 0x00008000,
    FpgaConfigMfc_Flags           = 0x0000ff00,

    FpgaConfigMfcLinkDown         = 0x00010000,

    FpgaConfig_XY_Encoder         = 0x01000000,
};

// hardware status flags
enum HwStatusFlagsEnm 
{
    HwOK                    = 0x00000001,   // exec: hardware seems to be OK
    HwCasErr                = 0x00000002,   // exec: PPR_SR_CAS_TIME_ERR

	HwLaserDioDisabled      = 0x00000010,   // exec: PPR_SR_DIOR_LASER_ENABLE

    HwSyncDioAsserted       = 0x00000100,   // exec: ^PPR_SR_DIOR_SYNC
    HwSyncDioLastFrame      = 0x00000200,   // exec: PPR_SR_DIOR_SYNC_LASTFRAME
    HwSyncEnabled           = 0x00000400,   // exec: FCS_CR_SYNC_SENSE_ENABLE

    HwMotionZ               = 0x00001000,   // exec: FMP_CR_MOTION_BUSY
    HwMotionX               = 0x00002000,   // exec: FMP_CR_X_MOVE
    HwMotionY               = 0x00004000,   // exec: FMP_CR_Y_MOVE

    HwMotionCWLimit         = 0x00010000,   // exec: FMP_CR_CW_LIMIT_SWITCH
    HwMotionCWLimitSense    = 0x00020000,   // exec: FMP_CR_CW_SENSE    
    HwMotionCCWLimit        = 0x00040000,   // exec: FMP_CR_CCW_LIMIT_SWITCH
    HwMotionCCWLimitSense   = 0x00080000,   // exec: FMP_CR_CCW_SENSE

    HwMotionInhibit         = 0x00100000,   // exec: FMP_CR_MOTION_INHIBIT
    HwMotionInhibitSense    = 0x00200000,   // exec: FMP_CR_MOTION_INHIBIT_SENSE    
};

// sensor status flags
enum StatusFlagsEnm 
{
	MsHwOK                  = 0x00000001,   // exec: hardware seems to be OK
	MsSwOK                  = 0x00000002,   // exec: software finds all OK    
	MsXYMotion              = 0x00000004,   // exec: XY motion
	MsZMotion               = 0x00000008,   // exec: Z  motion

	MsEnableLaser           = 0x00000010,   // param: turn laser On, Off
	MsLaserDisabledMode     = 0x00000020,   // exec: entered laser disabled mode    
	MsEnableSyncSensitivity = 0x00000040,   // param: sync is enabled
	MsSyncMode              = 0x00000080,   // exec: entered sync mode

	MsExecuteAf             = 0x00000100,   // param    
	MsLaserTracking         = 0x00000200,   // param
	MsZTracking             = 0x00000400,   // param
	MsNearWindow            = 0x00000800,   // exec: set if near mode is used (7D or dominate)

	MsMiv                   = 0x00001000,   // exec
	MsInFocus               = 0x00002000,   // exec
	MsFMotion               = 0x00004000,   // exec
	MsCachedData            = 0x00008000,   // exec: signifies that data is generated from last frame, and temporary unavailable
};

// sensor window definitions
#define     FAR_WINDOW                  0       // far mode window
#define     NEAR_WINDOW                 1       // near mode window
#define     FAR3D_WINDOW                2       // indicate far window working in 3D mode
#define     SV_WINDOW                   3       // single frame window

//#define MAX_SCANLINE_LENGTH				1400 NS: changed to 4000 below to support in future buffer requirements for scanline
#define  MAX_SCANLINE_LENGTH				4000

// error codes return by sensor
enum AtfCodesEnm 
{
	AfStatusOK					= 0,
	AfStatusSaturated			= 1,
	AfStatusLowIntensity		= 2,
    AfStatusOutOfBound			= 3,
	AfStatusFailed				= 5,
	AfNotSupported				= 6,
	AfSyntaxError				= 7,
	AfNotAvailable				= 11,
};

#define AtfNamesTable					\
	static const char* g_AtfStatusName[] = {\
	"0-OK",								\
	"1-Saturated",						\
	"2-LowIntensity",					\
	"3-OutOfBound",						\
	0,									\
	"5-Failed",							\
	"6-NotSupported",					\
	"7-SyntaxError",					\
	0,									\
	0,									\
	0,									\
	"11-Not Available",					\
	};

typedef enum {
	WindowFarEnm	= 0,	// far mode window
	WindowAtf4Enm	= 0,	// atf4 window
	WindowNear1Enm	= 2,	// near mode single window
	WindowNear7Enm	= 1,	// near mode seven segment window
	WindowNear3Enm	= 1,	// near mode 3 segments window
	WindowAutoEnm   = 0x1000,	// allow for automatic change between far and near window
} WindowEnm;

enum CmAutoDetectEnum
{
	CmAutoDetectStatusDone		= 0,	// ready to be run
	CmAutoDetectStop		    = 1,	// 
	CmAutoDetectStatusInitial	= 4,	// not ran yet, ready to be run
	CmAutoDetectStatusPending	= 11,	// will be in progress
	CmAutoDetectStatusFailed	= 10,	// failed due to some error
	CmAutoDetectStatusBusy		= 13,	// in progress
	// other codes indicate error
};
enum CmRetarderEnum
{
	CmRetarderStatusUnavailable = 0,	// no retardation installed (not a wasp)
	CmRetarderStatusCalibrating = 1,	// undergoing calibration
	CmRetarderStatusActive		= 2,	// ready for operation
	CmRetarderStatusInactive	= 3,	// turned off
};

enum ConfigExtEnum {
	CeePZ1_Activate     = 0x0400,             // activate PZ1 (turns on PZ1 and sets it to 0)
	CeePZ2_Activate     = 0x0800,             // activate PZ2 (turns on PZ2 and sets it to 0)
	CeeZAA_Move         = 0x0100,             // use Zaa for motion
	CeePZ_Move          = 0x0200,             // use Pz for motion
	CeeX_Move			= 0x1000,			  // X stage
	CeeFC_Move			= 0x2000,			  // FC stage
	CeeAO_Out           = 0x0000,             // use analog out for sensor position
	CeeCanbus			= 0x4000,				//zaa canbus
	CeeCan402			= 0x8000,				//zaa canbus 402
} ;

enum StageSelectorEnum {
	SseZAA				= 1,
	SsePZ				= 2,
	SseOOA				= 3,
};

enum OoaStatus
{
	OoaStatusCCWLimitON			= 0x0001,
	OoaStatusCWLimitON			= 0x0002,
	OoaStatusDirReverse			= 0x0004,
	OoaStatusIsMoving			= 0x0080,
	OoaStatusMcxMask			= 0x00FF,
	OoaStatusIsHoming			= 0x0100,
	OoaStatusHomed				= 0x0200,
	OoaStatusIsInPosition		= 0x0400,
	OoaStatusLastMoveStarted	= 0x1000,
	OoaStatusLastMoveTo			= 0x2000,
	OoaStatusLastMoveError		= 0x4000,
	OoaStatusLastMoveMask		= 0xF000,
	OoaStatusOoaMask			= 0xFF00,
};

typedef enum {
	PrcesEnm_7DotNoOutliers        = 0x0000,	// select peaks w/o outliers
	PrcesEnm_7DotLeastMotion       = 0x0100,   // select peaks that pass screening
	PrcesEnm_7DotAvgAll            = 0x0200,   // select average out of 3 dots (before 7.1.41.1)       
	PrcesEnm_7DotTop			   = 0x0200,   // use upper dots (recent then 7.1.41.1)       
	PrcesEnm_7DotMedian            = 0x0300,   // select median out of 3 dots
	PrcesEnm_7Dot1                 = 0x0400,   // force dot 1
	PrcesEnm_7Dot2                 = 0x0500,   // force dot 2
	PrcesEnm_7Dot3                 = 0x0600,   // force dot 3
	PrcesEnm_7DotCentral           = 0x0700,   // force dot 4
	PrcesEnm_7Dot5                 = 0x0800,   // force dot 5
	PrcesEnm_7Dot6                 = 0x0900,   // force dot 6
	PrcesEnm_7Dot7                 = 0x0a00,   // force dot 7
	PrcesEnm_7DotConsistent        = 0x0b00,   // use dots that proved to be most stable    
	PrcesEnm_7DotBottom            = 0x0c00,   // use lower dots
	PrcesEnm_7DotRecent            = 0x0d00,   // use mst recent dot    
	PrcesEnm_7DotLeft              = 0x0e00,   // use all left dots (1,2,3)
	PrcesEnm_7DotRight             = 0x0f00,   // use all right dots (5,6,7)    
} ProcessEnm;

enum EooStatus
{
	EoaStatusUninitialized		= 0,
	EoaStatusAbsent				= 1,	// hw not found
	EoaStatusCalibrating		= 2,	// hw undergoes calibratrion
	EoaStatusOK					= 3,	// hw ready and calibrated
	EoaStatusWalking			= 4,	// hw driven by internal process
	EoaStatusFailed				= 99,	// hw operation had failed
};

typedef enum
{
	ErrOK = 0,
	ErrNoAccess = 1,
	ErrWrongType = 2,
	ErrOutOfBound = 3,
	ErrInvalid = 4,
	ErrUnavailable = 5,
	ErrNotSupported = 6,
	ErrSntaxError = 7,
	ErrNoresources = 8,
	ErrInternal = 9,
	ErrOperFailed = 10,
	ErrTimeout = 11,
	ErrChksum = 12,
	ErrUnknown = 13,
	ErrOperFailedWithNack = 2570,
// For atf_sendCommand():
	ErrInvalidPacketIndex = 0xfffffff7,
	ErrInvalidPacketID = 0xfffffff8,
	ErrInvalidRequest = 0xfffffff9,
	ErrResponseBufferMissing = 0xfffffffa,
	ErrRequestBufferMissing = 0xfffffffb,
	ErrMalformedMessage = 0xfffffffc,
	ErrIncorrectDevice = 0xfffffffd,
	ErrResponseSizeTooLong = 0xfffffffe,
	ErrComPortNotAvailable = 0xffffffff
} EppErrorCodes;

 enum OptionReg{
	DOF = 0x08,
	MCMplus = 0x04,
	ExtZ = 0x02,
	IntZ = 0x01

};

 enum DofStatus {
	 DofNOErr=0x00,
	 DofComOK = 0x01,			     ///commmand done
	 Dof_Timeout = 0x02,	// TIMEOUT	.......need to check value it corresponds to timeout
	 DofMotorDisabled = 0x04,	     // Motor disabled
	 DofInFoldBack = 0x08,		     // In Foldback
	 Dof_COMErr_NoDataRec = 0x10,  // Communication error: No data recieved
	 Dof_COMErr_ErrCode = 0x20,    // Communication error: Error code received
	 Dof_COMErr_ReSyncErr = 0x30,   // Communication error: Resync Error, can be used to check if dover stage is connected after power up
	
 };

enum NamedPipeMessageOffsets {
	 AtfMessageOffsetDeviceId			= 0,
	 AtfMessageOffsetClientId			= (AtfMessageOffsetDeviceId + 4),
	 // Requests
	 AtfMessageOffsetRequestId			= (AtfMessageOffsetClientId + 4),
	 AtfMessageOffsetRequestParameters	= (AtfMessageOffsetRequestId + 4),
	 // Responses
	 AtfMessageOffsetResponseValue		= (AtfMessageOffsetClientId + 4),
	 AtfMessageOffsetResponseParameters	= (AtfMessageOffsetResponseValue + 4),
	 // WriteArray
	 AtfMessageOffsetWriteArrayPacketIndex	= AtfMessageOffsetRequestParameters,
	 AtfMessageOffsetWriteArrayPacketID		= (AtfMessageOffsetWriteArrayPacketIndex + 4),
	 AtfMessageOffsetWriteArrayBid			= (AtfMessageOffsetWriteArrayPacketID + 4),
	 AtfMessageOffsetWriteArrayPid			= (AtfMessageOffsetWriteArrayBid + 4),
	 AtfMessageOffsetWriteArrayTag			= (AtfMessageOffsetWriteArrayPid + 4),
	 AtfMessageOffsetWriteArrayNum			= (AtfMessageOffsetWriteArrayTag + 4),
	 AtfMessageOffsetWriteArrayOffset		= (AtfMessageOffsetWriteArrayNum + 4),
	 AtfMessageOffsetWriteArrayFromSize		= (AtfMessageOffsetWriteArrayOffset + 4),
	 AtfMessageOffsetWriteArrayFrom			= (AtfMessageOffsetWriteArrayFromSize + 4),
	 // WriteArray response
	 AtfMessageOffsetWriteArrayResponsePacket	= AtfMessageOffsetResponseParameters,
	 // ReadArray
	 AtfMessageOffsetReadArrayBid		= AtfMessageOffsetRequestParameters,
	 AtfMessageOffsetReadArrayPid		= (AtfMessageOffsetReadArrayBid + 4),
	 AtfMessageOffsetReadArrayTag		= (AtfMessageOffsetReadArrayPid + 4),
	 AtfMessageOffsetReadArrayNum		= (AtfMessageOffsetReadArrayTag + 4),
	 AtfMessageOffsetReadArrayOffset	= (AtfMessageOffsetReadArrayNum + 4),
	 // ReadArray response
	 AtfMessageOffsetReadArrayResponsePacket	= AtfMessageOffsetResponseParameters,
	 AtfMessageOffsetReadArrayToSize			= (AtfMessageOffsetReadArrayResponsePacket + 4),
	 AtfMessageOffsetReadArrayTo				= (AtfMessageOffsetReadArrayToSize + 4),
	 // GetCommBaudrate
	 AtfMessageOffsetGetCommBaudrateValue	= AtfMessageOffsetRequestParameters,
	 // SendCmnd
	 AtfMessageOffsetSendCmndPacketIndex	= AtfMessageOffsetRequestParameters,
	 AtfMessageOffsetSendCmndPacketID		= (AtfMessageOffsetSendCmndPacketIndex + 4),
	 AtfMessageOffsetSendCmndExpByteNum		= (AtfMessageOffsetSendCmndPacketID + 4),
	 AtfMessageOffsetSendCmndTimeout		= (AtfMessageOffsetSendCmndExpByteNum + 4),
	 AtfMessageOffsetSendCmndToSendSize		= (AtfMessageOffsetSendCmndTimeout + 4),
	 AtfMessageOffsetSendCmndToSend			= (AtfMessageOffsetSendCmndToSendSize + 4),
	 // SendCmnd response
	 AtfMessageOffsetSendCmndResponsePacketIndex	= AtfMessageOffsetResponseParameters,
	 AtfMessageOffsetSendCmndResponsePacketID		= (AtfMessageOffsetSendCmndPacketIndex + 4),
	 AtfMessageOffsetSendCmndToRecvSize				= (AtfMessageOffsetSendCmndPacketID + 4),
	 AtfMessageOffsetSendCmndToRecv					= (AtfMessageOffsetSendCmndToRecvSize + 4),
 };

 enum NamedPipeMessageRequests {
	 AtfMessageRequestInvalid				= -1,
	 AtfMessageRequestWriteArray			= 0,
	 AtfMessageRequestReadArray,
	 AtfMessageRequestChangeCommTimeouts,
	 AtfMessageRequestResetCommTimeouts,
	 AtfMessageRequestChangeCommBaudrate,
	 AtfMessageRequestGetCommBaudrate,
	 AtfMessageRequestRecoverSensor,
	 AtfMessageRequestPingAck,
	 AtfMessageRequestReset,
	 AtfMessageRequestIsSerialConnection,
	 AtfMessageRequestSendCmnd,
	 AtfMessageRequestMySendCmnd,
	 AtfMessageRequestGetNewClientID,
 };

 // total 
 enum NamedPipeMessageBufferSizes {
	 AtfMessageBufferSize					= 256,
	 AtfMessageBufferSizeWriteArrayRequest	= (AtfMessageBufferSize - AtfMessageOffsetWriteArrayFrom),
	 AtfMessageBufferSizeReadArrayResponse	= (AtfMessageBufferSize - AtfMessageOffsetReadArrayTo),
	 AtfMessageBufferSizeSendCmndRequest	= (AtfMessageBufferSize - AtfMessageOffsetSendCmndToSend),
	 AtfMessageBufferSizeSendCmndResponse	= (AtfMessageBufferSize - AtfMessageOffsetSendCmndToRecv),
	 AtfMessageBufferSizeMySendCmndRequest	= (AtfMessageBufferSize - AtfMessageOffsetSendCmndToSend),
	 AtfMessageBufferSizeMySendCmndResponse	= (AtfMessageBufferSize - AtfMessageOffsetSendCmndToRecv),
 };

 /******************************************************************************
		for pfa sensor 
 ******************************************************************************/
#define OBJCONFEXT_MODE_ALL                       0x100000
#define OBJCONFEXT_MODE_AF                        0x200000
#define OBJCONFEXT_MODE_AOI                       0x400000
#define OBJCONFEXT_MODE_EE                        0x800000
#define OBJCONFEXT_MODE_SR                       0x1000000
#define OBJCONFEXT_MODE_VIDEO                    0x2000000
#define OBJCONFEXT_MODE_MASK                     0x3F00000

/*****************************************************************************/

#ifdef __cplusplus
	}
#endif