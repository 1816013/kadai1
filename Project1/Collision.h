#pragma once
#include <Unit/Obj.h>

class Collision
{
public:
	Collision();
	~Collision();
	bool Update(std::vector<shared_Obj>& list);

private:
	Vector2_D _pos;	// 座標し
	Vector2 _size ;	// ｻｲｽﾞ
	UNIT _type;		// 種類
};

