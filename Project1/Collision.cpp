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
	bool ColF = false;
	std::vector<shared_Obj> tmpList = list;
	for (auto itr : list) {	// ˆê‚Â
		itr->SetColF(false);
		_pos = itr->pos();
		_size = itr->size();
		_type = itr->GetUnitType();
		for (auto itr2 : list) {	// “ñ‚Â
			auto pos = itr2->pos();
			Vector2 size = itr2->size();
			if (_type != itr2->GetUnitType())
			{
				if (!(_pos.x + _size.x / 2 < pos.x - size.x / 2
					|| _pos.x - _size.x / 2 > pos.x + size.x / 2
					|| _pos.y - _size.y / 2 > pos.y + size.y / 2
					|| _pos.y + _size.y / 2 < pos.y - size.y / 2))
				{
					itr->SetColF(true);
					itr2->SetColF(true);
					if (itr2->GetUnitType() == UNIT::P_SHOT&& _type != UNIT::PLAYER)
					{
						tmpList.erase(std::remove_if(tmpList.begin(),
							tmpList.end(),
							[](shared_Obj& obj) {return (*obj).GetUnitType() == UNIT::PLAYER || (*obj).isColF() == false; }), tmpList.end());
						ColF = true;
					}
					if (_type == UNIT::ENEMY && itr2->GetUnitType() == UNIT::PLAYER)
					{
						tmpList.erase(std::remove_if(tmpList.begin(),
							tmpList.end(),
							[](shared_Obj& obj) {return (*obj).GetUnitType() == UNIT::P_SHOT || (*obj).GetUnitType() == UNIT::E_SHOT || (*obj).GetUnitType() == UNIT::ENEMY || (*obj).isColF() == false; }), tmpList.end());
						ColF = true;

					}
					if (itr2->GetUnitType() == UNIT::E_SHOT && _type != UNIT::ENEMY)
					{
						tmpList.erase(std::remove_if(tmpList.begin(),
							tmpList.end(),
							[](shared_Obj& obj) {return (*obj).GetUnitType() == UNIT::ENEMY || (*obj).isColF() == false; }), tmpList.end());
						ColF = true;

					}
				}
			}
		}
	}
	
	if (ColF)
	{
		for (auto itr : tmpList)
		{	// ˆê‚Â
			//itr->SetAlive(false);
			itr->submitLife();
		}
	}
	return true;
}