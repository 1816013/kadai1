#pragma once
#include <tuple>
#include <vector>
#include "Obj.h"

enum class E_STATE
{
	VECTOR,
	SIZE,
	TYPE,
	AIM,
	WAITC,
	MAX
};

enum class E_TYPE
{
	A,
	B,
	C,
	MAX
};

enum class E_MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SWIRL,
	AIMING,
	MAX
};

using E_AIM = std::vector<std::pair<Vector2_D, E_MOVE_TYPE>>;	// 1つ目の要素は 目標座標, 二つ目の要素は移動タイプ
using ENEMY_T = std::tuple<Vector2_D, Vector2, E_TYPE, E_AIM, int>;



class Enemy :
	public Obj
{
public:
	Enemy();								// ｺﾝｽﾄﾗｸﾀ
	Enemy(const ENEMY_T& state);					// 引数付きｺﾝｽﾄﾗｸﾀ
	~Enemy();								// ﾃﾞｽﾄﾗｸﾀ

	void Draw(void) override;				// ｴﾈﾐｰの描画
	void Update(void);						// ｴﾈﾐｰの移動関数にしたい
	UNIT GetUnitType(void) override;		// お前はｴﾈﾐｰか？
	void EnemyAnim(void);

	void(Enemy::*move)(void);				// 関数ﾎﾟｲﾝﾀ
	void SetMoveProc(void);
	void M_Sigmoid(void);
	void M_Aiming(void);
	void M_Swirl(void);
	void M_Wait(void);
private:
	bool init(void) override;
	E_TYPE _eType;
	E_AIM _aim;
	int _aimCnt = 0;
	float _angle;
	Vector2_D _speed = { 4,4 };
	double Add;
	double AddAngle;
	Vector2_D _startP;
	Vector2_D Aim;
	int WaitCnt = 0;
	int WaitTime;

	// ﾄﾘｶﾞｰｷｰ用
	bool _newKey;
	bool _lastKey;

};

