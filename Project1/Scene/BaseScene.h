#pragma once
#include <memory>

enum class SCN_ID	
{
	GAME,	// �ްђ��̼��
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
};

