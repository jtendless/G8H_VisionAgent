
#ifndef _SERVER_INTERFACE_H_
#define _SERVER_INTERFACE_H_

#include "SHMInterface.h"

class CServerInterface
{
public:
	CServerInterface(void);
	virtual ~CServerInterface(void);

	void *m_pParentDlg;
	int SetParentDlg(void *pDlg);

	int m_nCnt;
	/////////////////////////////////////////////////
	int	 m_nArgSize;

	void ShmFunctionTableInitialize(void);

	int	 (CServerInterface::*m_ShmFuncTable[MAX_SHM_FUNCTION])(void *pArg);
	int	 ExecShmFuncTable(int nFuncID, void *pArg);
		 
	//통신수정부분 - 4.
	//Interface Function------------------------------------------------------------------------------------------------
	int Example(void *pArg);
	int VisionFind(void *pArg);
	int VisionGetData(void *pArg);
	int SetLight(void *pArg);
	int LightOn(void *pArg);
	//int GetLightState(void *pArg);

};

#endif