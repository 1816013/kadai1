#pragma once
#include <tuple>
#include <vector>
#include "Obj.h"

enum class E_STATE	// ��а�ð��
{
	VECTOR,		// ���W
	SIZE,		// ����
	TYPE,		// ���
	AIM,		// �ڕW�_
	WAITC,		// �ҋ@����
	MAX
};

enum class E_TYPE	// ��а�̎��
{
	ZAKO,	// �޺
	GOEI,	// �޴�
	BOSS,	// �޽
	MAX
};

enum class E_MOVE_TYPE	// �ړ�����
{
	WAIT,		// �ҋ@
	SIGMOID,	// ���Ӳ��
	SWIRL,		// �Q��
	AIMING,		// �꒼��
	ZOOM,		// �g��k��
	MAX
};

using E_AIM = std::vector<std::pair<Vector2_D, E_MOVE_TYPE>>;	//  �ڕW���W, �ړ��^�C�v
using ENEMY_T = std::tuple<Vector2_D, Vector2, E_TYPE, E_AIM, int>;	// ���W, ����, ���, �ڕW���W, �ҋ@���� 



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
	void SetMoveProc(void);		// �ړ�����
	void M_Sigmoid(void);		// ���Ӳ�ދȐ�
	void M_Aiming(void);		// �ŏI�ڕW�Ɉړ�
	void M_Swirl(void);			// �Q���ړ�
	void M_Wait(void);			// �ґ��p�ҋ@
	void M_ZOOM(void);			// �g��k��
	bool shot(void);			// ��а�̼���
	bool init(void) override;

	E_TYPE _eType;		// ��а�̎��
	E_AIM _aim;			// ��а�̖ڕW���W
	int _aimCnt = 0;	// ��а�̈ړ����̶���
	float _rad;			// �Q���̊p�x
	double Add;			// ���Ӳ�ޗp-10�`10�܂�			
	double AddAngle;	// �Q���̊p�x���Z�p�̊p�x
	Vector2_D _startP;	// ��а�̏����o�����W
	int WaitCnt = 0;	// �ҋ@�p����
	int WaitTime;		// �ҋ@����

	Vector2_D storagePos;	// �ްїp�ŏI�n�_���L�^����p
	
	Vector2_D nowRange = { 1.0f, 1.0f };	// ���݂̽ްє{��
	Vector2_D maxRange = { 1.35f, 1.1f };	// �ő�ްє{��
	Vector2_D minRange = { 1.0f, 1.0f };	// �ŏ��ްє{��
	Vector2_D AddRange = (maxRange - minRange) / 50.0;	// �ްє{���ύX�p
};

