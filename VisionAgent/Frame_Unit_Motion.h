#pragma once
#include "BaseMotion.h"
class CPlcModule;

class CFrame_Unit_Motion : public CBaseMotion
{
	CFrame_Unit_Motion();
	~CFrame_Unit_Motion();

	CPlcModule		*m_pPLC;
	CWkLibVision	*m_pVision_Frame;
	CWkLibBdc		*m_pLight;

	BOOL InitMotion();
};

