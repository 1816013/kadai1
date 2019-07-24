#include <DxLib.h>
#include <cmath>
#include "Enemy.h"
#include <common/ImageMng.h>
#include <scene/SceneMng.h>
#include "_DebugConOut.h"
#include "_DebugDispOut.h"



Enemy::Enemy()
{
	animKey(ANIM::NOMAL2);
	init();
	_alive = true;
	_death = false;
}

Enemy::Enemy(const ENEMY_T& state)
{
	_eType = std::get<static_cast<int>(E_STATE::TYPE)>(state);
	_pos = std::get<static_cast<int>(E_STATE::VECTOR)>(state);
	//_pos = { 0,350 };
	_size = std::get<static_cast<int>(E_STATE::SIZE)>(state);
	_aim = std::get<static_cast<int>(E_STATE::AIM)>(state);
	WaitTime = std::get<static_cast<int>(E_STATE::WAITC)>(state);
	_startP = _pos;
	_alive = true;
	_death = false;
	Aim = {(double) 100, (double)lpSceneMng.gameScreenSize.y / 2 - 16 };
	Add = -10;
	_angle = 0;
	AddAngle = 0;
	init();
	TRACE("enemy�̐���\n");
}

Enemy::~Enemy()
{
	TRACE("enemy�̔j��\n");
}

void Enemy::Draw(void)
{
	//DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("���"/*, "image/char.png", Vector2(10, 10), Vector2(30, 32)*/)[10], true);
}

void Enemy::Update(void)
{
	_dbgDrawCircle(_pos.x, _pos.y, _size.x / 2, 0xff0000, true);
	/*if (DestroyProc())
	{
		return;
	}
	if (rand() % 300 == 0)
	{
		_alive = false;
		animKey(ANIM::DEATH);
	}*/
 	SetMoveProc();
	(this->*move)();
}

UNIT Enemy::GetUnitType(void)
{
	return UNIT::ENEMY;
}

void Enemy::EnemyAnim(void)
{
	_animCnt = lpSceneMng.Frame() % 60;
}

void Enemy::SetMoveProc(void)
{
	if (_aim[_aimCnt].second == E_MOVE_TYPE::WAIT)
	{
		move = &Enemy::M_Wait;
	}
	if (_aim[_aimCnt].second == E_MOVE_TYPE::SIGMOID)
	{
		move = &Enemy::M_Sigmoid;
	}
	if (_aim[_aimCnt].second == E_MOVE_TYPE::SWIRL)
	{
		move = &Enemy::M_Swirl;
	}
	if (_aim[_aimCnt].second == E_MOVE_TYPE::AIMING)
	{
		move = &Enemy::M_Aiming;
	}
	/*if (_moveCnt < 36000)
	{
		
	}
	else
	{
		move = &Enemy::M_Aiming;
	}*/
}

void Enemy::M_Sigmoid(void)
{
	Vector2_D range;
	auto sigmoid = [](double ran, double x) { return ran / (1.0 + exp(-1.0 * x )); };
	Add += 0.2; 
	range = { _aim[_aimCnt].first.x -  _startP.x , _aim[_aimCnt].first.y - _startP.y  };
	if (Add <= 10.0)
	{
		//	x���K��(Add + 10) / 20�@=  (0.0 �` 1.0 �` ��)
							//  Add =   -10 �`  10 �` ��
		_pos.x = (Add + 10) / 20 * range.x + _startP.x;
		// y���K���V�O���C�h�͍ŏ�����y�͐��K������Ă���
		_pos.y = sigmoid(range.y, Add) + _startP.y;
	}
	else
	{
		Add = -10;
		_startP = _pos;
		//move = &Enemy::SetMoveProc;
		_aimCnt++;
		
	}
	//TRACE( "%f  %f\n", Add, sigmoid(range.y, Add)) + _startP.y;
	//move = &Enemy::SetMoveProc;
}

void Enemy::M_Aiming(void)
{

	_angle = atan2(_aim[_aimCnt].first.y - _pos.y, _aim[_aimCnt].first.x - _pos.x);
	if (abs((int)_aim[_aimCnt].first.x - _pos.x) < _speed.x)
	{
		_speed.x = abs((int)_aim[_aimCnt].first.x - _pos.x);
	}
	if (abs((int)_aim[_aimCnt].first.y - _pos.y) < _speed.y)
	{
		_speed.y = abs((int)_aim[_aimCnt].first.y - _pos.y);
	}

	_pos.x += cos(_angle) * _speed.x;
	_pos.y += sin(_angle) * _speed.y;
	
}

void Enemy::M_Swirl(void)
{
	_angle += (3.5 + AddAngle) * DX_PI / 180;
	_pos.x += cos(_angle) * -_speed.x * 2;
	_pos.y -= sin(_angle) * _speed.y * 2 ;
	AddAngle += 0.05;
	if (_angle > abs(540 * DX_PI / 180 ))
	{
		//move = &Enemy::SetMoveProc;
		_aimCnt++;
	}
}

void Enemy::M_Wait(void)
{
	if (WaitTime < WaitCnt)
	{
		//move = &Enemy::SetMoveProc;
		_aimCnt++;
	}
	WaitCnt++;
}



bool Enemy::init(void)
{
	AnimVector data;
	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("player")[0], 30));
	data.emplace_back(IMAGE_ID("���")[10 + 10 * static_cast<int>(_eType)], 30);
	data.emplace_back(IMAGE_ID("���")[11 + 10 * static_cast<int>(_eType)], 60);
	SetAnim(ANIM::NOMAL, data);

	/*data.emplace_back(IMAGE_ID("���")[20], 30);
	data.emplace_back(IMAGE_ID("���")[21], 60);
	SetAnim(ANIM::NOMAL2, data);

	data.emplace_back(IMAGE_ID("���")[30], 30);
	data.emplace_back(IMAGE_ID("���")[31], 60);
	SetAnim(ANIM::NOMAL3, data);*/

	data.reserve(6);
	data.emplace_back(IMAGE_ID("�G����")[0], 5);
	data.emplace_back(IMAGE_ID("�G����")[1], 15);
	data.emplace_back(IMAGE_ID("�G����")[2], 25);
	data.emplace_back(IMAGE_ID("�G����")[3], 35);
	data.emplace_back(IMAGE_ID("�G����")[4], 45);
	data.emplace_back(-1, 55);

	SetAnim(ANIM::DEATH, data);
	EnemyAnim();
	return true;
}
