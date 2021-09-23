#include "stdafx.h"
#include "Data/ModelData.h"
#include "Vision/SharedInfo.h"
#include "Log/Logger.h"

CMaterialPara				CModelData::m_MaterialPara;
CAtMaterialPara				CModelData::m_AtMaterialPara;
CMaterialParaAlignStick		CModelData::m_MaterialParaAlignStick;
CAtMaterialParaAlignStick	CModelData::m_AtMaterialParaAlignStick;
CInspectionPara				CModelData::m_InspectionPara;
CStretchPara				CModelData::m_StretchPara;
CModelDataGlass				CModelData::m_GlassPara;
CModelDataAlign				CModelData::m_AlignPara;
CModelDataManual			CModelData::m_ModelSubManualPara;
CModelDataPpa				CModelData::m_PpaPara;

#pragma region //MaterialPara
void CMaterialPara::Init()
{
	int i = 0, j = 0;

	//Sitck Info
	Info.dStickSizeX = 0.0;
	Info.dStickSizeY = 0.0;
	Info.dStickLeftTopX = 0.0;
	Info.dStickLeftTopY = 0.0;
	Info.dAlignLeftHoleX = 0.0;
	Info.dAlignLeftHoleY = 0.0;
	Info.dAlignRightHoleX = 0.0;
	Info.dAlignRightHoleY = 0.0;
	Info.nHoleShape = 0;
	Info.nHoleArrange = 0;
	Info.dAlignHoleSizeX = 0.0;
	Info.dAlignHoleSizeY = 0.0;
	Info.dStickThickness = 0.0;
	Info.dPaperThickness = 0.0;
	//Cell Info
	Info.nCellCountX = 0;
	Info.nCellCountY = 0;
	Info.dFirstCellLeftTopX = 0.0;
	Info.dFirstCellLeftTopY = 0.0;
	Info.dCellPitchX = 0.0;
	Info.dCellPitchY = 0.0;
	
	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		for (j = 0; j < CELL_Y_COUNT_MAX; j++)
		{
			//Sub Cell Info
			Info.dCellLeftTopX[i][j] = 0.0;
			Info.dCellLeftTopX[i][j] = 0.0;
			Info.dCellLeftTopY[i][j] = 0.0;
			Info.dCellSizeX[i][j] = 0.0;
			Info.dCellSizeY[i][j] = 0.0;
			Info.nInspectionSlotCount[i][j] = 0;

			//Slot Info
			Info.dSlotCenterShiftX[i][j] = 0.0;
			Info.dSlotCenterShiftY[i][j] = 0.0;
			Info.dSlotSizeX[i][j] = 0.0;
			Info.dSlotSizeY[i][j] = 0.0;
			Info.dSlotAngle[i][j] = 0.0;
			Info.dSlotPitchX[i][j] = 0.0;
			Info.dSlotPitchY[i][j] = 0.0;
			Info.dSlotTotalPitchX[i][j] = 0.0;
			Info.dSlotTotalPitchY[i][j] = 0.0;
		}
	}

	//Tegkey Info
	Info.dTegkey_LT_X = 0.0;
	Info.dTegkey_LT_Y = 0.0;
	Info.dTegkey_LB_X = 0.0;
	Info.dTegkey_LB_Y = 0.0;
	Info.dTegkey_RT_X = 0.0;
	Info.dTegkey_RT_Y = 0.0;
	Info.dTegkey_RB_X = 0.0;
	Info.dTegkey_RB_Y = 0.0;
	Info.dTegkey_SizeX = 0.0;
	Info.dTegkey_SizeY = 0.0;

	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		Info.dStickWingCenterYOffset[i] = 0.0;
	}

	//KJT 20210411
	Info.dTPSizeX = 0.0;
	Info.dTPSizeY = 0.0;
	Info.nTPRepeatCount = 0;
	Info.nTPCount = 0;
	for (i = 0; i < MAX_TP_COUNT; i++)
	{
		Info.dTPPosX[i] = 0.0;
		Info.dTPPosY[i] = 0.0;
	}

	//KJT 20210411
	Info.d3DHoleSizeX = 0.0;
	Info.d3DHoleSizeY = 0.0;
	Info.n3DHoleRepeatCount = 0;
	Info.n3DHoleCount = 0;
	for (i = 0; i < MAX_3D_HOLE_COUNT; i++)
	{
		Info.d3DHolePosX[i] = 0.0;
		Info.d3DHolePosY[i] = 0.0;
	}

	//KJT 20210824
	for (i = 0; i < 4; i++)
	{
		Info.dReview10XCornerLT_X[i] = 0.0;
		Info.dReview10XCornerLT_Y[i] = 0.0;

		Info.dReview10XCornerRB_X[i] = 0.0;
		Info.dReview10XCornerRB_Y[i] = 0.0;

		Info.dReview10XCornerAngle[i] = 0.0;
	}
}
BOOL CMaterialPara::Save(BOOL byTensionRatio/* = FALSE*/) //KJT 20210301
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#pragma region //KJT 20210415
	if (byTensionRatio)
	{
		double dRatioX = CModelData::m_AtMaterialPara.Info.dTensionRatioX;
		double dRatioY = CModelData::m_AtMaterialPara.Info.dTensionRatioY; //KJT 20210415

		Info.dStickSizeX = CModelData::m_AtMaterialPara.Info.dStickSizeX * dRatioX;
		Info.dStickSizeY = CModelData::m_AtMaterialPara.Info.dStickSizeY * dRatioY;
		Info.dStickLeftTopX = CModelData::m_AtMaterialPara.Info.dStickLeftTopX * dRatioX;
		Info.dStickLeftTopY = CModelData::m_AtMaterialPara.Info.dStickLeftTopY * dRatioY;
		Info.dAlignLeftHoleX = CModelData::m_AtMaterialPara.Info.dAlignLeftHoleX * dRatioX;
		Info.dAlignLeftHoleY = CModelData::m_AtMaterialPara.Info.dAlignLeftHoleY * dRatioY;
		Info.dAlignRightHoleX = CModelData::m_AtMaterialPara.Info.dAlignRightHoleX * dRatioX;
		Info.dAlignRightHoleY = CModelData::m_AtMaterialPara.Info.dAlignRightHoleY * dRatioY;
		Info.nHoleShape = CModelData::m_AtMaterialPara.Info.nHoleShape;
		Info.nHoleArrange = CModelData::m_AtMaterialPara.Info.nHoleArrange;
		Info.dAlignHoleSizeX = CModelData::m_AtMaterialPara.Info.dAlignHoleSizeX * dRatioX;
		Info.dAlignHoleSizeY = CModelData::m_AtMaterialPara.Info.dAlignHoleSizeY * dRatioY;
		Info.dStickThickness = CModelData::m_AtMaterialPara.Info.dStickThickness;
		Info.dPaperThickness = CModelData::m_AtMaterialPara.Info.dPaperThickness;

		//Cell Info
		Info.nCellCountX = CModelData::m_AtMaterialPara.Info.nCellCountX;
		Info.nCellCountY = CModelData::m_AtMaterialPara.Info.nCellCountY;
		Info.dFirstCellLeftTopX = CModelData::m_AtMaterialPara.Info.dFirstCellLeftTopX * dRatioX;
		Info.dFirstCellLeftTopY = CModelData::m_AtMaterialPara.Info.dFirstCellLeftTopY * dRatioY;
		Info.dCellPitchX = CModelData::m_AtMaterialPara.Info.dCellPitchX * dRatioX;
		Info.dCellPitchY = CModelData::m_AtMaterialPara.Info.dCellPitchY * dRatioY;

		for (i = 0; i < CELL_X_COUNT_MAX; i++)
		{
			for (j = 0; j < CELL_Y_COUNT_MAX; j++)
			{
				//Sub Cell Info
				Info.dCellLeftTopX[i][j] = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[i][j] * dRatioX;
				Info.dCellLeftTopY[i][j] = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[i][j] * dRatioY;
				Info.dCellSizeX[i][j] = CModelData::m_AtMaterialPara.Info.dCellSizeX[i][j] * dRatioX;
				Info.dCellSizeY[i][j] = CModelData::m_AtMaterialPara.Info.dCellSizeY[i][j] * dRatioY;
				Info.nInspectionSlotCount[i][j]; CModelData::m_AtMaterialPara.Info.nInspectionSlotCount[i][j];

				//Slot Info
				Info.dSlotCenterShiftX[i][j] = CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[i][j] * dRatioX;
				Info.dSlotCenterShiftY[i][j] = CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[i][j] * dRatioY;
				Info.dSlotSizeX[i][j] = CModelData::m_AtMaterialPara.Info.dSlotSizeX[i][j] * dRatioX;
				Info.dSlotSizeY[i][j] = CModelData::m_AtMaterialPara.Info.dSlotSizeY[i][j] * dRatioY;
				Info.dSlotAngle[i][j] = CModelData::m_AtMaterialPara.Info.dSlotAngle[i][j];
				Info.dSlotPitchX[i][j] = CModelData::m_AtMaterialPara.Info.dSlotPitchX[i][j] * dRatioX;
				Info.dSlotPitchY[i][j] = CModelData::m_AtMaterialPara.Info.dSlotPitchY[i][j] * dRatioY;
				Info.dSlotTotalPitchX[i][j] = CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[i][j] * dRatioX;
				Info.dSlotTotalPitchY[i][j] = CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[i][j] * dRatioY;
			}
		}

		//Tegkey Info
		Info.dTegkey_LT_X = CModelData::m_AtMaterialPara.Info.dTegkey_LT_X * dRatioX;
		Info.dTegkey_LT_Y = CModelData::m_AtMaterialPara.Info.dTegkey_LT_Y * dRatioY;
		Info.dTegkey_LB_X = CModelData::m_AtMaterialPara.Info.dTegkey_LB_X * dRatioX;
		Info.dTegkey_LB_Y = CModelData::m_AtMaterialPara.Info.dTegkey_LB_Y * dRatioY;
		Info.dTegkey_RT_X = CModelData::m_AtMaterialPara.Info.dTegkey_RT_X * dRatioX;
		Info.dTegkey_RT_Y = CModelData::m_AtMaterialPara.Info.dTegkey_RT_Y * dRatioY;
		Info.dTegkey_RB_X = CModelData::m_AtMaterialPara.Info.dTegkey_RB_X * dRatioX;
		Info.dTegkey_RB_Y = CModelData::m_AtMaterialPara.Info.dTegkey_RB_Y * dRatioY;
		Info.dTegkey_SizeX = CModelData::m_AtMaterialPara.Info.dTegkey_SizeX * dRatioX;
		Info.dTegkey_SizeY = CModelData::m_AtMaterialPara.Info.dTegkey_SizeY * dRatioY;

		////Wing Y Offset
		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			Info.dStickWingCenterYOffset[i] = CModelData::m_AtMaterialPara.Info.dStickWingCenterYOffset[i];
		}

		//sunghaklee : HalfEdge --> TP Hole
		//Half Edge Hole XY
		Info.dTPSizeX = CModelData::m_AtMaterialPara.Info.dTPSizeX * dRatioX;
		Info.dTPSizeY = CModelData::m_AtMaterialPara.Info.dTPSizeY * dRatioY;
		Info.nTPRepeatCount = CModelData::m_AtMaterialPara.Info.nTPRepeatCount;
		Info.nTPCount = CModelData::m_AtMaterialPara.Info.nTPCount;
		for (i = 0; i < Info.nTPCount; i++)
		{
			Info.dTPPosX[i] = CModelData::m_AtMaterialPara.Info.dTPPosX[i] * dRatioX;
			Info.dTPPosY[i] = CModelData::m_AtMaterialPara.Info.dTPPosY[i] * dRatioY;
		}

		//sunghaklee : 3D Hole		
		Info.d3DHoleSizeX = CModelData::m_AtMaterialPara.Info.d3DHoleSizeX * dRatioX;
		Info.d3DHoleSizeY = CModelData::m_AtMaterialPara.Info.d3DHoleSizeY * dRatioY;
		Info.n3DHoleRepeatCount = CModelData::m_AtMaterialPara.Info.n3DHoleRepeatCount;
		Info.n3DHoleCount = CModelData::m_AtMaterialPara.Info.n3DHoleCount;
		
		for (i = 0; i < Info.n3DHoleCount; i++)
		{
			Info.d3DHolePosX[i] = CModelData::m_AtMaterialPara.Info.d3DHolePosX[i] * dRatioX;
			Info.d3DHolePosY[i] = CModelData::m_AtMaterialPara.Info.d3DHolePosY[i] * dRatioY;
		}

		//KJT 20210824
		for (i = 0; i < 4; i++)
		{
			Info.dReview10XCornerLT_X[i] = CModelData::m_AtMaterialPara.Info.dReview10XCornerLT_X[i] * dRatioX;
			Info.dReview10XCornerLT_Y[i] = CModelData::m_AtMaterialPara.Info.dReview10XCornerLT_Y[i] * dRatioY;

			Info.dReview10XCornerRB_X[i] = CModelData::m_AtMaterialPara.Info.dReview10XCornerRB_X[i] * dRatioX;
			Info.dReview10XCornerRB_Y[i] = CModelData::m_AtMaterialPara.Info.dReview10XCornerRB_Y[i] * dRatioY;

			Info.dReview10XCornerAngle[i] = CModelData::m_AtMaterialPara.Info.dReview10XCornerAngle[i] * dRatioY;
		}

		Str.Format(_T("MaterialPara / Tension Ratio (X:%.10f, Y:%.10f)"), dRatioX, dRatioY);
		Total_Msg(Str);
}
#pragma endregion

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\MaterialPara.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\MaterialPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("MaterialPara"));
	xml->IntoElem();

	//Sitck Info
	xml->AddElem(_T("dStickSizeX"), Info.dStickSizeX);
	xml->AddElem(_T("dStickSizeY"), Info.dStickSizeY);
	xml->AddElem(_T("dStickLeftTopX"), Info.dStickLeftTopX);
	xml->AddElem(_T("dStickLeftTopY"), Info.dStickLeftTopY);
	xml->AddElem(_T("dAlignLeftHoleX"), Info.dAlignLeftHoleX);
	xml->AddElem(_T("dAlignLeftHoleY"), Info.dAlignLeftHoleY);
	xml->AddElem(_T("dAlignRightHoleX"), Info.dAlignRightHoleX);
	xml->AddElem(_T("dAlignRightHoleY"), Info.dAlignRightHoleY);
	xml->AddElem(_T("nHoleShape"), Info.nHoleShape);
	xml->AddElem(_T("nHoleArrange"), Info.nHoleArrange);
	xml->AddElem(_T("dAlignHoleSizeX"), Info.dAlignHoleSizeX);
	xml->AddElem(_T("dAlignHoleSizeY"), Info.dAlignHoleSizeY);
	xml->AddElem(_T("dStickThickness"), Info.dStickThickness);
	xml->AddElem(_T("dPaperThickness"), Info.dPaperThickness);

	//Cell Info
	xml->AddElem(_T("nCellCountX"), Info.nCellCountX);
	xml->AddElem(_T("nCellCountY"), Info.nCellCountY);
	xml->AddElem(_T("dFirstCellLeftTopX"), Info.dFirstCellLeftTopX);
	xml->AddElem(_T("dFirstCellLeftTopY"), Info.dFirstCellLeftTopY);
	xml->AddElem(_T("dCellPitchX"), Info.dCellPitchX);
	xml->AddElem(_T("dCellPitchY"), Info.dCellPitchY);
	
	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		for (j = 0; j < CELL_Y_COUNT_MAX; j++)
		{
			//Sub Cell Info
			Str.Format(_T("dCellLeftTopX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dCellLeftTopX[i][j]);
			Str.Format(_T("dCellLeftTopY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dCellLeftTopY[i][j]);
			Str.Format(_T("dCellSizeX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dCellSizeX[i][j]);
			Str.Format(_T("dCellSizeY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dCellSizeY[i][j]);
			Str.Format(_T("nInspectionSlotCount_%d_%d"), i, j);
			xml->AddElem(Str, Info.nInspectionSlotCount[i][j]);

			//Slot Info
			Str.Format(_T("dSlotCenterShiftX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotCenterShiftX[i][j]);
			Str.Format(_T("dSlotCenterShiftY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotCenterShiftY[i][j]);
			Str.Format(_T("dSlotSizeX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotSizeX[i][j]);
			Str.Format(_T("dSlotSizeY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotSizeY[i][j]);
			Str.Format(_T("dSlotAngle_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotAngle[i][j]);
			Str.Format(_T("dSlotPitchX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotPitchX[i][j]);
			Str.Format(_T("dSlotPitchY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotPitchY[i][j]);
			Str.Format(_T("dSlotTotalPitchX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotTotalPitchX[i][j]);
			Str.Format(_T("dSlotTotalPitchY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotTotalPitchY[i][j]);
		}
	}

	//Tegkey Info
	xml->AddElem(_T("dTegkey_LT_X"), Info.dTegkey_LT_X);
	xml->AddElem(_T("dTegkey_LT_Y"), Info.dTegkey_LT_Y);
	xml->AddElem(_T("dTegkey_LB_X"), Info.dTegkey_LB_X);
	xml->AddElem(_T("dTegkey_LB_Y"), Info.dTegkey_LB_Y);
	xml->AddElem(_T("dTegkey_RT_X"), Info.dTegkey_RT_X);
	xml->AddElem(_T("dTegkey_RT_Y"), Info.dTegkey_RT_Y);
	xml->AddElem(_T("dTegkey_RB_X"), Info.dTegkey_RB_X);
	xml->AddElem(_T("dTegkey_RB_Y"), Info.dTegkey_RB_Y);
	xml->AddElem(_T("dTegkey_SizeX"), Info.dTegkey_SizeX);
	xml->AddElem(_T("dTegkey_SizeY"), Info.dTegkey_SizeY);

	//Wing Y Offset
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		Str.Format(_T("dStickWingCenterYOffset_%d"), i);
		xml->AddElem(Str, Info.dStickWingCenterYOffset[i]);
	}

	//KJT 20210411
	Str.Format(_T("dTPSizeX"));
	xml->AddElem(Str, Info.dTPSizeX);
	Str.Format(_T("dTPSizeY"));
	xml->AddElem(Str, Info.dTPSizeY);
	Str.Format(_T("nTPRepeatCount"));
	xml->AddElem(Str, Info.nTPRepeatCount);
	Str.Format(_T("nTPCount"));
	xml->AddElem(Str, Info.nTPCount);
	for (i = 0; i < Info.nTPCount; i++)
	{
		Str.Format(_T("dTPPosX_%d"), i);
		xml->AddElem(Str, Info.dTPPosX[i]);
		Str.Format(_T("dTPPosY_%d"), i);
		xml->AddElem(Str, Info.dTPPosY[i]);
	}

	//KJT 20210411
	Str.Format(_T("d3DHoleSizeX"));
	xml->AddElem(Str, Info.d3DHoleSizeX);
	Str.Format(_T("d3DHoleSizeY"));
	xml->AddElem(Str, Info.d3DHoleSizeY);
	Str.Format(_T("n3DHoleRepeatCount"));
	xml->AddElem(Str, Info.n3DHoleRepeatCount);
	Str.Format(_T("n3DHoleCount"));
	xml->AddElem(Str, Info.n3DHoleCount);
	for (i = 0; i < Info.n3DHoleCount; i++)
	{
		Str.Format(_T("d3DHolePosX_%d"), i);
		xml->AddElem(Str, Info.d3DHolePosX[i]);
		Str.Format(_T("d3DHolePosY_%d"), i);
		xml->AddElem(Str, Info.d3DHolePosY[i]);
	}

	//KJT 20210824
	for (i = 0; i < 4; i++)
	{
		Str.Format(_T("dReview10XCornerLT_X_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerLT_X[i]);
		Str.Format(_T("dReview10XCornerLT_Y_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerLT_Y[i]);

		Str.Format(_T("dReview10XCornerRB_X_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerRB_X[i]);
		Str.Format(_T("dReview10XCornerRB_Y_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerRB_Y[i]);

		Str.Format(_T("dReview10XCornerAngle_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerAngle[i]);
	}

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("MaterialPara Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CMaterialPara::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\MaterialPara.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();

	Str.Format(_T("MaterialPara Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
#else //xml
	szFilePath.AppendFormat(_T("\\MaterialPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("MaterialPara")))
	{
		xml->IntoElem();

		//Sitck Info
		if (xml->FindElem(_T("dStickSizeX"))) Info.dStickSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dStickSizeY"))) Info.dStickSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dStickLeftTopX"))) Info.dStickLeftTopX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dStickLeftTopY"))) Info.dStickLeftTopY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignLeftHoleX"))) Info.dAlignLeftHoleX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignLeftHoleY"))) Info.dAlignLeftHoleY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignRightHoleX"))) Info.dAlignRightHoleX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignRightHoleY"))) Info.dAlignRightHoleY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nHoleShape"))) Info.nHoleShape = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nHoleArrange"))) Info.nHoleArrange = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dAlignHoleSizeX"))) Info.dAlignHoleSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignHoleSizeY"))) Info.dAlignHoleSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dStickThickness"))) Info.dStickThickness = _tstof(xml->GetData());
		if (xml->FindElem(_T("dPaperThickness"))) Info.dPaperThickness = _tstof(xml->GetData());

		//Cell Info
		if (xml->FindElem(_T("nCellCountX"))) Info.nCellCountX = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nCellCountY"))) Info.nCellCountY = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dFirstCellLeftTopX"))) Info.dFirstCellLeftTopX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dFirstCellLeftTopY"))) Info.dFirstCellLeftTopY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dCellPitchX"))) Info.dCellPitchX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dCellPitchY"))) Info.dCellPitchY = _tstof(xml->GetData());
		
		for (i=0; i< CELL_X_COUNT_MAX; i++)
		{
			for (j = 0; j < CELL_Y_COUNT_MAX; j++)
			{
				//Sub Cell Info
				Str.Format(_T("dCellLeftTopX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dCellLeftTopX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dCellLeftTopY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dCellLeftTopY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dCellSizeX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dCellSizeX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dCellSizeY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dCellSizeY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("nInspectionSlotCount_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.nInspectionSlotCount[i][j] = _tstoi(xml->GetData());

				//Slot Info
				Str.Format(_T("dSlotCenterShiftX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotCenterShiftX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotCenterShiftY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotCenterShiftY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotSizeX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotSizeX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotSizeY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotSizeY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotAngle_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotAngle[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotPitchX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotPitchX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotPitchY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotPitchY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotTotalPitchX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotTotalPitchX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotTotalPitchY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotTotalPitchY[i][j] = _tstof(xml->GetData());
			}
		}

		//Tegkey Info
		if (xml->FindElem(_T("dTegkey_LT_X"))) Info.dTegkey_LT_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_LT_Y"))) Info.dTegkey_LT_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_LB_X"))) Info.dTegkey_LB_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_LB_Y"))) Info.dTegkey_LB_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_RT_X"))) Info.dTegkey_RT_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_RT_Y"))) Info.dTegkey_RT_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_RB_X"))) Info.dTegkey_RB_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_RB_Y"))) Info.dTegkey_RB_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_SizeX"))) Info.dTegkey_SizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_SizeY"))) Info.dTegkey_SizeY = _tstof(xml->GetData());
		
		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			//Wing Y Offset //0:+
			Str.Format(_T("dStickWingCenterYOffset_%d"), i);
			if (xml->FindElem(Str)) Info.dStickWingCenterYOffset[i] = _tstof(xml->GetData());
		}

		//KJT 20210411
		Str.Format(_T("dTPSizeX"));
		if (xml->FindElem(Str)) Info.dTPSizeX = _tstof(xml->GetData());
		Str.Format(_T("dTPSizeY"));
		if (xml->FindElem(Str)) Info.dTPSizeY = _tstof(xml->GetData());
		Str.Format(_T("nTPRepeatCount"));
		if (xml->FindElem(Str)) Info.nTPRepeatCount = _tstoi(xml->GetData());
		Str.Format(_T("nTPCount"));
		if (xml->FindElem(Str)) Info.nTPCount = _tstoi(xml->GetData());
		for (i = 0; i < Info.nTPCount; i++)
		{
			Str.Format(_T("dTPPosX_%d"), i);
			if (xml->FindElem(Str)) Info.dTPPosX[i] = _tstof(xml->GetData());
			Str.Format(_T("dTPPosY_%d"), i);
			if (xml->FindElem(Str)) Info.dTPPosY[i] = _tstof(xml->GetData());
		}

		//KJT 20210411
		Str.Format(_T("d3DHoleSizeX"));
		if (xml->FindElem(Str)) Info.d3DHoleSizeX = _tstof(xml->GetData());
		Str.Format(_T("d3DHoleSizeY"));
		if (xml->FindElem(Str)) Info.d3DHoleSizeY = _tstof(xml->GetData());
		Str.Format(_T("n3DHoleRepeatCount"));
		if (xml->FindElem(Str)) Info.n3DHoleRepeatCount = _tstoi(xml->GetData());
		Str.Format(_T("n3DHoleCount"));
		if (xml->FindElem(Str)) Info.n3DHoleCount = _tstoi(xml->GetData());

		for (i = 0; i < Info.n3DHoleCount; i++)
		{
			Str.Format(_T("d3DHolePosX_%d"), i);
			if (xml->FindElem(Str)) Info.d3DHolePosX[i] = _tstof(xml->GetData());
			Str.Format(_T("d3DHolePosY_%d"), i);
			if (xml->FindElem(Str)) Info.d3DHolePosY[i] = _tstof(xml->GetData());
		}

		//KJT 20210824
		for (i = 0; i < 4; i++)
		{
			Str.Format(_T("dReview10XCornerLT_X_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerLT_X[i] = _tstof(xml->GetData());
			Str.Format(_T("dReview10XCornerLT_Y_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerLT_Y[i] = _tstof(xml->GetData());

			Str.Format(_T("dReview10XCornerRB_X_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerRB_X[i] = _tstof(xml->GetData());
			Str.Format(_T("dReview10XCornerRB_Y_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerRB_Y[i] = _tstof(xml->GetData());

			Str.Format(_T("dReview10XCornerAngle_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerAngle[i] = _tstof(xml->GetData());
		}

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("MaterialPara Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion

#pragma region //AtMaterialPara
void CAtMaterialPara::Init()
{
	int i = 0, j = 0;

	//Sitck Info
	Info.dStickSizeX = 0.0;
	Info.dStickSizeY = 0.0;
	Info.dStickLeftTopX = 0.0;
	Info.dStickLeftTopY = 0.0;
	Info.dAlignLeftHoleX = 0.0;
	Info.dAlignLeftHoleY = 0.0;
	Info.dAlignRightHoleX = 0.0;
	Info.dAlignRightHoleY = 0.0;
	Info.nHoleShape = 0;
	Info.nHoleArrange = 0;
	Info.dAlignHoleSizeX = 0.0;
	Info.dAlignHoleSizeY = 0.0;
	Info.dStickThickness = 0.0;
	Info.dPaperThickness = 0.0;
	//Cell Info
	Info.nCellCountX = 0;
	Info.nCellCountY = 0;
	Info.dFirstCellLeftTopX = 0.0;
	Info.dFirstCellLeftTopY = 0.0;
	Info.dCellPitchX = 0.0;
	Info.dCellPitchY = 0.0;

	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		for (j = 0; j < CELL_Y_COUNT_MAX; j++)
		{
			//Sub Cell Info
			Info.dCellLeftTopX[i][j] = 0.0;
			Info.dCellLeftTopX[i][j];
			Info.dCellLeftTopY[i][j];
			Info.dCellSizeX[i][j];
			Info.dCellSizeY[i][j];
			Info.nInspectionSlotCount[i][j];

			//Slot Info
			Info.dSlotCenterShiftX[i][j];
			Info.dSlotCenterShiftY[i][j];
			Info.dSlotSizeX[i][j];
			Info.dSlotSizeY[i][j];
			Info.dSlotAngle[i][j];
			Info.dSlotPitchX[i][j];
			Info.dSlotPitchY[i][j];
			Info.dSlotTotalPitchX[i][j];
			Info.dSlotTotalPitchY[i][j];
		}
	}

	Info.dTegkey_LT_X = 0.0;
	Info.dTegkey_LT_Y = 0.0;
	Info.dTegkey_LB_X = 0.0;
	Info.dTegkey_LB_Y = 0.0;
	Info.dTegkey_RT_X = 0.0;
	Info.dTegkey_RT_Y = 0.0;
	Info.dTegkey_RB_X = 0.0;
	Info.dTegkey_RB_Y = 0.0;
	Info.dTegkey_SizeX = 0.0;
	Info.dTegkey_SizeY = 0.0;

	//Wing Y Offset
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		Info.dStickWingCenterYOffset[i] = 0.0; //0:+

	Info.dTensionRatioX = 1.0; //KJT 20210316
	Info.dTensionRatioY = 1.0; //KJT 20210415

	//KJT 20210411
	Info.dTPSizeX = 0.0;
	Info.dTPSizeY = 0.0;
	Info.nTPRepeatCount = 0;
	Info.nTPCount = 0;
	for (i = 0; i < MAX_TP_COUNT; i++)
	{
		Info.dTPPosX[i] = 0.0;
		Info.dTPPosY[i] = 0.0;
	}

	//KJT 20210411
	Info.d3DHoleSizeX = 0.0;
	Info.d3DHoleSizeY = 0.0;
	Info.n3DHoleRepeatCount = 0;
	Info.n3DHoleCount = 0;
	for (i = 0; i < MAX_3D_HOLE_COUNT; i++)
	{
		Info.d3DHolePosX[i] = 0.0;
		Info.d3DHolePosY[i] = 0.0;
	}

	//KJT 20210824
	for (i = 0; i < 4; i++)
	{
		Info.dReview10XCornerLT_X[i] = 0.0;
		Info.dReview10XCornerLT_Y[i] = 0.0;

		Info.dReview10XCornerRB_X[i] = 0.0;
		Info.dReview10XCornerRB_Y[i] = 0.0;

		Info.dReview10XCornerAngle[i] = 0.0;
	}
}
BOOL CAtMaterialPara::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\AtMaterialPara.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\AtMaterialPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("AtMaterialPara"));
	xml->IntoElem();

	//Sitck Info
	xml->AddElem(_T("dStickSizeX"), Info.dStickSizeX);
	xml->AddElem(_T("dStickSizeY"), Info.dStickSizeY);
	xml->AddElem(_T("dStickLeftTopX"), Info.dStickLeftTopX);
	xml->AddElem(_T("dStickLeftTopY"), Info.dStickLeftTopY);
	xml->AddElem(_T("dAlignLeftHoleX"), Info.dAlignLeftHoleX);
	xml->AddElem(_T("dAlignLeftHoleY"), Info.dAlignLeftHoleY);
	xml->AddElem(_T("dAlignRightHoleX"), Info.dAlignRightHoleX);
	xml->AddElem(_T("dAlignRightHoleY"), Info.dAlignRightHoleY);
	xml->AddElem(_T("nHoleShape"), Info.nHoleShape);
	xml->AddElem(_T("nHoleArrange"), Info.nHoleArrange);
	xml->AddElem(_T("dAlignHoleSizeX"), Info.dAlignHoleSizeX);
	xml->AddElem(_T("dAlignHoleSizeY"), Info.dAlignHoleSizeY);
	xml->AddElem(_T("dStickThickness"), Info.dStickThickness);
	xml->AddElem(_T("dPaperThickness"), Info.dPaperThickness);

	//Cell Info
	xml->AddElem(_T("nCellCountX"), Info.nCellCountX);
	xml->AddElem(_T("nCellCountY"), Info.nCellCountY);
	xml->AddElem(_T("dFirstCellLeftTopX"), Info.dFirstCellLeftTopX);
	xml->AddElem(_T("dFirstCellLeftTopY"), Info.dFirstCellLeftTopY);
	xml->AddElem(_T("dCellPitchX"), Info.dCellPitchX);
	xml->AddElem(_T("dCellPitchY"), Info.dCellPitchY);

	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		for (j = 0; j < CELL_Y_COUNT_MAX; j++)
		{
			//Sub Cell Info
			Str.Format(_T("dCellLeftTopX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dCellLeftTopX[i][j]);
			Str.Format(_T("dCellLeftTopY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dCellLeftTopY[i][j]);
			Str.Format(_T("dCellSizeX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dCellSizeX[i][j]);
			Str.Format(_T("dCellSizeY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dCellSizeY[i][j]);
			Str.Format(_T("nInspectionSlotCount_%d_%d"), i, j);
			xml->AddElem(Str, Info.nInspectionSlotCount[i][j]);

			//Slot Info
			Str.Format(_T("dSlotCenterShiftX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotCenterShiftX[i][j]);
			Str.Format(_T("dSlotCenterShiftY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotCenterShiftY[i][j]);
			Str.Format(_T("dSlotSizeX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotSizeX[i][j]);
			Str.Format(_T("dSlotSizeY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotSizeY[i][j]);
			Str.Format(_T("dSlotAngle_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotAngle[i][j]);
			Str.Format(_T("dSlotPitchX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotPitchX[i][j]);
			Str.Format(_T("dSlotPitchY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotPitchY[i][j]);
			Str.Format(_T("dSlotTotalPitchX_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotTotalPitchX[i][j]);
			Str.Format(_T("dSlotTotalPitchY_%d_%d"), i, j);
			xml->AddElem(Str, Info.dSlotTotalPitchY[i][j]);
		}
	}

	//Tegkey Info
	xml->AddElem(_T("dTegkey_LT_X"), Info.dTegkey_LT_X);
	xml->AddElem(_T("dTegkey_LT_Y"), Info.dTegkey_LT_Y);
	xml->AddElem(_T("dTegkey_LB_X"), Info.dTegkey_LB_X);
	xml->AddElem(_T("dTegkey_LB_Y"), Info.dTegkey_LB_Y);
	xml->AddElem(_T("dTegkey_RT_X"), Info.dTegkey_RT_X);
	xml->AddElem(_T("dTegkey_RT_Y"), Info.dTegkey_RT_Y);
	xml->AddElem(_T("dTegkey_RB_X"), Info.dTegkey_RB_X);
	xml->AddElem(_T("dTegkey_RB_Y"), Info.dTegkey_RB_Y);
	xml->AddElem(_T("dTegkey_SizeX"), Info.dTegkey_SizeX);
	xml->AddElem(_T("dTegkey_SizeY"), Info.dTegkey_SizeY);

	//Wing Y Offset
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		Str.Format(_T("dStickWingCenterYOffset_%d"), i);
		xml->AddElem(Str, Info.dStickWingCenterYOffset[i]);
	}

	xml->AddElem(_T("dTensionRatioX"), Info.dTensionRatioX); //KJT 20210301
	xml->AddElem(_T("dTensionRatioY"), Info.dTensionRatioY); //KJT 20210415


	//sunghaklee : HalfEdge --> TP Hole
	//KJT 20210411
	Str.Format(_T("dTPSizeX"));
	xml->AddElem(Str, Info.dTPSizeX);
	Str.Format(_T("dTPSizeY"));
	xml->AddElem(Str, Info.dTPSizeY);
	Str.Format(_T("nTPRepeatCount"));
	xml->AddElem(Str, Info.nTPRepeatCount);
	Str.Format(_T("nTPCount"));
	xml->AddElem(Str, Info.nTPCount);	

	for (i = 0; i < Info.nTPCount; i++)
	{
		Str.Format(_T("dTPPosX_%d"), i);
		xml->AddElem(Str, Info.dTPPosX[i]);
		Str.Format(_T("dTPPosY_%d"), i);
		xml->AddElem(Str, Info.dTPPosY[i]);
	}

	//sunghaklee : 3D Hole
	//KJT 20210411
	Str.Format(_T("d3DHoleSizeX"));
	xml->AddElem(Str, Info.d3DHoleSizeX);
	Str.Format(_T("d3DHoleSizeY"));
	xml->AddElem(Str, Info.d3DHoleSizeY);
	Str.Format(_T("n3DHoleRepeatCount"));
	xml->AddElem(Str, Info.n3DHoleRepeatCount);
	Str.Format(_T("n3DHoleCount"));
	xml->AddElem(Str, Info.n3DHoleCount);

	for (i = 0; i < Info.n3DHoleCount; i++)
	{
		Str.Format(_T("d3DHolePosX_%d"), i);
		xml->AddElem(Str, Info.d3DHolePosX[i]);
		Str.Format(_T("d3DHolePosY_%d"), i);
		xml->AddElem(Str, Info.d3DHolePosY[i]);
	}

	//KJT 20210824
	for (i = 0; i < 4; i++)
	{
		Str.Format(_T("dReview10XCornerLT_X_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerLT_X[i]);
		Str.Format(_T("dReview10XCornerLT_Y_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerLT_Y[i]);

		Str.Format(_T("dReview10XCornerRB_X_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerRB_X[i]);
		Str.Format(_T("dReview10XCornerRB_Y_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerRB_Y[i]);

		Str.Format(_T("dReview10XCornerAngle_%d"), i);
		xml->AddElem(Str, Info.dReview10XCornerAngle[i]);
	}

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("AtMaterialPara Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CAtMaterialPara::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\AtMaterialPara.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\AtMaterialPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("AtMaterialPara")))
	{
		xml->IntoElem();

		//Sitck Info
		if (xml->FindElem(_T("dStickSizeX"))) Info.dStickSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dStickSizeY"))) Info.dStickSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dStickLeftTopX"))) Info.dStickLeftTopX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dStickLeftTopY"))) Info.dStickLeftTopY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignLeftHoleX"))) Info.dAlignLeftHoleX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignLeftHoleY"))) Info.dAlignLeftHoleY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignRightHoleX"))) Info.dAlignRightHoleX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignRightHoleY"))) Info.dAlignRightHoleY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nHoleShape"))) Info.nHoleShape = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nHoleArrange"))) Info.nHoleArrange = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dAlignHoleSizeX"))) Info.dAlignHoleSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignHoleSizeY"))) Info.dAlignHoleSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dStickThickness"))) Info.dStickThickness = _tstof(xml->GetData());
		if (xml->FindElem(_T("dPaperThickness"))) Info.dPaperThickness = _tstof(xml->GetData());

		//Cell Info
		if (xml->FindElem(_T("nCellCountX"))) Info.nCellCountX = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nCellCountY"))) Info.nCellCountY = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dFirstCellLeftTopX"))) Info.dFirstCellLeftTopX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dFirstCellLeftTopY"))) Info.dFirstCellLeftTopY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dCellPitchX"))) Info.dCellPitchX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dCellPitchY"))) Info.dCellPitchY = _tstof(xml->GetData());

		for (i = 0; i < CELL_X_COUNT_MAX; i++)
		{
			for (j = 0; j < CELL_Y_COUNT_MAX; j++)
			{
				//Sub Cell Info
				Str.Format(_T("dCellLeftTopX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dCellLeftTopX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dCellLeftTopY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dCellLeftTopY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dCellSizeX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dCellSizeX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dCellSizeY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dCellSizeY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("nInspectionSlotCount_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.nInspectionSlotCount[i][j] = _tstoi(xml->GetData());

				//Slot Info
				Str.Format(_T("dSlotCenterShiftX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotCenterShiftX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotCenterShiftY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotCenterShiftY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotSizeX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotSizeX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotSizeY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotSizeY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotAngle_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotAngle[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotPitchX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotPitchX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotPitchY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotPitchY[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotTotalPitchX_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotTotalPitchX[i][j] = _tstof(xml->GetData());
				Str.Format(_T("dSlotTotalPitchY_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dSlotTotalPitchY[i][j] = _tstof(xml->GetData());
			}
		}

		//Tegkey Info
		if (xml->FindElem(_T("dTegkey_LT_X"))) Info.dTegkey_LT_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_LT_Y"))) Info.dTegkey_LT_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_LB_X"))) Info.dTegkey_LB_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_LB_Y"))) Info.dTegkey_LB_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_RT_X"))) Info.dTegkey_RT_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_RT_Y"))) Info.dTegkey_RT_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_RB_X"))) Info.dTegkey_RB_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_RB_Y"))) Info.dTegkey_RB_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_SizeX"))) Info.dTegkey_SizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkey_SizeY"))) Info.dTegkey_SizeY = _tstof(xml->GetData());

		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			//Wing Y Offset //0:+
			Str.Format(_T("dStickWingCenterYOffset_%d"), i);
			if (xml->FindElem(Str)) Info.dStickWingCenterYOffset[i] = _tstof(xml->GetData());
		}

		if (xml->FindElem(_T("dTensionRatioX"))) Info.dTensionRatioX = _tstof(xml->GetData()); //KJT 20210301
		if (xml->FindElem(_T("dTensionRatioY"))) Info.dTensionRatioY = _tstof(xml->GetData()); //KJT 20210415


		//sunghaklee : HalfEdge --> TP Hole
		//KJT 20210411	
		Str.Format(_T("dTPSizeX"));
		if (xml->FindElem(Str)) Info.dTPSizeX = _tstof(xml->GetData());
		Str.Format(_T("dTPSizeY"));
		if (xml->FindElem(Str)) Info.dTPSizeY = _tstof(xml->GetData());		
		Str.Format(_T("nTPRepeatCount"));
		if (xml->FindElem(Str)) Info.nTPRepeatCount = _tstoi(xml->GetData());
		Str.Format(_T("nTPCount"));
		if (xml->FindElem(Str)) Info.nTPCount = _tstoi(xml->GetData());
		
		for (i = 0; i < Info.nTPCount; i++)
		{
			Str.Format(_T("dTPPosX_%d"), i);
			if (xml->FindElem(Str)) Info.dTPPosX[i] = _tstof(xml->GetData());
			Str.Format(_T("dTPPosY_%d"), i);
			if (xml->FindElem(Str)) Info.dTPPosY[i] = _tstof(xml->GetData());
		}

		//sunghaklee : 3D Hole
		//KJT 20210411	
		Str.Format(_T("d3DHoleSizeX"));
		if (xml->FindElem(Str)) Info.d3DHoleSizeX = _tstof(xml->GetData());
		Str.Format(_T("d3DHoleSizeY"));
		if (xml->FindElem(Str)) Info.d3DHoleSizeY = _tstof(xml->GetData());
		Str.Format(_T("n3DHoleRepeatCount"));
		if (xml->FindElem(Str)) Info.n3DHoleRepeatCount = _tstoi(xml->GetData());
		Str.Format(_T("n3DHoleCount"));
		if (xml->FindElem(Str)) Info.n3DHoleCount = _tstoi(xml->GetData());

		for (i = 0; i < Info.n3DHoleCount; i++)
		{
			Str.Format(_T("d3DHolePosX_%d"), i);
			if (xml->FindElem(Str)) Info.d3DHolePosX[i] = _tstof(xml->GetData());
			Str.Format(_T("d3DHolePosY_%d"), i);
			if (xml->FindElem(Str)) Info.d3DHolePosY[i] = _tstof(xml->GetData());
		}

		//KJT 20210824
		for (i = 0; i < 4; i++)
		{
			Str.Format(_T("dReview10XCornerLT_X_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerLT_X[i] = _tstof(xml->GetData());
			Str.Format(_T("dReview10XCornerLT_Y_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerLT_Y[i] = _tstof(xml->GetData());

			Str.Format(_T("dReview10XCornerRB_X_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerRB_X[i] = _tstof(xml->GetData());
			Str.Format(_T("dReview10XCornerRB_Y_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerRB_Y[i] = _tstof(xml->GetData());

			Str.Format(_T("dReview10XCornerAngle_%d"), i);
			if (xml->FindElem(Str)) Info.dReview10XCornerAngle[i] = _tstof(xml->GetData());
		}

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("AtMaterialPara Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion

#pragma region //MaterialParaAlignStick
void CMaterialParaAlignStick::Init()
{
	swprintf_s(Info.strID, _T(""));
	
	Info.nOrder = 0;
	Info.dSizeX = 0.0;
	Info.dSizeY = 0.0;
	Info.dPosY = 0.0;

	Info.dAlignMarkSizeX = 0.0;
	Info.dAlignMarkSizeY = 0.0;
	Info.dAlignMarkLTX = 0.0;
	Info.dAlignMarkLTY = 0.0;
	Info.dAlignMarkRTX = 0.0;
	Info.dAlignMarkRTY = 0.0;

	Info.dDepoMarkSizeX = 0.0;
	Info.dDepoMarkSizeY = 0.0;
	Info.dDepoMarkLTX = 0.0;
	Info.dDepoMarkLTY = 0.0;
	Info.dDepoMarkRTX = 0.0;
	Info.dDepoMarkRTY = 0.0;

	Info.dTegSizeX = 0.0;
	Info.dTegSizeY = 0.0;
	Info.dTegLT1X = 0.0;
	Info.dTegLT1Y = 0.0;
	Info.dTegRT2X = 0.0;
	Info.dTegRT2Y = 0.0;

	Info.dSkirtPitchY = 0.0;

	Info.dBcrPosX = 0.0;
	Info.dBcrPosY = 0.0;
}
BOOL CMaterialParaAlignStick::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\MaterialParaAlignStick.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\MaterialParaAlignStick.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("MaterialParaAlignStick"));
	xml->IntoElem();

	xml->AddElem(_T("strID"), Info.strID);
	xml->AddElem(_T("nOrder"), Info.nOrder);
	xml->AddElem(_T("dSizeX"), Info.dSizeX);
	xml->AddElem(_T("dSizeY"), Info.dSizeY);
	xml->AddElem(_T("dPosY"), Info.dPosY);

	xml->AddElem(_T("dAlignMarkSizeX"), Info.dAlignMarkSizeX);
	xml->AddElem(_T("dAlignMarkSizeY"), Info.dAlignMarkSizeY);
	xml->AddElem(_T("dAlignMarkLTX"), Info.dAlignMarkLTX);
	xml->AddElem(_T("dAlignMarkLTY"), Info.dAlignMarkLTY);
	xml->AddElem(_T("dAlignMarkRTX"), Info.dAlignMarkRTX);
	xml->AddElem(_T("dAlignMarkRTY"), Info.dAlignMarkRTY);

	xml->AddElem(_T("dDepoMarkSizeX"), Info.dDepoMarkSizeX);
	xml->AddElem(_T("dDepoMarkSizeY"), Info.dDepoMarkSizeY);
	xml->AddElem(_T("dDepoMarkLTX"), Info.dDepoMarkLTX);
	xml->AddElem(_T("dDepoMarkLTY"), Info.dDepoMarkLTY);
	xml->AddElem(_T("dDepoMarkRTX"), Info.dDepoMarkRTX);
	xml->AddElem(_T("dDepoMarkRTY"), Info.dDepoMarkRTY);

	xml->AddElem(_T("dTegSizeX"), Info.dTegSizeX);
	xml->AddElem(_T("dTegSizeY"), Info.dTegSizeY);
	xml->AddElem(_T("dTegLT1X"), Info.dTegLT1X);
	xml->AddElem(_T("dTegLT1Y"), Info.dTegLT1Y);
	xml->AddElem(_T("dTegRT2X"), Info.dTegRT2X);
	xml->AddElem(_T("dTegRT2Y"), Info.dTegRT2Y);

	xml->AddElem(_T("dSkirtPitchY"), Info.dSkirtPitchY);

	xml->AddElem(_T("dBcrPosX"), Info.dBcrPosX);
	xml->AddElem(_T("dBcrPosY"), Info.dBcrPosY);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif
	
	Str.Format(_T("MaterialParaAlignStick Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CMaterialParaAlignStick::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\MaterialParaAlignStick.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\MaterialParaAlignStick.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("MaterialParaAlignStick")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("strID"))) 	swprintf_s(Info.strID, _T("%s"), xml->GetData());
		if (xml->FindElem(_T("nOrder"))) Info.nOrder = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dSizeX"))) Info.dSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dSizeY"))) Info.dSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dPosY"))) Info.dPosY = _tstof(xml->GetData());

		if (xml->FindElem(_T("dAlignMarkSizeX"))) Info.dAlignMarkSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkSizeY"))) Info.dAlignMarkSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkLTX"))) Info.dAlignMarkLTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkLTY"))) Info.dAlignMarkLTY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkRTX"))) Info.dAlignMarkRTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkRTY"))) Info.dAlignMarkRTY = _tstof(xml->GetData());

		if (xml->FindElem(_T("dDepoMarkSizeX"))) Info.dDepoMarkSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkSizeY"))) Info.dDepoMarkSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkLTX"))) Info.dDepoMarkLTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkLTY"))) Info.dDepoMarkLTY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkRTX"))) Info.dDepoMarkRTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkRTY"))) Info.dDepoMarkRTY = _tstof(xml->GetData());

		if (xml->FindElem(_T("dTegSizeX"))) Info.dTegSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegSizeY"))) Info.dTegSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegLT1X"))) Info.dTegLT1X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegLT1Y"))) Info.dTegLT1Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegRT2X"))) Info.dTegRT2X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegRT2Y"))) Info.dTegRT2Y = _tstof(xml->GetData());

		if (xml->FindElem(_T("dSkirtPitchY"))) Info.dSkirtPitchY = _tstof(xml->GetData());

		if (xml->FindElem(_T("dBcrPosX"))) Info.dBcrPosX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dBcrPosY"))) Info.dBcrPosY = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("MaterialParaAlignStick Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion
#pragma region //AtMaterialParaAlignStick
void CAtMaterialParaAlignStick::Init()
{
	swprintf_s(Info.strID, _T(""));

	Info.nOrder = 0;
	Info.dSizeX = 0.0;
	Info.dSizeY = 0.0;
	Info.dPosY = 0.0;

	Info.dAlignMarkSizeX = 0.0;
	Info.dAlignMarkSizeY = 0.0;
	Info.dAlignMarkLTX = 0.0;
	Info.dAlignMarkLTY = 0.0;
	Info.dAlignMarkRTX = 0.0;
	Info.dAlignMarkRTY = 0.0;

	Info.dDepoMarkSizeX = 0.0;
	Info.dDepoMarkSizeY = 0.0;
	Info.dDepoMarkLTX = 0.0;
	Info.dDepoMarkLTY = 0.0;
	Info.dDepoMarkRTX = 0.0;
	Info.dDepoMarkRTY = 0.0;

	Info.dTegSizeX = 0.0;
	Info.dTegSizeY = 0.0;
	Info.dTegLT1X = 0.0;
	Info.dTegLT1Y = 0.0;
	Info.dTegRT2X = 0.0;
	Info.dTegRT2Y = 0.0;

	Info.dSkirtPitchY = 0.0;

	Info.dBcrPosX = 0.0;
	Info.dBcrPosY = 0.0;
}
BOOL CAtMaterialParaAlignStick::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\AtMaterialParaAlignStick.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\AtMaterialParaAlignStick.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("AtMaterialParaAlignStick"));
	xml->IntoElem();

	xml->AddElem(_T("strID"), Info.strID);
	xml->AddElem(_T("nOrder"), Info.nOrder);
	xml->AddElem(_T("dSizeX"), Info.dSizeX);
	xml->AddElem(_T("dSizeY"), Info.dSizeY);
	xml->AddElem(_T("dPosY"), Info.dPosY);

	xml->AddElem(_T("dAlignMarkSizeX"), Info.dAlignMarkSizeX);
	xml->AddElem(_T("dAlignMarkSizeY"), Info.dAlignMarkSizeY);
	xml->AddElem(_T("dAlignMarkLTX"), Info.dAlignMarkLTX);
	xml->AddElem(_T("dAlignMarkLTY"), Info.dAlignMarkLTY);
	xml->AddElem(_T("dAlignMarkRTX"), Info.dAlignMarkRTX);
	xml->AddElem(_T("dAlignMarkRTY"), Info.dAlignMarkRTY);

	xml->AddElem(_T("dDepoMarkSizeX"), Info.dDepoMarkSizeX);
	xml->AddElem(_T("dDepoMarkSizeY"), Info.dDepoMarkSizeY);
	xml->AddElem(_T("dDepoMarkLTX"), Info.dDepoMarkLTX);
	xml->AddElem(_T("dDepoMarkLTY"), Info.dDepoMarkLTY);
	xml->AddElem(_T("dDepoMarkRTX"), Info.dDepoMarkRTX);
	xml->AddElem(_T("dDepoMarkRTY"), Info.dDepoMarkRTY);

	xml->AddElem(_T("dTegSizeX"), Info.dTegSizeX);
	xml->AddElem(_T("dTegSizeY"), Info.dTegSizeY);
	xml->AddElem(_T("dTegLT1X"), Info.dTegLT1X);
	xml->AddElem(_T("dTegLT1Y"), Info.dTegLT1Y);
	xml->AddElem(_T("dTegRT2X"), Info.dTegRT2X);
	xml->AddElem(_T("dTegRT2Y"), Info.dTegRT2Y);

	xml->AddElem(_T("dSkirtPitchY"), Info.dSkirtPitchY);

	xml->AddElem(_T("dBcrPosX"), Info.dBcrPosX);
	xml->AddElem(_T("dBcrPosY"), Info.dBcrPosY);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("AtMaterialParaAlignStick Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CAtMaterialParaAlignStick::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\AtMaterialParaAlignStick.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\AtMaterialParaAlignStick.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("AtMaterialParaAlignStick")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("strID"))) 	wsprintf(Info.strID, _T("%s"), xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nOrder"))) Info.nOrder = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dSizeX"))) Info.dSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dSizeY"))) Info.dSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dPosY"))) Info.dPosY = _tstof(xml->GetData());

		if (xml->FindElem(_T("dAlignMarkSizeX"))) Info.dAlignMarkSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkSizeY"))) Info.dAlignMarkSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkLTX"))) Info.dAlignMarkLTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkLTY"))) Info.dAlignMarkLTY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkRTX"))) Info.dAlignMarkRTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dAlignMarkRTY"))) Info.dAlignMarkRTY = _tstof(xml->GetData());

		if (xml->FindElem(_T("dDepoMarkSizeX"))) Info.dDepoMarkSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkSizeY"))) Info.dDepoMarkSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkLTX"))) Info.dDepoMarkLTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkLTY"))) Info.dDepoMarkLTY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkRTX"))) Info.dDepoMarkRTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDepoMarkRTY"))) Info.dDepoMarkRTY = _tstof(xml->GetData());

		if (xml->FindElem(_T("dTegSizeX"))) Info.dTegSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegSizeY"))) Info.dTegSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegLT1X"))) Info.dTegLT1X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegLT1Y"))) Info.dTegLT1Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegRT2X"))) Info.dTegRT2X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegRT2Y"))) Info.dTegRT2Y = _tstof(xml->GetData());

		if (xml->FindElem(_T("dSkirtPitchY"))) Info.dSkirtPitchY = _tstof(xml->GetData());

		if (xml->FindElem(_T("dBcrPosX"))) Info.dBcrPosX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dBcrPosY"))) Info.dBcrPosY = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("AtMaterialParaAlignStick Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion

#pragma region //InspectionPara
void CInspectionPara::Init()
{
}
BOOL CInspectionPara::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\InspectionPara.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\InspectionPara.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("InspectionPara"));
	xml->IntoElem();

	xml->AddElem(_T("bPPAUse"), Info.bPPAUse);
	xml->AddElem(_T("bAOIUse"), Info.bAOIUse);
	xml->AddElem(_T("bAOIReviewUse"), Info.bAOIReviewUse);
	xml->AddElem(_T("nPPAAlignMethod"), Info.nPPAAlignMethod);
	xml->AddElem(_T("nEdgeAlignMethod"), Info.nEdgeAlignMethod);
	xml->AddElem(_T("nDarkThreshold"), Info.nDarkThreshold);
	xml->AddElem(_T("nBrightThreshold"), Info.nBrightThreshold);
	xml->AddElem(_T("dAOIDefectSizeMin"), Info.dAOIDefectSizeMin);
	xml->AddElem(_T("nPPAFocusType"), Info.nPPAFocusType);
	xml->AddElem(_T("nPPATrackingType"), Info.nPPATrackingType);
	xml->AddElem(_T("bInspectionStageVacuumOn"), Info.bInspectionStageVacuumOn);
	xml->AddElem(_T("bAppendixSensorUse"), Info.bAppendixSensorUse);

	xml->AddElem(_T("dInspectionStage_HoleZ"), Info.dInspectionStage_HoleZ);
	xml->AddElem(_T("dInspectionStage_HeightZ"), Info.dInspectionStage_HeightZ);

	xml->AddElem(_T("nAlignDataUseMode"), Info.nAlignDataUseMode);
	xml->AddElem(_T("nMeasureCameraMode"), Info.nMeasureCameraMode);
	xml->AddElem(_T("nStickTensionUseMode"), Info.nStickTensionUseMode);
	//xml->AddElem(_T("nMaterialParaUseMode"), Info.nMaterialParaUseMode);

	xml->AddElem(_T("bLoaderFingerUse_Stick1"), Info.bLoaderFingerUse_Stick1);
	xml->AddElem(_T("bLoaderFingerUse_Stick2"), Info.bLoaderFingerUse_Stick2);
	xml->AddElem(_T("bLoaderFingerUse_Stick3"), Info.bLoaderFingerUse_Stick3);
	xml->AddElem(_T("bLoaderFingerUse_Stick4"), Info.bLoaderFingerUse_Stick4);
	xml->AddElem(_T("bLoaderFingerUse_Stick5"), Info.bLoaderFingerUse_Stick5);
	xml->AddElem(_T("bLoaderFingerUse_Paper1"), Info.bLoaderFingerUse_Paper1);
	xml->AddElem(_T("bLoaderFingerUse_Paper2"), Info.bLoaderFingerUse_Paper2);
	xml->AddElem(_T("bLoaderFingerUse_Paper3"), Info.bLoaderFingerUse_Paper3);
	xml->AddElem(_T("bLoaderFingerUse_Paper4"), Info.bLoaderFingerUse_Paper4);
	xml->AddElem(_T("bLoaderFingerUse_Paper5"), Info.bLoaderFingerUse_Paper5);

	xml->AddElem(_T("bUnloaderFingerUse_Stick1"), Info.bUnloaderFingerUse_Stick1);
	xml->AddElem(_T("bUnloaderFingerUse_Stick2"), Info.bUnloaderFingerUse_Stick2);
	xml->AddElem(_T("bUnloaderFingerUse_Stick3"), Info.bUnloaderFingerUse_Stick3);
	xml->AddElem(_T("bUnloaderFingerUse_Stick4"), Info.bUnloaderFingerUse_Stick4);
	xml->AddElem(_T("bUnloaderFingerUse_Stick5"), Info.bUnloaderFingerUse_Stick5);

	xml->AddElem(_T("bPaperUnloaderFingerUse_1"), Info.bPaperUnloaderFingerUse_1);
	xml->AddElem(_T("bPaperUnloaderFingerUse_2"), Info.bPaperUnloaderFingerUse_2);
	xml->AddElem(_T("bPaperUnloaderFingerUse_3_4"), Info.bPaperUnloaderFingerUse_3_4);
	xml->AddElem(_T("bPaperUnloaderFingerUse_5"), Info.bPaperUnloaderFingerUse_5);
	xml->AddElem(_T("bPaperUnloaderFingerUse_6"), Info.bPaperUnloaderFingerUse_6);

	xml->AddElem(_T("bOnlyUnloadingMode"), Info.bOnlyUnloadingMode); //KJT 20210406

	xml->AddElem(_T("bMappingDataUse"), Info.bMappingDataUse);

	xml->AddElem(_T("bMeasureCornerR"), Info.bMeasureCornerR);

	xml->AddElem(_T("nAOIReviewBacklight"), Info.nAOIReviewBacklight);

	xml->AddElem(_T("bAlignDataUse"), Info.bAlignDataUse);

	xml->AddElem(_T("b3dFlowUse"), Info.b3dFlowUse);

	xml->AddElem(_T("bSWAlignFlowUse"), Info.bSWAlignFlowUse);

	xml->AddElem(_T("bTPUse"), Info.bTPUse);

	xml->AddElem(_T("bSwAlignVerifyUse"), Info.bSwAlignVerifyUse); //KJT 20210428

	xml->AddElem(_T("nAOIScanSpeedLevel"), Info.nAOIScanSpeedLevel);

	xml->AddElem(_T("nBoxStickExistType"), Info.nBoxStickExistType);
	xml->AddElem(_T("bOnlyUnloadModePreAlignUse"), Info.bOnlyUnloadModePreAlignUse);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("InspectionPara Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CInspectionPara::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\InspectionPara.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\InspectionPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("InspectionPara")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("bPPAUse"))) Info.bPPAUse = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bAOIUse"))) Info.bAOIUse = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bAOIReviewUse"))) Info.bAOIReviewUse = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPPAAlignMethod"))) Info.nPPAAlignMethod = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nEdgeAlignMethod"))) Info.nEdgeAlignMethod = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nDarkThreshold"))) Info.nDarkThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBrightThreshold"))) Info.nBrightThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dAOIDefectSizeMin"))) Info.dAOIDefectSizeMin = _tstof(xml->GetData());
		if (xml->FindElem(_T("nPPAFocusType"))) Info.nPPAFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPPATrackingType"))) Info.nPPATrackingType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bInspectionStageVacuumOn"))) Info.bInspectionStageVacuumOn = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bAppendixSensorUse"))) Info.bAppendixSensorUse = _tstoi(xml->GetData());

		if (xml->FindElem(_T("dInspectionStage_HoleZ"))) Info.dInspectionStage_HoleZ = _tstof(xml->GetData());
		if (xml->FindElem(_T("dInspectionStage_HeightZ"))) Info.dInspectionStage_HeightZ = _tstof(xml->GetData());

		if (xml->FindElem(_T("nAlignDataUseMode"))) Info.nAlignDataUseMode = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nMeasureCameraMode"))) Info.nMeasureCameraMode = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nStickTensionUseMode"))) Info.nStickTensionUseMode = _tstoi(xml->GetData());
		//if (xml->FindElem(_T("nMaterialParaUseMode"))) Info.nMaterialParaUseMode = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bLoaderFingerUse_Stick1"))) Info.bLoaderFingerUse_Stick1 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Stick2"))) Info.bLoaderFingerUse_Stick2 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Stick3"))) Info.bLoaderFingerUse_Stick3 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Stick4"))) Info.bLoaderFingerUse_Stick4 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Stick5"))) Info.bLoaderFingerUse_Stick5 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Paper1"))) Info.bLoaderFingerUse_Paper1 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Paper2"))) Info.bLoaderFingerUse_Paper2 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Paper3"))) Info.bLoaderFingerUse_Paper3 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Paper4"))) Info.bLoaderFingerUse_Paper4 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bLoaderFingerUse_Paper5"))) Info.bLoaderFingerUse_Paper5 = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bUnloaderFingerUse_Stick1"))) Info.bUnloaderFingerUse_Stick1 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bUnloaderFingerUse_Stick2"))) Info.bUnloaderFingerUse_Stick2 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bUnloaderFingerUse_Stick3"))) Info.bUnloaderFingerUse_Stick3 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bUnloaderFingerUse_Stick4"))) Info.bUnloaderFingerUse_Stick4 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bUnloaderFingerUse_Stick5"))) Info.bUnloaderFingerUse_Stick5 = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bPaperUnloaderFingerUse_1"))) Info.bPaperUnloaderFingerUse_1 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bPaperUnloaderFingerUse_2"))) Info.bPaperUnloaderFingerUse_2 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bPaperUnloaderFingerUse_3_4"))) Info.bPaperUnloaderFingerUse_3_4 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bPaperUnloaderFingerUse_5"))) Info.bPaperUnloaderFingerUse_5 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bPaperUnloaderFingerUse_6"))) Info.bPaperUnloaderFingerUse_6 = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bOnlyUnloadingMode"))) Info.bOnlyUnloadingMode = _tstoi(xml->GetData()); //KJT 20210406

		if (xml->FindElem(_T("bMappingDataUse"))) Info.bMappingDataUse = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bMeasureCornerR"))) Info.bMeasureCornerR = _tstoi(xml->GetData());

		if (xml->FindElem(_T("nAOIReviewBacklight"))) Info.nAOIReviewBacklight = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bAlignDataUse"))) Info.bAlignDataUse = _tstoi(xml->GetData());

		if (xml->FindElem(_T("b3dFlowUse"))) Info.b3dFlowUse = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bSWAlignFlowUse"))) Info.bSWAlignFlowUse = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bTPUse"))) Info.bTPUse = _tstoi(xml->GetData());

		if (xml->FindElem(_T("bSwAlignVerifyUse"))) Info.bSwAlignVerifyUse = _tstoi(xml->GetData()); //KJT 20210428

		if (xml->FindElem(_T("nAOIScanSpeedLevel"))) Info.nAOIScanSpeedLevel = _tstoi(xml->GetData());

		if (xml->FindElem(_T("nBoxStickExistType"))) Info.nBoxStickExistType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("bOnlyUnloadModePreAlignUse"))) Info.bOnlyUnloadModePreAlignUse = _tstoi(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("InspectionPara Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion

#pragma region //StretchPara
void CStretchPara::Init()
{
	int i = 0, j = 0;
	for (i = 0; i < MAX_STEP; i++)
	{
		for (j = 0; j < eGRIPPER_ROW_MAX; j++)
		{
			Info.dStretchNewton[i][j] = 0.0;
		}
	}

	for (j = 0; j < eGRIPPER_ROW_MAX; j++)
		Info.bStretchUse[j] = 0;

	Info.nStepCount = 1;
	Info.dSpeedMax = 0.1;
	Info.dSpeedMin = 0.1;
	Info.dOkRange = 1.0;
	Info.dDecelRange = 1.0;
	Info.dReleaseForce = 1.0;
	Info.dMaxForce = 1.0;
}
BOOL CStretchPara::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\StretchPara.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\StretchPara.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("StretchPara"));
	xml->IntoElem();

	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		Str.Format(_T("bStretchUse_%d"), i);
		xml->AddElem(Str, Info.bStretchUse[i]);
	}
	
	for (i = 0; i < MAX_STEP; i++)
	{
		for (j = 0; j < eGRIPPER_ROW_MAX; j++)
		{
			Str.Format(_T("dStretchNewton_%d_%d"), i, j);
			xml->AddElem(Str, Info.dStretchNewton[i][j]);
		}
	}

	xml->AddElem(_T("nStepCount"), Info.nStepCount);
	xml->AddElem(_T("dSpeedMax"), Info.dSpeedMax);
	xml->AddElem(_T("dSpeedMin"), Info.dSpeedMin);
	xml->AddElem(_T("dOkRange"), Info.dOkRange);
	xml->AddElem(_T("dDecelRange"), Info.dDecelRange);
	xml->AddElem(_T("dReleaseForce"), Info.dReleaseForce);
	xml->AddElem(_T("dMaxForce"), Info.dMaxForce);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("StretchPara Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CStretchPara::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\StretchPara.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\StretchPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("StretchPara")))
	{
		xml->IntoElem();

		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			Str.Format(_T("bStretchUse_%d"), i);
			if (xml->FindElem(Str)) Info.bStretchUse[i] = _tstoi(xml->GetData());
		}
		
		for (i = 0; i < MAX_STEP; i++)
		{
			for (j = 0; j < eGRIPPER_ROW_MAX; j++)
			{
				Str.Format(_T("dStretchNewton_%d_%d"), i, j);
				if (xml->FindElem(Str)) Info.dStretchNewton[i][j] = _tstof(xml->GetData());
			}
		}

		if (xml->FindElem(_T("nStepCount"))) Info.nStepCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dSpeedMax"))) Info.dSpeedMax = _tstof(xml->GetData());
		if (xml->FindElem(_T("dSpeedMin"))) Info.dSpeedMin = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOkRange"))) Info.dOkRange = _tstof(xml->GetData());
		if (xml->FindElem(_T("dDecelRange"))) Info.dDecelRange = _tstof(xml->GetData());
		if (xml->FindElem(_T("dReleaseForce"))) Info.dReleaseForce = _tstof(xml->GetData());
		if (xml->FindElem(_T("dMaxForce"))) Info.dMaxForce = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("StretchPara Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion

#pragma region //Glass Info
void CModelDataGlass::Init()
{
	//Info.dGlassSizeX;
	//Info.dGlassSizeY;
	//Info.dGlassHeightZ;

	//Info.dGlassAlignMarkSizeX;
	//Info.dGlassAlignMarkSizeY;

	//Info.nGlassAlignPoint; //0:2Point, 1:4Point
	//Info.nGlassAlignApplyCalibCheck;

	//Info.dGlassAlignMark_LT_X;
	//Info.dGlassAlignMark_LT_Y;
	//Info.dGlassAlignMark_RT_X;
	//Info.dGlassAlignMark_RT_Y;
	//Info.dGlassAlignMark_LB_X;
	//Info.dGlassAlignMark_LB_Y;
	//Info.dGlassAlignMark_RB_X;
	//Info.dGlassAlignMark_RB_Y;

	//Info.nVerticalPreAlignTargetCount;
	//Info.dVerticalPreAlignTargetX;
	//Info.dVerticalPreAlignTargetY;
	//Info.dVerticalPreAlignTargetT;

	//Info.nBrightnessPreAlignCoaxial;
	//Info.nBrightnessPreAlignRing;
	//Info.nBrightnessPreAlignThreshold;

	//Info.nBrightness10XCoaxial;
	//Info.nBrightness10XRing;
	//Info.nBrightness10XBackLight;
	//Info.nBrightness10XThreshold;

	//Info.nBrightness20XCoaxial;
	//Info.nBrightness20XRing;
	//Info.nBrightness20XBackLight;
	//Info.nBrightness20XThreshold;

	//Info.nBrightnessPreAlignMarkSelect;
	//Info.nBrightnessPreAlignFindSelect;

	//Info.nBrightness10XLightSelect;
	//Info.nBrightness10XMarkSelect;
	//Info.nBrightness10XFindSelect;
	//Info.nBrightness10XFocusSelect;

	//Info.nBrightness20XLightSelect;
	//Info.nBrightness20XMarkSelect;
	//Info.nBrightness20XFindSelect;
	//Info.nBrightness20XFocusSelect;
}
BOOL CModelDataGlass::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Glass.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Glass.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Glass"));
	xml->IntoElem();

	xml->AddElem(_T("dGlassSizeX"), Info.dGlassSizeX);
	xml->AddElem(_T("dGlassSizeY"), Info.dGlassSizeY);
	xml->AddElem(_T("dGlassHeightZ"), Info.dGlassHeightZ);

	xml->AddElem(_T("dGlassAlignMarkSizeX"), Info.dGlassAlignMarkSizeX);
	xml->AddElem(_T("dGlassAlignMarkSizeY"), Info.dGlassAlignMarkSizeY);

	xml->AddElem(_T("nGlassAlignPoint"), Info.nGlassAlignPoint); //0:2Point, 1:4Point
	xml->AddElem(_T("nGlassAlignApplyCalibCheck"), Info.nGlassAlignApplyCalibCheck);

	xml->AddElem(_T("dGlassAlignMark_LT_X"), Info.dGlassAlignMark_LT_X);
	xml->AddElem(_T("dGlassAlignMark_LT_Y"), Info.dGlassAlignMark_LT_Y);
	xml->AddElem(_T("dGlassAlignMark_RT_X"), Info.dGlassAlignMark_RT_X);
	xml->AddElem(_T("dGlassAlignMark_RT_Y"), Info.dGlassAlignMark_RT_Y);
	xml->AddElem(_T("dGlassAlignMark_LB_X"), Info.dGlassAlignMark_LB_X);
	xml->AddElem(_T("dGlassAlignMark_LB_Y"), Info.dGlassAlignMark_LB_Y);
	xml->AddElem(_T("dGlassAlignMark_RB_X"), Info.dGlassAlignMark_RB_X);
	xml->AddElem(_T("dGlassAlignMark_RB_Y"), Info.dGlassAlignMark_RB_Y);

	xml->AddElem(_T("nGlassMainAlignTargetCount"), Info.nGlassMainAlignTargetCount);
	xml->AddElem(_T("dGlassMainAlignTargetX"), Info.dGlassMainAlignTargetX);
	xml->AddElem(_T("dGlassMainAlignTargetY"), Info.dGlassMainAlignTargetY);
	xml->AddElem(_T("dGlassMainAlignTargetT"), Info.dGlassMainAlignTargetT);
	xml->AddElem(_T("dGlassPreAlignTargetX"), Info.dGlassPreAlignTargetX);
	xml->AddElem(_T("dGlassPreAlignTargetY"), Info.dGlassPreAlignTargetY);
	xml->AddElem(_T("dGlassPreAlignTargetT"), Info.dGlassPreAlignTargetT);

	xml->AddElem(_T("nBrightnessPreAlignCoaxial"), Info.nBrightnessPreAlignCoaxial);
	xml->AddElem(_T("nBrightnessPreAlignRing"), Info.nBrightnessPreAlignRing);
	xml->AddElem(_T("nBrightnessPreAlignThreshold"), Info.nBrightnessPreAlignThreshold);

	xml->AddElem(_T("nBrightness10XCoaxial"), Info.nBrightness10XCoaxial);
	xml->AddElem(_T("nBrightness10XRing"), Info.nBrightness10XRing);
	xml->AddElem(_T("nBrightness10XBackLight"), Info.nBrightness10XBackLight);
	xml->AddElem(_T("nBrightness10XThreshold"), Info.nBrightness10XThreshold);

	xml->AddElem(_T("nBrightness20XCoaxial"), Info.nBrightness20XCoaxial);
	xml->AddElem(_T("nBrightness20XRing"), Info.nBrightness20XRing);
	xml->AddElem(_T("nBrightness20XBackLight"), Info.nBrightness20XBackLight);
	xml->AddElem(_T("nBrightness20XThreshold"), Info.nBrightness20XThreshold);

	xml->AddElem(_T("nBrightnessPreAlignMarkSelect"), Info.nBrightnessPreAlignMarkSelect);
	xml->AddElem(_T("nBrightnessPreAlignFindSelect"), Info.nBrightnessPreAlignFindSelect);

	xml->AddElem(_T("nBrightness10XLightSelect"), Info.nBrightness10XLightSelect);
	xml->AddElem(_T("nBrightness10XMarkSelect"), Info.nBrightness10XMarkSelect);
	xml->AddElem(_T("nBrightness10XFindSelect"), Info.nBrightness10XFindSelect);
	xml->AddElem(_T("nBrightness10XFocusSelect"), Info.nBrightness10XFocusSelect);

	xml->AddElem(_T("nBrightness20XLightSelect"), Info.nBrightness20XLightSelect);
	xml->AddElem(_T("nBrightness20XMarkSelect"), Info.nBrightness20XMarkSelect);
	xml->AddElem(_T("nBrightness20XFindSelect"), Info.nBrightness20XFindSelect);
	xml->AddElem(_T("nBrightness20XFocusSelect"), Info.nBrightness20XFocusSelect);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ModelDataGlass Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CModelDataGlass::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Glass.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Glass.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Glass")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("dGlassSizeX"))) Info.dGlassSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassSizeY"))) Info.dGlassSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassHeightZ"))) Info.dGlassHeightZ = _tstof(xml->GetData());

		if (xml->FindElem(_T("dGlassAlignMarkSizeX"))) Info.dGlassAlignMarkSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassAlignMarkSizeY"))) Info.dGlassAlignMarkSizeY = _tstof(xml->GetData());

		if (xml->FindElem(_T("nGlassAlignPoint"))) Info.nGlassAlignPoint = _tstoi(xml->GetData()); //0:2Point, 1:4Point
		if (xml->FindElem(_T("nGlassAlignApplyCalibCheck"))) Info.nGlassAlignApplyCalibCheck = _tstoi(xml->GetData());

		if (xml->FindElem(_T("dGlassAlignMark_LT_X"))) Info.dGlassAlignMark_LT_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassAlignMark_LT_Y"))) Info.dGlassAlignMark_LT_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassAlignMark_RT_X"))) Info.dGlassAlignMark_RT_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassAlignMark_RT_Y"))) Info.dGlassAlignMark_RT_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassAlignMark_LB_X"))) Info.dGlassAlignMark_LB_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassAlignMark_LB_Y"))) Info.dGlassAlignMark_LB_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassAlignMark_RB_X"))) Info.dGlassAlignMark_RB_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassAlignMark_RB_Y"))) Info.dGlassAlignMark_RB_Y = _tstof(xml->GetData());

		if (xml->FindElem(_T("nGlassPreAlignTargetCount"))) Info.nGlassMainAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dGlassMainAlignTargetX"))) Info.dGlassMainAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassMainAlignTargetY"))) Info.dGlassMainAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassMainAlignTargetT"))) Info.dGlassMainAlignTargetT = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassPreAlignTargetX"))) Info.dGlassPreAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassPreAlignTargetY"))) Info.dGlassPreAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("dGlassPreAlignTargetT"))) Info.dGlassPreAlignTargetT = _tstof(xml->GetData());

		if (xml->FindElem(_T("nBrightnessPreAlignCoaxial"))) Info.nBrightnessPreAlignCoaxial = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightnessPreAlignRing"))) Info.nBrightnessPreAlignRing = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightnessPreAlignThreshold"))) Info.nBrightnessPreAlignThreshold = _tstoi(xml->GetData()); //KJT 20210727

		if (xml->FindElem(_T("nBrightness10XCoaxial"))) Info.nBrightness10XCoaxial = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness10XRing"))) Info.nBrightness10XRing = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness10XBackLight"))) Info.nBrightness10XBackLight = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness10XThreshold"))) Info.nBrightness10XThreshold = _tstoi(xml->GetData()); //KJT 20210727

		if (xml->FindElem(_T("nBrightness20XCoaxial"))) Info.nBrightness20XCoaxial = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness20XRing"))) Info.nBrightness20XRing = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness20XBackLight"))) Info.nBrightness20XBackLight = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness20XThreshold"))) Info.nBrightness20XThreshold = _tstoi(xml->GetData()); //KJT 20210727

		if (xml->FindElem(_T("nBrightnessPreAlignMarkSelect"))) Info.nBrightnessPreAlignMarkSelect = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightnessPreAlignFindSelect"))) Info.nBrightnessPreAlignFindSelect = _tstoi(xml->GetData()); //KJT 20210727

		if (xml->FindElem(_T("nBrightness10XLightSelect"))) Info.nBrightness10XLightSelect = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness10XMarkSelect"))) Info.nBrightness10XMarkSelect = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness10XFindSelect"))) Info.nBrightness10XFindSelect = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness10XFocusSelect"))) Info.nBrightness10XFocusSelect = _tstoi(xml->GetData()); //KJT 20210727

		if (xml->FindElem(_T("nBrightness20XLightSelect"))) Info.nBrightness20XLightSelect = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness20XMarkSelect"))) Info.nBrightness20XMarkSelect = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness20XFindSelect"))) Info.nBrightness20XFindSelect = _tstoi(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("nBrightness20XFocusSelect"))) Info.nBrightness20XFocusSelect = _tstoi(xml->GetData()); //KJT 20210727

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ModelDataGlass Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion


#pragma region //Align Para Info
void CModelDataAlign::Init()
{
	////Box Left Align
	Info.nBoxAlignLeftTargetCount = 10;
	Info.dBoxAlignLeftTargetX = 0.0;
	Info.dBoxAlignLeftTargetY = 0.0;
	Info.nBoxAlignLeftCoAxial = 0;
	Info.nBoxAlignLeftRing = 40;
	Info.nBoxAlignLeftThreshold = 200;
	Info.nBoxAlignLeftLightType = eLight_Front;
	Info.nBoxAlignLeftMarkType = eMark_Pattern;
	Info.nBoxAlignLeftFocusType = eFocusType_None;
	Info.nBoxAlignLeftBlackWhiteType = eBlack;

	////Box Align Right
	Info.nBoxAlignRightTargetCount = 10;
	Info.dBoxAlignRightTargetX = 0.0;
	Info.dBoxAlignRightTargetY = 0.0;
	Info.nBoxAlignRightCoAxial = 0;
	Info.nBoxAlignRightRing = 40;
	Info.nBoxAlignRightThreshold = 200;
	Info.nBoxAlignRightLightType = eLight_Front;
	Info.nBoxAlignRightMarkType = eMark_Pattern;
	Info.nBoxAlignRightFocusType = eFocusType_None;
	Info.nBoxAlignRightBlackWhiteType = eBlack;

	////Pre Align
	Info.nPreAlignTargetCount = 10;
	Info.dPreAlignTargetX = 0.25;
	Info.dPreAlignTargetY = 0.002;
	Info.nPreAlignCoAxial_L = 27;
	Info.nPreAlignRing_L = 70;
	Info.nPreAlignThreshold_L = 110;
	Info.nPreAlignCoAxial_R = 27;
	Info.nPreAlignRing_R = 70;
	Info.nPreAlignThreshold_R = 110;
	Info.nPreAlignLightType = eLight_Front;
	Info.nPreAlignMarkType = eMark_Blob;
	Info.nPreAlignFocusType = eFocusType_Image;
	Info.nPreAlignBlackWhiteType = eBlack;

	////Main 2P Align
	Info.nMain2PAlignTargetCount = 20;
	Info.dMain2PAlignTargetX = 0.0;
	Info.dMain2PAlignTargetY = 0.0;
	Info.nMain2PAlignCoAxial = 25;
	Info.nMain2PAlignRing = 0;
	Info.nMain2PAlignThreshold = 100;
	Info.nMain2PAlignBackLight = 20;
	Info.nMain2PAlignLightType = eLight_Front;
	Info.nMain2PAlignMarkType = eMark_Blob;
	Info.nMain2PAlignFocusType = eFocusType_Both;
	Info.nMain2PAlignBlackWhiteType = eBlack;

	////Edge 4P Align
	Info.nEdge4PAlignTargetCount = 20;
	Info.dEdge4PAlignTargetX = 0.0;
	Info.dEdge4PAlignTargetY = 0.0;
	Info.nEdge4PAlignCoAxial = 0;
	Info.nEdge4PAlignRing = 0;
	Info.nEdge4PAlignThreshold = 150;
	Info.nEdge4PAlignLightType = eLight_Front;
	Info.nEdge4PAlignMarkType = eMark_Blob;
	Info.nEdge4PAlignFocusType = eFocusType_Both;
	Info.nEdge4PAlignBlackWhiteType =  eWhite;
	Info.nEdge4PAlignBacklight = 100;

	////Vertical Pre Align
	Info.nVerticalPreAlignTargetCount = 10;
	Info.dVerticalPreAlignTargetX = 0.003;
	Info.dVerticalPreAlignTargetY = 0.003;
	Info.nVerticalPreAlignCoAxial = 25;
	Info.nVerticalPreAlignRing = 0;
	Info.nVerticalPreAlignThreshold = 150;
	Info.nVerticalPreAlignBackLight = 10;
	Info.nVerticalPreAlignLightType = eLight_Front;
	Info.nVerticalPreAlignMarkType = eMark_Blob;
	Info.nVerticalPreAlignFocusType = eFocusType_Both;
	Info.nVerticalPreAlignBlackWhiteType = eWhite;

	//Vertical Main Align
	Info.nVerticalMainAlignTargetCount = 20;
	Info.dVerticalMainAlignTargetX = 0.001;
	Info.dVerticalMainAlignTargetY = 0.004;
	Info.nVerticalMainAlignCoAxial = 25;
	Info.nVerticalMainAlignRing = 0;
	Info.nVerticalMainAlignThreshold = 150;
	Info.nVerticalMainAlignBackLight = 10;
	Info.nVerticalMainAlignLightType = eLight_Front;
	Info.nVerticalMainAlignMarkType = eMark_Blob;
	Info.nVerticalMainAlignFocusType = eFocusType_Both;
	Info.nVerticalMainAlignBlackWhiteType = eWhite;
}
BOOL CModelDataAlign::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\AlignPara.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\AlignPara.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("AlignPara"));
	xml->IntoElem();

	//Box Left Align
	xml->AddElem(_T("nBoxAlignLeftTargetCount"), Info.nBoxAlignLeftTargetCount);
	xml->AddElem(_T("dBoxAlignLeftTargetX"), Info.dBoxAlignLeftTargetX);
	xml->AddElem(_T("dBoxAlignLeftTargetY"), Info.dBoxAlignLeftTargetY);
	xml->AddElem(_T("nBoxAlignLeftCoAxial"), Info.nBoxAlignLeftCoAxial);
	xml->AddElem(_T("nBoxAlignLeftRing"), Info.nBoxAlignLeftRing);
	xml->AddElem(_T("nBoxAlignLeftThreshold"), Info.nBoxAlignLeftThreshold);
	xml->AddElem(_T("nBoxAlignLeftLightType"), Info.nBoxAlignLeftLightType);
	xml->AddElem(_T("nBoxAlignLeftMarkType"), Info.nBoxAlignLeftMarkType);
	xml->AddElem(_T("nBoxAlignLeftFocusType"), Info.nBoxAlignLeftFocusType);
	xml->AddElem(_T("nBoxAlignLeftBlackWhiteType"), Info.nBoxAlignLeftBlackWhiteType);

	//Box Align Right
	xml->AddElem(_T("nBoxAlignRightTargetCount"), Info.nBoxAlignRightTargetCount);
	xml->AddElem(_T("dBoxAlignRightTargetX"), Info.dBoxAlignRightTargetX);
	xml->AddElem(_T("dBoxAlignRightTargetY"), Info.dBoxAlignRightTargetY);
	xml->AddElem(_T("nBoxAlignRightCoAxial"), Info.nBoxAlignRightCoAxial);
	xml->AddElem(_T("nBoxAlignRightRing"), Info.nBoxAlignRightRing);
	xml->AddElem(_T("nBoxAlignRightThreshold"), Info.nBoxAlignRightThreshold);
	xml->AddElem(_T("nBoxAlignRightLightType"), Info.nBoxAlignRightLightType);
	xml->AddElem(_T("nBoxAlignRightMarkType"), Info.nBoxAlignRightMarkType);
	xml->AddElem(_T("nBoxAlignRightFocusType"), Info.nBoxAlignRightFocusType);
	xml->AddElem(_T("nBoxAlignRightBlackWhiteType"), Info.nBoxAlignRightBlackWhiteType);

	//Pre Align
	xml->AddElem(_T("nPreAlignTargetCount"), Info.nPreAlignTargetCount);
	xml->AddElem(_T("dPreAlignTargetX"), Info.dPreAlignTargetX);
	xml->AddElem(_T("dPreAlignTargetY"), Info.dPreAlignTargetY);
	xml->AddElem(_T("nPreAlignCoAxial_L"), Info.nPreAlignCoAxial_L);
	xml->AddElem(_T("nPreAlignRing_L"), Info.nPreAlignRing_L);
	xml->AddElem(_T("nPreAlignThreshold_L"), Info.nPreAlignThreshold_L);
	xml->AddElem(_T("nPreAlignCoAxial_R"), Info.nPreAlignCoAxial_R);
	xml->AddElem(_T("nPreAlignRing_R"), Info.nPreAlignRing_R);
	xml->AddElem(_T("nPreAlignThreshold_R"), Info.nPreAlignThreshold_R);
	xml->AddElem(_T("nPreAlignLightType"), Info.nPreAlignLightType);
	xml->AddElem(_T("nPreAlignMarkType"), Info.nPreAlignMarkType);
	xml->AddElem(_T("nPreAlignFocusType"), Info.nPreAlignFocusType);
	xml->AddElem(_T("nPreAlignBlackWhiteType"), Info.nPreAlignBlackWhiteType);
	
	//Main 2P Align
	xml->AddElem(_T("nMain2PAlignTargetCount"), Info.nMain2PAlignTargetCount);
	xml->AddElem(_T("dMain2PAlignTargetX"), Info.dMain2PAlignTargetX);
	xml->AddElem(_T("dMain2PAlignTargetY"), Info.dMain2PAlignTargetY);
	xml->AddElem(_T("nMain2PAlignCoAxial"), Info.nMain2PAlignCoAxial);
	xml->AddElem(_T("nMain2PAlignRing"), Info.nMain2PAlignRing);
	xml->AddElem(_T("nMain2PAlignThreshold"), Info.nMain2PAlignThreshold);
	xml->AddElem(_T("nMain2PAlignBackLight"), Info.nMain2PAlignBackLight);
	xml->AddElem(_T("nMain2PAlignLightType"), Info.nMain2PAlignLightType);
	xml->AddElem(_T("nMain2PAlignMarkType"), Info.nMain2PAlignMarkType);
	xml->AddElem(_T("nMain2PAlignFocusType"), Info.nMain2PAlignFocusType);
	xml->AddElem(_T("nMain2PAlignBlackWhiteType"), Info.nMain2PAlignBlackWhiteType);
	
	//Edge 4P Align
	xml->AddElem(_T("nEdge4PAlignTargetCount"), Info.nEdge4PAlignTargetCount);
	xml->AddElem(_T("dEdge4PAlignTargetX"), Info.dEdge4PAlignTargetX);
	xml->AddElem(_T("dEdge4PAlignTargetY"), Info.dEdge4PAlignTargetY);
	xml->AddElem(_T("nEdge4PAlignCoAxial"), Info.nEdge4PAlignCoAxial);
	xml->AddElem(_T("nEdge4PAlignRing"), Info.nEdge4PAlignRing);
	xml->AddElem(_T("nEdge4PAlignThreshold"), Info.nEdge4PAlignThreshold);
	xml->AddElem(_T("nEdge4PAlignLightType"), Info.nEdge4PAlignLightType);
	xml->AddElem(_T("nEdge4PAlignMarkType"), Info.nEdge4PAlignMarkType);
	xml->AddElem(_T("nEdge4PAlignFocusType"), Info.nEdge4PAlignFocusType);
	xml->AddElem(_T("nEdge4PAlignBlackWhiteType"), Info.nEdge4PAlignBlackWhiteType);
	xml->AddElem(_T("nEdge4PAlignBacklight"), Info.nEdge4PAlignBacklight);
	
	//Tegkey Align
	xml->AddElem(_T("nTegkeyAlignTargetCount"), Info.nTegkeyAlignTargetCount);
	xml->AddElem(_T("dTegkeyAlignTargetX"), Info.dTegkeyAlignTargetX);
	xml->AddElem(_T("dTegkeyAlignTargetY"), Info.dTegkeyAlignTargetY);
	xml->AddElem(_T("nTegkeyAlignCoAxial"), Info.nTegkeyAlignCoAxial);
	xml->AddElem(_T("nTegkeyAlignRing"), Info.nTegkeyAlignRing);
	xml->AddElem(_T("nTegkeyAlignThreshold"), Info.nTegkeyAlignThreshold);
	xml->AddElem(_T("nTegkeyAlignLightType"), Info.nTegkeyAlignLightType);
	xml->AddElem(_T("nTegkeyAlignMarkType"), Info.nTegkeyAlignMarkType);
	xml->AddElem(_T("nTegkeyAlignFocusType"), Info.nTegkeyAlignFocusType);
	xml->AddElem(_T("nTegkeyAlignBlackWhiteType"), Info.nTegkeyAlignBlackWhiteType);
	xml->AddElem(_T("nTegkeyAlignBacklight"), Info.nTegkeyAlignBacklight);

	//Vertical Pre Align
	xml->AddElem(_T("nVerticalPreAlignTargetCount"), Info.nVerticalPreAlignTargetCount);
	xml->AddElem(_T("dVerticalPreAlignTargetX"), Info.dVerticalPreAlignTargetX);
	xml->AddElem(_T("dVerticalPreAlignTargetY"), Info.dVerticalPreAlignTargetY);
	xml->AddElem(_T("nVerticalPreAlignCoAxial"), Info.nVerticalPreAlignCoAxial);
	xml->AddElem(_T("nVerticalPreAlignRing"), Info.nVerticalPreAlignRing);
	xml->AddElem(_T("nVerticalPreAlignThreshold"), Info.nVerticalPreAlignThreshold);
	xml->AddElem(_T("nVerticalPreAlignBackLight"), Info.nVerticalPreAlignBackLight);
	xml->AddElem(_T("nVerticalPreAlignLightType"), Info.nVerticalPreAlignLightType);
	xml->AddElem(_T("nVerticalPreAlignMarkType"), Info.nVerticalPreAlignMarkType);
	xml->AddElem(_T("nVerticalPreAlignFocusType"), Info.nVerticalPreAlignFocusType);
	xml->AddElem(_T("nVerticalPreAlignBlackWhiteType"), Info.nVerticalPreAlignBlackWhiteType);
	
	//Vertical Main Align
	xml->AddElem(_T("nVerticalMainAlignTargetCount"), Info.nVerticalMainAlignTargetCount);
	xml->AddElem(_T("dVerticalMainAlignTargetX"), Info.dVerticalMainAlignTargetX);
	xml->AddElem(_T("dVerticalMainAlignTargetY"), Info.dVerticalMainAlignTargetY);
	xml->AddElem(_T("nVerticalMainAlignCoAxial"), Info.nVerticalMainAlignCoAxial);
	xml->AddElem(_T("nVerticalMainAlignRing"), Info.nVerticalMainAlignRing);
	xml->AddElem(_T("nVerticalMainAlignThreshold"), Info.nVerticalMainAlignThreshold);
	xml->AddElem(_T("nVerticalMainAlignBackLight"), Info.nVerticalMainAlignBackLight);
	xml->AddElem(_T("nVerticalMainAlignLightType"), Info.nVerticalMainAlignLightType);
	xml->AddElem(_T("nVerticalMainAlignMarkType"), Info.nVerticalMainAlignMarkType);
	xml->AddElem(_T("nVerticalMainAlignFocusType"), Info.nVerticalMainAlignFocusType);
	xml->AddElem(_T("nVerticalMainAlignBlackWhiteType"), Info.nVerticalMainAlignBlackWhiteType);

	//Sw Align //KJT 20210307
	xml->AddElem(_T("nSwAlignTargetCount"), Info.nSwAlignTargetCount);
	xml->AddElem(_T("dSwAlignTargetX"), Info.dSwAlignTargetX);
	xml->AddElem(_T("dSwAlignTargetY"), Info.dSwAlignTargetY);
	xml->AddElem(_T("nSwAlignCoAxial"), Info.nSwAlignCoAxial);
	xml->AddElem(_T("nSwAlignRing"), Info.nSwAlignRing);
	xml->AddElem(_T("nSwAlignThreshold"), Info.nSwAlignThreshold);
	xml->AddElem(_T("nSwAlignLightType"), Info.nSwAlignLightType);
	xml->AddElem(_T("nSwAlignMarkType"), Info.nSwAlignMarkType);
	xml->AddElem(_T("nSwAlignFocusType"), Info.nSwAlignFocusType);
	xml->AddElem(_T("nSwAlignBlackWhiteType"), Info.nSwAlignBlackWhiteType);
	xml->AddElem(_T("nSwAlignBacklight"), Info.nSwAlignBacklight);

	//Measure TP
	for (i = 0; i < 3; i++) //KJT 20210824
	{
		Str.Format(_T("nTPCoAxial_%d"), i);
		xml->AddElem(Str, Info.nTPCoAxial[i]);
		Str.Format(_T("nTPRing_%d"), i);
		xml->AddElem(Str, Info.nTPRing[i]);
		Str.Format(_T("nTPThreshold_%d"), i);
		xml->AddElem(Str, Info.nTPThreshold[i]);
		Str.Format(_T("nTPBacklight_%d"), i);
		xml->AddElem(Str, Info.nTPBacklight[i]);
	}
	xml->AddElem(_T("nTPLightType"), Info.nTPLightType);
	xml->AddElem(_T("nTPMarkType"), Info.nTPMarkType);
	xml->AddElem(_T("nTPFocusType"), Info.nTPFocusType);
	xml->AddElem(_T("nTPBlackWhiteType"), Info.nTPBlackWhiteType);

	//x20 light ratio
	xml->AddElem(_T("dx20CoAxialScale"), Info.dx20CoAxialScale);
	xml->AddElem(_T("dx20RingScale"), Info.dx20RingScale);
	xml->AddElem(_T("dx20BackLightScale"), Info.dx20BackLightScale);

	xml->AddElem(_T("dx50CoAxialScale"), Info.dx50CoAxialScale);
	xml->AddElem(_T("dx50RingScale"), Info.dx50RingScale);
	xml->AddElem(_T("dx50BackLightScale"), Info.dx50BackLightScale);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ModelDataAlignPara Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CModelDataAlign::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\AlignPara.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\AlignPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("AlignPara")))
	{
		xml->IntoElem();

		//Box Left Align
		if (xml->FindElem(_T("nBoxAlignLeftTargetCount"))) Info.nBoxAlignLeftTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dBoxAlignLeftTargetX"))) Info.dBoxAlignLeftTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dBoxAlignLeftTargetY"))) Info.dBoxAlignLeftTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignLeftCoAxial"))) Info.nBoxAlignLeftCoAxial = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignLeftRing"))) Info.nBoxAlignLeftRing = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignLeftThreshold"))) Info.nBoxAlignLeftThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignLeftLightType"))) Info.nBoxAlignLeftLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignLeftMarkType"))) Info.nBoxAlignLeftMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignLeftFocusType"))) Info.nBoxAlignLeftFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignLeftBlackWhiteType"))) Info.nBoxAlignLeftBlackWhiteType = _tstoi(xml->GetData());

		//Box Align Right
		if (xml->FindElem(_T("nBoxAlignRightTargetCount"))) Info.nBoxAlignRightTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dBoxAlignRightTargetX"))) Info.dBoxAlignRightTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dBoxAlignRightTargetY"))) Info.dBoxAlignRightTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignRightCoAxial"))) Info.nBoxAlignRightCoAxial = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignRightRing"))) Info.nBoxAlignRightRing = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignRightThreshold"))) Info.nBoxAlignRightThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignRightLightType"))) Info.nBoxAlignRightLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignRightMarkType"))) Info.nBoxAlignRightMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignRightFocusType"))) Info.nBoxAlignRightFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nBoxAlignRightBlackWhiteType"))) Info.nBoxAlignRightBlackWhiteType = _tstoi(xml->GetData());

		//Pre Align
		if (xml->FindElem(_T("nPreAlignTargetCount"))) Info.nPreAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dPreAlignTargetX"))) Info.dPreAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dPreAlignTargetY"))) Info.dPreAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nPreAlignCoAxial_L"))) Info.nPreAlignCoAxial_L = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignRing_L"))) Info.nPreAlignRing_L = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignThreshold_L"))) Info.nPreAlignThreshold_L = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignCoAxial_R"))) Info.nPreAlignCoAxial_R = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignRing_R"))) Info.nPreAlignRing_R = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignThreshold_R"))) Info.nPreAlignThreshold_R = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignLightType"))) Info.nPreAlignLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignMarkType"))) Info.nPreAlignMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignFocusType"))) Info.nPreAlignFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPreAlignBlackWhiteType"))) Info.nPreAlignBlackWhiteType = _tstoi(xml->GetData());

		//Main 2P Align
		if (xml->FindElem(_T("nMain2PAlignTargetCount"))) Info.nMain2PAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dMain2PAlignTargetX"))) Info.dMain2PAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dMain2PAlignTargetY"))) Info.dMain2PAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nMain2PAlignCoAxial"))) Info.nMain2PAlignCoAxial = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nMain2PAlignRing"))) Info.nMain2PAlignRing = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nMain2PAlignThreshold"))) Info.nMain2PAlignThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nMain2PAlignBackLight"))) Info.nMain2PAlignBackLight = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nMain2PAlignLightType"))) Info.nMain2PAlignLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nMain2PAlignMarkType"))) Info.nMain2PAlignMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nMain2PAlignFocusType"))) Info.nMain2PAlignFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nMain2PAlignBlackWhiteType"))) Info.nMain2PAlignBlackWhiteType = _tstoi(xml->GetData());

		//Edge 4P Align
		if (xml->FindElem(_T("nEdge4PAlignTargetCount"))) Info.nEdge4PAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dEdge4PAlignTargetX"))) Info.dEdge4PAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dEdge4PAlignTargetY"))) Info.dEdge4PAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nEdge4PAlignCoAxial"))) Info.nEdge4PAlignCoAxial = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nEdge4PAlignRing"))) Info.nEdge4PAlignRing = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nEdge4PAlignThreshold"))) Info.nEdge4PAlignThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nEdge4PAlignLightType"))) Info.nEdge4PAlignLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nEdge4PAlignMarkType"))) Info.nEdge4PAlignMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nEdge4PAlignFocusType"))) Info.nEdge4PAlignFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nEdge4PAlignBlackWhiteType"))) Info.nEdge4PAlignBlackWhiteType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nEdge4PAlignBacklight"))) Info.nEdge4PAlignBacklight = _tstoi(xml->GetData());

		//Tegkey Align
		if (xml->FindElem(_T("nTegkeyAlignTargetCount"))) Info.nTegkeyAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dTegkeyAlignTargetX"))) Info.dTegkeyAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dTegkeyAlignTargetY"))) Info.dTegkeyAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nTegkeyAlignCoAxial"))) Info.nTegkeyAlignCoAxial = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTegkeyAlignRing"))) Info.nTegkeyAlignRing = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTegkeyAlignThreshold"))) Info.nTegkeyAlignThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTegkeyAlignLightType"))) Info.nTegkeyAlignLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTegkeyAlignMarkType"))) Info.nTegkeyAlignMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTegkeyAlignFocusType"))) Info.nTegkeyAlignFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTegkeyAlignBlackWhiteType"))) Info.nTegkeyAlignBlackWhiteType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTegkeyAlignBacklight"))) Info.nTegkeyAlignBacklight = _tstoi(xml->GetData());

		//Vertical Pre Align
		if (xml->FindElem(_T("nVerticalPreAlignTargetCount"))) Info.nVerticalPreAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dVerticalPreAlignTargetX"))) Info.dVerticalPreAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dVerticalPreAlignTargetY"))) Info.dVerticalPreAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nVerticalPreAlignCoAxial"))) Info.nVerticalPreAlignCoAxial = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalPreAlignRing"))) Info.nVerticalPreAlignRing = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalPreAlignThreshold"))) Info.nVerticalPreAlignThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalPreAlignBackLight"))) Info.nVerticalPreAlignBackLight = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalPreAlignLightType"))) Info.nVerticalPreAlignLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalPreAlignMarkType"))) Info.nVerticalPreAlignMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalPreAlignFocusType"))) Info.nVerticalPreAlignFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalPreAlignBlackWhiteType"))) Info.nVerticalPreAlignBlackWhiteType = _tstoi(xml->GetData());

		//Vertical Main Align
		if (xml->FindElem(_T("nVerticalMainAlignTargetCount"))) Info.nVerticalMainAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dVerticalMainAlignTargetX"))) Info.dVerticalMainAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dVerticalMainAlignTargetY"))) Info.dVerticalMainAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nVerticalMainAlignCoAxial"))) Info.nVerticalMainAlignCoAxial = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalMainAlignRing"))) Info.nVerticalMainAlignRing = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalMainAlignThreshold"))) Info.nVerticalMainAlignThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalMainAlignBackLight"))) Info.nVerticalMainAlignBackLight = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalMainAlignLightType"))) Info.nVerticalMainAlignLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalMainAlignMarkType"))) Info.nVerticalMainAlignMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalMainAlignFocusType"))) Info.nVerticalMainAlignFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nVerticalMainAlignBlackWhiteType"))) Info.nVerticalMainAlignBlackWhiteType = _tstoi(xml->GetData());

		//Sw Align //KJT 20210307
		if (xml->FindElem(_T("nSwAlignTargetCount"))) Info.nSwAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dSwAlignTargetX"))) Info.dSwAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dSwAlignTargetY"))) Info.dSwAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("nSwAlignCoAxial"))) Info.nSwAlignCoAxial = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nSwAlignRing"))) Info.nSwAlignRing = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nSwAlignThreshold"))) Info.nSwAlignThreshold = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nSwAlignLightType"))) Info.nSwAlignLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nSwAlignMarkType"))) Info.nSwAlignMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nSwAlignFocusType"))) Info.nSwAlignFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nSwAlignBlackWhiteType"))) Info.nSwAlignBlackWhiteType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nSwAlignBacklight"))) Info.nSwAlignBacklight = _tstoi(xml->GetData());

		//Measure TP
		for (i = 0; i < 3; i++) //KJT 20210824
		{
			Str.Format(_T("nTPCoAxial_%d"), i);
			if (xml->FindElem(Str)) Info.nTPCoAxial[i] = _tstoi(xml->GetData());
			Str.Format(_T("nTPRing_%d"), i);
			if (xml->FindElem(Str)) Info.nTPRing[i] = _tstoi(xml->GetData());
			Str.Format(_T("nTPThreshold_%d"), i);
			if (xml->FindElem(Str)) Info.nTPThreshold[i] = _tstoi(xml->GetData());
			Str.Format(_T("nTPBacklight_%d"), i);
			if (xml->FindElem(Str)) Info.nTPBacklight[i] = _tstoi(xml->GetData());
		}
		if (xml->FindElem(_T("nTPLightType"))) Info.nTPLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTPMarkType"))) Info.nTPMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTPFocusType"))) Info.nTPFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nTPBlackWhiteType"))) Info.nTPBlackWhiteType = _tstoi(xml->GetData());
		
		//x20 light scale
		if (xml->FindElem(_T("dx20CoAxialScale"))) Info.dx20CoAxialScale = _tstof(xml->GetData());
		if (xml->FindElem(_T("dx20RingScale"))) Info.dx20RingScale = _tstof(xml->GetData());
		if (xml->FindElem(_T("dx20BackLightScale"))) Info.dx20BackLightScale = _tstof(xml->GetData());
		//x50 light scale
		if (xml->FindElem(_T("dx50CoAxialScale"))) Info.dx50CoAxialScale = _tstof(xml->GetData());
		if (xml->FindElem(_T("dx50RingScale"))) Info.dx50RingScale = _tstof(xml->GetData());
		if (xml->FindElem(_T("dx50BackLightScale"))) Info.dx50BackLightScale = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ModelDataAlignPara Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion

#pragma region //ModelSubManual Para Info
void CModelDataManual::Init()
{
	Info.dStickLoaderX_AlignPos = 0.0;
	Info.dStickLoaderX_PickUpPos = 0.0;
	Info.dStickUnloaderX_PickUpPos = 0.0;
	Info.dPaperUnloaderX_PickUpPos = 0.0;
}
BOOL CModelDataManual::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\ModelSubManualPara.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\ModelSubManualPara.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("ModelSubManualPara"));
	xml->IntoElem();

	xml->AddElem(_T("dStickLoaderX_AlignPos"), Info.dStickLoaderX_AlignPos);
	xml->AddElem(_T("dStickLoaderX_PickUpPos"), Info.dStickLoaderX_PickUpPos);
	xml->AddElem(_T("dStickUnloaderX_PickUpPos"), Info.dStickUnloaderX_PickUpPos);
	xml->AddElem(_T("dPaperUnloaderX_PickUpPos"), Info.dPaperUnloaderX_PickUpPos);
	
	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ModelDataManualPara Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CModelDataManual::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\ModelSubManualPara.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\ModelSubManualPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("ModelSubManualPara")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("dStickLoaderX_AlignPos"))) Info.dStickLoaderX_AlignPos = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dStickLoaderX_PickUpPos"))) Info.dStickLoaderX_PickUpPos = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dStickUnloaderX_PickUpPos"))) Info.dStickUnloaderX_PickUpPos = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dPaperUnloaderX_PickUpPos"))) Info.dPaperUnloaderX_PickUpPos = _tstoi(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ModelDataManualPara Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion

#pragma region //PPA Para Info
void CModelDataPpa::Init()
{
	int i = 0;

	////PPA
	Info.nPpaTargetCount = 10;
	Info.dPpaTargetX = 0.0;
	Info.dPpaTargetY = 0.0;
	for (i = 0; i < 3; i++) //KJT 20210824
	{
		Info.nPpaCoAxial[i] = 0;
		Info.nPpaRing[i] = 0;
		Info.nPpaThreshold[i] = 100;
		Info.nPpaBacklight[i] = 10;
	}
	Info.nPpaLightType = eLight_Front;
	Info.nPpaMarkType = eMark_Blob;
	Info.nPpaFocusType = eFocusType_Both;
	Info.nPpaBlackWhiteType = eWhite;

	//KJT 20210525
	Info.nDivX = eDiv_3;
	Info.nDivY = eDiv_3;
	Info.nSlotQuantityXY = eQuantity_3X3;
}
BOOL CModelDataPpa::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\PpaPara.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else//xml
	szFilePath.AppendFormat(_T("\\PpaPara.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("PpaPara"));
	xml->IntoElem();

	//PPA
	xml->AddElem(_T("nPpaTargetCount"), Info.nPpaTargetCount);
	xml->AddElem(_T("dPpaTargetX"), Info.dPpaTargetX);
	xml->AddElem(_T("dPpaTargetY"), Info.dPpaTargetY);
	for (i = 0; i < 3; i++) //KJT 20210824
	{
		Str.Format(_T("nPpaCoAxial_%d"), i);
		xml->AddElem(Str, Info.nPpaCoAxial[i]);
		Str.Format(_T("nPpaRing_%d"), i);
		xml->AddElem(Str, Info.nPpaRing[i]);
		Str.Format(_T("nPpaThreshold_%d"), i);
		xml->AddElem(Str, Info.nPpaThreshold[i]);
		Str.Format(_T("nPpaBacklight_%d"), i);
		xml->AddElem(Str, Info.nPpaBacklight[i]);
	}

	xml->AddElem(_T("nPpaLightType"), Info.nPpaLightType);
	xml->AddElem(_T("nPpaMarkType"), Info.nPpaMarkType);
	xml->AddElem(_T("nPpaFocusType"), Info.nPpaFocusType);
	xml->AddElem(_T("nPpaBlackWhiteType"), Info.nPpaBlackWhiteType);

	//KJT 20210525
	xml->AddElem(_T("nDivX"), Info.nDivX);
	xml->AddElem(_T("nDivY"), Info.nDivY);
	xml->AddElem(_T("nSlotQuantityXY"), Info.nSlotQuantityXY);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ModelDataPpaPara Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CModelDataPpa::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Model"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\"));
	szFilePath.AppendFormat(SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\PpaPara.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(Info));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\PpaPara.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("PpaPara")))
	{
		xml->IntoElem();

		//PPA
		if (xml->FindElem(_T("nPpaTargetCount"))) Info.nPpaTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("dPpaTargetX"))) Info.dPpaTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dPpaTargetY"))) Info.dPpaTargetY = _tstof(xml->GetData());

		for (i = 0; i < 3; i++) //KJT 20210824
		{
			Str.Format(_T("nPpaCoAxial_%d"), i);
			if (xml->FindElem(Str)) Info.nPpaCoAxial[i] = _tstoi(xml->GetData());
			Str.Format(_T("nPpaRing_%d"), i);
			if (xml->FindElem(Str)) Info.nPpaRing[i] = _tstoi(xml->GetData());
			Str.Format(_T("nPpaThreshold_%d"), i);
			if (xml->FindElem(Str)) Info.nPpaThreshold[i] = _tstoi(xml->GetData());
			Str.Format(_T("nPpaBacklight_%d"), i);
			if (xml->FindElem(Str)) Info.nPpaBacklight[i] = _tstoi(xml->GetData());
		}

		if (xml->FindElem(_T("nPpaLightType"))) Info.nPpaLightType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPpaMarkType"))) Info.nPpaMarkType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPpaFocusType"))) Info.nPpaFocusType = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nPpaBlackWhiteType"))) Info.nPpaBlackWhiteType = _tstoi(xml->GetData());

		//KJT 20210525
		if (xml->FindElem(_T("nDivX"))) Info.nDivX = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nDivY"))) Info.nDivY = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nSlotQuantityXY"))) Info.nSlotQuantityXY = _tstoi(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ModelDataPpaPara Load Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
#pragma endregion

CModelData::CModelData()
{

}
//-------------------------------------------------------
CModelData::~CModelData()
{

}
//-------------------------------------------------------
void CModelData::Initialize(void)
{
	m_MaterialPara.Init();
	m_AtMaterialPara.Init();
	m_MaterialParaAlignStick.Init();
	m_AtMaterialParaAlignStick.Init();
	m_InspectionPara.Init();
	m_StretchPara.Init();
	m_GlassPara.Init();
	m_AlignPara.Init();
	m_ModelSubManualPara.Init();
	m_PpaPara.Init();
}
//-------------------------------------------------------
void CModelData::Finalize(void)
{

}
//-------------------------------------------------------
void CModelData::Save()
//-------------------------------------------------------
{
	m_MaterialPara.Save();
	m_AtMaterialPara.Save();
	m_MaterialParaAlignStick.Save();
	m_AtMaterialParaAlignStick.Save();
	m_InspectionPara.Save();
	m_StretchPara.Save();
	m_GlassPara.Save();
	m_AlignPara.Save();
	m_ModelSubManualPara.Save();
	m_PpaPara.Save();
}
//-------------------------------------------------------
void CModelData::Load()
{
	Initialize();

	m_MaterialPara.Load();
	m_AtMaterialPara.Load();
	m_MaterialParaAlignStick.Load();
	m_AtMaterialParaAlignStick.Load();
	m_InspectionPara.Load();
	m_StretchPara.Load();
	m_GlassPara.Load();
	m_AlignPara.Load();
	m_ModelSubManualPara.Load();
	m_PpaPara.Load();
}
//-------------------------------------------------------