
// VisionAgent.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
// CVisionAgentApp:
// �� Ŭ������ ������ ���ؼ��� VisionAgent.cpp�� �����Ͻʽÿ�.
//

class CVisionAgentApp : public CWinApp
{
public:
	

	CVisionAgentApp();

	HANDLE Mutex;
// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CVisionAgentApp theApp;

CString	_ToStr(LPCTSTR fmt, ...);
CString _ToUni(char* pMultibyte);
char*	_ToMbc(CString strUnicode);