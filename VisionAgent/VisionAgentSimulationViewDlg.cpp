// VisionAgentSimulationViewDlg.cpp : 구현 파일입니다.
#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentSimulationViewDlg.h"
#include "afxdialogex.h"


// CVisionAgentSimulationViewDlg 대화 상자입니다.
IMPLEMENT_DYNAMIC(CVisionAgentSimulationViewDlg, CDialogEx)

CVisionAgentSimulationViewDlg::CVisionAgentSimulationViewDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_VISION_AGENT_SIMULATION_VIEW_DIALOG, pParent)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	LOGBRUSH lbr;
	int i = 0;

	////////////////////////////////////////////
	m_nRealWidth = 4000;		//window width
	m_nRealHeight = 2000;		//window height
	m_nZbarHeight = 400;		//Z축표시 height
	////////////////////////////////////////////

	Colorbrush.CreateSolidBrush(RGB(50, 50, 50));

	m_brBlack.CreateSolidBrush(RGB(0, 0, 0));
	m_brLoadport.CreateSolidBrush(RGB(30, 60, 60));
	m_brLoader.CreateSolidBrush(RGB(150, 90, 150));
	m_brPaper.CreateSolidBrush(RGB(255, 120, 0));
	m_brGantryStone.CreateSolidBrush(RGB(150, 150, 150));
	m_brGantryY.CreateSolidBrush(RGB(130, 190, 130));
	m_brInspect.CreateSolidBrush(RGB(230, 230, 230));
	m_br3d.CreateSolidBrush(RGB(50, 50, 50));
	m_brBackLightX.CreateSolidBrush(RGB(20, 110, 180));
	m_brUnloaderY.CreateSolidBrush(RGB(30, 30, 30));
	m_brUnloader.CreateSolidBrush(RGB(30, 90, 90));
	m_brCamOn.CreateSolidBrush(RGB(250, 50, 50));
	m_brCamOff.CreateSolidBrush(RGB(150, 120, 60));
	m_brReverse.CreateSolidBrush(RGB(150, 200, 220));
	m_brUnloadstage.CreateSolidBrush(RGB(30, 60, 60));
	m_brCassette.CreateSolidBrush(RGB(30, 30, 60));
	m_brUnitBox.CreateSolidBrush(RGB(150, 60, 60));
	m_brStick.CreateSolidBrush(RGB(250, 250, 90));
	m_brStretch.CreateSolidBrush(RGB(255, 255, 0));

	lbr.lbStyle = BS_SOLID;
	lbr.lbHatch = 0;
	lbr.lbColor = RGB(127, 127, 127);	m_Black.CreatePen(PS_GEOMETRIC | PS_SOLID, 3, &lbr, 0, 0);
	lbr.lbColor = RGB(127, 127, 127);	m_Align.CreatePen(PS_GEOMETRIC | PS_DOT, 3, &lbr, 0, 0);
	lbr.lbColor = RGB(0, 200, 0);		m_Frame.CreatePen(PS_GEOMETRIC | PS_SOLID, 3, &lbr, 0, 0);
	lbr.lbColor = RGB(0, 127, 0);		m_Worked.CreatePen(PS_GEOMETRIC | PS_SOLID, 3, &lbr, 0, 0);
	lbr.lbColor = RGB(127, 0, 0);		m_NonWorked.CreatePen(PS_GEOMETRIC | PS_DOT, 3, &lbr, 0, 0);
	lbr.lbColor = RGB(0, 200, 200);		m_YBlock.CreatePen(PS_GEOMETRIC | PS_SOLID, 3, &lbr, 0, 0);
	lbr.lbColor = RGB(0, 200, 200);		m_Loader.CreatePen(PS_GEOMETRIC | PS_SOLID, 3, &lbr, 0, 0);

	m_Font.CreateFontW(50, 0, 0, 0, FW_THIN, 0, 0, 0, 0, 0, 0, 10, 0, _T("Verdana"));

	//축기본값 설정 scale,min,max					//offset x,y								//표시될박스 width,height
	setAxisScale(&AxGantryX, 1.5, -450, 450);		setAxisOffset(&AxGantryX, 0, 0);			setAxisBoxX(&AxGantryX, 110, 100);
	setAxisScale(&AxBackLightX, 1.4, -450, 450);	setAxisOffset(&AxBackLightX, 0, 0);	setAxisBoxY(&AxBackLightX, 100, 810);
	//setAxisScale(&AxInspectX, 1, -100, 100);		setAxisOffset(&AxInspectX, 0, 0);			setAxisBoxX(&AxInspectX, 100, 100);
	//setAxisScale(&Ax3dX, 0.6, -1100, 1100);			setAxisOffset(&Ax3dX, 0, -450);				setAxisBoxX(&Ax3dX, 100, 50);

	setAxisScale(&AxGantryY, 0.6, -750, 750);		setAxisOffset(&AxGantryY, 0, 200);			setAxisBoxY(&AxGantryY, 1960, 80);
	setAxisScale(&AxInspectY, 0.4, -500, 0);		setAxisOffset(&AxInspectY, 0, 200);			setAxisBoxY(&AxInspectY, 1460, 760);
	setAxisScale(&AxPaperUnloaderY, 0.4, -1600, 0);		setAxisOffset(&AxPaperUnloaderY, 0, -650);		setAxisBoxY(&AxPaperUnloaderY, 1600, 60);
	//setAxisScale(&AxBoxCamLeftY, 0.3, 0, 400);			setAxisOffset(&AxBoxCamLeftY, -800, 950);		setAxisBoxY(&AxBoxCamLeftY, 60, 80);
//	setAxisScale(&AxBoxCamRightY, 0.3, 0, 400);		setAxisOffset(&AxBoxCamRightY, 800, 950);		setAxisBoxY(&AxBoxCamRightY, 60, 80);
	setAxisScale(&AxUnloadstageY, 170, 0, 1);		setAxisOffset(&AxUnloadstageY, 0, -640);	setAxisBoxY(&AxUnloadstageY, 1460, 260);

	setAxisScale(&AxLoaderY, 0.4, -2200, 0);		setAxisOffset(&AxLoaderY, 0, 0);			setAxisBoxY(&AxLoaderY, 1600, 60);

	setAxisScale(&AxCameraZ1, 1, 0, 320);			setAxisOffset(&AxCameraZ1, 0, 0);			setAxisBoxZ(&AxCameraZ1, 100, 70);
	//setAxisScale(&AxCameraZ2, 1, 0, 260);			setAxisOffset(&AxCameraZ2, 0, 0);			setAxisBoxZ(&AxCameraZ2, 100, 70);
	//setAxisScale(&AxCamera3dZ, 1, 0, 328);			setAxisOffset(&AxCamera3dZ, 0, 0);			setAxisBoxZ(&AxCamera3dZ, 100, 70);
	setAxisScale(&AxLoaderZ, 1, -180, 145);			setAxisOffset(&AxLoaderZ, 0, 0);			setAxisBoxZ(&AxLoaderZ, 100, 100);
	setAxisScale(&AxUnloaderZ, 1, 0, 250);			setAxisOffset(&AxUnloaderZ, 0, 0);			setAxisBoxZ(&AxUnloaderZ, 100, 100);
	//setAxisScale(&AxInspectZ, 1, -6, 1);			setAxisOffset(&AxInspectZ, 0, 0);			setAxisBoxZ(&AxInspectZ, 100, 100);
	setAxisScale(&AxCassetteZ, 1, 0, 550);			setAxisOffset(&AxCassetteZ, 0, -880);		setAxisBoxZ(&AxCassetteZ, 1500, 160);
	setAxisScale(&AxLoadport, 1, 0, 0);				setAxisOffset(&AxLoadport, 0, 880);			setAxisBoxZ(&AxLoadport, 1500, 180);
	setAxisScale(&AxPaperUnloaderZ, 1, 0, 110);		setAxisOffset(&AxPaperUnloaderZ, 0, 0);		setAxisBoxZ(&AxPaperUnloaderZ, 100, 100);
#ifndef GRIPPER_0
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		setAxisScale(&AxStretchL[i], 3.0, -5, 25);		setAxisOffset(&AxStretchL[i], -850, 200 + (i * 35));	setAxisBoxX(&AxStretchL[i], 200, 35);
		setAxisScale(&AxStretchR[i], 3.0, -5, 25);		setAxisOffset(&AxStretchR[i], 850, 200 + (i * 35));	setAxisBoxX(&AxStretchR[i], 200, 35);
	}
#endif
	//BackLight X
	//setAxisOffset(&AxBackLightX, AxInspectY.box.left + 50, AxInspectY.box.bottom);
	AxBackLightX.box.top = AxInspectY.box.top - 50;
	AxBackLightX.box.bottom = AxInspectY.box.bottom + 50;

	AxPaperUnloaderY.box.left = AxGantryX.scope.left - 150;
	AxPaperUnloaderY.box.right = AxGantryX.scope.right + 150;

	AxLoaderY.box.left = AxGantryX.scope.left - 150;
	AxLoaderY.box.right = AxGantryX.scope.right + 150;

	AxLoaderZ.box.left = AxGantryX.scope.left;
	AxLoaderZ.box.right = AxGantryX.scope.right;
	//Ax3dX.box.bottom = Ax3dX.box.top + 150;
	AxGantryX.box.top = AxGantryX.box.bottom - 150;
	AxPaperUnloaderY.scope.top -= 20;
	AxPaperUnloaderY.scope.bottom += 20;
	AxGantryY.scope.top -= 20;
	AxGantryY.scope.bottom += 20;

	AxLoaderY.scope.top -= 20;
	AxLoaderY.scope.bottom += 20;

	//Z축bar
	setAxisZbar(&AxLoaderZ, -1900, -800);
	setAxisZbar(&AxCameraZ1, -1800, -800);
	//setAxisZbar(&AxCameraZ2, -1700, -800);
	//setAxisZbar(&AxCamera3dZ, -1600, -800);
	setAxisZbar(&AxUnloaderZ, -1700, -800);
	setAxisZbar(&AxCassetteZ, -1600, -800);
	setAxisZbar(&AxPaperUnloaderZ, -1500, -800);
	
}

CVisionAgentSimulationViewDlg::~CVisionAgentSimulationViewDlg()
{
	Colorbrush.DeleteObject();
	m_brBlack.DeleteObject();
	m_br3d.DeleteObject();
	m_brGantryY.DeleteObject();
	m_brUnloaderY.DeleteObject();
	m_brBackLightX.DeleteObject();
	m_brGantryStone.DeleteObject();
	m_brLoader.DeleteObject();
	m_brPaper.DeleteObject();
	m_brUnloader.DeleteObject();
	m_brCamOn.DeleteObject();
	m_brCamOff.DeleteObject();
	m_brStick.DeleteObject();
	m_brInspect.DeleteObject();
	m_brUnloadstage.DeleteObject();
	m_brReverse.DeleteObject();
	m_brLoadport.DeleteObject();
	m_brCassette.DeleteObject();
	m_brUnitBox.DeleteObject();
	m_NonWorked.DeleteObject();
	m_Align.DeleteObject();
	m_Frame.DeleteObject();
	m_Worked.DeleteObject();
	m_NonWorked.DeleteObject();
	m_YBlock.DeleteObject();
	m_Loader.DeleteObject();
	m_brStretch.DeleteObject();
}

void CVisionAgentSimulationViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// CVisionAgentSimulationViewDlg 메시지 처리기입니다.
BEGIN_MESSAGE_MAP(CVisionAgentSimulationViewDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	//ON_WM_CTLCOLOR_REFLECT()
	//ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL CVisionAgentSimulationViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;
}

void CVisionAgentSimulationViewDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE){
		SetTimer(1, 300, NULL);
	}
	else if (bShow == FALSE){
		KillTimer(1);
	}
}

void CVisionAgentSimulationViewDlg::OnTimer(UINT_PTR nIDEvent)
{
	Draw_Picture();

	CDialogEx::OnTimer(nIDEvent);
}

void CVisionAgentSimulationViewDlg::OnCancel()
{

	CDialogEx::OnCancel();
}

void CVisionAgentSimulationViewDlg::OnOK()
{
	//CDialogEx::OnOK();
}

//축Scale 초기화
void CVisionAgentSimulationViewDlg::setAxisScale(stUnitAxis* axis, double dscale, double dmin, double dmax)
{
	axis->dscale = dscale;
	axis->dmin = dmin;
	axis->dmax = dmax;
}

//축Offset 초기화
void CVisionAgentSimulationViewDlg::setAxisOffset(stUnitAxis* axis, int xoffset, int yoffset)
{
	axis->xoffset = xoffset;
	axis->yoffset = yoffset;
}

//X축초기화
void CVisionAgentSimulationViewDlg::setAxisBoxX(stUnitAxis* axis, int nboxwidth, int nboxheight)
{
	axis->box.left = axis->dpos * axis->dscale + axis->xoffset - nboxwidth / 2;
	axis->box.right = axis->dpos * axis->dscale + axis->xoffset + nboxwidth / 2;
	axis->box.top = axis->yoffset - nboxheight / 2;
	axis->box.bottom = axis->yoffset + nboxheight / 2;
	axis->scope.left = axis->dmin * axis->dscale + axis->xoffset - nboxwidth / 2;
	axis->scope.right = axis->dmax * axis->dscale + axis->xoffset + nboxwidth / 2;
	axis->scope.top = axis->box.top;
	axis->scope.bottom = axis->box.bottom;
}

//Y축초기화
void CVisionAgentSimulationViewDlg::setAxisBoxY(stUnitAxis* axis, int nboxwidth, int nboxheight)
{
	axis->box.left = axis->xoffset - nboxwidth / 2;
	axis->box.right = axis->xoffset + nboxwidth / 2;
	axis->box.top = axis->yoffset - (axis->dpos * axis->dscale) - nboxheight / 2;
	axis->box.bottom = axis->yoffset - (axis->dpos * axis->dscale) + nboxheight / 2;
	axis->scope.left = axis->box.left;
	axis->scope.right = axis->box.right;
	axis->scope.top = axis->yoffset - (axis->dmax * axis->dscale) - nboxheight / 2;
	axis->scope.bottom = axis->yoffset - (axis->dmin * axis->dscale) + nboxheight / 2;
}

//Z축초기화
void CVisionAgentSimulationViewDlg::setAxisBoxZ(stUnitAxis* axis, int nboxwidth, int nboxheight)
{
	axis->dscale = m_nZbarHeight / (axis->dmax - axis->dmin);
	axis->box.left = axis->xoffset - nboxwidth / 2;
	axis->box.right = axis->xoffset + nboxwidth / 2;
	axis->box.top = axis->yoffset - nboxheight / 2;
	axis->box.bottom = axis->yoffset + nboxheight / 2;

	CRect	zbar;		//Z축박스
	CRect	zscope;		//Z이동범위
}

//Z-Bar초기화
void CVisionAgentSimulationViewDlg::setAxisZbar(stUnitAxis* axis, int nleft, int ntop)
{
	axis->zbar.SetRect(nleft, ntop, nleft + 90, ntop + 50);
	axis->zscope.SetRect(nleft, ntop, nleft + 90, ntop + m_nZbarHeight + 50);
}

//X축위치
void CVisionAgentSimulationViewDlg::setAxisPosX(stUnitAxis* axis, double dpos)
{
	int dtemp = axis->xoffset + (int)(dpos * axis->dscale);
	axis->dpos = dpos;
	axis->box.MoveToX(dtemp - (axis->box.right - axis->box.left) / 2);
}
//Stretch축 위치
void CVisionAgentSimulationViewDlg::setAxisPosStretch(stUnitAxis* axis, double dpos, double dPosBase)
{
	int dtemp = axis->xoffset + (int)(dpos * axis->dscale);
	axis->dpos = dpos;
	axis->box.MoveToX(dtemp - (axis->box.right - axis->box.left) / 2);
}
//Y축위치
void CVisionAgentSimulationViewDlg::setAxisPosY(stUnitAxis* axis, double dpos)
{
	int dtemp = axis->yoffset - (int)(dpos * axis->dscale); //위치 증가시 좌표는 감소
	axis->dpos = dpos;
	axis->box.MoveToY(dtemp - (axis->box.bottom - axis->box.top) / 2);
	axis->zbar.MoveToY(dtemp);
}
//Z축위치
void CVisionAgentSimulationViewDlg::setAxisPosZ(stUnitAxis* axis, double dpos)
{
	int dtemp = axis->zscope.top + (int)((axis->dmax - dpos) * axis->dscale);  //위치 증가시 좌표는 감소
	axis->dpos = dpos;
	axis->zbar.MoveToY(dtemp);
}

void CVisionAgentSimulationViewDlg::setAxisUVWpos(stUnitAxisUVW* axis, double du, double dv, double dw)
{
	axis->upos = du;
	axis->vpos = dv;
	axis->wpos = dw;
}

void CVisionAgentSimulationViewDlg::Get_UnitPosition()
{
	int i = 0;

	setAxisPosX(&AxGantryX, SharedInfo::GetCmdPos(AXIS_GANTRY_X));
	//setAxisPosX(&AxBackLightX, SharedInfo::GetCmdPos(AXIS_BACKLIGHT_X));

	setAxisPosY(&AxGantryY, SharedInfo::GetActPos(AXIS_GANTRY_Y1));
	//setAxisPosY(&AxUnloadstageY, SharedInfo::DInputValue[_DIN_SEPARAT_PLATE_BACK]);
	//setAxisPosY(&AxPaperUnloaderY, SharedInfo::GetCmdPos(AXIS_UNLOADER_YL));

	//setAxisPosY(&AxLoaderY, SharedInfo::GetCmdPos(AXIS_LOADER_YL));

	//setAxisPosY(&AxBoxCamLeftY, SharedInfo::GetCmdPos(AXIS_BOX_ALIGN_CAMERA_YL));
	//setAxisPosY(&AxBoxCamRightY, SharedInfo::GetCmdPos(AXIS_BOX_ALIGN_CAMERA_YR));

	setAxisPosZ(&AxCameraZ1, SharedInfo::GetCmdPos(AXIS_CAMERA_Z1));
	//setAxisPosZ(&AxCameraZ2, SharedInfo::GetCmdPos(AXIS_CAMERA_Z2));
	//setAxisPosZ(&AxCamera3dZ, SharedInfo::GetCmdPos(AXIS_CAMERA_Z3));
	//setAxisPosZ(&AxCassetteZ, SharedInfo::GetCmdPos(AXIS_MAGAZINE_LIFT_Z));

	//setAxisPosZ(&AxLoaderZ, SharedInfo::GetCmdPos(AXIS_LOADER_Z));

	//setAxisPosZ(&AxUnloaderZ, SharedInfo::GetCmdPos(AXIS_UNLOADER_Z));

	//setAxisPosZ(&AxPaperUnloaderZ, SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL));
	
	setAxisUVWpos(&AxInspectuvw, SharedInfo::GetCmdPos(AXIS_GLASS_UVW_Y1), SharedInfo::GetCmdPos(AXIS_GLASS_UVW_Y2), SharedInfo::GetCmdPos(AXIS_GLASS_UVW_X1));
	//setAxisUVWpos(&AxBoxuvw, SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_X), SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_Y1), SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_Y2));
}

void CVisionAgentSimulationViewDlg::Draw_Unit(CDC *pDC)
{
	USES_CONVERSION;
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	double		dy, dy1, dy2, dyL[eGRIPPER_ROW_MAX], dyR[eGRIPPER_ROW_MAX];
	double		dPosy[5];		//Stage 5개 Position Y 값
	int			ntemp;
	long		n1, n2;
	long		PaperX, UnloadX, LoadX;
	CString		sMsg, str;
	CRect		rect;
	LOGBRUSH	lbr;
	CPen		pen;
	CPen		Linepen;
	int			oldBkMode;
	CPen*		poldPen;
	CFont*		poldFont;
	CBrush*		poldBrush;
	stUnitAxis	Ax;
	int i = 0;

	poldBrush = (CBrush*)pDC->SelectObject(&m_brBlack);
	poldPen = (CPen*)pDC->SelectObject(&pen);
	poldFont = (CFont*)pDC->SelectObject(&m_Font);
	oldBkMode = pDC->SetBkMode(OPAQUE);  //불투명배경

	//======================배경 그리기==========================	
	pDC->SetROP2(R2_COPYPEN);
	//배경 검정색으로
	CRect rcDraw(-m_nRealWidth / 2, -m_nRealHeight / 2, m_nRealWidth, m_nRealHeight / 2);
	pDC->SelectObject(&m_brBlack);
	pDC->FillRect(rcDraw, &m_brBlack);

	//3D범위
	pDC->SelectObject(&m_br3d);
	//pDC->Rectangle(Ax3dX.scope);

	////BoxCamera 범위
	//pDC->Rectangle(AxBoxCamLeftY.scope);
	//pDC->Rectangle(AxBoxCamRightY.scope);

	//Stretch범위
	//pDC->Rectangle(AxStretchL[0].scope);
	//pDC->Rectangle(AxStretchL[1].scope);
	//pDC->Rectangle(AxStretchL[2].scope);
	//pDC->Rectangle(AxStretchL[3].scope);

	//pDC->Rectangle(AxStretchR[0].scope);
	//pDC->Rectangle(AxStretchR[1].scope);
	//pDC->Rectangle(AxStretchR[2].scope);
	//pDC->Rectangle(AxStretchR[3].scope);

	//Z-Bar
	pDC->SelectObject(&m_brGantryY);
	pDC->Rectangle(AxLoaderZ.zscope);
	pDC->Rectangle(AxUnloaderZ.zscope);
	pDC->Rectangle(AxCassetteZ.zscope);
	pDC->Rectangle(AxCameraZ1.zscope);
	pDC->Rectangle(AxPaperUnloaderZ.zscope);
	//pDC->Rectangle(AxCameraZ2.zscope);
	//pDC->Rectangle(AxCamera3dZ.zscope);
	//pDC->Rectangle(AxInspectZ.zscope);

	//GantryStone
	pDC->SelectObject(&m_brGantryStone);
	pDC->Rectangle(AxGantryX.scope.left - 250, AxGantryY.scope.top, AxGantryX.scope.left - 150, AxGantryY.scope.bottom);
	pDC->Rectangle(AxGantryX.scope.right + 150, AxGantryY.scope.top, AxGantryX.scope.right + 250, AxGantryY.scope.bottom);

	//PaperUnloaderStone
	pDC->Rectangle(AxGantryX.scope.left - 140, AxPaperUnloaderY.scope.top, AxGantryX.scope.left - 40, AxPaperUnloaderY.scope.bottom);
	pDC->Rectangle(AxGantryX.scope.right + 40, AxPaperUnloaderY.scope.top, AxGantryX.scope.right + 140, AxPaperUnloaderY.scope.bottom);

	//UnloaderStone
	pDC->Rectangle(AxGantryX.scope.left - 140, AxLoaderY.scope.top, AxGantryX.scope.left - 40, AxLoaderY.scope.bottom);
	pDC->Rectangle(AxGantryX.scope.right + 40, AxLoaderY.scope.top, AxGantryX.scope.right + 140, AxLoaderY.scope.bottom);

	////======================장치 그리기==========================
	dy = -(AxGantryY.dpos * AxGantryY.dscale) + AxGantryY.yoffset - 40;		//Gantry_Y 좌표값
	n1 = AxGantryX.scope.left;
	n2 = AxGantryX.scope.right;

	dy1 = -(AxGantryY.dpos * AxGantryY.dscale) + AxGantryY.yoffset - 40;		//Loder 좌표값

	PaperX = 0.0; // -SharedInfo::GetCmdPos(AXIS_UNLOADER_XL) + 600;
	UnloadX = 0.0; // SharedInfo::GetCmdPos(AXIS_UNLOADER_X);
	LoadX = 0.0; //SharedInfo::GetCmdPos(AXIS_LOADER_X);


	//Cassette	
	pDC->SelectObject(&m_brCassette);
	pDC->Rectangle(AxCassetteZ.box);

	//Unloadstage	
	pDC->SetROP2(R2_XORPEN);
	pDC->SelectObject(&m_brUnloadstage);
	pDC->Rectangle(AxUnloadstageY.box);

	//Backlight X
	pDC->SelectObject(&m_brBackLightX);
	pDC->Rectangle(AxBackLightX.box.left, n1, AxBackLightX.box.right, n1);
	pDC->Rectangle(AxBackLightX.box);

	pDC->SetROP2(R2_COPYPEN);
	//InspectStage
	pDC->SelectObject(&m_brInspect);
	pDC->Rectangle(AxInspectY.box);

	//Loadport
	pDC->SelectObject(&m_brLoadport);
	pDC->Rectangle(AxLoadport.box);

	//Stretch
	pDC->SelectObject(&m_brStretch);
	
#ifndef GRIPPER_0
	for (i = 0; i<eGRIPPER_ROW_MAX; i++)
	{
		//20210802 JINI
		//AxStretchL[i].box.MoveToY(dyL[i]);
		//AxStretchR[i].box.MoveToY(dyR[i]);

		pDC->Rectangle(AxStretchL[i].box);
		pDC->Rectangle(AxStretchR[i].box);
	}
#endif
	//Y축값
	pDC->SelectObject(&m_brGantryStone);

	//Gantry 이동에 맞춤	
	AxGantryY.box.MoveToY((int)dy);
	AxGantryX.box.MoveToY((int)dy);
	AxLoaderZ.box.MoveToY((int)dy + 180);
	AxCameraZ1.box.MoveToY((int)dy + 70);
	//AxCameraZ2.box.MoveToY((int)dy - 70);
	//AxCamera3dZ.box.MoveToY((int)dy - 140);

	AxCameraZ1.box.MoveToX(AxGantryX.box.left + 5);
	//AxCameraZ2.box.MoveToX(AxGantryX.box.left + 5);
	//AxCamera3dZ.box.MoveToX(AxGantryX.box.left + 5);

	//Stick  (각stage에 있을 때)
	pDC->SetROP2(R2_COPYPEN);
	dPosy[0] = (AxLoadport.box.top + AxLoadport.box.bottom) / 2 - 45;
	dPosy[1] = dy + 94;
	dPosy[2] = (AxInspectY.box.top + AxInspectY.box.bottom) / 2 - 150;
	dPosy[3] = (AxPaperUnloaderY.box.top + AxPaperUnloaderY.box.bottom) / 2 - 50;
	dPosy[4] = (AxUnloadstageY.box.top + AxUnloadstageY.box.bottom) / 2 - 45;
	//Total_Log(_T(" stick dPosy[0] = %.0f"), dPosy[0]);	
	pDC->SelectObject(&m_brStick);
	rect.SetRect(-600, -55, 600, 55);
	for (int i = 0; i < 5; i++) {
		if (strlen(pDlg->m_POSITION[i].STICKID) != 0) {
			rect.MoveToY(dPosy[i]);
			pDC->Rectangle(rect);
		}
	}

	//GantryStone X
	pDC->SelectObject(&m_brGantryY);
	pDC->Rectangle(AxGantryY.box);
	pDC->Rectangle(AxGantryX.box);

	//Stick Unloader Gantry에 달려서 같이 움직인다.
	pDC->SelectObject(&m_brPaper);
	pDC->Rectangle(-UnloadX, (int)dy - 130, -UnloadX + 40, (int)dy);		//Paper-Left
	pDC->Rectangle(UnloadX - 40, (int)dy - 130, UnloadX, (int)dy);		//Paper-right
	pDC->Rectangle(n1, (int)dy - 90, n2, (int)dy - 40);			//Paper_X

	//Loader 
	pDC->SelectObject(&m_brLoader);
	pDC->Rectangle(-LoadX, AxLoaderY.box.top - 30, -LoadX + 40, AxLoaderY.box.bottom + 30);	//Left
	pDC->Rectangle(LoadX - 40, AxLoaderY.box.top - 30, LoadX, AxLoaderY.box.bottom + 30);	//right
	pDC->Rectangle(AxLoaderY.box);

	//PaperUnloader	
	pDC->SelectObject(&m_brUnloader);
	pDC->Rectangle(-PaperX, AxPaperUnloaderY.box.top - 30, -PaperX+40, AxPaperUnloaderY.box.bottom + 30);	//Left
	pDC->Rectangle(PaperX -40, AxPaperUnloaderY.box.top - 30, PaperX, AxPaperUnloaderY.box.bottom + 30);	//right
	pDC->Rectangle(AxPaperUnloaderY.box);

	////CAMERA
	pDC->SelectObject(&m_brCamOff);
	pDC->Rectangle(AxCameraZ1.box);
	//pDC->Rectangle(AxCameraZ2.box);
	//pDC->Rectangle(AxCamera3dZ.box);

	//3DCamera
	//Ax3dX.box.left -= 650;
	//Ax3dX.box.right -= 650;
	//pDC->Rectangle(Ax3dX.box);
	//Ax3dX.box.left += 650;
	//Ax3dX.box.right += 650;

	////BoxCamera
	//pDC->SelectObject(&m_brUnitBox);
	//pDC->Rectangle(AxBoxCamLeftY.box);
	//pDC->Rectangle(AxBoxCamRightY.box);	

	//Z-Bar
	pDC->SelectObject(&m_brUnitBox);
	pDC->Rectangle(AxLoaderZ.zbar);
	pDC->Rectangle(AxUnloaderZ.zbar);
	pDC->Rectangle(AxCassetteZ.zbar);
	pDC->Rectangle(AxCameraZ1.zbar);
	pDC->Rectangle(AxPaperUnloaderZ.zbar);

	//pDC->Rectangle(AxCameraZ2.zbar);
	//pDC->Rectangle(AxCamera3dZ.zbar);
	//pDC->Rectangle(AxInspectZ.zbar);

	//-------------
	lbr.lbStyle = BS_SOLID;
	lbr.lbColor = RGB(0, 200, 9);
	lbr.lbHatch = 0;
	pen.CreatePen(PS_GEOMETRIC | PS_DOT, 3, &lbr, 0, 0);

	pDC->SelectObject(&pen);
	pDC->MoveTo(0, -m_nRealHeight / 2 + 100);					//0 = x 기구 움직이는 값
	pDC->LineTo(0, m_nRealHeight / 2 - 100);
	pDC->MoveTo(-m_nRealWidth / 4, AxGantryY.yoffset);			//0 = y 기구 움직이는 값
	pDC->LineTo(m_nRealWidth / 4, AxGantryY.yoffset);

	//============================================================
	pDC->SelectObject(&pen);
	pDC->SelectObject(m_Font);
	pDC->SetTextColor(RGB(200, 200, 200));
	pDC->SetBkMode(TRANSPARENT);

	sMsg.Format(_T("Ld"));		pDC->TextOutW(-1900, -900, sMsg);
	sMsg.Format(_T("Z1"));		pDC->TextOutW(-1800, -900, sMsg);
	//sMsg.Format(_T("Z2"));		pDC->TextOutW(-1700, -900, sMsg);
	//sMsg.Format(_T("Z3"));		pDC->TextOutW(-1600, -900, sMsg);
	sMsg.Format(_T("Un"));		pDC->TextOutW(-1700, -900, sMsg);
	sMsg.Format(_T("Cst"));		pDC->TextOutW(-1600, -900, sMsg);
	sMsg.Format(_T("PUldZ"));		pDC->TextOutW(-1500, -900, sMsg);
#ifndef GRIPPER_0
	sMsg.Format(_T("1      2       3"));
	pDC->TextOutW(1320, -950, sMsg);
	sMsg.Format(_T("Tension-L : %4.3f %4.3f %4.3f"), unitTension.TensionL[0], unitTension.TensionL[1], unitTension.TensionL[2]);
	pDC->TextOutW(1000, -900, sMsg);

	sMsg.Format(_T("Tension-R : %4.3f %4.3f %4.3f"), unitTension.TensionR[0], unitTension.TensionR[1], unitTension.TensionR[2]);
	pDC->TextOutW(1000, -840, sMsg);

	sMsg.Format(_T("Stretch-L  : %4.2f %4.2f %4.2f"), unitStretch.StretchL[0], unitStretch.StretchL[1], unitStretch.StretchL[2]);
	pDC->TextOutW(1000, -780, sMsg);

	sMsg.Format(_T("Stretch-R  : %4.2f %4.2f %4.2f"), unitStretch.StretchR[0], unitStretch.StretchR[1], unitStretch.StretchR[2]);
	pDC->TextOutW(1000, -720, sMsg);

	sMsg.Format(_T("Clamp L:  %s   %s   %s"), unitClamp.ClampL[0], unitClamp.ClampL[1], unitClamp.ClampL[2]);
	pDC->TextOutW(1200, -500, sMsg);

	sMsg.Format(_T("Clamp R:  %s   %s   %s"), unitClamp.ClampR[0], unitClamp.ClampR[1], unitClamp.ClampR[2]);
	pDC->TextOutW(1200, -440, sMsg);
#endif

	sMsg.Format(_T("Gantry-X  : %10.3f"), AxGantryX.dpos);			pDC->TextOutW(1200, -50, sMsg);
	sMsg.Format(_T("Gantry-Y  : %10.3f"), AxGantryY.dpos);			pDC->TextOutW(1200, 10, sMsg);
	//sMsg.Format(_T("BoxCam-L  : %10.3f"), AxBoxCamLeftY.dpos);			pDC->TextOutW(1200, 400, sMsg);
	//sMsg.Format(_T("BoxCam-R  : %10.3f"), AxBoxCamRightY.dpos);		pDC->TextOutW(1200, 500, sMsg);
	sMsg.Format(_T("Loader-Y  : %10.3f"), AxLoaderY.dpos);			pDC->TextOutW(1200, 150, sMsg);
	sMsg.Format(_T("Loader-Z  : %10.3f"), AxLoaderZ.dpos);			pDC->TextOutW(1200, 210, sMsg);
	//sMsg.Format(_T("Loader-x  : %10.3f"), SharedInfo::GetCmdPos(AXIS_LOADER_X));			pDC->TextOutW(1200, 270, sMsg);
	//sMsg.Format(_T("Inspect-Y : %10.3f"), AxInspectY.dpos);			pDC->TextOutW(1200, 300, sMsg);
	//sMsg.Format(_T("Inspect-Z : %10.3f"), AxInspectZ.dpos);			pDC->TextOutW(1200, 300, sMsg);	
	//sMsg.Format(_T("Unloader-Y: %10.3f"), AxPaperUnloaderY.dpos);		pDC->TextOutW(1200, 400, sMsg);
	//sMsg.Format(_T("Unloader-Z: %10.3f"), AxUnloaderZ.dpos);		pDC->TextOutW(1200, 500, sMsg);
	//sMsg.Format(_T("Cassette-Z: %10.3f"), AxCassetteZ.dpos);		pDC->TextOutW(1200, 600, sMsg);

	sMsg.Format(_T("Unloader-Z : %10.3f"), AxUnloaderZ.dpos);		pDC->TextOutW(1200, 410, sMsg);
	sMsg.Format(_T("Unloader-X : %10.3f"), 0.0);		pDC->TextOutW(1200, 470, sMsg);

	sMsg.Format(_T("Camera-Z1 : %10.3f"), AxCameraZ1.dpos);			pDC->TextOutW(1200, 610, sMsg);
	//sMsg.Format(_T("Camera-Z2 : %10.3f"), AxCameraZ2.dpos);			pDC->TextOutW(1200, 800, sMsg);
	//sMsg.Format(_T("Camera-Z3 : %10.3f"), AxCamera3dZ.dpos);			pDC->TextOutW(1200, 900, sMsg);


	//sMsg.Format(_T("Pitch-R      : %4.1f  %4.1f  %4.1f  %4.1f"), unitPitch.PitchR[0], unitPitch.PitchR[1], unitPitch.PitchR[2], unitPitch.PitchR[3]);
	//pDC->TextOutW(1000, -600, sMsg);

	//sMsg.Format(_T("Buffer    : %10.3f"), AxUnloadstageY.dpos);		pDC->TextOutW(-1900, -200, sMsg);

#if 0
	if (AxUnloadstageY.dpos < 1.0)
	{
		sMsg.Format(_T("Buffer-CYL:    FORWARD"));						pDC->TextOutW(-1900, -200, sMsg);
	}
	else
	{
		sMsg.Format(_T("Buffer-CYL:   BACKWARD"));					pDC->TextOutW(-1900, -200, sMsg);
	}
#endif

	//sMsg.Format(_T("3DCamera-X: %10.3f"), Ax3dX.dpos);				pDC->TextOutW(-1900, 0, sMsg);
	//sMsg.Format(_T("Inspect-Y : %10.3f"), AxInspectY.dpos);			pDC->TextOutW(-1900, 100, sMsg);
	//sMsg.Format(_T("Inspect-Z : %10.3f"), AxInspectZ.dpos);			pDC->TextOutW(-1900, 200, sMsg);	

	sMsg.Format(_T("Cassette-Z : %10.3f"), 0.0);		pDC->TextOutW(-1900, -190, sMsg);

	sMsg.Format(_T("InspUvw-X  : %10.3f"), AxInspectuvw.upos);		pDC->TextOutW(-1900, -50, sMsg);
	sMsg.Format(_T("InspUvw-Y1 : %10.3f"), AxInspectuvw.vpos);		pDC->TextOutW(-1900, 10, sMsg);
	sMsg.Format(_T("InspUvw-Y2 : %10.3f"), AxInspectuvw.wpos);		pDC->TextOutW(-1900, 70, sMsg);

	sMsg.Format(_T("BoxUvw-X   : %10.3f"), AxBoxuvw.upos);			pDC->TextOutW(-1900, 210, sMsg);
	sMsg.Format(_T("BoxUvw-Y1  : %10.3f"), AxBoxuvw.vpos);			pDC->TextOutW(-1900, 270, sMsg);
	sMsg.Format(_T("BoxUvw-Y2  : %10.3f"), AxBoxuvw.wpos);			pDC->TextOutW(-1900, 330, sMsg);

	sMsg.Format(_T("BackLt-X   : %10.3f"), 0.0);			pDC->TextOutW(-1900, 470, sMsg);//900

	sMsg.Format(_T("Paper-Y	   : %10.3f"), 0.0);		pDC->TextOutW(-1900, 610, sMsg);
	sMsg.Format(_T("Paper-Z    : %10.3f"), 0.0);	pDC->TextOutW(-1900, 670, sMsg);
	sMsg.Format(_T("Paper-X	   : %10.3f"), 0.0);		pDC->TextOutW(-1900, 730, sMsg);

	//============================================================


	lbr.lbStyle = BS_SOLID;
	lbr.lbColor = RGB(200, 0, 9);
	lbr.lbHatch = 0;
	Linepen.CreatePen(PS_GEOMETRIC | PS_DOT, 3, &lbr, 0, 0);

	pDC->SelectObject(&Linepen);

	pDC->MoveTo(-1900, -100);		//
	pDC->LineTo(-1300, -100);

	pDC->MoveTo(-1900, 160);		//BoxUvw-X 
	pDC->LineTo(-1300, 160);

	pDC->MoveTo(-1900, 420);		//BackLt-X
	pDC->LineTo(-1300, 420);

	pDC->MoveTo(-1900, 560);		// Paper-Y
	pDC->LineTo(-1300, 560);

	pDC->MoveTo(1200, -100);		//Gantry-X
	pDC->LineTo(1800, -100);

	pDC->MoveTo(1200, 100);		//Gantry-Y
	pDC->LineTo(1800, 100);

	pDC->MoveTo(1200, 360);		//Unloader-Z
	pDC->LineTo(1800, 360);

	pDC->MoveTo(1200, 560);		//Camera-Z1
	pDC->LineTo(1800, 560);

	//============================================================

	pDC->SelectObject(poldFont);
	pDC->SelectObject(poldPen);
	pDC->SelectObject(poldBrush);
}


void CVisionAgentSimulationViewDlg::Draw_Picture()
{
	CClientDC dc(this);
	CBitmap mBitmap;
	CRect rc;
	CDC mMemDC;
	CDC* pDC = &dc;

	//Total_Log(_T("--Draw_Picture()--"));

	GetClientRect(&rc);
	mMemDC.CreateCompatibleDC(pDC);
	mBitmap.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	mMemDC.SelectObject(&mBitmap);

	SetMapMode(mMemDC, MM_ANISOTROPIC);							//XY축단위 가변형으로
	mMemDC.SetWindowExt(m_nRealWidth, m_nRealHeight);			//논리좌표상 화면크기설정
	mMemDC.SetViewportExt(rc.Width(), rc.Height());				//논리좌표와 매칭할 뷰포트화면크기
	mMemDC.SetViewportOrg(rc.Width() / 2, (rc.Height() / 2));	//0점위치변경

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(m_nRealWidth, m_nRealHeight);
	pDC->SetViewportExt(rc.Width(), rc.Height());
	pDC->SetViewportOrg(rc.Width() / 2, (rc.Height() / 2));

	CRect rcDraw(-m_nRealWidth / 2, -m_nRealHeight / 2, m_nRealWidth / 2, m_nRealHeight / 2);	//화면논리좌표
	//----------------------

	Get_UnitPosition();		//좌표값 가저오기

	Draw_Unit(&mMemDC);		//화면에 그리기

	pDC->BitBlt(rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), &mMemDC, rcDraw.left, rcDraw.top, SRCCOPY);

	mMemDC.DeleteDC();
}

