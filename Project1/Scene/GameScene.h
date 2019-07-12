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
	unique_Base Update(unique_Base own) override;	// �e�����ްĂ��܂Ƃ߂�
	void Draw(void);			// �ްѽ�ذ݂ł̕`��
	SCN_ID GetSceneID(void);	// ���ǂ��̼��
	void EnemyInstance(ENEMY_T state);
private:
	std::vector<shared_Obj> _objList;
	int _ghGameScreen;			// �ްїp��ذ�
	bool Init(void);			// �ݽ�ݽ�Ȃǂ̏�����
	int _cnt;
	bool _newKey;
	bool _lastKey;
};

