#include "stdafx.h"
#include "CamAreaModul.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "SystemDlg.h"

#ifndef MIL_NOT_USE
CCamAreaModul *g_pCam6G_LT = NULL; 
CCamAreaModul *g_pCam6G_RT = NULL; 
CCamAreaModul *g_pCam6G_RB = NULL; 
CCamAreaModul *g_pCam6G_LB = NULL; 

CCamAreaModul *g_pCam8G_LT = NULL; 
CCamAreaModul *g_pCam8G_RT = NULL; 
CCamAreaModul *g_pCam8G_RB = NULL; 
CCamAreaModul *g_pCam8G_LB = NULL; 

//CCamAreaModul *g_pReview10x = NULL; 
#endif

#ifndef SIM_MODE
#define PPA_X10_PIXEL2MM_X		0.00034415	// 1 mm = 2905.7 pixel
#define PPA_X10_PIXEL2MM_Y		0.00034458	// 1 mm = 2902.1 pixel

#define FOCUS_MAX_POSITION_VARIATION   M_DEFAULT
#define FOCUS_MODE                     M_SMART_SCAN
#define FOCUS_MODE2                    M_SCAN_ALL 
#define FOCUS_MODE3                    M_SCAN_ALL 
#define FOCUS_SENSITIVITY              3
#define FOCUS_MAX_NB_POSITIONS         40 //200
#define FOCUS_MAX_NB_POSITIONS3         500 
#define FOCUS_MIN_POSITION             0
#define FOCUS_MAX_POSITION             (FOCUS_MAX_NB_POSITIONS - 1)
#define FOCUS_MAX_POSITION3             (FOCUS_MAX_NB_POSITIONS3 - 1) 
#define FOCUS_START_POSITION           25 //100
#define FOCUS_START_POSITION2          50
#define FOCUS_START_POSITION3         200  

#define FOCUS_POS_RANGE					1.0
#define FOCUS_MAX_STEP_VALUE			0.01
#define FOCUS_MIN_STEP_VALUE			0.001
#define FOCUS_MAX_FOCUS_VALUE			10000000
#define FOCUS_MIN_FOCUS_VALUE			10000
#define FOCUS_TOLERANCE_VALUE			10000
#define FOCUS_DESCENT_COUNT				10

CCamAreaModul::CCamAreaModul(int nCam, MIL_ID sys, MIL_ID Dig, int Motor)
{
	m_nCam = nCam;
	m_nSys = sys;
	m_nDig = Dig;
	m_AxisCCD = Motor;
}


CCamAreaModul::~CCamAreaModul()
{
}

BEGIN_MESSAGE_MAP(CCamAreaModul, CWnd)
	//{{AFX_MSG_MAP(CImageFullWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CImageFullWnd message handlers
void CCamAreaModul::SetParentPoint(CWnd *pParamWnd)
{
	m_pParentWnd = (CWnd *)pParamWnd;
}

int CCamAreaModul::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;


	MilFocusImage = NULL;
	MilGrabMImage = NULL;
	MilInspImage = NULL;

	//m_MilImageAutofocus = NULL;
#if 1
	MbufAlloc2d(m_nSys, CAM_X_SIZE, CAM_Y_SIZE, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_GRAB, &MilGrabMImage);
	MbufAlloc2d(m_nSys, CAM_X_SIZE, CAM_Y_SIZE, 8 + M_UNSIGNED, M_IMAGE + M_PROC, &MilFocusImage);
	MbufAlloc2d(m_nSys, CAM_X_SIZE, CAM_Y_SIZE, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_GRAB, &MilInspImage);

	//MbufAlloc2d(m_nSys, CAM_X_SIZE, CAM_Y_SIZE, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_GRAB, &m_MilImageAutofocus);
	//MbufClear(m_MilImageAutofocus, 0);
#endif

	return 0;
}

void CCamAreaModul::initDisplay()
{


}




void CCamAreaModul::OnDestroy()
{
	MbufFree(MilFocusImage);
	MbufFree(MilGrabMImage);
	MbufFree(MilInspImage);
	//MbufFree(m_MilImageAutofocus);

	CWnd::OnDestroy();
}

void CCamAreaModul::CopyImage(int nCam, MIL_ID milSrc)
{


}

void CCamAreaModul::SetFindImageDraw(int nCam, int fX, int fY)
{

}






void CCamAreaModul::OnPaint()
{
	CPaintDC dc(this);


}

void CCamAreaModul::OnMouseMove(UINT nFlags, CPoint point)
{
	
	CWnd::OnMouseMove(nFlags, point);
}



void CCamAreaModul::OnLButtonDown(UINT nFlags, CPoint point)
{


	CWnd::OnLButtonDown(nFlags, point);
}


void CCamAreaModul::OnRButtonDown(UINT nFlags, CPoint point)
{


	CWnd::OnRButtonDown(nFlags, point);
}



void CCamAreaModul::OnLButtonUp(UINT nFlags, CPoint point)
{

	
	CWnd::OnLButtonUp(nFlags, point);
}



void CCamAreaModul::OnTimer(UINT_PTR nIDEvent)
{

	CWnd::OnTimer(nIDEvent);
}

void CCamAreaModul::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDblClk(nFlags, point);
}




BOOL CCamAreaModul::PreTranslateMessage(MSG* pMsg)
{




	return CWnd::PreTranslateMessage(pMsg);
}



BOOL CCamAreaModul::OnEraseBkgnd(CDC* pDC)
{
	

	return TRUE;
	//	return CWnd::OnEraseBkgnd(pDC);
}


void CCamAreaModul::OnMenu()
{
	
}


void CCamAreaModul::OnMenuStop()
{
	
}


void CCamAreaModul::OnMenuSave()
{
	
}


void CCamAreaModul::OnMenuTestInsp()
{

}


void CCamAreaModul::OnMenuOpen()
{

}

#if 0
#pragma region ////20201009 Add. New AutoFocus
int CCamAreaModul::GrabQuickOnce(int nDeviceNo, int nCameraNo)
{
#if 0
	if (!m_bOpen) return -1;

#ifdef _MIL_TEST_MODE_
#else
	MdigGrab(m_MilDigitizer[nDeviceNo][nCameraNo], m_MilImage[nDeviceNo][nCameraNo]);
#endif
#endif
	return 0;
}

int CCamAreaModul::GrabOnce(int nDeviceNo, int nCameraNo)
{
#if 0
	if (!m_bOpen) return -1;
#ifdef _MIL_TEST_MODE_
	int nWndNum = 0;
	if (!m_hWnd[nWndNum])  return -1;
	MdispSelectWindow(m_MilDisplay[nDeviceNo][nCameraNo], m_MilImage[nDeviceNo][nCameraNo], m_hWnd[nWndNum]);
	//MdigGrab(m_MilDigitizer[nDeviceNo][nCameraNo], m_MilImage[nDeviceNo][nCameraNo]);
#else
	int nWndNum = nDeviceNo * 2 + nCameraNo;
	if (!m_hWnd[nWndNum])  return -1;
	MdispSelectWindow(m_MilDisplay[nDeviceNo][nCameraNo], m_MilImage[nDeviceNo][nCameraNo], m_hWnd[nWndNum]);
	MdigGrab(m_MilDigitizer[nDeviceNo][nCameraNo], m_MilImage[nDeviceNo][nCameraNo]);

	// 20170914 by sbs
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	//if (!pDlg->m_CameraSetting.m_bCameraFillDisplay)
	if (0)
	{
		MdispControlInt64(m_MilDisplay[0][0], M_FILL_DISPLAY, M_DISABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
		MdispControlInt64(m_MilDisplay[0][1], M_FILL_DISPLAY, M_DISABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
		MdispControlInt64(m_MilDisplay[1][0], M_FILL_DISPLAY, M_DISABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
#ifdef CMM_OBSOLETE	
		MdispControlInt64(m_MilDisplay[1][1], M_FILL_DISPLAY, M_DISABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
		MdispControlInt64(m_MilDisplay[2][0], M_FILL_DISPLAY, M_DISABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
#endif
	}
	else
	{
		MdispControlInt64(m_MilDisplay[0][0], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
		MdispControlInt64(m_MilDisplay[0][1], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
		MdispControlInt64(m_MilDisplay[1][0], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
#ifdef CMM_OBSOLETE
		MdispControlInt64(m_MilDisplay[1][1], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
		MdispControlInt64(m_MilDisplay[2][0], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
#endif
	}

	// sglee: i think it should be changed for the purpose of the camera.
	if (nWndNum == 0)
		MdispInquire(m_MilDisplay[0][0], M_OVERLAY_ID, &m_MilOverlay_Left);		// 20170730 by sbs
	else if (nWndNum == 1)
		MdispInquire(m_MilDisplay[0][1], M_OVERLAY_ID, &m_MilOverlay_Right);		// 20170730 by sbs
	else
	{
		MdispInquire(m_MilDisplay[nDeviceNo][nCameraNo], M_OVERLAY_ID, &m_MilOverlayImage);		// 20170730 by sbs
		MbufGet(m_MilImage[nDeviceNo][nCameraNo], m_pByteImageBuffer_PPA);
	}

#endif
#endif
	return 0;
}
int CCamAreaModul::GrabStop(int nDeviceNo, int nCameraNo)
{
	//if (!m_bOpen) return -1;
#ifdef _MIL_TEST_MODE_
#else
	MdigHalt(Devs::MilDigReview10X);
#endif
	return 0;
}
int CCamAreaModul::GrabContinuous(int nDeviceNo, int nCameraNo)
{
	//if (!m_bOpen) return -1;
#ifdef _MIL_TEST_MODE_
	int nWndNum = 0;
	if (!m_hWnd[nWndNum])  return -1;
	MdispSelectWindow(m_MilDisplay[nDeviceNo][nCameraNo], m_MilImage[nDeviceNo][nCameraNo], m_hWnd[nWndNum]);
#else
	//int nWndNum = nDeviceNo * 2 + nCameraNo;
	//if (!m_hWnd[nWndNum])  return -1;
	//MdispAlloc(m_MilSystem[nDeviceNo], M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_WINDOWED, &m_MilDisplay[nDeviceNo][nCameraNo]);
	//MdispControlInt64(m_MilDisplay[nDeviceNo][nCameraNo], M_FILL_DISPLAY, M_ENABLE);	// 출력 화면 크기에 맞춤

	//MdispSelectWindow(m_MilDisplay[nDeviceNo][nCameraNo], m_MilImage[nDeviceNo][nCameraNo], m_hWnd[nWndNum]);
	MdigGrabContinuous(Devs::MilDigReview10X, MilDisplay);

	// 20170802 by sbs from
	//MdispControlInt64(m_MilDisplay[0][0], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
	//MdispControlInt64(m_MilDisplay[0][1], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
	//MdispControlInt64(m_MilDisplay[1][0], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
#ifdef CMM_OBSOLETE	
	MdispControlInt64(m_MilDisplay[1][1], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
	MdispControlInt64(m_MilDisplay[2][0], M_FILL_DISPLAY, M_ENABLE);	// 1:1 화면 표시 M_DISABLE, 화면에 맞게 채움 M_ENABLE
#endif
	// 20170802 by sbs to
#endif
	return 0;
}
#pragma endregion
#endif
#endif //SIM_MODE