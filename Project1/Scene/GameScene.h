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
	unique_Base Update(unique_Base own) override;	// �e�����ްĂ��܂Ƃ߂�
	void Draw(void);								// �ްѽ�ذ݂ł̕`��
	SCN_ID GetSceneID(void);						// ���̼��
	SCN_ID NextSceneID(void);						// ���̼�݂��擾
	void EnemyInstance(ENEMY_T state);				// ��а��ݽ�ݽ����
private:
	void DrawChar(std::string str, Vector2 pos);	// ������̕`��p

	std::unique_ptr<InputState> _inputState;
	std::vector<shared_Obj> _objList;	// ��׊i�[�p
	std::vector<ShotPair> _shotList;	// ���Ĉꎞ�i�[ؽ�
	int _ghGameScreen;			// �ްїp��ذ�
	bool Init(void);			// �ݽ�ݽ�Ȃǂ̏�����
	E_AIM eMoveCon;				// �ڕW���W�ƈړ����@���i�[�������


	// ��
	vecVec2_D _bossAim;			// �޽�̍ŏI�ڕW
	vecVec2_D _goeiAim;			// �޴��̍ŏI�ڕW
	vecVec2_D _zakoAim;			// �޺�̍ŏI�ڕW
	int _popCnt;				// ��а�̏o���Ԋu�̶���
	int _arrivalCnt;			// ��а���S���o����i�߂鶳�����̗ʂɂȂ�ƴ�а�̓������ς��



	std::unique_ptr<Collision> _col;
};

