#pragma once
#include <list>
#include <memory>
#include <vector>
#include "BaseScene.h"
#include <Unit/Obj.h>
#include <Unit/Enemy.h>
#include <Input/InputState.h>


class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;	// 各ｱｯﾌﾟﾃﾞｰﾄをまとめる
	void Draw(void);			// ｹﾞｰﾑｽｸﾘｰﾝでの描画
	SCN_ID GetSceneID(void);	// 今どこのｼｰﾝ
	void EnemyInstance(ENEMY_T state);
private:
	std::vector<shared_Obj> _objList;	// ｷｬﾗ格納用
	int _ghGameScreen;			// ｹﾞｰﾑ用ｽｸﾘｰﾝ
	bool Init(void);			// ｲﾝｽﾀﾝｽなどの初期化
	int _cnt;

	bool _newKey;
	bool _lastKey;
};

