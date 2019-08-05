#pragma once
#include <unit/Obj.h>


using ShotPair = std::pair<Vector2_D, UNIT >;

class Shot : public Obj
{
public:
	Shot();
	Shot(ShotPair state, Vector2 size);
	~Shot();
	void Update(void) override;				// ｼｮｯﾄ移動
	UNIT GetUnitType(void) override;		// 何のｼｮｯﾄか
	void Draw(void) override;				// 描画
	bool init(void) override;				// 初期化
	bool HitCheck(std::vector<shared_Obj> list) override;	// 当たり判定
	UNIT GetUType(void);					// 弾を打ったﾕﾆｯﾄのﾀｲﾌﾟは何か
private:
	UNIT _uType;	// 弾を打ったﾕﾆｯﾄのﾀｲﾌﾟ

};
