#pragma once

#include <thread>


#define __IP_LENGTH		20

enum _E_CAMERA_LIST
{
	E_CAMERA_INVALID = -1,

	E_CAMERA_PYLON,
	E_CAMERA_USB,
	
	E_CAMERA_MAX,
};

extern LPCTSTR g_szCameraList_Element[];

struct _ST_CAMERA_CFG
{
	_E_CAMERA_LIST		eCamareName;
	
	//int					nFrameRate;
	int					nCameraIndex;
	
	TCHAR				szIpAddr[__IP_LENGTH];	// GigE Camera IP Address

	TCHAR				szVid[__IP_LENGTH];		// USB Camera VID
	TCHAR				szPid[__IP_LENGTH];		// USB Camera PID
	

	_ST_CAMERA_CFG()
	{
		ZeroMemory(this, sizeof(*this));
	}
};


struct _ST_IMAGE_INFO_BASLER
{
	int		nImgW;
	int		nImgH;
	int		nCh;

	double	dRatio_x;
	double	dRatio_y;

	BYTE*	czImg;

	_ST_IMAGE_INFO_BASLER()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

class CCameraBase
{
public:
	CCameraBase();
	~CCameraBase();

protected:
	_ST_IMAGE_INFO_BASLER		m_stImageInfo;
	//_ST_CAMERA_CFG		m_stCameraCfg;

	static bool			m_bInitPylon;
	static bool			m_bOpened;
	static int			m_nCameraCnt;
protected:


public:
	// 순수 가상 함수
	virtual BOOL			Open(_ST_CAMERA_CFG stCameraCfg)       = 0;
	virtual BOOL			Close()                                = 0;
	virtual BOOL			doDeinit()                             = 0;


	virtual BOOL			GrabOneShot()                          = 0;
	virtual BOOL			GrabContinue()                         = 0;
	virtual void			GrabStop()                             = 0;
	virtual BOOL			IsOpened()							= 0;
	virtual INT				GetCennetedCnt()					= 0;
	virtual void		SetGrabOk()								= 0;
	virtual void		ResetGrabOk() = 0;
	virtual BOOL			GetGrabOk() = 0;

	virtual _ST_IMAGE_INFO_BASLER	getImageInfo()                         = 0;
	virtual void			setImageInfo(_ST_IMAGE_INFO_BASLER imageInfo) = 0;

	// 
	void			TerminatePylon();
};

