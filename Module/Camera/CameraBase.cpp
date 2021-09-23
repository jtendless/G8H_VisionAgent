#include "stdafx.h"
#include "CameraBase.h"

LPCTSTR g_szCameraList_Element[] = 
{
	_T("PYLON"),
	_T("USB"),
	_T("MAX"),
};

bool CCameraBase::m_bInitPylon = false;
bool CCameraBase::m_bOpened = false;

int   CCameraBase::m_nCameraCnt = 0;

CCameraBase::CCameraBase()
{
}


CCameraBase::~CCameraBase()
{
}

BOOL CCameraBase::Open(_ST_CAMERA_CFG stCameraCfg)
{
	return TRUE;
}
BOOL CCameraBase::Close()
{
	return TRUE;
}

void CCameraBase::TerminatePylon()
{
	if (CCameraBase::m_bInitPylon == true)
	{
		CCameraBase::m_bInitPylon = false;
		PylonTerminate();
	}
}
