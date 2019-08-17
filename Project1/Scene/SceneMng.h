#pragma once
#include <memory>
#include <vector>
#include <Scene/BaseScene.h>
#include <common/VECTOR2.h>

#define lpSceneMng SceneMng::GetInstance()

using DrawQueT = std::tuple<int, int, int>;	// ���̨�������, x���W, y���W

enum class DRAW_QUE
{
	IMAGE,	// �����
	X,		// X���W
	Y		// Y���W
};


class SceneMng
{
public:
	static SceneMng &GetInstance(void)	
	{
		return (*s_Instance);
	}
	void Run(void);	// �����ݒ�

	bool addDrawQue(DrawQueT dQue);		// �`��p�̷���ɏ���}������

	const Vector2 screenSize;		// ����޳�̻���(800, 600)
	const Vector2 gameScreenSize;	// �ްѽ�ذ݂̻���(500, 390)
	const Vector2 gameScreenPos;	// �ްѽ�ذ݂̍����pos

	int Frame(void);				// ��Ұ��ݗp�ڰт�n��
private:
	struct SceneDeleter							// ��ذ��
	{
		void operator()(SceneMng* sceneMng)
		{
			delete sceneMng;
		}
	};
	SceneMng();
	~SceneMng();

	bool SysInit(void);	// ���я�����(�ŏ��̂ݏ������������)
	void Draw(void);	// �`��̷�������Ƃɕ`�悵�Ă���
	std::vector <DrawQueT> _drawList;	// �`��̷��

	// �ϐ�
	static std::unique_ptr<SceneMng, SceneDeleter> s_Instance;		
	unique_Base _activeScene;		// ���݂̼��
	SCN_ID _nowScnID;						// ���݂̼��ID
	SCN_ID _nextScnID;						// ���݂̼��ID
	int frame = 0;		// ��Ұ��ݗp�ڰ�


};

