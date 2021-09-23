#if !defined (USERTIMER_H)
#define USERTIMER_H

/////////////////////////////////////////
//CUserTimer definition
/////////////////////////////////////////
#define	TIMER_OK	0
#define	TIMER_NG	1

class CUserTimer : public CObject
{
protected:
	DWORD	m_dwTimeStamp;
	DWORD	m_dwTimeCompensator;
	BOOL	m_bLock;
public:
	void SetTimeOut(DWORD dwTimeOut);
	BOOL CheckTimeOut();
	DWORD m_dwTimeOut;
	CUserTimer(DWORD dwTimeOut);
	~CUserTimer();

	int	SetTimer();
	int GetLapTime(DWORD* pdLapTime);
	int ReleaseTimer();
};

#endif