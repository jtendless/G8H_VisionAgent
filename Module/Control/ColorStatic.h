#pragma once
class CColorStatic : public CStatic
{
public:
	CColorStatic();
	~CColorStatic();

	void SetTransparent(bool ATransparent = true);
	void SetBackgroundColor(COLORREF AColor);
	void SetTextColor(COLORREF AColor);
	void SetData(CString strData);

	//SubClassing전에 지정 해주기.
	void SetParaOriginColor(COLORREF AColor);
	void SetParaChangeColor(COLORREF AColor);
	void SetActButton(BOOL bActbutton);
	void SetNumButton(BOOL bNum, int mLimit, int pLimit);

	bool MTransparent = FALSE;

	COLORREF MBackgroundColor = RGB(125, 125, 125);
	COLORREF MCurrentBackgroundColor = RGB(125, 125, 125);
	COLORREF MChangeBackgroundColor = RGB(255, 255, 255);

	COLORREF MTextColor = RGB(0, 0, 0);

	CBrush m_ColorBrush;

	INT m_mLimit;
	INT m_pLimit;
	BOOL m_bClick;
	BOOL m_bBkDraw;
	BOOL m_bTrack;
	BOOL m_bActButton;
	BOOL m_bNum;

	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	virtual void PreSubclassWindow();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

