#pragma once
#include <list>
#include <memory>
#include <vector>
#include "BaseScene.h"
#include <Unit/Obj.h>
#include <Unit/Enemy.h>
#include <Unit/Shot.h>
#include <Input/InputState.h>
#include "Collision.h"

using vecVec2_D = std::vector<Vector2_D>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;	// 各ｱｯﾌﾟﾃﾞｰﾄをまとめる
	void Draw(void);								// ｹﾞｰﾑｽｸﾘｰﾝでの描画
	SCN_ID GetSceneID(void);						// 今のｼｰﾝ
	SCN_ID NextSceneID(void);						// 次のｼｰﾝを取得
	void EnemyInstance(ENEMY_T state);				// ｴﾈﾐｰをｲﾝｽﾀﾝｽする
private:
	void DrawChar(std::string str, Vector2 pos);	// 文字列の描画用

	std::unique_ptr<InputState> _inputState;
	std::vector<shared_Obj> _objList;	// ｷｬﾗ格納用
	std::vector<ShotPair> _shotList;	// ｼｮｯﾄ一時格納ﾘｽﾄ
	int _ghGameScreen;			// ｹﾞｰﾑ用ｽｸﾘｰﾝ
	bool Init(void);			// ｲﾝｽﾀﾝｽなどの初期化
	E_AIM eMoveCon;				// 目標座標と移動方法を格納するもの


	// 仮
	vecVec2_D _bossAim;			// ﾎﾞｽの最終目標
	vecVec2_D _goeiAim;			// ｺﾞｴｲの最終目標
	vecVec2_D _zakoAim;			// ｻﾞｺの最終目標
	int _popCnt;				// ｴﾈﾐｰの出現間隔のｶｳﾝﾀ
	int _arrivalCnt;			// ｴﾈﾐｰが全部出たら進めるｶｳﾝﾀ一定の量になるとｴﾈﾐｰの動きが変わる



	std::unique_ptr<Collision> _col;
};

