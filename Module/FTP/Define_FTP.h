
#ifndef _DEFINE_FTP_H_
#define _DEFINE_FTP_H_

#define DEF_PATH_TPD			_T("D:\\B12_IQC\\TPD")

static LPCTSTR	TPD_EQP_ID		= _T("C7CMMS0201");
static LPCTSTR	TPD_EQP_ID_PATH = _T("C7CMMS02");	//FTP 파일 경로
static LPCTSTR	TPD_MC_ID		= _T("C7CMMS0201");


namespace NS_TPD
{
	const int No = 0;				//! NO
	const int MachineUnit = 1;		//! MACHINEUNIT
	const int Time = 2;				//! TIME

	const int RecipeID = 3;			//! LOTID
	const int FrameID = 4;			//! CSTID
	const int Press_PPID = 5;		//! [AIR_PRESS] PPID
	const int Press_Step = 6;		//! [AIR_PRESS] STEP
	const int Press_PrcID = 7;		//! [AIR_PRESS] PRCID 
	const int Press_SLOTID = 8;		//! [AIR_PRESS] SLOTID 
	const int Press_GLSID = 9;		//! [AIR_PRESS] GLSID 
	const int Press_EQPSTATUS = 10;	//! [AIR_PRESS] EPQSTATUS 
	const int Press_KeyID = 11;		//! [AIR_PRESS] KEYID 

	const int TPD_MAX_CNT = 12;
};
#endif