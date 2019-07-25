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
	init();
}

Shot::~Shot()
{
}

void Shot::Update(void)
{
	_dbgDrawBox(_pos.x - _size.x, _pos.y - _size.y , _pos.x + _size.x , _pos.y + _size.y , 0xffffff, true);
	_pos.y -= 3;
	if (_pos.y < 0)
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
	if (GetUnitType() == UNIT::PLAYER)
	{
		AnimVector data;
		data.reserve(1);
		data.emplace_back(IMAGE_ID("’e")[1], 10);
		SetAnim(ANIM::NOMAL, data);
	}
	if (GetUnitType() == UNIT::ENEMY)
	{
		AnimVector data;
		data.reserve(1);
		data.emplace_back(IMAGE_ID("’e")[0], 10);
		SetAnim(ANIM::NOMAL, data);
	}
	return true;
}
