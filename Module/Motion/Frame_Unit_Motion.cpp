#include "stdafx.h"
#include "Frame_Unit_Motion.h"

//---------------------------------------------------------------------
CFrame_Unit_Motion::CFrame_Unit_Motion()
{
}
//---------------------------------------------------------------------
CFrame_Unit_Motion::~CFrame_Unit_Motion()
{
}
//---------------------------------------------------------------------
BOOL CFrame_Unit_Motion::InitMotion()
{
	return TRUE;
}
//---------------------------------------------------------------------
BOOL	CFrame_Unit_Motion::Move_UVW(double dPos_U, double dPos_V, double dPos_W)
{
	return TRUE;
}
//---------------------------------------------------------------------
BOOL	CFrame_Unit_Motion::Is_Move_UVW(double dPos_U, double dPos_V, double dPos_W)
{
	return TRUE;
}
//---------------------------------------------------------------------
//2. UVW Stage
BOOL	CFrame_Unit_Motion::Move_UVW_Home_Pos()
{
	// UVW Stage 대기 위치로 이동
	return	TRUE;
}
//---------------------------------------------------------------------
BOOL	CFrame_Unit_Motion::Is_UVW_Home_Pos()
{
	// UVW Stage 대기 위치로 이동 완료 확인
	BOOL	bComplete = FALSE;
	return	bComplete;
}
//---------------------------------------------------------------------
BOOL	CFrame_Unit_Motion::Move_UVW_Wait_Pos()
{
	// UVW Stage 대기 위치로 이동
	return	TRUE;
}
//---------------------------------------------------------------------
BOOL	CFrame_Unit_Motion::Is_UVW_Wait_Pos()
{
	// UVW Stage 대기 위치로 이동 완료 확인
	BOOL	bComplete = TRUE;
	return	bComplete;
}
//---------------------------------------------------------------------
BOOL	CFrame_Unit_Motion::Move_UVW_Align_Pos(double dU_Pos, double dV_Pos, double dW_Pos)
{
	// UVW Stage Align 위치로 이동 
	return	TRUE;
}
//---------------------------------------------------------------------
BOOL	CFrame_Unit_Motion::Is_UVW_Align_Pos(double dU_Pos, double dV_Pos, double dW_Pos)
{
	// UVW Stage Align 위치로 이동 완료 확인
	return	TRUE;
}