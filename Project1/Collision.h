#pragma once
#include <Unit/Obj.h>

class Collision
{
public:
	Collision();
	~Collision();
	bool Update(std::vector<shared_Obj>& list);

private:
	Vector2_D _pos;	// ç¿ïWÇµ
	Vector2 _size ;	// ª≤Ωﬁ
	UNIT _type;		// éÌóﬁ
};

