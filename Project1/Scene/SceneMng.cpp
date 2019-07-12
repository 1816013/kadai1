#include <DxLib.h>
#include <main.h>
#include <common/VECTOR2.h>
#include <common/ImageMng.h>
#include "SceneMng.h"
#include <Scene/GameScene.h>
#include "_DebugConOut.h"
#include "_DebugDispOut.h"

std::unique_ptr<SceneMng, SceneMng::SceneDeleter> SceneMng::s_Instance(new SceneMng);

void SceneMng::Run(void)
{
	SysInit();

	ImageMng::GetInstance().GetID("���", "image/char.png", Vector2(10, 10), Vector2(30, 32));
	ImageMng::GetInstance().GetID("�G����", "image/en_blast.png", Vector2(5, 1), Vector2(64, 64));
	ImageMng::GetInstance().GetID("���@����", "image/pl_blast.png", Vector2(4, 1), Vector2(64, 64));

	_activeScene = std::make_unique<GameScene>();
	// ----------�ް�ٰ��
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_drawList.clear(); // �`��ؽĂ̏�����
		// ��݊Ǘ�
		_activeScene = _activeScene->Update(std::move(_activeScene));
		addDrawQue({ IMAGE_ID("�g")[0], 0, 0 });
		Draw();
		_dbgStartDrawDebug();
	}
	
	DxLib_End();

}

bool SceneMng::addDrawQue(DrawQueT dQue)
{
	//image���ǂ܂�Ă��邩�̃`�F�b�N
	if (std::get<static_cast<int> (DRAW_QUE::IMAGE)>(dQue) == -1)
	{
		return false;
	}
	_drawList.emplace_back(dQue);
	return true;
}

SceneMng::SceneMng() : screenSize{ 800, 600 }, gameScreenSize{ 500, 390 }, gameScreenPos{ 150, 105 }
{
	
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	// ----------���я���
	SetWindowText("�M�����K");
	// ���я���
	SetGraphMode(screenSize.x, screenSize.y, 16);	// 800�~600�h�b�g65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);							// true:window false:�ٽ�ذ�
	if (DxLib_Init() == -1)
	{
		return false;				//DXײ���؏���������
	}
	// TRACE("DXLIB����������\n");
	
	SET_IMAGE_ID("�g", "image/frame.png");
	_dbgSetUp(200);
#ifdef DEBUG
	_DebugConOut::GetInstance();
#endif // DEBUG
	


	return true;
}

void SceneMng::Draw(void)
{
	_dbgAddDrawDebug();
	SetDrawScreen(DX_SCREEN_BACK);					//�ЂƂ܂��ޯ��ޯ̧�ɕ`��
	ClsDrawScreen(); //��ʏ���
	// ���̨������قƍ��W���K�v
	for (auto _dQue : _drawList)
	{
		DrawGraph(std::get<static_cast<int> (DRAW_QUE::X)>(_dQue),
				  std::get<static_cast<int> (DRAW_QUE::Y)>(_dQue), 
				  std::get<static_cast<int> (DRAW_QUE::IMAGE)>(_dQue),
				  true);
	}
	
	ScreenFlip();	//����ʂ�\��ʂɏu�Ժ�߰
}
