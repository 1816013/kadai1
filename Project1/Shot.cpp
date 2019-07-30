#include "shot.h"
#include <common/ImageMng.h>
#include <unit/Obj.h>
#include "_DebugConOut.h"
#include "_DebugDispOut.h"

Shot::Shot()
{
}

Shot::Shot(Vector2_D pos,Vector2 size, UNIT type)
{
	_pos = pos;
	_size = size;
	_uType = type;
	_life = 1;
	init();
}

Shot::~Shot()
{
}

void Shot::Update(void)
{
	_dbgDrawBox(_pos.x - _size.x, _pos.y - _size.y , _pos.x + _size.x , _pos.y + _size.y , 0xffffff, true);
	_pos.y -= 7;
	if (_pos.y < 0 || _life < 0)
	{
		_death = true;
		TRACE("’e‚ðíœ\n");
	}
}

UNIT Shot::GetUnitType(void)
{
	return UNIT::SHOT;
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

void Shot::HitCheck(std::vector<shared_Obj> list)
{
	for (auto itr : list) {
		auto pos = itr->pos();
		Vector2 size = { 32, 30 };
		if (itr->GetUnitType() == UNIT::ENEMY && _uType == UNIT::PLAYER && itr->isAlive())
		{
			if (!((*this)._pos.x + (*this)._size.x / 2 < pos.x - size.x / 2
				|| (*this)._pos.x - (*this)._size.x / 2 > pos.x + size.x / 2
				|| (*this)._pos.y - (*this)._size.y / 2 > pos.y + size.y / 2
				|| (*this)._pos.y + (*this)._size.y / 2 < pos.y - size.y / 2))
			{
	 			_life--;
				TRACE("’¼Œ‚’e\n");
			}
		}			
	}
}

UNIT Shot::GetUType(void)
{
	return _uType;
}
