
#include "stdafx.h"
#include "ServerInterface.h"
#include "CommonDefine.h"
#include "VisionAgentDlg.h"
#include "Log/Logger.h"


CServerInterface::CServerInterface(void)
{
	m_pParentDlg = NULL;
	ShmFunctionTableInitialize();
	m_nCnt = 0;
}

CServerInterface::~CServerInterface(void)
{
	
}

int CServerInterface::SetParentDlg(void *pDlg)
{
	m_pParentDlg = pDlg;

	return TRUE;
}

//통신수정부분 - 5.
void CServerInterface::ShmFunctionTableInitialize(void)
{
	m_ShmFuncTable[VisionFind_Func] = &CServerInterface::VisionFind;
	//m_ShmFuncTable[VisionGetData_Func] = &CServerInterface::VisionGetData;
	m_ShmFuncTable[SetLight_Func] = &CServerInterface::SetLight;
	m_ShmFuncTable[LightOn_Func] = &CServerInterface::LightOn;
	//m_ShmFuncTable[GetLightState_Func] = &CServerInterface::GetLightState;

}

int CServerInterface::ExecShmFuncTable(int nFuncID, void *pArg)
{
	//TRACE(_T(" ServerInterface::m_nFuncAddr = %d\n"), nFuncID);

	//if (nFuncID == 64)
	//	nFuncID = nFuncID;

	return(this->*m_ShmFuncTable[nFuncID])(pArg);
}
//통신수정부분 - 3.
int CServerInterface::Example(void *pArg)
{
	//기능 작성.	
	//st_SystemGetMaxAxisSize* pCmdArg = (st_SystemGetMaxAxisSize*)pArg;
	//m_nArgSize = sizeof(st_SystemGetMaxAxisSize);
	
	return FMM_SUCCESS;
}

int CServerInterface::VisionFind(void *pArg)
{
	//기능 작성.	
	st_VisionFind *pCmdArg = (st_VisionFind*)pArg;
	m_nArgSize = sizeof(st_VisionFind);

	CVisionAgentDlg *pDlg = (CVisionAgentDlg*)m_pParentDlg;

	if (pCmdArg->nOption == 0) {
		switch (pCmdArg->nCameraIndex)
		{
#if 0
		case 0:
			pDlg->m_AlignCamera_1->m_BlobData.dMarkSizeX = pCmdArg->dMarkPixelSize[0];
			pDlg->m_AlignCamera_1->m_BlobData.dMarkSizeY = pCmdArg->dMarkPixelSize[1];
			pDlg->m_AlignCamera_1->m_CameraInfo.nType = pCmdArg->nType;
			pDlg->m_AlignCamera_1->m_CameraInfo.nBin = pCmdArg->nBin;
			Sleep(10);
			pDlg->m_AlignCamera_1->BlobInspect();
			
			break;
		case 1:
			pDlg->m_AlignCamera_2->m_BlobData.dMarkSizeX = pCmdArg->dMarkPixelSize[0];
			pDlg->m_AlignCamera_2->m_BlobData.dMarkSizeY = pCmdArg->dMarkPixelSize[1];
			pDlg->m_AlignCamera_2->m_CameraInfo.nType = pCmdArg->nType;
			pDlg->m_AlignCamera_2->m_CameraInfo.nBin = pCmdArg->nBin;
			Sleep(10);
			pDlg->m_AlignCamera_2->BlobInspect();

			break;

		case 2:
			pDlg->m_AlignCamera_3->m_BlobData.dMarkSizeX = pCmdArg->dMarkPixelSize[0];
			pDlg->m_AlignCamera_3->m_BlobData.dMarkSizeY = pCmdArg->dMarkPixelSize[1];
			pDlg->m_AlignCamera_3->m_CameraInfo.nType = pCmdArg->nType;
			pDlg->m_AlignCamera_3->m_CameraInfo.nBin = pCmdArg->nBin;
			Sleep(10);
			pDlg->m_AlignCamera_3->BlobInspect();

			break;

		case 3:
			pDlg->m_AlignCamera_4->m_BlobData.dMarkSizeX = pCmdArg->dMarkPixelSize[0];
			pDlg->m_AlignCamera_4->m_BlobData.dMarkSizeY = pCmdArg->dMarkPixelSize[1];
			pDlg->m_AlignCamera_4->m_CameraInfo.nType = pCmdArg->nType;
			pDlg->m_AlignCamera_4->m_CameraInfo.nBin = pCmdArg->nBin;
			Sleep(10);
			pDlg->m_AlignCamera_4->BlobInspect();

			break;
#endif
		}
	}

	//Pattern Find.
	if (pCmdArg->nOption == 1) 
	{
		switch (pCmdArg->nCameraIndex)
		{
		case 1:
			AfxMessageBox(_T("%d"), pCmdArg->nOption);
			break;


		case 2:
			AfxMessageBox(_T("%d"), pCmdArg->nOption);
			break;


		case 3:
			AfxMessageBox(_T("%d"), pCmdArg->nOption);
			break;


		case 4:
			AfxMessageBox(_T("%d"), pCmdArg->nOption);
			break;
		}
	}

	//Model Find.
	if (pCmdArg->nOption == 2)
	{
		switch (pCmdArg->nCameraIndex)
		{
		case 1:
			AfxMessageBox(_T("%d"), pCmdArg->nOption);
			break;


		case 2:
			AfxMessageBox(_T("%d"), pCmdArg->nOption);
			break;


		case 3:
			AfxMessageBox(_T("%d"), pCmdArg->nOption);
			break;


		case 4:
			AfxMessageBox(_T("%d"), pCmdArg->nOption);
			break;
		}
	}

	Vision_Msg(_T("Vision Find #%d"), pCmdArg->nCameraIndex);

	return FMM_SUCCESS;
}

int CServerInterface::VisionGetData(void *pArg)
{
	//기능 작성.	
	st_VisionReturn *pCmdArg = (st_VisionReturn*)pArg;
	m_nArgSize = sizeof(st_VisionReturn);

	CVisionAgentDlg *pDlg = (CVisionAgentDlg*)m_pParentDlg;

	switch (pCmdArg->nCameraIndex)
	{
#if 0
	case 0:

		pCmdArg->dMarkPixelPos[0] = pDlg->m_AlignCamera_1->m_BlobData.dPosX;
		pCmdArg->dMarkPixelPos[1] = pDlg->m_AlignCamera_1->m_BlobData.dPosY;
		pCmdArg->dMarkCD[0] = pDlg->m_AlignCamera_1->m_BlobData.dCdX;
		pCmdArg->dMarkCD[1] = pDlg->m_AlignCamera_1->m_BlobData.dCdY;
		break;

	case 1:

		pCmdArg->dMarkPixelPos[0] = pDlg->m_AlignCamera_2->m_BlobData.dPosX;
		pCmdArg->dMarkPixelPos[1] = pDlg->m_AlignCamera_2->m_BlobData.dPosY;
		pCmdArg->dMarkCD[0] = pDlg->m_AlignCamera_2->m_BlobData.dCdX;
		pCmdArg->dMarkCD[1] = pDlg->m_AlignCamera_2->m_BlobData.dCdY;
		break;

	case 2:

		pCmdArg->dMarkPixelPos[0] = pDlg->m_AlignCamera_3->m_BlobData.dPosX;
		pCmdArg->dMarkPixelPos[1] = pDlg->m_AlignCamera_3->m_BlobData.dPosY;
		pCmdArg->dMarkCD[0] = pDlg->m_AlignCamera_3->m_BlobData.dCdX;
		pCmdArg->dMarkCD[1] = pDlg->m_AlignCamera_3->m_BlobData.dCdY;
		break;

	case 3:
		pCmdArg->dMarkPixelPos[0] = pDlg->m_AlignCamera_4->m_BlobData.dPosX;
		pCmdArg->dMarkPixelPos[1] = pDlg->m_AlignCamera_4->m_BlobData.dPosY;
		pCmdArg->dMarkCD[0] = pDlg->m_AlignCamera_4->m_BlobData.dCdX;
		pCmdArg->dMarkCD[1] = pDlg->m_AlignCamera_4->m_BlobData.dCdY;
		break;
#endif

	}

	Vision_Msg(_T("Vision Feedback #%d"), pCmdArg->nCameraIndex);

	return FMM_SUCCESS;
}

int CServerInterface::SetLight(void *pArg)
{
	st_SetLight *pCmdArg = (st_SetLight*)pArg;
	m_nArgSize = sizeof(st_SetLight);

	CVisionAgentDlg *pDlg = (CVisionAgentDlg*)m_pParentDlg;
	int nRet = 0;
	

	switch (pCmdArg->nCameraIndex)
	{
#if 0
	case 0:
		pDlg->m_AlignCamera_1->m_CameraInfo.nAxisLight = pCmdArg->nBright[0];
		nRet = pDlg->m_LightController->SetBrightness(AXIS_LIGHT_1, pCmdArg->nBright[0]);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		pDlg->m_AlignCamera_1->m_CameraInfo.nRingLight1 = pCmdArg->nBright[1];
		nRet = pDlg->m_LightController->SetBrightness(SIDE_LIGHT_1, pCmdArg->nBright[1]);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		break;
	case 1:
		pDlg->m_AlignCamera_2->m_CameraInfo.nAxisLight = pCmdArg->nBright[0];
		nRet = pDlg->m_LightController->SetBrightness(AXIS_LIGHT_2, pCmdArg->nBright[0]);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}

		pDlg->m_AlignCamera_2->m_CameraInfo.nRingLight1 = pCmdArg->nBright[1];
		nRet = pDlg->m_LightController->SetBrightness(SIDE_LIGHT_2, pCmdArg->nBright[1]);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		break;
	case 2:
		pDlg->m_AlignCamera_3->m_CameraInfo.nAxisLight = pCmdArg->nBright[0];
		nRet = pDlg->m_LightController->SetBrightness(AXIS_LIGHT_3, pCmdArg->nBright[0]);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		pDlg->m_AlignCamera_3->m_CameraInfo.nRingLight1 = pCmdArg->nBright[1];
		nRet = pDlg->m_LightController->SetBrightness(SIDE_LIGHT_3, pCmdArg->nBright[1]);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		break;
	case 3:
		pDlg->m_AlignCamera_4->m_CameraInfo.nAxisLight = pCmdArg->nBright[0];
		nRet = pDlg->m_LightController->SetBrightness(AXIS_LIGHT_4, pCmdArg->nBright[0]);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		pDlg->m_AlignCamera_4->m_CameraInfo.nRingLight1 = pCmdArg->nBright[1];
		nRet = pDlg->m_LightController->SetBrightness(SIDE_LIGHT_4, pCmdArg->nBright[1]);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		break;

	default:
		return LIGHT_CONTROL_FAIL;
		break;
#endif
	}
		
	return FMM_SUCCESS;

}

int CServerInterface::LightOn(void *pArg)
{
	//기능 작성.	
	st_LightOn *pCmdArg = (st_LightOn*)pArg;
	m_nArgSize = sizeof(st_LightOn);

	CVisionAgentDlg *pDlg = (CVisionAgentDlg*)m_pParentDlg;
	int nRet = 0;


	switch (pCmdArg->nCameraIndex)
	{
#if 0
	case 0:
		nRet = pDlg->m_LightController->TurnOnChannel(AXIS_LIGHT_1, pCmdArg->nOnOff);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}

		nRet = pDlg->m_LightController->TurnOnChannel(SIDE_LIGHT_1, pCmdArg->nOnOff);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		break;
	case 1:
		nRet = pDlg->m_LightController->TurnOnChannel(AXIS_LIGHT_2, pCmdArg->nOnOff);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}

		nRet = pDlg->m_LightController->TurnOnChannel(SIDE_LIGHT_2, pCmdArg->nOnOff);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		break;
	case 2:
		nRet = pDlg->m_LightController->TurnOnChannel(AXIS_LIGHT_3, pCmdArg->nOnOff);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}

		nRet = pDlg->m_LightController->TurnOnChannel(SIDE_LIGHT_3, pCmdArg->nOnOff);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		break;
	case 3:
		nRet = pDlg->m_LightController->TurnOnChannel(AXIS_LIGHT_4, pCmdArg->nOnOff);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}

		nRet = pDlg->m_LightController->TurnOnChannel(SIDE_LIGHT_4, pCmdArg->nOnOff);
		if (nRet <= 0)
		{
			return LIGHT_CONTROL_FAIL;
		}
		break;
		
	default:
		return LIGHT_CONTROL_FAIL;
		break;
#endif
	} 

	return FMM_SUCCESS;
}
//
//int CServerInterface::GetLightState(void *pArg)
//{
//	//기능 작성.	
//	st_GetLightState *pCmdArg = (st_GetLightState*)pArg;
//	m_nArgSize = sizeof(st_GetLightState);
//
//	CVisionAgentDlg *pDlg = (CVisionAgentDlg*)m_pParentDlg;
//	BOOL bOnOff = FALSE;
//	BOOL bOnOff2 = FALSE;
//	int nValue[2] = { 0, };
//	switch (pCmdArg->nCameraIndex)
//	{
//#if 0
//	case 0:
//		bOnOff = pDlg->m_LightController->IsTurnedOn(AXIS_LIGHT_1);
//		Sleep(100);
//		bOnOff2 = pDlg->m_LightController->IsTurnedOn(SIDE_LIGHT_1);
//		Sleep(100);
//		nValue[0] = pDlg->m_LightController->GetBrightness(AXIS_LIGHT_1);
//		Sleep(100);
//		nValue[1] = pDlg->m_LightController->GetBrightness(SIDE_LIGHT_1);
//		break;
//	case 1:
//		bOnOff = pDlg->m_LightController->IsTurnedOn(AXIS_LIGHT_2);
//		Sleep(100);
//		bOnOff2 = pDlg->m_LightController->IsTurnedOn(SIDE_LIGHT_2);
//		Sleep(100);
//		nValue[0] = pDlg->m_LightController->GetBrightness(AXIS_LIGHT_2);
//		Sleep(100);
//		nValue[1] = pDlg->m_LightController->GetBrightness(SIDE_LIGHT_2);
//		break;
//	case 2:
//		bOnOff = pDlg->m_LightController->IsTurnedOn(AXIS_LIGHT_3);
//		Sleep(100);
//		bOnOff2 = pDlg->m_LightController->IsTurnedOn(SIDE_LIGHT_3);
//		Sleep(100);
//		nValue[0] = pDlg->m_LightController->GetBrightness(AXIS_LIGHT_3);
//		Sleep(100);
//		nValue[1] = pDlg->m_LightController->GetBrightness(SIDE_LIGHT_3);
//		break;
//	case 3:
//		bOnOff = pDlg->m_LightController->IsTurnedOn(AXIS_LIGHT_4);
//		Sleep(100);
//		bOnOff2 = pDlg->m_LightController->IsTurnedOn(SIDE_LIGHT_4);
//		Sleep(100);
//		nValue[0] = pDlg->m_LightController->GetBrightness(AXIS_LIGHT_4);
//		Sleep(100);
//		nValue[1] = pDlg->m_LightController->GetBrightness(SIDE_LIGHT_4);
//		break;
//#endif
//	default:
//		break;
//	}
//	
//	pCmdArg->bOnOff = bOnOff &&  bOnOff2;
//	memcpy(pCmdArg->nLightValue, nValue, sizeof(nValue));
//	
//	return FMM_SUCCESS;
//
//}
