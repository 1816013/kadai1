#pragma once
#include "Obj.h"
#include <memory>
#include <Input/KeyState.h>

class Player :
	public Obj
{
public:
	Player();							// ｺﾝｽﾄﾗｸﾀ
	Player(const Vector2_D& vec, const Vector2& size);	// 引数付きｺﾝｽﾄﾗｸﾀ
	~Player();							// ﾃﾞｽﾄﾗｸﾀ
	void Update(void);					// ﾌﾟﾚｲﾔｰの移動処理関数
	void Draw(void) override;			// ﾌﾟﾚｲﾔｰ描画
	UNIT GetUnitType(void) override;	// お前はﾌﾟﾚｲﾔｰか？
	bool HitCheck(std::vector<shared_Obj> list)override;	// 当たり判定
	
private:
	bool init(void) override;			// 描画ﾃﾞｰﾀの初期化など
	std::unique_ptr<InputState> _inputState;	
	int _remain;						// 残機
};