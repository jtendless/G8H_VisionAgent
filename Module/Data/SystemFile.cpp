#include "stdafx.h"
#include "SystemFile.h"
#include "SystemData.h"

CSystemFile::CSystemFile()
{
    setClassName("CSystemFile");
	
	Register("m_Option", &m_Option);
	Register("m_Camera", &m_Machine);

}

CSystemFile::~CSystemFile()
{

}

//Option ----------------------------------------------------------------------------------------
CSystemFileOption::CSystemFileOption()
{
	setClassName("CSystemFileOption");

	Register("m_bRecipeCheckPass", &m_bRecipeCheckPass);
	Register("m_bImageAutoSave", &m_bImageAutoSave);
	Register("m_bImageAutoDel", &m_bImageAutoDel);

	Register("m_nUserMode", &m_nUserMode);
	Register("m_nWorkMode", &m_nWorkMode);
	Register("nImageDelPeriod", &nImageDelPeriod);

	Register("m_strActiveModelName", &m_strActiveModelName);
	
}

void CSystemFileOption::CopyFrom(CSystemDataOption &data)
{

	m_strActiveModelName = CopyToXstring(data.m_strActiveModelName);
	m_bRecipeCheckPass = data.m_bRecipeCheckPass;
	m_bImageAutoSave = data.m_bImageAutoSave;
	m_bImageAutoDel = data.m_bImageAutoDel;

	m_nUserMode = data.m_nUserMode;
	m_nWorkMode = data.m_nWorkMode;

	nImageDelPeriod = data.nImageDelPeriod;

}

//Camera -------------------------------------------------------------------------------------------------------
CSystemFileMachine::CSystemFileMachine()
{
	setClassName("CSystemFileMachine");
	
	Register("dGlassCameraPosOffsetX",	&dGlassCameraPosOffsetX);
	Register("dGlassCameraPosOffsetY1",	&dGlassCameraPosOffsetY1);
	Register("dGlassCameraPosOffsetY2",	&dGlassCameraPosOffsetY2);

	Register("dFilmCameraPosOffsetX", &dFilmCameraPosOffsetX);
	Register("dFilmCameraPosOffsetY1", &dFilmCameraPosOffsetY1);
	Register("dFilmCameraPosOffsetY2", &dFilmCameraPosOffsetY2);

	Register("nHoleMarkAxisLightTop", &nHoleMarkAxisLightTop);
	Register("nHoleMarkAxisLightBottom", &nHoleMarkAxisLightBottom);
	Register("nHoleMarkRingLightTop", &nHoleMarkRingLightTop);
	Register("nHoleMarkRingLightBottom", &nHoleMarkRingLightBottom);
	Register("nHoleMarkBinTop", &nHoleMarkBinTop);
	Register("nHoleMarkBinBottom", &nHoleMarkBinBottom);

	Register("m_strIpNumGlassTop", &m_strIpNumGlassTop);
	Register("m_strIpNumGlassBtm", &m_strIpNumGlassBtm);
	Register("m_strIpNumFilmTop", &m_strIpNumFilmTop);
	Register("m_strIpNumFilmBtm", &m_strIpNumFilmBtm);
}

void CSystemFileMachine::CopyFrom(CSystemDataMachine & data)
{
	dGlassCameraPosOffsetX			=	data.dGlassCameraPosOffsetX;
	dGlassCameraPosOffsetY1		= data.dGlassCameraPosOffsetY1;
	dGlassCameraPosOffsetY2		= data.dGlassCameraPosOffsetY2;

	dFilmCameraPosOffsetX = data.dFilmCameraPosOffsetX;
	dFilmCameraPosOffsetY1 = data.dFilmCameraPosOffsetY1;
	dFilmCameraPosOffsetY2 = data.dFilmCameraPosOffsetY2;

	nHoleMarkAxisLightTop = data.nHoleMarkAxisLightTop;
	nHoleMarkAxisLightBottom = data.nHoleMarkAxisLightBottom;

	nHoleMarkRingLightTop = data.nHoleMarkRingLightTop;
	nHoleMarkRingLightBottom = data.nHoleMarkRingLightBottom;

	nHoleMarkBinTop = data.nHoleMarkBinTop;
	nHoleMarkBinBottom = data.nHoleMarkBinBottom;

	m_strIpNumGlassTop = CopyToXstring(data.m_strIpNumGlassTop);
	m_strIpNumGlassBtm = CopyToXstring(data.m_strIpNumGlassBtm);
	m_strIpNumFilmTop = CopyToXstring(data.m_strIpNumFilmTop);
	m_strIpNumFilmBtm = CopyToXstring(data.m_strIpNumFilmBtm);
}
