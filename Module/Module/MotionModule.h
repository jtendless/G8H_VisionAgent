#pragma once

#include "../Common/CommonDefine.h"



class CAjinAxis;
class CUmacAxis;
class CIO;

class CMotionModule
{
public:
	CMotionModule();
	~CMotionModule();

	//2. Umac Check
	CWinThread* m_pStatus_Umac_Thread;
	int m_nIs_Running_Status_Umac_Thread;
	int m_nStop_Status_Umac_Thread;

	CAjinAxis	*m_pAjinAxis;
	CUmacAxis	*m_pUmacAxis;
	CIO			*m_pIO;

	void InitializeAcl();
};

UINT Status_Umac_Thread_Proc(LPVOID lpParam);