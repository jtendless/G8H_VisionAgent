#pragma once
class CColorButton : public CButton
{
private:
	COLORREF m_foreColor;
	COLORREF m_backColor;
	COLORREF m_disabledColor;

public:
	CColorButton();
	~CColorButton();

	void SetForeColor(COLORREF color) { m_foreColor = color; }
	void SetBackGroundColor(COLORREF color) { m_backColor = color; }
	void SetDisabledColor(COLORREF color) { m_disabledColor = color; }
	COLORREF GetForeColor() const { return m_foreColor; }
	COLORREF GetBackGroundColor() const { return m_backColor; }
	COLORREF GetDisabledColor() const { return m_disabledColor; }

	void DrawBkGround(CDC *pDC, CRect rect, COLORREF color);
	void DrawCaption(CDC *pDC, CRect rect, COLORREF color, const CString& str);

	DECLARE_MESSAGE_MAP()
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};