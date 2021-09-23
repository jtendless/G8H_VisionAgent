#include "stdafx.h"
#include "SystemData.h"
#include "Log/Logger.h"
#include "Vision/SharedInfo.h"
#include "Data/XmlFile.h"

CSystemDataSafety		CSystemData::m_Safety;
CSystemDataOption		CSystemData::m_Option;
CSystemDataCoordinate	CSystemData::m_Coordinate;
CSystemDataOther		CSystemData::m_Other; //KJT 20210329
CSystemDataStage		CSystemData::m_Stage;
CSystemDataCameraCal	CSystemData::m_CameraCal; //KJT 20210524
//-------------------------------------------------------------------
CSystemData::CSystemData()
{

}
//-------------------------------------------------------------------
CSystemData::~CSystemData()
{

}
//-------------------------------------------------------------------
void CSystemData::Initialize(void)
{

}
//-------------------------------------------------------------------
void CSystemData::Finalize(void)
{


}
BOOL CSystemData::Load()
{
	m_Safety.Load();
	m_Option.Load();
	m_Coordinate.Load();
	m_Other.Load();
	m_Stage.Load();
	m_CameraCal.Load(); //KJT 20210524
	
	m_Other.InitElectricChuck();

	return TRUE;
}
//-------------------------------------------------------------------
BOOL CSystemData::Save( )
{
	m_Safety.Save();
	m_Option.Save();
	m_Coordinate.Save();
	m_Other.Save();
	m_Stage.Save();

	return TRUE;
}

#pragma region //System Safety
BOOL CSystemDataSafety::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\System"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Safety.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Safety.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Safety"));
	xml->IntoElem();

	xml->AddElem(_T("m_dSafetyPos_Min_Review10X_X"), Info.m_dSafetyPos_Min_Review10X_X);
	xml->AddElem(_T("m_dSafetyPos_Max_Review10X_X"), Info.m_dSafetyPos_Max_Review10X_X);
	xml->AddElem(_T("m_dSafetyPos_Min_Review10X_Y_In_BoxStage"), Info.m_dSafetyPos_Min_Review10X_Y_In_BoxStage);
	xml->AddElem(_T("m_dSafetyPos_Min_Review10X_Y_In_PaperStage"), Info.m_dSafetyPos_Min_Review10X_Y_In_PaperStage);
	xml->AddElem(_T("m_dSafetyPos_Min_Review10X_Y_In_InspectionStage"), Info.m_dSafetyPos_Min_Review10X_Y_In_InspectionStage);
	xml->AddElem(_T("m_dSafetyPos_Max_Review10X_Y"), Info.m_dSafetyPos_Max_Review10X_Y);
	xml->AddElem(_T("m_dSafetyPos_Min_Review10X_Z"), Info.m_dSafetyPos_Min_Review10X_Z);
	
	xml->AddElem(_T("m_dSafetyPos_Min_AOI_X"), Info.m_dSafetyPos_Min_AOI_X);
	xml->AddElem(_T("m_dSafetyPos_Max_AOI_X"), Info.m_dSafetyPos_Max_AOI_X);
	xml->AddElem(_T("m_dSafetyPos_Min_AOI_Y"), Info.m_dSafetyPos_Min_AOI_Y);
	xml->AddElem(_T("m_dSafetyPos_Max_AOI_Y"), Info.m_dSafetyPos_Max_AOI_Y);
	xml->AddElem(_T("m_dSafetyPos_Min_AOI_Z"), Info.m_dSafetyPos_Min_AOI_Z);

	xml->AddElem(_T("m_dSafetyPos_Min_Zoom_3D_X"), Info.m_dSafetyPos_Min_Zoom_3D_X);
	xml->AddElem(_T("m_dSafetyPos_Max_Zoom_3D_X"), Info.m_dSafetyPos_Max_Zoom_3D_X);
	xml->AddElem(_T("m_dSafetyPos_Min_Zoom_3D_Y"), Info.m_dSafetyPos_Min_Zoom_3D_Y);
	xml->AddElem(_T("m_dSafetyPos_Max_Zoom_3D_Y"), Info.m_dSafetyPos_Max_Zoom_3D_Y);
	xml->AddElem(_T("m_dSafetyPos_Min_Zoom_3D_Z"), Info.m_dSafetyPos_Min_Zoom_3D_Z);

	xml->AddElem(_T("m_dSafetyPos_Min_Loader_Z_In_Box_Stage"), Info.m_dSafetyPos_Min_Loader_Z_In_Box_Stage);
	xml->AddElem(_T("m_dSafetyPos_Min_Loader_Z_In_Paper_Stage"), Info.m_dSafetyPos_Min_Loader_Z_In_Paper_Stage);
	xml->AddElem(_T("m_dSafetyPos_Min_Loader_Z_In_Inspection_Stage"), Info.m_dSafetyPos_Min_Loader_Z_In_Inspection_Stage);

	xml->AddElem(_T("m_dDist_GantryY_To_UnloaderY"), Info.m_dDist_GantryY_To_UnloaderY);
	xml->AddElem(_T("m_dDist_GantryY_To_LoaderY"), Info.m_dDist_GantryY_To_LoaderY);

	xml->AddElem(_T("m_dMinDist_GantryY_To_UnloaderY"), Info.m_dMinDist_GantryY_To_UnloaderY);
	xml->AddElem(_T("m_dMinDist_GantryY_To_LoaderY"), Info.m_dMinDist_GantryY_To_LoaderY);

	xml->AddElem(_T("m_dMinDist_PaperUnloaderY_To_LoaderY"), Info.m_dMinDist_PaperUnloaderY_To_LoaderY);
	xml->AddElem(_T("m_dMinDist_PaperUnloaderX_To_LoaderX"), Info.m_dMinDist_PaperUnloaderX_To_LoaderX);

	xml->AddElem(_T("m_nUseSystemSafety"), Info.m_nUseSystemSafety);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("System Safety Save (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
BOOL CSystemDataSafety::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\System"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Safety.dat"));
	if (file.Open(szFilePath, CFile::modeRead) == FALSE)
	{
		file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(&Info, sizeof(Info));
		return FALSE;
	}

	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Safety.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Safety")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("m_dSafetyPos_Min_Review10X_X"))) Info.m_dSafetyPos_Min_Review10X_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Max_Review10X_X"))) Info.m_dSafetyPos_Max_Review10X_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_Review10X_Y_In_BoxStage"))) Info.m_dSafetyPos_Min_Review10X_Y_In_BoxStage = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_Review10X_Y_In_PaperStage"))) Info.m_dSafetyPos_Min_Review10X_Y_In_PaperStage = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_Review10X_Y_In_InspectionStage"))) Info.m_dSafetyPos_Min_Review10X_Y_In_InspectionStage = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Max_Review10X_Y"))) Info.m_dSafetyPos_Max_Review10X_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_Review10X_Z"))) Info.m_dSafetyPos_Min_Review10X_Z = _tstof(xml->GetData());
		
		if (xml->FindElem(_T("m_dSafetyPos_Min_AOI_X"))) Info.m_dSafetyPos_Min_AOI_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Max_AOI_X"))) Info.m_dSafetyPos_Max_AOI_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_AOI_Y"))) Info.m_dSafetyPos_Min_AOI_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Max_AOI_Y"))) Info.m_dSafetyPos_Max_AOI_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_AOI_Z"))) Info.m_dSafetyPos_Min_AOI_Z = _tstof(xml->GetData());
		
		if (xml->FindElem(_T("m_dSafetyPos_Min_Zoom_3D_X"))) Info.m_dSafetyPos_Min_Zoom_3D_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Max_Zoom_3D_X"))) Info.m_dSafetyPos_Max_Zoom_3D_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_Zoom_3D_Y"))) Info.m_dSafetyPos_Min_Zoom_3D_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Max_Zoom_3D_Y"))) Info.m_dSafetyPos_Max_Zoom_3D_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_Zoom_3D_Z"))) Info.m_dSafetyPos_Min_Zoom_3D_Z = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_dSafetyPos_Min_Loader_Z_In_Box_Stage"))) Info.m_dSafetyPos_Min_Loader_Z_In_Box_Stage = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_Loader_Z_In_Paper_Stage"))) Info.m_dSafetyPos_Min_Loader_Z_In_Paper_Stage = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSafetyPos_Min_Loader_Z_In_Inspection_Stage"))) Info.m_dSafetyPos_Min_Loader_Z_In_Inspection_Stage = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_dDist_GantryY_To_UnloaderY"))) Info.m_dDist_GantryY_To_UnloaderY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dDist_GantryY_To_LoaderY"))) Info.m_dDist_GantryY_To_LoaderY = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_dMinDist_GantryY_To_UnloaderY"))) Info.m_dMinDist_GantryY_To_UnloaderY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dMinDist_GantryY_To_LoaderY"))) Info.m_dMinDist_GantryY_To_LoaderY = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_dMinDist_PaperUnloaderY_To_LoaderY"))) Info.m_dMinDist_PaperUnloaderY_To_LoaderY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dMinDist_PaperUnloaderX_To_LoaderX"))) Info.m_dMinDist_PaperUnloaderX_To_LoaderX = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_nUseSystemSafety"))) Info.m_nUseSystemSafety = _tstoi(xml->GetData());
		
		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("System Safety Load (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //System Option
BOOL CSystemDataOption::Save( )
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\System"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Option.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Option.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Option"));
	xml->IntoElem();

	xml->AddElem(_T("m_strActiveModelName"), Info.m_strActiveModelName);

	xml->AddElem(_T("m_bImageAutoSave"), Info.m_bImageAutoSave); // 이미지 자동 저장 기능 사용 여부 확인
	xml->AddElem(_T("m_bImageAutoDel"), Info.m_bImageAutoDel); // 이미지 자동 삭제 기능 사용 여부 확인

	xml->AddElem(_T("m_nUserMode"), Info.m_nUserMode);
	xml->AddElem(_T("m_nWorkMode"), Info.m_nWorkMode);
	
	xml->AddElem(_T("nImageDelPeriod"), Info.nImageDelPeriod); // 이미지 보관 기간? 이미지 삭제 주기? 얼마나 보관할지?

	xml->AddElem(_T("m_dAutoFocusSpeed"), Info.m_dAutoFocusSpeed);
	xml->AddElem(_T("m_dAutoFocusUpRange"), Info.m_dAutoFocusUpRange);
	xml->AddElem(_T("m_dAutoFocusDownRange"), Info.m_dAutoFocusDownRange);

	xml->AddElem(_T("m_nAutoFocusMode"), Info.m_nAutoFocusMode);

	xml->AddElem(_T("m_nSmart_InMotionCheckMode"), Info.m_nSmart_InMotionCheckMode);
	xml->AddElem(_T("m_nSmart_DelayTime"), Info.m_nSmart_DelayTime);
	xml->AddElem(_T("m_nSmart_MaxTurnCount"), Info.m_nSmart_MaxTurnCount);
	xml->AddElem(_T("m_nSmart_RefTurnCount"), Info.m_nSmart_RefTurnCount);
	xml->AddElem(_T("m_dSmart_LimitFocusValue"), Info.m_dSmart_LimitFocusValue);
	xml->AddElem(_T("m_dSmart_MinFocusValue"), Info.m_dSmart_MinFocusValue);
	xml->AddElem(_T("m_dSmart_FocusTolerance"), Info.m_dSmart_FocusTolerance);
	xml->AddElem(_T("m_nSmart_ScanMode"), Info.m_nSmart_ScanMode);
	xml->AddElem(_T("m_dSmart_MinStepValue"), Info.m_dSmart_MinStepValue);
	xml->AddElem(_T("m_dSmart_MaxStepValue"), Info.m_dSmart_MaxStepValue);
	xml->AddElem(_T("m_dSmart_DownDistRange"), Info.m_dSmart_DownDistRange);
	xml->AddElem(_T("m_dSmart_UpDistRange"), Info.m_dSmart_UpDistRange);
	xml->AddElem(_T("m_dSmart_Vel"), Info.m_dSmart_Vel); //KJT 20210803 Add
	xml->AddElem(_T("m_dSmart_Accel"), Info.m_dSmart_Accel);
	xml->AddElem(_T("m_dSmart_Decel"), Info.m_dSmart_Decel);

	xml->AddElem(_T("m_bAOIAlgorithmSkip"), Info.m_bAOIAlgorithmSkip);
	xml->AddElem(_T("m_bAOIMappingGlassMode"), Info.m_bAOIMappingGlassMode);
	xml->AddElem(_T("m_dAOI_Z_MappingGlassPos"), Info.m_dAOI_Z_MappingGlassPos);

	xml->AddElem(_T("m_bGlassMode"), Info.m_bGlassMode);
	xml->AddElem(_T("m_bAOIAgingMode"), Info.m_bAOIAgingMode);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("System Option Save (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
BOOL CSystemDataOption::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\System"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Option.dat"));
	if (file.Open(szFilePath, CFile::modeRead) == FALSE)
	{
		file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(&Info, sizeof(Info));
		return FALSE;
	}

	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Option.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Option")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("m_strActiveModelName"))) 	wsprintf(Info.m_strActiveModelName, _T("%s"), xml->GetData()); //KJT 20210727

		if (xml->FindElem(_T("m_bImageAutoSave"))) Info.m_bImageAutoSave = _tstoi(xml->GetData()); // 이미지 자동 저장 기능 사용 여부 확인
		if (xml->FindElem(_T("m_bImageAutoDel"))) Info.m_bImageAutoDel = _tstoi(xml->GetData()); // 이미지 자동 삭제 기능 사용 여부 확인

		if (xml->FindElem(_T("m_nUserMode"))) Info.m_nUserMode = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nWorkMode"))) Info.m_nWorkMode = _tstoi(xml->GetData());

		if (xml->FindElem(_T("nImageDelPeriod"))) Info.nImageDelPeriod = _tstoi(xml->GetData()); // 이미지 보관 기간? 이미지 삭제 주기? 얼마나 보관할지?

		if (xml->FindElem(_T("m_dAutoFocusSpeed"))) Info.m_dAutoFocusSpeed = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAutoFocusUpRange"))) Info.m_dAutoFocusUpRange = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAutoFocusDownRange"))) Info.m_dAutoFocusDownRange = _tstof(xml->GetData());
		
		if (xml->FindElem(_T("m_nAutoFocusMode"))) Info.m_nAutoFocusMode = _tstoi(xml->GetData());
		
		if (xml->FindElem(_T("m_nSmart_InMotionCheckMode"))) Info.m_nSmart_InMotionCheckMode = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nSmart_DelayTime"))) Info.m_nSmart_DelayTime = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nSmart_MaxTurnCount"))) Info.m_nSmart_MaxTurnCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nSmart_RefTurnCount"))) Info.m_nSmart_RefTurnCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_LimitFocusValue"))) Info.m_dSmart_LimitFocusValue = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_MinFocusValue"))) Info.m_dSmart_MinFocusValue = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_FocusTolerance"))) Info.m_dSmart_FocusTolerance = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_nSmart_ScanMode"))) Info.m_nSmart_ScanMode = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_MinStepValue"))) Info.m_dSmart_MinStepValue = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_MaxStepValue"))) Info.m_dSmart_MaxStepValue = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_DownDistRange"))) Info.m_dSmart_DownDistRange = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_UpDistRange"))) Info.m_dSmart_UpDistRange = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_Vel"))) Info.m_dSmart_Vel = _tstof(xml->GetData()); //KJT 20210803 Add
		if (xml->FindElem(_T("m_dSmart_Accel"))) Info.m_dSmart_Accel = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dSmart_Decel"))) Info.m_dSmart_Decel = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_bAOIAlgorithmSkip"))) Info.m_bAOIAlgorithmSkip = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_bAOIMappingGlassMode"))) Info.m_bAOIMappingGlassMode = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dAOI_Z_MappingGlassPos"))) Info.m_dAOI_Z_MappingGlassPos = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_bGlassMode"))) Info.m_bGlassMode = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_bAOIAgingMode"))) Info.m_bAOIAgingMode = _tstoi(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("System Option Load (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region
BOOL CSystemDataCoordinate::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\System"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Coordinate.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Coordinate.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Coordinate"));
	xml->IntoElem();

	//Camera Offset
	xml->AddElem(_T("dOffsetReview10xTo20x_X"), Info.dOffsetReview10xTo20x_X);
	xml->AddElem(_T("dOffsetReview10xTo20x_Y"), Info.dOffsetReview10xTo20x_Y);
	xml->AddElem(_T("dOffsetReview10xTo20x_Z"), Info.dOffsetReview10xTo20x_Z);
	xml->AddElem(_T("dOffsetReview10xToPreAlign_X"), Info.dOffsetReview10xToPreAlign_X);
	xml->AddElem(_T("dOffsetReview10xToPreAlign_Y"), Info.dOffsetReview10xToPreAlign_Y);
	xml->AddElem(_T("dOffsetReview10xToPreAlign_Z"), Info.dOffsetReview10xToPreAlign_Z);
	xml->AddElem(_T("dOffsetReview10xToAoi_X"), Info.dOffsetReview10xToAoi_X);
	xml->AddElem(_T("dOffsetReview10xToAoi_Y"), Info.dOffsetReview10xToAoi_Y);
	xml->AddElem(_T("dOffsetReview10xToAoi_Z"), Info.dOffsetReview10xToAoi_Z);
	xml->AddElem(_T("dOffsetReview10xTo3dCam_X"), Info.dOffsetReview10xTo3dCam_X);
	xml->AddElem(_T("dOffsetReview10xTo3dCam_Y"), Info.dOffsetReview10xTo3dCam_Y);
	xml->AddElem(_T("dOffsetReview10xTo3dCam_Z"), Info.dOffsetReview10xTo3dCam_Z);
	xml->AddElem(_T("dOffsetReview10xTo50x_X"), Info.dOffsetReview10xTo50x_X);
	xml->AddElem(_T("dOffsetReview10xTo50x_Y"), Info.dOffsetReview10xTo50x_Y);

	for (i = 0; i < DIRECT_AXIS_MAX; i++)
	{
		Str.Format(_T("dOffsetCameraZ_%d"), i);
		xml->AddElem(Str, Info.dOffsetCameraZ[i]);
	}

	//xml->AddElem(_T("dOffsetCamera3DMainZ"), Info.dOffsetCamera3DMainZ);
	xml->AddElem(_T("d3DCam_Resolution_X"), Info.d3DCam_Resolution_X);
	xml->AddElem(_T("d3DCam_Resolution_Y"), Info.d3DCam_Resolution_Y);
	
	xml->AddElem(_T("d10XCam_Resolution_X"), Info.d10XCam_Resolution_X);
	xml->AddElem(_T("d10XCam_Resolution_Y"), Info.d10XCam_Resolution_Y);

	xml->AddElem(_T("d20XCam_Resolution_X"), Info.d20XCam_Resolution_X);
	xml->AddElem(_T("d20XCam_Resolution_Y"), Info.d20XCam_Resolution_Y);

	xml->AddElem(_T("d50XCam_Resolution_X"), Info.d50XCam_Resolution_X);
	xml->AddElem(_T("d50XCam_Resolution_Y"), Info.d50XCam_Resolution_Y);

	xml->AddElem(_T("dMax_Tension_Offset_LoaderX"), Info.dMax_Tension_Offset_LoaderX); //KJT 20210806 Add
	xml->AddElem(_T("dMax_Tension_Offset_UnloaderX"), Info.dMax_Tension_Offset_UnloaderX);
	xml->AddElem(_T("dMax_Tension_Offset_PaperUnloaderX"), Info.dMax_Tension_Offset_PaperUnloaderX);

	xml->AddElem(_T("dOffsetReview10xToLaser_X"), Info.dOffsetReview10xToLaser_X); //KJT 20210824 Add
	xml->AddElem(_T("dOffsetReview10xToLaser_Y"), Info.dOffsetReview10xToLaser_Y); //KJT 20210824 Add

	xml->AddElem(_T("dLaserFocusOffsetGlass"), Info.dLaserFocusOffsetGlass);
	xml->AddElem(_T("dLaserFocusOffsetStick"), Info.dLaserFocusOffsetStick);	

	for (i = 0; i < eAOI_Vel_Max; i++)
	{
		Str.Format(_T("nBackLightXFwdStartDelay_%d"), i);
		xml->AddElem(Str, Info.nBackLightXFwdStartDelay[i]);
		Str.Format(_T("dBackLightXFwdAccDecScale_%d"), i);
		xml->AddElem(Str, Info.dBackLightXFwdAccDecScale[i]);
		Str.Format(_T("nBackLightXBwdStartDelay_%d"), i);
		xml->AddElem(Str, Info.nBackLightXBwdStartDelay[i]);
		Str.Format(_T("dBackLightXBwdAccDecScale_%d"), i);
		xml->AddElem(Str, Info.dBackLightXBwdAccDecScale[i]);
	}

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("System Coordinate Save (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//-------------------------------------------------------------------
BOOL CSystemDataCoordinate::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\System"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Coordinate.dat"));
	if (file.Open(szFilePath, CFile::modeRead) == FALSE)
	{
		file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(&Info, sizeof(Info));
		return FALSE;
	}

	file.Read(&Info, sizeof(Info));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Coordinate.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Coordinate")))
	{
		xml->IntoElem();

		//Camera Offset
		if (xml->FindElem(_T("dOffsetReview10xTo20x_X"))) Info.dOffsetReview10xTo20x_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xTo20x_Y"))) Info.dOffsetReview10xTo20x_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xTo20x_Z"))) Info.dOffsetReview10xTo20x_Z = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xToPreAlign_X"))) Info.dOffsetReview10xToPreAlign_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xToPreAlign_Y"))) Info.dOffsetReview10xToPreAlign_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xToPreAlign_Z"))) Info.dOffsetReview10xToPreAlign_Z = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xToAoi_X"))) Info.dOffsetReview10xToAoi_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xToAoi_Y"))) Info.dOffsetReview10xToAoi_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xToAoi_Z"))) Info.dOffsetReview10xToAoi_Z = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xTo3dCam_X"))) Info.dOffsetReview10xTo3dCam_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xTo3dCam_Y"))) Info.dOffsetReview10xTo3dCam_Y = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xTo3dCam_Z"))) Info.dOffsetReview10xTo3dCam_Z = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xTo50x_X"))) Info.dOffsetReview10xTo50x_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("dOffsetReview10xTo50x_Y"))) Info.dOffsetReview10xTo50x_Y = _tstof(xml->GetData());

		for (i = 0; i < DIRECT_AXIS_MAX; i++)
		{
			Str.Format(_T("dOffsetCameraZ_%d"), i);
			if (xml->FindElem(Str)) Info.dOffsetCameraZ[i] = _tstof(xml->GetData());
		}

		//if (xml->FindElem(_T("dOffsetCamera3DMainZ"))) Info.dOffsetCamera3DMainZ = _tstof(xml->GetData());
		if (xml->FindElem(_T("d3DCam_Resolution_X"))) Info.d3DCam_Resolution_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("d3DCam_Resolution_Y"))) Info.d3DCam_Resolution_Y = _tstof(xml->GetData());

		if (xml->FindElem(_T("d10XCam_Resolution_X"))) Info.d10XCam_Resolution_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("d10XCam_Resolution_Y"))) Info.d10XCam_Resolution_Y = _tstof(xml->GetData());

		if (xml->FindElem(_T("d20XCam_Resolution_X"))) Info.d20XCam_Resolution_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("d20XCam_Resolution_Y"))) Info.d20XCam_Resolution_Y = _tstof(xml->GetData());

		if (xml->FindElem(_T("d50XCam_Resolution_X"))) Info.d50XCam_Resolution_X = _tstof(xml->GetData());
		if (xml->FindElem(_T("d50XCam_Resolution_Y"))) Info.d50XCam_Resolution_Y = _tstof(xml->GetData());

		if (xml->FindElem(_T("dMax_Tension_Offset_LoaderX"))) Info.dMax_Tension_Offset_LoaderX = _tstof(xml->GetData()); //KJT 20210806 Add
		if (xml->FindElem(_T("dMax_Tension_Offset_UnloaderX"))) Info.dMax_Tension_Offset_UnloaderX = _tstof(xml->GetData());
		if (xml->FindElem(_T("dMax_Tension_Offset_PaperUnloaderX"))) Info.dMax_Tension_Offset_PaperUnloaderX = _tstof(xml->GetData());

		if (xml->FindElem(_T("dOffsetReview10xToLaser_X"))) Info.dOffsetReview10xToLaser_X = _tstof(xml->GetData()); //KJT 20210824 Add
		if (xml->FindElem(_T("dOffsetReview10xToLaser_Y"))) Info.dOffsetReview10xToLaser_Y = _tstof(xml->GetData()); //KJT 20210824 Add

		if (xml->FindElem(_T("dLaserFocusOffsetGlass"))) Info.dLaserFocusOffsetGlass = _tstof(xml->GetData());
		if (xml->FindElem(_T("dLaserFocusOffsetStick"))) Info.dLaserFocusOffsetStick = _tstof(xml->GetData());

		for (i = 0; i < eAOI_Vel_Max; i++)
		{
			Str.Format(_T("nBackLightXFwdStartDelay_%d"), i);
			if (xml->FindElem(Str)) Info.nBackLightXFwdStartDelay[i] = _tstoi(xml->GetData());
			Str.Format(_T("dBackLightXFwdAccDecScale_%d"), i);
			if (xml->FindElem(Str)) Info.dBackLightXFwdAccDecScale[i] = _tstof(xml->GetData());
			Str.Format(_T("nBackLightXBwdStartDelay_%d"), i);
			if (xml->FindElem(Str)) Info.nBackLightXBwdStartDelay[i] = _tstoi(xml->GetData());
			Str.Format(_T("dBackLightXBwdAccDecScale_%d"), i);
			if (xml->FindElem(Str)) Info.dBackLightXBwdAccDecScale[i] = _tstof(xml->GetData());
		}

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("System Coordinate Load (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //System Other //KJT 20210329
BOOL CSystemDataOther::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0;

	//#if !XML_USE //dat
	szFilePath.Format(_T("%s\\Data\\System\\Other.dat"), SharedInfo::VisionAgentPath);
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
	//#else //xml
	szFilePath.Format(_T("%s\\Data\\System\\Other.xml"), SharedInfo::VisionAgentPath);

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Other"));
	xml->IntoElem();

	for (i = 0; i < MAX_AUTO_DELETE_DIR_PATH; i++)
	{
		xml->AddElem(_T("m_bAutoDeleteDirPathUse"), Info.m_bAutoDeleteDirPathUse[i]);
		xml->AddElem(_T("m_nFileStoreDays"), Info.m_nFileStoreDays[i]);
	}

	xml->AddElem(_T("m_dHighTemperature"), Info.m_dHighTemperature);
	xml->AddElem(_T("m_dLowTemperature"), Info.m_dLowTemperature);
	xml->AddElem(_T("m_nUseTemperatureCheck"), Info.m_nUseTemperatureCheck);
	xml->AddElem(_T("m_nUseDoorOpenCheck"), Info.m_nUseDoorOpenCheck);	
	xml->AddElem(_T("m_nUseAuto3DConnection"), Info.m_nUseAuto3DConnection);

	xml->AddElem(_T("m_nElectricChuckVolt"), Info.m_nElectricChuckVolt);

	xml->AddElem(_T("m_dZoom2XPos"), Info.m_dZoom2XPos);
	xml->AddElem(_T("m_dZoom10XPos"), Info.m_dZoom10XPos);
	xml->AddElem(_T("m_dZoom20XPos"), Info.m_dZoom20XPos);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
	//#endif

	Str.Format(_T("System Other Save (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL CSystemDataOther::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0;

#if !XML_USE //dat
	szFilePath.Format(_T("%s\\Data\\System\\Other.dat"), SharedInfo::VisionAgentPath);
	if (file.Open(szFilePath, CFile::modeRead) == FALSE)
	{
		file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(&Info, sizeof(Info));
		return FALSE;
	}

	file.Read(&Info, sizeof(Info));
	file.Close();
#else
	szFilePath.Format(_T("%s\\Data\\System\\Other.xml"), SharedInfo::VisionAgentPath);

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Other")))
	{
		xml->IntoElem();

		for (i = 0; i < MAX_AUTO_DELETE_DIR_PATH; i++)
		{
			if (xml->FindElem(_T("m_bAutoDeleteDirPathUse"))) Info.m_bAutoDeleteDirPathUse[i] = _tstoi(xml->GetData());
			if (xml->FindElem(_T("m_nFileStoreDays"))) Info.m_nFileStoreDays[i] = _tstoi(xml->GetData());
		}
				
		if (xml->FindElem(_T("m_dHighTemperature"))) Info.m_dHighTemperature = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLowTemperature"))) Info.m_dLowTemperature = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_nUseTemperatureCheck"))) Info.m_nUseTemperatureCheck = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nUseDoorOpenCheck"))) Info.m_nUseDoorOpenCheck = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nUseAuto3DConnection"))) Info.m_nUseAuto3DConnection = _tstoi(xml->GetData());

		if (xml->FindElem(_T("m_nElectricChuckVolt"))) Info.m_nElectricChuckVolt = _tstoi(xml->GetData());
		
		if (xml->FindElem(_T("m_dZoom2XPos"))) Info.m_dZoom2XPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dZoom10XPos"))) Info.m_dZoom10XPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dZoom20XPos"))) Info.m_dZoom20XPos = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("System Other Load (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion


BOOL CSystemDataOther::InitElectricChuck()
{
	//CString str, strVolt1, strVolt2;

	//g_CommESC.Esc_Send_Msg(_T("SYSTem:REMote"));

	//strVolt1.Format(_T("+%d"), Info.m_nElectricChuckVolt);
	//strVolt2.Format(_T("-%d"), Info.m_nElectricChuckVolt);

	//str.Format(_T("VOLT %s, %s"), strVolt1, strVolt2);
	//g_CommESC.Esc_Send_Msg(str);

	return TRUE;
}

#pragma region //Machine Stage Info
BOOL CSystemDataStage::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\System"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Stage.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Stage.xml"));

	CXmlFile* xml = new CXmlFile;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Stage"));
	xml->IntoElem();

	xml->AddElem(_T("m_dParameterSizeX"), Info.m_dParameterSizeX);
	xml->AddElem(_T("m_dParameterSizeY"), Info.m_dParameterSizeY);
	xml->AddElem(_T("m_dParameterZ"), Info.m_dParameterZ);
	xml->AddElem(_T("m_dParameterStartX"), Info.m_dParameterStartX);
	xml->AddElem(_T("m_dParameterStartY"), Info.m_dParameterStartY);
	xml->AddElem(_T("m_dParameterPitchX"), Info.m_dParameterPitchX);
	xml->AddElem(_T("m_dParameterPitchY"), Info.m_dParameterPitchY);
	xml->AddElem(_T("m_nParameterCountX"), Info.m_nParameterCountX);
	xml->AddElem(_T("m_nParameterCountY"), Info.m_nParameterCountY);
	xml->AddElem(_T("m_nParameterPitchFile"), Info.m_nParameterPitchFile);

	xml->AddElem(_T("m_nPointNoX"), Info.m_nPointNoX);
	xml->AddElem(_T("m_nPointNoY"), Info.m_nPointNoY);

	xml->AddElem(_T("m_nCalibDelay"), Info.m_nCalibDelay);
	xml->AddElem(_T("m_nCalibRepeat"), Info.m_nCalibRepeat);
	xml->AddElem(_T("m_dCalib3SigmaX"), Info.m_dCalib3SigmaX);
	xml->AddElem(_T("m_dCalib3SigmaY"), Info.m_dCalib3SigmaY);
	xml->AddElem(_T("m_nCaliApplyCalib"), Info.m_nCaliApplyCalib);
	
	xml->AddElem(_T("m_nVerifyRepeat"), Info.m_nVerifyRepeat);
	xml->AddElem(_T("m_dVerifyWorldX1"), Info.m_dVerifyWorldX1);
	xml->AddElem(_T("m_dVerifyWorldY1"), Info.m_dVerifyWorldY1);
	xml->AddElem(_T("m_dVerifyWorldX2"), Info.m_dVerifyWorldX2);
	xml->AddElem(_T("m_dVerifyWorldY2"), Info.m_dVerifyWorldY2);
	xml->AddElem(_T("m_dVerifyRealX1"), Info.m_dVerifyRealX1);
	xml->AddElem(_T("m_dVerifyRealY1"), Info.m_dVerifyRealY1);
	xml->AddElem(_T("m_dVerifyRealX2"), Info.m_dVerifyRealX2);
	xml->AddElem(_T("m_dVerifyRealY2"), Info.m_dVerifyRealY2);

	xml->AddElem(_T("m_nAlignPoint2_4"), Info.m_nAlignPoint2_4);
	xml->AddElem(_T("m_dAlignLTX"), Info.m_dAlignLTX);
	xml->AddElem(_T("m_dAlignLTY"), Info.m_dAlignLTY);
	xml->AddElem(_T("m_dAlignRTX"), Info.m_dAlignRTX);
	xml->AddElem(_T("m_dAlignRTY"), Info.m_dAlignRTY);
	xml->AddElem(_T("m_dAlignLBX"), Info.m_dAlignLBX);
	xml->AddElem(_T("m_dAlignLBY"), Info.m_dAlignLBY);
	xml->AddElem(_T("m_dAlignRBX"), Info.m_dAlignRBX);
	xml->AddElem(_T("m_dAlignRBY"), Info.m_dAlignRBY);
	xml->AddElem(_T("m_nAlignTargetCount"), Info.m_nAlignTargetCount);
	xml->AddElem(_T("m_dAlignTargetX"), Info.m_dAlignTargetX);
	xml->AddElem(_T("m_dAlignTargetY"), Info.m_dAlignTargetY);
	xml->AddElem(_T("m_dAlignTargetT"), Info.m_dAlignTargetT);
	xml->AddElem(_T("m_nAlignRealignCount"), Info.m_nAlignRealignCount);

	xml->AddElem(_T("m_nCalibVerify"), Info.m_nCalibVerify);

	xml->AddElem(_T("m_nXYTIntervalCount"), Info.m_nXYTIntervalCount);
	xml->AddElem(_T("m_nMappingRepeatCount"), Info.m_nMappingRepeatCount);
	xml->AddElem(_T("m_nVerificationRepeatCount"), Info.m_nVerificationRepeatCount);
		
	xml->AddElem(_T("m_nMappingPreAlign"), Info.m_nMappingPreAlign);
	xml->AddElem(_T("m_nMappingMainAlign"), Info.m_nMappingMainAlign);
	xml->AddElem(_T("m_nApplyMappingResult"), Info.m_nApplyMappingResult);	

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("System Stage Save (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
BOOL CSystemDataStage::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\System"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Stage.dat"));
	if (file.Open(szFilePath, CFile::modeRead) == FALSE)
	{
		file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(&Info, sizeof(Info));
		return FALSE;
	}

	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Stage.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Stage")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("m_dParameterSizeX"))) Info.m_dParameterSizeX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dParameterSizeY"))) Info.m_dParameterSizeY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dParameterZ"))) Info.m_dParameterZ = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dParameterStartX"))) Info.m_dParameterStartX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dParameterStartY"))) Info.m_dParameterStartY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dParameterPitchX"))) Info.m_dParameterPitchX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dParameterPitchY"))) Info.m_dParameterPitchY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_nParameterCountX"))) Info.m_nParameterCountX = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nParameterCountY"))) Info.m_nParameterCountY = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nParameterPitchFile"))) Info.m_nParameterPitchFile = _tstoi(xml->GetData());

		if (xml->FindElem(_T("m_nPointNoX"))) Info.m_nPointNoX = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nPointNoY"))) Info.m_nPointNoY = _tstoi(xml->GetData());

		if (xml->FindElem(_T("m_nCalibDelay"))) Info.m_nCalibDelay = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nCalibRepeat"))) Info.m_nCalibRepeat = _tstoi(xml->GetData());

		if (xml->FindElem(_T("m_dCalib3SigmaX"))) Info.m_dCalib3SigmaX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dCalib3SigmaY"))) Info.m_dCalib3SigmaY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_nCaliApplyCalib"))) Info.m_nCaliApplyCalib = _tstoi(xml->GetData());

		if (xml->FindElem(_T("m_nVerifyRepeat"))) Info.m_nVerifyRepeat = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dVerifyWorldX1"))) Info.m_dVerifyWorldX1 = _tstof(xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("m_dVerifyWorldY1"))) Info.m_dVerifyWorldY1 = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dVerifyWorldX2"))) Info.m_dVerifyWorldX2 = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dVerifyWorldY2"))) Info.m_dVerifyWorldY2 = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dVerifyRealX1"))) Info.m_dVerifyRealX1 = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dVerifyRealY1"))) Info.m_dVerifyRealY1 = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dVerifyRealX2"))) Info.m_dVerifyRealX2 = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dVerifyRealY2"))) Info.m_dVerifyRealY2 = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_nAlignPoint2_4"))) Info.m_nAlignPoint2_4 = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dAlignLTX"))) Info.m_dAlignLTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignLTY"))) Info.m_dAlignLTY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignRTX"))) Info.m_dAlignRTX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignRTY"))) Info.m_dAlignRTY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignLBX"))) Info.m_dAlignLBX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignLBY"))) Info.m_dAlignLBY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignRBX"))) Info.m_dAlignRBX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignRBY"))) Info.m_dAlignRBY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_nAlignTargetCount"))) Info.m_nAlignTargetCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dAlignTargetX"))) Info.m_dAlignTargetX = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignTargetY"))) Info.m_dAlignTargetY = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dAlignTargetT"))) Info.m_dAlignTargetT = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_nAlignRealignCount"))) Info.m_nAlignRealignCount = _tstoi(xml->GetData());

		if (xml->FindElem(_T("m_nCalibVerify"))) Info.m_nCalibVerify = _tstoi(xml->GetData());
		
		if (xml->FindElem(_T("m_nXYTIntervalCount"))) Info.m_nXYTIntervalCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nMappingRepeatCount"))) Info.m_nMappingRepeatCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nVerificationRepeatCount"))) Info.m_nVerificationRepeatCount = _tstoi(xml->GetData());

		if (xml->FindElem(_T("m_nMappingPreAlign"))) Info.m_nMappingPreAlign = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nMappingMainAlign"))) Info.m_nMappingMainAlign = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_nApplyMappingResult"))) Info.m_nApplyMappingResult = _tstoi(xml->GetData());			

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("System Stage Load (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Camera Cal Info
BOOL CSystemDataCameraCal::Init()
{
	return TRUE;
}
BOOL CSystemDataCameraCal::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;

//#if !XML_USE //dat
	szFilePath.Format(_T("%s\\Data\\System\\CameraCalPara.dat"), SharedInfo::VisionAgentPath);
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
//#else //xml
	szFilePath.Format(_T("%s\\Data\\System\\CameraCalPara.xml"), SharedInfo::VisionAgentPath);

	CXmlFile* xml = new CXmlFile;

	CString strTemp;

	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));

	for (int i = 0; i < 3; i++)
	{
		strTemp.Format(_T("CameraCal%d"), i);
		xml->AddElem(strTemp);
		xml->IntoElem();

		xml->AddElem(_T("m_dParameterSizeX"), Info[i].m_dParameterSizeX);
		xml->AddElem(_T("m_dParameterSizeY"), Info[i].m_dParameterSizeY);
		xml->AddElem(_T("m_dParameterZ"), Info[i].m_dParameterZ);
		xml->AddElem(_T("m_dParameterStartX"), Info[i].m_dParameterStartX);
		xml->AddElem(_T("m_dParameterStartY"), Info[i].m_dParameterStartY);
		xml->AddElem(_T("m_dParameterPitchX"), Info[i].m_dParameterPitchX);
		xml->AddElem(_T("m_dParameterPitchY"), Info[i].m_dParameterPitchY);
		xml->AddElem(_T("m_nParameterCountX"), Info[i].m_nParameterCountX);
		xml->AddElem(_T("m_nParameterCountY"), Info[i].m_nParameterCountY);

		xml->AddElem(_T("m_nCalibDelay"), Info[i].m_nCalibDelay);
		xml->AddElem(_T("m_nCalibRepeat"), Info[i].m_nCalibRepeat);
		xml->AddElem(_T("m_nCaliApplyCalib"), Info[i].m_nCaliApplyCalib);
		xml->AddElem(_T("m_nCaliFindType"), Info[i].m_nCaliFindType); //KJT 20210820 Add

		xml->OutOfElem();
	}

	xml->Save(szFilePath);
	delete xml;
//#endif

	Str.Format(_T("Camera Cal Save (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;

	return TRUE;
}
BOOL CSystemDataCameraCal::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;

#if !XML_USE //dat
	szFilePath.Format(_T("%s\\Data\\System\\CameraCalPara.dat"), SharedInfo::VisionAgentPath);
	if (file.Open(szFilePath, CFile::modeRead) == FALSE)
	{
		file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(&Info, sizeof(Info));
		return FALSE;
	}

	file.Read(&Info, sizeof(Info));
	file.Close();
#else //xml
	szFilePath.Format(_T("%s\\Data\\System\\CameraCalPara.xml"), SharedInfo::VisionAgentPath);

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);

	CString strTemp;

	for (int i = 0; i < 3; i++)
	{
		strTemp.Format(_T("CameraCal%d"), i);
		if (xml->FindElem(strTemp))
		{
			xml->IntoElem();

			if (xml->FindElem(_T("m_dParameterSizeX"))) Info[i].m_dParameterSizeX = _tstof(xml->GetData());
			if (xml->FindElem(_T("m_dParameterSizeY"))) Info[i].m_dParameterSizeY = _tstof(xml->GetData());
			if (xml->FindElem(_T("m_dParameterZ"))) Info[i].m_dParameterZ = _tstof(xml->GetData());
			if (xml->FindElem(_T("m_dParameterStartX"))) Info[i].m_dParameterStartX = _tstof(xml->GetData());
			if (xml->FindElem(_T("m_dParameterStartY"))) Info[i].m_dParameterStartY = _tstof(xml->GetData());
			if (xml->FindElem(_T("m_dParameterPitchX"))) Info[i].m_dParameterPitchX = _tstof(xml->GetData());
			if (xml->FindElem(_T("m_dParameterPitchY"))) Info[i].m_dParameterPitchY = _tstof(xml->GetData());
			if (xml->FindElem(_T("m_nParameterCountX"))) Info[i].m_nParameterCountX = _tstoi(xml->GetData());
			if (xml->FindElem(_T("m_nParameterCountY"))) Info[i].m_nParameterCountY = _tstoi(xml->GetData());

			if (xml->FindElem(_T("m_nCalibDelay"))) Info[i].m_nCalibDelay = _tstoi(xml->GetData());
			if (xml->FindElem(_T("m_nCalibRepeat"))) Info[i].m_nCalibRepeat = _tstoi(xml->GetData());
			if (xml->FindElem(_T("m_nCaliApplyCalib"))) Info[i].m_nCaliApplyCalib = _tstoi(xml->GetData());
			if (xml->FindElem(_T("m_nCaliFindType"))) Info[i].m_nCaliFindType = _tstoi(xml->GetData()); //KJT 20210820 Add

			xml->OutOfElem();

			Str.Format(_T("Camera Cal Load Ok (%s)"), szFilePath);
			Total_Msg(Str);
		}
		else
		{
			Str.Format(_T("Camera Cal Load Fail !! (%s)"), szFilePath);
			Total_Msg(Str);
		}
	}

	delete xml;
#endif
	
	return TRUE;
}
#pragma endregion