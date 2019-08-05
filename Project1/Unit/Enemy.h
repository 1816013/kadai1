#pragma once
#include <tuple>
#include <vector>
#include "Obj.h"

enum class E_STATE	// ｴﾈﾐｰｽﾃｰﾀｽ
{
	VECTOR,		// 座標
	SIZE,		// ｻｲｽﾞ
	TYPE,		// 種類
	AIM,		// 目標点
	WAITC,		// 待機時間
	MAX
};

enum class E_TYPE	// ｴﾈﾐｰの種類
{
	ZAKO,	// ｻﾞｺ
	GOEI,	// ｺﾞｴｲ
	BOSS,	// ﾎﾞｽ
	MAX
};

enum class E_MOVE_TYPE	// 移動ﾀｲﾌﾟ
{
	WAIT,		// 待機
	SIGMOID,	// ｼｸﾞﾓｲﾄﾞ
	SWIRL,		// 渦巻
	AIMING,		// 一直線
	ZOOM,		// 拡大縮小
	MAX
};

using E_AIM = std::vector<std::pair<Vector2_D, E_MOVE_TYPE>>;	//  目標座標, 移動タイプ
using ENEMY_T = std::tuple<Vector2_D, Vector2, E_TYPE, E_AIM, int>;	// 座標, ｻｲｽﾞ, 種類, 目標座標, 待機時間 



class Enemy :
	public Obj
{
public:
	Enemy();								// ｺﾝｽﾄﾗｸﾀ
	Enemy(const ENEMY_T& state);			// 引数付きｺﾝｽﾄﾗｸﾀ
	~Enemy();								// ﾃﾞｽﾄﾗｸﾀ

	void Draw(void) override;				// ｴﾈﾐｰの描画
	void Update(void);						// ｴﾈﾐｰの移動関数にしたい
	UNIT GetUnitType(void) override;		// お前はｴﾈﾐｰか？
	void EnemyAnim(void);					// ｴﾈﾐｰのｱﾆﾒｰｼｮﾝをそろえる
	bool HitCheck(std::vector<shared_Obj> list) override;	// 当たり判定
	
private:
	void(Enemy::*move)(void);				// 関数ﾎﾟｲﾝﾀ
	void SetMoveProc(void);		// 移動制御
	void M_Sigmoid(void);		// ｼｸﾞﾓｲﾄﾞ曲線
	void M_Aiming(void);		// 最終目標に移動
	void M_Swirl(void);			// 渦巻移動
	void M_Wait(void);			// 編隊用待機
	void M_ZOOM(void);			// 拡大縮小
	bool shot(void);			// ｴﾈﾐｰのｼｮｯﾄ
	bool init(void) override;

	E_TYPE _eType;		// ｴﾈﾐｰの種類
	E_AIM _aim;			// ｴﾈﾐｰの目標座標
	int _aimCnt = 0;	// ｴﾈﾐｰの移動順のｶｳﾝﾀ
	float _rad;			// 渦巻の角度
	double Add;			// ｼｸﾞﾓｲﾄﾞ用-10～10まで			
	double AddAngle;	// 渦巻の角度加算用の角度
	Vector2_D _startP;	// ｴﾈﾐｰの初期出現座標
	int WaitCnt = 0;	// 待機用ｶｳﾝﾀ
	int WaitTime;		// 待機時間

	Vector2_D storagePos;	// ｽﾞｰﾑ用最終地点を記録する用
	
	Vector2_D nowRange = { 1.0f, 1.0f };	// 現在のｽﾞｰﾑ倍率
	Vector2_D maxRange = { 1.35f, 1.1f };	// 最大ｽﾞｰﾑ倍率
	Vector2_D minRange = { 1.0f, 1.0f };	// 最小ｽﾞｰﾑ倍率
	Vector2_D AddRange = (maxRange - minRange) / 50.0;	// ｽﾞｰﾑ倍率変更用
};

