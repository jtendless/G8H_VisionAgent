#include <string.h>
#include "stdafx.h"
#include "hash.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
void CHash::GetHashPathName(char *sFileName, CString *pstrHash)
{
	pstrHash->Format(_T("%08d//%08d"),
		(INT)TranHashValue2NumberInLayer(GetHashValue(sFileName), 0),
		(INT)TranHashValue2NumberInLayer(GetHashValue(sFileName), 1));
}

//////////////////////////////////////////////////////////////////////
long CHash::GetHashValue(char *pKeyStr) 
{
	int    strLength ;
	int    i, tmpVal=0;

	if ((strLength = (INT)strlen(pKeyStr)) == 0) return(0) ;

	for (i=0; i<strLength; i++) {
		tmpVal = ((tmpVal * 0x00ff) + (0x00ff & toupper(pKeyStr[i]))) % SEED ;
	}
	return(tmpVal);
}

//////////////////////////////////////////////////////////////////////
long CHash::TranHashValue2NumberInLayer(long HashValue, long LayerNumber) 
{
    int     LayerSize ;
	long    lTmp      ;
    LayerSize = SEED / ((int)pow(SEED, 0.5)) ;

	if (LayerNumber == 0)
		 lTmp = HashValue / LayerSize ;  // 0 - (layerSize-1)
	else lTmp = HashValue % LayerSize ;  // 0 - (layerSize-1)

	return(lTmp) ;
}
