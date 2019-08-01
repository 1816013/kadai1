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
	unique_Base Update(unique_Base own) override;	// �e�����ްĂ��܂Ƃ߂�
	void Draw(void);			// �ްѽ�ذ݂ł̕`��
	SCN_ID GetSceneID(void);	// ���ǂ��̼��
	void EnemyInstance(ENEMY_T state);
private:
	std::unique_ptr<InputState> _inputState;
	std::vector<shared_Obj> _objList;	// ��׊i�[�p
	int _ghGameScreen;			// �ްїp��ذ�
	bool Init(void);			// �ݽ�ݽ�Ȃǂ̏�����
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

