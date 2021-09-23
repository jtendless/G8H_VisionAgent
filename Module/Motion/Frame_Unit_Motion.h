#pragma once
#include "BaseMotion.h"
class CPlcModule;
/*-----------------------------------------------------------------------------
1. Frame Loader ��
  - Up/Down
  - Homing
2. Frame ���� ��
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
	BOOL	Move_UVW_Home_Pos();												// UVW Stage ���� ��ġ�� �̵�
	BOOL	Is_UVW_Home_Pos();													// UVW Stage ���� ��ġ�� �̵� �Ϸ� Ȯ��
	BOOL	Move_UVW_Wait_Pos();												// UVW Stage ��� ��ġ�� �̵�
	BOOL	Is_UVW_Wait_Pos();													// UVW Stage ��� ��ġ�� �̵� �Ϸ� Ȯ��
	BOOL	Move_UVW_Align_Pos(double dU_Pos, double dV_Pos, double dW_Pos);	// UVW Stage Align ��ġ�� �̵�
	BOOL	Is_UVW_Align_Pos(double dU_Pos, double dV_Pos, double dW_Pos);		// UVW Stage Align ��ġ�� �̵� �Ϸ� Ȯ��
};
/*--------------------------------------------------------------
�� ���� �� �ε�����Ϳ��� �޴� ���� ���� �Լ��� ȣ���Ͽ� Ȯ���� ������?
�ƴϸ� �� ���� �� �ε�����Ϳ��� �޴� ���� ���� ������ �����Ͽ� 
ReadAll()���� �Լ��� ����Ͽ� ���� ���� �޾ƿ��� ����� ����.
--------------------------------------------------------------*/
