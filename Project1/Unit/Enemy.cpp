#include <DxLib.h>
#include <cmath>
#include "Enemy.h"
#include "common/ImageMng.h"
#include "_DebugConOut.h"
#include "_DebugDispOut.h"



Enemy::Enemy()
{
	animKey(ANIM::NOMAL2);
	init();
	_alive = true;
	_death = false;
}

Enemy::Enemy(ENEMY_T state)
{
	_eType = std::get<static_cast<int>(E_STATE::TYPE)>(state);
	_pos = std::get<static_cast<int>(E_STATE::VECTOR)>(state);
	_size = std::get<static_cast<int>(E_STATE::SIZE)>(state);
	_aim = std::get<static_cast<int>(E_STATE::AIM)>(state);
	_speed = { 5 , 5 };
	_alive = true;
	_death = false;
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
	/*if (DestroyProc())
	{
		return;
	}
	if (rand() % 300 == 0)
	{
		_alive = false;
		animKey(ANIM::DEATH);
	}*/
	
	if (_pos == _aim && !_placement)
	{
		_placement = true;
		TRACE("”z’uŠ®—¹\n");
	}
	if (_placement)
	{
		_dbgDrawCircle(_pos.x, _pos.y, _size.x / 2, 0xff0000, true);
		
	}

	if (_moveCnt < 60)
	{
		Vector2 aim = { rand()% 100 + 150, rand() % 100 + 220 };
		auto angle = atan2(aim.y - _pos.y, aim.x - _pos.x);
		_pos.x += cos(angle) * 5;
		_pos.y += sin(angle) * 5;

	}
	else
	{
		// ’´‚¦‚»‚¤‚É‚È‚Á‚½‚ç½Ëß°ÄŞ’²®
		if (abs(_aim.x - _pos.x) < _speed.x)
		{
			_speed.x = abs(_aim.x - _pos.x);
		}
		if (abs(_aim.y - _pos.y) < _speed.y)
		{
			_speed.y = abs(_aim.y - _pos.y);
		}
		// –Ú“I’n‚ÉŒü‚©‚¤
		if (_pos.x < _aim.x)
		{
			_pos.x += _speed.x;
		}
		else
		{
			_pos.x -= _speed.x;
		}
		if (_pos.y < _aim.y)
		{
			_pos.y += _speed.y;
		}
		else
		{
			_pos.y -= _speed.y;
		}
	}
	_moveCnt++;
	/*auto angle = atan2(_aim.y - _pos.y, _aim.x - _pos.x);
	_pos.x += cos(angle);
	_pos.y += sin(angle);*/
}

UNIT Enemy::GetUnitType(void)
{
	return UNIT::ENEMY;
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
	return true;
}
