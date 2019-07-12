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
	unique_Base Update(unique_Base own) override;	// Še±¯ÌßÃŞ°Ä‚ğ‚Ü‚Æ‚ß‚é
	void Draw(void);			// ¹Ş°Ñ½¸Ø°İ‚Å‚Ì•`‰æ
	SCN_ID GetSceneID(void);	// ¡‚Ç‚±‚Ì¼°İ
	void EnemyInstance(ENEMY_T state);
private:
	std::vector<shared_Obj> _objList;
	int _ghGameScreen;			// ¹Ş°Ñ—p½¸Ø°İ
	bool Init(void);			// ²İ½Àİ½‚È‚Ç‚Ì‰Šú‰»
	int _cnt;
	bool _newKey;
	bool _lastKey;
};

