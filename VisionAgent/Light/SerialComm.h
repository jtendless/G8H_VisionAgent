#if !defined (SERIALCOMM_H)
#define SERIALCOMM_H

#include <afxmt.h>

#define PORT_OK						0
#define	PORT_OPEN_ERROR				1
#define	PORT_CONFIGURE_ERROR		2
#define	PORT_COMSTAT_ACESS_ERROR	3
#define	PORT_READ_ERROR				4
#define	PORT_WRITE_ERROR			5
#define	PORT_CLOSE_ERROR			6
#define	PORT_CLEAN_ERROR			7
#define	PORT_NOT_READY				8
#define	PORT_MEM_ALLOC_ERROR		9
#define PORT_FALSE_RETURN_ERROR		10


#define	STX							0x02
#define	ETX							0x03
#define	CR							0x0D
#define	LF							0x0A



class CSerialComm : public CObject
{
protected:
	CSerialComm();
public:
	HANDLE	m_hPort;	
	int m_nReadInterval;
	DWORD m_dwTotalReadBytes;
	BYTE* m_pbtDataRead;
	DWORD m_dwMaxReadSize;

	int CleanPort();
	int WritePort(CString stDataToWrite);
	int WritePort(char *pData, int nSize);
	int ReadPort();
	int ClosePort();
	int m_nLastError;
	int OpenPort(CString stPortName, DWORD dwMaxReadSize);
	virtual ~CSerialComm();

	virtual int ConfigPort();
};

#endif