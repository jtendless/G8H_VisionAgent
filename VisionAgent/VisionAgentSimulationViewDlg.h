#pragma once
#include "VisionAgentDlg.h"
#define UNIT_XYZ_MAX_COUNT  20
#define UNIT_UVW_MAX_COUNT  2
// CVisionAgentSimulationViewDlg 대화 상자입니다.

struct stUnitAxis {
	stUnitAxis() {
		axisno = 0;
		xoffset = 0;
		yoffset = 0;
		dpos = 0;
		dmin = 0;
		dmax = 0;
		dscale = 1;
		box.SetRect(-50, -50, 50, 50);
		scope.SetRect(-50, -50, 50, 50);
		zbar.SetRect(-40, -25, 80, 25);
		zscope.SetRect(-40, -25, 80, 25);
	}
	int		axisno;		//축번호
	int		xoffset;	//0점좌표옵셋(중심기준)
	int		yoffset;	//0점좌표옵셋(중심기준)
	double	dpos;		//실좌표값
	double	dmin;		//최소치
	double	dmax;		//최대치	
	double	dscale;		//배율
	CRect	box;		//축박스
	CRect	scope;		//이동범위
	CRect	zbar;		//Z축박스
	CRect	zscope;		//Z이동범위
};

struct stUnitAxisUVW {
	stUnitAxisUVW() {
		axisno = 0;
		upos = 0;
		vpos = 0;
		wpos = 0;
	}
	int axisno;
	double	upos, vpos, wpos;
};

struct stUnitTension {
	stUnitTension() {
		int i = 0;
		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			TensionL[i] = 0.0;
			TensionR[i] = 0.0;
		}
	}	
	double	TensionL[eGRIPPER_ROW_MAX];
	double	TensionR[eGRIPPER_ROW_MAX];
};

struct stUnitStretch {
	stUnitStretch() {
		int i = 0;
		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			StretchL[i] = 0.0;
			StretchR[i] = 0.0;
		}
	}
	double	StretchL[eGRIPPER_ROW_MAX];
	double	StretchR[eGRIPPER_ROW_MAX];
};

struct stUnitPitch {
	stUnitPitch() {
		int i = 0;
		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			PitchL[i] = 0.0;
			PitchR[i] = 0.0;
		}
	}
	double	PitchL[eGRIPPER_ROW_MAX];
	double	PitchR[eGRIPPER_ROW_MAX];
};

struct stUnitClamp {
	stUnitClamp() {
		int i = 0;
		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			ClampL[i] = _T("OFF");
			ClampR[i] = _T("OFF");
		}
	}
	CString ClampL[eGRIPPER_ROW_MAX];
	CString ClampR[eGRIPPER_ROW_MAX];
};

class CVisionAgentSimulationViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSimulationViewDlg)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CVisionAgentSimulationViewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentSimulationViewDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_SIMULATION_VIEW_DIALOG };
#endif

	CBrush Colorbrush;

	stUnitAxis	AxGantryX, AxGantryY;
	stUnitAxis	Ax3dX;
	stUnitAxis	AxInspectX, AxInspectY, AxInspectZ;
	stUnitAxis	AxBackLightX;

	stUnitAxis	AxPaperUnloaderY, AxPaperUnloaderZ;

	stUnitAxis	AxUnloaderZ;
	stUnitAxis	AxLoaderY;
	//stUnitAxis	AxBoxCamLeftY, AxBoxCamRightY;
	stUnitAxis	AxUnloadstageY;
	stUnitAxis	AxCameraZ1;// , AxCameraZ2, AxCamera3dZ;
	stUnitAxis	AxCassetteZ;
	stUnitAxis	AxLoaderZ;
	stUnitAxis	AxLoadport;

	stUnitAxis	AxZbarLoader;
	stUnitAxis	AxZbarUnloader;
	stUnitAxis	AxZbarInspect;
	stUnitAxis	AxZbarZ1, AxZbarZ2, AxZbarZ3;
	stUnitAxis	AxZbarCassette;

	stUnitAxisUVW	AxInspectuvw, AxBoxuvw;

	stUnitAxis	AxStretchL[eGRIPPER_ROW_MAX], AxStretchR[eGRIPPER_ROW_MAX];

	stUnitTension	unitTension;
	stUnitStretch	unitStretch;
	//stUnitPitch		unitPitch;
	stUnitClamp	unitClamp;

	//CRect	RectGantryStoneY1, RectGantryStoneY2;
	//CRect	RectUnloaderStoneY1, RectUnloaderStoneY2;

	INT m_nRealWidth;
	INT m_nRealHeight;

	INT		m_nZbarHeight;	// Z축Box Scope(높이)

	CBrush	m_brBlack;
	CBrush	m_brGantryStone;
	CBrush	m_brGantryY, m_brUnloaderY;
	CBrush	m_brLoader, m_brUnloader;
	CBrush	m_brPaper;
	CBrush  m_brBackLightX;
	CBrush	m_br3d;
	CBrush	m_brReverse;
	CBrush	m_brCamOn, m_brCamOff;
	CBrush	m_brInspect;
	CBrush	m_brLoadport;
	CBrush  m_brUnloadstage;
	CBrush	m_brCassette;
	CBrush	m_brUnitBox;
	CBrush	m_brStick;
	CBrush	m_brStretch;

	CFont	m_Font;
	CPen	m_Align;		// Align guide
	CPen	m_YBlock;		// Y Stage Area
	CPen	m_Frame;		// Frame
	CPen	m_Loader;		// Loader
	CPen	m_Worked;		// Worked Mask
	CPen	m_NonWorked;	// non worked Mask
	CPen	m_Black;
	CPen	*m_pOldPen;

	static CVisionAgentSimulationViewDlg* GetInstance(void) { static CVisionAgentSimulationViewDlg _instance; return &_instance; }

	void setAxisScale(stUnitAxis* axis, double dscale, double dmin, double dmax);
	void setAxisOffset(stUnitAxis* axis, int xoffset, int yoffset);
	void setAxisBoxX(stUnitAxis* axis, int nboxwidth, int nboxheight);
	void setAxisBoxY(stUnitAxis* axis, int nboxwidth, int nboxheight);
	void setAxisBoxZ(stUnitAxis* axis, int nboxwidth, int nboxheight);

	void setAxisX(stUnitAxis* axis, double dscale, double dmin, double dmax, int xoffset, int yoffset, int nboxwidth, int nboxheight);
	void setAxisY(stUnitAxis* axis, double dscale, double dmin, double dmax, int xoffset, int yoffset, int nboxwidth, int nboxheight);
	void setAxisZ(stUnitAxis* axis, double dmin, double dmax, int xoffset, int yoffset, int nboxwidth, int nboxheight);
	void setAxisYbox(stUnitAxis* axis, int nboxwidth, int nboxheight);

	void setAxisZbar(stUnitAxis* axis, int nleft, int ntop);

	void setAxisPosX(stUnitAxis* axis, double dpos);
	void setAxisPosStretch(stUnitAxis* axis, double dpos, double dPosBase);
	void setAxisPosY(stUnitAxis* axis, double dpos);
	void setAxisPosZ(stUnitAxis* axis, double dpos);
	void setAxisUVWpos(stUnitAxisUVW* axis, double du, double dv, double dw);

	void Draw_Overlay(CDC *pDC);
	void Get_UnitPosition();


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);


	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	void Draw_Picture();
	void Draw_Unit(CDC *pDC);
};


