#pragma once
#include "BaseMotion.h"
class CPlcModule;
/*-----------------------------------------------------------------------------
1. Frame Loader 부
  - Up/Down
  - Homing
2. Frame 투입 부
  - BCR(Barcode Read)
  - Homing
  - Wait Position
  - Align Position
3. Frame Align
-----------------------------------------------------------------------------*/
class CFrame_Unit_Motion : public CBaseMotion
{
public:
	CFrame_Unit_Motion();
	~CFrame_Unit_Motion();
	
	BOOL InitMotion();

	BOOL	Move_UVW(double dPos_U, double dPos_V, double dPos_W);
	BOOL	Is_Move_UVW(double dPos_U, double dPos_V, double dPos_W);

	//1. UVW Stage
	BOOL	Move_UVW_Home_Pos();												// UVW Stage 원점 위치로 이동
	BOOL	Is_UVW_Home_Pos();													// UVW Stage 원점 위치로 이동 완료 확인
	BOOL	Move_UVW_Wait_Pos();												// UVW Stage 대기 위치로 이동
	BOOL	Is_UVW_Wait_Pos();													// UVW Stage 대기 위치로 이동 완료 확인
	BOOL	Move_UVW_Align_Pos(double dU_Pos, double dV_Pos, double dW_Pos);	// UVW Stage Align 위치로 이동
	BOOL	Is_UVW_Align_Pos(double dU_Pos, double dV_Pos, double dW_Pos);		// UVW Stage Align 위치로 이동 완료 확인
};
/*--------------------------------------------------------------
각 센서 및 인디게이터에서 받는 값을 개별 함수를 호출하여 확인할 것인지?
아니면 각 센서 및 인디게이터에서 받는 값에 대한 변수를 선언하여 
ReadAll()같은 함수를 사용하여 센서 값을 받아오는 방법도 있음.
--------------------------------------------------------------*/
