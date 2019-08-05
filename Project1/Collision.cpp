#include <algorithm>
#include "collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::Update(std::vector<shared_Obj>& list)
{
	//std::vector<shared_Obj> tmpList = list;
	//for (auto itr : list) {	// ˆê‚Â
	//	_pos = itr->pos();
	//	_size = itr->size();
	//	_type = itr->GetUnitType();
	//	if (itr->GetUnitType() == UNIT::PLAYER)
	//	{
	//		std::remove_if(tmpList.begin(),
	//			tmpList.end(),
	//			[](shared_Obj& obj) {return (*obj).GetUnitType() == UNIT::PLAYER && (*obj).GetUnitType() == UNIT::ENEMY; });
	//	}
	//	if (itr->GetUnitType() == UNIT::P_SHOT)
	//	{
	//		std::remove_if(tmpList.begin(),
	//			tmpList.end(),
	//			[](shared_Obj& obj) {return (*obj).GetUnitType() == UNIT::ENEMY && (*obj).GetUnitType() == UNIT::PLAYER; });
	//	}
	//	if (itr->GetUnitType() == UNIT::ENEMY)
	//	{
	//		std::remove_if(tmpList.begin(),
	//			tmpList.end(),
	//			[](shared_Obj& obj) {return (*obj).GetUnitType() == UNIT::PLAYER && (*obj).GetUnitType() == UNIT::ENEMY; });
	//	}
	//	if (itr->GetUnitType() == UNIT::E_SHOT)
	//	{
	//		std::remove_if(tmpList.begin(),
	//			tmpList.end(),
	//			[](shared_Obj& obj) {return (*obj).GetUnitType() == UNIT::PLAYER && (*obj).GetUnitType() == UNIT::E_SHOT; });
	//	}
	//	for (auto itr2 : tmpList) {	// “ñ‚Â
	//		auto pos = itr2->pos();
	//		Vector2 size = itr2->size();
	//		if (_type != itr2->GetUnitType())
	//		{
	//			if (!(_pos.x + _size.x / 2 < pos.x - size.x / 2
	//				|| _pos.x - _size.x / 2 > pos.x + size.x / 2
	//				|| _pos.y - _size.y / 2 > pos.y + size.y / 2
	//				|| _pos.y + _size.y / 2 < pos.y - size.y / 2))
	//			{
	//				itr->SetAlive(false);
	//			}
	//		}
	//	}
	//}
	/*if (ColF)
	{
		for (auto itr : tmpList)
		{
			
		}
		ColF = false;
	}*/
	return true;
}