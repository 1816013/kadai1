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

using ENEMY_T = std::tuple<Vector2_D, Vector2, E_TYPE, Vector2>;

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
	double sigmoid(double gain, double x);
	bool init(void) override;
	E_TYPE _eType;
	Vector2 _aim;
	int _moveCnt;
	bool _placement = false;
	int _angle;
};

