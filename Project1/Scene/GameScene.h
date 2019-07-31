#pragma once
#include <list>
#include <memory>
#include <vector>
#include "BaseScene.h"
#include <Unit/Obj.h>
#include <Unit/Enemy.h>
#include <Input/InputState.h>

using vecVec2_D = std::vector<Vector2_D>;

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
	E_AIM eMoveCon;
	Vector2_D aim[21];
	Vector2_D sigAim[2];
	Vector2_D sigAim2[2];
	vecVec2_D _bossAim;
	vecVec2_D _goeiAim;
	vecVec2_D _zakoAim;
	std::vector<vecVec2_D> _enAim;
	bool _newKey;
	bool _lastKey;
	bool _newKey2;
	bool _lastKey2;
	int _arrivalCnt;
};

