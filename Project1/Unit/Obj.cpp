#include <DxLib.h>
#include "Obj.h"
#include "Enemy.h"
#include "common/ImageMng.h"
#include "_DebugDispOut.h"

Obj::Obj()
{
	_animFrame = 0;
	_animKey = ANIM::NOMAL;
}

Obj::~Obj()
{

}

void Obj::Draw(void)
{
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return;
	}
	if (_animMap[_animKey].size() <= _animFrame)
	{
		return;
	}
	if (_animMap[_animKey][_animFrame].second <= _animCnt)
	{
		if (_animMap[_animKey][_animFrame].first != -1)
		{
			_animFrame++;
		}
		if (_animMap[_animKey].size() <= _animFrame)
		{
			_animFrame = 0;
			_animCnt = 0;
		}
	}

	DrawRotaGraph(_pos.x, _pos.y, 1.0, 0, _animMap[_animKey][_animFrame].first, true);
	//_dbgDrawBox(_pos.x, _pos.y, _pos.x + _size.x, _pos.y + _size.y, 0x00ff00, true);
	_animCnt++;
}

void Obj::Draw(int id)
{
	DrawGraph(_pos.x, _pos.y, id, true);
	//_dbgDrawBox(_pos.x, _pos.y, _pos.x + _size.x, _pos.y + _size.y, 0x00ff00, true);
}


const ANIM Obj::animKey(void)const
{
	return _animKey;
}

bool Obj::animKey(const ANIM key)
{
	if ((key < ANIM::NOMAL) || (key > ANIM::MAX))
	{
		return false;
	}
	if (_animKey != key)
	{
		_animCnt = 0;
	}
	_animKey = key;
	return true;
}

const Vector2_D Obj::pos(void) const
{
	return _pos;
}

void Obj::setAlive(bool alive)
{
	_alive = alive;
}

bool Obj::SetAnim(const ANIM key, AnimVector& data)
{
	return _animMap.try_emplace(key, std::move(data)).second; 
	/*if (_animMap.find(key) == _animMap.end()) // ã‚Ìˆ—‚Æˆê
	{
		_animMap.emplace(key, data);
		return true;
	}
	return false;*/
}

bool Obj::isAnimEnd(void)
{
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return false;
	}
	if (_animMap[_animKey].size() <= _animFrame)
	{
		return false;
	}
	return _animMap[_animKey][_animFrame].first == -1 ? true:false;
}

bool Obj::DestroyProc(void)
{
	if (_alive)
	{
		return false;
	}
	if (isAnimEnd())
	{
		_death = true;
	}
	return true;
}
