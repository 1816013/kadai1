#pragma once
#include <tuple>
#include <vector>
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

enum class E_MOVE_TYPE
{
	SIGMOID,
	CIRCLE,
	UP,
	MAX
};

using E_AIM = std::vector<std::pair<Vector2, E_MOVE_TYPE>>;	// 1�ڂ̗v�f�� �ڕW���W, ��ڂ̗v�f�͈ړ��^�C�v
using ENEMY_T = std::tuple<Vector2_D, Vector2, E_TYPE, E_AIM>;



class Enemy :
	public Obj
{
public:
	Enemy();								// �ݽ�׸�
	Enemy(ENEMY_T state, int cnt);					// �����t���ݽ�׸�
	~Enemy();								// �޽�׸�

	void Draw(void) override;				// ��а�̕`��
	void Update(void);						// ��а�̈ړ��֐��ɂ�����
	UNIT GetUnitType(void) override;		// ���O�ʹ�а���H
	void EnemyAnim(void);

	void(Enemy::*move)(void);				// �֐��߲��
	void SetMoveProc(void);
	void M_Sigmoid(void);
	void M_Aiming(void);
	void M_Swirl(void);
private:
	bool init(void) override;
	E_TYPE _eType;
	E_AIM _aim;
	int _aimCnt = 0;
	int _moveCnt;
	float _angle;
	double _speed = 3;
	double Add;
	double AddAngle;
	Vector2_D _startP;
	Vector2_D Aim;
	bool _newKey;
	bool _lastKey;

};

