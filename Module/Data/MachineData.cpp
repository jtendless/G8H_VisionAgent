#include "stdafx.h"
#include "MachineData.h"
#include "VisionAgentDlg.h"

CMachineDataMotor				CMachineData::m_MachineDataMotor;
//--------------------------------------------
void		CMachineDataMotor::Init()
{
	for (int i = 0; i < AXIS_MAX; i++)
	{
		DefaultInfo.dAutoVel[i] = 1.0; DefaultInfo.dMaxVel[i] = 10.0;

		DefaultInfo.dSafetyPosMin[i] = -150.0;
		DefaultInfo.dSafetyPosMax[i] = 150.0;
		DefaultInfo.dOriginPos[i] = 0.0;

		DefaultInfo.dAutoAccel[i] = DefaultInfo.dAutoVel[i] * DEFAULT_VEL_WORK_DIV * 2.0;
		DefaultInfo.dAutoDecel[i] = DefaultInfo.dAutoVel[i] * DEFAULT_VEL_WORK_DIV * 2.0;

		DefaultInfo.dManualHighVel[i] = DefaultInfo.dAutoVel[i] * DEFAULT_VEL_WORK_DIV * 0.75;
		DefaultInfo.dManualHighAccel[i] = DefaultInfo.dAutoAccel[i] * DEFAULT_VEL_WORK_DIV * 0.75;
		DefaultInfo.dManualHighDecel[i] = DefaultInfo.dAutoDecel[i] * DEFAULT_VEL_WORK_DIV * 0.75;

		DefaultInfo.dManualMediumVel[i] = DefaultInfo.dAutoVel[i] * DEFAULT_VEL_WORK_DIV * 0.5;
		DefaultInfo.dManualMediumAccel[i] = DefaultInfo.dAutoAccel[i] * DEFAULT_VEL_WORK_DIV * 0.5;
		DefaultInfo.dManualMediumDecel[i] = DefaultInfo.dAutoDecel[i] * DEFAULT_VEL_WORK_DIV * 0.5;

		DefaultInfo.dManualLowVel[i] = DefaultInfo.dAutoVel[i] * DEFAULT_VEL_WORK_DIV * 0.25;
		DefaultInfo.dManualLowAccel[i] = DefaultInfo.dAutoAccel[i] * DEFAULT_VEL_WORK_DIV * 0.25;
		DefaultInfo.dManualLowDecel[i] = DefaultInfo.dAutoDecel[i] * DEFAULT_VEL_WORK_DIV * 0.25;
	}
}
//--------------------------------------------
BOOL		CMachineDataMotor::Save()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Machine"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Motor.dat"));
	file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(CMachineDataMotorInfo));
	file.Close();
#else //xml
	szFilePath.AppendFormat(_T("\\Motor.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("Motor"));
	xml->IntoElem();

	for (i = 0; i < AXIS_MAX; i++)
	{
		Str.Format(_T("dSafetyPosMin_%d"), i);
		xml->AddElem(Str, Info.dSafetyPosMin[i]);
		Str.Format(_T("dSafetyPosMax_%d"), i);
		xml->AddElem(Str, Info.dSafetyPosMax[i]);
		Str.Format(_T("dOriginPos_%d"), i);
		xml->AddElem(Str, Info.dOriginPos[i]);
		Str.Format(_T("dMaxVel_%d"), i);
		xml->AddElem(Str, Info.dMaxVel[i]);
		Str.Format(_T("dAutoVel_%d"), i);
		xml->AddElem(Str, Info.dAutoVel[i]);
		Str.Format(_T("dAutoAccel_%d"), i);
		xml->AddElem(Str, Info.dAutoAccel[i]);
		Str.Format(_T("dAutoDecel_%d"), i);
		xml->AddElem(Str, Info.dAutoDecel[i]);
		Str.Format(_T("dManualHighVel_%d"), i);
		xml->AddElem(Str, Info.dManualHighVel[i]);
		Str.Format(_T("dManualHighAccel_%d"), i);
		xml->AddElem(Str, Info.dManualHighAccel[i]);
		Str.Format(_T("dManualHighDecel_%d"), i);
		xml->AddElem(Str, Info.dManualHighDecel[i]);
		Str.Format(_T("dManualMediumVel_%d"), i);
		xml->AddElem(Str, Info.dManualMediumVel[i]);
		Str.Format(_T("dManualMediumAccel_%d"), i);
		xml->AddElem(Str, Info.dManualMediumAccel[i]);
		Str.Format(_T("dManualMediumDecel_%d"), i);
		xml->AddElem(Str, Info.dManualMediumDecel[i]);
		Str.Format(_T("dManualLowVel_%d"), i);
		xml->AddElem(Str, Info.dManualLowVel[i]);
		Str.Format(_T("dManualLowAccel_%d"), i);
		xml->AddElem(Str, Info.dManualLowAccel[i]);
		Str.Format(_T("dManualLowDecel_%d"), i);
		xml->AddElem(Str, Info.dManualLowDecel[i]);
	}

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
#endif
	Str.Format(_T("MachineDataMotor Save Ok (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//--------------------------------------------
BOOL		CMachineDataMotor::Load()
{
	CString szFilePath, Str;
	CFile file;
	int i = 0, j = 0;
	szFilePath = SharedInfo::GetExeFilePath();
	szFilePath.AppendFormat(_T("\\Data"));
	::CreateDirectory(szFilePath, NULL);
	szFilePath.AppendFormat(_T("\\Machine"));
	::CreateDirectory(szFilePath, NULL);

#if !XML_USE //dat
	szFilePath.AppendFormat(_T("\\Motor.dat"));
	if (file.Open(szFilePath, CFile::modeRead) == FALSE)
	{
		file.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(&DefaultInfo, sizeof(CMachineDataMotorInfo));
		return FALSE;
	}

	file.Read(&Info, sizeof(Info));
	file.Close();
#else
	szFilePath.AppendFormat(_T("\\Motor.xml"));

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("Motor")))
	{
		xml->IntoElem();

		for (i = 0; i < AXIS_MAX; i++)
		{
			Str.Format(_T("dSafetyPosMin_%d"), i);
			if (xml->FindElem(Str)) Info.dSafetyPosMin[i] = _tstof(xml->GetData());
			Str.Format(_T("dSafetyPosMax_%d"), i);
			if (xml->FindElem(Str)) Info.dSafetyPosMax[i] = _tstof(xml->GetData());
			Str.Format(_T("dOriginPos_%d"), i);
			if (xml->FindElem(Str)) Info.dOriginPos[i] = _tstof(xml->GetData());
			Str.Format(_T("dMaxVel_%d"), i);
			if (xml->FindElem(Str)) Info.dMaxVel[i] = _tstof(xml->GetData());
			Str.Format(_T("dAutoVel_%d"), i);
			if (xml->FindElem(Str)) Info.dAutoVel[i] = _tstof(xml->GetData());
			Str.Format(_T("dAutoAccel_%d"), i);
			if (xml->FindElem(Str)) Info.dAutoAccel[i] = _tstof(xml->GetData());
			Str.Format(_T("dAutoDecel_%d"), i);
			if (xml->FindElem(Str)) Info.dAutoDecel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualHighVel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualHighVel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualHighAccel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualHighAccel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualHighDecel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualHighDecel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualMediumVel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualMediumVel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualMediumAccel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualMediumAccel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualMediumDecel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualMediumDecel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualLowVel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualLowVel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualLowAccel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualLowAccel[i] = _tstof(xml->GetData());
			Str.Format(_T("dManualLowDecel_%d"), i);
			if (xml->FindElem(Str)) Info.dManualLowDecel[i] = _tstof(xml->GetData());
		}

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("MotorPara Load (%s)"), szFilePath);
	Total_Msg(Str);
	return TRUE;
}
//--------------------------------------------
CMachineData::CMachineData()
{

}
//--------------------------------------------
CMachineData::~CMachineData()
{

}
//--------------------------------------------
void CMachineData::Initialize(void)
{

}
//--------------------------------------------
void CMachineData::Finalize(void)
{

}
//--------------------------------------------
void CMachineData::Save()
{
	m_MachineDataMotor.Save();
}
//--------------------------------------------
void CMachineData::Load()
{
	m_MachineDataMotor.Load();
}
//--------------------------------------------