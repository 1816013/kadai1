#pragma once
#include <memory>

enum class SCN_ID	
{
	TITLE,
	GAME,	// �ްђ��̼��
	GAMEOVER,
	CLEAR,
	MAX
};

class BaseScene;	// ���������Ȃ��Ƹ׽��using�Ŏg���Ȃ�
using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene() {};
	virtual unique_Base Update(unique_Base own) = 0;
	virtual SCN_ID GetSceneID(void) = 0;
	virtual SCN_ID NextSceneID(void) = 0;
	SCN_ID _scnID;	// ���݂̼��ID
};

