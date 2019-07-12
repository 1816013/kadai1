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
	Enemy();								// ｺﾝｽﾄﾗｸﾀ
	Enemy(ENEMY_T state);					// 引数付きｺﾝｽﾄﾗｸﾀ
	~Enemy();								// ﾃﾞｽﾄﾗｸﾀ
	void Draw(void) override;				// ｴﾈﾐｰの描画
	void Update(void);						// ｴﾈﾐｰの移動関数にしたい
	UNIT GetUnitType(void) override;		// お前はｴﾈﾐｰか？
private:
	bool init(void) override;
	E_TYPE _eType;
	Vector2 _aim;
	int _moveCnt;
	bool _placement = false;
};

