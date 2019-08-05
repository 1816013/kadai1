#include "shot.h"
#include <DxLib.h>
#include <common/ImageMng.h>
#include <unit/Obj.h>
#include <Scene/SceneMng.h>
#include "_DebugConOut.h"
#include "_DebugDispOut.h"

Shot::Shot()
{
}

Shot::Shot(ShotPair state,Vector2 size)
{
	_pos = state.first;
	_size = size;
	_uType = state.second;
	_alive = true;

	init();
}

Shot::~Shot()
{
}

void Shot::Update(void)
{
	_dbgDrawBox(_pos.x - _size.x, _pos.y - _size.y , _pos.x + _size.x , _pos.y + _size.y , 0xffffff, true);
	if (_uType == UNIT::PLAYER)
	{
		_pos.y -= 7;
		_angle = 0;
	}
	if (_uType == UNIT::ENEMY)
	{
		_pos.y += 7;
		_angle = 180 * DX_PI / 180;
	}
	if (_pos.y < 0 || _pos.y > lpSceneMng.gameScreenSize.y || !_alive)
	{
		_death = true;
	}
}

UNIT Shot::GetUnitType(void)
{
	if (_uType == UNIT::PLAYER)
	{
		return UNIT::P_SHOT;
	}
	if (_uType == UNIT::ENEMY)
	{
		return UNIT::E_SHOT;
	}
}

void Shot::Draw(void)
{
}

bool Shot::init(void)
{
	if (_uType == UNIT::PLAYER)
	{
		AnimVector data;
		data.reserve(1);
		data.emplace_back(IMAGE_ID("’e")[1], 10);
		SetAnim(ANIM::NOMAL, data);
	}
	if (_uType == UNIT::ENEMY)
	{
		AnimVector data;
		data.reserve(1);
		data.emplace_back(IMAGE_ID("’e")[0], 10);
		SetAnim(ANIM::NOMAL, data);
	}
	return true;
}

bool Shot::HitCheck(std::vector<shared_Obj> list)
{
	for (auto itr : list) {
		auto pos = itr->pos();
		Vector2 size = itr->size();
		if (itr->GetUnitType() == UNIT::ENEMY && _uType == UNIT::PLAYER && itr->isAlive())
		{
			if (!((*this)._pos.x + (*this)._size.x / 2 < pos.x - size.x / 2
				|| (*this)._pos.x - (*this)._size.x / 2 > pos.x + size.x / 2
				|| (*this)._pos.y - (*this)._size.y / 2 > pos.y + size.y / 2
				|| (*this)._pos.y + (*this)._size.y / 2 < pos.y - size.y / 2))
			{
 				_death = true;
				TRACE("’¼Œ‚’e\n");
				return true;
			}
		}			
	}
	return false;
}

UNIT Shot::GetUType(void)
{
	return _uType;
}
