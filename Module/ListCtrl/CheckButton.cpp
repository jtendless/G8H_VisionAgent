#include "stdafx.h"
#include "CheckButton.h"

CCheckButton::CCheckButton(int nCol)
{
	m_nCol = nCol;
}


CCheckButton::~CCheckButton()
{
}

BEGIN_MESSAGE_MAP(CCheckButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CCheckButton::OnBnClicked)
END_MESSAGE_MAP()

void CCheckButton::OnBnClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nCheck = GetCheck();

	SetCheck(!nCheck);

	this->GetParent()->SendMessage(WM_CHECKSTATUS, m_nCol, !nCheck);
}
