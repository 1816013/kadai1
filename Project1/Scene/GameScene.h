#pragma once
#include <list>
#include <memory>
#include <vector>
#include "BaseScene.h"
#include <Unit/Obj.h>
#include <Unit/Enemy.h>
#include "Shot.h"
#include <Input/InputState.h>

using vecVec2_D = std::vector<Vector2_D>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;	// Še±¯ÌßÃŞ°Ä‚ğ‚Ü‚Æ‚ß‚é
	void Draw(void);			// ¹Ş°Ñ½¸Ø°İ‚Å‚Ì•`‰æ
	SCN_ID GetSceneID(void);	// ¡‚Ç‚±‚Ì¼°İ
	void EnemyInstance(ENEMY_T state);
private:
	std::unique_ptr<InputState> _inputState;
	std::vector<shared_Obj> _objList;	// ·¬×Ši”[—p
	int _ghGameScreen;			// ¹Ş°Ñ—p½¸Ø°İ
	bool Init(void);			// ²İ½Àİ½‚È‚Ç‚Ì‰Šú‰»
	E_AIM eMoveCon;
	Vector2_D sigAim[2];
	Vector2_D sigAim2[2];
	vecVec2_D _bossAim;
	vecVec2_D _goeiAim;
	vecVec2_D _zakoAim;
	std::vector<vecVec2_D> _enAim;
	std::vector<ShotPair> _shotList;
	bool _newKey;
	bool _lastKey;
	int _arrivalCnt;
};

