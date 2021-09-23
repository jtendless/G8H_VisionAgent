#pragma once


// CDrawMask

class CDrawMask : public CStatic
{
	DECLARE_DYNAMIC(CDrawMask)

public:
	INT m_nRealWidth;
	INT m_nRealHeight;

	CPen	m_Frame;		// Frame
	CPen	m_Worked;		// Worked Mask
	CPen	m_Cover1;		// non worked Cover
	CPen	m_Howling1;		// non worked Howling
	CPen	m_Cover2;		// non worked Cover
	CPen	m_Howling2;		// non worked Howling
	CFont	m_Font;

	INT		nOldMode;
	CPen	*m_pOldPen;
	CFont	*poldFont;

	void CDrawMask::Draw_Mask( CDC *pDC );

	void PositionViewPoint(CDC* pDC, FLOAT fPos_X, FLOAT fPos_Y);

public:

	CDrawMask();
	virtual ~CDrawMask();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


