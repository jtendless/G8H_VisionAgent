
// DlgProxy.cpp: 구현 파일
//

#include "stdafx.h"
#include "framework.h"
#include "VisionAgent.h"
#include "DlgProxy.h"
#include "VisionAgentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVisionAgentDlgAutoProxy

IMPLEMENT_DYNCREATE(CVisionAgentDlgAutoProxy, CCmdTarget)

CVisionAgentDlgAutoProxy::CVisionAgentDlgAutoProxy()
{
	EnableAutomation();

	// 자동화 개체가 활성화되어 있는 동안 계속 응용 프로그램을 실행하기 위해
	//	생성자에서 AfxOleLockApp를 호출합니다.
	AfxOleLockApp();

	// 응용 프로그램의 주 창 포인터를 통해 대화 상자에 대한
	//  액세스를 가져옵니다.  프록시의 내부 포인터를 설정하여
	//  대화 상자를 가리키고 대화 상자의 후방 포인터를 이 프록시로
	//  설정합니다.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CVisionAgentDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CVisionAgentDlg)))
		{
			m_pDialog = reinterpret_cast<CVisionAgentDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CVisionAgentDlgAutoProxy::~CVisionAgentDlgAutoProxy()
{
	// 모든 개체가 OLE 자동화로 만들어졌을 때 응용 프로그램을 종료하기 위해
	// 	소멸자가 AfxOleUnlockApp를 호출합니다.
	//  이러한 호출로 주 대화 상자가 삭제될 수 있습니다.
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CVisionAgentDlgAutoProxy::OnFinalRelease()
{
	// 자동화 개체에 대한 마지막 참조가 해제되면
	// OnFinalRelease가 호출됩니다.  기본 클래스에서 자동으로 개체를 삭제합니다.
	// 기본 클래스를 호출하기 전에 개체에 필요한 추가 정리 작업을
	// 추가하세요.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CVisionAgentDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVisionAgentDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 참고: IID_IVisionAgent에 대한 지원을 추가하여
//  VBA에서 형식 안전 바인딩을 지원합니다.
//  이 IID는 .IDL 파일에 있는 dispinterface의 GUID와 일치해야 합니다.

// {e1843dcf-0f83-49a1-ad48-643fe65dd2f5}
static const IID IID_IVisionAgent =
{0xe1843dcf,0x0f83,0x49a1,{0xad,0x48,0x64,0x3f,0xe6,0x5d,0xd2,0xf5}};

BEGIN_INTERFACE_MAP(CVisionAgentDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CVisionAgentDlgAutoProxy, IID_IVisionAgent, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in pch.h of this project
// {c4b2731e-86fe-4324-982a-98606a312766}
IMPLEMENT_OLECREATE2(CVisionAgentDlgAutoProxy, "VisionAgent.Application", 0xc4b2731e,0x86fe,0x4324,0x98,0x2a,0x98,0x60,0x6a,0x31,0x27,0x66)


// CVisionAgentDlgAutoProxy 메시지 처리기
