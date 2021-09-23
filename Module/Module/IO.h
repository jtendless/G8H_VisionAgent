#pragma once
class CIO
{
public:
	CIO();
	~CIO();

	int m_nInputActiveLevel[8][16];
	int m_nOutputActiveLevel[8][16];

	int m_nPrevAnalogInput[2][16];
	int m_nPrevInput[8][16];
	int m_nPrevOutput[8][16];

	int m_nAnalogInput[2][16];
	int m_nInput[8][16];
	int m_nOutput[8][16];

	CWinThread* m_pIOCheckThread;
	int m_nIsRunningIOCheckThread;
	int m_nStopIOCheckThread;

	int StartIOCheck();
	int StopIOCheck();

	int GetAnalogInputBit(int nWordNo, int nBitNo);

	int GetActiveInputBit(int nWordNo, int nBitNo);

	int GetActiveOutputBit(int nWordNo, int nBitNo);
	int SetActiveOutputBit(int nWordNo, int nBitNo);
	int SetNonActiveOutputBit(int nWordNo, int nBitNo);
};

