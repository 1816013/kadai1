#pragma once
#include <Unit/Obj.h>

class Collision
{
public:
	Collision();
	~Collision();
	bool Update(std::vector<shared_Obj> list);
};

