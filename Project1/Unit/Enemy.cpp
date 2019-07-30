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
	_rad = 0;
	AddAngle = 0;
	init();
	TRACE("enemy‚Ì¶¬\n");
}

Enemy::~Enemy()
{
	TRACE("enemy‚Ì”jŠü\n");
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
	range = { _aim[_aimCnt].first.x - _startP.x , _aim[_aimCnt].first.y - _startP.y  };
	if (Add <= 10.0)
	{
		//	x³‹K‰»(Add + 10) / 20@=  (0.0 ` 1.0 ` ‡)
							//  Add =   -10 `  10 ` ‡
		_pos.x = (Add + 10 ) / 20 * range.x + _startP.x;
		// y³‹K‰»ƒVƒOƒ‚ƒCƒh‚ÍÅ‰‚©‚çy‚Í³‹K‰»‚³‚ê‚Ä‚¢‚é
		_pos.y = sigmoid(range.y, Add) + _startP.y;
	}
	else
	{
		Add = -10;
		_startP = _pos;
		_aimCnt++;
		
	}
	Vector2_D move;
	move.x = (Add + 0.2 + 10) / 20 * range.x + _startP.x;
	move.y = sigmoid(range.y, Add + 0.2) + _startP.y;
	_angle = atan2(move.y - _pos.y, move.x - _pos.x) + 90 * DX_PI / 180;
	//TRACE( "%f  %f\n", Add, sigmoid(range.y, Add)) + _startP.y;
	//move = &Enemy::SetMoveProc;
}

void Enemy::M_Aiming(void)
{

	_rad = atan2(_aim[_aimCnt].first.y - _pos.y, _aim[_aimCnt].first.x - _pos.x);
	if (abs((int)_aim[_aimCnt].first.x - _pos.x) < _speed.x)
	{
		_speed.x = abs((int)_aim[_aimCnt].first.x - _pos.x);
	}
	if (abs((int)_aim[_aimCnt].first.y - _pos.y) < _speed.y)
	{
		_speed.y = abs((int)_aim[_aimCnt].first.y - _pos.y);
	}

	_pos.x += cos(_rad) * _speed.x;
	_pos.y += sin(_rad) * _speed.y;
	if (_aim[_aimCnt].first  / 100.0 == _pos / 100.0)
	{
		_angle = 0;
	}
	else
	{
		_angle = _rad + 90 * DX_PI / 180;
	}
	
}

void Enemy::M_Swirl(void)
{
	_rad += (4.5 + AddAngle) * DX_PI / 180;
	AddAngle += 5 * DX_PI / 180;
	_pos.y -= sin(_rad) * _speed.y * 2;
	
	Vector2_D move = _pos;
	if (_startP.x < lpSceneMng.gameScreenSize.x / 2)
	{
		move.x += cos(_rad) * -_speed.x * 2;
		_pos = move;
		move.x += cos(_rad + (4.5 + AddAngle) * DX_PI / 180) * -_speed.x * 2;
	}
	else
	{
		move.x += cos(_rad) * _speed.x * 2;	
		_pos = move;
		move.x += cos(_rad + (4.5 + AddAngle) * DX_PI / 180) * _speed.x * 2;

	}
	if (_rad > abs(540 * DX_PI / 180 ))
	{
		_aimCnt++;
	}
	
	//move.x += cos(_rad + (4.5 + AddAngle) * DX_PI / 180) * -_speed.x * 2;
	move.y -= sin(_rad + (4.5 + AddAngle) * DX_PI / 180) * _speed.y * 2;
	_angle = atan2(move.y - _pos.y, move.x - _pos.x) + 90 * DX_PI / 180;
	//_angle = _rad + 90 * DX_PI / 180;
}

void Enemy::M_Wait(void)
{
	if (WaitTime < WaitCnt)
	{
		_aimCnt++;
	}
	WaitCnt++;
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
	data.emplace_back(IMAGE_ID("“G”š”­")[0], 5);
	data.emplace_back(IMAGE_ID("“G”š”­")[1], 15);
	data.emplace_back(IMAGE_ID("“G”š”­")[2], 25);
	data.emplace_back(IMAGE_ID("“G”š”­")[3], 35);
	data.emplace_back(IMAGE_ID("“G”š”­")[4], 45);
	data.emplace_back(-1, 55);

	SetAnim(ANIM::DEATH, data);
	EnemyAnim();
	return true;
}
