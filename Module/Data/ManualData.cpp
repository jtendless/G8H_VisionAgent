#include "stdafx.h"
#include "ManualData.h"
#include "Module/Vision/SharedInfo.h"
#include "Module/Data/XmlFile.h"

CManualDataGantry				CManualData::m_ManualDataGantry;
CManualDataBox					CManualData::m_ManualDataBox;
CManualDataLoader				CManualData::m_ManualDataLoader;
CManualDataInspect				CManualData::m_ManualDataInspect;
CManualDataClamp				CManualData::m_ManualDataClamp;
CManualDataStretch				CManualData::m_ManualDataStretch;
CManualDataPitch				CManualData::m_ManualDataPitch;
CManualDataGripperZ				CManualData::m_ManualDataGripperZ;
CManualDataUnloader				CManualData::m_ManualDataUnloader;
CManualDataCassette				CManualData::m_ManualDataCassette;

#pragma region //Gantry
void		CManualDataGantry::Init()
{
	//Gantry X	
	Info.m_dGantry_X_Wait_Pos = 0.000;

	//Gantry Y	
	Info.m_dGantry_Y_Wait_Pos = 0.000;
	Info.m_dGantry_Y_Stick_Load_In_Box_Pos = 0.000;
	Info.m_dGantry_Y_Paper_Unload_Pos = 0.000;
	Info.m_dGantry_Y_Stick_Unload_To_Stage_Pos = 0.000;
	//21.02.23 sjc
	Info.m_dGantry_Y_Loading_Safe_Pos = 0.000;
	Info.m_dGantry_Y_Unloading_Safe_Pos = 0.000;

	//Camera Z1
	Info.m_dGantry_Z1_Wait_Pos = 0.000;
	Info.m_dGantry_Z1_Inspection_AOI_Pos = 0.000;

	//Camera Z2
	Info.m_dGantry_Z2_Wait_Pos = 0.000;
	Info.m_dGantry_Z1_PreAlign_Pos = 0.000;
	Info.m_dGantry_Z2_Inspection_3D_Pos = 0.000;
	double  m_dGantry_Z2_Review_AOI_Pos = 0.0;

	//3D Camera Main Z
	Info.m_dGantry_Z3_Wait_Pos = 0.000;
	Info.m_dGantry_Z1_Inspection_Review_Pos = 0.000;
	Info.m_dGantry_Z3_Mapping_Review_Pos = 0.000;	

	//3D Camera Sub Z
	Info.m_d3D_Camera_Sub_Z_Wait_Pos = 0.000;
}
//--------------------------------------------
BOOL		CManualDataGantry::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Gantry.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataGantryInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Gantry.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Gantry"));
	xml->IntoElem();

	//Gantry X
	xml->AddElem(_T("m_dGantry_X_Wait_Pos"), Info.m_dGantry_X_Wait_Pos);

	//Gantry Y
	xml->AddElem(_T("m_dGantry_Y_Wait_Pos"), Info.m_dGantry_Y_Wait_Pos);
	xml->AddElem(_T("m_dGantry_Y_Stick_Load_In_Box_Pos"), Info.m_dGantry_Y_Stick_Load_In_Box_Pos);
	xml->AddElem(_T("m_dGantry_Y_Paper_Unload_Pos"), Info.m_dGantry_Y_Paper_Unload_Pos);
	xml->AddElem(_T("m_dGantry_Y_Stick_Unload_To_Stage_Pos"), Info.m_dGantry_Y_Stick_Unload_To_Stage_Pos);
	xml->AddElem(_T("m_dGantry_Y_Stick_Load_In_Stage_Pos"), Info.m_dGantry_Y_Stick_Load_In_Stage_Pos);
	xml->AddElem(_T("m_dGantry_Y_Stick_Unload_To_Box_Pos"), Info.m_dGantry_Y_Stick_Unload_To_Box_Pos);
	//21.02.23 sjc
	xml->AddElem(_T("m_dGantry_Y_Loading_Safe_Pos"), Info.m_dGantry_Y_Loading_Safe_Pos);
	xml->AddElem(_T("m_dGantry_Y_Unloading_Safe_Pos"), Info.m_dGantry_Y_Unloading_Safe_Pos);

	//Gantry Z1 //AOI
	xml->AddElem(_T("m_dGantry_Z1_Wait_Pos"), Info.m_dGantry_Z1_Wait_Pos);
	xml->AddElem(_T("m_dGantry_Z1_Inspection_AOI_Pos"), Info.m_dGantry_Z1_Inspection_AOI_Pos);

	//Gantry Z2 //Zoom + 3D
	xml->AddElem(_T("m_dGantry_Z2_Wait_Pos"), Info.m_dGantry_Z2_Wait_Pos);
	xml->AddElem(_T("m_dGantry_Z1_PreAlign_Pos"), Info.m_dGantry_Z1_PreAlign_Pos);
	xml->AddElem(_T("m_dGantry_Z2_Inspection_3D_Pos"), Info.m_dGantry_Z2_Inspection_3D_Pos);
	xml->AddElem(_T("m_dGantry_Z2_AOI_Review_Pos"), Info.m_dGantry_Z2_AOI_Review_Pos);
	
	
	//3D Camera Main Z -> Z3 = review cam
	xml->AddElem(_T("m_dGantry_Z3_Wait_Pos"), Info.m_dGantry_Z3_Wait_Pos);
	xml->AddElem(_T("m_dGantry_Z1_Inspection_Review_Pos"), Info.m_dGantry_Z1_Inspection_Review_Pos);
	xml->AddElem(_T("m_dGantry_Z3_Mapping_Review_Pos"), Info.m_dGantry_Z3_Mapping_Review_Pos);
	

	//3D Camera Sub Z
	xml->AddElem(_T("m_d3D_Camera_Sub_Z_Wait_Pos"), Info.m_d3D_Camera_Sub_Z_Wait_Pos);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataGantry Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//--------------------------------------------
BOOL		CManualDataGantry::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Gantry.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataGantryInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Gantry.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Gantry")))
	{
		xml->IntoElem();

		//Gantry X	
		if (xml->FindElem(_T("m_dGantry_X_Wait_Pos"))) Info.m_dGantry_X_Wait_Pos = _tstof(xml->GetData());
		
		//Gantry Y	
		if (xml->FindElem(_T("m_dGantry_Y_Wait_Pos"))) Info.m_dGantry_Y_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Y_Stick_Load_In_Box_Pos"))) Info.m_dGantry_Y_Stick_Load_In_Box_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Y_Paper_Unload_Pos"))) Info.m_dGantry_Y_Paper_Unload_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Y_Stick_Unload_To_Stage_Pos"))) Info.m_dGantry_Y_Stick_Unload_To_Stage_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Y_Stick_Load_In_Stage_Pos"))) Info.m_dGantry_Y_Stick_Load_In_Stage_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Y_Stick_Unload_To_Box_Pos"))) Info.m_dGantry_Y_Stick_Unload_To_Box_Pos = _tstof(xml->GetData());
		//21.02.23 sjc
		if (xml->FindElem(_T("m_dGantry_Y_Loading_Safe_Pos"))) Info.m_dGantry_Y_Loading_Safe_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Y_Unloading_Safe_Pos"))) Info.m_dGantry_Y_Unloading_Safe_Pos = _tstof(xml->GetData());
		//Gantry Z1 //aoi
		if (xml->FindElem(_T("m_dGantry_Z1_Wait_Pos"))) Info.m_dGantry_Z1_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Z1_Inspection_AOI_Pos"))) Info.m_dGantry_Z1_Inspection_AOI_Pos = _tstof(xml->GetData());
		
		//Gantry Z2 //zoom 3d
		if (xml->FindElem(_T("m_dGantry_Z2_Wait_Pos"))) Info.m_dGantry_Z2_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Z1_PreAlign_Pos"))) Info.m_dGantry_Z1_PreAlign_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Z2_Inspection_3D_Pos"))) Info.m_dGantry_Z2_Inspection_3D_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Z2_AOI_Review_Pos"))) Info.m_dGantry_Z2_AOI_Review_Pos = _tstof(xml->GetData());
		

		//review
		if (xml->FindElem(_T("m_dGantry_Z3_Wait_Pos"))) Info.m_dGantry_Z3_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Z1_Inspection_Review_Pos"))) Info.m_dGantry_Z1_Inspection_Review_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGantry_Z3_Mapping_Review_Pos"))) Info.m_dGantry_Z3_Mapping_Review_Pos = _tstof(xml->GetData());

		
		//3D Camera Sub Z
		if (xml->FindElem(_T("m_d3D_Camera_Sub_Z_Wait_Pos"))) Info.m_d3D_Camera_Sub_Z_Wait_Pos = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataGantry Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Box
void		CManualDataBox::Init()
{
	//LoadingStageX
	Info.m_dLoadingStageX_Wait_Pos = 0.000;
	Info.m_dLoadingStageX_StickLoad_Pos = 0.000;
	Info.m_dLoadingStageX_StickUnload_Pos = 0.000;

	//LoadingStageY
	Info.m_dLoadingStageY_Wait_Pos = 0.000;
	Info.m_dLoadingStageY_StickLoad_Pos = 0.000;
	Info.m_dLoadingStageY_StickUnload_Pos = 0.000;
	
	//LoadingStageT
	Info.m_dLoadingStageT_Wait_Pos = 0.000;
	Info.m_dLoadingStageT_StickLoad_Pos = 0.000;
	Info.m_dLoadingStageT_StickUnload_Pos = 0.000;

	//BoxAlignCameraYL
	//Info.m_dBoxAlignCameraYL_Wait_Pos = 0.000;
	//Info.m_dBoxAlignCameraYL_Inspection_Pos = 0.000;

	//BoxAlignCameraYR
	//Info.m_dBoxAlignCameraYR_Wait_Pos = 0.000;
	//Info.m_dBoxAlignCameraYR_Inspection_Pos = 0.000;
}
//--------------------------------------------
BOOL		CManualDataBox::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Box.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataBoxInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Box.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Box"));
	xml->IntoElem();

	//Loading Stage X
	xml->AddElem(_T("m_dLoadingStageX_Wait_Pos"), Info.m_dLoadingStageX_Wait_Pos);
	xml->AddElem(_T("m_dLoadingStageX_StickLoad_Pos"), Info.m_dLoadingStageX_StickLoad_Pos);
	xml->AddElem(_T("m_dLoadingStageX_StickUnload_Pos"), Info.m_dLoadingStageX_StickUnload_Pos);

	//Loading Stage Y
	xml->AddElem(_T("m_dLoadingStageY_Wait_Pos"), Info.m_dLoadingStageY_Wait_Pos);
	xml->AddElem(_T("m_dLoadingStageY_StickLoad_Pos"), Info.m_dLoadingStageY_StickLoad_Pos);
	xml->AddElem(_T("m_dLoadingStageY_StickUnload_Pos"), Info.m_dLoadingStageY_StickUnload_Pos);

	//Loading Stage T
	xml->AddElem(_T("m_dLoadingStageT_Wait_Pos"), Info.m_dLoadingStageT_Wait_Pos);
	xml->AddElem(_T("m_dLoadingStageT_StickLoad_Pos"), Info.m_dLoadingStageT_StickLoad_Pos);
	xml->AddElem(_T("m_dLoadingStageT_StickUnload_Pos"), Info.m_dLoadingStageT_StickUnload_Pos);

	//Box Align Camera YL
	//xml->AddElem(_T("m_dBoxAlignCameraYL_Wait_Pos"), Info.m_dBoxAlignCameraYL_Wait_Pos);
	//xml->AddElem(_T("m_dBoxAlignCameraYL_Inspection_Pos"), Info.m_dBoxAlignCameraYL_Inspection_Pos);

	//Box Align Camera YR
	//xml->AddElem(_T("m_dBoxAlignCameraYR_Wait_Pos"), Info.m_dBoxAlignCameraYR_Wait_Pos);
	//xml->AddElem(_T("m_dBoxAlignCameraYR_Inspection_Pos"), Info.m_dBoxAlignCameraYR_Inspection_Pos);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataBox Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//--------------------------------------------
BOOL		CManualDataBox::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Box.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataBoxInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Box.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Box")))
	{
		xml->IntoElem();

		//Loading Stage X
		if (xml->FindElem(_T("m_dLoadingStageX_Wait_Pos"))) Info.m_dLoadingStageX_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoadingStageX_StickLoad_Pos"))) Info.m_dLoadingStageX_StickLoad_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoadingStageX_StickUnload_Pos"))) Info.m_dLoadingStageX_StickUnload_Pos = _tstof(xml->GetData());

		//Loading Stage Y
		if (xml->FindElem(_T("m_dLoadingStageY_Wait_Pos"))) Info.m_dLoadingStageY_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoadingStageY_StickLoad_Pos"))) Info.m_dLoadingStageY_StickLoad_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoadingStageY_StickUnload_Pos"))) Info.m_dLoadingStageY_StickUnload_Pos = _tstof(xml->GetData());

		//Loading Stage T
		if (xml->FindElem(_T("m_dLoadingStageT_Wait_Pos"))) Info.m_dLoadingStageT_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoadingStageT_StickLoad_Pos"))) Info.m_dLoadingStageT_StickLoad_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoadingStageT_StickUnload_Pos"))) Info.m_dLoadingStageT_StickUnload_Pos = _tstof(xml->GetData());

		//Box Align Camera YL
		//if (xml->FindElem(_T("m_dBoxAlignCameraYL_Wait_Pos"))) Info.m_dBoxAlignCameraYL_Wait_Pos = _tstof(xml->GetData());
		//if (xml->FindElem(_T("m_dBoxAlignCameraYL_Inspection_Pos"))) Info.m_dBoxAlignCameraYL_Inspection_Pos = _tstof(xml->GetData());

		//Box Align Camera YR
		//if (xml->FindElem(_T("m_dBoxAlignCameraYR_Wait_Pos"))) Info.m_dBoxAlignCameraYR_Wait_Pos = _tstof(xml->GetData());
		//if (xml->FindElem(_T("m_dBoxAlignCameraYR_Inspection_Pos"))) Info.m_dBoxAlignCameraYR_Inspection_Pos = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataBox Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Loader
void		CManualDataLoader::Init()
{
	//Loader Z
	Info.m_dLoaderZ_Wait_Pos = 0.000;
	Info.m_dLoaderZ_StickLoadInBox1st_Pos = 0.000;
	Info.m_dLoaderZ_Vibration_Pos = 0.000;
	Info.m_dLoaderZ_PaperUnloader_Pos = 0.000;
	Info.m_dLoaderZ_StickUnloadToStage_Pos = 0.000;
	Info.m_dLoaderZ_StickLoadInStage1st_Pos = 0.000;
	
	Info.m_dLoaderZ_StickUnoadToBox_Pos = 0.000;

	Info.m_nLoaderZ_StepDownCount = 1;
	Info.m_dLoaderZ_StepDownOffset = 0.0;
	Info.m_dLoaderZ_StepUpOffset = 0.0;
	Info.m_nLoaderZ_VibrationCount = 3;
	Info.m_dLoaderZ_VibrationOffset = 0.000;
	Info.m_dLoaderZ_VibrationVel = 100.0;
	
	//21.02.23 sjc
	//Loader Y
	Info.m_dLoaderY_Wait_Pos = 0.000;
	Info.m_dLoaderY_Stick_Load_Pos = 0.000;
	Info.m_dLoaderY_Stick_Unload_Pos = 0.000;
	Info.m_dLoaderY_Paper_Load_Pos = 0.000;
	Info.m_dLoaderY_Paper_Unload_Pos = 0.000;
	Info.m_dLoaderY_Inspection_Pos = 0.000;

	//Loader X
	Info.m_dLoaderX_Wait_Pos = 0.000;
	Info.m_dLoaderX_Tension_Offset = 0.000;

	//21.02.26 sjc
	Info.m_dLoaderZ_Inspection_Pos = 0.000;
	//21.02.28 sjc
	Info.m_dLoaderZL_Wait_Pos = 0.000;
	Info.m_dLoaderZR_Wait_Pos = 0.000;
	Info.m_dLoaderZL_Down_Pos = 0.000;
	Info.m_dLoaderZR_Down_Pos = 0.000;

}
//--------------------------------------------
BOOL		CManualDataLoader::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Loader.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataLoaderInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Loader.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Loader"));
	xml->IntoElem();

#pragma region //Loader Z
	xml->AddElem(_T("m_dLoaderZ_Wait_Pos"), Info.m_dLoaderZ_Wait_Pos);
	xml->AddElem(_T("m_dLoaderZ_StickLoadInBox1st_Pos"), Info.m_dLoaderZ_StickLoadInBox1st_Pos);
	xml->AddElem(_T("m_dLoaderZ_Vibration_Pos"), Info.m_dLoaderZ_Vibration_Pos);
	xml->AddElem(_T("m_dLoaderZ_PaperUnloader_Pos"), Info.m_dLoaderZ_PaperUnloader_Pos);
	xml->AddElem(_T("m_dLoaderZ_StickUnloadToStage_Pos"), Info.m_dLoaderZ_StickUnloadToStage_Pos);

	xml->AddElem(_T("m_dLoaderZ_StickLoadInStage1st_Pos"), Info.m_dLoaderZ_StickLoadInStage1st_Pos);	
	xml->AddElem(_T("m_dLoaderZ_StickUnoadToBox_Pos"), Info.m_dLoaderZ_StickUnoadToBox_Pos);	
	
	xml->AddElem(_T("m_nLoaderZ_StepDownCount"), Info.m_nLoaderZ_StepDownCount);
	xml->AddElem(_T("m_dLoaderZ_StepDownOffset"), Info.m_dLoaderZ_StepDownOffset);
	xml->AddElem(_T("m_dLoaderZ_StepUpOffset"), Info.m_dLoaderZ_StepUpOffset);
	xml->AddElem(_T("m_nLoaderZ_VibrationCount"), Info.m_nLoaderZ_VibrationCount);
	xml->AddElem(_T("m_dLoaderZ_VibrationOffset"), Info.m_dLoaderZ_VibrationOffset); //KJT 20210317
	xml->AddElem(_T("m_dLoaderZ_VibrationVel"), Info.m_dLoaderZ_VibrationVel);

#pragma endregion

#pragma region //Loader Sub Z
	//21.02.28 sjc
	xml->AddElem(_T("m_dLoaderZL_Wait_Pos"), Info.m_dLoaderZL_Wait_Pos);
	xml->AddElem(_T("m_dLoaderZR_Wait_Pos"), Info.m_dLoaderZR_Wait_Pos);
	xml->AddElem(_T("m_dLoaderZL_Down_Pos"), Info.m_dLoaderZL_Down_Pos);
	xml->AddElem(_T("m_dLoaderZR_Down_Pos"), Info.m_dLoaderZR_Down_Pos);
#pragma endregion

#pragma region //Loader X
	xml->AddElem(_T("m_dLoaderX_Wait_Pos"), Info.m_dLoaderX_Wait_Pos);
	xml->AddElem(_T("m_dLoaderX_Tension_Offset"), Info.m_dLoaderX_Tension_Offset);
#pragma endregion
#pragma region//Loader Y
	//21.02.23 sjc
	xml->AddElem(_T("m_dLoaderY_Wait_Pos"), Info.m_dLoaderY_Wait_Pos);
	xml->AddElem(_T("m_dLoaderY_Stick_Load_Pos"), Info.m_dLoaderY_Stick_Load_Pos);
	xml->AddElem(_T("m_dLoaderY_Stick_Unload_Pos"), Info.m_dLoaderY_Stick_Unload_Pos);
	xml->AddElem(_T("m_dLoaderY_Paper_Load_Pos"), Info.m_dLoaderY_Paper_Load_Pos);
	xml->AddElem(_T("m_dLoaderY_Paper_Unload_Pos"), Info.m_dLoaderY_Paper_Unload_Pos);
	xml->AddElem(_T("m_dLoaderY_Inspection_Pos"), Info.m_dLoaderY_Inspection_Pos);
	xml->AddElem(_T("m_dLoaderZ_Inspection_Pos"), Info.m_dLoaderZ_Inspection_Pos);	
#pragma endregion
	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataLoader Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//--------------------------------------------
BOOL		CManualDataLoader::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Loader.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataLoaderInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Loader.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Loader")))
	{
		xml->IntoElem();

#pragma region //Loader Z
		if (xml->FindElem(_T("m_dLoaderZ_Wait_Pos"))) Info.m_dLoaderZ_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZ_StickLoadInBox1st_Pos"))) Info.m_dLoaderZ_StickLoadInBox1st_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZ_Vibration_Pos"))) Info.m_dLoaderZ_Vibration_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZ_PaperUnloader_Pos"))) Info.m_dLoaderZ_PaperUnloader_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZ_StickUnloadToStage_Pos"))) Info.m_dLoaderZ_StickUnloadToStage_Pos = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_dLoaderZ_StickLoadInStage1st_Pos"))) Info.m_dLoaderZ_StickLoadInStage1st_Pos = _tstof(xml->GetData());		
		if (xml->FindElem(_T("m_dLoaderZ_StickUnoadToBox_Pos"))) Info.m_dLoaderZ_StickUnoadToBox_Pos = _tstof(xml->GetData());
		
		if (xml->FindElem(_T("m_nLoaderZ_StepDownCount"))) Info.m_nLoaderZ_StepDownCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZ_StepDownOffset"))) Info.m_dLoaderZ_StepDownOffset = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZ_StepUpOffset"))) Info.m_dLoaderZ_StepUpOffset = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_nLoaderZ_VibrationCount"))) Info.m_nLoaderZ_VibrationCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZ_VibrationOffset"))) Info.m_dLoaderZ_VibrationOffset = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZ_VibrationVel"))) Info.m_dLoaderZ_VibrationVel = _tstof(xml->GetData());

#pragma endregion

#pragma region //Loader Sub Z
		//21.02.28 sjc
		if (xml->FindElem(_T("m_dLoaderZL_Wait_Pos"))) Info.m_dLoaderZL_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZR_Wait_Pos"))) Info.m_dLoaderZR_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZL_Down_Pos"))) Info.m_dLoaderZL_Down_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderZR_Down_Pos"))) Info.m_dLoaderZR_Down_Pos = _tstof(xml->GetData());
#pragma endregion

#pragma region //Loader X
		if (xml->FindElem(_T("m_dLoaderX_Wait_Pos"))) Info.m_dLoaderX_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderX_Tension_Offset"))) Info.m_dLoaderX_Tension_Offset = _tstof(xml->GetData());
#pragma endregion
#pragma region//Loader Y
		if (xml->FindElem(_T("m_dLoaderY_Wait_Pos"))) Info.m_dLoaderY_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderY_Stick_Load_Pos"))) Info.m_dLoaderY_Stick_Load_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderY_Stick_Unload_Pos"))) Info.m_dLoaderY_Stick_Unload_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderY_Paper_Load_Pos"))) Info.m_dLoaderY_Paper_Load_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderY_Paper_Unload_Pos"))) Info.m_dLoaderY_Paper_Unload_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dLoaderY_Inspection_Pos"))) Info.m_dLoaderY_Inspection_Pos = _tstof(xml->GetData());
#pragma endregion
		//21.02.26 sjc
		if (xml->FindElem(_T("m_dLoaderZ_Inspection_Pos"))) Info.m_dLoaderZ_Inspection_Pos = _tstof(xml->GetData());
		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataLoader Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Inspect
void		CManualDataInspect::Init()
{
	//InspectionStage X
	Info.m_dInspectionStageX_Wait_Pos = 0.000;
	Info.m_dInspectionStageX_StickLoad_Pos = 0.000;
	Info.m_dInspectionStageX_StickUnload_Pos = 0.000;

	//InspectionStage Y
	Info.m_dInspectionStageY_Wait_Pos = 0.000;
	Info.m_dInspectionStageY_StickLoad_Pos = 0.000;
	Info.m_dInspectionStageY_StickUnload_Pos = 0.000;

	//InspectionStage T
	Info.m_dInspectionStageT_Wait_Pos = 0.000;
	Info.m_dInspectionStageT_StickLoad_Pos = 0.000;
	Info.m_dInspectionStageT_StickUnload_Pos = 0.000;

	//BackLightX
	Info.m_dBackLightX_Wait_Pos = 0.000;
}
//--------------------------------------------
BOOL		CManualDataInspect::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Inspect.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataInspectInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Inspect.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Inspect"));
	xml->IntoElem();

	//Inspection Stage X
	xml->AddElem(_T("m_dInspectionStageX_Wait_Pos"), Info.m_dInspectionStageX_Wait_Pos);
	xml->AddElem(_T("m_dInspectionStageX_StickLoad_Pos"), Info.m_dInspectionStageX_StickLoad_Pos);
	xml->AddElem(_T("m_dInspectionStageX_StickUnload_Pos"), Info.m_dInspectionStageX_StickUnload_Pos);

	//Inspection Stage Y
	xml->AddElem(_T("m_dInspectionStageY_Wait_Pos"), Info.m_dInspectionStageY_Wait_Pos);
	xml->AddElem(_T("m_dInspectionStageY_StickLoad_Pos"), Info.m_dInspectionStageY_StickLoad_Pos);
	xml->AddElem(_T("m_dInspectionStageY_StickUnload_Pos"), Info.m_dInspectionStageY_StickUnload_Pos);

	//Inspection Stage T
	xml->AddElem(_T("m_dInspectionStageT_Wait_Pos"), Info.m_dInspectionStageT_Wait_Pos);
	xml->AddElem(_T("m_dInspectionStageT_StickLoad_Pos"), Info.m_dInspectionStageT_StickLoad_Pos);
	xml->AddElem(_T("m_dInspectionStageT_StickUnload_Pos"), Info.m_dInspectionStageT_StickUnload_Pos);

	//BackLight X
	xml->AddElem(_T("m_dBackLightX_Wait_Pos"), Info.m_dBackLightX_Wait_Pos);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataInspect Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//--------------------------------------------
BOOL		CManualDataInspect::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Inspect.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataInspectInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Inspect.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Inspect")))
	{
		xml->IntoElem();

		//Inspection Stage X
		if (xml->FindElem(_T("m_dInspectionStageX_Wait_Pos"))) Info.m_dInspectionStageX_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dInspectionStageX_StickLoad_Pos"))) Info.m_dInspectionStageX_StickLoad_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dInspectionStageX_StickUnload_Pos"))) Info.m_dInspectionStageX_StickUnload_Pos = _tstof(xml->GetData());

		//Inspection Stage Y
		if (xml->FindElem(_T("m_dInspectionStageY_Wait_Pos"))) Info.m_dInspectionStageY_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dInspectionStageY_StickLoad_Pos"))) Info.m_dInspectionStageY_StickLoad_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dInspectionStageY_StickUnload_Pos"))) Info.m_dInspectionStageY_StickUnload_Pos = _tstof(xml->GetData());

		//Inspection Stage T
		if (xml->FindElem(_T("m_dInspectionStageT_Wait_Pos"))) Info.m_dInspectionStageT_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dInspectionStageT_StickLoad_Pos"))) Info.m_dInspectionStageT_StickLoad_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dInspectionStageT_StickUnload_Pos"))) Info.m_dInspectionStageT_StickUnload_Pos = _tstof(xml->GetData());

		//BackLight X
		if (xml->FindElem(_T("m_dBackLightX_Wait_Pos"))) Info.m_dBackLightX_Wait_Pos = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataInspect Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Clamp
void CManualDataClamp::Init()
{
	Info.m_dClampTorque = 0.0;
}
BOOL CManualDataClamp::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Clamp.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataClampInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Clamp.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Clamp"));
	xml->IntoElem();

	//Clamp Torque
	xml->AddElem(_T("m_dClampTorque"), Info.m_dClampTorque);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataClamp Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
BOOL CManualDataClamp::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Clamp.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataClampInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Clamp.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Clamp")))
	{
		xml->IntoElem();

		//Clamp Torque
		if (xml->FindElem(_T("m_dClampTorque"))) Info.m_dClampTorque = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataClamp Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Stretch
void CManualDataStretch::Init()
{
}
BOOL CManualDataStretch::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Stretch.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataStretchInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Stretch.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Stretch"));
	xml->IntoElem();
	//21.04.03 del
	//for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
		//Stretch Left
		Str.Format(_T("m_dStretchLeft_WaitPos_1"));
		xml->AddElem(Str, Info.m_dStretchLeft_1_WaitPos);
		Str.Format(_T("m_dStretchLeft_ForwardPos_1"));
		xml->AddElem(Str, Info.m_dStretchLeft_1_ForwardPos);
		Str.Format(_T("m_dStretchLeft_BackwardPos_1"));
		xml->AddElem(Str, Info.m_dStretchLeft_1_BackwardPos);
		//21.04.03 sjc
		Str.Format(_T("m_dStretchLeft_WaitPos_2"));
		xml->AddElem(Str, Info.m_dStretchLeft_2_WaitPos);
		Str.Format(_T("m_dStretchLeft_ForwardPos_2"));
		xml->AddElem(Str, Info.m_dStretchLeft_2_ForwardPos);
		Str.Format(_T("m_dStretchLeft_BackwardPos_2"));
		xml->AddElem(Str, Info.m_dStretchLeft_2_BackwardPos);

		Str.Format(_T("m_dStretchLeft_WaitPos_3"));
		xml->AddElem(Str, Info.m_dStretchLeft_3_WaitPos);
		Str.Format(_T("m_dStretchLeft_ForwardPos_3"));
		xml->AddElem(Str, Info.m_dStretchLeft_3_ForwardPos);
		Str.Format(_T("m_dStretchLeft_BackwardPos_3"));
		xml->AddElem(Str, Info.m_dStretchLeft_3_BackwardPos);
		//

		//Stretch Right
		Str.Format(_T("m_dStretchRight_WaitPos_1"));
		xml->AddElem(Str, Info.m_dStretchRight_1_WaitPos);
		Str.Format(_T("m_dStretchRight_ForwardPos_1"));
		xml->AddElem(Str, Info.m_dStretchRight_1_ForwardPos);
		Str.Format(_T("m_dStretchRight_BackwardPos_1"));
		xml->AddElem(Str, Info.m_dStretchRight_1_BackwardPos);
		//21.04.03 sjc
		Str.Format(_T("m_dStretchRight_WaitPos_2"));
		xml->AddElem(Str, Info.m_dStretchRight_2_WaitPos);
		Str.Format(_T("m_dStretchRight_ForwardPos_2"));
		xml->AddElem(Str, Info.m_dStretchRight_2_ForwardPos);
		Str.Format(_T("m_dStretchRight_BackwardPos_2"));
		xml->AddElem(Str, Info.m_dStretchRight_2_BackwardPos);

		Str.Format(_T("m_dStretchRight_WaitPos_3"));
		xml->AddElem(Str, Info.m_dStretchRight_3_WaitPos);
		Str.Format(_T("m_dStretchRight_ForwardPos_3"));
		xml->AddElem(Str, Info.m_dStretchRight_3_ForwardPos);
		Str.Format(_T("m_dStretchRight_BackwardPos_3"));
		xml->AddElem(Str, Info.m_dStretchRight_3_BackwardPos);
		//
	//}

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataStretch Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
BOOL CManualDataStretch::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Stretch.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataStretchInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Stretch.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Stretch")))
	{
		xml->IntoElem();
		//21.04.03 sjc del
		//for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		//{
			//Stretch Left
			Str.Format(_T("m_dStretchLeft_WaitPos_1"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_1_WaitPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchLeft_ForwardPos_1"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_1_ForwardPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchLeft_BackwardPos_1"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_1_BackwardPos = _tstof(xml->GetData());

			//21.04.03 sjc
			Str.Format(_T("m_dStretchLeft_WaitPos_2"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_2_WaitPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchLeft_ForwardPos_2"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_2_ForwardPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchLeft_BackwardPos_2"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_2_BackwardPos = _tstof(xml->GetData());

			Str.Format(_T("m_dStretchLeft_WaitPos_3"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_3_WaitPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchLeft_ForwardPos_3"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_3_ForwardPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchLeft_BackwardPos_3"));
			if (xml->FindElem(Str)) Info.m_dStretchLeft_3_BackwardPos = _tstof(xml->GetData());

			//Stretch Right
			Str.Format(_T("m_dStretchRight_WaitPos_1"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_1_WaitPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchRight_ForwardPos_1"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_1_ForwardPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchRight_BackwardPos_1"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_1_BackwardPos = _tstof(xml->GetData());

			//21.04.03 sjc
			Str.Format(_T("m_dStretchRight_WaitPos_2"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_2_WaitPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchRight_ForwardPos_2"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_2_ForwardPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchRight_BackwardPos_2"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_2_BackwardPos = _tstof(xml->GetData());

			Str.Format(_T("m_dStretchRight_WaitPos_3"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_3_WaitPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchRight_ForwardPos_3"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_3_ForwardPos = _tstof(xml->GetData());
			Str.Format(_T("m_dStretchRight_BackwardPos_3"));
			if (xml->FindElem(Str)) Info.m_dStretchRight_3_BackwardPos = _tstof(xml->GetData());
		//}

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataStretch Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Pitch
void CManualDataPitch::Init()
{
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		//Pitch Left
		Info.m_dPitchLeft_WaitPos[i] = 0.0;
		//Pitch Right
		Info.m_dPitchRight_WaitPos[i] = 0.0;
	}
}
BOOL CManualDataPitch::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Pitch.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataPitchInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Pitch.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Pitch"));
	xml->IntoElem();

	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		//Pitch Left
		Str.Format(_T("m_dPitchLeft_WaitPos_%d"), i);
		xml->AddElem(Str, Info.m_dPitchLeft_WaitPos[i]);

		//Pitch Right
		Str.Format(_T("m_dPitchRight_WaitPos_%d"), i);
		xml->AddElem(Str, Info.m_dPitchRight_WaitPos[i]);
	}

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataPitch Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
BOOL CManualDataPitch::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	int i = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Pitch.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataPitchInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Pitch.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Pitch")))
	{
		xml->IntoElem();

		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			//Pitch Left
			Str.Format(_T("m_dPitchLeft_WaitPos_%d"), i);
			if (xml->FindElem(Str)) Info.m_dPitchLeft_WaitPos[i] = _tstof(xml->GetData());

			//Pitch Right
			Str.Format(_T("m_dPitchRight_WaitPos_%d"), i);
			if (xml->FindElem(Str)) Info.m_dPitchRight_WaitPos[i] = _tstof(xml->GetData());
		}

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataPitch Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //GripperZ
void		CManualDataGripperZ::Init()
{
	Info.m_dGripperLeftZ_WaitPos = 0.0;
	Info.m_dGripperLeftZ_LoadingPos = 0.0;
	Info.m_dGripperLeftZ_ClampPos = 0.0;
	Info.m_dGripperLeftZ_TensionPos = 0.0;
	Info.m_dGripperLeftZ_UnclampPos = 0.0;

	Info.m_dGripperRightZ_WaitPos = 0.0;
	Info.m_dGripperRightZ_LoadingPos = 0.0;
	Info.m_dGripperRightZ_ClampPos = 0.0;
	Info.m_dGripperRightZ_TensionPos = 0.0;
	Info.m_dGripperRightZ_UnclampPos = 0.0;
}
BOOL		CManualDataGripperZ::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\GripperZ.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataGripperZInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\GripperZ.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("GripperZ"));
	xml->IntoElem();

	xml->AddElem(_T("m_dGripperLeftZ_WaitPos"), Info.m_dGripperLeftZ_WaitPos);
	xml->AddElem(_T("m_dGripperLeftZ_LoadingPos"), Info.m_dGripperLeftZ_LoadingPos);
	xml->AddElem(_T("m_dGripperLeftZ_ClampPos"), Info.m_dGripperLeftZ_ClampPos);
	xml->AddElem(_T("m_dGripperLeftZ_TensionPos"), Info.m_dGripperLeftZ_TensionPos);
	xml->AddElem(_T("m_dGripperLeftZ_UnclampPos"), Info.m_dGripperLeftZ_UnclampPos);

	xml->AddElem(_T("m_dGripperRightZ_WaitPos"), Info.m_dGripperRightZ_WaitPos);
	xml->AddElem(_T("m_dGripperRightZ_LoadingPos"), Info.m_dGripperRightZ_LoadingPos);
	xml->AddElem(_T("m_dGripperRightZ_ClampPos"), Info.m_dGripperRightZ_ClampPos);
	xml->AddElem(_T("m_dGripperRightZ_TensionPos"), Info.m_dGripperRightZ_TensionPos);
	xml->AddElem(_T("m_dGripperRightZ_UnclampPos"), Info.m_dGripperRightZ_UnclampPos);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataGripperZ Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
BOOL		CManualDataGripperZ::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\GripperZ.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataGripperZInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\GripperZ.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("GripperZ")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("m_dGripperLeftZ_WaitPos"))) Info.m_dGripperLeftZ_WaitPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGripperLeftZ_LoadingPos"))) Info.m_dGripperLeftZ_LoadingPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGripperLeftZ_ClampPos"))) Info.m_dGripperLeftZ_ClampPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGripperLeftZ_TensionPos"))) Info.m_dGripperLeftZ_TensionPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGripperLeftZ_UnclampPos"))) Info.m_dGripperLeftZ_UnclampPos = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_dGripperRightZ_WaitPos"))) Info.m_dGripperRightZ_WaitPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGripperRightZ_LoadingPos"))) Info.m_dGripperRightZ_LoadingPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGripperRightZ_ClampPos"))) Info.m_dGripperRightZ_ClampPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGripperRightZ_TensionPos"))) Info.m_dGripperRightZ_TensionPos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dGripperRightZ_UnclampPos"))) Info.m_dGripperRightZ_UnclampPos = _tstof(xml->GetData());
		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataGripperZ Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Unloader
void		CManualDataUnloader::Init()
{
	//Unloader Z
	Info.m_dUnloaderZ_Wait_Pos = 0.000;
	Info.m_dUnloaderZ_Load_In_Stage_Pos = 0.000;
	Info.m_dUnloaderZ_Unload_To_Cst_Pos = 0.000;
	   	
	Info.m_dUnloaderZ_Load_In_Cst_Pos = 0.000;
	Info.m_dUnloaderZ_Unload_To_Stage_Pos = 0.000;
	//21.02.15 SJC
	Info.m_dUnloaderZ_Paper_Load_Pos = 0.000;
	Info.m_dUnloaderZ_Paper_Unload_Pos = 0.000;
	Info.m_dUnloaderZ_Vibration_Pos = 0.000;	

	Info.m_nUnloaderZ_StepDownCount = 1;
	Info.m_dUnloaderZ_StepDownOffset = 0.0;
	Info.m_dUnloaderZ_StepUpOffset = 0.0;
	Info.m_nUnloaderZ_VibrationCount = 3;
	Info.m_dUnloaderZ_VibrationOffset = 0.0; //KJT 20210317
	Info.m_dUnloaderZ_VibrationVel = 100.0;


	//Paper Unloader Y
	Info.m_dUnloaderY_Wait_Pos = 0.000;
	Info.m_dUnloaderY_Load_In_Stage_Pos = 0.000;
	Info.m_dUnloaderY_Unload_To_Cst_Pos = 0.000;
	Info.m_dUnloaderY_Load_In_Cst_Pos = 0.000;
	Info.m_dUnloaderY_Unload_To_Stage_Pos = 0.000;
	//21.02.15 SJC
	Info.m_dUnloaderY_Paper_Load_Pos = 0.000;
	Info.m_dUnloaderY_Paper_Load_Waiting_Pos = 0.000;
	Info.m_dUnloaderY_Paper_Unload_Pos = 0.000;
	Info.m_dUnloaderY_Cassette_Safety_Pos = 0.0;

	//Paper Unloader X
	Info.m_dPaperUnloader_XL_Wait_Pos = 0.000;
	Info.m_dPaperUnloader_XL_Tension_Offset = 0.000;
	Info.m_dPaperUnloader_XR_Wait_Pos = 0.000;
	Info.m_dPaperUnloader_XR_Tension_Offset = 0.000;

	//Mask Unloaer X
	Info.m_dUnloaderX_Wait_Pos = 0.000;
	Info.m_dUnloaderX_Tension_Offset = 0.000;
		
	//21.02.25 sjc
	Info.m_dUnloaderZL_Wait_Pos = 0.000;
	Info.m_dUnloaderZL_Down_Pos = 0.000;
	Info.m_dUnloaderZR_Wait_Pos = 0.000;
	Info.m_dUnloaderZR_Down_Pos = 0.000;

	Info.m_dUnloaderZL_Paper_Load_Pos = 0.000;
	Info.m_dUnloaderZR_Paper_Load_Pos = 0.000;
	Info.m_dUnloaderZL_Paper_Unload_Pos = 0.000;
	Info.m_dUnloaderZR_Paper_Unload_Pos = 0.000;
}
//--------------------------------------------
BOOL		CManualDataUnloader::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Unloader.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataUnloaderInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Unloader.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Unloader"));
	xml->IntoElem();

	//Unloader Z
	xml->AddElem(_T("m_dUnloaderZ_Wait_Pos"), Info.m_dUnloaderZ_Wait_Pos);
	xml->AddElem(_T("m_dUnloaderZ_Load_In_Stage_Pos"), Info.m_dUnloaderZ_Load_In_Stage_Pos);
	xml->AddElem(_T("m_dUnloaderZ_Unload_To_Cst_Pos"), Info.m_dUnloaderZ_Unload_To_Cst_Pos);
	xml->AddElem(_T("m_dUnloaderZ_Load_In_Cst_Pos"), Info.m_dUnloaderZ_Load_In_Cst_Pos);
	xml->AddElem(_T("m_dUnloaderZ_Unload_To_Stage_Pos"), Info.m_dUnloaderZ_Unload_To_Stage_Pos);

	xml->AddElem(_T("m_dUnloaderZ_Paper_Load_Pos"), Info.m_dUnloaderZ_Paper_Load_Pos);
	xml->AddElem(_T("m_dUnloaderZ_Paper_Unload_Pos"), Info.m_dUnloaderZ_Paper_Unload_Pos);
	xml->AddElem(_T("m_dUnloaderZ_Vibration_Pos"), Info.m_dUnloaderZ_Vibration_Pos);
	
	xml->AddElem(_T("m_nUnloaderZ_StepDownCount"), Info.m_nUnloaderZ_StepDownCount);
	xml->AddElem(_T("m_dUnloaderZ_StepDownOffset"), Info.m_dUnloaderZ_StepDownOffset);
	xml->AddElem(_T("m_dUnloaderZ_StepUpOffset"), Info.m_dUnloaderZ_StepUpOffset);
	xml->AddElem(_T("m_nUnloaderZ_VibrationCount"), Info.m_nUnloaderZ_VibrationCount);
	xml->AddElem(_T("m_dUnloaderZ_VibrationOffset"), Info.m_dUnloaderZ_VibrationOffset); //KJT 20210317
	xml->AddElem(_T("m_dUnloaderZ_VibrationVel"), Info.m_dUnloaderZ_VibrationVel);

	//Paper Unloader Y
	xml->AddElem(_T("m_dUnloaderY_Wait_Pos"), Info.m_dUnloaderY_Wait_Pos);
	xml->AddElem(_T("m_dUnloaderY_Load_In_Stage_Pos"), Info.m_dUnloaderY_Load_In_Stage_Pos);
	xml->AddElem(_T("m_dUnloaderY_Unload_To_Cst_Pos"), Info.m_dUnloaderY_Unload_To_Cst_Pos);
	xml->AddElem(_T("m_dUnloaderY_Load_In_Cst_Pos"), Info.m_dUnloaderY_Load_In_Cst_Pos);
	xml->AddElem(_T("m_dUnloaderY_Unload_To_Stage_Pos"), Info.m_dUnloaderY_Unload_To_Stage_Pos);
	//21.02.15 SJC
	xml->AddElem(_T("m_dUnloaderY_Paper_Load_Pos"), Info.m_dUnloaderY_Paper_Load_Pos);
	xml->AddElem(_T("m_dUnloaderY_Paper_Load_Waiting_Pos"), Info.m_dUnloaderY_Paper_Load_Waiting_Pos);
	xml->AddElem(_T("m_dUnloaderY_Paper_Unload_Pos"), Info.m_dUnloaderY_Paper_Unload_Pos);		
	xml->AddElem(_T("m_dUnloaderY_Cassette_Safety_Pos"), Info.m_dUnloaderY_Cassette_Safety_Pos);
	//

	//Paper Unloader X
	xml->AddElem(_T("m_dPaperUnloader_XL_Wait_Pos"), Info.m_dPaperUnloader_XL_Wait_Pos);
	xml->AddElem(_T("m_dPaperUnloader_XL_Tension_Offset"), Info.m_dPaperUnloader_XL_Tension_Offset);
	xml->AddElem(_T("m_dPaperUnloader_XR_Wait_Pos"), Info.m_dPaperUnloader_XR_Wait_Pos);
	xml->AddElem(_T("m_dPaperUnloader_XR_Tension_Offset"), Info.m_dPaperUnloader_XR_Tension_Offset);

	//Mask Unloader X
	xml->AddElem(_T("m_dUnloaderX_Wait_Pos"), Info.m_dUnloaderX_Wait_Pos);
	xml->AddElem(_T("m_dUnloaderX_Tension_Offset"), Info.m_dUnloaderX_Tension_Offset);
		
	//21.02.25 sjc
	xml->AddElem(_T("m_dUnloaderZL_Wait_Pos"), Info.m_dUnloaderZL_Wait_Pos);
	xml->AddElem(_T("m_dUnloaderZL_Down_Pos"), Info.m_dUnloaderZL_Down_Pos);
	xml->AddElem(_T("m_dUnloaderZR_Wait_Pos"), Info.m_dUnloaderZR_Wait_Pos);
	xml->AddElem(_T("m_dUnloaderZR_Down_Pos"), Info.m_dUnloaderZR_Down_Pos);

	xml->AddElem(_T("m_dUnloaderZL_Paper_Load_Pos"), Info.m_dUnloaderZL_Paper_Load_Pos);
	xml->AddElem(_T("m_dUnloaderZR_Paper_Load_Pos"), Info.m_dUnloaderZR_Paper_Load_Pos);
	xml->AddElem(_T("m_dUnloaderZL_Paper_Unload_Pos"), Info.m_dUnloaderZL_Paper_Unload_Pos);
	xml->AddElem(_T("m_dUnloaderZR_Paper_Unload_Pos"), Info.m_dUnloaderZR_Paper_Unload_Pos);

	//
	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataUnloader Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//--------------------------------------------
BOOL		CManualDataUnloader::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Unloader.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataUnloaderInfo));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Unloader.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Unloader")))
	{
		xml->IntoElem();

		//Unloader Z
		if (xml->FindElem(_T("m_dUnloaderZ_Wait_Pos"))) Info.m_dUnloaderZ_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_Load_In_Stage_Pos"))) Info.m_dUnloaderZ_Load_In_Stage_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_Unload_To_Cst_Pos"))) Info.m_dUnloaderZ_Unload_To_Cst_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_Load_In_Cst_Pos"))) Info.m_dUnloaderZ_Load_In_Cst_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_Unload_To_Stage_Pos"))) Info.m_dUnloaderZ_Unload_To_Stage_Pos = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_dUnloaderZ_Paper_Load_Pos"))) Info.m_dUnloaderZ_Paper_Load_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_Paper_Unload_Pos"))) Info.m_dUnloaderZ_Paper_Unload_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_Vibration_Pos"))) Info.m_dUnloaderZ_Vibration_Pos = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_nUnloaderZ_StepDownCount"))) Info.m_nUnloaderZ_StepDownCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_StepDownOffset"))) Info.m_dUnloaderZ_StepDownOffset = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_StepUpOffset"))) Info.m_dUnloaderZ_StepUpOffset = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_nUnloaderZ_VibrationCount"))) Info.m_nUnloaderZ_VibrationCount = _tstoi(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_VibrationOffset"))) Info.m_dUnloaderZ_VibrationOffset = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZ_VibrationVel"))) Info.m_dUnloaderZ_VibrationVel = _tstof(xml->GetData());
			

		//Paper Unloader Y
		if (xml->FindElem(_T("m_dUnloaderY_Wait_Pos"))) Info.m_dUnloaderY_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderY_Load_In_Stage_Pos"))) Info.m_dUnloaderY_Load_In_Stage_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderY_Unload_To_Cst_Pos"))) Info.m_dUnloaderY_Unload_To_Cst_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderY_Load_In_Cst_Pos"))) Info.m_dUnloaderY_Load_In_Cst_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderY_Unload_To_Stage_Pos"))) Info.m_dUnloaderY_Unload_To_Stage_Pos = _tstof(xml->GetData());
		//21.02.15 SJC
		if (xml->FindElem(_T("m_dUnloaderY_Paper_Load_Pos"))) Info.m_dUnloaderY_Paper_Load_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderY_Paper_Load_Waiting_Pos"))) Info.m_dUnloaderY_Paper_Load_Waiting_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderY_Paper_Unload_Pos"))) Info.m_dUnloaderY_Paper_Unload_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderY_Cassette_Safety_Pos"))) Info.m_dUnloaderY_Cassette_Safety_Pos = _tstof(xml->GetData());
		//

		//Paper Unloader X
		if (xml->FindElem(_T("m_dPaperUnloader_XL_Wait_Pos"))) Info.m_dPaperUnloader_XL_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dPaperUnloader_XL_Tension_Offset"))) Info.m_dPaperUnloader_XL_Tension_Offset = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dPaperUnloader_XR_Wait_Pos"))) Info.m_dPaperUnloader_XR_Wait_Pos = _tstof(xml->GetData());		
		if (xml->FindElem(_T("m_dPaperUnloader_XR_Tension_Offset"))) Info.m_dPaperUnloader_XR_Tension_Offset = _tstof(xml->GetData());

		//Mask Unloader X
		if (xml->FindElem(_T("m_dUnloaderX_Wait_Pos"))) Info.m_dUnloaderX_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderX_Tension_Offset"))) Info.m_dUnloaderX_Tension_Offset = _tstof(xml->GetData());
				
		//21.02.25 sjc
		if (xml->FindElem(_T("m_dUnloaderZL_Wait_Pos"))) Info.m_dUnloaderZL_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZL_Down_Pos"))) Info.m_dUnloaderZL_Down_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZR_Wait_Pos"))) Info.m_dUnloaderZR_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZR_Down_Pos"))) Info.m_dUnloaderZR_Down_Pos = _tstof(xml->GetData());

		if (xml->FindElem(_T("m_dUnloaderZL_Paper_Load_Pos"))) Info.m_dUnloaderZL_Paper_Load_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZR_Paper_Load_Pos"))) Info.m_dUnloaderZR_Paper_Load_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZL_Paper_Unload_Pos"))) Info.m_dUnloaderZL_Paper_Unload_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dUnloaderZR_Paper_Unload_Pos"))) Info.m_dUnloaderZR_Paper_Unload_Pos = _tstof(xml->GetData());
		//
		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataUnloader Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

#pragma region //Cassette
void		CManualDataCassette::Init()
{
	//Cassette Z
	Info.m_dCassetteZ_Wait_Pos = 0.000;
	Info.m_dCassetteZ_1Floor_Pos = 0.000;
	Info.m_dCassetteZ_2Floor_Pos = 0.000;
	Info.m_dCassetteZ_3Floor_Pos = 0.000;
	Info.m_dCassetteZ_4Floor_Pos = 0.000;
	Info.m_dCassetteZ_5Floor_Pos = 0.000;
	Info.m_dCassetteZ_6Floor_Pos = 0.000;
}
//--------------------------------------------
BOOL		CManualDataCassette::Save()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Cassette.dat"));
	file.Open(szFilePath, CFile::modeCreate);
	file.Close();
	file.Open(szFilePath, CFile::modeWrite);
	file.Write(&Info, sizeof(CManualDataCassetteInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Cassette.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Cassette"));
	xml->IntoElem();

	//Cassette Z
	xml->AddElem(_T("m_dCassetteZ_Wait_Pos"), Info.m_dCassetteZ_Wait_Pos);
	xml->AddElem(_T("m_dCassetteZ_1Floor_Pos"), Info.m_dCassetteZ_1Floor_Pos);
	xml->AddElem(_T("m_dCassetteZ_2Floor_Pos"), Info.m_dCassetteZ_2Floor_Pos);
	xml->AddElem(_T("m_dCassetteZ_3Floor_Pos"), Info.m_dCassetteZ_3Floor_Pos);
	xml->AddElem(_T("m_dCassetteZ_4Floor_Pos"), Info.m_dCassetteZ_4Floor_Pos);
	xml->AddElem(_T("m_dCassetteZ_5Floor_Pos"), Info.m_dCassetteZ_5Floor_Pos);
	xml->AddElem(_T("m_dCassetteZ_6Floor_Pos"), Info.m_dCassetteZ_6Floor_Pos);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif

	Str.Format(_T("ManualDataCassette Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//--------------------------------------------
BOOL		CManualDataCassette::Load()
{
	CString Str = _T("");
	CString szFilePath;
	CFile file;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Manual"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Cassette.dat"));
	if (!FileExist(szFilePath)) return FALSE;
	file.Open(szFilePath, CFile::modeRead);
	file.Read(&Info, sizeof(CManualDataCassetteInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Cassette.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Cassette")))
	{
		xml->IntoElem();

		//Cassette Z	
		if (xml->FindElem(_T("m_dCassetteZ_Wait_Pos"))) Info.m_dCassetteZ_Wait_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dCassetteZ_1Floor_Pos"))) Info.m_dCassetteZ_1Floor_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dCassetteZ_2Floor_Pos"))) Info.m_dCassetteZ_2Floor_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dCassetteZ_3Floor_Pos"))) Info.m_dCassetteZ_3Floor_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dCassetteZ_4Floor_Pos"))) Info.m_dCassetteZ_4Floor_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dCassetteZ_5Floor_Pos"))) Info.m_dCassetteZ_5Floor_Pos = _tstof(xml->GetData());
		if (xml->FindElem(_T("m_dCassetteZ_6Floor_Pos"))) Info.m_dCassetteZ_6Floor_Pos = _tstof(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ManualDataCassette Load Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
#pragma endregion

CManualData::CManualData()
{

}
//--------------------------------------------
CManualData::~CManualData()
{

}
//--------------------------------------------
void CManualData::Initialize(void)
{
	m_ManualDataGantry.Init();
	m_ManualDataBox.Init();
	m_ManualDataLoader.Init();
	m_ManualDataInspect.Init();
	m_ManualDataClamp.Init();
	m_ManualDataStretch.Init();
	m_ManualDataPitch.Init();
	m_ManualDataGripperZ.Init();
	m_ManualDataUnloader.Init();
	m_ManualDataCassette.Init();
}
//--------------------------------------------
void CManualData::Finalize(void)
{

}
//--------------------------------------------
void CManualData::Save()
{
	m_ManualDataGantry.Save();
	m_ManualDataBox.Save();
	m_ManualDataLoader.Save();
	m_ManualDataInspect.Save();
	m_ManualDataClamp.Save();
	m_ManualDataStretch.Save();
	m_ManualDataPitch.Save();
	m_ManualDataGripperZ.Save();	
	m_ManualDataUnloader.Save();
	m_ManualDataCassette.Save();
}
//--------------------------------------------
void CManualData::Load()
{
	Initialize();

	m_ManualDataGantry.Load();
	m_ManualDataBox.Load();
	m_ManualDataLoader.Load();
	m_ManualDataInspect.Load();
	m_ManualDataClamp.Load();
	m_ManualDataStretch.Load();
	m_ManualDataPitch.Load();
	m_ManualDataGripperZ.Load();
	m_ManualDataUnloader.Load();
	m_ManualDataCassette.Load();
}
//--------------------------------------------