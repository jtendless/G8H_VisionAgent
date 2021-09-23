#include "stdafx.h"
#include "Camera_Pylon.h"

#include "PylonStringHelpers.h"

#define __REAL_OPEN

CCamera_Pylon::CCamera_Pylon()
{
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ResetEvent(m_hEvent);
}


CCamera_Pylon::~CCamera_Pylon()
{

}


bool CCamera_Pylon::doInit_Pylon()
{
	try
	{
		if (CCameraBase::m_bInitPylon == false)
		{
			PylonInitialize();
			CCameraBase::m_bInitPylon = true;
			CCameraBase::m_bOpened = true;
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
}



bool CCamera_Pylon::doDeinit_Pylon()
{
	try
	{
		if (CCameraBase::m_bInitPylon == true)
		{
			CCameraBase::m_bInitPylon = false;
			PylonTerminate();
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
}


Pylon::String_t CCamera_Pylon::GetString_t(LPCTSTR pszString)
{
	if (pszString == NULL)		return Pylon::String_t();
	CT2CW pszWString(pszString);
	CW2Utf8 pszUtf8String(pszWString);
	return Pylon::String_t(pszUtf8String);
}




//////////////////////////////////////////////////////
BOOL CCamera_Pylon::GrabOneShot(void)
{
	if (!m_bOpened)				return false;
	if (m_pCamera == nullptr)	return false;

	BOOL	bResult = TRUE;

	try
	{
		//m_pCamera->StartGrabbing(1, GrabStrategy_OneByOne, GrabLoop_ProvidedByUser /*GrabLoop_ProvidedByInstantCamera*/);			// grab one...   한장 그랩

		if (IsGrabbing() == true)		return TRUE;

		m_pCamera->StartGrabbing(1, GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera /*GrabLoop_ProvidedByInstantCamera*/);			// grab one...   한장 그랩

		DWORD ret = WaitForSingleObject(m_hEvent, 10000);
		ResetEvent(m_hEvent);

		switch (ret)
		{
		case WAIT_FAILED:		bResult = FALSE;	break;
		case WAIT_ABANDONED:	bResult = FALSE;	break;
		case WAIT_TIMEOUT:		bResult = FALSE;	break;
		default:				bResult = TRUE;
		}

	}
	catch (GenICam::GenericException ex)
	{
		TRACE("[ERROR] CGigECamera::Grab\n");
		return  FALSE;
	}
	catch (...)//catch (CException* e)
	{
		TRACE("[ERROR] CGigECamera::StartGrabbing\n");
		return  FALSE;
	}

	return bResult;
}


//////////////////////////////////////////////////////
BOOL CCamera_Pylon::GrabContinue(void)
{
	if (!m_bOpened)				return false;
	if (m_pCamera == nullptr)	return false;
	
	try
	{
		m_pCamera->StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);			// continue grab
	}
	catch (GenICam::GenericException ex)
	{
		TRACE("[ERROR] CGigECamera::Grab\n");
		return false;
	}
	catch (...)//catch (CException* e)
	{
		TRACE("[ERROR] CGigECamera::StartGrabbing\n");
		return false;

	}

	return TRUE;
}

//////////////////////////////////////////////////////
void CCamera_Pylon::GrabStop()
{
	if (!m_bOpened)							return;
	if (m_pCamera == nullptr)			return;

	try
	{
		if (IsGrabbing())	m_pCamera->StopGrabbing();
	}
	catch (...)
	{
	}

	Sleep(50);
}

//////////////////////////////////////////////////////
bool CCamera_Pylon::IsGrabbing(void)
{
	if (!m_bOpened)				return false;
	if (m_pCamera == nullptr)	return false;

	bool	bReturn = false;

	try
	{
		bReturn = m_pCamera->IsGrabbing();
	}
	catch (...)
	{
	}

	return bReturn;
}


//////////////////////////////////////////////////////
void CCamera_Pylon::OnImageGrabbed(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult)
{
	try
	{
		//memcpy(&m_GrabResultPtr, &ptrGrabResult, sizeof(CGrabResultPtr));


		if (ptrGrabResult->GrabSucceeded() && !GetGrabOk())
		{
			const uint8_t *pImageBuffer = (uint8_t *)ptrGrabResult->GetBuffer();

			if (m_stImageInfo.czImg == NULL)	
				m_stImageInfo.czImg = new unsigned char[ptrGrabResult->GetWidth() * ptrGrabResult->GetHeight()];

			m_stImageInfo.nImgW = ptrGrabResult->GetWidth();
			m_stImageInfo.nImgH = ptrGrabResult->GetHeight();

			//memset(m_stImageInfo.czImg, 0x00, sizeof(unsigned char) * m_stImageInfo.nImgW * m_stImageInfo.nImgH);
			memcpy(m_stImageInfo.czImg, (BYTE*) pImageBuffer, sizeof(BYTE) * m_stImageInfo.nImgW * m_stImageInfo.nImgH);
			
			SetEvent(m_hEvent);

			SetGrabOk();

			// Save grab image to a .bmp file
			//CImagePersistence::Save(ImageFileFormat_Bmp, "C:\\temp\\GrabbedImage.bmp", ptrGrabResult);
		}
	}
	catch (.../*GenICam::GenericException &e*/)
	{
		TRACE("[ERROR] FAIL TO GRAB\n");
		
	}
}


//////////////////////////////////////////////////////
//void CCamera_Pylon::OnCameraEvent(CBaslerGigEInstantCamera& camera, intptr_t userProvidedId, GenApi::INode* pNode)
//{
//	CString str;
//	str.Format(_T("%d"), camera.GetCameraContext());
//
//	switch (userProvidedId)
//	{
//	case eExposureEndEvent:
//		break;
//
//	default:
//		break;
//	}
//}

//////////////////////////////////////////////////////
void CCamera_Pylon::OnOpened(CInstantCamera& camera)
{
	using namespace GenApi;

	try
	{
		// Get the camera control object.
		INodeMap &Control = camera.GetNodeMap();

		// Get the trigger selector node.
		CEnumerationPtr triggerSelector(Control.GetNode("TriggerSelector"));
		// Get the trigger mode node.
		CEnumerationPtr triggerMode(Control.GetNode("TriggerMode"));

		// Check the available camera trigger mode(s) to select the appropriate one: acquisition start trigger mode 
		// (used by previous cameras, i.e. for cameras supporting only the legacy image acquisition control mode;
		// do not confuse with acquisition start command) or frame start trigger mode
		// (used by newer cameras, i.e.for cameras using the standard image acquisition control mode;
		// equivalent to the acquisition start trigger mode in the leagcy image acquisition control mode).
		bool frameStartAvailable = false;
		bool acquisitionStartAvailable = false;
		{
			// Frame start trigger mode available?
			GenApi::IEnumEntry* frameStart = triggerSelector->GetEntryByName("FrameStart");
			frameStartAvailable = frameStart && IsAvailable(frameStart);

			// Acquisition start trigger mode available?
			GenApi::IEnumEntry* acquisitionStart = triggerSelector->GetEntryByName("AcquisitionStart");
			acquisitionStartAvailable = acquisitionStart && IsAvailable(acquisitionStart);
		}

		// Preselect the trigger mode for image acquisition.
		const char* triggerSelectorValue = "FrameStart";

		// Check to see if the camera implements the acquisition start trigger mode only.
		if (acquisitionStartAvailable && !frameStartAvailable)
		{
			// Camera uses the acquisition start trigger as the only trigger mode.
			triggerSelector->FromString("AcquisitionStart");
			triggerMode->FromString("On");
			triggerSelectorValue = "AcquisitionStart";
		}
		else
		{
			// Camera may have the acquisition start trigger mode and the frame start trigger mode implemented.
			// In this case, the acquisition trigger mode must be switched off.
			if (acquisitionStartAvailable)
			{
				triggerSelector->FromString("AcquisitionStart");
				triggerMode->FromString("Off");
			}
			// To trigger each single frame by software or external hardware trigger: Enable the frame start trigger mode.
			assert(frameStartAvailable); //Frame start trigger mode must be available here.
			triggerSelector->FromString("FrameStart");
			//triggerMode->FromString("On");
			triggerMode->FromString("Off");
		}

		// Note: The trigger selector must be set to the appropriate trigger mode 
		// before setting the trigger source or issuing software triggers.
		// Frame start trigger mode for newer cameras (i.e. for cameras supporting the standard image acquisition control mode).
		triggerSelector->FromString(triggerSelectorValue);

		// The trigger source must be set to 'Software'.
		CEnumerationPtr(Control.GetNode("TriggerSource"))->FromString("Software");

		//// Alternative hardware trigger configuration:
		//// This configuration can be copied and modified to create a hardware trigger configuration.
		//// Remove setting the 'TriggerSource' to 'Software' (see above) and 
		//// use the commented lines as a starting point.
		//// The camera user's manual contains more information about available configurations.
		//// The pylon Viewer tool can be used to test the selected settings first.

		//// The trigger source must be set to the trigger input, e.g. 'Line1'.
		//CEnumerationPtr(Control.GetNode("TriggerSource"))->FromString("Line1");

		////The trigger activation must be set to e.g. 'RisingEdge'.
		//CEnumerationPtr(Control.GetNode("TriggerActivation"))->FromString("RisingEdge");

		// Enable the continuous acquisition mode.
		CEnumerationPtr(Control.GetNode("AcquisitionMode"))->FromString("Continuous");
	}
	catch (GenICam::GenericException& e)
	{
		throw RUNTIME_EXCEPTION("Could not apply configuration. GenICam::GenericException caught in OnOpened method msg=%hs", e.what());
	}
	catch (std::exception& e)
	{
		throw RUNTIME_EXCEPTION("Could not apply configuration. std::exception caught in OnOpened method msg=%hs", e.what());
	}
	catch (...)
	{
		throw RUNTIME_EXCEPTION("Could not apply configuration. Unknown exception caught in OnOpened method.");
	}
}

//////////////////////////////////////////////////////
void CCamera_Pylon::OnCameraDeviceRemoved(CInstantCamera& camera)
{
	TRACE("[ERROR] CGigECamera::OnCameraDeviceRemoved - Camera Disconnected.\n");
}





///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
BOOL CCamera_Pylon::Open(_ST_CAMERA_CFG stCameraCfg)
{
	BOOL	bResult = FALSE;

	doInit_Pylon();

	/********************************************************************************/
	/* 주어진 IP Address  로 객체를 생성한다.                                       */
	CTlFactory& tlFactory = CTlFactory::GetInstance();
	CBaslerGigEDeviceInfo di;

	Pylon::String_t	string = GetString_t(stCameraCfg.szIpAddr);
	di.SetIpAddress(GetString_t(stCameraCfg.szIpAddr));
	/* Set Device Info                                                              */
	/********************************************************************************/

	try
	{ 
		//memcpy(&m_stCameraCfg, &stCameraCfg, sizeof(_ST_CAMERA_CFG));
		IPylonDevice* pIPylonDevice = tlFactory.CreateDevice(di);
		m_pCamera = new Camera_t(pIPylonDevice);

		m_pCamera->SetCameraContext(m_nContext);
		m_pCamera->RegisterImageEventHandler(this, RegistrationMode_Append, Cleanup_None);
		m_pCamera->RegisterConfiguration(this, RegistrationMode_ReplaceAll, Cleanup_None);

		m_pCamera->Open();

#if INIT_TRIG
		m_pCamera->TriggerMode.SetValue(TriggerMode_On);
		m_pCamera->TriggerSource.SetValue(TriggerSource_Line1);
		m_pCamera->StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
#endif
		
		m_bOpened = true;
		m_nCameraCnt++;

		bResult   = TRUE;

		//GrabContinue();
		//GrabOneShot();
		
	}
	catch (...)
	{
		TRACE("================= FAIL TO OPEN CAMERA %d================/n", stCameraCfg.nCameraIndex);
		m_bOpened = false;
		bResult   = FALSE;
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
BOOL CCamera_Pylon::Close()
{	
	//if (m_bOpened == false)		return TRUE;
	
	try
	{
		if (m_pCamera != nullptr)
		{
			if (m_bOpened == true)
			{
				GrabStop();
				Sleep(100);

				m_pCamera->DeregisterImageEventHandler(this);
				m_pCamera->DeregisterConfiguration(this);
			}
					
			//if (CCameraBase::m_bOpened == true)
			{
				CCameraBase::m_bOpened = false;
				if (m_pCamera)	m_pCamera->Close();
			}
			

			delete m_pCamera;
			m_pCamera = nullptr;
		}


	}
	catch (...)
	{
		TRACE("[ERROR] FAIL TO CLOSE PYLON\n");
	}
	
	if (m_stImageInfo.czImg)
	{
		delete[] m_stImageInfo.czImg;
		m_stImageInfo.czImg = NULL;
	}

	m_bOpened = false;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
BOOL CCamera_Pylon::doDeinit()
{
	//doDeinit_Pylon();

	if (m_pCamera)
	{
		Close();

		//if (--m_nCameraCnt == 0)
			//doDeinit_Pylon();
	}

	return TRUE;
}
