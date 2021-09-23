
// stdafx.h : ÀÚÁÖ »ç¿ëÇÏÁö¸¸ ÀÚÁÖ º¯°æµÇÁö´Â ¾Ê´Â
// Ç¥ÁØ ½Ã½ºÅÛ Æ÷ÇÔ ÆÄÀÏ ¹× ÇÁ·ÎÁ§Æ® °ü·Ã Æ÷ÇÔ ÆÄÀÏÀÌ 
// µé¾î ÀÖ´Â Æ÷ÇÔ ÆÄÀÏÀÔ´Ï´Ù.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // °ÅÀÇ »ç¿ëµÇÁö ¾Ê´Â ³»¿ëÀº Windows Çì´õ¿¡¼­ Á¦¿ÜÇÕ´Ï´Ù.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ÀÏºÎ CString »ý¼ºÀÚ´Â ¸í½ÃÀûÀ¸·Î ¼±¾ðµË´Ï´Ù.

// MFCÀÇ °øÅë ºÎºÐ°ú ¹«½Ã °¡´ÉÇÑ °æ°í ¸Þ½ÃÁö¿¡ ´ëÇÑ ¼û±â±â¸¦ ÇØÁ¦ÇÕ´Ï´Ù.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ÇÙ½É ¹× Ç¥ÁØ ±¸¼º ¿ä¼ÒÀÔ´Ï´Ù.
#include <afxext.h>         // MFC È®ÀåÀÔ´Ï´Ù.


#include <afxdisp.h>        // MFC ÀÚµ¿È­ Å¬·¡½ºÀÔ´Ï´Ù.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 °ø¿ë ÄÁÆ®·Ñ¿¡ ´ëÇÑ MFC Áö¿øÀÔ´Ï´Ù.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows °ø¿ë ÄÁÆ®·Ñ¿¡ ´ëÇÑ MFC Áö¿øÀÔ´Ï´Ù.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFCÀÇ ¸®º» ¹× ÄÁÆ®·Ñ ¸·´ë Áö¿ø

#pragma warning(disable: 4800)
#pragma warning(disable: 4819)
#pragma warning(disable: 4101)

//20201106
#include "mmSystem.h"
#pragma comment(lib, "Winmm.lib")

#include "Data/XmlFile.h"

#include "VisionAgentDlg.h"
#include "Vision/VisionAgentDefine.h"
#include "Motion/MotionAgentDefine.h"
#include "Vision/SharedInfo.h"
#include "Vision/Devs.h"

//#include "CIM/CimInfo.h"

#include "CalcAlign/CalcAlign.h"

#include "Data/ModelData.h"
#include "Data/SystemData.h"
#include "Data/ManualData.h"
#include "Data/MachineData.h"

#include "Control/NumEdit.h"
#include "Control/ClrButton.h"
#include "ListCtrl/CommonListCtrl.h"

#include "FmmLight1.h"
#include "FmmLight2.h"

#define UM_MP_CONNECTION_MESSAGE		WM_USER + 1

//#include "../WkLibFlow/WkLibFlow.h"
//#include "../WkLibCtrl/WkLibCtrl.h"

#ifndef SIM_MODE
#include "../WkLibLaserDispOm/WkLibLaserDispOm.h"
#pragma comment(lib, "../Execution/WkLibLaserDispOm")
#endif

#ifndef MIL_NOT_USE
#include "../WkLibVision/WkLibVision.h"
#pragma comment(lib,"../Execution/WkLibVision.lib")

#include "mil.h"
#pragma comment(lib, "Mil.lib")
#pragma comment(lib, "Milcal.lib")
#pragma comment(lib, "Miledge.lib")
#pragma comment(lib, "Milim.lib")
#endif

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#pragma region //Motion
#include "Motion/JogMotion.h"
#include "Motion/GantryMotion.h"
#include "Motion/Frame_Unit_Motion.h"
#include "Motion/InspectionStageMotion.h"
#include "Motion/ClampMotion.h"
#include "Motion/StretchMotion.h"
#pragma endregion


#include "../Module/Log/LogDefine.h"

//#include "C:/MELSEC/Common/INCLUDE/Mdfunc.h"
//#pragma comment(lib,"C:/MELSEC/Common/LIB/x64/MdFunc32.lib") 

#ifdef _DEBUG
#pragma comment (lib, "../Execution/WkLibBdc.lib")
#pragma comment (lib, "../Execution/WkLibMitubish.lib")
#pragma comment (lib, "../Execution/WkLibPua310.lib")
//#pragma comment (lib, "../Execution/WkLibVision.lib")
#pragma comment(lib, "../Execution/WkLibFlow.lib")
#pragma comment(lib, "../Execution/WkLibCtrl.lib")
#else
#pragma comment (lib, "../Execution/WkLibBdc.lib")
#pragma comment (lib, "../Execution/WkLibMitubish.lib")
#pragma comment (lib, "../Execution/WkLibPua310.lib")
#pragma comment (lib, "../Execution/WkLibVision.lib")
#pragma comment(lib, "../Execution/WkLibFlow.lib")
#pragma comment(lib, "../Execution/WkLibCtrl.lib")
#endif

#include "Common/CommonDefine.h"

#include "CamAreaModul.h"

#include "Dll/Ajin/include/AXD.h"	
#include "Dll/Ajin/include/AXA.h"	
#include "Dll/Ajin/include/AXL.h"	

#include "Module/MotionModule.h"
#include "Module/UmacAxis.h"
#include "Module/AjinAxis.h"
#include "Module/IO.h"

#include <afxcontrolbars.h>

#include "PositionKeyInDlg.h"
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>


#define SAFE_PRINTF(szDest,...)		_sntprintf_s(szDest, _countof(szDest), _countof(szDest)-1, ##__VA_ARGS__)
#define SAFE_STRCPY(szDest, szSrc)	_tcsncpy_s(szDest, _countof(szDest), szSrc, _countof(szDest)-1)


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

//¿¡·¯ ¹«½ÃÇÏ±â À§ÇÑ ÀÓ½Ã ÀÛ¼º - Choi_20200422
#define STRSAFE_NO_DEPRECATE
//---------------------------------------------

#define	CAM_BUF_SIZE_X_2M	2448//1600
#define	CAM_BUF_SIZE_Y_2M	2048//1200
#define	CAM_BUF_SIZE_X_5M	2448
#define	CAM_BUF_SIZE_Y_5M	2048

#define	LED_LAMP_ON		RGB(50, 255, 50)
#define	LED_LAMP_OFF	RGB(200, 200, 206)

enum
{
	_eSTATE_NONE = 0,
	_eSTATE_START,
	_eSTATE_COMPLETE,
};

/*Flow Group ID*/
enum {
	_eFRAME_LOAD_GRP_ID_PRODUCT_RECEIVE = 0,
	_eFRAME_LOAD_GRP_ID_CENTERING,
	_eFRAME_LOAD_GRP_ID_BCR,
	_eFRAME_LOAD_GRP_ID_COUNT,
}eFrame_Load_Grp_ID;

enum {
	_eFRAME_ALIGN_GRP_ID_MEASURE = 0,
	_eFRAME_ALIGN_GRP_ID_ALIGN,
	_eFRAME_ALIGN_GRP_ID_COUNT,
}eFrame_Align_Grp_ID;

enum {
	_eFRAME_CF_PUSH_GRP_ID_WAIT_POS = 0,
	_eFRAME_CF_PUSH_GRP_ID_FORWARD,
	_eFRAME_CF_PUSH_GRP_ID_CONTACT,
	_eFRAME_CF_PUSH_GRP_ID_PUSH,
	_eFRAME_CF_PUSH_GRP_ID_COUNT,
}eFrame_CF_Push_Grp_ID;

enum {
	_eFRAME_FLATNESS_GRP_ID_MEASURE = 0,
	_eFRAME_FLATNESS_GRP_ID_WAIT_POS,
	_eFRAME_FLATNESS_GRP_ID_COUNT,
}eFrame_Flatness_Grp_ID;

enum {
	_eFRAME_CF_RELEASE_GRP_ID_RELEASE = 0,
	_eFRAME_CF_RELEASE_GRP_ID_BACKWARD,
	_eFRAME_CF_RELEASE_GRP_ID_COUNT,
}eFrame_CF_Release_Grp_ID;

enum {
	_eFRAME_UNLOAD_GRP_ID_WAIT_POS = 0,
	_eFRAME_UNLOAD_GRP_ID_CENTERING,
	_eFRAME_UNLOAD_GRP_ID_PRODUCT_GETOUT,
	_eFRAME_UNLOAD_GRP_ID_RETURN,
	_eFRAME_UNLOAD_GRP_ID_COUNT,
}eFrame_UnLoad_Grp_ID;

enum {
	_eMASK_LOAD_GRP_ID_PICK_UP,
	_eMASK_LOAD_GRP_ID_RETURN,
	_eMASK_LOAD_GRP_ID_COUNT,
}eMask_Load_Grp_ID;

enum {
	_eMASK_INSERT_GRP_ID_WAIT_POS = 0,
	_eMASK_INSERT_GRP_ID_INSERT,
	_eMASK_INSERT_GRP_ID_COUNT
}eMask_Insert_Grp_ID;

enum {
	_eMASK_ALIGN_GRP_ID_WAIT_POS = 0,
	_eMASK_ALIGN_GRP_ID_ALIGN_MEAS,
	_eMASK_ALIGN_GRP_ID_ALIGN_MOVE,
	_eMASK_ALIGN_GRP_ID_COUNT
}eMask_Align_Grp_ID;

enum {
	_eMASK_TENSION_GRP_ID_WAIT_POS = 0,
	_eMASK_TENSION_GRP_ID_TENSION,
	_eMASK_TENSION_GRP_ID_COUNT
}eMask_Tension_Grp_ID;

enum {
	_eMASK_TRANSLATE_GRP_ID_WAIT_POS = 0,
	_eMASK_TRANSLATE_GRP_ID_TARGET_POS,
	_eMASK_TRANSLATE_GRP_ID_COUNT
}eMask_Translate_Grp_ID;

enum {
	_eMASK_WELDING_GRP_ID_WAIT_POS = 0,
	_eMASK_WELDING_GRP_ID_WELDING_BEFORE_MEAS,
	_eMASK_WELDING_GRP_ID_WELDING,
	_eMASK_WELDING_GRP_ID_WELDING_AFTER_MEAS,
	_eMASK_WELDING_GRP_ID_COUNT
}eMask_Welding_Grp_ID;

#define DEFAULT_SPEED_LOW		2
#define DEFAULT_SPEED_MID		5
#define DEFAULT_SPEED_HIGH		10
#define DEFAULT_SPEED			DEFAULT_SPEED_LOW
#define DEFAULT_ACCEL			100
#define DEFAULT_DECEL			100

bool FileExist(LPCTSTR lpPathName);
CString GetHomeDir();
bool	DirectoryExist(CString DirPath);
bool	DeleteDir(CString DirPath);
BOOL IsSameDirectory(CString StrLocation);

/////////////////////////////////////////////////////
// Show Error Message
#define UM_ERROR_MSG				WM_USER+1200
//notify alarm
#define UM_NOTIFY_ALARM				WM_USER+1201
//send message
#define SEND_MESSAGE_BOX			WM_USER+1202
//Open message Box - Step by Step
#define OPEN_MESSAGE_BOX			WM_USER+1203
//Close message Box  - Step by Step
#define CLOSE_MESSAGE_BOX			WM_USER+1204
// Show Command Message 
#define UM_COMMAND_MSG				WM_USER+1210  
#define UM_SERIAL_COMMAND_MSG				WM_USER+1233
//Show Process State
#define UPDATEDATA_RUN_STEP			WM_USER+1220

#define LD35AF_RECEIVED				WM_USER+1300	// ppa
#define LAF3_RECEIVED				WM_USER+1301	// review
#define NAMSG_COMM_READ			    WM_USER +1302

//#define SAVE_IMAGE_DATA				WM_USER+1400

// UM_COMMAND_MSG용 WPARM 값
#define CMD_SHOW_ALARM				100
#define CMD_SHOW_INIT_PROCESS		101
#define CMD_UPDATE_INIT_PROCESS		102
#define CMD_HIDE_INIT_PROCESS		103
#define CMD_INIT_MATROX_BD			104       
#define CMD_INIT_SAPERA_BD			105
#define CMD_INIT_GIGE_CAM			106
#define CMD_INIT_WORK_NETWORK		107
#define CMD_CAM_VIEW_SHOW			108
#define CMD_SERIAL_LASER		109
#define CMD_SERIAL_TEMP			110