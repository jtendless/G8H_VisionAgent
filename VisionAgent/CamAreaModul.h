

#pragma once

// ImageZoomWnd.h : header file
//

#define MAX_DATA_NAM		10000

#ifndef MIL_NOT_USE
#include "mil.h"
#endif



#ifndef MIL_NOT_USE



typedef struct
{
	INT nIteration;
	INT nFocusValue;
	DOUBLE dPos;

} DigFocusTable;

typedef struct
{
	MIL_ID      SourceImage;
	MIL_ID      FocusImage;
	MIL_ID      GrabImage;
	MIL_ID      Display;
	long        Iteration;
	double     dStartPos;
	BOOL       bStop;
	int			AxisID;
	int         nDigNum;
}  DigHookUserData;

/////////////////////////////////////////////////////////////////////////////
// CCamAreaModul window
class CCamAreaModul : public CWnd
{
private:
	int		m_nIndex;
	double	m_dZoomX, m_dZoomY;
	float   m_fTapZoomX, m_fTapZoomY;
	CWnd	*m_pParentWnd;
	CStatic *StaticView;
public:
	MIL_ID	MilImage, MilDisplay;
	MIL_ID MilGrabMImage;
	MIL_ID MilFocusImage;
	MIL_ID MilInspImage;
	MIL_ID MilZOOMImage;
	MIL_ID	MilOverlayImage;
	long	TransparentColor;
	int m_AxisCCD;
	int m_nCnt;


	DigHookUserData UserData;

	CCamAreaModul(int nCam, MIL_ID sys, MIL_ID Dig, int Motor);
	virtual ~CCamAreaModul();

	int m_nCam;
	MIL_ID m_nSys;
	MIL_ID m_nDig;
	void SetParentPoint(CWnd *m_parm_point);
	void CopyImage(int nIndex, MIL_ID milSrc);
	void SetFindImageDraw(int nCam, int fX, int fY);

	void initDisplay();

#if 0
#pragma region ////20201009 Add. New AutoFocus
	int  m_nAFGrab;
	CEvent	m_HookEvent;
	MIL_ID  m_MilImageAutofocus;
	int GrabQuickOnce(int nDeviceNo, int nCameraNo);
	int GrabOnce(int nDeviceNo, int nCameraNo);
	int GrabStop(int nDeviceNo, int nCameraNo);
	int GrabContinuous(int nDeviceNo, int nCameraNo);
#pragma endregion
#endif

protected:
	//{{AFX_MSG(CCamAreaModul)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMenu();
	afx_msg void OnMenuStop();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuTestInsp();
	afx_msg void OnMenuOpen();
};

#ifndef MIL_NOT_USE
extern CCamAreaModul *g_pCam6G_LT;
extern CCamAreaModul *g_pCam6G_RT;
extern CCamAreaModul *g_pCam6G_RB;
extern CCamAreaModul *g_pCam6G_LB;

extern CCamAreaModul *g_pCam8G_LT;
extern CCamAreaModul *g_pCam8G_RT;
extern CCamAreaModul *g_pCam8G_RB;
extern CCamAreaModul *g_pCam8G_LB;

//extern CCamAreaModul *g_pReview10x;
#endif
#endif // !MIL_NOT_USE


