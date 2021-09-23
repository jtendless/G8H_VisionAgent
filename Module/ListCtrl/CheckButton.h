#pragma once
class CCheckButton : public CButton
{
private:
	//CheckREF m_foreCheck;
	//CheckREF m_backCheck;
	//CheckREF m_disabledCheck;

public:
	CCheckButton(int nCol);
	~CCheckButton();

	int m_nCol;
	/*
	void SetForeCheck(CheckREF Check) { m_foreCheck = Check; }
	void SetBackGroundCheck(CheckREF Check) { m_backCheck = Check; }
	void SetDisabledCheck(CheckREF Check) { m_disabledCheck = Check; }
	CheckREF GetForeCheck() const { return m_foreCheck; }
	CheckREF GetBackGroundCheck() const { return m_backCheck; }
	CheckREF GetDisabledCheck() const { return m_disabledCheck; }

	void DrawBkGround(CDC *pDC, CRect rect, CheckREF Check);
	void DrawCaption(CDC *pDC, CRect rect, CheckREF Check, const CString& str);
	*/

	DECLARE_MESSAGE_MAP()
	//virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClicked();
};