#pragma once
#include "BaseScene.h"
#include <string>
#include <common/VECTOR2.h>
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own) override;	// �e�����ްĂ��܂Ƃ߂�
	void Draw(void);								// ���ٽ�ذ݂ł̕`��
	SCN_ID GetSceneID(void);						// ���̼�݂��擾
	SCN_ID NextSceneID(void);						// ���̼�݂��擾
private:
	void DrawChar(std::string str, Vector2 pos);	// ������̕`��p
	int _ghTitleScreen;			// �ް����ٗp��ذ�
};

