#pragma once
#include <Unit/Obj.h>

class Collision
{
public:
	Collision();
	~Collision();
	bool Update(std::vector<shared_Obj>& list);

private:
	Vector2_D _pos;	// ���W��
	Vector2 _size ;	// ����
	UNIT _type;		// ���
};

