#pragma once
#include "XMLSerialization.h"
using namespace xmls;

class CSystemDataOption;
class CSystemDataMachine;

class CSystemFileOption : public Serializable
{
public:
	xBool m_bRecipeCheckPass;
	xBool m_bImageAutoSave;
	xBool m_bImageAutoDel;


	xInt	m_nUserMode;
	xInt	m_nWorkMode;

	xInt	nImageDelPeriod;

	xString	m_strActiveModelName = _T("..");


	
public:
	CSystemFileOption();
	
	void CopyFrom(CSystemDataOption &data);
	
};

class CSystemFileMachine : public Serializable
{
public:
	xString	m_strIpNumGlassTop = _T("..");
	xString	m_strIpNumGlassBtm = _T("..");
	xString	m_strIpNumFilmTop = _T("..");
	xString	m_strIpNumFilmBtm = _T("..");


	xDouble dGlassCameraPosOffsetX;
	xDouble dGlassCameraPosOffsetY1;
	xDouble dGlassCameraPosOffsetY2;

	xDouble dFilmCameraPosOffsetX;
	xDouble dFilmCameraPosOffsetY1;
	xDouble dFilmCameraPosOffsetY2;

	xInt nHoleMarkAxisLightTop;
	xInt nHoleMarkAxisLightBottom;
	xInt nHoleMarkRingLightTop;
	xInt nHoleMarkRingLightBottom;
	xInt nHoleMarkBinTop;
	xInt nHoleMarkBinBottom;


public:
	CSystemFileMachine();

	void CopyFrom(CSystemDataMachine &data);
};


class CSystemFile : public Serializable
{
public:
	CSystemFileOption		m_Option;
	CSystemFileMachine		m_Machine;

public:
	CSystemFile();
	~CSystemFile();

	
};

