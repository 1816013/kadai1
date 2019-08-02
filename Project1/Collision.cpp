#include "collision.h"

Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::Update(std::vector<shared_Obj> list)
{
	//for (auto itr : list) {	// ˆê‚Â
	//	if (itr->GetUnitType() == UNIT::ENEMY)
	//	{
	//		auto pos = itr->pos();
	//		Vector2 size = itr->size();		
	//		if (!(_pos.x + _size.x / 2 < pos.x - size.x / 2
	//			|| _pos.x - _size.x / 2 > pos.x + size.x / 2
	//			|| _pos.y - _size.y / 2 > pos.y + size.y / 2
	//			|| _pos.y + _size.y / 2 < pos.y - size.y / 2))
	//	
	//	}
	//}
	return false;
}