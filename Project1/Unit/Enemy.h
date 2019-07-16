#pragma once
#include <tuple>
#include "Obj.h"

enum class E_STATE
{
	VECTOR,
	SIZE,
	TYPE,
	AIM,
	MAX
};

enum class E_TYPE
{
	A,
	B,
	C,
	MAX
};

using ENEMY_T = std::tuple<Vector2, Vector2, E_TYPE, Vector2>;

class Enemy :
	public Obj
{
public:
	Enemy();								// �ݽ�׸�
	Enemy(ENEMY_T state);					// �����t���ݽ�׸�
	~Enemy();								// �޽�׸�
	void Draw(void) override;				// ��а�̕`��
	void Update(void);						// ��а�̈ړ��֐��ɂ�����
	UNIT GetUnitType(void) override;		// ���O�ʹ�а���H
private:
	double sigmond(double gain, double x);
	bool init(void) override;
	E_TYPE _eType;
	Vector2 _aim;
	int _moveCnt;
	bool _placement = false;
	int _angle;
};

