#pragma once
#include <list>
#include <memory>
#include <vector>
#include "BaseScene.h"
#include <Unit/Obj.h>
#include <Unit/Enemy.h>
#include "Shot.h"
#include <Input/InputState.h>
#include "Collision.h"

using vecVec2_D = std::vector<Vector2_D>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;	// äe±ØÃﬂ√ﬁ∞ƒÇÇ‹Ç∆ÇﬂÇÈ
	void Draw(void);			// πﬁ∞—Ω∏ÿ∞›Ç≈ÇÃï`âÊ
	SCN_ID GetSceneID(void);	// ç°Ç«Ç±ÇÃº∞›
	void EnemyInstance(ENEMY_T state);
private:
	std::unique_ptr<InputState> _inputState;
	std::vector<shared_Obj> _objList;	// ∑¨◊äiî[óp
	int _ghGameScreen;			// πﬁ∞—ópΩ∏ÿ∞›
	bool Init(void);			// ≤›Ω¿›ΩÇ»Ç«ÇÃèâä˙âª
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
	int _popCnt;


	std::unique_ptr<Collision> _col;
};

