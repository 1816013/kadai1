#pragma once
#include <vector>
#include <memory>
#include <map>
#include <common/VECTOR2.h>

enum class ANIM
{
	NOMAL,		// 通常
	EX,			// 特殊
	DEATH,		// 爆発
	MAX
};

enum class UNIT
{
	PLAYER,
	P_SHOT,
	ENEMY,
	E_SHOT,
	MAX
};

class Obj;
using unique_Obj = std::unique_ptr<Obj>;	
using shared_Obj = std::shared_ptr<Obj>;

using AnimVector = std::vector<std::pair<int, int>>;	//　一つ目の引数はﾊﾝﾄﾞﾙ二つ目の引数はｶｳﾝﾀ
				 //std::vector<std::vector<int>>
				 //std::vector<std::array<2,int>>
class Obj
{
public:
	Obj();								// ｺﾝｽﾄﾗｸﾀ
	virtual ~Obj();						// ﾃﾞｽﾄﾗｸﾀ
	virtual void Draw(void);			// ｱﾆﾒｰｼｮﾝ管理の描画
	void Draw(int id);					// ｽﾃｰｼﾞ数の描画
	virtual void Update(void) = 0;		// ｵﾌﾞｼﾞｪｸﾄの操作行動
	virtual UNIT GetUnitType(void) = 0;	// ｷｬﾗの種類の取得
	virtual bool init(void) = 0;		// ｱﾆﾒｰｼｮﾝの初期化初期設定
	virtual bool HitCheck(std::vector<shared_Obj> list) = 0; // 当たり判定
	const ANIM animKey(void) const;		// _animKeyの取得
	bool animKey(const ANIM key);		// _animKeyの設定
	const Vector2_D pos(void) const;	// ｵﾌﾞｼﾞｪｸﾄの座標取得
	const Vector2 size(void) const;		// ｵﾌﾞｼﾞｪｸﾄの大きさ取得
	void SetAlive(bool flag);			// 生きているかの設定
	bool isAlive(void) { return _alive; };	// 叙述関数(ﾌﾟﾚﾃﾞｨｹｰﾄ)やられたか
	bool isDeath(void) { return _death; };	// 叙述関数(ﾌﾟﾚﾃﾞｨｹｰﾄ)死んでるか
	bool isShot(void) { return _shotF; };	// 叙述関数(ﾌﾟﾚﾃﾞｨｹｰﾄ)撃っているか
	void SetColF(bool flag);
	bool isColF(void) { return _colF; };
	int submitLife(void) { return _life -= 1; };

	// 仮
	bool AllArrivalF(bool flag);		// 全員到着したかのｾｯﾄ
	

private:
	std::map<ANIM, AnimVector> _animMap;
	ANIM _animKey;						// ｱﾆﾒｰｼｮﾝの名前
protected:
	int _animCnt;						// ｱﾆﾒｰｼｮﾝのｶｳﾝﾀ
	int _animFrame;						// ｱﾆﾒｰｼｮﾝの現在のｺﾏ
	bool SetAnim(const ANIM key, AnimVector& data);	// ｱﾆﾒｰｼｮﾝのｾｯﾄ
	bool isAnimEnd(void);				// ｱﾆﾒｰｼｮﾝの終了
	bool DestroyProc(void);				// やられたあとの制御
	Vector2_D _pos;						// ｷｬﾗの座標
	Vector2 _size;						// ｷｬﾗのｻｲｽﾞ
	Vector2_D _speed;					// ｷｬﾗの速度
	bool _alive;						// 生きているか
	bool _death;						// 死んでいるか
	float _angle;						// 角度
	int _life;							// HP
	bool _shotF;						// ｼｮｯﾄ撃っているか
	bool _colF;							// 衝突
	
	// 仮
	bool _AllArrivalF;					// 全員到着したか(ｴﾈﾐｰのみ)
};

