#pragma once
#include <afxinet.h>

class CSecs
{
public:
	CSecs();
	~CSecs();
private:
	bool m_SECSCommunicationOK;

public:

	void *pParentDlg;
	void SetParentDlg(void *pPDlg) { pParentDlg = pPDlg; }

	static CSecs* instance;
	static CSecs* Create();
	static CSecs* GetInstance();
	static void DeleteInstance();

public:
	//=== FTP start==========
	CInternetSession* m_pSession = NULL;
	CFtpConnection* m_pFtpCon = NULL;
	CFtpFileFind* m_pFileFind = NULL;

	//void CSecs::ftpOpen();
	//void CSecs::ftpClose();
	//void CSecs::ftpPut(CString filename, CString localpath, CString serverpath);
	//void CSecs::ftpTest();
	//int  CSecs::SaveTPDFile();
	//===FTP end==========

	bool RecvFlag[15][99];
	void CSecs::SFAllClear();		//모든 RecvFlag를 False로 set
	void CSecs::SFClear(short nStrm, short nFunc);	//해당 RecvFlag를 False로 set
	void CSecs::Start();
	void CSecs::Stop();
	void CSecs::SendMsg(CString sMsg, int nDeviceID);
	long CSecs::XcomMake(long * plMsgId, short nDevId, short nStrm, short nFunc, long lSysByte);
	void CSecs::XcomSend(long lMsgId, short nStrm, short nFunc);
	void CSecs::XcomReply(long lMsgId, short nStrm, short nFunc);
	void CSecs::XcomMsgClose(long lMsgId);
	void CSecs::XcomAck(CString strAck);

	long CSecs::XcomList(long lMsgId, long nItems);
	long CSecs::XcomU2(long lMsgId, unsigned short * plValue, long lCount);
	long CSecs::XcomAscii(long lMsgId, char* str, long lCount);
	long CSecs::XcomAscii(long lMsgId, CString str, long lCount);
	long CSecs::XcomAscii(long lMsgId, float fnum, long lCount);
	long CSecs::XcomBinary(long lMsgId, unsigned char* pnValue, long lCount);
	//long CSecs::XcomBinary(long lMsgId, char * pValue, long lCount);
	//long CSecs::XcomBinary(long lMsgId, char Value, long lCount);
	long CSecs::XcomGetAscii(long lMsgId, char * pszValue, long * plCount, long lSize);
	long CSecs::XcomGetU2(long lMsgId, unsigned short * plValue, long * plCount, long lSize);
	long CSecs::XcomGetList(long lMsgId, long * pnItems);
	long CSecs::XcomGetBinary(long lMsgId, unsigned char * pnValue, long * plCount, long lSize);

	/////////////////////////////////////////////////////
	CWnd* pVDlg;		//MainDlg handle
	void SetMainDlgHandle(CWnd* pWnd) { pVDlg = pWnd; }					//Set MainDlg Windows Handle
	CWnd* GetMainDlgWnd(){ return pVDlg; }

	HWND m_MainDlgHWnd;	//MainDlg HWND
	void SetMainDlgHWnd(HWND MainHWnd) { m_MainDlgHWnd = MainHWnd; }	//Set MainDlg Windows Handle

	void CSecs::SecsEventXcomproctrl1(short nEventId, long lParam);
	void CSecs::SecsMsgXcomproctrl1();

	void CSecs::LogBinary(BYTE * bStr, long lSize, long nReturn);
	void CSecs::LogSecsMsg(CString strFunc, CString strMsg);

public:
	bool	bLogWrite = true;		//Log출력여부

	WORD	UnitId, U2;
	long	lists, lSize, lCnt;
	long	lMsgId;
	short	nStrm, nFunc;
	long	nReturn;
	//BYTE	nBinary = 0;
	//BYTE	nBin[255];
	//char*	pchar;
	//BYTE	nBool = 0;
	char	buffer[250];
	//bool	SecsInitialized = false;
	CString	strAck;
	int		nLogView = 1;	// 0:none, 1: send & recive, 2: +make & close, 3:+list, 4: +body(ascii,binary,u2,..)

	int nLoadPort = 1;
	int nUnloadPort = 2;

	//--20171211 jinsuk
	bool bEvent_Log_Flag = true;		//event 발생시 Log출력 여부
	int  nEventIdold = 0;				//이전 event no
	int  nSameEventCount = 0;			//동일event 반복횟수

	//-----
	CString PackageName = L"";		//패키지 이름
	CString PackageNamePrev = L"";	//직전 패키지 이름
	int		PackageStep = 0;		//패키지 스텝
	int		PackageStepPrev = 0;	//직전 패키지 스텝
	int		PackageStepCount = 0;	//직전 패키지 스텝
	CString recvSFmsg = L"";		//최근 수신메시지
	CString sendSFmsg = L"";		//최근 발신메시지
	bool	PackageChecking = FALSE;	//체크진행중인지 여부

	//void CSecs::EqpEvent(CString strEventName);
	//void CSecs::PackageCheck();
	//-----
	//void CSecs::RecvHostCommand();
	void CSecs::ApplyLSD();
	void CSecs::Put_LSD();
	void CSecs::SetAPDStickParameter();
	void CSecs::XcomWriteAPD();
	void CSecs::XcomWriteLSD();
	void CSecs::XcomWriteStickParameter();		//스틱정보 쓰기
	void CSecs::XcomWriteMeasureParameter();	//측정결과 쓰기
	void CSecs::XcomWriteParam(char* strItem, char* strVlaue);
	void CSecs::XcomWriteParam(char* strItem, float fVlaue);
	void CSecs::XcomWrite_InspectData();
	void CSecs::XcomWrite_InspectATData();
	//-----
	//void CSecs::SecsInitialize();
	void CSecs::S1F1();		//AreYouThere
	void CSecs::S1F1recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S1F2(long lSysByte);
	void CSecs::S1F2recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S1F61();	//All Equipment Status Report
	void CSecs::S1F62recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F63recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);	//All Equipment Status Request
	void CSecs::S1F64(long lSysByte);	//All Equipment Status Request
	void CSecs::S1F67();	//All Glass Position Data Report
	void CSecs::S1F68recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F69recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F70(long lSysByte);
	void CSecs::S1F71();
	void CSecs::S1F72recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F73recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F74(long lSysByte);
	void CSecs::S1F75();
	void CSecs::S1F76recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F77();
	void CSecs::S1F78recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F79recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F80(long lSysByte);
	void CSecs::S1F81recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S1F82(long lSysByte);
	void CSecs::S1F83();
	void CSecs::S1F84recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S1F85();
	void CSecs::S1F86recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S1F87();
	void CSecs::S1F88recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S1F89();
	void CSecs::S1F90recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S1F91();
	void CSecs::S1F91(int num);
	void CSecs::S1F92recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S1F93recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S1F94(long lSysByte);
	void CSecs::S2F17();	//Date and Time Request 
	void CSecs::S2F18recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F25();	//Loopback Diagnostic Request
	void CSecs::S2F25recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F26(BYTE* byteStr = NULL);
	void CSecs::S2F26recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F31recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);	/*  Date and Time Data Send  */
	void CSecs::S2F32(long lSysByte);
	void CSecs::S2F61();
	void CSecs::S2F62recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F63();
	void CSecs::S2F64recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F65();
	void CSecs::S2F66recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F67();
	void CSecs::S2F68recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F69recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F70();
	void CSecs::S2F71recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F72(long lSysByte);
	void CSecs::S2F75();
	void CSecs::S2F76recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F77();
	void CSecs::S2F78recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F79();
	void CSecs::S2F80recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F83();
	void CSecs::S2F84recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F85();
	void CSecs::S2F86recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F87recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F88(long lSysByte);
	void CSecs::S2F89recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F90(long lSysByte);
	void CSecs::S2F91recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F92(long lSysByte);
	void CSecs::S2F93();
	void CSecs::S2F94recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F95();
	void CSecs::S2F96recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F97recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S2F98(long lSysByte);
	void CSecs::S3F53();
	void CSecs::S3F54recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S3F63();
	void CSecs::S3F64recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S3F71();
	void CSecs::S3F72recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S3F73();
	void CSecs::S3F74recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S3F75();
	void CSecs::S3F76recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S3F81();
	void CSecs::S3F82recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S3F83recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S3F84(long lSysByte);
	void CSecs::S3F87();
	void CSecs::S3F88recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S3F91();
	void CSecs::S3F92recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S5F1();
	void CSecs::S5F1(BYTE alcd,char* alid ,char* altx);
	void CSecs::S5F1RESET(BYTE alcd, char* alid, char* altx);
	void CSecs::S5F2recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S6F61();
	void CSecs::S6F62recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S6F63();
	void CSecs::S6F64recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S6F65recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S6F66(long lSysByte);
	void CSecs::S6F67();
	void CSecs::S6F68recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F69();
	void CSecs::S6F70recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F71();
	void CSecs::S6F72recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F73();
	void CSecs::S6F74recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F83();
	void CSecs::S6F84recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F85();
	void CSecs::S6F86recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F89();
	void CSecs::S6F90recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F91();
	void CSecs::S6F92recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F93();
	void CSecs::S6F94recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F95();
	void CSecs::S6F96recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S6F97();
	void CSecs::S6F98recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S7F19recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S7F20(long lSysByte);
	void CSecs::S7F61recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S7F62(long lSysByte);
	void CSecs::S7F63();
	void CSecs::S7F64recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S7F67recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S7F68(long lSysByte);
	void CSecs::S7F69recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S7F70(long lSysByte);
	void CSecs::S7F77recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S7F78(long lSysByte);
	void CSecs::S7F79recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S7F80(long lSysByte);
	void CSecs::S7F81recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S7F82(long lSysByte);
	void CSecs::S9F1();
	void CSecs::S9F3();
	void CSecs::S9F5();
	void CSecs::S9F7();
	void CSecs::S9F9();
	void CSecs::S9F11();
	void CSecs::S9F13();
	void CSecs::S10F3recv(long lMsgId, short nDevId, short nStrm, short nFunc, long lSysByte, short nWbit);
	void CSecs::S10F4(long lSysByte);
	void CSecs::S15F65recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S15F66(long lSysByte);
	void CSecs::S15F71recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S15F72(long lSysByte);
	void CSecs::S15F73recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S15F74(long lSysByte);
	void CSecs::S15F75recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S15F76(long lSysByte);
	void CSecs::S15F77recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S15F78(long lSysByte);
	void CSecs::S15F79();
	void CSecs::S15F80recv(long lMsgId, short nDevId, short nStrm1, short nFunc1, long lSysByte, short nWbit);
	void CSecs::S15F75A(float dx[], float dy[], int xlength, int ylength); //Send Data
};

