#pragma once
#include "CameraBase.h"

#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <pylon/gige/PylonGigEIncludes.h>
#include <pylon/GrabResultPtr.h>
#include <pylon/ImageEventHandler.h>
#include <pylon/SoftwareTriggerConfiguration.h>
#include <pylon/gige/GigETransportLayer.h>
#include <pylon/ConfigurationEventHandler.h>
#include <pylon/gige/_BaslerGigECameraParams.h>

#ifdef PYLON_WINDOW_BUILG
#include <pylon\PylonGUI.h>
#endif

using namespace Pylon;
using namespace GenApi;
using namespace Basler_GigECamera;

typedef Pylon::CBaslerGigEInstantCamera Camera_t;

enum eMODE
{
	MODE_SOFTTRIGGER,				// Soft-Trigger mode
	MODE_HARDTRIGGER,				// Hard-Trigger mode
	MODE_CONTINUE					// Free Run mode
};

enum eEvents
{
	eExposureEndEvent = 100,
	eEventOverrunEvent = 200
};

class CCamera_Pylon
	: public CCameraBase, public CImageEventHandler, public CBaslerGigECameraEventHandler, public CConfigurationEventHandler
{
public:
	CCamera_Pylon();
	~CCamera_Pylon();

private:
	bool				m_bOpened = false;
		
	int					m_nMode;
	int					m_nContext;
	int					m_bGrabOk = false;


	CString				m_sIpAddr;
	Pylon::CDeviceInfo	m_pDeviceInfo;
	CGrabResultPtr		m_GrabResultPtr;
	
	Camera_t*		    m_pCamera = nullptr;

	HANDLE				m_hEvent;


private:
	bool				doInit_Pylon();
	bool				doDeinit_Pylon();

	bool				IsGrabbing(void);

	Pylon::String_t		GetString_t(LPCTSTR pszString);

	/********************************************************************************/
	// for Events                                                                   
public:
	virtual void	OnImageGrabbed(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult);

	
	//virtual void	OnCameraEvent(Camera_t& camera, intptr_t userProvidedId, GenApi::INode* pNode);
	virtual void	OnOpened(CInstantCamera& camera);
	virtual void	OnCameraDeviceRemoved(CInstantCamera& camera);
	/********************************************************************************/

public:
	// 순수 가상 함수
	virtual BOOL		Open(_ST_CAMERA_CFG stCameraCfg);
	virtual BOOL		Close();
	virtual BOOL		doDeinit();
	virtual BOOL		GrabOneShot();
	virtual BOOL		GrabContinue();
	virtual void		GrabStop();
	virtual BOOL		IsOpened() { return m_bOpened; };
	virtual INT			GetCennetedCnt() { return m_nCameraCnt; };
	virtual void		SetGrabOk() { m_bGrabOk = true; };
	virtual void		ResetGrabOk() { m_bGrabOk = false; };
	virtual BOOL		GetGrabOk() { return m_bGrabOk; };

	virtual _ST_IMAGE_INFO_BASLER		getImageInfo()		                   { return m_stImageInfo; }
	virtual void			setImageInfo(_ST_IMAGE_INFO_BASLER imageInfo) { memcpy(&m_stImageInfo, &imageInfo, sizeof(imageInfo)); }
};

