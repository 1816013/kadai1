#pragma once
#include <tuple>
#include "Obj.h"

enum class E_STATE
{
	VECTOR,
	SIZE,
	TYPE,
	AIM,
	MAX
};

enum class E_TYPE
{
	A,
	B,
	C,
	MAX
};

using ENEMY_T = std::tuple<Vector2, Vector2, E_TYPE, Vector2>;

class Enemy :
	public Obj
{
public:
	Enemy();								// ºİ½Ä×¸À
	Enemy(ENEMY_T state);					// ˆø”•t‚«ºİ½Ä×¸À
	~Enemy();								// ÃŞ½Ä×¸À
	void Draw(void) override;				// ´ÈĞ°‚Ì•`‰æ
	void Update(void);						// ´ÈĞ°‚ÌˆÚ“®ŠÖ”‚É‚µ‚½‚¢
	UNIT GetUnitType(void) override;		// ‚¨‘O‚Í´ÈĞ°‚©H
private:
	bool init(void) override;
	E_TYPE _eType;
	Vector2 _aim;
};

