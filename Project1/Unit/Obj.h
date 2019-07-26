#pragma once
#include <vector>
#include <memory>
#include <map>
#include <common/VECTOR2.h>

enum class ANIM
{
	NOMAL,		// 通常
	NOMAL2,
	NOMAL3,
	EX,			// 特殊
	DEATH,		// 爆発
	MAX
};

enum class UNIT
{
	PLAYER,
	ENEMY,
	SHOT,
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
	const ANIM animKey(void) const;		// _animKeyの取得
	bool animKey(const ANIM key);		// _animKeyの設定
	const Vector2_D pos(void) const;		// ｵﾌﾞｼﾞｪｸﾄの座標取得
	bool isAlive(void) { return _alive; };	// 叙述関数(ﾌﾟﾚﾃﾞｨｹｰﾄ)
	void setAlive(bool alive);				// 生きているか取得
	bool isDeath(void) { return _death; };	// 叙述関数(ﾌﾟﾚﾃﾞｨｹｰﾄ)
private:
	std::map<ANIM, AnimVector> _animMap;
	ANIM _animKey;						// ｱﾆﾒｰｼｮﾝの名前
	int _animFrame;						// ｱﾆﾒｰｼｮﾝの現在のｺﾏ
	bool _animEnd;
protected:
	int _animCnt;						// ｱﾆﾒｰｼｮﾝのｶｳﾝﾀ
	bool SetAnim(const ANIM key, AnimVector& data);	// ｱﾆﾒｰｼｮﾝのｾｯﾄ
	bool isAnimEnd(void);
	bool DestroyProc(void);
	Vector2_D _pos;						// ｷｬﾗの座標
	Vector2 _size;						// ｷｬﾗのｻｲｽﾞ
	bool _alive;						// 生きているか
	bool _death;
	float _angle;

};

