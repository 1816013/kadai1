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
	WAITC,
	MAX
};

enum class E_TYPE
{
	ZAKO,
	GOEI,
	BOSS,	
	MAX
};

enum class E_MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SWIRL,
	AIMING,
	ZOOM,
	MAX
};

using E_AIM = std::vector<std::pair<Vector2_D, E_MOVE_TYPE>>;	// 1�ڂ̗v�f�� �ڕW���W, ��ڂ̗v�f�͈ړ��^�C�v
using ENEMY_T = std::tuple<Vector2_D, Vector2, E_TYPE, E_AIM, int>;



class Enemy :
	public Obj
{
public:
	Enemy();								// �ݽ�׸�
	Enemy(const ENEMY_T& state);			// �����t���ݽ�׸�
	~Enemy();								// �޽�׸�

	void Draw(void) override;				// ��а�̕`��
	void Update(void);						// ��а�̈ړ��֐��ɂ�����
	UNIT GetUnitType(void) override;		// ���O�ʹ�а���H
	void EnemyAnim(void);					// ��а�̱�Ұ��݂����낦��
	bool HitCheck(std::vector<shared_Obj> list) override;	// �����蔻��
	
private:
	void(Enemy::*move)(void);				// �֐��߲��
	void SetMoveProc(void);
	void M_Sigmoid(void);
	void M_Aiming(void);
	void M_Swirl(void);
	void M_Wait(void);
	void M_ZOOM(void);
	bool shot(void);
	bool init(void) override;

	E_TYPE _eType;
	E_AIM _aim;
	int _aimCnt = 0;
	float _rad;
	double Add;
	double AddAngle;
	Vector2_D _startP;
	int WaitCnt = 0;
	int WaitTime;

	Vector2_D storagePos;
	
	Vector2_D nowRange = { 1.0f, 1.0f };
	Vector2_D maxRange = { 1.35f, 1.1f };
	Vector2_D minRange = { 1.0f, 1.0f };
	Vector2_D AddRange = (maxRange - minRange) / 50.0;

	Vector2_D _movement;

	// �ضް���p
	bool _newKey;
	bool _lastKey;

};

