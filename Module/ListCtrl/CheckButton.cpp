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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int nCheck = GetCheck();

	SetCheck(!nCheck);

	this->GetParent()->SendMessage(WM_CHECKSTATUS, m_nCol, !nCheck);
}
