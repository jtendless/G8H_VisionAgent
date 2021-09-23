#include "stdafx.h"
#include "ModelFile.h"

CModelFileGlass::CModelFileGlass()
{
	setClassName("CModelFileGlass");

	Register("dAlignTargetX", &dAlignTargetX);
	Register("dAlignTargetY", &dAlignTargetY);
	Register("dAlignTargetT", &dAlignTargetT);

	Register("nAlignAxisLightTop", &nAlignAxisLightTop);
	Register("nAlignAxisLightBottom", &nAlignAxisLightBottom);

	Register("nAlignRingLightTop", &nAlignRingLightTop);
	Register("nAlignRingLightBottom", &nAlignRingLightBottom);

	Register("nAlignBinTop", &nAlignBinTop);
	Register("nAlignBinBottom", &nAlignBinBottom);

	Register("nInspectAxisLightTop", &nInspectAxisLightTop);
	Register("nInspectAxisLightBottom", &nInspectAxisLightBottom);

	Register("nInspectRingLightTop", &nInspectRingLightTop);
	Register("nInspectRingLightBottom", &nInspectRingLightBottom);

	Register("nInspectBinTop", &nInspectBinTop);
	Register("nInspectBinBottom", &nInspectBinBottom);

	Register("dInspectTargetX", &dInspectTargetX);
	Register("dInspectTargetY", &dInspectTargetY);

	Register("strGlassId", &strGlassId);
}

void CModelFileGlass::CopyFrom(CModelDataGlass &data)
{
	dAlignTargetX = data.dAlignTargetX;
	dAlignTargetY = data.dAlignTargetY;
	dAlignTargetT = data.dAlignTargetT;

	nAlignAxisLightTop = data.nAlignAxisLightTop;
	nAlignAxisLightBottom = data.nAlignAxisLightBottom;

	nAlignRingLightTop = data.nAlignRingLightTop;
	nAlignRingLightBottom = data.nAlignRingLightBottom;

	nAlignBinTop = data.nAlignBinTop;
	nAlignBinBottom = data.nAlignBinBottom;

	nInspectAxisLightTop = data.nInspectAxisLightTop;
	nInspectAxisLightBottom = data.nInspectAxisLightBottom;

	nInspectRingLightTop = data.nInspectRingLightTop;
	nInspectRingLightBottom = data.nInspectRingLightBottom;
	
	nInspectBinTop = data.nInspectBinTop;
	nInspectBinBottom = data.nInspectBinBottom;

	dInspectTargetX = data.dInspectTargetX;
	dInspectTargetY = data.dInspectTargetY;

	strGlassId = CopyToXstring(data.strGlassId);
}

//Film ------------------------------------------------------------

CModelFileFilm::CModelFileFilm()
{
	setClassName("CModelFileFilm");
	
	Register("dAlignTargetX", &dAlignTargetX);
	Register("dAlignTargetY", &dAlignTargetY);
	Register("dAlignTargetT", &dAlignTargetT);

	char cTemp[128];
	memset(cTemp, 0, sizeof(cTemp));

	for (int i = 0; i < FILM_MAX_NUM; i++)
	{
		sprintf_s(cTemp, "dAlignOffsetX[%d]", i);
		Register(cTemp, &dAlignOffsetX[i]);

		sprintf_s(cTemp, "dAlignOffsetY[%d]", i);
		Register(cTemp, &dAlignOffsetY[i]);

		sprintf_s(cTemp, "dAlignOffsetT[%d]", i);
		Register(cTemp, &dAlignOffsetT[i]);
	}

	Register("nAlignAxisLightTop", &nAlignAxisLightTop);
	Register("nAlignAxisLightBottom", &nAlignAxisLightBottom);

	Register("nAlignRingLightTop", &nAlignRingLightTop);
	Register("nAlignRingLightBottom", &nAlignRingLightBottom);

	Register("nAlignBinTop", &nAlignBinTop);
	Register("nAlignBinBottom", &nAlignBinBottom);

	Register("nInspectAxisLightTop", &nInspectAxisLightTop);
	Register("nInspectAxisLightBottom", &nInspectAxisLightBottom);

	Register("nInspectRingLightTop", &nInspectRingLightTop);
	Register("nInspectRingLightBottom", &nInspectRingLightBottom);

	Register("nInspectBinTop", &nInspectBinTop);
	Register("nInspectBinBottom", &nInspectBinBottom);

	Register("nRoi1StartX", &nRoi1StartX);
	Register("nRoi1StartY", &nRoi1StartY);
	Register("nRoi1EndX", &nRoi1EndX);
	Register("nRoi1EndY", &nRoi1EndY);

	Register("nRoi2StartX", &nRoi2StartX);
	Register("nRoi2StartY", &nRoi2StartY);
	Register("nRoi2EndX", &nRoi2EndX);
	Register("nRoi2EndY", &nRoi2EndY);

	Register("nRoi3StartX", &nRoi3StartX);
	Register("nRoi3StartY", &nRoi3StartY);
	Register("nRoi3EndX", &nRoi3EndX);
	Register("nRoi3EndY", &nRoi3EndY);

	Register("nRoi4StartX", &nRoi4StartX);
	Register("nRoi4StartY", &nRoi4StartY);
	Register("nRoi4EndX", &nRoi4EndX);
	Register("nRoi4EndY", &nRoi4EndY);

	Register("nRoi5StartX", &nRoi5StartX);
	Register("nRoi5StartY", &nRoi5StartY);
	Register("nRoi5EndX", &nRoi5EndX);
	Register("nRoi5EndY", &nRoi5EndY);

	Register("nRoi6StartX", &nRoi6StartX);
	Register("nRoi6StartY", &nRoi6StartY);
	Register("nRoi6EndX", &nRoi6EndX);
	Register("nRoi6EndY", &nRoi6EndY);

	Register("nRoi7StartX", &nRoi7StartX);
	Register("nRoi7StartY", &nRoi7StartY);
	Register("nRoi7EndX", &nRoi7EndX);
	Register("nRoi7EndY", &nRoi7EndY);

	Register("nRoi8StartX", &nRoi8StartX);
	Register("nRoi8StartY", &nRoi8StartY);
	Register("nRoi8EndX", &nRoi8EndX);
	Register("nRoi8EndY", &nRoi8EndY);

	Register("strGlassId", &strFilmId);
}

void CModelFileFilm::CopyFrom(CModelDataFilm &data)
{
	dAlignTargetX = data.dAlignTargetX;
	dAlignTargetY = data.dAlignTargetY;
	dAlignTargetT = data.dAlignTargetT;

	for (int i = 0; i < FILM_MAX_NUM; i++)
	{
		dAlignOffsetX[i] = data.dAlignOffsetX[i];
		dAlignOffsetY[i] = data.dAlignOffsetY[i];
		dAlignOffsetT[i] = data.dAlignOffsetT[i];
	}

	nAlignAxisLightTop = data.nAlignAxisLightTop;
	nAlignAxisLightBottom = data.nAlignAxisLightBottom;

	nAlignRingLightTop = data.nAlignRingLightTop;
	nAlignRingLightBottom = data.nAlignRingLightBottom;

	nAlignBinTop = data.nAlignBinTop;
	nAlignBinBottom = data.nAlignBinBottom;

	nInspectAxisLightTop = data.nInspectAxisLightTop;
	nInspectAxisLightBottom = data.nInspectAxisLightBottom;

	nInspectRingLightTop = data.nInspectRingLightTop;
	nInspectRingLightBottom = data.nInspectRingLightBottom;

	nInspectBinTop = data.nInspectBinTop;
	nInspectBinBottom = data.nInspectBinBottom;

	nRoi1StartX = data.nRoi1StartX;
	nRoi1StartY = data.nRoi1StartY;
	nRoi1EndX = data.nRoi1EndX;
	nRoi1EndY = data.nRoi1EndY;

	nRoi2StartX =	data.nRoi2StartX;
	nRoi2StartY =	data.nRoi2StartY;
	nRoi2EndX =		data.nRoi2EndX;
	nRoi2EndY =		data.nRoi2EndY;

	nRoi3StartX =	data.nRoi3StartX;
	nRoi3StartY =	data.nRoi3StartY;
	nRoi3EndX =		data.nRoi3EndX;
	nRoi3EndY =		data.nRoi3EndY;

	nRoi4StartX =	data.nRoi4StartX;
	nRoi4StartY =	data.nRoi4StartY;
	nRoi4EndX =		data.nRoi4EndX;
	nRoi4EndY =		data.nRoi4EndY;

	nRoi5StartX = data.nRoi5StartX;
	nRoi5StartY = data.nRoi5StartY;
	nRoi5EndX = data.nRoi5EndX;
	nRoi5EndY = data.nRoi5EndY;

	nRoi6StartX = data.nRoi6StartX;
	nRoi6StartY = data.nRoi6StartY;
	nRoi6EndX = data.nRoi6EndX;
	nRoi6EndY = data.nRoi6EndY;

	nRoi7StartX = data.nRoi7StartX;
	nRoi7StartY = data.nRoi7StartY;
	nRoi7EndX = data.nRoi7EndX;
	nRoi7EndY = data.nRoi7EndY;

	nRoi8StartX = data.nRoi8StartX;
	nRoi8StartY = data.nRoi8StartY;
	nRoi8EndX = data.nRoi8EndX;
	nRoi8EndY = data.nRoi8EndY;

	strFilmId = CopyToXstring(data.strFilmId);
}

//----------------------------------------------------------------------------------
CModelFile::CModelFile()
{
	//Awking ModelFile Register
	setClassName("CModelFile");
	setVersion("1.0");

	Register("Glass", &Glass);
	Register("Film", &Film);

}

CModelFile::~CModelFile()
{

}

