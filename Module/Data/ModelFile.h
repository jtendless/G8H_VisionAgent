#pragma once
#include "../Module/Data/XMLSerialization.h"

using namespace xmls;

class CModelDataGlass;
class CModelDataFilm;


class CModelFileGlass : public Serializable
{
public:
	CModelFileGlass();
	   	 
	xDouble dAlignTargetX;
	xDouble dAlignTargetY;
	xDouble dAlignTargetT;

	xInt nAlignAxisLightTop;
	xInt nAlignRingLightTop;

	xInt nAlignAxisLightBottom;
	xInt nAlignRingLightBottom;

	xInt nAlignBinTop;
	xInt nAlignBinBottom;

	xInt nInspectAxisLightTop;
	xInt nInspectAxisLightBottom;

	xInt nInspectRingLightTop;
	xInt nInspectRingLightBottom;
	
	xInt nInspectBinTop;
	xInt nInspectBinBottom;
	
	xDouble dInspectTargetX;
	xDouble dInspectTargetY;
	
	xString strGlassId;

	void CopyFrom(CModelDataGlass &file);

};

//Film------------------------------------------------------
class CModelFileFilm : public Serializable
{
public:
	CModelFileFilm();

	xString strFilmId;

	xDouble dAlignTargetX;
	xDouble dAlignTargetY;
	xDouble dAlignTargetT;

	xDouble dAlignOffsetX[FILM_MAX_NUM];
	xDouble dAlignOffsetY[FILM_MAX_NUM];
	xDouble dAlignOffsetT[FILM_MAX_NUM];

	xInt nAlignAxisLightTop;
	xInt nAlignAxisLightBottom;

	xInt nAlignRingLightTop;
	xInt nAlignRingLightBottom;

	xInt nAlignBinTop;
	xInt nAlignBinBottom;

	xInt nInspectAxisLightTop;
	xInt nInspectAxisLightBottom;

	xInt nInspectRingLightTop;
	xInt nInspectRingLightBottom;


	xInt nInspectBinTop;
	xInt nInspectBinBottom;

	xInt nRoi1StartX;
	xInt nRoi1StartY;
	xInt nRoi1EndX;
	xInt nRoi1EndY;

	xInt nRoi2StartX;
	xInt nRoi2StartY;
	xInt nRoi2EndX;
	xInt nRoi2EndY;

	xInt nRoi3StartX;
	xInt nRoi3StartY;
	xInt nRoi3EndX;
	xInt nRoi3EndY;

	xInt nRoi4StartX;
	xInt nRoi4StartY;
	xInt nRoi4EndX;
	xInt nRoi4EndY;

	xInt nRoi5StartX;
	xInt nRoi5StartY;
	xInt nRoi5EndX;
	xInt nRoi5EndY;

	xInt nRoi6StartX;
	xInt nRoi6StartY;
	xInt nRoi6EndX;
	xInt nRoi6EndY;

	xInt nRoi7StartX;
	xInt nRoi7StartY;
	xInt nRoi7EndX;
	xInt nRoi7EndY;

	xInt nRoi8StartX;
	xInt nRoi8StartY;
	xInt nRoi8EndX;
	xInt nRoi8EndY;

	void CopyFrom(CModelDataFilm &file);

};
//---------------------------------------------------------------


class CModelFile : public Serializable
{
public:
	//Awking ModelFile
	
	CModelFileGlass			Glass;
	CModelFileFilm			Film;

public:
	CModelFile();
	~CModelFile();
	
};



