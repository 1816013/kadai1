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
	_moveCnt = 0;
	move = &Enemy::SetMoveProc;
}

Enemy::Enemy(ENEMY_T state, int cnt)
{
	_eType = std::get<static_cast<int>(E_STATE::TYPE)>(state);
	_pos = std::get<static_cast<int>(E_STATE::VECTOR)>(state);
	//_pos = { 0,350 };
	_size = std::get<static_cast<int>(E_STATE::SIZE)>(state);
	_aim = std::get<static_cast<int>(E_STATE::AIM)>(state);
	_aimCnt = cnt;
	_startP = _pos;
	_alive = true;
	_death = false;
	Aim = {(double) 100, (double)lpSceneMng.gameScreenSize.y / 2 - 16 + 50 };
	move = &Enemy::SetMoveProc;
	Add = -10;
	init();
	TRACE("enemyÌ¶¬\n");
}

Enemy::~Enemy()
{
	TRACE("enemyÌjü\n");
}

void Enemy::Draw(void)
{
	//DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("·¬×"/*, "image/char.png", Vector2(10, 10), Vector2(30, 32)*/)[10], true);
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
	
	(this->*move)();
	_moveCnt++;
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
	move = &Enemy::M_Aiming;
	/*if (_moveCnt < 36000)
	{
		move = &Enemy::M_Sigmoid;
	}
	else
	{
		
	}*/
}

void Enemy::M_Sigmoid(void)
{
	Vector2_D range;

	
	auto sigmoid = [](double ran, double x) { return ran / (1.0 + exp(-1.0 * x )); };
	Add += 0.1;
	//range = 300;
	range = { static_cast<double> (abs(static_cast<int>(_startP.x )- Aim.x)), static_cast<double> (abs(static_cast<int>(_startP.y) - Aim.y)) };
	if (std::round(_pos.x ) != Aim.x)
	{
		if (_startP.y > Aim.y)
		{ 
			_pos.y = sigmoid(-range.y, Add) + _startP.y;
		}
		else
		{
			_pos.y = sigmoid(range.y, Add) + _startP.y;
		}
		if (_startP.x < Aim.x)
		{
			_pos.x += 2;
		}
		else
		{
			_pos.x -= 2;
		}
	}
	else
	{
		//move = &Enemy::M_Aiming;
	}
	/*if (CheckHitKey(KEY_INPUT_0))
	{
		_startP = Aim;
		Aim = { (double)300, (double)lpSceneMng.gameScreenSize.y / 2 - 16 - 100 };
		
	}*/

	//TRACE( "%f  %f\n", Add, sigmoid(range.y, Add)) + _startP.y;
	//move = &Enemy::SetMoveProc;
}

void Enemy::M_Aiming(void)
{
	if (std::round(_pos.x) != Aim.x || std::round(_pos.y) != Aim.y)
	{
		_angle = atan2(_aim[_aimCnt % 21].first.y - _pos.y, _aim[_aimCnt % 21].first.x - _pos.x);
		_pos.x += cos(_angle) * _speed;
		_pos.y += sin(_angle) * _speed;
	}
}

void Enemy::M_Swirl(void)
{
}



bool Enemy::init(void)
{
	AnimVector data;
	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("player")[0], 30));
	data.emplace_back(IMAGE_ID("·¬×")[10 + 10 * static_cast<int>(_eType)], 30);
	data.emplace_back(IMAGE_ID("·¬×")[11 + 10 * static_cast<int>(_eType)], 60);
	SetAnim(ANIM::NOMAL, data);

	/*data.emplace_back(IMAGE_ID("·¬×")[20], 30);
	data.emplace_back(IMAGE_ID("·¬×")[21], 60);
	SetAnim(ANIM::NOMAL2, data);

	data.emplace_back(IMAGE_ID("·¬×")[30], 30);
	data.emplace_back(IMAGE_ID("·¬×")[31], 60);
	SetAnim(ANIM::NOMAL3, data);*/

	data.reserve(6);
	data.emplace_back(IMAGE_ID("G­")[0], 5);
	data.emplace_back(IMAGE_ID("G­")[1], 15);
	data.emplace_back(IMAGE_ID("G­")[2], 25);
	data.emplace_back(IMAGE_ID("G­")[3], 35);
	data.emplace_back(IMAGE_ID("G­")[4], 45);
	data.emplace_back(-1, 55);

	SetAnim(ANIM::DEATH, data);
	EnemyAnim();
	return true;
}
